#include <stdlib.h>

#include "gtkplt.h"
#include "margins.h"
#include "title.h"
#include "axis.h"

GtkPltPlotAxis *gtkplt_axis_init() {
   GtkPltPlotAxis *axis = (GtkPltPlotAxis*) malloc(sizeof(GtkPltPlotAxis));
   axis->scale = gtkplt_linear;
   axis->linewidth = 3.0;
   axis->nmajorticks = 10;
   axis->nminorticks = 4;
   axis->range[0] = 0.0;
   axis->range[1] = 10.0;
   axis->title = NULL;
   axis->titlefont = strdup("Helvetica");
   axis->titlefontsize = 12;
   axis->labelfont = strdup("Helvetica");
   axis->labelfontsize = 12;
   axis->titlewidth = 0.0;
   axis->titlelabeldist = 0.0;
   axis->labelwidth = 0.0;
   axis->labeltickdist = 0.0;
   axis->tickwidth = 9.0;
   
   return axis;
}

void gtkplt_axis_finalize(GtkPltPlotAxis *axis_ptr) {
   if (axis_ptr->title != NULL) {
      free(axis_ptr->title);
      axis_ptr->title = NULL;
   }
   free(axis_ptr->titlefont);
   free(axis_ptr->labelfont);
   free(axis_ptr);
}

double gtkplt_xaxis_area_xmin(GtkPltPlotData *data) {
   return gtkplt_yaxis_area_xmax(data);
}
double gtkplt_xaxis_area_xmax(GtkPltPlotData *data) {
   return gtkplt_ormargin_xmin(data);
}
double gtkplt_xaxis_area_ymin(GtkPltPlotData *data) {
   double xaxis_width = 0.0;
   xaxis_width += data->xaxis->titlewidth;
   xaxis_width += data->xaxis->titlelabeldist;
   xaxis_width += data->xaxis->labelwidth;
   xaxis_width += data->xaxis->labeltickdist;
   xaxis_width += data->xaxis->tickwidth;
   return gtkplt_xaxis_area_ymax(data)-xaxis_width;
}
double gtkplt_xaxis_area_ymax(GtkPltPlotData *data) {
   return gtkplt_obmargin_ymin(data);
}

double gtkplt_yaxis_area_xmin(GtkPltPlotData *data) {
   return gtkplt_olmargin_xmax(data);
}
double gtkplt_yaxis_area_xmax(GtkPltPlotData *data) {
   double yaxis_width = 0.0;
   yaxis_width += data->yaxis->titlewidth;
   yaxis_width += data->yaxis->titlelabeldist;
   yaxis_width += data->yaxis->labelwidth;
   yaxis_width += data->yaxis->labeltickdist;
   yaxis_width += data->yaxis->tickwidth;

   return gtkplt_yaxis_area_xmin(data) + yaxis_width;
}
double gtkplt_yaxis_area_ymin(GtkPltPlotData *data) {
   return gtkplt_tbmargin_ymax(data);
}
double gtkplt_yaxis_area_ymax(GtkPltPlotData *data) {
   return gtkplt_xaxis_area_ymin(data);
}

void gtkplt_set_xaxis_title(GtkPltPlot *plot, const char *title) {
   GtkPltPlotData *data = plot->data;
   gtkplt_remove_xaxis_title(plot);
   data->xaxis->title = strdup(title);
}

void gtkplt_remove_xaxis_title(GtkPltPlot *plot) {
   GtkPltPlotData *data = plot->data;
   if (data->xaxis->title != NULL) {
      free(data->xaxis->title);
   }
   data->xaxis->title = NULL;
}

void gtkplt_set_xaxis_title_font(GtkPltPlot *plot, const char *font) {
   GtkPltPlotData *data = plot->data;
   free(data->xaxis->titlefont);
   data->xaxis->titlefont = strdup(font);
}

void gtkplt_set_xaxis_title_fontsize(GtkPltPlot *plot, int fontsize) {
   GtkPltPlotData *data = plot->data;
   data->xaxis->titlefontsize = fontsize;
}

void gtkplt_set_yaxis_title(GtkPltPlot *plot, const char *title) {
   GtkPltPlotData *data = plot->data;
   gtkplt_remove_yaxis_title(plot);
   data->yaxis->title = strdup(title);
}

void gtkplt_remove_yaxis_title(GtkPltPlot *plot) {
   GtkPltPlotData *data = plot->data;
   if (data->yaxis->title != NULL) {
      free(data->yaxis->title);
   }
   data->yaxis->title = NULL;
}

void gtkplt_set_yaxis_title_font(GtkPltPlot *plot, const char *font) {
   GtkPltPlotData *data = plot->data;
   free(data->yaxis->titlefont);
   data->yaxis->titlefont = strdup(font);
}

void gtkplt_set_yaxis_title_fontsize(GtkPltPlot *plot, int fontsize) {
   GtkPltPlotData *data = plot->data;
   data->yaxis->titlefontsize = fontsize;
}

