#ifndef ZONASEGURA_H
#define ZONASEGURA_H
#include "ObjetoJuego.h"
class ZonaSegura: public ObjetoJuego
{
private:

    int puntosNecesarios;

    bool desbloqueada;

    QPixmap spritePortal;
public:
    ZonaSegura(float x, float y, float ancho, float alto, int puntosNecesarios, QString rutaSprite);
    virtual ~ZonaSegura();

    void actualizar(float deltaTime) override;

    void renderizar(QPainter* painter) override;

    void actualizarEstado(int puntosJugador);

    bool estaDesbloqueada() const;

    int getPuntosNecesarios() const;
    QRectF getHitbox() const;
};

#endif // ZONASEGURA_H
