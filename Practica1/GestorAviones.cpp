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
    Avion* inicio = listaAviones.getInicioAvionesDisponibles();
    generarCodigoDOT(inicio, "Aviones_Disponibles.dot");
}

void GestorAviones::mostrarAvionesMantenimiento() {
    Avion* inicio = listaAviones.getInicioAvionesMantenimiento();
    generarCodigoDOT(inicio, "Aviones_Mantenimiento.dot");
}

void GestorAviones::generarCodigoDOT(Avion* inicio, const std::string& nombreArchivoDOT) {
    GVC_t *gvc;
    Agraph_t *grafo;
    FILE *archivoDOT;

    gvc = gvContext();
    if (!gvc) {
        cerr << "Error al inicializar el contexto Graphviz" << endl;
        return;
    }

    archivoDOT = fopen(nombreArchivoDOT.c_str(), "w");
    if (!archivoDOT) {
        cerr << "Error al abrir el archivo DOT: " << nombreArchivoDOT << endl;
        gvFreeContext(gvc);
        return;
    }

    grafo = agopen("G", Agdirected, nullptr);
    if (!grafo) {
        cerr << "Error al crear el grafo" << endl;
        fclose(archivoDOT);
        gvFreeContext(gvc);
        return;
    }

    if (inicio != nullptr) {
        Avion* actual = inicio;
        do {
            Agnode_t* nodo = agnode(grafo, nullptr, 1);
            agsafeset(nodo, (char*)"label", (char*)(actual->modelo + "\\n" + actual->vuelo).c_str(), (char*)"");
            actual = actual->siguiente;
        } while (actual != inicio);

        actual = inicio;
        do {
            Agnode_t* nodoActual = agnode(grafo, (char*)(actual->modelo + actual->vuelo).c_str(), 0);
            Agnode_t* nodoSiguiente = agnode(grafo, (char*)(actual->siguiente->modelo + actual->siguiente->vuelo).c_str(), 0);
            Agnode_t* nodoAnterior = agnode(grafo, (char*)(actual->anterior->modelo + actual->anterior->vuelo).c_str(), 0);

            if (nodoActual && nodoSiguiente) {
                agedge(grafo, nodoActual, nodoSiguiente, nullptr, 1);
            }
            if (nodoActual && nodoAnterior) {
                agedge(grafo, nodoActual, nodoAnterior, nullptr, 1);
            }
            actual = actual->siguiente;
        } while (actual != inicio);
    }

    agwrite(grafo, archivoDOT);
    fclose(archivoDOT);
    agclose(grafo);
    gvFreeContext(gvc);

    cout << "Archivo DOT generado exitosamente: " << nombreArchivoDOT << endl;
}
