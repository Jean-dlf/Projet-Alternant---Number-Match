#include <stdio.h>
#include <stdlib.h>
#include "../Headers/types.h"


/* Initialisation du plateau */
plateau *initialisation_plateau(int n, int m){
    plateau *p = NULL; /* Initialisation du plateau à NULL */
    int i, j;

    /* Permet d'allouer le type plateau */
    if((p = (plateau *) malloc ( sizeof(plateau))) == NULL){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire du plateau de jeu\n");
        return NULL;
    }

    /* Définition de p->n et p->m */
    p->n = n;
    p->m = m;

    /* Permet d'allouer le plateau de jeu */
    if((p->tab = (cases**) malloc ( n * sizeof(cases *))) == NULL){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire des lignes du plateau de jeu\n");
        free(p);
        p = NULL;
        return NULL;
    }

    /* Permet d'allouer chaque case du tableau */
    for(i = 0 ; i < n ; i++){
        if((p->tab[i] = (cases *) calloc ( m, sizeof(cases))) == NULL){ /* Ici on fait calloc au lieu de malloc, ça sert à allouer exactement comme malloc juste ça initialise toutes les cases à 0 directement */
            fprintf(stderr, "Erreur lors de l'allocation de la mémoire des colonnes du plateau de jeu\n");

            /* Libération cases allouées précédemment */
            for(i = i - 1; i >= 0; i--){
                free(p->tab[i]);
                p->tab[i] = NULL;
            }

            /* Libération */
            free(p->tab);
            free(p);
            return NULL;
        }

        /* Iitialisatio des cases */
        for(j = 0; j < m; j++){
            p->tab[i][j].x = i;
            p->tab[i][j].y = j;
            p->tab[i][j].value = 0;
        }
    }
    
    /* Initialisation score et mode */
    p->score_actuel = 0;
    p->mode = 0;

    return p;
}

/* Initialisation du type cases */
cases *initialisation_cases(int x, int y, int value){
    cases *c = NULL; /* Initialisation à vide */

    /* Allocation du type cases */
    if((c = (cases *) malloc ( sizeof(cases))) == NULL){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire d'une case\n");
        free(c); /* Libération en cas d'échec */
        return NULL;
    }

    /* Initialisation des coordonées et des values de la case */
    c->x = x;
    c->y = y;
    c->value = value;

    return c;
}

/* Fonction pour mettre les 3 premières lignes du tableau avec des values aléatoires */
plateau *random_initialisation(plateau *p){
    int i, j;

    for(i = 0; i < p->n; i++){
        for(j = 0; j < p->m; j++){
            p->tab[i][j].value = rand() % (9 - 1 + 1) + 1; /* Rand permet de mettre des values aléatoires et le reste permet de savoir l'intervalle (ici de 1 à 9) */
        }
    }

    return p;
}

/* Initialisation d'une l_cases */
l_cases *initialisation_l_cases(cases *c1, cases *c2){
    l_cases *l_c = NULL;

    /* Initialisatio de la liste de cases */
    if((l_c = (l_cases*) malloc (sizeof(l_cases))) == NULL){
        fprintf(stderr, "Erreur allocation de la structure l_cases\n");
        return NULL;
    };

    /* Défiition de sa longueur max à 2 */
    l_c->n = 2;

    /* Allocation de la taille */
    if((l_c->c = (cases*) malloc (2 * sizeof(cases))) == NULL){
        fprintf(stderr, "Erreur allocation du tableau de cases\n");
        free(l_c);
        return NULL;
    }

    /* Initialisation des cases dans l_cases */
    l_c->c[0] = *c1;
    l_c->c[1] = *c2;

    return l_c;
}