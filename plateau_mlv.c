#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include <time.h>
#include "mlv.h"
#include "menu.h"
#include "types.h"

void display_plateau_mlv(plateau *p, button t_button_game[2]){
    int size_p, text_width, text_height, i, j, x, y, size, cw, ch, pw, ph, gap;
    char text[10];
    char *name_button[2] = {"ADD LINES", "CLUE"};
    MLV_Font *police;

    MLV_clear_window(MLV_COLOR_BEIGE);

    size_p = 100;
    police = MLV_load_font("./game_over.ttf", size_p);

    /*MLV_get_size_of_adapted_text_box_with_font("NUMBER MATCH", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, 25, "NUMBER MATCH", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);*/

    plateau_details(p, &size, &cw, &ch, &pw, &ph);

    for(i = 0; i < p->n; i++){
        for(j = 0; j < p->m; j++){
            x = cw + j * size;
            y = ch + i * size;

            MLV_draw_rectangle(x, y, size, size, MLV_COLOR_BLACK);

            sprintf(text, "%d", p->tab[i][j].value);
            size_p = size;
            police = MLV_load_font("./game_over.ttf", size_p);

            MLV_draw_text_box_with_font(x, y, size, size, text, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

            MLV_free_font(police);
        }
    }

    /* Bouton Bonus */
    size_p = 100;
    police = MLV_load_font("./game_over.ttf", size_p);
    gap = 300;

    create_button(&t_button_game[0], name_button[0], (LX / 2) - gap/2, 25, police);
    display_text(t_button_game[0], police);
    
    create_button(&t_button_game[1], name_button[1], (LX / 2) + gap/2, 25, police);
    display_text(t_button_game[1], police);

    MLV_free_font(police);
    MLV_actualise_window();
}