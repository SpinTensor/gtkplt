#include <gtk/gtk.h>

void on_main_window_destroy(GtkWidget window,
                            gpointer user_data) {
   (void) window;
   (void) user_data;
   gtk_main_quit();
}

int main(int argc, char **argv) {
   GtkWidget *main_window;
   gtk_init(&argc, &argv);
   main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_widget_show(main_window);

   g_signal_connect(main_window,
                    "destroy",
                    G_CALLBACK(on_main_window_destroy),
                    NULL);

   gtk_main();

   return 0;
}
