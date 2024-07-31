// prevent redefinition
#ifndef GAME_H
#define GAME_H
// include header files and libraries
#include "Player.h"
#include "AIOpponent.h"

class Game{
public:
    void playGame(Player humanPlayer, Player AI);
};

#endif //GAME_H
