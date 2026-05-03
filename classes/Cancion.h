//
// Created by Matías Collao on 03-05-2026.
//

#ifndef TALLER_1_ESTRUCTURA_CANCION_H
#define TALLER_1_ESTRUCTURA_CANCION_H
#include <string>
using namespace std;

class Cancion {
    private:
        int id;
        string nombre;
        string artista;
        string album;
        int ano;
        int duracion;
        string ruta;
    public:
    Cancion(int id, string nombre, string artista, string album, int ano, int duracion, string ruta);

    int getId();
    string getNombre();
    string getArtista();
    string getAlbum();
    int getAno();
    int getDuracion();
    string getRuta();

};
#endif //TALLER_1_ESTRUCTURA_CANCION_H
