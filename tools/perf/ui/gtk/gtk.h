<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_GTK_H_
#घोषणा _PERF_GTK_H_ 1

#समावेश <stdbool.h>

#आशय GCC diagnostic ignored "-Wstrict-prototypes"
#समावेश <gtk/gtk.h>
#आशय GCC diagnostic error "-Wstrict-prototypes"


काष्ठा perf_gtk_context अणु
	GtkWidget *मुख्य_winकरोw;
	GtkWidget *notebook;

#अगर_घोषित HAVE_GTK_INFO_BAR_SUPPORT
	GtkWidget *info_bar;
	GtkWidget *message_label;
#पूर्ण_अगर
	GtkWidget *statbar;
	guपूर्णांक statbar_ctx_id;
पूर्ण;

पूर्णांक perf_gtk__init(व्योम);
व्योम perf_gtk__निकास(bool रुको_क्रम_ok);

बाह्य काष्ठा perf_gtk_context *pgctx;

अटल अंतरभूत bool perf_gtk__is_active_context(काष्ठा perf_gtk_context *ctx)
अणु
	वापस ctx && ctx->मुख्य_winकरोw;
पूर्ण

काष्ठा perf_gtk_context *perf_gtk__activate_context(GtkWidget *winकरोw);
पूर्णांक perf_gtk__deactivate_context(काष्ठा perf_gtk_context **ctx);

व्योम perf_gtk__init_helpline(व्योम);
व्योम gtk_ui_progress__init(व्योम);
व्योम perf_gtk__init_hpp(व्योम);

व्योम perf_gtk__संकेत(पूर्णांक sig);
व्योम perf_gtk__resize_winकरोw(GtkWidget *winकरोw);
स्थिर अक्षर *perf_gtk__get_percent_color(द्विगुन percent);
GtkWidget *perf_gtk__setup_statusbar(व्योम);

#अगर_घोषित HAVE_GTK_INFO_BAR_SUPPORT
GtkWidget *perf_gtk__setup_info_bar(व्योम);
#अन्यथा
अटल अंतरभूत GtkWidget *perf_gtk__setup_info_bar(व्योम)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

काष्ठा evsel;
काष्ठा evlist;
काष्ठा hist_entry;
काष्ठा hist_browser_समयr;

पूर्णांक evlist__gtk_browse_hists(काष्ठा evlist *evlist, स्थिर अक्षर *help,
			     काष्ठा hist_browser_समयr *hbt, भग्न min_pcnt);
पूर्णांक hist_entry__gtk_annotate(काष्ठा hist_entry *he,
			     काष्ठा evsel *evsel,
			     काष्ठा hist_browser_समयr *hbt);
व्योम perf_gtk__show_annotations(व्योम);

#पूर्ण_अगर /* _PERF_GTK_H_ */
