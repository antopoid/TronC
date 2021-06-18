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
    SDL_EnableUNICODE(SDL_ENABLE); //active le dechifrage des carracteres ascii grace à unicode
    int i=0, j=0;
    memset(chaine, 0, 80); //permet de remplir le tableau de 0
    SDL_Color couleurCyan = {120, 239, 252};
    SDL_Color couleurNoir = {0, 0, 0};
    //Definie le fond en noir 
    for (i=300; i<=400; ++i) for (j=110; j<=150; ++j) pset(i, j, 0);
    //Barre superieur et inferieur 
    for (i=170; i<=470; ++i) { pset(i, 150, 3); pset(i, 200, 3); pset(i, 359, 3); }
    //Barre gauche et droite 
    for (j=150; j<=200; ++j) { pset(170, j, 3); pset(470, j, 3); }  
    
    SDL_Rect position; //definie les positions de l'ecriture
            position.x = 670;
            position.y = 328;
            sprintf(score, "Score : %d", pts); /* On écrit dans la chaîne le nouveau score */
            texte = TTF_RenderText_Shaded(police, score, couleurCyan, couleurNoir); /* On écrit la chaine temps dans la SDL_Surface */

    SDL_BlitSurface(texte, NULL, screen, &position); // Blit du texte 

    i=0;
    while(i <= 10) {
 
    SDL_WaitEvent(&event);
    
    if(event.key.keysym.unicode >= 'a' && event.key.keysym.unicode <= 'z') {strcat(chaine,SDL_GetKeyName(event.key.keysym.unicode));i++;} //recupere les touches appuyé entre a et z
    else if(event.key.keysym.unicode >= 'A' && event.key.keysym.unicode <= 'Z') {strcat(chaine,SDL_GetKeyName(event.key.keysym.unicode));i++;} //recupere les touches appuyé entre A et Z
    else if(event.key.keysym.sym == SDLK_RETURN) {inser=1;break;} //si la touche appuyé est entrée on insert dans la liste chainée
    else if(event.key.keysym.sym == SDLK_ESCAPE) {inser=1;break;} //si la touche appuyé est echap alors on insert et retour au menu
    else if(event.key.keysym.sym == SDL_QUIT) {inser=1;break;} //si la touche appuyé la croix alors on insert et quit
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

//fonction pour dessiner la grille (pas encore implementé)
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
    SDL_Color couleurVert = {0, 255, 0};
    //chercher fonction changement taille
    police = TTF_OpenFont("./ttf/TRON.ttf", size); // Chargement de la police 
    if(clr==1)texte = TTF_RenderText_Blended(police, strn, couleurCyan); // Écriture du texte dans la SDL_Surface texte en mode Blended (optimal)
    if(clr==3)texte = TTF_RenderText_Blended(police, strn, couleurVert); // Écriture du texte dans la SDL_Surface texte en mode Blended (optimal)
    if(clr==2)texte = TTF_RenderText_Blended(police, strn, couleurRouge); // Écriture du texte dans la SDL_Surface texte en mode Blended (optimal)
    SDL_Rect position;
    position.x = x;
    position.y = y;
    SDL_BlitSurface(texte, NULL, screen, &position); // Blit du texte //
    TTF_CloseFont(police); //Ferme la police
}
double calculate_distance_to_player(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)); //calcul de l'hypothenuse entre le joueur et l'IA grace au theoreme de pythagore (distance joueur - IA)
}

