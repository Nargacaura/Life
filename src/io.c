/**
  \file io.c
  \brief Source d'entrée/sortie

 */
#include "../hdr/io.h"
#include "../hdr/jeu.h"

static void affiche_trait(int c) {
  int i;
  for (i=0; i<c; ++i) printf ("|---");
  printf("|\n");
  return;
}

int oldToggle=0; /**< \brief \c oldToggle est l'indicateur de vieillesse*/
static void affiche_ligne(int ligne, const grille *g) {
  if(oldToggle==0){
    for (int i=0; i < g->nbc; ++i) {
      if (est_vivante(ligne, i, *g))
        printf ("| ¤ ");
      else if(g->cellules[ligne][i]==-1)
        printf("| X ");
      else
        printf ("|   ");
    }
  } else {
    for(int i=0; i<g->nbc; ++i){
      if(est_vivante(ligne, i, *g))
        printf("| %d ", g->cellules[ligne][i]);
      else if (g->cellules[ligne][i]==-1)
        printf("| X ");
      else printf("|   ");
    }
  } 
  printf("|\n");
  return;
}

unsigned int t=0; /**< étape */
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

int (*compte_v)(int, int, int, grille)=compte_voisins_vivants_nc;
/**< \brief \c compte_v est le mode de jeu */
int dist=1; /**< \brief \c dist est la distance de voisinage */
void debut_jeu(grille *g, grille *gc) {
  int c = getchar();
  while (c != 'q') { // touche 'q' pour quitter
    switch (c) {
      case 'c':{
        getchar();
        if(compte_v==compte_voisins_vivants_c){
          compte_v=compte_voisins_vivants_nc;
          printf("Voisinage cyclique désactivé.   ");
        } else {
          compte_v=compte_voisins_vivants_c;
          printf("Voisinage cyclique activé.      ");
        }
        printf("\n\e[%dA", 2);
        break;
      }
      case 'n': {
        printf("^ Nouvelle distance de voisinage");
        printf("\n\e[%dA", 2);
        dist=scanf("%d", &dist);
        getchar();
        printf("\n\e[%dA", 2);
        break;
      }

      case 'v':{
        if(oldToggle==0){
          oldToggle=1;
          printf("Vieillissement activé.           ");
        } else {
          oldToggle=0;
          printf("Vieillissement désactivé.        ");
        }
        getchar();
        printf("\n\e[%dA", 2);
        break;
      }
      case '\n' :
        { // touche "entree" pour évoluer
          evolue(g,gc, dist, oldToggle, (*compte_v));
          efface_grille(g);
          affiche_grille(g);
          break;
        }
      case 'o': //oscillations
        break;
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
