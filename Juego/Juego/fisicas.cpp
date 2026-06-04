#include "fisicas.h"

//fisicas::fisicas() {}

// BASE

fisicas::fisicas(float gravedad)
{
    gravity_ = gravedad;
}

float fisicas::getgravedad() const
{
    return gravity_;
}

void fisicas::setgravedad(float g)
{
    gravity_ = g;
}
void fisicas::aplicarfuerza(Vector2D& velocidad, Vector2D fuerza, float dt)
{
    velocidad.setX(velocidad.getX()+ fuerza.getX()*dt);

    velocidad.setY(velocidad.getY()+ fuerza.getY()*dt);
}

// ==================== FRICTION ====================

FrictionPhysics::FrictionPhysics(float frictionCoeff)
{
    frictionCoeff_ = frictionCoeff;
}
void FrictionPhysics::actualizar(Vector2D& pos,Vector2D& velocidad, float dt)
{
    velocidad.setX(velocidad.getX()*(1.0f-frictionCoeff_));

    velocidad.setY(velocidad.getY()*(1.0f-frictionCoeff_));

    pos.mover(velocidad.getX()*dt,velocidad.getY()*dt);
}
void FrictionPhysics::reboteX(Vector2D& velocidad,float restitution)
{
    velocidad.setX( -velocidad.getX() * restitution);
}

void FrictionPhysics::reboteY(Vector2D& velocidad, float restitution)
{
    velocidad.setY( -velocidad.getY() * restitution);
}


// ==================== GRAVITY ====================

GravityPhysics::GravityPhysics(float gravity,float groundY): fisicas(gravity)
{
    groundY_ = groundY;
    isGrounded_ = false;
}


void GravityPhysics::actualizar(Vector2D& pos,Vector2D& velocidad, float dt){
    velocidad.setY(velocidad.getY()+ gravity_*dt);

    pos.mover(velocidad.getX()*dt,velocidad.getY()*dt);

    if(pos.getY() >= groundY_)
    {
        pos.setY(groundY_);

        velocidad.setY(0);

        isGrounded_ = true;
    }
    else
    {
        isGrounded_ = false;
    }
}

void GravityPhysics::jump(Vector2D& velocidad,float jumpForce)
{
    if(!isGrounded_)
    {
        return;
    }

    velocidad.setY(-jumpForce);

    isGrounded_ = false;
}

bool GravityPhysics::isGrounded() const
{
    return isGrounded_;
}
void GravityPhysics::setGrounded(bool grounded)
{
    isGrounded_ = grounded;
}
