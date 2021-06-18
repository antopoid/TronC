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
               sprintf(strn, "Welcome to TRONC"); draw_text(60,10,55,strn,1); 
               sprintf(strn, "Multiplayer 1 vs 1"); draw_text(60,230,25,strn,2);           
               sprintf(strn, "Soloplayer 1 vs IA"); draw_text(60,310,25,strn,1);
               sprintf(strn, "Scores"); draw_text(60,400,25,strn,1);
               sprintf(strn, "Settings"); draw_text(60,480,25,strn,1);
               sprintf(strn, "Exit"); draw_text(60,560,25,strn,1);
               }

if(pointeur==1){ 
               sprintf(strn, "Welcome to TRONC"); draw_text(60,10,55,strn,1); 
               sprintf(strn, "Multiplayer 1 vs 1"); draw_text(60,230,25,strn,1);           
               sprintf(strn, "Soloplayer 1 vs IA"); draw_text(60,310,25,strn,2);
               sprintf(strn, "Scores"); draw_text(60,400,25,strn,1);
               sprintf(strn, "Settings"); draw_text(60,480,25,strn,1);
               sprintf(strn, "Exit"); draw_text(60,560,25,strn,1);
               }

if(pointeur==2){ 
               sprintf(strn, "Welcome to TRONC"); draw_text(60,10,55,strn,1); 
               sprintf(strn, "Multiplayer 1 vs 1"); draw_text(60,230,25,strn,1);           
               sprintf(strn, "Soloplayer 1 vs IA"); draw_text(60,310,25,strn,1);
               sprintf(strn, "Scores"); draw_text(60,400,25,strn,2);
               sprintf(strn, "Settings"); draw_text(60,480,25,strn,1);
               sprintf(strn, "Exit"); draw_text(60,560,25,strn,1);
               }

if(pointeur==3){ 
               sprintf(strn, "Welcome to TRONC"); draw_text(60,10,55,strn,1); 
               sprintf(strn, "Multiplayer 1 vs 1"); draw_text(60,230,25,strn,1);           
               sprintf(strn, "Soloplayer 1 vs IA"); draw_text(60,310,25,strn,1);
               sprintf(strn, "Scores"); draw_text(60,400,25,strn,1);
               sprintf(strn, "Settings"); draw_text(60,480,25,strn,2);
               sprintf(strn, "Exit"); draw_text(60,560,25,strn,1);
              }

if(pointeur==4){ 
               sprintf(strn, "Welcome to TRONC"); draw_text(60,10,55,strn,1); 
               sprintf(strn, "Multiplayer 1 vs 1"); draw_text(60,230,25,strn,1);           
               sprintf(strn, "Soloplayer 1 vs IA"); draw_text(60,310,25,strn,1);
               sprintf(strn, "Scores"); draw_text(60,400,25,strn,1);
               sprintf(strn, "Settings"); draw_text(60,480,25,strn,1);
               sprintf(strn, "Exit"); draw_text(60,560,25,strn,2);
              }
tour=0;
} 
sprintf(strn, "Player 1 Controls"); draw_text(700,300,25,strn,1);
sprintf(strn, "UP"); draw_text(800,330,18,strn,1);
sprintf(strn, "DOWN"); draw_text(800,430,18,strn,1);
sprintf(strn, "LEFT"); draw_text(750,380,18,strn,1);
sprintf(strn, "RIGHT"); draw_text(850,380,18,strn,1);

sprintf(strn, "Player 2 Controls"); draw_text(800,570,25,strn,1);
sprintf(strn, "Z"); draw_text(800,600,18,strn,1);
sprintf(strn, "S"); draw_text(800,600,18,strn,1);
sprintf(strn, "Q"); draw_text(7700,600,18,strn,1);
sprintf(strn, "D"); draw_text(830,600,18,strn,1);  

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