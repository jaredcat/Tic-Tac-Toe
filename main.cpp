#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

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
        cout << endl << "I:" << i << "  j:" << j;
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

class Player{    
    public:
        int team;
        int ishuman=1;
        std::string piece;
        Player(std::string);
        std::string convertToPiece();
    private:
};

class AI : public Player{
    public:
        AI(string piece) : Player(piece){
            this->ishuman = 0;
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
    return "";
}

void gameLoop(Board &current_game, Player &player1, Player &player2){
    int winner = 0;
    int move;
    
    while((winner = current_game.win()) == 0){
        if(player1.piece == "X"){
            current_game.print();
            current_game.getMoves();
            cout << endl << "Player 1: Select move#: ";
            cin >> move;
            if (current_game.validateMove(move)){
                current_game.insertMove(player1.team, move);
            }
            if((winner = current_game.win()) != 0)
                break;
            if(player2.ishuman){
                current_game.print();
                current_game.getMoves();
                cout << endl << "Player 2: Select move#: ";
                cin >> move;
                if (current_game.validateMove(move)){
                    current_game.insertMove(player2.team, move);
                }
            }else{
                //call ai move
            }
        }else{
            if(player2.ishuman){
                current_game.print();
                current_game.getMoves();
                cout << endl << "Player 2: Select move#: ";
                cin >> move;
                if (current_game.validateMove(move)){
                    current_game.insertMove(player2.team, move);
                }
            }else{
                //call ai move
            }
            if((winner = current_game.win()) != 0)
                break;
            current_game.print();
            current_game.getMoves();
            cout << endl << "Player 1: Select move#: ";
            cin >> move;
            if (current_game.validateMove(move)){
                current_game.insertMove(player1.team, move);
            }
        }
    }
    cout << endl << winner << " won.";
}

string oppositePiece(string piece){
    if(piece == "X"){
        return "O";
    }
    return "X";
}

int main(){
  int board_size = 3;
  int humans = 1;
  string player = "X";
  cout << "Pick the size of the grid (default = 3): ";
  cin >> board_size;
  Board board(board_size); //initialize a new board
  board.print();
  cout << endl << "1 or 2 human players? ";
  cin >> humans;
  if(humans == 1){
      cout << endl << "X or O (X moves first): ";
      cin >> player;
      player = toupper(player[0]);
      Player human(player); //initializes human player to their piece
      cout << "You are " << human.convertToPiece();
      AI ai(oppositePiece(human.piece)); //initializes ai player to opposite piece
      cout << endl << "AI is " << ai.piece; 
      gameLoop(board, human, ai); //game logic within the game is done here
  }else if(humans == 2){
      cout << endl << "Player 1: X or O (X moves first): ";
      cin >> player;
      player = toupper(player[0]);
      Player human1(player); //initializes human player to their piece
      Player human2(oppositePiece(human1.piece)); //initializes player 2 to opposite piece
      cout << endl << "Player 1 is: " << human1.piece;
      cout << endl << "Player 2 is: " << human2.piece; 
      gameLoop(board, human1, human2); //game logic within the game is done here   
  }
  return 0;
}