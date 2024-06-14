#include "GestorAviones.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <graphviz/gvc.h>

using json = nlohmann::json;
using namespace std;

GestorAviones::~GestorAviones() {}

void GestorAviones::cargarAvionesDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        json data;
        archivo >> data;

        for (const auto& avionData : data) {
            Avion avion;
            avion.vuelo = avionData["vuelo"];
            avion.numero_de_registro = avionData["numero_de_registro"];
            avion.modelo = avionData["modelo"];
            avion.fabricante = avionData["fabricante"];
            avion.ano_fabricacion = avionData["ano_fabricacion"];
            avion.peso_max_despegue = avionData["peso_max_despegue"];
            avion.aerolinea = avionData["aerolinea"];
            avion.estado = avionData["estado"];

            if (avion.estado == "Disponible") {
                listaAviones.insertarAvionDisponible(avion);
            } else if (avion.estado == "Mantenimiento") {
                listaAviones.insertarAvionMantenimiento(avion);
            } else {
                cout << "Estado de avión desconocido: " << avion.estado << endl;
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
    }
}

void GestorAviones::mostrarAvionesDisponibles() {
    cout << "Aviones Disponibles:" << endl;
    listaAviones.mostrarAvionesDisponibles();
}

void GestorAviones::mostrarAvionesMantenimiento() {
    cout << "Aviones en Mantenimiento:" << endl;
    listaAviones.mostrarAvionesMantenimiento();
}
