#ifndef RENDERER_H
#define RENDERER_H

#include "split.h"

void refresh_all_splits();
void draw_lines_around_splits();
void draw_lines_around_split(split* _split);
void draw_char(char* _position,unsigned char _character);
void draw_cursor(split* _split);
void refresh_split(split* _split);
void draw_help_menu();
void draw_mini_buffer();
void clear_screen();

#endif
