#ifndef MARGINS_H
#define MARGINS_H

#include "gtkplt.h"

double gtkplt_otmargin_xmin(GtkPltPlotData *data);
double gtkplt_otmargin_xmax(GtkPltPlotData *data);
double gtkplt_otmargin_ymin(GtkPltPlotData *data);
double gtkplt_otmargin_ymax(GtkPltPlotData *data);

double gtkplt_obmargin_xmin(GtkPltPlotData *data);
double gtkplt_obmargin_xmax(GtkPltPlotData *data);
double gtkplt_obmargin_ymin(GtkPltPlotData *data);
double gtkplt_obmargin_ymax(GtkPltPlotData *data);

double gtkplt_olmargin_xmin(GtkPltPlotData *data);
double gtkplt_olmargin_xmax(GtkPltPlotData *data);
double gtkplt_olmargin_ymin(GtkPltPlotData *data);
double gtkplt_olmargin_ymax(GtkPltPlotData *data);

double gtkplt_ormargin_xmin(GtkPltPlotData *data);
double gtkplt_ormargin_xmax(GtkPltPlotData *data);
double gtkplt_ormargin_ymin(GtkPltPlotData *data);
double gtkplt_ormargin_ymax(GtkPltPlotData *data);

// title text margin
double gtkplt_ttmargin_xmin(GtkPltPlotData *data);
double gtkplt_ttmargin_ymin(GtkPltPlotData *data);
double gtkplt_ttmargin_xmax(GtkPltPlotData *data);
double gtkplt_ttmargin_ymax(GtkPltPlotData *data);

// title box margin
double gtkplt_tbmargin_xmin(GtkPltPlotData *data);
double gtkplt_tbmargin_ymin(GtkPltPlotData *data);
double gtkplt_tbmargin_xmax(GtkPltPlotData *data);
double gtkplt_tbmargin_ymax(GtkPltPlotData *data);

#endif
