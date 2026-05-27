#include "nivel2.h"
#include <QKeyEvent>
#include <QBrush>
#include <QPen>

// ======================================================
// CONSTRUCTOR
// ======================================================

Nivel2::Nivel2()
{
    completado = false;

    camaraX = 0;

    fondoNivel.load(
        ":/img/Recursos/fondo_n2_largo.png");

    crearNivel();
}

// ======================================================
// DESTRUCTOR
// ======================================================

Nivel2::~Nivel2()
{
    fondoNivel.load(
        ":/img/Recursos/fondo_n2.png");
    delete jugador;

    delete portal;

    for(auto e : enemigos)
    {
        delete e;
    }

    for(auto p : plataformas)
    {
        delete p;
    }

    for(auto pr : premios)
    {
        delete pr;
    }
}

// ======================================================
// CREAR NIVEL
// ======================================================

void Nivel2::crearNivel()
{
    // ==================================================
    // JUGADOR
    // ==================================================

    jugador = new SnowMan(
        100,
        500,
        70,
        70,

        new GravityPhysics(
            980,
            600),

        3);

    jugador->setVelocidadAuto(0);

    jugador->setNivelActual(2);

    jugador->setLimites(
        QRectF(0,0,5000,768));

    // ==================================================
    // ENEMIGOS
    // ==================================================

    FireEnemy* enemigo1 =
        new FireEnemy(
            1400,
            560,
            48,
            48,

            new FrictionPhysics(0.03f));

    enemigo1->setTarget(jugador);

    enemigos.push_back(enemigo1);

    FireEnemy* enemigo2 =
        new FireEnemy(
            2800,
            520,
            48,
            48,

            new FrictionPhysics(0.03f));

    enemigo2->setTarget(jugador);

    enemigos.push_back(enemigo2);

    FireEnemy* enemigo3 =
        new FireEnemy(
            4000,
            380,
            48,
            48,

            new FrictionPhysics(0.03f));

    enemigo3->setTarget(jugador);

    enemigos.push_back(enemigo3);

    // ==================================================
    // PLATAFORMAS
    // ==================================================

    plataformas.push_back(
        new obstaculo(
            0,
            650,
            800,
            50,
            "suelo"));

    plataformas.push_back(
        new obstaculo(
            900,
            600,
            300,
            40,
            "plataforma"));

    plataformas.push_back(
        new obstaculo(
            1400,
            520,
            300,
            40,
            "plataforma"));

    plataformas.push_back(
        new obstaculo(
            1900,
            450,
            300,
            40,
            "plataforma"));

    plataformas.push_back(
        new obstaculo(
            2500,
            600,
            500,
            40,
            "plataforma"));

    plataformas.push_back(
        new obstaculo(
            3300,
            500,
            400,
            40,
            "plataforma"));

    plataformas.push_back(
        new obstaculo(
            4200,
            420,
            500,
            40,
            "plataforma"));

    // ==================================================
    // PREMIOS
    // ==================================================

    premios.push_back(
        new premio(
            1000,
            540,
            100));

    premios.push_back(
        new premio(
            1600,
            460,
            100));

    premios.push_back(
        new premio(
            2700,
            540,
            100));

    premios.push_back(
        new premio(
            4300,
            360,
            100));

    // ==================================================
    // PORTAL
    // ==================================================

    portal = new ZonaSegura(
        4700,
        300,
        100,
        120,
        300);
}

// ======================================================
// UPDATE
// ======================================================

void Nivel2::actualizar(float dt)
{
    if(completado)
        return;

    jugador->actualizar(dt);

    // CAMARA

    camaraX =
        jugador->getPosicion().getX()
        - 300;

    if(camaraX < 0)
    {
        camaraX = 0;
    }

    // ENEMIGOS

    for(auto enemigo : enemigos)
    {
        enemigo->actualizar(dt);
    }

    verificarColisiones();

    actualizarPortal();

    // GANAR

    if(portal->estaDesbloqueada())
    {
        if(jugador->colisionaCon(*portal))
        {
            completado = true;
        }
    }
}

// ======================================================
// COLISIONES
// ======================================================

void Nivel2::verificarColisiones()
{
    // PREMIOS

    for(auto pr : premios)
    {
        if(pr->estaActivo())
        {
            if(jugador->colisionaCon(*pr))
            {
                jugador->recogerDiamante(
                    pr->getPuntos());

                pr->setActivo(false);
            }
        }
    }

    // ENEMIGOS

    for(auto enemigo : enemigos)
    {
        if(enemigo->estaActivo())
        {
            if(jugador->colisionaCon(*enemigo))
            {
                jugador->recibirDanio(1);
            }
        }
    }
}

// ======================================================
// PORTAL
// ======================================================

void Nivel2::actualizarPortal()
{
    portal->actualizarEstado(
        jugador->getPuntaje());
}

// ======================================================
// RENDER
// ======================================================

void Nivel2::renderizar(QPainter* painter)
{
    painter->drawPixmap(
        QRectF(0,0,1366,768),

        fondoNivel,

        QRectF(
            camaraX * 0.3f,
            0,
            1366,
            768));
    // FONDO

    painter->drawPixmap(QRectF(0,0,1366,768),fondoNivel,

        QRect(
            camaraX,
            0,
            1366,
            768));

    // LAVA

    painter->setBrush(
        QColor(255,80,0));

    painter->setPen(Qt::NoPen);

    painter->drawRect(
        QRectF(
            0,
            680,
            1366,
            88));

    // PLATAFORMAS

    painter->setBrush(
        QColor(80,80,80));

    for(auto p : plataformas)
    {
        painter->drawRect(
            QRectF(p->getPosicion().getX()- camaraX,

                p->getPosicion().getY(),

                200,

                40));
    }

    // PREMIOS

    for(auto pr : premios)
    {
        if(pr->estaActivo()){
            painter->setBrush(QColor(0,255,255));

            painter->drawEllipse(QRectF(pr->getPosicion().getX()- camaraX,

                    pr->getPosicion().getY(),

                    30,

                    30));
        }
    }

    // PORTAL

    if(portal->estaDesbloqueada())
    {
        painter->setBrush(
            QColor(100,255,100));
    }
    else
    {
        painter->setBrush(
            QColor(120,120,120));
    }

    painter->drawRect(
        QRectF(
            portal->getPosicion().getX()
                - camaraX,

            portal->getPosicion().getY(),

            100,

            120));

    // ENEMIGOS

    for(auto enemigo : enemigos)
    {
        enemigo->renderizar(painter,camaraX);
    }

    // JUGADOR

    jugador->renderizar(
        painter,
        camaraX);

    // HUD

    painter->setPen(Qt::white);

    painter->drawText(
        20,
        40,

        "VIDAS: "
            + QString::number(
                jugador->getVidas()));

    painter->drawText(
        20,
        80,

        "PUNTAJE: "
            + QString::number(
                jugador->getPuntaje()));
}
void Nivel2::manejarTeclaPresionada(
    QKeyEvent* event)
{
    jugador->manejarTeclaPresionada(
        static_cast<Qt::Key>(event->key()));
}

void Nivel2::manejarTeclaLiberada(
    QKeyEvent* event)
{
    jugador->manejarTeclaLiberada(
        static_cast<Qt::Key>(event->key()));
}
