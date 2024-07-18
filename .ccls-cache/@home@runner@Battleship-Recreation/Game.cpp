// include header file
#include "Game.h"
// include libraries
#include <ctime>



void Game::playGame(Player humanPlayer, Player AI) {
    bool gameOver = false, newGuess = false, firstGuessP = true, firstGuessAI = true;
    int randX, randY, x, y;
    char tempX;
    string guess, tempY;
    point AIGuess, playerGuess;
    srand(time(NULL));
    // instructions
    cout << "Now that the ships are set up, the game can begin. You will go first and will takes turns with the AI to make\n"
            "guesses as to where the other player's ships are. When a ship is found, it is considered sunk. The first player\n"
            "to sink all of the opposing player's ships wins. When you guess a location, your guess will appear on your guess\n"
            "board, which will be displayed each time you have to make a guess. Hits will be displayed as O's on the board,\n"
            "and misses will be displayed as X's. The AI's guesses will also be displayed on your playing board so that you\n"
            "can see how close the AI is to winning. If you wish to quit the game at any time, simply enter Q in place of\n"
            "coordinates when it's your turn to guess. Ready? Good luck!\n";

    while(!gameOver) {
        // player guess
        cout << "Where would you like to guess?\n";
        getline(cin, guess);
        if (guess.find('Q') != string::npos || guess.find('q') != string::npos){
            cout << "Thank you for playing!\n";
            gameOver = true;
        }
        else {
            while (!newGuess) {
                tempY.clear();
                try {
                    // set up guess
                    tempX = guess[0];
                    for (int holdY = 1; guess[holdY] != '\0'; holdY++)
                        tempY += guess[holdY];
                    x = humanPlayer.charToInt(tempX);
                    if (!isdigit(tempY[0])) {
                        cout
                                << "Please be sure you are entering your coordinates LetterNumber (ex. A1) and not NumberLetter (ex. 2D).\n";
                        continue;
                    }
                    y = stoi(tempY);
                    if (y > 10 || y <= 0)
                        throw y;
                    else if (x > 10 || x <= 0)
                        throw x;
                    playerGuess.x = humanPlayer.charToInt(tempX) - 1;
                    playerGuess.y = stoi(tempY) - 1;

                }
                catch (int outside) {
                    cout << "You are unable to guess at point " << tempX << y << " because it extends off the board.\n";
                    continue;
                }
                if (firstGuessP) {
                    newGuess = true;
                    firstGuessP = false;
                } else {
                    for (int i = 0; i < humanPlayer.getGuessedPoints().size(); i++) {
                        if (playerGuess.x == humanPlayer.getGuessedPoints()[i].x &&
                            playerGuess.y == humanPlayer.getGuessedPoints()[i].y) {
                            cout
                                    << "You have already guessed this point, or a ship you have already sunk is in this location. Please\n"
                                       "enter a new value:\n";
                            cout << "Where would you like to guess?\n";
                            getline(cin, guess);
                            newGuess = false;
                            break;
                        } else {
                            newGuess = true;
                        }
                    }
                }
            }
            newGuess = false;
            humanPlayer.guess(playerGuess, &AI);
            cout << "YOUR GUESS BOARD\n";
            humanPlayer.displayGuessBoard();
            if (AI.lost()) {
                gameOver = true;
                cout << "PLAYER WINS\n";
                break;
            }


            cout << "Now it's the AI's turn:\n";
            // AI guess
            while (!newGuess) {
                randX = rand() % 10;
                randY = rand() % 10;
                if (firstGuessAI) {
                    newGuess = true;
                    firstGuessAI = false;
                } else {
                    for (int i = 0; i < AI.getGuessedPoints().size(); i++) {
                        if (randX == AI.getGuessedPoints()[i].x && randY == AI.getGuessedPoints()[i].y) {
                            newGuess = false;
                            break;
                        } else {
                            newGuess = true;
                        }
                    }
                }
            }
            AIGuess.x = randX;
            AIGuess.y = randY;
            AI.addGuessedPoints(AIGuess);
            newGuess = false;
            AI.guess(AIGuess, &humanPlayer);
            cout << "YOUR PLAY BOARD\n";
            humanPlayer.displayPlayBoard();
            if (humanPlayer.lost()) {
                gameOver = true;
                cout << "AI WINS\n";
                break;
            }
        }
    }
    // display all boards
    cout << "PLAYER GUESS BOARD\n";
    humanPlayer.displayGuessBoard();
    cout << "PLAYER GAME BOARD\n";
    humanPlayer.displayPlayBoard();
    cout << "AI GUESS BOARD\n";
    AI.displayGuessBoard();
    cout << "AI GAME BOARD\n";
    AI.displayPlayBoard();

}


