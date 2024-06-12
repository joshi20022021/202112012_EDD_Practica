#ifndef EDDFINAL_LISTAAVIONES_H
#define EDDFINAL_LISTAAVIONES_H

#include "Avion.h"
#include "NodoAvion.h"

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
    NodoAvion* getInicioAvionesDisponibles() const { return avionesDisponibles; }
    NodoAvion* getInicioAvionesMantenimiento() const { return avionesMantenimiento; }
};

// Implementación de las funciones getInicioAvionesDisponibles() y getInicioAvionesMantenimiento()
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

#endif // EDDFINAL_LISTAAVIONES_H
