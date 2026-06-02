#include "obstaculo.h"
using namespace std;

obstaculo::obstaculo(float x, float y, int ancho, int alto, string tipo) : ObjetoJuego(x, y, ancho, alto){
    this->tipo = tipo;
    if(tipo == "roca")
    {
        setSprite(":/img/Recursos/roca.png");
    }
    else if(tipo == "hielo")
    {
        setSprite(":/img/Recursos/hielo.png");
    }
    else{setSprite(":/img/Recursos/caja.png");}
}


obstaculo::~obstaculo(){}

void obstaculo::actualizar(float deltaTime){
    (void)deltaTime;
}

void obstaculo::renderizar(QPainter* painter){
    ObjetoJuego::renderizar(painter);
}

string obstaculo::getTipo() const{
    return tipo;
}
QRectF obstaculo::getHitbox() const
{
    if(tipo == "roca")
    {
        return QRectF(
            posicion.getX() + 10,
            posicion.getY() + 10,
            60,
            60
            );
    }

    if(tipo == "hielo")
    {
        return QRectF(
            posicion.getX() + 15,
            posicion.getY() + 15,
            50,
            50
            );
    }

    return QRectF(
        posicion.getX() + 10,
        posicion.getY() + 10,
        50,
        50
        );
}
