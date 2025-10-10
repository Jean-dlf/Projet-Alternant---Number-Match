
#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "plateau.h"
#include "jeu.h"

/************ FONCTIONS UTILES AU BON FONCTIONNEMENT DU JEU ************/

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void afficher_case(cases *c){
    printf("Cordonnée x : %d   ---   Coordonnée y : %d   ---   Valeur : %d\n", c->x, c->y, c->valeur);
}

int cases_similaire(cases *c1, cases *c2){
    if(c1->valeur == c2->valeur){
        printf("Valeur similaire\n");
        return 1;
    }

    return 0;
}

int verif_somme_10(cases *c1, cases *c2){
    if(c1->valeur + c2->valeur == 10){
        printf("Somme égale à 10\n");
        return 1;
    }

    return 0;
}

int verif_cases_vides(plateau *p, int x, int y){
    if(p->tab[x][y].valeur == 0){
        return 1;
    }

    return 0;
}

int dans_plateau(plateau *p, int x, int y){

    if(x < 0 || x >= p->n || y < 0 || y >= p->m){
        printf("La case depasse les limites du plateau de jeu\n");
        return 0;
    }

    return 1;
}

int voisin_fin_debut_ligne(cases *c1, cases *c2, plateau *p){
    cases c_h, c_b;

    c_h = cases_haute(c1, c2);

    if(c_h.x == c1->x && c_h.y == c1->y && c_h.valeur == c1->valeur){
        c_b = *c2;
    } else {
        c_b = *c1;
    }

    if(c_h.y == p->m - 1 && c_b.x == c_h.x + 1 && c_b.y == 0){
        return 1;
    }

    return 0;
}

int voisins(cases *c1, cases *c2, plateau *p){
    int espace_x, espace_y, x, y, dec_x, dec_y;

    /* On calcule la différence entre les coordonnées x et y de c1 et c2 */
    if(c1->x >= c2->x){
        espace_x = c1->x - c2->x;
    } else {
        espace_x = c2->x - c1->x;
    }

    if(c1->y >= c2->y){
        espace_y = c1->y - c2->y;
    } else {
        espace_y = c2->y - c1->y;
    }

    /* Voisins Directs */
    
    if((espace_x <= 1 && espace_y <= 1) && (espace_x != 0 && espace_y != 0)){
        printf("Voisins Directs\n");
        return 1;
    }

    /* On regarde si y'a des cases vides entre */
        /* D'abord on regarde si ils peuvent être voisins */
    if((c1->x == c2->x) || (c1->y == c2->y) || (espace_x == espace_y)){
        
        /* On calcule la direction (Diagonale, Horizontale, Verticale)*/

            /* Calcul de x */
        if(c1->x > c2->x){
            dec_x = -1;
        } else if(c1->x < c2->x){
            dec_x = 1;
        } else {
            dec_x = 0;
        }

            /* Calcul de y */
        if(c1->y > c2->y){
            dec_y = -1;
        } else if(c1->y < c2->y){
            dec_y = 1;
        } else {
            dec_y = 0;
        }

        /* On commence en c1 en l'excluant */
        x = c1->x + dec_x;
        y = c1->y + dec_y;

        /* On parcourt */
        while(x != c2->x || y != c2->y){
            if(dans_plateau(p, x, y) == 0){
                printf("Dépassement de limite\n");
                return 0;
            }

            /* Pas voisins car pas de cases vides entre elles */
            if(verif_cases_vides(p, x, y) == 0){
                printf("Pas vide donc c1 et c2 ne sont pas voisins\n");
                return 0;
            }

            x += dec_x;
            y += dec_y;
        }

        /* Les cases sont voisines car il y a que des cases vides entre elles */
        printf("Cases Voisines\n");
        return 1;


    } else {
        printf("Cases pas Voisines\n");
        return 0;
    }
}

cases cases_haute(cases *c1, cases *c2){

    if(c1->x > c2->x){
        return *c2;
    } else if(c1->x < c2->x){
        return *c1;
    } else {
        if(c1->y < c2->y){
            return *c1;
        } else {
            return *c2;
        }
    }
}

