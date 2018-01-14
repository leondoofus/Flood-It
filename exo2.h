#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "Liste_case.h"
#include "API_Grille.h"
#include "exo1.h"

typedef struct {
	int dim; 		/* dimension de la grille */
	int nbcl;		/* nombre de couleurs */

	Liste  Lzsg;	/* Liste des cases de la zone Zsg */
	Liste *B; 		/* Tableau de listes de cases de la bordure*/
	int **App;  	/* Tableau a double entree des appartenances */
} S_Zsg;


/*Initialise la Zsg*/
void init_Zsg(S_Zsg **s,int dim,int nbcl);

/*Ajout la case i, j dans la Zsg*/
void ajoute_Zsg(S_Zsg *s,int i,int j);

/*Retourne 1 si la case i,j de couleur cl se trouve dans le tableau de bordure, 0 sinon */
int appartient_Bordure (S_Zsg* s,int i, int j, int cl);

/*Retourne 1 si la case i,j se trouve dans la Zsg, 0 sinon*/
int appartient_Zsg(S_Zsg *s,int i,int j);

/*Agrandit la Zsg à partir de la case k,l*/
int agrandit_Zone(int **M, S_Zsg *Z, int cl, int k, int l);

/*Retourne le nombre de changement pour finir le jeu
Elle appelle la fonction agrandit_zone pour changer la couleur de la Zsg*/
int strequence_aleatoire_rapide(int **M, S_Zsg *Zone, Grille *G, int aff);

/*Affiche le tableau de App*/
void affiche_Zone (S_Zsg *s);

/*Retourne 1 si le tableau App est bien remplit par une seul couleur, 0 sinon*/
int test_plein(int dim,int **App);
