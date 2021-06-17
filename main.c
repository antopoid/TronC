//C-tron Made by Antoine Poidevin


#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "scores.h"

static SDL_Surface *screen = NULL, *texte = NULL;
static Uint32 colors_rgb[4];
//Definie un tableau des dimensions de l'ecran pour y inscrire chaque couleur de chaque pixels
static char point[1280][720];
//Variables player 1                      //Variables player 2                  //Variables score                   //variables menu              
static int x=140, y=90, dx=1, dy=0, pts=0, x1=160, y1=90, dx1=1, dy1=0, pts1=0, tempsActuel = 0, tempsPrecedent = 0, pointeur = 0, tour=0, check = 0, winner = 0, inser=0, speed=2, difficulty=2;
static char score[80] = {""}; /* Tableau de char suffisamment grand */ 
static char strn[80] = {""}; /* Tableau de char suffisamment grand */ 
static char chaine[80] = {""};
static SDL_Event event;
TTF_Font *police = NULL; //Variable pour police SDL_tff

//fonction pour recuperer touche appuyé
int get_event () {
  if (SDL_PollEvent(&event)) {        // If there's an event to handle
    if (event.type == SDL_KEYDOWN)    // If a key was pressed
      return event.key.keysym.sym;
    if (event.type == SDL_QUIT)
      return SDL_QUIT;
  }
  return 0;
}

//fonction pour rafraichir ecran
void update_screen () { SDL_Flip(screen); }

void prect(int x, int y, int w, int h, Uint32 c) {
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
  SDL_FillRect(screen, &rect, c);
}

//Cursor 
void pset(int x, int y, int c) {
  prect(x*2, y*2, 2, 2, colors_rgb[c]);
  point[x][y] = c;
}


//fonction pour dessiner carré vert
void draw_green_square () {
  int h=(rand()%636)+1, v=(rand()%316)+1, x, y;
  for (x=h; x<=h+2; ++x) for (y=v; y<=v+2; ++y) pset(x, y, 1);
}

//fonction pour afficher score
void draw_score (int pts) {
    SDL_Color couleurCyan = {120, 239, 252};
    SDL_Color couleurNoir = {0, 0, 0};
    int i=0, j=0;
    for (i=10; i<=300; ++i) for (j=330; j<=350; ++j) pset(i, j, 0);
    SDL_Rect position;
    position.x = 30;
    position.y = 660;
    tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent >= 300) /* Si 100ms au moins se sont écoulées */
        {
            sprintf(score, "Score : %d", pts); /* On écrit dans la chaîne le nouveau score */
            SDL_FreeSurface(texte); /* On supprime la surface précédente de la mémoire avant d'en charger une nouvelle (IMPORTANT) */
            texte = TTF_RenderText_Shaded(police, score, couleurCyan, couleurNoir); /* On écrit la chaine temps dans la SDL_Surface */
            tempsPrecedent = tempsActuel; /* On met à jour le tempsPrecedent */
        }
    SDL_BlitSurface(texte, NULL, screen, &position); // Blit du texte 
    //free(texte);
}

