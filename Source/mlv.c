#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "../Headers/plateau_mlv.h"
#include "../Headers/types.h"

/*** Fonction utile pour l'affichage ***/

#define MARGE_H 150
#define MARGE_W 100
#define TITLE_H 50

void plateau_details(plateau *p, int *size, int *offset_x, int *offset_y, int *width, int *height){
    int size_w, size_h;

    /* Empêcher une division par 0 */
    if(p->n <= 0|| p->m < 0){
        *size = 0;
        *width = 0;
        *height = 0;
        *offset_x = 0;
        *offset_y = 0;
        return;
    }
    
    size_w = (LX - MARGE_W) / p->m;
    size_h = (LY - MARGE_H) / p->n;

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
cases* get_details(plateau *p, int mx, int my){
    int x0 = (LX - p->m * CASES) / 2;
    int y0 = 150;
    int i, j, x, y;
    int real_visible = VISIBLE;
    if(offset + VISIBLE > p->n){
        real_visible = p->n - offset;
    }

    for(i = 0; i < real_visible; i++){
        for(j = 0; j < p->m; j++){
            x = x0 + j * CASES; y = y0 + i * CASES;
            if(mx >= x && mx <= x + CASES && my >= y && my <= y + CASES){
                return &p->tab[offset + i][j];
            }
        }
    }
    return NULL;
}