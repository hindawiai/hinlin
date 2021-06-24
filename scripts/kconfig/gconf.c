<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002-2003 Roमुख्य Lievin <roms@tilp.info>
 */

#समावेश <मानककोष.स>
#समावेश "lkc.h"
#समावेश "images.h"

#समावेश <glade/glade.h>
#समावेश <gtk/gtk.h>
#समावेश <glib.h>
#समावेश <gdk/gdkkeysyms.h>

#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <strings.h>
#समावेश <unistd.h>
#समावेश <समय.स>

//#घोषणा DEBUG

क्रमागत अणु
	SINGLE_VIEW, SPLIT_VIEW, FULL_VIEW
पूर्ण;

क्रमागत अणु
	OPT_NORMAL, OPT_ALL, OPT_PROMPT
पूर्ण;

अटल gपूर्णांक view_mode = FULL_VIEW;
अटल gboolean show_name = TRUE;
अटल gboolean show_range = TRUE;
अटल gboolean show_value = TRUE;
अटल gboolean resizeable = FALSE;
अटल पूर्णांक opt_mode = OPT_NORMAL;

GtkWidget *मुख्य_wnd = शून्य;
GtkWidget *tree1_w = शून्य;	// left  frame
GtkWidget *tree2_w = शून्य;	// right frame
GtkWidget *text_w = शून्य;
GtkWidget *hpaned = शून्य;
GtkWidget *vpaned = शून्य;
GtkWidget *back_btn = शून्य;
GtkWidget *save_btn = शून्य;
GtkWidget *save_menu_item = शून्य;

GtkTextTag *tag1, *tag2;
GdkColor color;

GtkTreeStore *tree1, *tree2, *tree;
GtkTreeModel *model1, *model2;
अटल GtkTreeIter *parents[256];
अटल gपूर्णांक indent;

अटल काष्ठा menu *current; // current node क्रम SINGLE view
अटल काष्ठा menu *browsed; // browsed node क्रम SPLIT view

क्रमागत अणु
	COL_OPTION, COL_NAME, COL_NO, COL_MOD, COL_YES, COL_VALUE,
	COL_MENU, COL_COLOR, COL_EDIT, COL_PIXBUF,
	COL_PIXVIS, COL_BTNVIS, COL_BTNACT, COL_BTNINC, COL_BTNRAD,
	COL_NUMBER
पूर्ण;

अटल व्योम display_list(व्योम);
अटल व्योम display_tree(काष्ठा menu *menu);
अटल व्योम display_tree_part(व्योम);
अटल व्योम update_tree(काष्ठा menu *src, GtkTreeIter * dst);
अटल व्योम set_node(GtkTreeIter * node, काष्ठा menu *menu, gअक्षर ** row);
अटल gअक्षर **fill_row(काष्ठा menu *menu);
अटल व्योम conf_changed(व्योम);

/* Helping/Debugging Functions */
#अगर_घोषित DEBUG
अटल स्थिर अक्षर *dbg_sym_flags(पूर्णांक val)
अणु
	अटल अक्षर buf[256];

	bzero(buf, 256);

	अगर (val & SYMBOL_CONST)
		म_जोड़ो(buf, "const/");
	अगर (val & SYMBOL_CHECK)
		म_जोड़ो(buf, "check/");
	अगर (val & SYMBOL_CHOICE)
		म_जोड़ो(buf, "choice/");
	अगर (val & SYMBOL_CHOICEVAL)
		म_जोड़ो(buf, "choiceval/");
	अगर (val & SYMBOL_VALID)
		म_जोड़ो(buf, "valid/");
	अगर (val & SYMBOL_OPTIONAL)
		म_जोड़ो(buf, "optional/");
	अगर (val & SYMBOL_WRITE)
		म_जोड़ो(buf, "write/");
	अगर (val & SYMBOL_CHANGED)
		म_जोड़ो(buf, "changed/");
	अगर (val & SYMBOL_NO_WRITE)
		म_जोड़ो(buf, "no_write/");

	buf[म_माप(buf) - 1] = '\0';

	वापस buf;
पूर्ण
#पूर्ण_अगर

अटल व्योम replace_button_icon(GladeXML *xml, GdkDrawable *winकरोw,
				GtkStyle *style, gअक्षर *btn_name, gअक्षर **xpm)
अणु
	GdkPixmap *pixmap;
	GdkBiपंचांगap *mask;
	GtkToolButton *button;
	GtkWidget *image;

	pixmap = gdk_pixmap_create_from_xpm_d(winकरोw, &mask,
					      &style->bg[GTK_STATE_NORMAL],
					      xpm);

	button = GTK_TOOL_BUTTON(glade_xml_get_widget(xml, btn_name));
	image = gtk_image_new_from_pixmap(pixmap, mask);
	gtk_widget_show(image);
	gtk_tool_button_set_icon_widget(button, image);
पूर्ण

/* Main Winकरोw Initialization */
अटल व्योम init_मुख्य_winकरोw(स्थिर gअक्षर *glade_file)
अणु
	GladeXML *xml;
	GtkWidget *widget;
	GtkTextBuffer *txtbuf;
	GtkStyle *style;

	xml = glade_xml_new(glade_file, "window1", शून्य);
	अगर (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_संकेत_स्वतःconnect(xml);

	मुख्य_wnd = glade_xml_get_widget(xml, "window1");
	hpaned = glade_xml_get_widget(xml, "hpaned1");
	vpaned = glade_xml_get_widget(xml, "vpaned1");
	tree1_w = glade_xml_get_widget(xml, "treeview1");
	tree2_w = glade_xml_get_widget(xml, "treeview2");
	text_w = glade_xml_get_widget(xml, "textview3");

	back_btn = glade_xml_get_widget(xml, "button1");
	gtk_widget_set_sensitive(back_btn, FALSE);

	widget = glade_xml_get_widget(xml, "show_name1");
	gtk_check_menu_item_set_active((GtkCheckMenuItem *) widget,
				       show_name);

	widget = glade_xml_get_widget(xml, "show_range1");
	gtk_check_menu_item_set_active((GtkCheckMenuItem *) widget,
				       show_range);

	widget = glade_xml_get_widget(xml, "show_data1");
	gtk_check_menu_item_set_active((GtkCheckMenuItem *) widget,
				       show_value);

	save_btn = glade_xml_get_widget(xml, "button3");
	save_menu_item = glade_xml_get_widget(xml, "save1");
	conf_set_changed_callback(conf_changed);

	style = gtk_widget_get_style(मुख्य_wnd);
	widget = glade_xml_get_widget(xml, "toolbar1");

	replace_button_icon(xml, मुख्य_wnd->winकरोw, style,
			    "button4", (gअक्षर **) xpm_single_view);
	replace_button_icon(xml, मुख्य_wnd->winकरोw, style,
			    "button5", (gअक्षर **) xpm_split_view);
	replace_button_icon(xml, मुख्य_wnd->winकरोw, style,
			    "button6", (gअक्षर **) xpm_tree_view);

	txtbuf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_w));
	tag1 = gtk_text_buffer_create_tag(txtbuf, "mytag1",
					  "foreground", "red",
					  "weight", PANGO_WEIGHT_BOLD,
					  शून्य);
	tag2 = gtk_text_buffer_create_tag(txtbuf, "mytag2",
					  /*"style", PANGO_STYLE_OBLIQUE, */
					  शून्य);

	gtk_winकरोw_set_title(GTK_WINDOW(मुख्य_wnd), rooपंचांगenu.prompt->text);

	gtk_widget_show(मुख्य_wnd);
