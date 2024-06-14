#ifndef GESTORAVIONES_H
#define GESTORAVIONES_H

#include "ListaAviones.h" // Asumiendo que ListaAviones contiene la definición de Avion
#include <fstream>
#include <string>  // Necesario para std::string

class GestorAviones {
private:
    ListaAviones listaAviones;

public:
    ~GestorAviones();

    void cargarAvionesDesdeArchivo(const std::string& nombreArchivo);
    void mostrarAvionesDisponibles();
    void mostrarAvionesMantenimiento();
};

#endif // GESTORAVIONES_H
