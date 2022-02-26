#include "sudoku.hpp"
#include <iostream>
#include <fstream>


//Helper text

//MAIN MAIN
int main(int argc, char * argv[]){
				if (argc < 2){
								std::cout << "Weird amount of arguments";
				}
		
				std::fstream * file = new std::fstream();
				file->open(argv[1]);

				sudoku *s = new sudoku( *file);

				std::cout << "DONE\n";
				while (!s->is_solved()){
								s->cycle_again();
								s->print_board();
				}

}
