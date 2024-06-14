#ifndef LISTAAVIONES_H
#define LISTAAVIONES_H

#include "Avion.h"
#include "NodoAvion.h"
#include <fstream>
#include <sstream>

class ListaAviones {
private:
    NodoAvion* avionesDisponibles;
    NodoAvion* avionesMantenimiento;

public:
    ListaAviones();
    ~ListaAviones();

    void insertarAvionDisponible(const Avion& avion);
    void insertarAvionMantenimiento(const Avion& avion);
    void mostrarAvionesDisponibles();
    void mostrarAvionesMantenimiento();

    Avion* getInicioAvionesDisponibles();
    Avion* getInicioAvionesMantenimiento();

    void procesarMovimientoAvionPublic(const std::string& archivoMovimientos);

private:
    NodoAvion* buscarAvionPorRegistro(const std::string& numeroRegistro, NodoAvion* inicio);
    void moverAvionMantenimiento(NodoAvion* nodoAvion);
    void moverAvionDisponible(NodoAvion* nodoAvion);
    void procesarMovimientoAvion(const std::string& archivoMovimientos);
};

inline Avion* ListaAviones::getInicioAvionesDisponibles() {
    if (avionesDisponibles != nullptr) {
        return avionesDisponibles->avion;
    } else {
        return nullptr;
    }
}

inline Avion* ListaAviones::getInicioAvionesMantenimiento() {
    if (avionesMantenimiento != nullptr) {
        return avionesMantenimiento->avion;
    } else {
        return nullptr;
    }
}

#endif // LISTAAVIONES_H
