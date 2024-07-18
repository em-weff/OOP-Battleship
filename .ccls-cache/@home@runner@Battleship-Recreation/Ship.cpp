// include header file
#include "Ship.h"

//default constructor
Ship::Ship(){
    shipType = "Generic Ship";
    orientation = 'v';
    sunk = false;
    boardSymbol = '-'; // to represent nothing's there
    size = 1;
}


Ship::Ship(vector<point> location, char orient, string name, int size){
    shipType = name;
    bool orientated = false;
    if(orient == 'h' || orient == 'H' || orient == 'v' || orient == 'V'){
        orientation = orient;
        orientated = true;
    }
    else{
        while(orientated == false){
            cout << "The value you entered for your " << shipType << "'s orientation was invalid. Please enter either h "
                    "(for horizontal orientation) or v (for vertical orientation):\n";
            cin >> orient;
            if(orient == 'h' || orient == 'v'){
                orientation = orient;
                orientated = true;
            }
        }
    }
    sunk = false;
    boardSymbol = shipType[0]; // S for ship
    for(int i = 0; i < size; i++){
        this->location.push_back(location[i]);
    }
    this->size = size;
}

bool Ship::getSunk() {
    return sunk;
}

void Ship::setSunk(bool condition) {
    sunk = condition;
}

int Ship::getSize() {
    return size;
}

vector<point> Ship::getLocation() {
    return location;
}

char Ship::getOrientation() {
    return orientation;
}

char Ship::getBoardSymbol() {
    return boardSymbol;
}

void Ship::setBoardSymbol(char set){
    boardSymbol = set;
}

bool Ship::hit(point locationToCheck) {
    for (int i = 0; i < size; i++){
        if(location[i].x == locationToCheck.x){
            if(location[i].y == locationToCheck.y){
                return true;
            }
        }
    }
    return false;
}

string Ship::getShipType() {
    return shipType;
}