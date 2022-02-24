#ifndef SODUKO_H
#define SODUKO_H

#include <istream>
#include <cstdint>
#define BOARD_SIZE 9


class soduko{

		private: 

		uint16_t board[BOARD_SIZE][BOARD_SIZE];
		uint16_t potential_values[BOARD_SIZE][BOARD_SIZE];
		uint16_t possible_values[BOARD_SIZE];
		

		//Used to go through the list of potential_values and set values where possible.
		void set_values();
		//Go through and filter potential values
		void handle_potential_values();
		//Return value with the bit at position val set
		uint16_t get_bitwise_value(uint16_t val);
		//Return sum of all values 
		uint16_t full_value();

		void handle_square_potential();
		void handle_vertical_potential();
		void handle_horizontal_porential();
		void handle_square(int x, int y);

		public:
		
		soduko(std::istream&);
		//Return true if the soduko is solved
		bool is_solved();
		//Do one cycle of solving 
		void cycle_again();
		//Get the integer list
		//Returns true if it cant be solved
		bool unsolveable();

		void print_board();
};

#endif
