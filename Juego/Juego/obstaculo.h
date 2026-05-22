#ifndef OBSTACULO_H
#define OBSTACULO_H
#include "objetoJuego.h"
#include <string>
using namespace std;

class obstaculo : public ObjetoJuego
{
private:
    string tipo;
public:
    obstaculo(float x, float y, float ancho, float alto, string tipo );
    virtual ~obstaculo();
    void actualizar(float deltaTime ) override;
    void renderizar() override;
    string getTipo() const;
};

#endif // OBSTACULO_H
