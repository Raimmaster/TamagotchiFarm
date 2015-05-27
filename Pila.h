#ifndef PILA_H
#define PILA_H

#include "Nodo.h"

template <typename Tipo>
class Pila{
private:
    Nodo* tope = NULL;

public:
    Pila(){

    }

    Nodo<Tipo>* getTope(){
        return tope;
    }

    void meter(Nodo* obj){
        if(tope)
            obj->anterior = tope;

        tope = obj;
    }

    bool sacar(){
        if(tope){
            Nodo* t = tope;
            tope = tope->anterior;
            delete t;
            return true;
        }

        return false;
    }

    bool isEmpty(){
        if(tope)
            return false;

        return true;
    }

    void anular(){
        while(sacar());
    }
};

#endif // PILA_H
