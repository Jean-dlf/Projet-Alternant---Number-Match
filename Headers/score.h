#ifndef _SCORE_H_
#define _SCORE_H_

int load_score(char *name_f, tparti t_player);

int save_score(char *name_f, tparti t_player, int nb_score);

int collect_score(char *name_f, tparti t_player);

int update_high_scores(parti player);

#endif