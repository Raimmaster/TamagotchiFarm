#include "Mensaje.h"

Mensaje::Mensaje(QString mensaje, TIPO tipo)
{
    this->mensaje = mensaje;
    this->tipo = tipo;
}

QString Mensaje::getMensaje(){
    return mensaje;
}

TIPO Mensaje::getTipo(){
    return tipo;
}
