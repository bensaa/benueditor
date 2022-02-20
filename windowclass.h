#ifndef WINDOWCLASS_H
#define WINDOWCLASS_H

#include <gtkmm/drawingarea.h>

class Windowclass : public Gtk::DrawingArea{
public:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

#endif
