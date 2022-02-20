#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "globals.h"
#include "commands.h"
#include "windowclass.h"
#include "input.h"

void static init_function(){
	add_split(main_split);
	active_split = main_split;

	std::string file1txt = "This is file1.(green highligth)\n\nThere is some sample text.\n"
		"Fourth line\nMore data\nMore data\nEnd of this file.\n\n\nAnother header(green highligth)\n"
		"\nData data.\nFinland Suomi.\nAnother line.\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	int ii = 0;
	buff1.rows.emplace_back();
	while(ii < file1txt.length()){
		if(file1txt[ii] == '\n'){
			buff1.rows.emplace_back();
		}
		else{
			int rowI = buff1.rows.size() - 1;
			buff1.rows[rowI].emplace_back();
			int charI = buff1.rows[rowI].size() - 1;
			buff1.rows[rowI][charI].character = file1txt[ii];
			if(rowI == 0 || rowI == 9){
				buff1.rows[rowI][charI].foreground[0] = 0x00;
				buff1.rows[rowI][charI].foreground[1] = 0xff;
				buff1.rows[rowI][charI].foreground[2] = 0x00;
			}
		}
		ii++;
	}

	buff1.cursor_y = 2;
	strcpy(buff1.filepath, "/home/benu/main.cpp");

	char tmp_arr[200];
	char* tmp_pointer = help_menu_text;
	int line_index = 0;
	int char_index = 0;
	help_buffer.cursor_y = 2;
	help_buffer.rows.emplace_back();

	for(int i = 0; i < strlen(help_menu_text);i++){
		if(help_menu_text[i] == '\n'){
			help_buffer.rows.emplace_back();
			line_index++;
			char_index = 0;
			tmp_pointer++;
		}
		else{
			help_buffer.rows[line_index].emplace_back();
			help_buffer.rows[line_index][char_index].character = *tmp_pointer++;
			char_index++;
		}
	}

	printf("size: %d\n", help_buffer.rows.size());
	printf("test\n", help_buffer.rows.size());

	strcpy(help_buffer.filepath, " F1 to close this window.");

	main_frame->show = true;
	main_frame->constant = true;
	main_frame->start_x = 0;
	main_frame->start_y = 0;
	main_frame->merged_buffer = &buff1;
	main_frame->row_count = 20;
	main_frame->column_count = 20;
	
	// main_frame->childs.push_back(main_split);
	main_frame->child1 = main_split;


	main_split->parent = main_frame;
	main_split->show = true;
	main_split->start_x = 0;
	main_split->start_y = 0;
	main_split->merged_buffer = &buff1;
	main_split->row_count = 20;
	main_split->column_count = 20;

	help_menu->show = true;
	help_menu->width_usage = 0.8;
	help_menu->height_usage = 0.8;
	help_menu->start_x = screen_width * 0.1;
	help_menu->start_y = screen_height * 0.1;
	help_menu->width = 0.8 * screen_width;
	help_menu->height = 0.8 * screen_height;
	// help_menu->merged_buffer = &help_buffer;
	help_menu->merged_buffer = &help_buffer;
	help_menu->row_count = help_menu->height / slot_height;
	help_menu->column_count = help_menu->width / slot_width;
}



int main(int argc, char** argv){
	init_function();
	image_pointer = (char*)malloc(2000*1100*3);
	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
	Happ = &app;
	Gtk::Window win;
	win.set_default_size(600,600);
	win.set_title("benu");
	Windowclass drawarea_3D;
	Hwin = &drawarea_3D;
	win.signal_key_press_event().connect(sigc::ptr_fun(onKeyPress),false );
	win.signal_key_release_event().connect(sigc::ptr_fun(onKeyRelease),false );
	win.signal_check_resize().connect(sigc::ptr_fun(onResize),false );
	win.add(drawarea_3D);

	drawarea_3D.show();

	return app->run(win);
}

