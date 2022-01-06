#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "board.h"

/* Item Functions */

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

void freeItem( Item *node )
{
  if (node && node->board) free(node->board);
	if (node) free(node);
}


void initList( list_t *list_p )
{
  //if (list_p == NULL) list_p = malloc(sizeof(list_t));
	assert(list_p);

  list_p->numElements = 0;
  list_p->first = NULL;
  list_p->last = NULL;
}

int listCount( list_t *list )
{
	return list->numElements;
}

// return an item with corresponding board , or null
Item* onList( list_t *list, char *board)
{
  Item *item = list->first;
  int i;
  while (item != NULL) {
    i=0;
    while (i < MAX_BOARD && item->board[i] == board[i]) {
      i += 1;
    }
    if (i == MAX_BOARD) return item;
    item = item->next;
  }
  return NULL;
} // a verif

// return and remove first item
Item *popFirst( list_t *list ) //
{
	Item *item = list->first;
  delList(list, item);
  list->numElements -= 1;
  // list->first = list->first->next; // on rearrange la liste
  // list->first->next->prev = NULL; // on dit que le premier élément de la liste n'a plus d'antécédent
  // list->numElements -= 1;
	return item;
} // a verif

// return and remove last item
Item *popLast( list_t *list ) //
{
	Item *item = list->last;
  delList(list, item);
  list->numElements -= 1;
  return item;
} // a verif

// remove a node from list
void delList( list_t *list, Item *node) {
  if (list == NULL || node == NULL) return;
  if(node->prev != NULL) {
    node->prev->next = node->next;
  }
  if (node->next != NULL) {
    node->next->prev = node->prev;
  }
  if (list->first == node) {
    list->first = node->next;
  }
  if (list->last == node) {
    list->last = node->prev;
  }
  node->prev = NULL;
  node->next = NULL;
} // a verif
// return and remove best item with minimal f value
Item *popBest( list_t *list ) // and remove the best board from the list.
{
  if (list->numElements == 0) return NULL;
  Item *best = list->first, *tmp = list->first;
  while (tmp) {
    if (tmp->f < best->f) best = tmp;
    tmp = tmp->next;
  }
  delList(list, best);
  list->numElements -= 1;
  return best;
}

 // add item in top
void addFirst( list_t *list, Item *node ) // add in head
{
  node->next= list->first;
  if(list->first != NULL) {
    list->first->prev = node;
  } else {
    list->last = node;
  }
  list->first = node;
  list->numElements += 1;
} // a verif

 // add item in queue
void addLast( list_t *list, Item *node ) // add in tail
{
  node->prev = list->last;
  if(list->last != NULL) {
    list->last->next = node;
  } else {
    list->first = node;
  }
  list->last = node;
  list->numElements += 1;
} // a verif

void cleanupList( list_t *list )
{
  Item *item = list->first;
  while (item) {
    Item *tmp = item;
    freeItem(item);
    item = tmp->next;
  }
  list->numElements = 0;
} // a verif

void printList( list_t list ) {
	Item *item = list.first;
  while (item) {
    printf("%.2f [%s] - ", item->f, item->board);
    item = item->next;
  }
  printf(" (nb_items: %d)\n", list.numElements);
}


// TEST LIST
//
// int main()
// {
//   Item *item;
// 	char str[3];
//
// 	list_t openList;
//
// 	initList( &openList );
//
// 	for (int i=0; i<10; i++) {
// 		item = nodeAlloc();
// 		item->f = i;
// 		sprintf(str, "%2d", i);
//         item->board = strdup(str);
// 		addLast( &openList, item );
// 	}
//
//
//
// 	for (int i=20; i<25; i++) {
//     item = nodeAlloc();
//     item->f = i;
//     sprintf(str, "%2d", i);
//     item->board = strdup(str);
//     addFirst( &openList, item );
//   }
//   printf("\n\n");
// 	printList(openList);
// 	printf("\n");
//
//   /*
//
// 	Item *node = popBest( &openList );
// 	printf("best node = %.2f\n", node->f);
// 	printList(openList);
// 	printf("\n");
//
//   */
//
//   Item *node = popFirst(&openList);
//   printf("first node = %.2f\n", node->f);
//   printList(openList);
//   printf("\n");
//
// 	strcpy(str, "23");
// 	node = onList(&openList, str);
// 	if (node) printf("found %s: %.2f!\n", str, node->f);
// 	printList(openList);
// 	printf("\n");
//
// 	//node = popFirst(&openList);
//
// 	item = nodeAlloc();
//     item->f = 50;
//     sprintf(str, "50");
//     item->board = strdup(str);
//     addLast( &openList, item );
//
// 	node = popFirst(&openList);
// 	if (node) printf("first: %.2f\n", node->f);
// 	printList(openList);
//     printf("\n");
//
// 	node = popLast(&openList);
// 	if (node) printf("last: %.2f\n", node->f);
// 	printList(openList);
//     printf("\n");
//
// 	printf("clean\n");
// 	cleanupList(&openList);
// 	printList(openList);
// 	printf("\n");
//
//
//
// 	return 0;
// }
