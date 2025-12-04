#include <stdlib.h>
#include <stdio.h>
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


/* Version graphique */
int game_graphic(plateau *p, int n, int m, parti *player_s, int mode){
    int pts, nb_ajt_lig, nb_ind_cpl, loose_i, size;
    int *empty_tab = NULL;
    int mx, my, pressed;
    plateau *tmp;
    button t_bouton_game[3];
    l_cases *l_c;
    cases *c1 = NULL, *c2 = NULL;
    parti player;

    if(player_s && p){
        player = *player_s;
        nb_ajt_lig = player.bonus_add_lines;
        nb_ind_cpl = player.bonus_clue;
        p->mode = mode;
    } else {
        p = initialisation_plateau(n, m);
        p->mode = mode;
        random_initialisation(p);
    }

    player = *player_s;

    nb_ajt_lig = player.bonus_add_lines;
    nb_ind_cpl = player.bonus_clue;
    
    display_plateau_mlv(p, t_bouton_game);
    MLV_actualise_window();
    
    loose_i = 0;
    
    while(p->n != 0 && loose_i == 0){

        MLV_wait_mouse(&mx, &my);
        pressed = clic_button(t_bouton_game, 3, mx, my);

        if(pressed == 0 && nb_ajt_lig > 0){
            tmp = bonus_add_lines(p);
            if(tmp != p){
                free_plateau(p);
                p = tmp;
            }
            nb_ajt_lig--;
        } 
        else if (pressed == 1 && nb_ind_cpl > 0){
            bonus_clue(p);
            nb_ind_cpl--;
        } else if (pressed == 2){
            if(pause_game(&player, p) == 0){
                if(player_s){
                    *player_s = player;
                }
                free_plateau(p);
                printf("Partie quittée depuis le menu pause\n");
                return -1;
            }
        } else{
            c1 = get_details(p, mx, my);

            if(c1 != NULL){
                MLV_wait_mouse(&mx, &my);
                c2 = get_details(p, mx, my);

                if(c2 != NULL && c1 != c2){
                    l_c = initialisation_l_cases(c1, c2);
                    if(l_c){
                        if(match(l_c, p)){
                            reset(p, *l_c);
                            pts = points_for_match(l_c);
                            player.score += pts;

                            empty_tab = empty_lines(p, &size);
                            if(size > 0 && empty_tab){
                                delete_empty_lines(p, empty_tab, size);
                            }
                            if(empty_tab){
                                free(empty_tab);
                                empty_tab = NULL;
                            }
                        }
                        if(l_c){
                            free(l_c->c);
                            free(l_c);
                            l_c = NULL;
                        }
                    }
                }
            }
        }

        display_plateau_mlv(p, t_bouton_game);
        MLV_actualise_window();

        if(loose(p, nb_ajt_lig)){
            printf("Vous avez perdu\n");
            printf("Score final : %d\n", player.score);

            player.score += add_point_for_bonus(player);

            printf("Score final après ajout bonus : %d\n", player.score);

            update_high_scores(player);
            
            player.bonus_add_lines = nb_ajt_lig;
            player.bonus_clue = nb_ind_cpl;
            *player_s = player;

            return 0;
        }
    }

    printf("Félicitations ! Score : %d\n", player.score);

    player.bonus_add_lines = nb_ajt_lig;
    player.bonus_clue = nb_ind_cpl;
    *player_s = player;

    return 1;
}
