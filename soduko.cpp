#include "soduko.hpp"
#include <iostream>

void soduko::print_board(){
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

uint16_t soduko::full_value(){
		
		uint16_t toReturn = 0;
		for (uint16_t i = 1; i <= BOARD_SIZE; ++i) toReturn += get_bitwise_value(i);
		return toReturn;
}

void soduko::set_values(){

}

void soduko::handle_potential_values(){

		handle_square_potential();
		handle_vertical_potential();
		handle_horizontal_porential();
		

}

void soduko::handle_square(int x, int y){
		
		uint16_t val = 0;
		for (int i = 0; i < BOARD_SIZE; ++i){
				val += get_bitwise_value(board[x + i%3][y + i/3]);
		}
		val = ~val;
		for (int i = 0; i < BOARD_SIZE; ++i){
				potential_values[x + i%3][y + i/3] &= val;
		}
}

void soduko::handle_square_potential(){

		for (int i = 0; i < 3; ++i){
				for (int j = 0; j < 3; ++j){
						handle_square(3*i, 3*j);
				}
		}
}

void soduko::handle_vertical_potential(){

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

}

		
void soduko::handle_horizontal_porential(){

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
}


		
soduko::soduko(std::istream &in){

		int c;
		int pos = 0;

		uint16_t val = 0;
				
for (int i = 0; i < BOARD_SIZE + 1; ++i) val += get_bitwise_value(i);

		while(true){
				c = in.get();
				if (c == -1 || c == 10) break;
				
				board[pos % BOARD_SIZE][pos / BOARD_SIZE] = c - '0';
				potential_values[pos % BOARD_SIZE][pos / BOARD_SIZE] = val;
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

bool soduko::is_solved(){
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



void soduko::cycle_again(){
		
		
		for (int i = 0; i < BOARD_SIZE; ++i){
				for (int j = 0; j < BOARD_SIZE; ++j){
						if (board[i][j] != 0) continue;
						for (int x = 1; x < BOARD_SIZE +1; ++x){
								if (potential_values[i][j] == possible_values[x]){
										board[i][j] = x;
										potential_values[i][j] = 0;
										break;
								}
						}
				
				}
		}
		handle_potential_values();

}




uint16_t soduko::get_bitwise_value(uint16_t val){
		if (val == 0) return 0;
		return 1 << (val - 1); 
}

bool soduko::unsolveable(){

		
		return false;

}

