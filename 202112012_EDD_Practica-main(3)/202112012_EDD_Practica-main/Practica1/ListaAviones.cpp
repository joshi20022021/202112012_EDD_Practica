#include "ListaAviones.h"
#include <iostream>
#include <cstdlib>

ListaAviones::ListaAviones() : avionesDisponibles(nullptr), avionesMantenimiento(nullptr) {}

ListaAviones::~ListaAviones() {
    while (avionesDisponibles != nullptr) {
        NodoAvion* temp = avionesDisponibles;
        avionesDisponibles = avionesDisponibles->siguiente;
        delete temp;
    }

    while (avionesMantenimiento != nullptr) {
        NodoAvion* temp = avionesMantenimiento;
        avionesMantenimiento = avionesMantenimiento->siguiente;
        delete temp;
    }
}

void ListaAviones::insertarAvionDisponible(const Avion& avion) {
    NodoAvion* nuevoNodo = new NodoAvion(new Avion(avion));
    if (!avionesDisponibles) {
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
        avionesDisponibles = nuevoNodo;
    } else {
        NodoAvion* ultimoNodo = avionesDisponibles->anterior;
        nuevoNodo->siguiente = avionesDisponibles;
        nuevoNodo->anterior = ultimoNodo;
        avionesDisponibles->anterior = nuevoNodo;
        ultimoNodo->siguiente = nuevoNodo;
    }
}

void ListaAviones::insertarAvionMantenimiento(const Avion& avion) {
    NodoAvion* nuevoNodo = new NodoAvion(new Avion(avion));
    if (!avionesMantenimiento) {
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
        avionesMantenimiento = nuevoNodo;
    } else {
        NodoAvion* ultimoNodo = avionesMantenimiento->anterior;
        nuevoNodo->siguiente = avionesMantenimiento;
        nuevoNodo->anterior = ultimoNodo;
        avionesMantenimiento->anterior = nuevoNodo;
        ultimoNodo->siguiente = nuevoNodo;
    }
}
void ListaAviones::mostrarAvionesDisponibles() {
    if (!avionesDisponibles) {
        std::cout << "No hay aviones disponibles." << std::endl;
    } else {
        std::ofstream archivoDOT("AvionesDisponibles.dot");
        if (!archivoDOT.is_open()) {
            std::cerr << "Error al abrir el archivo AvionesDisponibles.dot" << std::endl;
            return;
        }

        archivoDOT << "digraph AvionesDisponibles {" << "\n";
        archivoDOT << "rankdir=TB;" << "\n"; // Cambiar a orientación vertical
        archivoDOT << "node [shape=plaintext];" << "\n";

        NodoAvion* actual = avionesDisponibles;
        NodoAvion* primero = avionesDisponibles;

        do {
            archivoDOT << "node" << actual->avion->numero_de_registro << " [label=<" << "\n";
            archivoDOT << "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">" << "\n";
            archivoDOT << "<tr><td align=\"center\"><b>Vuelo: " << actual->avion->vuelo << "</b></td></tr>" << "\n";
            archivoDOT << "<tr><td>Registro: " << actual->avion->numero_de_registro << "</td></tr>" << "\n";
            archivoDOT << "<tr><td>Modelo: " << actual->avion->modelo << "</td></tr>" << "\n";
            archivoDOT << "<tr><td>Fabricante: " << actual->avion->fabricante << "</td></tr>" << "\n";
            archivoDOT << "<tr><td>Año de fabricación: " << actual->avion->ano_fabricacion << "</td></tr>" << "\n";
            archivoDOT << "<tr><td>Peso máximo de despegue: " << actual->avion->peso_max_despegue << "</td></tr>" << "\n";
            archivoDOT << "<tr><td>Aerolínea: " << actual->avion->aerolinea << "</td></tr>" << "\n";
            archivoDOT << "<tr><td>Estado: " << actual->avion->estado << "</td></tr>" << "\n";
            archivoDOT << "</table>" << "\n";
            archivoDOT << ">];" << "\n";

            archivoDOT << "node" << actual->avion->numero_de_registro << " -> node" << actual->siguiente->avion->numero_de_registro << ";" << "\n";

            actual = actual->siguiente;
        } while (actual != primero);

        archivoDOT << "}" << "\n";
        archivoDOT.close();

        // Generar el archivo SVG utilizando Graphviz
        std::string comandoDotToPdf = "dot -Tpdf AvionesDisponibles.dot -o AvionesDisponibles.pdf";
        std::cout << "Comando DOT a PDF: " << comandoDotToPdf << std::endl; // Debugging

        int resultado = system(comandoDotToPdf.c_str());
        if (resultado != 0) {
            std::cerr << "Error al generar el archivo PDF desde DOT para aviones disponibles." << std::endl;
        } else {
            std::cout << "Archivo PDF para aviones disponibles generado exitosamente: AvionesDisponibles.pdf" << std::endl;

            // Abrir el archivo SVG con el visor predeterminado del sistema
            std::string comandoAbrirSvg = "xdg-open AvionesDisponibles.pdf &";
            system(comandoAbrirSvg.c_str());
        }
    }
}


