
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <vector>

struct slot{
	char character = ' ';
	unsigned char foreground[3] = {0xff,0xff,0xff};
	unsigned char background[3] = {0x30,0x30,0x30};
	char scheme = 'n';
};

struct buffer{
	char filepath[200];
	std::vector<char> data;
	std::vector<std::vector<slot>> rows;
	int mapped_first_line;
	int cursor_x = 0;
	int cursor_y = 0;
};

#endif
