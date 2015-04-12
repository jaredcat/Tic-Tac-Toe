#include "board.h"
#include <iostream>
using namespace std;

Board::Board(int size){
    
    board_size = size; //stores the board size in the object
    //allocate memory for new board of <size> by <size>
    cells = new int* [size];
    for(int i=0; i<size; ++i)
        cells[i] = new int [size];
    
    // Initialize the game cells to 0 (no moves)
    for(int i =0; i<size; ++i){
        for(int j=0; j < size; ++j){
            cells[j][i] = 0;
        }
    }
}

Board::~Board(){
    for(int i=0; i < board_size; ++i){
        delete[] cells[i];
    }
    delete[] cells;
    //cout << endl << "Array deleted";
}

void Board::print(){
    cout << endl << endl;
    for (int i=0; i < board_size; ++i){ //every row
        for (int j=0; j < board_size-1; ++j) //every column but the last
            cout << " " << convertToPiece(cells[j][i]) << " |";
        cout << " " << convertToPiece(cells[board_size-1][i]); //last column
        cout << endl;
        if(i != board_size-1){ //last row doesn't need horizontal break lines
            for (int j=1; j < board_size; ++j)
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

int Board::validateMove(int move){
    int count = 0;
    int i, j;
    for (i=0; i < board_size; ++i){ //every row
        for (j=0; j < board_size; ++j){ //every column
            if(cells[j][i] == 0){
                ++count;
                if(count == move)
                    break;
            }
        }
        if(count == move)
            break;
    }
    if(cells[j][i] == 0)
        return 1;
    return 0;
    
}

void Board::insertMove(int player, int move){
    int count = 0;
    int i, j;
    for (i=0; i < board_size; ++i){ //every row
        for (j=0; j < board_size; ++j){ //every column
            if(cells[j][i] == 0){
                ++count;
                if(count == move)
                    break;
            }
        }
        if(count == move)
            break;
    }
    cells[j][i] = player;
}

int Board::win(){
    //Checks for any vertical win states
    for(int i=0; i < board_size; ++i){
        for(int j=1; i < board_size; ++j){
            if(cells[i][j-1] == 0 || cells[i][j] != cells[i][j-1]){
                break;
            }else if(j == board_size-1){
                return cells[i][j];
            }
        }
    }
    
    //checks for horizontal win states
    for(int i=0; i < board_size; ++i){
        for(int j=1; i < board_size; ++j){
            if(cells[j][i-1] == 0 || cells[j][i] != cells[j][i-1]){
                break;
            }else if(j == board_size-1){
                return cells[i][j];
            }
        }
    }
    
    //checks for diagonal win states
    for(int i=1; i < board_size; ++i){
        if(cells[i-1][i-1] == 0 || cells[i][i] != cells[i-1][i-1]){
            break;
        }else if(i == board_size-1){
            return cells[i][i];
        }
    }
    
    //checks for diagonal win states
    for(int i=1, j = board_size-2; i < board_size; ++i, --j){
        if(cells[i-1][j+1] == 0 || cells[i][j] != cells[i-1][j+1]){
            break;
        }else if(i == board_size-1){
            return cells[i][j];
        }
    }

    return 0;
}

void Board::getMoves(){
    int count = 1;
    for (int i=0; i < board_size; ++i){ //every column
        for (int j=0; j < board_size; ++j){ //every row
            if(cells[j][i] == 0){
                cout << endl << count << ". (" << j << "," << i << ")";
                ++count;
            }
        }
    }
}