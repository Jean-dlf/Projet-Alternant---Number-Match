#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include <time.h>
#include "../Headers/mlv.h"
#include "../Headers/menu.h"
#include "../Headers/types.h"

void display_plateau_mlv(plateau *p, button t_button_game[3]){
    int size_p, i, j, x, y, size, cw, ch, pw, ph, gap;
    int width_img, height_img;
    char text[25];
    char *name_button[3] = {"ADD LINES", "CLUE", "PAUSE"};
    MLV_Font *police;
    MLV_Image *image[1];
    
    MLV_clear_window(MLV_rgba(115, 146, 183, 255));

    size_p = 100;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    /*MLV_get_size_of_adapted_text_box_with_font("NUMBER MATCH", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, 25, "NUMBER MATCH", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);*/

    MLV_free_font(police);

    plateau_details(p, &size, &cw, &ch, &pw, &ph);

    size_p = size;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    if((p->mode) == 0){
        for(i = 0; i < p->n; i++){
            for(j = 0; j < p->m; j++){
                x = cw + j * size;
                y = ch + i * size;

                MLV_draw_rectangle(x, y, size, size, MLV_COLOR_BLACK);
                if(p->tab[i][j].select == 1){
                    sprintf(text, "%d", p->tab[i][j].value);
                    MLV_draw_text_box_with_font(x, y, size, size, text, police, 10, MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_GREEN, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
                }else if(p->tab[i][j].value == 0){
                    MLV_draw_text_box_with_font(x, y, size, size, "", police, 10, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_rgba(179, 197, 215, 255), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
                } else {
                    sprintf(text, "%d", p->tab[i][j].value);
                    MLV_draw_text_box_with_font(x, y, size, size, text, police, 10, MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_rgba(147, 172, 199, 255), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
                }
            }
        }
    } else if(p->mode == 1){
        for(i = 0; i < p->n; i++){
            for(j = 0; j < p->m; j++){
                x = cw + j * size;
                y = ch + i * size;
                
                MLV_draw_rectangle(x, y, size, size, MLV_COLOR_BLACK);
                
                sprintf(text, "./Assets/%d.png", p->tab[i][j].value);
               
                image[0] = MLV_load_image(text);
                MLV_resize_image_with_proportions(image[0], size-10, size-10);
                MLV_get_image_size(image[0], &width_img, &height_img);
                MLV_draw_image(image[0], x+10, y+5);
                MLV_free_image(image[0]);
            }  
        }
    }
    MLV_free_font(police);

    /* Bouton Bonus */
    size_p = 100;
    police = MLV_load_font("./Font/game_over.ttf", size_p);
    gap = 300;

    create_button(&t_button_game[0], name_button[0], (LX / 2) - gap, 25, police);
    display_text(t_button_game[0], police);
    
    create_button(&t_button_game[1], name_button[1], (LX / 2), 25, police);
    display_text(t_button_game[1], police);

    create_button(&t_button_game[2], name_button[2], (LX / 2) + gap, 25, police);
    display_text(t_button_game[2], police);

    MLV_free_font(police);
    MLV_actualise_window();
}







/* ------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------ */
/* ---------------------------- VERSION AVEC FLECHES ---------------------------- */
/* ------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------ */

void display_plateau_mlv2(plateau *p, button t_button_game[3]){
    int size_p, i, j, x, y, size, cw, ch, pw, ph, gap;
    int width_img, height_img;
    char text[25];
    char *name_button[3] = {"ADD LINES", "CLUE", "PAUSE"};
    MLV_Font *police;
    MLV_Image *image[1];
    
    MLV_clear_window(MLV_COLOR_BEIGE);

    size_p = 100;
    police = MLV_load_font("./Font/game_over.ttf", size_p);

    /*MLV_get_size_of_adapted_text_box_with_font("NUMBER MATCH", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, 25, "NUMBER MATCH", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);*/

    MLV_free_font(police);

    plateau_details(p, &size, &cw, &ch, &pw, &ph);

    size_p = size / 2;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    if((p->mode) == 0){
        for(i = 0; i < p->n; i++){
            for(j = 0; j < p->m; j++){
                x = cw + j * size;
                y = ch + i * size;

                MLV_draw_rectangle(x, y, size, size, MLV_COLOR_BLACK);

                if(p->tab[i][j].value != 0){
                    sprintf(text, "%d", p->tab[i][j].value);
                    MLV_draw_text_box_with_font(x, y, size, size, text, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
                } else { 
                    MLV_draw_text_box_with_font(x, y, size, size, "", police, 10, MLV_ALPHA_TRANSPARENT, MLV_ALPHA_TRANSPARENT, MLV_rgba(128, 128, 128, 128), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER); 
                }
            }
        }
    } else if(p->mode == 1){
        for(i = 0; i < p->n; i++){
            for(j = 0; j < p->m; j++){
                x = cw + j * size;
                y = ch + i * size;
                
                MLV_draw_rectangle(x, y, size, size, MLV_COLOR_BLACK);
                
                sprintf(text, "./Assets/%d.png", p->tab[i][j].value);
               
                image[0] = MLV_load_image(text);
                MLV_resize_image_with_proportions(image[0], size-10, size-10);
                MLV_get_image_size(image[0], &width_img, &height_img);
                MLV_draw_image(image[0], x+10, y+5);
                MLV_free_image(image[0]);
            }  
        }
    }
    MLV_free_font(police);

    /* Bouton Bonus */
    size_p = 100;
    police = MLV_load_font("./Font/game_over.ttf", size_p);
    gap = 300;

    create_button(&t_button_game[0], name_button[0], (LX / 2) - gap, 25, police);
    display_text(t_button_game[0], police);
    
    create_button(&t_button_game[1], name_button[1], (LX / 2), 25, police);
    display_text(t_button_game[1], police);

    create_button(&t_button_game[2], name_button[2], (LX / 2) + gap, 25, police);
    display_text(t_button_game[2], police);

    MLV_free_font(police);
    MLV_actualise_window();
}

