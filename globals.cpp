#include "globals.h"
#include "split.h"
#include "windowclass.h"


MODE current_mode = normalMode;
bool show_help = false;

int screen_width = 600;
int screen_width_bytes = 1800;
int screen_height = 600;
int screen_height_bytes = 1800;
int slot_width = 14;
int slot_width_bytes = 42;
int slot_height = 28;
char* image_pointer;

bool ctrl_down = false;
bool shift_down = false;
bool alt_down = false;
bool ctrl_x_prefix = false;

buffer buff1;
buffer help_buffer;
char help_menu_text[2000] =	
	" HELP MENU 2222\n"
	" F1 To toggle this window.\n"
	"\n"
	" MOVEMENT KEYS:\n"
	" C-p previous line\n"
	" C-n next line\n"
	" C-f forward char\n"
	" C-b backward char\n"
	"\n"
	" M-f forward word\n"
	" M-b backward word\n"
	"\n"
	" M-9 previous buffer\n"
	" M-0 next buffer\n"
	" C-x 2 split vertically\n"
	" C-x 3 split horizontially";


char minibuffer_text[300] = {'t','h','i','s',' ','i',
	's',' ','c','o','m','m','a','n','d','l','i','n','e',0x00};
char* mb_position = minibuffer_text;
char* mb_end = minibuffer_text + 4;
const char* mb_limit = minibuffer_text + 299;

split* main_split = new split('s');
split* main_frame = new split('m');
split* help_menu = new split('s');

split* active_split = NULL;
split* split_register[20] = {main_split};
std::vector<buffer*> buffer_register;
int split_count = 0;

Glib::RefPtr<Gtk::Application>* Happ;
Windowclass* Hwin = NULL;

char inactive_split_colors[3] = {0x00,0x00,0x00};
char active_split_colors[3] = {0x00,0x40,0x00};

int border_width = 2;
int border_width_bytes = border_width*3;


