#ifndef ENTIDAD_H
#define ENTIDAD_H
#include "objetoJuego.h"
#include "fisicas.h"
#include <stdexcept>
class entidad : public ObjetoJuego
{
protected:

    Vector2D velocidad;

    int health;

    float speed;

    fisicas* physics;
public:
    entidad(float x, float y, float ancho, float alto, fisicas* physics);
    virtual ~entidad();
    virtual void actualizar(float dt) override;
    void aplicarfuerza(Vector2D force, float dt);
    void setfisicas(fisicas* nuevo);

    // VIDA
    int getHealth() const;

    void setHealth(int hp);

    void takeDamage(int amount);

    bool isAlive() const;
    // VELOCIDAD
    Vector2D getVelocity() const;

    void setVelocity(Vector2D vel);

    // SPEED
    float getSpeed() const;

    void setSpeed(float s);

protected:
    virtual void updateLogic(float dt) = 0;

};

#endif // ENTIDAD_H

