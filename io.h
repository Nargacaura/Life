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
 \brief Affichage de la grille | \c affiche_grille
 Affiche la grille donnée.

 \param g Pointeur sur le tableau à afficher
 */
void affiche_grille (const grille *g);

/**
 \brief Effacement de la grille | \c efface_grille
 Efface la grille donnée.
 
 \param g Pointeur sur le tableau à effacer
 */
void efface_grille (const grille *g);

/**
 \brief Que le jeu commence ! | \c debut_jeu
 Débute le jeu avec la grille et sa copie.
 
 \param g Pointeur sur le tableau original
 \param gc Pointeur sur la copie du tableau
 */
void debut_jeu(grille *g, grille *gc);

#endif
