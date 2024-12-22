#include <gtk/gtk.h>

typedef struct {
    GtkWidget *entry;
    GtkWidget *list_box;
} AppWidgets;

static void add_task(GtkWidget *button, gpointer data) {
    AppWidgets *widgets = (AppWidgets *)data;
    const gchar *task_text = gtk_editable_get_text(GTK_EDITABLE(widgets->entry));

    if (g_strcmp0(task_text, "") != 0) {
        GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        GtkWidget *label = gtk_label_new(task_text);
        GtkWidget *remove_button = gtk_button_new_with_label("Remove");

        gtk_box_append(GTK_BOX(row), label);
        gtk_box_append(GTK_BOX(row), remove_button);
        gtk_list_box_append(GTK_LIST_BOX(widgets->list_box), row);

        g_signal_connect_swapped(remove_button, "clicked", G_CALLBACK(gtk_widget_set_visible), row);
        gtk_widget_set_visible(row, TRUE);

        gtk_editable_set_text(GTK_EDITABLE(widgets->entry), "");
    }
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *entry;
    GtkWidget *add_button;
    GtkWidget *list_box;

    AppWidgets *widgets = g_malloc(sizeof(AppWidgets));

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "To-Do List");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    entry = gtk_entry_new();
    gtk_box_append(GTK_BOX(vbox), entry);
    widgets->entry = entry;

    add_button = gtk_button_new_with_label("Add Task");
    gtk_box_append(GTK_BOX(vbox), add_button);

    list_box = gtk_list_box_new();
    gtk_box_append(GTK_BOX(vbox), list_box);
    widgets->list_box = list_box;

    g_signal_connect(add_button, "clicked", G_CALLBACK(add_task), widgets);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.todo", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
