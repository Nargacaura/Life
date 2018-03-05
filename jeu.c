#include "jeu.h"

int compte_voisins_vivants(int i, int j, grille g) {
  int v = 0;
  int n=i-1, c=j-1;
  int templ, tempc;
  if(n<0)
    n=g.nbl-1;
  if(c<0)
    c=g.nbc-1;
  for(templ=0; templ<3 && n<=i+1; templ++, n++){
    for(tempc=0; tempc<3 && c<=j+1; tempc++, c++){
      if(n>=g.nbl)
        n=0;
      if(c>=g.nbc)
        c=0;
      if(g.cellules[n][c]!=0 && (n!=i && c!=j))
        v++;
    }
  }
  return v;
}

void evolue(grille *g, grille *gc) {
  copie_grille (g,gc); // copie temporaire de la grille
  for (int i=0; i < g->nbl; i++) {
    for (int j=0; j < g->nbc; ++j) {
      /*set_vivante(i, j, *g);*/
      /*set_morte(i, j, *g);*/
    }
  }
}
