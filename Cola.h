#ifndef COLA_H
#define COLA_H
#include "Nodo.h"

template <typename Tipo>
class Cola{
private:
    Nodo<Tipo>* frente = NULL;
    Nodo<Tipo>* ultimo = NULL;
public:
    unsigned int size;
    Cola(){
        size = 0;
    }

    Nodo<Tipo>* getFrente(){
        return frente;
    }

    bool isEmpty(){
        if(frente)
            return false;

        return true;
    }

    bool quitarDeCola(){
        Nodo<Tipo>* temp;
        if(frente){
            temp = frente;
            frente = frente->anterior;
            delete temp;
            size--;

            return true;
        }

        return false;
    }

    void anular(){
        while(quitarDeCola());
    }

    /**
     * @brief agregar - Agrega el objeto a la cola
     * @param valor - Valor a dar al nuevo objeto
     * @return - True si se pudo
     */
    bool agregar(Tipo valor){
        Nodo<Tipo>* n = new Nodo<Tipo>(valor);
        ponerEnCola(n);
        size++;

        return true;
    }

private:
    void ponerEnCola(Nodo<Tipo>* n){
        if(!frente){
            frente = n;
            ultimo = n;
            return;
        }

        ultimo->anterior = n;
        ultimo = n;        
    }
};


#endif // COLA_H
