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

/* Fonction fonctionnement des menus -- fonctionnement du jeu complet */
void management(){
    plateau *p = NULL;
    plateau p_custom;
    int n = 0, m = 0;
    button t_menu_p[4], t_menu_s[5], t_menu_level[6], next;
    char *nom_save[4] = {"./Save/save1.txt", "./Save/save2.txt", "./Save/save3.txt", "./Save/save4.txt"};
    int pressed, mx, my, c_save, mode_game, res, pn, pm, back_menu;
    parti plyr;
    
    /* Affichage du menu principal */
    menu_p(t_menu_p);
    MLV_actualise_window();

    /* Boucle de fonctionnement des menus */
    while(1){
        
        /* Attend la sélection d'un bouton du menu principal */
        MLV_wait_mouse(&mx, &my);
        pressed = clic_button(t_menu_p, 4, mx, my);

        /* Choix de sélection des boutons */
        switch(pressed){
            
            /* ----------  JEU  ---------- */
            case 0:
            do{ 
                    /* Choix du mode de jeu */
                    mode_game = choice_mode_game();

                    /* Mode de jeu classique */
                    if(mode_game == 0){

                        /* Affichage des règles */
                        menu_rules_classic(&next);
                        MLV_actualise_window();
                        pressed = -1;
                        while(pressed == -1){
                            MLV_wait_mouse(&mx, &my);
                            pressed = clic_button(&next, 1, mx, my);
                        }
                        MLV_actualise_window();

                    /* Mode de jeu Serrurier */
                    } else if(mode_game == 1){

                        /* Affichage des règles */
                        menu_rules_locksmith(&next);
                        MLV_actualise_window();
                        pressed = -1;
                        while(pressed == -1){
                            MLV_wait_mouse(&mx, &my);
                            pressed = clic_button(&next, 1, mx, my);
                        }
                        MLV_actualise_window();

                    /* Retour au menu principal */
                    } else if(mode_game == 2){
                        menu_p(t_menu_p);
                        MLV_actualise_window();
                        back_menu = 1;
                        break;

                    /* Si aucun bouton appuyé */
                    } else {
                        mode_game = -1;
                    }
                } while(mode_game == -1);

                /* Permet de revenir au menu principal */
                if(back_menu){
                    back_menu = 0;
                    break;
                }

                /* Menu de choix de la difficulté */
                menu_ask_difficulty(t_menu_level, CUSTOM);                        
                MLV_actualise_window();

                /* Initialisation des données du joueur */
                plyr.score = 0;
                plyr.bonus_add_lines = 3;
                plyr.bonus_clue = 3;
                plyr.time_elapsed = 0.0;

                /* Attend ddu choix de la difficulté */
                do{
                    MLV_wait_mouse(&mx, &my);
                    pressed = clic_button(t_menu_level, 6, mx, my);
                } while(pressed < 0);

                /* Si retour au menu principal sélectionné */
                if(pressed == 5){
                    menu_p(t_menu_p);
                    MLV_actualise_window();
                    break;
                }
                      
                /* Différent choix de la sélection */
                switch(pressed){

                    /* Taille 6 x 6 */
                    case 0:
                        n = 6;
                        m = 6;
                        plyr.difficulty = 0;
                        break;

                    /* Taille 8 x 8 */
                    case 1:
                        n = 8;
                        m = 8;
                        plyr.difficulty = 1;
                        break;

                    /* Taille 6 x 10 */
                    case 2:
                        n = 6;
                        m = 10;
                        plyr.difficulty = 2;
                        break;

                    /* Tille 8 x 6 */
                    case 3:
                        n = 8;
                        m = 6;
                        plyr.difficulty = 3;
                        break;

                    /* Choix de difficulté personnalisé */
                    case 4:
                        /* Demande des dimensions du plateau */
                        menu_customised_dimensions(&p_custom);

                        /* Ajout de la taille inscrite */
                        n = p_custom.n;
                        m = p_custom.m;
                        plyr.difficulty = 4;
                        break;

                }

                /* Demande le nom du joueur */
                ask_name(&plyr);
                
                /* Boucle de jeu tant que le joueur ne perd pas */
                do {
                    res = game_graphic(NULL, n, m, &plyr, mode_game);
                } while(res == 1);

                /* Si perdu on lui affiche son récapitulatif */
                if(res == 0){
                    recap_game(plyr);
                }    
                                
                /* Retour au menu principal */
                menu_p(t_menu_p);
                MLV_actualise_window();
                
                break;
                
                /* ----------  MENU SAUVEGARDES  ---------- */
            case 1:

                /* Affichage menu principal */
                menu_save(t_menu_s);
                MLV_actualise_window();

                c_save = 1;
                
                /* Boucle menu sauvegarde */
                while(c_save){
                    MLV_wait_mouse(&mx, &my);
                    pressed = clic_button(t_menu_s, 5, mx, my);

                    /* Si rien sélectionné */
                    if(pressed == -1){
                        c_save = 1;
                    }

                    /* Si un bouton a été appuyé */
                    if(pressed >= 0 && pressed < 4){
                        /* Charger le fichier cliqué */

                        /* On charge la sauvegarde chosiie si non vide */
                        if(load_save(nom_save[pressed], &plyr, &p) == 1){
                            pn = p->n;
                            pm = p->m;
                            mode_game = p->mode;

                            /* Lancement de la partie chargée */
                            res = game_graphic(p, pn, pm, &plyr, mode_game);
                            p = NULL;

                            /* Si pas perdu on relance une nouvelle partie */
                            while(res == 1){
                                res = game_graphic(NULL, pn, pm, &plyr, mode_game);
                            }

                            /* Si perdu récapitulatif */
                            if(res == 0){
                                recap_game(plyr);
                            }

                            /* Menu Principal */
                            MLV_clear_window(MLV_COLOR_BEIGE);
                            menu_p(t_menu_p);
                            MLV_actualise_window();
                            c_save = 0;
                            
                        /* Aucune sauvegarde dans le fichier */
                        } else {
                            printf("Pas de sauvegarde\n");
                        }

                    }

                    /* On retour au menu principal */
                    if (pressed == 4) {
                        c_save = 0;
                    }
                }

                /* Affichage du menu principal */
                menu_p(t_menu_p);
                MLV_actualise_window();
                break;

            /* ----------  MENU SCORE  ---------- */
            case 2:

                /* Affichage du menu des scores */
                menu_score();
                MLV_actualise_window();

                /* Menu Principal */
                menu_p(t_menu_p);
                MLV_actualise_window();            
                break;

            /* ----------  QUITTER  ---------- */
            case 3:

                /* On quitte le jeu */
                return ;

        default:
            break;
        }
    }
}