/*
void Game::playGame(Player humanPlayer, Player AI) {
    bool gameOver = false, newGuess = false, firstGuessP = true, firstGuessAI = true;
    int randX, randY, playerNumGuesses = 1, AINumGuesses = 1;
    char tempX;
    string guess, tempY;
    point AIGuess, playerGuess;
    srand(time(NULL));
    // instructions
    cout << "Now that the ships are set up, the game can begin. You will go first and will takes turns with the AI to make\n"
            "guesses as to where the other player's ships are. When a ship is found, it is considered sunk. The first player\n"
            "to sink all of the opposing player's ships wins. When you guess a location, your guess will appear on your guess\n"
            "board, which will be displayed each time you have to make a guess. Hits will be displayed as O's on the board,\n"
            "and misses will be displayed as X's. The AI's guesses will also be displayed on your playing board so that you\n"
            "can see how close the AI is to winning. If you wish to quit the game at any time, simply enter Q in place of\n"
            "coordinates when it's your turn to guess. Ready? Good luck!\n";

    while(!gameOver){
        // player guess
        // AI guess
        while (!newGuess) {
            randX = rand() % 10;
            randY = rand() % 10;
            if(firstGuessP == true) {
                newGuess = true;
                firstGuessP = false;
            }
            else{
                for (int i = 0; i < humanPlayer.getGuessedPoints().size(); i++) {
                    if (randX == humanPlayer.getGuessedPoints()[i].x && randY == humanPlayer.getGuessedPoints()[i].y) {
                        newGuess = false;
                        break;
                    }
                    else {
                        newGuess = true;
                    }
                }
            }
        }
        playerGuess.x = randX;
        playerGuess.y = randY;
        newGuess = false;
        humanPlayer.guess(playerGuess, &AI);

        cout << "\n\nMY PLAY GUESS BOARD\n";
        humanPlayer.displayGuessBoard();
        cout << "\n\nOPPONENT BOARD\n";
        AI.displayPlayBoard();

        cout << "Player Guesses: " << playerNumGuesses++ << endl;
        if(humanPlayer.won()){
            gameOver = true;
            cout << "PLAYER WINS\n";
            break;
        }


        // AI guess
        while (!newGuess) {
            randX = rand() % 10;
            randY = rand() % 10;
            if(firstGuessAI == true) {
                newGuess = true;
                firstGuessAI = false;
            }
            else{
                for (int i = 0; i < AI.getGuessedPoints().size(); i++) {
                    if (randX == AI.getGuessedPoints()[i].x && randY == AI.getGuessedPoints()[i].y) {
                        newGuess = false;
                        break;
                    }
                    else {
                        newGuess = true;
                    }
                }
            }
        }
        AIGuess.x = randX;
        AIGuess.y = randY;
        newGuess = false;
        AI.guess(AIGuess, &humanPlayer);

        cout << "\n\nOPPONENT GUESS BOARD\n";
        AI.displayGuessBoard();
        cout << "\n\nMY PLAY BOARD\n";
        humanPlayer.displayPlayBoard();

        cout << "AI Guesses: " << AINumGuesses++ << endl;
        if(AI.won()){
            gameOver = true;
            cout << "AI WINS\n";
            break;
        }
    }
}
*/