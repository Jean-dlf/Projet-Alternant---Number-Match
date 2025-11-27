#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include <time.h>
#include "menu.h"
#include "types.h"
#include "initialisation.h"
#include "game_logic.h"
#include "game.h"
#include "save.h"
#include "plateau_mlv.h"

void management(){
    plateau *p = NULL;
    int n = 10, m = 10;
    button t_menu_p[5], t_menu_s[5], back;
    char *nom_save[4] = {"save1.txt", "save2.txt", "save3.txt", "save4.txt"};
    int pressed;
    int back_menu_p = 1;
    parti j;
    
    menu_p(t_menu_p);

    while(back_menu_p == 1){
        menu_p(t_menu_p);
        pressed = clic_button(t_menu_p, 5);
        switch(pressed){
            
            /* Lancement du jeu */
            case 0:
            printf("Jeu\n");
            /*afficher_plateau_mlv(p);*/
            /*game_term(p, n, m, 1, NULL);*/
            game_graphic(p, n, m);
            back_menu_p = 0;
            break;

            /* Menu sauvegarde */
            case 1:
            printf("Menu sauvegarde\n");
            menu_save(t_menu_s);

            while(back_menu_p == 1){
                pressed = clic_button(t_menu_s, 5);

                if(pressed < 4){
                    printf("Save %s\n", nom_save[pressed]);


                    if(load_save(nom_save[pressed], &j, &p) == 1){
                        printf("Score chargé : %d\n", j.score);
                        game_term(p, p->n, p->m, 0, &j);
                        back_menu_p = 0;
                    } else {
                        printf("Pas de sauvegarde\n");
                        back_menu_p = 0;
                    }
                } else if(pressed == 4){
                    printf("Menu Principal\n");
                    back_menu_p = 0;
                }
            }
            break;

            /* Menu règles */
            case 2:
            printf("Menu règles\n");
            menu_rules(&back);
            pressed = clic_button(&back, 1);
            if(pressed == 0){
                printf("Menu Principal\n");
                back_menu_p = 0;
            }
            break;

            /* Menu score */
            case 3:
            printf("Menu score\n");
            menu_score(&back);
            pressed = clic_button(&back, 1);
            if(pressed == 0){
                printf("Menu Principal\n");
                back_menu_p = 0;
            }
            break;

            /* Exit lors du menu */
            case 4:
            printf("Au revoir\n");
            return ;
        }
        back_menu_p = 1;
    }
}