#include "player.h"
#include <iostream>
#include <string>
using namespace std;

Player::Player(string piece){
    if(piece == "X"){
        team = 1;
        this->piece = piece;
    }else if(piece == "O"){
        team = 2;
        this->piece = piece;
    }else{
        team = 1;
        this->piece = piece;
    }
}

//Converts the teams id to game piece
string Player::convertToPiece(){
    switch(team){
        case(1):
            return "X";
            break;
        case(2):
            return "O";
            break;
    }
    return "";
}