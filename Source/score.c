#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/mlv.h"
#include "../Headers/types.h"
#include "../Headers/menu.h"

#define MAX_SCORE 10

int load_score(char *name_f, tparti t_player){
    FILE *f = NULL;
    int i;

    if((f = fopen(name_f, "r")) == NULL){
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

int save_score(char *name_f, tparti t_player, int nb_score){
    FILE *f = NULL;
    int i;

    if((f = fopen(name_f, "w")) == NULL){
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
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", name_f);
        return -1;
    }

    for(i = 0; i < LENGTH_TP; i++){
        if(fscanf(f, "%10s %d", t_player[i].name_player, &t_player[i].score) != 2){
            fprintf(stderr, "Erreur lors de la récupération\n");
            fclose(f);
            return -1;
        }
    }
    fclose(f);
    return 1;
}

int update_high_scores(parti player){
    tparti t_player;
    int i, j, inserted;
    char *name_files_score[4] = {"./Save/score1.txt", "./Save/score2.txt", "./Save/score3.txt", "./Save/score4.txt"};

    inserted = 0;

    if(player.difficulty < 0 || player.difficulty > 3){
        return 0;
    }
    
    printf("%d\n", player.difficulty);
    if(collect_score(name_files_score[player.difficulty], t_player) == -1){
        fprintf(stderr, "Erreur lors de la récupération des scores\n");
        return -1;
    }

    for(i = 0; i < LENGTH_TP; i++){
        if(player.score > t_player[i].score){
            for(j = LENGTH_TP - 1; j > i; j--){
                t_player[j] = t_player[j-1];
            }
            t_player[i] = player;
            inserted = 1;
            break;
        }
    }

    if(inserted){
        if(save_score(name_files_score[player.difficulty], t_player, LENGTH_TP) == -1){
            fprintf(stderr, "Erreur lors de la sauvegarde des scores\n");
            return -1;
        }
    }
    return 1;
}