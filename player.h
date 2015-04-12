#ifndef PLAYER_H
#define PLAYER_H
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
};
#endif