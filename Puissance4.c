#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "board.h"

list_t openList_p;
list_t closedList_p;
int joueur=1;

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
            if(0) { //Si le joueur est une IA
                for (int i = 0; i < MAX_BOARD; i++) {
                    // recup le prochain possible cout
                    // dans notre cas 7 possibilités ou moins
                    //
                    child_p = getChildBoard(cur_node, i, joueur); // le prochain possible cout

                    if (child_p != NULL) {

                    }
                }
            }
            else{ //Si le joueur est humain :
                printBoard(cur_node);
                int choix=-1;
                while(choix<0 || choix>WH_BOARD-1){
                    printf("Joueur %d, choisissez un coup entre 0 et %d\n", joueur, WH_BOARD-1);
                    scanf("%d",&choix);
                }

            }
        }
    }
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