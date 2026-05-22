#ifndef ZONASEGURA_H
#define ZONASEGURA_H
#include "ObjetoJuego.h"
class ZonaSegura: public ObjetoJuego
{
private:

    int puntosNecesarios;

    bool desbloqueada;
public:
    ZonaSegura(float x,float y,float ancho,float alto,int puntosNecesarios);
    virtual ~ZonaSegura();

    void actualizar(float deltaTime) override;

    void renderizar() override;

    void actualizarEstado(int puntosJugador);

    bool estaDesbloqueada() const;

    int getPuntosNecesarios() const;
};

#endif // ZONASEGURA_H
