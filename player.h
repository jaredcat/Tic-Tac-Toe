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
        AI(std::string piece, int difficulty = 3) : Player(piece){
			this->difficulty = difficulty;
        };
        std::array<int,2> getAIMove(int team, Board &curent_game, bool trace = false); //picks the AIs next move
		int difficulty; //depth bound of minimax search
    
    private:
        //recursive function that considers all possible game states (within reason or depth) to find next move for best possible outcome
        std::array<long,4> minimax(Board &curent_game, bool max, int level = 3, bool trace = false, long alpha = -2000000000, long beta = 2000000000, long count = 0);
};
#endif
