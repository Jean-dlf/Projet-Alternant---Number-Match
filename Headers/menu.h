#ifndef _MENU_H_
#define _MENU_H_

#include "types.h"
#include <MLV/MLV_all.h>

int verif(button button, int coord_x, int coord_y);

int clic_button(button t_button[], int longueur, int mx, int my);

void create_button(button *button, char* message, int x, int y, MLV_Font *police);

void display_text(button button , MLV_Font *police);

void menu_p(button t_button_menu[4]);

void menu_save(button t_button_save[5]);

void menu_mode(button t_button_menu[3]);

void menu_choice_mode(button t_button_choice_mode[3]);

int choice_mode_game();

void menu_rules_classic(button *next);

void menu_rules_locksmith(button *next);

void menu_score();

void menu_pause(button t_button_pause[3]);

int crushing_save();

void save_pause_management(parti *plyr, plateau *p , int pressed);

int pause_game(parti *plyr, plateau *p);

void display_text_box(char *message);

void ask_name(parti *p);

void recap_game(parti player);

void menu_ask_difficulty(button t_button_level[6], int custom);

void menu_customised_dimensions(plateau *p);

#endif