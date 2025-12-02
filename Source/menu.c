#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "../Headers/types.h"
#include "../Headers/mlv.h"
#include "../Headers/save.h"
#include "../Headers/game_logic.h"
#include "../Headers/score.h"

/* verifie si on clique sur un bouton */
int verif(button button, int coord_x, int coord_y){
    if((coord_x > button.x && coord_x < button.x + button.width) && (coord_y > button.y && coord_y < button.y + button.height)){
        return 1;
    }
    return 0;
}

/* renvoie la valeur button clique */
int clic_button(button t_button[], int length, int mx, int my){
    int i;

    for(i = 0; i < length; i++){
        if(verif(t_button[i], mx, my) == 1 ){
            return i;
        }
    }
    return -1;
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
    police = MLV_load_font("./Font/game_over.ttf", size_p);

    MLV_get_size_of_adapted_text_box_with_font("NUMBER MATCH", police, 10, &text_width, &text_height);
  
    MLV_draw_adapted_text_box_with_font((LX - text_width) / 2, text_height / 3 - 25, "NUMBER MATCH", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    size_p = 150;
    police = MLV_load_font("./Font/game_over.ttf", size_p);

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
    police = MLV_load_font("./Font/game_over.ttf", size_p);

    /* Titre */
    MLV_get_size_of_adapted_text_box_with_font("SAVE", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3 - 25, "SAVE", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    size_p = 100;
    police = MLV_load_font("./Font/game_over.ttf", size_p);
    
    /* button save */
    for(i = 0; i < 5; i++){
        create_button(&t_button_save[i], name_button_save[i], LX / 2, 150 + i * 100, police);
        display_text(t_button_save[i], police);
    }

    MLV_free_font(police);
    MLV_actualise_window();
}

void menu_mode(button t_button_mode[3]){
    char *name_button_mode[3] = {"NORMAL", "SERRURIER", "BACK"};
    int text_width, text_height, i, size_p;
    int width_img, height_img, x;
    MLV_Font *police;
    MLV_Image *image[1];
    char *name_image[1] = {"./Assets/cadena_icone_mode_jeu.png"};
        
    MLV_clear_window(MLV_COLOR_BEIGE);

    size_p = 180;
    police = MLV_load_font("./Font/game_over.ttf", size_p);

    /* Titre */
    MLV_get_size_of_adapted_text_box_with_font("MODE DE JEU", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3 - 25, "MODE DE JEU", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    MLV_free_font(police);

    size_p = 150;
    police = MLV_load_font("./Font/game_over.ttf", size_p);
    
    /* button mode */
    for(i = 0; i < 3; i++){
        create_button(&t_button_mode[i], name_button_mode[i], LX / 2, 150 + i * 100, police);
        display_text(t_button_mode[i], police);
    }

    x = LX / 2;

    image[0] = MLV_load_image(name_image[0]);
    MLV_resize_image_with_proportions(image[0], 60, 60);
    MLV_get_image_size(image[0], &width_img, &height_img);
    MLV_draw_image(image[0], x - 215, LY - 525);
    MLV_free_image(image[0]);

    image[0] = MLV_load_image(name_image[0]);
    MLV_resize_image_with_proportions(image[0], 60, 60);
    MLV_get_image_size(image[0], &width_img, &height_img);
    MLV_draw_image(image[0], x + 180, LY - 525);
    MLV_free_image(image[0]);
    

    MLV_free_font(police);
    MLV_actualise_window();
}

void menu_choice_mode(button t_button_choice_mode[3]){
    char *name_button_choice_mode[3] = {"CLASSIC", "LOCKSMITH", "BACK"};
    int text_width, text_height, i, size_p;
    MLV_Font *police;

    MLV_clear_window(MLV_COLOR_BEIGE);

    size_p = 180;
    police = MLV_load_font("./Font/game_over.ttf", size_p);

    MLV_get_size_of_adapted_text_box_with_font("SELECT MODE", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font((LX - text_width) / 2, text_height / 3, "SELECT MODE", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    MLV_free_font(police);

    size_p = 100;
    police = MLV_load_font("./Font/game_over.ttf", size_p);

    for(i = 0; i < 3; i++){
        create_button(&t_button_choice_mode[i], name_button_choice_mode[i], LX / 2, LX / 3 + i * 100, police);
        display_text(t_button_choice_mode[i], police);
    }

    MLV_free_font(police);
    MLV_actualise_window();
}

int choice_mode_game(){
    button t_bouton_choice_mode[3];
    int pressed, mx, my;

    menu_choice_mode(t_bouton_choice_mode);

    MLV_wait_mouse(&mx, &my);
    pressed = clic_button(t_bouton_choice_mode, 3, mx, my);
    
    return pressed;
}

void menu_rules(button *back){
    char display[500];
    char *name_button_back[1] = {"BACK"};
    int text_width, text_height, width_img, height_img, x, size_p;
    MLV_Font *police;
    MLV_Image *image[1];
    char *name_image[1] = {"./Assets/number_match.png"};

    MLV_clear_window(MLV_COLOR_BEIGE);

    size_p = 180;
    police = MLV_load_font("./Font/game_over.ttf", size_p);

    /* Titre */
    MLV_get_size_of_adapted_text_box_with_font("RULES", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3 - 25, "RULES", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    /* Texte */
    size_p = 60;
    police = MLV_load_font("./Font/game_over.ttf", size_p);

    sprintf(display, "VOTRE OBJECTIF : VIDER LE PLATEAU DE JEU\nPOUR CELA VOUS DEVEZ TROUVER DES PAIRES DE CHIFFRES IDENTIQUES\nLES PAIRES PEUVENT ETRE :\n -HORIZONTALES --- (FLECHE ROUGE)\n-VERTICALES --- (FLECHE ORANGE)\n-EN DIAGONALE --- (FLECHE VIOLETTE)\n-OU UN CHIFFRE EN FIN DE LIGNE ET L'AUTRE AU DEBUT DE LA SUIVANTE\n --- (FLECHE BLEUE)\n");
    MLV_get_size_of_adapted_text_box_with_font(display, police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3, display, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    /* button back */
    size_p = 80;
    police = MLV_load_font("./Font/game_over.ttf", size_p);

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
    tparti t_player;
    int text_width, text_height, i, k, size_p;
    MLV_Font *police;
    MLV_Color color;

    MLV_clear_window(MLV_COLOR_BEIGE);

    /* Titre */
    size_p = 180;
    police = MLV_load_font("./Font/game_over.ttf", size_p);

    MLV_get_size_of_adapted_text_box_with_font("HIGH SCORES", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font((LX - text_width) / 2, text_height / 3 - 25, "HIGHT SCORES", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    size_p = 80;
    police = MLV_load_font("./Font/game_over.ttf", size_p);
    k = 0;

    
    if(collect_score("./Save/score.txt", t_player) == -1){
        fprintf(stderr, "Erreur lors de la récupération des scores\n");
        return ;
    }


    for(i = 0; i < 10; i++) {
        switch(i){
            case 0:
            /* OR */
            color = MLV_rgba(255, 215, 0, 255);
            break;

            case 1:
            /* ARGENT */
            color = MLV_rgba(192, 192, 192, 255);
            break;

            case 2:
            /* BRONZE */
            color = MLV_rgba(205, 127, 50, 255);
            break;

            default:
            color = MLV_COLOR_BLACK;
            break;
        }
        sprintf(display, "%s --   Score = %d   |   Pseudo = %s", name_button_score[i], t_player[i].score, t_player[i].name_player);
        MLV_get_size_of_adapted_text_box_with_font(display, police, 10, &text_width, &text_height);
        MLV_draw_adapted_text_box_with_font(30, text_height / 3 + 100 + k, display, police, 10, MLV_ALPHA_TRANSPARENT, color, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
        k += 60;
    }

    size_p = 80;
    police = MLV_load_font("./Font/game_over.ttf", size_p);

    create_button(back, name_button_back[0], 60, 0, police);
    display_text(*back, police);

    MLV_free_font(police);
    MLV_actualise_window();
}

void menu_pause(button t_bouton_pause[3]){
    char *name_button_pause[3] = {"RESUME", "SAVE", "QUIT"};
    int text_width, text_height, i, size_p;
    MLV_Font *police;

    MLV_clear_window(MLV_COLOR_BEIGE);
    
    size_p = 180;
    police = MLV_load_font("./Font/game_over.ttf", size_p);

    MLV_get_size_of_adapted_text_box_with_font("PAUSE", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font((LX - text_width) / 2, text_height / 3, "PAUSE", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    size_p = 100;
    police = MLV_load_font("./Font/game_over.ttf", size_p);


    for(i = 0; i < 3; i++){
        create_button(&t_bouton_pause[i], name_button_pause[i], LX / 2, LY / 3 + i * 100, police);
        display_text(t_bouton_pause[i], police);
    }

    MLV_free_font(police);
    MLV_actualise_window();
}

int crushing_save(){
    MLV_Keyboard_button key;
    MLV_Font *police;
    int size_p, text_width, text_height;

    MLV_clear_window(MLV_COLOR_BEIGE);

    size_p = 180;
    police = MLV_load_font("./Font/game_over.ttf", size_p);

    MLV_get_size_of_adapted_text_box_with_font("CRUSH THE SAVE : (O/N)", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font((LX - text_width) / 2, text_height / 3, "CRUSH THE SAVE : (O/N)", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
    
    MLV_actualise_window();
    MLV_wait_keyboard(&key, NULL, NULL);

    if(key == MLV_KEYBOARD_o){
        return 1;
    } else if(key == MLV_KEYBOARD_n){
        return 0;
    }
    return -1;
}

void save_pause_management(parti *plyr, plateau *p, int pressed){
    char *name_save[4] = {"./Save/save1.txt", "./Save/save2.txt", "./Save/save3.txt", "./Save/save4.txt"};
    int crushed;
    FILE *f;

    f = fopen(name_save[pressed], "r");

    if(f == NULL){
        if(save_game(name_save[pressed], plyr, p) == 1){
            printf("Partie bien sauvegardé\n");
        }
    } else {
        fclose(f);
        crushed = crushing_save();
        if(crushed){
            if(save_game(name_save[pressed], plyr, p) == 1){
                printf("Partie bien sauvegardé après confirmation d'écrasement\n");
            }
        } else if(crushed == 0){
            printf("Annulation de l'écrasement\n");
        } else{
            printf("Mauvaise touche\n");
        }
    }
}

int pause_game(parti *plyr, plateau *p){
    button t_button_pause[3], t_button_save[5];
    int pressed, in_pause, mx, my;

    in_pause = 1;

    MLV_clear_window(MLV_COLOR_BEIGE);

    while(in_pause){
        menu_pause(t_button_pause);

        MLV_wait_mouse(&mx, &my);
        pressed = clic_button(t_button_pause, 3, mx, my);

        switch(pressed){
            case 0:
                /* ---------- CONTINUE ----------*/
                return 1;
                    
            case 1:
                /* ---------- MENU SAUVEGARDE ----------*/
                while(1){
                    menu_save(t_button_save);
                    MLV_wait_mouse(&mx, &my);
                    pressed = clic_button(t_button_save, 5, mx, my);

                    if(pressed >= 0 && pressed < 4){
                        save_pause_management(plyr, p, pressed);
                    }
                    
                    if(pressed == 4){
                        break;
                    }
                }
                break;
                    
            case 2:
                /* ---------- QUITTER PARTIE ----------*/
                return 0;

            default:
                break;
        }
    }
    return 1;
}

/* Fonction qui affiche une boite de dialogue */
void display_text_box(char *message){
    int text_w, text_h, text_x, text_y, size_p;
    MLV_Font *police;

    size_p = 80;
    police = MLV_load_font("./Font/game_over.ttf", size_p);
    MLV_get_size_of_adapted_text_box_with_font(message, police, 10, &text_w, &text_h);
    
    text_x = (LX - text_w) / 2;
    text_y = (LY - text_h - 100) / 3;
  
    MLV_draw_adapted_text_box_with_font(text_x, text_y, message, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
  
    MLV_actualise_window();
    MLV_free_font(police);
}

void ask_name(parti *p){
    int valide, size_p, marge;
    MLV_Font *police;
    char mess_err[50];
    char *tmp = NULL;

    MLV_clear_window(MLV_COLOR_BEIGE);

    size_p = 100;
    police = MLV_load_font("./Font/game_over.ttf", size_p);

    valide = 1;

    marge = 50;
    
    while(valide){
        MLV_wait_input_box_with_font(marge, LY / 3, LX - (marge * 2), LY / 3, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_COLOR_BEIGE, "Enter your name :", &tmp, police);

        if(strlen(tmp) > 10){
            sprintf(mess_err, "You cannot have a name longer than 10 caracters");
              display_text_box(mess_err);
        } else {
            strcpy(p->name_player, tmp);
            valide = 0;
        }

        free(tmp);
        tmp = NULL;
    }

    MLV_free_font(police);
}