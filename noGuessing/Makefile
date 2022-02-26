
prog: main.o soduko.o
	g++ -o prog main.o soduko.o -g

main.o: main.cpp
	g++ -c main.cpp -g

soduko.o: soduko.cpp
	g++ -c soduko.cpp -g

clean:
	rm -f *.o
	rm -f prog
