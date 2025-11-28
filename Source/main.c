#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "../Headers/types.h"
#include "../Headers/initialisation.h"
#include "../Headers/plateau.h"
#include "../Headers/game_logic.h"
#include "../Headers/game.h"
#include "../Headers/menu_management.h"

/* Le main est vide, il contient simplement les valeurs dont on a besoin, ici le nombre de lignes et de colonnes du plateau et le plateau */
int main(){

    MLV_create_window("NUMBER MATCH", "NUMBER MATCH", LX, LY);

    srand(time(NULL));

    /* On appelle la fonction qui fait fonctionner le jeu */
    management();

    MLV_free_window();

    exit(EXIT_SUCCESS);
}