#include "fireenemy.h"
#include "snowman.h"
#include <cmath>
#include <stdexcept>
#include <QPen>


FireEnemy::FireEnemy(float x,float y,float ancho,float alto,fisicas* physics,FireAgent* agent)

    : entidad(x,y,ancho,alto,physics)
{
    estrategiaActual = new EstrategiaPersecucion();
    this->agent = agent;

    target = nullptr;

    estado = EstadoFireEnemy::PATRULLANDO;

    radioDerretimiento = 30.0f;

    animTimer = 0.0f;

    speed = 120.0f;

    health = 1;
}

// ======================================================
// DESTRUCTOR
// ======================================================

FireEnemy::~FireEnemy(){
    delete estrategiaActual;
}

// ======================================================
// UPDATE
// ======================================================

void FireEnemy::updateLogic(float dt)
{
    if(!activo || target == nullptr)
        return;

    animTimer += dt;

    // Fase 2 IA
    if(agent != nullptr)
    {
        // futura IA
    }
    else
    {
        // seek simple
        float dx =
            target->getPosicion().getX()
            - posicion.getX();

        float dy =
            target->getPosicion().getY()
            - posicion.getY();

        float distancia =
            std::sqrt(dx*dx + dy*dy);

        // =============================
        // CAMBIO DE ESTRATEGIA
        // =============================

        delete estrategiaActual;

        if(distancia < 120)
        {
            estrategiaActual =
                new EstrategiaAtaque();
        }
        else
        {
            estrategiaActual =
                new EstrategiaPersecucion();
        }

        // EJECUTAR IA

        estrategiaActual->ejecutar(
            this,
            target);
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
        }
    }
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

    painter->save();

    // Animación
    float pulse =
        1.0f +
        0.1f * std::sin(animTimer * 6.0f);

    float w = ancho * pulse;

    float h = alto * pulse;

    float ox = (w - ancho)/2.0f;

    float oy = (h - alto)/2.0f;

    // Aura
    painter->setBrush(
        QColor(255,120,0,80));

    painter->setPen(Qt::NoPen);

    painter->drawEllipse(
        QRectF(posicion.getX()-ox-8,
               posicion.getY()-oy-8,
               w+16,
               h+16));

    // Cuerpo
    painter->setBrush(
        QColor(255,140,0));

    painter->drawEllipse(
        QRectF(posicion.getX()-ox,
               posicion.getY()-oy,
               w,
               h));

    // Núcleo
    painter->setBrush(
        QColor(255,230,50));

    painter->drawEllipse(
        QRectF(posicion.getX()+w*0.2f-ox,
               posicion.getY()+h*0.2f-oy,
               w*0.6f,
               h*0.6f));

    // Ojos
    painter->setBrush(
        QColor(0,180,0));

    painter->drawEllipse(
        QRectF(posicion.getX()+6,
               posicion.getY()+8,
               7,
               7));

    painter->drawEllipse(
        QRectF(posicion.getX()+22,
               posicion.getY()+8,
               7,
               7));

    painter->restore();
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
            float dx =
                target->getPosicion().getX()
                - posicion.getX();

            float dy =
                target->getPosicion().getY()
                - posicion.getY();

            float distancia =
                std::sqrt(dx*dx + dy*dy);

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

// PROYECTIL

bool FireEnemy::lanzarProyectil()
{
    if(target == nullptr)
        return false;

    return true;
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

void FireEnemy::setAgent(FireAgent* agent)
{
    if(agent == nullptr)
    {
        throw std::invalid_argument(
            "agent null");
    }

    this->agent = agent;
}
