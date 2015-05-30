#include "Mensaje.h"

Mensaje::Mensaje(string mess, int tipo)
{
    this->mensaje = mess;
    this->tipo = tipo;
}

string Mensaje::getMensaje(){
    return this->mensaje;
}

int Mensaje::getTipo(){
    return tipo;
}
