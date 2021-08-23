#ifndef TITLE_H
#define TITLE_H

#include "gtkplt.h"

double gtkplt_ttmargin_xmin(GtkPltPlotData *data);
double gtkplt_ttmargin_ymin(GtkPltPlotData *data);
double gtkplt_ttmargin_xmax(GtkPltPlotData *data);
double gtkplt_ttmargin_ymax(GtkPltPlotData *data);

double gtkplt_tbmargin_xmin(GtkPltPlotData *data);
double gtkplt_tbmargin_ymin(GtkPltPlotData *data);
double gtkplt_tbmargin_xmax(GtkPltPlotData *data);
double gtkplt_tbmargin_ymax(GtkPltPlotData *data);

void gtkplt_plot_draw_title(cairo_t *cr, GtkPltPlotData *data);
void gtkplt_plot_set_title_margins(cairo_t *cr, GtkPltPlotData *data);

#endif
