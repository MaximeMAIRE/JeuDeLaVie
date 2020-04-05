#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

#ifdef MODE_GRA
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#endif

int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	
	
	#ifdef MODE_GRA
	debut_jeu_cairo(&g,&gc);
	#else
	affiche_grille(g);
	debut_jeu(&g, &gc);
	#endif
	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}