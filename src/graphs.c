#include "gtkplt.h"

GtkPltPlotGraph *gtkplt_graphs_init() {
   return NULL;
}

void gtkplt_graphs_finalize(GtkPltPlotGraph *graphs_ptr) {
   if (graphs_ptr->xvals != NULL) {
      free(graphs_ptr->xvals);
      graphs_ptr->xvals = NULL;
   }
   if (graphs_ptr->yvals != NULL) {
      free(graphs_ptr->yvals);
      graphs_ptr->yvals = NULL;
   }
   if (graphs_ptr->has_xerrvals && graphs_ptr->xerrvals != NULL) {
      free(graphs_ptr->xerrvals);
      graphs_ptr->xerrvals = NULL;
   }
   if (graphs_ptr->has_yerrvals && graphs_ptr->yerrvals != NULL) {
      free(graphs_ptr->yerrvals);
      graphs_ptr->yerrvals = NULL;
   }
   if (graphs_ptr->title != NULL) {
      free(graphs_ptr->title);
      graphs_ptr->title = NULL;
   }
   if (graphs_ptr->titlefont != NULL) {
      free(graphs_ptr->titlefont);
      graphs_ptr->titlefont = NULL;
   }
}
