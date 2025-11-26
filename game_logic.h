
/*jeu.h*/

#ifndef _JEU_H_
#define _JEU_H_
#include "types.h"

void viderBuffer();

void display_case(cases *c);

int similar_boxes(cases *c1, cases *c2);

int verif_sum_10(cases *c1, cases *c2);

int points_for_match(l_cases *l_c);

int verif_empty_boxes(plateau *p, int x, int y);

int in_plateau(plateau *p, int x, int y);

cases high_box(cases *c1, cases *c2);

int neighbor_start_beginning_line(cases *c1, cases *c2, plateau *p);

int neighbors(cases *c1, cases *c2, plateau *p);

int neighbors_more(cases *c1, cases *c2, plateau *p);

cases select_box(plateau *p);

l_cases pair_list(plateau *p);

int match(l_cases *l_c, plateau *p);

plateau *reset(plateau *p, l_cases l_c);

int *empty_lines(plateau *p, int *taille);

void display_tab(int *tab, int taille);

void display_l_cases(l_cases l_c);

plateau *delete_empty_lines(plateau *p, int *tab_vide, int taille);

/***** BONUS *****/

int empty_plateau(plateau *p);

cases *last_box(plateau *p);

plateau *use_add_lines(plateau *p, int *valide);

plateau *bonus_add_lines(plateau *p);

int add_nb_lines_plateau(plateau *p, int nb_ligne);

tab_couples possible_couples(plateau *p);

void display_possible_couples(tab_couples t_c);

void free_tab_couples(tab_couples *t_c);

l_cases random_couple(tab_couples *t_c);

void bonus_clue(plateau *p);

int use_clue(plateau *p);

/*** Défaite ***/

int empty(plateau *p);

int loose(plateau *p, int nb_ajt_lig, int nb_ind_cpl);

#endif