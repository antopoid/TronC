//TronC Made by Antoine Poidevin

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "liste/liste_scores.h"
#include <math.h>
#include <time.h>

#define PLAYER_ONE_COLOR 3
#define PLAYER_TWO_COLOR 2
#define AI_COLOR PLAYER_TWO_COLOR
#define GREEN_SQUARE_COLOR 1
#define EMPTY_SQUARE 0

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define DISTANCE_OBSTACLE 10

typedef struct {
    int x, y;
} direction_t;

static direction_t possibleDirections[] = {
        { .x = 0, .y = -1 },
        { .x = 0, .y = 1 },
        { .x = 1, .y = 0 },
        { .x = -1, .y = 0 }
};


static SDL_Surface *screen = NULL, *texte = NULL;
static Uint32 colors_rgb[5];
//Definie un tableau des dimensions de l'ecran pour y inscrire chaque couleur de chaque pixels
static char point[1280][720];
//Variables player 1                      //Variables player 2                  //Variables score                   //variables menu              
static int x=140, y=90, dx=1, dy=0, pts=0, x_1=160, y_1=90, dx1=1, dy1=0, pts1=0, tempsActuel = 0, tempsPrecedent = 0, pointeur = 0, tour=0, check = 0, winner = 0, inser=0, speed=2, difficulty=2, print=0, bonus=0;
static int last_distance = -1, current_distance = -1;
static char score[80] = {""}; /* Tableau de char suffisamment grand */ 
static char strn[80] = {""}; /* Tableau de char suffisamment grand */ 
static char chaine[80] = {""};
static SDL_Event event;
TTF_Font *police = NULL; //Variable pour police SDL_tff
FILE  *fichier; // FILE en majuscule
#include "fonctions/fonctions.h"



//fonction principal
int main( int argc, char* args[] ) {

    Liste *maListe = initialisation(); // Creatin de la liste chainée
    SDL_Init(SDL_INIT_EVERYTHING); // Initialise tout ce qu'il faut pour faire fonctionner SDL
    screen = SDL_SetVideoMode(1280, 720, 32, SDL_SWSURFACE); //Decide de la taille de la fenetre
    SDL_WM_SetCaption("C-SDL GAME TRONC", NULL); //Titre de la fenetre
    
    if(TTF_Init() == -1) //Verifie qu'il n'y a pas d'erreur
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    //Initialise les differentes couleurs utilisées pour les pixels
    colors_rgb[0] = SDL_MapRGB(screen->format, 0,    0,   0);
    colors_rgb[1] = SDL_MapRGB(screen->format, 0,   255,  0);
    colors_rgb[2] = SDL_MapRGB(screen->format, 255,   0,  0);
    colors_rgb[3] = SDL_MapRGB(screen->format, 120, 239, 252);
    colors_rgb[4] = SDL_MapRGB(screen->format, 50,    50,   50);

    goto MENU;

#include "goto/menu.h"
#include "goto/settings.h"
#include "goto/affscores.h"
#include "goto/soloplayer.h"
#include "goto/multiplayer.h"
#include "goto/close.h"


}