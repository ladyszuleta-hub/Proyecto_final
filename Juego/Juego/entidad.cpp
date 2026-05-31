#include "entidad.h"

entidad::entidad(float x, float y, float ancho, float alto, fisicas *physics): ObjetoJuego(x,y,ancho,alto)
{
    velocidad = Vector2D(0,0);

    vidas = 3;

    speed = 150.0f;

    if(physics == nullptr)
        throw std::invalid_argument(
            "physics no puede ser nullptr");

    this->physics = physics;
}


entidad::~entidad()
{
    delete physics;

    physics = nullptr;
}



void entidad::actualizar(float dt)
{
    if(!activo)
        return;

    // física
    physics->actualizar(posicion,velocidad,dt);
    // lógica específica
    updateLogic(dt);
}



void entidad::aplicarfuerza(Vector2D force,float dt)
{
    if(!activo)
        return;
    physics->aplicarfuerza(velocidad,force,dt);
}

void entidad::setfisicas(fisicas* nuevo)
{
    if(nuevo == nullptr)
        throw std::invalid_argument(
            "nuevo physics null");

    delete physics;
    physics = nuevo;
}


int entidad::getVidas() const
{
    return vidas;
}

void entidad::setVidas(int hp)
{
    if(hp < 0)
        throw std::invalid_argument(
            "hp negativa");

    vidas = hp;
}

void entidad::takeDamage(int amount)
{
    if(amount < 0)
        throw std::invalid_argument(
            "damage negativo");
    vidas -= amount;
    if(vidas <= 0)
    {
        vidas = 0;
        activo = false;
    }
}

bool entidad::isAlive() const
{
    return activo && vidas > 0;
}


Vector2D entidad::getVelocity() const
{
    return velocidad;
}

void entidad::setVelocity(Vector2D vel)
{
    velocidad = vel;
}


float entidad::getSpeed() const
{
    return speed;
}

void entidad::setSpeed(float s)
{
    if(s < 0)
        throw std::invalid_argument(
            "speed negativa");

    speed = s;
}
fisicas* entidad::getPhysics() const
{
    return physics;
}
