#include "fireenemy.h"
#include "snowman.h"
#include <cmath>
#include <stdexcept>
#include <QPen>


FireEnemy::FireEnemy(float x,float y,float ancho,float alto,fisicas* physics): entidad(x,y,ancho,alto,physics)
{
    target = nullptr;
    frameActual = 0;

    cargarSprites();

    spriteProyectil.load(":/img/Recursos/proyectil_de_fuego.png");

    estado = EstadoFireEnemy::PATRULLANDO;

    radioDerretimiento = 30.0f;

    animTimer = 0.0f;

    speed = 180.0f;

    vidas = 1;

    ataquesExitosos = 0;

    vecesQuePerdioAlJugador = 0;

    proyectilActivo = false;
    proyectil.activo = false;
}

FireEnemy::~FireEnemy(){

}
void FireEnemy::setVelocidad(float v)
{
    if(v > 0)
    {
        speed = v;
    }
}

float FireEnemy::getVelocidad() const
{
    return speed;
}

void FireEnemy::updateLogic(float dt)
{
    if(!activo || target == nullptr)
        return;

    animTimer += dt;

    Percepcion p = percibir();

    TipoAccion accion =
        decidirAccion(p);

    ejecutarAccion(accion);

    if(proyectil.activo)
    {
        proyectil.x += proyectil.vx * dt;
        proyectil.y += proyectil.vy * dt;
    }

    if(proyectil.activo)
    {
        float dx =
            proyectil.x - target->getPosicion().getX();

        float dy =
            proyectil.y - target->getPosicion().getY();

        float distancia =
            std::sqrt(dx*dx + dy*dy);

        if(distancia < 25)
        {
            target->recibirDanio(1);

            proyectil.activo = false;

            proyectilActivo = false;
        }
    }
    if(proyectil.activo)
    {
        if(proyectil.x < -100 ||
            proyectil.x > 5000 ||
            proyectil.y < -100 ||
            proyectil.y > 1000)
        {
            proyectil.activo = false;

            proyectilActivo = false;
        }
    }


    // DAÑO AL JUGADOR

    if(target->isAlive())
    {
        float dx =
            target->getPosicion().getX()
            - posicion.getX();

        float dy =
            target->getPosicion().getY()
            - posicion.getY();

        float distancia =
            std::sqrt(dx*dx + dy*dy);

        if(distancia < radioDerretimiento)
        {
            target->recibirDanio(1);

            ataquesExitosos++;
        }
    }
    actualizarSprite();
}

// SEEK SIMPLE

void FireEnemy::simpleSeek(float dt)
{
    float dx =
        target->getPosicion().getX()
        - posicion.getX();

    float dy =
        target->getPosicion().getY()
        - posicion.getY();

    float distancia =
        std::sqrt(dx*dx + dy*dy);

    if(distancia < 5.0f)
    {
        estado = EstadoFireEnemy::ATACANDO;
        return;
    }

    // Normalizar
    dx /= distancia;
    dy /= distancia;

    velocidad.setX(dx * speed);

    velocidad.setY(dy * speed);

    estado = EstadoFireEnemy::PERSIGUIENDO;

    (void)dt;
}
// RENDER

void FireEnemy::renderizar(QPainter* painter,float camaraX)
{
    if(!activo)
        return;


    painter->drawPixmap(QRectF(posicion.getX() - camaraX,posicion.getY(),ancho,alto),
        frames[frameActual],frames[frameActual].rect());

    if(proyectil.activo)
    {
        painter->drawPixmap(QRectF(proyectil.x - camaraX,
                proyectil.y,32,32),spriteProyectil,spriteProyectil.rect());
    }
}

// ACCIONES

