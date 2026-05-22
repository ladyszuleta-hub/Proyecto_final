#ifndef PREMIO_H
#define PREMIO_H
#include "objetoJuego.h"

class premio : public ObjetoJuego
{
private:
    int puntos;
public:
    premio(float x,float y,int puntos = 100);
    virtual ~premio();

    void actualizar(float deltaTime) override;

    void renderizar() override;

    int getPuntos() const;
};

#endif // PREMIO_H

