#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "types.h"
#include "initialisation.h"
#include "plateau.h"
#include "jeu.h"
#include "deroulement.h"

/* Le main est vide, il contient simplement les valeurs dont on a besoin, ici le nombre de lignes et de colonnes du plateau et le plateau */
int main(){
    
    int n = 5;
    int m = 6;
    plateau *p = NULL;

    srand(time(NULL));

    /* On appelle la fonction qui fait fonctionner le jeu */
    deroulement(p, n, m);

    exit(EXIT_SUCCESS);
}