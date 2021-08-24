#include <gtk/gtk.h>

void gtkplt_place_text(cairo_t *cr, const char *text,
                       double xpos, double ypos, double angle,
                       double RGBcolor[3], const char *font, int fontsize) {
    cairo_select_font_face(cr, font,
                           CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, fontsize);
    cairo_set_source_rgb(cr, RGBcolor[0], RGBcolor[1], RGBcolor[2]);

    cairo_font_extents_t font_extent;
    cairo_font_extents(cr, &font_extent);

    cairo_text_extents_t extent;
    cairo_text_extents(cr, text, &extent);

    double nx = -0.5*extent.width;
    double ny = 0.5*font_extent.height;

    cairo_translate(cr, xpos, ypos);
    cairo_rotate(cr, angle);
    cairo_translate(cr, nx, ny);
    cairo_move_to(cr, 0.0, 0.0);
    cairo_show_text(cr, text);
    cairo_restore(cr);
}
