#ifndef MENSAJES_H
#define MENSAJES_H
#include <QString>

using namespace std;

enum TIPO{
    WIN,
    LOSS
};

class Mensaje
{
public:
    Mensaje(QString mensaje, TIPO tipo);
    QString getMensaje();
    TIPO getTipo();
private:
    QString mensaje;
    TIPO tipo;
};

#endif // MENSAJES_H
