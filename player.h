#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include <iostream>
#include <string>

class Player{    
    public:
        int team;
        int ishuman=1;
        std::string piece;
        Player(std::string);
        std::string convertToPiece();
    private:
};

class AI : public Player{
    public:
        AI(std::string piece) : Player(piece){
            this->ishuman = 0;
        };
        int getAIMove(Board &curent_game);
    
    private:
        int minimax(Board &curent_game, int level = 10, long alpha = -2000000000, long beta = 2000000000);
        int evaluate(Board &curent_game);
};
#endif