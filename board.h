#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <array>

class Board{    
    public:
        int board_size;
        int **cells;
        
        Board(int size = 3); //initializes the 2D board array
        ~Board(); //deleted 2D array
        void print(); //prints the board to console in a human readable form
        std::array<int,2> validateMove(int move); //check if the move attempted in valid/open cell
        void insertMove(int player, int col, int row); //changes a cell to a player
        int win(); //checks for end-game states (win or tie)
        long evaluate(); //Scores the board for minimax
        //void printMoves(); //prints possible moves for human. not needed anymore
        std::vector<std::array<int,2>> getMoves(); //gets all possible moves in an AI readable state
        
    private:
        void convertToPiece(int);
};

#endif
