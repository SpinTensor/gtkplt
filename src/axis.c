#include <stdlib.h>

#include "gtkplt.h"
#include "margins.h"
#include "title.h"
#include "axis.h"
#include "text.h"

GtkPltPlotAxis *gtkplt_axis_init() {
   GtkPltPlotAxis *axis = (GtkPltPlotAxis*) malloc(sizeof(GtkPltPlotAxis));
   axis->scale = gtkplt_linear;
   axis->linewidth = 3.0;
   axis->nmajorticks = 4;
   axis->nminorticks = 4;
   axis->range[0] = 0.0;
   axis->range[1] = 0.0;
   axis->autorange[0] = true;
   axis->autorange[1] = true;
   axis->autorangevals[0] = 0.0;
   axis->autorangevals[1] = 0.0;
   axis->title = NULL;
   axis->titlefont = strdup("Helvetica");
   axis->titlefontsize = 18;
   axis->labelfont = strdup("Helvetica");
   axis->labelfontsize = 12;
   axis->labelformat = strdup("%.1f");
   axis->titlewidth = 0.0;
   axis->titlelabeldist = 0.0;
   axis->labelwidth = 0.0;
   axis->labeltickdist = 0.0;
   axis->tickwidth = 9.0;
   
   return axis;
}

void gtkplt_axis_finalize(GtkPltPlotAxis *axis_ptr) {
   if (axis_ptr->title != NULL) {
      free(axis_ptr->title);
      axis_ptr->title = NULL;
   }
   free(axis_ptr->titlefont);
   free(axis_ptr->labelfont);
   free(axis_ptr);
}

double gtkplt_xaxis_area_xmin(GtkPltPlotData *data) {
   return gtkplt_yaxis_area_xmax(data);
}
double gtkplt_xaxis_area_xmax(GtkPltPlotData *data) {
   return gtkplt_ormargin_xmin(data);
}
double gtkplt_xaxis_area_ymin(GtkPltPlotData *data) {
   double xaxis_width = 0.0;
   xaxis_width += data->xaxis->titlewidth;
   xaxis_width += data->xaxis->titlelabeldist;
   xaxis_width += data->xaxis->labelwidth;
   xaxis_width += data->xaxis->labeltickdist;
   xaxis_width += data->xaxis->tickwidth;
   return gtkplt_xaxis_area_ymax(data)-xaxis_width;
}
double gtkplt_xaxis_area_ymax(GtkPltPlotData *data) {
   return gtkplt_obmargin_ymin(data);
}

double gtkplt_yaxis_area_xmin(GtkPltPlotData *data) {
   return gtkplt_olmargin_xmax(data);
}
double gtkplt_yaxis_area_xmax(GtkPltPlotData *data) {
   double yaxis_width = 0.0;
   yaxis_width += data->yaxis->titlewidth;
   yaxis_width += data->yaxis->titlelabeldist;
   yaxis_width += data->yaxis->labelwidth;
   yaxis_width += data->yaxis->labeltickdist;
   yaxis_width += data->yaxis->tickwidth;

   return gtkplt_yaxis_area_xmin(data) + yaxis_width;
}
double gtkplt_yaxis_area_ymin(GtkPltPlotData *data) {
   return gtkplt_tbmargin_ymax(data);
}
double gtkplt_yaxis_area_ymax(GtkPltPlotData *data) {
   return gtkplt_xaxis_area_ymin(data);
}

void gtkplt_set_xaxis_range(GtkPltPlot *plot, double *xmin_ptr, double *xmax_ptr) {
   GtkPltPlotData *data = plot->data;
   if (xmin_ptr == NULL) {
      data->xaxis->autorange[0] = true;
   } else {
      data->xaxis->autorange[0] = false;
      data->xaxis->range[0] = *xmin_ptr;
   }
   if (xmax_ptr == NULL) {
      data->xaxis->autorange[1] = true;
   } else {
      data->xaxis->autorange[1] = false;
      data->xaxis->range[1] = *xmax_ptr;
   }
}

