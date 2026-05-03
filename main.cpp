#include <iostream>

#include "Reproductor.h"
using namespace std;

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void mostrarMenu(Reproductor& miRepo) {
    limpiarPantalla();
    Cancion* actual = miRepo.getCancionActual();

    cout << "========================================" << endl;
    if (actual != nullptr) {
        string estado = miRepo.estaPausado() ? "En Pausa" : "Reproduciendo";
        cout << estado << ": " << actual->getNombre() << endl;
        cout << "Artista: " << actual->getArtista() << endl;
        cout << "Album: " << actual->getAlbum() << " [" << actual->getAno() << "]" << endl;
    } else {
        cout << "Reproduccion Detenida" << endl;
    }
    cout << "========================================" << endl;

    cout << "W - Reproducir/Pausar" << endl;
    cout << "Q - Pista Anterior" << endl;
    cout << "E - Pista Siguiente" << endl;
    cout << "X - Salir" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Ingrese Opcion: ";
}

int main() {
    Reproductor miReproductor;
    miReproductor.cargarCanciones();
    cout << "\n ---LISTADO DE CANCIONES---" << endl;
    miReproductor.mostrarTodasLasCanciones();

    char opcion;
    bool ejecutar = true;

    while (ejecutar) {
        mostrarMenu(miReproductor);
        cin >> opcion;
        opcion = toupper(opcion);

        switch (opcion) {
            case 'W':
                miReproductor.reproducirPausar();
                break;
            case 'Q':
                miReproductor.anteriorPista();
                break;
            case 'E':
                miReproductor.siguientePista();
                break;
            case 'X':
                ejecutar = false;
                cout << "Guardando y Saliendo..." << endl;
                break;
            default:
                cout << "Opción no valida" << endl;
                break;
        }
    }






    return 0;
}
