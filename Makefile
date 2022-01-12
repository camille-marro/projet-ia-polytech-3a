all: taquin board.o list.o

list.o: list.c list.h
	gcc -c list.c

board.o: board.c board.h
	gcc -c board.c

 

taquin: taquin.c board.c list.c board.h list.h item.h
	gcc -o taquin taquin.c board.c list.c
