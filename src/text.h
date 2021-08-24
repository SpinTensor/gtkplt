#ifndef TEXT_H
#define TEXT_H

#include <gtk/gtk.h>

void gtkpl_place_text(cairo_t *cr, const char *text,
                      double xpos, double ypos, double angle,
                      double RGBcolor[3], const char *font, int fontsize);
#endif
