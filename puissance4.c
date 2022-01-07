#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "board.h"

list_t openList_p;
list_t closedList_p;

void showSolution( Item *goal )
{
    int i = 0, j;

    printf("\nSolution:");

    while (goal) {
        printBoard( goal );
        goal = goal->parent;
        i++;
    }

    printf("\nLength of the solution = %d\n", i-1);
    printf("Size of open list = %d\n", openList_p.numElements);
    printf("Size of closed list = %d\n", closedList_p.numElements);
}

void parcours(void) {
    Item *cur_node, *child_p;
    while (listCount(&openList_p)) { // tant que y'a des trucs dans open list
        cur_node = popFirst(&openList_p);

        addLast(&closedList_p, cur_node);
        if (evaluateBoard(cur_node) == 1.0) {
            showSolution(cur_node);
            return;
        } else {
            for (int i = 0; i < MAX_BOARD; i++) {
                // recup le prochain possible cout
                // dans notre cas 7 possibilités ou moins
                //
                child_p = getChildBoard(cur_node, i); // le prochain possible cout

                if (child_p != NULL) {

                }
            }
        }
    }
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


int main()
{
    /* init lists */
    initList(&openList_p);
    initList(&closedList_p);


    printf("\nInitial:");
    Item *initial_state = initGame();
    printBoard( initial_state );

    // printf("\nSearching ...\n");
    // addLast( &openList_p, initial_state );
    // bfs();
    // printf("Finished!\n");

    printf("\nSearching ...\n");
    addFirst (&openList_p, initial_state );
    printf("J'adore les arbres morts\n");
    printf("Finished!\n");

    /* clean lists */
    cleanupList( &openList_p );
    cleanupList( &closedList_p );

    return 0;
}

