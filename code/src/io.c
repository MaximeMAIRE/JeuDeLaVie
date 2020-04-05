/** 
 * \file io.c 
 * code pour les fonctions d'affichages
 * \author Maxime MAIRE
 */

#include "io.h"

#define SIZEX 800
#define SIZEY 850
#include <stdio.h>
#include <stdlib.h>
#ifdef MODE_GRA
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#endif

int vieillissement = 0;
static int evol = 1;
int periode = 0;

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}


void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i)
	{
		if (vieillissement==1)
		{
			if (ligne[i]==0) printf("|   ");
			else if(ligne[i]==-1) printf("|%d ",ligne[i]);
			else printf ("| %d ",ligne[i]);		
		}
		else
		{	
			if (ligne[i]==0) printf("|   ");
			else if(ligne[i]==-1) printf("|%d ",ligne[i]); 
			else printf("| 0 ");
		}
	}
	printf("|\n");
	return;
}


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


void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}


void debut_jeu(grille *g, grille *gc){
	voisins_vivants = compte_voisins_vivants_non_cyclique;
	printf("Temps d'evolution : %d\n",evol);
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
				evol = 1;
				libere_grille(g);
				libere_grille(gc);

				printf("Entrer le nom de la nouvelle grille: ");
				scanf("%s",chaine);
				init_grille_from_file(chaine,g);
				alloue_grille (g->nbl, g->nbc, gc);
				printf("Temps d'evolution : %d \n",evol);
				affiche_grille(*g);
				break;
			}
			case '\n' : 
			{ // touche "entree" pour évoluer
				evol++;
				if (voisins_vivants==compte_voisins_vivants_non_cyclique)
				{
					printf("Temps d'evolution : %d\nMode non cyclique\n",evol);
				}
				else
				{
					printf("Temps d'evolution : %d\nMode cyclique\n",evol);
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

#ifdef MODE_GRA
static void do_drawing(cairo_t *cr,grille g)
{
	char t_evol[100]; 
	char t_cycl[50];
	char t_v[50];
	char t_periode[100];
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0); 

	cairo_select_font_face(cr, "UTF-8",
    CAIRO_FONT_SLANT_NORMAL,
    CAIRO_FONT_WEIGHT_BOLD);

	cairo_set_font_size(cr, 13);
	sprintf(t_evol,"Temps d'evolution : %d",evol);
	cairo_move_to(cr, 20, 30);
	cairo_show_text(cr, t_evol);
	sprintf(t_cycl, "Mode %s cyclique",(voisins_vivants!=compte_voisins_vivants_non_cyclique)?"":"non");
	cairo_move_to(cr, 200, 30);
	cairo_show_text(cr, t_cycl);
	sprintf(t_v,"Vieillissement : %s",(vieillissement)?"oui !" : "non");
	cairo_move_to(cr, 350, 30);
	cairo_show_text(cr, t_v);
	if(periode>=2)
	{
		cairo_move_to(cr, 20, 70);
		sprintf(t_periode, "Durée de la période : %d",periode);
		cairo_show_text(cr, t_periode);
		periode =0;
	}
	else if (periode==1)
	{
		cairo_move_to(cr, 20, 70);
		cairo_show_text(cr, "Il n'y a pas d'oscillation");
		periode=0;
	}
	else if (periode==-1)
	{
		cairo_move_to(cr, 20, 70);
		cairo_show_text(cr, "Enlever le mode vieillissement pour pouvoir avoir la période si il y en a une");
		periode=0;
	}
	
}

void paint(cairo_surface_t *surface,grille *g)
{
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);

	// background
	cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
	cairo_paint(cr);
	

	// filled rectangle
	cairo_rectangle(cr,0,0,SIZEX,100);
	cairo_set_source_rgb (cr, 0.5, 0.5, 0.5);
	cairo_fill(cr);
	do_drawing(cr,*g);

	for (int i=0;i<g->nbl;i++)
	{

		for(int j=0; j<g->nbc;j++)
		{
			int a,b,x,t;
			if(g->nbl >= g->nbc)
			{
				x = 60+(g->nbl-1)*20;
				x = SIZEY-x-100;
				t = x/g->nbl;
				a = 30+t*j+20*j;
				b = 30+t*i+20*i+100;
			}
			else
			{
				x = 60+(g->nbc-1)*20;
				x = SIZEX-x;
				t = x/g->nbc;
				a = 30+t*j+20*j;
				b = 30+t*i+20*i+100;
			}
			
			if (vieillissement==0)
			{
				cairo_rectangle(cr,a,b,t,t);
				if (est_vivante(i,j,*g))
				{
					cairo_set_source_rgb (cr, 0.0, 0.9, 0.0);
					cairo_fill(cr);
				}
				cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
				cairo_fill(cr);
			}
			else
			{
				cairo_rectangle(cr,a,b,t,t);
				if (est_vivante(i,j,*g))
				{
					float age = g->cellules[i][j];
					age = age /10;
					cairo_set_source_rgb (cr, 0.0, 1-age, 0.0);
					cairo_fill(cr);
				}
				else
				{
					cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
					cairo_fill(cr);
				}
			}
		}
	}
	cairo_destroy(cr); // destroy cairo mask
}

