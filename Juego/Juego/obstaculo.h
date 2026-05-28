#ifndef OBSTACULO_H
#define OBSTACULO_H
#include "objetoJuego.h"
#include <QPainter>
#include <QPixmap>
#include <string>
using namespace std;

class obstaculo : public ObjetoJuego
{
private:
    string tipo;
    QPixmap sprite;
public:
    obstaculo(float x, float y, int ancho, int alto, string tipo );
    virtual ~obstaculo();
    void actualizar(float deltaTime ) override;
    void renderizar(QPainter* painter) override;
    string getTipo() const;
};

#endif // OBSTACULO_H
