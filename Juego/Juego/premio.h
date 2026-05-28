#ifndef PREMIO_H
#define PREMIO_H
#include "objetoJuego.h"
#include <QPainter>
#include <QRectF>
#include <QString>
#include <QPixmap>
using namespace std;
class premio : public ObjetoJuego
{
private:
    int puntos;
    QPixmap sprite;
    QString tipo;
public:
    premio(float x, float y,QString tipo, int puntos = 100);
    virtual ~premio();

    void actualizar(float deltaTime) override;

    void renderizar(QPainter* painter) override;

    int getPuntos() const;
    QString getTipo() const;
};

#endif // PREMIO_H

