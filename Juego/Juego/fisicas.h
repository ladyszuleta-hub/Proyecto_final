#ifndef FISICAS_H
#define FISICAS_H
#include "Vector2D.h"
#include <stdexcept>
//Clase basica.
class fisicas
{
public:
    //fisicas();
    explicit fisicas(float gravedad = 0.0f);
    virtual ~fisicas()=default;

    virtual void aplicarfuerza(Vector2D& velocidad, Vector2D fuerza, float dt);

    virtual void actualizar(Vector2D& pos,Vector2D& velocidad, float dt)=0;
    float getgravedad() const;
    void setgravedad(float g);
protected:
    float gravity_;
};

// FISICA DE FRICCIÓN (NIVEL HIELO)

class FrictionPhysics : public fisicas {

public:

    explicit FrictionPhysics(float frictionCoeff = 0.08f);
    void actualizar(Vector2D& pos,Vector2D& velocidad, float dt) override;

    void bounceX(Vector2D& velocity, float restitution = 0.8f);
    void bounceY(Vector2D& velocity, float restitution = 0.8f);

private:

    float frictionCoeff_;
    void reboteX(Vector2D& velocidad, float restitution = 0.8f);
    void reboteY(Vector2D& velocidad, float restitution = 0.8f);
};


// FÍSICA DE GRAVEDAD
class GravityPhysics : public fisicas {

public:

    explicit GravityPhysics(float gravity = 980.0f,float groundY = 500.0f);

    void actualizar(Vector2D& pos,Vector2D& velocidad, float dt) override;

    void jump(Vector2D& velocidad,float jumpForce = 500.0f);

    bool isGrounded() const;

    void setGrounded(bool grounded);

private:

    float groundY_;
    bool isGrounded_;
};



// FÍSICA DE VIENTO

class WindPhysics : public fisicas {

public:

    explicit WindPhysics(Vector2D windDirection = Vector2D(1,0),float windStrength = 200.0f);

    void actualizar(Vector2D& pos,Vector2D& velocidad, float dt) override;


private:

    Vector2D windDirection_;
    float windStrength_;
};

#endif
