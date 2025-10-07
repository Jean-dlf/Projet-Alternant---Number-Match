#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "types.h"
#include "initialisation.h"
#include "plateau.h"
#include "jeu.h"

int main(){
    
    int n = 6;
    int m = 6;
    int taille;
    plateau *p;
    cases *c1, *c2, *c3, *c4, *c5, *c6, *c7, *c8, *c9, *c10;
    l_cases l_c;
    int *tab_vide;

    srand(time(NULL));

    c1 = initialisation_cases(0, 0, 5);
    c2 = initialisation_cases(0, 1, 0);
    c3 = initialisation_cases(0, 2, 0);
    c4 = initialisation_cases(0, 3, 0);
    c5 = initialisation_cases(0, 4, 0);
    c6 = initialisation_cases(0, 5, 0);
    c7 = initialisation_cases(1, 0, 0);
    c8 = initialisation_cases(1, 1, 0);
    c9 = initialisation_cases(1, 2, 5);
    c10 = initialisation_cases(3, 0, 9);

    p = initialisation_plateau(n, m);
    initialisation_aleatoire(p);

    p->tab[c1->x][c1->y].valeur = c1->valeur;
    p->tab[c2->x][c2->y].valeur = c2->valeur;
    p->tab[c3->x][c3->y].valeur = c3->valeur;
    p->tab[c4->x][c4->y].valeur = c4->valeur;
    p->tab[c5->x][c5->y].valeur = c5->valeur;
    p->tab[c6->x][c6->y].valeur = c6->valeur;
    p->tab[c7->x][c7->y].valeur = c7->valeur;
    p->tab[c8->x][c8->y].valeur = c8->valeur;
    p->tab[c9->x][c9->y].valeur = c9->valeur;
    p->tab[c10->x][c10->y].valeur = c10->valeur;

    afficher_plateau(p);
    
    l_c = liste_paire(p);

    mise_a_zero(p, l_c);

    afficher_plateau(p);

    tab_vide = ligne_vide(p, &taille);
    aff_tab(tab_vide, taille);

    suppression_ligne_vide(p, tab_vide, taille);

    afficher_plateau(p);

    /*afficher_case(c3);

    voisins(c1, c2, p);*/

    exit(EXIT_SUCCESS);
}