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
    velocidadEnemigo = 180;
    estadoMenu = MENU_PRINCIPAL;

    ui->btnnivel1->hide();
    ui->btnNivel2->hide();
    ui->btnsalirju->hide();
    ui->btnFacil->hide();
    ui->btnNormal->hide();
    ui->btnDificil->hide();

    fondoMenuPrincipal = QPixmap(":/img/Recursos/menuprinc.png");

    fondoMenuNiveles = QPixmap(":/img/Recursos/submenu1.png");

    fondoMenuDificultad = QPixmap(":/img/Recursos/submenudific.png");
    fondoGameOver = QPixmap(":/img/Recursos/gameover.png");

    fondoActual = fondoMenuPrincipal;
    mostrandoHistoria = false;

    imagenHistoria = QPixmap(":/img/Recursos/ganaste.png");

    timerVictoria = new QTimer(this);

    timerVictoria->setSingleShot(true);
    setFixedSize(1366,768);
    //audio
    audio = new QAudioOutput(this);
    musica = new QMediaPlayer(this);
    musica->setAudioOutput(audio);
    audio->setVolume(0.4);
    musica->setSource(QUrl("qrc:/Recursos/menuprincipal.mp3"));

    musica->play();
    ui->btnMusica->setIcon(QIcon(":/img/Recursos/musica.png"));

    ui->btnMusica->setIconSize(QSize(80,80));
    ui->btnMusica->setFocusPolicy(Qt::NoFocus);


    // TIMER

    timer = new QTimer(this);

    //musica
    connect(
        ui->btnMusica,
        &QPushButton::clicked,

        this,
        [=]()
    {
            if(musica->playbackState() == QMediaPlayer::PlayingState)
            {
                musica->stop();
            }
            else
            {
                musica->play();
            }
        });

    // BOTON JUGAR
    connect(
        ui->btnJugar,
        &QPushButton::clicked,

        this,

        [=]()
        {
            mostrarMenuNiveles();
            update();
        });
    connect(
        ui->btnsalirju,
        &QPushButton::clicked,

        this,

        [=]()
        {
            volverMenuPrincipal();
            update();
        });
    connect(
        ui->btndificultad,
        &QPushButton::clicked,

        this,

        [=]()
        {
            mostrarMenuDificultad();
            update();
        });
    connect(
        ui->btnnivel1,
        &QPushButton::clicked,

        this,

        [=]()
        {
            mostrarHistoriaInicioNivel1();
        });

    connect(
        ui->btnNivel2,
        &QPushButton::clicked,

        this,

        [=]()
        {
            musica->stop();
            musica->setSource(
                QUrl("qrc:/Recursos/nivell2.mp3"));

            musica->play();
            setFocus();
            juegoIniciado = true;
            ocultarTodosLosBotones();

            // crear nivel 2
            nivel2 = new Nivel2();

            nivel2->setVelocidadEnemigo(
                velocidadEnemigo);

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

                "Juego creado por Davielys y Ladys \n\n"
                "Proyecto en Qt Creator\n\n"
                "Imagenes generadas con IA"
                );
        });

    connect(
        timerVictoria,
        &QTimer::timeout,

        this,

        [=]()
        {
            mostrandoHistoria = false;

            volverMenuNiveles();
        });
    connect(
        musica,
        &QMediaPlayer::mediaStatusChanged,
        this,
        [=](QMediaPlayer::MediaStatus status)
        {
            if(status ==
                QMediaPlayer::EndOfMedia)
            {
                musica->setPosition(0);
                musica->play();
            }
        });
    // GAME LOOP

    connect(
        timer,
        &QTimer::timeout,

        this,

        [=]()
        {
            gameloop();

        });
    connect(ui->btnFacil,
            &QPushButton::clicked,
            this,
            [=]()
            {
                velocidadEnemigo=100;
                volverMenuPrincipal();
            });
    connect(ui->btnNormal,
            &QPushButton::clicked,
            this,
            [=]()
            {
                velocidadEnemigo=180;
                volverMenuPrincipal();
            });
    connect(ui->btnDificil,
            &QPushButton::clicked,
            this,
            [=]()
            {
                velocidadEnemigo=360;
                volverMenuPrincipal();
            });
}

