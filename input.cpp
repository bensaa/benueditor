#include <gdkmm/general.h>
#include <gtkmm/application.h>
#include "globals.h"
#include "renderer.h"
#include "input.h"
#include "commands.h"
#include "keybindings.h"

bool onKeyPress(GdkEventKey* event){
	if(current_mode == normalMode){
		switch(event->hardware_keycode){
		case 11:{
			key_two();
			break;
		}
		case 12:{
			key_three();
			break;
		}
		case 19:{
			key_zero();
			break;
		}
		case 20:{
			key_ctrl_plus();
			break;
		}
		case 32:{
			key_o();
			if(ctrl_down){
			}
			break;
		}
		case 34:{//å
			key_meta_plus();
			break;
		}
		case 37:{
			ctrl_down = true;
			break;
		}
		case 41:{
			key_f();
			break;
		}
		case 48:{//ä
			key_meta_minus();
			break;
		}
		case 50:{
			shift_down = true;
			break;
		}
		case 53:{
			if(ctrl_down){
				ctrl_x_prefix = true;
				printf("ctrl-x true");
			}
			else{
				key_x();
			}
			break;
		}
		case 61:{
			key_ctrl_minus();
			break;
		}

		case 64:{
			alt_down = true;
			break;
		}
		case 67:{
			key_F1();
			break;
		}
		case 68:{
			key_F2();
			break;
		}
		case 113:{
			arrow_left();
			break;
		}
		case 111:{
			arrow_up();
			break;
		}
		case 116:{
			arrow_down();
			break;
		}
		case 114:{
			arrow_right();
			break;
		}
		case 24:{((Gtk::Application*)Happ)->quit();break;}
		case 9:{((Gtk::Application*)Happ)->quit();}
		}
	}
	else if(current_mode == commandMode){
		switch(event->hardware_keycode){
		case 9:{command_esc();break;}
		case 22:{command_backspace();break;}
		case 36:{mb_execute_command();break;}
		case 113:{
			command_key_arrow_left();
			break;
		}
		case 111:{
			command_key_arrow_up();
			break;
		}
		case 116:{
			command_key_arrow_down();
			break;
		}
		case 114:{
			command_key_arrow_right();
			break;
		}
		case 119:{
			command_delete();
			break;
		}
		default:{
			command_write_character(event->hardware_keycode);
		}
		}
	}
	printf("key %d\n",event->hardware_keycode);
	return true;
}
	

bool onKeyRelease(GdkEventKey* event){
	switch(event->hardware_keycode){
	case 37:{
		ctrl_down = false;
		break;
	}
	case 50:{
		shift_down = false;
		break;
	}
	case 64:{
		alt_down = false;
		break;
	}}
	printf("key %d\n",event->hardware_keycode);
	return true;
}

void onResize(){
	screen_width = Hwin->get_width();
	screen_width_bytes = screen_width*3;
	screen_height = Hwin->get_height();
	screen_height_bytes = screen_height*3;
	
	main_frame->set_width(screen_width);
	main_frame->set_height(screen_height-slot_height);
	main_frame->refresh();
	
	// set_width_splits(screen_width);
	// set_height_splits(screen_height-slot_height);
	// refresh_all_splits();
	draw_mini_buffer();
	draw_lines_around_splits();
	if(show_help){
		help_menu->start_x = screen_width * 0.1;
		help_menu->start_y = screen_height * 0.1;
		help_menu->width = 0.8 * screen_width;
		help_menu->height = (0.88 * screen_height)-slot_height;
		help_menu->row_count = help_menu->height / slot_height;
		help_menu->column_count = help_menu->width / slot_width;
		draw_help_menu();
	}
	// print_splits();
}
