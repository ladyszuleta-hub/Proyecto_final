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

            // CREAR JUGADOR

            jugador = new SnowMan(

                300,
                100,

                40,
                48,

                new GravityPhysics(
                    500.0f,
                    650.0f
                    ),

                3
                );

            // LIMITES

            jugador->setLimites(
                QRectF(
                    0,
                    0,
                    width(),
                    height()
                    ));

            // CREAR ENEMIGO

            enemigo = new FireEnemy(

                900,
                150,

                36,
                36,

                new FrictionPhysics(
                    0.01f
                    )
                );

            enemigo->setTarget(jugador);

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
                // ACTUALIZAR JUGADOR

                jugador->actualizar(0.016f);

                // ACTUALIZAR ENEMIGO

                enemigo->actualizar(0.016f);

                // REDIBUJAR

                update();
            }
        });
}

MainWindow::~MainWindow()
{
    delete jugador;

    delete enemigo;

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
        jugador->renderizar(&painter);

        enemigo->renderizar(&painter);

        // HUD

        painter.setPen(Qt::white);

        painter.setFont(
            QFont(
                "Arial",
                16,
                QFont::Bold
                ));

        painter.drawText(
            20,
            40,
            "VIDAS: "
                + QString::number(
                    jugador->getVidas()
                    ));

        painter.drawText(
            20,
            70,
            "PUNTAJE: "
                + QString::number(
                    jugador->getPuntaje()
                    ));
    }
}

// TECLADO

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(juegoIniciado)
    {
        jugador->manejarTeclaPresionada(
            static_cast<Qt::Key>(
                event->key()
                ));
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(juegoIniciado)
    {
        jugador->manejarTeclaLiberada(
            static_cast<Qt::Key>(
                event->key()
                ));
    }
}
