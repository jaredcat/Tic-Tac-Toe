#include "player.h"
#include <iostream>
#include <string>
#include <array>
using namespace std;

Player::Player(string piece){
    team = 1;
    this->piece = "X";
    if(piece == "O"){
        team = -1;
        this->piece = "O";
    }
}

//Converts the teams id to game piece
string Player::convertToPiece(){
    switch(team){
        case(1):
            return "X";
            break;
        case(-1):
            return "O";
            break;
    }
    return "";
}

int* AI::getAIMove(int team, Board &current_game){
    int difficulty = 10;
    bool max = true;
    if(team == -1)
        max = false;
    int *move = (int*)minimax(current_game, max, difficulty);

    return new int[2] {move[1],move[2]};
}

long* AI::minimax(Board &current_game, bool max, int depth, long alpha, long beta){
    vector<array<int,2>> move = current_game.getMoves();
    long score = 0;
    long bestCol = -1;
    long bestRow = -1;
    int current_team = (max) ? 1 : -1;
    
    if(move.size() == 0 || depth == 0 || current_game.win()){
        score = current_game.evaluate(this->team);
        return new long[3] {score, bestCol, bestRow};
    }else{
        for(uint i=0; i < move.size(); ++i){
            current_game.cells[move[i][0]][move[i][1]] = current_team;            
            if(max){
                score = minimax(current_game, false, depth-1, alpha, beta)[0];
                if(score > alpha){
                    alpha = score;
                    bestCol = move[i][0];
                    bestRow = move[i][1];
                }
            }else{
                score = minimax(current_game, true, depth-1, alpha, beta)[0];
                if(score < beta){
                    beta = score;
                    bestCol = move[i][0];
                    bestRow = move[i][1];
                }
            }
            current_game.cells[move[i][0]][move[i][1]] = 0;
            if(alpha >= beta) break;
        }
        return new long[3] {(max) ? alpha : beta, bestCol, bestRow};       
    }
    return new long[3]{0,0,0};
}