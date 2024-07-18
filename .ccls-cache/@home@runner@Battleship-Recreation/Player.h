// prevent redefinition
#ifndef PLAYER_H
#define PLAYER_H

//include other libraries and classes
#include "Ship.h"
#include <iostream>
using namespace std;

class Player{
protected:
    char playBoard[10][10];
    char guessBoard[10][10];
    int shipsLeft;
    Ship* myShips[5];
    vector<point> guessedPoints;
    const static int totalShips = 5;
    const static char shipHit = 'O';
    const static char shipMiss = 'X';
    string name;

public:
    Player();

    void beginGame();
    void setUpShips(string currentShipName, int currentShipSize, int shipsPlaced);
    void updatePlayboard(Ship add);
    void updatePlayboard(point location, char newSymbol);
    void updateGuessboard(Ship add);
    void updateGuessboard(point location, char newSymbol);

    void guess(point guess, Player* opponent);
    bool checkOverlap(Ship check);

    void displayPlayBoard();
    void displayGuessBoard();

    int charToInt(char change);
    char intToChar(int change);

    void setShipsLeft(int set);
    int getShipsLeft();

    void setName(string set);
    string getName();

    vector<point> getGuessedPoints();
    void addGuessedPoints(point add);
    void updateGuessedPoints(Ship sunk);

    bool lost();

};


#endif //PLAYER_H
