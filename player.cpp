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

int AI::getAIMove(Board &current_game){
    int difficulty = 10;
    minimax(current_game, difficulty);

    return 0;
}

int AI::minimax(Board &current_game, int level, long alpha, long beta){
    //int minmax[3];
    
    if (this->piece == "X"){
        //If Max
    }else{
        //Else Min
    }
    
    return 0;
}

int AI::evaluate(Board &curent_game){

    
    return 0;
}