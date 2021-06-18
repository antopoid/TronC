SETTINGS:

fichier=fopen("data/settings.txt","r");// (pour read) ouverture en lecture. Le fichier doit exister.
    if (print==1)
    {
      fichier=fopen("data/settings.txt","w");
      fprintf(fichier, "%d %d %d",speed ,difficulty, bonus);
      fclose(fichier);
      print=0;
    }
    if (fichier == NULL)
    {
      printf("Erreur fichier\n");
        fclose(fichier);
    }
    else
    {
       fscanf(fichier,"%d %d %d",&speed ,&difficulty, &bonus);
    }
fclose(fichier);

contour(0); //dessine les contours sans afficher le score
while (get_event()) {}  // empty the event queue
while (1) 
{
      if(pointeur>2)pointeur=0;if(pointeur<0)pointeur=2;if(speed>3)speed=3;if(speed<1)speed=1;if(difficulty>3)difficulty=3;if(difficulty<1)difficulty=1;if(bonus<0)bonus=0;if(bonus>1)bonus=1;
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
        sprintf(strn, "Bonus"); draw_text(330,480,25,strn,1);
            if (bonus == 1){sprintf(strn, "ON"); draw_text(650,480,25,strn,1);}
            if (bonus == 0){sprintf(strn, "OFF"); draw_text(650,480,25,strn,1);}
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
        sprintf(strn, "Bonus"); draw_text(330,480,25,strn,1);
            if (bonus == 1){sprintf(strn, "ON"); draw_text(650,480,25,strn,1);}
            if (bonus == 0){sprintf(strn, "OFF"); draw_text(650,480,25,strn,1);}
      }
      if(pointeur==2){  
         sprintf(strn, "Settings"); draw_text(450,100,40,strn,1);
         sprintf(strn, "Speed"); draw_text(330,280,25,strn,1);
            if (speed == 3){sprintf(strn, "FAST"); draw_text(650,280,25,strn,1);}
            if (speed == 2){sprintf(strn, "MEDIUM"); draw_text(650,280,25,strn,1);}
            if (speed == 1){sprintf(strn, "SLOW"); draw_text(650,280,25,strn,1);}
         sprintf(strn, "Difficullty"); draw_text(330,380,25,strn,1);
            if (difficulty == 3){sprintf(strn, "HARD"); draw_text(650,380,25,strn,2);}
            if (difficulty == 2){sprintf(strn, "NORMAL"); draw_text(650,380,25,strn,2);}
            if (difficulty == 1){sprintf(strn, "EASY"); draw_text(650,380,25,strn,2);}
        sprintf(strn, "Bonus"); draw_text(330,480,25,strn,1);
            if (bonus == 1){sprintf(strn, "ON ->"); draw_text(650,480,25,strn,2);}
            if (bonus == 0){sprintf(strn, "<- OFF"); draw_text(650,480,25,strn,2);}
      }

  switch (get_event()) {
    case SDLK_UP: pointeur --; goto SETTINGS;
    case SDLK_DOWN: pointeur ++; goto SETTINGS;
    case SDLK_RIGHT: if(pointeur==0)speed++; if(pointeur==1)difficulty++; print=1; if(pointeur==2)bonus--; goto SETTINGS;
    case SDLK_LEFT: if(pointeur==0)speed--; if(pointeur==1)difficulty--; print=1; if(pointeur==2)bonus++; goto SETTINGS;
        case SDLK_RETURN: goto MENU;
        case SDLK_ESCAPE: goto MENU;
        case SDL_QUIT: goto CLOSE;
  }
    update_screen();
    SDL_Delay(50);
}