void MainWindow::gameloop(){
if(juegoIniciado)
    {
        if(nivel1 != nullptr)
        {
            nivel1->actualizar(0.016f);
            if(nivel1->nivelCompletado())
            {
                imagenHistoria.load(":/img/Recursos/ganaste.png");
                mostrandoHistoria = true;

                timer->stop();
                timerVictoria->start(3000);
                update();
            }

        }
        if(nivel1 != nullptr &&nivel1->juegoTerminado()){
            mostrarGameOver();
        }
        if(nivel2 != nullptr)
        {
            nivel2->actualizar(0.016f);

            if(nivel2->nivelCompletado())
            {
                mostrarHistoriaFinal();
                /*imagenHistoria.load(":/img/Recursos/ganaste.png");
                mostrandoHistoria = true;

                timer->stop();

                timerVictoria->start(3000);

                update();*/
            }
        }
        if(nivel2 != nullptr && nivel2->juegoTerminado()){
            mostrarGameOver();
        }
        update();
}
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
    mostrarMenuPrincipal();
    musica->stop();

    musica->setSource(
        QUrl("qrc:/Recursos/menuprincipal.mp3"));

    musica->play();
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
            nivel1->renderizar(&painter);
        }
        if(nivel2 != nullptr)
        {
            nivel2->renderizar(&painter);
        }
    }
    if(mostrandoHistoria)
    {
        painter.drawPixmap(
            rect(),
            imagenHistoria);
    }
}

// TECLADO

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(nivel1 != nullptr)
    {
        nivel1->manejarTeclaPresionada(event);
    }
    if(nivel2 != nullptr)
    {
        nivel2->manejarTeclaPresionada(event);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(nivel1 != nullptr)
    {
        nivel1->manejarTeclaLiberada(event);
    }

    if(nivel2 != nullptr)
    {
        nivel2->manejarTeclaLiberada(event);
    }
}

void MainWindow::volverMenuNiveles()
{
    delete nivel1;
    nivel1 = nullptr;

    delete nivel2;
    nivel2 = nullptr;

    juegoIniciado = false;
    mostrarMenuNiveles();

    update();
}
void MainWindow::ocultarTodosLosBotones()
{
    ui->btnJugar->hide();
    ui->btnSalir->hide();
    ui->btnCreditos->hide();

    ui->btnnivel1->hide();
    ui->btnNivel2->hide();

    ui->btnFacil->hide();
    ui->btnNormal->hide();
    ui->btnDificil->hide();

    ui->btnsalirju->hide();
    ui->btndificultad->hide();
}
void MainWindow::mostrarMenuPrincipal()
{
    ocultarTodosLosBotones();

    ui->btnJugar->show();
    ui->btnSalir->show();
    ui->btnCreditos->show();
    ui->btndificultad->show();

    estadoMenu = MENU_PRINCIPAL;
    fondoActual = fondoMenuPrincipal;
}
void MainWindow::mostrarMenuNiveles()
{
    ocultarTodosLosBotones();

    ui->btnnivel1->show();
    ui->btnsalirju->show();
    ui->btnNivel2->show();
    estadoMenu = MENU_NIVELES;
    fondoActual = fondoMenuNiveles;
}
void MainWindow::mostrarMenuDificultad()
{
    ocultarTodosLosBotones();

    ui->btnFacil->show();
    ui->btnNormal->show();
    ui->btnDificil->show();

    estadoMenu = MENU_DIFICULTAD;
    fondoActual = fondoMenuDificultad;
}

void MainWindow::mostrarHistoriaInicioNivel1()
{

    imagenHistoria.load(
        ":/img/Recursos/historian1.png");

    mostrandoHistoria = true;

    update();
    ocultarTodosLosBotones();
    QTimer::singleShot(
        5000,
        this,
        [=]()
        {
            mostrandoHistoria = false;

            iniciarNivel1();

            update();
        });
}
void MainWindow::iniciarNivel1()
{
    musica->stop();

    musica->setSource(QUrl("qrc:/Recursos/nivel1.mp3"));

    musica->play();
    setFocus();

    juegoIniciado = true;

    estadoMenu = JUGANDO;
    ocultarTodosLosBotones();

    // crear nivel 1
    if(nivel1 == nullptr)
    {
        nivel1 = new Nivel1();
        nivel1->setVelocidadEnemigo(velocidadEnemigo);
    }
    // fondo del nivel

    fondoActual = QPixmap(
        ":/img/Recursos/fondo_n1.png");

    timer->start(16);


    update();

}
void MainWindow::mostrarHistoriaFinal()
{
    imagenHistoria.load(":/img/Recursos/historian2.png");

    mostrandoHistoria = true;

    update();

    QTimer::singleShot(
        4000,
        this,
        [=]()
        {
            mostrandoHistoria = false;

            imagenHistoria.load(":/img/Recursos/ganaste.png");

            mostrandoHistoria = true;

            update();
            timer->stop();

            timerVictoria->start(1000);

        });
}
