#include <gtk/gtk.h>

// Callback function to display the input text
static void on_button_clicked(GtkWidget *button, gpointer entry) {
    const gchar *input_text = gtk_editable_get_text(GTK_EDITABLE(entry));

    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_ancestor(button, GTK_TYPE_WINDOW)),
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "You entered: %s", input_text);
    gtk_window_set_title(GTK_WINDOW(dialog), "Input Output");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_window_destroy(GTK_WINDOW(dialog));
}

// Activate function to create the main application window
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window, *grid;
    GtkWidget *entry, *button;

    // Create a new window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Input Output Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 100);

    // Create a grid and add it to the window
    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);

    // Create an entry widget for user input
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 1, 1);

    // Create a button to display the input text
    button = gtk_button_new_with_label("Show Input");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), entry);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

    // Show the window
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    // Create a new GTK application
    app = gtk_application_new("org.gtk.example.input_output", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // Run the application
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