void ListaAviones::mostrarAvionesMantenimiento() {
    if (!avionesMantenimiento) {
        std::cout << "No hay aviones en mantenimiento." << std::endl;
    } else {
        std::ofstream archivoDOT("AvionesMantenimiento.dot");
        if (!archivoDOT.is_open()) {
            std::cerr << "Error al abrir el archivo AvionesMantenimiento.dot" << std::endl;
            return;
        }

        archivoDOT << "digraph AvionesMantenimiento {" << "\n";
        archivoDOT << "rankdir=TB;" << "\n"; // Cambiar a orientación vertical
        archivoDOT << "node [shape=plaintext];" << "\n";

        NodoAvion* actual = avionesMantenimiento;
        NodoAvion* primero = avionesMantenimiento;

        do {
            archivoDOT << "node" << actual->avion->numero_de_registro << " [label=<" << "\n";
            archivoDOT << "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">" << "\n";
            archivoDOT << "<tr><td align=\"center\"><b>Vuelo: " << actual->avion->vuelo << "</b></td></tr>" << "\n";
            archivoDOT << "<tr><td>Registro: " << actual->avion->numero_de_registro << "</td></tr>" << "\n";
            archivoDOT << "<tr><td>Modelo: " << actual->avion->modelo << "</td></tr>" << "\n";
            archivoDOT << "<tr><td>Fabricante: " << actual->avion->fabricante << "</td></tr>" << "\n";
            archivoDOT << "<tr><td>Año de fabricación: " << actual->avion->ano_fabricacion << "</td></tr>" << "\n";
            archivoDOT << "<tr><td>Peso máximo de despegue: " << actual->avion->peso_max_despegue << "</td></tr>" << "\n";
            archivoDOT << "<tr><td>Aerolínea: " << actual->avion->aerolinea << "</td></tr>" << "\n";
            archivoDOT << "<tr><td>Estado: " << actual->avion->estado << "</td></tr>" << "\n";
            archivoDOT << "</table>" << "\n";
            archivoDOT << ">];" << "\n";

            archivoDOT << "node" << actual->avion->numero_de_registro << " -> node" << actual->siguiente->avion->numero_de_registro << ";" << "\n";

            actual = actual->siguiente;
        } while (actual != primero);

        archivoDOT << "}" << "\n";
        archivoDOT.close();

        // Generar el archivo PDF utilizando Graphviz
        std::string comandoDotToPdf = "dot -Tpdf AvionesMantenimiento.dot -o AvionesMantenimiento.pdf";
        std::cout << "Comando DOT a PDF: " << comandoDotToPdf << std::endl; // Debugging

        int resultado = system(comandoDotToPdf.c_str());
        if (resultado != 0) {
            std::cerr << "Error al generar el archivo PDF desde DOT para aviones en mantenimiento." << std::endl;
        } else {
            std::cout << "Archivo PDF para aviones en mantenimiento generado exitosamente: AvionesMantenimiento.pdf" << std::endl;

            // Abrir el PDF con Zathura
            std::string comandoAbrirPdf = "zathura AvionesMantenimiento.pdf &";
            system(comandoAbrirPdf.c_str());
        }
    }
}


