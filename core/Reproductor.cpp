//
// Created by Matías Collao on 03-05-2026.
//

#include "Reproductor.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Reproductor::Reproductor() {
    this->modoAleatorio = false;
    this->modoRepeticion = 0;
    this->estaReproduciendo = false;
    cancionActual = nullptr;
    pausado = true;
    modoRepeticion = 0;
}

void Reproductor::cargarCanciones() {
    ifstream archivo("music_source.txt");
    string linea;

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id_str, nombre, artista, album, anio_str, duracion_str, ruta;

        getline(ss, id_str, ',');
        getline(ss, nombre, ',');
        getline(ss, artista, ',');
        getline(ss, album, ',');
        getline(ss, anio_str, ',');
        getline(ss, duracion_str, ',');
        getline(ss, ruta, ',');

        int id = stoi(id_str);
        int anio = stoi(anio_str);
        int duracion = stoi(duracion_str);

        Cancion* nuevaCancion = new Cancion(id, nombre, artista, album, anio, duracion, ruta);

        listaGeneral.insertarFinal(nuevaCancion);
    }

    archivo.close();
    cout << "Se cargaron " << listaGeneral.getTamano() << " canciones correctamente" << endl;


}

void Reproductor::mostrarTodasLasCanciones() {
    for (int i = 0; i < listaGeneral.getTamano(); i++) {
        Cancion* c = listaGeneral.obtener(i);
        cout << c->getId() << ". " << c->getNombre() << " - " << c->getArtista() << endl;
    }
}
void Reproductor::reproducirPausar() {
    if (cancionActual == nullptr && listaGeneral.getTamano() > 0) {
        cancionActual = listaGeneral.obtener(0);
    }
    pausado = !pausado;
}

void Reproductor::siguientePista() {
    if (cancionActual != nullptr) {
        historial.apilar(cancionActual);
    }

    if (!colaReproduccion.estaVacia()) {
        cancionActual = colaReproduccion.desencolar();
    } else {
        cout << "No hay mas canciones en la cola." << endl;
    }
}
void Reproductor::anteriorPista() {
    if (!historial.estaVacia()) {
        cancionActual = historial.desapilar();
    } else {
        cout << "No hay historial para retroceder." << endl;
    }
}

Cancion* Reproductor::getCancionActual() {return cancionActual; }
bool Reproductor::estaPausado() { return pausado;}



