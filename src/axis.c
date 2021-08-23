#include <stdlib.h>

#include "gtkplt.h"
#include "margins.h"
#include "title.h"
#include "axis.h"

const double majorticks_width = 3.0;
const double minorticks_width = 1.5;

GtkPltPlotAxis *gtkplt_axis_init() {
   GtkPltPlotAxis *axis = (GtkPltPlotAxis*) malloc(sizeof(GtkPltPlotAxis));
   axis->scale = gtkplt_linear;
   axis->nmajorticks = 10;
   axis->nminorticks = 4;
   axis->range[0] = 0.0;
   axis->range[1] = 10.0;
   axis->label = NULL;
   axis->labelfont = NULL;
   axis->labelfontsize = 12;
   axis->axis_width = 40;
   axis->axis_label_dist = 10;
   
   return axis;
}

void gtkplt_axis_finalize(GtkPltPlotAxis *axis_ptr) {
   if (axis_ptr->label != NULL) {
      free(axis_ptr->label);
      axis_ptr->label = NULL;
   }
   if (axis_ptr->labelfont != NULL) {
      free(axis_ptr->labelfont);
      axis_ptr->labelfont = NULL;
   }
   free(axis_ptr);
}

double gtkplt_xaxis_area_xmin(GtkPltPlotData *data) {
   return gtkplt_yaxis_area_xmax(data);
}
double gtkplt_xaxis_area_xmax(GtkPltPlotData *data) {
   return gtkplt_ormargin_xmin(data);
}
double gtkplt_xaxis_area_ymin(GtkPltPlotData *data) {
   return gtkplt_xaxis_area_ymax(data)-data->xaxis->axis_width;
}
double gtkplt_xaxis_area_ymax(GtkPltPlotData *data) {
   return gtkplt_obmargin_ymin(data);
}

double gtkplt_yaxis_area_xmin(GtkPltPlotData *data) {
   return gtkplt_olmargin_xmax(data);
}
double gtkplt_yaxis_area_xmax(GtkPltPlotData *data) {
   return gtkplt_yaxis_area_xmin(data) + data->yaxis->axis_width;
}
double gtkplt_yaxis_area_ymin(GtkPltPlotData *data) {
   return gtkplt_tbmargin_ymax(data);
}
double gtkplt_yaxis_area_ymax(GtkPltPlotData *data) {
   return gtkplt_xaxis_area_ymin(data);
}


void gtkplt_plot_draw_yaxis_minorticks(cairo_t *cr, GtkPltPlotData *data,
                                       double yminpos, double ymaxpos,
                                       double xmaxpos) {
   double xminpos = xmaxpos - 1.5*majorticks_width;

   int nticks = data->yaxis->nminorticks < 0 ? 0 : data->yaxis->nminorticks;

   double tickspacing;
   tickspacing = ymaxpos - yminpos;
   tickspacing /= nticks + 1;

   cairo_set_line_width(cr, minorticks_width);
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
   double xminpos = xmaxpos - 3*majorticks_width;

   double tickspacing ;
   tickspacing = ymaxpos - yminpos;
   tickspacing /= nticks - 1;

   cairo_set_line_width(cr, majorticks_width);
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
   double ymaxpos = yminpos + 1.5*majorticks_width;

   int nticks = data->xaxis->nminorticks < 0 ? 0 : data->xaxis->nminorticks;

   double tickspacing;
   tickspacing = xmaxpos - xminpos;
   tickspacing /= nticks + 1;

   cairo_set_line_width(cr, minorticks_width);
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
   double ymaxpos = yminpos + 3*majorticks_width;

   double tickspacing ;
   tickspacing = xmaxpos - xminpos;
   tickspacing /= nticks - 1;

   cairo_set_line_width(cr, majorticks_width);
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

void gtkplt_plot_draw_axis(cairo_t *cr, GtkPltPlotData *data) {

   // draw axis frame
   cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
   cairo_set_line_width(cr, majorticks_width);
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
