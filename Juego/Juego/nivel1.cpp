#include "nivel1.h"
#include <cstdlib>

Nivel1::Nivel1()
{
    enemigo = new FireEnemy(500,500,48,48,new FrictionPhysics(0.02f));
    jugador = new SnowMan(120,120,64,64,new FrictionPhysics(0.01));
    limitesMapa =QRectF(55,45,1265,655);

    jugador->setLimites(limitesMapa);
    jugador->resetTeclas();
    enemigo->setTarget(jugador);

    crearObstaculos();
    generarPremios();
    generarVidas();

    puntosMinimos = 400;
    tiempoRestante = 60.0f;
    completado = false;

    portal =new ZonaSegura(1050,100,100,94,puntosMinimos,":/img/Recursos/portalN1.png");
    //sonido para el portal
    audioPortal = new QAudioOutput();

    sonidoPortal = new QMediaPlayer();

    sonidoPortal->setAudioOutput(audioPortal);

    sonidoPortal->setSource(QUrl("qrc:/Recursos/zonasegura.mp3"));

    audioPortal->setVolume(1.0);

}
void Nivel1::crearObstaculos()
{
    obstaculos.push_back(new obstaculo(300,180,80,80,"roca"));

    obstaculos.push_back(new obstaculo(700, 220, 90,90,"hielo"));

    obstaculos.push_back(new obstaculo(500,500,70,70,"caja"));

    obstaculos.push_back(new obstaculo(1000,400,80,80,"roca"));

    obstaculos.push_back(new obstaculo(200, 500, 90,90,"hielo"));

    obstaculos.push_back(new obstaculo(900,180,70,70,"caja"));
}
void Nivel1::generarVidas()
{
    vidasExtra.push_back(
        new premio(250,600,"vida",0));

    vidasExtra.push_back(
        new premio(950,100,"vida",0));
}
void Nivel1::generarPremios()
{
    // 8 diamantes aleatorios
    for(int i = 0; i < 8; i++)
    {
        float x, y;

        do
        {
            x = 60 + rand()%1100;
            y = 50 + rand()%600;
        }
        while(!posicionLibre(x,y));

        premios.push_back(new premio(x,y,"diamante",50));
    }

    // Copos en posiciones especificas
    premios.push_back(
        new premio(150,120,"copo",0));

    premios.push_back(
        new premio(850,320,"copo",0));

    premios.push_back(
        new premio(1150,550,"copo",0));
}
bool Nivel1::posicionLibre(float x, float y)
{
    QRectF nuevo(x, y, 32, 32);

    for(auto* obstaculo : obstaculos)
    {
        if(nuevo.intersects(obstaculo->getHitbox()))
            return false;
    }

    return true;
}
void Nivel1::detectarColisiones()
{
    for(auto* obstaculo : obstaculos)
    {
        QRectF jugadorRect(jugador->getPosicion().getX(),jugador->getPosicion().getY(),64,64);

        if(jugadorRect.intersects(obstaculo->getHitbox()))
        {
            Vector2D vel = jugador->getVelocity();

            vel.setX(-vel.getX());
            vel.setY(-vel.getY());

            jugador->setVelocity(vel);

            jugador->recibirDanio(0);
        }
    }

    for(auto* premio : premios)
    {
        if(premio->estaActivo() && jugador->colisionaCon(*premio)){
            if(premio->getTipo() == "copo")
                {
                    jugador->recogerCopo();
                }
                else
                {
                    jugador->recogerDiamante(premio->getPuntos());
                }

                premio->setActivo(false);
            }
        }

    for(auto* vida : vidasExtra)
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
        QRectF jugadorRect(jugador->getPosicion().getX(),jugador->getPosicion().getY(),50,50);

        if(jugadorRect.intersects(portal->getHitbox()))
        {
            sonidoPortal->play();
            completado = true;
        }
    }
}

void Nivel1::renderizar(QPainter* painter)
{
    portal->renderizar(painter);
    jugador->renderizar(painter);
    enemigo->renderizar(painter);

    for(auto* obstaculo : obstaculos)
    {
        obstaculo->renderizar( painter);
    }

    for(auto* premio : premios)
    {
        if(premio->estaActivo())
        {
            premio->renderizar(painter);
        }
    }

    for(auto* vida : vidasExtra)
    {
        if(vida->estaActivo())
        {
            vida->renderizar(painter);
        }
    }
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
    renderizarTemporizador(painter);
    renderizarBoost(painter);
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
    jugador->manejarTeclaLiberada(static_cast<Qt::Key>(event->key()));
}
Nivel1::~Nivel1()
{
    delete jugador;

    delete enemigo;

    delete portal;

    delete audioPortal;
    delete sonidoPortal;

    for(auto* obstaculo : obstaculos)
    {
        delete obstaculo;
    }

    for(auto* premio : premios)
    {
        delete premio;
    }

    for(auto* vida : vidasExtra)
    {
        delete vida;
    }
}
void Nivel1::actualizar(float dt)
{
    jugador->actualizar(dt);
    enemigo->actualizar(dt);
    portal->actualizarEstado(jugador->getPuntaje());
    detectarColisiones();
    tiempoRestante -= dt;

    if(tiempoRestante < 0)
    {
        tiempoRestante = 0;
    }

}
bool Nivel1::juegoTerminado() const
{
    return jugador->getVidas() <= 0|| tiempoRestante <= 0;
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
void Nivel1::renderizarTemporizador(QPainter* painter)
{
    int minutos = static_cast<int>(tiempoRestante) / 60;

    int segundos = static_cast<int>(tiempoRestante) % 60;

    QString tiempoTexto =QString("%1:%2").arg(minutos).arg(segundos, 2, 10, QChar('0'));

    painter->setFont(QFont("Arial",22,QFont::Bold));

    if(tiempoRestante <= 10)
    {
        if(static_cast<int>(tiempoRestante * 2) % 2 == 0)
            painter->setPen(Qt::red);
        else
            painter->setPen(Qt::darkRed);

    }
    else
    {
        painter->setPen(Qt::black);
    }
    painter->drawText(1100,40,"TIEMPO " + tiempoTexto);
}
void Nivel1::renderizarBoost(QPainter* painter)
{
    if(!jugador->tieneBoostVelocidad())
        return;

    painter->setPen(Qt::black);

    painter->drawText(
        20,
        110,
        "VELOCIDAD");

    // Fondo de la barra
    painter->drawRect(
        120,
        95,
        120,
        20);

    // Barra que se vacía
    float porcentaje =jugador->getBoostTimer() / 4.0f;

    painter->fillRect(
        121,
        96,
        static_cast<int>(118 * porcentaje),
        18,
        Qt::cyan);
}
