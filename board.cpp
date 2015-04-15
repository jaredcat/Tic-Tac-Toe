#include "board.h"
#include <iostream>
#include <vector>
using namespace std;

Board::Board(int size){
    
    //stores the board size in the object
    board_size = size; 
    
    //allocate memory for new board of that is a square of the input size
    cells = new int[(size*size)];    
    
    // Initialize the game cells to 0 (no moves)
    for(int i =0; i<size*size; ++i){
        cells[i] = 0;
    }
}

Board::~Board(){
    delete[] cells;
    //cout << endl << "Array deleted";
}

void Board::print(){
    cout << endl << endl;
    //for every cell
    for(int i=0; i < board_size*board_size; ++i){
        //for every cell in a row, but the last
        for(int j=1; j < board_size; ++j, ++i)
            cout << " " << convertToPiece(cells[i]) << " |";
        //print out last row
        cout << " " << convertToPiece(cells[i]) << " " << endl;
        //if not the bottom row
        if(i < (board_size*(board_size-1))){
            //print a horizontal spacer for every cell
            for(int j=1; j < board_size; ++j)
                cout << "----";
            cout << "---" << endl;
        }
    }
}

//Converts numbers into letters
string Board::convertToPiece(int cell){
    switch(cell){
        case(1):
            return "X";
            break;
        case(2):
            return "O";
            break;
        default:
            return " ";
    }
}

void Board::printMoves(){
    for (int i=0; i < board_size*board_size; ++i){
        if(cells[i] == 0){
            cout << endl << "Cell: " << i+1;
        }
    }
}

vector<int> Board::getMoves(){
    vector<int> moves;
    //for every cell
    for (int i=0; i < board_size*board_size; ++i){
        if(cells[i] == 0){
            moves.push_back(i);
        }
    }
    return moves;
}

bool Board::validateMove(int move){
    if(move > 0 || move <= board_size*board_size){
        if(cells[move-1] == 0)
            return true;
    }
    return false;
}

void Board::insertMove(int player, int move){
    
    cells[move-1] = player;
}

bool Board::win(){
    //checks for horizontal win states
    for(int i=0; i <= board_size*(board_size-1); i+=board_size){
        for(int j=1; j < board_size; ++j){
            //cout << endl << j+i-1 << "=" << cells[i+j-1] << " vs " << i+j << "=" << cells[i+j]; 
            if(cells[i+j-1] == 0 || cells[i+j-1] != cells[i+j]){
                break;
            }else if(j == board_size-1){
                return true;
            }
        }
    }
    
    //Checks for any vertical win states
    for(int i=0; i < board_size; ++i){
        for(int j=i+board_size; j < board_size*board_size; j+=board_size){
            //cout << endl << j-board_size << "=" << cells[j-board_size] << " vs " << j << "=" << cells[j]; 
            if(cells[j-board_size] == 0 || cells[j-board_size] != cells[j]){
                break;
            }else if(j >= board_size*(board_size-1)){
                return true;
            }
        }
    }
    
    //checks for diagonal win states
    for(int i=board_size*2-2; i < board_size*board_size; i+=board_size-1){
        //cout << endl << i-board_size+1 << "=" << cells[i-board_size+1] << " vs " << i << "=" << cells[i]; 
        if(cells[i-board_size+1] == 0 || cells[i-board_size+1] != cells[i]){
            break;
        }else if(i == board_size*(board_size-1)){
            return true;
        }
    }

    return false;
}