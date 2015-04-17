#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include <iostream>
#include <string>
#include <array>

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
        int* getAIMove(int team, Board &curent_game);
    
    private:
        long* minimax(Board &curent_game, bool max, int level = 10, long alpha = -2000000000, long beta = 2000000000);
};
#endif