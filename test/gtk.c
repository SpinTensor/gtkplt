#include <stdbool.h>
#include <gtk/gtk.h>

int main(int argc, char **argv) {
   gtk_init(&argc, &argv);

   bool auto_terminate = false;
   if (argc > 1) {
      auto_terminate = (strcmp(argv[1], "timeout") == 0);
   }

   // Create a window
   GtkWindow *main_window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
   g_signal_connect(GTK_WIDGET(main_window),
                    "destroy",
                    G_CALLBACK(gtk_main_quit),
                    NULL);

   if (auto_terminate) {
      g_timeout_add_seconds(1, (GSourceFunc) gtk_main_quit, NULL);
   }

   gtk_widget_show_all(GTK_WIDGET(main_window));
   gtk_main();

   return 0;
}
