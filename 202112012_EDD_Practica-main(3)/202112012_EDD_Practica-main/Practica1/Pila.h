#ifndef EDDFINAL_PILA_H
#define EDDFINAL_PILA_H

#include "NodoPasajero.h"

class Pila {
private:
    NodoPasajero* tope;

public:
    Pila();
    ~Pila();
    void apilar(const Pasajero& pasajero);
    void mostrarPila() const;
    bool estaVacia() const;
    Pasajero desapilar();
};

#endif // EDDFINAL_PILA_H