// La direction est modifiée par le biais des pointeurs
void set_next_direction(int x, int y, int *dx, int *dy, int new_dx, int new_dy) {
    int no_obstacle = 1;
    int step;
    // 0 = x, 1 = y
    int direction_axis = -1;

    if (new_dx != 0) {
        // Changement de direction en x, droite ou gauche
        direction_axis = 0;
    } else if (new_dy != 0) {
        // Changement de direction en y, haut ou bas
        direction_axis = 1;
    }

    if (direction_axis == 0) {
        step = 1;

        while (no_obstacle && step < DISTANCE_OBSTACLE) {
            no_obstacle = point[x + new_dx * step][y] == EMPTY_SQUARE;
            step++;
        }
    } else if (direction_axis == 1) {
        step = 1;

        while (no_obstacle && step < DISTANCE_OBSTACLE) {
            no_obstacle = point[x][y + new_dy * step] == EMPTY_SQUARE;
            step++;
        }
    }

    if (no_obstacle) {
        *dx = new_dx;
        *dy = new_dy;
    }
}

//Mode facile de l'IA
void move_ai_easy() {
    //Si IA vers la droite
    if (dx1 == 1 && dy1 == 0 && check == 0) {
        if (point[x_1 + 4][y_1] != 0 || point[x_1 + 8][y_1] != 0) {
            dx1 = 0;
            dy1 = 1;
            check = 1;
            if (point[x_1][y_1 + 4] != 0) {
                dx1 = 0;
                dy1 = -1;
            }
            if (point[x_1][y_1 - 4] != 0) {
                dx1 = 0;
                dy1 = 1;
            }
        }
    }
    //Si IA vers la gauche
    if (dx1 == -1 && dy1 == 0 && check == 0) {
        if (point[x_1 - 4][y_1] != 0) {
            dx1 = 0;
            dy1 = 1;
            check = 1;
            if (point[x_1][y_1 + 4] != 0) {
                dx1 = 0;
                dy1 = -1;
            }
            if (point[x_1][y_1 - 4] != 0) {
                dx1 = 0;
                dy1 = 1;
            }
        }
    }
    //Si IA vers le bas
    if (dx1 == 0 && dy1 == 1 && check == 0) {
        if (point[x_1][y_1 + 4] != 0) {
            dx1 = 1;
            dy1 = 0;
            check = 1;
            if (point[x_1 + 4][y_1] != 0) {
                dx1 = -1;
                dy1 = 0;
            }
            if (point[x_1 - 4][y_1] != 0) {
                dx1 = 1;
                dy1 = 0;
            }
        }
    }
    //Si IA vers le haut
    if (dx1 == 0 && dy1 == -1 && check == 0) {
        if (point[x_1][y_1 - 4] != 0) {
            dx1 = 1;
            dy1 = 0;
            check = 1;
            if (point[x_1 + 4][y_1] != 0) {
                dx1 = -1;
                dy1 = 0;
            }
            if (point[x_1 - 4][y_1] != 0) {
                dx1 = 1;
                dy1 = 0;
            }
        }
    }
}

//Mode normal de l'IA
void move_ai_normal() {
    direction_t direction;

    // Plus le dénominateur est élevé, moins la condition est probable
    if (rand() < RAND_MAX / 100) {
        // Entre 0 et 3, choisis une direction parmi celles possibles
        do {
            direction = possibleDirections[rand() % 4]; //Ajoute un coté impredictible a l'IA (random)
        } while (direction.x == dx1 && direction.y == dy1);

        set_next_direction(x_1, y_1, &dx1, &dy1, direction.x, direction.y);
    } else {
        //Si IA vers la droite
        if (dx1 == 1 && dy1 == 0 && check == 0) {
            if (point[x_1 + 4][y_1] != 0 || point[x_1 + 8][y_1] != 0) {
                dx1 = 0;
                dy1 = 1;
                check = 1;
                if (point[x_1][y_1 + 4] != 0) {
                    dx1 = 0;
                    dy1 = -1;
                }
                if (point[x_1][y_1 - 4] != 0) {
                    dx1 = 0;
                    dy1 = 1;
                }
            }
        }
        //Si IA vers la gauche
        if (dx1 == -1 && dy1 == 0 && check == 0) {
            if (point[x_1 - 4][y_1] != 0) {
                dx1 = 0;
                dy1 = 1;
                check = 1;
                if (point[x_1][y_1 + 4] != 0) {
                    dx1 = 0;
                    dy1 = -1;
                }
                if (point[x_1][y_1 - 4] != 0) {
                    dx1 = 0;
                    dy1 = 1;
                }
            }
        }
        //Si IA vers le bas
        if (dx1 == 0 && dy1 == 1 && check == 0) {
            if (point[x_1][y_1 + 4] != 0) {
                dx1 = 1;
                dy1 = 0;
                check = 1;
                if (point[x_1 + 4][y_1] != 0) {
                    dx1 = -1;
                    dy1 = 0;
                }
                if (point[x_1 - 4][y_1] != 0) {
                    dx1 = 1;
                    dy1 = 0;
                }
            }
        }
        //Si IA vers le haut
        if (dx1 == 0 && dy1 == -1 && check == 0) {
            if (point[x_1][y_1 - 4] != 0) {
                dx1 = 1;
                dy1 = 0;
                check = 1;
                if (point[x_1 + 4][y_1] != 0) {
                    dx1 = -1;
                    dy1 = 0;
                }
                if (point[x_1 - 4][y_1] != 0) {
                    dx1 = 1;
                    dy1 = 0;
                }
            }
        }
    }
}

