#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
//#include <malloc.h>

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
  return;
}



void bfs( void )
{
  Item *cur_node, *child_p, *temp;
  int i;

	/* While items are on the open list */
	while ( listCount(&openList_p) ) 
	{ 
		/* Get the first item on the open list */
		cur_node = popFirst(&openList_p);

		/* Add it to the "visited" list */
        addLast( &closedList_p, cur_node );
      
    	/* Do we have a solution? */
    	if ( evaluateBoard(cur_node) == 0.0 ) 
    	{
      		showSolution(cur_node);
      		return;
    	} 
    	else 
    	{
      		/* Enumerate possible movements */
      		for(i = 0; i < MAX_BOARD; i++) 
      		{
        		child_p = getChildBoard( cur_node, i );

        		/* Ignore this child if already visited or invalid */
        		if (child_p != NULL && onList(&closedList_p, child_p->board) == NULL) 
        		{
                	/* Add child node to openList */
                	addLast( &openList_p, child_p );
            	}
        	}
      
    	}
  	}
  return;
}

void dfs( void )
{
    Item *cur_node, *child_p, *temp;
    int i;
    
    /* While items are on the open list */
    while ( listCount(&openList_p) ) 
    {        
        /* Get the first item on the open list */
        cur_node = popFirst(&openList_p);
        
        /* Add it to the "visited" list */
        addLast( &closedList_p, cur_node );

        /* Do we have a solution? */
        if ( evaluateBoard(cur_node) == 0.0 ) 
        {
            showSolution(cur_node);
            return;  
        } 
        else 
        {
            /* Enumerate possible movements */
            for(i = 0; i < MAX_BOARD; i++) 
            {
                child_p = getChildBoard( cur_node, i );
                
                /* Ignore this child if already visited or invalid */
                if (child_p != NULL && onList(&closedList_p, child_p->board) == NULL) 
                { 
                    /* Add child node to openList */
                    addFirst( &openList_p, child_p );  
                }
            }
        }
    }   
    return;
}

int main()
{
    
    /* init lists */
    initList(&openList_p);
    initList(&closedList_p);

    char j1[20];
    char j2[20];
      printf(   "\n*******************\n");
	printf(" * *\n");
	printf(" * *\n");
	printf(" * PUISSANCE 4 *\n");
	printf(" * *\n");
	printf(" * *\n");
	printf(" *******************\n");
    Item *initial_state = initGame();
	Item *NODE ;
	Item *NODE1, *NODE2 ,*NODE3, *NODE4 ;
    printBoard( initial_state );
	 

   NODE= getChildBoard( initial_state, 41 );
   NODE1=getChildBoard( NODE, 34 );
   NODE2=getChildBoard( NODE1, 40 );
   NODE3=getChildBoard( NODE2, 27 );
   NODE4=getChildBoard( NODE3, 20);

    
    /* clean lists */
    cleanupList( &openList_p );
    cleanupList( &closedList_p );

    return 0;
}
