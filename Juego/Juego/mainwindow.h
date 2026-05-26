#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include "nivel1.h"
#include "fireenemy.h"
#include "snowman.h"

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

private:

    Ui::MainWindow *ui;
    QPixmap fondoActual;
    QTimer* timer;
    Nivel1* nivel1;
    bool juegoIniciado;


    float dt;
};

#endif // MAINWINDOW_H

