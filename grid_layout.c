#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *entry;
    GtkWidget *button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Grid Layout");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);

    label = gtk_label_new("Enter text:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 2, 1);

    button = gtk_button_new_with_label("Submit");
    gtk_grid_attach(GTK_GRID(grid), button, 1, 1, 1, 1);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
