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
   int ngraphs = 10;
   int *graphIDs = (int*) malloc(ngraphs*sizeof(int));
   double **graphdata = (double**) malloc(2*ngraphs*sizeof(double*));
   for (int igraph=0; igraph<ngraphs; igraph++) {
      graphdata[2*igraph] = (double*) malloc(nvals*sizeof(double));
      graphdata[2*igraph+1] = (double*) malloc(nvals*sizeof(double));
      for (int i=0; i<nvals; i++) {
         graphdata[2*igraph][i] = dx*i+xmin;
         graphdata[2*igraph+1][i] = sin(graphdata[2*igraph][i])+0.1*igraph;
      }
      graphIDs[igraph] = gtkplt_add_graph(plot, nvals,
                                          graphdata[2*igraph],
                                          graphdata[2*igraph+1]);
      gtkplt_set_graph_type(plot, graphIDs[igraph], "wl");
      gtkplt_set_graph_color_rgb(plot, graphIDs[igraph], 1.0-0.1*igraph, 0.1*igraph, 0.0);
   }
   gtkplt_set_title(plot, "Titletext!");
   gtkplt_set_xaxis_title(plot, "x-axis");
   gtkplt_set_yaxis_title(plot, "y-axis");
   gtkplt_set_xaxis_autorange(plot);
   gtkplt_set_yaxis_autorange(plot);

   gtk_widget_set_size_request(GTK_WIDGET(plot), 480, 320);
   if (auto_terminate) {
      g_timeout_add_seconds(5, (GSourceFunc) gtk_main_quit, NULL);
   }
   gtk_widget_show_all(GTK_WIDGET(window));
   gtk_main();

   free(graphIDs);
   for (int igraph=0; igraph<ngraphs; igraph++) {
      free(graphdata[2*igraph]);
      free(graphdata[2*igraph+1]);
   }
   free(graphdata);

   return 0;
}
