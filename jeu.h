#ifndef _JEU_H_
#define _JEU_H_
#include "types.h"

void afficher_case(cases *c);

int cases_similaire(cases *c1, cases *c2);

int verif_somme_10(cases *c1, cases *c2);

int verif_cases_vides(plateau *p, int x, int y);

int dans_plateau(plateau *p, int x, int y);

int voisins(cases *c1, cases *c2, plateau *p);

cases cases_haute(cases *c1, cases *c2);

int voisin_plus(cases *c1, cases *c2, plateau *p);

cases select_case(plateau *p);

l_cases liste_paire(plateau *p);

int match(l_cases *l_c, plateau *p);

plateau *mise_a_zero(plateau *p, l_cases l_c);

int *ligne_vide(plateau *p, int *taille);

void aff_tab(int *tab, int taille);

void afficher_l_cases(l_cases l_c);

plateau *suppression_ligne_vide(plateau *p, int *tab_vide, int taille);

plateau *bonus_ajout_ligne(plateau *p);

/***** BONUS *****/

int plateau_vide(plateau *p);

cases *derniere_case(plateau *p);

plateau *utiliser_ajout_ligne(plateau *p);

plateau *bonus_ajout_ligne(plateau *p);

int ajout_nb_ligne_plateau(plateau *p, int nb_ligne);


tab_couples couples_possibles(plateau *p);

void afficher_couples_possibles(tab_couples t_c);

void liberer_tab_couples(tab_couples *t_c);

l_cases couple_aleatoire(tab_couples *t_c);

void bonus_indice(plateau *p);

int utiliser_indice(plateau *p);

#endif