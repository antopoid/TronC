NEWGAME_MULTIPLAYER:
    contour(1);//Definie les contour pour l'affichage du score 
    x=330; y=180; dx=1; dy=0; pts=0;    //Spwan player 1
    pset(x, y, 3);
    x_1=310; y_1=180; dx1=-1; dy1=0; pts1=0;    //Spawn player 2 
    pset(x_1, y_1, 2); 
    draw_green_square(); //Draw breen square
    update_screen();     //Refresh screen
    SDL_Delay(100); //Add delay
    police = TTF_OpenFont("./ttf/TRON.ttf", 25);    //Change policy to desired
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
    x_1=x_1+dx1; y_1=y_1+dy1;

    //If players cross red or blue lines
    if (point[x][y] == 3) goto END_MULTIPLAYER;
    if (point[x][y] == 2) goto END_MULTIPLAYER;
    if (point[x_1][y_1] == 3) goto END_MULTIPLAYER;
    if (point[x_1][y_1] == 2) goto END_MULTIPLAYER;
    //If player one hit green pixel
    if (point[x][y] == 1) hit_green_pixel();
    if (point[x_1][y_1] == 1) hit_green_pixel();
    //If player two hit green pixel
    pts++;
    draw_score(pts);
    pset(x, y, 3);
    pset(x_1, y_1, 2);
    update_screen();
 
    goto WALK_MULTIPLAYER;

END_MULTIPLAYER:
    contour(0);
    inser=0;  
    suppression(maListe);
    lire(maListe);
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
      SDL_Delay(50);
      switch (get_event()) {
    case SDLK_p:
    case SDLK_RETURN:
    case SDLK_SPACE:  goto NEWGAME_MULTIPLAYER;
        case SDLK_ESCAPE: tour++; goto MENU;
        case SDL_QUIT: goto CLOSE;
      }
    }
