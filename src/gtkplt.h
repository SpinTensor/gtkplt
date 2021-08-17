#ifndef __GTKPLT_H__
#define __GTKPLT_H__

#include <stdbool.h>

#include <gtk/gtk.h>

// Handle C++ includes
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Type structure to hold data for the plots
enum en_labelorientation {
   horizontal,
   vertical_up,
   vertical_down,
   diagonal_up,
   diagonal_down
};

typedef struct {
   double xpos, ypos;
   int fontsize;
   char *font;
   char *text;
   enum en_labelorientation orientation;
} GtkPltPlotLabel;

typedef struct {
   double xpos, ypos;
} GtkPltPlotLegend;

enum en_lineshape {
   solid,
   dotted,
   densly_dotted,
   loosely_dotted,
   dashed,
   densly_dashed,
   loosely_dashed,
   dashdotted,
   densly_dashdotted,
   loosely_dashdotted,
   filled
};

enum en_plottype {
   points,
   line,
   linepoints,
   bar
};

typedef struct {
   int nvals;
   double *xvals;
   double *yvals;
   bool has_xerrvals;
   double *xerrvals;
   bool has_yerrvals;
   double *yerrvals;
   double RGBcolor[3];
   enum en_lineshape lineshape;
   unsigned char linewidth;
   enum en_plottype plottype;
   char *title;
   char *titlefont;
   int titlefontsize;
   bool show_in_legend;
} GtkPltPlotDataSet;

typedef struct {
   unsigned int ndatasets;
   GtkPltPlotDataSet *datasets;
   GtkPltPlotLegend *legend;
   unsigned int nlabels;
   GtkPltPlotLabel *labels;
} GtkPltPlotPlotArea;

enum en_axisscale {
   linear,
   log
};

typedef struct {
   enum en_axisscale scale;
   unsigned int nmajortics;
   unsigned int nminortics;
   double range[2];
   char *label;
   char *labelfont;
   int labelfontsize;
   enum en_labelorientation labelorientation;
} GtkPltPlotAxis;

typedef struct {
   GtkPltPlotPlotArea *PlotArea;
   GtkPltPlotAxis *Axis;
} GtkPltPlotData;

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

typedef struct {
   GtkDrawingArea parent;

   GtkDrawingArea *drawingarea;
   GtkPltPlotData *data;
} GtkPltPlot;

typedef struct {
   GtkDrawingAreaClass parent_class;
} GtkPltPlotClass;

// Public API
GType gtkplt_plot_get_type(void) G_GNUC_CONST;
GtkWidget *gtkplt_plot_new(void);

G_END_DECLS

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __GTKPLT_H__
