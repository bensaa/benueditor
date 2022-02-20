#include "globals.h"
#include "split.h"
#include "renderer.h"
#include "characters.h"

void refresh_all_splits(){
	for(int i = 0; i < split_count;i++){
		if(split_register[i]->show){
			refresh_split(split_register[i]);
			draw_lines_around_split(split_register[i]);
		}
	}
    Hwin->queue_draw();
}

void draw_lines_around_split(split* _split){
	char* tmp_color;

	tmp_color = inactive_split_colors;
		
	int split_start_offset_x = _split->start_x*3;
	int split_start_offset_y = _split->start_y*screen_width_bytes;
		
	char* tmp_image_pointer = image_pointer + split_start_offset_y +
		split_start_offset_x;
		
	if(_split == active_split){tmp_color = active_split_colors;}

	//top edge
	char* pixel_pointer = tmp_image_pointer;
	char* pixel_pointer2 = tmp_image_pointer + screen_width_bytes;
	for(int i2 = 0; i2 < _split->width;i2++){
		*pixel_pointer++ = tmp_color[0];
		*pixel_pointer++ = tmp_color[1];
		*pixel_pointer++ = tmp_color[2];
		*pixel_pointer2++ = tmp_color[0];
		*pixel_pointer2++ = tmp_color[1];
		*pixel_pointer2++ = tmp_color[2];
	}
	//bottom edge
	pixel_pointer = tmp_image_pointer + (_split->height-slot_height)*screen_width_bytes;
	pixel_pointer2 = tmp_image_pointer + (_split->height-slot_height+1)*screen_width_bytes;
	for(int i2 = 0; i2 < _split->width;i2++){
		*pixel_pointer++ = tmp_color[0];
		*pixel_pointer++ = tmp_color[1];
		*pixel_pointer++ = tmp_color[2];
		*pixel_pointer2++ = tmp_color[0];
		*pixel_pointer2++ = tmp_color[1];
		*pixel_pointer2++ = tmp_color[2];
	}
	//right edge
	pixel_pointer = tmp_image_pointer - 6 + _split->width*3;
	for(int i2 = 0; i2 < _split->height-slot_height;i2++){
		*pixel_pointer++ = tmp_color[0];
		*pixel_pointer++ = tmp_color[1];
		*pixel_pointer++ = tmp_color[2];
		*pixel_pointer++ = tmp_color[0];
		*pixel_pointer++ = tmp_color[1];
		*pixel_pointer++ = tmp_color[2];
		pixel_pointer += screen_width_bytes - 6;
	}
	//left edge
	pixel_pointer = tmp_image_pointer;
	for(int i2 = 0; i2 < _split->height-slot_height;i2++){
		*pixel_pointer++ = tmp_color[0];
		*pixel_pointer++ = tmp_color[1];
		*pixel_pointer++ = tmp_color[2];
		*pixel_pointer++ = tmp_color[0];
		*pixel_pointer++ = tmp_color[1];
		*pixel_pointer++ = tmp_color[2];
		pixel_pointer += screen_width_bytes - 6;
	}
}


