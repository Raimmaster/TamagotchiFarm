#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFileDialog>
#include "Tamagotchi.h"
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    const static unsigned int TIEMPO_VICTORIA = 40, LOSE_TIME = 30;
    int tipoToInt();
    bool searchFarm(string nombre);
    ~MainWindow();

private slots:
    void on_bCrear_clicked();

private:
    Ui::MainWindow *ui;
    //Variables para almacenar una imagen
    QPixmap image;
    QImage  *imageObject;
    QGraphicsScene *scene;
    void init();
    vector<Tamagotchi*> granja;
};

#endif // MAINWINDOW_H
