// ListaDoblementeEnlazada.cpp

#include "ListaDoblementeEnlazada.h"
#include <iostream>

ListaDoblementeEnlazada::ListaDoblementeEnlazada() : primero(nullptr), ultimo(nullptr) {
    // Constructor por defecto: inicializa los punteros primero y último
}

ListaDoblementeEnlazada::~ListaDoblementeEnlazada() {
    // Destructor: libera toda la memoria de los nodos
    NodoLista* actual = primero;
    while (actual) {
        NodoLista* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaDoblementeEnlazada::insertarOrdenado(const Pasajero& pasajero, const ComparadorPasajero& comparador) {
    // Insertar un nuevo nodo ordenadamente según el comparador
    NodoLista* nuevoNodo = new NodoLista(pasajero);

    if (!primero) {
        // Caso: lista vacía
        primero = ultimo = nuevoNodo;
    } else {
        // Caso: lista no vacía
        NodoLista* actual = primero;
        while (actual) {
            if (comparador(nuevoNodo->pasajero, actual->pasajero)) {
                // Insertar antes del nodo actual
                nuevoNodo->siguiente = actual;
                nuevoNodo->anterior = actual->anterior;
                if (actual->anterior) {
                    actual->anterior->siguiente = nuevoNodo;
                } else {
                    primero = nuevoNodo;
                }
                actual->anterior = nuevoNodo;
                return;
            }
            actual = actual->siguiente;
        }
        // Si no se insertó antes, se inserta al final
        ultimo->siguiente = nuevoNodo;
        nuevoNodo->anterior = ultimo;
        ultimo = nuevoNodo;
    }
}

void ListaDoblementeEnlazada::mostrarOrdenadoPorVueloYAsiento() const {
    // Mostrar todos los pasajeros ordenados por vuelo y asiento
    if (!primero) {
        std::cout << "La lista está vacía." << std::endl;
        return;
    }

    // Crear una copia superficial de la lista para trabajar con ella
    ListaDoblementeEnlazada listaCopia(*this); // Se llama al constructor de copia

    while (!listaCopia.estaVacia()) {
        // Encontrar el nodo con el menor vuelo y, en caso de empate, menor asiento
        NodoLista* menor = listaCopia.encontrarMenorPorVueloYAsiento();

        // Mostrar la información del pasajero
        std::cout << "Nombre: " << menor->pasajero.nombre << std::endl;
        std::cout << "Número de pasaporte: " << menor->pasajero.numeroPasaporte << std::endl;
        std::cout << "Vuelo: " << menor->pasajero.vuelo << std::endl;
        std::cout << "Asiento: " << menor->pasajero.asiento << std::endl;
        std::cout << "Origen: " << menor->pasajero.origen << std::endl;
        std::cout << "Destino: " << menor->pasajero.destino << std::endl;
        std::cout << "Equipaje facturado: " << menor->pasajero.equipajeFacturado << std::endl;
        std::cout << std::endl;

        // Eliminar el nodo menor de la lista copia
        listaCopia.eliminarNodo(menor);
    }
}

NodoLista* ListaDoblementeEnlazada::encontrarMenorPorVueloYAsiento() const {
    // Encontrar el nodo con el menor vuelo y, en caso de empate, menor asiento
    NodoLista* actual = primero;
    NodoLista* menor = primero;

    while (actual) {
        if (actual->pasajero.vuelo < menor->pasajero.vuelo ||
            (actual->pasajero.vuelo == menor->pasajero.vuelo &&
             actual->pasajero.asiento < menor->pasajero.asiento)) {
            menor = actual;
        }
        actual = actual->siguiente;
    }

    return menor;
}

void ListaDoblementeEnlazada::eliminarNodo(NodoLista* nodo) {
    // Eliminar un nodo dado de la lista
    if (!nodo) return;

    if (nodo->anterior) {
        nodo->anterior->siguiente = nodo->siguiente;
    } else {
        primero = nodo->siguiente;
    }

    if (nodo->siguiente) {
        nodo->siguiente->anterior = nodo->anterior;
    } else {
        ultimo = nodo->anterior;
    }

    delete nodo;
}

bool ListaDoblementeEnlazada::estaVacia() const {
    // Verificar si la lista está vacía
    return primero == nullptr;
}

NodoLista* ListaDoblementeEnlazada::obtenerPrimero() const {
    // Obtener el primer nodo de la lista
    return primero;
}
