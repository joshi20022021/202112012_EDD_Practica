// ComparadorPasajero.h

#ifndef FINALEDD_COMPARADOR_PASAJERO_H
#define FINALEDD_COMPARADOR_PASAJERO_H

#include "Pasajero.h"

class ComparadorPasajero {
public:
    bool operator()(const Pasajero& p1, const Pasajero& p2) const {
        // Primero comparar por número de vuelo
        if (p1.vuelo < p2.vuelo)
            return true;
        if (p1.vuelo > p2.vuelo)
            return false;

        // Si tienen el mismo número de vuelo, comparar por número de asiento
        return p1.asiento < p2.asiento;
    }
};

#endif // COMPARADOR_PASAJERO_H