//fonction pour afficher score fianl sous forme de popup
void draw_score_final (Liste *liste, int pts) {
    SDL_EnableUNICODE(SDL_ENABLE);
    int i=0, j=0;
    memset(chaine, 0, 80);
    SDL_Color couleurCyan = {120, 239, 252};
    SDL_Color couleurNoir = {0, 0, 0};
    //Definie le fond en noir 
    for (i=300; i<=400; ++i) for (j=110; j<=150; ++j) pset(i, j, 0);
    //Barre superieur et inferieur 
    for (i=170; i<=470; ++i) { pset(i, 150, 3); pset(i, 200, 3); pset(i, 359, 3); }
    //Barre gauche et droite 
    for (j=150; j<=200; ++j) { pset(170, j, 3); pset(470, j, 3); }  
    
    SDL_Rect position;
            position.x = 670;
            position.y = 328;

            sprintf(score, "Score : %d", pts); /* On écrit dans la chaîne le nouveau score */
            texte = TTF_RenderText_Shaded(police, score, couleurCyan, couleurNoir); /* On écrit la chaine temps dans la SDL_Surface */

    SDL_BlitSurface(texte, NULL, screen, &position); // Blit du texte 

    i=0;
    while(i <= 10) {
 
    SDL_WaitEvent(&event);
    
    if(event.key.keysym.unicode >= 'a' && event.key.keysym.unicode <= 'z') {strcat(chaine,SDL_GetKeyName(event.key.keysym.unicode));i++;}
    else if(event.key.keysym.unicode >= 'A' && event.key.keysym.unicode <= 'Z') {strcat(chaine,SDL_GetKeyName(event.key.keysym.unicode));i++;}
    else if(event.key.keysym.sym == SDLK_RETURN) {inser=1;break;}
    else if(event.key.keysym.sym == SDLK_ESCAPE) {inser=1;break;}
    else if(event.key.keysym.sym == SDL_QUIT) {inser=1;break;}
    texte = TTF_RenderText_Blended(police, chaine, couleurCyan);
    SDL_Rect position;
    position.x = 360;
    position.y = 328;
    SDL_BlitSurface(texte, NULL, screen, &position);
    SDL_FreeSurface(texte);
    update_screen();
  }
    SDL_EnableUNICODE(SDL_DISABLE);
}

//fonction declenché sur un pixel vert
void hit_green_pixel () {
  draw_green_square(); ++pts;
  update_screen(); SDL_Delay(100);
  // noise();
}

//fonction pour dessiner contour 
void contour (int Affscore) {
     int i=0;
     int j=0;
    //Definie le fond en noir 
    for (i=0; i<=640; ++i) for (j=0; j<=360; ++j) pset(i, j, 0);
    //Barre superieur et inferieur 
    if(Affscore==1){for (i=0; i<=640; ++i) { pset(i, 0, 3); pset(i, 320, 3); pset(i, 359, 3); }}
    if(Affscore==0){for (i=0; i<=640; ++i) { pset(i, 0, 3); pset(i, 359, 3); }}   
    //Barre gauche et droite 
    for (j=0; j<=360; ++j) { pset(0, j, 3); pset(639, j, 3); }
}

//fonction pour ecrire du texte
void draw_text (int x, int y, int size, char strn[],int clr) {
    SDL_Color couleurCyan = {120, 239, 252};
    SDL_Color couleurRouge = {211, 44, 31};
    //chercher fonction changement taille
    police = TTF_OpenFont("./TRON.ttf", size); // Chargement de la police 
    if(clr==1)texte = TTF_RenderText_Blended(police, strn, couleurCyan); // Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) 
    if(clr==2)texte = TTF_RenderText_Blended(police, strn, couleurRouge); // Écriture du texte dans la SDL_Surface texte en mode Blended (optimal)
    SDL_Rect position;
    position.x = x;
    position.y = y;
    SDL_BlitSurface(texte, NULL, screen, &position); // Blit du texte //
    TTF_CloseFont(police); //Ferme la police
}

