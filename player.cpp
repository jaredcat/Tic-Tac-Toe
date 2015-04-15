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
    bool max = true;
    if(this->piece == "O")
        max = false;
        
    int move = minimax(current_game, max, difficulty)[1];

    return move;
}

int* AI::minimax(Board &current_game, bool max, int depth, int alpha, int beta){
    vector<int> move = current_game.getMoves();
    int score;
    int bestMove = -1;
    
    if(depth == 0){
        score = evaluate(current_game);
        return new int[2] {score, bestMove};
    }else{
        for(int i=0; move.size(); ++i){
            current_game.cells[move[i]] = this->team;
            if(max){
                score = minimax(current_game, false, depth-1, alpha, beta)[0];
                if(score > alpha){
                    alpha = score;
                    bestMove = move[i];
                }
            }else{
                score = minimax(current_game, true, depth-1, alpha, beta)[0];
                if(score < beta){
                    beta = score;
                    bestMove = move[i];
                }
            }
            current_game.cells[move[i]] = 0;
            if(alpha >= beta) break;
        }
        return new int[2] {(max) ? alpha : beta, bestMove};       
    }
}

int AI::evaluate(Board &current_game){
    
    return 0;
}