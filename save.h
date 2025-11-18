#ifndef _SAVE_H_
#define _SAVE_H_

int charger_save(char *nom, parti *jo, plateau **p);

int save_parti(char *nom, parti *jo, plateau *p);

parti initialiser_score(char *nom_joueur);

void sauvegarder_parti(parti joueur);

void afficher_score();

#endif