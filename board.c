#include <stdio.h>
//#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"



// Initialize a new Game for the nQueens problem: an empty board..
Item *initGame()
{
    int i;
    Item *node;

    char *initial = (char*)malloc(MAX_BOARD*sizeof(char));
    for (int i=0; i<MAX_BOARD; i++) initial[i] = 0;

    node = nodeAlloc();
    initBoard(node, initial);

    node->f = 0;
    node->depth = 0;

    return node;
}

//Item *initGameKnight()
//{
//  int i;
//  Item *node;
//
//	char *initial = (char*)malloc(MAX_BOARD*sizeof(char));
//	for (int i=0; i<MAX_BOARD; i++) initial[i] = 0;
//  initial[0] = 2;
//
//  node = nodeAlloc();
//  node->blank = 0;
//	initBoard(node, initial);
//
//  node->depth = 0;
//
//  return node;
//}

Item* InitGamePui(){
    int i;
    Item* node;
    char* initial = (char*)malloc( MAX_BOARD * sizeof(char));
    for (int i=0; i<MAX_BOARD; i++) initial[i] = 0;
    node = nodeAlloc();
    node->blank = 0;
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
    // on copy board dans node->board
    for (int i = 0; i < MAX_BOARD; i++) {
        node->board[i] = board[i];
    }
}

// Return 0 if all queens are placed. Positive otherwise
// Ie: nb queens that still need to be placed.
double evaluateBoard(Item *node) {
    int nb = WH_BOARD;
    for (int i = 0; i < MAX_BOARD; i++) {
        if (node->board[i] == 1) nb -= 1;
    }
    return nb;
}

// Return 0 if knight is on the last case, return 1 else
//double evaluateBoardKnight(Item *node) {
//  if (node == NULL) return 1;
//  if(node->board[MAX_BOARD-1] == 2) {
//    return 0;
//  }
//  return 1;
//}


/*
  node : pour recup le board
  pos : la position du possible prochain mouv
  return 1 si la pos est valide 0 sinon
*/

//int isValidPositionKnight (Item *node, int pos){
//  if (node == NULL) return 0;
//  int ii = pos / WH_BOARD;
//  int jj = pos % WH_BOARD;
//
//  for (int i = 0; i < WH_BOARD; i++) {
//    for (int j = 0; j < WH_BOARD; j++) {
//      if (node->board[i*WH_BOARD + j] == 2) {
//        if (abs(i - ii) * abs (j - jj) == 2 ) return 1;
//      }
//    }
//  }
//  return 0;
//}
// Test if position pos is valid with respect to node's state
// nQueens -> not same row ; not same column ; not same diagonal

int isValidPosition( Item *node, int pos )
{
    int ii = pos / WH_BOARD;
    int jj = pos % WH_BOARD;

    if (CasePlusBasse(node, jj) == ii) {
        return 1;
    } else return 0;
}

int CasePlusBasse(Item* node, int j) //Renvoie la case libre la plus basse de la colonne j
{

    for(int i = HE_BOARD-1;i>0;i--)
    {
        if(node->board[i*WH_BOARD + j]==0)
        {
            return i*WH_BOARD + j;
        }
    }
    return -1; //Cas où la colonne j est complètement remplie
}

//Item *getChildBoardKnightUCS(Item *node, int pos) {
//  Item *newNode = NULL;
//  if (isValidPositionKnight(node, pos)) {
//    newNode = nodeAlloc();
//    initBoard(newNode, node->board);
//    newNode->depth += 1;
//    newNode->f = node->f + 1;
//
//    newNode->board[pos] = 2;
//    newNode->board[node->blank] = 1;
//
//    newNode->blank = pos;
//
//    newNode->parent = node;
//  }
//  return newNode;
//
//}

//Item *getChildBoardKnight(Item *node, int pos) {
//  Item *newNode = NULL;
//  if (isValidPositionKnight(node, pos)) {
//    newNode = nodeAlloc();
//    initBoard(newNode, node->board);
//    newNode->depth += 1;
//
//    newNode->board[pos] = 2;
//    newNode->board[node->blank] = 1;
//
//    newNode->blank = pos;
//
//    newNode->parent = node;
//  }
//  return newNode;
//}

// Return a new item where a new queen is added at position pos if possible. NULL if not valid
Item *getChildBoard( Item *node, int pos, int joueur)
{
    Item *newNode = NULL;

    if ( isValidPosition(node, pos) ) {

        /* allocate and init child node */
        newNode = nodeAlloc();
        initBoard(newNode, node->board);
        newNode->depth += 1;

        /* Make move */
        newNode->board[pos] = 1;

        /* link child to parent for backtrack */
        newNode->parent = node;
    }

    return newNode;
}
