#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include <iostream>
#include <string>

class Player{    
    public:
        int team;
        std::string piece;
        Player(std::string);
        std::string convertToPiece();
    private:
};

class AI : public Player{
    public:
        AI(std::string piece) : Player(piece){
        };
        int getAIMove(Board &curent_game);
    
    private:
        int* minimax(Board &curent_game, bool max, int level = 10, int alpha = -32000, int beta = 32000);
        int evaluate(Board &curent_game);
};
#endif