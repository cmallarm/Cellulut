#include "red.h"

#include<iostream>
#include "neighborhood.h"
#include "red.h"
#include "state.h"
#include <math.h>
#include <algorithm>
#include <fstream>

using namespace std;

Red::Red(unsigned int w, unsigned int h, unsigned int nb) : height(h), width(w), nbStates(nb),matrice(nullptr), transition(nullptr){
    if (w > 0 && h > 0) {
        matrice = new State * [w];
        for (int i=0; i<h; ++i) {
            matrice[i] = new State [h];
        }
        transition = new State * [w];
        for (int i=0; i<h; ++i) {
            transition[i] = new State [h];
        }
    }


}

Red::~Red() {
    for( int i=0; i<height; i++){
        delete[] matrice[i];
        delete[] transition[i];
    }
    delete[] matrice;
    delete[] transition;
}


LifeGame::LifeGame(unsigned int l, unsigned int h, unsigned int a) : Red::Red(l,h,2), alive(State(1, "Vivante", "Blanc")), dead(State(0, "Morte", "Noir")), alea(a){
    for( int i=0; i<l; i++){
        for( int j=0; j<h;j++){
            if(rand()%100 >=alea){
                this->setMatrice(i,j,dead);
            }else{
                this->setMatrice(i,j,alive);
            }
        }
    }
    cout<<*this;
}

void LifeGame::next(){
    int i,j =0;
    Neighborhood v(2);
    for(i=0; i<this->getHeight(); i++){ //colonne
        for(j=0; j<this->getWidth();j++){ //ligne

            //Calcule du voisinnage
            v.DeMoore(i,j,*this);

            //Fonction de transition
            if(getMatrice(i,j).getIndex()==0 && v.getNeighbours(1)==3){
                        setTransition(i,j,getAlive());
                }else if(getMatrice(i,j).getIndex()==1 && (v.getNeighbours(1)<2 || v.getNeighbours(1)>3)){
                        setTransition(i,j,getDead());
                }
                else{
                    setTransition(i,j,getMatrice(i,j));
                }

            }
    }
            cout << "\n";
            cout << "\n";

        //Mise à jour de la nouvelle configuration
        for( i=0; i<getHeight(); i++){
            for( j=0; j<getWidth();j++){
                setMatrice(i,j,getTransition(i,j));
            }
        }

        //Affichage
        cout << *this;


}

ostream& operator<<(ostream& f , const Red &red) {
    int i,j;
    for( i=0; i<red.getHeight(); i++){
        for( j=0; j<red.getWidth();j++){
            f<< (red.getMatrice(i,j)).getIndex();
        }
        f << "\n";
    }
    return f;
}
