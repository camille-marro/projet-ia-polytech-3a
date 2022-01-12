#include <stdlib.h>
#include "board.h"


int main(int argc, char *argv[])
{
  Board game;
  int choix, turn = 1;
  initGame(game);
  printBoard(game);

  do
  {
      printf("turn gamer ==> %d \n", turn);
      choix = valid_choice(game, choix);
      add_Pion(game,choix,turn);
      clrscr();
      printBoard(game);
      if (turn == 1)
      {
          turn = 2;
      }
      else{
          turn = 1;
      }
  }while (evaluate_board(game) == 0);

  printf("Le joueur %d a perdu :(\n", turn);
  



//  printf("la colonne %d est-elle valid? %d\n",0,valid_colonne(game, 0));
//  game[lower_case(game,0)][0] = 1;
//  printBoard(game);
///*======================================================================*/
//  printf("la colonne %d est-elle valid? %d\n",0,valid_colonne(game, 0));
//  game[lower_case(game,0)][0] = 1;
//  printBoard(game);
///*======================================================================*/
//  printf("la colonne %d est-elle valid? %d\n",0,valid_colonne(game, 0));
//  game[lower_case(game,0)][0] = 8;
//  printBoard(game);
///*======================================================================*/
//  printf("la colonne %d est-elle valid? %d\n",0,valid_colonne(game, 0));
//  game[lower_case(game,0)][0] = 1;
//  printBoard(game);
///*======================================================================*/
//  printf("la colonne %d est-elle valid? %d\n",0,valid_colonne(game, 0));
//  game[lower_case(game,0)][0] = 7;
//  printBoard(game);
///*======================================================================*/
//  printf("la colonne %d est-elle valid? %d\n",0,valid_colonne(game, 0));
//  game[lower_case(game,0)][0] = 5;
//  printBoard(game);
///*======================================================================*/
//  printf("la colonne %d est-elle valid? %d\n",1,valid_colonne(game, 1));
//  game[lower_case(game,1)][1] = 2;
//  printBoard(game);
///*======================================================================*/
//  printf("la colonne %d est-elle valid? %d\n",1,valid_colonne(game, 1));
//  game[lower_case(game,1)][1] = 3;
//  printBoard(game);
///*======================================================================*/
//  printf("la colonne %d est-elle valid? %d\n",1,valid_colonne(game, 1));
//  game[lower_case(game,1)][1] = 1;
//  printBoard(game);
///*======================================================================*/
//  printf("la colonne %d est-elle valid? %d\n",2,valid_colonne(game, 2));
//  game[lower_case(game,2)][2] = 3;
//  printBoard(game);
///*======================================================================*/
//  printf("la colonne %d est-elle valid? %d\n",2,valid_colonne(game, 2));
//  game[lower_case(game,2)][2] = 1;
//  printBoard(game);
///*======================================================================*/
//  printf("la colonne %d est-elle valid? %d\n",1,valid_colonne(game, 1));
//  game[lower_case(game,3)][3] = 1;
//  printBoard(game);
///*======================================================================*/
//  printf("la colonne %d est-elle valid? %d\n",4,valid_colonne(game, 4));
//  printf("la valeur kdk = %d", lower_case(game,4));
//  game[lower_case(game,4)][4] = 1;
//  printBoard(game);
///*======================================================================*/
//  printf("la colonne %d est-elle valid? %d\n",5,valid_colonne(game, 5));
//  game[lower_case(game,5)][5] = 1;
//  printf("%d\n",lower_case(game,5));
//  printBoard(game);
///*======================================================================*/
//  printf("la colonne %d est-elle valid? %d\n",6,valid_colonne(game, 6));
//  game[lower_case(game,6)][6] = 1;
//  printBoard(game);
///*======================================================================*/
//printf("evaluate board ====> %d", evaluate_board(game));
}
