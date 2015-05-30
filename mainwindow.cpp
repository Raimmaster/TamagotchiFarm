#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    //QStrings para las pilas
    pHambre = "";
    pSleep = "";
    pEnfermedad = "";
    pDesechos = "";

    //Log
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

void MainWindow::checkVictory(){
    if(!anyAtTop()){
        int coinType = rand() % 3;
        actual->giftCoins.agregar(coinType);
        ui->lCoinsDonables->setText(QString("Donables: %1").arg(actual->giftCoins.size));
    }
}

void MainWindow::checkLoss(){

}

void MainWindow::incrementCounter(){
    TIEMPO++;

    if(!actual)
        return;

    if(TIEMPO % CHECK_TIME == 0)
        checkStatus();

    if(TIEMPO % TIEMPO_VICTORIA == 0)
        checkVictory();

    if(TIEMPO % LOSE_TIME == 0)
        checkLoss();

    if(actual)
        cout<<"My HP: "<<actual->getHp()<<endl;
}

int MainWindow::tipoToInt(){
    char tipo = ui->cTipo->currentText().toStdString().at(0);
    cout<<tipo<<endl;
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
        //Actualizar labels
        ui->pbHealth->setValue(actual->getHp());
        ui->lCoinsPersonales->setText(QString("Personales: %1").arg(actual->giftCoins.size));
    }
}

void MainWindow::on_bHambre_clicked()
{
    if(!actual)
        return;

    if(actual->hambre.getTope()->valor > 0)
        actual->hambre.sacar();

    setlHambreStatus();
}

void MainWindow::on_bSleep_clicked()
{
    if(!actual)
        return;    

    if(actual->sleep.getTope()->valor > 0)
        actual->sleep.sacar();

    setlSleepStatus();
}

void MainWindow::on_bEnfermedad_clicked()
{
    if(!actual)
        return;

    if(actual->enfermedad.getTope()->valor > 0)
        actual->enfermedad.sacar();

    setlEnfermedadStatus();
}

void MainWindow::on_bDesechos_clicked()
{
    if(!actual)
        return;

    if(actual->desechos.getTope()->valor > 0)
        actual->desechos.sacar();

    setlDesechosStatus();
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
