#ifndef _TYPES_H_
#define _TYPES_H_

typedef struct{
    int x;
    int y;
    int valeur;
} cases;

typedef struct{
    cases **tab;
    int n;
    int m;
    /*int cases_vides;*/
} plateau;

/* Type fait pour représenter une paire de cases */
typedef struct{
    int n;
    cases *c;
} l_cases;

/* Type fait pour le bonus d'indice */

typedef struct {
    int n;
    l_cases *lc;
} tab_couples;



/*typedef struct {
    cases c1;
    cases c2;
} couple;*/

    /* Tableau de couples */
/*typedef struct {
    int n;
    couple* tab;
} tab_couples;*/

#endif