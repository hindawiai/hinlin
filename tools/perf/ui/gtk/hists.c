<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "../evlist.h"
#समावेश "../callchain.h"
#समावेश "../evsel.h"
#समावेश "../sort.h"
#समावेश "../hist.h"
#समावेश "../helpline.h"
#समावेश "../string2.h"
#समावेश "gtk.h"
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <linux/माला.स>

#घोषणा MAX_COLUMNS			32

अटल पूर्णांक __percent_color_snम_लिखो(काष्ठा perf_hpp *hpp, स्थिर अक्षर *fmt, ...)
अणु
	पूर्णांक ret = 0;
	पूर्णांक len;
	बहु_सूची args;
	द्विगुन percent;
	स्थिर अक्षर *markup;
	अक्षर *buf = hpp->buf;
	माप_प्रकार size = hpp->size;

	बहु_शुरू(args, fmt);
	len = बहु_तर्क(args, पूर्णांक);
	percent = बहु_तर्क(args, द्विगुन);
	बहु_पूर्ण(args);

	markup = perf_gtk__get_percent_color(percent);
	अगर (markup)
		ret += scnम_लिखो(buf, size, markup);

	ret += scnम_लिखो(buf + ret, size - ret, fmt, len, percent);

	अगर (markup)
		ret += scnम_लिखो(buf + ret, size - ret, "</span>");

	वापस ret;
पूर्ण

#घोषणा __HPP_COLOR_PERCENT_FN(_type, _field)					\
अटल u64 he_get_##_field(काष्ठा hist_entry *he)				\
अणु										\
	वापस he->stat._field;							\
पूर्ण										\
										\
अटल पूर्णांक perf_gtk__hpp_color_##_type(काष्ठा perf_hpp_fmt *fmt,		\
				       काष्ठा perf_hpp *hpp,			\
				       काष्ठा hist_entry *he)			\
अणु										\
	वापस hpp__fmt(fmt, hpp, he, he_get_##_field, " %*.2f%%",		\
			__percent_color_snम_लिखो, true);			\
पूर्ण

#घोषणा __HPP_COLOR_ACC_PERCENT_FN(_type, _field)				\
अटल u64 he_get_acc_##_field(काष्ठा hist_entry *he)				\
अणु										\
	वापस he->stat_acc->_field;						\
पूर्ण										\
										\
अटल पूर्णांक perf_gtk__hpp_color_##_type(काष्ठा perf_hpp_fmt *fmt,		\
				       काष्ठा perf_hpp *hpp,			\
				       काष्ठा hist_entry *he)			\
अणु										\
	वापस hpp__fmt_acc(fmt, hpp, he, he_get_acc_##_field, " %*.2f%%", 	\
			    __percent_color_snम_लिखो, true);			\
पूर्ण

__HPP_COLOR_PERCENT_FN(overhead, period)
__HPP_COLOR_PERCENT_FN(overhead_sys, period_sys)
__HPP_COLOR_PERCENT_FN(overhead_us, period_us)
__HPP_COLOR_PERCENT_FN(overhead_guest_sys, period_guest_sys)
__HPP_COLOR_PERCENT_FN(overhead_guest_us, period_guest_us)
__HPP_COLOR_ACC_PERCENT_FN(overhead_acc, period)

#अघोषित __HPP_COLOR_PERCENT_FN


व्योम perf_gtk__init_hpp(व्योम)
अणु
	perf_hpp__क्रमmat[PERF_HPP__OVERHEAD].color =
				perf_gtk__hpp_color_overhead;
	perf_hpp__क्रमmat[PERF_HPP__OVERHEAD_SYS].color =
				perf_gtk__hpp_color_overhead_sys;
	perf_hpp__क्रमmat[PERF_HPP__OVERHEAD_US].color =
				perf_gtk__hpp_color_overhead_us;
	perf_hpp__क्रमmat[PERF_HPP__OVERHEAD_GUEST_SYS].color =
				perf_gtk__hpp_color_overhead_guest_sys;
	perf_hpp__क्रमmat[PERF_HPP__OVERHEAD_GUEST_US].color =
				perf_gtk__hpp_color_overhead_guest_us;
	perf_hpp__क्रमmat[PERF_HPP__OVERHEAD_ACC].color =
				perf_gtk__hpp_color_overhead_acc;
