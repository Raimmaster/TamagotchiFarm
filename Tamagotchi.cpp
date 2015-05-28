#include "Tamagotchi.h"

void Tamagotchi::setResistances(){
    switch(tipo){
        case 0:
            rHambre = 0;
            rSleep = 2;
            rEnfermedad = 1;
            rDesechos = 2;
            break;
        case 1:
            rHambre = 0;
            rSleep = 3;
            rEnfermedad = 3;
            rDesechos = 0;
            break;
        case 2:
            rHambre = 3;
            rSleep = 2;
            rEnfermedad = 0;
            rDesechos = 1;
            break;
    }
}

Tamagotchi::Tamagotchi(string nombre, int tipo)
{
    this->nombre = nombre;
    this->tipo = tipo;
    setResistances();
    hp = 100;
    imagePath = "";
}

string Tamagotchi::getNombre(){
    return nombre;
}

unsigned int Tamagotchi::getHp(){
    return hp;
}

/**
 * @brief Tamagotchi::checkResistances - Chequea las resistencias para disminuir la vida lo necesario
 * @param h - Cantidad de hambre
 * @param s - Cantidad de sueño
 * @param e - Cantidad de enfermedad
 * @param d - Cantidad de desechos
 */
void Tamagotchi::checkResistances(int h, int s, int e, int d){
    h -= rHambre;
    s -= rSleep;
    e -= rEnfermedad;
    d -= rDesechos;

    if(h < 0)
        h = 0;
    if(s < 0)
        s = 0;
    if(e < 0)
        e = 0;
    if(d < 0)
        d = 0;

    hp -= (h + s + e + d);//disminuir vida menos la suma de todos los valores de daño
}

/**
 * @brief Tamagotchi::~Tamagotchi - El destructor anula todas las colecciones
 */
Tamagotchi::~Tamagotchi(){
    hambre.anular();
    sleep.anular();
    enfermedad.anular();
    desechos.anular();
    myCoins.anular();
    giftCoins.anular();
    logros.anular();
}
