
#include "split.h"
#include "globals.h"
#include "renderer.h"
#include "input.h"
#include "commands.h"

split::split(char _type){
	type = _type;
	merged_buffer = &buff1;
	start_x = 0;
	start_y = 0;
	width_usage = 1.0;
	height_usage = 1.0;
}
void split::refresh(){
	if(type == 'm'){
		if(child1 != 0){
			child1->refresh();}
		if(child2 != 0){
			child2->refresh();}
	}
	else if(type == 's'){
		refresh_split(this);
		Hwin->queue_draw();
	}
	else{
		child1->refresh();
		child2->refresh();
	}
}
void split::set_width(int _width){
	width = _width;
	if(type == 'm'){
		if(child1 != 0){
			child1->set_width(_width);}
		if(child2 != 0){
			child2->set_width(_width);}
	}
	else if(type == 's'){
		column_count = _width / slot_width;
	}
	else if(type == 'h'){
		child1->set_width(width * child1->width_usage);
		child1->start_x = start_x;
		child2->set_width(width * child2->width_usage);
		child2->start_x = child1->width + child1->start_x;
	}
	else{
		child1->start_x = start_x;
		child1->set_width(width);
		child2->start_x = start_x;
		child2->set_width(width);
	}
}

void split::set_height(int _height){
	height = _height;
	
	if(type == 'm'){
		if(child1 != 0){
			child1->set_height(_height);}
		if(child2 != 0){
			child2->set_height(_height);}
	}
	else if(type == 's'){
		row_count = height / slot_height;
	}
	else if(type == 'h'){
		child1->start_y = start_y;
		child1->set_height(height);
		child2->start_y = start_y;
		child2->set_height(height);
	}
	else{
		child1->start_y = start_y;
		child1->set_height(height * child1->height_usage);
		child2->start_y = child1->start_y + child1->height;
		child2->set_height(height * child2->height_usage);
	}
}

void split::get_width_usage(float _amount, split* _split){
	if(type == 'm'){return;}
	if(type == 's'){
		parent->get_width_usage(_amount, this);
	}
	else if(type == 'h'){
		split* _split2 = child2;
		
		if(_split == child2){
			_split2 = child1;}
		
		if(_split2->width_usage - _amount > 0.05 && _split2->width_usage - _amount < 0.95){
			_split->width_usage = _split->width_usage + _amount;
			_split2->width_usage = 1.0 - _split->width_usage;
			set_width(width);
			onResize();
			Hwin->queue_draw();
		}
		else{
			parent->get_width_usage(_amount, this);
		}
	}
	else if(type == 'v'){
		parent->get_width_usage(_amount, this);
	}
}
void split::get_height_usage(float _amount, split* _split){
	if(type == 'm'){return;}
	if(type == 's'){
		parent->get_height_usage(_amount, this);
	}
	else if(type == 'h'){
		parent->get_height_usage(_amount, this);
	}
	else if(type == 'v'){
		split* _split2 = child2;
		
		if(_split == child2){
			_split2 = child1;}
		
		if(_split2->height_usage - _amount > 0.05 && _split2->height_usage - _amount < 0.95){
			_split->height_usage = _split->height_usage + _amount;
			_split2->height_usage = 1.0 - _split->height_usage;
			set_height(height);
			onResize();
			Hwin->queue_draw();
		}
		else{
			parent->get_width_usage(_amount, this);
		}
	}
}
void split::split_left(){
	split* old_parent = parent;

	old_parent->remove_child(this);
	parent = new split('h');
	old_parent->add_child(parent);
	parent->width_usage = width_usage;
	parent->height_usage = height_usage;
	parent->child1 = this;
	parent->parent = old_parent;
	parent->start_x = start_x;
	parent->start_y = start_y;
	parent->width = width;
	parent->height = height;

	split* new_split= new split('s');
	add_split(new_split);
	parent->child2 = new_split;
	new_split->parent = parent;
	width_usage =  0.5;
	height_usage = 1.0;
	new_split->width_usage = 0.5;
	new_split->height_usage = height_usage;
	new_split->width = width - width/2;
	width = width/2;
	column_count = width / slot_width;
		
	new_split->column_count = new_split->width / slot_width;
	new_split->start_x = start_x + width;
	new_split->start_y = start_y;
	new_split->height = height;
	new_split->row_count = new_split->height / slot_height;
	new_split->merged_buffer = merged_buffer;

	// print_splits();
	active_split = new_split;
	onResize();
	Hwin->queue_draw();
}

