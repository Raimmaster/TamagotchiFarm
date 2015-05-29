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
    unsigned int randomPila = rand() % 4 + 1;

    switch(randomPila){
        case 1:
            actual->hambre.agregar(actual->hambre.getTope()->valor + 1);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
    }
}

void MainWindow::incrementCounter(){
    TIEMPO++;
    cout<<"Tiempo: "<<TIEMPO<<endl;


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
    cout<<"TIEMPO ACTUAL: "<<TIEMPO<<endl;
    Tamagotchi* temp = searchFarm(nombre);

    if(temp){
        actual = temp;
        cout<<actual->getNombre()<< " HP: "<<actual->getHp()<<endl;
    }
}
