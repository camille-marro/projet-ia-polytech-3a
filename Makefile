all: Puissance4 board.o list.o 

list.o: list.c list.h
	gcc -c list.c

board.o: board.c board.h
	gcc -c board.c
 

Puissance4: Puissance4.c board.c list.c board.h list.h item.h
	gcc Puissance4.c board.c list.c $(sdl2-config --cflags --libs) -o Puissance4