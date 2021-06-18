#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///// STRUCTURE /////

typedef struct Element Element;
struct Element
{
  char* nom;
    int nombre;
    Element *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    Element *premier;
};

Liste *initialisation();
void insertion(Liste *liste,char* nvNom, int nvNombre);
void suppression(Liste *liste);
void afficherListe(Liste *liste);

///// FONCTION /////

Liste *initialisation()
{
    Liste *liste = malloc(sizeof(*liste));
    liste->premier =NULL;
    return liste;
}


void insertion(Liste *liste,char* nvNom, int nvNombre)
{
    /* Création du nouvel élément */
    Element *nouveau = malloc(sizeof(Element));
    nouveau->nombre=nvNombre;
    nouveau->nom = (char*)malloc((strlen(nvNom))*sizeof(char));
    strcpy(nouveau->nom,nvNom);
    nouveau->suivant=NULL;

    Element *temp = malloc(sizeof(Element));
   
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    if (liste->premier==NULL)
    {
      liste->premier=nouveau;
    }else{
        temp=liste->premier;
        if (temp->nombre < nouveau->nombre)
        {
            liste->premier = nouveau;
            nouveau->suivant = temp;
        }else{
            while(temp->suivant!=NULL){
                if (temp->suivant->nombre < nvNombre)
                {
                    nouveau->suivant=temp->suivant;
                    temp->suivant=nouveau;
                    break;
                }
                temp=temp->suivant;
            }
            if (temp->suivant == NULL)
            {
                temp->suivant=nouveau;
            }
        }
    }
    
    /*nouveau->suivant = liste->premier;     // Insertion de l'élément au début de la liste 
    liste->premier = nouveau;*/
}


void suppression(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    while (liste->premier != NULL)
    {
        //printf("suppression\n");
        Element *aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }
}

void afficherListe(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Element *actuel = liste->premier;

    while (actuel != NULL)
    {
        printf("%s %d\n",actuel->nom, actuel->nombre);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}

void ecrire(Liste *liste)
{
    FILE  *fichier; // FILE en majuscule
      Element *actuel = liste->premier;
      fichier=fopen("data/score.txt","w");
      while(actuel!=NULL)
      {
        fprintf(fichier,"%s %d\n",actuel->nom,actuel->nombre);
        actuel=actuel->suivant;
      }  
      fclose(fichier);
}

void lire(Liste *liste)
{
    char* name=malloc(100*sizeof(char));
    int score;
    FILE  *fichier; // FILE en majuscule
    fichier=fopen("data/score.txt","r");// (pour read) ouverture en lecture. Le fichier doit exister.
    if (fichier == NULL)
    {
      printf("Erreur fichier\n");
        fclose(fichier);
    }
    else{
        while(fscanf(fichier,"%s %d\n",name, &score) != EOF)
        {
           insertion(liste,name, score);
        }
      fclose(fichier);
    }
}