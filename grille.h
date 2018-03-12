/**
  \file grille.h
  \brief Headers pour \c grille.c

 */
#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdbool.h>

/**
 \typedef grille
 \brief Grille comprenant le nombre de lignes, le nombre de colonnes et une matrice cellulaire.

 */
typedef struct {
  int nbl; /** \brief nombre de lignes */
  int nbc; /** \brief nombre de colonnes */
  int **cellules; /** \brief matrice cellulaire */
} grille;

/**
 \brief Allocation de la grille | \c alloue_grille
 Alloue la grille de taille l*c. Toutes les cellules seront \b mortes par défaut.
 
 \param l Lignes
 \param c Colonnes
 \param g Pointeur sur le tableau à allouer
 */
void alloue_grille(int l, int c, grille* g);

/**
 \brief Libération de la grille | \c libere_grille
 Libère la grille donnée.
 
 \param g Pointeur qur leableau à libérer
 */
void libere_grille(grille* g);

/**
 \brief Initialisation de la grille | \c init_grille_from_file
 Alloue la grille et l'initialise depuis un fichier. 
 
 \param filename Chemin du fichier à initialiser
 \param g Pointeur sur le tableau à initialiser
 */
void init_grille_from_file(char const*const filename, grille* g);

/**
 \brief La naissance d'une cellule | \c set_vivante
 Rend la cellule vivante (bienvenue parmi les cellules !).
 
 \param i Ligne où se trouve la cellule
 \param j Colonne où se situe la cellule
 \param g Grille
 \return 1 sur la cellule (i,j) : la cellule est \b vivante
 */
inline void set_vivante(int i, int j, grille g) {
  g.cellules[i][j] = 1;
}

/**
 \brief La mort d'une cellule | \c set_morte
 Rend la cellule morte (RIP cellule).
 
 \param i Ligne où se trouve la cellule
 \param j Colonne où se situe la cellule
 \param g Grille
 \return 0 sur la cellule (i,j) : la cellule est \b morte
 */
inline void set_morte(int i, int j, grille g) {
  g.cellules[i][j] = 0;
}

/**
 \brief Est-elle vivante ? | \c est_vivante
 Teste si la cellule est vivante.
 
 \param i Ligne où se trouve la cellule
 \param j Colonne où se situe la cellule
 \param g Grille
 \return Booléen vérifiant l'existence de cette cellule
 */
inline bool est_vivante(int i, int j, grille g) {
  return g.cellules[i][j] == 1;
}

/**
 \brief Copie de la grille | \c copie_grille
 Copie la grille (pour des raisons de sécurité ?) sans allouer la destination
 
 \param gs Pointeur sur la grille source
 \param gd Pointeur sur la grille destination
 */
void copie_grille(const grille *gs, grille *gd);

#endif // __GRILLE_H
