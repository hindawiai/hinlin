<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "gtk.h"
#समावेश "util/sort.h"
#समावेश "util/debug.h"
#समावेश "util/annotate.h"
#समावेश "util/evsel.h"
#समावेश "util/map.h"
#समावेश "util/dso.h"
#समावेश "util/symbol.h"
#समावेश "ui/helpline.h"
#समावेश <पूर्णांकtypes.h>
#समावेश <संकेत.स>

क्रमागत अणु
	ANN_COL__PERCENT,
	ANN_COL__OFFSET,
	ANN_COL__LINE,

	MAX_ANN_COLS
पूर्ण;

अटल स्थिर अक्षर *स्थिर col_names[] = अणु
	"Overhead",
	"Offset",
	"Line"
पूर्ण;

अटल पूर्णांक perf_gtk__get_percent(अक्षर *buf, माप_प्रकार size, काष्ठा symbol *sym,
				 काष्ठा disयंत्र_line *dl, पूर्णांक evidx)
अणु
	काष्ठा sym_hist *symhist;
	द्विगुन percent = 0.0;
	स्थिर अक्षर *markup;
	पूर्णांक ret = 0;

	म_नकल(buf, "");

	अगर (dl->al.offset == (s64) -1)
		वापस 0;

	symhist = annotation__histogram(symbol__annotation(sym), evidx);
	अगर (!symbol_conf.event_group && !symhist->addr[dl->al.offset].nr_samples)
		वापस 0;

	percent = 100.0 * symhist->addr[dl->al.offset].nr_samples / symhist->nr_samples;

	markup = perf_gtk__get_percent_color(percent);
	अगर (markup)
		ret += scnम_लिखो(buf, size, "%s", markup);
	ret += scnम_लिखो(buf + ret, size - ret, "%6.2f%%", percent);
	अगर (markup)
		ret += scnम_लिखो(buf + ret, size - ret, "</span>");

	वापस ret;
पूर्ण

अटल पूर्णांक perf_gtk__get_offset(अक्षर *buf, माप_प्रकार size, काष्ठा map_symbol *ms,
				काष्ठा disयंत्र_line *dl)
अणु
	u64 start = map__rip_2objdump(ms->map, ms->sym->start);

	म_नकल(buf, "");

	अगर (dl->al.offset == (s64) -1)
		वापस 0;

	वापस scnम_लिखो(buf, size, "%"PRIx64, start + dl->al.offset);
पूर्ण

अटल पूर्णांक perf_gtk__get_line(अक्षर *buf, माप_प्रकार size, काष्ठा disयंत्र_line *dl)
अणु
	पूर्णांक ret = 0;
	अक्षर *line = g_markup_escape_text(dl->al.line, -1);
	स्थिर अक्षर *markup = "<span fgcolor='gray'>";

	म_नकल(buf, "");

	अगर (!line)
		वापस 0;

	अगर (dl->al.offset != (s64) -1)
		markup = शून्य;

	अगर (markup)
		ret += scnम_लिखो(buf, size, "%s", markup);
	ret += scnम_लिखो(buf + ret, size - ret, "%s", line);
	अगर (markup)
		ret += scnम_लिखो(buf + ret, size - ret, "</span>");

	g_मुक्त(line);
	वापस ret;
पूर्ण

अटल पूर्णांक perf_gtk__annotate_symbol(GtkWidget *winकरोw, काष्ठा map_symbol *ms,
				काष्ठा evsel *evsel,
				काष्ठा hist_browser_समयr *hbt __maybe_unused)
अणु
	काष्ठा symbol *sym = ms->sym;
	काष्ठा disयंत्र_line *pos, *n;
	काष्ठा annotation *notes;
	GType col_types[MAX_ANN_COLS];
	GtkCellRenderer *renderer;
	GtkListStore *store;
	GtkWidget *view;
	पूर्णांक i;
	अक्षर s[512];

	notes = symbol__annotation(sym);

	क्रम (i = 0; i < MAX_ANN_COLS; i++) अणु
		col_types[i] = G_TYPE_STRING;
	पूर्ण
	store = gtk_list_store_newv(MAX_ANN_COLS, col_types);

	view = gtk_tree_view_new();
	renderer = gtk_cell_renderer_text_new();

	क्रम (i = 0; i < MAX_ANN_COLS; i++) अणु
		gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
					-1, col_names[i], renderer, "markup",
					i, शून्य);
	पूर्ण

	gtk_tree_view_set_model(GTK_TREE_VIEW(view), GTK_TREE_MODEL(store));
	g_object_unref(GTK_TREE_MODEL(store));

	list_क्रम_each_entry(pos, &notes->src->source, al.node) अणु
		GtkTreeIter iter;
		पूर्णांक ret = 0;

		gtk_list_store_append(store, &iter);

		अगर (evsel__is_group_event(evsel)) अणु
			क्रम (i = 0; i < evsel->core.nr_members; i++) अणु
				ret += perf_gtk__get_percent(s + ret,
							     माप(s) - ret,
							     sym, pos,
							     evsel->idx + i);
				ret += scnम_लिखो(s + ret, माप(s) - ret, " ");
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = perf_gtk__get_percent(s, माप(s), sym, pos,
						    evsel->idx);
		पूर्ण

		अगर (ret)
			gtk_list_store_set(store, &iter, ANN_COL__PERCENT, s, -1);
		अगर (perf_gtk__get_offset(s, माप(s), ms, pos))
			gtk_list_store_set(store, &iter, ANN_COL__OFFSET, s, -1);
		अगर (perf_gtk__get_line(s, माप(s), pos))
			gtk_list_store_set(store, &iter, ANN_COL__LINE, s, -1);
	पूर्ण

	gtk_container_add(GTK_CONTAINER(winकरोw), view);

	list_क्रम_each_entry_safe(pos, n, &notes->src->source, al.node) अणु
		list_del_init(&pos->al.node);
		disयंत्र_line__मुक्त(pos);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक symbol__gtk_annotate(काष्ठा map_symbol *ms, काष्ठा evsel *evsel,
				काष्ठा hist_browser_समयr *hbt)
