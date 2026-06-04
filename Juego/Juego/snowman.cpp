#include "snowman.h"

#include <stdexcept>
#include <QPen>
#include <QPixmap>
#include <QDebug>


// CONSTRUCTOR

SnowMan::SnowMan(float x, float y,float ancho,float alto,fisicas* physics,int vidas)

    : entidad(x,y,ancho,alto,physics)
{
    if(vidas <= 0)
        throw std::invalid_argument(
            "vidas deben ser mayores a 0");

    this->vidas = vidas;

    puntaje = 0;

    estado = EstadoSnowMan::IDLE;

    boostVelocidadActivo = false;

    boostTimer = 0.0f;

    velocidadNormal = speed;

    invulnerable = false;

    hitTimer = 0.0f;

    moviendoIzquierda = false;

    moviendoDerecha = false;

    velocidadAuto = 80.0f;

    tieneLimites = false;

    frameActual = 0;

    animTimer = 0;
    tiempoGolpeado = 0.0f;

    nivelActual = 1;

    cargarFrames();
    modoPlataforma = false;
    //sonido
    audioPremio = new QAudioOutput();
    sonidoPremio = new QMediaPlayer();

    sonidoPremio->setAudioOutput(audioPremio);

    audioPremio->setVolume(1.0);
    sonidoPremio->setSource(QUrl("qrc:/Recursos/premio.mp3"));

}
SnowMan::~SnowMan()
{
    delete sonidoPremio;
    delete audioPremio;
}

void SnowMan::updateLogic(float dt)
{
    if(estado == EstadoSnowMan::MUERTO)
        return;

    // Movimiento continuo
    if(moviendoIzquierda)
        moverIzquierda(dt);

    if(moviendoDerecha)
        moverDerecha(dt);

    // ======================================
    // SOLO NIVEL 1
    // ======================================

    if(nivelActual == 1)
    {
        if(moviendoArriba)
        {
            moverArriba(dt);
        }

        if(moviendoAbajo)
        {
            moverAbajo(dt);
        }
    }

    // Timers
    if(tiempoGolpeado > 0)
    {
        tiempoGolpeado -= dt;
    }
    else if(estado == EstadoSnowMan::GOLPEADO)
    {
        estado = EstadoSnowMan::IDLE;
    }
    actualizarBoost(dt);

    actualizarHit(dt);
    // Limitar mapa
    if(tieneLimites)
        limitarDentroMapa();

    // Estados visuales
    if(estado != EstadoSnowMan::GOLPEADO)
    {
        if(moviendoIzquierda)
        {
            estado = EstadoSnowMan::MOVIENDO_IZQUIERDA;
        }
        else if(moviendoDerecha)
        {
            estado = EstadoSnowMan::MOVIENDO_DERECHA;
        }
        else if(moviendoAbajo)
        {
            estado = EstadoSnowMan::MOVIENDO_ABAJO;
        }
        else if(moviendoArriba)
        {
            estado = EstadoSnowMan::MOVIENDO_ARRIBA;
        }
        else
        {
            estado = EstadoSnowMan::IDLE;
        }
    }

    actualizarSprite(dt);
}

void SnowMan::renderizar(QPainter* painter,float camaraX)
{
    if(!activo)
        return;
    if(frames.empty())
        return;
    if(boostVelocidadActivo)
    {
        int alpha;

        if(static_cast<int>(boostTimer * 10) % 2 == 0)
            alpha = 100;
        else
            alpha = 80;

        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(190,240,255,alpha));

        painter->drawEllipse(
            posicion.getX() - camaraX - 8,
            posicion.getY() - 8,
            ancho + 16,
            alto + 16);
    }

    painter->drawPixmap(
        QRectF(posicion.getX() - camaraX,posicion.getY(),ancho,alto),
        frames[frameActual],frames[frameActual].rect());

}
void SnowMan::manejarTeclaPresionada(Qt::Key key)
{
    switch(key)
    {
    case Qt::Key_Left:
    case Qt::Key_A:

        moviendoIzquierda = true;
        break;

    case Qt::Key_Right:
    case Qt::Key_D:

        moviendoDerecha = true;
        break;
    case Qt::Key_Up:
    case Qt::Key_W:

        if(nivelActual == 1)
        {
            moviendoArriba = true;
        }
        else
        {
            saltar();
        }

        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        moviendoAbajo=true;
        break;

    case Qt::Key_Space:

        saltar();
        break;

    default:
        break;
    }
}

void SnowMan::manejarTeclaLiberada(Qt::Key key)
{
    switch(key)
    {
    case Qt::Key_Left:
    case Qt::Key_A:

        moviendoIzquierda = false;
        break;

    case Qt::Key_Right:
    case Qt::Key_D:

        moviendoDerecha = false;
        break;
    case Qt::Key_Up:
    case Qt::Key_W:

        if(!modoPlataforma)
        {
            moviendoArriba = false;
        }

        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        moviendoAbajo=false;
        break;
    case Qt::Key_Space:

        break;


    default:
        break;
    }
}
void SnowMan::resetTeclas()
{
    moviendoIzquierda = false;
    moviendoDerecha = false;
    moviendoArriba = false;
    moviendoAbajo = false;
}

void SnowMan::moverIzquierda(float dt)
{
    aplicarfuerza(
        Vector2D(-speed,0),
        dt);
}

void SnowMan::moverDerecha(float dt)
{
    aplicarfuerza(
        Vector2D(speed,0),
        dt);
}
void SnowMan::moverArriba(float dt)
{
    aplicarfuerza(Vector2D(0,-speed),dt);
}
void SnowMan::moverAbajo(float dt)
{
    aplicarfuerza(Vector2D(0,speed),dt);
}

