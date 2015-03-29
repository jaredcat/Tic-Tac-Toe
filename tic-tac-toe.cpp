#include <iostream>
#include <string>
using namespace std;

class Board{
    int **cells;
    
    public:
        Board(int size);
        ~Board();
        Print();
        
    
    private:
        int board_size;
};

Board::Board(int size = 3){
    
    this->board_size = size;
    this->cells = new int* [size];
    for(int i=0; i<size; ++i)
        cells[i] = new int [size];
    
    for(int i =0; i<size; ++i){
        for(int j=0; j < size; ++j)
            cells[j][i] = 0;
    }    
}

Board::~Board(){
    for(int i=0; i < board_size; ++i){
        delete[] cells[i];
    }
    delete[] cells;
    cout << endl << "Array deleted";
}

Board::Print(){
    for (int i=0; i < board_size; ++i){
        for (int j=1; j < board_size; ++j)
            cout << " " << cells[j][i] << " |";
        cout << " " << cells[board_size-1][i];
        cout << endl;
        if(i != board_size-1){
            for (int j=1; j < board_size; ++j)
                cout << "----";
            cout << "---" << endl;
        }
    }
    return 0;
}

/*class Player{
  player(int team){
    int i = 0;
  }
};

class AI : public Player{
  AI(int team){
    Player(team);
  }
};*/

int main(){
  int board_size = 3;
  
  cout << "Pick the size of the grid (default = 3): ";
  cin >> board_size;
  Board board(board_size);
  board.Print();
  return 0;
}