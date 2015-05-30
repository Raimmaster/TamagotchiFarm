#include "Mensaje.h"

Mensaje::Mensaje(QString mensaje, int tipo)
{
    this->mensaje = mensaje;
    this->tipo = tipo;
}

QString Mensaje::getMensaje(){
    return mensaje;
}

int Mensaje::getTipo(){
    return tipo;
}
