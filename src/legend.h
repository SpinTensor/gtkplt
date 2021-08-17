#ifndef LEGEND_H
#define LEGEND_H

#include "gtkplt.h"

   GtkPltPlotLegend *gtkplt_legend_init();

   void gtkplt_legend_finalize(GtkPltPlotLegend *legend_ptr);

#endif
