// include header files
#ifndef AIOPPONENT_H
#define AIOPPONENT_H
// include parent header file
#include "Player.h"

class AIOpponent : public Player{
public:
    void setUpShips(bool* success, string fileName);
};


#endif //AIOPPONENT_H
