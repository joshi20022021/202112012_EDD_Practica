#include "Pasajero.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Pasajero& pasajero) {
    os << "Nombre: " << pasajero.nombre << ", "
       << "Nacionalidad: " << pasajero.nacionalidad << ", "
       << "Número de Pasaporte: " << pasajero.numeroPasaporte << ", "
       << "Vuelo: " << pasajero.vuelo << ", "
       << "Asiento: " << pasajero.asiento << ", "
       << "Destino: " << pasajero.destino << ", "
       << "Origen: " << pasajero.origen << ", "
       << "Equipaje Facturado: " << pasajero.equipajeFacturado;

    return os;
}
