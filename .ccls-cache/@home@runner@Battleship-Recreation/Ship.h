// prevent redefinition
#ifndef SHIP_H
#define SHIP_H

// include libraries
#include "Point.h"
#include <iostream>
#include <vector>
using namespace std;

class Ship{
private:
    int size;
    char orientation;
    bool sunk;
    string shipType;
    char boardSymbol;
    vector<point> location;
public:
    Ship();
    Ship(vector<point> location, char orient, string name, int size);
    void setSunk(bool condition);
    bool getSunk();
    int getSize();
    vector<point> getLocation();
    char getOrientation();
    char getBoardSymbol();
    void setBoardSymbol(char set);
    bool hit(point locationToCheck);
    string getShipType();
};

#endif //SHIP_H