पूर्ण

अटल व्योम perf_gtk__add_callchain_flat(काष्ठा rb_root *root, GtkTreeStore *store,
					 GtkTreeIter *parent, पूर्णांक col, u64 total)
अणु
	काष्ठा rb_node *nd;
	bool has_single_node = (rb_first(root) == rb_last(root));

	क्रम (nd = rb_first(root); nd; nd = rb_next(nd)) अणु
		काष्ठा callchain_node *node;
		काष्ठा callchain_list *chain;
		GtkTreeIter iter, new_parent;
		bool need_new_parent;

		node = rb_entry(nd, काष्ठा callchain_node, rb_node);

		new_parent = *parent;
		need_new_parent = !has_single_node;

		callchain_node__make_parent_list(node);

		list_क्रम_each_entry(chain, &node->parent_val, list) अणु
			अक्षर buf[128];

			gtk_tree_store_append(store, &iter, &new_parent);

			callchain_node__scnम_लिखो_value(node, buf, माप(buf), total);
			gtk_tree_store_set(store, &iter, 0, buf, -1);

			callchain_list__sym_name(chain, buf, माप(buf), false);
			gtk_tree_store_set(store, &iter, col, buf, -1);

			अगर (need_new_parent) अणु
				/*
				 * Only show the top-most symbol in a callchain
				 * अगर it's not the only callchain.
				 */
				new_parent = iter;
				need_new_parent = false;
			पूर्ण
		पूर्ण

		list_क्रम_each_entry(chain, &node->val, list) अणु
			अक्षर buf[128];

			gtk_tree_store_append(store, &iter, &new_parent);

			callchain_node__scnम_लिखो_value(node, buf, माप(buf), total);
			gtk_tree_store_set(store, &iter, 0, buf, -1);

			callchain_list__sym_name(chain, buf, माप(buf), false);
			gtk_tree_store_set(store, &iter, col, buf, -1);

			अगर (need_new_parent) अणु
				/*
				 * Only show the top-most symbol in a callchain
				 * अगर it's not the only callchain.
				 */
				new_parent = iter;
				need_new_parent = false;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम perf_gtk__add_callchain_folded(काष्ठा rb_root *root, GtkTreeStore *store,
					   GtkTreeIter *parent, पूर्णांक col, u64 total)
अणु
	काष्ठा rb_node *nd;

	क्रम (nd = rb_first(root); nd; nd = rb_next(nd)) अणु
		काष्ठा callchain_node *node;
		काष्ठा callchain_list *chain;
		GtkTreeIter iter;
		अक्षर buf[64];
		अक्षर *str, *str_alloc = शून्य;
		bool first = true;

		node = rb_entry(nd, काष्ठा callchain_node, rb_node);

		callchain_node__make_parent_list(node);

		list_क्रम_each_entry(chain, &node->parent_val, list) अणु
			अक्षर name[1024];

			callchain_list__sym_name(chain, name, माप(name), false);

			अगर (aप्र_लिखो(&str, "%s%s%s",
				     first ? "" : str_alloc,
				     first ? "" : symbol_conf.field_sep ?: "; ",
				     name) < 0)
				वापस;

			first = false;
			मुक्त(str_alloc);
			str_alloc = str;
		पूर्ण

		list_क्रम_each_entry(chain, &node->val, list) अणु
			अक्षर name[1024];

			callchain_list__sym_name(chain, name, माप(name), false);

			अगर (aप्र_लिखो(&str, "%s%s%s",
				     first ? "" : str_alloc,
				     first ? "" : symbol_conf.field_sep ?: "; ",
				     name) < 0)
				वापस;

			first = false;
			मुक्त(str_alloc);
			str_alloc = str;
		पूर्ण

		gtk_tree_store_append(store, &iter, parent);

		callchain_node__scnम_लिखो_value(node, buf, माप(buf), total);
		gtk_tree_store_set(store, &iter, 0, buf, -1);

		gtk_tree_store_set(store, &iter, col, str, -1);

		मुक्त(str_alloc);
	पूर्ण
पूर्ण

अटल व्योम perf_gtk__add_callchain_graph(काष्ठा rb_root *root, GtkTreeStore *store,
					  GtkTreeIter *parent, पूर्णांक col, u64 total)
