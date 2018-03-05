#include "jeu.h"

int compte_voisins_vivants(int i, int j, grille g) {
  int v = 0;
  int lb=i-1, cb=j-1;
  int le=i+1, ce=j+1;
  if(i==0)
    lb=g.nbl-1;
  if(j==0)
    cb=g.nbc-1;
  if(i==g.nbl-1)
    le=0;
  if(j==g.nbc-1)
    ce=0;
  for(; lb<=le; lb++){
    for(; cb<=ce; cb++){
      if(est_vivante(modulo(lb, g.nbl), modulo(cb, g.nbc), g)
       && (lb!=i && cb!=j))
        v++;
    }
  }
  return v;
}

void evolue(grille *g, grille *gc) {
  copie_grille (g,gc); // copie temporaire de la grille
  for (int i=0; i < gc->nbl; i++) {
    for (int j=0; j < gc->nbc; j++) {
      if(!est_vivante(i, j, *gc) && compte_voisins_vivants(i, j, *gc)==3)
        set_vivante(i, j, *gc);
      else {
        if(est_vivante(i, j, *gc) &&
          (compte_voisins_vivants(i, j, *gc)==3 || compte_voisins_vivants(i, j, *gc)==2))
          set_vivante(i, j, *gc);
        else set_morte(i, j, *gc);
      }
    }
  }
}
