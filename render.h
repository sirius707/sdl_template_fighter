#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "common.h"

void s_render_init(void);

void s_render_players(void);

void s_render_prepare(void);
void s_render_present(void);

void s_render_total(void);//a function that calls all render functiosn in order
#endif // RENDER_H_INCLUDED
