#include "windowclass.h"
#include <gtkmm/drawingarea.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <glibmm/fileutils.h>
#include "globals.h"
#include "renderer.h"


bool Windowclass::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
	auto start = std::chrono::high_resolution_clock::now();
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

	// main_split.refresh_all();
	// draw_mini_buffer();

	start = std::chrono::high_resolution_clock::now();
	auto image = Gdk::Pixbuf::create_from_data((const guint8*)image_pointer ,
											   Gdk::Colorspace::COLORSPACE_RGB, false, 8,
											   screen_width, screen_height, screen_width_bytes);
	Gdk::Cairo::set_source_pixbuf(cr, image, 0, 0);
	cr->rectangle(0, 0, screen_width, screen_height);
	cr->fill();
	stop = std::chrono::high_resolution_clock::now();

	
	duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
	printf("time: %lu microseconds\n\n",duration.count()/1000);
	return true;
}

