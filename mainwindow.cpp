#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lHambre->setText("---------\n---------\n---------\n---------\n---------");
    ui->lSleep->setText("---------\n---------\n---------\n---------\n---------");
    ui->lEnfermedad->setText("---------\n---------\n---------\n---------\n---------");
    ui->lDesechos->setText("---------\n---------\n---------\n---------\n---------");
}

MainWindow::~MainWindow()
{   
    delete ui;
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
