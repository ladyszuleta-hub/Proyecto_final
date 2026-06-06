#include "nivel2.h"
#include <QKeyEvent>
#include <QBrush>
#include <QPen>
#include <cmath>
#include <QMessageBox>
Nivel2::Nivel2()
{
    completado = false;

    camaraX = 0;

    tiempoOscilacion = 0;

    dificultadDificil = false;
    generarVidas();

    fondoNivel.load(
        ":/img/Recursos/fondo_n2.png");

    crearNivel();
}


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


void Nivel2::crearNivel()
{

    jugador = new SnowMan(
        100,
        500,
        70,
        70,

        new GravityPhysics(
            980,
            5000),

        3);

    jugador->setVelocidadAuto(0);


    jugador->setNivelActual(2);

    jugador->setLimites(
        QRectF(0,0,8000,2000));


    FireEnemy* enemigo1 =
        new FireEnemy(40,400,48,48,

            new FrictionPhysics(0.03f));

    enemigo1->setTarget(jugador);

    enemigos.push_back(enemigo1);


    plataformas.push_back(
        new obstaculo(
            0,
            650,
            1200,
            50,
            "suelo"));



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

    plataformas.push_back(
        new obstaculo(
            5000,
            450,
            250,
            40,
            "plataforma"));

    plataformas.push_back(
        new obstaculo(
            5700,
            320,
            250,
            40,
            "plataforma"));

    plataformas.push_back(
        new obstaculo(
            6500,
            500,
            250,
            40,
            "plataforma"));

    plataformas.push_back(
        new obstaculo(
            7300,
            350,
            250,
            40,
            "plataforma"));


    portal = new ZonaSegura(
        7700,
        240,
        100,
        120,
        0,":/img/Recursos/portalN2.png");

}
void Nivel2::generarVidas()
{
    vidasExtra.push_back(
        new premio(1700,250,"vida",0));

    vidasExtra.push_back(
        new premio(5900,290,"vida",0));
}

void Nivel2::actualizar(float dt)
{



    if(completado)
        return;

    jugador->actualizar(dt);
    if(dificultadDificil)
    {
        tiempoOscilacion += dt;

        plataformas[4]->setPosicion(plataformas[4]->getPosicion().getX(),
            500 + 50 * sin(tiempoOscilacion + (4)));
        plataformas[6]->setPosicion(plataformas[6]->getPosicion().getX(),
                                    250 + 50 * sin(tiempoOscilacion + (6)));
        plataformas[8]->setPosicion(plataformas[8]->getPosicion().getX(),
                                    320 + 50 * sin(tiempoOscilacion + (8)));
    }
    float nuevaY =
        320 + 80 *
                  std::sin(tiempoOscilacion * 2.0f);

    plataformas[3]->setPosicion(
        2200,
        nuevaY);

    // CAMARA

    // CAMARA

    camaraX =
        jugador->getPosicion().getX()
        - 400;

    if(camaraX < 0)
    {
        camaraX = 0;
    }

    if(camaraX > 7000)
    {
        camaraX = 7000;
    }

    // ENEMIGOS

    for(auto*
             enemigo : enemigos)
    {
        enemigo->actualizar(dt);
    }

    verificarColisiones();

    actualizarPortal();

    // CAER AL VACIO


    if(jugador->getPosicion().getY() > 900)
    {
        jugador->recibirDanio(1);

        jugador->setPosicion(100,500);

        jugador->setVelocity(
            Vector2D(0,0));
    }


    // GANAR

    if(portal->estaDesbloqueada())
    {
        if(jugador->colisionaCon(*portal))
        {
            completado = true;
        }
    }
}

void Nivel2::verificarColisiones()
{
    // PREMIOS

    for(auto* pr : premios)
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

    for(auto* enemigo : enemigos)
    {
        if(enemigo->estaActivo())
        {
            if(jugador->colisionaCon(*enemigo))
            {
                jugador->recibirDanio(1);
            }
        }
    }
    //vida
    for(auto* vida : vidasExtra)
    {
        if(vida->estaActivo() && jugador->colisionaCon(*vida))
        {
            jugador->setVidas(jugador->getVidas()+1);

            vida->setActivo(false);
        }
    }
    for(auto* plataforma : plataformas)
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

void Nivel2::renderizar(QPainter *painter)
{

    // FONDO
    for(int x = 0; x < 8000; x += fondoNivel.width())
    {
        painter->drawPixmap(
            x - camaraX,
            0,
            fondoNivel);
    }

    // PLATAFORMAS

    for(auto* plataforma : plataformas)
    {
        painter->save();

        painter->translate(-camaraX,0);

        plataforma->renderizar(painter);

        painter->restore();
    }

    // ENEMIGOS

    for(auto* enemigo : enemigos)
    {
        painter->save();

        painter->translate(-camaraX,0);

        enemigo->renderizar(painter);

        painter->restore();
    }
    //vida
    for(auto* vida : vidasExtra)
    {
        if(vida->estaActivo())
        {
            painter->save();

            painter->translate(-camaraX,0);

            vida->renderizar(painter);

            painter->restore();
        }
    }

    // JUGADOR

    painter->save();

    painter->translate(-camaraX,0);

    jugador->renderizar(painter);

    painter->restore();

    // PORTAL FINAL

    painter->save();

    painter->translate(-camaraX,0);

    portal->renderizar(painter);

    painter->restore();


    painter->setPen(Qt::white);

    painter->setFont(
        QFont("Arial",20,QFont::Bold));

    painter->drawText(
        20,
        40,
        "Vidas: " +
            QString::number(
                jugador->getVidas()));

    painter->drawText(
        20,
        80,
        "Puntos: " +
            QString::number(
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
bool Nivel2::juegoTerminado() const
{
    return jugador->getVidas() <= 0;
}
bool Nivel2::nivelCompletado() const
{
    return completado;
}
void Nivel2::setVelocidadEnemigo(float velocidad)
{
    for(auto* enemigo : enemigos)
    {
        enemigo->setVelocidad(velocidad);
    }

    // Dificil = más enemigos
    if(velocidad >= 360)
    {
        FireEnemy* enemigo2 =
            new FireEnemy(
                2500,
                250,
                48,
                48,
                new FrictionPhysics(0.03f));

        enemigo2->setTarget(jugador);
        enemigo2->setVelocidad(velocidad);

        enemigos.push_back(enemigo2);

        FireEnemy* enemigo3 =
            new FireEnemy(
                5000,
                250,
                48,
                48,
                new FrictionPhysics(0.03f));

        enemigo3->setTarget(jugador);
        enemigo3->setVelocidad(velocidad);

        enemigos.push_back(enemigo3);
    }
}
void Nivel2::setDificultadDificil(bool estado)
{
    dificultadDificil = estado;
}
