#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/** 
 * \file jeu.h
 * header pour les fonctions d'evolution
 * \author Maxime MAIRE
 */

// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
static inline int modulo(int i, int m) {return (i+m)%m;}

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.
 /** 
 * \fn int compte_voisins_vivants_non_cyclique(int i, int j, grille g);
 * \param i est un entier representant la ieme ligne de la grille g
 * \param j est un entier representant la jeme colonne de la grille g
 * \param g est une grille
 * \return Retourne un entier, representant le nombre de voisin (en mode non cyclique) d'une case de ligne i et de colonne j d'une grille g
 */
int compte_voisins_vivants_non_cyclique (int i, int j, grille g);

// fait évoluer la grille g d'un pas de temps
/** 
 * \fn void evolue (grille *g, grille *gc);
 * \param *g est un pointeur sur la grille g
 * \param *gc est un pointeur sur la grille gc
 * \return Retourne vide, mais evolue la grille passé en argument
 */
void evolue (grille *g, grille *gc);

// pointeur de fonction
int (*voisins_vivants) (int,int,grille);

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont non cycliques
/** 
 * \fn int compte_voisins_vivants_cyclique(int i, int j, grille g);
 * \param i est un entier representant la ieme ligne de la grille g
 * \param j est un entier representant la jeme colonne de la grille g
 * \param g est une grille
 * \return Retourne un entier, representant le nombre de voisin (en mode cyclique) d'une case de ligne i et de colonne j d'une grille g
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g);


#endif