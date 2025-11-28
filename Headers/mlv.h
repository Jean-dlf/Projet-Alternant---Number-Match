#ifndef _MLV_H_
#define _MLV_H_

#include "types.h"

void plateau_details(plateau *p, int *size, int *offset_x, int *offset_y, int *width, int *height);

void wait_mouse_release();

cases *get_details(plateau *p, int mx, int my);

#endif