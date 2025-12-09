#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Headers/types.h"
#include "../Headers/initialisation.h"

/*** Parti score et nom  ***/

int load_save(char *name_f, parti *plyr, plateau **p){
    FILE *f = NULL;
    int i, j, n, m, mode_tmp;

    if((f = fopen(name_f, "r")) == NULL){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier f\n");
        return -1;
    }

    if(fscanf(f, "%10s", plyr->name_player) != 1){
        fprintf(stderr, "Erreur lecture du nom du joueur\n");
        fclose(f);
        return -1;
    }

    if(fscanf(f, "%d %d %d %d %d %d", &plyr->score, &plyr->score_max, &plyr->bonus_add_lines, &plyr->bonus_clue, &mode_tmp, &plyr->difficulty) != 6){
        fprintf(stderr, "Erreur lecture informations du joueur\n");
        fclose(f);
        return -1;
    }

    if(fscanf(f, "%d %d", &n ,&m) != 2){
        fprintf(stderr, "Erreur lecture dimensions du plateau\n");
        fclose(f);
        return -1;
    }

    *p = initialisation_plateau(n, m);
    (*p)->mode = mode_tmp;
    (*p)->score_actuel = &plyr->score;
    
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            if(fscanf(f, "%d", &(*p)->tab[i][j].value) != 1){
                fprintf(stderr, "Erreur lecture de la case [%d][%d]\n", i, j);
                fclose(f);
                return -1;
            }
        }
    }

    fclose(f);
    return 1;
}

int save_game(char *name_f, parti *plyr, plateau *p){
    FILE *f;
    int i, j;

    if((f = fopen(name_f, "w")) == NULL){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", name_f);
        return -1;
    }

    fprintf(f, "%s\n", plyr->name_player);
    fprintf(f, "%d %d %d %d %d %d\n", plyr->score, plyr->score_max, plyr->bonus_add_lines, plyr->bonus_clue, p->mode, plyr->difficulty);

    fprintf(f, "%d %d\n", p->n, p->m);

    for(i = 0; i < p->n; i++){
        for(j = 0; j < p->m; j++){
            fprintf(f, "%d ", p->tab[i][j].value);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 1;
}

parti initialisation_score(char *name_player){
    char path[256], lines[80];
    parti player;
    FILE *f;

    player.score = 0;
    player.score_max = 0;

    strncpy(player.name_player, name_player, 10);
    player.name_player[10] = '\0';

    sprintf(path, "%s.txt", player.name_player);
    
    f = fopen(path,"r");
    if (f){
        if (fgets(lines, sizeof(lines), f) != NULL) {
            player.score_max = atoi(lines);
        }
        
        fclose(f);
    } else {
        f = fopen(path, "w");
        if (f) {
            fprintf(f, "0\n0\n");
            fclose(f);
        } else {
            fprintf(stderr, "Erreur : impossible de créer le fichier %s.txt\n", path);
        }  
    }
    return player;
}

void save_parti(parti player) {
    char path[256];
    FILE *f;

    sprintf(path, "%s.txt", player.name_player);

    f = fopen(path, "w");
    if (f) {
        fprintf(f, "%d\n%d\n", player.score_max, player.score);
        fclose(f);
    } else {
        fprintf(stderr, "Erreur : impossible d'ouvrir %s pour écriture\n", path);
    }
}

void display_score(){
    parti player;
    char name_player[80];
    printf("quel est votre nom de joueur ?");
    if (scanf("%79s", name_player) != 1) {
        fprintf(stderr, "Erreur de lecture du nom du joueur\n");
        exit(EXIT_FAILURE);
    }
    player = initialisation_score(name_player);
    
    save_parti(player);
    
    printf("joueur : %s \nscore : %d \nmeilleur_score : %d\n",player.name_player,player.score, player.score_max);
}