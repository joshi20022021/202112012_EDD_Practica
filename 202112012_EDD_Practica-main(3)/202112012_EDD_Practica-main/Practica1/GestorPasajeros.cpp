#include "GestorPasajeros.h"
#include <fstream>
#include "ComparadorPasajero.h"
#include <iostream>
#include <sstream>
#include <nlohmann/json.hpp>
#include "ListaDoblementeEnlazada.h"

using json = nlohmann::json;

void GestorPasajeros::buscarPasajeroEnLista(const std::string& numeroPasaporte) const {
    listaEquipajeCero.buscarPasajero(numeroPasaporte);
}

void GestorPasajeros::mostrarListaEquipajeCeroOrdenada() const {
    listaEquipajeCero.mostrarOrdenadoPorVueloYAsiento();
}

void GestorPasajeros::mostrarPilaEquipaje() const {
    std::cout << "Contenido de la pila de equipaje:" << std::endl;
    pilaEquipajeMayorCero.mostrarPila();
}

void GestorPasajeros::procesarIngresoPasajero(const std::string& otraRuta) {
    if (!frente) {
        std::cout << "No hay pasajeros en la cola." << std::endl;
        return;
    }

    std::ifstream archivo(otraRuta);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << otraRuta << std::endl;
        return;
    }

    std::string linea;
    std::cout << "Contenido del archivo " << otraRuta << ":" << std::endl;
    while (std::getline(archivo, linea)) {
        if (linea.find("IngresoPasajero;") != std::string::npos) {
            NodoPasajero* nodoPasajero = frente;
            frente = frente->siguiente;
            Pasajero pasajero = nodoPasajero->pasajero;
            delete nodoPasajero;

            if (pasajero.equipajeFacturado > 0) {
                listaEquipajeCero.insertarOrdenado(pasajero, ComparadorPasajero());
                pilaEquipajeMayorCero.apilar(pasajero);
            }
        }
    }

    archivo.close();
    listaAviones.procesarMovimientoAvionPublic(otraRuta);
}

void GestorPasajeros::cargarPasajerosDesdeArchivo(const std::string& rutaArchivo) {
    std::ifstream file(rutaArchivo);
    if (!file) {
        std::cout << "Error al abrir el archivo: " << rutaArchivo << std::endl;
        return;
    }

    json data;
    try {
        file >> data;
    } catch (const json::parse_error& e) {
        std::cout << "Error al parsear el archivo JSON: " << e.what() << std::endl;
        return;
    }

    for (const auto& pasajeroData : data) {
        Pasajero pasajero;
        try {
            pasajero.nombre = pasajeroData.at("nombre").get<std::string>();
            pasajero.nacionalidad = pasajeroData.at("nacionalidad").get<std::string>();
            pasajero.numeroPasaporte = pasajeroData.at("numero_de_pasaporte").get<std::string>();
            pasajero.vuelo = pasajeroData.at("vuelo").get<std::string>();
            pasajero.asiento = pasajeroData.at("asiento").get<int>();
            pasajero.destino = pasajeroData.at("destino").get<std::string>();
            pasajero.origen = pasajeroData.at("origen").get<std::string>();
            pasajero.equipajeFacturado = pasajeroData.at("equipaje_facturado").get<int>();

            NodoPasajero* nuevoNodo = new NodoPasajero(pasajero);
            if (!frente) {
                frente = fin = nuevoNodo;
            } else {
                fin->siguiente = nuevoNodo;
                nuevoNodo->anterior = fin;
                fin = nuevoNodo;
            }

        } catch (const json::out_of_range& e) {
            std::cout << "Error al acceder a los datos del pasajero: " << e.what() << std::endl;
            continue;
        }
    }

    std::cout << "Pasajeros cargados a la cola correctamente." << std::endl;
}

void GestorPasajeros::mostrarColaPasajeros() {
    std::cout << "Cola de pasajeros:" << std::endl;
    NodoPasajero* actual = frente;
    int i = 1;

    std::ofstream archivoDOT("ColaPasajeros.dot");
    if (!archivoDOT.is_open()) {
        std::cerr << "Error al abrir el archivo ColaPasajeros.dot" << std::endl;
        return;
    }

    archivoDOT << "digraph ColaPasajeros {" << std::endl;
    archivoDOT << "rankdir=TB;" << std::endl;
    archivoDOT << "node [shape=record];" << std::endl;

    while (actual) {
        archivoDOT << "node" << i << " [label=\"{"
                   << "Nombre: " << actual->pasajero.nombre << " | "
                   << "Número de pasaporte: " << actual->pasajero.numeroPasaporte << " | "
                   << "Vuelo: " << actual->pasajero.vuelo << " | "
                   << "Asiento: " << actual->pasajero.asiento << " | "
                   << "Origen: " << actual->pasajero.origen << " | "
                   << "Destino: " << actual->pasajero.destino << " | "
                   << "Equipaje facturado: " << (actual->pasajero.equipajeFacturado ? "Sí" : "No") << "}\"];" << std::endl;

        if (actual->siguiente) {
            archivoDOT << "node" << i << " -> "
                       << "node" << i + 1 << ";" << std::endl;
        }

        actual = actual->siguiente;
        i++;
    }

    archivoDOT << "}" << std::endl;
    archivoDOT.close();

    std::string comandoDotToPdf = "dot -Tpdf ColaPasajeros.dot -o ColaPasajeros.pdf";
    std::cout << "Comando DOT a PDF: " << comandoDotToPdf << std::endl;

    int resultado = system(comandoDotToPdf.c_str());
    if (resultado != 0) {
        std::cerr << "Error al generar el archivo PDF desde DOT para la cola de pasajeros." << std::endl;
    } else {
        std::cout << "Archivo PDF para la cola de pasajeros generado exitosamente: ColaPasajeros.pdf" << std::endl;

        std::string comandoAbrirPdf = "zathura ColaPasajeros.pdf &";
        system(comandoAbrirPdf.c_str());
    }
}
