#include "board.h"
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <stdio.h>
using namespace std; 

Board::Board(int size){
    
    //stores the board size in the object
    board_size = size; 
    
    //allocate memory for new board of that is a square of the input size
    cells = new int* [size];
    for(int i=0; i<size; ++i)
        cells[i] = new int [size];
    
    // Initialize the game cells to 0 (no moves)
    for(int row=0; row < size; ++row){
        for(int col=0; col < size; ++col){
            cells[col][row] = 0;
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
    int count=1;
    cout << endl;
    for (int row=0; row < board_size; ++row){ //every row
		for (int col = 0; col < board_size; ++col){ //every column
            if(cells[col][row] == 0){ //if the cell is not occupied
                //Adjust spacing for numbers length
                if(count <  10){
                    cout << " " << count;
                }else if(count < 100){
                    cout << " " << count;
                }else{
                    cout << count;
                }                
            }else{ //cell is occupied
                cout << " ";
                convertToPiece(cells[col][row]); //print X or O
            }
            if(col != board_size-1){ //if not the last cell print a '|'
                if(count < 10 || cells[col][row] != 0){
                    cout << " |";
                }else{
                    cout << "|";
                }
            }    
            ++count;
		}
        cout << endl; //new row
        if(row != board_size-1){ //last row doesn't need horizontal break lines
            for (int col=1; col < board_size; ++col)
                cout << "----";
            cout << "---" << endl;
        }
    }
}

//Converts numbers into letters
void Board::convertToPiece(int cell){
    switch(cell){
        case(1):
            printf("%c[%dm%s",0x1b,32,"X"); //prints green X
            printf("%c[%dm%s",0x1b,37,""); //sets text back to white
            break;
        case(-1):
            printf("%c[%dm%s",0x1b,31,"O"); //prints red O
            printf("%c[%dm%s",0x1b,37,"");//sets text back to white
            break;
        default:
            cout << " ";
    }
}

/*void Board::printMoves(){
    int count = 0;
    cout << endl << "Moves: ";
    for (int row=0; row < board_size; ++row){
        for(int col=0; col < board_size; ++col){
            ++count;
            if(cells[col][row] == 0){
                cout << endl << "Cell: " << count;
            }
        }
    }
}*/

vector<array<int,2>> Board::getMoves(){
    vector<array<int,2>> moves; //vector of x,y coordinates

    for (int row=0; row < board_size; ++row){
        for(int col=0; col < board_size; ++col){
            if(cells[col][row] == 0){ //cell not occupied
                moves.push_back(array<int, 2>{{col, row}}); //adds possible move to stack
            }
        }
    }
    return moves;
}

array<int,2> Board::validateMove(int move){
    int count = 0;
    if(move > 0 && move <= board_size*board_size){ //checks if the cell requested even exists
        for(int row=0; row < board_size; ++row){
            for(int col=0; col < board_size; ++col){
                ++count;
                if(count == move){ //converts cell number into x,y coordinates
                    if(cells[col][row] == 0){ //checks if its already occupied
                        return array<int,2>{{col,row}}; //allow the move
                    }else{
                        return array<int,2>{{-1,-1}}; //move rejected
                    }
                }
            }
        }
    }
    return array<int,2>{{-1,-1}};
}

void Board::insertMove(int player, int col, int row){
    cells[col][row] = player; //occupies cell by a player
}

int Board::win(){
    //checks for horizontal win states
    for(int row=0; row < board_size; ++row){
        for(int col=1; col < board_size; ++col){
            //if a cell is not occupied then a win is no possible in this row
            //if two cells are not occupied by the same player then a win is not possible in this row
            if(cells[col-1][row] == 0 || cells[col][row] != cells[col-1][row]){
                break;
            }else if(col == board_size-1){ //reached the end of the row without detecting change in player or empty cell = win
                return cells[col][row]; //return winning player
            }
        }
    }
    
    //Checks for any vertical win states
    for(int col=0; col < board_size; ++col){
        for(int row=1; row < board_size; ++row){
            //if a cell is not occupied then a win is no possible in this column
            //if two cells are not occupied by the same player then a win is not possible in this column
            if(cells[col][row-1] == 0 || cells[col][row] != cells[col][row-1]){
                break;
            }else if(row == board_size-1){ //reached the end of the column without detecting change in player or empty cell = win
                return cells[col][row]; //return winning player
            }
        }
    }
    
    //checks for '\' win states
    for(int both=1; both < board_size; ++both){
        //if a cell is not occupied then a win is no possible in this diagonal
        //if two cells are not occupied by the same player then a win is not possible in this diagonal
        if(cells[both-1][both-1] == 0 || cells[both][both] != cells[both-1][both-1]){
            break;
        }else if(both == board_size-1){//reached the end of the diagonal without detecting change in player or empty cell = win
            return cells[both][both];//return winning player
        }
    }
    
    //checks for '/' win states
    for(int col=1, row = board_size-2; col < board_size; ++col, --row){
        //if a cell is not occupied then a win is no possible in this diagonal
        //if two cells are not occupied by the same player then a win is not possible in this diagonal
        if(cells[col-1][row+1] == 0 || cells[col][row] != cells[col-1][row+1]){
            break;
        }else if(col == board_size-1){//reached the end of the diagonal without detecting change in player or empty cell = win
            return cells[col][row];//return winning player
        }
    }

	//checks for tie
	int no_tie = false;
	for (int row = 0; row < board_size; ++row){
		for (int col = 0; col < board_size; ++col){
			if (cells[col][row] == 0){ //if there is an open cell then the game can continue
				no_tie = true;
			}
			if (no_tie)
				break;
		}
		if (no_tie)
			break;
	}
	if (!no_tie) //if every cell is occupied but no previous win was triggered
		return 0; //0 = tie

    return 2; //2 = continue game
}

long Board::evaluate(){
	long score = 0; //single piece is worth 1 while consecutive pieces are worth *10
	long temp_score = 0;

	//evaluates rows
	for (int row = 0; row < board_size; ++row){ //for every row
		for (int col = 0; col < board_size; col++){ //look at every column
			if (cells[col][row] == 1){ //if a row is "X"
				temp_score = 1; //then positive score
			}
			else if (cells[col][row] == -1){ //if a row is "O"
				temp_score = -1; //then negative score
			}
			else{
				temp_score = 0; //empty cell
			}
			if (cells[col][row] != 0 && !(col + 1 >= board_size)){ //if the cell is not empty and not at end of row
				for (int i = col + 1; i < board_size; ++i, ++col){ //check every cell
					if (cells[i - 1][row] == cells[i][row]){ //if the next cell is the same player
						temp_score *= 10; //then score is worth *10
					}
					else{ //chain broken
						col = i; //continue where left off
						break;
					}
				}
			}
			score += temp_score; //add the score to the game state's total score
		}
	}

	//evaluates columns
	for (int col = 0; col < board_size; ++col){
		for (int row = 0; row < board_size; ++row){
			if (cells[col][row] == 1){
				temp_score = 1;
			}
			else if (cells[col][row] == -1){
				temp_score = -1;
			}
			else{
				temp_score = 0;
			}
			if (cells[col][row] != 0 && !(row + 1 >= board_size)){
				for (int i = row + 1; i < board_size; ++i, ++row){
					if (cells[col][i - 1] == cells[col][i]){
						temp_score *= 10;
					}
					else{
						row = i;
						break;
					}
				}
			}
			score += temp_score;
		}
	}

	//evaluates '\'
	for (int both = 0; both < board_size; ++both){ //increment x and y at the same rate
		if (cells[both][both] == 1){
			temp_score = 1;
		}
		else if (cells[both][both] == -1){
			temp_score = -1;
		}
		else{
			temp_score = 0;
		}
		if (cells[both][both] != 0 && !(both + 1 >= board_size)){
			for (int i = both + 1; i <board_size; ++i, ++both){
				if (cells[i - 1][i - 1] == cells[i][i]){
					temp_score *= 10;
				}
				else{
					both = i;
					break;
				}
			}
		}
		score += temp_score;
	}

	//evaluates '/'
	for (int col = 0, row = board_size - 1; col < board_size; ++col, --row){ //increments x and y inversely
		if (cells[col][row] == 1){
			temp_score = 1;
		}
		else if (cells[col][row] == -1){
			temp_score = -1;
		}
		else{
			temp_score = 0;
		}
		if (cells[col][row] != 0 && !(col + 1 >= board_size)){
			for (int i = col + 1, j = row - 1; i < board_size; ++i, ++col, --j, --row){
				if (cells[i - 1][j + 1] == cells[i][j]){
					temp_score *= 10;
				}
				else{
					col = i;
					row = j;
					break;
				}
			}
		}
		score += temp_score;
	}

	return score; //sum of all pieces and chains of pieces of a board
}
