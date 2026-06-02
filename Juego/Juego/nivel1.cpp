#include "nivel1.h"
#include <cstdlib>

Nivel1::Nivel1()
{
    enemigo = new FireEnemy(500,500,48,48,new FrictionPhysics(0.02f));
    limitesMapa =QRectF(55,40,1265,665);

    puntosMinimos = 820;
    completado = false;

    jugador = new SnowMan(120,120,64,64,new FrictionPhysics(0.01));

    jugador->setLimites(limitesMapa);
    enemigo->setTarget(jugador);

    crearObstaculos();

    generarPremios();

    generarVidas();

    portal =new ZonaSegura(1050,560,100,100,puntosMinimos,":/img/Recursos/portalN1.png");
    sonidoportal.setSource(
        QUrl("qrc:/Recursos/zonasegura.mp3"));

    sonidoportal.setVolume(1);
}
void Nivel1::crearObstaculos()
{
    obstaculos.push_back(new obstaculo(300,180,80,80,"roca"));

    obstaculos.push_back(new obstaculo(700, 220, 90,90,"hielo"));

    obstaculos.push_back(new obstaculo(500,500,70,70,"caja"));
}
void Nivel1::generarVidas()
{
    for(int i=0;i<2;i++)
    {
        vidasExtra.push_back(new premio(55+rand()%1100,40+rand()%620,"vida",0));
    }
}
void Nivel1::generarPremios()
{
    for(int i=0;i<8;i++)
    {
        premios.push_back(new premio(60+rand()%1100,50+rand()%600,"diamante",50));
        premios.push_back(new premio(60+rand()%1100,50+rand()%600,"copo",60));
    }
}
void Nivel1::detectarColisiones()
{
    for(auto obstaculo : obstaculos)
    {
        QRectF jugadorRect(
            jugador->getPosicion().getX(),
            jugador->getPosicion().getY(),
            64,
            64
            );

        if(jugadorRect.intersects(
                obstaculo->getHitbox()))
        {
            Vector2D vel = jugador->getVelocity();

            vel.setX(-vel.getX());
            vel.setY(-vel.getY());

            jugador->setVelocity(vel);

            jugador->recibirDanio(0);
        }
    }

    for(auto premio : premios)
    {
        if(premio->estaActivo() && jugador->colisionaCon(*premio))
            {if(premio->getTipo() == "copo")
                {
                    jugador->recogerCopo();
                }
                else
                {
                    jugador->recogerDiamante(
                        premio->getPuntos()
                        );
                }

                premio->setActivo(false);
            }
        }

    for(auto vida : vidasExtra)
    {
        if(vida->estaActivo() && jugador->colisionaCon(*vida))
        {
            jugador->setVidas(jugador->getVidas()+1);

            vida->setActivo(false);
        }
    }
    if(jugador->colisionaCon(*enemigo))
    {
        jugador->recibirDanio(1);
    }
    if(portal->estaDesbloqueada())
    {
        if(jugador->colisionaCon(*portal))
        {
            sonidoportal.play();
            completado = true;
        }
    }
}

void Nivel1::renderizar(QPainter* painter)
{
    jugador->renderizar(painter);
    enemigo->renderizar(painter);

    for(auto obstaculo : obstaculos)
    {
        obstaculo->renderizar( painter);
    }

    for(auto premio : premios)
    {
        if(premio->estaActivo())
        {
            premio->renderizar(painter);
        }
    }

    for(auto vida : vidasExtra)
    {
        if(vida->estaActivo())
        {
            vida->renderizar(painter);
        }
    }

    portal->renderizar(painter);
    painter->setPen(Qt::black);

    painter->setFont(
        QFont(
            "Arial",
            18,
            QFont::Bold
            )
        );
    painter->setPen(Qt::black);

    painter->setFont(
        QFont(
            "Arial",
            18,
            QFont::Bold
            )
        );
    painter->drawText(20,40,"VIDAS: " +QString::number(jugador->getVidas())
        );
    painter->drawText(20,75, "PUNTAJE: " + QString::number(jugador->getPuntaje())
        );
}
void Nivel1::manejarTeclaPresionada(
    QKeyEvent* event)
{
    jugador->manejarTeclaPresionada(
        static_cast<Qt::Key>(event->key()));
}

void Nivel1::manejarTeclaLiberada(
    QKeyEvent* event)
{
    jugador->manejarTeclaLiberada(
        static_cast<Qt::Key>(event->key()));
}
Nivel1::~Nivel1()
{
    delete jugador;

    delete enemigo;

    delete portal;

    for(auto obstaculo : obstaculos)
    {
        delete obstaculo;
    }

    for(auto premio : premios)
    {
        delete premio;
    }

    for(auto vida : vidasExtra)
    {
        delete vida;
    }
}
void Nivel1::actualizar(float dt)
{
    //jugador->setChocando(false);
    jugador->actualizar(dt);
    enemigo->actualizar(dt);
    portal->actualizarEstado(jugador->getPuntaje());
    detectarColisiones();
}
bool Nivel1::juegoTerminado() const
{
    return jugador->getVidas() <= 0;
}
bool Nivel1::nivelCompletado() const
{
    return completado;
}
void Nivel1::setVelocidadEnemigo(float v)
{
    if(enemigo)
    {
        enemigo->setVelocidad(v);
    }
}
