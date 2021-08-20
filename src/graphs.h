#ifndef GRAPHS_H
#define GRAPHS_H

#include "gtkplt.h"

   GtkPltPlotGraph *gtkplt_graphs_init();

   void gtkplt_graphs_finalize(GtkPltPlotGraph *graphs_ptr);

   void gtkplt_plot_graph(cairo_t *cr, GtkPltPlotData *data,
                          GtkPltPlotGraph *graph,
                          guint width, guint height);

#endif
