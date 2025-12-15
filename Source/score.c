#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/mlv.h"
#include "../Headers/types.h"
#include "../Headers/menu.h"

#define MAX_SCORE 10

/* Convertie le temps en minutes secondes */
void convert_seconds_to_minutes(double t, int *m, int *s){
    *m = (int)t / 60;
    *s = (int)t % 60;
}

/* Converti le temps en secondes */
double convert_mmss_to_seconds(int m, int s){
    return m * 60 + s;
}


/* Lecture des meilleurs scores */
int load_score(char *name_f, tparti t_player){
    FILE *f = NULL;
    int i, minutes, seconds;

    /* Ouverture du fichier */
    if((f = fopen(name_f, "r")) == NULL){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier f\n");
        return -1;
    }

    /* Lecture des meilleurs scores */
    for(i = 0; i < MAX_SCORE; i++){
        if(fscanf(f, "%10s %d %d:%d", t_player[i].name_player, &t_player[i].score, &minutes, &seconds) != 4){
            fprintf(stderr, "Erreur lecture tableau score\n");
            fclose(f);
            return -1;
        }

        t_player[i].time_elapsed = convert_mmss_to_seconds(minutes, seconds);
    }

    fclose(f);
    return 1;
}

/* Ecrit les meilleurs scores dans un fichier score */
int save_score(char *name_f, tparti t_player, int nb_score){
    FILE *f = NULL;
    int i, minutes, seconds;

    /* Ouverture fichier */
    if((f = fopen(name_f, "w")) == NULL){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier f\n");
        return -1;
    }

    /* Ecrit les noms des joueurs, le score, et le timer */
    for(i = 0; i < nb_score; i++){
        convert_seconds_to_minutes(t_player[i].time_elapsed, &minutes, &seconds);
        
        fprintf(f, "%s %d %02d:%02d\n", t_player[i].name_player, t_player[i].score, minutes, seconds);
    }

    fclose(f);
    return 1;
}

/* Récupère tous les meilleurs scores */
int collect_score(char *name_f, tparti t_player){
    FILE *f = NULL;
    int i, minutes, seconds;

    if((f = fopen(name_f, "r")) == NULL){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", name_f);
        return -1;
    }

    for(i = 0; i < LENGTH_TP; i++){
        if(fscanf(f, "%10s %d %d:%d", t_player[i].name_player, &t_player[i].score, &minutes, &seconds) != 4){
            fprintf(stderr, "Erreur lors de la récupération\n");
            fclose(f);
            return -1;
        }

        t_player[i].time_elapsed = convert_mmss_to_seconds(minutes, seconds);
    }
   
    fclose(f);
    return 1;
}

/* Renvoie le meilleur score d'un plateau */
int get_best_score(int difficulty){
    tparti t_player;
    char *files[4] = {"./Save/score1.txt", "./Save/score2.txt", "./Save/score3.txt", "./Save/score4.txt"};

    if(difficulty < 0 || difficulty > 3){
        return -1;
    }

    if(collect_score(files[difficulty], t_player) == -1){
        return -1;
    }

    return t_player[0].score;
}


/* Met à jour les scores */
int update_high_scores(parti player){
    tparti t_player;
    int i, j, inserted;
    char *name_files_score[4] = {"./Save/score1.txt", "./Save/score2.txt", "./Save/score3.txt", "./Save/score4.txt"};

    inserted = 0;

    if(player.difficulty < 0 || player.difficulty > 3){
        return 0;
    }
   
    if(collect_score(name_files_score[player.difficulty], t_player) == -1){
        fprintf(stderr, "Erreur lors de la récupération des scores\n");
        return -1;
    }

    for(i = 0; i < LENGTH_TP; i++){
        
        if(player.score > t_player[i].score || (player.score == t_player[i].score && player.time_elapsed < t_player[i].time_elapsed)){
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