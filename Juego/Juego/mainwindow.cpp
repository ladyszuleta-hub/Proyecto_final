#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    nivel2 = nullptr;
    ui->setupUi(this);
    nivel1 = nullptr;
    nivel2Desbloqueado = false;

    // CONFIGURACION INICIAL

    juegoIniciado = false;
    estadoMenu = MENU_PRINCIPAL;

    ui->btnnivel1->hide();
    ui->btnNivel2->hide();
    ui->btndificultad->hide();
    ui->btnFacil->hide();
    ui->btnNormal->hide();
    ui->btnDificil->hide();

    fondoMenuPrincipal = QPixmap(
        ":/img/Recursos/menuprinc.png");

    fondoMenuNiveles = QPixmap(
        ":/img/Recursos/submenu1.png");

    fondoMenuDificultad = QPixmap(
        ":/img/Recursos/submenudific.png");
    fondoGameOver = QPixmap(
        ":/img/Recursos/gameover.png");

    fondoActual = fondoMenuPrincipal;
    mostrandoVictoria = false;

    imagenVictoria = QPixmap(
        ":/img/Recursos/ganaste.png");

    timerVictoria = new QTimer(this);

    timerVictoria->setSingleShot(true);
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
            estadoMenu = MENU_NIVELES;

            fondoActual = fondoMenuNiveles;

            ui->btnJugar->hide();
            ui->btnSalir->hide();
            ui->btnCreditos->hide();
            ui->btnOpciones->hide();


            ui->btnnivel1->show();
            ui->btnNivel2->show();
            ui->btndificultad->show();
            update();
        });

    connect(
        ui->btndificultad,
        &QPushButton::clicked,

        this,

        [=]()
        {
            estadoMenu = MENU_DIFICULTAD;

            fondoActual = fondoMenuDificultad;
            ui->btnJugar->hide();
            ui->btnSalir->hide();
            ui->btnCreditos->hide();
            ui->btnOpciones->hide();

            ui->btnnivel1->hide();
            ui->btnNivel2->hide();
            ui->btndificultad->hide();

            ui->btnFacil->show();
            ui->btnNormal->show();
            ui->btnDificil->show();

            update();
        });
    connect(
        ui->btnnivel1,
        &QPushButton::clicked,

        this,

        [=]()
        {
            juegoIniciado = true;

            estadoMenu = JUGANDO;

            // ocultar botones de menú

            ui->btnnivel1->hide();
            ui->btnNivel2->hide();
            ui->btndificultad->hide();

            ui->btnFacil->hide();
            ui->btnNormal->hide();
            ui->btnDificil->hide();

            // crear nivel 1
            if(nivel1 == nullptr)
            {
                nivel1 = new Nivel1();
            }
            // fondo del nivel

            fondoActual = QPixmap(
                ":/img/Recursos/fondo_n1.png");

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
            //ui->label->hide();

            ui->btnJugar->hide();

            ui->btnNivel2->hide();
            ui->btnnivel1->hide();
            ui->btndificultad->hide();

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
    connect(
        timerVictoria,
        &QTimer::timeout,

        this,

        [=]()
        {
            mostrandoVictoria = false;

            volverMenuNiveles();
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
                    if(nivel1->nivelCompletado())
                    {
                        nivel2Desbloqueado = true;
                        mostrandoVictoria = true;

                        timer->stop();
                        timerVictoria->start(3000);
                        update();
                    }

                }
                if(nivel1 != nullptr &&nivel1->juegoTerminado()){
                    mostrarGameOver();
                }
                // borrar cuando este liso el nivel 1
                if(nivel2 != nullptr)
                {
                // borrar cuando este liso el nivel 1
                    nivel2->actualizar(0.016f);
                }
                if(nivel2 != nullptr && nivel2->juegoTerminado()){
                    mostrarGameOver();
                }
                /*nivel1->actualizar(0.016f);*/ //descomentar cuando el nivel 1 este listo, es solo para probar el nivel 2 sin pasar por el nivel 1

                update();
            }
        });
}
void MainWindow::mostrarGameOver()
{
    estadoMenu = GAME_OVER;

    juegoIniciado = false;

    fondoActual = fondoGameOver;

    update();

    QTimer::singleShot(
        3000,
        this,
        &MainWindow::volverMenuPrincipal);
}
void MainWindow::volverMenuPrincipal()
{
    delete nivel1;
    nivel1 = nullptr;

    delete nivel2;
    nivel2 = nullptr;

    juegoIniciado = false;

    estadoMenu = MENU_PRINCIPAL;

    fondoActual = fondoMenuPrincipal;

    ui->btnJugar->show();
    ui->btnSalir->show();
    ui->btnOpciones->show();
    ui->btnCreditos->show();

    ui->btnnivel1->hide();
    ui->btnNivel2->hide();
    ui->btndificultad->hide();

    ui->btnFacil->hide();
    ui->btnNormal->hide();
    ui->btnDificil->hide();

    update();
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

    if(estadoMenu == GAME_OVER)
    {
        painter.drawPixmap(
            rect(),
            fondoGameOver);

        return;
    }

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
    if(mostrandoVictoria)
    {
        painter.drawPixmap(
            rect(),
            imagenVictoria);
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
void MainWindow::volverMenuNiveles()
{
    delete nivel1;
    nivel1 = nullptr;

    delete nivel2;
    nivel2 = nullptr;

    juegoIniciado = false;

    estadoMenu = MENU_NIVELES;

    fondoActual = fondoMenuNiveles;

    ui->btnnivel1->show();

    ui->btndificultad->show();

    if(nivel2Desbloqueado)
    {
        ui->btnNivel2->show();
    }

    update();
}
