#include<stdlib.h>
#include "exo1.h"
#include "Liste_case.h"

typedef struct sommet Sommet ;
/* Element d’une liste chainee de pointeurs sur Sommets */

typedef struct cellule_som {
	Sommet * sommet;
	struct cellule_som * suiv ;
} Cellule_som ;

struct sommet{
	int num ; /* Numero du sommet (sert uniquement a l’affichage) */
	int cl ; /* Couleur d’origine du sommet-zone */
	Liste cases ; 
	/* Listes des cases du sommet-zone */
	int nbcase_som ; /* Nombre de cases de cette liste */
	Cellule_som * sommet_adj ; /* Liste des aretes/pointeurs sur les sommets
	adjacents */
	int marque;
	int distance; /* Nombre d'aretes reliant ce sommet a la racine du parcours en largeur */
	Sommet *pere; /* Pere du sommet dans l'arborescence du parcours en largeur */
};
typedef struct graphe_zone {
	int nbsom ; /* Nombre de sommets dans le graphe */
	Cellule_som * som ; /* Liste chainee des sommets du graphe */
	Sommet *** mat ; /* Matrice de pointeurs sur les sommets indiquant
	a quel sommet appartient une case (i,j) de la grille */
} Graphe_zone;

/*Ajout un sommet dans une liste des sommets*/
void ajoute_liste_sommet(Cellule_som **liste, Sommet *som);


/*Supprimer une liste des sommets*/
void detruit_liste_somme(Cellule_som *liste);

/*Ajout 2 sommets dans leur liste des adjacents*/
void ajoute_voisin(Sommet *s1, Sommet *s2);

/*Retourne 1 si 2 sommets sont adjacents, 0 sinon*/
int adjacent(Sommet *s1,Sommet *s2);

/*Initialisation d'un graphe*/
void init_graphe_zone(Graphe_zone **G, int dim);

/*Creation d'un graphe*/
void cree_graphe_zone(Graphe_zone* G,int** M,int dim);

/*Affiche un graphe sous forme texte*/
void affiche_graphe (Graphe_zone *G);
