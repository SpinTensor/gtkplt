#include "gtkplt.h"
#include "margins.h"

double gtkplt_ttmargin_xmin(GtkPltPlotData *data) {
   return gtkplt_olmargin_xmax(data);
}
double gtkplt_ttmargin_ymin(GtkPltPlotData *data) {
   return gtkplt_otmargin_ymax(data);
}
double gtkplt_ttmargin_xmax(GtkPltPlotData *data) {
   return gtkplt_ormargin_xmin(data);
}
double gtkplt_ttmargin_ymax(GtkPltPlotData *data) {
   return gtkplt_ttmargin_ymin(data) + data->title_margin;
}

double gtkplt_tbmargin_xmin(GtkPltPlotData *data) {
   return gtkplt_ttmargin_xmin(data);
}
double gtkplt_tbmargin_ymin(GtkPltPlotData *data) {
   return gtkplt_ttmargin_ymin(data)+data->title_height;
}
double gtkplt_tbmargin_xmax(GtkPltPlotData *data) {
   return gtkplt_ttmargin_xmax(data);
}
double gtkplt_tbmargin_ymax(GtkPltPlotData *data) {
   return gtkplt_tbmargin_ymin(data) + data->title_margin;
}
