#include "board.h"
#include <iostream>
#include <vector>
#include <array>
#include <string>
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
    //for every cell
    cout << endl;
    for (int row=0; row < board_size; ++row){ //every row
		for (int col = 0; col < board_size - 1; ++col){ //every column but the last
			cout << " " << convertToPiece(cells[col][row]) << " |";
		}
        cout << " " << convertToPiece(cells[board_size-1][row]); //last column
        cout << endl;
        if(row != board_size-1){ //last row doesn't need horizontal break lines
            for (int col=1; col < board_size; ++col)
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
        case(-1):
            return "O";
            break;
        default:
            return " ";
    }
}

void Board::printMoves(){
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
}

vector<array<int,2>> Board::getMoves(){
    vector<array<int,2>> moves;

    for (int row=0; row < board_size; ++row){
        for(int col=0; col < board_size; ++col){
            if(cells[col][row] == 0){
                moves.push_back(array<int, 2>{{col, row}});
            }
        }
    }
    return moves;
}

array<int,2> Board::validateMove(int move){
    int count = 0;
    if(move > 0 && move <= board_size*board_size){
        for(int row=0; row < board_size; ++row){
            for(int col=0; col < board_size; ++col){
                ++count;
                if(count == move){
                    if(cells[col][row] == 0){
                        return array<int,2>{{col,row}};
                    }else{
                        return array<int,2>{{-1,-1}};
                    }
                }
            }
        }
    }
    return array<int,2>{{-1,-1}};
}

void Board::insertMove(int player, int col, int row){
    cells[col][row] = player;
}

int Board::win(){
    //checks for horizontal win states
    for(int row=0; row < board_size; ++row){
        for(int col=1; col < board_size; ++col){
            if(cells[col-1][row] == 0 || cells[col][row] != cells[col-1][row]){
                break;
            }else if(col == board_size-1){
                return cells[col][row];
            }
        }
    }
    
    //Checks for any vertical win states
    for(int col=0; col < board_size; ++col){
        for(int row=1; row < board_size; ++row){
            if(cells[col][row-1] == 0 || cells[col][row] != cells[col][row-1]){
                break;
            }else if(row == board_size-1){
                return cells[col][row];
            }
        }
    }
    
    //checks for '\' win states
    for(int both=1; both < board_size; ++both){
        if(cells[both-1][both-1] == 0 || cells[both][both] != cells[both-1][both-1]){
            break;
        }else if(both == board_size-1){
            return cells[both][both];
        }
    }
    
    //checks for '/' win states
    for(int col=1, row = board_size-2; col < board_size; ++col, --row){
        if(cells[col-1][row+1] == 0 || cells[col][row] != cells[col-1][row+1]){
            break;
        }else if(col == board_size-1){
            return cells[col][row];
        }
    }

	//checks for tie
	int no_tie = false;
	for (int row = 0; row < board_size; ++row){
		for (int col = 0; col < board_size; ++col){
			if (cells[col][row] == 0){
				no_tie = true;
			}
			if (no_tie)
				break;
		}
		if (no_tie)
			break;
	}
	if (!no_tie)
		return 0;

    return 2;
}

long Board::evaluate(){
	long score = 0;
	long temp_score = 0;

	//evaluates rows
	for (int row = 0; row < board_size; ++row){
		for (int col = 0; col < board_size; col++){
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
				for (int i = col + 1; i < board_size; ++i, ++col){
					if (cells[i - 1][row] == cells[i][row]){
						temp_score *= 10;
					}
					else{
						col = i;
						break;
					}
				}
			}
			score += temp_score;
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
	for (int both = 0; both < board_size; ++both){
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
	for (int col = 0, row = board_size - 1; col < board_size; ++col, --row){
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

	return score;
}