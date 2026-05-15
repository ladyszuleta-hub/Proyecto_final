#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D {
private:
    float x;
    float y;

public:
    // Constructor
    Vector2D(float x = 0, float y = 0);

    // Getters
    float getX() const;
    float getY() const;

    // Setters
    void setX(float x);
    void setY(float y);

    // Movimiento
    void mover(float dx, float dy);

    // Distancia entre vectores
    float distancia(const Vector2D& otro) const;
};

#endif
