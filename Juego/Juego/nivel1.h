#ifndef NIVEL1_H
#define NIVEL1_H

#include <vector>
#include <QPainter>
#include <QKeyEvent>
#include "fireenemy.h"
#include <QSoundEffect>
#include "snowman.h"
#include "obstaculo.h"
#include "premio.h"
#include "zonasegura.h"

class Nivel1
{
private:

    SnowMan* jugador;
    FireEnemy* enemigo;

    std::vector<obstaculo*> obstaculos;

    std::vector<premio*> premios;

    std::vector<premio*> vidasExtra;

    ZonaSegura* portal;

    int puntosMinimos;

    QRectF limitesMapa;
    bool completado;


public:

    Nivel1();

    ~Nivel1();

    void actualizar(float dt);

    void renderizar(QPainter* painter);

    void manejarTeclaPresionada(QKeyEvent* event);

    void manejarTeclaLiberada(QKeyEvent* event);
    bool juegoTerminado() const;
    bool nivelCompletado() const;
    void setVelocidadEnemigo(float v);

private:

    void crearObstaculos();

    void generarPremios();

    void generarVidas();

    void detectarColisiones();
    QSoundEffect sonidoportal;


};
#endif // NIVEL1_H
