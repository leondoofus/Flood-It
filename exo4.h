#include "exo3.h"

/*Change la couleur des voisins de Zsg ayant la couleur cl en couleur de la Zsg*/
void mise_a_jour_zsg (Grille *Grl,Graphe_zone *G, Sommet *Zsg, int cl, int aff);

/*Calcul la couleur la plus présents dans les bordure chaque itération
Cette fonction retourne le nombre de changement*/
int sequence_graph_max_bordure(Grille *Grl,Graphe_zone *G, int nbcl, int aff);
