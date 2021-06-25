<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <पूर्णांकtypes.h>

#समावेश "gtk.h"
#समावेश "../progress.h"

अटल GtkWidget *dialog;
अटल GtkWidget *progress;

अटल व्योम gtk_ui_progress__update(काष्ठा ui_progress *p)
अणु
	द्विगुन fraction = p->total ? 1.0 * p->curr / p->total : 0.0;
	अक्षर buf[1024];

	अगर (dialog == शून्य) अणु
		GtkWidget *vbox = gtk_vbox_new(TRUE, 5);
		GtkWidget *label = gtk_label_new(p->title);

		dialog = gtk_winकरोw_new(GTK_WINDOW_TOPLEVEL);
		progress = gtk_progress_bar_new();

		gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, FALSE, 3);
		gtk_box_pack_start(GTK_BOX(vbox), progress, TRUE, TRUE, 3);

		gtk_container_add(GTK_CONTAINER(dialog), vbox);

		gtk_winकरोw_set_title(GTK_WINDOW(dialog), "perf");
		gtk_winकरोw_resize(GTK_WINDOW(dialog), 300, 80);
		gtk_winकरोw_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

		gtk_widget_show_all(dialog);
	पूर्ण

	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress), fraction);
	snम_लिखो(buf, माप(buf), "%"PRIu64" / %"PRIu64, p->curr, p->total);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress), buf);

	/* we didn't call gtk_मुख्य yet, so करो it manually */
	जबतक (gtk_events_pending())
		gtk_मुख्य_iteration();
पूर्ण

अटल व्योम gtk_ui_progress__finish(व्योम)
अणु
	/* this will also destroy all of its children */
	gtk_widget_destroy(dialog);

	dialog = शून्य;
पूर्ण

अटल काष्ठा ui_progress_ops gtk_ui_progress__ops = अणु
	.update		= gtk_ui_progress__update,
	.finish		= gtk_ui_progress__finish,
पूर्ण;

व्योम gtk_ui_progress__init(व्योम)
अणु
	ui_progress__ops = &gtk_ui_progress__ops;
पूर्ण
