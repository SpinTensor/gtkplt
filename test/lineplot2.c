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

   double xmin = 0 ;
   double xmax = 10.0;
   double ymin = 0 ;
   double ymax = 10.0;

   double xvals1[] = {3,7,7,3,3};
   double yvals1[] = {3,3,7,7,3};
   unsigned int ID1 = gtkplt_add_graph(plot, 5, xvals1, yvals1);
   gtkplt_set_graph_type(plot, ID1, "wl");

   double xvals2[] = {-1,5,11,8,11,5,-1,2,-1};
   double yvals2[] = {11,8,11,5,-1,2,-1,5,11};
   unsigned int ID2 = gtkplt_add_graph(plot, 9, xvals2, yvals2);
   gtkplt_set_graph_type(plot, ID2, "wl");

   double xvals3[] = {-1,5,11,5,-1};
   double yvals3[] = {5,11,5,-1,5};
   unsigned int ID3 = gtkplt_add_graph(plot, 5, xvals3, yvals3);
   gtkplt_set_graph_type(plot, ID3, "wl");

   double xvals4[] = {-1,11};
   double yvals4[] = {5,5};
   unsigned int ID4 = gtkplt_add_graph(plot, 2, xvals4, yvals4);
   gtkplt_set_graph_type(plot, ID4, "wl");

   double xvals5[] = {5,5};
   double yvals5[] = {-1,11};
   unsigned int ID5 = gtkplt_add_graph(plot, 2, xvals5, yvals5);
   gtkplt_set_graph_type(plot, ID5, "wl");

   double xvals6[] = {-1,11};
   double yvals6[] = {-1,11};
   unsigned int ID6 = gtkplt_add_graph(plot, 2, xvals6, yvals6);
   gtkplt_set_graph_type(plot, ID6, "wl");

   double xvals7[] = {-1,11};
   double yvals7[] = {11,-1};
   unsigned int ID7 = gtkplt_add_graph(plot, 2, xvals7, yvals7);
   gtkplt_set_graph_type(plot, ID7, "wl");

   double xvals8[] = {-1,11,11,-1,-1};
   double yvals8[] = {11,11,-1,-1,11};
   unsigned int ID8 = gtkplt_add_graph(plot, 5, xvals8, yvals8);
   gtkplt_set_graph_type(plot, ID8, "wl");

   gtkplt_set_title(plot, "Titletext!");
   gtkplt_set_xaxis_title(plot, "x-axis");
   gtkplt_set_yaxis_title(plot, "y-axis");
   gtkplt_set_xaxis_range(plot, &xmin, &xmax);
   gtkplt_set_yaxis_range(plot, &ymin, &ymax);

   gtk_widget_set_size_request(GTK_WIDGET(plot), 480, 320);
   if (auto_terminate) {
      g_timeout_add_seconds(5, (GSourceFunc) gtk_main_quit, NULL);
   }
   gtk_widget_show_all(GTK_WIDGET(window));
   gtk_main();

   return 0;
}
