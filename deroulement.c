
/*deroulement.c*/

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "plateau.h"
#include "initialisation.h"
#include "jeu.h"

void deroulement(plateau *p, int n, int m){
    int *tab_vide = NULL;
    int taille, pts, i;
    l_cases l_c;
    plateau *new_p;
    char nom_joueur[80];

    printf("Entrez votre nom de joueur : ");
    if(scanf("%79s", nom_joueur) != 1){
        fprintf(stderr, "Erreur lecture nom joueur\n");
        return;
    }
    viderBuffer();

    parti joueur = initialiser_score(nom_joueur);


    /*cases *c1, *c2;, *c3, *c4, *c5, *c6, *c7, *c8, *c9, *c10, *c11, *c12;*/

    /*c1 = initialisation_cases(0, 0, 1);
    c2 = initialisation_cases(0, 1, 1);
    c3 = initialisation_cases(2, 5, 1);
    c4 = initialisation_cases(3, 0, 0);
    c5 = initialisation_cases(3, 1, 9);
    c6 = initialisation_cases(0, 0, 5);
    c7 = initialisation_cases(0, 1, 5);
    c8 = initialisation_cases(1, 3, 5);
    c9 = initialisation_cases(2, 0, 5);
    c10 = initialisation_cases(2, 1, 5);
    c11 = initialisation_cases(2, 2, 5);
    c12 = initialisation_cases(2, 3, 5);*/

    p = initialisation_plateau(n, m);
    if(p == NULL){
        fprintf(stderr,"Erreur initialisation plateau\n");
        return;
    }
    initialisation_aleatoire(p);

    /*p->tab[c1->x][c1->y].valeur = c1->valeur;
    p->tab[c2->x][c2->y].valeur = c2->valeur;
    p->tab[c3->x][c3->y].valeur = c3->valeur;
    p->tab[c4->x][c4->y].valeur = c4->valeur;
    p->tab[c5->x][c5->y].valeur = c5->valeur;
    p->tab[c6->x][c6->y].valeur = c6->valeur;
    p->tab[c7->x][c7->y].valeur = c7->valeur;
    p->tab[c8->x][c8->y].valeur = c8->valeur;
    p->tab[c9->x][c9->y].valeur = c9->valeur;
    p->tab[c10->x][c10->y].valeur = c10->valeur;
    p->tab[c11->x][c11->y].valeur = c11->valeur;
    p->tab[c12->x][c12->y].valeur = c12->valeur;*/

    afficher_plateau(p);

    while(p->n != 0){
        l_c = liste_paire(p);

        if(match(&l_c, p)){
            mise_a_zero(p, l_c);

            /*ajout des points pour ce match*/
            pts = points_pour_match(&l_c);
            joueur.score += pts;
            printf("+%d points ! Score actuel : %d\n",pts,joueur.score);

            tab_vide = ligne_vide(p, &taille);
            if(taille != 0){
                suppression_ligne_vide(p, tab_vide, taille);
            }
            if(tab_vide != NULL){
                free(tab_vide);
                tab_vide = NULL;
            }
        }
        afficher_plateau(p);

        if(!plateau_vide(p)){
            new_p = utiliser_ajout_ligne(p);
            if(new_p != p){
                p = new_p;
            }
            afficher_plateau(p);

            utiliser_indice(p);
        }
    }

    if(joueur.score > joueur.score_max){
        joueur.score_max = joueur.score;
        printf("Nouveau record ! %d points \n", joueur.score_max);
    }
    sauvegarder_parti(joueur);

    /*Libération mémoire plateau*/
    if(p != NULL){
        for(i = 0; i < p->n; i++){
            free(p->tab[i]);
        }
        free(p->tab);
        free(p);
        p = NULL;
    }

    if(system("clear") == 0){
    }
    printf("Vous avez gagné ! Score final : %d\n",joueur.score);
}

