#include <iostream>
#include <string>
using namespace std;

class Board{    
    public:
        int **cells;
        Board(int size);
        ~Board();
        print();
        int validateMove(int x, int y);
        insertMove(int player, int x, int y);
        bool win();
        
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
    //cout << endl << "Array deleted";
}

Board::print(){
    cout << endl;
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

int Board::validateMove(int x, int y){
    if(cells[x-1][y-1] != 0)
        return 0;
    return 1;
}

Board::insertMove(int player, int x, int y){
    cells[x-1][y-1] = player;
}

bool Board::win(){
    //Checks for any vertical win states
    for(int i=0; i < board_size; ++i){
        for(int j=1; i < board_size; ++j){
            if(cells[i][j-1] == 0 || cells[i][j] != cells[i][j-1]){
                break;
            }else if(j == board_size-1){
                return true;
            }
        }
    }
    
    //checks for horizontal win states
    for(int i=0; i < board_size; ++i){
        for(int j=1; i < board_size; ++j){
            if(cells[j][i-1] == 0 || cells[j][i] != cells[j][i-1]){
                break;
            }else if(j == board_size-1){
                return true;
            }
        }
    }
    
    //checks for diagonal win states
    for(int i=1; i < board_size; ++i){
        if(cells[i-1][i-1] == 0 || cells[i][i] != cells[i-1][i-1]){
            break;
        }else if(i == board_size-1){
            return true;
        }
    }
    
    //checks for diagonal win states
    for(int i=1, j = board_size-2; i < board_size; ++i, --j){
        if(cells[i-1][j-1] == 0 || cells[i][j] != cells[i-1][j-1]){
            break;
        }else if(i == board_size-1){
            return true;
        }
    }
    
    return true;
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

int gameLoop(Board current_game, Player human, Player ai){
    bool win = false;
    int winner = 0;
    
    while(!current_game.win()){
        current_game.print();
        
    }
    cout << endl << winner << " won.";
    return winner;
}

int main(){
  int board_size = 3;
  string player = "X";
  string keep_playing = "Y";
  int winner = 0, score_x = 0, score_y = 0;
  //while(keep_playing == "Y"){
      cout << "Pick the size of the grid (default = 3): ";
      cin >> board_size;
      Board board(board_size); //initialize a new board
      board.print();
      cout << endl << "X or O (X moves first): ";
      cin >> player;
      player = toupper(player[0]);
      Player human(player); //initializes human player to their piece
      cout << "You are " << human.convertToPiece();
      AI ai(human.piece); //initializes ai player to opposite piece
      cout << endl << "AI is " << ai.piece; 
      winner = gameLoop(board, human, ai); //game logic within the game is done here
      cout << endl << endl << "Would you like to play again? (Y/N): ";

   // }
  
  return 0;
}