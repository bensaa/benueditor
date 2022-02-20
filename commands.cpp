#include "split.h"
#include "globals.h"
#include "commands.h"
#include "renderer.h"
#include "input.h"

void toggle_help(){
	if(show_help){show_help = false;}
	else{show_help = true;}
	onResize();
}

void next_split(){
	for(int i = 0; i < split_count-1;i++){
		if(split_register[i] == active_split){
			active_split =  split_register[i + 1];
			return;
		}
	}
	active_split = split_register[0];
}

void add_split(split* _split){
	split_register[split_count] = _split;
	split_count++;
}

void remove_split(split* _split){
	if(split_count < 2) return;
	
	for(int i = 0; i < split_count;i++){
		if(split_register[i] == _split){
			for(int i2 = i; i2 < split_count - 1;i2++){
				split_register[i2] = split_register[i2+1];
			}
			break;
		}
	}
	split_count--;
}

void print_splits(){
	for(int i = 0; i < split_count;i++){
		if(split_register[i] == main_split){
			printf("main split: %u\n", split_register[i]);
		}	
		printf("split: %u start_x: %d width: %d width_usage: %f height: %d height_usage: %f\n",
			   split_register[i],
			   split_register[i]->start_x,
			   split_register[i]->width,
			   split_register[i]->width_usage,
			   split_register[i]->height,
			   split_register[i]->height_usage
			);
	}
}

void add_character_to_minibuffer(char _character){
	if(mb_position < mb_limit){
		char* tmp_p = mb_end;
		while(tmp_p >= mb_position){
			*(tmp_p + 1) = *tmp_p;
			tmp_p--;
		}
		*mb_position = _character;
		mb_end++;
		mb_position++;
		draw_mini_buffer();
		Hwin->queue_draw();
	}
}

void remove_chacters_from_minibuffer(int _count){
	char* tmp_p = mb_position;
	while((tmp_p + _count) < mb_end){
		*tmp_p = *(tmp_p + _count);
		tmp_p++;
	}
	*tmp_p = 0x00;
	mb_end = tmp_p;
	draw_mini_buffer();
	Hwin->queue_draw();
}

void move_mb_cursor(int _count){
	mb_position += _count;
	if(mb_position >= mb_limit){
		mb_position = (char*)(mb_limit - 1);
	}
	else if(mb_position > mb_end){
		mb_position = mb_end;
	}
	else if(mb_position < minibuffer_text){
		mb_position = minibuffer_text;
	}
}

void mb_execute_command(){
	printf("%s\n",minibuffer_text);
}

// struct buffer{
// 	char filepath[200];
// 	std::vector<char> data;
// 	std::vector<std::vector<slot>> rows;
// 	int mapped_first_line;
// 	int cursor_x;
// 	int cursor_y;
// };

// struct slot{
// 	char character = ' ';
// 	unsigned char foreground[3] = {0xff,0xff,0xff};
// 	unsigned char background[3] = {0x30,0x30,0x30};
// 	char scheme = 'n';
// };

void load_file(char* _path){
	FILE *fp = fopen(_path, "rb");
	fseek(fp, 0, SEEK_END);
	long fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char buff[fsize];
	fread(buff, 1, fsize, fp);
	fclose(fp);
	buffer* new_buffer = (buffer*)malloc(sizeof(buffer));

	std::vector<slot> line;
	for(char* c = buff;c < buff + fsize;c++){
		if(*c == '\n') {
			new_buffer->rows.push_back(line);
			line.clear();
		}
		else{
			line.push_back({*c, {0xff,0xff,0xff},{0x30,0x30,0x30},'n'});
		}
	}
	new_buffer->rows.push_back(line);

	buffer_register.push_back(new_buffer);

}
