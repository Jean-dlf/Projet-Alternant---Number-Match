
/*initialisation.c*/

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

/*** NOTE IMPORTANTE ***/
/* Pour les malloc faut toujours vérifier si l'allocation est NULL */

/* Initialisation du plateau */
plateau *initialisation_plateau(int n, int m){
    plateau *p = NULL; /* Initialisation du plateau à NULL */
    int i, j;

    /* Permet d'allouer le type plateau */
    if((p = (plateau *) malloc ( sizeof(plateau))) == NULL){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire du plateau de jeu\n");
        return NULL;
    }

    p->n = n; /* On donne le n en paramètre au n du plateau */
    p->m = m; /* On donne le m en paramètre au m du plateau */

    /* Permet d'allouer le plateau de jeu */
    if((p->tab = (cases**) malloc ( n * sizeof(cases *))) == NULL){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire des lignes du plateau de jeu\n");
        free(p); /* Si l'allocation a échoué alors on libère l'allocation du type plateau */
        p = NULL; /* Et on le redéfinit à NULL */
        return NULL;
    }

    /* Permet d'allouer chaque case du tableau */
    for(i = 0 ; i < n ; i++){
        if((p->tab[i] = (cases *) calloc ( m, sizeof(cases))) == NULL){ /* Ici on fait calloc au lieu de malloc, ça sert à allouer exactement comme malloc juste ça initialise toutes les cases à 0 directement */
            fprintf(stderr, "Erreur lors de l'allocation de la mémoire des colonnes du plateau de jeu\n");
            /* Si il y a une erreur lors de l'allocation d'une case alors on part de là où ça a bugué puis on revient au début tout en libérant l'espace alloué précédemment */
            /* C'est important en cas d'échec de libérer l'espace allouer */
            for(i = i - 1; i >= 0; i--){
                free(p->tab[i]); /* C'est la fonction pour libérer l'espace allouer */
                p->tab[i] = NULL;
            }
            /* Note important faut libérer tout dans le bon sens, donc d'abord chaque cases p->tab[i] ensuite le tableau p->tab puis le plateau p */
            free(p->tab);
            free(p);
            return NULL;
        }

        /* Si tout a fonctionné alors on initialise chaque cases avec les coordonnées actuelles de i et j et avec une value de base à 0 */
        for(j = 0; j < m; j++){
            p->tab[i][j].x = i;
            p->tab[i][j].y = j;
            p->tab[i][j].value = 0;
        }
    }
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

    for(i = 0; i < 3; i++){
        for(j = 0; j < p->m; j++){
            p->tab[i][j].value = rand() % (9 - 1 + 1) + 1; /* Rand permet de mettre des values aléatoires et le reste permet de savoir l'intervalle (ici de 1 à 9) */
        }
    }

    return p;
}

/* Initialisation d'une l_cases */
l_cases *initialisation_l_cases(cases *c1, cases *c2){
    l_cases *l_c = NULL;

    if((l_c = (l_cases*) malloc (sizeof(l_cases))) == NULL){
        fprintf(stderr, "Erreur allocation de la structure l_cases\n");
        return NULL;
    };

    l_c->n = 2;

    if((l_c->c = (cases*) malloc (2 * sizeof(cases))) == NULL){
        fprintf(stderr, "Erreur allocation du tableau de cases\n");
        free(l_c);
        return NULL;
    }

    l_c->c[0] = *c1;
    l_c->c[1] = *c2;

    return l_c;
}