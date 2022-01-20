#include <stdio.h>
//#include <malloc.h>
#include <assert.h>
#include <stdlib.h> 
#include <math.h>
#include "board.h"





void initGame(Board game)
{
    int i,j;
    for ( i = 0; i < HT_BOARD; i++)
    {
        for ( j = 0; j < WH_BOARD; j++)
        {
            game[i][j] = 0;
        }
    }
}

void printBoard(Board game)
{
    int i,j;
    printf("\n");
    for ( i = 0; i < HT_BOARD; i++)
    {
        for ( j = 0; j < WH_BOARD; j++)
        {
            
            if (game[i][j] != 0){
                printf(" ║ %d ", game[i][j]);
            }
            else{
                printf(" ║   ");
            }
        }
        printf("║\n\n");
    }
}


bool valid_colonne(Board game, int j)
{
    return(game[0][j] == 0);
}


int lower_case(Board game, int j)
{
    int i;
    i = HT_BOARD - 1;
    while (i >= 0)
    {
        if (game[i][j] == 0)
        {
            return i;
        }
        i--;
    }
    return -1;
}

bool ligne(Board game, int ii, int jj)
{
    int j;
    for (j = jj + 1; j < jj+4; j++)
    {
      if(j<WH_BOARD)
      {
        if (game[ii][j] != game[ii][jj])
        {
          return 0;
        }
      }
      else
      {
        return 0;
      }
    }
    return 1;
}

bool colonne(Board game, int ii, int jj)
{
    int i;
    for (i = ii + 1; i < ii+4; i++)
    {
        //printf("la case [%d][%d]",i,jj);
      if(i<HT_BOARD)
      {
        if (game[i][jj] != game[ii][jj])
        {
          return 0;
        }
      }
      else
      {
        return 0;
      }
    }
    return 1;
}

bool oblique_right(Board game, int ii, int jj)
{
    int i,j;
    i = ii;
    j = jj;
    int tmp = 1;
    while (tmp<4)
    {
        i ++;
        j ++;
        if (i < HT_BOARD && j < WH_BOARD)
        {
            if (game[i][j] != game[ii][jj])
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
        tmp ++; 
    }

    return 1;
}

bool oblique_left(Board game, int ii, int jj)
{
    int i,j;
    i = ii;
    j = jj;
    int tmp = 1;
    while (tmp<4)
    {
        i ++;
        j --;
        if (i < HT_BOARD && j >= 0)
        {
            if (game[i][j] != game[ii][jj])
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
        tmp ++; 
    }
    return 1;
}


bool evaluate_board(Board game)
{
    int i,j;
    for (i = 0; i < HT_BOARD; i++)
    {
        for ( j = 0; j < WH_BOARD; j++)
        {
            if (game[i][j] != 0)
            {
                if (ligne(game, i, j))
                {
                    return 1;
                }
                else if (colonne(game, i, j))
                {
                    return 1;
                }
                else if (oblique_right(game, i, j))
                {
                    return  1;
                }
                else if (oblique_left(game, i, j))
                {
                    return 1;
                }
            }
            
        }
        
    }
    return 0;
}

void add_Pion(Board game, int choice, int turn)
{
    game[lower_case(game,choice)][choice] = turn;
}


int valid_choice(Board game, int choix)
{
    do
    {
        printf("Colonne : ?");
        scanf("%d",&choix);
    }while(choix>=WH_BOARD || choix<0 || !valid_colonne(game, choix));

    return choix;
}

/* Vider écran Clear Screen */
void clrscr()
{
    system("@cls||clear");
}