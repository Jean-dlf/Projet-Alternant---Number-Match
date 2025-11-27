#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "mlv.h"
#include "game_logic.h"

/* verifie si on clique sur un bouton */
int verif(button button, int coord_x, int coord_y){
    if((coord_x > button.x && coord_x < button.x + button.width) && (coord_y > button.y && coord_y < button.y + button.height)){
        return 1;
    }
    return 0;
}

/* renvoie la valeur button clique */
int clic_button(button t_button[], int length){
    int i, s_x, s_y;

    MLV_wait_mouse(&s_x, &s_y);
    for( i = 0; i < length; i++ ){
        if(verif(t_button[i], s_x, s_y) == 1 ){
            return i;
        }
    }
    return i;
}

/* cree un button */
void create_button(button *button, char* message, int x, int y, MLV_Font *police){
    int width, height;
    MLV_get_size_of_adapted_text_box_with_font(message, police, 10, &width, &height);
    button -> x = x - width/2;
    button -> y = y;
    button -> height = height;
    button -> width = width;
    strcpy(button -> txt, message);    
}

/* affiche le texte dun button */
void display_text(button button , MLV_Font *police){
    MLV_draw_adapted_text_box_with_font( button.x, button.y, button.txt, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
}

/* display du menu principal */
void menu_p(button t_button_menu[5]){
    char *name_button[5] = {"START", "SAVE", "RULES", "SCORE", "EXIT"}; 
    int text_width, text_height, i, size_p;
    MLV_Font *police;

    
    MLV_clear_window(MLV_COLOR_BEIGE);

    /* Titre */
    size_p = 180;
    police = MLV_load_font("./game_over.ttf", size_p);

    MLV_get_size_of_adapted_text_box_with_font("NUMBER MATCH", police, 10, &text_width, &text_height);
  
    MLV_draw_adapted_text_box_with_font((LX - text_width) / 2, text_height / 3 - 25, "NUMBER MATCH", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    size_p = 150;
    police = MLV_load_font("./game_over.ttf", size_p);

    for(i = 0; i < 5; i++){
        create_button(&t_button_menu[i], name_button[i], LX / 2, 150 + i * 120, police);
        display_text(t_button_menu[i], police);
    }

    MLV_free_font(police);
    MLV_actualise_window();
}

void menu_save(button t_button_save[5]){
    char *name_button_save[5] = {"SAVE 1", "SAVE 2", "SAVE 3", "SAVE 4", "BACK"};
    int text_width, text_height, i, size_p;
    MLV_Font *police;
        
    MLV_clear_window(MLV_COLOR_BEIGE);

    size_p = 180;
    police = MLV_load_font("./game_over.ttf", size_p);

    /* Titre */
    MLV_get_size_of_adapted_text_box_with_font("SAVE", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3 - 25, "SAVE", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    size_p = 100;
    police = MLV_load_font("./game_over.ttf", size_p);
    
    /* button save */
    for(i = 0; i < 5; i++){
        create_button(&t_button_save[i], name_button_save[i], LX / 2, 150 + i * 100, police);
        display_text(t_button_save[i], police);
    }

    MLV_free_font(police);
    MLV_actualise_window();
}

void menu_rules(button *back){
    char display[500];
    char *name_button_back[1] = {"BACK"};
    int text_width, text_height, width_img, height_img, x, size_p;
    MLV_Font *police;
    MLV_Image *image[1];
    char *name_image[1] = {"./number_match.png"};

    MLV_clear_window(MLV_COLOR_BEIGE);

    size_p = 180;
    police = MLV_load_font("./game_over.ttf", size_p);

    /* Titre */
    MLV_get_size_of_adapted_text_box_with_font("RULES", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3 - 25, "RULES", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    /* Texte */
    size_p = 60;
    police = MLV_load_font("./game_over.ttf", size_p);

    sprintf(display, "VOTRE OBJECTIF : VIDER LE PLATEAU DE JEU\nPOUR CELA VOUS DEVEZ TROUVER DES PAIRES DE CHIFFRES IDENTIQUES\nLES PAIRES PEUVENT ETRE :\n -HORIZONTALES --- (FLECHE ROUGE)\n-VERTICALES --- (FLECHE ORANGE)\n-EN DIAGONALE --- (FLECHE VIOLETTE)\n-OU UN CHIFFRE EN FIN DE LIGNE ET L'AUTRE AU DEBUT DE LA SUIVANTE\n --- (FLECHE BLEUE)\n");
    MLV_get_size_of_adapted_text_box_with_font(display, police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3, display, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    /* button back */
    size_p = 80;
    police = MLV_load_font("./game_over.ttf", size_p);

    create_button(back, name_button_back[0], 60, 1, police);
    display_text(*back, police);

    /* Image */
    x = LX / 2;

    image[0] = MLV_load_image(name_image[0]);
    MLV_resize_image_with_proportions(image[0], 300, 300);
    MLV_get_image_size(image[0], &width_img, &height_img);
    MLV_draw_image(image[0], x - (width_img / 2), LY - height_img - 25);
    MLV_free_image(image[0]);

    MLV_free_font(police);
    MLV_actualise_window();
}

void menu_score(button *back) {
    char *name_button_score[10] = {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th"};
    char display[200];
    char *name_button_back[1] = {"BACK"};
    tparti t_score;
    int text_width, text_height, i, k, size_p;
    MLV_Font *police;
    MLV_Color color;

    MLV_clear_window(MLV_COLOR_BEIGE);

    /* Titre */
    size_p = 180;
    police = MLV_load_font("./game_over.ttf", size_p);

    MLV_get_size_of_adapted_text_box_with_font("HIGH SCORES", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font((LX - text_width) / 2, text_height / 3 - 25, "HIGHT SCORES", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    size_p = 80;
    police = MLV_load_font("./game_over.ttf", size_p);
    k = 0;

    for(i = 0; i < 10; i++) {
        switch(i){
            case 0:
            color = MLV_rgba(255, 215, 0, 255);
            break;

            case 1:
            color = MLV_rgba(192, 192, 192, 255);
            break;

            case 2:
            color = MLV_rgba(205, 127, 50, 255);
            break;

            default:
            color = MLV_COLOR_BLACK;
            break;
        }
        sprintf(display, "%s --   Score = %d   |   Pseudo = %s   |   Timer = ", name_button_score[i], 80, "Oui" /* t_score[i].score, t_score[i].nom_joueur */);
        MLV_get_size_of_adapted_text_box_with_font(display, police, 10, &text_width, &text_height);
        MLV_draw_adapted_text_box_with_font(30, text_height / 3 + 100 + k, display, police, 10, MLV_ALPHA_TRANSPARENT, color, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
        k += 60;
    }

    size_p = 80;
    police = MLV_load_font("./game_over.ttf", size_p);

    create_button(back, name_button_back[0], 60, 0, police);
    display_text(*back, police);

    MLV_free_font(police);
    MLV_actualise_window();
}