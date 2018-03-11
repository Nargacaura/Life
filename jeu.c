/**
  \file jeu.c
  \brief Source du "jeu"

 */ 
#include "jeu.h"
#include <stdio.h>

int compte_voisins_vivants(int i, int j, grille g) {
  int v = 0;
  for(int templ=-1; templ<=1; templ++){
    for(int tempc=-1; tempc<=1; tempc++){
      if(templ!=0)
        v+=est_vivante(modulo(i+templ, g.nbl), modulo(j+tempc, g.nbc), g);
      else {
        if(tempc!=0)
          v+=est_vivante(modulo(i, g.nbl), modulo(j+tempc, g.nbc), g);
      }
    }
  }
  return v;
}

void evolue(grille *g, grille *gc) {
  copie_grille (g,gc); // copie temporaire de la grille
  for (int i=0; i < g->nbl; ++i) {
    for (int j=0; j < g->nbc; ++j) {
      if(!est_vivante(i, j, *gc) && compte_voisins_vivants(i, j, *gc)==3) /**< Si elle est morte et a 3 voisins */
        set_vivante(i, j, *g);
      else {
        if(est_vivante(i, j, *gc) &&
          (compte_voisins_vivants(i, j, *gc)==2 || compte_voisins_vivants(i, j, *gc)==3)) /**< Si elle est déjà vivante */
          set_vivante(i, j, *g);
        else set_morte(i, j, *g); /**< sinon elle meurt */
      }
    }
  }
}
