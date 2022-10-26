#include "lifegame.h"
#include "red.h"
#include <QHeaderView>

WindowLG::WindowLG(QWidget* parent, int dim, int sp) : QWidget(parent), dimension(dim), grid(nullptr), init(0), speed(sp){

    // --- Déclaration du mainLayout (vertical)

    mainLayout = new QVBoxLayout;

    // --- Ajout de la première colonne avec aleal et alea et la vitesse de lecture

    alea = new QSpinBox;
    alea->setRange(0, 100);
    alea->setValue(50);

    aleaSlide = new QSlider(Qt::Horizontal);
    aleaSlide->setRange(0,100);
    aleaSlide->setValue(50);

    aleaLabel = new QLabel("% de Vie :");

    speedBox = new QSpinBox;
    speedBox->setRange(1, 60);
    speedBox->setValue(2);

    speedLabel = new QLabel("Vitesse de lecture :");
    param = new QVBoxLayout;
    param->addWidget(aleaLabel);
    param->addWidget(alea);
    param->addWidget(aleaSlide);
    param->addWidget(speedLabel);
    param->addWidget(speedBox);


    // -- Ajout des buttons

    simulationButton = new QPushButton("Suivant");
    simulationButton->setAutoRepeatDelay(speed/2);
    simulationButton->setAutoRepeatInterval(speed);
    simulationButton->setAutoRepeat(true);

    modeAutoButton = new QPushButton("Simulation");
    stopButton = new QPushButton("Arrêter");

    resetButton = new QPushButton("Remise à zéro");
    resetButton->setVisible(false);

    newButton = new QPushButton("Recommencer");
    newButton->setVisible(false);

    previousButton = new QPushButton("Retour");
    previousButton->setVisible(false);


    buttons = new QHBoxLayout;
    buttons->addWidget(simulationButton);
    buttons->addWidget(modeAutoButton);
    buttons->addWidget(stopButton);


    // --- Ajout de la grid d'états simulés

    states = new QTableWidget(dimension, dimension);
    states->horizontalHeader()->setVisible(false);
    states->verticalHeader()->setVisible(false);
    states->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    states->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    states->setFixedHeight(dimension*10);
    states->setFixedWidth(dimension*10);
    states->horizontalHeader()->setMinimumSectionSize(10);
    states->verticalHeader()->setMinimumSectionSize(10);

    for (int i = 0; i < dimension; i++) {
        states->setRowHeight(i, 10);
        states->setColumnWidth(i, 10);

        for (int j = 0; j < dimension; j++) {
            QTableWidgetItem* cell = new QTableWidgetItem;
            states->setItem(i, j, cell);
            cell->setBackground(Qt::white);
            cell->setForeground(Qt::white);
            cell->setText("");
            cell->setFlags(Qt::ItemIsEditable);
        }
    }

    // --- Affectation à "soi-même" du layout principal

    mainLayout->addLayout(param);
    mainLayout->addLayout(buttons);
    mainLayout->addWidget(previousButton);
    mainLayout->addWidget(resetButton);
    mainLayout->addWidget(newButton);
    mainLayout->addWidget(states);

    this->setLayout(mainLayout);

    // --- Mise en place des connexions

    connect(alea, SIGNAL(valueChanged(int)), aleaSlide, SLOT(setValue(int)));
    connect(aleaSlide, SIGNAL(valueChanged(int)), alea, SLOT(setValue(int)));

    connect(speedBox, SIGNAL(valueChanged(int)), this, SLOT(maj_vit()));

    connect(simulationButton, SIGNAL(clicked()), this, SLOT(simulate()));
    connect(aleaSlide, SIGNAL(valueChanged(int)), this, SLOT(maj_alea()));

    connect(stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    connect(modeAutoButton, SIGNAL(clicked()), this, SLOT(modeAuto()));
    connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));
    connect(previousButton, SIGNAL(clicked()), this, SLOT(back()));
    connect(newButton, SIGNAL(clicked()), this, SLOT(news()));

    connect(states, SIGNAL(clicked(const QModelIndex&)), this, SLOT(nextState(const QModelIndex&)));

}

void WindowLG::showGrid(const LifeGame &R){
    for(int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            QTableWidgetItem* cell = states->item(i, j);

            if (R.getMatrice(i,j).getIndex() == 0) {
                cell->setForeground(Qt::black);
                cell->setBackground(Qt::black);
                cell->setText("1");
            } else {
                cell->setForeground(Qt::white);
                cell->setBackground(Qt::white);
                cell->setText("");
            }
        }

    }
}

void WindowLG::simulate() {
    if(init==0){
        //Création de la grid
        grid = new LifeGame(dimension,dimension,alea->value());
        sim = new Simulator(*grid);
        init=1;
        resetButton->setVisible(true);
        newButton->setVisible(true);
        previousButton->setVisible(true);
    }else{
        resetButton->setVisible(true);
        newButton->setVisible(true);
        previousButton->setVisible(true);

        sim->next();
    }
    showGrid(*grid);
}

void WindowLG::maj_alea() {
    //Création de la grid
    delete grid;
    grid = new LifeGame(dimension,dimension,alea->value());
    delete sim;
    sim = new Simulator(*grid);
    showGrid(*grid);
}

void WindowLG::maj_speed() {
    speed=speedBox->value()*100;
    simulationButton->setAutoRepeatDelay(speed);
    simulationButton->setAutoRepeatInterval(speed);
}

void WindowLG::stop() {
    simulationButton->setDown(false);
    simulationButton->setVisible(true);
}

void WindowLG::modeAuto(){
    simulationButton->setDown(true);
    simulationButton->setVisible(false);
}


void WindowLG::reset(){
    sim->reset();
    showGrid(*grid);
}

void WindowLG::news(){
    //Création de la grid
    delete grid;
    grid = new LifeGame(dimension,dimension,alea->value());
    delete sim;
    sim = new Simulator(*grid);
    showGrid(*grid);
}

void WindowLG::previous(){
    sim->back();
    showGrid(*grid);
}

void WindowLG::nextState(const QModelIndex& i){
        QTableWidgetItem* cell = states->item(i.row(), i.column());

        if (cell->text() == "") {
            cell->setForeground(Qt::black);
            cell->setBackground(Qt::black);
            cell->setText("1");
        } else {
            cell->setForeground(Qt::white);
            cell->setBackground(Qt::white);
            cell->setText("");
        }

        //Création de la grid
        grid = new LifeGame(dimension,dimension,alea->value());
        sim = new Simulator(*grid);
        init=1;
        resetButton->setVisible(true);
        newButton->setVisible(true);
        previousButton->setVisible(true);

        for(int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                QTableWidgetItem* cell = states->item(i, j);

                if (cell->background()== Qt::white) {
                    grid->setMatrice(i,j, grid->getAlive());
                } else {
                    grid->setMatrice(i, j, grid->getDead());
                }
            }

        }
        delete sim;
        sim = new Simulator(*grid);

        showGrid(*grid);

        init=1;
}

WindowLG::~WindowLG() {
    delete grid;
    delete sim;
}
