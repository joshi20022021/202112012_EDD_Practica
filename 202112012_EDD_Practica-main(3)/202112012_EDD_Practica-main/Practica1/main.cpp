#include <iostream>
#include <fstream>
#include <limits>
#include "GestorPasajeros.h"
#include "GestorAviones.h"

int main() {
    int opcion, subOpcion;
    GestorPasajeros gestorPasajeros;
    GestorAviones gestorAviones;

    do {
        std::cout << "|---------------MENU----------------|" << std::endl;
        std::cout << "|       1. Carga de aviones         |" << std::endl;
        std::cout << "|      2. Carga de pasajeros        |" << std::endl;
        std::cout << "|     3. Procesar registro          |" << std::endl;
        std::cout << "|      4. Consultar pasajero        |" << std::endl;
        std::cout << "|      5. Visualizar reportes       |" << std::endl;
        std::cout << "|             6. Salir              |" << std::endl;
        std::cout << "|-----------------------------------|" << std::endl;
        std::cout << "Ingrese una opción: ";
        std::cin >> opcion;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                std::string rutaArchivo;
                std::cout << "Ingrese la ruta del archivo JSON de aviones: ";
                std::getline(std::cin, rutaArchivo);

                gestorAviones.cargarAvionesDesdeArchivo(rutaArchivo);
                break;
            }
            case 2: {
                std::string rutaArchivo;
                std::cout << "Ingrese la ruta del archivo JSON de pasajeros: ";
                std::getline(std::cin, rutaArchivo);

                gestorPasajeros.cargarPasajerosDesdeArchivo(rutaArchivo);
                gestorPasajeros.mostrarColaPasajeros();
                break;
            }
            case 3: {
                std::string otraRuta;
                std::cout << "Ingrese la ruta del archivo de registro de pasajeros: ";
                std::getline(std::cin, otraRuta);

                gestorPasajeros.procesarIngresoPasajero(otraRuta);
                break;
            }
            case 4: {
                std::string numeroPasaporte;
                std::cout << "Ingrese el número de pasaporte del pasajero: ";
                std::getline(std::cin, numeroPasaporte);

                gestorPasajeros.buscarPasajeroEnLista(numeroPasaporte);
                break;
            }
            case 5: {
                do {
                    std::cout << "---------------REPORTES---------------" << std::endl;
                    std::cout << "|  1. Lista de aviones disponibles   |" << std::endl;
                    std::cout << "|  2. Lista de aviones en mantenimiento|" << std::endl;
                    std::cout << "|    3. Mostrar pila de equipaje     |" << std::endl;
                    std::cout << "|  4. Mostrar pasajeros ordenados    |" << std::endl;
                    std::cout << "|   5. Volver al menú principal      |" << std::endl;
                    std::cout << "Ingrese una opción: ";
                    std::cin >> subOpcion;

                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    switch (subOpcion) {
                        case 1:
                            gestorAviones.mostrarAvionesDisponibles();
                            break;
                        case 2:
                            gestorAviones.mostrarAvionesMantenimiento();
                            break;
                        case 3:
                            gestorPasajeros.mostrarPilaEquipaje();
                            break;
                        case 4:
                            gestorPasajeros.mostrarListaEquipajeCeroOrdenada();
                            break;
                        case 5:
                            break;
                        default:
                            std::cout << "Opción inválida. Por favor, seleccione una opción válida." << std::endl;
                            break;
                    }
                } while (subOpcion != 5);
                break;
            }
            case 6:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opción inválida. Por favor, seleccione una opción válida." << std::endl;
                break;
        }
    } while (opcion != 6);

    return 0;
}
