#ifndef DATASETS_H
#define DATASETS_H

#include "gtkplt.h"

   GtkPltPlotDataSet *gtkplt_datasets_init();

   void gtkplt_datasets_finalize(GtkPltPlotDataSet *datasets_ptr);

#endif
