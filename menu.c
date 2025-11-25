#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "jeu.h"

/* verifie si on clique sur un bouton */
int verif(bouton bouton, int coord_x, int coord_y){
    if((coord_x > bouton.x && coord_x < bouton.x + bouton.largeur) && (coord_y > bouton.y && coord_y < bouton.y + bouton.hauteur)){
        return 1;
    }
    return 0;
}

/* renvoie la valeur bouton clique */
int clic_bouton(bouton t_bouton[], int longueur){
    int i, s_x, s_y;

    MLV_wait_mouse(&s_x, &s_y);
    for( i = 0; i < longueur; i++ ){
        if( verif(t_bouton[i], s_x, s_y) == 1 ){
            return i;
        }
    }
    return i;
}

/* cree un bouton */
void cree_bouton(bouton *bouton, char* message, int x, int y, MLV_Font *police){
    int largeur, hauteur;
    MLV_get_size_of_adapted_text_box_with_font(message, police, 10, &largeur, &hauteur);
    bouton -> x = x - largeur/2;
    bouton -> y = y;
    bouton -> hauteur = hauteur;
    bouton -> largeur = largeur;
    strcpy(bouton -> txt, message);    
}

/* affiche le texte dun bouton */
void afficher_text(bouton bouton , MLV_Font *police){
    MLV_draw_adapted_text_box_with_font( bouton.x, bouton.y, bouton.txt, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER );
}

/* affichage du menu principal */
void menu_p(bouton t_bouton_menu[5]){
    char *nom_bouton[5] = {"START", "SAVE", "RULES", "SCORE", "EXIT"}; 
    int text_width, text_height, i, taille_p;
    MLV_Font *police;

    
    MLV_clear_window(MLV_COLOR_BEIGE);

    /* Titre */
    taille_p = 180;
    police = MLV_load_font("./game_over.ttf", taille_p);

    MLV_get_size_of_adapted_text_box_with_font("NUMBER MATCH", police, 10, &text_width, &text_height);
  
    MLV_draw_adapted_text_box_with_font((LX - text_width) / 2, text_height / 3 - 25, "NUMBER MATCH", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    taille_p = 100;
    police = MLV_load_font("./game_over.ttf", taille_p);

    for(i = 0; i < 5; i++){
        cree_bouton(&t_bouton_menu[i], nom_bouton[i], LX / 2, 150 + i * 100, police);
        afficher_text(t_bouton_menu[i], police);
    }

    MLV_free_font(police);
    MLV_actualise_window();
}

void menu_save(bouton t_bouton_save[5]){
    char *nom_bouton_save[5] = {"SAVE 1", "SAVE 2", "SAVE 3", "SAVE 4", "BACK"};
    int text_width, text_height, i, taille_p;
    MLV_Font *police;
        
    MLV_clear_window(MLV_COLOR_BEIGE);

    taille_p = 180;
    police = MLV_load_font("./game_over.ttf", taille_p);

    /* Titre */
    MLV_get_size_of_adapted_text_box_with_font("SAVE", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, text_height / 3 - 25, "SAVE", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    taille_p = 100;
    police = MLV_load_font("./game_over.ttf", taille_p);
    
    /* bouton save */
    for(i = 0; i < 5; i++){
        cree_bouton(&t_bouton_save[i], nom_bouton_save[i], LX / 2, 150 + i * 100, police);
        afficher_text(t_bouton_save[i], police);
    }

    MLV_free_font(police);
    MLV_actualise_window();
}

void menu_rules(bouton *retour){
    char affichage[500];
    char *nom_bouton_retour[1] = {"BACK"};
    int long_text, haut_text, long_img, haut_img, x, taille_p;
    MLV_Font *police;
    MLV_Image *image[1];
    char *noms_image[1] = {"./number_match.png"};

    MLV_clear_window(MLV_COLOR_BEIGE);

    taille_p = 180;
    police = MLV_load_font("./game_over.ttf", taille_p);

    /* Titre */
    MLV_get_size_of_adapted_text_box_with_font("RULES", police, 10, &long_text, &haut_text);
    MLV_draw_adapted_text_box_with_font( (LX - long_text) / 2, haut_text / 3 - 25, "RULES", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    /* Texte */
    taille_p = 60;
    police = MLV_load_font("./game_over.ttf", taille_p);

    sprintf(affichage, "VOTRE OBJECTIF : VIDER LE PLATEAU DE JEU\nPOUR CELA VOUS DEVEZ TROUVER DES PAIRES DE CHIFFRES IDENTIQUES\nLES PAIRES PEUVENT ETRE :\n -HORIZONTALES --- (FLECHE ROUGE)\n-VERTICALES --- (FLECHE ORANGE)\n-EN DIAGONALE --- (FLECHE VIOLETTE)\n-OU UN CHIFFRE EN FIN DE LIGNE ET L'AUTRE AU DEBUT DE LA SUIVANTE\n --- (FLECHE BLEUE)\n");
    MLV_get_size_of_adapted_text_box_with_font(affichage, police, 10, &long_text, &haut_text);
    MLV_draw_adapted_text_box_with_font( (LX - long_text) / 2, haut_text / 3, affichage, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    /* Bouton Retour */
    taille_p = 80;
    police = MLV_load_font("./game_over.ttf", taille_p);

    cree_bouton(retour, nom_bouton_retour[0], 60, 1, police);
    afficher_text(*retour, police);

    /* Image */
    x = LX / 2;

    image[0] = MLV_load_image(noms_image[0]);
    MLV_resize_image_with_proportions(image[0], 300, 300);
    MLV_get_image_size(image[0], &long_img, &haut_img);
    MLV_draw_image(image[0], x - (long_img / 2), LY - haut_img - 25);
    MLV_free_image(image[0]);

    MLV_free_font(police);
    MLV_actualise_window();
}

void menu_score(bouton *retour) {
    char *nom_bouton_score[10] = {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th"};
    char affichage[200];
    char *nom_bouton_retour[1] = {"BACK"};
    tparti t_score;
    int long_text, haut_text, i, k, taille_p;
    MLV_Font *police;
    MLV_Color color;

    MLV_clear_window(MLV_COLOR_BEIGE);

    /* Titre */
    taille_p = 180;
    police = MLV_load_font("./game_over.ttf", taille_p);

    MLV_get_size_of_adapted_text_box_with_font("HIGH SCORES", police, 10, &long_text, &haut_text);
    MLV_draw_adapted_text_box_with_font((LX - long_text) / 2, haut_text / 3 - 25, "HIGHT SCORES", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_BLACK, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    taille_p = 80;
    police = MLV_load_font("./game_over.ttf", taille_p);
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
        sprintf(affichage, "%s --   Score = %d   |   Pseudo = %s   |   Timer = ", nom_bouton_score[i], 80, "Oui" /* t_score[i].score, t_score[i].nom_joueur */);
        MLV_get_size_of_adapted_text_box_with_font(affichage, police, 10, &long_text, &haut_text);
        MLV_draw_adapted_text_box_with_font(30, haut_text / 3 + 100 + k, affichage, police, 10, MLV_ALPHA_TRANSPARENT, color, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
        k += 60;
    }

    taille_p = 80;
    police = MLV_load_font("./game_over.ttf", taille_p);

    cree_bouton(retour, nom_bouton_retour[0], 60, 0, police);
    afficher_text(*retour, police);

    MLV_free_font(police);
    MLV_actualise_window();
}