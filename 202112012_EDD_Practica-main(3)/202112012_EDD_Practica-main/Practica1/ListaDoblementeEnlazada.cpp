// ListaDoblementeEnlazada.cpp

#include "ListaDoblementeEnlazada.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

ListaDoblementeEnlazada::ListaDoblementeEnlazada() : primero(nullptr), ultimo(nullptr) {
}

ListaDoblementeEnlazada::~ListaDoblementeEnlazada() {
    NodoLista* actual = primero;
    while (actual) {
        NodoLista* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaDoblementeEnlazada::insertarOrdenado(const Pasajero& pasajero, const ComparadorPasajero& comparador) {
    NodoLista* nuevoNodo = new NodoLista(pasajero);

    if (!primero) {
        primero = ultimo = nuevoNodo;
    } else {
        NodoLista* actual = primero;
        while (actual) {
            if (comparador(nuevoNodo->pasajero, actual->pasajero)) {
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

    ListaDoblementeEnlazada listaCopia(*this);

    // Crear archivo DOT para la lista doblemente enlazada
    std::ofstream archivoDOT("ListaDoblementeEnlazada.dot");
    if (!archivoDOT.is_open()) {
        std::cerr << "Error al abrir el archivo ListaDoblementeEnlazada.dot" << std::endl;
        return;
    }

    archivoDOT << "digraph ListaDoblementeEnlazada {" << std::endl;
    archivoDOT << "rankdir=TB;" << std::endl; // Orientación vertical
    archivoDOT << "node [shape=record];" << std::endl;

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

        // Agregar el nodo al archivo DOT
        archivoDOT << "node" << menor->pasajero.numeroPasaporte << " [label=\"{"
                   << "Nombre: " << menor->pasajero.nombre << " | "
                   << "Número de pasaporte: " << menor->pasajero.numeroPasaporte << " | "
                   << "Vuelo: " << menor->pasajero.vuelo << " | "
                   << "Asiento: " << menor->pasajero.asiento << " | "
                   << "Origen: " << menor->pasajero.origen << " | "
                   << "Destino: " << menor->pasajero.destino << " | "
                   << "Equipaje facturado: " << menor->pasajero.equipajeFacturado << "}\"];" << std::endl;

        if (menor->siguiente) {
            archivoDOT << "node" << menor->pasajero.numeroPasaporte << " -> "
                       << "node" << menor->siguiente->pasajero.numeroPasaporte << " [dir=forward];" << std::endl;
        }

        if (menor->anterior) {
            archivoDOT << "node" << menor->pasajero.numeroPasaporte << " -> "
                       << "node" << menor->anterior->pasajero.numeroPasaporte << " [dir=back];" << std::endl;
        }

        listaCopia.eliminarNodo(menor);
    }

    archivoDOT << "}" << std::endl;
    archivoDOT.close();
    std::string comandoDotToPdf = "dot -Tpdf ListaDoblementeEnlazada.dot -o ListaDoblementeEnlazada.pdf";
    std::cout << "Comando DOT a PDF: " << comandoDotToPdf << std::endl; // Debugging

    int resultado = system(comandoDotToPdf.c_str());
    if (resultado != 0) {
        std::cerr << "Error al generar el archivo PDF desde DOT para pasajeros." << std::endl;
    } else {
        std::cout << "Archivo PDF para pasajeros generado exitosamente: ListaDoblementeEnlazada.pdf" << std::endl;

        // Abrir el archivo SVG con el visor predeterminado del sistema
        std::string comandoAbrirSvg = "xdg-open ListaDoblementeEnlazada.pdf &";
        system(comandoAbrirSvg.c_str());
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
    return primero == nullptr;
}

NodoLista* ListaDoblementeEnlazada::obtenerPrimero() const {
    return primero;
}
void ListaDoblementeEnlazada::buscarPasajero(const std::string& numeroPasaporte) const {
    NodoLista* actual = primero;
    bool encontrado = false;

    while (actual) {
        if (actual->pasajero.numeroPasaporte == numeroPasaporte) {
            encontrado = true;
            std::cout << "Información del pasajero encontrado:" << std::endl;
            std::cout << "Nombre: " << actual->pasajero.nombre << std::endl;
            std::cout << "Número de pasaporte: " << actual->pasajero.numeroPasaporte << std::endl;
            std::cout << "Vuelo: " << actual->pasajero.vuelo << std::endl;
            std::cout << "Asiento: " << actual->pasajero.asiento << std::endl;
            std::cout << "Origen: " << actual->pasajero.origen << std::endl;
            std::cout << "Destino: " << actual->pasajero.destino << std::endl;
            std::cout << "Equipaje facturado: " << actual->pasajero.equipajeFacturado << std::endl;
            break; // Salir del bucle al encontrar el pasajero
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        std::cout << "No se encontró ningún pasajero con el número de pasaporte: " << numeroPasaporte << std::endl;
    }
}
