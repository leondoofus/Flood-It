#include "exo5.h"

/*Retourne le pointeur ver le sommet plus loin d'un graphe*/
Sommet *sommet_plus_ploin(Graphe_zone *G, int dmax);

/*Retourne le nombre de changement pour arriver au sommet plus loin recursivement*/
int sequence_plus (Grille *Grl, Graphe_zone *G, int nbsomori, int aff);

/*Retourne le nombre de changement pour arriver aux coins de la grille, puis appliquer max_bordure*/
int sequence_coins_max_bordure (Grille *Grl, Graphe_zone *G, int nbsomori, int dim, int nbcl, int aff);

/*Retourne le nombre de changement en parcourant le graphe en largeur*/
int sequence_largeur (Grille *Grl, Graphe_zone *G, int nbsomori, int aff);
