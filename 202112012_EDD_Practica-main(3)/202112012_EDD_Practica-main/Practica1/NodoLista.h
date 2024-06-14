//
// Created by joshi2002 on 13/06/24.
//

#ifndef EDDFINAL_NODOLISTA_H
#define EDDFINAL_NODOLISTA_H
#include "Pasajero.h"

struct NodoLista {
    Pasajero pasajero;
    NodoLista* anterior;
    NodoLista* siguiente;

    NodoLista(const Pasajero& _pasajero) : pasajero(_pasajero), anterior(nullptr), siguiente(nullptr) {}
};
#endif //EDDFINAL_NODOLISTA_H
