#include "exo4.h"

void mise_a_jour_zsg (Grille *Grl,Graphe_zone *G, Sommet *Zsg, int cl, int aff)
{
	Cellule_som *tmp = Zsg->sommet_adj;
	while(tmp){
		if(tmp->sommet->marque == 1 && tmp->sommet->cl==cl){
			G->nbsom--;
			tmp->sommet->marque = 0;
			
			Cellule_som *tmp2 = tmp->sommet->sommet_adj;
			while(tmp2){
				if (tmp2->sommet->marque == 2){
					tmp2->sommet->marque=1;
					ajoute_voisin(Zsg,tmp2->sommet);
					//supprime zsg de la liste adj de tmp2
				}
				tmp2=tmp2->suiv;
				//Ajoute en tête dans Zsg->sommet_adj si il n'y est pas déjà et n'est pas dans la Zsg
			}
			Elnt_liste *tmp3 = tmp->sommet->cases;
			//Elnt_liste *tmp4;
			while(tmp3){
				ajoute_en_tete (&(Zsg->cases), tmp3->i, tmp3->j);
				Zsg->nbcase_som++;
				G->mat[tmp3->i][tmp3->j] = Zsg;
				if (aff) Grille_attribue_couleur_case(Grl, tmp3->i, tmp3->j, Zsg->cl);
				tmp3=tmp3->suiv;
				//Ajoute en tête dans Zsg->cases et modifie M[i][j] et attribue couleur
			}
			if (aff) Grille_redessine_Grille();
			*(tmp->sommet) = *Zsg;
		}
		tmp=tmp->suiv;	
	}
			
}


int sequence_graph_max_bordure(Grille *Grl,Graphe_zone *G, int nbcl, int aff){
	int nbCoup=0;
	while(G->nbsom != 1){
		int tab [nbcl];
		int i;
		for(i=0;i<nbcl;i++) tab[i]=0;
		Cellule_som *tmp = G->mat[0][0]->sommet_adj; 
		while(tmp){
			if (tmp->sommet->marque==1)
				tab[tmp->sommet->cl] += tmp->sommet->nbcase_som;
			tmp = tmp->suiv;	
		}
		int clMax=0;
		int max=0;
		for(i=0;i<nbcl;i++){
			if(tab[i]>max){
				clMax=i;
				max=tab[i];
			}
		}
	mise_a_jour_zsg (Grl,G,G->mat[0][0], clMax, aff);
	nbCoup++;
	}
	return nbCoup;
}

