#include <stdlib.h>

#include "gtkplt.h"

GtkPltPlotAxis *gtkplt_axis_init() {
   GtkPltPlotAxis *axis = (GtkPltPlotAxis*) malloc(2*sizeof(GtkPltPlotAxis));
   for (int iaxis=0; iaxis<2; iaxis++) {
      axis[iaxis].scale = linear;
      axis[iaxis].nmajortics = 10;
      axis[iaxis].nminortics = 4;
      axis[iaxis].range[0] = 0.0;
      axis[iaxis].range[1] = 1.0;
      axis[iaxis].label = NULL;
      axis[iaxis].labelfont = NULL;
      axis[iaxis].labelfontsize = 12;
   }
   axis[0].labelorientation = horizontal;
   axis[1].labelorientation = vertical_up;

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
