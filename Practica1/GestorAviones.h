#ifndef GESTORAVIONES_H
#define GESTORAVIONES_H

#include "ListaAviones.h"
#include <fstream>

class GestorAviones {
private:
    ListaAviones listaAviones;

    Avion* getInicioAvionesDisponibles();
    Avion* getInicioAvionesMantenimiento();
    void generarCodigoDOT(Avion* inicio, const std::string& nombreArchivo);

public:
    ~GestorAviones();

    void cargarAvionesDesdeArchivo(const std::string& nombreArchivo);
    void mostrarAvionesDisponibles();
    void mostrarAvionesMantenimiento();
};

#endif // GESTORAVIONES_H
