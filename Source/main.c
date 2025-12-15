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

int main(){

    /* Affichage de la fenêtre */
    MLV_create_full_screen_window("NUMBER MATCH", "NUMBER MATCH", LX, LY);

    srand(time(NULL));

    /* On appelle la fonction qui fait fonctionner le jeu */
    management();

    /* Libération de la fenêtre */
    MLV_free_window();

    exit(EXIT_SUCCESS);
}