पूर्ण

अटल व्योम init_tree_model(व्योम)
अणु
	gपूर्णांक i;

	tree = tree2 = gtk_tree_store_new(COL_NUMBER,
					  G_TYPE_STRING, G_TYPE_STRING,
					  G_TYPE_STRING, G_TYPE_STRING,
					  G_TYPE_STRING, G_TYPE_STRING,
					  G_TYPE_POINTER, GDK_TYPE_COLOR,
					  G_TYPE_BOOLEAN, GDK_TYPE_PIXBUF,
					  G_TYPE_BOOLEAN, G_TYPE_BOOLEAN,
					  G_TYPE_BOOLEAN, G_TYPE_BOOLEAN,
					  G_TYPE_BOOLEAN);
	model2 = GTK_TREE_MODEL(tree2);

	क्रम (parents[0] = शून्य, i = 1; i < 256; i++)
		parents[i] = (GtkTreeIter *) g_दो_स्मृति(माप(GtkTreeIter));

	tree1 = gtk_tree_store_new(COL_NUMBER,
				   G_TYPE_STRING, G_TYPE_STRING,
				   G_TYPE_STRING, G_TYPE_STRING,
				   G_TYPE_STRING, G_TYPE_STRING,
				   G_TYPE_POINTER, GDK_TYPE_COLOR,
				   G_TYPE_BOOLEAN, GDK_TYPE_PIXBUF,
				   G_TYPE_BOOLEAN, G_TYPE_BOOLEAN,
				   G_TYPE_BOOLEAN, G_TYPE_BOOLEAN,
				   G_TYPE_BOOLEAN);
	model1 = GTK_TREE_MODEL(tree1);
पूर्ण

अटल व्योम init_left_tree(व्योम)
अणु
	GtkTreeView *view = GTK_TREE_VIEW(tree1_w);
	GtkCellRenderer *renderer;
	GtkTreeSelection *sel;
	GtkTreeViewColumn *column;

	gtk_tree_view_set_model(view, model1);
	gtk_tree_view_set_headers_visible(view, TRUE);
	gtk_tree_view_set_rules_hपूर्णांक(view, TRUE);

	column = gtk_tree_view_column_new();
	gtk_tree_view_append_column(view, column);
	gtk_tree_view_column_set_title(column, "Options");

	renderer = gtk_cell_renderer_toggle_new();
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(column),
					renderer, FALSE);
	gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(column),
					    renderer,
					    "active", COL_BTNACT,
					    "inconsistent", COL_BTNINC,
					    "visible", COL_BTNVIS,
					    "radio", COL_BTNRAD, शून्य);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(column),
					renderer, FALSE);
	gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(column),
					    renderer,
					    "text", COL_OPTION,
					    "foreground-gdk",
					    COL_COLOR, शून्य);

	sel = gtk_tree_view_get_selection(view);
	gtk_tree_selection_set_mode(sel, GTK_SELECTION_SINGLE);
	gtk_widget_realize(tree1_w);
पूर्ण

अटल व्योम renderer_edited(GtkCellRendererText * cell,
			    स्थिर gअक्षर * path_string,
			    स्थिर gअक्षर * new_text, gpoपूर्णांकer user_data);

अटल व्योम init_right_tree(व्योम)
अणु
	GtkTreeView *view = GTK_TREE_VIEW(tree2_w);
	GtkCellRenderer *renderer;
	GtkTreeSelection *sel;
	GtkTreeViewColumn *column;
	gपूर्णांक i;

	gtk_tree_view_set_model(view, model2);
	gtk_tree_view_set_headers_visible(view, TRUE);
	gtk_tree_view_set_rules_hपूर्णांक(view, TRUE);

	column = gtk_tree_view_column_new();
	gtk_tree_view_append_column(view, column);
	gtk_tree_view_column_set_title(column, "Options");

	renderer = gtk_cell_renderer_pixbuf_new();
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(column),
					renderer, FALSE);
	gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(column),
					    renderer,
					    "pixbuf", COL_PIXBUF,
					    "visible", COL_PIXVIS, शून्य);
	renderer = gtk_cell_renderer_toggle_new();
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(column),
					renderer, FALSE);
	gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(column),
					    renderer,
					    "active", COL_BTNACT,
					    "inconsistent", COL_BTNINC,
					    "visible", COL_BTNVIS,
					    "radio", COL_BTNRAD, शून्य);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(column),
					renderer, FALSE);
	gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(column),
					    renderer,
					    "text", COL_OPTION,
					    "foreground-gdk",
					    COL_COLOR, शून्य);

	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1,
						    "Name", renderer,
						    "text", COL_NAME,
						    "foreground-gdk",
						    COL_COLOR, शून्य);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1,
						    "N", renderer,
						    "text", COL_NO,
						    "foreground-gdk",
						    COL_COLOR, शून्य);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1,
						    "M", renderer,
						    "text", COL_MOD,
						    "foreground-gdk",
						    COL_COLOR, शून्य);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1,
						    "Y", renderer,
						    "text", COL_YES,
						    "foreground-gdk",
						    COL_COLOR, शून्य);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1,
						    "Value", renderer,
						    "text", COL_VALUE,
						    "editable",
						    COL_EDIT,
						    "foreground-gdk",
						    COL_COLOR, शून्य);
	g_संकेत_connect(G_OBJECT(renderer), "edited",
			 G_CALLBACK(renderer_edited), शून्य);

	column = gtk_tree_view_get_column(view, COL_NAME);
	gtk_tree_view_column_set_visible(column, show_name);
	column = gtk_tree_view_get_column(view, COL_NO);
	gtk_tree_view_column_set_visible(column, show_range);
	column = gtk_tree_view_get_column(view, COL_MOD);
	gtk_tree_view_column_set_visible(column, show_range);
	column = gtk_tree_view_get_column(view, COL_YES);
	gtk_tree_view_column_set_visible(column, show_range);
	column = gtk_tree_view_get_column(view, COL_VALUE);
	gtk_tree_view_column_set_visible(column, show_value);

	अगर (resizeable) अणु
		क्रम (i = 0; i < COL_VALUE; i++) अणु
			column = gtk_tree_view_get_column(view, i);
			gtk_tree_view_column_set_resizable(column, TRUE);
		पूर्ण
	पूर्ण

	sel = gtk_tree_view_get_selection(view);
	gtk_tree_selection_set_mode(sel, GTK_SELECTION_SINGLE);
पूर्ण


/* Utility Functions */


