# Reproductor de Música C++ (Taller 1)

**Autor:** Matías Collao Valdivia  
**Carrera:** Ingeniería Civil Informática  
**Rut** 22.060.152-8

## 1. Descripción del Proyecto
Este programa es un reproductor de música desarrollado en C++ que utiliza estructuras de datos lineales implementadas manualmente, sin el uso de librerías STL como std::list o std::vector. El sistema permite gestionar un catálogo de canciones, controlar una cola de reproducción dinámica, mantener un historial mediante una pila y persistir el estado del usuario en archivos locales.

### Estructuras Implementadas:
*   **Lista Enlazada (Templates):** Utilizada para el almacenamiento y gestión del catálogo global de canciones.
*   **Pila (Templates):** Implementada para gestionar el historial de canciones reproducidas, permitiendo la función de "pista anterior".
*   **Cola (Templates):** Utilizada para la gestión de canciones pendientes en la lista de reproducción actual.

## 2. Instrucciones de Instalación y Ejecución
Para ejecutar este proyecto en un entorno local (optimizado para CLion), siga estos pasos:

1.  **Configuración en CLion**: Abra la carpeta del proyecto y el IDE detectará el archivo CMakeLists.txt automáticamente.
2.  **Archivos de Datos**: El archivo music_source.txt debe estar ubicado en la carpeta de ejecución (cmake-build-debug) para que el programa cargue la base de datos al iniciar.
3.  **Compilación**: Ejecute el programa desde el IDE; esto generará el archivo status.cfg para guardar el progreso de reproducción de forma automática.

## 3. Guía de Uso
El control del reproductor se realiza mediante comandos de teclado en la consola principal:

*   **W**: Reproducir o Pausar la canción actual.
*   **Q**: Volver a la pista anterior.
*   **E**: Avanzar a la siguiente pista.
*   **S**: Alternar el modo Aleatorio (mezcla la cola de reproducción actual una vez).
*   **R**: Ciclar entre los modos de repetición: Desactivado, Repetir Una (R1) y Repetir Todas (RA).
*   **A**: Acceder al submenú de lista actual (visualización de pendientes y salto a canción específica).
*   **L**: Acceder al submenú de Catálogo (permite agregar nuevas canciones, eliminar registros o reproducir una específica).
*   **X**: Salir del programa guardando el estado y liberando la memoria utilizada.

## 4. Diagrama de Clases (Arquitectura)
Este diagrama representa la arquitectura del software y la relación de composición entre el controlador y las estructuras de datos:
```mermaid
classDiagram
    class Reproductor {
        -ListaEnlazada canciones
        -Pila historial
        -Cola pendientes
        -Cancion actual
        +cargarCanciones()
        +guardarConfiguracion()
        +mezclarCola()
    }
    class ListaEnlazada {
        -Nodo cabeza
        +insertarFinal(T)
        +eliminar(int)
    }
    class Pila {
        -Nodo tope
        +apilar(T)
        +desapilar()
    }
    class Cola {
        -Nodo frente
        +encolar(T)
        +desencolar()
    }
    class Cancion {
        -int id
        -string nombre
        -string artista
    }

    Reproductor "1" *-- "1" ListaEnlazada
    Reproductor "1" *-- "1" Pila
    Reproductor "1" *-- "1" Cola
    ListaEnlazada "1" *-- "many" Nodo
    Pila "1" *-- "many" Nodo
    Cola "1" *-- "many" Nodo
    Nodo "1" --> "1" Cancion