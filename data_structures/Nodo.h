//
// Created by Matías Collao on 03-05-2026.
//

#ifndef TALLER_1_ESTRUCTURA_NODO_H
#define TALLER_1_ESTRUCTURA_NODO_H

template<typename T>
class Nodo {
public:
    T *dato;
    Nodo<T> *siguiente;

    Nodo(T *nuevoDato) {
        this->dato = nuevoDato;
        this->siguiente = nullptr;
    }
};


#endif //TALLER_1_ESTRUCTURA_NODO_H
