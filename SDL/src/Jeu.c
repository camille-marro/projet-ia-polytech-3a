#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600

void SDL_ExitWithError(const char *message);
void board();
void placer(int i, int j, int k);
void left();
void right();
void enter();
void initialiser_A_Null(int *tableau, int n);
int verif_colonne(int *tab, int posX);
int switch_player(int player);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *pion1 = NULL;
SDL_Texture *texture1 = NULL;
SDL_Rect pionposition;

int *coord;
int *column;
int pion = 0;
int colonne = 0;


int main(int argc, char *argv[])
{
    //Lancement SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Initialisation SDL");

    //Création fenêtre + rendu
    if(SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) != 0)
        SDL_ExitWithError("Creation fenetre echouee");

    //Couleur blanche
    if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Changement Impossible du couleur du rendu"); 

    //Mettre la couleur en plein ecran
    SDL_RenderClear(renderer);
    /*------------------------------------------------------------*/

    coord = (int *)malloc(sizeof(int) * 100);
    column = (int *)malloc(sizeof(int) * 7);

    initialiser_A_Null(coord,84);
    initialiser_A_Null(column,7);

    board();
    placer(50,9,0);
    SDL_RenderPresent(renderer);
    pionposition.x = 50;
    pionposition.y = 9;




    SDL_bool program_launched = SDL_TRUE;
    while (program_launched)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_MOUSEMOTION:
                    //printf("%d / %d\n", event.motion.x, event.motion.y);
                    //event.motion.xrel
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    printf("%d / %d\n", event.motion.x, event.motion.y);
                    break;
                case SDL_KEYDOWN:
                    //if(event.key.keysym.sym == SDLK_ESCAPE){break;}
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_RIGHT :
                            if (pionposition.x + 140 < WINDOW_WIDTH)
                            {
                                right();
                                //colonne ++;
                                coord[pion] = pionposition.x;
                                coord[pion + 1] = pionposition.y;
                                SDL_RenderClear(renderer);
                                board();
                                coord[pion] = 0;
                                coord[pion + 1] = 0;
                            }
                            break;
                        case SDLK_LEFT :
                            if (pionposition.x - 140 > 0)
                            {
                                left();
                                //colonne ++;
                                coord[pion] = pionposition.x;
                                coord[pion + 1] = pionposition.y;
                                SDL_RenderClear(renderer);
                                board();
                                coord[pion] = 0;
                                coord[pion + 1] = 0;
                            }
                            break;
                        case SDLK_RETURN :
                            colonne = verif_colonne(column,pionposition.x);
                            if (colonne != -1)
                            {
                                enter();
                                coord[pion] = pionposition.x;
                                coord[pion + 1] = pionposition.y;
                                pion += 2;
                                SDL_RenderClear(renderer);
                                board();
                                pionposition.x = 50;
                                pionposition.y = 9;
                            }
                            break;
                    }
                    break;
                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;
                default:
                    continue;
            }
        }
    }


    return 0;
}

void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void board()
{
    SDL_Surface *board = NULL;
    SDL_Texture *texture = NULL;

    board = SDL_LoadBMP("src/four.bmp"); 

    if (board == NULL)
    {
        SDL_ExitWithError("Impossible de charger l'image");
    }
    texture = SDL_CreateTextureFromSurface(renderer, board);
    SDL_FreeSurface(board);

    if (texture == NULL)
    {
        SDL_ExitWithError("Impossible de creer la texture");
    }
    SDL_Rect boardposition;
    SDL_QueryTexture(texture, NULL, NULL, &boardposition.w, &boardposition.h);
    boardposition.x = (WINDOW_WIDTH - boardposition.w) / 2;
    boardposition.y = (WINDOW_HEIGHT -boardposition.h) / 2;
    SDL_RenderCopy(renderer, texture, NULL, &boardposition);

    int i = 0;

    while (coord[i] != 0 && i < 84)
    {
        placer(coord[i], coord[i+1], i-(i/2));
        i += 2;
    }
    SDL_RenderPresent(renderer);
    
}

void placer(int i, int j, int k)
{
    SDL_Surface *image = NULL;
    SDL_Texture *texture = NULL;

    if (k % 2 == 0){
        image = SDL_LoadBMP("src/pion1.bmp");
    }
    else{
        image = SDL_LoadBMP("src/pion2.bmp");
    }
     
    if (image == NULL)
    {
        SDL_ExitWithError("Impossible de charger l'image");
    }

    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    if (texture == NULL)
    {
        SDL_ExitWithError("Impossible de creer la texture");
    }

    SDL_Rect pionpos;
    SDL_QueryTexture(texture, NULL, NULL, &pionpos.w, &pionpos.h);
    pionpos.x = i;
    pionpos.y = j;
    SDL_RenderCopy(renderer, texture, NULL, &pionpos);

}


void left()
{
    pionposition.x -= 140;
}

void right()
{
    pionposition.x += 140;
}

void enter()
{
    pionposition.y += 100 * (6 - column[colonne]);  
}


void initialiser_A_Null(int *tableau, int n)
{
    int i;
    for ( i = 0; i < n; i++)
    {
        tableau[i] = 0;
    }
}

int verif_colonne(int *tab, int posX)
{
    switch (posX)
    {
        case 50:
            if (tab[0] < 6)
            {
                tab[0]++;
                return 0;
            }       
            break;
        case 190:
            if (tab[1] < 6)
            {
                tab[1]++;
                return 1;
            }        
            break;
        case 330:
            if (tab[2] < 6)
            {
                tab[2]++;
                return 2;
            }   
            break;
        case 470:
            if (tab[3] < 6)
            {
                tab[3]++;
                return 3;
            }         
            break;
        case 610:
            if (tab[4] < 6)
            {
                tab[4]++;
                return 4;
            }  
            break;
        case 750:
            if (tab[5] < 6)
            {
                tab[5]++;
                return 5;
            }         
            break;
        case 890:
            if (tab[6] < 6)
            {
                tab[6]++;
                return 6;
            }            
            break;
        default:
        exit(EXIT_FAILURE);
    }
    return -1;
}