void draw_lines_around_splits(){
	char* tmp_color;

	for(int i = 0; i < split_count;i++){
		tmp_color = inactive_split_colors;
		split* _split = split_register[i];
		
		int split_start_offset_x = _split->start_x*3;
		int split_start_offset_y = _split->start_y*screen_width_bytes;
		
		char* tmp_image_pointer = image_pointer + split_start_offset_y +
			split_start_offset_x;
		
		if(_split == active_split){tmp_color = active_split_colors;}

		//top edge
		char* pixel_pointer = tmp_image_pointer;
		char* pixel_pointer2 = tmp_image_pointer + screen_width_bytes;
		for(int i2 = 0; i2 < _split->width;i2++){
			*pixel_pointer++ = tmp_color[0];
			*pixel_pointer++ = tmp_color[1];
			*pixel_pointer++ = tmp_color[2];
			*pixel_pointer2++ = tmp_color[0];
			*pixel_pointer2++ = tmp_color[1];
			*pixel_pointer2++ = tmp_color[2];
		}
		//bottom edge
		pixel_pointer = tmp_image_pointer + (_split->height-slot_height)*screen_width_bytes;
		pixel_pointer2 = tmp_image_pointer + (_split->height-slot_height+1)*screen_width_bytes;
		for(int i2 = 0; i2 < _split->width;i2++){
			*pixel_pointer++ = tmp_color[0];
			*pixel_pointer++ = tmp_color[1];
			*pixel_pointer++ = tmp_color[2];
			*pixel_pointer2++ = tmp_color[0];
			*pixel_pointer2++ = tmp_color[1];
			*pixel_pointer2++ = tmp_color[2];
		}
		//right edge
		pixel_pointer = tmp_image_pointer - 6 + _split->width*3;
		for(int i2 = 0; i2 < _split->height-slot_height;i2++){
			*pixel_pointer++ = tmp_color[0];
			*pixel_pointer++ = tmp_color[1];
			*pixel_pointer++ = tmp_color[2];
			*pixel_pointer++ = tmp_color[0];
			*pixel_pointer++ = tmp_color[1];
			*pixel_pointer++ = tmp_color[2];
			pixel_pointer += screen_width_bytes - 6;
		}
		//left edge
		pixel_pointer = tmp_image_pointer;
		for(int i2 = 0; i2 < _split->height-slot_height;i2++){
			*pixel_pointer++ = tmp_color[0];
			*pixel_pointer++ = tmp_color[1];
			*pixel_pointer++ = tmp_color[2];
			*pixel_pointer++ = tmp_color[0];
			*pixel_pointer++ = tmp_color[1];
			*pixel_pointer++ = tmp_color[2];
			pixel_pointer += screen_width_bytes - 6;
		}
	}
}

void draw_char(char* _position,unsigned char _character,char fg_color,char bg_color){
	unsigned char* tmp_char = characters[_character];
	unsigned int end_to_next_row_begin = screen_width_bytes - slot_width_bytes;

	for(int i3 = 0; i3 < slot_height;i3++){
		unsigned char tmp_byte = tmp_char[i3+i3];
		int i5 = 0;
		for(int i4 = 0; i4 < slot_width;i4++){
			if(i5 == 8){
				i5 = 0;
				tmp_byte = tmp_char[i3+i3+1];
			}
			unsigned char bitmask = 0b10000000 >> (i5);
			if((tmp_byte & bitmask) == bitmask){
				*_position++ = fg_color;
				*_position++ = fg_color;
				*_position++ = fg_color;
			}
			else{
				*_position++ = bg_color;
				*_position++ = bg_color;
				*_position++ = bg_color;
			}
			i5++;
		}
		_position += end_to_next_row_begin;
	}
}

void draw_cursor(split* _split){
	buffer* pbuff = _split->merged_buffer;

	int current_line = pbuff->cursor_y - pbuff->mapped_first_line;
	char _character = pbuff->rows[current_line][pbuff->cursor_x].character;
	//check which character cursor covers
	unsigned char* tmp_char;
	if(_character == '\t'){
		tmp_char = character_empty;
	}
	else{
		tmp_char = characters[_character];
	}

	int offset_y = _split->start_y*screen_width_bytes +
		pbuff->cursor_y*slot_height*screen_width_bytes;
	int offset_x = _split->start_x*3;

	for(int i = 0; i < pbuff->cursor_x;i++){
		if(pbuff->rows[current_line][i].character == '\t'){
			offset_x += slot_width_bytes * 4;
		}
		else{
			offset_x += slot_width_bytes;
		}
	}
	char* _position = image_pointer + offset_y + offset_x;

	for(int i3 = 0; i3 < slot_height;i3++){
		unsigned char tmp_byte = tmp_char[i3+i3];
		for(int i4 = 0; i4 < slot_width;i4++){
			unsigned char bitmask = 0b10000000 >> (i4 % 8);
			if(i4 == 8){
				tmp_byte = tmp_char[i3+i3+1];
			}
			if((tmp_byte & bitmask) == bitmask){
				*_position++ = 0x00;
				*_position++ = 0x00;
				*_position++ = 0x00;
			}
			else{
				*_position++ = 0xff;
				*_position++ = 0x00;
				*_position++ = 0x00;
			}
		}
		_position += (screen_width*3 - slot_width_bytes);
	}
}


