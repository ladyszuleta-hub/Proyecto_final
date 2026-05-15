#ifndef OBJETOJUEGO_H
#define OBJETOJUEGO_H

#include "Vector2D.h"

class ObjetoJuego
{
protected:
    Vector2D posicion;
    float ancho;
    float alto;
    bool activo;

public:
    // Constructor
    ObjetoJuego(float x, float y, float ancho, float alto);

    // Destructor virtual
    virtual ~ObjetoJuego();

    // Métodos virtuales
    virtual void actualizar(float deltaTime);
    virtual void renderizar();

    // Colisiones
    bool colisionaCon(const ObjetoJuego& otro) const;

    // Getters
    Vector2D getPosicion() const;
    bool estaActivo() const;

    // Setters
    void setActivo(bool estado);
};

#endif
