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
    Mensaje(QString mensaje, int tipo);
    QString getMensaje();
    int getTipo();
    const static int WIN = 0, LOSS = 1;
private:
    QString mensaje;
    int tipo;
};

#endif // MENSAJES_H
