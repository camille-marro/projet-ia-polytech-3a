#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "board.h"

/* Item Functions */ 

/*==============================================================*/
Item *nodeAlloc()
{
  Item *node;

  node = (Item *) malloc( sizeof(Item) );
  assert(node);

  node->parent = NULL;
  node->prev = NULL;
  node->next = NULL;
  node->f = node->g = node->h = (double)0.0;

  return node;
}

/*==============================================================*/
void freeItem( Item *node )
{
  if (node && node->board) free(node->board);
	if (node) free(node);
}


/*==============================================================*/
void initList( list_t *list_p )
{
  //if (list_p == NULL) list_p = malloc(sizeof(list_t));
	assert(list_p);
  list_p->numElements = 0;
  list_p->first = NULL;
  list_p->last = NULL;
}

/*==============================================================*/
int listCount( list_t *list )
{
	return list->numElements;
}

/*==============================================================*/
// return an item with corresponding board , or null
/*
Item* onList( list_t *list, char *board)
{
	Item *item = list -> first;
	while (item) 
	{
    	if (strncmp(item -> board, board, strlen(board)) == 0)
    	{
    		return item;
    	}
    	item = item->next;
  	}
  return NULL;
}
*/

/*==============================================================*/
Item* onList( list_t *list, char *board)
{
    Item *item = list->first;
    int i ;
    
    while(item!=NULL){
        i=0;
        while(i<MAX_BOARD && item->board[i]==board[i]){
            i++;
        }
        if(i==MAX_BOARD)
        {return item ;}
    
    item = item->next ;
    }

  return NULL;
}
/*==============================================================
// return and remove first item
Item *popFirst( list_t *list ) //
{
	assert(list);
	Item *item = NULL;
	item = list -> first;
	list -> first = item -> next;
	list -> first -> prev = NULL;
	list -> numElements--;
	return item;
}

==============================================================
// return and remove last item
Item *popLast( list_t *list ) //
{
	assert(list);
	Item *item = NULL;
	item = list -> last;
	list -> last = item -> prev;
	list -> last -> next = NULL;
	list -> numElements--;
  return item;
}
*/
/*==============================================================*/
// return and remove last item
Item *popLast( list_t *list ) //
{
    if (list -> numElements == 0)
        return NULL ;
    
    Item *item = list->last ;
    
    if (list -> numElements == 1){
        list->first = NULL;
        list->last = NULL;
    }
    
    else{
        list->last = list->last->prev ;
        list->last->next = NULL ;
    }
        
    list -> numElements-- ;
    
    return item ;
}

/*==============================================================*/
// return and remove first item
Item *popFirst( list_t *list ) //
{
    if (list -> numElements == 0)
        return NULL ;
    
    Item *item = list->first ;
    
    if (list -> numElements == 1)
	{
        list->first = NULL;
        list->last = NULL;
    }
    
    else{
        list->first = list->first->next ;
        list->first->prev = NULL ;
    }
    
    list -> numElements-- ;
    
    return item ;
}

/*==============================================================*/
// remove a node from list
void delList( list_t *list, Item *node) {
	Item *item = list -> first;
	while (item) 
	{
    	if (item == node)
    	{
    		item -> prev -> next = node -> next;
    		node -> next -> prev = node -> prev;
    		list -> numElements--;
    		freeItem(node);
    	}
    	item = item->next;
  	}
}
/*==============================================================*/
// return and remove best item with minimal f value
Item *popBest( list_t *list ) // and remove the best board from the list.
{
  Item *item = list -> first;
  int min    = list -> first -> f;
  item       = item->next; 

	while (item) 
	{
    	if (item -> f < min)
    	{
    		min = item -> f;
    	}
    	item = item->next;
  	}

  	item = list -> first;

	while (item) 
	{
    	if (item -> f == min)
    	{
    		delList(list, item);
    		return item;
    	}
    	item = item->next;
  	}
}

/*==============================================================*/
 // add item in top
void addFirst( list_t *list, Item *node ) // add in head
{
	if (list->numElements == 0)
	{
		list -> first = node;
		list -> last  = node;
	}
	else
	{
		node -> next          = list -> first;
		list -> first -> prev = node;
		list -> first         = node;
	}
	list -> numElements++;
}

/*==============================================================*/
 // add item in queue
void addLast( list_t *list, Item *node ) // add in tail
{
	if (list->numElements == 0)
	{
		list -> first         = node;
		list -> last  		  = node;
	}
	else
	{
		node -> prev          = list -> last;
		list -> last -> next  = node;
		list -> last          = node;
	}
	list -> numElements++;
}

/*==============================================================*/
void cleanupList( list_t *list )
{
	/*
	Item *item = list -> first;
	Item *node = item -> next;
	while (node) 
	{
		freeItem(item);
    	list -> numElements --;
    	item = node;
    	node = node -> next;
  	}
  	*/
  	//A REFAIRE
  	list -> first = NULL;
  	list -> numElements = 0;
}

/*==============================================================*/
void printList( list_t list ) {
	Item *item = list.first;
  while (item) {
    printf("%.2f [%s] - ", item->f, item->board);
    item = item->next;
  }
  printf(" (nb_items: %d)\n", list.numElements);
}


/*==============================================================*/




/*============================= M A I N ============================*/
/*
int main()
{
  Item *item;
	char str[3];

	list_t openList;
  
	initList( &openList );

//==========Test AddLast===========
	for (int i=0; i<10; i++) {
		item = nodeAlloc();
		item->f = i;
		sprintf(str, "%2d", i);
        item->board = strdup(str);
		addLast( &openList, item );
	}

//==========Test AddFirst===========
	for (int i=20; i<25; i++) {
    	item = nodeAlloc();
    	item->f = i;
    	sprintf(str, "%2d", i);
    	item->board = strdup(str);
    	addFirst( &openList, item );
	}	

	printList(openList);

//==========Test PopBest===========
	Item *node = popBest( &openList );
	printf("best node = %.2f\n", node->f);
	printList(openList);
	printf("\n");

//==========Test OnList===========
	strcpy(str, "23");
	node = onList(&openList, str);
	if (node)
	{
		printf("found %s: %.2f!\n", str, node->f); 
	}
	else
	{
		printf("L'élement %s ne se trouve pas dans la liste\n", str);
	}
	printList(openList);
	printf("\n");

//==========Test PopFirst===========
	node = popFirst(&openList);
	
	item = nodeAlloc();
    item->f = 50;
    sprintf(str, "50");
    item->board = strdup(str);
    addLast( &openList, item );

	node = popFirst(&openList);
	if (node) printf("first: %.2f\n", node->f); 
	printList(openList);
    printf("\n");

//==========Test PopLast===========
	node = popLast(&openList);
	if (node) printf("last: %.2f\n", node->f); 
	printList(openList);
    printf("\n");

//==========Test Cleanlist===========
	printf("clean\n");	
	cleanupList(&openList);
	printList(openList);
	printf("\n");

	printList(openList);

	return 0;
}

*/