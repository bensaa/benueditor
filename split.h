#ifndef SPLIT_H
#define SPLIT_H

#include "structures.h"
#include "vector"

class split {
public:
	bool constant = false;
	bool show = false;
	char type;
	buffer* merged_buffer;
	int start_x;
	int start_y;
	int column_count;
	int row_count;
	float width_usage;
	float height_usage;
	split* parent = 0;
	int height;
	int width;
	split* child1 = 0;
	split* child2 = 0;
	
	split(char _type);
	std::vector<split*> childs;
	void refresh();
	void set_width(int _width);
	void set_height(int _height);
	void get_width_usage(float _amount, split* _split);
	void get_height_usage(float _amount, split* _split);
	void split_left();
	void split_down();
	void add_child(split* _split);
	void remove_child(split* _split);
	void delete_split();
	void cursor_left();
	void cursor_up();
	void cursor_down();
	void cursor_right();
};

#endif
