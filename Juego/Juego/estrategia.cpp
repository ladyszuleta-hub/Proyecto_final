#include "estrategia.h"
#include "fireenemy.h"
#include "snowman.h"

// PERSECUCION

void EstrategiaPersecucion::ejecutar(
    FireEnemy* enemigo,
    SnowMan* jugador)
{
    (void)jugador;

    enemigo->ejecutarAccion(
        TipoAccion::PERSEGUIR);
}

// ATAQUE

void EstrategiaAtaque::ejecutar(
    FireEnemy* enemigo,
    SnowMan* jugador)
{
    (void)jugador;

    enemigo->ejecutarAccion(
        TipoAccion::LANZAR_PROYECTIL);
}

// BLOQUEO

void EstrategiaBloqueo::ejecutar(
    FireEnemy* enemigo,
    SnowMan* jugador)
{
    (void)jugador;

    enemigo->ejecutarAccion(
        TipoAccion::BLOQUEAR_CAMINO);
}
