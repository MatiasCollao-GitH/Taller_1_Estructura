//
// Created by Matías Collao on 03-05-2026.
//

#ifndef TALLER_1_ESTRUCTURA_REPRODUCTOR_H
#define TALLER_1_ESTRUCTURA_REPRODUCTOR_H

#include <string>

#include "Cancion.h"
#include "Cola.h"
#include "Pila.h"
#include "../data_structures/ListaEnlazada.h"
using namespace std;

class Reproductor {
    private:
    ListaEnlazada<Cancion> listaGeneral;
    Pila<Cancion> historial;
    Cola<Cancion> colaReproduccion;

    Cancion* cancionActual;
    bool pausado;
    int modoReproduccion; //0 1 2


    bool modoAleatorio;
    int modoRepeticion;
    bool estaReproduciendo;

    public:
    Reproductor();
    void cargarCanciones();
    void mostrarTodasLasCanciones();

    void reproducirPausar();
    void siguientePista();
    void anteriorPista();
    Cancion* getCancionActual();
    bool estaPausado();

    Cancion *buscarPorId(int id);

    void guardarConfiguracion();

    void cargarConfiguracion();

    void cambiarModoAleatorio();

    void mezclarCola();

    void cambiarModoRepeticion();

    bool getModoAleatorio();

    int getModoRepeticion();

    void mostrarListaReproduccion();

    void saltarACancion(int posicion);

    void agregarCancionAlRegistro(string nombre, string artista, string album, int anio, int duracion, string ruta);

    void eliminarCancionDelRegistro(int posicion);

    void reproducirEspecifica(int posicion);

    void agregarACola(int posicion);

};


#endif //TALLER_1_ESTRUCTURA_REPRODUCTOR_H
