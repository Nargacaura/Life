/**
  \file io.h
  \brief Headers pour \c io.c

 */
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/**
 \fn affiche_grille (const grille*)
 \brief Affiche la grille donnée.

 \param g Pointeur sur le tableau à afficher
 */
void affiche_grille (const grille *g);

/**
 \fn efface_grille (const grille*)
 \brief Efface la grille donnée.
 
 \param g Pointeur sur le tableau à effacer
 */
void efface_grille (const grille *g);

/**
 \fn debut_jeu (grille*, grille*)
 \brief Débute le jeu avec la grille et sa copie.
 
 \param g Pointeur sur le tableau original
 \param gc Pointeur sur la copie du tableau
 */
void debut_jeu(grille *g, grille *gc);

#endif
