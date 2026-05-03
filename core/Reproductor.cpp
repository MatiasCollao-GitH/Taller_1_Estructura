//
// Created by Matías Collao on 03-05-2026.
//

#include "Reproductor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
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
    if (cancionActual == nullptr) return;
    if (cancionActual != nullptr) {
        historial.apilar(cancionActual);
    }
    if (modoRepeticion == 1) return;

    if (!colaReproduccion.estaVacia()) {
        cancionActual = colaReproduccion.desencolar();
    } else {
        if (modoRepeticion == 2) {
            for (int i = 0; i < listaGeneral.getTamano(); i++) {
                colaReproduccion.encolar(listaGeneral.obtener(i));
            }
            if (modoAleatorio) mezclarCola();
            cancionActual = colaReproduccion.desencolar();
        } else {
            cancionActual = nullptr;
        }
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

Cancion* Reproductor::buscarPorId(int id) {
    for (int i = 0; i < listaGeneral.getTamano(); i++) {
        if (listaGeneral.obtener(i)->getId() == id) {
            return listaGeneral.obtener(i);
        }
    }
    return nullptr;
}
void Reproductor::guardarConfiguracion() {
    ofstream archivo("status.cfg");
    if (!archivo.is_open()) return;

    archivo << "ID_ACTUAL " << (cancionActual ? cancionActual->getId() : -1) << endl;
    archivo << "MODO_PAUSA " << (pausado ? 1 : 0) << endl;
    archivo << "ALEATORIO " << (modoAleatorio ? 1 : 0) << endl;
    archivo << "REPETICION " << modoRepeticion << endl;
    archivo << "PENDIENTES ";
    archivo << endl;

    archivo.close();
}

void Reproductor::cargarConfiguracion() {
    ifstream archivo("status.cfg");
    if (!archivo.is_open()) {
        this->cancionActual = nullptr;
        this->pausado = true;
        this->modoAleatorio = false;
        this->modoRepeticion = 0;
        return;
    }

    string parametro;
    while (archivo >> parametro) {
        if (parametro == "ID_ACTUAL") {
            int id;
            archivo >> id;
            this->cancionActual = buscarPorId(id);
        } else if (parametro == "MODO_PAUSA") {
            int p;
            archivo >> p;
            this->pausado = (p == 1);
        } else if (parametro == "ALEATORIO") {
            int a;
            archivo >> a;
            this->modoAleatorio = (a == 1);
        } else if (parametro == "REPETICION") {
            archivo >> this->modoRepeticion;
        }
    }
    archivo.close();
}

void Reproductor::cambiarModoAleatorio() {
    modoAleatorio = !modoAleatorio;
    if (modoAleatorio) {
        mezclarCola();
    }
}

void Reproductor::mezclarCola() {
    if (colaReproduccion.estaVacia()) return;
    int n = 0;
    ListaEnlazada<Cancion> temp;
    while (!colaReproduccion.estaVacia()) {
        temp.insertarFinal(colaReproduccion.desencolar());
        n++;
    }

    Cancion** arreglo = new Cancion*[n];
    for (int i = 0; i < n; i++) {
        arreglo[i] = temp.obtener(i);
    }

    srand(time(0));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Cancion* aux = arreglo[i];
        arreglo[i] = arreglo[j];
        arreglo[j] = aux;
    }

    for (int i = 0; i < n; i++) {
        colaReproduccion.encolar(arreglo[i]);
    }

    delete[] arreglo;
}

void Reproductor::cambiarModoRepeticion() {
    modoRepeticion = (modoRepeticion + 1) % 3;
}

bool Reproductor::getModoAleatorio() {
    return this->modoAleatorio;
}

int Reproductor::getModoRepeticion() {
    return this->modoRepeticion;
}

void Reproductor::mostrarListaReproduccion() {
    cout << "Actual (" << (modoAleatorio ? "S-" : "")
         << (modoRepeticion == 1 ? "R1" : (modoRepeticion == 2 ? "RA" : ""))
         << "): " << (cancionActual ? cancionActual->getNombre() : "Vacía") << endl;

    cout << "Lista de reproducción actual:" << endl;

    if (colaReproduccion.estaVacia()) {
        cout << "Vacía" << endl;
    } else {
        ListaEnlazada<Cancion> temp;
        int i = 1;
        while (!colaReproduccion.estaVacia()) {
            Cancion* c = colaReproduccion.desencolar();
            cout << i << ". " << c->getNombre() << " - " << c->getArtista() << endl;
            temp.insertarFinal(c);
            i++;
        }

        for (int j = 0; j < temp.getTamano(); j++) {
            colaReproduccion.encolar(temp.obtener(j));
        }
    }
}

void Reproductor::agregarCancionAlRegistro(string nombre, string artista, string album, int ano, int duracion, string ruta) {
    int nuevoId = listaGeneral.getTamano() + 1;
    Cancion* nueva = new Cancion(nuevoId, nombre, artista, album, ano, duracion, ruta);
    listaGeneral.insertarFinal(nueva);

    ofstream archivo("music_source.txt", ios::app);
    if (archivo.is_open()) {
        archivo << nuevoId << "," << nombre << "," << artista << "," << album << ","
                << ano << "," << duracion << "," << ruta << endl;
        archivo.close();
    }
}

void Reproductor::eliminarCancionDelRegistro(int posicion) {
    int indice = posicion - 1;
    if (indice < 0 || indice >= listaGeneral.getTamano()) return;
    ofstream archivo("music_source.txt");
    for (int i = 0; i < listaGeneral.getTamano(); i++) {
        Cancion* c = listaGeneral.obtener(i);
        archivo << c->getId() << "," << c->getNombre() << "," << c->getArtista() << ","
                << c->getAlbum() << "," << c->getAno() << "," << c->getDuracion() << ","
                << c->getRuta() << endl;
    }
    archivo.close();
}

void Reproductor::saltarACancion(int posicion) {
    for (int i = 1; i < posicion; i++) {
        if (!colaReproduccion.estaVacia()) {
            colaReproduccion.desencolar();
        }
    }
    siguientePista();
}

Reproductor::~Reproductor() {
    for (int i = 0; i < listaGeneral.getTamano(); i++) {
        delete listaGeneral.obtener(i);
    }
}