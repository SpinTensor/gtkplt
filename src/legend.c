#include <stdlib.h>

#include "gtkplt.h"

GtkPltPlotLegend *gtkplt_legend_init() {
   GtkPltPlotLegend *legend = (GtkPltPlotLegend*) malloc(sizeof(GtkPltPlotLegend));
   legend->xpos = 0;
   legend->ypos = 0;
   return legend;
}

void gtkplt_legend_finalize(GtkPltPlotLegend *legend_ptr) {
   free(legend_ptr);
}
