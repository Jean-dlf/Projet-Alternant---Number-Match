#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include <time.h>
#include "../Headers/menu.h"
#include "../Headers/types.h"
#include "../Headers/initialisation.h"
#include "../Headers/game_logic.h"
#include "../Headers/game.h"
#include "../Headers/save.h"
#include "../Headers/plateau_mlv.h"

void management(){
    plateau *p = NULL;
    int n = 10, m = 10;
    button t_menu_p[5], t_menu_s[5], back;
    char *nom_save[4] = {"save1.txt", "save2.txt", "save3.txt", "save4.txt"};
    int pressed, mx, my, c_save, mode_game;
    parti plyr;
    
    menu_p(t_menu_p);
    MLV_actualise_window();

    while(1){
        MLV_wait_mouse(&mx, &my);
        pressed = clic_button(t_menu_p, 5, mx, my);

        switch(pressed){
            
            /* ----------  JEU  ---------- */
            case 0:
                mode_game = choice_mode_game();
                if(mode_game == 0 || mode_game == 1){
                    game_graphic(p, n, m, NULL, mode_game);
                } else {
                    menu_p(t_menu_p);
                    MLV_actualise_window();
                }

                menu_p(t_menu_p);
                MLV_actualise_window();
                /* Retour au menu principal */
                break;

            /* ----------  MENU SAUVEGARDES  ---------- */
            case 1:

                menu_save(t_menu_s);
                MLV_actualise_window();

                c_save = 1;
                
                while(c_save){
                    MLV_wait_mouse(&mx, &my);
                    pressed = clic_button(t_menu_s, 5, mx, my);

                    if(pressed == -1){
                        c_save = 1;
                    }

                    if(pressed >= 0 && pressed < 4){
                        /* Charger le fichier cliqué */
                        printf("Save %s\n", nom_save[pressed]);

                        if(load_save(nom_save[pressed], &plyr, &p) == 1){
                            printf("Score chargé : %d\n", plyr.score);
                            game_graphic(p, p->n, p->m, &plyr, 0);
                            MLV_clear_window(MLV_COLOR_BEIGE);
                            menu_p(t_menu_p);
                            MLV_actualise_window();
                            c_save = 0;
                            
                        } else {
                            printf("Pas de sauvegarde\n");
                        }

                    }

                    if (pressed == 4) {
                        printf("Retour menu principal\n");
                        c_save = 0;
                    }
                }
                menu_p(t_menu_p);
                MLV_actualise_window();
                break;

            /* ----------  MENU REGLES  ---------- */
            case 2:

                menu_rules(&back);
                MLV_actualise_window();

                MLV_wait_mouse(&mx, &my);
                clic_button(&back, 1, mx, my);

                menu_p(t_menu_p);
                MLV_actualise_window();            
                break;

            /* ----------  MENU SCORE  ---------- */
            case 3:

                menu_score(&back);
                MLV_actualise_window();

                MLV_wait_mouse(&mx, &my);
                clic_button(&back, 1, mx, my);

                menu_p(t_menu_p);
                MLV_actualise_window();            
                break;

            /* ----------  QUITTER  ---------- */
            case 4:

                return ;

        default:
            break;
        }
    }
}