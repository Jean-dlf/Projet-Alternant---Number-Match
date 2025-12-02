#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/mlv.h"
#include "../Headers/types.h"

#define MAX_SCORE 10

int load_score(tparti t_player){
    FILE *f = NULL;
    int i;

    if((f = fopen("./Save/score.txt", "r")) == NULL){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier f\n");
        return -1;
    }

    for(i = 0; i < MAX_SCORE; i++){
        if(fscanf(f, "%10s %d", t_player[i].name_player, &t_player[i].score) != 2){
            fprintf(stderr, "Erreur lecture tableau score\n");
            fclose(f);
            return -1;
        }   
    }

    fclose(f);
    return 1;
}

int save_score(tparti t_player, int nb_score){
    FILE *f = NULL;
    int i;

    if((f = fopen("./Save/score.txt", "w")) == NULL){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier f\n");
        return -1;
    }

    for(i = 0; i < nb_score; i++){
        fprintf(f, "%s %d\n", t_player[i].name_player, t_player[i].score);
    }

    fclose(f);
    return 1;
}

int collect_score(char *name_f, tparti t_player){
    FILE *f = NULL;
    int i;

    if((f = fopen(name_f, "r")) == NULL){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier f\n");
        return -1;
    }

    for(i = 0; i < LENGTH_TP; i++){
        if(fscanf(f, "%10s %d", t_player[i].name_player, &t_player[i].score) != 2){
            fprintf(stderr, "Erreur lors de la récupération\n");
            fclose(f);
            return -1;
        }
        printf("collect_score %d %s\n", t_player[i].score, t_player[i].name_player);
    }
    fclose(f);
    return 1;
}

int change_player_score(parti *plyr1, parti *plyr2){
    parti plyr_tmp;
    plyr_tmp.score = 0;

    if((strcpy(plyr_tmp.name_player, plyr1->name_player)) == NULL ){
        fprintf(stderr, "Erreur lors du deplacement\n");
        return -1;
    }
    plyr_tmp.score = plyr1->score;

    if((strcpy(plyr1->name_player, plyr2->name_player)) == NULL){
        fprintf(stderr, "Erreur lors du deplacement\n");
        return -1;
    }
    
    plyr1->score = plyr2->score;

    if((strcpy(plyr2->name_player, plyr_tmp.name_player)) == NULL){
        fprintf(stderr, "Erreur lors du deplacement\n");
        return -1;
    }
    plyr2->score = plyr_tmp.score;
    
    return 1;
}

int tri_insertion(char *name_f, parti new_score, tparti t_player){
    FILE *f;
    int i, j;

    if((f = fopen(name_f, "w")) == NULL){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier f\n");
        return -1;
    }

    for(i = 0; i < 10; i++){
        if(new_score.score_max > t_player[i].score_max){
            for(j = 9; j > i; j--){
                if(change_player_score(&t_player[i + 1], &t_player[i]) == -1){
                    fprintf(stderr, "Erreur lors du déplacement de score\n");
                    return -1;
                }
            }

            if(change_player_score(&t_player[i], &new_score) == -1){
                fprintf(stderr, "Erreur lors du déplacement de score\n");
                return -1;
            }
        }
    }

    for(i = 0; i < LENGTH_TP; i++){
        fprintf(f, "%s %d\n", t_player[i].name_player, t_player->score);
    }

    fclose(f);
    return 1;
}