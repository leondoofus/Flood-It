#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "exo1.h"
#include "exo2.h"
#include "exo6.h"
 
int main(int argc,char**argv){

  int dim, nbcl, nivdif, graine;
  Grille *G;
  int i,j;
  int **M;

  clock_t
    temps_initial, /* Temps initial en micro-secondes */
    temps_final;   /* Temps final en micro-secondes */
  float
    temps_cpu;     /* Temps total en secondes */


  if(argc!=5){
    printf("usage: %s <dimension nb_de_couleurs niveau_difficulte graine>\n",argv[0]);
    return 1;
  }

  dim=atoi(argv[1]);


  nbcl=atoi(argv[2]);
  nivdif=atoi(argv[3]);
  graine=atoi(argv[4]);

  /* Generation de l'instance */

  M=(int **) malloc(sizeof(int*)*dim);
  for (i=0;i<dim;i++){
    M[i]=(int*) malloc(sizeof(int)*dim);
    if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
  }

  Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);

  /* Affichage de la grille */

  Grille_init(dim,nbcl, 500,&G);

  Grille_ouvre_fenetre(G);

  for (i=0;i<dim;i++)
    for (j=0;j<dim;j++){
      Grille_attribue_couleur_case(G,i,j,M[i][j]);
    }

  Grille_redessine_Grille();
 
  /* 
     A VOUS DE JOUER

  */
	int aff;
	printf ("Mode d'affichage:\n\t1 - Non\n\t2 - Oui\n");
	scanf ("%d", &aff);
	if (!(aff == 1 || aff == 2)){
		printf ("Choix incorrect\n");
		Grille_ferme_fenetre();
		Grille_free(&G);
		return 0;
	}
	aff--;
	//aff=1;
	int choix;
	printf ("Choix du mode:\n1 - Récursif\n2 - Impératif\n3 - Structure acyclique\n4 - Graphe - Max bordure\n5 - Graphe - Parcour en largeur\n");
	printf ("6 - Graphe - Plus court chemin + max bordure\n7 - Graphe - Plus loin sommet + max bordure\n8 - Graphe - Coins + max bordure\n");
	scanf ("%d", &choix);
	if (choix == 1){
		temps_initial = clock();
		Liste *l = malloc (sizeof(Liste));
		init_liste(l);
		int changementCouleur;
		//FILE *f1=fopen ("RecursifSequenceAleatoire.txt","a");
		changementCouleur=sequence_aleatoire_rec(M,G,dim,nbcl,1,0,0, aff);
		temps_final = clock();
		temps_cpu = (double)(temps_final - temps_initial)/CLOCKS_PER_SEC;	
		printf("Dimension : %d\n%d couleur(s)\nTemps d'execution : %f\n%d fois de changement\n",dim,nbcl,temps_cpu,changementCouleur);
		//fprintf(f1,"%d\t%f\t%d\t%d\n",dim,temps_cpu,changementCouleur,nbcl);
		//fclose(f1);
	} else if (choix == 2){
		temps_initial = clock();
		Liste *l = malloc (sizeof(Liste));
		init_liste(l);
		int changementCouleur;
		//FILE *f1=fopen ("ImperatifSequenceAleatoire.txt","a");
		changementCouleur=sequence_aleatoire_rec(M,G,dim,nbcl,1,1,0, aff);
		temps_final = clock();
		temps_cpu = (double)(temps_final - temps_initial)/CLOCKS_PER_SEC;	
		printf("Dimension : %d\n%d couleur(s)\nTemps d'execution : %f\n%d fois de changement\n",dim,nbcl,temps_cpu,changementCouleur);
		//fprintf(f1,"%d\t%f\t%d\t\%d\n",dim,temps_cpu,changementCouleur, nbcl);
		//fclose(f1);
	} else if (choix == 3){
		temps_initial = clock();
		S_Zsg *Zone;
		init_Zsg (&Zone,dim, nbcl);
		int changementCouleur;
		//FILE *f1=fopen ("IteratifSequenceAleatoire.txt","a");
		changementCouleur=strequence_aleatoire_rapide(M,Zone,G, aff);
		temps_final = clock();	
		temps_cpu = (double)(temps_final - temps_initial)/CLOCKS_PER_SEC;
		printf("Dimension : %d\n%d couleur(s)\nTemps d'execution : %f\n%d fois de changement\n",dim,nbcl,temps_cpu,changementCouleur);
		//fprintf(f1,"%d\t%f\t%d\t\%d\n",dim,temps_cpu,changementCouleur, nbcl);
		//fclose(f1);
	} else if (choix == 4){
		temps_initial = clock();
		Graphe_zone *Graph = malloc(sizeof(Graphe_zone));
		init_graphe_zone (&Graph, dim);
		cree_graphe_zone(Graph,M,dim);
		//affiche_graphe(Graph);
		int changementCouleur;
		//FILE *f1=fopen ("MaxBordure.txt","a");
		//remplit_distance_largeur (Graph, Graph->mat[0][0], Graph->nbsom);
		//plus_court_chemin_graphe_zone(Graph);
		//affiche_graphe_plus_court(Graph);
		changementCouleur = sequence_graph_max_bordure(G,Graph,nbcl,aff);
		temps_final = clock();	
		temps_cpu = (double)(temps_final - temps_initial)/CLOCKS_PER_SEC;
		printf("Dimension : %d\n%d couleur(s)\nTemps d'execution : %f\n%d fois de changement\n",dim,nbcl,temps_cpu,changementCouleur);
		//fprintf(f1,"%d\t%f\t%d\t\%d\n",dim,temps_cpu,changementCouleur, nbcl);
		//fclose(f1);
	} else if (choix == 5){
		temps_initial = clock();
		Graphe_zone *Graph = malloc(sizeof(Graphe_zone));
		init_graphe_zone (&Graph, dim);
		cree_graphe_zone(Graph,M,dim);
		int changementCouleur;
		//FILE *f1=fopen ("Largeur.txt","a");
		changementCouleur=sequence_largeur(G,Graph,Graph->nbsom, aff);
		temps_final = clock();	
		temps_cpu = (double)(temps_final - temps_initial)/CLOCKS_PER_SEC;
		printf("Dimension : %d\n%d couleur(s)\nTemps d'execution : %f\n%d fois de changement\n",dim,nbcl,temps_cpu,changementCouleur);
		//fprintf(f1,"%d\t%f\t%d\t\%d\n",dim,temps_cpu,changementCouleur, nbcl);
		//fclose(f1);
	} else if (choix == 6){
		temps_initial = clock();
		Graphe_zone *Graph = malloc(sizeof(Graphe_zone));
		init_graphe_zone (&Graph, dim);
		cree_graphe_zone(Graph,M,dim);
		//affiche_graphe(Graph);
		int changementCouleur;
		//FILE *f1=fopen ("PlusCourtChemin.txt","a");
		remplit_distance_largeur (Graph, Graph->mat[0][0], Graph->nbsom);
		//plus_court_chemin_graphe_zone(Graph);
		//affiche_graphe_plus_court(Graph);
		changementCouleur = sequence_plus_court_chemin (G, Graph, Graph->mat[dim-1][dim-1],aff);
		changementCouleur += sequence_graph_max_bordure(G,Graph,nbcl,aff);
		temps_final = clock();	
		temps_cpu = (double)(temps_final - temps_initial)/CLOCKS_PER_SEC;
		printf("Dimension : %d\n%d couleur(s)\nTemps d'execution : %f\n%d fois de changement\n",dim,nbcl,temps_cpu,changementCouleur);
		//fprintf(f1,"%d\t%f\t%d\t\%d\n",dim,temps_cpu,changementCouleur, nbcl);
		//fclose(f1);
	} else if (choix == 7){
		temps_initial = clock();
		Graphe_zone *Graph = malloc(sizeof(Graphe_zone));
		init_graphe_zone (&Graph, dim);
		cree_graphe_zone(Graph,M,dim);
		int changementCouleur;
		//FILE *f1=fopen ("PlusLoinSommet.txt","a");
		changementCouleur=sequence_plus (G, Graph, Graph->nbsom, aff);
		temps_final = clock();	
		temps_cpu = (double)(temps_final - temps_initial)/CLOCKS_PER_SEC;
		printf("Dimension : %d\n%d couleur(s)\nTemps d'execution : %f\n%d fois de changement\n",dim,nbcl,temps_cpu,changementCouleur);
		//fprintf(f1,"%d\t%f\t%d\t\%d\n",dim,temps_cpu,changementCouleur, nbcl);
		//fclose(f1);
	} else if (choix == 8){
		temps_initial = clock();
		Graphe_zone *Graph = malloc(sizeof(Graphe_zone));
		init_graphe_zone (&Graph, dim);
		cree_graphe_zone(Graph,M,dim);
		int changementCouleur;
		//FILE *f1=fopen ("Coins.txt","a");
		changementCouleur=sequence_coins_max_bordure(G,Graph,Graph->nbsom,dim,nbcl,aff);
		temps_final = clock();	
		temps_cpu = (double)(temps_final - temps_initial)/CLOCKS_PER_SEC;
		printf("Dimension : %d\n%d couleur(s)\nTemps d'execution : %f\n%d fois de changement\n",dim,nbcl,temps_cpu,changementCouleur);
		//fprintf(f1,"%d\t%f\t%d\t\%d\n",dim,temps_cpu,changementCouleur, nbcl);
		//fclose(f1);

	} else {
		printf ("Choix incorrect\n");
		Grille_ferme_fenetre();
		Grille_free(&G);
		return 1;
	}
	printf("Fin\n");
	
  //Grille_attente_touche();
 
  Grille_ferme_fenetre();

  Grille_free(&G);

  return 0;
}
