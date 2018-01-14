#include "exo4.h"

/*Enfile un sommet dans une liste des sommets*/
void enfile_liste (Cellule_som ** liste, Sommet *som);

/*Defile un sommet d'une liste de sommet, retourne un pointeur vers le sommet defile*/
Sommet *defile_liste (Cellule_som **liste);

/*Retourne 1 si le jeu est fini, 0 sinon*/
int fini_parcour (Graphe_zone *G);

/*Calcul la distance de tous les sommets d'un graphe a partir de la racine en utilisant la file
Cette fonction retourne la distance maximale depuis la racine*/
int remplit_distance_largeur (Graphe_zone *G, Sommet *racine, int nbsomori);

/*Calcul la distance de tous les sommets d'un graphe a partir de la Zsg en utilisant la marque*/
void plus_court_chemin_graphe_zone(Graphe_zone* G);

/*Affiche un graphe sous forme texte avec la distance des sommets*/
void affiche_graphe_plus_court (Graphe_zone *G);

/*Retourne le nombre de changement couleurs pour arriver a la destination*/
int sequence_plus_court_chemin (Grille *Grl, Graphe_zone *G,Sommet *destination, int aff);
