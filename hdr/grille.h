/**
  \file grille.h
  \brief Headers pour \c grille.c

 */
#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdbool.h>

/**
  \brief Grille comprenant le nombre de lignes, le nombre de colonnes et une matrice cellulaire.
 */
typedef struct {
  int nbl; /**< \brief nombre de lignes */
  int nbc; /**< \brief nombre de colonnes */
  int **cellules; /**< \brief matrice cellulaire */
} grille;

/**
 \fn alloue_grille (int, int, grille*)
 \brief Alloue la grille de taille l*c. Toutes les cellules seront \b mortes par défaut.
 
 \param l Lignes
 \param c Colonnes
 \param g Pointeur sur le tableau à allouer
 */
void alloue_grille(int l, int c, grille* g);

/**
 \fn libere_grille (grille*)
 \brief Libère la grille donnée.
 
 \param g Pointeur qur leableau à libérer
 */
void libere_grille(grille* g);

/**
 \fn init_grille_from_file (const char*, grille*)
 \brief Initialise la grille depuis un fichier. 
 
 \param filename Chemin du fichier à initialiser
 \param g Pointeur sur le tableau à initialiser
 */
void init_grille_from_file(char const*const filename, grille* g);

/**
 \fn set_vivante (int, int, grille)
 \brief Rend la cellule vivante (bienvenue parmi les cellules !).
 
 \param i Ligne où se trouve la cellule
 \param j Colonne où se situe la cellule
 \param g Grille
 \return 1 sur la cellule (i,j) : la cellule est \b vivante
 */
inline void set_vivante(int i, int j, grille g) {
  g.cellules[i][j]++;
}

/**
 \fn set_morte (int, int, grille)
 \brief Rend la cellule morte (RIP cellule).
 
 \param i Ligne où se trouve la cellule
 \param j Colonne où se situe la cellule
 \param g Grille
 \return 0 sur la cellule (i,j) : la cellule est \b morte
 */
inline void set_morte(int i, int j, grille g) {
  g.cellules[i][j] = 0;
}

/**
 \fn set_non_viable (int, int, grille)
 \brief Un peu comme la zone 51: personne de doit aller là-bas.
 
 \param i Ligne où se trouve la cellule
 \param j Colonne où se situe la cellule
 \param g Grille
 \return -1 sur la cellule (i,j) : la cellule est \b non-viable
 */
inline void set_non_viable(int i, int j, grille g){
  g.cellules[i][j]=-1;
}

/**
 \fn est_vivante (int, int, grille)
 \brief Teste si la cellule est vivante.
 
 \param i Ligne où se trouve la cellule
 \param j Colonne où se situe la cellule
 \param g Grille
 \return Booléen vérifiant l'existence de cette cellule
 */
inline bool est_vivante(int i, int j, grille g) {
  return g.cellules[i][j] >0;
}

/**
 \fn copie_grille (const grille*, grille*)
 \brief Copie la grille (pour des raisons de sécurité ?) sans allouer la destination
 
 \param gs Pointeur sur la grille source
 \param gd Pointeur sur la grille destination
 */
void copie_grille(const grille *gs, grille *gd);

#endif // __GRILLE_H
