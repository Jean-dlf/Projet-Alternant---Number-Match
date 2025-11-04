
/*plateau.c*/

#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include <time.h>

void afficher_plateau(plateau *p){
    int i, j,x,y,larg,haut;
    char nb[3];
    x = 150;
    y = 100;
    larg = 30;
    haut = 30;
    MLV_create_window("number match", "plateau", 640,480);
    
    for(i = 0; i < p->n;i++){
        for(j = 0; j < p->m; j++){
            sprintf(nb,"%d",p->tab[i][j].valeur);
            MLV_draw_text_box(x,y,larg,haut,nb,5,MLV_COLOR_BLACK,MLV_COLOR_BLACK,MLV_COLOR_WHITE,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
            x+=larg;
        }
        x = 150;
        y += haut;
    }
    MLV_actualise_window();
}