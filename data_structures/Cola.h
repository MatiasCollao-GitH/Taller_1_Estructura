//
// Created by Matías Collao on 03-05-2026.
//

#ifndef TALLER_1_ESTRUCTURA_COLA_H
#define TALLER_1_ESTRUCTURA_COLA_H
#include "Nodo.h"

template<typename T>
class Cola {
private:
    Nodo<T> *frente;
    Nodo<T> *final;

public:
    Cola() { frente = final = nullptr; }

    void encolar(T *dato) {
        Nodo<T> *nuevo = new Nodo<T>(dato);
        if (final == nullptr) {
            frente = final = nuevo;
            return;
        }
        final->siguiente = nuevo;
        final = nuevo;
    }

    T *desencolar() {
        if (frente == nullptr) return nullptr;
        Nodo<T> *aux = frente;
        T *dato = aux->dato;
        frente = frente->siguiente;
        if (frente == nullptr) final = nullptr;
        delete aux;
        return dato;
    }

    bool estaVacia() { return frente == nullptr; }

    ~Cola() {
        while (frente != nullptr) {
            Nodo<T> *aux = frente;
            frente = frente->siguiente;
            delete aux;
        }
        final = nullptr;
    }
};


#endif //TALLER_1_ESTRUCTURA_COLA_H