int voisin_plus(cases *c1, cases *c2, plateau *p){
    int i, j;
    cases c_h, c_b;

    if(voisins(c1, c2, p)){
        return 1;
    } else {

        c_h = cases_haute(c1, c2);

        if(c_h.x == c1->x && c_h.y == c1->y && c_h.valeur == c1->valeur){
            c_b = *c2;
        } else {
            c_b = *c1;
        }

        for(i = c_h.x; i < p->n; i++){
            for(j = c_h.y + 1; j < p->m; j++){

                if(i == c_b.x && j == c_b.y){
                    printf("on est arrivé à la case 2\n");
                    return 1;
                }

                if(p->tab[i][j].valeur != 0){
                    printf("Il y a un chiffre != 0 entre c1 et c2\n");
                    printf("on est en (%d ; %d)\n", i, j);
                    return 0;
                }
            }
        }
    }
    return 0;
}

cases select_case(plateau *p){
    int lig, col;
    cases c;

    printf("Veuillez entrer le numéro de la ligne (de 0 à %d) : ", p->n - 1);
    if((scanf("%d", &lig) != 1) || lig < 0 || lig > p->n - 1){
        fprintf(stderr, "Erreur lors de la saisie de la ligne : %d\n", lig);
        viderBuffer();
        c.x = -1;
        c.y = -1;
        return c;
    }

    printf("Veuillez entrer le numéro de la colonne (de 0 à %d) : ", p->m - 1);
    if((scanf("%d", &col) != 1) || col < 0 || col > p->m - 1){
        fprintf(stderr, "Erreur lors de la saisie de la ligne : %d\n", col);
        viderBuffer();
        c.x = -1;
        c.y = -1;
        return c;
    }

    c = p->tab[lig][col];

    printf("Case sélectionée : (%d, %d)\n", c.x, c.y);
    printf("La valeur de la case sélectionnée est : %d\n", c.valeur);

    return c;
}

l_cases liste_paire(plateau *p){
    l_cases l_c;
    cases c1, c2;

    l_c.n = 2;
    if((l_c.c = (cases*) malloc (2 * sizeof(cases))) == NULL){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire de la liste de case\n");
        l_c.n = 0;
        l_c.c = NULL;
        return l_c;
    }

    do{
        printf("Première case\n");
        c1 = select_case(p);
    } while(c1.x == -1 || c1.y == -1);

    do{
        printf("Deuxième case\n");
        c2 = select_case(p);

        if((c2.x == c1.x && c2.y == c1.y)){
            printf("Même case ! Choisissez en une différente\n");
            c2.x = -1;
            c2.y = -1;
        }

    } while(c2.x == -1 || c2.y == -1);

    l_c.c[0] = c1;
    l_c.c[1] = c2;

    return l_c;
}

int match(l_cases *l_c, plateau *p){

    if((cases_similaire(&l_c->c[0], &l_c->c[1]) || verif_somme_10(&l_c->c[0], &l_c->c[1])) && (voisins(&l_c->c[0], &l_c->c[1], p) || (voisin_plus(&l_c->c[0], &l_c->c[1], p)) || (voisin_fin_debut_ligne(&l_c->c[0], &l_c->c[1], p)) )){
        printf("Il y a match\n");
        return 1;
    }
   
    printf("Il y a pas match\n");
    return 0;
}

plateau *mise_a_zero(plateau *p, l_cases l_c){
    l_c.c[0].valeur = 0;
    l_c.c[1].valeur = 0;

    p->tab[l_c.c[0].x][l_c.c[0].y].valeur = l_c.c[0].valeur;
    p->tab[l_c.c[1].x][l_c.c[1].y].valeur = l_c.c[1].valeur;

    return p;
}

int *ligne_vide(plateau *p, int *taille){
    int i, j, est_vide = 1, x = 0;
    int *tab_vide;

    if((tab_vide = (int *) malloc ( p->n * sizeof(int))) == NULL){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire du tableau de ligne vide\n");
        *taille = 0;
        return NULL;
    }
    
    for(i = 0; i < p->n; i++){
        est_vide = 1;
        for(j = 0; j < p->m; j++){
            if(!verif_cases_vides(p, i, j)){
                est_vide = 0;
            }
        }
        if(est_vide){
            tab_vide[x] = i;
            x++;
        }
    }
    *taille = x;
    return tab_vide;
}

void aff_tab(int *tab, int taille){
    int i;
    
    for(i = 0; i < taille; i++){
        printf("tab[%d] = %d\n", i, tab[i]);
    }
}

void afficher_l_cases(l_cases l_c){
    int i;

    printf("L_cases : \n");
    for(i = 0; i < l_c.n; i++){
        printf("Case %d : (%d, %d) -> %d\n", i, l_c.c[i].x, l_c.c[i].y, l_c.c[i].valeur);
    }
}


