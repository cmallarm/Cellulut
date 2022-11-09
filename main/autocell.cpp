#include "autocell.h"
#include "lifegame.h"
#include <QHeaderView>

AutoCell::AutoCell(QWidget* parent, int dim) : QWidget(parent), dimension(dim) {

    mainLayout = new QVBoxLayout;
    lifeGameButton = new QPushButton("Life Game", this);

    dim_ = new QSpinBox;
    dim_->setRange(0, 100);
    dim_->setValue(50);

    dim_l = new QLabel("Dimension de la grille");

    dimChoice = new QVBoxLayout;
    dimChoice->addWidget(dim_);
    dimChoice->addWidget(dim_l);

    mainLayout->addLayout(dimChoice);
    mainLayout->addWidget(dim_l);
    mainLayout->addWidget(lifeGameButton);

    this->setLayout(mainLayout);

    connect(lifeGameButton, SIGNAL(clicked()), this, SLOT(setLifeGame()));
}

void AutoCell::setLifeGame(){
    int dimension = dim_->value();
    WindowLG *window = new WindowLG(nullptr, dimension);
    window->setWindowTitle("Life Game");
    window->show();

}
