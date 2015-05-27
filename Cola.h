#ifndef COLA_H
#define COLA_H
#include "Nodo.h"

template <typename Tipo>
class Cola{
public:
    Cola(){

    }
    Nodo* frente = NULL;
    Nodo* ultimo = NULL;
    Nodo* getFrente(){
        return frente;
    }

    bool isEmpty(){
        if(frente)
            return false;

        return true;
    }
    void ponerEnCola(Nodo<Tipo>* n){
        if(!frente){
            frente = n;
            ultimo = n;
            return;
        }

        ultimo->anterior = n;
        ultimo = n;
    }

    bool quitarDeCola(){
        Nodo<Tipo>* temp;
        if(frente){
            temp = frente;
            frente = frente->anterior;
            delete temp;
            return true;
        }

        return false;
    }

    void anular(){
        while(quitarDeCola());
    }
};


#endif // COLA_H
