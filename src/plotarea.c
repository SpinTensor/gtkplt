#include <stdlib.h>

#include "gtkplt.h"
#include "legend.h"
#include "graphs.h"
#include "labels.h"

GtkPltPlotPlotArea *gtkplt_plotarea_init() {
   GtkPltPlotPlotArea *plotarea = (GtkPltPlotPlotArea*) malloc(sizeof(GtkPltPlotPlotArea));
   plotarea->ngraphs = 0;
   plotarea->graphs = NULL;
   plotarea->legend = gtkplt_legend_init();
   plotarea->nlabels = 0;
   plotarea->labels = NULL;
   return plotarea;
}

void gtkplt_plotarea_finalize(GtkPltPlotPlotArea *plotarea_ptr) {
   gtkplt_legend_finalize(plotarea_ptr->legend);
   plotarea_ptr->legend = NULL;

   for (unsigned int i=0; i<plotarea_ptr->ngraphs; i++) {
      gtkplt_graphs_finalize(plotarea_ptr->graphs+i);
   }
   if (plotarea_ptr->graphs != 0) {
      free(plotarea_ptr->graphs);
      plotarea_ptr->graphs = NULL;
   }
   plotarea_ptr->ngraphs = 0;

   for (unsigned int i=0; i<plotarea_ptr->nlabels; i++) {
      gtkplt_labels_finalize(plotarea_ptr->labels+i);
   }
   if (plotarea_ptr->labels != 0) {
      free(plotarea_ptr->labels);
      plotarea_ptr->labels = NULL;
   }
   plotarea_ptr->nlabels = 0;
   free(plotarea_ptr);
}
