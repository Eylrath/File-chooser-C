#include<gtk/gtk.h>
#include<string.h>

static void activate(GtkApplication *app, gpointer user_data)
{
	//declaration of GtkWidgets
	GtkWidget *window;
	GtkWidget *scrolled_window;
	GtkWidget *image;
	GtkWidget *chooser;


	//setting response action for the file_chooser widget
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	
	//assignment and settings for window
	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "scrolled_image");
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);

	//setting the dialog widget
	gint res;
	chooser = gtk_file_chooser_dialog_new("WYBIERZ PLIK", GTK_WINDOW(window), action, "ZAMKNIJ" , GTK_RESPONSE_CANCEL, "OTWORZ", GTK_RESPONSE_ACCEPT, NULL);
	res = gtk_dialog_run(GTK_DIALOG(chooser));


		
	//assignment for scrolled_window and setting its borders
	scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_set_border_width(GTK_CONTAINER(scrolled_window), 5);
	if (res == GTK_RESPONSE_ACCEPT)
	{
		char *file;
		char ext[5];
		file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser));
		if(strlen(file)>=4)
		{
			strcpy(ext, file + strlen(file) - 3);
			if(strcmp(ext, "gif")==0 || strcmp(ext, "jpg")==0)
			{
				image = gtk_image_new_from_file(file);
				g_free(file);
				gtk_container_add(GTK_CONTAINER(scrolled_window), image);		
				gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
				gtk_container_add(GTK_CONTAINER(window), scrolled_window);	
				gtk_widget_show_all(window);
			}
			else
				gtk_widget_destroy(window);
		}
		else 
			gtk_widget_destroy(window);
	}
	else	
		gtk_widget_destroy(window);
	gtk_widget_destroy(chooser);

}

int main(int argc, char **argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}
