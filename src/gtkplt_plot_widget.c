#include <gtk/gtk.h>

#include "gtkplt.h"
#include "plot.h"

gboolean gtkplt_plot_draw_callback(GtkWidget *widget, cairo_t *cr, gpointer widgetdata);

// Define Type
G_DEFINE_TYPE(GtkPltPlot, gtkplt_plot, GTK_TYPE_DRAWING_AREA)

static void _gtkplt_plot_finalize(GObject *self);
static gboolean _gtkplt_plot_on_draw(GtkWidget *self, cairo_t *cr, gpointer data);

// Initialization
static void gtkplt_plot_class_init(GtkPltPlotClass *klass) {
   GObjectClass *object_klass = G_OBJECT_CLASS(klass);
   object_klass->finalize     = _gtkplt_plot_finalize;
}

static void gtkplt_plot_init(GtkPltPlot *plot) {
   plot->drawingarea = GTK_DRAWING_AREA(gtk_drawing_area_new());
   gtk_widget_show(GTK_WIDGET(plot->drawingarea));

   g_signal_connect(G_OBJECT(plot),
                    "draw",
                    G_CALLBACK(_gtkplt_plot_on_draw),
                    (gpointer) &(plot->data));
}

static void _gtkplt_plot_finalize(GObject *self) {
   G_OBJECT_CLASS(gtkplt_plot_parent_class)->finalize(self);
}

GtkWidget *gtkplt_plot_new() {
   return g_object_new(GTKPLT_PLOT_TYPE, NULL);
}

gboolean _gtkplt_plot_on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
   GtkPltPlotData *plotdata_ptr = (GtkPltPlotData*) data;

   gtkplt_plot(widget, cr, plotdata_ptr);

   return FALSE;
}
