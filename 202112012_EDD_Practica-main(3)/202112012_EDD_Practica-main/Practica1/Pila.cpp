#include "Pila.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

Pila::Pila() : tope(nullptr) {}

Pila::~Pila() {
    while (!estaVacia()) {
        desapilar();
    }
}

void Pila::apilar(const Pasajero& pasajero) {
    NodoPasajero* nuevoNodo = new NodoPasajero(pasajero);
    nuevoNodo->siguiente = tope;
    tope = nuevoNodo;
}

void Pila::mostrarPila() const {
    if (estaVacia()) {
        std::cout << "Pila de equipaje está vacía." << std::endl;
        return;
    }

    // Imprimir la pila en consola
    std::cout << "Pila de equipaje:" << std::endl;
    NodoPasajero* actual = tope;
    while (actual) {
        std::cout << "Nombre: " << actual->pasajero.nombre
                  << " - Número de pasaporte: " << actual->pasajero.numeroPasaporte
                  << " - Asiento: " << actual->pasajero.asiento
                  << " - Equipaje facturado: " << (actual->pasajero.equipajeFacturado ? "Sí" : "No") << std::endl;
        actual = actual->siguiente;
    }

    // Crear archivo DOT para la pila
    std::ofstream archivoDOT("PilaEquipaje.dot");
    if (!archivoDOT.is_open()) {
        std::cerr << "Error al abrir el archivo PilaEquipaje.dot" << std::endl;
        return;
    }

    archivoDOT << "digraph PilaEquipaje {" << std::endl;
    archivoDOT << "rankdir=TB;" << std::endl; // Orientación vertical
    archivoDOT << "node [shape=record];" << std::endl;

    actual = tope;
    while (actual) {
        archivoDOT << "node" << actual->pasajero.numeroPasaporte << " [label=\"{"
                   << "Nombre: " << actual->pasajero.nombre << " | "
                   << "Número de pasaporte: " << actual->pasajero.numeroPasaporte << " | "
                   << "Asiento: " << actual->pasajero.asiento << " | "
                   << "Equipaje facturado: " << (actual->pasajero.equipajeFacturado ? "Sí" : "No") << "}\"];" << std::endl;

        if (actual->siguiente) {
            archivoDOT << "node" << actual->pasajero.numeroPasaporte << " -> "
                       << "node" << actual->siguiente->pasajero.numeroPasaporte << ";" << std::endl;
        }

        actual = actual->siguiente;
    }

    archivoDOT << "}" << std::endl;
    archivoDOT.close();

    // Generar el archivo PDF utilizando Graphviz
    std::string comandoDotToPdf = "dot -Tpdf PilaEquipaje.dot -o PilaEquipaje.pdf";
    std::cout << "Comando DOT a PDF: " << comandoDotToPdf << std::endl; // Debugging

    int resultado = system(comandoDotToPdf.c_str());
    if (resultado != 0) {
        std::cerr << "Error al generar el archivo PDF desde DOT para la pila de equipaje." << std::endl;
    } else {
        std::cout << "Archivo PDF para la pila de equipaje generado exitosamente: PilaEquipaje.pdf" << std::endl;

        // Abrir el archivo PDF con el visor predeterminado del sistema
        std::string comandoAbrirPdf = "xdg-open PilaEquipaje.pdf &";
        system(comandoAbrirPdf.c_str());
    }
}



bool Pila::estaVacia() const {
    return tope == nullptr;
}

Pasajero Pila::desapilar() {
    if (estaVacia()) {
        throw std::runtime_error("Error: La pila está vacía.");
    }
    NodoPasajero* nodoDesapilado = tope;
    Pasajero pasajero = nodoDesapilado->pasajero;
    tope = tope->siguiente;
    delete nodoDesapilado;
    return pasajero;
}
