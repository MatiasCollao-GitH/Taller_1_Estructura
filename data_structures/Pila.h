//
// Created by Matías Collao on 03-05-2026.
//

#ifndef TALLER_1_ESTRUCTURA_PILA_H
#define TALLER_1_ESTRUCTURA_PILA_H
#include "Nodo.h"

template <typename T>
class Pila {
private:
    Nodo<T>* tope;
public:
    Pila() { tope = nullptr; }

    void apilar(T* dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        nuevo->siguiente = tope;
        tope = nuevo;
    }

    T* desapilar() {
        if (tope == nullptr) return nullptr;
        Nodo<T>* aux = tope;
        T* dato = aux->dato;
        tope = tope->siguiente;
        delete aux;
        return dato;
    }

    bool estaVacia() { return tope == nullptr; }
};


#endif //TALLER_1_ESTRUCTURA_PILA_H