अणु
	काष्ठा rb_node *nd;
	bool has_single_node = (rb_first(root) == rb_last(root));

	क्रम (nd = rb_first(root); nd; nd = rb_next(nd)) अणु
		काष्ठा callchain_node *node;
		काष्ठा callchain_list *chain;
		GtkTreeIter iter, new_parent;
		bool need_new_parent;
		u64 child_total;

		node = rb_entry(nd, काष्ठा callchain_node, rb_node);

		new_parent = *parent;
		need_new_parent = !has_single_node && (node->val_nr > 1);

		list_क्रम_each_entry(chain, &node->val, list) अणु
			अक्षर buf[128];

			gtk_tree_store_append(store, &iter, &new_parent);

			callchain_node__scnम_लिखो_value(node, buf, माप(buf), total);
			gtk_tree_store_set(store, &iter, 0, buf, -1);

			callchain_list__sym_name(chain, buf, माप(buf), false);
			gtk_tree_store_set(store, &iter, col, buf, -1);

			अगर (need_new_parent) अणु
				/*
				 * Only show the top-most symbol in a callchain
				 * अगर it's not the only callchain.
				 */
				new_parent = iter;
				need_new_parent = false;
			पूर्ण
		पूर्ण

		अगर (callchain_param.mode == CHAIN_GRAPH_REL)
			child_total = node->children_hit;
		अन्यथा
			child_total = total;

		/* Now 'iter' contains info of the last callchain_list */
		perf_gtk__add_callchain_graph(&node->rb_root, store, &iter, col,
					      child_total);
	पूर्ण
पूर्ण

अटल व्योम perf_gtk__add_callchain(काष्ठा rb_root *root, GtkTreeStore *store,
				    GtkTreeIter *parent, पूर्णांक col, u64 total)
अणु
	अगर (callchain_param.mode == CHAIN_FLAT)
		perf_gtk__add_callchain_flat(root, store, parent, col, total);
	अन्यथा अगर (callchain_param.mode == CHAIN_FOLDED)
		perf_gtk__add_callchain_folded(root, store, parent, col, total);
	अन्यथा
		perf_gtk__add_callchain_graph(root, store, parent, col, total);
पूर्ण

अटल व्योम on_row_activated(GtkTreeView *view, GtkTreePath *path,
			     GtkTreeViewColumn *col __maybe_unused,
			     gpoपूर्णांकer user_data __maybe_unused)
अणु
	bool expanded = gtk_tree_view_row_expanded(view, path);

	अगर (expanded)
		gtk_tree_view_collapse_row(view, path);
	अन्यथा
		gtk_tree_view_expand_row(view, path, FALSE);
पूर्ण

अटल व्योम perf_gtk__show_hists(GtkWidget *winकरोw, काष्ठा hists *hists,
				 भग्न min_pcnt)
