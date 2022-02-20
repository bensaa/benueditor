#ifndef COMMANDS_H
#define COMMANDS_H

#include "split.h"

void toggle_help();
void next_split();
void add_split(split* _split);
void remove_split(split* _split);
void print_splits();
void remove_chacters_from_minibuffer(int _count);
void add_character_to_minibuffer(char _character);
void move_mb_cursor(int _count);
void mb_execute_command();

#endif