void SnowMan::saltar()
{
    GravityPhysics* gp =
        dynamic_cast<GravityPhysics*>(physics);

    if(gp == nullptr)
    {
        return;
    }

    gp->jump(velocidad,650.0f);

    estado = EstadoSnowMan::SALTANDO;
}

void SnowMan::recogerCopo()
{
    boostTimer = 4.0f;

    if(!boostVelocidadActivo)
    {
        boostVelocidadActivo = true;
        speed = velocidadNormal * 1.8f;
    }
    sonidoPremio->setPosition(0);
    sonidoPremio->play();

}


void SnowMan::recogerDiamante(int puntos)
{
    if(puntos < 0)
    {
        throw std::invalid_argument(
            "puntos negativos");
    }

    puntaje += puntos;
    sonidoPremio->setPosition(0);
    sonidoPremio->play();
}

void SnowMan::recibirDanio(int cantidad)
{
    if(invulnerable)
        return;

    vidas -= cantidad;

    estado = EstadoSnowMan::GOLPEADO;

    invulnerable = true;

    hitTimer = 1.5f;

    if(vidas <= 0)
    {
        vidas = 0;

        estado = EstadoSnowMan::MUERTO;

        activo = false;
    }
    tiempoGolpeado = 0.2f;
}

int SnowMan::getVidas() const
{
    return vidas;
}

int SnowMan::getPuntaje() const
{
    return puntaje;
}
float SnowMan::getBoostTimer() const
{
    return boostTimer;
}
bool SnowMan::tieneBoostVelocidad() const
{
    return boostVelocidadActivo;
}

bool SnowMan::esInvulnerable() const
{
    return invulnerable;
}

EstadoSnowMan SnowMan::getEstado() const
{
    return estado;
}
void SnowMan::setLimites(QRectF limites)
{
    limitesMapa = limites;

    tieneLimites = true;
}


void SnowMan::actualizarBoost(float dt)
{
    if(!boostVelocidadActivo)
        return;

    boostTimer -= dt;

    if(boostTimer <= 0.0f)
    {
        boostVelocidadActivo = false;

        boostTimer = 0.0f;

        speed = velocidadNormal;
    }
}

void SnowMan::actualizarHit(float dt)
{
    if(!invulnerable)
        return;

    hitTimer -= dt;

    if(hitTimer <= 0.0f)
    {
        invulnerable = false;

        hitTimer = 0.0f;

        if(estado == EstadoSnowMan::GOLPEADO)
        {
            estado = EstadoSnowMan::IDLE;
        }
    }
}


void SnowMan::limitarDentroMapa()
{
    if(posicion.getX() < limitesMapa.left())
    {
        posicion.setX(limitesMapa.left());
    }

    if(posicion.getX() + ancho > limitesMapa.right())
    {
        posicion.setX(
            limitesMapa.right() - ancho);
    }
    if(posicion.getY() < limitesMapa.top())
    {
        posicion.setY(limitesMapa.top());
    }

    // ABAJO
    if(posicion.getY() + alto > limitesMapa.bottom())
    {
        posicion.setY(limitesMapa.bottom() - alto);
    }
}
void SnowMan::cargarFrames()
{
    spriteSheet.load(":/img/Recursos/snow.png");

    if(spriteSheet.isNull())
    {
        qDebug() << "No se pudo cargar el sprite";
        return;
    }

    int filas = 5;

    int columnas = 5;

    int anchoFrame =spriteSheet.width()/columnas;

    int altoFrame =spriteSheet.height()/filas;

    for(int y=0; y<filas; y++)
    {
        for(int x=0; x<columnas; x++)
        {
            frames.push_back(
                spriteSheet.copy(x*anchoFrame,y*altoFrame,anchoFrame,altoFrame)
                );
        }
    }
}
void SnowMan::actualizarSprite(float dt)
{
    animTimer += dt;

    switch(estado)
    {
    case EstadoSnowMan::IDLE:
        frameActual = 0;
        break;

    case EstadoSnowMan::MOVIENDO_DERECHA:

        if(animTimer < 0.15f)
            frameActual = 2;
        else
            frameActual = 8;

        if(animTimer >= 0.30f)
            animTimer = 0;

        break;

    case EstadoSnowMan::MOVIENDO_IZQUIERDA:

        if(animTimer < 0.15f)
            frameActual = 6;
        else
            frameActual = 7;

        if(animTimer >= 0.30f)
            animTimer = 0;

        break;

    case EstadoSnowMan::MOVIENDO_ARRIBA:

        if(animTimer < 0.15f)
            frameActual = 16;
        else
            frameActual = 17;

        if(animTimer >= 0.30f)
            animTimer = 0;

        break;

    case EstadoSnowMan::MOVIENDO_ABAJO:

        if(animTimer < 0.15f)
            frameActual = 5;
        else
            frameActual = 1;

        if(animTimer >= 0.30f)
            animTimer = 0;

        break;

    case EstadoSnowMan::SALTANDO:
        frameActual = 8;
        break;

    case EstadoSnowMan::GOLPEADO:
        frameActual = 13;
        break;

    case EstadoSnowMan::MUERTO:
        frameActual = 14;
        break;
    }
}


void SnowMan::setVelocidadAuto(float v)
{
    velocidadAuto = v;
}
void SnowMan::setNivelActual(int nivel)
{
    nivelActual = nivel;
}
void SnowMan::setModoPlataforma(bool estado)
{
    modoPlataforma = estado;
}
void SnowMan::setVidas(int hp)
{
    if(hp < 0)
        throw std::invalid_argument(
            "hp negativa");

    vidas = hp;
}
