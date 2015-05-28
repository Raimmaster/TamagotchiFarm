#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFileDialog>
#include "Tamagotchi.h"
#include <vector>

#include "MyTimer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    const static unsigned int TIEMPO_VICTORIA = 8, LOSE_TIME = 5;
    int tipoToInt();
    Tamagotchi* searchFarm(string nombre);
    void updateComboElegir();
    ~MainWindow();

public slots:
    void incrementCounter();

private slots:
    void on_bCrear_clicked();

    void on_bCambiar_clicked();

private:
    Ui::MainWindow *ui;
    //Variables para almacenar una imagen
    QPixmap image;
    QImage  *imageObject;
    QGraphicsScene *scene;
    void init();
    vector<Tamagotchi*> granja;
    Tamagotchi* actual;
    //QTimer* timer;
    MyTimer* timer;
    unsigned int* TIEMPO;
};

#endif // MAINWINDOW_H
