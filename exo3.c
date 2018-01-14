#include "exo3.h"

void ajoute_liste_sommet(Cellule_som **liste,Sommet *som)
{
	Cellule_som *cell = (Cellule_som *) malloc(sizeof(Cellule_som));
	cell->sommet=som;
	cell->suiv=*liste;
	*liste=cell;
}
void detruit_liste_somme(Cellule_som *liste)
{
	Cellule_som *tmp;
	while(liste)
	{
		tmp=liste;
		free(tmp);
		liste=liste->suiv;
	}
}
void ajoute_voisin(Sommet *s1, Sommet *s2)
{
	ajoute_liste_sommet(&(s1->sommet_adj),s2);
	ajoute_liste_sommet(&(s2->sommet_adj),s1);
}
int adjacent(Sommet *s1,Sommet *s2)
{
	
	Cellule_som *tmp = s1->sommet_adj; 
	while (tmp){	
		if(tmp->sommet==s2)
			return 1;
		tmp=tmp->suiv;
	}
	return 0;
}

void init_graphe_zone(Graphe_zone **G, int dim)
{
	*G = (Graphe_zone *)malloc(sizeof(Graphe_zone));
	(*G)->som = (Cellule_som *)malloc(sizeof(Cellule_som));
	(*G)->som=NULL;
	int i, j;
	(*G)->mat=(Sommet ***)malloc(sizeof(Sommet **)*dim);
	for(i=0;i<dim;i++)
	{
		(*G)->mat[i]=(Sommet **)malloc(sizeof(Sommet *)*dim);
		for(j=0;j<dim;j++)
		{
			(*G)->mat[i][j]=(Sommet *)malloc(sizeof(Sommet));
			(*G)->mat[i][j]=NULL;
		}
	}
}

void cree_graphe_zone(Graphe_zone* G,int** M,int dim)
{
	int i,j,numero;
	numero=1;
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			if(G->mat[i][j]==NULL){
				int taille = 0;
				Liste *l = malloc (sizeof(Liste));
				init_liste(l);
				trouve_zone_imp(M,dim,i,j,&taille,l);
				Sommet* s=(Sommet *)malloc(sizeof(Sommet));
				s->nbcase_som=taille;
				s->cl=M[i][j];
				s->cases=*l;
				s->sommet_adj=(Cellule_som *) malloc(sizeof(Cellule_som));
				s->sommet_adj=NULL;
				s->num=numero++;
				s->marque = 2;
				s->distance=0;
				s->pere= NULL;
				Liste* tmp=l;
				G->mat[i][j]=s;
				G->nbsom=1+G->nbsom;
				ajoute_liste_sommet(&(G->som),s);
				while(*tmp){
					G->mat[(*tmp)->i][(*tmp)->j]=s;
					(*tmp)=(*tmp)->suiv;
				}
			}
		}
	}
	
	for(i=0;i<dim-1;i++){
		for(j=0;j<dim;j++){
			if(G->mat[i][j]!=G->mat[i+1][j] && !adjacent(G->mat[i][j],G->mat[i+1][j]))
				ajoute_voisin(G->mat[i][j],G->mat[i+1][j]);
			if(G->mat[j][i]!=G->mat[j][i+1] && !adjacent(G->mat[j][i],G->mat[j][i+1]))
				ajoute_voisin(G->mat[j][i],G->mat[j][i+1]);
		}	
	}
	G->mat[0][0]->marque=0;
	Cellule_som *tmp = G->mat[0][0]->sommet_adj;
	while(tmp!=NULL){
		tmp->sommet->marque=1;
		tmp = tmp->suiv;
	}
}

void affiche_graphe (Graphe_zone *G){
	Cellule_som *tmp=G->som;
	printf("nbsom %d\n",G->nbsom);
	while(tmp!=NULL){
		printf("Zone numero %d taille %d couleur %d marque %d \n", tmp->sommet->num,tmp->sommet->nbcase_som,tmp->sommet->cl,tmp->sommet->marque);
		Cellule_som *tmp2=tmp->sommet->sommet_adj;
		printf ("\tListe d'adj\n");
		while(tmp2!=NULL){
			printf("\t\tZone num %d taille %d couleur %d marque %d\n", tmp2->sommet->num,tmp2->sommet->nbcase_som,tmp2->sommet->cl,tmp2->sommet->marque);
			tmp2=tmp2->suiv;
		}
		tmp=tmp->suiv;
	}										
}
