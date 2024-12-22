#include <gtk/gtk.h>

// Callback function for button click
static void on_button_clicked(GtkWidget *widget, gpointer data) {
    g_print("Button clicked!\n");
}

// Activate function to create the main application window
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window, *button;

    // Create a new window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Simple GTK Program");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);

    // Create a button and add it to the window
    button = gtk_button_new_with_label("Click Me");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_window_set_child(GTK_WINDOW(window), button);

    // Show the window
    gtk_window_present(GTK_WINDOW(window));
}

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
