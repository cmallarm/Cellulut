#include "neighborhood.h"

using namespace std;


Neighborhood::Neighborhood(unsigned int nb) {
    neighbours = new unsigned int[nb];

    for (unsigned int i = 0; i < nb; i++) {
        neighbours[i]=0;
    }
};

void Neighborhood::VonNeuman(int i, int j, const Red &r){
    neighbours[0]=0;
    neighbours[1]=0;

    int J=j-1, I=i-1, indice;
    if(J<0){
        J=r.getWidth()-1;
    }if(I<0){
        I=r.getHeight()-1;
    }
    indice= r.getMatrice(i,(j+1)%r.getWidth()).getIndex();
    neighbours[indice]++;
    indice= r.getMatrice((i+1)%r.getHeight(),j).getIndex();
    neighbours[indice]++;
    indice= r.getMatrice(i,J%r.getWidth()).getIndex();
    neighbours[indice]++;
    indice= r.getMatrice(I%r.getHeight(),j).getIndex();
    neighbours[indice]++;
}

void Neighborhood::DeMoore(int i, int j, const Red &r){
    neighbours[0]=0;
    neighbours[1]=0;

    int J=j-1, I=i-1, indice;
    if(J<0){
        J=r.getWidth()-1;
    }if(I<0){
        I=r.getHeight()-1;
    }
    indice= r.getMatrice(i,(j+1)%r.getWidth()).getIndex();
    neighbours[indice]++;
    indice= r.getMatrice((i+1)%r.getHeight(),j).getIndex();
    neighbours[indice]++;
    indice= r.getMatrice(i,J%r.getWidth()).getIndex();
    neighbours[indice]++;
    indice= r.getMatrice(I%r.getHeight(),j).getIndex();
    neighbours[indice]++;
    indice= r.getMatrice((i+1)%r.getHeight(),(j+1)%r.getWidth()).getIndex();
    neighbours[indice]++;
    indice= r.getMatrice(I%r.getHeight(),J%r.getWidth()).getIndex();
    neighbours[indice]++;
    indice= r.getMatrice(I%r.getHeight(),(j+1)%r.getWidth()).getIndex();
    neighbours[indice]++;
    indice= r.getMatrice((i+1)%r.getHeight(),J%r.getWidth()).getIndex();
    neighbours[indice]++;
}

Neighborhood::~Neighborhood(){
    delete[] neighbours;
}
