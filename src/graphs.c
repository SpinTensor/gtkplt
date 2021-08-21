#include <stdlib.h>
#include <stdbool.h>

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

// Public API

// add a graph to the plot widget;
unsigned int gtkplt_add_graph(GtkPltPlot *plot, int nvals,
                              double *xvals, double *yvals) {
   GtkPltPlotData *data = plot->data;
   GtkPltPlotPlotArea *plotarea = data->PlotArea;

   // TODO search for first invalid graph in all existing graphs and take that one
   if (plotarea->ngraphs == 0) {
      plotarea->ngraphs++;
      plotarea->graphs = (GtkPltPlotGraph*) malloc(sizeof(GtkPltPlotGraph));
   } else {
      plotarea->ngraphs++;
      plotarea->graphs = (GtkPltPlotGraph*)
                         realloc(plotarea->graphs,
                                 plotarea->ngraphs*sizeof(GtkPltPlotGraph));
   }

   GtkPltPlotGraph *graph = plotarea->graphs + plotarea->ngraphs-1;
   graph->ID = plotarea->ngraphs-1;
   graph->valid = true;
   graph->nvals = nvals;
   graph->xvals = (double*) malloc(nvals*sizeof(double));
   for (int i=0; i<nvals; i++) {
      graph->xvals[i] = xvals[i];
   }
   graph->yvals = (double*) malloc(nvals*sizeof(double));
   for (int i=0; i<nvals; i++) {
      graph->yvals[i] = yvals[i];
   }
   graph->has_xerrvals = false;
   graph->xerrvals = NULL;
   graph->has_yerrvals = false;
   graph->yerrvals = NULL;
   graph->RGBcolor[0] = 1.0;
   graph->RGBcolor[1] = 0.0;
   graph->RGBcolor[2] = 0.0;
   graph->lineshape = gtkplt_solid;
   graph->linewidth = 2;
   graph->plottype = gtkplt_points;
   graph->title = NULL;
   graph->titlefont = NULL;
   graph->titlefontsize = 0.0;
   graph->show_in_legend = false;

   return graph->ID;
}

void gtkplt_plot_graph(cairo_t *cr, GtkPltPlotData *data,
                       GtkPltPlotGraph *graph) {


   for (int i=0; i<graph->nvals; i++) {
      double rx = data->widget_width/10.0*graph->xvals[i];
      double ry = data->widget_height/10.0*graph->yvals[i];
      cairo_set_source_rgb(cr,
                           graph->RGBcolor[0],
                           graph->RGBcolor[1],
                           graph->RGBcolor[2]);
                           
      cairo_arc(cr,
                rx, ry, // center coordinates
                1, // radius
                0, 2*G_PI);
      cairo_stroke_preserve(cr);
      cairo_fill(cr);

   }
}
