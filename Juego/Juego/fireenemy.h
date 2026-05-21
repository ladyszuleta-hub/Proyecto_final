#ifndef FIREENEMY_H
#define FIREENEMY_H

#include "entidad.h"
#include <QPainter>

    // Forward declaration
    class FireAgent;
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

// ======================================================
// FIRE ENEMY
// ======================================================

class FireEnemy : public entidad
{
public:

    FireEnemy(float x,
              float y,
              float ancho,
              float alto,
              fisicas* physics,
              FireAgent* agent = nullptr);

    ~FireEnemy() override;

    // ==========================================
    // GAME LOOP
    // ==========================================

    void updateLogic(float dt) override;

    void renderizar(QPainter* painter);

    // ==========================================
    // TARGET
    // ==========================================

    void setTarget(SnowMan* target);

    // ==========================================
    // IA
    // ==========================================

    void ejecutarAccion(TipoAccion accion);

    // ==========================================
    // PROYECTILES
    // ==========================================

    bool lanzarProyectil();

    // ==========================================
    // GETTERS
    // ==========================================

    EstadoFireEnemy getEstado() const;

    float getRadioDerretimiento() const;

    void setRadioDerretimiento(float r);

    void setAgent(FireAgent* agent);

private:

    FireAgent* agent;

    SnowMan* target;

    EstadoFireEnemy estado;

    float radioDerretimiento;

    float animTimer;

    // ==========================================
    // SEEK SIMPLE
    // ==========================================

    void simpleSeek(float dt);
};

#endif // FIREENEMY_H
