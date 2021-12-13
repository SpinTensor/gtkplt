#ifndef __GTKPLT_H__
#define __GTKPLT_H__

#include <stdbool.h>

#include <gtk/gtk.h>

// Handle C++ includes
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct {
   double xpos, ypos;
   int fontsize;
   char *font;
   char *text;
   double angle;
} GtkPltPlotLabel;

typedef struct {
   double xpos, ypos;
} GtkPltPlotLegend;

enum gtkplt_en_lineshape {
   gtkplt_solid,
   gtkplt_dotted,
   gtkplt_densly_dotted,
   gtkplt_loosely_dotted,
   gtkplt_dashed,
   gtkplt_densly_dashed,
   gtkplt_loosely_dashed,
   gtkplt_dashdotted,
   gtkplt_densly_dashdotted,
   gtkplt_loosely_dashdotted,
   gtkplt_filled
};

enum gtkplt_en_plottype {
   gtkplt_points,
   gtkplt_line,
   gtkplt_linepoints,
   gtkplt_bar
};

typedef struct {
   unsigned int ID;
   bool valid;
   int nvals;
   double *xvals;
   double *yvals;
   bool has_xerrvals;
   double *xerrvals;
   bool has_yerrvals;
   double *yerrvals;
   double RGBcolor[3];
   enum gtkplt_en_lineshape lineshape;
   unsigned char linewidth;
   enum gtkplt_en_plottype plottype;
   char *title;
   char *titlefont;
   int titlefontsize;
   bool show_in_legend;
} GtkPltPlotGraph;

typedef struct {
   unsigned int ngraphs;
   GtkPltPlotGraph *graphs;
   GtkPltPlotLegend *legend;
   unsigned int nlabels;
   GtkPltPlotLabel *labels;
} GtkPltPlotPlotArea;

enum gtkplt_en_axisscale {
   gtkplt_linear,
   gtkplt_log
};

typedef struct {
   enum gtkplt_en_axisscale scale;
   int linewidth;
   int nmajorticks;
   int nminorticks;
   double range[2];
   bool autorange[2];
   double autorangevals[2];
   // title
   char *title;
   char *titlefont;
   int titlefontsize;
   double titleangle;
   // label
   char *labelfont;
   char *labelformat;
   int labelfontsize;
   double labelangle;
   // distances and measures
   double titlewidth;
   double titlelabeldist;
   double labelwidth;
   double labeltickdist;
   double tickwidth;
} GtkPltPlotAxis;

typedef struct {
   double left_margin;
   double right_margin;
   double top_margin;
   double bottom_margin;
   char *title;
   char *titlefont;
   int titlefontsize;
   double title_height;
   double title_tmargin;
   double title_bmargin;
   double widget_width;
   double widget_height;
   GtkPltPlotPlotArea *PlotArea;
   GtkPltPlotAxis *xaxis;
   GtkPltPlotAxis *yaxis;
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

unsigned int gtkplt_add_graph(GtkPltPlot *plot, int nvals, double *xvals, double *yvals);

// Title appearance
void gtkplt_set_title(GtkPltPlot *plot, const char *title);
void gtkplt_remove_title(GtkPltPlot *plot);
void gtkplt_set_title_font(GtkPltPlot *plot, const char *font);
void gtkplt_set_title_fontsize(GtkPltPlot *plot, int fontsize);

// Axis title appearance
void gtkplt_set_xaxis_title(GtkPltPlot *plot, const char *title);
void gtkplt_remove_xaxis_title(GtkPltPlot *plot);
void gtkplt_set_xaxis_title_font(GtkPltPlot *plot, const char *title);
void gtkplt_set_xaxis_title_fontsize(GtkPltPlot *plot, int fontsize);
void gtkplt_set_yaxis_title(GtkPltPlot *plot, const char *title);
void gtkplt_remove_yaxis_title(GtkPltPlot *plot);
void gtkplt_set_yaxis_title_font(GtkPltPlot *plot, const char *title);
void gtkplt_set_yaxis_title_fontsize(GtkPltPlot *plot, int fontsize);

// Axis scaling
// passing null counts as activating
void gtkplt_set_xaxis_range(GtkPltPlot *plot, double *xmin_ptr, double *xmax_ptr);
void gtkplt_set_yaxis_range(GtkPltPlot *plot, double *ymin_ptr, double *ymax_ptr);
void gtkplt_set_xaxis_autorange(GtkPltPlot *plot);
void gtkplt_set_yaxis_autorange(GtkPltPlot *plot);

G_END_DECLS

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __GTKPLT_H__
