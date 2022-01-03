#include <stdlib.h>

#include <gtk/gtk.h>
#include <math.h>
#include <gtkplt.h>

int main(int argc,char *argv[]) {
   bool auto_terminate = false;
   if (argc > 1) {
      auto_terminate = (strcmp(argv[1], "timeout") == 0);
   }

   GtkWindow *window;
   GtkPltPlot *plot;

   gtk_init(&argc, &argv);
   window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
   g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

   plot = GTKPLT_PLOT(gtkplt_plot_new());
   gtk_container_add(GTK_CONTAINER(window),
                     GTK_WIDGET(plot));

   double xmin = -6.5 ;
   double xmax = 6.5;
   double dx = 0.1;
   int nvals = (xmax-xmin) / dx + 0.5 + 1.0;
   double *xvals = (double*) malloc(nvals*sizeof(double));
   double *yvals = (double*) malloc(nvals*sizeof(double));
   for (int i=0; i<nvals; i++) {
      xvals[i] = dx*i+xmin;
      yvals[i] = sin(xvals[i]);
   }
   gtkplt_add_graph(plot, nvals, xvals, yvals);
   gtkplt_set_title(plot, "Titletext!");
   gtkplt_set_xaxis_title(plot, "x-axis");
   gtkplt_set_yaxis_title(plot, "y-axis");
   double xrange_min = -4;
   double xrange_max = 10;
   gtkplt_set_xaxis_range(plot, &xrange_min, &xrange_max);
   double yrange_min = -0.5;
   double yrange_max = 1.5;
   gtkplt_set_yaxis_range(plot, &yrange_min, &yrange_max);

   gtk_widget_set_size_request(GTK_WIDGET(plot), 480, 320);
   if (auto_terminate) {
      g_timeout_add_seconds(5, (GSourceFunc) gtk_main_quit, NULL);
   }
   gtk_widget_show_all(GTK_WIDGET(window));
   gtk_main();

   free(xvals);
   xvals = NULL;
   free(yvals);
   yvals = NULL;

   return 0;
}
