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
        Pila.h
        NodoAvion.h
        ListaAviones.h
        ListaAviones.cpp
        ColaPasajeros.cpp
)
target_link_libraries(EDDFINAL PUBLIC cgraph gvc)
