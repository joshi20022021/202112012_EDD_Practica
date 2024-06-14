#ifndef EDDFINAL_PILA_H
#define EDDFINAL_PILA_H

#include "NodoPasajero.h" // Incluir la definición de NodoPasajero

class Pila {
private:
    NodoPasajero* tope; // Puntero al tope de la pila

public:
    Pila(); // Constructor por defecto
    ~Pila(); // Destructor
    void apilar(const Pasajero& pasajero); // Método para apilar un Pasajero
    void mostrarPila() const; // Método para mostrar los elementos de la pila
    bool estaVacia() const; // Método para verificar si la pila está vacía
    Pasajero desapilar(); // Método para desapilar un Pasajero
};

#endif // EDDFINAL_PILA_H
