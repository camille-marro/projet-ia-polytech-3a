#include <stdio.h>
//#include <malloc.h>
#include <assert.h>
#include <stdlib.h> 
#include <math.h>
#include "board.h"



Item *initGame(int difficulty)
{
  int i;
  Item *node;

  char *initial = (char*)malloc(MAX_BOARD*sizeof(char));

  for (int i = 0; i < MAX_BOARD; i++)
  {
    initial[i] = 0;
  }
  node = nodeAlloc();
  initBoard(node, initial);
  node->depth = 0;

  return node;
}


// print a board
void printBoard( Item *node )
{
  assert(node);
	printf("\n");
	for (int j=0; j<WH_BOARD; j++) if (j==0) printf(" ___"); else printf("____"); printf("\n");
	for (int i = 0 ; i < MAX_BOARD ; i++) {
    if (i%WH_BOARD == 0) printf("|");
    if (node->board[i] == 0) printf("   |");
    else printf("%2d |", node->board[i]);
    if (((i+1)%WH_BOARD) == 0) {
			printf("\n");
			for (int j=0; j<WH_BOARD; j++) if (j==0) printf(" ___"); else printf("____"); printf("\n");
		}
  }
	printf("\n");
}


// initialize node's state from a given board
void initBoard(Item *node, char *board) {
	assert( node );

	
	node->size = MAX_BOARD;
  node->board = calloc(MAX_BOARD, sizeof(char));
  
	/* Copy board */
  for (int i = 0; i < MAX_BOARD; i++)
  {
    node -> board[i] = board[i];
  }
  
}

// Return 0 if all numbers are placed. Otherwise the number of the ones well placed
// Ie: nb that still need to be placed.
double evaluateBoard(Item *node) {
  int nb = 0;
  
	
  return nb;
}

// Test if position pos is valid with respect to node's state
// Taquin -> UP ; DOWN ; RIGHT ; LEFT

int isValidPosition( Item *node, int pos )
{
  int i, j;
	i= pos /WH_BOARD;
  j= pos % WH_BOARD;
 
  if(node->board[pos] == 0)
  {
    if (i + 1 == HT_BOARD)
    {
      return 1; // POSITION VALIDE
    }
    else if (node->board[(i+1)*WH_BOARD+j] != 0)
    {
      return 1; // POSITION VALIDE
    }
  }
	 
	 return 0; // POSITION INVALIDE
}

// Return a new item where a new move is placed at position pos if possible. NULL if not valid
Item *getChildBoard( Item *node, int pos )
{
  Item *child_p = NULL;
  int l;

	if ( isValidPosition(node, pos) == 1 ) {
		

        /* allocate and init child node */
        child_p = nodeAlloc() ;
        initBoard(child_p, node->board) ;
		 
		/* Make move */
        child_p->board[pos] = 1;
        printBoard(child_p) ;


		/* link child to parent for backtrack */
        child_p->parent = node;

        child_p->depth = node->depth +1 ;
  }

  return child_p;
}
