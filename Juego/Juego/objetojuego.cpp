#include "ObjetoJuego.h"

// Constructor
ObjetoJuego::ObjetoJuego(float x, float y, float ancho, float alto)
    : posicion(x, y)
{
    this->ancho = ancho;
    this->alto = alto;
    activo = true;
}

// Destructor
ObjetoJuego::~ObjetoJuego()
{
}

// Métodos virtuales
void ObjetoJuego::actualizar(float deltaTime)
{
}

void ObjetoJuego::renderizar(QPainter* painter)
{
    if(!activo)
        return;

    if(sprite.isNull())
        return;

    painter->drawPixmap(QRectF(posicion.getX(),posicion.getY(),ancho,alto),sprite,sprite.rect());
}

// Colisión simple rectangular
bool ObjetoJuego::colisionaCon(const ObjetoJuego& otro) const
{
    return (
        posicion.getX() < otro.posicion.getX() + otro.ancho &&
        posicion.getX() + ancho > otro.posicion.getX() &&
        posicion.getY() < otro.posicion.getY() + otro.alto &&
        posicion.getY() + alto > otro.posicion.getY()
        );
}

// Getters
Vector2D ObjetoJuego::getPosicion() const
{
    return posicion;
}

bool ObjetoJuego::estaActivo() const
{
    return activo;
}

// Setter
void ObjetoJuego::setActivo(bool estado)
{
    activo = estado;
}
void ObjetoJuego::setSprite(const QString& ruta)
{
    sprite.load(ruta);
}

void ObjetoJuego::setPosicion(float x,float y)
{
    posicion.setX(x);
    posicion.setY(y);
}
