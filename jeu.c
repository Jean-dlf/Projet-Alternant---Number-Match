
/*jeu.c*/

#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "plateau.h"
#include "jeu.h"

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

/************ FONCTIONS UTILES AU BON FONCTIONNEMENT DU JEU ************/

/* Affiche les coordonnées et la valeur d'une case */
void afficher_case(cases *c){
    printf("Cordonnée x : %d   ---   Coordonnée y : %d   ---   Valeur : %d\n", c->x, c->y, c->valeur);
}

/* Vérifie si 2 cases ont la même valeur */
int cases_similaire(cases *c1, cases *c2){
    if(c1->valeur == c2->valeur){
        return 1;
    }

    return 0;
}

/* Vérifie si la somme de 2 cases est égale à 10 */
int verif_somme_10(cases *c1, cases *c2){
    if(c1->valeur + c2->valeur == 10){
        return 1;
    }

    return 0;
}

int points_pour_match(l_cases *l_c){
    /*  - si somme == 10  -> 15 points (bonus)
        - si valeurs identiques -> 10 points
        - fallback -> 5 points */
    if(verif_somme_10(&l_c->c[0], &l_c->c[1])){
        return 15;
    }
    if(cases_similaire(&l_c->c[0], &l_c->c[1])){
        return 10;
    }
    return 5;
}

/* Permet de vérifier si une case à une valeur de 0 soit est vide */
int verif_cases_vides(plateau *p, int x, int y){
    if(p->tab[x][y].valeur == 0){
        return 1;
    }

    return 0;
}

/* Vérifie si des coordonées sont dans le plateau */
int dans_plateau(plateau *p, int x, int y){

    if(x < 0 || x >= p->n || y < 0 || y >= p->m){
        return 0;
    }

    return 1;
}

/* Permet de retourner la cases parmi qui est la + haute dans le plateau */
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

int voisin_fin_debut_ligne(cases *c1, cases *c2, plateau *p){
    cases c_h, c_b;
    int i, j;

    /* Regarde quel cases est la + haute */
    c_h = cases_haute(c1, c2);

    /* On note que l'autre est la case basse */
    if(c_h.x == c1->x && c_h.y == c1->y && c_h.valeur == c1->valeur){
        c_b = *c2;
    } else {
        c_b = *c1;
    }

    /* On vérifie si la case haute est à la dernière colonne et si la case basse est à la 1ère colonne de la ligne d'après */
    if(c_h.y == p->m - 1 && c_b.x == c_h.x + 1 && c_b.y == 0){
        return 1;
    }

    /* Vérification avec des 0 entre c1 et c2 */
    i = c_h.x;
    j = c_h.y;

    /* On parcourt tant qu'on a pas atteint la case d'en bas */
    while(i != c_b.x || j != c_b.y){
        /* On part de la case après celle d'en haut */
        j++;


        /* Vérifie si on ne dépasse pas le nombre de colonne max */
        if(j == p->m){
        j = 0;
        i++;
        }

        /* Vérifie si on a atteint le but */
        if(i == c_b.x && j == c_b.y){
            if(p->tab[i][j].valeur == c_b.valeur){
                return 1;
            } else {
                return 0;
            }
        }

        /* Vérifie si la valeur de la case actuelle = 0 */
        if(p->tab[i][j].valeur != 0){
            return 0;
        }
    }

    return 0;
}

/* Fonction qui vérifie si 2 cases sont voisines */
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

    /* Vérifie si ils sont voisins directs soit côte à côté sans être sur la même case */
    if((espace_x <= 1 && espace_y <= 1) && (espace_x != 0 && espace_y != 0)){
        return 1;
    }

    /** On regarde si y'a des cases vides entre **/
        /* D'abord on regarde si ils peuvent être voisins */
    if((c1->x == c2->x) || (c1->y == c2->y) || (espace_x == espace_y)){
        
        /** On calcule la direction (Diagonale, Horizontale, Verticale) **/

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
            /* On regarde si les coordonnées sont toujours dans le plateau */
            if(dans_plateau(p, x, y) == 0){
                return 0;
            }

            /* Pas voisins car pas de cases vides entre elles */
            if(verif_cases_vides(p, x, y) == 0){
                return 0;
            }

            /* On incrément avec la direction voulu */
            x += dec_x;
            y += dec_y;
        }

        /* Les cases sont voisines car il y a que des cases vides entre elles */
        return 1;


    } else {
        return 0;
    }
}

