#ifndef PILA_H
#define PILA_H

#include "Nodo.h"

template <typename Tipo>
class Pila{
private:
    Nodo<Tipo>* tope = NULL;

public:
    Pila(){

    }

    Nodo<Tipo>* getTope(){
        return tope;
    }

    void meter(Nodo<Tipo>* obj){
        if(tope)
            obj->anterior = tope;

        tope = obj;
    }

    bool sacar(){
        if(tope){
            Nodo<Tipo>* t = tope;
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

    bool agregar(Tipo valor){
        Nodo<Tipo>* n = new Nodo<Tipo>(valor);
        meter(n);

        return true;
    }
};

#endif // PILA_H
