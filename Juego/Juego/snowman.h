#ifndef SNOWMAN_H
#define SNOWMAN_H

#include "entidad.h"

#include <QKeyEvent>
#include <QPainter>
#include <QRectF>
#include <QPixmap>
#include <QVector>

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

class SnowMan : public entidad
{
public:

    SnowMan(float x,float y,float ancho,float alto,fisicas* physics,int vidas = 3);

    ~SnowMan() override = default;

    void updateLogic(float dt) override;

    void setModoPlataforma(bool estado);


    void renderizar(QPainter* painter,float camaraX = 0);


    void manejarTeclaPresionada(Qt::Key key);

    void manejarTeclaLiberada(Qt::Key key);


    void moverIzquierda(float dt);

    void moverDerecha(float dt);

    void moverArriba(float dt);

    void moverAbajo(float dt);

    void saltar();


    void recogerCopo();

    void recogerDiamante(int puntos = 100);


    void recibirDanio(int cantidad = 1);


    int getVidas() const;
    void setVidas(int hp);

    int getPuntaje() const;

    bool tieneBoostVelocidad() const;

    bool esInvulnerable() const;

    EstadoSnowMan getEstado() const;


    void setLimites(QRectF limites);
    //sprites
    void cargarFrames();

    void actualizarSprite(float dt);

    void setChocando(bool estado);

    void setNivelActual(int nivel);
    void setVelocidadAuto(float v);

private:


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
    bool modoPlataforma;

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
