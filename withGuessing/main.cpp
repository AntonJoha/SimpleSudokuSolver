#include <iostream>
#include <fstream>

typedef struct board{
	
	uint16_t table[9][9] = {0};

}board_t;

void print_board(board_t);

void solve(board_t);

board_t init_board(std::istream &file){
	
	board_t toReturn;
	int pos = 0;
	while (true){

		char c = file.get();

		if( c == '\0' || c == '\n') break;

		toReturn.table[pos % 9][pos / 9] = c - '0';

		++pos;
	}
	return toReturn;
}



//MAIN MAIN
int main(int argc, char * argv[]){
	if (argc < 2){
		std::cout << "Weird amount of arguments";
		return 1;
	}
		
	std::fstream * file = new std::fstream();
	file->open(argv[1]);
	
	board_t board = init_board(*file);
	
	file->close();
	
	solve(board);
}


bool can_place(const int x,const int y,const uint16_t sought, const board_t &board){
	
	int xFirst = x/3;
	xFirst *=3;

	int yFirst = y/3;
	yFirst *= 3;

	for (int i = 0; i < 9; ++i){
		if (board.table[x][i] == sought) return false;
		if (board.table[i][y] == sought) return false;
		if (board.table[xFirst + i %3][yFirst + i /3] == sought) return false;
	}
	return true;
}

void solve(board_t board){
	
	for (int i = 0; i < 81; ++i){
		if (board.table[i % 9][i / 9] != 0) continue;
		for (int j = 1; j < 10; ++j){
			if (can_place(i % 9, i / 9 , j, board)){
				board.table[i %9][i/9] = j;
				solve(board);
				board.table[i %9][i/9] = 0;
			}
		}
		return;
	}
	print_board(board);
}

void print_board(board_t board){
	std::cout << "------------------------------------\n";
	for (int i = 0; i < 81;++i){
		std::cout << board.table[i % 9][i / 9] << " ";
		if (i % 9 == 8) std::cout << "\n";
	}
	std::cout << "----------------------------------\n";
}
