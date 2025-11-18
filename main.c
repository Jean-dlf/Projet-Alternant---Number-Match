
/*main.c*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "initialisation.h"
#include "plateau.h"
#include "jeu.h"
#include "deroulement.h"
#include "gestion_menu.h"

/* Le main est vide, il contient simplement les valeurs dont on a besoin, ici le nombre de lignes et de colonnes du plateau et le plateau */
int main(){

    MLV_create_full_screen_window("NUMBER MATCH", "NUMBER MATCH", LX, LY);

    srand(time(NULL));

    /* On appelle la fonction qui fait fonctionner le jeu */
    gestion();

    MLV_free_window();

    exit(EXIT_SUCCESS);
}