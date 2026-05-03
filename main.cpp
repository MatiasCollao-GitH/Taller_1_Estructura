#include <iostream>

#include "Reproductor.h"
using namespace std;

void mostrarMenu() {
    cout << "--- REPRODUCTOR ---" << endl;
    cout << "W - Reproducir/Pausar" << endl;
    cout << "Q - Pista Anterior" << endl;
    cout << "E - Pista Siguiente" << endl;
    cout << "X - Salir" << endl;
    cout << "Ingrese Opcion: ";
};

int main() {
    Reproductor miReproductor;
    miReproductor.cargarCanciones();
    cout << "\n ---LISTADO DE CANCIONES---" << endl;
    miReproductor.mostrarTodasLasCanciones();

    char opcion;
    bool ejecutar = true;

    while (ejecutar) {
        mostrarMenu();
        cin >> opcion;
        opcion = toupper(opcion);

        switch (opcion) {
            case 'W':
                cout << "Cambiando estado de reproduccion..." << endl;
                break;
                //pausaPlay
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
