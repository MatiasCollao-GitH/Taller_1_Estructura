//
// Created by Matías Collao on 03-05-2026.
//

#ifndef TALLER_1_ESTRUCTURA_LISTAENLAZADA_H
#define TALLER_1_ESTRUCTURA_LISTAENLAZADA_H
#include "Nodo.h"

template <typename T>
class ListaEnlazada {
    private:
    Nodo<T>* cabeza;
    int tamano;

    public:
    ListaEnlazada() {
        cabeza = nullptr;
        tamano = 0;
    }
    void insertarFinal(T* nuevoDato) {
        Nodo<T>* nuevoNodo = new Nodo<T>(nuevoDato);

        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
        tamano++;

    }
    int getTamano() {
        return tamano;
    }
    T* obtener(int indice) {
        if (indice < 0 || indice >= tamano) return nullptr;

        Nodo<T>* actual = cabeza;
        for (int i = 0; i < indice; i++) {
            actual = actual->siguiente;
        }
        return actual->dato;
    }

};



#endif //TALLER_1_ESTRUCTURA_LISTAENLAZADA_H
