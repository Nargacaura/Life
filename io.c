/**
  \file io.c
  \brief Source d'entrée/sortie

 */
#include "io.h"
#include "jeu.h"

static void affiche_trait(int c) {
  int i;
  for (i=0; i<c; ++i) printf ("|---");
  printf("|\n");
  return;
}

static void affiche_ligne(int ligne, const grille *g) {
  for (int i=0; i < g->nbc; ++i) {
    if (est_vivante(ligne, i, *g))
      printf ("| O ");
    else
      printf ("|   ");
  }
  printf("|\n");
  return;
}

int t=0;
void affiche_grille(const grille *g) {
  printf("Life: le jeu de la Vie | étape %d\n", t++);
  affiche_trait(g->nbc);
  for (int i=0; i < g->nbl; ++i) {
    affiche_ligne(i, g);
    affiche_trait(g->nbc);
  }
  printf("\n");
  return;
}

void efface_grille(const grille *g) {
  printf("\n\e[%dA", g->nbl * 2 + 5);
}

int (*compte_v)(int, int, int, grille)=compte_voisins_vivants_c;
int dist=1;
void debut_jeu(grille *g, grille *gc) {
  int c = getchar();
  while (c != 'q') { // touche 'q' pour quitter
    switch (c) {
      case 'c':{
        if(compte_v==compte_voisins_vivants_c){
          compte_v=compte_voisins_vivants_nc;
          printf("Voisinage cyclique désactivé.");
        } else {
          compte_v=compte_voisins_vivants_c;
          printf("Voisinage cyclique activé.");
        }
        break;
      }
      case 'n': {
        printf("Nouvelle distance de voisinage: ");
        dist=scanf("%d", &dist);
        break;
      }
      case '\n' :
        { // touche "entree" pour évoluer
          evolue(g,gc, dist, (*compte_v));
          efface_grille(g);
          affiche_grille(g);
          break;
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
