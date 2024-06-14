#ifndef LISTA_DOBLEMENTE_ENLAZADA_H
#define LISTA_DOBLEMENTE_ENLAZADA_H

#include "NodoLista.h"
#include "Pasajero.h"
#include "ComparadorPasajero.h"

class ListaDoblementeEnlazada {
public:
    ListaDoblementeEnlazada();
    ~ListaDoblementeEnlazada();
    void insertarOrdenado(const Pasajero& pasajero, const ComparadorPasajero& comparador);
    void mostrarOrdenadoPorVueloYAsiento() const;
    NodoLista* obtenerPrimero() const;
    bool estaVacia() const;
    NodoLista* encontrarMenorPorVueloYAsiento() const;
    void eliminarNodo(NodoLista* nodo);
    void buscarPasajero(const std::string& numeroPasaporte) const;
private:
    NodoLista* primero;
    NodoLista* ultimo;
};

#endif // LISTA_DOBLEMENTE_ENLAZADA_H
