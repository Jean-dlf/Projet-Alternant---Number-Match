#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../Headers/types.h"

void display_plateau(plateau *p){
    int i, j;

    printf("      ");
    for(i = 0; i < p->m; i++){
        printf("%d   ", i);
    }
    printf("\n");
    for(i = 0; i < p->n; i++){
        printf("%d - ", i);
        for(j = 0; j < p->m; j++){
            printf("| %d ", p->tab[i][j].value);
        }
        printf("| \n");
    }
}

void free_plateau(plateau *p){
    int i;

    for(i = 0; i < p->n; i++){
        free(p->tab[i]);
    }
    free(p->tab);
    free(p);
}