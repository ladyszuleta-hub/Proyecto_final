#include "premio.h"
using namespace std;

premio::premio(float x, float y, QString tipo, int puntos):ObjetoJuego(x,y,32,32){
    this->puntos = puntos;
    if(tipo == "diamante")
    {
        setSprite(":/img/Recursos/diamante.png");
    }
    else if(tipo == "vida")
    {
        setSprite(":/img/Recursos/vida.png");
    }
    else if(tipo == "copo")
    {
        setSprite(":/img/Recursos/copo.png");
    }
}

premio::~premio(){}

void premio::actualizar(float deltaTime){
    (void)deltaTime;
}

void premio::renderizar(QPainter* painter){
    ObjetoJuego::renderizar(painter);
}

int premio::getPuntos() const{
    return puntos;
}
QString premio::getTipo() const{
    return tipo;
}
