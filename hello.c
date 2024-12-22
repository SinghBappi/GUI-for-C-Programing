#include <gtk/gtk.h>

// Function called when the application is activated
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *label;

    // Create a new window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Hello! Com Tech I.T. World");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    // Create a new label with "Hello! Com Tech IT World"
    label = gtk_label_new("Hello! Com Tech IT World");
    gtk_window_set_child(GTK_WINDOW(window), label);

    // Show the window
    gtk_window_present(GTK_WINDOW(window));
}

// Main function where the program starts
int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    // Create a new GTK application
    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // Run the application
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
