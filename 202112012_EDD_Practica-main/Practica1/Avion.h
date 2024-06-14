#ifndef EDDFINAL_AVION_H
#define EDDFINAL_AVION_H

#include <string>

class Avion {
public:
    std::string vuelo;
    std::string numero_de_registro;
    std::string modelo;
    std::string fabricante;
    int ano_fabricacion;
    int peso_max_despegue;
    std::string aerolinea;
    std::string estado;

    Avion* siguiente; // Puntero al siguiente avión en la lista
    Avion* anterior;  // Puntero al avión anterior en la lista
};

#endif // AVION_H
