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
 if (bonus==1)
 {
  int h=(rand()%636)+1, v=(rand()%316)+1, x, y;
  for (x=h; x<=h+3; ++x) for (y=v; y<=v+3; ++y) pset(x, y, 1);
 }
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

void draw_grille (){
  for (int j = 10; j < 320; j=j+10)
  {
    for (int i=2; i<=638; ++i) {pset(i, j, 4);update_screen();}    
  } 
  for (int j = 0; j < 640; j=j+10)
  {
    for (int i=2; i<=320; ++i) {pset(j, i, 4);update_screen();} 
  }
}

//fonction pour ecrire du texte
void draw_text (int x, int y, int size, char strn[],int clr) {
    SDL_Color couleurCyan = {120, 239, 252};
    SDL_Color couleurRouge = {211, 44, 31};
    //chercher fonction changement taille
    police = TTF_OpenFont("./ttf/TRON.ttf", size); // Chargement de la police 
    if(clr==1)texte = TTF_RenderText_Blended(police, strn, couleurCyan); // Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) 
    if(clr==2)texte = TTF_RenderText_Blended(police, strn, couleurRouge); // Écriture du texte dans la SDL_Surface texte en mode Blended (optimal)
    SDL_Rect position;
    position.x = x;
    position.y = y;
    SDL_BlitSurface(texte, NULL, screen, &position); // Blit du texte //
    TTF_CloseFont(police); //Ferme la police
}