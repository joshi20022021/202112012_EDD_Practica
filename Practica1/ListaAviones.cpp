#include "ListaAviones.h"
#include <iostream>

ListaAviones::ListaAviones() : avionesDisponibles(nullptr), avionesMantenimiento(nullptr) {}

ListaAviones::~ListaAviones() {
    while (avionesDisponibles != nullptr) {
        NodoAvion* temp = avionesDisponibles;
        avionesDisponibles = avionesDisponibles->siguiente;
        delete temp;
    }

    while (avionesMantenimiento != nullptr) {
        NodoAvion* temp = avionesMantenimiento;
        avionesMantenimiento = avionesMantenimiento->siguiente;
        delete temp;
    }
}

void ListaAviones::insertarAvionDisponible(const Avion& avion) {
    NodoAvion* nuevoNodo = new NodoAvion(new Avion(avion));
    if (!avionesDisponibles) {
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
        avionesDisponibles = nuevoNodo;
    } else {
        NodoAvion* ultimoNodo = avionesDisponibles->anterior;
        nuevoNodo->siguiente = avionesDisponibles;
        nuevoNodo->anterior = ultimoNodo;
        avionesDisponibles->anterior = nuevoNodo;
        ultimoNodo->siguiente = nuevoNodo;
    }
}

void ListaAviones::insertarAvionMantenimiento(const Avion& avion) {
    NodoAvion* nuevoNodo = new NodoAvion(new Avion(avion));
    if (!avionesMantenimiento) {
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
        avionesMantenimiento = nuevoNodo;
    } else {
        NodoAvion* ultimoNodo = avionesMantenimiento->anterior;
        nuevoNodo->siguiente = avionesMantenimiento;
        nuevoNodo->anterior = ultimoNodo;
        avionesMantenimiento->anterior = nuevoNodo;
        ultimoNodo->siguiente = nuevoNodo;
    }
}

void ListaAviones::mostrarAvionesDisponibles() {
    if (!avionesDisponibles) {
        std::cout << "No hay aviones disponibles." << std::endl;
    } else {
        std::cout << "Aviones Disponibles:" << std::endl;
        NodoAvion* actual = avionesDisponibles;
        do {
            std::cout << "Vuelo: " << actual->avion->vuelo << std::endl;
            std::cout << "Número de registro: " << actual->avion->numero_de_registro << std::endl;
            std::cout << "Modelo: " << actual->avion->modelo << std::endl;
            std::cout << "Fabricante: " << actual->avion->fabricante << std::endl;
            std::cout << "Año de fabricación: " << actual->avion->ano_fabricacion << std::endl;
            std::cout << "Peso máximo de despegue: " << actual->avion->peso_max_despegue << std::endl;
            std::cout << "Aerolínea: " << actual->avion->aerolinea << std::endl;
            std::cout << "Estado: " << actual->avion->estado << std::endl;
            std::cout << "---------------------------" << std::endl;
            actual = actual->siguiente;
        } while (actual != avionesDisponibles);
    }
}

void ListaAviones::mostrarAvionesMantenimiento() {
    if (!avionesMantenimiento) {
        std::cout << "No hay aviones en mantenimiento." << std::endl;
    } else {
        std::cout << "Aviones en Mantenimiento:" << std::endl;
        NodoAvion* actual = avionesMantenimiento;
        do {
            std::cout << "Vuelo: " << actual->avion->vuelo << std::endl;
            std::cout << "Número de registro: " << actual->avion->numero_de_registro << std::endl;
            std::cout << "Modelo: " << actual->avion->modelo << std::endl;
            std::cout << "Fabricante: " << actual->avion->fabricante << std::endl;
            std::cout << "Año de fabricación: " << actual->avion->ano_fabricacion << std::endl;
            std::cout << "Peso máximo de despegue: " << actual->avion->peso_max_despegue << std::endl;
            std::cout << "Aerolínea: " << actual->avion->aerolinea << std::endl;
            std::cout << "Estado: " << actual->avion->estado << std::endl;
            std::cout << "---------------------------" << std::endl;
            actual = actual->siguiente;
        } while (actual != avionesMantenimiento);
    }
}
