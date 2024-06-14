cmake_minimum_required(VERSION 3.28)
project(EDDFINAL)

set(CMAKE_CXX_STANDARD 17)

# Añadir el ejecutable
add_executable(EDDFINAL
        main.cpp
        GestorAviones.h
        Avion.h
        GestorAviones.cpp
        GestorPasajeros.h
        GestorPasajeros.cpp
        NodoAvion.h
        ListaAviones.h
        ListaAviones.cpp
        NodoPasajero.h
        Pasajero.h
        ListaDoblementeEnlazada.cpp
        Pila.cpp
        Pila.h
        ListaDoblementeEnlazada.h
        Pasajero.cpp
)
target_link_libraries(EDDFINAL PUBLIC cgraph gvc)
