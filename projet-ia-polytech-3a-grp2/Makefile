all: main board.o 


board.o: board.c board.h
	gcc -c board.c


main: main.c board.c board.h 
	gcc -o main main.c board.c 