plateau *suppression_ligne_vide(plateau *p, int *tab_vide, int taille){
    int i, j, k, est_vide;
    int new_i = 0;
    cases **new_tab;

    if((new_tab = (cases **) malloc((p->n - taille) * sizeof(cases *))) == NULL){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire de new_tab\n");
        return p;
    }

     for(i = 0; i < p->n; i++){
        est_vide = 0;
        for(j = 0; j < taille; j++){
            if(i == tab_vide[j]){
                est_vide = 1;
            }
        }

        if(!est_vide){
            new_tab[new_i] = p->tab[i];

            for(k = 0; k < p->m; k++){
                new_tab[new_i][k].x = new_i;
            }

            new_i++;

        } else {
            free(p->tab[i]);
        }
    }

    free(p->tab);

    p->tab = new_tab;
    p->n = new_i;
    
    return p;
}


/************ BONUS DE JEU ************/

/***** BONUS AJOUT DE LIGNE  *****/

int plateau_vide(plateau *p){
    int i, j;

    for(i = 0; i < p->n; i++){
        for(j = 0; j < p->m; j++){
            if(p->tab[i][j].valeur != 0){
                return 0;
            }
        }
    }
    return 1;
}

cases *derniere_case(plateau *p){
    int i, j;

    for(i = p->n - 1; i >= 0; i--){
        for(j = p->m - 1; j >= 0; j--){
            if(p->tab[i][j].valeur != 0){
                return &(p->tab[i][j]);
            }
        }
    }
    
    return NULL;
}

plateau *utiliser_ajout_ligne(plateau *p){
    char rep = 'A';
    while(rep != 'N' && rep != 'O'){
        printf("Voulez vous utiliser le bonus ajout de ligne ? (O ou N) : ");
        if(scanf(" %c", &rep) != 1 || (rep != 'O' && rep != 'N')){
            fprintf(stderr, "Erreur il vous faut rentrer soit O ou N pour commencer\n");
        }
        viderBuffer();
    }

    if(rep == 'O'){
        p = bonus_ajout_ligne(p);
    }
    return p;
}

plateau *bonus_ajout_ligne(plateau *p){
    l_cases l_c;
    cases *c;
    int i, j, k, max, nb_lig_all;

    max = p->n * p->m;

    if((l_c.c = (cases*) malloc ( max * sizeof(cases))) == NULL){
        printf("Erreur lors de l'allocation de mémoire de la liste de cases\n");
        return p;
    }

    k = 0;

    for(i = 0; i < p->n; i++){
        for(j = 0; j < p->m; j++){
            if(p->tab[i][j].valeur != 0){
                l_c.c[k] = p->tab[i][j];
                k++;
            }
        }
    }

    l_c.n = k;

    c = derniere_case(p);

    if(c->x == p->n - 1 && c->y == p->m - 1){
        printf("Ajout de ligne\n");
        nb_lig_all = l_c.n / p->m;
        if(l_c.n % p->m != 0){
            nb_lig_all += 1;
        }
        if(!ajout_nb_ligne_plateau(p, nb_lig_all)){
            fprintf(stderr, "Erreur : impossible d'ajouter des lignes\n");
            free(l_c.c);
            return p;
        }
    }

    k = 0;
    i = c->x;
    j = c->y;

    while(k <= l_c.n){
        if(k == 0 || (j == p->m && i != p->n - 1)){
            j = 0;
            i++;
        }
        p->tab[i][j].valeur = l_c.c[k].valeur;
        k++;
        j++;
    }


    free(l_c.c);

    return p;
}

int ajout_nb_ligne_plateau(plateau *p, int nb_ligne){
    int i, j;
    int new_nb_ligne = p->n + nb_ligne;    
    cases **new_tab;

    new_tab = (cases**) realloc(p->tab, new_nb_ligne * sizeof(cases*));
    if (new_tab == NULL) {
        fprintf(stderr, "Erreur lors de la réallocation de la mémoire du tableau\n");
        return 0;
    }

    p->tab = new_tab;

    for(i = p->n; i < new_nb_ligne; i++){
        if((p->tab[i] = (cases*) malloc ( p->m * sizeof(cases))) == NULL){
            fprintf(stderr, "Erreur lors de l'allocation des nouvelles lignes\n");
            for(j = p->n; j < i; j++){
                free(p->tab[j]);
            }
            return 0;
        }
        for(j = 0; j < p->m; j++){
            p->tab[i][j].x = i;
            p->tab[i][j].y = j;
            p->tab[i][j].valeur = 0;
        }
    }
    p->n = new_nb_ligne;
    return 1;
}

/***** BONUS INDICE *****/

