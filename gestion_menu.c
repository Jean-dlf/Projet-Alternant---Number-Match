#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include <time.h>
#include "menu.h"
#include "types.h"
#include "initialisation.h"
#include "jeu.h"
#include "deroulement.h"
#include "save.h"

void gestion(){
    plateau *p = NULL;
    int n = 3, m = 6;
    bouton t_menu_p[5], t_menu_s[5], retour;
    char *nom_save[4] = {"save1.txt", "save2.txt", "save3.txt", "save4.txt"};
    int pressed;
    int retour_menu_p = 1;
    parti j;
    
    menu_p(t_menu_p);

    while(retour_menu_p == 1){
        menu_p(t_menu_p);
        pressed = clic_bouton(t_menu_p, 5);
        switch(pressed){
            
            /* Lancement du jeu */
            case 0:
            printf("Jeu\n");
            deroulement(p, n, m, 1, NULL);
            retour_menu_p = 0;
            break;

            /* Menu sauvegarde */
            case 1:
            printf("Menu sauvegarde\n");
            menu_save(t_menu_s);

            while(retour_menu_p == 1){
                pressed = clic_bouton(t_menu_s, 5);

                if(pressed < 4){
                    printf("Save %s\n", nom_save[pressed]);


                    if(charger_save(nom_save[pressed], &j, &p) == 1){
                        printf("Score chargé : %d\n", j.score);
                        deroulement(p, p->n, p->m, 0, &j);
                        retour_menu_p = 0;
                    } else {
                        printf("Pas de sauvegarde\n");
                        retour_menu_p = 0;
                    }
                } else if(pressed == 4){
                    printf("Menu Principal\n");
                    retour_menu_p = 0;
                }
            }
            break;

            /* Menu règles */
            case 2:
            printf("Menu règles\n");
            menu_rules(&retour);
            pressed = clic_bouton(&retour, 1);
            if(pressed == 0){
                printf("Menu Principal\n");
                retour_menu_p = 0;
            }
            break;

            /* Menu score */
            case 3:
            printf("Menu score\n");
            menu_score(&retour);
            pressed = clic_bouton(&retour, 1);
            if(pressed == 0){
                printf("Menu Principal\n");
                retour_menu_p = 0;
            }
            break;

            /* Exit lors du menu */
            case 4:
            printf("Au revoir\n");
            return ;
        }
        retour_menu_p = 1;
    }
}