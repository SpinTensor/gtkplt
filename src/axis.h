#ifndef AXIS_H
#define AXIS_H

#include "gtkplt.h"

GtkPltPlotAxis *gtkplt_axis_init();

void gtkplt_axis_finalize(GtkPltPlotAxis *axis);

double gtkplt_xaxis_area_xmin(GtkPltPlotData *data);
double gtkplt_xaxis_area_xmax(GtkPltPlotData *data);
double gtkplt_xaxis_area_ymin(GtkPltPlotData *data);
double gtkplt_xaxis_area_ymax(GtkPltPlotData *data);

double gtkplt_yaxis_area_xmin(GtkPltPlotData *data);
double gtkplt_yaxis_area_xmax(GtkPltPlotData *data);
double gtkplt_yaxis_area_ymin(GtkPltPlotData *data);
double gtkplt_yaxis_area_ymax(GtkPltPlotData *data);

void gtkplt_axis_autoranges(GtkPltPlotData *data, char axis_ident);

void gtkplt_plot_draw_axis(cairo_t *cr, GtkPltPlotData *data);
#endif
