#include <stdlib.h>

#include "gtkplt.h"
#include "margins.h"
#include "title.h"
#include "axis.h"

const double majorticks_width = 3.0;
const double minorticks_width = 1.0;

GtkPltPlotAxis *gtkplt_axis_init() {
   GtkPltPlotAxis *axis = (GtkPltPlotAxis*) malloc(2*sizeof(GtkPltPlotAxis));
   for (int iaxis=0; iaxis<2; iaxis++) {
      axis[iaxis].scale = gtkplt_linear;
      axis[iaxis].nmajortics = 10;
      axis[iaxis].nminortics = 4;
      axis[iaxis].range[0] = 0.0;
      axis[iaxis].range[1] = 10.0;
      axis[iaxis].label = NULL;
      axis[iaxis].labelfont = NULL;
      axis[iaxis].labelfontsize = 12;
      axis[iaxis].axis_width = 40;
      axis[iaxis].axis_label_dist = 10;
   }
   axis[0].labelorientation = gtkplt_horizontal;
   axis[1].labelorientation = gtkplt_vertical_up;

   return axis;
}

void gtkplt_axis_finalize(GtkPltPlotAxis *axis_ptr) {
   for (int iaxis=0; iaxis<2; iaxis++) {
      if (axis_ptr[iaxis].label != NULL) {
         free(axis_ptr[iaxis].label);
         axis_ptr[iaxis].label = NULL;
      }
      if (axis_ptr[iaxis].labelfont != NULL) {
         free(axis_ptr[iaxis].labelfont);
         axis_ptr[iaxis].labelfont = NULL;
      }
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
   return gtkplt_xaxis_area_ymax(data)-data->Axis[0].axis_width;
}
double gtkplt_xaxis_area_ymax(GtkPltPlotData *data) {
   return gtkplt_obmargin_ymin(data);
}

double gtkplt_yaxis_area_xmin(GtkPltPlotData *data) {
   return gtkplt_olmargin_xmax(data);
}
double gtkplt_yaxis_area_xmax(GtkPltPlotData *data) {
   return gtkplt_yaxis_area_xmin(data) + data->Axis[1].axis_width;
}
double gtkplt_yaxis_area_ymin(GtkPltPlotData *data) {
   return gtkplt_tbmargin_ymax(data);
}
double gtkplt_yaxis_area_ymax(GtkPltPlotData *data) {
   return gtkplt_xaxis_area_ymin(data);
}

void gtkplt_plot_draw_xaxis_majorticks(cairo_t *cr, GtkPltPlotData *data) {
   // minimum is two ticks
   int nticks = data->Axis[0].nmajortics < 2 ? 2 : data->Axis[0].nmajortics;

   double tickspacing ;
   tickspacing = gtkplt_xaxis_area_xmax(data) - gtkplt_xaxis_area_xmin(data);
   tickspacing /= nticks - 1;

   double xminpos = gtkplt_xaxis_area_xmin(data);
   double xmaxpos = gtkplt_xaxis_area_xmax(data);
   double yminpos = gtkplt_xaxis_area_ymin(data);
   double ymaxpos = yminpos + 3*majorticks_width;

   for (int itick=0; itick<= nticks; itick++) {
      double x = xminpos + itick*tickspacing;
      cairo_move_to(cr, x, yminpos);
      cairo_line_to(cr, x, ymaxpos);
   }

   cairo_stroke(cr);
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

   cairo_stroke(cr);

   // dtaw ticks
   gtkplt_plot_draw_xaxis_majorticks(cr, data);

}
