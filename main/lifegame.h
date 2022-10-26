#ifndef LIFEGAME_H
#define LIFEGAME_H

#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>

#include "red.h"
#include "simulator.h"

class WindowLG : public QWidget {

    Q_OBJECT

    QSpinBox* alea;
    QLabel* aleaLabel;
    QSlider* aleaSlide;

    QSpinBox* speedBox;
    QLabel* speedLabel;

    int dimension;

    QVBoxLayout* param;
    QHBoxLayout* buttons;
    QVBoxLayout* mainLayout;

    QTableWidget* states;

    QPushButton* simulationButton;
    QPushButton* modeAutoButton;
    QPushButton* stopButton;
    QPushButton* newButton;
    QPushButton* previousButton;
    QPushButton* resetButton;

    LifeGame* grid;
    Simulator<LifeGame>* sim;
    int init;
    int speed;

    void showGrid(const LifeGame &R);


public:
    explicit WindowLG(QWidget* parent = nullptr, int dim = 10, int vit = 2000);
    ~WindowLG();

private slots:
    void simulate();
    void maj_alea();
    void maj_speed();
    void stop();
    void modeAuto();
    void reset();
    void news();
    void previous();
    void nextState(const QModelIndex&);


};

#endif // LIFEGAME_H

