#ifndef INPUT_H
#define INPUT_H

#include <gdkmm/general.h>

void next_split();
bool onKeyPress(GdkEventKey* event);
bool onKeyRelease(GdkEventKey* event);
void onResize();

#endif
