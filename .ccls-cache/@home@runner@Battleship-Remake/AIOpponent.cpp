// include header file
#include "AIOpponent.h"
// include libraries
#include <fstream>

// if at any point the AI is unable to place a ship, the bool success is set to false
// this is reflected in main.cpp, where the function is called, and will end the program
void AIOpponent::setUpShips(bool *success) {
    for(int i = 0; i < totalShips; i++){
        placeShip(availShips[i]->getShipType(), availShips[i]->getSize(), i);
    }
}

void AIOpponent::placeShip(string currentShipName, int currentShipSize, int shipsPlaced){
    string coordinates, tempY;
    char tempX, orientation;
    int x, y;
    bool oriented, positioned, overlap = true;
    vector<point> hold;
    point currentLocation;
    Ship* testShip;

    while(overlap) {
        hold.clear();
        testShip = nullptr;
        oriented = false;
        positioned = false;
        tempY.clear();

        while (!oriented) {
            cout << "How would you like your ship to be oriented? Please enter v for vertical or h for horizontal:\n";
            cin >> orientation;
            cin.ignore();
            if(orientation == '\n') {
                cout << "You can't enter nothing.\n";
                continue;
            }
            switch (orientation) {
                case 'v':
                case 'V':
                    cout << "Your ship is oriented vertically.\n";
                    orientation = 'v';
                    oriented = true;
                    break;
                case 'h':
                case 'H':
                    cout << "Your ship is oriented horizontally.\n";
                    orientation = 'h';
                    oriented = true;
                    break;
                default:
                    cout << "The value you entered is not a valid option. Please be sure to only enter v or h.\n";
                    break;
            }
        }

        while (!positioned) {
            tempY.clear();
            cout << "Where would you like to place your ship?\n";
            cin >> coordinates;
            if(coordinates[0] == '\n') {
                cout << "You can't enter nothing.\n";
                continue;
            }
            try {
                tempX = coordinates[0];
                for (int holdY = 1; coordinates[holdY] != '\0'; holdY++)
                    tempY += coordinates[holdY];
                x = charToInt(tempX);
                if(!isdigit(tempY[0])){
                    cout << "Please be sure you are entering your coordinates LetterNumber (ex. A1) and not NumberLetter (ex. 2D).\n";
                    continue;
                }
                y = stoi(tempY);
                if(y > 10 || y <= 0)
                    throw y;
                else if(x > 10 || x <= 0)
                    throw x;
            }
            catch(int big){
                cout << currentShipName << " is not able to be placed at " << tempX << y <<" because it extends off the board.\n";
                continue;
            }
            if (orientation == 'v') {
                if ((10 - (y - 1)) < currentShipSize) {
                    cout << "There is not enough room to place your ship here.\n";
                    tempY.clear();
                }
                else {
                    for (int place = 0; place < currentShipSize; place++) {
                        currentLocation.x = (x - 1);
                        currentLocation.y = (y - 1) + place;
                        hold.push_back(currentLocation);
                    }
                    positioned = true;
                }
            }
            if (orientation == 'h') {
                if ((10 - (x - 1)) < currentShipSize) {
                    cout << "There is not enough room to place your ship here.\n";
                    tempY.clear();
                }
                else {
                    // do the vector thing here and set up the ship
                    for (int place = 0; place < currentShipSize; place++) {
                        currentLocation.x = (x - 1) + place;
                        currentLocation.y = (y - 1);
                        hold.push_back(currentLocation);
                    }
                    positioned = true;
                }
            }
        }
        testShip = new Ship(hold, orientation, currentShipName, currentShipSize);
        overlap = checkOverlap(*testShip);
        if(overlap){
            cout << "You will need to pick a new location for this ship.\n";
        }
    }
    myShips[shipsPlaced] = testShip;
    updatePlayboard(*testShip);
    displayPlayBoard();
}