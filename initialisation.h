
/*initialisation.h*/

#ifndef _INITIALISATION_H_
#define _INITIALISATION_H_

plateau *initialisation_plateau(int n, int m);

cases *initialisation_cases(int x, int y, int value);

plateau *random_initialisation(plateau *p);

l_cases *initialisation_l_cases(cases *c1, cases *c2);

#endif