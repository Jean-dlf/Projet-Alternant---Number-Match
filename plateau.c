#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include <time.h>

void afficher_plateau(plateau *p){
    int i, j;

    for(i = 0; i < p->n; i++){
        for(j = 0; j < p->m; j++){
            printf("| %d ", p->tab[i][j].valeur);
        }
        printf("| \n");
    }
}