अणु
	काष्ठा perf_hpp_fmt *fmt;
	GType col_types[MAX_COLUMNS];
	GtkCellRenderer *renderer;
	GtkTreeStore *store;
	काष्ठा rb_node *nd;
	GtkWidget *view;
	पूर्णांक col_idx;
	पूर्णांक sym_col = -1;
	पूर्णांक nr_cols;
	अक्षर s[512];

	काष्ठा perf_hpp hpp = अणु
		.buf		= s,
		.size		= माप(s),
	पूर्ण;

	nr_cols = 0;

	hists__क्रम_each_क्रमmat(hists, fmt)
		col_types[nr_cols++] = G_TYPE_STRING;

	store = gtk_tree_store_newv(nr_cols, col_types);

	view = gtk_tree_view_new();

	renderer = gtk_cell_renderer_text_new();

	col_idx = 0;

	hists__क्रम_each_क्रमmat(hists, fmt) अणु
		अगर (perf_hpp__should_skip(fmt, hists))
			जारी;

		/*
		 * XXX no way to determine where symcol column is..
		 *     Just use last column क्रम now.
		 */
		अगर (perf_hpp__is_sort_entry(fmt))
			sym_col = col_idx;

		gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
							    -1, fmt->name,
							    renderer, "markup",
							    col_idx++, शून्य);
	पूर्ण

	क्रम (col_idx = 0; col_idx < nr_cols; col_idx++) अणु
		GtkTreeViewColumn *column;

		column = gtk_tree_view_get_column(GTK_TREE_VIEW(view), col_idx);
		gtk_tree_view_column_set_resizable(column, TRUE);

		अगर (col_idx == sym_col) अणु
			gtk_tree_view_set_expander_column(GTK_TREE_VIEW(view),
							  column);
		पूर्ण
	पूर्ण

	gtk_tree_view_set_model(GTK_TREE_VIEW(view), GTK_TREE_MODEL(store));

	g_object_unref(GTK_TREE_MODEL(store));

	क्रम (nd = rb_first_cached(&hists->entries); nd; nd = rb_next(nd)) अणु
		काष्ठा hist_entry *h = rb_entry(nd, काष्ठा hist_entry, rb_node);
		GtkTreeIter iter;
		u64 total = hists__total_period(h->hists);
		भग्न percent;

		अगर (h->filtered)
			जारी;

		percent = hist_entry__get_percent_limit(h);
		अगर (percent < min_pcnt)
			जारी;

		gtk_tree_store_append(store, &iter, शून्य);

		col_idx = 0;

		hists__क्रम_each_क्रमmat(hists, fmt) अणु
			अगर (perf_hpp__should_skip(fmt, h->hists))
				जारी;

			अगर (fmt->color)
				fmt->color(fmt, &hpp, h);
			अन्यथा
				fmt->entry(fmt, &hpp, h);

			gtk_tree_store_set(store, &iter, col_idx++, s, -1);
		पूर्ण

		अगर (hist_entry__has_callchains(h) &&
		    symbol_conf.use_callchain && hists__has(hists, sym)) अणु
			अगर (callchain_param.mode == CHAIN_GRAPH_REL)
				total = symbol_conf.cumulate_callchain ?
					h->stat_acc->period : h->stat.period;

			perf_gtk__add_callchain(&h->sorted_chain, store, &iter,
						sym_col, total);
		पूर्ण
	पूर्ण

	gtk_tree_view_set_rules_hपूर्णांक(GTK_TREE_VIEW(view), TRUE);

	g_संकेत_connect(view, "row-activated",
			 G_CALLBACK(on_row_activated), शून्य);
	gtk_container_add(GTK_CONTAINER(winकरोw), view);
पूर्ण

अटल व्योम perf_gtk__add_hierarchy_entries(काष्ठा hists *hists,
					    काष्ठा rb_root_cached *root,
					    GtkTreeStore *store,
					    GtkTreeIter *parent,
					    काष्ठा perf_hpp *hpp,
					    भग्न min_pcnt)
अणु
	पूर्णांक col_idx = 0;
	काष्ठा rb_node *node;
	काष्ठा hist_entry *he;
	काष्ठा perf_hpp_fmt *fmt;
	काष्ठा perf_hpp_list_node *fmt_node;
	u64 total = hists__total_period(hists);
	पूर्णांक size;

	क्रम (node = rb_first_cached(root); node; node = rb_next(node)) अणु
		GtkTreeIter iter;
		भग्न percent;
		अक्षर *bf;

		he = rb_entry(node, काष्ठा hist_entry, rb_node);
		अगर (he->filtered)
			जारी;

		percent = hist_entry__get_percent_limit(he);
		अगर (percent < min_pcnt)
			जारी;

		gtk_tree_store_append(store, &iter, parent);

		col_idx = 0;

		/* the first hpp_list_node is क्रम overhead columns */
		fmt_node = list_first_entry(&hists->hpp_क्रमmats,
					    काष्ठा perf_hpp_list_node, list);
		perf_hpp_list__क्रम_each_क्रमmat(&fmt_node->hpp, fmt) अणु
			अगर (fmt->color)
				fmt->color(fmt, hpp, he);
			अन्यथा
				fmt->entry(fmt, hpp, he);

			gtk_tree_store_set(store, &iter, col_idx++, hpp->buf, -1);
		पूर्ण

		bf = hpp->buf;
		size = hpp->size;
		perf_hpp_list__क्रम_each_क्रमmat(he->hpp_list, fmt) अणु
			पूर्णांक ret;

			अगर (fmt->color)
				ret = fmt->color(fmt, hpp, he);
			अन्यथा
				ret = fmt->entry(fmt, hpp, he);

			snम_लिखो(hpp->buf + ret, hpp->size - ret, "  ");
			advance_hpp(hpp, ret + 2);
		पूर्ण

		gtk_tree_store_set(store, &iter, col_idx, strim(bf), -1);

		अगर (!he->leaf) अणु
			hpp->buf = bf;
			hpp->size = size;

			perf_gtk__add_hierarchy_entries(hists, &he->hroot_out,
							store, &iter, hpp,
							min_pcnt);

			अगर (!hist_entry__has_hierarchy_children(he, min_pcnt)) अणु
				अक्षर buf[32];
				GtkTreeIter child;

				snम_लिखो(buf, माप(buf), "no entry >= %.2f%%",
					 min_pcnt);

				gtk_tree_store_append(store, &child, &iter);
				gtk_tree_store_set(store, &child, col_idx, buf, -1);
			पूर्ण
		पूर्ण

		अगर (he->leaf && hist_entry__has_callchains(he) && symbol_conf.use_callchain) अणु
			अगर (callchain_param.mode == CHAIN_GRAPH_REL)
				total = symbol_conf.cumulate_callchain ?
					he->stat_acc->period : he->stat.period;

			perf_gtk__add_callchain(&he->sorted_chain, store, &iter,
						col_idx, total);
		पूर्ण
	पूर्ण

