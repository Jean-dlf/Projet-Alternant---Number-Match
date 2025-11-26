#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "game_logic.h"
#include "initialisation.h"
#include "plateau.h"
#include "plateau_mlv.h"
#include "save.h"

void game(plateau *p, int n, int m, int save, parti *player_s){
    int *tab_vide = NULL;
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

        initialisation_aleatoire(p);
    } else {
        printf("Partie chargée : %d x %d\n", p->n, p->m);
        player = *player_s;
        nb_ajt_lig = player.bonus_add_lines;
        nb_ind_cpl = player.bonus_clue;
    }

    display_plateau(p);
    display_plateau_mlv(p);

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

            tab_vide = empty_lines(p, &size);
            if(size != 0){
                delete_empty_lines(p, tab_vide, size);
            }

            if(tab_vide != NULL){
                free(tab_vide);
                tab_vide = NULL;
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
                if(use_clue(p)/* && compte_indice_couple(nb_ind_cpl) != -1*/){
                    nb_ind_cpl -= 1;
                }
            } else {
                printf("Vous n'avez plus d'utilisation de bonus d'indice de couple possible\n");
            }

            display_plateau(p);

            if(loose(p, nb_ajt_lig, nb_ind_cpl)){
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