#include <stdlib.h>

#include "gtkplt.h"
#include "margins.h"
#include "title.h"
#include "axis.h"

GtkPltPlotAxis *gtkplt_axis_init() {
   GtkPltPlotAxis *axis = (GtkPltPlotAxis*) malloc(2*sizeof(GtkPltPlotAxis));
   for (int iaxis=0; iaxis<2; iaxis++) {
      axis[iaxis].scale = gtkplt_linear;
      axis[iaxis].nmajortics = 10;
      axis[iaxis].nminortics = 4;
      axis[iaxis].range[0] = 0.0;
      axis[iaxis].range[1] = 10.0;
      axis[iaxis].label = NULL;
      axis[iaxis].labelfont = NULL;
      axis[iaxis].labelfontsize = 12;
      axis[iaxis].axis_width = 40;
      axis[iaxis].axis_label_dist = 10;
   }
   axis[0].labelorientation = gtkplt_horizontal;
   axis[1].labelorientation = gtkplt_vertical_up;

   return axis;
}

void gtkplt_axis_finalize(GtkPltPlotAxis *axis_ptr) {
   for (int iaxis=0; iaxis<2; iaxis++) {
      if (axis_ptr[iaxis].label != NULL) {
         free(axis_ptr[iaxis].label);
         axis_ptr[iaxis].label = NULL;
      }
      if (axis_ptr[iaxis].labelfont != NULL) {
         free(axis_ptr[iaxis].labelfont);
         axis_ptr[iaxis].labelfont = NULL;
      }
   }
   free(axis_ptr);
}

double gtkplt_xaxis_area_xmin(GtkPltPlotData *data) {
   return gtkplt_yaxis_area_xmax(data);
}
double gtkplt_xaxis_area_xmax(GtkPltPlotData *data) {
   return gtkplt_ormargin_xmin(data);
}
double gtkplt_xaxis_area_ymin(GtkPltPlotData *data) {
   return gtkplt_xaxis_area_ymax(data)-data->Axis[0].axis_width;
}
double gtkplt_xaxis_area_ymax(GtkPltPlotData *data) {
   return gtkplt_obmargin_ymin(data);
}

double gtkplt_yaxis_area_xmin(GtkPltPlotData *data) {
   return gtkplt_olmargin_xmax(data);
}
double gtkplt_yaxis_area_xmax(GtkPltPlotData *data) {
   return gtkplt_yaxis_area_xmin(data) + data->Axis[1].axis_width;
}
double gtkplt_yaxis_area_ymin(GtkPltPlotData *data) {
   return gtkplt_tbmargin_ymax(data);
}
double gtkplt_yaxis_area_ymax(GtkPltPlotData *data) {
   return gtkplt_xaxis_area_ymin(data);
}
