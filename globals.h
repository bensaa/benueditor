#ifndef GLOBALS_H
#define GLOBALS_H

#include "split.h"
#include "structures.h"
#include "windowclass.h"
#include <gtkmm/application.h>
#include <vector>

enum MODE {
	normalMode = 0,commandMode
};

extern MODE current_mode;
extern bool show_help;

extern int screen_width;
extern int screen_width_bytes;
extern int screen_height;
extern int screen_height_bytes;
extern int slot_width;
extern int slot_width_bytes;
extern int slot_height;
extern char* image_pointer;
extern bool ctrl_down;
extern bool shift_down;
extern bool alt_down;
extern bool ctrl_x_prefix;

extern buffer buff1;
extern buffer help_buffer;
extern char help_menu_text[2000];

extern char minibuffer_text[300];
extern char* mb_end;
extern char* mb_position;
extern const char* mb_limit;


extern split* main_split;
extern split* main_frame;
extern split* help_menu;

extern split* active_split;
extern split* split_register[20];
extern std::vector<buffer*> buffer_register;

extern int split_count;
extern Glib::RefPtr<Gtk::Application>* Happ;
extern Windowclass* Hwin;

extern char inactive_split_colors[3];
extern char active_split_colors[3];

extern int border_width;
extern int border_width_bytes;

#endif
