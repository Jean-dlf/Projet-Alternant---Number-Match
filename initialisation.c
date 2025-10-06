#include <stdio.h>
#include <stdlib.h>
#include "types.h"

plateau *initialisation_plateau(int n, int m){
    plateau *p = NULL;
    int i, j;

    if((p = (plateau *) malloc ( sizeof(plateau))) == NULL){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire du plateau de jeu\n");
        return NULL;
    }

    p->n = n;
    p->m = m;

    if((p->tab = (cases**) malloc ( n * sizeof(cases *))) == NULL){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire des lignes du plateau de jeu\n");
        free(p);
        p = NULL;
        return NULL;
    }

    for(i = 0 ; i < n ; i++){
        if((p->tab[i] = (cases *) calloc ( m, sizeof(cases))) == NULL){
            fprintf(stderr, "Erreur lors de l'allocation de la mémoire des colonnes du plateau de jeu\n");
            for(i = i - 1; i >= 0; i--){
                free(p->tab[i]);
                p->tab[i] = NULL;
            }
            free(p);
            return NULL;
        }

        for(j = 0; j < m; j++){
            p->tab[i][j].x = i;
            p->tab[i][j].y = j;
            p->tab[i][j].valeur = 0;
        }
    }
    printf("L'initialisation est terminée\n");
    return p;
}

cases *initialisation_cases(int x, int y, int valeur){
    cases *c = NULL;

    if((c = (cases *) malloc ( sizeof(cases))) == NULL){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire d'une case\n");
        free(c);
        return NULL;
    }

    c->x = x;
    c->y = y;
    c->valeur = valeur;

    printf("L'initialisation de la case est terminée\n");
    return c;
}

plateau *initialisation_aleatoire(plateau *p){
    int i, j;

    for(i = 0; i < 3; i++){
        for(j = 0; j < p->m; j++){
            p->tab[i][j].valeur = rand() % (9 - 1 + 1) + 1;
        }
    }

    return p;
}