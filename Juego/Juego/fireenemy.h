#ifndef FIREENEMY_H
#define FIREENEMY_H

#include "entidad.h"
#include <QPainter>
#include <QPixmap>
#include <vector>

struct Percepcion
{
    bool jugadorVisible;

    float distanciaJugador;

    int vidasJugador;

    bool jugadorDebil;
};


class SnowMan;

// ESTADOS


enum class EstadoFireEnemy
{
    PATRULLANDO,
    PERSIGUIENDO,
    ATACANDO,
    BLOQUEADO
};

enum class TipoAccion
{
    PERSEGUIR,
    LANZAR_PROYECTIL,
    BLOQUEAR_CAMINO,
    PATRULLAR
};
struct Proyectil
{
    float x;
    float y;

    float vx;
    float vy;

    bool activo;
};
class FireEnemy : public entidad
{
public:

    FireEnemy(float x,float y,float ancho,float alto,fisicas* physics);

    ~FireEnemy() override;

    // GAME LOOP

    void updateLogic(float dt) override;

    void renderizar(QPainter* painter,float camaraX = 0);
    // TARGET

    void setTarget(SnowMan* target);
    // IA

    void ejecutarAccion(TipoAccion accion);

    // PROYECTILES

    bool lanzarProyectil();
    // GETTERS

    EstadoFireEnemy getEstado() const;

    float getRadioDerretimiento() const;

    void setRadioDerretimiento(float r);
    // VELOCIDAD
    void setVelocidad(float v);

    float getVelocidad() const;


private:


    SnowMan* target;

    EstadoFireEnemy estado;

    float radioDerretimiento;

    float animTimer;

    void simpleSeek(float dt);
    Percepcion percibir();
    TipoAccion razonamiento(const Percepcion& p);
    int ataquesExitosos;
    QPixmap spriteProyectil;
    bool proyectilActivo;
    Proyectil proyectil;
    int vecesQuePerdioAlJugador;
    QPixmap spriteSheet;

    std::vector<QPixmap> frames;

    int frameActual;

    void cargarSprites();
    void aprendizaje();

    void actualizarSprite();
};

#endif // FIREENEMY_H