void gtkplt_set_yaxis_range(GtkPltPlot *plot, double *ymin_ptr, double *ymax_ptr) {
   GtkPltPlotData *data = plot->data;
   if (ymin_ptr == NULL) {
      data->yaxis->autorange[0] = true;
   } else {
      data->yaxis->autorange[0] = false;
      data->yaxis->range[0] = *ymin_ptr;
   }
   if (ymax_ptr == NULL) {
      data->yaxis->autorange[1] = true;
   } else {
      data->yaxis->autorange[1] = false;
      data->yaxis->range[1] = *ymax_ptr;
   }
}

void gtkplt_set_xaxis_autorange(GtkPltPlot *plot) {
   gtkplt_set_xaxis_range(plot, NULL, NULL);
}

void gtkplt_set_yaxis_autorange(GtkPltPlot *plot) {
   gtkplt_set_yaxis_range(plot, NULL, NULL);
}

void gtkplt_set_xaxis_title(GtkPltPlot *plot, const char *title) {
   GtkPltPlotData *data = plot->data;
   gtkplt_remove_xaxis_title(plot);
   data->xaxis->title = strdup(title);
}

void gtkplt_remove_xaxis_title(GtkPltPlot *plot) {
   GtkPltPlotData *data = plot->data;
   if (data->xaxis->title != NULL) {
      free(data->xaxis->title);
   }
   data->xaxis->title = NULL;
}

void gtkplt_set_xaxis_title_font(GtkPltPlot *plot, const char *font) {
   GtkPltPlotData *data = plot->data;
   free(data->xaxis->titlefont);
   data->xaxis->titlefont = strdup(font);
}

void gtkplt_set_xaxis_title_fontsize(GtkPltPlot *plot, int fontsize) {
   GtkPltPlotData *data = plot->data;
   data->xaxis->titlefontsize = fontsize;
}

void gtkplt_set_yaxis_title(GtkPltPlot *plot, const char *title) {
   GtkPltPlotData *data = plot->data;
   gtkplt_remove_yaxis_title(plot);
   data->yaxis->title = strdup(title);
}

void gtkplt_remove_yaxis_title(GtkPltPlot *plot) {
   GtkPltPlotData *data = plot->data;
   if (data->yaxis->title != NULL) {
      free(data->yaxis->title);
   }
   data->yaxis->title = NULL;
}

void gtkplt_set_yaxis_title_font(GtkPltPlot *plot, const char *font) {
   GtkPltPlotData *data = plot->data;
   free(data->yaxis->titlefont);
   data->yaxis->titlefont = strdup(font);
}

void gtkplt_set_yaxis_title_fontsize(GtkPltPlot *plot, int fontsize) {
   GtkPltPlotData *data = plot->data;
   data->yaxis->titlefontsize = fontsize;
}

void gtkplt_plot_draw_yaxis_minorticks(cairo_t *cr, GtkPltPlotData *data,
                                       double yminpos, double ymaxpos,
                                       double xmaxpos) {
   double xminpos = xmaxpos - 0.5*data->yaxis->tickwidth;

   int nticks = data->yaxis->nminorticks < 0 ? 0 : data->yaxis->nminorticks;

   double tickspacing;
   tickspacing = ymaxpos - yminpos;
   tickspacing /= nticks + 1;

   cairo_set_line_width(cr, data->yaxis->tickwidth/6.0);
   for (int itick=1; itick<=nticks; itick++) {
      double y = yminpos + itick*tickspacing;
      cairo_move_to(cr, xminpos, y);
      cairo_line_to(cr, xmaxpos, y);
   }
   cairo_stroke(cr);
}

void gtkplt_plot_draw_yaxis_majorticks(cairo_t *cr, GtkPltPlotData *data) {
   // minimum is two ticks
   data->yaxis->nmajorticks = data->yaxis->nmajorticks < 2 ? 2 : data->yaxis->nmajorticks;
   int nticks = data->yaxis->nmajorticks;

   double yminpos = gtkplt_yaxis_area_ymin(data);
   double ymaxpos = gtkplt_yaxis_area_ymax(data);
   double xmaxpos = gtkplt_yaxis_area_xmax(data);
   double xminpos = xmaxpos - data->yaxis->tickwidth;

   double tickspacing ;
   tickspacing = ymaxpos - yminpos;
   tickspacing /= nticks - 1;

   cairo_set_line_width(cr, data->yaxis->tickwidth/3.0);
   cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
   for (int itick=0; itick<nticks; itick++) {
      double y = yminpos + itick*tickspacing;
      cairo_move_to(cr, xmaxpos, y);
      cairo_line_to(cr, xminpos, y);
   }
   for (int itick=0; itick<nticks-1; itick++) {
      double y = yminpos + itick*tickspacing;
      // minor ticks
      gtkplt_plot_draw_yaxis_minorticks(cr, data, y, y+tickspacing, xmaxpos);
   }
   cairo_stroke(cr);
}

