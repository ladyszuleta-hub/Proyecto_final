#ifndef SNOWMAN_H
#define SNOWMAN_H

#include "entidad.h"

#include <QKeyEvent>
#include <QPainter>
#include <QRectF>
#include <QPixmap>
#include <QVector>

// ======================================================
// ESTADOS DEL PERSONAJE
// ======================================================

enum class EstadoSnowMan
{
    IDLE,
    MOVIENDO_ARRIBA,
    MOVIENDO_ABAJO,
    MOVIENDO_IZQUIERDA,
    MOVIENDO_DERECHA,
    SALTANDO,
    GOLPEADO,
    MUERTO
};

// ======================================================
// CLASE SNOWMAN
// ======================================================

class SnowMan : public entidad
{
public:

    // ==================================================
    // CONSTRUCTOR
    // ==================================================

    SnowMan(float x,
            float y,
            float ancho,
            float alto,
            fisicas* physics,
            int vidas = 3);

    ~SnowMan() override = default;

    // ==================================================
    // CICLO PRINCIPAL
    // ==================================================

    void updateLogic(float dt) override;

    void renderizar(QPainter* painter);

    // ==================================================
    // INPUT
    // ==================================================

    void manejarTeclaPresionada(Qt::Key key);

    void manejarTeclaLiberada(Qt::Key key);

    // ==================================================
    // MOVIMIENTO
    // ==================================================

    void moverIzquierda(float dt);

    void moverDerecha(float dt);

    void moverArriba(float dt);

    void moverAbajo(float dt);

    void saltar();

    // ==================================================
    // POWER UPS
    // ==================================================

    void recogerCopo();

    void recogerDiamante(int puntos = 100);

    // ==================================================
    // DAÑO
    // ==================================================

    void recibirDanio(int cantidad = 1);

    // ==================================================
    // GETTERS
    // ==================================================

    int getVidas() const;

    int getPuntaje() const;

    bool tieneBoostVelocidad() const;

    bool esInvulnerable() const;

    EstadoSnowMan getEstado() const;

    // ==================================================
    // LÍMITES DEL MAPA
    // ==================================================

    void setLimites(QRectF limites);
    //sprites
    void cargarFrames();

    void actualizarSprite(float dt);

    void setChocando(bool estado);

    void setNivelActual(int nivel);

private:

    // ==================================================
    // ATRIBUTOS
    // ==================================================

    int vidas;

    int puntaje;

    EstadoSnowMan estado;

    // Boost velocidad
    bool boostVelocidadActivo;

    float boostTimer;

    float velocidadNormal;

    // Invulnerabilidad
    bool invulnerable;

    float hitTimer;

    // Movimiento continuo
    bool moviendoIzquierda;

    bool moviendoDerecha;
    bool moviendoArriba;

    bool moviendoAbajo;

    // Movimiento automático nivel 1
    float velocidadAuto;

    // Límites
    QRectF limitesMapa;

    bool tieneLimites;

    // ==================================================
    // MÉTODOS PRIVADOS
    // ==================================================

    void actualizarBoost(float dt);

    void actualizarHit(float dt);

    void limitarDentroMapa();

    //sprites
    QPixmap spriteSheet;

    QVector<QPixmap> frames;

    int frameActual;

    float animTimer;

    bool chocando;

    int nivelActual;
};

#endif // SNOWMAN_H
