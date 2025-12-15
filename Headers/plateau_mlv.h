#ifndef _PLATEAU_MENU_H_
#define _PLATEAU_MENU_H_

#include "types.h"

/* NOMBRE DE CASES VISIBLES AU MAXIMUM SUR LA FENETRE DE JEU */
#define VISIBLE 11

/* TAILLE DES CASES */
#define CASES 90

/* Variable permettant de savoir de combien de case le plateau dépasse de l'affichage */
extern int offset;

void display_plateau_mlv(plateau *p, button t_button_game[5], double elapsed, parti *plyr);

#endif