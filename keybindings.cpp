#include "keybindings.h"
#include "globals.h"
#include "commands.h"
#include "input.h"
#include "renderer.h"


void key_x(){
	next_split();
}
	
void key_o(){
	next_split();
	draw_lines_around_splits();
	Hwin->queue_draw();
}

void key_f(){
	current_mode = commandMode;
	draw_mini_buffer();
	Hwin->queue_draw();
}

void key_two(){
	active_split->split_down();
}

void key_three(){
	active_split->split_left();
}

void key_zero(){
	active_split->delete_split();
}

void arrow_left(){
	active_split->cursor_left();
}

void arrow_up(){
	active_split->cursor_up();
}

void arrow_down(){
	active_split->cursor_down();
}

void arrow_right(){
	active_split->cursor_right();
}

void key_F1(){
	toggle_help();
}

void key_F2(){
	onResize();
}

void key_ctrl_plus(){
	active_split->get_width_usage(0.1, active_split);
}

void key_ctrl_minus(){
	active_split->get_width_usage(-0.1, active_split);
}

void key_meta_plus(){
	active_split->get_height_usage(0.1, active_split);
}

void key_meta_minus(){
	active_split->get_height_usage(-0.1, active_split);
}

void command_key_arrow_right(){
	move_mb_cursor(1);
	draw_mini_buffer();
	Hwin->queue_draw();
}
void command_key_arrow_left(){
	move_mb_cursor(-1);
	draw_mini_buffer();
	Hwin->queue_draw();
}
void command_key_arrow_up(){
}
void command_key_arrow_down(){
}

void command_backspace(){
	move_mb_cursor(-1);
	remove_chacters_from_minibuffer(1);
}
void command_delete(){
	remove_chacters_from_minibuffer(1);
}

void command_enter(){
	mb_execute_command();
}

void command_esc(){
	current_mode = normalMode;
	draw_mini_buffer();
	Hwin->queue_draw();
}

void command_write_character(int _keycode){
	switch(_keycode){
	case 10:{add_character_to_minibuffer('1');break;}
	case 11:{add_character_to_minibuffer('2');break;}
	case 12:{add_character_to_minibuffer('3');break;}
	case 13:{add_character_to_minibuffer('4');break;}
	case 14:{add_character_to_minibuffer('5');break;}
	case 15:{add_character_to_minibuffer('6');break;}
	case 16:{add_character_to_minibuffer('7');break;}
	case 17:{add_character_to_minibuffer('8');break;}
	case 18:{add_character_to_minibuffer('9');break;}
	case 19:{add_character_to_minibuffer('0');break;}
	case 24:{add_character_to_minibuffer('q');break;}
	case 25:{add_character_to_minibuffer('w');break;}
	case 26:{add_character_to_minibuffer('e');break;}
	case 27:{add_character_to_minibuffer('r');break;}
	case 28:{add_character_to_minibuffer('t');break;}
	case 29:{add_character_to_minibuffer('y');break;}
	case 30:{add_character_to_minibuffer('u');break;}
	case 31:{add_character_to_minibuffer('i');break;}
	case 32:{add_character_to_minibuffer('o');break;}
	case 33:{add_character_to_minibuffer('p');break;}
	case 38:{add_character_to_minibuffer('a');break;}
	case 39:{add_character_to_minibuffer('s');break;}
	case 40:{add_character_to_minibuffer('d');break;}
	case 41:{add_character_to_minibuffer('f');break;}
	case 42:{add_character_to_minibuffer('g');break;}
	case 43:{add_character_to_minibuffer('h');break;}
	case 44:{add_character_to_minibuffer('j');break;}
	case 45:{add_character_to_minibuffer('k');break;}
	case 46:{add_character_to_minibuffer('l');break;}
	case 52:{add_character_to_minibuffer('z');break;}
	case 53:{add_character_to_minibuffer('x');break;}
	case 54:{add_character_to_minibuffer('c');break;}
	case 55:{add_character_to_minibuffer('v');break;}
	case 56:{add_character_to_minibuffer('b');break;}
	case 57:{add_character_to_minibuffer('n');break;}
	case 58:{add_character_to_minibuffer('m');break;}
	}
}
