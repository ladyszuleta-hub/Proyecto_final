#include "ZonaSegura.h"
#include <QPixmap>

// Constructor
ZonaSegura::ZonaSegura(float x,float y,float ancho,float alto,int puntosNecesarios,QString rutaSprite): ObjetoJuego(x, y, ancho, alto){
    this->puntosNecesarios = puntosNecesarios;

    desbloqueada = false;

    spritePortal.load(rutaSprite);
}

ZonaSegura::~ZonaSegura(){}

void ZonaSegura::actualizar(float deltaTime){
    (void)deltaTime;
}

void ZonaSegura::renderizar(QPainter* painter){
        if(!desbloqueada)
            return;

        painter->drawPixmap(
            QRectF(
                posicion.getX(),
                posicion.getY(),
                ancho,
                alto),
            spritePortal,
            spritePortal.rect());
}

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
