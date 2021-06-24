<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "../evsel.h"
#समावेश "../sort.h"
#समावेश "../hist.h"
#समावेश "../helpline.h"
#समावेश "gtk.h"

#समावेश <संकेत.स>

व्योम perf_gtk__संकेत(पूर्णांक sig)
अणु
	perf_gtk__निकास(false);
	pसंकेत(sig, "perf");
पूर्ण

व्योम perf_gtk__resize_winकरोw(GtkWidget *winकरोw)
अणु
	GdkRectangle rect;
	GdkScreen *screen;
	पूर्णांक monitor;
	पूर्णांक height;
	पूर्णांक width;

	screen = gtk_widget_get_screen(winकरोw);

	monitor = gdk_screen_get_monitor_at_winकरोw(screen, winकरोw->winकरोw);

	gdk_screen_get_monitor_geometry(screen, monitor, &rect);

	width	= rect.width * 3 / 4;
	height	= rect.height * 3 / 4;

	gtk_winकरोw_resize(GTK_WINDOW(winकरोw), width, height);
पूर्ण

स्थिर अक्षर *perf_gtk__get_percent_color(द्विगुन percent)
अणु
	अगर (percent >= MIN_RED)
		वापस "<span fgcolor='red'>";
	अगर (percent >= MIN_GREEN)
		वापस "<span fgcolor='dark green'>";
	वापस शून्य;
पूर्ण

#अगर_घोषित HAVE_GTK_INFO_BAR_SUPPORT
GtkWidget *perf_gtk__setup_info_bar(व्योम)
अणु
	GtkWidget *info_bar;
	GtkWidget *label;
	GtkWidget *content_area;

	info_bar = gtk_info_bar_new();
	gtk_widget_set_no_show_all(info_bar, TRUE);

	label = gtk_label_new("");
	gtk_widget_show(label);

	content_area = gtk_info_bar_get_content_area(GTK_INFO_BAR(info_bar));
	gtk_container_add(GTK_CONTAINER(content_area), label);

	gtk_info_bar_add_button(GTK_INFO_BAR(info_bar), GTK_STOCK_OK,
				GTK_RESPONSE_OK);
	g_संकेत_connect(info_bar, "response",
			 G_CALLBACK(gtk_widget_hide), शून्य);

	pgctx->info_bar = info_bar;
	pgctx->message_label = label;

	वापस info_bar;
पूर्ण
#पूर्ण_अगर

GtkWidget *perf_gtk__setup_statusbar(व्योम)
अणु
	GtkWidget *stbar;
	अचिन्हित ctxid;

	stbar = gtk_statusbar_new();

	ctxid = gtk_statusbar_get_context_id(GTK_STATUSBAR(stbar),
					     "perf report");
	pgctx->statbar = stbar;
	pgctx->statbar_ctx_id = ctxid;

	वापस stbar;
पूर्ण
