#include <iostream>
#include <string>
using namespace std;

class Board{
  public:
    Board(int size);
    
  private:
    int board_size
};

Board::Board(int size = 3){
  board_size = size;
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
  return 0;
}