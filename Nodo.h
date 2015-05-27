#ifndef NODO_H
#define NODO_H

#include <iostream>
using namespace std;

template <typename Tipo>
class Nodo
{
public:
    Tipo valor;
    Nodo* anterior;
    Nodo(Tipo valor){
        this->valor = valor;
        this->anterior = NULL;
    }
};

#endif // NODO_H
