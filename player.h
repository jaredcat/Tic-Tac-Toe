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
        AI(std::string piece, int difficulty = 5) : Player(piece){
			this->difficulty = difficulty;
        };
        int* getAIMove(int team, Board &curent_game);
		int difficulty;
    
    private:
        long* minimax(Board &curent_game, bool max, int level = 2, long alpha = -2000000000, long beta = 2000000000, long count = 0);
};
#endif