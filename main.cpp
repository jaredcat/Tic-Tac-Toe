#include "board.h"
#include "player.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


void gameLoop(Board &current_game, Player &player1, Player &player2){
    int winner = 0;
    int move = -1;
    array<int,2> valid;
    
    if(player1.piece == "X"){
        do{
            current_game.print();
            //current_game.printMoves();
            cout << endl << endl << "Player 1:" << endl << "Select cell number: ";
            cin >> move;
            valid = current_game.validateMove(move);
        }while(valid[0] == -1);
        current_game.insertMove(player1.team, valid[0], valid[1]);
    }
    
    do{
        do{
            current_game.print();
            //current_game.printMoves();
            cout << endl << endl << "Player 2:" << endl << "Select cell: ";
            cin >> move;
            valid = current_game.validateMove(move);
        }while(valid[0] == -1);
        current_game.insertMove(player2.team, valid[0], valid[1]);
        if((winner = current_game.win()) < 2)
            break;
        
        do{
            current_game.print();
            //current_game.printMoves();
            cout << endl << endl << "Player 1:" << endl << "Select cell number: ";
            cin >> move;
            valid = current_game.validateMove(move);
        }while(valid[0] == -1);
        current_game.insertMove(player1.team, valid[0], valid[1]);
		if ((winner = current_game.win()) < 2)
			break;

	}while (current_game.win() == 2);
    current_game.print();
	cout << endl;
    if(player1.team == winner){
        cout << "Player 1 won.";
    }else if(player2.team  == winner){
        cout << "Player 2 won.";
	}else{
		cout << "Tie game.";
	}
}

void gameLoop(Board &current_game, Player &human, AI &ai, bool trace){
    int winner = 0;
    int move = -1;
    array<int,2> aimove, valid;
    
    //if human player is X then let them move first
    if(human.piece == "X"){
        do{
            current_game.print();
            //current_game.printMoves();
            cout << endl << "Select cell number: ";
            cin >> move;
            valid = current_game.validateMove(move);
        }while(valid[0] == -1);
        current_game.insertMove(human.team, valid[0], valid[1]);
    }
    
    do{
        current_game.print();
        //let AI player make its move
        aimove = ai.getAIMove(ai.team, current_game, trace);
        current_game.insertMove(ai.team, aimove[0], aimove[1]);
		if ((winner = current_game.win()) < 2)
			break;
        
        //let human player make its move
        do{
            current_game.print();
            //current_game.printMoves();
            cout << endl << "Select cell number: ";
            cin >> move;
            valid = current_game.validateMove(move);
        }while(valid[0] == -1);
        current_game.insertMove(human.team, valid[0], valid[1]);
		if ((winner = current_game.win()) < 2)
			break;

	}while (current_game.win() == 2 );
    current_game.print();
	cout << endl;
	if (human.team == winner){
		cout << "Human won.";
	}
	else if (ai.team == winner){
		cout << "AI won.";
	}
	else{
		cout << "Tie game.";
	}
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
  int difficulty = 3;
  string player = "X";
  string trace = "N";
  bool booltrace = false;
  
  cout << endl << "Pick the size of the grid (default = 3): ";
  cin >> board_size;
  Board board(board_size); //initialize a new board
  board.print();
  cout << endl << "1 or 2 human players? ";
  cin >> humans;
  if(humans == 1){
      cout << "Select AI \"difficulty\"/depth (default = 3) : ";
      cin >> difficulty;
      do{
          player.clear();
          cout << "X or O (X moves first): ";
          cin >> player;
          player = toupper(player[0]);
      }while(player != "X" && player != "O");
      Player human(player); //initializes human player to their piece
      AI ai(oppositePiece(human.piece), difficulty); //initializes ai player to opposite piece
      do{
          trace.clear();
          cout << "Display trace (Y/N): ";
          cin >> trace;
          trace = toupper(trace[0]);
      }while(trace != "Y" && trace != "N");
      booltrace = false;
      if(trace == "Y")
          booltrace = true;
      cout << endl << "You are " << human.piece;
      cout << endl << "AI is " << ai.piece << endl; 
      gameLoop(board, human, ai, booltrace); //game logic within the game is done here
  }else if(humans == 2){
      do{
          player.clear();
          cout << "X or O (X moves first): ";
          cin >> player;
          player = toupper(player[0]);
      }while(player != "X" && player != "O");
      Player human1(player); //initializes human player to their piece
      Player human2(oppositePiece(human1.piece)); //initializes player 2 to opposite piece
      cout << endl << "Player 1 is: " << human1.piece;
      cout << endl << "Player 2 is: " << human2.piece << endl; 
      gameLoop(board, human1, human2); //game logic within the game is done here   
  }
  cout << endl;
  return 0;
}
