#include "exo6.h"

Sommet *sommet_plus_loin(Graphe_zone *G, int dmax){
	Cellule_som *tmp=G->som;
	while(tmp){
		if (tmp->sommet->distance == dmax){
			return tmp->sommet;
		}
		tmp=tmp->suiv;
	}
	return NULL;
}

int sequence_plus (Grille *Grl, Graphe_zone *G, int nbsomori, int aff){
	if (!fini_parcour(G)){
		int dmax=remplit_distance_largeur (G, G->mat[0][0], nbsomori);
		Sommet *plusloin = sommet_plus_loin (G, dmax);
		return sequence_plus_court_chemin (Grl, G, plusloin, aff) + sequence_plus (Grl, G, nbsomori, aff);
	} else {
		return 0;
	}
}

int sequence_coins_max_bordure (Grille *Grl, Graphe_zone *G, int nbsomori, int dim, int nbcl, int aff){
	remplit_distance_largeur (G, G->mat[0][0], nbsomori);
	int change = sequence_plus_court_chemin (Grl, G, G->mat[dim-1][dim-1], aff);
	remplit_distance_largeur (G, G->mat[0][0], nbsomori);
	change += sequence_plus_court_chemin (Grl, G, G->mat[0][dim-1], aff);
	remplit_distance_largeur (G, G->mat[0][0], nbsomori);
	change += sequence_plus_court_chemin (Grl, G, G->mat[dim-1][0], aff);
	change += sequence_graph_max_bordure(Grl, G, nbcl, aff);
	return change;
}

int sequence_largeur (Grille *Grl, Graphe_zone *G, int nbsomori, int aff){
	int dmax = remplit_distance_largeur (G, G->mat[0][0], nbsomori);
	int change = 0;
	int i;
	for (i=1; i<=dmax; i++){
		Cellule_som *cour = G->som;
		while (cour){
			if (cour->sommet->distance == i){
				mise_a_jour_zsg (Grl, G, G->mat[0][0], cour->sommet->cl, aff);
				change ++;
			}
			cour = cour->suiv;
		}
	}
	return change;
}
