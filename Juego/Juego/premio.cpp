#include "premio.h"

premio::premio(float x, float y, int puntos):ObjetoJuego(x,y,32,32){
    this->puntos = puntos;
}

premio::~premio(){}

void premio::actualizar(float deltaTime){
    (void)deltaTime;
}

void premio::renderizar(){}

int premio::getPuntos() const{
    return puntos;
}
