#include "gtkplt.h"

GtkPltPlotLabel *gtkplt_labels_init() {
   return NULL;
}

void gtkplt_labels_finalize(GtkPltPlotLabel *labels_ptr) {
   if (labels_ptr->text != NULL) {
      free(labels_ptr->text);
      labels_ptr->text = NULL;
   }
   if (labels_ptr->font != NULL) {
      free(labels_ptr->font);
      labels_ptr->font = NULL;
   }
}
