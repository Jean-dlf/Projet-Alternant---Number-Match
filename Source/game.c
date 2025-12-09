#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../Headers/types.h"
#include "../Headers/game_logic.h"
#include "../Headers/initialisation.h"
#include "../Headers/plateau.h"
#include "../Headers/plateau_mlv.h"
#include "../Headers/save.h"
#include "../Headers/mlv.h"
#include "../Headers/menu.h"
#include "../Headers/score.h"

void game_term(plateau *p, int n, int m, int save, parti *player_s){
    int *empty_tab = NULL;
    int size, pts, i, nb_ajt_lig, nb_ind_cpl, valid, loose_i;
    l_cases l_c;
    plateau *new_p;
    char name_player[80];
    parti player;

    loose_i = 0;

    if(save){
        /*printf("Entrez votre nom de player : ");
        if(scanf("%79s", name_player) != 1){
            fprintf(stderr, "Erreur lecture nom player\n");
            return ;
        }

        viderBuffer();
        player = initialiser_score(name_player);*/

        p = initialisation_plateau(n, m);
        if(p == NULL){
            fprintf(stderr,"Erreur initialisation plateau\n");
            return ;
        }

        nb_ajt_lig = 3;
        nb_ind_cpl = 3;

        random_initialisation(p);
    } else {
        printf("Partie chargée : %d x %d\n", p->n, p->m);
        player = *player_s;
        nb_ajt_lig = player.bonus_add_lines;
        nb_ind_cpl = player.bonus_clue;
    }

    display_plateau(p);

    while(p->n != 0 && loose_i == 0){
        printf("oui ou non : ");
        if (scanf("%79s", name_player) != 1) {
            fprintf(stderr, "Erreur lecture nom player\n");
            return;
        } else {
            /* si la première lettre est 'o' → on annule */
            if (name_player[0] == 'o' || name_player[0] == 'O') {
                printf("Partie annulée.\n");
                exit(EXIT_SUCCESS);
            } else {
                printf("oui\n");
            }
        }

        l_c = pair_list(p);

        if(match(&l_c, p)){
            reset(p, l_c);

            /* ajout des points pour ce match */
            pts = points_for_match(&l_c);
            player.score += pts;
            printf("+%d points ! Score actuel : %d\n", pts, player.score);

            empty_tab = empty_lines(p, &size);
            if(size != 0){
                delete_empty_lines(p, empty_tab, size);
            }

            if(empty_tab != NULL){
                free(empty_tab);
                empty_tab = NULL;
            }
        }

        display_plateau(p);

        if(!empty_plateau(p)){
            if(nb_ajt_lig > 0){
                new_p = use_add_lines(p, &valid);
                if(new_p != p){
                    p = new_p;
                }
                if(valid == 1/* && compte_ajout_ligne(nb_ajt_lig) != -1*/){
                    nb_ajt_lig -= 1;
                }
            } else {
                printf("Vous n'avez plus d'utilisation de bonus d'ajout de lignes possible\n");
            }

            if(nb_ind_cpl > 0){
                if(use_clue(p)){
                    nb_ind_cpl -= 1;
                }
            } else {
                printf("Vous n'avez plus d'utilisation de bonus d'indice de couple possible\n");
            }

            display_plateau(p);

            if(loose(p, nb_ajt_lig)){
                printf("Vous avez perdu\n");
                return ;
            }
        }

        printf("Nombre d'utilisation possible du bonus d'indice de couples : %d\n", nb_ind_cpl);
        printf("Nombre d'utilisation possible du bonus d'ajout de lignes : %d\n", nb_ajt_lig);
    }

    if(player.score > player.score_max){
        player.score_max = player.score;
        printf("Nouveau record ! %d points \n", player.score_max);
    }

    player.bonus_add_lines = nb_ajt_lig;
    player.bonus_clue = nb_ind_cpl;

    save_parti(player);

    /* Libération mémoire plateau */
    if(p != NULL){
        for(i = 0; i < p->n; i++){
            free(p->tab[i]);
        }
        free(p->tab);
        free(p);
        p = NULL;
    }

    printf("Vous avez gagné ! Score final : %d\n", player.score);
    return ;
}

