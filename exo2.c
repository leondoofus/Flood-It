#include <stdio.h>
#include <stdlib.h>
#include "exo2.h"

void init_Zsg(S_Zsg **s,int dim,int nbcl)
{
	*s=(S_Zsg *)malloc(sizeof(S_Zsg));
	(*s)->dim=dim;
	(*s)->nbcl=nbcl;
	int i,j;
	init_liste(&(*s)->Lzsg);
	(*s)->B=malloc(sizeof(Liste *)*nbcl);
	(*s)->App=(int **)(malloc (sizeof(int*)*dim));
	for(i=0;i<dim;i++)
	{
		
		(*s)->App[i]=(int *)(malloc(sizeof(int)*dim));
		for(j=0;j<dim;j++)
		{
			(*s)->App[i][j]=-2;
		}
	}
}
void ajoute_Zsg(S_Zsg *s,int i,int j)
{
	ajoute_en_tete(&s->Lzsg,i,j);
	s->App[i][j]=-1;
}

void ajoute_Bordure(S_Zsg *s,int cl,int i,int j)
{
	ajoute_en_tete(&(s->B[cl]),i,j);
	s->App[i][j]=cl;
}

int appartient_Bordure (S_Zsg* s,int i, int j,int cl)
{
	return s->App[i][j]==cl;
}

int appartient_Zsg(S_Zsg *s,int i,int j)
{
	return s->App[i][j]==-1;
}

int agrandit_Zone(int **M, S_Zsg *Z, int cl, int k, int l)
{
	int dim = Z->dim;
	int nbAjout=0;
	if (!dans_la_liste (Z->Lzsg, k, l)){
		ajoute_en_tete(&(Z->Lzsg),k,l);
		Z->App[k][l]=-1;
		nbAjout++;
	}
	int u, v;
	for (u =k ; u<dim; u ++){
		for (v = l; v<dim; v++){
			if ((u-1>=0 && appartient_Zsg(Z,u-1,v))  || (v-1>=0 && appartient_Zsg(Z,u,v-1))
			||(u+1<dim && appartient_Zsg(Z,u+1,v)) || (v+1<dim && appartient_Zsg(Z,u,v+1))){
				if (M[u][v] == cl){
					if (Z->App[u][v] != -1){
						ajoute_en_tete(&(Z->Lzsg),u,v);
						Z->App[u][v]=-1;
						nbAjout++;
					}
				} else if(M[u][v] != cl && Z->App[u][v]!= cl){
					ajoute_Bordure(Z,cl,u,v);
				}
			}
		}
	}
	return nbAjout;
}

int strequence_aleatoire_rapide(int **M, S_Zsg *Zone, Grille *G, int aff)
{
	if (test_plein(Zone->dim,Zone->App)) return 0;
	int i;
	for (i=0; i<Zone->nbcl; i++){
		init_liste(&(Zone->B[i]));
	}
	agrandit_Zone(M,Zone,M[0][0],0,0);
	int cl = rand()%(G->nbcl);
	while (cl==M[0][0]){
		cl = rand()%(G->nbcl);
	}
	Liste tmp=Zone->Lzsg;
	while (tmp){
		M[tmp->i][tmp->j]=cl;
		if (aff) Grille_attribue_couleur_case(G,tmp->i,tmp->j,M[tmp->i][tmp->j]);			
		tmp=tmp->suiv;
	}
	if (aff) Grille_redessine_Grille();
	Liste tmpB=Zone->B[M[0][0]];
	while(tmpB)	{	
		int a,b;
		enleve_en_tete(&tmpB, &a, &b);
		agrandit_Zone(M,Zone,cl,a,b);
	}
	return 1 + strequence_aleatoire_rapide(M, Zone, G, aff);
}

int test_plein(int dim,int **App)
{
	int i,j;
	for (i=dim-1;i>=0;i--){
		for (j=dim-1;j>0;j--){
			if(App[i][j]!=-1){
				return 0;
			}
		}
	}
	return 1;
}

void affiche_Zone (S_Zsg *s){
	printf ("Dimension = %d\n", s->dim);
	printf ("Couleur = %d\n", s->nbcl);
	int i, j;
	for (j=0; j<s->dim; j++){
		for (i=0; i<s->dim; i++){
			if (s->App[i][j] >= 0) printf (" ");
			printf ("%d | ", s->App[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
