#ifndef _PUISSANCE_H
#define _PUISSANCE_H
#define WH_BOARD 7 
#define HT_BOARD 6
#define MAX_BOARD WH_BOARD * HT_BOARD

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef int bool;
typedef char Pion;
typedef Pion Board[HT_BOARD][WH_BOARD];



void initGame(Board game);
void printBoard(Board game);
bool valid_colonne(Board game, int j);
int lower_case(Board game, int j);
void add_Pion(Board game, int choice, int turn);
bool ligne(Board game, int ii, int jj);
bool colonne(Board game, int ii, int jj);
bool oblique_right(Board game, int ii, int jj);
bool oblique_left(Board game, int ii, int jj);
bool evaluate_board(Board game);

int valid_choice(Board game, int choix);
void clrscr();


#endif