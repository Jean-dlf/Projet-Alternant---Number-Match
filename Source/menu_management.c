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
    int n = 3, m = 6;
    button t_menu_p[4], t_menu_s[5], t_menu_level[5], back;
    char *nom_save[4] = {"./Save/save1.txt", "./Save/save2.txt", "./Save/save3.txt", "./Save/save4.txt"};
    int pressed, mx, my, c_save, mode_game, res, pn, pm;
    parti plyr;
    
    menu_p(t_menu_p);
    MLV_actualise_window();

    while(1){
        MLV_wait_mouse(&mx, &my);
        pressed = clic_button(t_menu_p, 4, mx, my);

        switch(pressed){
            
            /* ----------  JEU  ---------- */
            case 0:
                mode_game = choice_mode_game();
                if(mode_game == 0 || mode_game == 1){
                    if(mode_game == 0){
                        menu_rules_classic(&back);
                        MLV_actualise_window();
                        MLV_wait_mouse(&mx, &my);
                        clic_button(&back, 1, mx, my);
                        menu_ask_difficulty(t_menu_level);
                    }
                    else {
                        menu_rules_locksmith(&back);
                        MLV_actualise_window();
                        MLV_wait_mouse(&mx, &my);
                        clic_button(&back, 1, mx, my);
                        menu_ask_difficulty(t_menu_level);
                    }
                    plyr.score = 0;
                    plyr.bonus_add_lines = 3;
                    plyr.bonus_clue = 3;
                    menu_ask_difficulty(t_menu_level);
                    MLV_actualise_window();
                    MLV_wait_mouse(&mx, &my);
                    pressed = clic_button(t_menu_level, 6, mx, my);
                    if(pressed >= 0 && pressed < 4){
                        ask_name(&plyr);
                        
                        switch(pressed){
                        case 0:
                            n = 6;
                            m = 6;
                            plyr.difficulty = 0;
                            break;
                        case 1:
                            n = 8;
                            m = 8;
                            plyr.difficulty = 1;
                            break;
                        case 2:
                            n = 6;
                            m = 10;
                            plyr.difficulty = 2;
                            break;
                        case 3:
                            n = 8;
                            m = 6;
                            plyr.difficulty = 3;
                            break;
                            
                        case 4:
                            menu_p(t_menu_p);
                            MLV_actualise_window();
                            break;
                        }
                        
                        printf("%s / %d / %d / %d / %d / %d\n", plyr.name_player, plyr.bonus_add_lines, plyr.bonus_clue, plyr.difficulty, plyr.score, plyr.score_max);
                        res = game_graphic(p, n, m, &plyr, mode_game);
                        
                        while(res == 1){
                            res = game_graphic(p, n, m, &plyr, mode_game);
                        }
                        if(res == 0){
                            recap_game(plyr);
                        }
                    }
                }
                menu_p(t_menu_p);
                MLV_actualise_window();
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
                            pn = p->n;
                            pm = p->m;
                            mode_game = p->mode;

                            printf("Score chargé : %d\n", plyr.score);
                            res = game_graphic(p, pn, pm, &plyr, mode_game);
                            p = NULL;

                            while(res == 1){
                                res = game_graphic(NULL, pn, pm, &plyr, mode_game);
                            }
                            if(res == 0){
                                recap_game(plyr);
                            }
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

            /* ----------  MENU SCORE  ---------- */
            case 2:

                menu_score(&back);
                MLV_actualise_window();

                menu_p(t_menu_p);
                MLV_actualise_window();            
                break;

            /* ----------  QUITTER  ---------- */
            case 3:

                return ;

        default:
            break;
        }
    }
}