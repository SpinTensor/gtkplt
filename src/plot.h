#ifndef PLOT_H
#define PLOT_H

#include <gtk/gtk.h>

#include "gtkplt.h"

   GtkPltPlotData *gtkplt_init_plot();

   void gtkplt_finalize_plot(GtkPltPlotData *plotdata_ptr);
   
   void gtkplt_plot(cairo_t *cr, GtkPltPlotData *data);

#endif
