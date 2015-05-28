#ifndef TAMAGOTCHI_H
#define TAMAGOTCHI_H
#include <iostream>
#include "Pila.h"
#include "Cola.h"

using namespace std;

enum Tipos{
    WOLF,
    GHOST,
    SNAKE
};

enum ActivityCoins{
    FEED,
    SLEEP,
    CURE,
    CLEAN
};

class Tamagotchi
{
public:
    Tamagotchi(string nombre, int tipo);
    Pila<int> hambre, sleep, enfermedad, desechos;
    Cola<int> myCoins, giftCoins;
    Cola<string> logros;

    void setResistances();

    unsigned int getHp();
    void checkResistances(int h, int s, int e, int d);
    void useCoin();
    string imagePath = "";
    ~Tamagotchi();//destroyer
private:
    string nombre;
    int tipo;
    unsigned int hp = 100;
    int rHambre, rSleep, rEnfermedad, rDesechos;//resistencias
};

#endif // TAMAGOTCHI_H
