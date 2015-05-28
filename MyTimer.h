#ifndef MYTIMER_H
#define MYTIMER_H

#include <QtCore>

class MyTimer : public QObject
{
    Q_OBJECT

public:
    QTimer* timer;
    MyTimer(unsigned int* tiempo);
    unsigned int* tiempo;

public slots:
    void slotIncrement();
};

#endif // MYTIMER_H