अटल व्योम text_insert_help(काष्ठा menu *menu)
अणु
	GtkTextBuffer *buffer;
	GtkTextIter start, end;
	स्थिर अक्षर *prompt = menu_get_prompt(menu);
	काष्ठा gstr help = str_new();

	menu_get_ext_help(menu, &help);

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_w));
	gtk_text_buffer_get_bounds(buffer, &start, &end);
	gtk_text_buffer_delete(buffer, &start, &end);
	gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_w), 15);

	gtk_text_buffer_get_end_iter(buffer, &end);
	gtk_text_buffer_insert_with_tags(buffer, &end, prompt, -1, tag1,
					 शून्य);
	gtk_text_buffer_insert_at_cursor(buffer, "\n\n", 2);
	gtk_text_buffer_get_end_iter(buffer, &end);
	gtk_text_buffer_insert_with_tags(buffer, &end, str_get(&help), -1, tag2,
					 शून्य);
	str_मुक्त(&help);
पूर्ण


अटल व्योम text_insert_msg(स्थिर अक्षर *title, स्थिर अक्षर *message)
अणु
	GtkTextBuffer *buffer;
	GtkTextIter start, end;
	स्थिर अक्षर *msg = message;

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_w));
	gtk_text_buffer_get_bounds(buffer, &start, &end);
	gtk_text_buffer_delete(buffer, &start, &end);
	gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_w), 15);

	gtk_text_buffer_get_end_iter(buffer, &end);
	gtk_text_buffer_insert_with_tags(buffer, &end, title, -1, tag1,
					 शून्य);
	gtk_text_buffer_insert_at_cursor(buffer, "\n\n", 2);
	gtk_text_buffer_get_end_iter(buffer, &end);
	gtk_text_buffer_insert_with_tags(buffer, &end, msg, -1, tag2,
					 शून्य);
पूर्ण


/* Main Winकरोws Callbacks */

व्योम on_save_activate(GtkMenuItem * menuitem, gpoपूर्णांकer user_data);
gboolean on_winकरोw1_delete_event(GtkWidget * widget, GdkEvent * event,
				 gpoपूर्णांकer user_data)
अणु
	GtkWidget *dialog, *label;
	gपूर्णांक result;

	अगर (!conf_get_changed())
		वापस FALSE;

	dialog = gtk_dialog_new_with_buttons("Warning !",
					     GTK_WINDOW(मुख्य_wnd),
					     (GtkDialogFlags)
					     (GTK_DIALOG_MODAL |
					      GTK_DIALOG_DESTROY_WITH_PARENT),
					     GTK_STOCK_OK,
					     GTK_RESPONSE_YES,
					     GTK_STOCK_NO,
					     GTK_RESPONSE_NO,
					     GTK_STOCK_CANCEL,
					     GTK_RESPONSE_CANCEL, शून्य);
	gtk_dialog_set_शेष_response(GTK_DIALOG(dialog),
					GTK_RESPONSE_CANCEL);

	label = gtk_label_new("\nSave configuration ?\n");
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), label);
	gtk_widget_show(label);

	result = gtk_dialog_run(GTK_DIALOG(dialog));
	चयन (result) अणु
	हाल GTK_RESPONSE_YES:
		on_save_activate(शून्य, शून्य);
		वापस FALSE;
	हाल GTK_RESPONSE_NO:
		वापस FALSE;
	हाल GTK_RESPONSE_CANCEL:
	हाल GTK_RESPONSE_DELETE_EVENT:
	शेष:
		gtk_widget_destroy(dialog);
		वापस TRUE;
	पूर्ण

	वापस FALSE;
पूर्ण


व्योम on_winकरोw1_destroy(GtkObject * object, gpoपूर्णांकer user_data)
अणु
	gtk_मुख्य_quit();
पूर्ण


व्योम
on_winकरोw1_size_request(GtkWidget * widget,
			GtkRequisition * requisition, gpoपूर्णांकer user_data)
अणु
	अटल gपूर्णांक old_h;
	gपूर्णांक w, h;

	अगर (widget->winकरोw == शून्य)
		gtk_winकरोw_get_शेष_size(GTK_WINDOW(मुख्य_wnd), &w, &h);
	अन्यथा
		gdk_winकरोw_get_size(widget->winकरोw, &w, &h);

	अगर (h == old_h)
		वापस;
	old_h = h;

	gtk_paned_set_position(GTK_PANED(vpaned), 2 * h / 3);
पूर्ण


/* Menu & Toolbar Callbacks */


अटल व्योम
load_filename(GtkFileSelection * file_selector, gpoपूर्णांकer user_data)
अणु
	स्थिर gअक्षर *fn;

	fn = gtk_file_selection_get_filename(GTK_खाता_SELECTION
					     (user_data));

	अगर (conf_पढ़ो(fn))
		text_insert_msg("Error", "Unable to load configuration !");
	अन्यथा
		display_tree(&rooपंचांगenu);
पूर्ण

व्योम on_load1_activate(GtkMenuItem * menuitem, gpoपूर्णांकer user_data)
अणु
	GtkWidget *fs;

	fs = gtk_file_selection_new("Load file...");
	g_संकेत_connect(GTK_OBJECT(GTK_खाता_SELECTION(fs)->ok_button),
			 "clicked",
			 G_CALLBACK(load_filename), (gpoपूर्णांकer) fs);
	g_संकेत_connect_swapped(GTK_OBJECT
				 (GTK_खाता_SELECTION(fs)->ok_button),
				 "clicked", G_CALLBACK(gtk_widget_destroy),
				 (gpoपूर्णांकer) fs);
	g_संकेत_connect_swapped(GTK_OBJECT
				 (GTK_खाता_SELECTION(fs)->cancel_button),
				 "clicked", G_CALLBACK(gtk_widget_destroy),
				 (gpoपूर्णांकer) fs);
	gtk_widget_show(fs);
पूर्ण


व्योम on_save_activate(GtkMenuItem * menuitem, gpoपूर्णांकer user_data)
अणु
	अगर (conf_ग_लिखो(शून्य))
		text_insert_msg("Error", "Unable to save configuration !");
	conf_ग_लिखो_स्वतःconf(0);
पूर्ण


अटल व्योम
store_filename(GtkFileSelection * file_selector, gpoपूर्णांकer user_data)
अणु
	स्थिर gअक्षर *fn;

	fn = gtk_file_selection_get_filename(GTK_खाता_SELECTION
					     (user_data));

	अगर (conf_ग_लिखो(fn))
		text_insert_msg("Error", "Unable to save configuration !");

	gtk_widget_destroy(GTK_WIDGET(user_data));
पूर्ण

व्योम on_save_as1_activate(GtkMenuItem * menuitem, gpoपूर्णांकer user_data)
अणु
	GtkWidget *fs;

	fs = gtk_file_selection_new("Save file as...");
	g_संकेत_connect(GTK_OBJECT(GTK_खाता_SELECTION(fs)->ok_button),
			 "clicked",
			 G_CALLBACK(store_filename), (gpoपूर्णांकer) fs);
	g_संकेत_connect_swapped(GTK_OBJECT
				 (GTK_खाता_SELECTION(fs)->ok_button),
				 "clicked", G_CALLBACK(gtk_widget_destroy),
				 (gpoपूर्णांकer) fs);
	g_संकेत_connect_swapped(GTK_OBJECT
				 (GTK_खाता_SELECTION(fs)->cancel_button),
				 "clicked", G_CALLBACK(gtk_widget_destroy),
				 (gpoपूर्णांकer) fs);
	gtk_widget_show(fs);
