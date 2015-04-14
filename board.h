#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>

class Board{    
    public:
        int board_size;
        int *cells;
        Board(int size = 3);
        ~Board();
        void print();
        bool validateMove(int move);
        void insertMove(int player, int move);
        bool win();
        void printMoves();
        std::vector<int> getMoves();
        
    private:
        std::string convertToPiece(int);
};

#endif