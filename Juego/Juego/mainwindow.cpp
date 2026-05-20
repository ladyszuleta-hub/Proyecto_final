#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Tamaño de la ventana
    setFixedSize(1366, 768);

    // Crear fondo
    QLabel *fondo = new QLabel(this);

    // Cargar imagen
    QPixmap imagen(":/img/Recursos/menuprinc.png");

    fondo->setPixmap(imagen);

    // Ajustar al tamaño de la ventana
    fondo->setScaledContents(true);

    // Posición y tamaño
    fondo->setGeometry(0, 0, width(), height());

    // Mandar detrás de todos los widgets
    fondo->lower();
}

MainWindow::~MainWindow()
{
    delete ui;
}
