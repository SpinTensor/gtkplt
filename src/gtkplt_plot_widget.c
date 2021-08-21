#include <gtk/gtk.h>

#include "gtkplt.h"
#include "plot.h"

gboolean gtkplt_plot_draw_callback(GtkWidget *widget, cairo_t *cr, gpointer widgetdata);

// Define Type
G_DEFINE_TYPE(GtkPltPlot, gtkplt_plot, GTK_TYPE_DRAWING_AREA)

static void gtkplt_plot_finalize(GObject *self);
static gboolean gtkplt_plot_on_draw(GtkWidget *self, cairo_t *cr, gpointer data);

// Initialization
static void gtkplt_plot_class_init(GtkPltPlotClass *klass) {
   GObjectClass *object_klass = G_OBJECT_CLASS(klass);
   object_klass->finalize     = gtkplt_plot_finalize;
}

static void gtkplt_plot_init(GtkPltPlot *plot) {
   plot->drawingarea = GTK_DRAWING_AREA(gtk_drawing_area_new());
   gtk_widget_show(GTK_WIDGET(plot->drawingarea));

   plot->data = gtkplt_init_plot();
   g_signal_connect(G_OBJECT(plot),
                    "draw",
                    G_CALLBACK(gtkplt_plot_on_draw),
                    (gpointer) plot->data);
}

static void gtkplt_plot_finalize(GObject *self) {
   GtkPltPlot *plot_ptr = (GtkPltPlot*) self;
   gtkplt_finalize_plot(plot_ptr->data);
   plot_ptr->data = NULL;
   G_OBJECT_CLASS(gtkplt_plot_parent_class)->finalize(self);
}

GtkWidget *gtkplt_plot_new() {
   return g_object_new(GTKPLT_PLOT_TYPE, NULL);
}

gboolean gtkplt_plot_on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
   GtkPltPlotData* plotdata = (GtkPltPlotData*) data;
   plotdata->widget_width = gtk_widget_get_allocated_width(widget);
   plotdata->widget_height = gtk_widget_get_allocated_height(widget);

   gtkplt_plot(cr, (GtkPltPlotData*) data);

   return FALSE;
}
