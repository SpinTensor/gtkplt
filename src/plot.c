#include <stdlib.h>

#include <gtk/gtk.h>

#include "gtkplt.h"
#include "axis.h"
#include "plotarea.h"

GtkPltPlotData *gtkplt_init_plot() {
   GtkPltPlotData *plotdata_ptr = (GtkPltPlotData*) malloc(sizeof(GtkPltPlotData));
   plotdata_ptr->Axis = gtkplt_axis_init();
   plotdata_ptr->PlotArea = gtkplt_plotarea_init();

   return plotdata_ptr;
}

void gtkplt_finalize_plot(GtkPltPlotData *plotdata_ptr) {
   gtkplt_axis_finalize(plotdata_ptr->Axis);
   plotdata_ptr->Axis = NULL;
   gtkplt_plotarea_finalize(plotdata_ptr->PlotArea);
   plotdata_ptr->PlotArea = NULL;
   free(plotdata_ptr);
}

void gtkplt_plot(GtkWidget *widget, cairo_t *cr, GtkPltPlotData *plotdata_ptr) {
}
