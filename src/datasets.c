#include "gtkplt.h"

GtkPltPlotDataSet *gtkplt_datasets_init() {
   return NULL;
}

void gtkplt_datasets_finalize(GtkPltPlotDataSet *datasets_ptr) {
   if (datasets_ptr->xvals != NULL) {
      free(datasets_ptr->xvals);
      datasets_ptr->xvals = NULL;
   }
   if (datasets_ptr->yvals != NULL) {
      free(datasets_ptr->yvals);
      datasets_ptr->yvals = NULL;
   }
   if (datasets_ptr->has_xerrvals && datasets_ptr->xerrvals != NULL) {
      free(datasets_ptr->xerrvals);
      datasets_ptr->xerrvals = NULL;
   }
   if (datasets_ptr->has_yerrvals && datasets_ptr->yerrvals != NULL) {
      free(datasets_ptr->yerrvals);
      datasets_ptr->yerrvals = NULL;
   }
   if (datasets_ptr->title != NULL) {
      free(datasets_ptr->title);
      datasets_ptr->title = NULL;
   }
   if (datasets_ptr->titlefont != NULL) {
      free(datasets_ptr->titlefont);
      datasets_ptr->titlefont = NULL;
   }
}
