#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fireenemy.h"
#include <QPainter>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    nivel2 = nullptr;
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

//borrar cuando termines el nivel 1, es solo para probar nivel 2
    connect(
        ui->btnNivel2,
        &QPushButton::clicked,

        this,

        [=]()
        {
            juegoIniciado = true;

            // ocultar menu
            ui->label->hide();

            ui->btnJugar->hide();

            ui->btnNivel2->hide();

            ui->btnSalir->hide();

            ui->btnOpciones->hide();

            ui->btnCreditos->hide();

            // crear nivel 2
            nivel2 = new Nivel2();

            fondoActual = QPixmap(
                ":/img/Recursos/fondo_n2.png");

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
            {   // borrar cuando este liso el nivel 1
                if(nivel1 != nullptr)
                {
                // borrar cuando este liso el nivel 1
                    nivel1->actualizar(0.016f);
                }
                // borrar cuando este liso el nivel 1
                if(nivel2 != nullptr)
                {
                // borrar cuando este liso el nivel 1
                    nivel2->actualizar(0.016f);
                }
                /*nivel1->actualizar(0.016f);*/ //descomentar cuando el nivel 1 este listo, es solo para probar el nivel 2 sin pasar por el nivel 1

                // REDIBUJAR

                update();
            }
        });
}

MainWindow::~MainWindow()
{
    delete nivel1;

    delete ui;
    delete nivel2;
}

// DIBUJAR

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    // DIBUJAR FONDO

    if(nivel2 == nullptr)
    {
        painter.drawPixmap(
            rect(),
            fondoActual);
    }
    // DIBUJAR GAMEPLAY

    if(juegoIniciado)
    {
        if(nivel1 != nullptr)
        {
         //borrar cuando este listo el nivel 1
            nivel1->renderizar(&painter);
        }
        //borrar cuando este listo el nivel 1
        if(nivel2 != nullptr)
        {
        //borrar cuando este listo el nivel 1
            nivel2->renderizar(&painter);
        }
        /*nivel1->renderizar(&painter);*/ //descomentar cuando este listo el nivel 1
    }
}

// TECLADO

void MainWindow::keyPressEvent(QKeyEvent *event)
{    //borrar cuando este listo el nivel 1
    if(nivel1 != nullptr)
    {//borrar cuando este listo el nivel 1
        nivel1->manejarTeclaPresionada(event);
    }
    //borrar cuando este listo el nivel 1
    if(nivel2 != nullptr)
    {//borrar cuando este listo el nivel 1
        nivel2->manejarTeclaPresionada(event);
    }

    /*if(juegoIniciado)
    {
        nivel1->manejarTeclaPresionada(event);
    }*/
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{//borrar cuando este listo el nivel 1
    if(nivel1 != nullptr)
    {//borrar cuando este listo el nivel 1
        nivel1->manejarTeclaLiberada(event);
    }//borrar cuando este listo el nivel 1

    if(nivel2 != nullptr)
    {//borrar cuando este listo el nivel 1
        nivel2->manejarTeclaLiberada(event);
    }
    /*if(juegoIniciado)                     //descomentar cuando este listo el nivel 1
    {
        nivel1->manejarTeclaLiberada(event);
    }*/
}
