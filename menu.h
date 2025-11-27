#ifndef _MENU_H_
#define _MENU_H_

#include "types.h"
#include <MLV/MLV_all.h>

int verif(button button, int coord_x, int coord_y);

int clic_button(button t_button[], int longueur);

void create_button(button *button, char* message, int x, int y, MLV_Font *police);

void display_text(button button , MLV_Font *police);

void menu_p(button t_button_menu[5]);

void menu_save(button t_button_save[5]);

void menu_mode(button t_button_menu[3]);

void menu_rules(button *back);

void menu_score(button *back);

#endif