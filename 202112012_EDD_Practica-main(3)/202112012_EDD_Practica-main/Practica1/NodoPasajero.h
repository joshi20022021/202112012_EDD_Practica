#ifndef NODO_PASAJERO_H
#define NODO_PASAJERO_H

#include "Pasajero.h"

struct NodoPasajero {
    Pasajero pasajero;
    NodoPasajero* siguiente;
    NodoPasajero* anterior;

    NodoPasajero(const Pasajero& p) : pasajero(p), siguiente(nullptr), anterior(nullptr) {}
};

#endif // NODO_PASAJERO_H
