//
// Created by Matías Collao on 03-05-2026.
//

#ifndef TALLER_1_ESTRUCTURA_REPRODUCTOR_H
#define TALLER_1_ESTRUCTURA_REPRODUCTOR_H

#include <string>

#include "Cancion.h"
#include "../data_structures/ListaEnlazada.h"
using namespace std;

class Reproductor {
    private:
    ListaEnlazada<Cancion> listaGeneral;

    bool modoAleatorio;
    int modoRepeticion;
    bool estaReproduciendo;

    public:
    Reproductor();

    void cargarCanciones();
    void mostrarTodasLasCanciones();

};



#endif //TALLER_1_ESTRUCTURA_REPRODUCTOR_H
