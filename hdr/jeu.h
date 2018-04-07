/**
  \file jeu.h
  \brief Headers pour \c jeu.c

 */ 
#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/**
 \fn modulo (int, int)
 \brief Modulo de deux nombres
 
 \param i Nombre aléatoire
 \param m Modulo limite
 \return Valeur du modulo
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

/**
 \fn compte_voisins_vivants_c (int, int, int, grille)
 \brief Compte les voisins d'une cellule en position (i,j) dans la grille \c g sans compter celle-ci. Le parcours est cyclique.
 
 \param i Ligne où la cellule se trouve
 \param j Colonne où la cellule se situe
 \param distance Rayon minimum du voisinage cyclique
 \param g Tableau de cellules
 \return Nombre de voisins vivants
 */
int compte_voisins_vivants_c(int i, int j, int distance, grille g);

/**
 \fn compte_voisins_vivants_nc (int, int, int, grille)
 \brief Compte les voisins d'une cellule en position (i,j) dans la grille \c g sans compter celle-ci. Le parcours est non cyclique.
 
 \param i Ligne où la cellule se trouve
 \param j Colonne où la cellule se situe
 \param distance Rayon minimum du voisinage cyclique
 \param g Tableau de cellules
 \return Nombre de voisins vivants
 */
int compte_voisins_vivants_nc(int i, int j, int distance, grille g);

/**
 \fn evolue (grille*, grille*, int, int, int (*)(int, int, int, grille))
 \brief Affiche l'état des cellules au temps t+1.
 
 \param g Tableau à copier
 \param gc Copie du tableau
 \param dist Rayon de voisins
 \param toggle Indicateur de vieillesse des cellules
 \param compte_v Statut du parcours (cyclique ou non)
 \return Tableau \c g au temps t+1
 */
void evolue (grille *g, grille *gc, int dist, int toggle, int (*compte_v)(int, int, int, grille));

#endif
