#include <stdlib.h>

#include <gtk/gtk.h>

#include "gtkplt.h"
//#include "axis.h"
//#include "plotarea.h"

GtkPltPlotData *gtkplt_init_plot() {
   GtkPltPlotData *plotdata_ptr= (GtkPltPlotData*) malloc(sizeof(GtkPltPlotData));
   return plotdata_ptr;
}

void gtkplt_finalize_plot(GtkPltPlotData *plotdata_ptr) {
   free(plotdata_ptr);
}

void gtkplt_plot(GtkWidget *widget, cairo_t *cr, GtkPltPlotData *plotdata_ptr) {
}