void gtkplt_plot_draw_xaxis_minorticks(cairo_t *cr, GtkPltPlotData *data,
                                       double xminpos, double xmaxpos,
                                       double yminpos) {
   double ymaxpos = yminpos + 0.5*data->xaxis->tickwidth;

   int nticks = data->xaxis->nminorticks < 0 ? 0 : data->xaxis->nminorticks;

   double tickspacing;
   tickspacing = xmaxpos - xminpos;
   tickspacing /= nticks + 1;

   cairo_set_line_width(cr, data->yaxis->tickwidth/6.0);
   for (int itick=1; itick<=nticks; itick++) {
      double x = xminpos + itick*tickspacing;
      cairo_move_to(cr, x, yminpos);
      cairo_line_to(cr, x, ymaxpos);
   }
   cairo_stroke(cr);
}
void gtkplt_plot_draw_xaxis_label(cairo_t *cr, GtkPltPlotData *data) {
   int nlabel = data->xaxis->nmajorticks;
   double xminpos = gtkplt_xaxis_area_xmin(data);
   double xmaxpos = gtkplt_xaxis_area_xmax(data);
   double y = gtkplt_xaxis_area_ymax(data)
              -data->xaxis->titlewidth 
              -data->xaxis->titlelabeldist
              -0.5*data->xaxis->labelwidth;

   double labelspacing ;
   labelspacing = xmaxpos - xminpos;
   labelspacing /= nlabel - 1;

   for (int ilabel=0; ilabel<nlabel; ilabel++) {
      double x = xminpos + ilabel*labelspacing;

      // create the label
      double xvalue;
      xvalue = data->xaxis->range[1]-data->xaxis->range[0];
      xvalue *= ilabel;
      xvalue /= nlabel-1;
      xvalue += data->xaxis->range[0];
      int labellen = snprintf(NULL, 0, data->xaxis->labelformat, xvalue);
      labellen++; // null terminator
      char *tmplabel = (char*) malloc(labellen*sizeof(char));
      snprintf(tmplabel, labellen*sizeof(char),
               data->xaxis->labelformat, xvalue);
      double color[3] = {0.0, 0.0, 0.0};
      gtkplt_place_text(cr, tmplabel,
                        x,
                        y,
                        0.0,
                        color,
                        data->xaxis->labelfont,
                        data->xaxis->labelfontsize);
      free(tmplabel);
   }
}

void gtkplt_plot_draw_yaxis_label(cairo_t *cr, GtkPltPlotData *data) {
   int nlabel = data->yaxis->nmajorticks;
   double yminpos = gtkplt_yaxis_area_ymin(data);
   double ymaxpos = gtkplt_yaxis_area_ymax(data);
   double x = gtkplt_yaxis_area_xmin(data)
              +data->yaxis->titlewidth
              +data->yaxis->titlelabeldist
              +0.5*data->yaxis->labelwidth;

   double labelspacing ;
   labelspacing = ymaxpos - yminpos;
   labelspacing /= nlabel - 1;

   for (int ilabel=0; ilabel<nlabel; ilabel++) {
      double y = yminpos + ilabel*labelspacing;

      // create the label
      double yvalue = 0.0;
      yvalue = data->yaxis->range[1]-data->yaxis->range[0];
      yvalue *= nlabel-1-ilabel;
      yvalue /= nlabel-1;
      yvalue += data->yaxis->range[0];
      int labellen = snprintf(NULL, 0, data->yaxis->labelformat, yvalue);
      labellen++; // null terminator
      char *tmplabel = (char*) malloc(labellen*sizeof(char));
      snprintf(tmplabel, labellen*sizeof(char),
               data->yaxis->labelformat, yvalue);
      double color[3] = {0.0, 0.0, 0.0};
      gtkplt_place_text(cr, tmplabel,
                        x,
                        y,
                        0.0,
                        color,
                        data->yaxis->labelfont,
                        data->yaxis->labelfontsize);
      free(tmplabel);
   }
}