पूर्ण


व्योम on_quit1_activate(GtkMenuItem * menuitem, gpoपूर्णांकer user_data)
अणु
	अगर (!on_winकरोw1_delete_event(शून्य, शून्य, शून्य))
		gtk_widget_destroy(GTK_WIDGET(मुख्य_wnd));
पूर्ण


व्योम on_show_name1_activate(GtkMenuItem * menuitem, gpoपूर्णांकer user_data)
अणु
	GtkTreeViewColumn *col;

	show_name = GTK_CHECK_MENU_ITEM(menuitem)->active;
	col = gtk_tree_view_get_column(GTK_TREE_VIEW(tree2_w), COL_NAME);
	अगर (col)
		gtk_tree_view_column_set_visible(col, show_name);
पूर्ण


व्योम on_show_range1_activate(GtkMenuItem * menuitem, gpoपूर्णांकer user_data)
अणु
	GtkTreeViewColumn *col;

	show_range = GTK_CHECK_MENU_ITEM(menuitem)->active;
	col = gtk_tree_view_get_column(GTK_TREE_VIEW(tree2_w), COL_NO);
	अगर (col)
		gtk_tree_view_column_set_visible(col, show_range);
	col = gtk_tree_view_get_column(GTK_TREE_VIEW(tree2_w), COL_MOD);
	अगर (col)
		gtk_tree_view_column_set_visible(col, show_range);
	col = gtk_tree_view_get_column(GTK_TREE_VIEW(tree2_w), COL_YES);
	अगर (col)
		gtk_tree_view_column_set_visible(col, show_range);

पूर्ण


व्योम on_show_data1_activate(GtkMenuItem * menuitem, gpoपूर्णांकer user_data)
अणु
	GtkTreeViewColumn *col;

	show_value = GTK_CHECK_MENU_ITEM(menuitem)->active;
	col = gtk_tree_view_get_column(GTK_TREE_VIEW(tree2_w), COL_VALUE);
	अगर (col)
		gtk_tree_view_column_set_visible(col, show_value);
पूर्ण


व्योम
on_set_option_mode1_activate(GtkMenuItem *menuitem, gpoपूर्णांकer user_data)
अणु
	opt_mode = OPT_NORMAL;
	gtk_tree_store_clear(tree2);
	display_tree(&rooपंचांगenu);	/* instead of update_tree to speed-up */
पूर्ण


व्योम
on_set_option_mode2_activate(GtkMenuItem *menuitem, gpoपूर्णांकer user_data)
अणु
	opt_mode = OPT_ALL;
	gtk_tree_store_clear(tree2);
	display_tree(&rooपंचांगenu);	/* instead of update_tree to speed-up */
पूर्ण


व्योम
on_set_option_mode3_activate(GtkMenuItem *menuitem, gpoपूर्णांकer user_data)
अणु
	opt_mode = OPT_PROMPT;
	gtk_tree_store_clear(tree2);
	display_tree(&rooपंचांगenu);	/* instead of update_tree to speed-up */
पूर्ण


व्योम on_पूर्णांकroduction1_activate(GtkMenuItem * menuitem, gpoपूर्णांकer user_data)
अणु
	GtkWidget *dialog;
	स्थिर gअक्षर *पूर्णांकro_text =
	    "Welcome to gkc, the GTK+ graphical configuration tool\n"
	    "For each option, a blank box indicates the feature is disabled, a\n"
	    "check indicates it is enabled, and a dot indicates that it is to\n"
	    "be compiled as a module.  Clicking on the box will cycle through the three states.\n"
	    "\n"
	    "If you do not see an option (e.g., a device driver) that you\n"
	    "believe should be present, try turning on Show All Options\n"
	    "under the Options menu.\n"
	    "Although there is no cross reference yet to help you figure out\n"
	    "what other options must be enabled to support the option you\n"
	    "are interested in, you can still view the help of a grayed-out\n"
	    "option.\n"
	    "\n"
	    "Toggling Show Debug Info under the Options menu will show \n"
	    "the dependencies, which you can then match by examining other options.";

	dialog = gtk_message_dialog_new(GTK_WINDOW(मुख्य_wnd),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_INFO,
					GTK_BUTTONS_CLOSE, "%s", पूर्णांकro_text);
	g_संकेत_connect_swapped(GTK_OBJECT(dialog), "response",
				 G_CALLBACK(gtk_widget_destroy),
				 GTK_OBJECT(dialog));
	gtk_widget_show_all(dialog);
पूर्ण


व्योम on_about1_activate(GtkMenuItem * menuitem, gpoपूर्णांकer user_data)
अणु
	GtkWidget *dialog;
	स्थिर gअक्षर *about_text =
	    "gkc is copyright (c) 2002 Romain Lievin <roms@lpg.ticalc.org>.\n"
	      "Based on the source code from Roman Zippel.\n";

	dialog = gtk_message_dialog_new(GTK_WINDOW(मुख्य_wnd),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_INFO,
					GTK_BUTTONS_CLOSE, "%s", about_text);
	g_संकेत_connect_swapped(GTK_OBJECT(dialog), "response",
				 G_CALLBACK(gtk_widget_destroy),
				 GTK_OBJECT(dialog));
	gtk_widget_show_all(dialog);
पूर्ण


व्योम on_license1_activate(GtkMenuItem * menuitem, gpoपूर्णांकer user_data)
अणु
	GtkWidget *dialog;
	स्थिर gअक्षर *license_text =
	    "gkc is released under the terms of the GNU GPL v2.\n"
	      "For more information, please see the source code or\n"
	      "visit http://www.fsf.org/licenses/licenses.html\n";

	dialog = gtk_message_dialog_new(GTK_WINDOW(मुख्य_wnd),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_INFO,
					GTK_BUTTONS_CLOSE, "%s", license_text);
	g_संकेत_connect_swapped(GTK_OBJECT(dialog), "response",
				 G_CALLBACK(gtk_widget_destroy),
				 GTK_OBJECT(dialog));
	gtk_widget_show_all(dialog);
पूर्ण


व्योम on_back_clicked(GtkButton * button, gpoपूर्णांकer user_data)
अणु
	क्रमागत prop_type ptype;

	current = current->parent;
	ptype = current->prompt ? current->prompt->type : P_UNKNOWN;
	अगर (ptype != P_MENU)
		current = current->parent;
	display_tree_part();

	अगर (current == &rooपंचांगenu)
		gtk_widget_set_sensitive(back_btn, FALSE);
पूर्ण


व्योम on_load_clicked(GtkButton * button, gpoपूर्णांकer user_data)
अणु
	on_load1_activate(शून्य, user_data);
पूर्ण


