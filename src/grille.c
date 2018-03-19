/**
  \file grille.c
  \brief Source de la grille

 */
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../hdr/grille.h"

void alloue_grille(int l, int c, grille* g) {
  g->nbc=c;
  g->nbl=l;
  g->cellules=(int**)malloc(l*sizeof(int*));

  int count;
  for(count=0; count<l; count++){
    g->cellules[count]=(int*)calloc(c, sizeof(int));
  } 
}

void libere_grille(grille* g) {
  int count;
  for(count=0; count<g->nbl; count++)
    free(g->cellules[count]);
  free(g->cellules);
  g->nbc=0;
  g->nbl=0;
}

void init_grille_from_file(char const*const filename, grille *const g) {
  FILE * pfile = fopen(filename, "r");
  if (pfile == NULL) {
    fprintf(stderr,
        "Erreur (%s:%d): Lecture du fichier \"%s\" impossible (%s)\n",
        __FILE__, __LINE__-4, filename, strerror(errno));
    exit(EXIT_FAILURE);
  }

  int l, c;
  fscanf(pfile, "%d", &l);
  fscanf(pfile, "%d", &c);
  alloue_grille(l,c,g);

  int vivantes=0;
  fscanf(pfile, "%d", & vivantes);
  for (int n=0; n < vivantes; n++){
    fscanf(pfile, "%d", &l);
    fscanf(pfile, "%d", &c);
    set_vivante(l,c,*g);
  }

  fclose (pfile);
  return;
}

void copie_grille(const grille *const gs, grille *const gd) {
  assert(gs->nbl == gd->nbl && gs->nbc == gd->nbc);
  for (int i=0; i < gs->nbl; ++i)
    for (int j=0; j < gs->nbc; ++j)
      gd->cellules[i][j] = gs->cellules[i][j];
}

extern inline bool est_vivante(int i, int j, grille g); 
extern inline void set_vivante(int i, int j, grille g);
extern inline void set_non_viable(int i, int j, grille g);
extern inline void set_morte(int i, int j, grille g);
