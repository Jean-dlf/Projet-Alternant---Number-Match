#ifndef _JEU_H_
#define _JEU_H_
#include "types.h"

void afficher_case(cases *c);

int cases_similaire(cases *c1, cases *c2);

int verif_somme_10(cases *c1, cases *c2);

int verif_cases_vides(plateau *p, int x, int y);

int dans_plateau(plateau *p);

int voisins(cases *c1, cases *c2, plateau *p);

cases cases_haute(cases *c1, cases *c2);

int voisin_plus(cases *c1, cases *c2, plateau *p);

cases select_case(plateau *p);

l_cases liste_paire(plateau *p);

int match(l_cases *l_c, plateau *p);

plateau *mise_a_zero(plateau *p, l_cases l_c);

int *ligne_vide(plateau *p, int *taille);

void aff_tab(int *tab, int taille);

plateau *suppression_ligne_vide(plateau *p, int *tab_vide, int taille);

#endif