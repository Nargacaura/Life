/**
  \file jeu.h
  \brief Headers pour \c jeu.c

 */ 
#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/**
 \brief Modulo | \c modulo
 
 \param i Nombre aléatoire
 \param m Modulo limite
 \return Valeur du modulo
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

/**
 \brief Compte des voisins vivants | \c compte_voisins_vivants
 Compte les voisins d'une cellule en position (i,j) dans la grille \c g sans compter celle-ci. Le parcours est cyclique.
 
 \param i Ligne où la cellule se trouve
 \param j Colonne où la cellule se situe
 \param g Tableau de cellules
 \return Nombre de voisins vivants
 */
int compte_voisins_vivants (int i, int j, grille g);

/**
 \brief Évolution | \c evolue
 Affiche l'état des cellules au temps t+1.
 
 \param g Tableau à copier
 \param gc Copie du tableau
 \return Tableau \c g au temps t+1
 */
void evolue (grille *g, grille *gc);

#endif
