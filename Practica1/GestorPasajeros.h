#ifndef GESTOR_PASAJEROS_H
#define GESTOR_PASAJEROS_H

#include <string>
#include <queue>
#include <stack>
#include "Pasajero.h"

class GestorPasajeros {
private:
    std::queue<Pasajero> colaRegistro;
    std::stack<int> pilaEquipajes;
    NodoPasajero* listaPasajerosOrdenados;

public:
    GestorPasajeros() : listaPasajerosOrdenados(nullptr) {}
    void cargarPasajerosDesdeArchivo(const std::string& rutaArchivo);
    void procesarRegistro();
    void mostrarPasajerosOrdenados();
    void mostrarEquipaje();
    void consultarPasajero(const std::string& numeroPasaporte);
};

#endif // GESTOR_PASAJEROS_H