व्योम on_single_clicked(GtkButton * button, gpoपूर्णांकer user_data)
अणु
	view_mode = SINGLE_VIEW;
	gtk_widget_hide(tree1_w);
	current = &rooपंचांगenu;
	display_tree_part();
पूर्ण


व्योम on_split_clicked(GtkButton * button, gpoपूर्णांकer user_data)
अणु
	gपूर्णांक w, h;
	view_mode = SPLIT_VIEW;
	gtk_widget_show(tree1_w);
	gtk_winकरोw_get_शेष_size(GTK_WINDOW(मुख्य_wnd), &w, &h);
	gtk_paned_set_position(GTK_PANED(hpaned), w / 2);
	अगर (tree2)
		gtk_tree_store_clear(tree2);
	display_list();

	/* Disable back btn, like in full mode. */
	gtk_widget_set_sensitive(back_btn, FALSE);
पूर्ण


व्योम on_full_clicked(GtkButton * button, gpoपूर्णांकer user_data)
अणु
	view_mode = FULL_VIEW;
	gtk_widget_hide(tree1_w);
	अगर (tree2)
		gtk_tree_store_clear(tree2);
	display_tree(&rooपंचांगenu);
	gtk_widget_set_sensitive(back_btn, FALSE);
पूर्ण


व्योम on_collapse_clicked(GtkButton * button, gpoपूर्णांकer user_data)
अणु
	gtk_tree_view_collapse_all(GTK_TREE_VIEW(tree2_w));
पूर्ण


व्योम on_expand_clicked(GtkButton * button, gpoपूर्णांकer user_data)
अणु
	gtk_tree_view_expand_all(GTK_TREE_VIEW(tree2_w));
पूर्ण


/* CTree Callbacks */

/* Change hex/पूर्णांक/string value in the cell */
अटल व्योम renderer_edited(GtkCellRendererText * cell,
			    स्थिर gअक्षर * path_string,
			    स्थिर gअक्षर * new_text, gpoपूर्णांकer user_data)
अणु
	GtkTreePath *path = gtk_tree_path_new_from_string(path_string);
	GtkTreeIter iter;
	स्थिर अक्षर *old_def, *new_def;
	काष्ठा menu *menu;
	काष्ठा symbol *sym;

	अगर (!gtk_tree_model_get_iter(model2, &iter, path))
		वापस;

	gtk_tree_model_get(model2, &iter, COL_MENU, &menu, -1);
	sym = menu->sym;

	gtk_tree_model_get(model2, &iter, COL_VALUE, &old_def, -1);
	new_def = new_text;

	sym_set_string_value(sym, new_def);

	update_tree(&rooपंचांगenu, शून्य);

	gtk_tree_path_मुक्त(path);
पूर्ण

/* Change the value of a symbol and update the tree */
अटल व्योम change_sym_value(काष्ठा menu *menu, gपूर्णांक col)
अणु
	काष्ठा symbol *sym = menu->sym;
	tristate newval;

	अगर (!sym)
		वापस;

	अगर (col == COL_NO)
		newval = no;
	अन्यथा अगर (col == COL_MOD)
		newval = mod;
	अन्यथा अगर (col == COL_YES)
		newval = yes;
	अन्यथा
		वापस;

	चयन (sym_get_type(sym)) अणु
	हाल S_BOOLEAN:
	हाल S_TRISTATE:
		अगर (!sym_tristate_within_range(sym, newval))
			newval = yes;
		sym_set_tristate_value(sym, newval);
		अगर (view_mode == FULL_VIEW)
			update_tree(&rooपंचांगenu, शून्य);
		अन्यथा अगर (view_mode == SPLIT_VIEW) अणु
			update_tree(browsed, शून्य);
			display_list();
		पूर्ण
		अन्यथा अगर (view_mode == SINGLE_VIEW)
			display_tree_part();	//fixme: keep exp/coll
		अवरोध;
	हाल S_INT:
	हाल S_HEX:
	हाल S_STRING:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम toggle_sym_value(काष्ठा menu *menu)
अणु
	अगर (!menu->sym)
		वापस;

	sym_toggle_tristate_value(menu->sym);
	अगर (view_mode == FULL_VIEW)
		update_tree(&rooपंचांगenu, शून्य);
	अन्यथा अगर (view_mode == SPLIT_VIEW) अणु
		update_tree(browsed, शून्य);
		display_list();
	पूर्ण
	अन्यथा अगर (view_mode == SINGLE_VIEW)
		display_tree_part();	//fixme: keep exp/coll
पूर्ण

अटल gपूर्णांक column2index(GtkTreeViewColumn * column)
अणु
	gपूर्णांक i;

	क्रम (i = 0; i < COL_NUMBER; i++) अणु
		GtkTreeViewColumn *col;

		col = gtk_tree_view_get_column(GTK_TREE_VIEW(tree2_w), i);
		अगर (col == column)
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण


/* User click: update choice (full) or goes करोwn (single) */
gboolean
on_treeview2_button_press_event(GtkWidget * widget,
				GdkEventButton * event, gpoपूर्णांकer user_data)
अणु
	GtkTreeView *view = GTK_TREE_VIEW(widget);
	GtkTreePath *path;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	काष्ठा menu *menu;
	gपूर्णांक col;

#अगर GTK_CHECK_VERSION(2,1,4) // bug in ctree with earlier version of GTK
	gपूर्णांक tx = (gपूर्णांक) event->x;
	gपूर्णांक ty = (gपूर्णांक) event->y;
	gपूर्णांक cx, cy;

	gtk_tree_view_get_path_at_pos(view, tx, ty, &path, &column, &cx,
				      &cy);
#अन्यथा
	gtk_tree_view_get_cursor(view, &path, &column);
#पूर्ण_अगर
	अगर (path == शून्य)
		वापस FALSE;

	अगर (!gtk_tree_model_get_iter(model2, &iter, path))
		वापस FALSE;
	gtk_tree_model_get(model2, &iter, COL_MENU, &menu, -1);

	col = column2index(column);
	अगर (event->type == GDK_2BUTTON_PRESS) अणु
		क्रमागत prop_type ptype;
		ptype = menu->prompt ? menu->prompt->type : P_UNKNOWN;

		अगर (ptype == P_MENU && view_mode != FULL_VIEW && col == COL_OPTION) अणु
			// goes करोwn पूर्णांकo menu
			current = menu;
			display_tree_part();
			gtk_widget_set_sensitive(back_btn, TRUE);
		पूर्ण अन्यथा अगर (col == COL_OPTION) अणु
			toggle_sym_value(menu);
			gtk_tree_view_expand_row(view, path, TRUE);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (col == COL_VALUE) अणु
			toggle_sym_value(menu);
			gtk_tree_view_expand_row(view, path, TRUE);
		पूर्ण अन्यथा अगर (col == COL_NO || col == COL_MOD
			   || col == COL_YES) अणु
			change_sym_value(menu, col);
			gtk_tree_view_expand_row(view, path, TRUE);
		पूर्ण
	पूर्ण

	वापस FALSE;
पूर्ण

