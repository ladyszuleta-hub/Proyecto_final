#ifndef NIVEL2_H
#define NIVEL2_H

#include <QPainter>
#include <QKeyEvent>
#include <QPixmap>

#include <vector>

#include "snowman.h"
#include "fireenemy.h"
#include "obstaculo.h"
#include "premio.h"
#include "ZonaSegura.h"

class Nivel2
{
public:

    Nivel2();

    ~Nivel2();

    void actualizar(float dt);

    void renderizar(QPainter* painter);

    void manejarTeclaPresionada(QKeyEvent* event);

    void manejarTeclaLiberada(QKeyEvent* event);

    bool nivelCompletado() const;
    bool juegoTerminado() const;

private:

    SnowMan* jugador;

    std::vector<FireEnemy*> enemigos;

    std::vector<obstaculo*> plataformas;

    std::vector<premio*> premios;

    ZonaSegura* portal;

    bool completado;

    float camaraX;

    QPixmap fondoNivel;

    // METODOS

    void crearNivel();

    void verificarColisiones();

    void actualizarPortal();

};

#endif // NIVEL2_H
