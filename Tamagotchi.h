#ifndef TAMAGOTCHI_H
#define TAMAGOTCHI_H
#include <iostream>

using namespace std;

enum Tipos{
    Wolf,
    Ghost,
    Snake
};



class Tamagotchi
{
public:
    Tamagotchi();

private:
    string nombre;
    unsigned int hp, waitTime;

};

#endif // TAMAGOTCHI_H
