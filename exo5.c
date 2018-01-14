#include "exo5.h"

void enfile_liste (Cellule_som ** liste, Sommet *som){
	Cellule_som *cell = (Cellule_som *) malloc(sizeof(Cellule_som));
	cell->sommet=som;
	cell->suiv=NULL;
	if (*liste == NULL){
		*liste = cell;
		return;
	}
	Cellule_som *tmp = (*liste);
	while (tmp->suiv) tmp=tmp->suiv;
	tmp->suiv = cell;
}

Sommet *defile_liste (Cellule_som **liste){
	if (*liste == NULL) return NULL;
	Sommet *som=(*liste)->sommet;
	Cellule_som *tmp = (*liste)->suiv;
	free(*liste);
	(*liste)=tmp;
	return som;
}

int fini_parcour (Graphe_zone *G)
{
	Cellule_som *tmp=G->som;
	while(tmp!=NULL){
		if (tmp->sommet->marque != 0) return 0;
		tmp=tmp->suiv;
	}
	return 1;
}

int remplit_distance_largeur (Graphe_zone *G, Sommet *racine, int nbsomori){
	int dmax=0; //distance plus loin
	char *visit = malloc (sizeof(char)*nbsomori);
	int i;
	for (i=0;i<G->nbsom;i++) visit[i] = 0;
	Cellule_som *File = NULL;
	visit[racine->num-1] = 1; //numeroter a partir de 1
	enfile_liste(&File, racine);
	racine->distance = 0;
	racine->pere = NULL;
	Cellule_som *cour;
	while (File){
		Sommet *som = defile_liste(&File);
		if (som->distance > dmax) dmax = som->distance;
		cour=som->sommet_adj;
		while (cour){
			if (visit[cour->sommet->num-1] == 0){
				visit[cour->sommet->num-1] = 1;
				cour->sommet->pere=som;
				cour->sommet->distance = som->distance+1;
				enfile_liste (&File, cour->sommet);
			}
			cour = cour->suiv;
		}
	}
	return dmax;
}

void plus_court_chemin_graphe_zone(Graphe_zone* G)
{
	//Sauvegarde les marques
	int sauvegarde [G->nbsom];
	int i=0;
	Cellule_som *tmp=G->som;
	while(tmp!=NULL){
		tmp->sommet->distance=-1;
		tmp->sommet->pere=NULL;
		sauvegarde[i]=tmp->sommet->marque;
		tmp->sommet->marque=3;
		i++;
		tmp=tmp->suiv;
	}
	
	G->mat[0][0]->distance = 0;
	tmp=G->mat[0][0]->sommet_adj;
	G->mat[0][0]->marque=1;
	
	while (!fini_parcour (G)){
		tmp=G->som;
		while (tmp){
			if (tmp->sommet->marque == 1){
				Cellule_som *tmp2=tmp->sommet->sommet_adj;
				while (tmp2){
					if (tmp2->sommet->marque == 3){
						tmp2->sommet->marque = 2;
						tmp2->sommet->pere=tmp->sommet;
						tmp2->sommet->distance=1+tmp2->sommet->pere->distance;
					}
					tmp2=tmp2->suiv;
				}
				tmp->sommet->marque=0; //ferme le sommet
			}
			tmp = tmp->suiv;	
		}
		tmp=G->som;
		while (tmp){
			if (tmp->sommet->marque == 2){
				tmp->sommet->marque = 1;
			}
			tmp = tmp->suiv;
		}
	}
	
	//Retourne les marques
	tmp=G->som;
	i=0;
	while(tmp!=NULL){
		tmp->sommet->marque=sauvegarde[i];
		i++;
		tmp=tmp->suiv;
	}
}




void affiche_graphe_plus_court (Graphe_zone *G){
	Cellule_som *tmp=G->som;
	while(tmp!=NULL){
		printf("Zone numero %d taille %d couleur %d distance %d\n", tmp->sommet->num,tmp->sommet->nbcase_som,tmp->sommet->cl,tmp->sommet->distance);
		tmp=tmp->suiv;
	}										
}

int sequence_plus_court_chemin (Grille *Grl, Graphe_zone *G, Sommet *destination, int aff){
	int taille=destination->distance;
	int * listeCouleur = (int *) malloc(sizeof(int)*taille);
	int i;
	Sommet *tmp=destination;
	for (i=taille-1;i>=0;i--){
		listeCouleur[i]=tmp->cl;
		tmp=tmp->pere;
	}
	for (i=0;i<taille;i++) mise_a_jour_zsg (Grl,G,G->mat[0][0], listeCouleur[i], aff);
	return taille;
}
