#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/** 
 * \file grille.h
 * header pour les fonctions sur les grilles
 * \author Maxime MAIRE
 */

// structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
/** 
 * \fn void alloue_grille(int l, int c, grille *g);
 * \param l est un entier representant le nombre de ligne a alloue pour la grille g
 * \param c est un entier representant le nombre de colonne a alloue pour la grille g
 * \param *g est un pointeur sur une grille
 * \return Retourne vide, mais alloue une grille de ligne l et de colonne c
 */
void alloue_grille (int l, int c, grille* g);

// libère une grille
/** 
 * \fn void libere_grille(grille *g);
 * \param *g est un pointeur sur une grille
 * \return Retourne vide, mais libere la grille g
 */
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
/** 
 * \fn void init_grille_from_file(char * filename, grille *g);
 * \param *filename est un tableau de charactere permettant de chercher un fichier a scanf
 * \param *g est un pointeur sur une grille
 * \return Retourne vide, mais alloue et initalise la grille g à partir d'un fichier
 */
void init_grille_from_file (char * filename, grille* g);

// rend vivante la cellule (i,j) de la grille g
/** 
 * \fn void set_vivante(int i, int j, grille g);
 * \param i est un entier
 * \param j est un entier
 * \param g est une grille
 * \return Retourne vide, mais met dans la case de linge i et de colonne j la valeur 1
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

// rend morte la cellule (i,j) de la grille g
/** 
 * \fn void set_morte(int i, int j, grille g);
 * \param i est un entier
 * \param j est un entier
 * \param g est une grille
 * \return Retourne vide, mais met dans la case de linge i et de colonne j la valeur 0
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

// teste si la cellule (i,j) de la grille g est vivante
/** 
 * \fn int est_vivante(int i, int j, grille g);
 * \param i est un entier
 * \param j est un entier
 * \param g est une grille
 * \return Retourne la valeur de la cellules de ligne i et de colonne j si elle est supérieur a 1, sinon elle renvoie 0
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] >= 1;}

/** 
 * \fn void set_non_viable(int i, int j, grille g);
 * \param i est un entier
 * \param j est un entier
 * \param g est une grille
 * \return Retourne vide, mais met dans la case de linge i et de colonne j la valeur -1
 */
static inline void set_non_viable(int i, int j, grille g){g.cellules[i][j] = -1;}

/** 
 * \fn int est_viable(int i, int j, grille g);
 * \param i est un entier
 * \param j est un entier
 * \param g est une grille
 * \return Retourne 0 si cellules ligne i et de colonne j == -1 sinon -1
 */
static inline int est_viable(int i, int j, grille g){return g.cellules[i][j] != -1;}

// recopie gs dans gd (sans allocation)
/** 
 * \fn void copie_grille(grille gs, grille gd);
 * \param gs est une grille 
 * \param gd est une grille
 * \return Retourne vide, mais recopie la grille gs dans la grille gd
 */
void copie_grille (grille gs, grille gd);

int vieillissement;

#endif
