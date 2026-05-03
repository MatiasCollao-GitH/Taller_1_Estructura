cmake_minimum_required(VERSION 4.2)
project(Taller_1_Estructura)

set(CMAKE_CXX_STANDARD 20)

include_directories(classes core data_structures)

add_executable(Taller_1_Estructura main.cpp
        classes/Cancion.h
        classes/Cancion.cpp
        core/Reproductor.h
        core/Reproductor.cpp
        data_structures/Nodo.h
        data_structures/ListaEnlazada.h
        data_structures/Pila.h
        data_structures/Cola.h)