पूर्ण

अटल व्योम perf_gtk__show_hierarchy(GtkWidget *winकरोw, काष्ठा hists *hists,
				     भग्न min_pcnt)
अणु
	काष्ठा perf_hpp_fmt *fmt;
	काष्ठा perf_hpp_list_node *fmt_node;
	GType col_types[MAX_COLUMNS];
	GtkCellRenderer *renderer;
	GtkTreeStore *store;
	GtkWidget *view;
	पूर्णांक col_idx;
	पूर्णांक nr_cols = 0;
	अक्षर s[512];
	अक्षर buf[512];
	bool first_node, first_col;
	काष्ठा perf_hpp hpp = अणु
		.buf		= s,
		.size		= माप(s),
	पूर्ण;

	hists__क्रम_each_क्रमmat(hists, fmt) अणु
		अगर (perf_hpp__is_sort_entry(fmt) ||
		    perf_hpp__is_dynamic_entry(fmt))
			अवरोध;

		col_types[nr_cols++] = G_TYPE_STRING;
	पूर्ण
	col_types[nr_cols++] = G_TYPE_STRING;

	store = gtk_tree_store_newv(nr_cols, col_types);
	view = gtk_tree_view_new();
	renderer = gtk_cell_renderer_text_new();

	col_idx = 0;

	/* the first hpp_list_node is क्रम overhead columns */
	fmt_node = list_first_entry(&hists->hpp_क्रमmats,
				    काष्ठा perf_hpp_list_node, list);
	perf_hpp_list__क्रम_each_क्रमmat(&fmt_node->hpp, fmt) अणु
		gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
							    -1, fmt->name,
							    renderer, "markup",
							    col_idx++, शून्य);
	पूर्ण

	/* स्थिरruct merged column header since sort keys share single column */
	buf[0] = '\0';
	first_node = true;
	list_क्रम_each_entry_जारी(fmt_node, &hists->hpp_क्रमmats, list) अणु
		अगर (!first_node)
			म_जोड़ो(buf, " / ");
		first_node = false;

		first_col = true;
		perf_hpp_list__क्रम_each_क्रमmat(&fmt_node->hpp ,fmt) अणु
			अगर (perf_hpp__should_skip(fmt, hists))
				जारी;

			अगर (!first_col)
				म_जोड़ो(buf, "+");
			first_col = false;

			fmt->header(fmt, &hpp, hists, 0, शून्य);
			म_जोड़ो(buf, strim(hpp.buf));
		पूर्ण
	पूर्ण

	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
						    -1, buf,
						    renderer, "markup",
						    col_idx++, शून्य);

	क्रम (col_idx = 0; col_idx < nr_cols; col_idx++) अणु
		GtkTreeViewColumn *column;

		column = gtk_tree_view_get_column(GTK_TREE_VIEW(view), col_idx);
		gtk_tree_view_column_set_resizable(column, TRUE);

		अगर (col_idx == 0) अणु
			gtk_tree_view_set_expander_column(GTK_TREE_VIEW(view),
							  column);
		पूर्ण
	पूर्ण

	gtk_tree_view_set_model(GTK_TREE_VIEW(view), GTK_TREE_MODEL(store));
	g_object_unref(GTK_TREE_MODEL(store));

	perf_gtk__add_hierarchy_entries(hists, &hists->entries, store,
					शून्य, &hpp, min_pcnt);

	gtk_tree_view_set_rules_hपूर्णांक(GTK_TREE_VIEW(view), TRUE);

	g_संकेत_connect(view, "row-activated",
			 G_CALLBACK(on_row_activated), शून्य);
	gtk_container_add(GTK_CONTAINER(winकरोw), view);
