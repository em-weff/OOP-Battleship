// include header file
#include "Player.h"
// include libraries
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctype.h>
using namespace std;


Player::Player() {
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            playBoard[i][j] = '-';
            guessBoard[i][j] = '-';
        }
    }
    shipsLeft = totalShips;
    for(int i = 0; i < shipsLeft; i++){
        myShips[i] = nullptr;
    }
}

void Player::beginGame() {
    cout << "To begin the game, you must first place your ships on your gameboard. The gameboard is a 10x10 grid, labeled "
            "with letters to represent the columns and numbers to represent the rows. There is an example shown below:\n\n";
    displayGuessBoard();
    cout << "The dashes represent empty spaces on the board, while ships will appear on the board as the first letter in\n"
            "their name. Be warned, however, as the Carrier and the Cruiser both have names that begin with C. The Carrier\n"
            "is larger than the Cruiser, however. Each ship has a different size, and each player receives "<< totalShips << " ships. You will\n"
            "be playing against our computer. You will get to place your ships, choosing the first space in which they are\n"
            "placed, as well as the orientation. The place you choose will be the top of the ship if you choose a vertical\n"
            "orientation, and the left side of the ship if you choose a horizontal position. More specific instructions will\n"
            "be given when we start placing the ships. Once the ships are placed, you and the AI will take turns guessing\n"
            "each other's ships are hidden. You will have a board on which your guesses are displayed, and another board on\n"
            "which your ships are displayed. In this version of the game, ships are sunk after one hit. Sunk ships will be\n"
            "displayed with O's in place of their letters, and misses will be displayed by X's. You will be able to see the\n"
            "AI's guesses on the board displaying your ships, and your own guesses on your guess board. The first player to\n"
            "sink all of the other player's ships will win the game. In addition, when you are asked to make a guess, you\n"
            "can quit the game at any time by entering Q in place of a set of coordinates. Now, let's get into setting up\n"
            "your ships. You have "<< totalShips <<" ships that all vary in size. Ships include the Carrier, which occupies 5 spaces; the\n"
            "Battleship, which occupies 4 spaces; the Cruiser, which occupies 3 spaces; the Submarine, which also occupies\n"
            "3 spaces; and the Destroyer, which occupies two spaces. To choose the space you want to place your ship in,\n"
            "you'll need to enter a letter-number coordinate set that corresponds with a spot in the grid. For example,\n"
            "A1 or H8. Keep in mind, that your ships cannot overlap or extend outside of the board's area. Ready? Let's set\n"
            "up your ships.\n\n";
    setUpShips("Carrier", 5, 0);
    setUpShips("Battleship", 4, 1);
    setUpShips("Cruiser", 3, 2);
    setUpShips("Submarine", 3, 3);
    setUpShips("Destroyer", 2, 4);
    cin.ignore();

}