/* Permet de vérifier si des cases sont voisines malgré un changement de ligne */
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

        /* On parcourt à partir de la case après la case haute */
        for(i = c_h.x; i < p->n; i++){
            for(j = c_h.y + 1; j < p->m; j++){

                if(i == c_b.x && j == c_b.y){
                    return 1;
                }

                if(p->tab[i][j].valeur != 0){
                    return 0;
                }
            }
        }
    }
    return 0;
}

/* Permet de rentrer les coordonnées des cases qu'on veut pour vérifier le match */
cases select_case(plateau *p){
    int lig, col;
    cases c;

    /* Pour entrer la ligne souhaitée */
    printf("Veuillez entrer le numéro de la ligne (de 0 à %d) : ", p->n - 1);
    if((scanf("%d", &lig) != 1) || lig < 0 || lig > p->n - 1){ /* On vérifie que le numéro de la ligne est dans le plateau */
        fprintf(stderr, "Erreur lors de la saisie de la ligne : %d\n", lig);
        viderBuffer();
        c.x = -1;
        c.y = -1;
        return c;
    }

    /* Pour entrer la colonne souhaitée */
    printf("Veuillez entrer le numéro de la colonne (de 0 à %d) : ", p->m - 1);
    if((scanf("%d", &col) != 1) || col < 0 || col > p->m - 1){ /* On vérifie que le numéro de la colonne est dans le plateau */
        fprintf(stderr, "Erreur lors de la saisie de la ligne : %d\n", col);
        viderBuffer();
        c.x = -1;
        c.y = -1;
        return c;
    }

    /* Si tout est bon alors on dit que la case = la case du plateau avec les valeurs rentrées */
    c = p->tab[lig][col];

    printf("Case sélectionée : (%d, %d)\n", c.x, c.y);
    printf("La valeur de la case sélectionnée est : %d\n", c.valeur);

    return c;
}

/* Permet de mettre les 2 cases sélectionées manuellement dans une liste de cases l_cases  */
l_cases liste_paire(plateau *p){
    l_cases l_c;
    cases c1, c2;

    l_c.n = 2; /* Initialise directement la longueur à 2 */
    if((l_c.c = (cases*) malloc (2 * sizeof(cases))) == NULL){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire de la liste de case\n");
        l_c.n = 0;
        l_c.c = NULL;
        return l_c;
    }

    /* On fait une boucle pour que si il y a une erreur alors on redemande à l'utilisateur d'entrer une bonne valeur */
    do{
        printf("Première case\n");
        c1 = select_case(p);        
    } while(c1.x == -1 || c1.y == -1); /* les -1 c'était les coordonées renvoyées en cas d'échec lors de l'entrée des coordonnées */

    do{
        printf("Deuxième case\n");
        c2 = select_case(p);

        /* Lorsque les 2 sont rentrées on vérifie si il n'a pas entré 2 fois la même case */
        if((c2.x == c1.x && c2.y == c1.y)){
            printf("Même case ! Choisissez en une différente\n");
            c2.x = -1;
            c2.y = -1;
        }

    } while(c2.x == -1 || c2.y == -1);

    /* Si tout est bon alors dans le tableau l_c on met les cases dedans */
    l_c.c[0] = c1;
    l_c.c[1] = c2;

    /* On retourne le tableau de cases */
    return l_c;
}

/* Fonction qui vérifie le match de 2 cases dans un l_cases */
int match(l_cases *l_c, plateau *p){

    /* Toutes les conditions pour le match */
    if((cases_similaire(&l_c->c[0], &l_c->c[1]) || verif_somme_10(&l_c->c[0], &l_c->c[1])) && (voisins(&l_c->c[0], &l_c->c[1], p) || (voisin_plus(&l_c->c[0], &l_c->c[1], p)) || (voisin_fin_debut_ligne(&l_c->c[0], &l_c->c[1], p)) )){
        /* Si toutes les conditions sont remplies */
        /*printf("Il y a match\n");*/
        return 1;
    }
   
    /*printf("Il y a pas match\n");*/
    return 0;
}

/* Permet après un match de mettre les valeurs des 2 cases à 0 pour les vider */
plateau *mise_a_zero(plateau *p, l_cases l_c){
    l_c.c[0].valeur = 0;
    l_c.c[1].valeur = 0;

    p->tab[l_c.c[0].x][l_c.c[0].y].valeur = l_c.c[0].valeur;
    p->tab[l_c.c[1].x][l_c.c[1].y].valeur = l_c.c[1].valeur;

    return p;
}

