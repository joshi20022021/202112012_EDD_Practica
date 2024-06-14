#include "Pila.h"
#include <iostream>

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

    std::cout << "Pila de equipaje:" << std::endl;
    NodoPasajero* actual = tope;
    while (actual) {
        std::cout << "Nombre: " << actual->pasajero.nombre
                  << " - Número de pasaporte: " << actual->pasajero.numeroPasaporte
                  << " - Equipaje facturado: " << actual->pasajero.equipajeFacturado << std::endl;
        actual = actual->siguiente;
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
