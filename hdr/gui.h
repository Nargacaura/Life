/**
  \file gui.h
  \brief Headers pour \c gui.c

 */
#ifndef __CAIRO_H
#define __CAIRO_H

#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include "grille.h"
#include "jeu.h"


/**
 \fn paint(cairo_surface_t*, grille, int, int, int, int)
 \brief Affiche graphiquement le jeu de la vie: les cellules, les cases représentées par les lignes & les colonnes, le texte contenant le titre et les informations utiles ...

 \param surface la surface utilisée pour Cairo
 \param g la grille allouée
 \param l le nombre de lignes
 \param c le nombre de colonnes
 \param age l'indicateur de vieillesse des cellules
 \param cycle l'indicateur du mode de jeu
 */

void paint(cairo_surface_t *surface, grille g, int l, int c, int age, int cycle);

#endif