अणु
	काष्ठा symbol *sym = ms->sym;
	GtkWidget *winकरोw;
	GtkWidget *notebook;
	GtkWidget *scrolled_winकरोw;
	GtkWidget *tab_label;
	पूर्णांक err;

	अगर (ms->map->dso->annotate_warned)
		वापस -1;

	err = symbol__annotate(ms, evsel, &annotation__शेष_options, शून्य);
	अगर (err) अणु
		अक्षर msg[बफ_मान];
		symbol__म_त्रुटि_disassemble(ms, err, msg, माप(msg));
		ui__error("Couldn't annotate %s: %s\n", sym->name, msg);
		वापस -1;
	पूर्ण

	symbol__calc_percent(sym, evsel);

	अगर (perf_gtk__is_active_context(pgctx)) अणु
		winकरोw = pgctx->मुख्य_winकरोw;
		notebook = pgctx->notebook;
	पूर्ण अन्यथा अणु
		GtkWidget *vbox;
		GtkWidget *infobar;
		GtkWidget *statbar;

		संकेत(संक_अंश, perf_gtk__संकेत);
		संकेत(संक_भ_त्रुटि,  perf_gtk__संकेत);
		संकेत(संक_विघ्न,  perf_gtk__संकेत);
		संकेत(SIGQUIT, perf_gtk__संकेत);
		संकेत(संक_इति, perf_gtk__संकेत);

		winकरोw = gtk_winकरोw_new(GTK_WINDOW_TOPLEVEL);
		gtk_winकरोw_set_title(GTK_WINDOW(winकरोw), "perf annotate");

		g_संकेत_connect(winकरोw, "delete_event", gtk_मुख्य_quit, शून्य);

		pgctx = perf_gtk__activate_context(winकरोw);
		अगर (!pgctx)
			वापस -1;

		vbox = gtk_vbox_new(FALSE, 0);
		notebook = gtk_notebook_new();
		pgctx->notebook = notebook;

		gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 0);

		infobar = perf_gtk__setup_info_bar();
		अगर (infobar) अणु
			gtk_box_pack_start(GTK_BOX(vbox), infobar,
					   FALSE, FALSE, 0);
		पूर्ण

		statbar = perf_gtk__setup_statusbar();
		gtk_box_pack_start(GTK_BOX(vbox), statbar, FALSE, FALSE, 0);

		gtk_container_add(GTK_CONTAINER(winकरोw), vbox);
	पूर्ण

	scrolled_winकरोw = gtk_scrolled_winकरोw_new(शून्य, शून्य);
	tab_label = gtk_label_new(sym->name);

	gtk_scrolled_winकरोw_set_policy(GTK_SCROLLED_WINDOW(scrolled_winकरोw),
				       GTK_POLICY_AUTOMATIC,
				       GTK_POLICY_AUTOMATIC);

	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), scrolled_winकरोw,
				 tab_label);

	perf_gtk__annotate_symbol(scrolled_winकरोw, ms, evsel, hbt);
	वापस 0;
पूर्ण

पूर्णांक hist_entry__gtk_annotate(काष्ठा hist_entry *he,
			     काष्ठा evsel *evsel,
			     काष्ठा hist_browser_समयr *hbt)
अणु
	वापस symbol__gtk_annotate(&he->ms, evsel, hbt);
पूर्ण

व्योम perf_gtk__show_annotations(व्योम)
अणु
	GtkWidget *winकरोw;

	अगर (!perf_gtk__is_active_context(pgctx))
		वापस;

	winकरोw = pgctx->मुख्य_winकरोw;
	gtk_widget_show_all(winकरोw);

	perf_gtk__resize_winकरोw(winकरोw);
	gtk_winकरोw_set_position(GTK_WINDOW(winकरोw), GTK_WIN_POS_CENTER);

	gtk_मुख्य();

	perf_gtk__deactivate_context(&pgctx);
पूर्ण
