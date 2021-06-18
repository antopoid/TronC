NEWGAME_SOLOPLAYER:
      //Definie les contour pour l'affichage du score 
    contour(1);
    //Spwan player 1
    x = 330;
    y = 180;
    dx = 1;
    dy = 0;
    pts = 0;
    pset(x, y, PLAYER_ONE_COLOR);
    //Spawn IA
    x_1 = 310;
    y_1 = 170;
    dx1 = 1;
    dy1 = 0;
    pts1 = 0;
    pset(x_1, y_1, PLAYER_TWO_COLOR);
    draw_green_square();
    //Rafraichie écran
    update_screen();
    SDL_Delay(100);
    //Met la police en petit pour le score 
    police = TTF_OpenFont("./TRON.ttf", 25);
    goto WALK_SOLOPLAYER;

    WALK_SOLOPLAYER:

    if (speed == 1) { SDL_Delay(10); }
    if (speed == 2) { SDL_Delay(7); }
    if (speed == 3) { SDL_Delay(4); }

    check = 0;
    switch (get_event()) {
        //Control Player 1
        case SDLK_UP:
            dx = 0;
            dy = -1;
            break;
        case SDLK_DOWN:
            dx = 0;
            dy = 1;
            break;
        case SDLK_LEFT:
            dx = -1;
            dy = 0;
            break;
        case SDLK_RIGHT:
            dx = 1;
            dy = 0;
            break;
            //Other control
        case SDLK_ESCAPE:
            goto END_SOLOPLAYER;
        case SDL_QUIT:
            goto CLOSE;
    }

    switch (difficulty) {
        case 1:
            move_ai_easy();
            break;
        case 3:
            move_ai_hard();
            break;
        case 2:
        default:
            move_ai_normal();
            break;
    }

    //printf("x:%d y:%d x_1:%d y_1:%d x-x_1:%d y-y_1:%d\n",x,y,x_1,y_1,x-x_1,y-y_1);

    //Add direction to cursor to make it move 
    x = x + dx;
    y = y + dy;
    x_1 = x_1 + dx1;
    y_1 = y_1 + dy1;

    //If players cross red or green lines
    if (point[x][y] == PLAYER_ONE_COLOR) {
        winner = 2;
        goto END_SOLOPLAYER;
    }
    if (point[x][y] == PLAYER_TWO_COLOR) {
        winner = 2;
        goto END_SOLOPLAYER;
    }
    if (point[x_1][y_1] == PLAYER_ONE_COLOR) {
        winner = 1;
        goto END_SOLOPLAYER;
    }
    if (point[x_1][y_1] == PLAYER_TWO_COLOR) {
        winner = 1;
        goto END_SOLOPLAYER;
    }
    //If player one hit green pixel
    if (point[x][y] == GREEN_SQUARE_COLOR) hit_green_pixel();
    if (point[x_1][y_1] == GREEN_SQUARE_COLOR) hit_green_pixel();

    pts++;
    draw_score(pts);
    pset(x, y, PLAYER_ONE_COLOR);
    pset(x_1, y_1, PLAYER_TWO_COLOR);
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