/* Key pressed: update choice */
gboolean
on_treeview2_key_press_event(GtkWidget * widget,
			     GdkEventKey * event, gpoपूर्णांकer user_data)
अणु
	GtkTreeView *view = GTK_TREE_VIEW(widget);
	GtkTreePath *path;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	काष्ठा menu *menu;
	gपूर्णांक col;

	gtk_tree_view_get_cursor(view, &path, &column);
	अगर (path == शून्य)
		वापस FALSE;

	अगर (event->keyval == GDK_space) अणु
		अगर (gtk_tree_view_row_expanded(view, path))
			gtk_tree_view_collapse_row(view, path);
		अन्यथा
			gtk_tree_view_expand_row(view, path, FALSE);
		वापस TRUE;
	पूर्ण
	अगर (event->keyval == GDK_KP_Enter) अणु
	पूर्ण
	अगर (widget == tree1_w)
		वापस FALSE;

	gtk_tree_model_get_iter(model2, &iter, path);
	gtk_tree_model_get(model2, &iter, COL_MENU, &menu, -1);

	अगर (!strहालcmp(event->string, "n"))
		col = COL_NO;
	अन्यथा अगर (!strहालcmp(event->string, "m"))
		col = COL_MOD;
	अन्यथा अगर (!strहालcmp(event->string, "y"))
		col = COL_YES;
	अन्यथा
		col = -1;
	change_sym_value(menu, col);

	वापस FALSE;
पूर्ण


/* Row selection changed: update help */
व्योम
on_treeview2_cursor_changed(GtkTreeView * treeview, gpoपूर्णांकer user_data)
अणु
	GtkTreeSelection *selection;
	GtkTreeIter iter;
	काष्ठा menu *menu;

	selection = gtk_tree_view_get_selection(treeview);
	अगर (gtk_tree_selection_get_selected(selection, &model2, &iter)) अणु
		gtk_tree_model_get(model2, &iter, COL_MENU, &menu, -1);
		text_insert_help(menu);
	पूर्ण
पूर्ण


/* User click: display sub-tree in the right frame. */
gboolean
on_treeview1_button_press_event(GtkWidget * widget,
				GdkEventButton * event, gpoपूर्णांकer user_data)
अणु
	GtkTreeView *view = GTK_TREE_VIEW(widget);
	GtkTreePath *path;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	काष्ठा menu *menu;

	gपूर्णांक tx = (gपूर्णांक) event->x;
	gपूर्णांक ty = (gपूर्णांक) event->y;
	gपूर्णांक cx, cy;

	gtk_tree_view_get_path_at_pos(view, tx, ty, &path, &column, &cx,
				      &cy);
	अगर (path == शून्य)
		वापस FALSE;

	gtk_tree_model_get_iter(model1, &iter, path);
	gtk_tree_model_get(model1, &iter, COL_MENU, &menu, -1);

	अगर (event->type == GDK_2BUTTON_PRESS) अणु
		toggle_sym_value(menu);
		current = menu;
		display_tree_part();
	पूर्ण अन्यथा अणु
		browsed = menu;
		display_tree_part();
	पूर्ण

	gtk_widget_realize(tree2_w);
	gtk_tree_view_set_cursor(view, path, शून्य, FALSE);
	gtk_widget_grab_focus(tree2_w);

	वापस FALSE;
पूर्ण


/* Fill a row of strings */
अटल gअक्षर **fill_row(काष्ठा menu *menu)
अणु
	अटल gअक्षर *row[COL_NUMBER];
	काष्ठा symbol *sym = menu->sym;
	स्थिर अक्षर *def;
	पूर्णांक stype;
	tristate val;
	क्रमागत prop_type ptype;
	पूर्णांक i;

	क्रम (i = COL_OPTION; i <= COL_COLOR; i++)
		g_मुक्त(row[i]);
	bzero(row, माप(row));

	ptype = menu->prompt ? menu->prompt->type : P_UNKNOWN;

	row[COL_OPTION] =
	    g_strdup_म_लिखो("%s %s %s %s",
			    ptype == P_COMMENT ? "***" : "",
			    menu_get_prompt(menu),
			    ptype == P_COMMENT ? "***" : "",
			    sym && !sym_has_value(sym) ? "(NEW)" : "");

	अगर (opt_mode == OPT_ALL && !menu_is_visible(menu))
		row[COL_COLOR] = g_strdup("DarkGray");
	अन्यथा अगर (opt_mode == OPT_PROMPT &&
			menu_has_prompt(menu) && !menu_is_visible(menu))
		row[COL_COLOR] = g_strdup("DarkGray");
	अन्यथा
		row[COL_COLOR] = g_strdup("Black");

	चयन (ptype) अणु
	हाल P_MENU:
		row[COL_PIXBUF] = (gअक्षर *) xpm_menu;
		अगर (view_mode == SINGLE_VIEW)
			row[COL_PIXVIS] = GINT_TO_POINTER(TRUE);
		row[COL_BTNVIS] = GINT_TO_POINTER(FALSE);
		अवरोध;
	हाल P_COMMENT:
		row[COL_PIXBUF] = (gअक्षर *) xpm_व्योम;
		row[COL_PIXVIS] = GINT_TO_POINTER(FALSE);
		row[COL_BTNVIS] = GINT_TO_POINTER(FALSE);
		अवरोध;
	शेष:
		row[COL_PIXBUF] = (gअक्षर *) xpm_व्योम;
		row[COL_PIXVIS] = GINT_TO_POINTER(FALSE);
		row[COL_BTNVIS] = GINT_TO_POINTER(TRUE);
		अवरोध;
	पूर्ण

	अगर (!sym)
		वापस row;
	row[COL_NAME] = g_strdup(sym->name);

	sym_calc_value(sym);
	sym->flags &= ~SYMBOL_CHANGED;

	अगर (sym_is_choice(sym)) अणु	// parse childs क्रम getting final value
		काष्ठा menu *child;
		काष्ठा symbol *def_sym = sym_get_choice_value(sym);
		काष्ठा menu *def_menu = शून्य;

		row[COL_BTNVIS] = GINT_TO_POINTER(FALSE);

		क्रम (child = menu->list; child; child = child->next) अणु
			अगर (menu_is_visible(child)
			    && child->sym == def_sym)
				def_menu = child;
		पूर्ण

		अगर (def_menu)
			row[COL_VALUE] =
			    g_strdup(menu_get_prompt(def_menu));
	पूर्ण
	अगर (sym->flags & SYMBOL_CHOICEVAL)
		row[COL_BTNRAD] = GINT_TO_POINTER(TRUE);

	stype = sym_get_type(sym);
	चयन (stype) अणु
	हाल S_BOOLEAN:
		अगर (GPOINTER_TO_INT(row[COL_PIXVIS]) == FALSE)
			row[COL_BTNVIS] = GINT_TO_POINTER(TRUE);
		अगर (sym_is_choice(sym))
			अवरोध;
		/* fall through */
	हाल S_TRISTATE:
		val = sym_get_tristate_value(sym);
		चयन (val) अणु
		हाल no:
			row[COL_NO] = g_strdup("N");
			row[COL_VALUE] = g_strdup("N");
			row[COL_BTNACT] = GINT_TO_POINTER(FALSE);
			row[COL_BTNINC] = GINT_TO_POINTER(FALSE);
			अवरोध;
		हाल mod:
			row[COL_MOD] = g_strdup("M");
			row[COL_VALUE] = g_strdup("M");
			row[COL_BTNINC] = GINT_TO_POINTER(TRUE);
			अवरोध;
		हाल yes:
			row[COL_YES] = g_strdup("Y");
			row[COL_VALUE] = g_strdup("Y");
			row[COL_BTNACT] = GINT_TO_POINTER(TRUE);
			row[COL_BTNINC] = GINT_TO_POINTER(FALSE);
			अवरोध;
		पूर्ण

		अगर (val != no && sym_tristate_within_range(sym, no))
			row[COL_NO] = g_strdup("_");
		अगर (val != mod && sym_tristate_within_range(sym, mod))
			row[COL_MOD] = g_strdup("_");
		अगर (val != yes && sym_tristate_within_range(sym, yes))
			row[COL_YES] = g_strdup("_");
		अवरोध;
	हाल S_INT:
	हाल S_HEX:
	हाल S_STRING:
		def = sym_get_string_value(sym);
		row[COL_VALUE] = g_strdup(def);
		row[COL_EDIT] = GINT_TO_POINTER(TRUE);
		row[COL_BTNVIS] = GINT_TO_POINTER(FALSE);
		अवरोध;
	पूर्ण

	वापस row;
