#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include "nivel1.h"
#include "fireenemy.h"
#include "snowman.h"
#include "nivel2.h"
enum EstadoMenu
{
    MENU_PRINCIPAL,
    MENU_NIVELES,
    MENU_DIFICULTAD,
    JUGANDO,
    GAME_OVER
};

enum Dificultad
{
    FACIL,
    NORMAL,
    DIFICIL
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

protected:


    void paintEvent(QPaintEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;
    void mostrarGameOver();
    void volverMenuPrincipal();

private:

    Ui::MainWindow *ui;
    QPixmap fondoActual;
    QPixmap fondoMenuPrincipal;
    QPixmap fondoMenuNiveles;
    QPixmap fondoMenuDificultad;
    QPixmap fondoGameOver;
    QTimer* timer;
    Nivel1* nivel1;
    bool juegoIniciado;
    Nivel2* nivel2;
    EstadoMenu estadoMenu;

    int nivelSeleccionado;
    Dificultad dificultadSeleccionada;
    bool nivel2Desbloqueado;
    void volverMenuNiveles();

    bool mostrandoVictoria;

    QPixmap imagenVictoria;

    QTimer* timerVictoria;

    float dt;
};

#endif // MAINWINDOW_H

