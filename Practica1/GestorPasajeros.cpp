#include "GestorPasajeros.h"
#include "ColaPasajeros.h" // Incluir la cabecera de ColaPasajeros
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

ColaPasajeros colaPasajeros; // Declarar una instancia de ColaPasajeros

void GestorPasajeros::cargarPasajerosDesdeArchivo(const std::string& rutaArchivo) {
    ifstream file(rutaArchivo);
    if (!file) {
        cout << "Error al abrir el archivo: " << rutaArchivo << endl;
        return;
    }

    json data;
    try {
        file >> data;
    } catch (const json::parse_error& e) {
        cout << "Error al parsear el archivo JSON: " << e.what() << endl;
        return;
    }

    for (const auto& pasajeroData : data) {
        Pasajero pasajero;
        try {
            pasajero.nombre = pasajeroData.at("nombre").get<string>();
            pasajero.nacionalidad = pasajeroData.at("nacionalidad").get<string>();
            pasajero.numeroPasaporte = pasajeroData.at("numero_de_pasaporte").get<string>();
            pasajero.vuelo = pasajeroData.at("vuelo").get<string>();
            pasajero.asiento = pasajeroData.at("asiento").get<string>();
            pasajero.destino = pasajeroData.at("destino").get<string>();
            pasajero.origen = pasajeroData.at("origen").get<string>();
            pasajero.equipajeFacturado = pasajeroData.at("equipaje_facturado").get<int>();
        } catch (const json::out_of_range& e) {
            cout << "Error al acceder a los datos del pasajero: " << e.what() << endl;
            continue;
        }

        colaPasajeros.agregarPasajero(pasajero); // Usar la instancia de ColaPasajeros
    }

    cout << "Pasajeros cargados desde el archivo correctamente." << endl;
}

void GestorPasajeros::procesarRegistro() {
    while (!colaPasajeros.estaVacia()) {
        Pasajero pasajero = colaPasajeros.obtenerPasajero(); // Obtener pasajero de la cola

        if (pasajero.equipajeFacturado > 0) {
            pilaEquipajes.push(pasajero.equipajeFacturado);
        }

        NodoPasajero* nuevoNodo = new NodoPasajero(pasajero);

        // Insertar el pasajero en la lista doblemente enlazada de forma ordenada
        if (listaPasajerosOrdenados == nullptr) {
            listaPasajerosOrdenados = nuevoNodo;
        } else {
            NodoPasajero* actual = listaPasajerosOrdenados;
            NodoPasajero* anterior = nullptr;
            while (actual != nullptr && (actual->pasajero.vuelo < nuevoNodo->pasajero.vuelo ||
                                         (actual->pasajero.vuelo == nuevoNodo->pasajero.vuelo && actual->pasajero.asiento < nuevoNodo->pasajero.asiento))) {
                anterior = actual;
                actual = actual->siguiente;
            }
            if (anterior == nullptr) {
                nuevoNodo->siguiente = listaPasajerosOrdenados;
                listaPasajerosOrdenados->anterior = nuevoNodo;
                listaPasajerosOrdenados = nuevoNodo;
            } else {
                nuevoNodo->siguiente = actual;
                nuevoNodo->anterior = anterior;
                if (actual != nullptr) {
                    actual->anterior = nuevoNodo;
                }
                anterior->siguiente = nuevoNodo;
            }
        }
    }
}

void GestorPasajeros::mostrarPasajerosOrdenados() {
    NodoPasajero* actual = listaPasajerosOrdenados;
    while (actual != nullptr) {
        Pasajero pasajero = actual->pasajero;
        cout << "Nombre: " << pasajero.nombre << ", Vuelo: " << pasajero.vuelo << ", Asiento: " << pasajero.asiento << ", Equipaje Facturado: " << pasajero.equipajeFacturado << endl;
        actual = actual->siguiente;
    }
}

void GestorPasajeros::mostrarEquipaje() {
    std::stack<int> tempPilaEquipajes = pilaEquipajes;
    cout << "Equipaje en la pila:" << endl;
    while (!tempPilaEquipajes.empty()) {
        int equipaje = tempPilaEquipajes.top();
        cout << "Equipaje Facturado: " << equipaje << endl;
        tempPilaEquipajes.pop();
    }
}

void GestorPasajeros::consultarPasajero(const std::string& numeroPasaporte) {
    NodoPasajero* actual = listaPasajerosOrdenados;
    while (actual != nullptr) {
        if (actual->pasajero.numeroPasaporte == numeroPasaporte) {
            Pasajero pasajero = actual->pasajero;
            cout << "Nombre: " << pasajero.nombre << endl;
            cout << "Nacionalidad: " << pasajero.nacionalidad << endl;
            cout << "Número de Pasaporte: " << pasajero.numeroPasaporte << endl;
            cout << "Vuelo: " << pasajero.vuelo << endl;
            cout << "Asiento: " << pasajero.asiento << endl;
            cout << "Destino: " << pasajero.destino << endl;
            cout << "Origen: " << pasajero.origen << endl;
            cout << "Equipaje Facturado: " << pasajero.equipajeFacturado << endl;
            return;
        }
        actual = actual->siguiente;
    }
    cout << "Pasajero no encontrado." << endl;
}
