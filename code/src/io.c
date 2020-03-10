/** 
 * \file io.c 
 * code pour les fonctions d'affichages
 * \author Maxime MAIRE
 */

#include "io.h"


/** 
 * \fn void affiche_trait(int c);
 * \param c est le nombre de colonne a affiché
 * \return Retourne vide, mais affiche des caracteres
 */
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}


/** 
 * \fn void affiche_ligne(int c, int* ligne);
 * \param c est le nombre de colonne a affiché
 * \param ligne est un pointeur sur entier
 * \return Retourne vide, mais affiche des caracteres
 */
void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (vieillissement==1)
			if (ligne[i] == 0 ) printf ("|   "); else printf ("| %d ",ligne[i]);		
		else
			if (ligne[i] == 0 ) printf ("|   "); else printf ("| 0 ");
	printf("|\n");
	return;
}


/** 
 * \fn void affiche_grille (grille g);
 * \param g est une grille
 * \return Retourne vide, mais affiche la grille g
 */
void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\033[100A");
	printf("\033[100B");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}


/** 
 * \fn void efface_grille (grille g);
 * \param g est une grille
 * \return Retourne vide, mais efface la grille g
 */
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}


/** 
 * \fn void debut_jeu (grille *g,grille *gc);
 * \param *g est un pointeur sur la grille g
 * \param *gc est un pointeur sur la grille gc
 * \return Retourne vide, mais efface la grille g
 */
void debut_jeu(grille *g, grille *gc){
	voisins_vivants = compte_voisins_vivants_non_cyclique;
	int a = 1;
	printf("Temps d'evolution : %d\n",a);
	char chaine[256];
	char c = getchar();
//	affiche_grille(*g);
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case'v':
			{
				if (vieillissement==0)
					vieillissement++;
				else
					vieillissement--; 
				break;
			}
			case 'c': // touche "c" pour activer/desactiver le voisinage cyclique
			{
				if (voisins_vivants==compte_voisins_vivants_non_cyclique)
					voisins_vivants = compte_voisins_vivants_cyclique;
				else
					voisins_vivants = compte_voisins_vivants_non_cyclique;
				break;
			}
			case 'n': // touche "n" pour charger une nouvelle grille
			{
				a = 1;
				libere_grille(g);
				libere_grille(gc);

				printf("Entrer le nom de la nouvelle grille: ");
				scanf("%s",chaine);
				init_grille_from_file(chaine,g);
				alloue_grille (g->nbl, g->nbc, gc);
				printf("Temps d'evolution : %d \n",a);
				affiche_grille(*g);
				break;
			}
			case '\n' : 
			{ // touche "entree" pour évoluer
				a++;
				if (voisins_vivants==compte_voisins_vivants_non_cyclique)
				{
					printf("Temps d'evolution : %d\nMode non cyclique\n",a);
				}
				else
				{
					printf("Temps d'evolution : %d\nMode cyclique\n",a);
				}
				if (vieillissement==1)
				{
					printf("mode vieillissement active");
				}
				else
				{
					printf("mode vieillissement desactive");
				}
				evolue(g,gc);
				efface_grille(*g);
				affiche_grille(*g);

			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}