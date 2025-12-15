#ifndef _TYPES_H_
#define _TYPES_H_

/* -- Dimension Tableau -- */
#define LX 1920
#define LY 1200

/* -- Longueur max texte boouton -- */
#define LENGTH_TP 10

/* -- VALEUR SELECTION BOUTON -- */
#define SELECT_NONE 0
#define SELECT_USER 1
#define SELECT_CLUE 2

/* -- VALEUR DIFFICULTE -- */
#define NO_CUSTOM 0
#define CUSTOM 1

/* -- TAILLE DES TITRES -- */
#define TITLE_SIZE 120

/* Structure case */
typedef struct{
    int x;
    int y;
    int value;
    int select;
} cases;

/* Structure plateau */
typedef struct{
    cases **tab; 
    int n;
    int m;
    int mode;
    int score_actuel;
} plateau;


/* Paire de 2 cases */
typedef struct{
    int n;
    cases *c;
} l_cases;


/* Tableau de paire de cases */
typedef struct {
    int n;
    l_cases *lc;
} tab_couples;


/* Struct du joueur */
typedef struct{
    int score_max;
    int score;
    char name_player[11];
    int bonus_add_lines;
    int bonus_clue;
    int difficulty;
    double time_elapsed;
} parti;
typedef parti tparti[LENGTH_TP];

/* Menu */
#define L 20

/* Structure bouton */
typedef struct{
  int x;
  int y;
  int height;
  int width;
  char txt[L];
} button;

#endif