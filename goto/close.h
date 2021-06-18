CLOSE:
    //TTF_CloseFont(police); /* Permet de femer la police, Doit être avant TTF_Quit() */
    TTF_Quit();
    SDL_FreeSurface(texte);
    SDL_Quit();
    return 0;