#ifndef MENSAJE_H
#define MENSAJE_H

#include <QString>
#include <iostream>

using namespace std;

enum TIPO{
    WIN,
    LOSS
};

class Mensaje
{
public:
    Mensaje(string mess, int tipo);
    string getMensaje();
    int getTipo();
    const static int WIN = 0, LOSS = 1;
private:
    string mensaje;
    int tipo;
};

#endif // MENSAJE_H
