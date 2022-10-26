#ifndef AUTOCELL_H
#define AUTOCELL_H

#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>

class AutoCell : public QWidget {
    Q_OBJECT

    int dimension;

    QSpinBox* dim_;
    QLabel* dim_l;

    QVBoxLayout* dimChoice;

    QVBoxLayout* mainLayout;
    QHBoxLayout* second;

    QTableWidget* states;
    QPushButton* simulation;


    int init;

    QPushButton* lifeGameButton;


public:
    explicit AutoCell(QWidget* parent = nullptr, int dim = 30);

private slots:
    void setLifeGame();
};

#endif // AUTOCELL_H
