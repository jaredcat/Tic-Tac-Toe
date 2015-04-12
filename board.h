#ifndef BOARD_H
#define BOARD_H
#include <iostream>

class Board{    
    public:
        int **cells;
        Board(int size = 3);
        ~Board();
        void print();
        int validateMove(int move);
        void insertMove(int player, int move);
        int win();
        void getMoves();
        
    private:
        int board_size;
        std::string convertToPiece(int);
};

#endif