/**
 * \file gui.c
 * \brief Code graphique du jeu de la Vie
 */

#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <errno.h>
#include <string.h>
#include "../hdr/gui.h"
#include "../hdr/grille.h"
#include "../hdr/jeu.h"

/**
 * \def SIZEX 
 * \brief la taille en pixels de la largeur
 * 
 * \def SIZEY
 * \brief la taille en pixels de la largeur
 */
#define SIZEX 700
#define SIZEY 600

//AFFICHAGE
void paint(cairo_surface_t *surface, grille g, int l, int c, int age, int cycle)
{
	// masque Cairo
	cairo_t *cr;
	cr=cairo_create(surface);

	// arrière-plan (en bleu de minuit...)
	cairo_set_source_rgb (cr, 0.098, 0.098, 0.4392);
	cairo_paint(cr);

	//Affichage du texte (la police de caractère est à changer selon celles installées)
	cairo_text_extents_t te;
	cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
	cairo_select_font_face (cr, "CoStar Brown",
		CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size (cr, 16);
	cairo_text_extents (cr, "Life: le jeu de la Vie", &te);
	cairo_move_to (cr, 50.5-te.x_bearing,
		25);
	cairo_show_text (cr, "Life: le jeu de la Vie");

	//Selon l'indicateur de vieillissement...
	switch(age){
		case 1:
			cairo_text_extents (cr, "Vieillissement", &te);
			cairo_move_to (cr, 50.5-te.x_bearing,
				SIZEY-25);
			cairo_show_text (cr, "Vieillissement");
			break;
		case 0:
			cairo_text_extents (cr, "Vies infinies", &te);
			cairo_move_to (cr, 50.5-te.x_bearing,
				SIZEY-25);
			cairo_show_text (cr, "Vies infinies");
			break;
		default:break;
	}

	//... et/ou celui du mode cyclique
	switch(cycle){
		case 1:
			cairo_text_extents (cr, "Mode cyclique", &te);
			cairo_move_to (cr, 250.5-te.x_bearing,
				SIZEY-25);
			cairo_show_text (cr, "Mode cyclique");
			break;
		case 0:
			cairo_text_extents (cr, "Mode non cyclique", &te);
			cairo_move_to (cr, 250.5-te.x_bearing,
				SIZEY-25);
			cairo_show_text (cr, "Mode non cyclique");
			break;
	}

	// lignes
	int maxl=++l;
	int maxc=++c;
	for(int i=1; i<=l; ++i){
		cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
		cairo_move_to (cr, 50.0, i*50.0);
		cairo_line_to(cr, maxc*50.0, i*50.0);
		cairo_set_line_width (cr, 1);
		cairo_stroke (cr);
	}

	//colonnes
	for(int i=1; i<=c; ++i){
		cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
		cairo_move_to (cr, i*50.0, 50.0);
		cairo_line_to(cr, i*50.0, maxl*50.0);
		cairo_set_line_width (cr, 1);
		cairo_stroke (cr);
	}

	//affichage des cellules vivantes & non viables
	cairo_set_font_size (cr, 32);
	for(int i=0; i<g.nbl; ++i) {
		for(int j=0; j<g.nbc; ++j) {
			//cellules vivantes
			if (est_vivante(i,j,g)) {
				cairo_text_extents (cr, "•", &te);
				cairo_move_to (cr, 65+j*50, 85+i*50);
				cairo_show_text (cr, "•");
			}
			//cellules non viables
			else if (g.cellules[i][j]==-1){
				cairo_text_extents (cr,"+", &te);
				cairo_move_to (cr, 65+j*50, 85+i*50);
				cairo_show_text (cr, "+");
			}
			else cairo_move_to(cr, 65+j*50, 85+i*50);
		}
	} 

	cairo_destroy(cr); // destroy cairo mask
}

/** \brief programme principal*/
int main (int argc, char *argv[]){
	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;

	//initialisation des variables
	grille g, c;
	int toggle=0, cycle=0, dist=1;
	int (*compte_v)(int, int, int, grille)=compte_voisins_vivants_nc;
	
	//si jamais on donne trop ou pas d'arguments
	if(argc!=2){
		printf("Usage: ./life <grille>\n");
		exit(1);
	}

	//initialisation de la grille
	init_grille_from_file(argv[1], &g);
	alloue_grille (g.nbl, g.nbc, &c);

	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "Life");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	// run the event loop
	while(1) {
		XAllowEvents(dpy, AsyncPointer, CurrentTime);
		XNextEvent(dpy, &e);
		//tout dépend du type d'évènement:
		switch(e.type){
			//au démarrage...
			case Expose: if(e.xexpose.count<1) {
				paint(cs, g, g.nbl, g.nbc, toggle, cycle);
				}
				break;
			//en cas d'appui sur la souris (ou le trackpad, j'ai pas essayé avec l'écran tactile)...
			case ButtonPress: switch(e.xbutton.button){
				//clic droit -> fin du programme
				case 3: 
					libere_grille(&g);
					cairo_surface_destroy(cs); // destroy cairo surface
					XCloseDisplay(dpy); // close the display
					exit(0);
				//clic gauche -> évolution de la grille
				case 1: evolue(&g,&c,dist,toggle,compte_v);
					paint(cs, g, g.nbl, g.nbc, toggle, cycle);
					break;
				}
				break;
			//en cas d'appui sur une touche du clavier...
			case KeyPress: switch(e.xkey.keycode){
				//c -> change de mode
				case 54:
					switch(cycle){
						case 1:
							compte_v=compte_voisins_vivants_nc;
							cycle=0;
							break;
						case 0:
							compte_v=compte_voisins_vivants_c;
							cycle=1;
							break;
					}
					paint(cs, g, g.nbl, g.nbc, toggle, cycle);
					break;
				
				//v -> change l'état des cellules
				case 55: switch(toggle){
						case 0:
							toggle=1;
							break;
						case 1:
							toggle=0;
							break;
						default:break;
					}
					paint(cs, g, g.nbl, g.nbc, toggle, cycle);
					break;
				
				//d -> demande la distance sur le terminal
				case 40:
					printf("Entrez la nouvelle distance: ");
					dist=scanf("%d", &dist);
					paint(cs, g, g.nbl, g.nbc, toggle, cycle);
					break;

				//n -> charge un nouveau fichier depuis le terminal
				case 57:
					libere_grille(&c);
					libere_grille(&g);
					char filename[4096];
					printf("Entrez un nouveau fichier: ");
					scanf("%s", filename);
					init_grille_from_file(filename, &g);
					alloue_grille (g.nbl, g.nbc, &c);
					paint(cs, g, g.nbl, g.nbc, toggle, cycle);
					break;
				//o -> oscillations
				case 32: break;
				default:break;
			}
			break;
			default:break;
		}
	}
	return 0;
}

