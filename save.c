#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "initialisation.h"

/*** Parti score et nom  ***/

int charger_save(char *nom, parti *jo, plateau **p){
    FILE *f = NULL;
    int i, j, n, m;

    if((f = fopen(nom, "r")) == NULL){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier f\n");
        return -1;
    }

    if(fscanf(f, "%10s %d %d", jo->nom_joueur, &jo-> score, &jo->score_max) != 3){
        fprintf(stderr, "Erreur lors de la lecture du nom du joueur, de son score et de son meilleur score\n");
        fclose(f);
        return -1;
    }

    if(fscanf(f, "%d %d", &n, &m) != 2){
        fprintf(stderr, "Erreur lors de la lecture de la taille du plateau de jeu\n");
        fclose(f);
        return -1;
    }

    *p = initialisation_plateau(n, m);
    if (!*p) {
        fprintf(stderr, "Erreur allocation plateau\n");
        fclose(f);
        return -1;
    }

    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            if(fscanf(f, "%d", &(*p)->tab[i][j].valeur) != 1){
                fprintf(stderr, "Erreur lors de la lecture de la case [%d ; %d] du plateau de jeu\n", i, j);
                fclose(f);
                return -1;
            }
        }
    }

    if(fscanf(f, "%d %d", &jo->bonus_ajout_ligne, &jo->bonus_indice) != 2){
        fprintf(stderr, "Erreur lors de la lecture du nombre des bonus\n");
        fclose(f);
        return -1;
    }

    fclose(f);
    return 1;
}

int save_parti(char *nom, parti *jo, plateau *p){
    FILE *f;
    int i, j;

    if((f = fopen(nom, "w")) == NULL){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier f");
        return -1;
    }

    fprintf(f, "%10s %d %d\n", jo->nom_joueur, jo->score, jo->score_max);

    fprintf(f, "%d %d", p->n, p->m);

    for(i = 0; i < p->n; i++){
        for(j = 0; j < p->m; j++){
            fprintf(f, "%d ", p->tab[i][j].valeur);
        }
        fprintf(f, "\n");
    }

    fprintf(f, "%d %d\n", jo ->bonus_ajout_ligne, jo->bonus_indice);

    fclose(f);
    return 1;
}

parti initialiser_score(char *nom_joueur){
    char chemin[256], ligne[80];
    parti joueur;
    FILE *f;

    joueur.score = 0;
    joueur.score_max = 0;

    strncpy(joueur.nom_joueur, nom_joueur, 10);
    joueur.nom_joueur[10] = '\0';

    sprintf(chemin, "%s.txt", joueur.nom_joueur);
    
    f = fopen(chemin,"r");
    if (f){
        if (fgets(ligne, sizeof(ligne), f) != NULL) {
            joueur.score_max = atoi(ligne);
        }
        
        fclose(f);
    } else {
        f = fopen(chemin, "w");
        if (f) {
            fprintf(f, "0\n0\n");
            fclose(f);
        } else {
            fprintf(stderr, "Erreur : impossible de créer le fichier %s.txt\n", chemin);
        }  
    }
    return joueur;
}

void sauvegarder_parti(parti joueur) {
    char chemin[256];
    FILE *f;

    sprintf(chemin, "%s.txt", joueur.nom_joueur);

    f = fopen(chemin, "w");
    if (f) {
        fprintf(f, "%d\n%d\n", joueur.score_max, joueur.score);
        fclose(f);
    } else {
        fprintf(stderr, "Erreur : impossible d'ouvrir %s pour écriture\n", chemin);
    }
}

void afficher_score(){
    parti joueur;
    char nom_joueur[80];
    printf("quel est votre nom de joueur ?");
    if (scanf("%79s", nom_joueur) != 1) {
        fprintf(stderr, "Erreur de lecture du nom du joueur\n");
        exit(EXIT_FAILURE);
    }
    joueur = initialiser_score(nom_joueur);
    
    sauvegarder_parti(joueur);
    
    printf("joueur : %s \nscore : %d \nmeilleur_score : %d\n",joueur.nom_joueur,joueur.score, joueur.score_max);
}