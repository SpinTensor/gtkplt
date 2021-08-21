#include "gtkplt.h"
#include "margins.h"

double gtkplt_otmargin_xmin(GtkPltPlotData *data) {
   (void) data;
   return 0.0;
}  
double gtkplt_otmargin_xmax(GtkPltPlotData *data) {
   return gtkplt_otmargin_xmin(data) + data->widget_width;
} 
double gtkplt_otmargin_ymin(GtkPltPlotData *data) {
   (void) data;
   return 0.0;
}  
double gtkplt_otmargin_ymax(GtkPltPlotData *data) {
   return gtkplt_otmargin_ymin(data) + data->top_margin;
}

double gtkplt_obmargin_xmin(GtkPltPlotData *data) {
   (void) data;
   return 0.0;
}  
double gtkplt_obmargin_xmax(GtkPltPlotData *data) {
   return gtkplt_obmargin_xmin(data) + data->widget_width;
} 
double gtkplt_obmargin_ymin(GtkPltPlotData *data) {
   return data->widget_height-data->bottom_margin;
}  
double gtkplt_obmargin_ymax(GtkPltPlotData *data) {
   return gtkplt_obmargin_ymin(data) + data->bottom_margin;
}

double gtkplt_olmargin_xmin(GtkPltPlotData *data) {
   (void) data;
   return 0.0;
}
double gtkplt_olmargin_xmax(GtkPltPlotData *data) {
   return gtkplt_olmargin_xmin(data) + data->left_margin;
}
double gtkplt_olmargin_ymin(GtkPltPlotData *data) {
   (void) data;
   return 0.0;
}
double gtkplt_olmargin_ymax(GtkPltPlotData *data) {
   return gtkplt_olmargin_ymin(data) + data->widget_height;
}

double gtkplt_ormargin_xmin(GtkPltPlotData *data) {
   (void) data;
   return data->widget_width-data->right_margin;
}
double gtkplt_ormargin_xmax(GtkPltPlotData *data) {
   return gtkplt_ormargin_xmin(data) + data->right_margin;
}
double gtkplt_ormargin_ymin(GtkPltPlotData *data) {
   (void) data;
   return 0.0;
}
double gtkplt_ormargin_ymax(GtkPltPlotData *data) {
   return gtkplt_ormargin_ymin(data) + data->widget_height;
}
