#include <iostream>
#include <limits> // Para usar la función de limpiar el búfer de entrada
#include "GestorAviones.h"
#include "GestorPasajeros.h"
using namespace std;

int main() {
    int opcion, subOpcion;
    GestorAviones gestor;
    GestorPasajeros gestorPasajeros;

    do {
        // Menú principal
        cout << "|---------------MENU----------------|" << endl;
        cout << "|       1. Carga de aviones         |" << endl;
        cout << "|      2. Carga de pasajeros        |" << endl;
        cout << "|     3. Procesar registro          |" << endl;
        cout << "|      4. Consultar pasajero        |" << endl;
        cout << "|      5. Visualizar reportes       |" << endl;
        cout << "|             6. Salir              |" << endl;
        cout << "|-----------------------------------|" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        // Limpiar el búfer de entrada
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Lógica para ejecutar la opción seleccionada
        switch (opcion) {
            case 1: {
                // Obtener la ruta del archivo de entrada
                string rutaArchivo;
                cout << "Ingrese la ruta del archivo JSON de aviones: ";
                getline(cin, rutaArchivo);

                // Llamar a la función cargarAvionesDesdeArchivo con la ruta del archivo
                gestor.cargarAvionesDesdeArchivo(rutaArchivo);
                break;
            }
            case 2: {
                // Obtener la ruta del archivo de entrada
                string rutaArchivo;
                cout << "Ingrese la ruta del archivo JSON de pasajeros: ";
                getline(cin, rutaArchivo);

                // Llamar a la función cargarPasajerosDesdeArchivo con la ruta del archivo
                gestorPasajeros.cargarPasajerosDesdeArchivo(rutaArchivo);
                break;
            }
            case 3: {
                gestorPasajeros.procesarRegistro();
                break;
            }
            case 4: {
                // Consultar pasajero por número de pasaporte
                string numeroPasaporte;
                cout << "Ingrese el número de pasaporte del pasajero: ";
                getline(cin, numeroPasaporte);
                gestorPasajeros.consultarPasajero(numeroPasaporte);
                break;
            }
            case 5:
                do {
                    // Submenú de reportes
                    cout << "---------------REPORTES---------------" << endl;
                    cout << "|  1. Lista de aviones disponibles   |" << endl;
                    cout << "|2. Lista de aviones en mantenimiento|" << endl;
                    cout << "|    3. Mostrar pila de equipaje     |" << endl;
                    cout << "|  4. Mostrar pasajeros ordenados    |" << endl;
                    cout << "|   5. Volver al menú principal      |" << endl;
                    cout << "Ingrese una opción: ";
                    cin >> subOpcion;

                    // Limpiar el búfer de entrada
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    switch (subOpcion) {
                        case 1:
                            gestor.mostrarAvionesDisponibles();
                            break;
                        case 2:
                            gestor.mostrarAvionesMantenimiento();
                            break;
                        case 3:
                            gestorPasajeros.mostrarEquipaje();
                            break;
                        case 4:
                            gestorPasajeros.mostrarPasajerosOrdenados();
                            break;
                        case 5:
                            // Volver al menú principal
                            break;
                        default:
                            cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
                            break;
                    }
                } while (subOpcion != 5);
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
                break;
        }
    } while (opcion != 6);

    return 0;
}
