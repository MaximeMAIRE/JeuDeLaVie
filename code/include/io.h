#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

#ifdef MODE_GRA
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#endif

/** 
 * \file io.h
 * header pour les fonctions d'affichage
 * \author Maxime MAIRE
 */

// affichage d'un trait horizontal
/** 
 * \fn void affiche_trait(int c);
 * \param c est le nombre de colonne a affiché
 * \return Retourne vide, mais affiche des caracteres
 */
void affiche_trait (int c);

// affichage d'une ligne de la grille
/** 
 * \fn void affiche_ligne(int c, int* ligne);
 * \param c est le nombre de colonne a affiché
 * \param ligne est un pointeur sur entier
 * \return Retourne vide, mais affiche des caracteres
 */
void affiche_ligne (int c, int* ligne);

// affichage d'une grille
/** 
 * \fn void affiche_grille (grille g);
 * \param g est une grille
 * \return Retourne vide, mais affiche la grille g
 */
void affiche_grille (grille g);

// effacement d'une grille
/** 
 * \fn void efface_grille (grille g);
 * \param g est une grille
 * \return Retourne vide, mais efface la grille g
 */
void efface_grille (grille g);

// debute le jeu
/** 
 * \fn void debut_jeu (grille *g,grille *gc);
 * \param *g est un pointeur sur la grille g
 * \param *gc est un pointeur sur la grille gc
 * \return Retourne vide, mais fait tourner le jeu
 */
void debut_jeu(grille *g, grille *gc);

#ifdef MODE_GRA

// affiche la fenetre graphique
/** 
 * \fn void paint(cairo_surface_t *surface, grille *g);
 * \param *surface est la zone alloué pour affiché la grille
 * \param *g est un pointeur sur la grille gc
 * \return Retourne vide, mais affiche une fenetre graphique
 */
void paint(cairo_surface_t *surface, grille *g);

// debute le jeu en version graphique
/** 
 * \fn void debut_jeu_cairo (grille *g, grille *gc);
 * \param *g est un pointeur sur la grille g
 * \param *gc est un pointeur sur la grille gc
 * \return Retourne vide, mais fait tourner le jeu graphiquement
 */
void debut_jeu_cairo(grille *g, grille *gc);
#endif

#endif