void gtkplt_plot_draw_xaxis_majorticks(cairo_t *cr, GtkPltPlotData *data) {
   // minimum is two ticks
   data->xaxis->nmajorticks = data->xaxis->nmajorticks < 2 ? 2 : data->xaxis->nmajorticks;
   int nticks = data->xaxis->nmajorticks;

   double xminpos = gtkplt_xaxis_area_xmin(data);
   double xmaxpos = gtkplt_xaxis_area_xmax(data);
   double yminpos = gtkplt_xaxis_area_ymin(data);
   double ymaxpos = yminpos + data->xaxis->tickwidth;

   double tickspacing ;
   tickspacing = xmaxpos - xminpos;
   tickspacing /= nticks - 1;

   cairo_set_line_width(cr, data->xaxis->tickwidth/3.0);
   cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
   for (int itick=0; itick<nticks; itick++) {
      // draw the tick
      double x = xminpos + itick*tickspacing;
      cairo_move_to(cr, x, yminpos);
      cairo_line_to(cr, x, ymaxpos);
   }
   for (int itick=0; itick<nticks-1; itick++) {
      double x = xminpos + itick*tickspacing;
      // minor ticks
      gtkplt_plot_draw_xaxis_minorticks(cr, data, x, x+tickspacing, yminpos);
   }
   cairo_stroke(cr);
}

void gtkplt_plot_draw_xaxis_title(cairo_t *cr, GtkPltPlotData *data) {
   double xpos = 0.5*(gtkplt_xaxis_area_xmax(data) + gtkplt_xaxis_area_xmin(data));
   double ypos = gtkplt_xaxis_area_ymax(data) - 0.5*data->xaxis->titlewidth;

   double color[3] = {0.0, 0.0, 0.0};
   gtkplt_place_text(cr, data->xaxis->title,
                     xpos, ypos, data->xaxis->titleangle,
                     color, data->xaxis->titlefont, data->xaxis->titlefontsize);
}

void gtkplt_plot_draw_yaxis_title(cairo_t *cr, GtkPltPlotData *data) {
   double xpos = gtkplt_yaxis_area_xmin(data) + 0.5*data->yaxis->titlewidth;
   double ypos = 0.5*(gtkplt_yaxis_area_ymax(data) + gtkplt_yaxis_area_ymin(data));

   double color[3] = {0.0, 0.0, 0.0};
   gtkplt_place_text(cr, data->yaxis->title,
                     xpos, ypos, data->yaxis->titleangle,
                     color, data->yaxis->titlefont, data->yaxis->titlefontsize);
}

void gtkplt_plot_configure_axis_placement(cairo_t *cr, GtkPltPlotData *data) {
   // set axis title height.
   cairo_font_extents_t font_extent;
   // x-axis
   cairo_select_font_face(cr, data->xaxis->titlefont,
                          CAIRO_FONT_SLANT_NORMAL,
                          CAIRO_FONT_WEIGHT_NORMAL);
   cairo_set_font_size(cr, data->xaxis->titlefontsize);
   cairo_font_extents(cr, &font_extent);
   data->xaxis->titlewidth = font_extent.height;

   // y-axis
   cairo_select_font_face(cr, data->yaxis->titlefont,
                          CAIRO_FONT_SLANT_NORMAL,
                          CAIRO_FONT_WEIGHT_NORMAL);
   cairo_set_font_size(cr, data->yaxis->titlefontsize);
   cairo_font_extents(cr, &font_extent);
   data->yaxis->titlewidth = font_extent.height;
   data->yaxis->titlelabeldist = 0.5*font_extent.height;

   // set the label height
   // x-axis
   cairo_select_font_face(cr, data->xaxis->labelfont,
                          CAIRO_FONT_SLANT_NORMAL,
                          CAIRO_FONT_WEIGHT_NORMAL);
   cairo_set_font_size(cr, data->xaxis->labelfontsize);
   cairo_font_extents(cr, &font_extent);
   data->xaxis->labelwidth = font_extent.height;
   // y-axis
   cairo_select_font_face(cr, data->yaxis->labelfont,
                          CAIRO_FONT_SLANT_NORMAL,
                          CAIRO_FONT_WEIGHT_NORMAL);
   cairo_set_font_size(cr, data->yaxis->labelfontsize);
   double textwidth[2];
   for (int irange=0; irange<2; irange++) {
      cairo_text_extents_t text_extent;
      int labellen = snprintf(NULL, 0,
                              data->yaxis->labelformat,
                              data->yaxis->range[irange]);
      labellen++; // null terminator
      char *tmplabel = (char*) malloc(labellen*sizeof(char));
      snprintf(tmplabel, labellen*sizeof(char),
               data->yaxis->labelformat, data->yaxis->range[irange]);
      cairo_text_extents(cr, tmplabel, &text_extent);
      textwidth[irange] = text_extent.width;
      free(tmplabel);
   }
   data->yaxis->labelwidth = textwidth[0] > textwidth[1] ? textwidth[0] : textwidth[1];
   data->yaxis->labeltickdist = 3;
}

