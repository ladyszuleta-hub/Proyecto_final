#include "nivel2.h"
#include <QKeyEvent>
#include <QBrush>
#include <QPen>
#include <QMessageBox>
// ======================================================
// CONSTRUCTOR
// ======================================================

Nivel2::Nivel2()
{
    completado = false;

    camaraX = 0;

    fondoNivel.load(
        ":/img/Recursos/fondo_n22.png");

    crearNivel();
}

// ======================================================
// DESTRUCTOR
// ======================================================

Nivel2::~Nivel2()
{
    fondoNivel.load( ":/img/Recursos/fondo_n2.png");
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
    // ENEMIGO
    // ==================================================

    FireEnemy* enemigo1 =
        new FireEnemy(
            2500,
            240,
            48,
            48,

            new FrictionPhysics(0.03f),
            nullptr);

    enemigo1->setTarget(jugador);

    enemigos.push_back(enemigo1);

    // ==================================================
    // SUELO PRINCIPAL
    // ==================================================

    plataformas.push_back(
        new obstaculo(
            0,
            650,
            1200,
            50,
            "suelo"));

    // ==================================================
    // PLATAFORMAS
    // ==================================================

    plataformas.push_back(
        new obstaculo(
            900,
            520,
            250,
            40,
            "plataforma"));

    plataformas.push_back(
        new obstaculo(
            1500,
            420,
            250,
            40,
            "plataforma"));

    plataformas.push_back(
        new obstaculo(
            2200,
            320,
            250,
            40,
            "plataforma"));

    plataformas.push_back(
        new obstaculo(
            3000,
            500,
            250,
            40,
            "plataforma"));

    plataformas.push_back(
        new obstaculo(
            3600,
            380,
            250,
            40,
            "plataforma"));

    plataformas.push_back(
        new obstaculo(
            4300,
            250,
            250,
            40,
            "plataforma"));

    // ==================================================
    // PORTAL FINAL
    // ==================================================

    portal = new ZonaSegura(
        4700,
        140,
        100,
        120,
        0);
}
    // ==================================================
    // PREMIOS
    // ==================================================
/*
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
*/
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

    // ======================================
    // CAER AL VACIO
    // ======================================

    if(jugador->getPosicion().getY() > 900)
    {
        jugador->recibirDanio(1);

        // volver al inicio

        jugador->setPosicion(100,500);

        Vector2D vel(0,0);

        jugador->setVelocity(vel);
    }

    // GANAR

    if(portal->estaDesbloqueada())
    {
        if(jugador->colisionaCon(*portal))
        {
            completado = true;
        }
    }
    if(jugador->getPosicion().getX() >= 3200)
    {
        completado = true;

        QMessageBox::information(
            nullptr,
            "GANASTE",
            "Nivel completado");
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
    for(auto plataforma : plataformas)
    {
        if(jugador->colisionaCon(*plataforma))
        {
            // SOLO si viene cayendo

            if(jugador->getVelocity().getY() > 0)
            {
                jugador->setPosicion(
                    jugador->getPosicion().getX(),

                    plataforma->getPosicion().getY()
                        - 70);

                Vector2D vel =
                    jugador->getVelocity();

                vel.setY(0);

                jugador->setVelocity(vel);

                GravityPhysics* gp =
                    dynamic_cast<GravityPhysics*>(
                        jugador->getPhysics());

                if(gp != nullptr)
                {
                    gp->setGrounded(true);
                }


            }

        }

    }
}


void Nivel2::actualizarPortal()
{
    portal->actualizarEstado(
        jugador->getPuntaje());
}

// ======================================================
// RENDER
// ======================================================

void Nivel2::renderizar(QPainter *painter)
{
    // =========================================
    // CAMARA
    // =========================================

    camaraX = jugador->getPosicion().getX() - 400;

    if(camaraX < 0)
        camaraX = 0;

    // limite final del mapa
    if(camaraX > 2500)
        camaraX = 2500;

    // =========================================
    // FONDO
    // =========================================

    painter->drawPixmap(
        QRect(0,0,1366,768),
        fondoNivel,
        QRect(camaraX,0,1366,768));

    // =========================================
    // PLATAFORMAS
    // =========================================

    for(auto plataforma : plataformas)
    {
        painter->save();

        painter->translate(-camaraX,0);

        plataforma->renderizar(painter);

        painter->restore();
    }

    // =========================================
    // ENEMIGOS
    // =========================================

    for(auto enemigo : enemigos)
    {
        painter->save();

        painter->translate(-camaraX,0);

        enemigo->renderizar(painter);

        painter->restore();
    }

    // =========================================
    // JUGADOR
    // =========================================

    painter->save();

    painter->translate(-camaraX,0);

    jugador->renderizar(painter);

    painter->restore();

    // =========================================
    // PORTAL FINAL
    // =========================================

    painter->save();

    painter->translate(-camaraX,0);

    portal->renderizar(painter);

    painter->restore();
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
