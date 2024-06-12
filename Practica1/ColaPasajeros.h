//
// Created by joshi2002 on 11/06/24.
//

#ifndef EDDFINAL_COLAPASAJEROS_H
#define EDDFINAL_COLAPASAJEROS_H

#include "Pasajero.h"
#include <queue> // Incluir la cabecera <queue>

class ColaPasajeros {
private:
    std::queue<Pasajero> colaRegistro;

public:
    ColaPasajeros() = default;
    ~ColaPasajeros() = default;

    void agregarPasajero(const Pasajero& pasajero);
    bool estaVacia() const;
    Pasajero obtenerPasajero();
};

#endif //EDDFINAL_COLAPASAJEROS_H
