#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H

#include "red.h"
#include<vector>

class Red;

class Neighborhood {
    unsigned int* neighbours; //tableau d'entier : la case d'indice x contiendra le nombre de voisins de la cellule à l'état d'indice x

    Neighborhood(const Neighborhood& v);

public:
    Neighborhood(unsigned int nb=2);
    ~Neighborhood();

    void VonNeuman(int i, int j, const Red &r);
    void DeMoore(int i, int j, const Red &r);

    unsigned int getNeighbours(unsigned int i=0)const {return neighbours[i];};
};

#endif // NEIGHBORHOOD_H
