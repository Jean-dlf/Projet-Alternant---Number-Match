#ifndef _SAVE_H_
#define _SAVE_H_

int load_save(char *nom, parti *jo, plateau **p);

int save_game(char *nom, parti *jo, plateau *p);

parti initialisation_score(char *nom_joueur);

void save_parti(parti joueur);

void display_score();

#endif