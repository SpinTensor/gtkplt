#include <stdbool.h>
#include <gtk/gtk.h>

void on_no_clicked(GtkButton* widget, gpointer data) {
   (void) widget;
   bool *saw_text = (bool*) data;
   *saw_text = false;
   gtk_main_quit();
}
void on_yes_clicked(GtkButton* widget, gpointer data) {
   (void) widget;
   bool *saw_text = (bool*) data;
   *saw_text = true;
   gtk_main_quit();
}

int main(int argc, char **argv) {
   gtk_init(&argc, &argv);
   // Create a window
   GtkWindow *main_window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
   g_signal_connect(GTK_WIDGET(main_window),
                    "destroy",
                    G_CALLBACK(gtk_main_quit),
                    NULL);
   // Add a box
   GtkBox *box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_VERTICAL, 0));
   gtk_container_add(GTK_CONTAINER(main_window),
                     GTK_WIDGET(box));
   // Add text
   GtkLabel *label = GTK_LABEL(gtk_label_new("Can you see this text\n"));
   gtk_box_pack_start(box, GTK_WIDGET(label), TRUE, TRUE, 0);
   // Add the buttons
   bool saw_text = false;
   GtkButton *yesbutton = GTK_BUTTON(gtk_button_new_with_label("Yes"));
   gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(yesbutton), TRUE, TRUE, 0);
   g_signal_connect(GTK_WIDGET(yesbutton), "clicked", G_CALLBACK(on_yes_clicked),
                    (gpointer) &saw_text);
   GtkButton *nobutton = GTK_BUTTON(gtk_button_new_with_label("no"));
   gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(nobutton), TRUE, TRUE, 0);
   g_signal_connect(GTK_WIDGET(nobutton), "clicked", G_CALLBACK(on_no_clicked),
                    (gpointer) &saw_text);

   gtk_widget_show_all(GTK_WIDGET(main_window));
   gtk_main();

   return saw_text ? EXIT_SUCCESS : EXIT_FAILURE;
}
