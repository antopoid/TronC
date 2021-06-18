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

    while (actuel != NULL && nbScore<=6)
    {
        sprintf(strn, "%d : %s -> %d",nbScore,actuel->nom, actuel->nombre); draw_text(405,height,30,strn,1);
        actuel = actuel->suivant;
        height=height+100;
        nbScore ++;
    }

  /////////fin liste chainée

  switch (get_event()) {
        case SDLK_RETURN: goto MENU;
        case SDLK_ESCAPE: goto MENU;
        case SDL_QUIT: goto CLOSE;
  }
    update_screen();
    SDL_Delay(50);
}
