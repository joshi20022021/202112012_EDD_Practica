#include "GestorPasajeros.h"
#include <fstream>
#include "ComparadorPasajero.h"
#include <iostream>
#include <sstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


void GestorPasajeros::mostrarListaEquipajeCeroOrdenada() const {
    // Mostrar la lista doblemente enlazada ordenada por vuelo y asiento
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
            delete nodoPasajero; // Liberar memoria del nodo sacado de la cola

            if (pasajero.equipajeFacturado > 0) {
                // Insertar en la lista doblemente enlazada
                listaEquipajeCero.insertarOrdenado(pasajero, ComparadorPasajero());

                // Insertar en la pila si el equipaje facturado es mayor que cero
                pilaEquipajeMayorCero.apilar(pasajero); // Actualizado para apilar Pasajero
            }
        } else {
        }
    }

    archivo.close();

    // Call the public method to process airplane movements
    listaAviones.procesarMovimientoAvionPublic(otraRuta); // Reemplaza con la ruta correcta
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
            pasajero.asiento = pasajeroData.at("asiento").get<std::string>();
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
    while (actual) {
        std::cout << "Pasajero " << i << ": " << actual->pasajero.nombre << " - Destino: " << actual->pasajero.destino << std::endl;
        actual = actual->siguiente;
        i++;
    }


}
