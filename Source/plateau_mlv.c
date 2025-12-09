#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include <time.h>
#include "../Headers/mlv.h"
#include "../Headers/menu.h"
#include "../Headers/plateau_mlv.h"
#include "../Headers/types.h"

int offset = 0;

void display_plateau_mlv(plateau *p, button t_button_game[5]){
    int real_visible, x0, y0, val, select;
    int size_p, text_width, text_height, i, j, x, y, l_p, space, bx, by, x_dot, y_dot;
    int width_img, height_img;
    char text[25];
    char *name_button[5] = {"↑", "↓", "ADD LINES", "CLUE", "PAUSE"};
    MLV_Font *police;
    MLV_Image *image[1];
    
    MLV_clear_window(MLV_rgba(122, 125, 125, 255));

    size_p = 80;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    MLV_get_size_of_adapted_text_box_with_font("NUMBER MATCH", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, 25, "NUMBER MATCH", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    
    if(offset < 0){
        offset = 0;
    }
    
    if(offset > p->n - VISIBLE){
        offset = p->n - VISIBLE;
    }
    if(offset < 0){
        offset = 0;
    }
    
    if(offset + VISIBLE > p->n){
        real_visible = p->n - offset;
    } else {
        real_visible = VISIBLE;
    }

    l_p = p->m * CASES;

    x0 = (LX - l_p) / 2;
    y0 = 150;

    size_p = 40;
    police = MLV_load_font("./Font/Crang.ttf", size_p);
    
    if(p->mode == 0){
        for(i = 0; i < real_visible; i++){
            for(j = 0; j < p->m; j++){
                x = x0 + j * CASES;
                y = y0 + i * CASES;
    
                MLV_draw_rectangle(x, y, CASES, CASES, MLV_COLOR_BLACK);
    
                val = p->tab[offset + i][j].value;
                select = p->tab[offset + i][j].select;
    
                /* -- Classique -- */
                if(select == SELECT_USER){
                    sprintf(text, "%d", p->tab[offset +  i][j].value);
                    MLV_draw_text_box_with_font(x, y, CASES, CASES, text, police, 10, MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_GREEN, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
                } else if(select == SELECT_CLUE){
                    sprintf(text, "%d", val);
                    MLV_draw_text_box_with_font(x, y, CASES, CASES, text, police, 10, MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_rgba(255, 215, 0, 255), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
                } else if(val != 0){
                        sprintf(text, "%d", val);
                        MLV_draw_text_box_with_font(x, y, CASES, CASES, text, police, 10, MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_rgba(147, 172, 199, 255), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
                } else { 
                        MLV_draw_text_box_with_font(x, y, CASES, CASES, "", police, 10, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_rgba(179, 197, 215, 255), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER); 
                }
            }
        }
    /* -- Mode serrure -- */
    } else if(p->mode == 1){
        for(i = 0; i < real_visible; i++){
            for(j = 0; j < p->m; j++){
                x = x0 + j * CASES;
                y = y0 + i * CASES;

                MLV_draw_rectangle(x, y, CASES, CASES, MLV_COLOR_BLACK);

                val = p->tab[offset + i][j].value;

                sprintf(text, "./Assets/%d.png", val);
                image[0] = MLV_load_image(text);
                if(image[0] != NULL){
                    MLV_resize_image_with_proportions(image[0], CASES - 10, CASES - 10);
                    MLV_get_image_size(image[0], &width_img, &height_img);
                    MLV_draw_image(image[0], x + 10, y + 5);
                    MLV_free_image(image[0]);
                } else {
                    MLV_draw_text_box_with_font(x, y, CASES, CASES, "", police, 10, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_rgba(179, 197, 215, 255), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
                }
            }
        }
    }
        
    if(offset + VISIBLE < p->n){
        x_dot = x0 + (l_p - 30) / 2;
        y_dot = y0 + real_visible * CASES + 10;

        MLV_draw_text_with_font(x_dot, y_dot, ". . .", police, MLV_COLOR_BLACK);
    }

    size_p = 400;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    bx = x0 + l_p + (size_p / 2);
    by = y0 + 50;
    
    if(p->n > VISIBLE){

        /* -- UP / DOWN -- */
        create_button(&t_button_game[0], name_button[0], bx, by, police);
        display_text(t_button_game[0], police); 
        
        create_button(&t_button_game[1], name_button[1], bx, by + size_p, police);
        display_text(t_button_game[1], police);
    } else {
        /* Initialiser des boutons "muets" hors écran ou à des coordonnées neutres pour empêcher des bugs de mémoire */
        create_button(&t_button_game[0], name_button[0], -1000, -1000, police);
        create_button(&t_button_game[1], name_button[1], -1000, -1000, police);
    }
    
    MLV_free_font(police);

    /* -- BOUTONS -- */
    
    space = 150;
    size_p = 50;
    police = MLV_load_font("./Font/Crang.ttf", size_p);
    bx = x0 / 2;

    for(i = 2; i < 5; i++){
        by = y0 + (i - 2) * space;
        create_button(&t_button_game[i], name_button[i], bx, by, police);
        display_text(t_button_game[i], police);
    }

    by = y0 + (i - 2) * space;
    
    sprintf(text,"SCORE : %d",p->score_actuel);
    
    MLV_get_size_of_adapted_text_box_with_font(text, police, 10, &text_width, &text_height);
    
    MLV_draw_adapted_text_box_with_font( bx/2, by, text, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_LEFT);
    
    MLV_free_font(police);
}

