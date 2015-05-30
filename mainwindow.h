#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFileDialog>
#include "Tamagotchi.h"
#include <vector>
#include <QTimer>
#include <QMessageBox>
#include "Mensaje.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    const static unsigned int TIEMPO_VICTORIA = 8, LOSE_TIME = 5, CHECK_TIME = 5, TOPE_ACTIVIDADES = 5;
    int tipoToInt();
    Tamagotchi* searchFarm(string nombre);
    void updateComboElegir();
    ~MainWindow();

public slots:
    void incrementCounter();

private slots:
    void on_bCrear_clicked();

    void on_bCambiar_clicked();

    void on_bHambre_clicked();

    void on_bSleep_clicked();

    void on_bEnfermedad_clicked();

    void on_bDesechos_clicked();

    void on_bDonar_clicked();

private:
    Ui::MainWindow *ui;
    //Variables para almacenar una imagen
    QPixmap image;
    QImage  *imageObject;
    QGraphicsScene *scene;
    //Granja, valores de estado, timers
    vector<Tamagotchi*> granja;
    Tamagotchi* actual;
    QTimer* timer;
    QString pHambre, pSleep, pEnfermedad, pDesechos;
    QString log;
    unsigned int TIEMPO;
    //Funciones
    void init();
    void checkStatus();
    void checkVictory();
    void checkLoss();
    bool anyAtTop();
    //Check activity labels
    void setlHambreStatus();
    void setlSleepStatus();
    void setlEnfermedadStatus();
    void setlDesechosStatus();
    void setActivityLabelsStatus();
    void setCoinsLabels();
    //Check logs
    void actualizarVictorias();
    //blocks
    void changeActivitiesStatus();
    void blockEverything();
};

#endif // MAINWINDOW_H
