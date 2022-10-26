#ifndef RED_H
#define RED_H

#include "state.h"
#include <vector>

class Red {
    unsigned int height;
    unsigned int width;
    unsigned int nbStates;
    State** matrice;
    State** transition;

public:
    Red(unsigned int h = 10, unsigned int w = 10, unsigned int nb = 2);

    unsigned int getHeight()const { return height; };
    unsigned int getWidth()const { return width; };
    State getMatrice(int i, int j)const { return matrice[i][j]; };
    void setMatrice(int i, int j, State e) { matrice[i][j]=e; };
    State getTransition(int i, int j)const { return transition[i][j]; };
    void setTransition(int i, int j, State e) { transition[i][j]=e; };
    ~Red();
};

ostream& operator<<(ostream& f , const Red &red);


class LifeGame : public Red{
    State alive;
    State dead;
    unsigned int alea;

public:
    LifeGame(unsigned int l = 10, unsigned int h = 10, unsigned int a = 50);

    State getAlive()const { return alive; };
    State getDead()const { return dead; };
    unsigned int getAlea()const { return alea; };

    void setAlea(unsigned int a) { if(a<=100) alea=a; };

    void next(); //Faire virtual pour les transitions ?
};

#endif // RED_H
