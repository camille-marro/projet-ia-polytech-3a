#include "list.h"

#define RANDINIT()  srand(time(NULL))
#define RANDOM()  ((float)rand() / (float)RAND_MAX)
#define RANDMAX(x)  (int)((float)(x)*rand()/(RAND_MAX+1.0))

#define WH_BOARD 7 //5
#define HE_BOARD 6
#define MAX_BOARD WH_BOARD*HE_BOARD //25



Item *initGame();

Item* initGamePui();

void initBoard(Item *node, char *board);

Item *getChildBoard( Item *node, int pos, int joueur);

double evaluateBoard( Item *node, int dercoup);

int ligne(char* board, int joueur, int ii, int jj);

int colonne(char* board, int joueur, int ii, int jj);

int diagonale(char* board, int joueur, int ii, int jj);

int antidiagonale(char* board, int joueur, int ii, int jj);

Item *initGameKnight(); 

Item *getChildBoardKnight( Item *node, int pos );

Item *getChildBoardKnightUCS( Item *node, int pos );

double evaluateBoardKnight( Item *node );

void printBoard( Item *board );

int isValidPosition( Item *node, int pos );

int CasePlusBasse(Item* node, int i);

void clrscr();

int ConvertToScore(int nbrepion);

int score(Item *node, int dercoup, int joueur);

int min(int a, int b);

int max(int a, int b);