#include <iostream>
#include <string>
using namespace std;

class Board{    
    public:
        int **cells;
        Board(int size);
        ~Board();
        print();
        
    private:
        int board_size;
        std::string convertToPiece(int);
};

Board::Board(int size = 3){
    
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
    cout << endl << "Array deleted";
}

Board::print(){
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
    return 0;
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

class Player{    
    public:
        int team;
        std::string piece;
        Player(std::string);
        std::string convertToPiece();
        
    private:
};

class AI : public Player{
    public:
        AI(string piece) : Player(piece){
            if(this->piece=="X"){
                this->piece = "O";
            }else{
                this->piece = "X";
            }
        };
};

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
}


int main(){
  int board_size = 3;
  string player = "X";
  
  cout << "Pick the size of the grid (default = 3): ";
  cin >> board_size;
  Board board(board_size);
  board.print();
  cout << "X or O (X moves first): ";
  cin >> player;
  player = toupper(player[0]);
  Player human(player);
  cout << "You are " << human.convertToPiece();
  AI ai(human.piece);
  cout << endl << "AI is " << ai.piece; 
  
  return 0;
}