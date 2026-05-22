#include "ZonaSegura.h"

// Constructor
ZonaSegura::ZonaSegura(float x,float y,float ancho,float alto,int puntosNecesarios): ObjetoJuego(x, y, ancho, alto){
    this->puntosNecesarios = puntosNecesarios;

    desbloqueada = false;
}

ZonaSegura::~ZonaSegura(){}

void ZonaSegura::actualizar(float deltaTime){
    (void)deltaTime;
}

void ZonaSegura::renderizar(){}

// Actualiza si el portal ya puede abrirse
void ZonaSegura::actualizarEstado(int puntosJugador){
    desbloqueada =puntosJugador >= puntosNecesarios;
}

bool ZonaSegura::estaDesbloqueada() const{
    return desbloqueada;
}

int ZonaSegura::getPuntosNecesarios() const{
    return puntosNecesarios;
}
