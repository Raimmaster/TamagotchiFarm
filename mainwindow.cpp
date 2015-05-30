#include "mainwindow.h"
#include "ui_mainwindow.h"

const int VICT = 0, LOST = 1;//constantes para ingresar el mensaje del log, gane o derrota
void init();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    init();
}

/**
 * @brief MainWindow::init - Inicialización de atributos necesarios en el form
 */
void MainWindow::init(){
    ui->lHambre->setText("");
    //\n---------
    ui->lSleep->setText("");
    ui->lEnfermedad->setText("");
    ui->lDesechos->setText("");


    QStringList listaTipos;
    listaTipos<<"Wolf"<<"Ghost"<<"Snake";
    ui->cTipo->addItems(listaTipos);

    ui->lCoinsPersonales->setText("Personales: 0");
    ui->lCoinsDonables->setText("Donables: 0");

    actual = NULL;
    pressedActivity = false;
    //QStrings para las pilas
    pHambre = "";
    pSleep = "";
    pEnfermedad = "";
    pDesechos = "";

    //Log
    cantidadLogs = 0;
    log = "";
    ui->lLog->setText(log);
    //Initialize timer
    TIEMPO = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(incrementCounter()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{   
    delete ui;
}

void MainWindow::checkStatus(){
    if(!actual)
        return;

    unsigned int randomPila = rand() % 4 + 1;
    unsigned int topeActual = 0;

    switch(randomPila){
        case 1://hambre
        topeActual = actual->hambre.getTope()->valor;
        if(topeActual < TOPE_ACTIVIDADES){
            actual->hambre.agregar(topeActual + 1);
            pHambre += "---------\n";
            ui->lHambre->setText(pHambre);
        }
            break;
        case 2://sueño
            topeActual = actual->sleep.getTope()->valor;
            if(topeActual < TOPE_ACTIVIDADES){
                actual->sleep.agregar(topeActual + 1);
                ui->lSleep->setText(ui->lSleep->text() + "---------\n");
            }
            break;
        case 3://enfermedad
            topeActual = actual->enfermedad.getTope()->valor;
            if(topeActual < TOPE_ACTIVIDADES){
                actual->enfermedad.agregar(topeActual + 1);
                ui->lEnfermedad->setText(ui->lEnfermedad->text() + "---------\n");
            }
            break;
        case 4://desechos
            topeActual = actual->desechos.getTope()->valor;
            if(topeActual < TOPE_ACTIVIDADES){
                actual->desechos.agregar(topeActual + 1);
                ui->lDesechos->setText(ui->lDesechos->text() + "---------\n");
            }
            break;
    }

    int dHambre = actual->hambre.getTope()->valor;
    int dSleep = actual->sleep.getTope()->valor;
    int dEnfermedad = actual->enfermedad.getTope()->valor;
    int dDesechos = actual->desechos.getTope()->valor;

    actual->checkResistances(dHambre, dSleep, dEnfermedad, dDesechos);
    if(actual->getHp() == 0)
        blockEverything();

    ui->pbHealth->setValue(actual->getHp());
}

bool MainWindow::anyAtTop(){
    if(!actual)
        return false ;

    int topHambre = actual->hambre.getTope()->valor;
    int topSleep = actual->sleep.getTope()->valor;
    int topEnfermedad = actual->enfermedad.getTope()->valor;
    int topDesechos = actual->desechos.getTope()->valor;

    if(topHambre == TOPE_ACTIVIDADES || topSleep == TOPE_ACTIVIDADES
            || topEnfermedad == TOPE_ACTIVIDADES || topDesechos == TOPE_ACTIVIDADES)
        return true;

    return false;
}

void MainWindow::actualizarVictorias(){
    int elTipo = LOST;
    do{
        elTipo = actual->logros.getFrente()->valor;
        if(cantidadLogs == 5){//check if log is full
            cantidadLogs = 0;
            log = "";
        }

        if(elTipo == VICT){
            QString nVictoria = "Has adquirido una victoria!";
            log += nVictoria + "\n";
            ui->lNewVictoria->setText(nVictoria);
        }        

        ui->lLog->setText(log);
        actual->logros.quitarDeCola();
    }while(elTipo == LOST);
}

void MainWindow::checkVictory(){
    if(!anyAtTop()){
        int coinType = rand() % 4;
        actual->giftCoins.agregar(coinType);
        ui->lCoinsDonables->setText(QString("Donables: %1").arg(actual->giftCoins.size));
        actual->logros.agregar(VICT);//agregar victoria
        cantidadLogs++;
        actualizarVictorias();
    }
}

void MainWindow::checkLoss(){
    if(anyAtTop()){
        ui->lNewVictoria->setText("Has adquirido una derrota!");
        actual->logros.agregar(LOST);
    }
}

void MainWindow::incrementCounter(){
    if(!actual || actual->getHp() == 0)
        return;

    TIEMPO++;

    if(TIEMPO % CHECK_TIME == 0)
        checkStatus();

    if(TIEMPO % TIEMPO_VICTORIA == 0)
        checkVictory();

    if(TIEMPO % LOSE_TIME == 0)
        checkLoss();

    if(pressedActivity && TIEMPO % LOAD_TIME == 0){
        pressedActivity = false;
        changeActivitiesStatus();
    }
}

int MainWindow::tipoToInt(){
    char tipo = ui->cTipo->currentText().toStdString().at(0);
    //W, G, S
    switch(tipo){
        case 'W':
            return 0;
        case 'G':
            return 1;
        case 'S':
            return 2;
        default:
            return -1;
    }
}

Tamagotchi* MainWindow::searchFarm(string nombre){
    for(unsigned int i = 0; i < granja.size(); i++){
        if(granja[i]->getNombre() == nombre)
            return granja[i];
    }

    return NULL;
}

void MainWindow::updateComboElegir(){
    ui->cTamagotchis->clear();
    for(unsigned int i = 0; i < granja.size(); i++){
        QString q = QString::fromStdString(granja[i]->getNombre());
        ui->cTamagotchis->addItem(q);
    }
}

void MainWindow::setlHambreStatus(){
    pHambre = "";
    for(int i = 0; i < actual->hambre.getTope()->valor; i++)
        pHambre += "---------\n";

    ui->lHambre->setText(pHambre);
}

void MainWindow::setlSleepStatus(){
    pSleep = "";
    for(int i = 0; i < actual->sleep.getTope()->valor; i++)
        pSleep += "---------\n";

    ui->lSleep->setText(pSleep);
}

void MainWindow::setlEnfermedadStatus(){
    pSleep = "";
    for(int i = 0; i < actual->enfermedad.getTope()->valor; i++)
        pSleep += "---------\n";

    ui->lEnfermedad->setText(pSleep);
}

void MainWindow::setlDesechosStatus(){
    pDesechos = "";
    for(int i = 0; i < actual->desechos.getTope()->valor; i++)
        pDesechos += "---------\n";

    ui->lDesechos->setText(pDesechos);
}

void MainWindow::setActivityLabelsStatus(){
    setlHambreStatus();
    setlSleepStatus();
    setlEnfermedadStatus();
    setlDesechosStatus();
}

void MainWindow::setCoinsLabels(){
    ui->lCoinsDonables->setText(QString("Donables: %1").arg(actual->giftCoins.size));
    ui->lCoinsPersonales->setText(QString("Personales: %1").arg(actual->myCoins.size));
}

void MainWindow::changeActivitiesStatus(){
    ui->bHambre->setEnabled(!ui->bHambre->isEnabled());
    ui->bSleep->setEnabled(!ui->bSleep->isEnabled());
    ui->bEnfermedad->setEnabled(!ui->bEnfermedad->isEnabled());
    ui->bDesechos->setEnabled(!ui->bDesechos->isEnabled());
}

void MainWindow::blockEverything(){
    bool isAlive = actual->getHp() > 0 ? true : false;

    ui->bHambre->setEnabled(isAlive);
    ui->bSleep->setEnabled(isAlive);
    ui->bEnfermedad->setEnabled(isAlive);
    ui->bDesechos->setEnabled(isAlive);

    ui->bDonar->setEnabled(isAlive);
}

void MainWindow::on_bCrear_clicked()
{
    string nombre = ui->tNombre->text().toStdString();
    ui->tNombre->clear();

    if(!searchFarm(nombre)){
        granja.push_back(new Tamagotchi(nombre, tipoToInt()));
        updateComboElegir();
    }
}

void MainWindow::on_bCambiar_clicked()
{
    string nombre = ui->cTamagotchis->currentText().toStdString();
    Tamagotchi* temp = searchFarm(nombre);

    if(temp){
        actual = temp;
        setActivityLabelsStatus();
        log = "";
        //Actualizar labels
        ui->pbHealth->setValue(actual->getHp());
        setCoinsLabels();
        blockEverything();
        ui->lLog->setText("");
        ui->lNewVictoria->setText("");
        cantidadLogs = 0;
        pressedActivity = false;
    }
}

void MainWindow::on_bHambre_clicked()
{
    if(!actual)
        return;

    if(actual->hambre.getTope()->valor > 0){
        actual->hambre.sacar();
        pressedActivity = true;
        changeActivitiesStatus();
    }

    setlHambreStatus();
}

void MainWindow::on_bSleep_clicked()
{
    if(!actual)
        return;    

    if(actual->sleep.getTope()->valor > 0){
        actual->sleep.sacar();
        pressedActivity = true;
        changeActivitiesStatus();
    }

    setlSleepStatus();
}

void MainWindow::on_bEnfermedad_clicked()
{
    if(!actual)
        return;

    if(actual->enfermedad.getTope()->valor > 0){
        actual->enfermedad.sacar();
        pressedActivity = true;
        changeActivitiesStatus();
    }

    setlEnfermedadStatus();
}

void MainWindow::on_bDesechos_clicked()
{
    if(!actual)
        return;

    if(actual->desechos.getTope()->valor > 0){
        actual->desechos.sacar();
        pressedActivity = true;
        changeActivitiesStatus();
    }

    setlDesechosStatus();
}

void MainWindow::on_bDonar_clicked()
{
    if(!actual)
        return;

    string nombre = ui->cTamagotchis->currentText().toStdString();

    if(nombre != actual->getNombre() && actual->giftCoins.size > 0){
        Tamagotchi* temp = searchFarm(nombre);
        temp->myCoins.agregar(actual->giftCoins.getFrente()->valor);
        actual->giftCoins.quitarDeCola();
        setCoinsLabels();
    }

}

void MainWindow::on_bUsar_clicked()
{
    if(!actual)
        return;

    if(actual->myCoins.getFrente()){
        int coin = actual->myCoins.getFrente()->valor;

        switch(coin){
            case 0://hambre
                actual->hambre.anular();
                actual->hambre.agregar(0);
                setlHambreStatus();
                break;
            case 1://sueño
                actual->sleep.anular();
                actual->sleep.agregar(0);
                setlSleepStatus();
                break;
            case 2://enfermedad
                actual->enfermedad.anular();
                actual->enfermedad.agregar(0);
                setlEnfermedadStatus();
                break;
            case 3://desechos
                actual->desechos.anular();
                actual->desechos.agregar(0);
                setlDesechosStatus();
                break;
        }

        actual->myCoins.quitarDeCola();
        setCoinsLabels();
    }
}

/*How to add images
 *
 QString imagePath = QFileDialog::getOpenFileName(
    this,
    tr("Open File"),
    "",
    tr("JPEG (*.jpg *.jpeg);;PNG (*.png)")
    );

    QString imagePath = "./Assets/Ghost/Ghost1.png";
    QDir d(imagePath);

    imagePath = d.relativeFilePath(imagePath);

    imageObject = new QImage();
    imageObject->load(imagePath);
    image = QPixmap::fromImage(*imageObject);
    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());
    ui->graphicsView->setScene(scene);
 */