void FireEnemy::ejecutarAccion(TipoAccion accion)
{
    switch(accion)
    {
    case TipoAccion::PERSEGUIR:

        estado = EstadoFireEnemy::PERSIGUIENDO;

        if(target)
        {
            float dx =target->getPosicion().getX()- posicion.getX();

            float dy =target->getPosicion().getY()- posicion.getY();

            float distancia =std::sqrt(dx*dx + dy*dy);

            dx /= distancia;

            dy /= distancia;

            velocidad.setX(dx * speed);

            velocidad.setY(dy * speed);
        }

        break;

    case TipoAccion::LANZAR_PROYECTIL:

        estado = EstadoFireEnemy::ATACANDO;

        lanzarProyectil();

        break;

    case TipoAccion::BLOQUEAR_CAMINO:

        estado = EstadoFireEnemy::BLOQUEADO;

        break;

    case TipoAccion::PATRULLAR:

        estado = EstadoFireEnemy::PATRULLANDO;

        velocidad.setX(
            speed * 0.5f *
            std::sin(animTimer));

        velocidad.setY(0);

        break;
    }
}

// GETTERS

EstadoFireEnemy FireEnemy::getEstado() const
{
    return estado;
}

float FireEnemy::getRadioDerretimiento() const
{
    return radioDerretimiento;
}

void FireEnemy::setRadioDerretimiento(float r)
{
    if(r < 0)
    {
        throw std::invalid_argument(
            "radio negativo");
    }

    radioDerretimiento = r;
}

void FireEnemy::setTarget(SnowMan* target)
{
    if(target == nullptr)
    {
        throw std::invalid_argument(
            "target null");
    }

    this->target = target;
}

Percepcion FireEnemy::percibir()
{
    Percepcion p;

    float dx =
        target->getPosicion().getX()
        - posicion.getX();

    float dy =
        target->getPosicion().getY()
        - posicion.getY();

    p.distanciaJugador =
        std::sqrt(dx*dx + dy*dy);

    p.jugadorVisible =
        p.distanciaJugador < 300;

    p.vidasJugador =
        target->getVidas();

    p.jugadorDebil =
        p.vidasJugador <= 1;

    return p;
}
TipoAccion FireEnemy::decidirAccion(const Percepcion& p)
{
    if(!p.jugadorVisible)
    {
        vecesQuePerdioAlJugador++;

        return TipoAccion::PATRULLAR;
    }

    if(p.distanciaJugador < 200){
        return TipoAccion::LANZAR_PROYECTIL;
    }

    return TipoAccion::PERSEGUIR;
}
bool FireEnemy::lanzarProyectil()
{
    if(proyectilActivo)
        return false;

    if(target == nullptr)
        return false;

    float dx =
        target->getPosicion().getX() - posicion.getX();

    float dy =
        target->getPosicion().getY() - posicion.getY();

    float distancia =
        std::sqrt(dx*dx + dy*dy);

    dx /= distancia;
    dy /= distancia;

    proyectil.x = posicion.getX() + ancho/2;
    proyectil.y = posicion.getY() + alto/2;

    proyectil.vx = dx * 300;
    proyectil.vy = dy * 300;

    proyectil.activo = true;
    proyectilActivo = true;

    return true;
}
void FireEnemy::actualizarSprite()
{
    if(target == nullptr)
        return;

    float dx =
        target->getPosicion().getX()
        - posicion.getX();

    float dy =
        target->getPosicion().getY()
        - posicion.getY();

    if(std::abs(dx) > std::abs(dy))
    {
        if(dx > 0)
        {
            frameActual = 3; // derecha
        }
        else
        {
            frameActual = 2; // izquierda
        }
    }
    else
    {
        if(dy > 0)
        {
            frameActual = 0; // abajo
        }
        else
        {
            frameActual = 1; // arriba
        }
    }
}
void FireEnemy::cargarSprites()
{
    spriteSheet.load(
        ":/img/Recursos/enemigo.png");

    if(spriteSheet.isNull())
    {
        qDebug() << "No se pudo cargar enemigo";
        return;
    }

    int filas = 2;
    int columnas = 2;

    int anchoFrame =
        spriteSheet.width()/columnas;

    int altoFrame =
        spriteSheet.height()/filas;

    for(int y=0;y<filas;y++)
    {
        for(int x=0;x<columnas;x++)
        {
            frames.push_back(
                spriteSheet.copy(x*anchoFrame,y*altoFrame,anchoFrame,altoFrame)
                );
        }
    }
}
