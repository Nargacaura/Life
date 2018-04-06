/**
  \file cairo.h
  \brief Headers pour \c cairo.c

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

void paint(cairo_surface_t *surface, grille g, int l, int c, int age, int cycle);

/**
 \brief Affichage de la grille | \c affiche_grille
 Affiche la grille donnée.

 \param g Pointeur sur le tableau à afficher
 */


/**
 \brief Effacement de la grille | \c efface_grille
 Efface la grille donnée.
 
 \param g Pointeur sur le tableau à effacer
 */

#endif
