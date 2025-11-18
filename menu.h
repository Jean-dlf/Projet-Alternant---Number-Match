#ifndef _MENU_H_
#define _MENU_H_

#include "types.h"

int verif(bouton bouton, int coord_x, int coord_y);

int clic_bouton(bouton t_bouton[], int longueur);

void cree_bouton(bouton *bouton, char* message, int x, int y, MLV_Font *police);

void menu_p(bouton t_bouton_menu[5]);

void menu_save(bouton t_bouton_save[5]);

void menu_rules(bouton *retour);

void menu_score(bouton *retour);

#endif