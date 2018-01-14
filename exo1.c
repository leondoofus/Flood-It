#include "exo1.h"
int dans_la_liste (Liste L, int i, int j){
	while (L){
		if ((L->i == i) && (L->j == j)){
			return 1;
		}
		L = L->suiv;
	}
	return 0;
}

void affiche_liste (Liste L){
	while (L){
		printf ("i %d j %d\n", L->i, L->j);
		L = L->suiv;
	}
}

void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, Liste *L)
{
	if (!dans_la_liste (*L, i, j)){
		(*taille)++;
		ajoute_en_tete(L,i,j);
	}
	if(j+1<dim && M[i][j+1]==M[i][j] && !dans_la_liste(*L, i, j+1)){
		trouve_zone_rec(M,dim,i,j+1,taille,L);	
	}
	if(j-1>=0 && M[i][j-1]==M[i][j] && !dans_la_liste(*L, i, j-1)){
		trouve_zone_rec(M,dim,i,j-1,taille,L);	
	}
	if(i+1<dim && M[i+1][j]==M[i][j] && !dans_la_liste(*L, i+1, j)){
		trouve_zone_rec(M,dim,i+1,j,taille,L);
	}
	if(i-1>=0 && M[i-1][j]==M[i][j] && !dans_la_liste(*L, i-1, j)){
		trouve_zone_rec(M,dim,i-1,j,taille,L);	
	}
}

int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff, int mode, int compteur, int modeaff)
{
	int couleurAleatoire = rand()%(G->nbcl);
	while (couleurAleatoire==M[0][0]){
		couleurAleatoire = rand()%(G->nbcl);
	}
	
	int t=0;
	Liste *l = malloc (sizeof(Liste));
	init_liste(l);
	if (mode)
		trouve_zone_imp(M,dim,0,0,&t,l);
	else
		trouve_zone_rec(M,dim,0,0,&t,l);
	
	int t1=t;
	Liste tmp = *l;
	while(tmp){
		M[tmp->i][tmp->j]=couleurAleatoire;
		if (modeaff) Grille_attribue_couleur_case(G,tmp->i,tmp->j,M[tmp->i][tmp->j]);
		tmp=tmp->suiv;
	}

	if (mode)
		trouve_zone_imp(M,dim,0,0,&t,l);
	else
		trouve_zone_rec(M,dim,0,0,&t,l);
		
	if (t1 != t) aff = 1;
	if(aff && t != dim*dim){
		if (modeaff) Grille_redessine_Grille();
	}
	if (t == dim*dim){
		return compteur;
	} else {
		//Liberation de la memoire utilise par la liste l
		tmp = *l;
		Liste tmp2;
		while(tmp){
			tmp2=tmp->suiv;
			free(tmp);
			tmp=tmp2;
		}
		return sequence_aleatoire_rec(M,G,dim,nbcl,aff,mode,compteur+1,modeaff);
	}
}

void trouve_zone_imp(int **M, int dim, int i, int j, int *taille, Liste *L)
{
	if (!dans_la_liste (*L, i, j)){
		(*taille)++;
		ajoute_en_tete(L,i,j);
	}
	Liste pile = malloc(sizeof(Elnt_liste));;
	init_liste(&pile);
	Liste tmp = *L;
	
	//Grille d'appartenance (char pour utiliser seulement 1 octet)
	char** App =(char**)malloc(sizeof(char*)*dim);
	int k,kk;
	for(k=0;k<dim;k++)
	{
		App[k]=(char*)malloc(sizeof(char)*dim);
		for(kk=0;kk<dim;kk++)
		{
			App[k][kk]='0';
		}
	}
	
	while (tmp){
		App[tmp->i][tmp->j]='1';
		if (!((tmp->i-1>=0 && M[tmp->i-1][tmp->j] == M[i][j])&&(tmp->i+1<dim && M[tmp->i+1][tmp->j] == M[i][j])
		&&(tmp->j-1>=0 && M[tmp->i][tmp->j-1] == M[i][j])&&(tmp->j+1<dim && M[tmp->i][tmp->j+1] == M[i][j]))){
			ajoute_en_tete(&pile,tmp->i, tmp->j);
		}
		tmp = tmp->suiv;
	}
	while (pile){
		int tmp1,tmp2;
		enleve_en_tete(&pile, &tmp1, &tmp2);
		if (tmp1+1<dim && M[tmp1+1][tmp2] == M[i][j]){
			if (App[tmp1+1][tmp2]=='0'){
				ajoute_en_tete (&pile, tmp1+1, tmp2);
				ajoute_en_tete (L, tmp1+1, tmp2);
				App[tmp1+1][tmp2]='1';
				(*taille)++;
			}
		}
		if (tmp2+1<dim && M[tmp1][tmp2+1] == M[i][j]){
			if (App[tmp1][tmp2+1]=='0'){
				ajoute_en_tete (&pile, tmp1, tmp2+1);
				ajoute_en_tete (L, tmp1, tmp2+1);
				App[tmp1][tmp2+1]='1';
				(*taille)++;
			}
		}
		if (tmp1-1>=0 && M[tmp1-1][tmp2] == M[i][j]){
			if (App[tmp1-1][tmp2]=='0'){
				ajoute_en_tete (&pile, tmp1-1, tmp2);
				ajoute_en_tete (L, tmp1-1, tmp2);
				App[tmp1-1][tmp2]=1;
				(*taille)++;
			}
		}
		if (tmp2-1>=0 && M[tmp1][tmp2-1] == M[i][j]){
			if (App[tmp1][tmp2-1]=='0'){
				ajoute_en_tete (&pile, tmp1, tmp2-1);
				ajoute_en_tete (L, tmp1, tmp2-1);
				App[tmp1][tmp2-1]='1';
				(*taille)++;
			}
		}
	}
	for(k=0;k<dim;k++){
		free(App[k]);
	}
	free(App);
}


