#ifndef PASAJERO_H
#define PASAJERO_H

#include <string>

struct Pasajero {
    std::string nombre;
    std::string nacionalidad;
    std::string numeroPasaporte;
    std::string vuelo;
    std::string asiento;
    std::string destino;
    std::string origen;
    int equipajeFacturado;
    friend std::ostream& operator<<(std::ostream& os, const Pasajero& pasajero);
};

#endif // PASAJERO_H
