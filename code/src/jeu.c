#include "jeu.h"
#include "io.h"
#include "grille.h"
/** 
 * \file jeu.c 
 * code pour les fonctions d'evolutions
 * \author Maxime MAIRE
 */

/** 
 * \fn int compte_voisins_vivants_cyclique(int i, int j, grille g);
 * \param i est un entier representant la ieme ligne de la grille g
 * \param j est un entier representant la jeme colonne de la grille g
 * \param g est une grille
 * \return Retourne un entier, representant le nombre de voisin (en mode cyclique) d'une case de ligne i et de colonne j d'une grille g
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

/** 
 * \fn int compte_voisins_vivants_non_cyclique(int i, int j, grille g);
 * \param i est un entier representant la ieme ligne de la grille g
 * \param j est un entier representant la jeme colonne de la grille g
 * \param g est une grille
 * \return Retourne un entier, representant le nombre de voisin (en mode non cyclique) d'une case de ligne i et de colonne j d'une grille g
 */
int compte_voisins_vivants_non_cyclique (int i, int j, grille g){
	int vc = 0, l=g.nbl-1, c = g.nbc-1;

	if ((i!=0) && (i!=l) && (j!=0) && (j!=c))
	{
		vc = compte_voisins_vivants_cyclique(i,j,g);
	}

	if (i == 0)
	{
		vc+= est_vivante(i+1,j,g);
		if (j == 0)
		{
			vc+= est_vivante(i,j+1,g);
			vc+= est_vivante(i+1,j+1,g);
		}
		else if (j==c)
		{
			vc+= est_vivante(i,j-1,g);
			vc+= est_vivante(i+1,j-1,g);
		}
		else
		{
			vc+= est_vivante(i,j+1,g);
			vc+= est_vivante(i+1,j+1,g);
			vc+= est_vivante(i,j-1,g);
			vc+= est_vivante(i+1,j-1,g);
		}
	}
	else if (i==l)
	{
		vc+= est_vivante(i-1,j,g);
		if (j == 0)
		{
			vc+= est_vivante(i,j+1,g);
			vc+= est_vivante(i-1,j+1,g);
		}
		else if (j==c)
		{
			vc+= est_vivante(i,j-1,g);
			vc+= est_vivante(i-1,j-1,g);
		}
		else
		{
			vc+= est_vivante(i,j+1,g);
			vc+= est_vivante(i-1,j+1,g);
			vc+= est_vivante(i,j-1,g);
			vc+= est_vivante(i-1,j-1,g);
		}

	}
	else if (j==0)
	{
		vc+= est_vivante(i+1,j+1,g);
		vc+= est_vivante(i,j+1,g);
		vc+= est_vivante(i-1,j+1,g);
		vc+= est_vivante(i-1,j,g);
		vc+= est_vivante(i+1,j,g);
	}
	else if (j==c)
	{
		vc+= est_vivante(i+1,j-1,g);
		vc+= est_vivante(i,j-1,g);
		vc+= est_vivante(i-1,j-1,g);
		vc+= est_vivante(i-1,j,g);
		vc+= est_vivante(i+1,j,g);
	}

	return vc;
}


/** 
 * \fn void evolue (grille *g, grille *gc);
 * \param *g est un pointeur sur la grille g
 * \param *gc est un pointeur sur la grille gc
 * \return Retourne vide, mais evolue la grille passé en argument
 */
void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = voisins_vivants (i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
				else
				{
					if (vieillissement==1)
					{
						g->cellules[i][j]++;
					}
					else
					{
						g->cellules[i][j]=1;
					}
				}
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
			if (g->cellules[i][j]==9)
			{
				set_morte(i,j,*g);
			}
		}
	}
	return;
}
