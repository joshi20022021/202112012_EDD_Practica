#ifndef GESTOR_PASAJEROS_H
#define GESTOR_PASAJEROS_H

#include <string>
#include "NodoPasajero.h"
#include "ListaDoblementeEnlazada.h"
#include "ListaAviones.h"
#include "Pila.h"

class GestorPasajeros {
public:
    GestorPasajeros() : frente(nullptr), fin(nullptr), listaEquipajeCero() {}

    void cargarPasajerosDesdeArchivo(const std::string& rutaArchivo);
    void mostrarColaPasajeros();
    void procesarIngresoPasajero(const std::string& otraRuta);
    void mostrarPilaEquipaje() const;
    void mostrarListaEquipajeCeroOrdenada() const;
    void buscarPasajeroEnLista(const std::string& numeroPasaporte) const;
private:
    NodoPasajero* frente;
    NodoPasajero* fin;
    ListaDoblementeEnlazada listaEquipajeCero;
    Pila pilaEquipajeMayorCero;
    ListaAviones listaAviones;
};

#endif // GESTOR_PASAJEROS_H
