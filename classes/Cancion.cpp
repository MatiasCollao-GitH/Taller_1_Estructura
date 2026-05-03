//
// Created by Matías Collao on 03-05-2026.
//

#include "Cancion.h"
using namespace std;

Cancion::Cancion(int id, string nombre, string artista, string album, int ano, int duracion, string ruta) {
    this->id = id;
    this->nombre = nombre;
    this->artista = artista;
    this->album = album;
    this->ano = ano;
    this->duracion = duracion;
    this->ruta = ruta;

}

int Cancion::getId() {return id;}
string Cancion::getNombre() {return nombre;}
string Cancion::getArtista() {return artista;}
string Cancion::getAlbum() {return album;}
int Cancion::getAno() {return ano;}
int Cancion::getDuracion() {return duracion;}
string Cancion::getRuta() {return ruta;}