पूर्ण


/* Set the node content with a row of strings */
अटल व्योम set_node(GtkTreeIter * node, काष्ठा menu *menu, gअक्षर ** row)
अणु
	GdkColor color;
	gboolean success;
	GdkPixbuf *pix;

	pix = gdk_pixbuf_new_from_xpm_data((स्थिर अक्षर **)
					   row[COL_PIXBUF]);

	gdk_color_parse(row[COL_COLOR], &color);
	gdk_colormap_alloc_colors(gdk_colormap_get_प्रणाली(), &color, 1,
				  FALSE, FALSE, &success);

	gtk_tree_store_set(tree, node,
			   COL_OPTION, row[COL_OPTION],
			   COL_NAME, row[COL_NAME],
			   COL_NO, row[COL_NO],
			   COL_MOD, row[COL_MOD],
			   COL_YES, row[COL_YES],
			   COL_VALUE, row[COL_VALUE],
			   COL_MENU, (gpoपूर्णांकer) menu,
			   COL_COLOR, &color,
			   COL_EDIT, GPOINTER_TO_INT(row[COL_EDIT]),
			   COL_PIXBUF, pix,
			   COL_PIXVIS, GPOINTER_TO_INT(row[COL_PIXVIS]),
			   COL_BTNVIS, GPOINTER_TO_INT(row[COL_BTNVIS]),
			   COL_BTNACT, GPOINTER_TO_INT(row[COL_BTNACT]),
			   COL_BTNINC, GPOINTER_TO_INT(row[COL_BTNINC]),
			   COL_BTNRAD, GPOINTER_TO_INT(row[COL_BTNRAD]),
			   -1);

	g_object_unref(pix);
पूर्ण


/* Add a node to the tree */
अटल व्योम place_node(काष्ठा menu *menu, अक्षर **row)
अणु
	GtkTreeIter *parent = parents[indent - 1];
	GtkTreeIter *node = parents[indent];

	gtk_tree_store_append(tree, node, parent);
	set_node(node, menu, row);
पूर्ण


/* Find a node in the GTK+ tree */
अटल GtkTreeIter found;

/*
 * Find a menu in the GtkTree starting at parent.
 */
अटल GtkTreeIter *gtktree_iter_find_node(GtkTreeIter *parent,
					   काष्ठा menu *tofind)
अणु
	GtkTreeIter iter;
	GtkTreeIter *child = &iter;
	gboolean valid;
	GtkTreeIter *ret;

	valid = gtk_tree_model_iter_children(model2, child, parent);
	जबतक (valid) अणु
		काष्ठा menu *menu;

		gtk_tree_model_get(model2, child, 6, &menu, -1);

		अगर (menu == tofind) अणु
			स_नकल(&found, child, माप(GtkTreeIter));
			वापस &found;
		पूर्ण

		ret = gtktree_iter_find_node(child, tofind);
		अगर (ret)
			वापस ret;

		valid = gtk_tree_model_iter_next(model2, child);
	पूर्ण

	वापस शून्य;
पूर्ण


/*
 * Update the tree by adding/removing entries
 * Does not change other nodes
 */
अटल व्योम update_tree(काष्ठा menu *src, GtkTreeIter * dst)
अणु
	काष्ठा menu *child1;
	GtkTreeIter iter, पंचांगp;
	GtkTreeIter *child2 = &iter;
	gboolean valid;
	GtkTreeIter *sibling;
	काष्ठा symbol *sym;
	काष्ठा menu *menu1, *menu2;

	अगर (src == &rooपंचांगenu)
		indent = 1;

	valid = gtk_tree_model_iter_children(model2, child2, dst);
	क्रम (child1 = src->list; child1; child1 = child1->next) अणु

		sym = child1->sym;

	      reparse:
		menu1 = child1;
		अगर (valid)
			gtk_tree_model_get(model2, child2, COL_MENU,
					   &menu2, -1);
		अन्यथा
			menu2 = शून्य;	// क्रमce adding of a first child

#अगर_घोषित DEBUG
		म_लिखो("%*c%s | %s\n", indent, ' ',
		       menu1 ? menu_get_prompt(menu1) : "nil",
		       menu2 ? menu_get_prompt(menu2) : "nil");
#पूर्ण_अगर

		अगर ((opt_mode == OPT_NORMAL && !menu_is_visible(child1)) ||
		    (opt_mode == OPT_PROMPT && !menu_has_prompt(child1)) ||
		    (opt_mode == OPT_ALL    && !menu_get_prompt(child1))) अणु

			/* हटाओ node */
			अगर (gtktree_iter_find_node(dst, menu1) != शून्य) अणु
				स_नकल(&पंचांगp, child2, माप(GtkTreeIter));
				valid = gtk_tree_model_iter_next(model2,
								 child2);
				gtk_tree_store_हटाओ(tree2, &पंचांगp);
				अगर (!valid)
					वापस;		/* next parent */
				अन्यथा
					जाओ reparse;	/* next child */
			पूर्ण अन्यथा
				जारी;
		पूर्ण

		अगर (menu1 != menu2) अणु
			अगर (gtktree_iter_find_node(dst, menu1) == शून्य) अणु	// add node
				अगर (!valid && !menu2)
					sibling = शून्य;
				अन्यथा
					sibling = child2;
				gtk_tree_store_insert_beक्रमe(tree2,
							     child2,
							     dst, sibling);
				set_node(child2, menu1, fill_row(menu1));
				अगर (menu2 == शून्य)
					valid = TRUE;
			पूर्ण अन्यथा अणु	// हटाओ node
				स_नकल(&पंचांगp, child2, माप(GtkTreeIter));
				valid = gtk_tree_model_iter_next(model2,
								 child2);
				gtk_tree_store_हटाओ(tree2, &पंचांगp);
				अगर (!valid)
					वापस;	// next parent
				अन्यथा
					जाओ reparse;	// next child
			पूर्ण
		पूर्ण अन्यथा अगर (sym && (sym->flags & SYMBOL_CHANGED)) अणु
			set_node(child2, menu1, fill_row(menu1));
		पूर्ण

		indent++;
		update_tree(child1, child2);
		indent--;

		valid = gtk_tree_model_iter_next(model2, child2);
	पूर्ण
