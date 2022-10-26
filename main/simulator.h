#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "red.h"

template<class T> class Simulator {
    T& automate;
    State*** tab_configs;
    int count;
    int nbHistory;
    State** start;

public:
    Simulator(T& a);
    ~Simulator();

    State** getConfig(int i=0);
    State getStart(int i=0, int j=0);

    void reset();
    void next();
    void back();
};

template<class T> Simulator<T>::Simulator(T &a): automate(a), tab_configs(nullptr), count(0), start(nullptr), nbHistory(1){
    tab_configs = new State**[12];
    for (int i=0; i<12; ++i) {
        tab_configs[i] = new State * [automate.getWidth()];
        for (int j=0; j<automate.getHeight(); ++j) {
            tab_configs[i][j] = new State [automate.getHeight()];
        }
    }

    start = new State * [automate.getWidth()];
    for (int i=0; i<automate.getHeight(); ++i) {
        start[i] = new State [automate.getHeight()];
    }

    for( int i=0; i<automate.getHeight(); i++){
        for( int j=0; j<automate.getWidth();j++){
            tab_configs[0][i][j]= automate.getMatrice(i,j);
            start[i][j]=automate.getMatrice(i,j);
        }
    }
}

template<class T> Simulator<T>::~Simulator(){
    for( int i=0; i<automate.getHeight(); i++){
        delete[] start[i];
    }
    delete[] start;

    for (int i=0; i<12; ++i) {
        for (int j=0; j<automate.getHeight(); ++j) {
            delete[] tab_configs[i][j];
        }
    }
    for (int i=0; i<12; ++i) {
        delete[] tab_configs[i];
    }
    delete[] tab_configs;
}

template<class T> State** Simulator<T>:: getConfig(int i){
    if(tab_configs[i]!=nullptr) return tab_configs[i];
}
template<class T> State Simulator<T>::getStart(int i, int j){
    return start[i][j];
}

template<class T> void Simulator<T>::reset(){
    count=0;
    nbHistory=1;
    for( int i=0; i<automate.getHeight(); i++){
        for( int j=0; j<automate.getWidth();j++){
            automate.setMatrice(i,j,start[i][j]);
            tab_configs[0][i][j]= automate.getMatrice(i,j);
        }
    }
}

template<class T> void Simulator<T>::next(){
    automate.next();
    count++;
    if(nbHistory<13){
        nbHistory=nbHistory+1;
    }


    State** tmp= tab_configs[count%12];
    for( int i=0; i<automate.getHeight(); i++){
        for( int j=0; j<automate.getWidth();j++){
            tmp[i][j]= automate.getMatrice(i,j);
        }
    }

}

template<class T> void Simulator<T>::back(){
    if(nbHistory>2){
        State** tmp= tab_configs[(count-1)%12];
        for( int i=0; i<automate.getHeight(); i++){
            for( int j=0; j<automate.getWidth();j++){
                automate.setMatrice(i,j,tmp[i][j]);
            }
        }
        nbHistory--;
        count--;
    }
}

#endif // SIMULATOR_H
