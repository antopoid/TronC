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
    SDL_Delay(20);
    //Met la police en petit pour le score 
    police = TTF_OpenFont("./ttf/TRON.ttf", 25);
    //draw_grille(); //Dessine une grille grise dans le fond de l'ecran
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