#include "grille.h"
#include "io.h"


/** 
 * \file grille.c
 * code pour les fonctions sur les grilles
 * \author Maxime MAIRE
 */


/** 
 * \fn void alloue_grille(int l, int c, grille *g);
 * \param l est un entier representant le nombre de ligne a alloue pour la grille g
 * \param c est un entier representant le nombre de colonne a alloue pour la grille g
 * \param *g est un pointeur sur une grille
 * \return Retourne vide, mais alloue une grille de ligne l et de colonne c
 */
void alloue_grille (int l, int c, grille* g)
{
	g->nbl = l;
	g->nbc = c;

	g->cellules = malloc((g->nbl) * sizeof(int*));
	if (g->cellules == NULL)
	{
		perror("malloc");
		exit(1);
	}
	for (int i =0; i<l; i++)
		{
		g->cellules[i] = malloc((g->nbc)*sizeof (int));
		if (g-> cellules[i] == NULL)
		{
			perror("malloc");
			exit(1);
		}
		for (int j=0 ; j<c ; j++)
		{
			set_morte(i,j,*g);
		}
	}
}


/** 
 * \fn void libere_grille(grille *g);
 * \param *g est un pointeur sur une grille
 * \return Retourne vide, mais libere la grille g
 */
void libere_grille(grille* g)
{
	for (int i=0;i<g->nbl;i++)
	{
		free(g->cellules[i]);
	}
	free(g->cellules);	
	return;
}


/** 
 * \fn void init_grille_from_file(char * filename, grille *g);
 * \param *filename est un tableau de charactere permettant de chercher un fichier a scanf
 * \param *g est un pointeur sur une grille
 * \return Retourne vide, mais alloue et initalise la grille g à partir d'un fichier
 */
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	
	fclose (pfile);
	return;
}

/** 
 * \fn void copie_grille(grille gs, grille gd);
 * \param gs est une grille 
 * \param gd est une grille
 * \return Retourne vide, mais recopie la grille gs dans la grille gd
 */
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}
