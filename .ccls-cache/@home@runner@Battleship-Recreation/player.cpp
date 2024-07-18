#include <iostream>
#include <string>
#include <vector>
#include "point.cpp"
#include "ship.cpp"
using namespace std;

class Player {
  private:
    char playBoard[10][10] = {};
    char guessBoard[10][10] = {};
    int shipsLeft;
    Ship myShips[5];
    vector<Point> guessedPoints;
    string name;
    const int totalShips = 5;
    const char shipHit = 'O';
    const char shipMiss = 'X';

  public:
    Player();
    // explains the rules and helps set up ships
    void beginGame(){
      cout << "Welcome to Battleship!" << endl;
    }
    void setUpShips(string currentShipName, int currentShipSize, int shipsPlaced);
    void updatePlayboard(Ship add);
    void updatePlayboard(Point location, char newSymbol);
    
    void updateGuessboard(Ship add);
    void updateGuessboard(Point location, char newSymbol);
    
    void guess(Point guess, Player opponent);
    
    bool checkOverlap(Ship check);
    
    void displayPlayBoard();
    void displayGuessBoard();
    
    int charToInt(char change);
    char intToChar(int change);
    
    void setShipsLeft(int set);
    int getShipsLeft();

    void setName(string set);
    string getName();

    vector<Point> getGuessedPoints();
    void addGuessedPoints(Point add);
    void updateGuessedPoints(Ship sunk);

    bool lost();
};