void debut_jeu_cairo(grille *g,grille *gc)
{
	voisins_vivants = compte_voisins_vivants_non_cyclique;

	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
	
	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "jeu de la vie");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	// run the event loop
	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) {
			paint(cs, g);
		} 
		else if(e.type==ButtonPress)
		{
			if(e.xbutton.button==3)
			{
				break;
			}
			if(e.xbutton.button==1)
			{
				evolue(g,gc);
				evol++;
				paint(cs,g);
			}
		}
		else if (e.type==KeyPress) 
		{
        	if (e.xkey.keycode==XKeysymToKeycode(dpy,'c')) 
			{
				if (voisins_vivants==compte_voisins_vivants_non_cyclique)
					voisins_vivants = compte_voisins_vivants_cyclique;
				else
					voisins_vivants = compte_voisins_vivants_non_cyclique;
				paint(cs,g);
			}
			if(e.xkey.keycode==XKeysymToKeycode(dpy,'v'))
			{
				if (vieillissement==0)
					vieillissement++;
				else
					vieillissement--; 
				paint(cs,g);
			} 
			if (e.xkey.keycode==XKeysymToKeycode(dpy,'n'))
			{
				char grille[100];
				printf("chemin de la nouvelle grille a chargée : ");
				scanf("%s",grille);
				libere_grille(g);
				libere_grille(gc);
				init_grille_from_file(grille, g);
				alloue_grille(g->nbl, g->nbc, gc);
				cairo_xlib_surface_set_size(cs,SIZEX,SIZEY);
				paint(cs,g);

			}
			if (e.xkey.keycode==XKeysymToKeycode(dpy,'o'))
			{
				if(vieillissement==0)
				{
					int sortie = 1;
					grille grille_test;
					alloue_grille(g->nbl,g->nbc,&grille_test);
					copie_grille(*g,grille_test);


					evolue(&grille_test,gc);
					periode++;
				
					while((!test_grille_eg(*g,grille_test)) && (sortie))
					{
						grille grille_test_2;
						alloue_grille(grille_test.nbl,grille_test.nbc,&grille_test_2);
						copie_grille(grille_test,grille_test_2);

						evolue(&grille_test,gc);
						periode++;

						if(test_grille_eg(grille_test,grille_test_2))
						{	sortie = 0;
							periode = 1;
						}
						libere_grille(&grille_test_2);
					}
					paint(cs,g);
					libere_grille(&grille_test);
				}
				else
				{
					periode =-1;
					paint(cs,g);
				}
			}
		}
	}

	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display

	return;
}
#endif