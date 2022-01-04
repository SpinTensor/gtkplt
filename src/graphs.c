#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "axis.h"
#include "gtkplt.h"
#include "geometry.h"

GtkPltPlotGraph *gtkplt_graphs_init() {
   return NULL;
}

void gtkplt_graphs_finalize(GtkPltPlotGraph *graphs_ptr) {
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

   // search for a free spot
   unsigned int newGraphID = -1;
   bool freeGraph = false;
   while (freeGraph == false && (newGraphID+1)<plotarea->ngraphs) {
      newGraphID++;
      freeGraph = (!plotarea->graphs[newGraphID].valid);
   }

   // if no free spot was found reallocate
   if (!freeGraph) {
      newGraphID = plotarea->ngraphs;
      plotarea->ngraphs++;
      plotarea->graphs = (GtkPltPlotGraph*)
                         realloc(plotarea->graphs,
                                 plotarea->ngraphs*sizeof(GtkPltPlotGraph));
   }

   GtkPltPlotGraph *graph = plotarea->graphs + newGraphID;
   graph->ID = newGraphID;
   graph->valid = true;
   graph->nvals = nvals;
   graph->xvals = xvals;
   graph->yvals = yvals;
   graph->has_xerrvals = false;
   graph->xerrvals = NULL;
   graph->has_yerrvals = false;
   graph->yerrvals = NULL;
   graph->RGBcolor[0] = 1.0;
   graph->RGBcolor[1] = 0.0;
   graph->RGBcolor[2] = 0.0;
   graph->lineshape = gtkplt_solid;
   graph->linewidth = 2;
   graph->pointsize = 2;
   graph->plottype = gtkplt_points;
   graph->title = NULL;
   graph->titlefont = NULL;
   graph->titlefontsize = 0.0;
   graph->show_in_legend = false;

   // precompute the autoscale values
   gtkplt_axis_autoranges(data, 'x');
   gtkplt_axis_autoranges(data, 'y');

   return graph->ID;
}

// remove a graph from the plot widget;
void gtkplt_remove_graph(GtkPltPlot *plot, unsigned int ID) {
   GtkPltPlotData *data = plot->data;
   GtkPltPlotPlotArea *plotarea = data->PlotArea;

   if (ID < plotarea->ngraphs) {
      GtkPltPlotGraph *graph = plotarea->graphs + ID;
      if (graph->valid) {
         graph->valid = false;
         graph->nvals = 0;
         graph->xvals = NULL;
         graph->yvals = NULL;
         graph->has_xerrvals = false;
         graph->xerrvals = NULL;
         graph->has_yerrvals = false;
         graph->yerrvals = NULL;
         free(graph->title);
         graph->title = NULL;
         free(graph->titlefont);
      }
   }
}

void gtkplt_set_graph_type(GtkPltPlot *plot, unsigned int ID, const char *typestr) {
   char *wtypestr = strdup(typestr);
   for (int i=0; wtypestr[i]; i++) {
      wtypestr[i] = tolower(wtypestr[i]);
   }

   GtkPltPlotData *data = plot->data;
   GtkPltPlotGraph *graph = data->PlotArea->graphs+ID;

   if (!strcmp(wtypestr, "point") || 
       !strcmp(wtypestr, "pt") ||
       !strcmp(wtypestr, "wp") ||
       !strcmp(wtypestr, "points")) {
      graph->plottype = gtkplt_points;
   } else if (!strcmp(wtypestr, "line") ||
              !strcmp(wtypestr, "ln") ||
              !strcmp(wtypestr, "wl")) {
      graph->plottype = gtkplt_line;
   } else if (!strcmp(wtypestr, "linepoint") ||
              !strcmp(wtypestr, "lpt") ||
              !strcmp(wtypestr, "wlp") ||
              !strcmp(wtypestr, "linepoints")) {
      graph->plottype = gtkplt_linepoints;
   } else if (!strcmp(wtypestr, "bar")) {
      graph->plottype = gtkplt_bar;
   }
   free(wtypestr);
}


