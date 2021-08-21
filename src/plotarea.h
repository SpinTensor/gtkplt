#ifndef PLOTAREA_H
#define PLOTAREA_H

#include "gtkplt.h"

   GtkPltPlotPlotArea *gtkplt_plotarea_init();

   void gtkplt_plotarea_finalize(GtkPltPlotPlotArea *plotarea_ptr);

   double gtkplt_plotarea_xmin(GtkPltPlotData *data);
   double gtkplt_plotarea_xmax(GtkPltPlotData *data);
   double gtkplt_plotarea_ymin(GtkPltPlotData *data);
   double gtkplt_plotarea_ymax(GtkPltPlotData *data);

#endif
