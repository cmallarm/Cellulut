#ifndef STATE_H
#define STATE_H

#include <string>
#include <iostream>

using namespace std;

class State{
    unsigned int index;
    string name;
    string color;

public:
    State(unsigned int i=0, string l="", string c="");

    unsigned int getIndex() const {return index;}
    string getName() const {return name;}
    string getColor() const {return color;}

};

#endif // STATE_H
