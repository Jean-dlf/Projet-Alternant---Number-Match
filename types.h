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

typedef struct{
    int n;
    cases *c;
} l_cases;

#endif