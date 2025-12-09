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
#include "../Headers/plateau.h"

void management(){
    plateau *p = NULL;
    plateau p_custom;
    int n = 0, m = 0;
    button t_menu_p[4], t_menu_s[5], t_menu_level[6], next;
    char *nom_save[4] = {"./Save/save1.txt", "./Save/save2.txt", "./Save/save3.txt", "./Save/save4.txt"};
    int pressed, mx, my, c_save, mode_game, res, pn, pm, back_menu;
    parti plyr;
    
    menu_p(t_menu_p);
    MLV_actualise_window();

    while(1){
        MLV_wait_mouse(&mx, &my);
        pressed = clic_button(t_menu_p, 4, mx, my);

        switch(pressed){
            
            /* ----------  JEU  ---------- */
            case 0:
            do{ 
                    mode_game = choice_mode_game();
                    if(mode_game == 0){

                        menu_rules_classic(&next);
                        MLV_actualise_window();
                        pressed = -1;
                        while(pressed == -1){
                            MLV_wait_mouse(&mx, &my);
                            pressed = clic_button(&next, 1, mx, my);
                        }

                        MLV_actualise_window();

                    } else if(mode_game == 1){

                        menu_rules_locksmith(&next);
                        MLV_actualise_window();

                        pressed = -1;
                        while(pressed == -1){
                            MLV_wait_mouse(&mx, &my);
                            pressed = clic_button(&next, 1, mx, my);
                        }

                        MLV_actualise_window();

                    } else if(mode_game == 2){
                        menu_p(t_menu_p);
                        MLV_actualise_window();
                        back_menu = 1;
                        break;
                    } else {
                        mode_game = -1;
                    }
                } while(mode_game == -1);

                if(back_menu){
                    back_menu = 0;
                    break;
                }

                menu_ask_difficulty(t_menu_level, CUSTOM);                        
                MLV_actualise_window();

                plyr.score = 0;
                plyr.bonus_add_lines = 3;
                plyr.bonus_clue = 3;

                do{
                    MLV_wait_mouse(&mx, &my);
                    pressed = clic_button(t_menu_level, 6, mx, my);
                } while(pressed < 0);

                if(pressed == 5){
                    menu_p(t_menu_p);
                    MLV_actualise_window();
                    break;
                }
                      
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
                        menu_customised_dimensions(&p_custom);

                        n = p_custom.n;
                        m = p_custom.m;
                        plyr.difficulty = 4;
                        break;

                }

                ask_name(&plyr);
                
                do {
                    res = game_graphic(NULL, n, m, &plyr, mode_game);
                } while(res == 1);

                if(res == 0){
                    recap_game(plyr);
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

                menu_score();
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