#ifndef __GTKPLT_H__
#define __GTKPLT_H__

#include <gtk/gtk.h>

// Handle C++ includes
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

G_BEGIN_DECLS

/* Standart GObject macros */
#define GTKPLT_PLOT_TYPE \
   (gtkplt_plot_get_type())
#define GTKPLT_PLOT(obj) \
   (G_TYPE_CHECK_INSTANCE_CAST((obj), \
                               GTKPLT_PLOT_TYPE, GtkPltPlot))
#define GTKPLT_PLOT_CLASS(klass) \
   (G_TYPE_CHECK_CLASS_CAST((klass), \
                            GTKPLT_PLOT_TYPE, GtkPltPlotClass))
#define MY_IS_CPU(obj) \
   (G_TYPE_CHECK_INSTANCE_TYPE((obj), \
                               GTKPLT_PLOT_TYPE))
#define MY_IS_CPU_CLASS(klass) \
   (G_TYPE_CHECK_CLASS_TYPE((klass), \
                            GTKPLT_PLOT_TYPE))
#define GTKPLT_PLOT_GET_CLASS(obj) \
   (G_TYPE_INSTANCE_GET_CLASS((obj), \
                              GTKPLT_PLOT_TYPE, \
                              GtkPltPlotClass))

typedef struct _GtkPltPlotData    GtkPltPlotData;
typedef struct _GtkPltPlot        GtkPltPlot;
typedef struct _GtkPltPlotClass   GtkPltPlotClass;
typedef struct _GtkPltPlotPrivate GtkPltPlotPrivate;

struct _GtkPltPlotData {
   int a;
};

struct _GtkPltPlot {
   GtkDrawingArea parent;

   GtkDrawingArea *drawingarea;
   GtkPltPlotData *data;
};

struct _GtkPltPlotClass {
   GtkDrawingAreaClass parent_class;
};

// Public API
GType gtkplt_plot_get_type(void) G_GNUC_CONST;
GtkWidget *gtkplt_plot_new(void);

G_END_DECLS

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __GTKPLT_H__