void gtkplt_plot_draw_yaxis_minorticks(cairo_t *cr, GtkPltPlotData *data,
                                       double yminpos, double ymaxpos,
                                       double xmaxpos) {
   double xminpos = xmaxpos - 0.5*data->yaxis->tickwidth;

   int nticks = data->yaxis->nminorticks < 0 ? 0 : data->yaxis->nminorticks;

   double tickspacing;
   tickspacing = ymaxpos - yminpos;
   tickspacing /= nticks + 1;

   cairo_set_line_width(cr, data->yaxis->tickwidth/6.0);
   for (int itick=1; itick<=nticks; itick++) {
      double y = yminpos + itick*tickspacing;
      cairo_move_to(cr, xminpos, y);
      cairo_line_to(cr, xmaxpos, y);
   }
}

void gtkplt_plot_draw_yaxis_majorticks(cairo_t *cr, GtkPltPlotData *data) {
   // minimum is two ticks
   int nticks = data->yaxis->nmajorticks < 2 ? 2 : data->yaxis->nmajorticks;

   double yminpos = gtkplt_yaxis_area_ymin(data);
   double ymaxpos = gtkplt_yaxis_area_ymax(data);
   double xmaxpos = gtkplt_yaxis_area_xmax(data);
   double xminpos = xmaxpos - data->yaxis->tickwidth;

   double tickspacing ;
   tickspacing = ymaxpos - yminpos;
   tickspacing /= nticks - 1;

   cairo_set_line_width(cr, data->yaxis->tickwidth/3.0);
   cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
   for (int itick=0; itick<nticks; itick++) {
      double y = yminpos + itick*tickspacing;
      cairo_move_to(cr, xmaxpos, y);
      cairo_line_to(cr, xminpos, y);
   }
   for (int itick=0; itick<nticks-1; itick++) {
      double y = yminpos + itick*tickspacing;
      // minor ticks
      gtkplt_plot_draw_yaxis_minorticks(cr, data, y, y+tickspacing, xmaxpos);
   }
}

void gtkplt_plot_draw_xaxis_minorticks(cairo_t *cr, GtkPltPlotData *data,
                                       double xminpos, double xmaxpos,
                                       double yminpos) {
   double ymaxpos = yminpos + 0.5*data->xaxis->tickwidth;

   int nticks = data->xaxis->nminorticks < 0 ? 0 : data->xaxis->nminorticks;

   double tickspacing;
   tickspacing = xmaxpos - xminpos;
   tickspacing /= nticks + 1;

   cairo_set_line_width(cr, data->yaxis->tickwidth/6.0);
   for (int itick=1; itick<=nticks; itick++) {
      double x = xminpos + itick*tickspacing;
      cairo_move_to(cr, x, yminpos);
      cairo_line_to(cr, x, ymaxpos);
   }
}

void gtkplt_plot_draw_xaxis_majorticks(cairo_t *cr, GtkPltPlotData *data) {
   // minimum is two ticks
   int nticks = data->xaxis->nmajorticks < 2 ? 2 : data->xaxis->nmajorticks;

   double xminpos = gtkplt_xaxis_area_xmin(data);
   double xmaxpos = gtkplt_xaxis_area_xmax(data);
   double yminpos = gtkplt_xaxis_area_ymin(data);
   double ymaxpos = yminpos + data->xaxis->tickwidth;

   double tickspacing ;
   tickspacing = xmaxpos - xminpos;
   tickspacing /= nticks - 1;

   cairo_set_line_width(cr, data->xaxis->tickwidth/3.0);
   cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
   for (int itick=0; itick<nticks; itick++) {
      double x = xminpos + itick*tickspacing;
      cairo_move_to(cr, x, yminpos);
      cairo_line_to(cr, x, ymaxpos);
   }
   for (int itick=0; itick<nticks-1; itick++) {
      double x = xminpos + itick*tickspacing;
      // minor ticks
      gtkplt_plot_draw_xaxis_minorticks(cr, data, x, x+tickspacing, yminpos);
   }
}

void gtkplt_plot_configure_axis_placement(cairo_t *cr, GtkPltPlotData *data) {

}

void gtkplt_plot_draw_axis(cairo_t *cr, GtkPltPlotData *data) {
   // first figure out where the axis should go.
   // The placement of the x- and y-axis are codependent on each other.
   gtkplt_plot_configure_axis_placement(cr, data);

   // draw axis frame
   cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
   cairo_set_line_width(cr, data->xaxis->linewidth);
   // top line
   cairo_move_to(cr, gtkplt_xaxis_area_xmin(data), gtkplt_yaxis_area_ymin(data));
   cairo_line_to(cr, gtkplt_xaxis_area_xmax(data), gtkplt_yaxis_area_ymin(data));
   cairo_line_to(cr, gtkplt_xaxis_area_xmax(data), gtkplt_yaxis_area_ymax(data));
   cairo_line_to(cr, gtkplt_xaxis_area_xmin(data), gtkplt_yaxis_area_ymax(data));
   cairo_close_path(cr);



   // dtaw ticks
   gtkplt_plot_draw_xaxis_majorticks(cr, data);
   gtkplt_plot_draw_yaxis_majorticks(cr, data);

   cairo_stroke(cr);
}
