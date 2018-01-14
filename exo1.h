#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "Liste_case.h"
#include "API_Grille.h"

/*Retourne 1 si la case i,j est dans la liste L, 0 sinon*/
int dans_la_liste (Liste L, int i, int j);

/*Affiche la liste*/
void affiche_liste (Liste L);

/*Cherche la Zsg et met à jour la valeur taille recursivement*/
void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, Liste *L);

/*Cherche la Zsg et met à jour la valeur taille impérativement*/
void trouve_zone_imp(int **M, int dim, int i, int j, int *taille, Liste *L);

/*Retourne le nombre de changement pour finir le jeu
Elle appelle la fonction trouve_zone_rec ou trouve_zone_imp pour changer la couleur de la Zsg
mode : 0 - recursif, 1 - imperatif
compteur compten le nombre d'iteration et permet a sequence_aleatoire d'être recursive terminale*/
int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff, int mode,int compteur, int modeaff);
