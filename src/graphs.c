#include <stdlib.h>
#include <stdbool.h>

#include "axis.h"
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

   cairo_set_source_rgb(cr,
                        graph->RGBcolor[0],
                        graph->RGBcolor[1],
                        graph->RGBcolor[2]);
   // define plot area origin
   // flip the y axis due to the
   // draw origin beeing in the top left corner
   double plotxmin = gtkplt_xaxis_area_xmin(data);
   double plotxmax = gtkplt_xaxis_area_xmax(data);
   double plotymin = gtkplt_yaxis_area_ymax(data);
   double plotymax = gtkplt_yaxis_area_ymin(data);
   // define the actual origin
   double rxmin = data->xaxis->range[0];
   double rxmax = data->xaxis->range[1];
   double rymin = data->yaxis->range[0];
   double rymax = data->yaxis->range[1];

#ifdef _DEBUG
printf("x e [%f,%f]\n", rxmin, rxmax);
printf("y e [%f,%f]\n", rymin, rymax);
#endif
   for (int i=0; i<graph->nvals; i++) {
#ifdef _DEBUG
printf("plotting %d: f(%f) = %f\n", i, graph->xvals[i], graph->yvals[i]);
#endif
      // determine whether the point needs to be drawn
      if (graph->xvals[i] >= rxmin && graph->xvals[i] <=rxmax &&
          graph->yvals[i] >= rymin && graph->yvals[i] <=rymax) {
         double plotx;
         plotx  = graph->xvals[i] - rxmin;
         plotx /= rxmax-rxmin;
         plotx *= plotxmax-plotxmin;
         plotx += plotxmin;
         double ploty;
         ploty  = graph->yvals[i] -rymin;
         ploty /= rymax-rymin;
         ploty *= plotymax-plotymin;
         ploty += plotymin;

         cairo_set_source_rgb(cr,
                              graph->RGBcolor[0],
                              graph->RGBcolor[1],
                              graph->RGBcolor[2]);
                              
         cairo_move_to(cr, plotx, ploty);
         cairo_arc(cr,
                   plotx, ploty, // center coordinates
                   1.0,          // radius
                   0.0,          // starting angle
                   2.0*G_PI      // ending angle
                   );
         cairo_stroke_preserve(cr);
         cairo_fill(cr);
      }
   }
}
