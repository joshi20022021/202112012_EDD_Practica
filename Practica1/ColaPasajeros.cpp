#include "ColaPasajeros.h"

void ColaPasajeros::agregarPasajero(const Pasajero& pasajero) {
    colaRegistro.push(pasajero);
}

bool ColaPasajeros::estaVacia() const {
    return colaRegistro.empty();
}

Pasajero ColaPasajeros::obtenerPasajero() {
    Pasajero pasajero = colaRegistro.front();
    colaRegistro.pop();
    return pasajero;
}