void Player::setUpShips(string currentShipName, int currentShipSize, int shipsPlaced) {
    // we need to tell players which ship they're placing then ask where they would like to place the tip of it, explaining
    // how the ship will be oriented
    // we can then put locations in the locations vector and check for overlap, asking the player to please enter another
    // spot if it collides and informing them which ship it collides with, otherwise we just set up the ship object and
    // put it where it needs to be
    string coordinates, tempY;
    char tempX, orientation;
    int x, y;
    bool oriented, positioned, overlap = true;
    vector<point> hold;
    point currentLocation;
    Ship* testShip;

    cout << "Let's place the " << currentShipName << ", which takes up " << currentShipSize << " spaces.\n";

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

bool Player::checkOverlap(Ship check) {
    // we have to check the x and y values of check against the x and y values of all the ships in myShips
    // let's run a loop that ends when myShips hits a null value
    for(int i = 0;  myShips[i] != nullptr; i++){
        // we need to check the location vector at myShips[i], so we need another iterator for that
        for(int l = 0; l < myShips[i]->getLocation().size(); l++){
            // now we need to compare every point in this vector with every point in the vector passed in via check
            for(int c = 0; c < check.getLocation().size(); c++){
                if(check.getLocation()[c].x == myShips[i]->getLocation()[l].x){
                    if(check.getLocation()[c].y == myShips[i]->getLocation()[l].y){
                        cout << check.getShipType() << " intersects with " << myShips[i]->getShipType() << " at " <<
                        intToChar(check.getLocation()[c].x + 1) << check.getLocation()[c].y + 1 << ".\n";
                        return true;
                    }
                }
            }
        }
    }
    // return false if we've run through the entire for loop without finding a match
    return false;
}

// the player is guessing the opponent's ships
void Player::guess(point guess, Player* opponent) {
    bool hit = false;
    int sunkShipIndex;
    for(int i = 0; hit != true && i < opponent->totalShips; i++){
        if(opponent->myShips[i]->getSunk() == false){
            hit = opponent->myShips[i]->hit(guess);
            if(hit){
                // update opponent's ship to sunk and update playBoard to show the hit
                opponent->myShips[i]->setSunk(hit);
                opponent->myShips[i]->setBoardSymbol(opponent->shipHit);
                opponent->updatePlayboard(*opponent->myShips[i]);
                opponent->setShipsLeft((opponent->getShipsLeft())-1);
                // update your guessboard to show the hit
                updateGuessboard(*opponent->myShips[i]);
                cout << "The " << name << " has sunk the " << opponent->getName() << "'s " << opponent->myShips[i]->getShipType() << endl;
                sunkShipIndex = i;
                break;
            }
            else{
                updateGuessboard(guess, shipMiss);
                opponent->updatePlayboard(guess, shipMiss);
            }
            // if hit, update ship and board
            // if miss, update ship and board
        }
    }
    if(hit) {
        // update your guessed points
        updateGuessedPoints(*opponent->myShips[sunkShipIndex]);
    }
    else {
        guessedPoints.push_back(guess);
    }

}

/*
// the opponent has made a guess and we are checking for a hit and updating our board
void Player::opponentGuess(point guess) {
    bool hit;
    for(int i = 0; i < totalShips; i++){
        if(myShips[i]->getSunk() == false){
            hit = myShips[i]->hit(guess);
            if(hit){
                // update my ship to sunk
                myShips[i]->setSunk(hit);
                myShips[i]->setBoardSymbol(shipHit);
                // update your guessboard to show the hit
                updatePlayboard(*myShips[i]);
                shipsLeft--;
            }
            // if hit, update ship and board
            // if miss, update ship and board
        }
    }
    if(!hit){
        updateGuessboard(guess, shipMiss);
    }
}
*/

void Player::updatePlayboard(Ship add){
    int x = 0, y = 0, i = 0;
    bool found = false;
    do{
        for (int v = 0; v < add.getLocation().size(); v++) {
            while (y < 10 && !found) {
                while (x < 10 && !found) {
                    if (add.getLocation()[v].x == x) {
                        if (add.getLocation()[v].y == y) {
                            playBoard[y][x] = add.getBoardSymbol();
                            found = true;
                        }
                    }
                    x++;
                }
                x = 0;
                y++;
            }
            y = 0;
            found = false;
        }
        i++;
    } while(myShips[i] != nullptr);
}

void Player::updatePlayboard(point location, char newSymbol){
    for(int x = 0; x < 10; x++){
        for(int y = 0; y < 10; y++){
            if(location.x == x && location.y == y){
                playBoard[y][x] = newSymbol;
            }
        }
    }
}

void Player::updateGuessboard(Ship add){
    for(int i = 0; i < add.getLocation().size(); i++){
        guessBoard[add.getLocation()[i].y][add.getLocation()[i].x] = add.getBoardSymbol();
    }
}

void Player::updateGuessboard(point location, char newSymbol){
    for(int x = 0; x < 10; x++){
        for(int y = 0; y < 10; y++){
            if(location.x == x && location.y == y){
                guessBoard[y][x] = newSymbol;
                x = 10;
                y = 10;
            }
        }
    }
}

char Player::intToChar(int change) {
    switch (change){
        case 1:
            return 'A';
        case 2:
            return 'B';
        case 3:
            return 'C';
        case 4:
            return 'D';
        case 5:
            return 'E';
        case 6:
            return 'F';
        case 7:
            return 'G';
        case 8:
            return 'H';
        case 9:
            return 'I';
        case 10:
            return 'J';
        default:
            return 'N';
            // this will indicate an error
    }
}

int Player::charToInt(char change) {
    switch (change){
        case 'a':
        case 'A':
            return 1;
        case 'b':
        case 'B':
            return 2;
        case 'c':
        case 'C':
            return 3;
        case 'd':
        case 'D':
            return 4;
        case 'e':
        case 'E':
            return 5;
        case 'f':
        case 'F':
            return 6;
        case 'g':
        case 'G':
            return 7;
        case 'h':
        case 'H':
            return 8;
        case 'i':
        case 'I':
            return 9;
        case 'j':
        case 'J':
            return 10;
        default:
            return 11;
            // this will indicate an error
    }
}


void Player::displayPlayBoard(){
    cout << "    A  B  C  D  E  F  G  H  I  J\n";
    for(int i = 0; i < 10; i++){
        if(i == 9){
            cout << i+1 << "  ";
        }
        else{
            cout << " "<< i+1 << "  ";
        }
        for(int j = 0; j < 10; j++){
            cout << playBoard[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void Player::displayGuessBoard(){
    cout << "    A  B  C  D  E  F  G  H  I  J\n";
    for(int i = 0; i < 10; i++){
        if(i == 9){
            cout << i+1 << "  ";
        }
        else{
            cout << " "<< i+1 << "  ";
        }
        for(int j = 0; j < 10; j++){
            cout << guessBoard[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

bool Player::lost() {
    if(shipsLeft == 0){
        return true;
    }
    else{
        return false;
    }
}

void Player::setShipsLeft(int set) {
    shipsLeft = set;
}

int Player::getShipsLeft() {
    return shipsLeft;
}

vector<point> Player::getGuessedPoints() {
    return guessedPoints;
}

void Player::addGuessedPoints(point add) {
    guessedPoints.push_back(add);
}

void Player::updateGuessedPoints(Ship sunk) {
    int guessedPointsSize = guessedPoints.size();
    bool found = false;
    if(!guessedPoints.empty()) {
        for (int i = 0; i < sunk.getLocation().size(); i++) {
            for (int j = 0; j < guessedPointsSize; j++) {
                if (guessedPoints[j].x == sunk.getLocation()[i].x && guessedPoints[j].y == sunk.getLocation()[i].y) {
                    found = true;
                    break;
                } else {
                    found = false;
                }
            }
            if(!found){
                guessedPoints.push_back(sunk.getLocation()[i]);
            }
        }
    }
    else{
        for(int i = 0; i < sunk.getLocation().size(); i++){
            guessedPoints.push_back(sunk.getLocation()[i]);
        }
    }
}

string Player::getName() {
    return name;
}

void Player::setName(string set) {
    name = set;
}