void refresh_split(split* _split){
	int split_start_offset_x = _split->start_x*3;
	int split_end_offset_x = _split->start_x*3+_split->width*3;

	int split_start_offset_y = _split->start_y*screen_width_bytes;
	buffer* pbuff = _split->merged_buffer;

	char* tmp_image_pointer = image_pointer + split_start_offset_y +
		split_start_offset_x;

	for(int i = 0; i < _split->row_count;i++){
		if(pbuff->rows.size() <= i){break;}
		char* old_row_start_pointer = tmp_image_pointer;

		int i2 = 0;
		int slot_offset_x = 0;
		while(slot_offset_x < _split->column_count){
			if(pbuff->rows[i].size() <= i2){break;}

			if(pbuff->rows[i][i2].character == '\t'){
				if(slot_offset_x >= _split->column_count-4){break;}

				char* pixel_pointer = tmp_image_pointer;
				
				for(int i3 = 0; i3 < slot_height;i3++){
					for(int i4 = 0; i4 < slot_width*4;i4++){
						*pixel_pointer++ = 0x30;
						*pixel_pointer++ = 0x30;
						*pixel_pointer++ = 0x30;
					}
					pixel_pointer += (screen_width_bytes - slot_width_bytes*4);
				}

				slot_offset_x += 4;
				tmp_image_pointer += slot_width_bytes*4;
				i2++;
			}
			else{
				unsigned char* fg_color = pbuff->rows[i][i2].foreground;
				unsigned char* bg_color = pbuff->rows[i][i2].background;
				unsigned char* tmp_char = characters[pbuff->rows[i][i2].character];
				char* pixel_pointer = tmp_image_pointer;

				for(int i3 = 0; i3 < slot_height;i3++){

					int i5 = 0;
					unsigned char tmp_char2 = tmp_char[i3+i3];
					for(int i4 = 0; i4 < slot_width;i4++){
						if(i5 == 8){
							i5 = 0;
							tmp_char2 = tmp_char[i3+i3+1];
						}
						unsigned char bitmask = 0b10000000 >> i5;
						if((tmp_char2 & bitmask) == bitmask){
							*pixel_pointer++ = fg_color[0];
							*pixel_pointer++ = fg_color[1];
							*pixel_pointer++ = fg_color[2];
						}
						else{
							*pixel_pointer++ = bg_color[0];
							*pixel_pointer++ = bg_color[1];
							*pixel_pointer++ = bg_color[2];
						}
						i5++;
					}
					pixel_pointer += (screen_width_bytes - slot_width_bytes);
				}
				slot_offset_x += 1;
				tmp_image_pointer += slot_width_bytes;
				i2++;
			}
		}
		//fill_cap
		char* pixel_pointer = tmp_image_pointer;
		unsigned int cap_width_bytes = (_split->width - slot_offset_x * slot_width) * 3;
		char* tmp_limit = pixel_pointer + cap_width_bytes;
		
		for(int i = 0; i < slot_height;i++){
			while(pixel_pointer < tmp_limit){
				*pixel_pointer++ = 0x30;
			}
			pixel_pointer += screen_width_bytes - cap_width_bytes;
			tmp_limit += screen_width_bytes;
		}
		
		tmp_image_pointer = old_row_start_pointer +  slot_height*screen_width_bytes;
	}
	
	//draw missing lines
	char* tmp_pointer = tmp_image_pointer;
	char* tmp_limit = tmp_image_pointer + _split->width * 3;
	int missing_lines_count = _split->height - (pbuff->rows.size() * slot_height);
	
	for(int i = 0; i < missing_lines_count;i++){
		tmp_pointer = tmp_image_pointer;
		while(tmp_pointer < tmp_limit)*tmp_pointer++ = 0x00;			
		
		tmp_image_pointer += screen_width_bytes;
		tmp_limit += screen_width_bytes;
	}

	tmp_image_pointer = image_pointer + split_start_offset_x + split_start_offset_y
		+ (_split->height- slot_height)*screen_width_bytes;
	
	// draw mode-line
	for(int i = 0; i < _split->column_count;i++){
		if(i < strlen(pbuff->filepath)){
			draw_char(tmp_image_pointer, pbuff->filepath[i],0xff,0x00);
			tmp_image_pointer += slot_width_bytes;
		}
		else{break;}
	}

	//fill mode-line end
	int cap_lenght_bytes;
	if(_split->column_count > strlen(pbuff->filepath)){
		cap_lenght_bytes = (_split->width - strlen(pbuff->filepath)*slot_width)*3;
	}
	else{
		cap_lenght_bytes = _split->width*3 - _split->column_count * slot_width_bytes;
	}
	char* pixel_pointer = tmp_image_pointer;

	for(int i = 0; i < slot_height;i++){
		while(pixel_pointer < (tmp_image_pointer + cap_lenght_bytes)){
			*pixel_pointer++ = 0x00;
		}
		tmp_image_pointer = tmp_image_pointer + screen_width_bytes;
		pixel_pointer = tmp_image_pointer;
	}
	
	draw_cursor(_split);

}