void gtkplt_plot_draw_axis(cairo_t *cr, GtkPltPlotData *data) {
   // first figure out where the axis should go.
   // The placement of the x- and y-axis are codependent on each other.
   gtkplt_plot_configure_axis_placement(cr, data);

   // draw axis frame
   cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
   cairo_set_line_width(cr, data->xaxis->linewidth);

   // top line
   cairo_move_to(cr, gtkplt_xaxis_area_xmin(data), gtkplt_yaxis_area_ymin(data));
   cairo_line_to(cr, gtkplt_xaxis_area_xmax(data), gtkplt_yaxis_area_ymin(data));
   cairo_line_to(cr, gtkplt_xaxis_area_xmax(data), gtkplt_yaxis_area_ymax(data));
   cairo_line_to(cr, gtkplt_xaxis_area_xmin(data), gtkplt_yaxis_area_ymax(data));
   cairo_close_path(cr);
   cairo_stroke(cr);

   // dtaw ticks
   gtkplt_plot_draw_xaxis_majorticks(cr, data);
   gtkplt_plot_draw_yaxis_majorticks(cr, data);

   // draw label
   gtkplt_plot_draw_xaxis_label(cr, data);
   gtkplt_plot_draw_yaxis_label(cr, data);

   // write title
   gtkplt_plot_draw_xaxis_title(cr, data);
   gtkplt_plot_draw_yaxis_title(cr, data);
}

void gtkplt_axis_autoranges(GtkPltPlotData *data, char axis_ident) {
   GtkPltPlotAxis *axis = NULL;
   if (axis_ident == 'x') {
      axis = data->xaxis;
   } else if (axis_ident == 'y') {
      axis = data->yaxis;
   } else {
      fprintf(stderr, "undefined axis given: %s:%d\n", __FILE__, __LINE__);
      abort();
   }
   // set default values
   axis->autorangevals[0] = 0.0;
   axis->autorangevals[1] = 1.0;
   bool vals_init = false;
   // combined search for min and max value
   for (unsigned int i=0; i<data->PlotArea->ngraphs; i++) {
      if (data->PlotArea->graphs[i].valid && data->PlotArea->graphs[i].nvals > 0) {
         double *vals = NULL;
         if (axis_ident == 'x') {
            vals = data-> PlotArea->graphs[i].xvals;
         } else if (axis_ident == 'y') {
            vals = data-> PlotArea->graphs[i].yvals;
         }
         double maxval = vals[0];
         double minval = vals[0];
         for (int ival=1; ival<data->PlotArea->graphs[i].nvals; ival++) {
            if (maxval < vals[ival]) {
               maxval = vals[ival];
            } else if (minval > vals[ival]) {
               minval = vals[ival];
            }
         }
         if (!vals_init || minval < axis->autorangevals[0]) {
            axis->autorangevals[0] = minval;
         }
         if (!vals_init || maxval < axis->autorangevals[1]) {
            axis->autorangevals[1] = maxval;
         }

#ifdef _DEBUG
         printf("auto-%crange = [%f, %f]\n", axis_ident, minval, maxval);
#endif
      }
   }
}