पूर्ण


/* Display the whole tree (single/split/full view) */
अटल व्योम display_tree(काष्ठा menu *menu)
अणु
	काष्ठा symbol *sym;
	काष्ठा property *prop;
	काष्ठा menu *child;
	क्रमागत prop_type ptype;

	अगर (menu == &rooपंचांगenu) अणु
		indent = 1;
		current = &rooपंचांगenu;
	पूर्ण

	क्रम (child = menu->list; child; child = child->next) अणु
		prop = child->prompt;
		sym = child->sym;
		ptype = prop ? prop->type : P_UNKNOWN;

		अगर (sym)
			sym->flags &= ~SYMBOL_CHANGED;

		अगर ((view_mode == SPLIT_VIEW)
		    && !(child->flags & MENU_ROOT) && (tree == tree1))
			जारी;

		अगर ((view_mode == SPLIT_VIEW) && (child->flags & MENU_ROOT)
		    && (tree == tree2))
			जारी;

		अगर ((opt_mode == OPT_NORMAL && menu_is_visible(child)) ||
		    (opt_mode == OPT_PROMPT && menu_has_prompt(child)) ||
		    (opt_mode == OPT_ALL    && menu_get_prompt(child)))
			place_node(child, fill_row(child));
#अगर_घोषित DEBUG
		म_लिखो("%*c%s: ", indent, ' ', menu_get_prompt(child));
		म_लिखो("%s", child->flags & MENU_ROOT ? "rootmenu | " : "");
		म_लिखो("%s", prop_get_type_name(ptype));
		म_लिखो(" | ");
		अगर (sym) अणु
			म_लिखो("%s", sym_type_name(sym->type));
			म_लिखो(" | ");
			म_लिखो("%s", dbg_sym_flags(sym->flags));
			म_लिखो("\n");
		पूर्ण अन्यथा
			म_लिखो("\n");
#पूर्ण_अगर
		अगर ((view_mode != FULL_VIEW) && (ptype == P_MENU)
		    && (tree == tree2))
			जारी;
/*
		अगर (((menu != &rooपंचांगenu) && !(menu->flags & MENU_ROOT))
		    || (view_mode == FULL_VIEW)
		    || (view_mode == SPLIT_VIEW))*/

		/* Change paned position अगर the view is not in 'split mode' */
		अगर (view_mode == SINGLE_VIEW || view_mode == FULL_VIEW) अणु
			gtk_paned_set_position(GTK_PANED(hpaned), 0);
		पूर्ण

		अगर (((view_mode == SINGLE_VIEW) && (menu->flags & MENU_ROOT))
		    || (view_mode == FULL_VIEW)
		    || (view_mode == SPLIT_VIEW)) अणु
			indent++;
			display_tree(child);
			indent--;
		पूर्ण
	पूर्ण
पूर्ण

/* Display a part of the tree starting at current node (single/split view) */
अटल व्योम display_tree_part(व्योम)
अणु
	अगर (tree2)
		gtk_tree_store_clear(tree2);
	अगर (view_mode == SINGLE_VIEW)
		display_tree(current);
	अन्यथा अगर (view_mode == SPLIT_VIEW)
		display_tree(browsed);
	gtk_tree_view_expand_all(GTK_TREE_VIEW(tree2_w));
पूर्ण

/* Display the list in the left frame (split view) */
अटल व्योम display_list(व्योम)
अणु
	अगर (tree1)
		gtk_tree_store_clear(tree1);

	tree = tree1;
	display_tree(&rooपंचांगenu);
	gtk_tree_view_expand_all(GTK_TREE_VIEW(tree1_w));
	tree = tree2;
पूर्ण

अटल व्योम fixup_rooपंचांगenu(काष्ठा menu *menu)
अणु
	काष्ठा menu *child;
	अटल पूर्णांक menu_cnt = 0;

	menu->flags |= MENU_ROOT;
	क्रम (child = menu->list; child; child = child->next) अणु
		अगर (child->prompt && child->prompt->type == P_MENU) अणु
			menu_cnt++;
			fixup_rooपंचांगenu(child);
			menu_cnt--;
		पूर्ण अन्यथा अगर (!menu_cnt)
			fixup_rooपंचांगenu(child);
	पूर्ण
पूर्ण


/* Main */
पूर्णांक मुख्य(पूर्णांक ac, अक्षर *av[])
अणु
	स्थिर अक्षर *name;
	अक्षर *env;
	gअक्षर *glade_file;

	/* GTK stuffs */
	gtk_set_locale();
	gtk_init(&ac, &av);
	glade_init();

	/* Determine GUI path */
	env = दो_पर्या(SRCTREE);
	अगर (env)
		glade_file = g_strconcat(env, "/scripts/kconfig/gconf.glade", शून्य);
	अन्यथा अगर (av[0][0] == '/')
		glade_file = g_strconcat(av[0], ".glade", शून्य);
	अन्यथा
		glade_file = g_strconcat(g_get_current_dir(), "/", av[0], ".glade", शून्य);

	/* Conf stuffs */
	अगर (ac > 1 && av[1][0] == '-') अणु
		चयन (av[1][1]) अणु
		हाल 'a':
			//showAll = 1;
			अवरोध;
		हाल 's':
			conf_set_message_callback(शून्य);
			अवरोध;
		हाल 'h':
		हाल '?':
			म_लिखो("%s [-s] <config>\n", av[0]);
			निकास(0);
		पूर्ण
		name = av[2];
	पूर्ण अन्यथा
		name = av[1];

	conf_parse(name);
	fixup_rooपंचांगenu(&rooपंचांगenu);
	conf_पढ़ो(शून्य);

	/* Load the पूर्णांकerface and connect संकेतs */
	init_मुख्य_winकरोw(glade_file);
	init_tree_model();
	init_left_tree();
	init_right_tree();

	चयन (view_mode) अणु
	हाल SINGLE_VIEW:
		display_tree_part();
		अवरोध;
	हाल SPLIT_VIEW:
		display_list();
		अवरोध;
	हाल FULL_VIEW:
		display_tree(&rooपंचांगenu);
		अवरोध;
	पूर्ण

	gtk_मुख्य();

	वापस 0;
पूर्ण

अटल व्योम conf_changed(व्योम)
अणु
	bool changed = conf_get_changed();
	gtk_widget_set_sensitive(save_btn, changed);
	gtk_widget_set_sensitive(save_menu_item, changed);
पूर्ण