void draw_help_menu(){
	split* _split = help_menu;
	
	int split_start_offset_x = _split->start_x*3;
	int split_end_offset_x = _split->start_x*3+_split->width*3;

	int split_start_offset_y = _split->start_y*screen_width_bytes;
	buffer* pbuff = _split->merged_buffer;

	char* tmp_image_pointer = image_pointer + split_start_offset_y +
		split_start_offset_x;

	for(int i = 0; i < _split->row_count;i++){
		if(pbuff->rows.size() <= i){break;}
		char* old_row_start_pointer = tmp_image_pointer;

		int i2 = 0;
		int slot_offset_x = 0;
		while(slot_offset_x < _split->column_count){
			if(pbuff->rows[i].size() <= i2){break;}

			if(pbuff->rows[i][i2].character == '\t'){
				if(slot_offset_x >= _split->column_count-4){break;}

				char* pixel_pointer = tmp_image_pointer;
				
				for(int i3 = 0; i3 < slot_height;i3++){
					for(int i4 = 0; i4 < slot_width*4;i4++){
						*pixel_pointer++ = 0x00;
						*pixel_pointer++ = 0x00;
						*pixel_pointer++ = 0x00;
					}
					pixel_pointer += (screen_width_bytes - slot_width_bytes*4);
				}

				slot_offset_x += 4;
				tmp_image_pointer += slot_width_bytes*4;
				i2++;
			}
			else{
				unsigned char* tmp_char = characters[pbuff->rows[i][i2].character];
				char* pixel_pointer = tmp_image_pointer;

				for(int i3 = 0; i3 < slot_height;i3++){

					int i5 = 0;
					unsigned char tmp_char2 = tmp_char[i3+i3];
					for(int i4 = 0; i4 < slot_width;i4++){
						if(i5 == 8){
							i5 = 0;
							tmp_char2 = tmp_char[i3+i3+1];
						}
						unsigned char bitmask = 0b10000000 >> i5;
						if((tmp_char2 & bitmask) == bitmask){
							*pixel_pointer++ = 0xff;
							*pixel_pointer++ = 0xff;
							*pixel_pointer++ = 0xff;
						}
						else{
							*pixel_pointer++ = 0x00;
							*pixel_pointer++ = 0x00;
							*pixel_pointer++ = 0x00;
						}
						i5++;
					}
					pixel_pointer += (screen_width_bytes - slot_width_bytes);
				}
				slot_offset_x += 1;
				tmp_image_pointer += slot_width_bytes;
				i2++;
			}
		}
		//fill_cap
		char* pixel_pointer = tmp_image_pointer;
		unsigned int cap_width_bytes = (_split->width - slot_offset_x * slot_width) * 3;
		char* tmp_limit = pixel_pointer + cap_width_bytes;

		for(int i = 0; i < slot_height;i++){
			while(pixel_pointer < tmp_limit){
				*pixel_pointer++ = 0x00;
			}
			pixel_pointer += screen_width_bytes - cap_width_bytes;
			tmp_limit += screen_width_bytes;
		}
		tmp_image_pointer = old_row_start_pointer +  slot_height*screen_width*3;
	}

	//draw missing lines
	char* tmp_pointer = tmp_image_pointer;
	char* tmp_limit = tmp_image_pointer + _split->width * 3;
	int missing_lines_count = _split->height - (pbuff->rows.size() * slot_height);
	
	for(int i = 0; i < missing_lines_count;i++){
		tmp_pointer = tmp_image_pointer;
		
		while(tmp_pointer < tmp_limit)*tmp_pointer++ = 0x00;
		
		tmp_image_pointer += screen_width_bytes;
		tmp_limit += screen_width_bytes;
	}

	tmp_image_pointer = image_pointer + split_start_offset_x + split_start_offset_y
		+ (_split->height- slot_height)*screen_width_bytes;
	
	// draw mode-line
	for(int i = 0; i < _split->column_count;i++){
		if(i < strlen(pbuff->filepath)){
			draw_char(tmp_image_pointer, pbuff->filepath[i],0xff,0x00);
			tmp_image_pointer += slot_width_bytes;
		}
		else{break;}
	}

	//fill mode-line end
	int cap_lenght_bytes;
	if(_split->column_count > strlen(pbuff->filepath)){
		cap_lenght_bytes = (_split->width - strlen(pbuff->filepath)*slot_width)*3;
	}
	else{
		cap_lenght_bytes = _split->width*3 - _split->column_count * slot_width_bytes;
	}
	char* pixel_pointer = tmp_image_pointer;

	for(int i = 0; i < slot_height;i++){
		while(pixel_pointer < (tmp_image_pointer + cap_lenght_bytes)){
			*pixel_pointer++ = 0x00;
		}
		tmp_image_pointer = tmp_image_pointer + screen_width_bytes;
		pixel_pointer = tmp_image_pointer;
	}
	// draw_cursor(_split);
}

