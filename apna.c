#include <gtk/gtk.h>

// Global variable for account balance
static double balance = 1000.0;

// Callback function to close the application
static void on_quit(GtkWidget *widget, gpointer data) {
    g_application_quit(G_APPLICATION(data));
}

// Callback function to show balance
static void on_show_balance(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    gchar *message = g_strdup_printf("Current Balance: $%.2f", balance);

    dialog = gtk_message_dialog_new(GTK_WINDOW(data),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "%s", message);
    gtk_window_set_title(GTK_WINDOW(dialog), "Balance");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_window_destroy(GTK_WINDOW(dialog));
    g_free(message);
}

// Callback function to deposit money
static void on_deposit(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *entry;
    const gchar *deposit_str;
    double deposit;

    dialog = gtk_dialog_new_with_buttons("Deposit", GTK_WINDOW(data), GTK_DIALOG_MODAL, "_OK", GTK_RESPONSE_OK, "_Cancel", GTK_RESPONSE_CANCEL, NULL);
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Enter amount");
    gtk_box_append(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), entry);
    gtk_widget_set_visible(entry, TRUE);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {
        deposit_str = gtk_entry_get_text(GTK_ENTRY(entry));
        deposit = g_ascii_strtod(deposit_str, NULL);
        balance += deposit;
    }
    gtk_window_destroy(GTK_WINDOW(dialog));
}

// Callback function to withdraw money
static void on_withdraw(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *entry;
    const gchar *withdraw_str;
    double withdraw;

    dialog = gtk_dialog_new_with_buttons("Withdraw", GTK_WINDOW(data), GTK_DIALOG_MODAL, "_OK", GTK_RESPONSE_OK, "_Cancel", GTK_RESPONSE_CANCEL, NULL);
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Enter amount");
    gtk_box_append(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), entry);
    gtk_widget_set_visible(entry, TRUE);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {
        withdraw_str = gtk_entry_get_text(GTK_ENTRY(entry));
        withdraw = g_ascii_strtod(withdraw_str, NULL);
        if (withdraw <= balance) {
            balance -= withdraw;
        } else {
            GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(data),
                                                             GTK_DIALOG_DESTROY_WITH_PARENT,
                                                             GTK_MESSAGE_ERROR,
                                                             GTK_BUTTONS_OK,
                                                             "Insufficient funds!");
            gtk_window_set_title(GTK_WINDOW(error_dialog), "Error");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_window_destroy(GTK_WINDOW(error_dialog));
        }
    }
    gtk_window_destroy(GTK_WINDOW(dialog));
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window, *grid;
    GtkWidget *balance_button, *deposit_button, *withdraw_button;

    // Create a new window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Banking System");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);

    balance_button = gtk_button_new_with_label("Check Balance");
    g_signal_connect(balance_button, "clicked", G_CALLBACK(on_show_balance), window);
    gtk_grid_attach(GTK_GRID(grid), balance_button, 0, 0, 1, 1);

    deposit_button = gtk_button_new_with_label("Deposit");
    g_signal_connect(deposit_button, "clicked", G_CALLBACK(on_deposit), window);
    gtk_grid_attach(GTK_GRID(grid), deposit_button, 0, 1, 1, 1);

    withdraw_button = gtk_button_new_with_label("Withdraw");
    g_signal_connect(withdraw_button, "clicked", G_CALLBACK(on_withdraw), window);
    gtk_grid_attach(GTK_GRID(grid), withdraw_button, 0, 2, 1, 1);

    g_signal_connect(window, "destroy", G_CALLBACK(on_quit), app);
    gtk_widget_set_visible(window, TRUE);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.banking", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