//fonction principal
int main( int argc, char* args[] ) {

    Liste *maListe = initialisation();
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(1280, 720, 32, SDL_SWSURFACE);
    SDL_WM_SetCaption("C-SDL GAME TRONC", NULL);
    //Initialise SDL_ttf (impression de texte)
    //Verifie qu'il n'y a pas d'erreur
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    //Initialise les differentes couleurs utilisées pour SDL_ttf
    //SDL_Color couleurCyan = {120, 239, 252};
    //SDL_Color couleurrouge = {255, 0, 0};
    //Initialise les differentes couleurs utilisées pour les pixels
    colors_rgb[0] = SDL_MapRGB(screen->format, 0,    0,   0);
    colors_rgb[1] = SDL_MapRGB(screen->format, 0,   255,  0);
    colors_rgb[2] = SDL_MapRGB(screen->format, 255,   0,  0);
    colors_rgb[3] = SDL_MapRGB(screen->format, 120, 239, 252);

    goto MENU;

MENU:
      contour(0);     //Definie les contour pour l'affichage sans score 
      while (get_event()) {}  // empty the event queue
      while (1) {
      if(pointeur>4)pointeur=0;
      if(pointeur<0)pointeur=4;
tour=1;
while(tour>0){
        //printf("%d\n", pointeur );
if(pointeur==0){  
               sprintf(strn, "Bienvenue dans TRONC"); draw_text(60,10,55,strn,1); 
               sprintf(strn, "Multiplayer 1 vs 1"); draw_text(60,230,25,strn,2);           
               sprintf(strn, "Soloplayer 1 vs IA"); draw_text(60,310,25,strn,1);
               sprintf(strn, "Scores"); draw_text(60,400,25,strn,1);
               sprintf(strn, "Settings"); draw_text(60,480,25,strn,1);
               sprintf(strn, "Exit"); draw_text(60,560,25,strn,1);
               }

if(pointeur==1){ 
               sprintf(strn, "Bienvenue dans TRONC"); draw_text(60,10,55,strn,1); 
               sprintf(strn, "Multiplayer 1 vs 1"); draw_text(60,230,25,strn,1);           
               sprintf(strn, "Soloplayer 1 vs IA"); draw_text(60,310,25,strn,2);
               sprintf(strn, "Scores"); draw_text(60,400,25,strn,1);
               sprintf(strn, "Settings"); draw_text(60,480,25,strn,1);
               sprintf(strn, "Exit"); draw_text(60,560,25,strn,1);
               }

if(pointeur==2){ 
               sprintf(strn, "Bienvenue dans TRONC"); draw_text(60,10,55,strn,1); 
               sprintf(strn, "Multiplayer 1 vs 1"); draw_text(60,230,25,strn,1);           
               sprintf(strn, "Soloplayer 1 vs IA"); draw_text(60,310,25,strn,1);
               sprintf(strn, "Scores"); draw_text(60,400,25,strn,2);
               sprintf(strn, "Settings"); draw_text(60,480,25,strn,1);
               sprintf(strn, "Exit"); draw_text(60,560,25,strn,1);
               }

if(pointeur==3){ 
               sprintf(strn, "Bienvenue dans TRONC"); draw_text(60,10,55,strn,1); 
               sprintf(strn, "Multiplayer 1 vs 1"); draw_text(60,230,25,strn,1);           
               sprintf(strn, "Soloplayer 1 vs IA"); draw_text(60,310,25,strn,1);
               sprintf(strn, "Scores"); draw_text(60,400,25,strn,1);
               sprintf(strn, "Settings"); draw_text(60,480,25,strn,2);
               sprintf(strn, "Exit"); draw_text(60,560,25,strn,1);
              }

if(pointeur==4){ 
               sprintf(strn, "Bienvenue dans TRONC"); draw_text(60,10,55,strn,1); 
               sprintf(strn, "Multiplayer 1 vs 1"); draw_text(60,230,25,strn,1);           
               sprintf(strn, "Soloplayer 1 vs IA"); draw_text(60,310,25,strn,1);
               sprintf(strn, "Scores"); draw_text(60,400,25,strn,1);
               sprintf(strn, "Settings"); draw_text(60,480,25,strn,1);
               sprintf(strn, "Exit"); draw_text(60,560,25,strn,2);
              }
tour=0;
}   

  switch (get_event()) {
    case SDLK_UP: pointeur --; tour++; goto MENU;
    case SDLK_DOWN: pointeur ++; tour++; goto MENU;
    case SDLK_p:
    case SDLK_RETURN: if (pointeur==0)goto NEWGAME_MULTIPLAYER;
                      if (pointeur==1)goto NEWGAME_SOLOPLAYER;
                      if (pointeur==2)goto SCORES;
                      if (pointeur==3)goto SETTINGS;
                      if (pointeur==4)goto CLOSE;
                      break;
    //case SDLK_SPACE: 
        case SDLK_ESCAPE: goto CLOSE;
        case SDL_QUIT: goto CLOSE;
      }
    //Rafraichie écran
    update_screen();
    //SDL_Delay(20);
    }

SETTINGS:

contour(0); //dessine les contours sans afficher le score
while (get_event()) {}  // empty the event queue
while (1) 
{
      if(pointeur>1)pointeur=0;if(pointeur<0)pointeur=1;if(speed>3)speed=3;if(speed<1)speed=1;if(difficulty>3)difficulty=3;if(difficulty<1)difficulty=1;
      if(pointeur==0){  
         sprintf(strn, "Settings"); draw_text(450,100,40,strn,1);
         sprintf(strn, "Speed"); draw_text(330,280,25,strn,1);
            if (speed == 3){sprintf(strn, "<- FAST"); draw_text(650,280,25,strn,2);}
            if (speed == 2){sprintf(strn, "<- MEDIUM ->"); draw_text(650,280,25,strn,2);}
            if (speed == 1){sprintf(strn, "SLOW ->"); draw_text(650,280,25,strn,2);}
         sprintf(strn, "Difficullty"); draw_text(330,380,25,strn,1);
            if (difficulty == 3){sprintf(strn, "HARD"); draw_text(650,380,25,strn,1);}
            if (difficulty == 2){sprintf(strn, "NORMAL"); draw_text(650,380,25,strn,1);}
            if (difficulty == 1){sprintf(strn, "EASY"); draw_text(650,380,25,strn,1);}
      }
      if(pointeur==1){  
         sprintf(strn, "Settings"); draw_text(450,100,40,strn,1);
         sprintf(strn, "Speed"); draw_text(330,280,25,strn,1);
            if (speed == 3){sprintf(strn, "FAST"); draw_text(650,280,25,strn,1);}
            if (speed == 2){sprintf(strn, "MEDIUM"); draw_text(650,280,25,strn,1);}
            if (speed == 1){sprintf(strn, "SLOW"); draw_text(650,280,25,strn,1);}
         sprintf(strn, "Difficullty"); draw_text(330,380,25,strn,1);
            if (difficulty == 3){sprintf(strn, "<- HARD"); draw_text(650,380,25,strn,2);}
            if (difficulty == 2){sprintf(strn, "<- NORMAL ->"); draw_text(650,380,25,strn,2);}
            if (difficulty == 1){sprintf(strn, "EASY ->"); draw_text(650,380,25,strn,2);}
      }



  switch (get_event()) {
    case SDLK_UP: pointeur --; goto SETTINGS;
    case SDLK_DOWN: pointeur ++; goto SETTINGS;
    case SDLK_RIGHT: if(pointeur==0)speed++; if(pointeur==1)difficulty++; goto SETTINGS;
    case SDLK_LEFT: if(pointeur==0)speed--; if(pointeur==1)difficulty--; goto SETTINGS;
        case SDLK_RETURN: goto MENU;
        case SDLK_ESCAPE: goto MENU;
        case SDL_QUIT: goto CLOSE;
  }
    update_screen();
    SDL_Delay(50);
}

SCORES:
    
    suppression(maListe);
    lire(maListe);
    Element *actuel = maListe->premier;
    contour(0); //dessine les contours sans afficher le score
    int height=220;
    int nbScore=1;

while (get_event()) {}  // empty the event queue
while (1) 
{
  //////////Liste chainée
sprintf(strn, "Best Scores"); draw_text(380,100,40,strn,1);
    //insertion(maListe,name, score);


    while (actuel != NULL && nbScore<=6)
    {
        sprintf(strn, "%d : %s -> %d",nbScore,actuel->nom, actuel->nombre); draw_text(405,height,30,strn,1);
        actuel = actuel->suivant;
        height=height+100;
        nbScore ++;
    }
    /*while (actuel->suivant != NULL)
    {
      suppression(maListe);
    }*/
  /////////fin liste chainée

  switch (get_event()) {
        case SDLK_RETURN: goto MENU;
        case SDLK_ESCAPE: goto MENU;
        case SDL_QUIT: goto CLOSE;
  }
    update_screen();
    SDL_Delay(50);
}

NEWGAME_SOLOPLAYER:
    //Definie les contour pour l'affichage du score 
    contour(1);
    //Spwan player 1
    x=330; y=180; dx=1; dy=0; pts=0;
    pset(x, y, 3);
    //Spawn IA
    x1=310; y1=170; dx1=1; dy1=0; pts1=0;
    pset(x1, y1, 2); 
    draw_green_square();
    //Rafraichie écran
    update_screen();
    SDL_Delay(100);
    //Met la police en petit pour le score 
    police = TTF_OpenFont("./TRON.ttf", 25);
    goto WALK_SOLOPLAYER;

WALK_SOLOPLAYER:

      if (speed==1){SDL_Delay(10);}
      if (speed==2){SDL_Delay(7);}
      if (speed==3){SDL_Delay(4);}
      
      check=0;
      switch (get_event()) {
      //Control Player 1
      case SDLK_UP:   dx=0; dy=-1; break;
      case SDLK_DOWN: dx=0; dy=1; break;
      case SDLK_LEFT: dx=-1; dy=0; break;
      case SDLK_RIGHT: dx=1; dy=0; break;
      //Other control
      case SDLK_ESCAPE: goto END_SOLOPLAYER;
      case SDL_QUIT: goto CLOSE;
      }

      //Si IA vers la droite
      if(dx1==1 && dy1==0 && check==0){
      if (point[x1+4][y1]!=0 || point[x1+8][y1]!=0 ){
        dx1=0; dy1=1;
        check=1;
        if (point[x1][y1+4] != 0 ){
          dx1=0; dy1=-1;
        }
        if (point[x1][y1-4] != 0 ){
          dx1=0; dy1=1;
        }
       }
      }
      //Si IA vers la gauche
      if(dx1==-1 && dy1==0 && check==0){
      if (point[x1-4][y1] != 0 ){
        dx1=0; dy1=1;
        check=1;
        if (point[x1][y1+4] != 0 ){
          dx1=0; dy1=-1;
        }
        if (point[x1][y1-4] != 0 ){
          dx1=0; dy1=1;
        }
       }
      }
      //Si IA vers le bas
      if(dx1==0 && dy1==1 && check==0){
      if (point[x1][y1+4] != 0 ){
        dx1=1; dy1=0;
        check=1;
        if (point[x1+4][y1] != 0 ){
          dx1=-1; dy1=0;
        }
        if (point[x1-4][y1] != 0 ){
          dx1=1; dy1=0;
        }
       }
      }
      //Si IA vers le haut
      if(dx1==0 && dy1==-1 && check==0){
      if (point[x1][y1-4] != 0 ){
        dx1=1; dy1=0;
        check=1;
        if (point[x1+4][y1] != 0 ){
          dx1=-1; dy1=0;
         }
        if (point[x1-4][y1] != 0 ){
          dx1=1; dy1=0;
        }
       }
      }
      
      /*if(x-x1>10 && check==0)
        if (point[x1-4][y1] != 0 ){
        {
          dx1=1; 
          dy1=1;
          check=1; 
        }}
      if(x-x1<-10 && check==0)
        if (point[x1-4][y1] != 0 ){
        {
          dx1=-1; 
          dy1=1;
          check=1; 
        }}
      if(y-y1>10 && check==0)
        if (point[x1][y1+4] != 0 ){
        {
          dx1=1; 
          dy1=1;
          check=1;
        }}
      if(y-y1<-10 && check==0)
        if (point[x1][y1-4] != 0 ){
        {
          dx1=1; 
          dy1=-1;
          check=1;
        }}*/

      //printf("x:%d y:%d x1:%d y1:%d x-x1:%d y-y1:%d\n",x,y,x1,y1,x-x1,y-y1);

    //Add direction to cursor to make it move 
    x=x+dx; y=y+dy;
    x1=x1+dx1; y1=y1+dy1;

    //If players cross red or green lines
    if (point[x][y] == 3){winner=2; goto END_SOLOPLAYER;} 
    if (point[x][y] == 2) {winner=2; goto END_SOLOPLAYER;} 
    if (point[x1][y1] == 3) {winner=1; goto END_SOLOPLAYER;} 
    if (point[x1][y1] == 2) {winner=1; goto END_SOLOPLAYER;} 
        //If player one hit green pixel
    if (point[x][y] == 1) hit_green_pixel();
    if (point[x1][y1] == 1) hit_green_pixel();

    pts++;
    draw_score(pts);
    pset(x, y, 3);
    pset(x1, y1, 2);
    update_screen(); 
    goto WALK_SOLOPLAYER;


NEWGAME_MULTIPLAYER:
    contour(1);//Definie les contour pour l'affichage du score 
    x=330; y=180; dx=1; dy=0; pts=0;    //Spwan player 1
    pset(x, y, 3);
    x1=310; y1=180; dx1=-1; dy1=0; pts1=0;    //Spawn player 2 
    pset(x1, y1, 2); 
    draw_green_square(); //Draw breen square
    update_screen();     //Refresh screen
    SDL_Delay(100); //Add delay
    police = TTF_OpenFont("./TRON.ttf", 25);    //Change policy to desired
    goto WALK_MULTIPLAYER;

WALK_MULTIPLAYER:

      if (speed==1){SDL_Delay(10);}
      if (speed==2){SDL_Delay(7);}
      if (speed==3){SDL_Delay(4);}

      switch (get_event()) {
      //Control Player 1
      case SDLK_UP:   dx=0; dy=-1; break;
      case SDLK_DOWN: dx=0; dy=1; break;
      case SDLK_LEFT: dx=-1; dy=0; break;
      case SDLK_RIGHT: dx=1; dy=0; break;
      //Control Player 2
      case SDLK_z:   dx1=0; dy1=-1; break;
      case SDLK_s: dx1=0; dy1=1; break;
      case SDLK_q: dx1=-1; dy1=0; break;
      case SDLK_d: dx1=1; dy1=0; break;
      //Other control
      case SDLK_ESCAPE: goto END_MULTIPLAYER;
      case SDL_QUIT: goto CLOSE;
    }
    
    //Add direction to cursor to make it move 
    x=x+dx; y=y+dy;
    x1=x1+dx1; y1=y1+dy1;

    //If players cross red or green lines
    if (point[x][y] == 3) goto END_MULTIPLAYER;
    if (point[x][y] == 2) goto END_MULTIPLAYER;
    if (point[x1][y1] == 3) goto END_MULTIPLAYER;
    if (point[x1][y1] == 2) goto END_MULTIPLAYER;
    //If player one hit green pixel
    if (point[x][y] == 1) hit_green_pixel();
    if (point[x1][y1] == 1) hit_green_pixel();
    //If player two hit green pixel
    //if (point1[x1][y1] == 1) hit_green_pixel();
    pts++;
    draw_score(pts);
    pset(x, y, 3);
    pset(x1, y1, 2);
    update_screen();
    goto WALK_MULTIPLAYER;

END_MULTIPLAYER:
    while (get_event()) {}  // empty the event queue
    while (1) {
      SDL_Delay(50);
      switch (get_event()) {
    case SDLK_p:
    case SDLK_RETURN:
    case SDLK_SPACE:  goto NEWGAME_MULTIPLAYER;
        case SDLK_ESCAPE: tour++; goto MENU;
        case SDL_QUIT: goto CLOSE;
      }
    }

END_SOLOPLAYER:
    contour(0);
    inser=0;  
    suppression(maListe);
    lire(maListe);
    //insertion(maListe,"antoine", pts);
    draw_score_final(maListe,pts);
    if (inser==1)
    {
      insertion(maListe,chaine, pts);
      ecrire(maListe);
      tour++; goto MENU;
    }

    update_screen();

    while (get_event()) {}  // empty the event queue
    while (1) {
      SDL_Delay(10);
      switch (get_event()) {
        case SDLK_p:
        case SDLK_RETURN:
        case SDLK_SPACE: goto NEWGAME_SOLOPLAYER;
        case SDLK_ESCAPE: tour++; goto MENU;
        case SDL_QUIT: goto CLOSE;
      }
    }

CLOSE:
    //TTF_CloseFont(police); /* Permet de femer la police, Doit être avant TTF_Quit() */
    TTF_Quit();
    SDL_FreeSurface(texte);
    SDL_Quit();
    return 0;
}