#include "obstaculo.h"
using namespace std;

obstaculo::obstaculo(float x, float y, float ancho, float alto, string tipo) : ObjetoJuego(x, y, ancho, alto){
    this->tipo = tipo;
}

obstaculo::~obstaculo(){}

void obstaculo::actualizar(float deltaTime){
    (void)deltaTime;
}

void obstaculo::renderizar(){}

string obstaculo::getTipo() const{
    return tipo;
}
