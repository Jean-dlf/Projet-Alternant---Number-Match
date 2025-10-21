#ifndef _TYPES_H_
#define _TYPES_H_

/* Une case du plateau */
typedef struct{
    int x; /* Coordonnée x : ligne */
    int y; /* Coordonnée y : colonne */
    int valeur; /* Valeur de la case */
} cases;

/* Type plateau de jeu (qui contient toutes les cases) */
typedef struct{
    cases **tab; /* Plateau de jeu (**tab ça correspond à un tableau à 2 entrées, ça revient à dire tab[][]) et le type cases veut dire que chaque cases du tableau est de type cases */
    int n; /* Longueur des lignes */
    int m; /* Longueur des colonnes */
} plateau;

/* Type fait pour représenter une paire de cases; on mettra 2 cases différentes du tableau pour vérifier si les 2 choisies peuvent être matché */
typedef struct{
    int n; /* Longueur de la liste de cases (ici ça sera souvent de 2 pour le match mais on peut la faire varier si besoin */
    cases *c; /* Contient des cases */ 
} l_cases; /* ça se représente comme un tableau mais de types cases [cases 1; cases 2] etc de longueur n */

/* Type fait pour le bonus d'indice */

/* Ce type est fait pour contenir des couples de cases */
typedef struct {
    int n; /* Longueur */
    l_cases *lc; /* Contient des listes de cases */
} tab_couples; /* Globalement ça revient à faire un tableau de couple de cases [ [cases1 ; cases 2] , [cases1 ; cases 2] ] etc de longueur n */


typedef struct{
    int score_max;
    int score;
    char *nom_joueur;
} parti;

#endif