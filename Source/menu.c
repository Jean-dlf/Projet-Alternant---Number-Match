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

/* -- Verifie si on clique sur un bouton -- */
int verif(button button, int coord_x, int coord_y){
    if((coord_x > button.x && coord_x < button.x + button.width) && (coord_y > button.y && coord_y < button.y + button.height)){
        return 1;
    }
    return 0;
}

/* -- Renvoie la valeur button cliqué -- */
int clic_button(button t_button[], int length, int mx, int my){
    int i;

    for(i = 0; i < length; i++){
        if(verif(t_button[i], mx, my) == 1 ){
            return i;
        }
    }
    return -1;
}

/* -- Cree un button -- */
void create_button(button *button, char* message, int x, int y, MLV_Font *police){
    int width, height;
    MLV_get_size_of_adapted_text_box_with_font(message, police, 10, &width, &height);
    button -> x = x - width/2;
    button -> y = y;
    button -> height = height;
    button -> width = width;
    strcpy(button -> txt, message);    
}

/* -- Affiche le texte des boutons -- */
void display_text(button button , MLV_Font *police){
    MLV_draw_adapted_text_box_with_font( button.x, button.y, button.txt, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
}

/* -- Menu principal -- */
void menu_p(button t_button_menu[4]){
    char *name_button[4] = {"START", "SAVE", "SCORE", "EXIT"}; 
    int text_width, text_height, i, size_p, space;
    MLV_Font *police;

    MLV_clear_window(MLV_rgba(122, 125, 125, 255));

    /* -- Titre -- */
    size_p = TITLE_SIZE;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    MLV_get_size_of_adapted_text_box_with_font("NUMBER MATCH", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font((LX - text_width) / 2, text_height / 3, "NUMBER MATCH", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    /* -- Boutons -- */
    size_p = 60;
    police = MLV_load_font("./Font/Crang.ttf", size_p);
    space = 200;

    for(i = 0; i < 4; i++){
        create_button(&t_button_menu[i], name_button[i], LX / 2, (text_height * 2) + i * space, police);
        display_text(t_button_menu[i], police);
    }

    MLV_free_font(police);
    MLV_actualise_window();
}

void menu_save(button t_button_save[5]){
    char *name_button_save[5] = {"SAVE 1", "SAVE 2", "SAVE 3", "SAVE 4", "BACK"};
    int text_width, text_height, i, size_p, space;
    MLV_Font *police;
        
    MLV_clear_window(MLV_rgba(122, 125, 125, 255));

    size_p = TITLE_SIZE;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    /* -- Titre -- */
    MLV_get_size_of_adapted_text_box_with_font("SAVE", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3, "SAVE", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    size_p = 60;
    police = MLV_load_font("./Font/Crang.ttf", size_p);
    space = 170;
    
    /* -- Boutons save -- */
    for(i = 0; i < 5; i++){
        create_button(&t_button_save[i], name_button_save[i], LX / 2, (text_height * 2) + i * space, police);
        display_text(t_button_save[i], police);
    }

    MLV_free_font(police);
    MLV_actualise_window();
}

/* -- Menu choix mode de jeu -- */
void menu_choice_mode(button t_button_choice_mode[3]){
    char *name_button_choice_mode[3] = {"CLASSIC", "LOCKSMITH", "BACK"};
    int text_width, text_height, i, size_p, space;
    MLV_Font *police;

    MLV_clear_window(MLV_rgba(122, 125, 125, 255));

    /* -- Titre -- */
    size_p = TITLE_SIZE;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    MLV_get_size_of_adapted_text_box_with_font("SELECT MODE", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font((LX - text_width) / 2, text_height / 3, "SELECT MODE", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    MLV_free_font(police);

    /* -- Boutons mode -- */
    size_p = 80;
    police = MLV_load_font("./Font/Crang.ttf", size_p);
    space = 300;

    for(i = 0; i < 3; i++){
        create_button(&t_button_choice_mode[i], name_button_choice_mode[i], LX / 2, (text_height * 2) + i * space, police);
        display_text(t_button_choice_mode[i], police);
    }

    MLV_free_font(police);
    MLV_actualise_window();
}

/* -- Gestion clique dans menu de choix de mode -- */
int choice_mode_game(){
    button t_bouton_choice_mode[3];
    int pressed, mx, my;

    menu_choice_mode(t_bouton_choice_mode);

    /* -- Attend le clique -- */
    MLV_wait_mouse(&mx, &my);
    pressed = clic_button(t_bouton_choice_mode, 3, mx, my);
    
    return pressed;
}

/* -- Menu règles -- */
void menu_rules_classic(button *next){
    char display1[500], display2[500];
    char *name_button_continue[1] = {"CONTINUE"};
    int text1_width, text1_height, text2_width, text2_height, title_width, title_height, size_p;
    MLV_Font *police;

    MLV_clear_window(MLV_rgba(122, 125, 125, 255));

    /* -- Titre -- */
    size_p = TITLE_SIZE;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    MLV_get_size_of_adapted_text_box_with_font("RULES", police, 10, &title_width, &title_height);
    MLV_draw_adapted_text_box_with_font( (LX - title_width) / 2, title_height / 3 - 25, "RULES", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    /* -- Texte règle -- */
    size_p = 30;
    police = MLV_load_font("./Font/Crang.ttf", size_p);
    
    /* ---- Texte règle commande ---- */
    sprintf(display1, "COMMENT JOUER ?\n\n LES PAIRES PEUVENT ETRE FORMEES DE DIFFERENTES MANIERES :\n - HORIZONTALEMENT\n     - VERTICALEMENT\n     - DIAGONALEMENT\n- OU AVEC UN CHIFFRE EN FIN DE LIGNE ET L'AUTRE AU DEBUT DE LA SUIVANTE\n EGALEMENT VOUS POUVEZ MATCHER 2 CASES SI IL Y A DES 0 ENTRE ELLES\n\n");
    MLV_get_size_of_adapted_text_box_with_font(display1, police, 10, &text1_width, &text1_height);
    MLV_draw_adapted_text_box_with_font( (LX - text1_width) / 2, title_height * 2, display1, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    /* ---- Texte règle points ---- */
    sprintf(display2, "SYSTEME DE POINTS ?\n\n - SOMME DES DEUX CHIFFRES = 10    →    +15 POINTS\n - CHIFFRES IDENTIQUES                →                +10 POINTS\n - TABLEAU ENTIEREMENT VIDE          →         +100 POINTS\n - BONUS D'INDICE RESTANT                         →                       +25 POINTS / BONUS\n\n\n Bon jeu !");
    MLV_get_size_of_adapted_text_box_with_font(display2, police, 10, &text2_width, &text2_height);
    MLV_draw_adapted_text_box_with_font( (LX - text2_width) / 2, ((title_height * 2) + text1_height), display2, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    /* -- Bouton continue -- */
    size_p = 40;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    create_button(next, name_button_continue[0], LX - 150, LY - 100, police);
    display_text(*next, police);

    MLV_free_font(police);
    MLV_actualise_window();
}

/* -- Menu règles Locksmith -- */
void menu_rules_locksmith(button *next){
    char display1[500], display2[500];
    char *name_button_next[1] = {"CONTINUE"};
    int title_width, title_height, text1_width, text1_height, text2_width, text2_height, width_img, height_img, x, size_p;
    MLV_Font *police;
    MLV_Image *image[1];
    char *name_image[1] = {"./Assets/locksmith_rules.png"};

    MLV_clear_window(MLV_rgba(122, 125, 125, 255));

    size_p = TITLE_SIZE;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    /* -- Titre -- */
    MLV_get_size_of_adapted_text_box_with_font("RULES", police, 5, &title_width, &title_height);
    MLV_draw_adapted_text_box_with_font( (LX - title_width) / 2, title_height / 3, "RULES", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    /* -- Texte -- */
    size_p = 30;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    sprintf(display1, "LES PAIRES PEUVENT ETRE FORMÉES DE PLUSIEURS MANIERES :\n\n - HORIZONTALEMENT\n - VERTICALEMENT\n - DIAGONALEMENT\n\n MATCHS POSSIBLES ?\n\n - 2 CADENAS IDENTIQUES\n - 2 CLES IDENTIQUES\n - 1 CLE ET SON CADENA CORRESPONDANT\n - 2 CHEVALIERS IDENTIQUES OU 1 CHEVALIER ET UNE CLE GRISE\n - 2 CADENAS JOKERS\n");    
    MLV_get_size_of_adapted_text_box_with_font(display1, police, 10, &text1_width, &text1_height);
    MLV_draw_adapted_text_box_with_font( (LX - text1_width) / 6, title_height * 2 - 50, display1, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_LEFT);

    sprintf(display2, "SYSTEME DE POINTS ?\n\n - SOMME DES DEUX CHIFFRES = 10    →    +15 POINTS\n - CHIFFRES IDENTIQUES                →                +10 POINTS\n - TABLEAU ENTIEREMENT VIDE          →         +100 POINTS\n - BONUS D'INDICE RESTANT                         →                       +25 POINTS / BONUS\n\n\n Bon jeu !");    
    MLV_get_size_of_adapted_text_box_with_font(display2, police, 10, &text2_width, &text2_height);
    MLV_draw_adapted_text_box_with_font( (LX - text2_width) / 6, ((title_height * 2) + text1_height) - 50, display2, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_LEFT);

    /* -- Button continue -- */
    size_p = 40;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    create_button(next, name_button_next[0], LX - 150, LY - 100, police);
    display_text(*next, police);

    /* -- Image -- */
    x = LX / 2;

    image[0] = MLV_load_image(name_image[0]);
    MLV_resize_image_with_proportions(image[0], 500, 500);
    MLV_get_image_size(image[0], &width_img, &height_img);
    MLV_draw_image(image[0], x + width_img, (LY / 2) - height_img);
    MLV_free_image(image[0]);

    MLV_free_font(police);
    MLV_actualise_window();
}

/* -- Menu choix de difficulté -- */
void menu_ask_difficulty(button t_button_level[6], int custom){
    char *name_button_score[5] = {"6 X 6", "8 X 8", "6 X 10", "8 X 6", "BACK"};
    char *name_button_game[6] = {"6 X 6", "8 X 8", "6 X 10", "8 X 6", "Custom", "BACK"};
    char **name_buttons;
    int text_width, text_height, i, size_p, space, nb_buttons;
    MLV_Font *police;

    MLV_clear_window(MLV_rgba(122, 125, 125, 255));

    /* -- Titre -- */
    size_p = TITLE_SIZE;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    MLV_get_size_of_adapted_text_box_with_font("CHOOSE YOUR DIFFICULTY", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font((LX - text_width) / 2, text_height / 3, "CHOOSE YOUR DIFFICULTY", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    /* -- Boutons choix difficulté -- */

    if(custom){
        name_buttons = name_button_game;
        nb_buttons = 6;
    } else {
        name_buttons = name_button_score;
        nb_buttons = 5;
    }

    size_p = 60; 
    police = MLV_load_font("./Font/Crang.ttf", size_p);
    space = 160;

    for(i = 0; i < nb_buttons; i++){
        
        create_button(&t_button_level[i], name_buttons[i], LX / 2, (text_height * 2) + i * space, police);
        display_text(t_button_level[i], police);
    }

    MLV_free_font(police);
    MLV_actualise_window();
}

/* -- Menu score -- */
void menu_score(){
    char *name_button_score[10] = {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th"};
    char display[200];
    char *name_files_score[4] = {"./Save/score1.txt", "./Save/score2.txt", "./Save/score3.txt", "./Save/score4.txt"};
    button t_button_level[6];
    tparti t_player;
    int text_width, text_height, title_width, title_height, i, size_p, mx, my, pressed, space;
    MLV_Font *police;
    MLV_Color color;

    /* -- Demande du niveau de diffulté dans menu score pour charger le bon classement -- */
    pressed = -1;
    menu_ask_difficulty(t_button_level, NO_CUSTOM);
    MLV_actualise_window();

    while(pressed == -1){
        MLV_wait_mouse(&mx, &my);
        pressed = clic_button(t_button_level, 5, mx, my);

        if(pressed == 4){
            return ;
        }
    }

    MLV_clear_window(MLV_rgba(122, 125, 125, 255));
    
    /* -- Titre -- */
    size_p = TITLE_SIZE;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    MLV_get_size_of_adapted_text_box_with_font("HIGH SCORES", police, 10, &title_width, &title_height);
    MLV_draw_adapted_text_box_with_font((LX - title_width) / 2, title_height / 3, "HIGHT SCORES", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    MLV_free_font(police);

    size_p = 40;
    police = MLV_load_font("./Font/Crang.ttf", size_p);


    /* -- Récupération des scores dans le bon fichier -- */
    if(collect_score(name_files_score[pressed], t_player) == -1){
        fprintf(stderr, "Erreur lors de la récupération des scores\n");
        return ;
    }

    /* -- Boucle d'affichage du classement -- */
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

        space = 100;
        
        sprintf(display, "%s --   Score = %d   |   Pseudo = %s", name_button_score[i], t_player[i].score, t_player[i].name_player);
        MLV_get_size_of_adapted_text_box_with_font(display, police, 10, &text_width, &text_height);
        MLV_draw_adapted_text_box_with_font(50, (title_height * 1.5) + i * space, display, police, 10, MLV_ALPHA_TRANSPARENT, color, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
    }

    MLV_free_font(police);
    MLV_actualise_window();

    /* -- Attend un clic n'importe où pour sortir -- */
    MLV_wait_mouse(NULL, NULL);
}

/* -- Menu pause -- */
void menu_pause(button t_bouton_pause[3]){
    char *name_button_pause[3] = {"RESUME", "SAVE", "QUIT"};
    int text_width, text_height, i, size_p, space;
    MLV_Font *police;

    MLV_clear_window(MLV_rgba(122, 125, 125, 255));

    /* -- Titre -- */
    size_p = TITLE_SIZE;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    MLV_get_size_of_adapted_text_box_with_font("PAUSE", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font((LX - text_width) / 2, text_height / 3, "PAUSE", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    /* -- Bouton pause -- */
    size_p = 60;
    police = MLV_load_font("./Font/Crang.ttf", size_p);
    space = 180;

    for(i = 0; i < 3; i++){
        create_button(&t_bouton_pause[i], name_button_pause[i], LX / 2, (text_height * 3) + i * space, police);
        display_text(t_bouton_pause[i], police);
    }

    MLV_free_font(police);
    MLV_actualise_window();
}

/* -- Confirmation d'écrasement save -- */
int crushing_save(){
    MLV_Font *police;
    button t_button_crush[2];
    char *name_button_crush[2] = {"NO", "YES"};
    int size_p, text_width, text_height, mx, my, pressed, space;

    MLV_clear_window(MLV_rgba(122, 125, 125, 255));

    /* -- Titre -- */
    size_p = 100;
    police = MLV_load_font("./Font/Crang.ttf", size_p);
    MLV_get_size_of_adapted_text_box_with_font("OVERWRITE EXISTING SAVE ?", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font((LX - text_width) / 2, text_height / 3, "OVERWRITE EXISTING SAVE ?", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    /* -- Boutons crushing save -- */
    size_p = 60;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    space = 300;

    create_button(&t_button_crush[1], name_button_crush[1], LX / 2 - space / 2, text_height * 3, police);
    display_text(t_button_crush[1], police);

    create_button(&t_button_crush[0], name_button_crush[0], LX / 2 + space / 2, text_height * 3, police);
    display_text(t_button_crush[0], police);

    MLV_actualise_window();

    /* -- Attend le renvoie de oui ou de non -- */
    pressed = -1;
    
    do{
        MLV_wait_mouse(&mx, &my);
        pressed = clic_button(t_button_crush, 2, mx, my);
    } while(pressed == -1);

    MLV_free_font(police);

    return pressed;
}

/* -- Gestion de l'écrasement d'une sauvegarde lors d'une partie -- */
void save_pause_management(parti *plyr, plateau *p, int pressed){
    char *name_save[4] = {"./Save/save1.txt", "./Save/save2.txt", "./Save/save3.txt", "./Save/save4.txt"};
    int crushed;
    FILE *f;

    f = fopen(name_save[pressed], "r");

    /* -- Si fichier vide on save simplement dedans -- */
    if(f == NULL){
        if(save_game(name_save[pressed], plyr, p) == 1){
            printf("Partie bien sauvegardé\n");
        }
    /* -- Sinon on demande si on veut écraser la sauvegarde présente -- */
    } else {
        fclose(f);
        crushed = crushing_save();
        if(crushed){
            /* -- Si oui on remplace -- */
            if(save_game(name_save[pressed], plyr, p) == 1){
                printf("Partie bien sauvegardé après confirmation d'écrasement\n");
            }
            /* -- Sinon on annule -- */
        } else if(crushed == 0){
            printf("Annulation de l'écrasement\n");
        }
    }
}

/* -- Gestion du menu pause -- */
int pause_game(parti *plyr, plateau *p){
    button t_button_pause[3], t_button_save[5];
    int pressed, in_pause, mx, my;

    in_pause = 1;

    MLV_clear_window(MLV_rgba(122, 125, 125, 255));

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

/* -- Fonction qui affiche une boite de dialogue -- */
void display_text_box(char *message){
    int text_w, text_h, text_x, text_y, size_p;
    MLV_Font *police;

    size_p = 40;
    police = MLV_load_font("./Font/Crang.ttf", size_p);
    MLV_get_size_of_adapted_text_box_with_font(message, police, 10, &text_w, &text_h);
    
    text_x = (LX - text_w) / 2;
    text_y = (LY - text_h - 100) / 3;
  
    MLV_draw_adapted_text_box_with_font(text_x, text_y, message, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
  
    MLV_actualise_window();
    MLV_free_font(police);
}

/* -- Fonction qui demande le nom de l'utilisateur -- */
void ask_name(parti *p){
    int valide, size_p, marge;
    MLV_Font *police;
    char mess_err[50];
    char *tmp = NULL;

    MLV_clear_window(MLV_rgba(122, 125, 125, 255));

    size_p = 80;
    police = MLV_load_font("./Font/Crang.ttf", size_p);
    
    valide = 1;
    marge = 50;
    
    while(valide){
        MLV_wait_input_box_with_font(marge, LY / 3, LX - (marge * 2), LY / 3, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_rgba(122, 125, 125, 255), "Enter your name :", &tmp, police);

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

/* -- Affiche les données du joueur à la fin du partie -- */
void recap_game(parti player){
    char display[250];
    int text_width, text_height, size_p;
    MLV_Font *police;

    MLV_clear_window(MLV_rgba(122, 125, 125, 255));

    /* -- Titre -- */
    size_p = TITLE_SIZE;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    MLV_get_size_of_adapted_text_box_with_font("RECAP GAME", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3, "RECAP GAME", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    MLV_free_font(police);

    /* -- Affichage du texte -- */    
    size_p = 60;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    sprintf(display, "NAME PLAYER : %s\n\nSCORE GAME : %d\n\nREMAINING BONUS CLUE : %d\n\nAJOUT DE %d POINTS", player.name_player, player.score, player.bonus_clue, add_point_for_bonus(player));
    MLV_get_size_of_adapted_text_box_with_font(display, police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, (LY - text_height) / 2 , display, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    MLV_free_font(police);
    MLV_actualise_window();
    MLV_wait_mouse(NULL, NULL);
}

void menu_customised_dimensions(plateau *p){
    MLV_Font *police;
    int size_p, valide, marge, value, text_width, text_height;
    char display[120];
    char mess_err[50];
    char *tmp = NULL;

    MLV_clear_window(MLV_rgba(122, 125, 125, 255));

    size_p = 60;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    sprintf(display, "/!\\ -- In custom mode\n it's impossible to save your best scores.");
    MLV_get_size_of_adapted_text_box_with_font(display, police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 2, display, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    valide = 1;
    marge = 50;

    size_p = 40;
    police = MLV_load_font("./Font/Crang.ttf", size_p);

    /* -- Demande pour la longueur -- */
    tmp = NULL;
    while(valide){
        MLV_wait_input_box_with_font(marge, LY / 3, LX - (marge * 2), LY / 3, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_rgba(122, 125, 125, 255), "Enter the length of the game board --- min 3 | max 11 ->", &tmp, police);
        
        value = atoi(tmp);
        free(tmp);
        tmp = NULL;
        
        if(value < 3 || value > 11){
            sprintf(mess_err, "You must enter a number between 3 and 11");
            display_text_box(mess_err);
        } else {
            p->n = value;
            valide = 0;
        }
    }

    valide = 1;

    /* -- Demande pour la hauteur -- */
    while(valide){
        MLV_wait_input_box_with_font(marge, LY / 3, LX - (marge * 2), LY / 3, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_rgba(122, 125, 125, 255), "Enter the height of the game board (min 3 | max 14) :", &tmp, police);
        
        value = atoi(tmp);
        free(tmp);
        tmp = NULL;
        
        if(value < 3 || value > 14){
            sprintf(mess_err, "You must enter a number between 3 and 14");
            display_text_box(mess_err);
        } else {
            p->m = value;
            valide = 0;
        }
    }

    MLV_free_font(police);
}