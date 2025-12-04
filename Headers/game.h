#ifndef _GAME_H_
#define _GAME_H_

#include "types.h"

void game_term(plateau *p, int n, int m, int save, parti *player_s);

int game_graphic(plateau *p, int n, int m, parti *player_s, int mode);

#endif