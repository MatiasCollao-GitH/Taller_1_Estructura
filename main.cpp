//Matías Collao Valdivia 220601528
//
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


void mostrarMenu(Reproductor &miRepo) {
    //limpiarPantalla();

    Cancion *actual = miRepo.getCancionActual();

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
    cout << "S - Activar/Desactivar modo aleatorio" << endl;
    cout << "R - Repetición (Desactivado/Repetir una/Repetir todas)" << endl;
    cout << "A - Ver lista de reproducción actual" << endl;
    cout << "L - Listado de canciones" << endl;
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
            case 'A': {
                bool enSubmenu = true;
                while (enSubmenu) {
                    limpiarPantalla();
                    miReproductor.mostrarListaActual();
                    cout << "\nOpciones:\nS<num> Saltar a la canción seleccionada\nV Volver al menú principal" << endl;
                    cout << "Ingrese Opción: ";
                    string comando;
                    cin >> comando;

                    char subOpcion = toupper(comando[0]);
                    if (subOpcion == 'S' && comando.length() > 1) {
                        int num = stoi(comando.substr(1));
                        miReproductor.saltarACancion(num);
                        enSubmenu = false;
                    } else if (subOpcion == 'V') {
                        enSubmenu = false;
                    }
                }
                break;
            }
            case 'L': {
                bool enSubmenuL = true;
                while (enSubmenuL) {
                    //limpiarPantalla();
                    miReproductor.mostrarTodasLasCanciones();
                    cout << "\nOpciones: R<num> Reproducir, A<num> Agregar al final, N Nuevo, D<num> Eliminar, V Volver" << endl;
                    cout << "Ingrese Opcion: ";
                    string comando;
                    cin >> comando;

                    char subOpcion = toupper(comando[0]);
                    int num = 0;

                    // Extraemos el número si el comando es largo (ej: R10)
                    if (comando.length() > 1) {
                        num = stoi(comando.substr(1));
                    }

                    if (subOpcion == 'R') {
                        miReproductor.reproducirEspecifica(num);
                        miReproductor.guardarConfiguracion();
                        enSubmenuL = false;
                    }
                    else if (subOpcion == 'A') {
                        miReproductor.agregarACola(num);
                        miReproductor.guardarConfiguracion();
                        cout << "Cancion agregada a la lista actual." << endl;
                    }
                    else if (subOpcion == 'N') {
                        string n, art, alb, rut;
                        int an, dur;
                        cin.ignore();
                        cout << "Nombre: "; getline(cin, n);
                        cout << "Artista: "; getline(cin, art);
                        cout << "Album: "; getline(cin, alb);
                        cout << "Ano: "; cin >> an;
                        cout << "Duracion (seg): "; cin >> dur;
                        cin.ignore();
                        cout << "Ruta del archivo: "; getline(cin, rut);

                        miReproductor.agregarCancionAlRegistro(n, art, alb, an, dur, rut);
                        miReproductor.guardarConfiguracion();
                    }
                    else if (subOpcion == 'D') {
                        miReproductor.eliminarCancionDelRegistro(num);
                        miReproductor.guardarConfiguracion();
                    }
                    else if (subOpcion == 'V') {
                        enSubmenuL = false;
                    }
                }
                break;
            }
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
