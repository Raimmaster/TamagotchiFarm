#include "MyTimer.h"

#include <iostream>

using namespace std;

MyTimer::MyTimer(unsigned int* tiempo)
{    
    this->tiempo = tiempo;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotIncrement()));
    timer->start(1000);
}

void MyTimer::slotIncrement(){
    (*tiempo)++;

    cout<<(*tiempo)<<endl;
}