void clear_screen(){
	char* tmp_pointer = image_pointer;
	char* tmp_end_pointer = image_pointer + 1920*screen_height*3;
	for(;tmp_pointer < tmp_end_pointer; tmp_pointer++){
		*tmp_pointer = 0x30;
	}
}

void draw_mini_buffer(){
	int minibuffer_y_offset = (screen_height - slot_height) * screen_width_bytes;

	char* tmp_pointer = image_pointer + minibuffer_y_offset;
	for(int i = 0; i < slot_height;i++){
		for(int i2 = 0; i2 < screen_width*3;i2++){
			*tmp_pointer++ = 0x20;
		}
	}
	unsigned char mode_char = 'N';
	if(current_mode == commandMode){
		mode_char = 'C';
	}
	draw_char(image_pointer + minibuffer_y_offset + screen_width_bytes - slot_width_bytes -3,
			  mode_char,0xff,0x20);

	tmp_pointer = image_pointer + minibuffer_y_offset;
	char* tmp_text_pointer = minibuffer_text;
	
	while(*tmp_text_pointer != 0x00){
		if(tmp_text_pointer == mb_position)
			draw_char(tmp_pointer,'_',0xff,0x20);
		else
			draw_char(tmp_pointer,*tmp_text_pointer,0xff,0x20);
		
		tmp_pointer += slot_width_bytes;
		tmp_text_pointer++;
	}
	if(mb_position == mb_end){
		draw_char(tmp_pointer,'_',0xff,0x20);
	}
}

