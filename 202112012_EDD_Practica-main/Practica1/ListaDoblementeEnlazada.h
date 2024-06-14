// ListaDoblementeEnlazada.h

#ifndef LISTA_DOBLEMENTE_ENLAZADA_H
#define LISTA_DOBLEMENTE_ENLAZADA_H

#include "NodoLista.h"
#include "Pasajero.h"
#include "ComparadorPasajero.h"

class ListaDoblementeEnlazada {
public:
    ListaDoblementeEnlazada(); // Constructor por defecto
    ~ListaDoblementeEnlazada(); // Destructor
    void insertarOrdenado(const Pasajero& pasajero, const ComparadorPasajero& comparador);
    void mostrarOrdenadoPorVueloYAsiento() const; // Nueva función para mostrar ordenado
    NodoLista* obtenerPrimero() const;
    bool estaVacia() const; // Declaración de la función estaVacia
    NodoLista* encontrarMenorPorVueloYAsiento() const; // Declaración de la función encontrarMenorPorVueloYAsiento
    void eliminarNodo(NodoLista* nodo); // Declaración de la función eliminarNodo

private:
    NodoLista* primero;
    NodoLista* ultimo;
};

#endif // LISTA_DOBLEMENTE_ENLAZADA_H
