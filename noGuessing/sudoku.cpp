#include "sudoku.hpp"
#include <iostream>

void sudoku::print_board(){
		std::cout << "Board\n";
		for (int i = 0; i < BOARD_SIZE; ++i){
				for (int j = 0; j < BOARD_SIZE; ++j){
						std::cout << board[j][i] << " ";
				}
				std::cout << "\n"; 
		}
		std::cout << "Potential\n";
		for (int i = 0; i < BOARD_SIZE; ++i){
				for (int j = 0; j < BOARD_SIZE; ++j){
						std::cout << potential_values[j][i] << " ";
				}
				std::cout << "\n"; 
		}

}

uint16_t sudoku::full_value(){

		uint16_t toReturn = 0;
		for (uint16_t i = 1; i <= BOARD_SIZE; ++i) toReturn += get_bitwise_value(i);
		return toReturn;
}

void sudoku::set_values(){

}

void sudoku::handle_potential_values(){

		handle_square_potential();
		handle_vertical_potential();
		handle_horizontal_porential();


}

void sudoku::handle_square(int x, int y){

		uint16_t val = 0;
		for (int i = 0; i < BOARD_SIZE; ++i){
			val += get_bitwise_value(board[x + i%3][y + i/3]);
		}
		val = ~val;
		for (int i = 0; i < BOARD_SIZE; ++i){
				potential_values[x + i%3][y + i/3] &= val;
		}

		for (uint16_t i = 1; i < 10; ++i){
			val = get_bitwise_value(i);
			int count = 0;
			for (int j = 0; j < BOARD_SIZE; ++j){
				if (val & potential_values[x + j %3][y + j /3]) ++count;
			}
			if (count == 1){
				for (int j = 0; j < BOARD_SIZE; ++j){
						if (val & potential_values[x + j %3 ][y + j /3]) {
							potential_values[x + j %3][y + j /3] = 0;
							board[x + j % 3][y + j /3] = i;
						}
					}
			}
		}

}

void sudoku::handle_square_potential(){

		for (int i = 0; i < 3; ++i){
				for (int j = 0; j < 3; ++j){
						handle_square(3*i, 3*j);
				}
		}
}

void sudoku::handle_vertical_potential(){

		for (int i = 0; i < BOARD_SIZE; ++i){
				uint16_t val = 0;
				for (int j = 0; j < BOARD_SIZE; ++j){
						val += get_bitwise_value(board[i][j]);
				}
				val = ~val;
				for (int j = 0; j < BOARD_SIZE; ++j){
						potential_values[i][j] &= val;
				}
		}
		

		for (uint16_t i = 1; i < 10; ++i){
			uint16_t val = get_bitwise_value(i);
			for (int j = 0; j < BOARD_SIZE; ++j){
				int count = 0;
				for (int k = 0; k < BOARD_SIZE; ++k){
					if ((val & potential_values[j][k])) count++;
				}
				if (count == 1){
					for (int k = 0; k < BOARD_SIZE; ++k){
						if (val & potential_values[j][k]) {
							potential_values[j][k] = 0;
							board[j][k] = i;
						}
					}
				}
			}
		}
}


void sudoku::handle_horizontal_porential(){

		
		for (int i = 0; i < BOARD_SIZE; ++i){
				uint16_t val = 0;
				for (int j = 0; j < BOARD_SIZE; ++j){
						val += get_bitwise_value(board[j][i]);
				}
				val = ~val;
				for (int j = 0; j < BOARD_SIZE; ++j){
						potential_values[j][i] &= val;
				}
		}

		
	//Go through and check if it's the only instance of a possible value;
		for (uint16_t i = 1; i < 10; ++i){
			uint16_t val = get_bitwise_value(i);
			for (int j = 0; j < BOARD_SIZE; ++j){
				int count = 0;
				for (int k = 0; k < BOARD_SIZE; ++k){
					if ((val & potential_values[k][j])) count++;
				}
				if (count == 1){
					for (int k = 0; k < BOARD_SIZE; ++k){
						if (val & potential_values[k][j]) {
							potential_values[k][j] = 0;
							board[k][j] = i;
						}
					}
				}
			}
		}
}


sudoku::sudoku(std::istream &in){

		int c;
		int pos = 0;

		uint16_t val = 0;

		for (int i = 0; i < BOARD_SIZE + 1; ++i) val += get_bitwise_value(i);

		while(true){
				c = in.get();
				if (c == -1 || c == 10) break;

				board[pos % BOARD_SIZE][pos / BOARD_SIZE] = c - '0';
				if (c - '0' == 0)
					potential_values[pos % BOARD_SIZE][pos / BOARD_SIZE] = val;
				else
					potential_values[pos % BOARD_SIZE][pos / BOARD_SIZE] = 0;
					
				++pos;
		}
		if (pos != BOARD_SIZE*BOARD_SIZE){
				for (; pos < BOARD_SIZE*BOARD_SIZE; ++pos){
						board[pos %BOARD_SIZE][pos / BOARD_SIZE] = 0;
						potential_values[pos % BOARD_SIZE][pos / BOARD_SIZE] = val;
						std::cout << pos << " \n";
				}
		}

		for (int i = 1; i < BOARD_SIZE + 1; ++i) possible_values[i] = get_bitwise_value(i);

		handle_potential_values();
}

bool sudoku::is_solved(){
		uint16_t expected = full_value();

		for (int i = 0; i < BOARD_SIZE; ++i){
				uint16_t curr = 0;
				for (int j = 0; j < BOARD_SIZE; ++j) {
						curr += get_bitwise_value(board[i][j]);
				}
				if (expected != curr) return false;
		}
		return true;
}



void sudoku::cycle_again(){


		for (int i = 0; i < BOARD_SIZE; ++i){
				for (int j = 0; j < BOARD_SIZE; ++j){
						if (board[i][j] != 0) continue;
						for (int x  = 0 ; x < BOARD_SIZE; ++x){
								if (potential_values[i][j] == possible_values[x]){
										board[i][j] = x;
										potential_values[i][j] = possible_values[x];
										break;
								}
						}

				}
		}
		handle_potential_values();
}




uint16_t sudoku::get_bitwise_value(uint16_t val){
		if (val == 0) return 0;
		return 1 << (val - 1); 
}

bool sudoku::unsolveable(){


		return false;

}

