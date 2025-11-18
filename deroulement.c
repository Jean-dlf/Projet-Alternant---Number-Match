#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "jeu.h"
#include "initialisation.h"
#include "plateau.h"

void deroulement(plateau *p, int n, int m, int save, parti *joueur_s){
    int *tab_vide = NULL;
    int taille, pts, i, nb_ajt_lig, nb_ind_cpl, valide, perdu;
    l_cases l_c;
    plateau *new_p;
    char nom_joueur[80];
    parti joueur;

    perdu = 0;

    if(save){
        printf("Entrez votre nom de joueur : ");
        if(scanf("%79s", nom_joueur) != 1){
            fprintf(stderr, "Erreur lecture nom joueur\n");
            return ;
        }

        viderBuffer();
        joueur = initialiser_score(nom_joueur);

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
        joueur = *joueur_s;
        nb_ajt_lig = joueur.bonus_ajout_ligne;
        nb_ind_cpl = joueur.bonus_indice;
    }

    afficher_plateau(p);

    while(p->n != 0 && perdu == 0){
        l_c = liste_paire(p);

        if(match(&l_c, p)){
            mise_a_zero(p, l_c);

            /* ajout des points pour ce match */
            pts = points_pour_match(&l_c);
            joueur.score += pts;
            printf("+%d points ! Score actuel : %d\n", pts, joueur.score);

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
            if(nb_ajt_lig > 0){
                new_p = utiliser_ajout_ligne(p, &valide);
                if(new_p != p){
                    p = new_p;
                }
                if(valide == 1/* && compte_ajout_ligne(nb_ajt_lig) != -1*/){
                    nb_ajt_lig -= 1;
                }
            } else {
                printf("Vous n'avez plus d'utilisation de bonus d'ajout de lignes possible\n");
            }

            if(nb_ind_cpl > 0){
                if(utiliser_indice(p)/* && compte_indice_couple(nb_ind_cpl) != -1*/){
                    nb_ind_cpl -= 1;
                }
            } else {
                printf("Vous n'avez plus d'utilisation de bonus d'indice de couple possible\n");
            }

            afficher_plateau(p);

            if(defaite(p, nb_ajt_lig, nb_ind_cpl)){
                printf("Vous avez perdu\n");
                return ;
            }
        }

        printf("Nombre d'utilisation possible du bonus d'indice de couples : %d\n", nb_ind_cpl);
        printf("Nombre d'utilisation possible du bonus d'ajout de lignes : %d\n", nb_ajt_lig);
    }

    if(joueur.score > joueur.score_max){
        joueur.score_max = joueur.score;
        printf("Nouveau record ! %d points \n", joueur.score_max);
    }

    joueur.bonus_ajout_ligne = nb_ajt_lig;
    joueur.bonus_indice = nb_ind_cpl;

    sauvegarder_parti(joueur);

    /* Libération mémoire plateau */
    if(p != NULL){
        for(i = 0; i < p->n; i++){
            free(p->tab[i]);
        }
        free(p->tab);
        free(p);
        p = NULL;
    }

    printf("Vous avez gagné ! Score final : %d\n", joueur.score);
    return ;
}