void gtkplt_plot_graph_points(cairo_t *cr, GtkPltPlotData *data,
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

void gtkplt_plot_graph_line(cairo_t *cr, GtkPltPlotData *data,
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
   cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
   cairo_set_line_width (cr, graph->linewidth);

   // prepare first (old) point
   double plotx_old = plotxmin+(plotxmax-plotxmin)*(graph->xvals[0] - rxmin)/(rxmax-rxmin);
   double ploty_old = plotymin+(plotymax-plotymin)*(graph->yvals[0] - rymin)/(rymax-rymin);
   bool inplot_old = graph->xvals[0] > rxmin &&
                     graph->xvals[0] < rxmax &&
                     graph->yvals[0] > rymin &&
                     graph->yvals[0] < rymax;
   for (int i=1; i<graph->nvals; i++) {
      double plotx_new = plotxmin+(plotxmax-plotxmin)*(graph->xvals[i] - rxmin)/(rxmax-rxmin);
      double ploty_new = plotymin+(plotymax-plotymin)*(graph->yvals[i] - rymin)/(rymax-rymin);
      bool inplot_new = graph->xvals[i] > rxmin &&
                        graph->xvals[i] < rxmax &&
                        graph->yvals[i] > rymin &&
                        graph->yvals[i] < rymax;
#ifdef _DEBUG
printf("plotting %d: (%f,%f) -> (%f,%f) ; (%s,%s,%s,%s) -> (%s,%s,%s,%s)\n", i,
       graph->xvals[i-1], graph->yvals[i-1],
       graph->xvals[i], graph->yvals[i],
       graph->xvals[i-1] > rxmin ? "true" : "false",
       graph->xvals[i-1] < rxmax ? "true" : "false",
       graph->yvals[i-1] > rymin ? "true" : "false",
       graph->yvals[i-1] < rymax ? "true" : "false",
       graph->xvals[i] > rxmin ? "true" : "false",
       graph->xvals[i] < rxmax ? "true" : "false",
       graph->yvals[i] > rymin ? "true" : "false",
       graph->yvals[i] < rymax ? "true" : "false");
#endif
      // four cases to consider
      if (inplot_old) {
         if (inplot_new) {
            cairo_set_source_rgb(cr,
                                 graph->RGBcolor[0],
                                 graph->RGBcolor[1],
                                 graph->RGBcolor[2]);
            cairo_move_to(cr, plotx_old, ploty_old);
            cairo_line_to(cr, plotx_new, ploty_new);
            cairo_stroke_preserve(cr);
            cairo_fill(cr);
         } else {
            double xs, ys;
            bool intersect;
            // check left yaxis for intersection
            intersect = gtkplt_linesegment_intersection(graph->xvals[i-1], graph->yvals[i-1], graph->xvals[i], graph->yvals[i], rxmin, rymin, rxmin, rymax, &xs, &ys);
            if (!intersect) {
               // check right yaxis for intersection
               intersect = gtkplt_linesegment_intersection(graph->xvals[i-1], graph->yvals[i-1], graph->xvals[i], graph->yvals[i], rxmax, rymin, rxmax, rymax, &xs, &ys);
               if (!intersect) {
                  // check the lower xaxis for intersection
                  intersect = gtkplt_linesegment_intersection(graph->xvals[i-1], graph->yvals[i-1], graph->xvals[i], graph->yvals[i], rxmin, rymin, rxmax, rymin, &xs, &ys);
                  if (!intersect) {
                     // check the upper xaxis for intersection
                     intersect = gtkplt_linesegment_intersection(graph->xvals[i-1], graph->yvals[i-1], graph->xvals[i], graph->yvals[i], rxmin, rymax, rxmax, rymax, &xs, &ys);
                     if (!intersect) {
                        // never should get here
                        fprintf(stderr, "Undefined behaviour in %s:%d ! No axis intersection found!\n", __FILE__, __LINE__);
                     }
                  }
               }
            }
            double plotxs = plotxmin+(plotxmax-plotxmin)*(xs - rxmin)/(rxmax-rxmin);
            double plotys = plotymin+(plotymax-plotymin)*(ys - rymin)/(rymax-rymin);
            cairo_set_source_rgb(cr,
                                 graph->RGBcolor[0],
                                 graph->RGBcolor[1],
                                 graph->RGBcolor[2]);

            cairo_move_to(cr, plotxs, plotys);
            cairo_line_to(cr, plotx_old, ploty_old);
            cairo_stroke_preserve(cr);
            cairo_fill(cr);
         }
      } else {
         if (inplot_new) {
            double xs, ys;
            bool intersect;
            // check left yaxis for intersection
            intersect = gtkplt_linesegment_intersection(graph->xvals[i-1], graph->yvals[i-1], graph->xvals[i], graph->yvals[i], rxmin, rymin, rxmin, rymax, &xs, &ys);
            if (!intersect) {
               // check right yaxis for intersection
               intersect = gtkplt_linesegment_intersection(graph->xvals[i-1], graph->yvals[i-1], graph->xvals[i], graph->yvals[i], rxmax, rymin, rxmax, rymax, &xs, &ys);
               if (!intersect) {
                  // check the lower xaxis for intersection
                  intersect = gtkplt_linesegment_intersection(graph->xvals[i-1], graph->yvals[i-1], graph->xvals[i], graph->yvals[i], rxmin, rymin, rxmax, rymin, &xs, &ys);
                  if (!intersect) {
                     // check the upper xaxis for intersection
                     intersect = gtkplt_linesegment_intersection(graph->xvals[i-1], graph->yvals[i-1], graph->xvals[i], graph->yvals[i], rxmin, rymax, rxmax, rymax, &xs, &ys);
                     if (!intersect) {
                        // never should get here
                        fprintf(stderr, "Undefined behaviour in %s:%d ! No axis intersection found!\n", __FILE__, __LINE__);
                     }
                  }
               }
            }
            double plotxs = plotxmin+(plotxmax-plotxmin)*(xs - rxmin)/(rxmax-rxmin);
            double plotys = plotymin+(plotymax-plotymin)*(ys - rymin)/(rymax-rymin);
            cairo_set_source_rgb(cr,
                                 graph->RGBcolor[0],
                                 graph->RGBcolor[1],
                                 graph->RGBcolor[2]);

            cairo_move_to(cr, plotxs, plotys);
            cairo_line_to(cr, plotx_new, ploty_new);
            cairo_stroke_preserve(cr);
            cairo_fill(cr);
         } else {
            double xs[4] = {0, 0, 0, 0}, ys[4] = {0, 0, 0, 0};
            bool intersect;
            int iinter = 0;
            // check left yaxis for intersection
            intersect = gtkplt_linesegment_intersection(graph->xvals[i-1], graph->yvals[i-1], graph->xvals[i], graph->yvals[i], rxmin, rymin, rxmin, rymax, xs+iinter, ys+iinter);
            if (intersect) {iinter++;}
            // check right yaxis for intersection
            intersect = gtkplt_linesegment_intersection(graph->xvals[i-1], graph->yvals[i-1], graph->xvals[i], graph->yvals[i], rxmax, rymin, rxmax, rymax, xs+iinter, ys+iinter);
            if (intersect) {iinter++;}
            // check the lower xaxis for intersection
            intersect = gtkplt_linesegment_intersection(graph->xvals[i-1], graph->yvals[i-1], graph->xvals[i], graph->yvals[i], rxmin, rymin, rxmax, rymin, xs+iinter, ys+iinter);
            if (intersect) {iinter++;}
            // check the upper xaxis for intersection
            intersect = gtkplt_linesegment_intersection(graph->xvals[i-1], graph->yvals[i-1], graph->xvals[i], graph->yvals[i], rxmin, rymax, rxmax, rymax, xs+iinter, ys+iinter);
            if (intersect) {iinter++;}
            if (iinter > 0) {
               // in very rare edge cases there might be more than two axis crossings,
               // like when the line passes exactly through a corner.
               // select the two crossings which are the furthest apart.
               double distsq = -1.0;
               int iidx = 0;
               int jidx = 1;
               for (int i=0; i<iinter-1; i++) {
                  for (int j=i+1; j<iinter; j++) {
                     double dx = xs[i]-xs[j];
                     double dy = ys[i]-ys[j];
                     double tmpdstsq = dx*dx + dy*dy;
                     if (tmpdstsq > distsq) {
                        distsq = tmpdstsq;
                        iidx = i;
                        jidx = j;
                     }
                  }
               }

               double plotxs[2], plotys[2];
               plotxs[0] = plotxmin+(plotxmax-plotxmin)*(xs[iidx] - rxmin)/(rxmax-rxmin);
               plotys[0] = plotymin+(plotymax-plotymin)*(ys[iidx] - rymin)/(rymax-rymin);
               plotxs[1] = plotxmin+(plotxmax-plotxmin)*(xs[jidx] - rxmin)/(rxmax-rxmin);
               plotys[1] = plotymin+(plotymax-plotymin)*(ys[jidx] - rymin)/(rymax-rymin);
               cairo_set_source_rgb(cr,
                                    graph->RGBcolor[0],
                                    graph->RGBcolor[1],
                                    graph->RGBcolor[2]);
               cairo_move_to(cr, plotxs[0], plotys[0]);
               cairo_line_to(cr, plotxs[1], plotys[1]);
               cairo_stroke_preserve(cr);
               cairo_fill(cr);
            }
         }
      }
      plotx_old = plotx_new;
      ploty_old = ploty_new;
      inplot_old = inplot_new;
   }
}

void gtkplt_free_graph_data(GtkPltPlot *plot, unsigned int ID) {
   GtkPltPlotData *data = plot->data;
   GtkPltPlotGraph *graph = data->PlotArea->graphs+ID;
   if (graph->xvals != NULL) {
      free(graph->xvals);
      graph->xvals = NULL;
   }
   if (graph->yvals != NULL) {
      free(graph->yvals);
      graph->yvals = NULL;
   }
   if (graph->has_xerrvals && graph->xerrvals != NULL) {
      free(graph->xerrvals);
      graph->xerrvals = NULL;
   }
   if (graph->has_yerrvals && graph->yerrvals != NULL) {
      free(graph->yerrvals);
      graph->yerrvals = NULL;
   }
}

void gtkplt_plot_graph(cairo_t *cr, GtkPltPlotData *data,
                       GtkPltPlotGraph *graph) {
   switch (graph->plottype) {
      case gtkplt_points:
         gtkplt_plot_graph_points(cr, data, graph);
         break;
      case gtkplt_line:
         gtkplt_plot_graph_line(cr, data, graph);
         break;
      case gtkplt_linepoints:
         break;
      case gtkplt_bar:
         break;
      default:
         gtkplt_plot_graph_points(cr, data, graph);
         break;
   }
}
