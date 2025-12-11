#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include <time.h>
#include "../Headers/mlv.h"
#include "../Headers/menu.h"
#include "../Headers/plateau_mlv.h"
#include "../Headers/types.h"

int offset = 0;

void display_plateau_mlv(plateau *p, button t_button_game[5], double elapsed) {
    /* Déclarations des variables en début de fonction */
    int real_visible, x0, y0, val, select;
    int size_p, text_width, text_height, i, j, x, y, l_p, space, bx, by, x_dot, y_dot;
    int width_img, height_img;
    char text[25], chrono[64];
    char *name_button[5] = {"↑", "↓", "ADD LINES", "CLUE", "PAUSE"};
    MLV_Font *police_title, *police_box, *police_timer, *police_but_score, *police_arrow;
    MLV_Image *image = NULL;  /* Pointeur pour l'image du nombre */
    MLV_Image *background = NULL;  /* Pointeur pour l'image de fond */
    MLV_Color wood_color = MLV_rgba(139, 69, 19, 255);  /* Couleur bois pour les cases du plateau */
    
    /* Initialiser la fenêtre */
    MLV_clear_window(MLV_rgba(122, 125, 125, 255));

    /* Charger et afficher le fond d'écran (image de pierre) */
    background = MLV_load_image("./Assets/background_key.png");
    MLV_resize_image_with_proportions(background, LX+250, LY+250);  /* Redimensionner l'image pour qu'elle couvre tout l'écran */
    MLV_draw_image(background, 0, 0);
    MLV_free_image(background);  /* Libérer l'image une fois qu'elle est dessinée */

    /* Chargement de la police */
    size_p = 40;
    police_timer = MLV_load_font("./Font/Crang.ttf", size_p);

    /* Affichage du chrono */
    sprintf(chrono, "Temps : %02d:%02d", (int)(elapsed / 60), (int)elapsed % 60);
    MLV_get_size_of_adapted_text_box_with_font(chrono, police_timer, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font(LX - text_width, 25, chrono, police_timer, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
    
    /* Chargement de la police */
    size_p = 80;
    police_title = MLV_load_font("./Font/Crang.ttf", size_p);
    

    /* Affichage du titre "NUMBER MATCH" */
    MLV_get_size_of_adapted_text_box_with_font("NUMBER MATCH", police_title, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font((LX - text_width) / 2, 25, "NUMBER MATCH", police_title, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    /* Ajuster l'offset pour afficher les cases visibles */
    if (offset < 0) {
        offset = 0;
    }

    if (offset > p->n - VISIBLE) {
        offset = p->n - VISIBLE;
    }
    if (offset < 0) {
        offset = 0;
    }

    if (offset + VISIBLE > p->n) {
        real_visible = p->n - offset;
    } else {
        real_visible = VISIBLE;
    }

    /* Calcul des coordonnées du plateau */
    l_p = p->m * CASES;
    x0 = (LX - l_p) / 2;
    y0 = 150;

    /* Police pour les cases */
    size_p = 40;
    police_box = MLV_load_font("./Font/Crang.ttf", size_p);

    /* Affichage du plateau de jeu */
    if (p->mode == 0) {  /* Mode classique */
        for (i = 0; i < real_visible; i++) {
            for (j = 0; j < p->m; j++) {
                x = x0 + j * CASES;
                y = y0 + i * CASES;

                /* Dessiner la case avec des coins arrondis en couleur bois */
                MLV_draw_filled_rectangle(x, y, CASES, CASES, MLV_ALPHA_TRANSPARENT);

                val = p->tab[offset + i][j].value;
                select = p->tab[offset + i][j].select;

                /* Affichage du texte dans les cases selon leur état */
                if (select == SELECT_USER) {
                    sprintf(text, "%d", p->tab[offset + i][j].value);
                    MLV_draw_text_box_with_font(x, y, CASES, CASES, text, police_box, 10, MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_GREEN, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
                } else if (select == SELECT_CLUE) {
                    sprintf(text, "%d", val);
                    MLV_draw_text_box_with_font(x, y, CASES, CASES, text, police_box, 10, MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_rgba(255, 215, 0, 255), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
                } else if (val != 0) {
                    sprintf(text, "%d", val);
                    MLV_draw_text_box_with_font(x, y, CASES, CASES, text, police_box, 10, MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_rgba(147, 172, 199, 255), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
                } else { 
                    MLV_draw_text_box_with_font(x, y, CASES, CASES, "", police_box, 10, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_rgba(179, 197, 215, 255), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER); 
                }
            }
        }
    } else if (p->mode == 1) {  /* Mode serrure */
        for (i = 0; i < real_visible; i++) {
            for (j = 0; j < p->m; j++) {
                x = x0 + j * CASES;
                y = y0 + i * CASES;

                /* Dessiner la case avec des coins arrondis en couleur bois */
                MLV_draw_filled_rectangle(x, y, CASES, CASES, wood_color);

                val = p->tab[offset + i][j].value;
                sprintf(text, "./Assets/%d.png", val);
                image = MLV_load_image(text);  /* Charger l'image du nombre */
                if (image != NULL) {
                    MLV_resize_image_with_proportions(image, CASES - 10, CASES - 10);
                    MLV_get_image_size(image, &width_img, &height_img);
                    MLV_draw_image(image, x + 10, y + 5);
                    MLV_free_image(image);  /* Libérer l'image une fois utilisée */
                } else {
                    MLV_draw_text_box_with_font(x, y, CASES, CASES, "", police_box, 10, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_rgba(179, 197, 215, 255), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
                }
            }
        }
    }

    /* Affichage du texte "..." si le plateau est plus grand que la zone visible */
    if (offset + VISIBLE < p->n) {
        x_dot = x0 + (l_p - 30) / 2;
        y_dot = y0 + real_visible * CASES + 10;

        MLV_draw_text_with_font(x_dot, y_dot, ". . .", police_box, MLV_COLOR_BLACK);
    }

    /* Affichage des boutons */
    size_p = 200;
    police_arrow = MLV_load_font("./Font/Crang.ttf", size_p);
    bx = x0 + l_p + size_p;
    by = y0 + 50;

    if (p->n > VISIBLE) {
        create_button(&t_button_game[0], name_button[0], bx, by, police_arrow);
        display_text(t_button_game[0], police_arrow); 
        
        create_button(&t_button_game[1], name_button[1], bx, by + size_p, police_arrow);
        display_text(t_button_game[1], police_arrow);
    } else {
        create_button(&t_button_game[0], name_button[0], -1000, -1000, police_arrow);
        create_button(&t_button_game[1], name_button[1], -1000, -1000, police_arrow);
    }

    /* Affichage des autres boutons */
    space = 150;
    size_p = 50;
    police_but_score = MLV_load_font("./Font/Crang.ttf", size_p);
    bx = x0 / 2;

    for (i = 2; i < 5; i++) {
        by = y0 + (i - 2) * space;
        create_button(&t_button_game[i], name_button[i], bx, by, police_but_score);
        display_text(t_button_game[i], police_but_score);
    }

    /* Affichage du score */
    by = y0 + (i - 2) * (space * 2);
    sprintf(text, "SCORE : %d", p->score_actuel);
    MLV_get_size_of_adapted_text_box_with_font(text, police_but_score, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font(10, by, text, police_but_score, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_LEFT);

    /* Libérer la police après utilisation */
    MLV_free_font(police_timer);
    MLV_free_font(police_title);
    MLV_free_font(police_box);
    MLV_free_font(police_arrow);
    MLV_free_font(police_but_score);
}