NodoAvion* ListaAviones::buscarAvionPorRegistro(const std::string& numeroRegistro, NodoAvion* inicio) {
    if (!inicio) {
        return nullptr;
    }

    NodoAvion* actual = inicio;
    do {
        if (actual->avion->numero_de_registro == numeroRegistro) {
            return actual;
        }
        actual = actual->siguiente;
    } while (actual != inicio);

    return nullptr;
}

void ListaAviones::moverAvionMantenimiento(NodoAvion* nodoAvion) {
    if (!nodoAvion) {
        return;
    }

    nodoAvion->avion->estado = "Mantenimiento";

    // Sacar de la lista de disponibles
    if (nodoAvion->siguiente == nodoAvion) {
        avionesDisponibles = nullptr;
    } else {
        nodoAvion->anterior->siguiente = nodoAvion->siguiente;
        nodoAvion->siguiente->anterior = nodoAvion->anterior;
        if (avionesDisponibles == nodoAvion) {
            avionesDisponibles = nodoAvion->siguiente;
        }
    }

    // Insertar en la lista de mantenimiento
    if (!avionesMantenimiento) {
        nodoAvion->siguiente = nodoAvion;
        nodoAvion->anterior = nodoAvion;
        avionesMantenimiento = nodoAvion;
    } else {
        NodoAvion* ultimoNodo = avionesMantenimiento->anterior;
        nodoAvion->siguiente = avionesMantenimiento;
        nodoAvion->anterior = ultimoNodo;
        avionesMantenimiento->anterior = nodoAvion;
        ultimoNodo->siguiente = nodoAvion;
    }
}

void ListaAviones::moverAvionDisponible(NodoAvion* nodoAvion) {
    if (!nodoAvion) {
        return;
    }

    nodoAvion->avion->estado = "Disponible";

    // Sacar de la lista de mantenimiento
    if (nodoAvion->siguiente == nodoAvion) {
        avionesMantenimiento = nullptr;
    } else {
        nodoAvion->anterior->siguiente = nodoAvion->siguiente;
        nodoAvion->siguiente->anterior = nodoAvion->anterior;
        if (avionesMantenimiento == nodoAvion) {
            avionesMantenimiento = nodoAvion->siguiente;
        }
    }

    // Insertar en la lista de disponibles
    if (!avionesDisponibles) {
        nodoAvion->siguiente = nodoAvion;
        nodoAvion->anterior = nodoAvion;
        avionesDisponibles = nodoAvion;
    } else {
        NodoAvion* ultimoNodo = avionesDisponibles->anterior;
        nodoAvion->siguiente = avionesDisponibles;
        nodoAvion->anterior = ultimoNodo;
        avionesDisponibles->anterior = nodoAvion;
        ultimoNodo->siguiente = nodoAvion;
    }
}

void ListaAviones::procesarMovimientoAvionPublic(const std::string& archivoMovimientos) {
    procesarMovimientoAvion(archivoMovimientos);
}

void ListaAviones::procesarMovimientoAvion(const std::string& archivoMovimientos) {
    std::ifstream archivo(archivoMovimientos);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << archivoMovimientos << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {

        std::istringstream iss(linea);
        std::string comando;
        if (iss >> comando) {
            if (comando == "MoverMantenimiento") {
                std::string numeroRegistro;
                if (iss >> numeroRegistro) {
                    NodoAvion* avionEncontrado = buscarAvionPorRegistro(numeroRegistro, avionesDisponibles);
                    if (avionEncontrado) {
                        moverAvionMantenimiento(avionEncontrado);
                    } else {
                        std::cout << "Avión no encontrado en la lista de disponibles: " << numeroRegistro << std::endl;
                    }
                } else {

                }
            } else if (comando == "MoverDisponible") {
                std::string numeroRegistro;
                if (iss >> numeroRegistro) {
                    NodoAvion* avionEncontrado = buscarAvionPorRegistro(numeroRegistro, avionesMantenimiento);
                    if (avionEncontrado) {
                        moverAvionDisponible(avionEncontrado);
                    } else {

                    }
                } else {
                }
            } else {

            }
        }
    }

    archivo.close();
}
