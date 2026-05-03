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
        string indicadores = "";
        if (miRepo.getModoAleatorio()) indicadores += "S-";
        if (miRepo.getModoRepeticion() == 1) indicadores += "R1";
        else if (miRepo.getModoRepeticion() == 2) indicadores += "RA";

        cout << "Reproduciendo (" << indicadores << "): " << actual->getNombre() << endl;
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
    miReproductor.cargarConfiguracion();
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
                miReproductor.guardarConfiguracion();
                break;
            case 'Q':
                miReproductor.anteriorPista();
                break;
            case 'E':
                miReproductor.siguientePista();
                break;
            case 'S':
                miReproductor.cambiarModoAleatorio();
                miReproductor.guardarConfiguracion();
                break;
            case 'R':
                miReproductor.cambiarModoRepeticion();
                miReproductor.guardarConfiguracion();
                break;
            case 'L': {
                limpiarPantalla();
                miReproductor.mostrarTodasLasCanciones();
                cout << "\nOpciones: R<num> Reproducir, A<num> Agregar al final, N Nuevo, D<num> Eliminar, V Volver" << endl;
                cout << "Ingrese comando (ej: R1 o N): ";
                string comando;
                cin >> comando;

                char subOpcion = toupper(comando[0]);
                if (subOpcion == 'N') {
                    string n, art, alb, rut;
                    int an, dur;
                    cout << "Nombre: "; cin.ignore(); getline(cin, n);
                    cout << "Artista: "; getline(cin, art);
                    miReproductor.agregarCancionAlRegistro(n, art, alb, an, dur, rut);
                } else if (subOpcion == 'D') {
                    int num = stoi(comando.substr(1));
                    miReproductor.eliminarCancionDelRegistro(num);
                }
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
