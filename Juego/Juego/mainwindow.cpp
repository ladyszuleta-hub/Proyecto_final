#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fireenemy.h"
#include <QPainter>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nivel1 = nullptr;

    // CONFIGURACION INICIAL

    juegoIniciado = false;

    fondoActual = QPixmap(
        ":/img/Recursos/menuprinc.png");

    setFixedSize(1366,768);


    // TIMER

    timer = new QTimer(this);

    // BOTON JUGAR

    connect(
        ui->btnJugar,
        &QPushButton::clicked,

        this,

        [=]()
        {
            // INICIAR JUEGO

            juegoIniciado = true;

            // OCULTAR MENU
            ui->label->hide();

            ui->btnJugar->hide();

            ui->btnSalir->hide();

            ui->btnOpciones->hide();

            ui->btnCreditos->hide();

            // CAMBIAR FONDO

            fondoActual = QPixmap(
                ":/img/Recursos/fondo_n1.png");


            nivel1 = new Nivel1();

            // INICIAR TIMER

            timer->start(16);

            update();
        });

    // BOTON SALIR

    connect(
        ui->btnSalir,
        &QPushButton::clicked,

        this,

        [=]()
        {
            close();
        });

    // BOTON CREDITOS

    connect(
        ui->btnCreditos,
        &QPushButton::clicked,

        this,

        [=]()
        {
            QMessageBox::information(

                this,

                "Creditos",

                "Juego creado por Davie\n\n"
                "Proyecto en Qt Creator"
                );
        });

    // BOTON OPCIONES

    connect(
        ui->btnOpciones,
        &QPushButton::clicked,

        this,

        [=]()
        {
            QMessageBox::information(

                this,

                "Opciones",

                "Aqui iran las opciones del juego"
                );
        });

    // GAME LOOP

    connect(
        timer,
        &QTimer::timeout,

        this,

        [=]()
        {
            if(juegoIniciado)
            {
                nivel1->actualizar(0.016f);

                // REDIBUJAR

                update();
            }
        });
}

MainWindow::~MainWindow()
{
    delete nivel1;

    delete ui;
}

// DIBUJAR

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    // DIBUJAR FONDO

    painter.drawPixmap(
        rect(),
        fondoActual);

    // DIBUJAR GAMEPLAY

    if(juegoIniciado)
    {
        nivel1->renderizar(&painter);
    }
}

// TECLADO

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(juegoIniciado)
    {
        nivel1->manejarTeclaPresionada(event);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(juegoIniciado)
    {
        nivel1->manejarTeclaLiberada(event);
    }
}
