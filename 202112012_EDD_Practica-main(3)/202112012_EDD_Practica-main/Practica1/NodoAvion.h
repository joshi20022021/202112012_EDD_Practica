#ifndef NODOAVION_H
#define NODOAVION_H

#include "Avion.h"

class NodoAvion {
public:
    Avion* avion;
    NodoAvion* siguiente;
    NodoAvion* anterior;

    NodoAvion(Avion* avion) : avion(avion), siguiente(nullptr), anterior(nullptr) {}
};

#endif // NODOAVION_H
