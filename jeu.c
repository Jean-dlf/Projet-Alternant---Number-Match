#include <stdlib.h>
#include <stdio.h>
#include "types.h"

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
            c_h = *c1;
            c_b = *c2;
        } else {
            c_h = *c2;
            c_b = *c1;
        }

        for(i = c_h.x; i < p->n; i++){
            for(j = c_h.y + 1; j < p->m; j++){

                if(p->tab[i][j].valeur == p->tab[c_b.x][c_b.y].valeur){
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
    if((scanf("%d", &lig) != 1) || lig < 0 || lig > p->n){
        fprintf(stderr, "Erreur lors de la saisie de la ligne : %d\n", lig);
        viderBuffer();
        c.x = -1;
        c.y = -1;
        return c;
    }

    printf("Veuillez entrer le numéro de la colonne (de 0 à %d) : ", p->m - 1);
    if((scanf("%d", &col) != 1) || col < 0 || col > p->m){
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

    /*printf("Liste de cases créée\n");
    printf("Case 1 : (%d, %d) --- Valeur : %d\n", l_c.c[0].x, l_c.c[0].y, l_c.c[0].valeur);
    printf("Case 2 : (%d, %d) --- Valeur : %d\n", l_c.c[1].x, l_c.c[1].y, l_c.c[1].valeur);*/

    return l_c;
}

int match(l_cases *l_c, plateau *p){

    if((cases_similaire(&l_c->c[0], &l_c->c[1]) || verif_somme_10(&l_c->c[0], &l_c->c[1])) && (voisins(&l_c->c[0], &l_c->c[1], p) || (voisin_plus(&l_c->c[0], &l_c->c[1], p)))){
        printf("Il y a match\n");
        return 1;
    }
   
    printf("Il y a pas match\n");
    return 0;
}

plateau *mise_a_zero(plateau *p, l_cases l_c){
    if(match(&l_c, p)){
        l_c.c[0].valeur = 0;
        l_c.c[1].valeur = 0;

        p->tab[l_c.c[0].x][l_c.c[0].y].valeur = l_c.c[0].valeur;
        p->tab[l_c.c[1].x][l_c.c[1].y].valeur = l_c.c[1].valeur;

        printf("Les cases ont été mises à zéro\n");
        printf("Case 1 : (%d, %d) = %d\n", l_c.c[0].x, l_c.c[0].y, l_c.c[0].valeur);
        printf("Case 2 : (%d, %d) = %d\n", l_c.c[1].x, l_c.c[1].y, l_c.c[1].valeur);
    }

    return p;
}

/* Faudrait renvoyer le numéro de la ligne vide au lieu de 1, (pour la boucle de jeu j'peux la faire boucler pour obtenir à chaque itération le numéro de la ligne jusqu'à ce que le renvoie de la fonction soit != 0 */
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
            /* printf("tab[%d][%d] = %d\n", i, j, p->tab[i][j].valeur); */
            if(!verif_cases_vides(p, i, j)){
                /* printf("ON DONNE PAS LA LIGNE tab[%d][%d] = %d\n", i, j, p->tab[i][j].valeur); */
                est_vide = 0;
            }
        }
        if(est_vide){
            printf("on est en (%d ; %d)\n", i, j);
            printf("i = %d\n", i);
            printf("x avant = %d\n", x);
            tab_vide[x] = i;
            x++;
            printf("x après = %d\n", x);
        }
    }
    *taille = x;
    printf("taille = %d\n", *taille);
    return tab_vide;
}

void aff_tab(int *tab, int taille){
    int i;
    
    for(i = 0; i < taille; i++){
        printf("tab[%d] = %d\n", i, tab[i]);
    }
}


plateau *suppression_ligne_vide(plateau *p, int *tab_vide, int taille){
    int i, j, k;

    for(i = 0; i < p->n; i++){
        for(j = 0; j < p->m; j++){
            for(k = 0; k < taille; k++){
                if((i == tab_vide[k]) && (i != p->n - 1)){
                    p->tab[i][j] = p->tab[i + 1][j];
                }
            }
        }
    }
    return p;
}