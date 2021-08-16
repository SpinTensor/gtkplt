#include <gtk/gtk.h>

#include "gtkplt.h"

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
   GtkPltPlotData plotdata = *((GtkPltPlotData*) data);

   guint width, height;
   GdkRGBA color;
   GtkStyleContext *context;

   context = gtk_widget_get_style_context (widget);
   width = gtk_widget_get_allocated_width (widget);
   height = gtk_widget_get_allocated_height (widget);
   gtk_render_background(context, cr, 0, 0, width, height);
   cairo_arc (cr, width/2.0, height/2.0, MIN (width, height) / 2.0, 0, 2 * G_PI);
   gtk_style_context_get_color (context, gtk_style_context_get_state (context), &color);
   gdk_cairo_set_source_rgba (cr, &color);
   gdk_cairo_set_source_rgba (cr, &color);
   cairo_fill (cr);
   return FALSE;
}
