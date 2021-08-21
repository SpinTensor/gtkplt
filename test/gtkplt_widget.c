#include <stdlib.h>

#include <gtk/gtk.h>
#include <math.h>
#include <gtkplt.h>

gint main(int argc,char *argv[]) {
    GtkWindow *window;
    GtkPltPlot *plot;
    
    gtk_init(&argc, &argv);
    window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    plot = GTKPLT_PLOT(gtkplt_plot_new());
    double xmin = -1.0;
    double xmax = 6.0;
    double dx = 0.5;
    int nvals = (xmax-xmin) / dx + 0.5;
    double *xvals = (double*) malloc(nvals*sizeof(double));
    double *yvals = (double*) malloc(nvals*sizeof(double));
    for (int i=0; i<nvals; i++) {
       xvals[i] = 0.5*i;
       yvals[i] = sin(xvals[i]);
    }
    gtkplt_add_graph(plot, nvals, xvals, yvals);
    free(xvals);
    xvals = NULL;
    free(yvals);
    yvals = NULL;
    gtk_container_add(GTK_CONTAINER(window),
                      GTK_WIDGET(plot));
    gtk_widget_set_size_request(GTK_WIDGET(plot), 1024, 768);
    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();
    return 0;
}
