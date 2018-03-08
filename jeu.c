#include "jeu.h"
#include <stdio.h>

int compte_voisins_vivants(int i, int j, grille g) {
  int v = 0;
  int lb=i-1, cb=j-1;
  for(int templ=0; templ<3; templ++, lb++){
    for(int tempc=0; tempc<3; tempc++, cb++){
      if(lb<0)
        lb=modulo(g.nbl+(i-1), g.nbl);
      if(cb<0)
        cb=modulo(g.nbc+(j-1), g.nbc);
      if(lb>g.nbl-1)
        lb=modulo(lb, g.nbl);
      if(cb>g.nbc-1)
        cb=modulo(cb, g.nbc);
      v+=est_vivante(lb, cb, g);
    }
  }
  return v;
}

void evolue(grille *g, grille *gc) {
  copie_grille (g,gc); // copie temporaire de la grille
  for (int i=0; i < g->nbl; ++i) {
    for (int j=0; j < g->nbc; ++j) {
      if(!est_vivante(i, j, *gc) && compte_voisins_vivants(i, j, *gc)==3)
        set_vivante(i, j, *g);
      else {
        if(est_vivante(i, j, *gc) &&
          (compte_voisins_vivants(i, j, *gc)==2 || compte_voisins_vivants(i, j, *gc)==3))
          set_vivante(i, j, *g);
        else set_morte(i, j, *g);
      }
    }
  }
}
