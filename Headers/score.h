#ifndef _SCORE_H_
#define _SCORE_H_

int load_score(tparti t_player);

int save_score(tparti t_player, int nb_score);

int collect_score(char *name_f, tparti t_player);

int change_player_score(parti *plyr1, parti *plyr2);

int tri_insertion(char *name_f, parti new_score, tparti t_player);

#endif