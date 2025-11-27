#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "types.h"

/*** Fonction utile pour l'affichage ***/

#define MARGE_H 150
#define MARGE_W 100
#define TITLE_H 50

void plateau_details(plateau *p, int *size, int *offset_x, int *offset_y, int *width, int *height){
    int size_w = (LX - MARGE_W) / p->m;
    int size_h = (LY - MARGE_H) / p->n;

    if(size_w < size_h){
        *size = size_w;
    } else {
        *size = size_h;
    }

    *width  = p->m * (*size);
    *height = p->n * (*size);

    *offset_x = (LX - *width) / 2;
    *offset_y = (LY - *height) / 2 + TITLE_H;
}


/*** Foncitons utiles au bon fonctionnement du code MLV ***/

/* Obtiens les coordonnées de là où clique le joueur */
cases *get_details(plateau *p){
    int s_x, s_y, size, cw, ch, pw, ph;
    cases c;

    MLV_wait_mouse(&s_x, &s_y);

    plateau_details(p, &size, &cw, &ch, &pw, &ph);

    if(s_x < cw || s_x >= cw + pw || s_y < ch || s_y >= ch + ph){
        return NULL;
    }

    c.y = (s_x - cw) / size;
    c.x = (s_y - ch) / size;

    return &p->tab[c.x][c.y];
}