/* Permet de renvoyer un tableau d'entier indiquant les lignes vides soit une ligne remplie de 0 */
int *ligne_vide(plateau *p, int *taille){
    int i, j, est_vide, x = 0;
    int *tab_vide;

    /* On alloue la longueur du tableau avec la taille max possible soit le nombre de ligne du plateau */
    if((tab_vide = (int *) malloc ( p->n * sizeof(int))) == NULL){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire du tableau de ligne vide\n");
        *taille = 0;
        return NULL;
    }

    /* On parcourt pour vérifier si une ligne est vide */
    for(i = 0; i < p->n; i++){
        est_vide = 1;
        for(j = 0; j < p->m; j++){
            if(!verif_cases_vides(p, i, j)){
                est_vide = 0;
            }
        }
        /* Si à la fin du parcours d'une ligne toutes les valeurs étaient à 0 alors est_vide = 1*/
        if(est_vide){
            /* On met à la valeur x du tableau le numéro de ligne */
            tab_vide[x] = i;
            x++;
        }
    }
    /* Particulier mais taille est un pointeur via le *, on dit que taille = à x pour connaître la taille du nombre de lignes vides */
    *taille = x;
    return tab_vide;
}

/* Fonction pour afficher les valeurs d'un tableau */
void aff_tab(int *tab, int taille){
    int i;
    
    for(i = 0; i < taille; i++){
        printf("tab[%d] = %d\n", i, tab[i]);
    }
}

/* Fonction pour afficher les cases contenues dans le tableau l_cases */
void afficher_l_cases(l_cases l_c){
    int i;

    printf("L_cases : \n");
    for(i = 0; i < l_c.n; i++){
        printf("Case %d : (%d, %d) -> %d\n", i, l_c.c[i].x, l_c.c[i].y, l_c.c[i].valeur);
    }
}

/* Fonction pour supprimer les lignes vides */
plateau *suppression_ligne_vide(plateau *p, int *tab_vide, int taille){
    int i, j, k, est_vide;
    int new_i = 0;
    cases **new_tab;

    /* On alloue un nouveau tableau avec le nombre de lignes totales - le nombre de lignes vides */
    if((new_tab = (cases **) malloc((p->n - taille) * sizeof(cases *))) == NULL){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire de new_tab\n");
        return p;
    }

    /* On parcourt chaque ligne */
    for(i = 0; i < p->n; i++){
        
        /* On suppose que la ligne est non vide */
        est_vide = 0;
        
        /* On parcourt le tableau des lignes vides */
        for(j = 0; j < taille; j++){
            
            /* On vérifie si la ligne i est dans le tableau des lignes à supprimer */
            if(i == tab_vide[j]){
                est_vide = 1;
            }
        }

        /* Si c'est pas vide */
        if(!est_vide){

            /* On la conserve dans le nouveau plateau */
            new_tab[new_i] = p->tab[i];

            /* On met à jour la coordonnée x de chaque ligne */
            for(k = 0; k < p->m; k++){
                new_tab[new_i][k].x = new_i;
            }

            /* On incrémente l'indice */
            new_i++;

        } else {
            
            /* On libère la ligne vide */
            free(p->tab[i]);
        }
    }

    /* On libère l'ancien plateau */
    free(p->tab);

    /* On initialise le plateau avec le nouveau plateau créé */
    p->tab = new_tab;

    /* Nouvelle longueur */
    p->n = new_i;
    
    return p;
}


/************ BONUS DE JEU ************/

/***** BONUS AJOUT DE LIGNE  *****/

/* Permet de vérifier si le plateau de jeu est vide */
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

/* Permet de retourner la dernière case du plateau qui est différente de 0 */
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

/* Permet de demander à l'utilisateur si il veut utiliser le bonus ajout de ligne */
plateau *utiliser_ajout_ligne(plateau *p, int *valide){
    char rep = 'A';

    *valide = 0;

    /* On boucle si la valeur rentrée n'est pas bonne */
    while(rep != 'N' && rep != 'O'){
        printf("Voulez vous utiliser le BONUS AJOUT DE LIGNE ? (O ou N) : ");
        if(scanf(" %c", &rep) != 1 || (rep != 'O' && rep != 'N')){
            fprintf(stderr, "Erreur il vous faut rentrer soit 'O' ou 'N' pour commencer\n");
        }
        viderBuffer();
    }

    /* Si oui on utilise le bonus */
    if(rep == 'O'){
        *valide = 1;
        p = bonus_ajout_ligne(p);
    }
    return p;
}

