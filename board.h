#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <array>

class Board{    
    public:
        int board_size;
        int **cells;
        
        Board(int size = 3);
        ~Board();
        void print();
        std::array<int,2> validateMove(int move);
        void insertMove(int player, int col, int row);
        int win();
        long evaluate();
        void printMoves();
        std::vector<std::array<int,2>> getMoves();
        
    private:
        std::string convertToPiece(int);
};

#endif