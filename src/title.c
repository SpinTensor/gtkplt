#include "gtkplt.h"
#include "margins.h"

double gtkplt_ttmargin_xmin(GtkPltPlotData *data) {
   return gtkplt_olmargin_xmax(data);
}
double gtkplt_ttmargin_ymin(GtkPltPlotData *data) {
   return gtkplt_otmargin_ymax(data);
}
double gtkplt_ttmargin_xmax(GtkPltPlotData *data) {
   return gtkplt_ormargin_xmin(data);
}
double gtkplt_ttmargin_ymax(GtkPltPlotData *data) {
   return gtkplt_ttmargin_ymin(data) + data->title_margin;
}

double gtkplt_tbmargin_xmin(GtkPltPlotData *data) {
   return gtkplt_ttmargin_xmin(data);
}
double gtkplt_tbmargin_ymin(GtkPltPlotData *data) {
   return gtkplt_ttmargin_ymin(data)+data->title_height;
}
double gtkplt_tbmargin_xmax(GtkPltPlotData *data) {
   return gtkplt_ttmargin_xmax(data);
}
double gtkplt_tbmargin_ymax(GtkPltPlotData *data) {
   return gtkplt_tbmargin_ymin(data) + data->title_margin;
}

void gtkplt_set_title(GtkPltPlot *plot, const char *title) {
   GtkPltPlotData *data = plot->data;
   gtkplt_remove_title(plot);
   data->title = strdup(title);
}

void gtkplt_remove_title(GtkPltPlot *plot) {
   GtkPltPlotData *data = plot->data;
   if (data->title != NULL) {
      free(data->title);
   }
   data->title = NULL;
}

void gtkplt_set_title_font(GtkPltPlot *plot, const char *font) {
   GtkPltPlotData *data = plot->data;
   free(data->titlefont);
   data->titlefont = strdup(font);
}

void gtkplt_set_title_fontsize(GtkPltPlot *plot, int fontsize) {
   GtkPltPlotData *data = plot->data;
   data->titlefontsize = fontsize;
}

void gtkplt_plot_draw_title(cairo_t *cr, GtkPltPlotData *data) {
   if (data->title == NULL) {
      // no title
      // set title area to zero height
      data->title_height = 0;
      data->title_margin = 0;
   } else {
      cairo_select_font_face(cr, data->titlefont,
                             CAIRO_FONT_SLANT_NORMAL,
                             CAIRO_FONT_WEIGHT_BOLD);

      cairo_set_font_size(cr, data->titlefontsize);

      // get the extent of the text about to displayed.
      cairo_text_extents_t extents;
      cairo_text_extents(cr, data->title, &extents);

      // set the title margin
      data->title_margin = extents.height*0.5;
      // set the title height
      data->title_height = extents.height;

      double xcenter = 0.5*(gtkplt_ttmargin_xmin(data) + gtkplt_ttmargin_xmax(data));
      double ycenter = 0.5*(gtkplt_tbmargin_ymin(data) + gtkplt_ttmargin_ymax(data));

      cairo_move_to(cr,
                    xcenter - extents.width*0.5,
                    ycenter + extents.height*0.25);
      cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
      cairo_show_text(cr, data->title);
   }
}