/* Utilisation du bonus ajout de ligne */
plateau *bonus_ajout_ligne(plateau *p){
    l_cases l_c;
    cases *c;
    int i, j, k, max, nb_lig_all;

    /* Nombre max de cases dans le plateau */
    max = p->n * p->m;

    /* Allocation de la liste de cases */
    if((l_c.c = (cases*) malloc ( max * sizeof(cases))) == NULL){
        printf("Erreur lors de l'allocation de mémoire de la liste de cases\n");
        return p;
    }

    k = 0;

    /* Copie des valeurs non nulles dans l_c */
    for(i = 0; i < p->n; i++){
        for(j = 0; j < p->m; j++){
            if(p->tab[i][j].valeur != 0){
                l_c.c[k] = p->tab[i][j];
                k++;
            }
        }
    }

    /* Initialisation de la longueur de l_c */
    l_c.n = k;

    /* Initialisation de la dernière case */
    c = derniere_case(p);

    printf("Ajout de ligne\n");

    /* Calcul du nombre de lignes nécessaire pour contenir toutes les cases non nulles */
    nb_lig_all = l_c.n / p->m;
    if(l_c.n % p->m != 0){
        /* Si reste on rajoute une ligne en plus */
        nb_lig_all += 1;
    }

    /* Ajout des lignes supplémentaires */
    if(!ajout_nb_ligne_plateau(p, nb_lig_all)){
        fprintf(stderr, "Erreur : impossible d'ajouter des lignes\n");
        free(l_c.c);
        return p;
    }

    k = 0;
    /* Position de départ de la recopie */
    i = c->x;
    j = c->y + 1;

    /* Si début = dernière colonne on commence à la ligne suivante et à la première colonne */
    if(j == p->m){
        j = 0;
        i++;
    }

    /* Recopie des valeurs */
    while(k < l_c.n && i < p->n){
        p->tab[i][j].valeur = l_c.c[k].valeur;
        k++;
        j++;
        if(j == p->m){
            j = 0;
            i++;
        }
    }

    /* On remplie le reste par 0 */
    while(i < p->n){
        while(j < p->m){
            p->tab[i][j].valeur = 0;
            j++;
        }
        j = 0;
        i++;
    }

    /* On libère l_c */
    free(l_c.c);

    return p;
}

/* Fonction qui ajoute un nombre de lignes dans le plateau */
int ajout_nb_ligne_plateau(plateau *p, int nb_ligne){
    int i, j;
    int ancien_n = p->n;
    int new_n = ancien_n + nb_ligne;
    cases **new_tab;

    /* On crée un nouveau plateau qui fait la taille du plateau de base + le nombre de ligne qu'on veut rajouter */
    new_tab = (cases**) realloc(p->tab, new_n * sizeof(cases*));
    if (new_tab == NULL) {
        fprintf(stderr, "Erreur lors de la réallocation de la mémoire du tableau\n");
        return 0;
    }

    /* On initialise le plateau avec le nouveau */
    p->tab = new_tab;

    /* On parcourt */
    for(i = ancien_n; i < new_n; i++){
        if((p->tab[i] = (cases*) malloc ( p->m * sizeof(cases))) == NULL){
            fprintf(stderr, "Erreur lors de l'allocation des nouvelles lignes\n");
            for(j = p->n; j < i; j++){
                free(p->tab[j]);
            }
            return 0;
        }

        /* On initialise les cases à 0 */
        for(j = 0; j < p->m; j++){
            p->tab[i][j].x = i;
            p->tab[i][j].y = j;
            p->tab[i][j].valeur = 0;
        }
    }
    p->n = new_n;
    return 1;
}

/***** BONUS INDICE *****/


