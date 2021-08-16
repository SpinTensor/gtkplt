#include <gtk/gtk.h>
#include <gtkplt.h>

gint main(int argc,char *argv[]) {
    GtkWindow *window;
    GtkPltPlot *plot;
    
    gtk_init(&argc, &argv);
    window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    plot = GTKPLT_PLOT(gtkplt_plot_new());
    gtk_container_add(GTK_CONTAINER(window),
                      GTK_WIDGET(plot));
    gtk_widget_set_size_request(GTK_WIDGET(plot), 200, 100);
    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();
    return 0;
}