पूर्ण

पूर्णांक evlist__gtk_browse_hists(काष्ठा evlist *evlist, स्थिर अक्षर *help,
			     काष्ठा hist_browser_समयr *hbt __maybe_unused, भग्न min_pcnt)
अणु
	काष्ठा evsel *pos;
	GtkWidget *vbox;
	GtkWidget *notebook;
	GtkWidget *info_bar;
	GtkWidget *statbar;
	GtkWidget *winकरोw;

	संकेत(संक_अंश, perf_gtk__संकेत);
	संकेत(संक_भ_त्रुटि,  perf_gtk__संकेत);
	संकेत(संक_विघ्न,  perf_gtk__संकेत);
	संकेत(SIGQUIT, perf_gtk__संकेत);
	संकेत(संक_इति, perf_gtk__संकेत);

	winकरोw = gtk_winकरोw_new(GTK_WINDOW_TOPLEVEL);

	gtk_winकरोw_set_title(GTK_WINDOW(winकरोw), "perf report");

	g_संकेत_connect(winकरोw, "delete_event", gtk_मुख्य_quit, शून्य);

	pgctx = perf_gtk__activate_context(winकरोw);
	अगर (!pgctx)
		वापस -1;

	vbox = gtk_vbox_new(FALSE, 0);

	notebook = gtk_notebook_new();

	gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 0);

	info_bar = perf_gtk__setup_info_bar();
	अगर (info_bar)
		gtk_box_pack_start(GTK_BOX(vbox), info_bar, FALSE, FALSE, 0);

	statbar = perf_gtk__setup_statusbar();
	gtk_box_pack_start(GTK_BOX(vbox), statbar, FALSE, FALSE, 0);

	gtk_container_add(GTK_CONTAINER(winकरोw), vbox);

	evlist__क्रम_each_entry(evlist, pos) अणु
		काष्ठा hists *hists = evsel__hists(pos);
		स्थिर अक्षर *evname = evsel__name(pos);
		GtkWidget *scrolled_winकरोw;
		GtkWidget *tab_label;
		अक्षर buf[512];
		माप_प्रकार size = माप(buf);

		अगर (symbol_conf.event_group) अणु
			अगर (!evsel__is_group_leader(pos))
				जारी;

			अगर (pos->core.nr_members > 1) अणु
				evsel__group_desc(pos, buf, size);
				evname = buf;
			पूर्ण
		पूर्ण

		scrolled_winकरोw = gtk_scrolled_winकरोw_new(शून्य, शून्य);

		gtk_scrolled_winकरोw_set_policy(GTK_SCROLLED_WINDOW(scrolled_winकरोw),
							GTK_POLICY_AUTOMATIC,
							GTK_POLICY_AUTOMATIC);

		अगर (symbol_conf.report_hierarchy)
			perf_gtk__show_hierarchy(scrolled_winकरोw, hists, min_pcnt);
		अन्यथा
			perf_gtk__show_hists(scrolled_winकरोw, hists, min_pcnt);

		tab_label = gtk_label_new(evname);

		gtk_notebook_append_page(GTK_NOTEBOOK(notebook), scrolled_winकरोw, tab_label);
	पूर्ण

	gtk_widget_show_all(winकरोw);

	perf_gtk__resize_winकरोw(winकरोw);

	gtk_winकरोw_set_position(GTK_WINDOW(winकरोw), GTK_WIN_POS_CENTER);

	ui_helpline__push(help);

	gtk_मुख्य();

	perf_gtk__deactivate_context(&pgctx);

	वापस 0;
पूर्ण