void split::split_down(){
	split* old_parent = parent;
		
	old_parent->remove_child(this);
	parent = new split('v');
	old_parent->add_child(parent);
	parent->width_usage = width_usage;
	parent->height_usage = height_usage;
	parent->child1 = this;
	parent->parent = old_parent;
	parent->start_x = start_x;
	parent->start_y = start_y;
	parent->width = width;
	parent->height = height;

	split* new_split= new split('s');
	add_split(new_split);
	parent->child2 = new_split;
	new_split->parent = parent;
	height_usage = 0.5;
	width_usage = 1.0;
	new_split->height_usage = 0.5;
	new_split->width_usage = 1.0;
	new_split->height = height * new_split->height_usage;
	height = height * height_usage;
	column_count = height / slot_height;
	
	new_split->column_count = new_split->width / slot_width;
	new_split->start_x = start_x;
	new_split->start_y = start_y + height;
	new_split->width = width;
	new_split->row_count = new_split->height / slot_height;
	new_split->merged_buffer = merged_buffer;
	
	// print_splits();
	active_split = new_split;
	onResize();
	Hwin->queue_draw();
}

void split::add_child(split* _split){
	if(child1 == 0){child1 = _split;}
	else if(child2 == 0){child2 = _split;}
	else{printf("error cannot add child\n");}
}

void split::remove_child(split* _split){
	if(child1 == _split){child1 = 0;}
	else if(child2 == _split){child2 = 0;}
	else{printf("error cant remove, child not found\n");}
}

void split::delete_split(){
	if(parent->type == 'm'){
		printf("this is last split cant remove\n");
		return;
	}
	if(this != parent->child1 && this != parent->child2){
		printf("error: split::delete_split(), can't delete split\n");
	}
	split* _split = parent->child2;
	if(this == parent->child2){_split = parent->child1;}
	
	if(parent->type == 'h'){
		_split->width = parent->width;
		_split->width_usage = parent->width_usage;
		_split->height_usage = parent->height_usage;
		_split->start_x = parent->start_x;
	}
	else{
		_split->height = parent->height;
		_split->height_usage = parent->height_usage;
		_split->width_usage = parent->width_usage;
		_split->start_y = parent->start_y;
	}
	_split->parent = parent->parent;
	parent->parent->remove_child(parent);
	parent->parent->add_child(_split);
	remove_split(this);
	split* next_active_split = _split;
	int iterations = 0;
	while(next_active_split->type != 's'){
		next_active_split = next_active_split->child1;
		iterations++;
		if(iterations > 20){return;}
	}
	active_split = next_active_split;
	delete(parent);
	delete(this);
	onResize();
	Hwin->queue_draw();

}
void split::cursor_left(){
	if(merged_buffer->cursor_x > 0){
		merged_buffer->cursor_x--;
	}
	else{
		if(merged_buffer->cursor_y > 0){
			merged_buffer->cursor_y--;
		}
	}
	refresh();
}
void split::cursor_up(){
	if(merged_buffer->cursor_y > 0){
		merged_buffer->cursor_y--;
	}
	else{
		if(merged_buffer->mapped_first_line > 0){
			merged_buffer->mapped_first_line--;
		}
	}
	refresh();
}
void split::cursor_down(){
	if(merged_buffer->cursor_y < row_count){
		merged_buffer->cursor_y++;
	}
	else{
		merged_buffer->mapped_first_line++;
	}
	refresh();
}
void split::cursor_right(){
	if(merged_buffer->cursor_x < column_count){
		merged_buffer->cursor_x++;
	}
	else{
		merged_buffer->cursor_y++;
	}
	refresh();
}

// void load_file(){
	

// }