//Mode hard de l'IA ( l'ia colle le joueur et reste tres agressive)
void move_ai_hard() {
    last_distance = current_distance;
    current_distance = (int) calculate_distance_to_player(x, y, x_1, y_1);

    // Le joueur s'éloigne de l'IA
    if (current_distance > last_distance) {
        // Le prochain pixel est libre
        if (point[x_1 + dx][y_1 + dy] == EMPTY_SQUARE) {
            // L'IA suit la direction du joueur
            set_next_direction(x_1, y_1, &dx1, &dy1, dx, dy);
            check = 1;
        }
    }

    //Si IA vers la droite
    if (dx1 == 1 && dy1 == 0 && check == 0) {
        if (point[x_1 + 1][y_1] != EMPTY_SQUARE) {
            dx1 = 0;
            dy1 = 1;
            check = 1;
            if (point[x_1][y_1 + 1] != EMPTY_SQUARE) {
                dx1 = 0;
                dy1 = -1;
            }
            if (point[x_1][y_1 - 1] != EMPTY_SQUARE) {
                dx1 = 0;
                dy1 = 1;
            }
        }
    }
    //Si IA vers la gauche
    if (dx1 == -1 && dy1 == 0 && check == 0) {
        if (point[x_1 - 1][y_1] != EMPTY_SQUARE) {
            dx1 = 0;
            dy1 = 1;
            check = 1;
            if (point[x_1][y_1 + 1] != EMPTY_SQUARE) {
                dx1 = 0;
                dy1 = -1;
            }
            if (point[x_1][y_1 - 1] != EMPTY_SQUARE) {
                dx1 = 0;
                dy1 = 1;
            }
        }
    }
    //Si IA vers le bas
    if (dx1 == 0 && dy1 == 1 && check == 0) {
        if (point[x_1][y_1 + 1] != EMPTY_SQUARE) {
            dx1 = 1;
            dy1 = 0;
            check = 1;
            if (point[x_1 + 1][y_1] != EMPTY_SQUARE) {
                dx1 = -1;
                dy1 = 0;
            }
            if (point[x_1 - 1][y_1] != EMPTY_SQUARE) {
                dx1 = 1;
                dy1 = 0;
            }
        }
    }
    //Si IA vers le haut
    if (dx1 == 0 && dy1 == -1 && check == 0) {
        if (point[x_1][y_1 - 1] != EMPTY_SQUARE) {
            dx1 = 1;
            dy1 = 0;
            check = 1;
            if (point[x_1 + 1][y_1] != EMPTY_SQUARE) {
                dx1 = -1;
                dy1 = 0;
            }
            if (point[x_1 - 1][y_1] != EMPTY_SQUARE) {
                dx1 = 1;
                dy1 = 0;
            }
        }
    }
}