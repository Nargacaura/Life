#include "jeu.h"

int compte_voisins_vivants(int i, int j, grille g) {
  int v = 0;
  int n, c;
  int templ, tempc;
  if(i==0)
    n=g.nbl-1;
  else n=i-1;
  if(j==0)
    c=g.nbc-1;
  else c=j-1;
  for(templ=0; templ<3; templ++, n++){
    for(tempc=0; tempc<3; tempc++, c++){
      if(n>=g.nbl)
        n=0;
      if(c>=g.nbc)
        c=0;
      if(est_vivante(n, c, g))
        v++;
    }
  }
  return v;
}

void evolue(grille *g, grille *gc) {
  copie_grille (g,gc); // copie temporaire de la grille
  for (int i=0; i < g->nbl; i++) {
    for (int j=0; j < g->nbc; j++) {
      if(!est_vivante(i, j, *gc) && compte_voisins_vivants(i, j, *gc)==3)
        set_vivante(i, j, *gc);
      else if(est_vivante(i, j, *gc) &&
       (compte_voisins_vivants(i, j, *gc)==3 || compte_voisins_vivants(i, j, *gc)==2))
        set_vivante(i, j, *gc);
      else set_morte(i, j, *gc);
    }
  }
}
