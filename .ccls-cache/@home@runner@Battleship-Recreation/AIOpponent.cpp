// include header file
#include "AIOpponent.h"
// include libraries
#include <fstream>

void AIOpponent::setUpShips(bool *success, string fileName) {
    // need to separate things by comma and have a file stream
    ifstream input;
    input.open(fileName);
    char breakChar1 = ',', breakChar2 = '\n';
    int inNum = 0, shipSize, x, y, shipsPlaced = 0, lineNum = 0;
    char tempX;
    bool overlap;
    string holderS, shipName, tempY;
    vector<point> shipLocation;
    point currentLocation;
    Ship* testShip;

    while(*success && !input.eof()){
        shipLocation.clear();
        testShip = nullptr;
        tempY.clear();
        if(inNum != 2){
            getline(input, holderS, breakChar1);
        }
        else{
            getline(input, holderS, breakChar2);
        }
        cout << holderS << endl;
        switch(inNum){
            case 0:
                shipName = holderS;
                if (holderS == "Carrier"){
                    shipSize = 5;
                }
                else if (holderS == "Battleship"){
                    shipSize = 4;
                }
                else if (holderS == "Cruiser"){
                    shipSize = 3;
                }
                else if (holderS == "Submarine"){
                    shipSize = 3;
                }
                else if (holderS == "Destroyer"){
                    shipSize = 2;
                }
                inNum++;
                break;
            case 1:
                try {
                    tempX = holderS[0];
                    for (int holdY = 1; holderS[holdY] != '\0'; holdY++)
                        tempY += holderS[holdY];
                    x = charToInt(tempX);
                    y = stoi(tempY);
                    if(y > 10 || y <= 0)
                        throw y;
                    inNum++;
                    cout << shipName << " is being placed at " << x << ", " << y << endl;
                }
                catch(int big){
                    cout << shipName << " is not able to be placed at " << tempX << "," << y <<" because it extends off the board.\n";
                    *success = false;
                    break;
                }
                break;
            case 2:
                try {
                    if (holderS[0] == 'v' || holderS[0] == 'V') {
                        if ((10 - (y - 1)) < shipSize) {
                            cout << shipName << " is not able to be placed at " << tempX << y <<" because it extends off the board.\n";
                            *success = false;
                            break;
                        } else {
                            for (int place = 0; place < shipSize; place++) {
                                currentLocation.x = (x - 1);
                                currentLocation.y = (y - 1) + place;
                                shipLocation.push_back(currentLocation);
                            }
                        }
                    }
                    if (holderS[0] == 'h' || holderS[0] == 'H') {
                        if ((10 - (x - 1)) < shipSize) {
                            cout << shipName << " is not able to be placed at " << tempX << y <<" because it extends off the board.\n";
                            *success = false;
                            break;
                        } else {
                            // do the vector thing here and set up the ship
                            for (int place = 0; place < shipSize; place++) {
                                currentLocation.x = (x - 1) + place;
                                currentLocation.y = (y - 1);
                                shipLocation.push_back(currentLocation);
                            }
                        }
                    }
                    testShip = new Ship(shipLocation, holderS[0], shipName, shipSize);
                    overlap = checkOverlap(*testShip);
                    if(overlap){
                        throw(overlap);
                    }
                    else{
                        myShips[shipsPlaced] = testShip;
                        updatePlayboard(*testShip);
                        shipsPlaced++;
                    }
                    inNum = 0;
                }
                catch(bool overlap){
                    *success = false;
                    break;
                }
                break;
        }
        if(*success){
            lineNum++;
        }
    }
    input.close();
    /*
    if(lineNum < 4){
        *success = false;
    }
    else{
        *success = true;
    }
    */
}