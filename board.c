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


Item* initGamePui(){
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
double evaluateBoard(Item* node, int dercoup) { //Regarde si autour du dernier coup, il y a des alignements
    if(dercoup==-1){
        printf("Pas de dernier coup\n");
        return 0;
    }
    int derjoueur = node->board[dercoup]; //Récupère le numéro du joueur
    int ii=dercoup/WH_BOARD;
    int jj=dercoup % WH_BOARD;
    if( ligne(node->board, derjoueur, ii, jj)) return derjoueur;
    else if (colonne(node->board, derjoueur, ii, jj)) return derjoueur;
    else if(diagonale(node->board, derjoueur, ii, jj)) return derjoueur;
    else if(antidiagonale(node->board, derjoueur, ii, jj)) return derjoueur;
    else return 0;
}

int ligne(char* board, int joueur, int ii, int jj){ //Regarde si pour un joueur donné, il y a 4 pions collés comprenant le dernier posé
    int nb=1; //Le "premier" pion est le dernier posé
    int j=jj-1;
    //Vérifier des deux côtés du dernier pion posé est nécessaire car on peut compléter une chaîne de 4 en posant un pion au milieu
    while(j>=0 && board[ii*WH_BOARD+j]==joueur){ //Vérification à gauche
        nb+=1;
        j-=1;
    }
    j=jj+1;
    while(j<WH_BOARD && board[ii*WH_BOARD+j]==joueur){ //Vérif à droite
        nb+=1;
        j+=1;
    }
    if(nb>=4) return 1;
    else return 0;
}

int colonne(char* board, int joueur, int ii, int jj){
    int nb=1;
    int i=ii-1;
    while(i>=0 && board[i*WH_BOARD+jj]==joueur){
        nb+=1;
        i-=1;
    }
    i=ii+1;
    while(i<HE_BOARD && board[i*WH_BOARD+jj]==joueur){ //Techniquement la vérification vers le haut ne sert à rien, mais je la mets pour le principe
        nb+=1;
        i+=1;
    }
    if(nb>=4) return 1;
    else return 0;
}

int diagonale(char* board, int joueur, int ii, int jj){ //Axe haut gauche - bas droit
    int nb=1;
    int i=ii-1;
    int j=jj-1;
    while(i>=0 && j>=0 && board[i*WH_BOARD+j]==joueur){ //Haut gauche
        nb+=1;
        i-=1;
        j-=1;
    }
    i=ii+1;
    j=jj+1;
    while(i<HE_BOARD && j<WH_BOARD && board[i*WH_BOARD+j]==joueur){ //Bas droit
        nb+=1;
        i+=1;
        j+=1;
    }
    if(nb>=4) return 1;
    else return 0;
}

int antidiagonale(char* board, int joueur, int ii, int jj){ //Axe bas gauche - haut droit
    int nb=1;
    int i=ii+1;
    int j=jj-1;
    while(i<HE_BOARD && j>=0 && board[i*WH_BOARD+j]==joueur){ //Bas gauche
        nb+=1;
        i+=1;
        j-=1;
    }
    i=ii-1;
    j=jj+1;
    while(i>=0 && j<WH_BOARD && board[i*WH_BOARD+j]==joueur){ //Haut droit
        nb+=1;
        i-=1;
        j+=1;
    }
    if(nb>=4) return 1;
    else return 0;
}

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
    if(j<0 || j>WH_BOARD) return -1; //Si j est incorrect, renvoie -1
    for(int i = HE_BOARD-1;i>0;i--)
    {
        if(node->board[i*WH_BOARD + j]==0)
        {
            return i*WH_BOARD + j;
        }
    }
    return -1; //Cas où la colonne j est complètement remplie
}

Item *getChildBoard( Item *node, int pos, int joueur)
{
    Item *newNode = NULL;

    if ( /*isValidPosition(node, pos)*/ 1 ) {

        /* allocate and init child node */
        newNode = nodeAlloc();
        initBoard(newNode, node->board);
        newNode->depth += 1;

        /* Make move */
        newNode->board[pos] = joueur;

        /* link child to parent for backtrack */
        newNode->parent = node;
    }

    return newNode;
}
