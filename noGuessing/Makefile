
prog: main.o sudoku.o
	g++ -o prog main.o sudoku.o -g

main.o: main.cpp
	g++ -c main.cpp -g

sudoku.o: sudoku.cpp
	g++ -c sudoku.cpp -g

clean:
	rm -f *.o
	rm -f prog
