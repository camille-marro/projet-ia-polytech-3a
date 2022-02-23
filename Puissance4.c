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

int minimax(Item *Node, int depth, int joueur) {
    int value;
    if (depth == 0 || evaluateBoard(Node, Node->pos) != 0) return Node->score;
    if (joueur == 2) {
        value = -100000;
        for (int i = 0; i < WH_BOARD; i++) {
            Node->score = minimax(getChildBoard(Node, CasePlusBasse(Node, i), 2), depth - 1, 1);
            value = max(value, Node->score);
        }
    }
    else {
        value = 100000;
        for (int i = 0; i < WH_BOARD; i++) {
            Node->score = minimax(getChildBoard(Node, CasePlusBasse(Node, i), 1), depth - 1, 2);
            value = min(value, Node->score);
        }
    }
    return value;
}


//int minimax(Item *Node, int depth, int joueur)
//{
//    int i;
//    int value, childscore, pos;
//    Item *child = nodeAlloc();
//    Item* best_child;
//    if (depth == 0 || evaluateBoard(Node, Node->pos) == joueur)
//    {
//        //printf("l'evaluation donne %f\n", evaluateBoard(Node, Node->pos));
//        pos=Node->pos;
//        Node->score = score(Node, pos, joueur);
//        //printf("Le score du noeud est %d\n",Node->score);
//        return Node->score;
//    }
//    //printBoard(Node);
//    if (joueur == 2)
//    {
//        printf("--- j2\n");
//        value = -10000;
//        for (i = 0; i < WH_BOARD; i++)
//        {
//            pos = CasePlusBasse(Node, i) ; //recup pos de la ieme colonne
//            child = getChildBoard(Node,pos,joueur);
//            //printBoard(child);
//            //printf("pos is %d\n", pos);
//            if(child!=NULL) {
//                childscore = minimax(child, depth - 1, 1);
//                if (childscore > value) {
//                    best_child = child; //inutile pour le moment (pas sûr que ça serve)
//                    value = childscore;
//                    //printf("Colonne %d : score %d\n", i, value);
//                }
//            }
//        }
//    }
//    else
//    {
//        //printf("j1\n");
//        value = 10000;
//        for (i = 0; i < WH_BOARD; i++)
//        {
//            pos = CasePlusBasse(Node, i);
//            //printf("pos is %d\n", pos);
//            child = getChildBoard(Node,pos,joueur);
//            //printBoard(child);
//            if(child!=NULL) {
//                childscore = minimax(child, depth - 1, 2);
//                if (childscore < value) {
//                    best_child = child;
//                    value = childscore;
//                    //printf("Colonne %d : score %d\n", i, value);
//                }
//            }
//        }
//    }
//    Node->score=value;
//    return value;
//}

void parcours(void) {
    int i, depth;
    Item *cur_node;
    int choix, pos=-1, resultat; //L'initialisation de pos sert à bloquer la première évaluation de la board
    cur_node = popFirst(&openList_p); // A déplacer vers la section IA ? Sert ici à récupérer initial_state dans cur_node.
    int value, childscore;
    Item *child;
    Item* best_child;
    while (1) { // Ce while n'est plus valable si on met un joueur humain (seule l'IA se sert de OpenList)

        //addLast(&closedList_p, cur_node);
        resultat = evaluateBoard(cur_node, pos);
        if (resultat == 1) {
            printf("Le joueur 1 a gagné\n");
            printBoard(cur_node);
            return;
        }
        else if (resultat == 2){
            printf("Le joueur 2 a gagné\n");
            printBoard(cur_node);
            return;
        }
        else {
            if(joueur == 2) { //Si le joueur est une IA
                //for (int i = 0; i < MAX_BOARD; i++) {
                //    // recup le prochain possible cout
                //    // dans notre cas 7 possibilités ou moins
                //    //
                //     = getChildBoard(cur_node, i, joueur); // le prochain possible cout
//
                //    if (child_p != NULL) {
//
                //    }
                //}
                printf("===================\n");
                value = -10000;
                depth=3;
                for (i = 0; i < WH_BOARD; i++)
                {
                    pos = CasePlusBasse(cur_node, i) ;
                    child = getChildBoard(cur_node,pos,joueur); //fait le move dans la ieme colonne
                    if(child!=NULL) {
                        childscore = minimax(child, depth - 1, 1);
                        //printf("%d - score  : %d\n", i, childscore);
                        if (childscore > value) {
                            best_child = child;
                            value = childscore;
                        }
                    }
                }
                cur_node->score = value;
                cur_node = best_child; //On joue le coup
                pos = cur_node->pos; //On rétablit pos qui sauvegarde le dernier coup joué (pour evaluateBoard)
                //clrscr();
                joueur = 1;
                printf("fin tour IA\n");
            }
            else{ //Si le joueur est humain :

                choix=-1;
                while(CasePlusBasse(cur_node, choix) == -1){ //CasePlusBasse revoie -1 si la colonne n'existe pas (hors limites) ou si la colonne est remplie
                    printf("Joueur %d, choisissez un coup entre 0 et %d\n", joueur, WH_BOARD-1);
                    scanf("%d",&choix);
                }
                pos = CasePlusBasse(cur_node, choix);
                cur_node = getChildBoard(cur_node, pos, joueur);
                //clrscr();
                joueur = 2;
            }
            printBoard(cur_node);
        }
    }
}



int main()
{
    /* init lists */
    initList(&openList_p);
    initList(&closedList_p);

    printf("\nInitial:");
    Item *initial_state = initGamePui();
    printBoard( initial_state );

    // printf("\nSearching ...\n");
    // addLast( &openList_p, initial_state );
    // bfs();
    // printf("Finished!\n");
    //initial_state->pos = 35;

    printf("\nSearching ...\n");
    addFirst (&openList_p, initial_state );
    parcours();
    //initial_state->board[35] = 1;
    //minimax(initial_state, 3, 2);
    //printf("Le score du board est %d ",score(initial_state,35,1));
    printf("Finished!\n");

    /* clean lists */
    cleanupList( &openList_p );
    cleanupList( &closedList_p );

    /*------------------------------------------------------------*/
    /*------------------------------------------------------------*/


    return 0;
}
