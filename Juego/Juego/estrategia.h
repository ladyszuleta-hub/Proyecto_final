#ifndef ESTRATEGIAS_H
#define ESTRATEGIAS_H

class FireEnemy;
class SnowMan;

class Estrategia
{
public:

    virtual ~Estrategia() = default;

    virtual void ejecutar(
        FireEnemy* enemigo,
        SnowMan* jugador) = 0;
};


// PERSECUCION

class EstrategiaPersecucion : public Estrategia
{
public:

    void ejecutar(
        FireEnemy* enemigo,
        SnowMan* jugador) override;
};

// ATAQUE

class EstrategiaAtaque : public Estrategia
{
public:

    void ejecutar(
        FireEnemy* enemigo,
        SnowMan* jugador) override;
};

// BLOQUEO

class EstrategiaBloqueo : public Estrategia
{
public:

    void ejecutar(
        FireEnemy* enemigo,
        SnowMan* jugador) override;
};

#endif // ESTRATEGIAS_H