tab_couples couples_possibles(plateau *p){
    tab_couples t_c;
    cases *c1, *c2;
    l_cases lc;
    int i, j, k, l;
    int taille_max = p->n * p->m * p->n * p->m;
    t_c.n = 0;

    /* Allocation pour stocker les couples possibles du plateau */
    if((t_c.lc = (l_cases *) malloc (taille_max * sizeof(l_cases))) == NULL){
        fprintf(stderr, "Erreur d'allocation mémoire pour tab_couples\n");
        t_c.n = 0;
        return t_c;
    }

    /* Parcours de toutes les cases du plateau pour la première case du couple */
    for(i = 0; i < p->n; i++){
        for(j = 0; j < p->m; j++){

            c1 = &p->tab[i][j]; /* Pointeur première case */

            /* On prend en compte que les cases non vides */
            if(c1->valeur != 0){

                /* Parcours du plateau pour la deuxième case du couple */
                for(k = 0; k < p->n; k++){
                    for(l = 0; l < p->m; l++){

                        /* On évite les doublons en ne prenant que les couples dans un sens */
                        if(k > i || (k == i && l > j)){

                            c2 = &p->tab[k][l]; /* Pointeur deuxième case */

                            /* Valeur non vide */
                            if(c2->valeur != 0){
                            
                                /* Création de la structure l_cases */
                                lc.n = 2;
                                lc.c = malloc(2 * sizeof(cases));
                                if(lc.c != NULL){
                                    lc.c[0] = *c1;
                                    lc.c[1] = *c2;

                                    /* Vérification du match */
                                    if(match(&lc, p)){
                                        /* Si oui alors on ajoute */
                                        t_c.lc[t_c.n] = lc;
                                        t_c.n++;
                                    } else {
                                        free(lc.c);  /* libère la mémoire si pas de match */
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return t_c;
}

/* Affiche les couples possibles */
void afficher_couples_possibles(tab_couples t_c){
    int i;

    printf("Couples possibles : %d\n", t_c.n);
    for(i = 0; i < t_c.n; i++){
        printf("Couple %d :\n", i + 1);
        afficher_case(&t_c.lc[i].c[0]);
        afficher_case(&t_c.lc[i].c[1]);
        printf("------------\n");
    }
}

/* Libère les couples de cases */
void liberer_tab_couples(tab_couples *t_c){
    int i;

    /* Libère chaque tableau de cases alloué par couple */
    for(i = 0; i < t_c->n; i++){
        free(t_c->lc[i].c);
    }

    /* Libère le tableau */
    free(t_c->lc);

    /* Réinitialise la structure */
    t_c->n = 0;
    t_c->lc = NULL;
}

/* Choisi un couple aléatoire parmi le tableau de couple */
l_cases couple_aleatoire(tab_couples *t_c){
    int random;
    l_cases vide = {0, NULL};
    
    /* Qu'un seul couple possible */
    if(t_c->n == 1){
        return t_c->lc[0];
    } 
    /* Aucun couple */
    else if(t_c->n == 0){
        printf("Il n'y a pas de solutions possibles\nUtilisez le bonus ajout de ligne\n");
        return vide;
    }

    /* Si plusieurs alors on choisi aléatoirement un couple */
    random = rand() % t_c->n;

    return t_c->lc[random];
}

/* Utilisation du bonus indice */
void bonus_indice(plateau *p){
    tab_couples t_c;
    l_cases l_c;

    /* Couple possible */
    t_c = couples_possibles(p);

    /* Couple choisit */
    l_c = couple_aleatoire(&t_c);

    /* Si aucun couple retourne rien */
    if(l_c.n == 0){
        return;
    } 

    /* Affiche du couple choisit */
    printf("Voici une solution possible parmi tous les couples possibles \n");
    afficher_l_cases(l_c);
    
}

/* Demande d'utilisation du bonus indice */
int utiliser_indice(plateau *p){
    char rep = 'A';

    /* On boucle si la valeur rentrée n'est pas bonne */
    while(rep != 'N' && rep != 'O'){
        printf("Voulez vous utiliser le BONUS INDICE ? (O ou N) : ");
        if(scanf(" %c", &rep) != 1 || (rep != 'O' && rep != 'N')){
            fprintf(stderr, "Erreur il vous faut rentrer soit O ou N pour commencer\n");
        }
        viderBuffer();
    }

    /* Si oui on utilise le bonus */
    if(rep == 'O'){
        bonus_indice(p);
        return 1;
    }
    return 0;
}

/* Défaite */
int vide(plateau *p){
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

int defaite(plateau *p, int nb_ajt_lig, int nb_ind_cpl){
    tab_couples c_possibles = couples_possibles(p);

    if(nb_ajt_lig == 0 && nb_ind_cpl == 0 && !vide(p) && c_possibles.n == 0) {
        return 1;
    }

    return 0;
}