/* -- Version Graphique -- */
int game_graphic(plateau *p, int n, int m, parti *player_s, int mode){

    /* ----- INITIALISATION ----- */

    int pts, nb_ajt_lig, nb_ind_cpl, loose_i, size, clue_active, free_p;
    int *empty_tab = NULL;
    int mx, my, pressed;
    plateau *tmp;
    button t_bouton_game[5];
    l_cases *l_c;
    cases *c1 = NULL, *c2 = NULL;
    parti *player;

    /* -- Variables utile pour le fonctionnement du chronomètre et la gestion des clics --*/
    time_t start_time, current_time;
    double elapsed;
    int waiting_second_click = 0; /* Indique si on attend le second click */
    MLV_Button_state mouse_state;
    MLV_Button_state last_state = MLV_RELEASED; /* Front montant du clic */
    cases *clicked; /* Case cliquée par l'utilisateur */

    free_p = 0;

    /* ----- INITIALISATION DU PLATEAU ----- */

    player = player_s;

    if(p == NULL){
        p = initialisation_plateau(n, m);
        p->mode = mode;
        random_initialisation(p);
        free_p = 1; /* Indique qu'on doit libérer le plateau à la fin */
    } else {
        p->mode = mode;
    }

    p->score_actuel = player->score;
    nb_ajt_lig = player->bonus_add_lines;
    nb_ind_cpl = player->bonus_clue;

    start_time = time(NULL); /* Début du chronomètre */
    elapsed = 0.0;

    display_plateau_mlv(p, t_bouton_game, elapsed);
    MLV_actualise_window();
    
    clue_active = 0;
    loose_i = 0;

    /* ----- BOUCLE PRINCIPALE DU JEU ----- */
    while(p->n != 0 && loose_i == 0){
        /* -- Mise à jour du temps écoulé -- */
        current_time = time(NULL);
        elapsed = difftime(current_time, start_time);

        /* -- Récupération de la position et l'état de la souris -- */
        MLV_get_mouse_position(&mx, &my);
        mouse_state = MLV_get_mouse_button_state(MLV_BUTTON_LEFT);
        pressed = -1; /* Valeur par défaut pour aucun bouton cliqué */

        /* -- Détection d'un front montant -- */
        if(mouse_state == MLV_PRESSED && last_state == MLV_RELEASED){
            pressed = clic_button(t_bouton_game, 5, mx, my); /* On vérifie si on clique sur un bouton du menu de la partie */

            /* ----- GESTION DES CASES ----- */
            clicked = get_details(p, mx, my);
            if(clicked != NULL && clicked->value != 0){
                if(!waiting_second_click){
                    /* -- 1ER CLIC -- */
                    if(c1 == clicked){
                        /* -- Si on reclique sur la même alors on la désélectionne -- */
                        c1->select = SELECT_NONE;
                        c1 = NULL;
                    } else {
                        /* -- Nouvelle sélection de case -- */
                        c1 = clicked;
                        c1->select = SELECT_USER;
                        waiting_second_click = 1;
                        c2 = NULL;
                    }
                } else {
                    /* -- 2ND CLIC -- */
                    c2 = clicked;
                    if(c2 == c1){
                        /* -- Désélection si clic sur la même case -- */
                        c1->select = SELECT_NONE;
                        c1 = NULL;
                        waiting_second_click = 0;
                    } else if(c2->value != 0){
                        /* -- Deuxième case cliqué, on vérifie le match en les 2 -- */
                        c2->select = SELECT_USER;
                        waiting_second_click = 0;

                        l_c = initialisation_l_cases(c1, c2);
                        if(l_c){
                            if(match(l_c, p)){
                                /* -- Il y a match -- */
                                reset(p, *l_c);
                                pts = points_for_match(l_c);
                                player->score += pts;
                                p->score_actuel = player->score;


                                empty_tab = empty_lines(p, &size);
                                if(size > 0 && empty_tab){
                                    delete_empty_lines(p, empty_tab, size);
                                }
                                if(empty_tab){
                                    free(empty_tab);
                                    empty_tab = NULL;
                                }
                            }
                            /* -- Désélection des cases après match ou non -- */
                            c1->select = SELECT_NONE;
                            c2->select = SELECT_NONE;

                            /* -- On libère l_c -- */
                            free(l_c->c);
                            free(l_c);
                            l_c = NULL;
                        }
                        /* -- On libère les 2 cases -- */
                        c1 = NULL;
                        c2 = NULL;
                    }
                }
            }
        }

        /* -- Mise à jour de l'état de la souris pour le front montant -- */
        last_state = mouse_state;

        /* ----- GESTION DU BONUS "INDICE" ACTIF ----- */
        if(clue_active && mouse_state == MLV_PRESSED && last_state == MLV_RELEASED){
            clicked = get_details(p, mx, my);
            if(clicked != NULL && clicked->value != 0){
                /* -- Utilisation du bonus ici -- */
                clicked->select = SELECT_CLUE;
                delete_bonus_clue(p);
                clue_active = 0;
            }
        }
        
        /* ----- GESTION DES BOUTONS DE BONUS ET DES FLECHES ----- */
        /* -- Flèche du haut -- */
        if(pressed == 0){
            offset--;
            if(offset < 0){
                offset = 0;
            }

        /* -- Flèche du base --*/
        } else if(pressed == 1){
            offset++;
            if(offset > p->n - VISIBLE){
                offset = p->n - VISIBLE;
            }
        
        /* -- Bonus ajout de ligne -- */
        } else if(pressed == 2 && nb_ajt_lig > 0){
            tmp = bonus_add_lines(p);
            if(tmp != p){
                if(free_p) free_plateau(p);
                p = tmp;
                free_p = 1;
            }
            nb_ajt_lig--;

        /* -- Bonus indice -- */
        } else if(pressed == 3 && nb_ind_cpl > 0){
            clue_active = bonus_clue(p);
            if(clue_active){
                nb_ind_cpl--;
                display_plateau_mlv(p, t_bouton_game, elapsed);
                MLV_actualise_window();
            }
        
        /* -- Pause -- */
        } else if(pressed == 4){
            if(pause_game(player, p) == 0){
                if(player_s){
                    player_s = player;
                }
                if(free_p){
                    free_plateau(p);
                }
                printf("Partie quittée depuis le menu pause\n");
                return -1;
            }
        } 

        /* -- Affichage du plateau -- */
        display_plateau_mlv(p, t_bouton_game, elapsed);
        MLV_actualise_window();

        /* ----- VERIFICATION DE LA DEFAITE ----- */
        if(loose(p, nb_ajt_lig)){
            player->score += add_point_for_bonus(*player);

            update_high_scores(*player);
            player->bonus_add_lines = nb_ajt_lig;
            player->bonus_clue = nb_ind_cpl;
            player_s = player;

            if(free_p){
                free_plateau(p);
            }
            return 0;
        }
    }

    /* ----- FIN DE PARTIE (VICTORIE PLATEAU VIDE) ----- */
    player->score += 100;
    player->bonus_add_lines = nb_ajt_lig;
    player->bonus_clue = nb_ind_cpl;

    /* -- On libère le plateau -- */
    if(free_p){
        free_plateau(p);
    }

    return 1;
}