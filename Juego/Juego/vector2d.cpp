#include "Vector2D.h"
#include <cmath>

// Constructor
Vector2D::Vector2D(float x, float y) {
    this->x = x;
    this->y = y;
}

// Getters
float Vector2D::getX() const {
    return x;
}

float Vector2D::getY() const {
    return y;
}

// Setters
void Vector2D::setX(float x) {
    this->x = x;
}

void Vector2D::setY(float y) {
    this->y = y;
}

// Movimiento
void Vector2D::mover(float dx, float dy) {
    x += dx;
    y += dy;
}

// Distancia
float Vector2D::distancia(const Vector2D& otro) const {
    return sqrt(pow(otro.x - x, 2) + pow(otro.y - y, 2));
}
