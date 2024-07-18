#include <iostream>
#include <typeinfo>
#include "Game.h"
using namespace std;

int main() {
    bool fileSuccess = true;
    string fileName;
    Player humanPlayer;
    AIOpponent AI;
    Game newGame;
    AI.setName("AI");
    humanPlayer.setName("Player");
    cout << "Please enter the full name of a file to be used to generate the AI's game board\n";
    getline(cin, fileName);
    try{
        AI.setUpShips(&fileSuccess, fileName);
        if(!fileSuccess) {
            throw (false);
        }
        else {
            humanPlayer.beginGame();
            newGame.playGame(humanPlayer, AI);
        }
    }
    catch(bool badFile){
        cout << "The file being used to generate ship placement for the AI did not contain the proper information to\n"
                "properly generate the board. We apologize for the inconvenience. Please reload the game and enter a\n"
                "different file name.\n";
    }

    return 0;
}
