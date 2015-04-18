#include "player.h"
#include <iostream>
#include <string>
#include <array>
#include <cstdio>
#include <ctime>
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

array<int,2> AI::getAIMove(int team, Board &current_game){
	bool max = true;
    if(team == -1)
        max = false;
    double duration;
    clock_t start = clock();
    array<long,4>move = minimax(current_game, max, this->difficulty);
    duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << endl << endl << "Possible states considered: " << move[3];
    cout << endl << "Time: " << duration << "s";
    return array<int,2>{{(int)move[1],(int)move[2]}};
}

array<long,4> AI::minimax(Board &current_game, bool max, int depth, long alpha, long beta, long count){
    vector<array<int,2>> move = current_game.getMoves();
    long score = 0;
    long bestCol = -1;
    long bestRow = -1;
    int current_team = (max) ? 1 : -1;
    
    if(move.size() == 0 || depth == 0 || current_game.win() != 2){
        score = current_game.evaluate();
		//current_game.print();
		//cout << score;
		return array<long,4>{{score, bestCol, bestRow, count}};
    }else{
		for (unsigned int i = 0; i < move.size(); ++i){
            current_game.cells[move[i][0]][move[i][1]] = current_team;  
			++count;
            if(max){
                array<long,4>temp = minimax(current_game, false, depth-1, alpha, beta, count);
				score = temp[0];
				count = temp[3];
                if(score > alpha){
                    alpha = score;
                    bestCol = move[i][0];
                    bestRow = move[i][1];
                }
            }else{
                array<long,4>temp = minimax(current_game, true, depth-1, alpha, beta, count);
				score = temp[0];
				count = temp[3];
                if(score < beta){
                    beta = score;
                    bestCol = move[i][0];
                    bestRow = move[i][1];
                }
            }
            current_game.cells[move[i][0]][move[i][1]] = 0;
            if(alpha >= beta) break;
        }
		return array<long,4>{{(max) ? alpha : beta, bestCol, bestRow, count}};
    }
    return array<long,4>{{0,0,0,0}};
}