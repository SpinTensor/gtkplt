#include <stdlib.h>

#include <gtk/gtk.h>

#include "gtkplt.h"
#include "axis.h"
#include "plotarea.h"
#include "graphs.h"


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

void gtkplt_plot(cairo_t *cr, GtkPltPlotData *data,
                 guint width, guint height) {

   // set background to white
   cairo_set_source_rgba(cr,
                         1.0,
                         1.0,
                         1.0,
                         1.0);
   cairo_paint(cr);

   // draw title

   // draw axis

   // draw graphs
   // TODO: correct upper bound
   for (int i=0; i<1; i++) {
      if (data->PlotArea->graphs[i].valid) {
         gtkplt_plot_graph(cr,
                           data,
                           data->PlotArea->graphs+i,
                           width,
                           height);
      }
   }

   // draw legend
   
   // draw labels

}
