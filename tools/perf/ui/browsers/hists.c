<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/rbtree.h>
#समावेश <linux/माला.स>
#समावेश <sys/ttyशेषs.h>
#समावेश <linux/समय64.h>
#समावेश <linux/zभाग.स>

#समावेश "../../util/debug.h"
#समावेश "../../util/dso.h"
#समावेश "../../util/callchain.h"
#समावेश "../../util/evsel.h"
#समावेश "../../util/evlist.h"
#समावेश "../../util/header.h"
#समावेश "../../util/hist.h"
#समावेश "../../util/machine.h"
#समावेश "../../util/map.h"
#समावेश "../../util/maps.h"
#समावेश "../../util/symbol.h"
#समावेश "../../util/map_symbol.h"
#समावेश "../../util/branch.h"
#समावेश "../../util/pstack.h"
#समावेश "../../util/sort.h"
#समावेश "../../util/top.h"
#समावेश "../../util/thread.h"
#समावेश "../../util/block-info.h"
#समावेश "../../arch/common.h"
#समावेश "../../perf.h"

#समावेश "../browsers/hists.h"
#समावेश "../helpline.h"
#समावेश "../util.h"
#समावेश "../ui.h"
#समावेश "map.h"
#समावेश "annotate.h"
#समावेश "srcline.h"
#समावेश "string2.h"
#समावेश "units.h"
#समावेश "time-utils.h"

#समावेश <linux/प्रकार.स>

बाह्य व्योम hist_browser__init_hpp(व्योम);

अटल पूर्णांक hists_browser__scnम_लिखो_title(काष्ठा hist_browser *browser, अक्षर *bf, माप_प्रकार size);
अटल व्योम hist_browser__update_nr_entries(काष्ठा hist_browser *hb);

अटल काष्ठा rb_node *hists__filter_entries(काष्ठा rb_node *nd,
					     भग्न min_pcnt);

अटल bool hist_browser__has_filter(काष्ठा hist_browser *hb)
अणु
	वापस hists__has_filter(hb->hists) || hb->min_pcnt || symbol_conf.has_filter || hb->c2c_filter;
पूर्ण

अटल पूर्णांक hist_browser__get_folding(काष्ठा hist_browser *browser)
अणु
	काष्ठा rb_node *nd;
	काष्ठा hists *hists = browser->hists;
	पूर्णांक unfolded_rows = 0;

	क्रम (nd = rb_first_cached(&hists->entries);
	     (nd = hists__filter_entries(nd, browser->min_pcnt)) != शून्य;
	     nd = rb_hierarchy_next(nd)) अणु
		काष्ठा hist_entry *he =
			rb_entry(nd, काष्ठा hist_entry, rb_node);

		अगर (he->leaf && he->unfolded)
			unfolded_rows += he->nr_rows;
	पूर्ण
	वापस unfolded_rows;
पूर्ण

अटल व्योम hist_browser__set_title_space(काष्ठा hist_browser *hb)
अणु
	काष्ठा ui_browser *browser = &hb->b;
	काष्ठा hists *hists = hb->hists;
	काष्ठा perf_hpp_list *hpp_list = hists->hpp_list;

	browser->extra_title_lines = hb->show_headers ? hpp_list->nr_header_lines : 0;
पूर्ण

अटल u32 hist_browser__nr_entries(काष्ठा hist_browser *hb)
अणु
	u32 nr_entries;

	अगर (symbol_conf.report_hierarchy)
		nr_entries = hb->nr_hierarchy_entries;
	अन्यथा अगर (hist_browser__has_filter(hb))
		nr_entries = hb->nr_non_filtered_entries;
	अन्यथा
		nr_entries = hb->hists->nr_entries;

	hb->nr_callchain_rows = hist_browser__get_folding(hb);
	वापस nr_entries + hb->nr_callchain_rows;
पूर्ण

अटल व्योम hist_browser__update_rows(काष्ठा hist_browser *hb)
अणु
	काष्ठा ui_browser *browser = &hb->b;
	काष्ठा hists *hists = hb->hists;
	काष्ठा perf_hpp_list *hpp_list = hists->hpp_list;
	u16 index_row;

	अगर (!hb->show_headers) अणु
		browser->rows += browser->extra_title_lines;
		browser->extra_title_lines = 0;
		वापस;
	पूर्ण

	browser->extra_title_lines = hpp_list->nr_header_lines;
	browser->rows -= browser->extra_title_lines;
	/*
	 * Verअगरy अगर we were at the last line and that line isn't
	 * visible because we now show the header line(s).
	 */
	index_row = browser->index - browser->top_idx;
	अगर (index_row >= browser->rows)
		browser->index -= index_row - browser->rows + 1;
पूर्ण

अटल व्योम hist_browser__refresh_dimensions(काष्ठा ui_browser *browser)
अणु
	काष्ठा hist_browser *hb = container_of(browser, काष्ठा hist_browser, b);

	/* 3 == +/- toggle symbol beक्रमe actual hist_entry rendering */
	browser->width = 3 + (hists__sort_list_width(hb->hists) + माप("[k]"));
	/*
 	 * FIXME: Just keeping existing behaviour, but this really should be
 	 *	  beक्रमe updating browser->width, as it will invalidate the
 	 *	  calculation above. Fix this and the fallout in another
 	 *	  changeset.
 	 */
	ui_browser__refresh_dimensions(browser);
पूर्ण

अटल व्योम hist_browser__reset(काष्ठा hist_browser *browser)
अणु
	/*
	 * The hists__हटाओ_entry_filter() alपढ़ोy folds non-filtered
	 * entries so we can assume it has 0 callchain rows.
	 */
	browser->nr_callchain_rows = 0;

	hist_browser__update_nr_entries(browser);
	browser->b.nr_entries = hist_browser__nr_entries(browser);
	hist_browser__refresh_dimensions(&browser->b);
	ui_browser__reset_index(&browser->b);
पूर्ण

अटल अक्षर tree__folded_sign(bool unfolded)
अणु
	वापस unfolded ? '-' : '+';
पूर्ण

अटल अक्षर hist_entry__folded(स्थिर काष्ठा hist_entry *he)
अणु
	वापस he->has_children ? tree__folded_sign(he->unfolded) : ' ';
पूर्ण

अटल अक्षर callchain_list__folded(स्थिर काष्ठा callchain_list *cl)
अणु
	वापस cl->has_children ? tree__folded_sign(cl->unfolded) : ' ';
पूर्ण

अटल व्योम callchain_list__set_folding(काष्ठा callchain_list *cl, bool unfold)
अणु
	cl->unfolded = unfold ? cl->has_children : false;
पूर्ण

अटल पूर्णांक callchain_node__count_rows_rb_tree(काष्ठा callchain_node *node)
अणु
	पूर्णांक n = 0;
	काष्ठा rb_node *nd;

	क्रम (nd = rb_first(&node->rb_root); nd; nd = rb_next(nd)) अणु
		काष्ठा callchain_node *child = rb_entry(nd, काष्ठा callchain_node, rb_node);
		काष्ठा callchain_list *chain;
		अक्षर folded_sign = ' '; /* No children */

		list_क्रम_each_entry(chain, &child->val, list) अणु
			++n;

			/* We need this because we may not have children */
			folded_sign = callchain_list__folded(chain);
			अगर (folded_sign == '+')
				अवरोध;
		पूर्ण

		अगर (folded_sign == '-') /* Have children and they're unfolded */
			n += callchain_node__count_rows_rb_tree(child);
	पूर्ण

	वापस n;
पूर्ण

अटल पूर्णांक callchain_node__count_flat_rows(काष्ठा callchain_node *node)
अणु
	काष्ठा callchain_list *chain;
	अक्षर folded_sign = 0;
	पूर्णांक n = 0;

	list_क्रम_each_entry(chain, &node->parent_val, list) अणु
		अगर (!folded_sign) अणु
			/* only check first chain list entry */
			folded_sign = callchain_list__folded(chain);
			अगर (folded_sign == '+')
				वापस 1;
		पूर्ण
		n++;
	पूर्ण

	list_क्रम_each_entry(chain, &node->val, list) अणु
		अगर (!folded_sign) अणु
			/* node->parent_val list might be empty */
			folded_sign = callchain_list__folded(chain);
			अगर (folded_sign == '+')
				वापस 1;
		पूर्ण
		n++;
	पूर्ण

	वापस n;
पूर्ण

अटल पूर्णांक callchain_node__count_folded_rows(काष्ठा callchain_node *node __maybe_unused)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक callchain_node__count_rows(काष्ठा callchain_node *node)
अणु
	काष्ठा callchain_list *chain;
	bool unfolded = false;
	पूर्णांक n = 0;

	अगर (callchain_param.mode == CHAIN_FLAT)
		वापस callchain_node__count_flat_rows(node);
	अन्यथा अगर (callchain_param.mode == CHAIN_FOLDED)
		वापस callchain_node__count_folded_rows(node);

	list_क्रम_each_entry(chain, &node->val, list) अणु
		++n;

		unfolded = chain->unfolded;
	पूर्ण

	अगर (unfolded)
		n += callchain_node__count_rows_rb_tree(node);

	वापस n;
पूर्ण

अटल पूर्णांक callchain__count_rows(काष्ठा rb_root *chain)
अणु
	काष्ठा rb_node *nd;
	पूर्णांक n = 0;

	क्रम (nd = rb_first(chain); nd; nd = rb_next(nd)) अणु
		काष्ठा callchain_node *node = rb_entry(nd, काष्ठा callchain_node, rb_node);
		n += callchain_node__count_rows(node);
	पूर्ण

	वापस n;
पूर्ण

अटल पूर्णांक hierarchy_count_rows(काष्ठा hist_browser *hb, काष्ठा hist_entry *he,
				bool include_children)
अणु
	पूर्णांक count = 0;
	काष्ठा rb_node *node;
	काष्ठा hist_entry *child;

	अगर (he->leaf)
		वापस callchain__count_rows(&he->sorted_chain);

	अगर (he->has_no_entry)
		वापस 1;

	node = rb_first_cached(&he->hroot_out);
	जबतक (node) अणु
		भग्न percent;

		child = rb_entry(node, काष्ठा hist_entry, rb_node);
		percent = hist_entry__get_percent_limit(child);

		अगर (!child->filtered && percent >= hb->min_pcnt) अणु
			count++;

			अगर (include_children && child->unfolded)
				count += hierarchy_count_rows(hb, child, true);
		पूर्ण

		node = rb_next(node);
	पूर्ण
	वापस count;
पूर्ण

अटल bool hist_entry__toggle_fold(काष्ठा hist_entry *he)
अणु
	अगर (!he)
		वापस false;

	अगर (!he->has_children)
		वापस false;

	he->unfolded = !he->unfolded;
	वापस true;
पूर्ण

अटल bool callchain_list__toggle_fold(काष्ठा callchain_list *cl)
अणु
	अगर (!cl)
		वापस false;

	अगर (!cl->has_children)
		वापस false;

	cl->unfolded = !cl->unfolded;
	वापस true;
पूर्ण

अटल व्योम callchain_node__init_have_children_rb_tree(काष्ठा callchain_node *node)
अणु
	काष्ठा rb_node *nd = rb_first(&node->rb_root);

	क्रम (nd = rb_first(&node->rb_root); nd; nd = rb_next(nd)) अणु
		काष्ठा callchain_node *child = rb_entry(nd, काष्ठा callchain_node, rb_node);
		काष्ठा callchain_list *chain;
		bool first = true;

		list_क्रम_each_entry(chain, &child->val, list) अणु
			अगर (first) अणु
				first = false;
				chain->has_children = chain->list.next != &child->val ||
							 !RB_EMPTY_ROOT(&child->rb_root);
			पूर्ण अन्यथा
				chain->has_children = chain->list.next == &child->val &&
							 !RB_EMPTY_ROOT(&child->rb_root);
		पूर्ण

		callchain_node__init_have_children_rb_tree(child);
	पूर्ण
पूर्ण

अटल व्योम callchain_node__init_have_children(काष्ठा callchain_node *node,
					       bool has_sibling)
अणु
	काष्ठा callchain_list *chain;

	chain = list_entry(node->val.next, काष्ठा callchain_list, list);
	chain->has_children = has_sibling;

	अगर (!list_empty(&node->val)) अणु
		chain = list_entry(node->val.prev, काष्ठा callchain_list, list);
		chain->has_children = !RB_EMPTY_ROOT(&node->rb_root);
	पूर्ण

	callchain_node__init_have_children_rb_tree(node);
पूर्ण

अटल व्योम callchain__init_have_children(काष्ठा rb_root *root)
अणु
	काष्ठा rb_node *nd = rb_first(root);
	bool has_sibling = nd && rb_next(nd);

	क्रम (nd = rb_first(root); nd; nd = rb_next(nd)) अणु
		काष्ठा callchain_node *node = rb_entry(nd, काष्ठा callchain_node, rb_node);
		callchain_node__init_have_children(node, has_sibling);
		अगर (callchain_param.mode == CHAIN_FLAT ||
		    callchain_param.mode == CHAIN_FOLDED)
			callchain_node__make_parent_list(node);
	पूर्ण
पूर्ण

अटल व्योम hist_entry__init_have_children(काष्ठा hist_entry *he)
अणु
	अगर (he->init_have_children)
		वापस;

	अगर (he->leaf) अणु
		he->has_children = !RB_EMPTY_ROOT(&he->sorted_chain);
		callchain__init_have_children(&he->sorted_chain);
	पूर्ण अन्यथा अणु
		he->has_children = !RB_EMPTY_ROOT(&he->hroot_out.rb_root);
	पूर्ण

	he->init_have_children = true;
पूर्ण

अटल bool hist_browser__selection_has_children(काष्ठा hist_browser *browser)
अणु
	काष्ठा hist_entry *he = browser->he_selection;
	काष्ठा map_symbol *ms = browser->selection;

	अगर (!he || !ms)
		वापस false;

	अगर (ms == &he->ms)
	       वापस he->has_children;

	वापस container_of(ms, काष्ठा callchain_list, ms)->has_children;
पूर्ण

अटल bool hist_browser__he_selection_unfolded(काष्ठा hist_browser *browser)
अणु
	वापस browser->he_selection ? browser->he_selection->unfolded : false;
पूर्ण

अटल bool hist_browser__selection_unfolded(काष्ठा hist_browser *browser)
अणु
	काष्ठा hist_entry *he = browser->he_selection;
	काष्ठा map_symbol *ms = browser->selection;

	अगर (!he || !ms)
		वापस false;

	अगर (ms == &he->ms)
	       वापस he->unfolded;

	वापस container_of(ms, काष्ठा callchain_list, ms)->unfolded;
पूर्ण

अटल अक्षर *hist_browser__selection_sym_name(काष्ठा hist_browser *browser, अक्षर *bf, माप_प्रकार size)
अणु
	काष्ठा hist_entry *he = browser->he_selection;
	काष्ठा map_symbol *ms = browser->selection;
	काष्ठा callchain_list *callchain_entry;

	अगर (!he || !ms)
		वापस शून्य;

	अगर (ms == &he->ms) अणु
	       hist_entry__sym_snम_लिखो(he, bf, size, 0);
	       वापस bf + 4; // skip the level, e.g. '[k] '
	पूर्ण

	callchain_entry = container_of(ms, काष्ठा callchain_list, ms);
	वापस callchain_list__sym_name(callchain_entry, bf, size, browser->show_dso);
पूर्ण

अटल bool hist_browser__toggle_fold(काष्ठा hist_browser *browser)
अणु
	काष्ठा hist_entry *he = browser->he_selection;
	काष्ठा map_symbol *ms = browser->selection;
	काष्ठा callchain_list *cl = container_of(ms, काष्ठा callchain_list, ms);
	bool has_children;

	अगर (!he || !ms)
		वापस false;

	अगर (ms == &he->ms)
		has_children = hist_entry__toggle_fold(he);
	अन्यथा
		has_children = callchain_list__toggle_fold(cl);

	अगर (has_children) अणु
		पूर्णांक child_rows = 0;

		hist_entry__init_have_children(he);
		browser->b.nr_entries -= he->nr_rows;

		अगर (he->leaf)
			browser->nr_callchain_rows -= he->nr_rows;
		अन्यथा
			browser->nr_hierarchy_entries -= he->nr_rows;

		अगर (symbol_conf.report_hierarchy)
			child_rows = hierarchy_count_rows(browser, he, true);

		अगर (he->unfolded) अणु
			अगर (he->leaf)
				he->nr_rows = callchain__count_rows(
						&he->sorted_chain);
			अन्यथा
				he->nr_rows = hierarchy_count_rows(browser, he, false);

			/* account gअक्रम children */
			अगर (symbol_conf.report_hierarchy)
				browser->b.nr_entries += child_rows - he->nr_rows;

			अगर (!he->leaf && he->nr_rows == 0) अणु
				he->has_no_entry = true;
				he->nr_rows = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (symbol_conf.report_hierarchy)
				browser->b.nr_entries -= child_rows - he->nr_rows;

			अगर (he->has_no_entry)
				he->has_no_entry = false;

			he->nr_rows = 0;
		पूर्ण

		browser->b.nr_entries += he->nr_rows;

		अगर (he->leaf)
			browser->nr_callchain_rows += he->nr_rows;
		अन्यथा
			browser->nr_hierarchy_entries += he->nr_rows;

		वापस true;
	पूर्ण

	/* If it करोesn't have children, no toggling perक्रमmed */
	वापस false;
पूर्ण

अटल पूर्णांक callchain_node__set_folding_rb_tree(काष्ठा callchain_node *node, bool unfold)
अणु
	पूर्णांक n = 0;
	काष्ठा rb_node *nd;

	क्रम (nd = rb_first(&node->rb_root); nd; nd = rb_next(nd)) अणु
		काष्ठा callchain_node *child = rb_entry(nd, काष्ठा callchain_node, rb_node);
		काष्ठा callchain_list *chain;
		bool has_children = false;

		list_क्रम_each_entry(chain, &child->val, list) अणु
			++n;
			callchain_list__set_folding(chain, unfold);
			has_children = chain->has_children;
		पूर्ण

		अगर (has_children)
			n += callchain_node__set_folding_rb_tree(child, unfold);
	पूर्ण

	वापस n;
पूर्ण

अटल पूर्णांक callchain_node__set_folding(काष्ठा callchain_node *node, bool unfold)
अणु
	काष्ठा callchain_list *chain;
	bool has_children = false;
	पूर्णांक n = 0;

	list_क्रम_each_entry(chain, &node->val, list) अणु
		++n;
		callchain_list__set_folding(chain, unfold);
		has_children = chain->has_children;
	पूर्ण

	अगर (has_children)
		n += callchain_node__set_folding_rb_tree(node, unfold);

	वापस n;
पूर्ण

अटल पूर्णांक callchain__set_folding(काष्ठा rb_root *chain, bool unfold)
अणु
	काष्ठा rb_node *nd;
	पूर्णांक n = 0;

	क्रम (nd = rb_first(chain); nd; nd = rb_next(nd)) अणु
		काष्ठा callchain_node *node = rb_entry(nd, काष्ठा callchain_node, rb_node);
		n += callchain_node__set_folding(node, unfold);
	पूर्ण

	वापस n;
पूर्ण

अटल पूर्णांक hierarchy_set_folding(काष्ठा hist_browser *hb, काष्ठा hist_entry *he,
				 bool unfold __maybe_unused)
अणु
	भग्न percent;
	काष्ठा rb_node *nd;
	काष्ठा hist_entry *child;
	पूर्णांक n = 0;

	क्रम (nd = rb_first_cached(&he->hroot_out); nd; nd = rb_next(nd)) अणु
		child = rb_entry(nd, काष्ठा hist_entry, rb_node);
		percent = hist_entry__get_percent_limit(child);
		अगर (!child->filtered && percent >= hb->min_pcnt)
			n++;
	पूर्ण

	वापस n;
पूर्ण

अटल व्योम __hist_entry__set_folding(काष्ठा hist_entry *he,
				      काष्ठा hist_browser *hb, bool unfold)
अणु
	hist_entry__init_have_children(he);
	he->unfolded = unfold ? he->has_children : false;

	अगर (he->has_children) अणु
		पूर्णांक n;

		अगर (he->leaf)
			n = callchain__set_folding(&he->sorted_chain, unfold);
		अन्यथा
			n = hierarchy_set_folding(hb, he, unfold);

		he->nr_rows = unfold ? n : 0;
	पूर्ण अन्यथा
		he->nr_rows = 0;
पूर्ण

अटल व्योम hist_entry__set_folding(काष्ठा hist_entry *he,
				    काष्ठा hist_browser *browser, bool unfold)
अणु
	द्विगुन percent;

	percent = hist_entry__get_percent_limit(he);
	अगर (he->filtered || percent < browser->min_pcnt)
		वापस;

	__hist_entry__set_folding(he, browser, unfold);

	अगर (!he->depth || unfold)
		browser->nr_hierarchy_entries++;
	अगर (he->leaf)
		browser->nr_callchain_rows += he->nr_rows;
	अन्यथा अगर (unfold && !hist_entry__has_hierarchy_children(he, browser->min_pcnt)) अणु
		browser->nr_hierarchy_entries++;
		he->has_no_entry = true;
		he->nr_rows = 1;
	पूर्ण अन्यथा
		he->has_no_entry = false;
पूर्ण

अटल व्योम
__hist_browser__set_folding(काष्ठा hist_browser *browser, bool unfold)
अणु
	काष्ठा rb_node *nd;
	काष्ठा hist_entry *he;

	nd = rb_first_cached(&browser->hists->entries);
	जबतक (nd) अणु
		he = rb_entry(nd, काष्ठा hist_entry, rb_node);

		/* set folding state even अगर it's currently folded */
		nd = __rb_hierarchy_next(nd, HMD_FORCE_CHILD);

		hist_entry__set_folding(he, browser, unfold);
	पूर्ण
पूर्ण

अटल व्योम hist_browser__set_folding(काष्ठा hist_browser *browser, bool unfold)
अणु
	browser->nr_hierarchy_entries = 0;
	browser->nr_callchain_rows = 0;
	__hist_browser__set_folding(browser, unfold);

	browser->b.nr_entries = hist_browser__nr_entries(browser);
	/* Go to the start, we may be way after valid entries after a collapse */
	ui_browser__reset_index(&browser->b);
पूर्ण

अटल व्योम hist_browser__set_folding_selected(काष्ठा hist_browser *browser, bool unfold)
अणु
	अगर (!browser->he_selection)
		वापस;

	hist_entry__set_folding(browser->he_selection, browser, unfold);
	browser->b.nr_entries = hist_browser__nr_entries(browser);
पूर्ण

अटल व्योम ui_browser__warn_lost_events(काष्ठा ui_browser *browser)
अणु
	ui_browser__warning(browser, 4,
		"Events are being lost, check IO/CPU overload!\n\n"
		"You may want to run 'perf' using a RT scheduler policy:\n\n"
		" perf top -r 80\n\n"
		"Or reduce the sampling frequency.");
पूर्ण

अटल पूर्णांक hist_browser__title(काष्ठा hist_browser *browser, अक्षर *bf, माप_प्रकार size)
अणु
	वापस browser->title ? browser->title(browser, bf, size) : 0;
पूर्ण

अटल पूर्णांक hist_browser__handle_hotkey(काष्ठा hist_browser *browser, bool warn_lost_event, अक्षर *title, माप_प्रकार size, पूर्णांक key)
अणु
	चयन (key) अणु
	हाल K_TIMER: अणु
		काष्ठा hist_browser_समयr *hbt = browser->hbt;
		काष्ठा evsel *evsel = hists_to_evsel(browser->hists);
		u64 nr_entries;

		WARN_ON_ONCE(!hbt);

		अगर (hbt)
			hbt->समयr(hbt->arg);

		अगर (hist_browser__has_filter(browser) || symbol_conf.report_hierarchy)
			hist_browser__update_nr_entries(browser);

		nr_entries = hist_browser__nr_entries(browser);
		ui_browser__update_nr_entries(&browser->b, nr_entries);

		अगर (warn_lost_event &&
		    (evsel->evlist->stats.nr_lost_warned !=
		     evsel->evlist->stats.nr_events[PERF_RECORD_LOST])) अणु
			evsel->evlist->stats.nr_lost_warned =
				evsel->evlist->stats.nr_events[PERF_RECORD_LOST];
			ui_browser__warn_lost_events(&browser->b);
		पूर्ण

		hist_browser__title(browser, title, size);
		ui_browser__show_title(&browser->b, title);
		अवरोध;
	पूर्ण
	हाल 'D': अणु /* Debug */
		काष्ठा hist_entry *h = rb_entry(browser->b.top, काष्ठा hist_entry, rb_node);
		अटल पूर्णांक seq;

		ui_helpline__pop();
		ui_helpline__fpush("%d: nr_ent=(%d,%d), etl: %d, rows=%d, idx=%d, fve: idx=%d, row_off=%d, nrows=%d",
				   seq++, browser->b.nr_entries, browser->hists->nr_entries,
				   browser->b.extra_title_lines, browser->b.rows,
				   browser->b.index, browser->b.top_idx, h->row_offset, h->nr_rows);
	पूर्ण
		अवरोध;
	हाल 'C':
		/* Collapse the whole world. */
		hist_browser__set_folding(browser, false);
		अवरोध;
	हाल 'c':
		/* Collapse the selected entry. */
		hist_browser__set_folding_selected(browser, false);
		अवरोध;
	हाल 'E':
		/* Expand the whole world. */
		hist_browser__set_folding(browser, true);
		अवरोध;
	हाल 'e':
		/* Expand the selected entry. */
		hist_browser__set_folding_selected(browser, !hist_browser__he_selection_unfolded(browser));
		अवरोध;
	हाल 'H':
		browser->show_headers = !browser->show_headers;
		hist_browser__update_rows(browser);
		अवरोध;
	हाल '+':
		अगर (hist_browser__toggle_fold(browser))
			अवरोध;
		/* fall thru */
	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hist_browser__run(काष्ठा hist_browser *browser, स्थिर अक्षर *help,
		      bool warn_lost_event, पूर्णांक key)
अणु
	अक्षर title[160];
	काष्ठा hist_browser_समयr *hbt = browser->hbt;
	पूर्णांक delay_secs = hbt ? hbt->refresh : 0;

	browser->b.entries = &browser->hists->entries;
	browser->b.nr_entries = hist_browser__nr_entries(browser);

	hist_browser__title(browser, title, माप(title));

	अगर (ui_browser__show(&browser->b, title, "%s", help) < 0)
		वापस -1;

	अगर (key && hist_browser__handle_hotkey(browser, warn_lost_event, title, माप(title), key))
		जाओ out;

	जबतक (1) अणु
		key = ui_browser__run(&browser->b, delay_secs);

		अगर (hist_browser__handle_hotkey(browser, warn_lost_event, title, माप(title), key))
			अवरोध;
	पूर्ण
out:
	ui_browser__hide(&browser->b);
	वापस key;
पूर्ण

काष्ठा callchain_prपूर्णांक_arg अणु
	/* क्रम hists browser */
	off_t	row_offset;
	bool	is_current_entry;

	/* क्रम file dump */
	खाता	*fp;
	पूर्णांक	prपूर्णांकed;
पूर्ण;

प्रकार व्योम (*prपूर्णांक_callchain_entry_fn)(काष्ठा hist_browser *browser,
					 काष्ठा callchain_list *chain,
					 स्थिर अक्षर *str, पूर्णांक offset,
					 अचिन्हित लघु row,
					 काष्ठा callchain_prपूर्णांक_arg *arg);

अटल व्योम hist_browser__show_callchain_entry(काष्ठा hist_browser *browser,
					       काष्ठा callchain_list *chain,
					       स्थिर अक्षर *str, पूर्णांक offset,
					       अचिन्हित लघु row,
					       काष्ठा callchain_prपूर्णांक_arg *arg)
अणु
	पूर्णांक color, width;
	अक्षर folded_sign = callchain_list__folded(chain);
	bool show_annotated = browser->show_dso && chain->ms.sym && symbol__annotation(chain->ms.sym)->src;

	color = HE_COLORSET_NORMAL;
	width = browser->b.width - (offset + 2);
	अगर (ui_browser__is_current_entry(&browser->b, row)) अणु
		browser->selection = &chain->ms;
		color = HE_COLORSET_SELECTED;
		arg->is_current_entry = true;
	पूर्ण

	ui_browser__set_color(&browser->b, color);
	ui_browser__जाओrc(&browser->b, row, 0);
	ui_browser__ग_लिखो_nstring(&browser->b, " ", offset);
	ui_browser__म_लिखो(&browser->b, "%c", folded_sign);
	ui_browser__ग_लिखो_graph(&browser->b, show_annotated ? SLSMG_RARROW_CHAR : ' ');
	ui_browser__ग_लिखो_nstring(&browser->b, str, width);
पूर्ण

अटल व्योम hist_browser__ख_लिखो_callchain_entry(काष्ठा hist_browser *b __maybe_unused,
						  काष्ठा callchain_list *chain,
						  स्थिर अक्षर *str, पूर्णांक offset,
						  अचिन्हित लघु row __maybe_unused,
						  काष्ठा callchain_prपूर्णांक_arg *arg)
अणु
	अक्षर folded_sign = callchain_list__folded(chain);

	arg->prपूर्णांकed += ख_लिखो(arg->fp, "%*s%c %s\n", offset, " ",
				folded_sign, str);
पूर्ण

प्रकार bool (*check_output_full_fn)(काष्ठा hist_browser *browser,
				     अचिन्हित लघु row);

अटल bool hist_browser__check_output_full(काष्ठा hist_browser *browser,
					    अचिन्हित लघु row)
अणु
	वापस browser->b.rows == row;
पूर्ण

अटल bool hist_browser__check_dump_full(काष्ठा hist_browser *browser __maybe_unused,
					  अचिन्हित लघु row __maybe_unused)
अणु
	वापस false;
पूर्ण

#घोषणा LEVEL_OFFSET_STEP 3

अटल पूर्णांक hist_browser__show_callchain_list(काष्ठा hist_browser *browser,
					     काष्ठा callchain_node *node,
					     काष्ठा callchain_list *chain,
					     अचिन्हित लघु row, u64 total,
					     bool need_percent, पूर्णांक offset,
					     prपूर्णांक_callchain_entry_fn prपूर्णांक,
					     काष्ठा callchain_prपूर्णांक_arg *arg)
अणु
	अक्षर bf[1024], *alloc_str;
	अक्षर buf[64], *alloc_str2;
	स्थिर अक्षर *str;
	पूर्णांक ret = 1;

	अगर (arg->row_offset != 0) अणु
		arg->row_offset--;
		वापस 0;
	पूर्ण

	alloc_str = शून्य;
	alloc_str2 = शून्य;

	str = callchain_list__sym_name(chain, bf, माप(bf),
				       browser->show_dso);

	अगर (symbol_conf.show_branchflag_count) अणु
		callchain_list_counts__म_लिखो_value(chain, शून्य,
						    buf, माप(buf));

		अगर (aप्र_लिखो(&alloc_str2, "%s%s", str, buf) < 0)
			str = "Not enough memory!";
		अन्यथा
			str = alloc_str2;
	पूर्ण

	अगर (need_percent) अणु
		callchain_node__scnम_लिखो_value(node, buf, माप(buf),
						total);

		अगर (aप्र_लिखो(&alloc_str, "%s %s", buf, str) < 0)
			str = "Not enough memory!";
		अन्यथा
			str = alloc_str;
	पूर्ण

	prपूर्णांक(browser, chain, str, offset, row, arg);
	मुक्त(alloc_str);
	मुक्त(alloc_str2);

	वापस ret;
पूर्ण

अटल bool check_percent_display(काष्ठा rb_node *node, u64 parent_total)
अणु
	काष्ठा callchain_node *child;

	अगर (node == शून्य)
		वापस false;

	अगर (rb_next(node))
		वापस true;

	child = rb_entry(node, काष्ठा callchain_node, rb_node);
	वापस callchain_cumul_hits(child) != parent_total;
पूर्ण

अटल पूर्णांक hist_browser__show_callchain_flat(काष्ठा hist_browser *browser,
					     काष्ठा rb_root *root,
					     अचिन्हित लघु row, u64 total,
					     u64 parent_total,
					     prपूर्णांक_callchain_entry_fn prपूर्णांक,
					     काष्ठा callchain_prपूर्णांक_arg *arg,
					     check_output_full_fn is_output_full)
अणु
	काष्ठा rb_node *node;
	पूर्णांक first_row = row, offset = LEVEL_OFFSET_STEP;
	bool need_percent;

	node = rb_first(root);
	need_percent = check_percent_display(node, parent_total);

	जबतक (node) अणु
		काष्ठा callchain_node *child = rb_entry(node, काष्ठा callchain_node, rb_node);
		काष्ठा rb_node *next = rb_next(node);
		काष्ठा callchain_list *chain;
		अक्षर folded_sign = ' ';
		पूर्णांक first = true;
		पूर्णांक extra_offset = 0;

		list_क्रम_each_entry(chain, &child->parent_val, list) अणु
			bool was_first = first;

			अगर (first)
				first = false;
			अन्यथा अगर (need_percent)
				extra_offset = LEVEL_OFFSET_STEP;

			folded_sign = callchain_list__folded(chain);

			row += hist_browser__show_callchain_list(browser, child,
							chain, row, total,
							was_first && need_percent,
							offset + extra_offset,
							prपूर्णांक, arg);

			अगर (is_output_full(browser, row))
				जाओ out;

			अगर (folded_sign == '+')
				जाओ next;
		पूर्ण

		list_क्रम_each_entry(chain, &child->val, list) अणु
			bool was_first = first;

			अगर (first)
				first = false;
			अन्यथा अगर (need_percent)
				extra_offset = LEVEL_OFFSET_STEP;

			folded_sign = callchain_list__folded(chain);

			row += hist_browser__show_callchain_list(browser, child,
							chain, row, total,
							was_first && need_percent,
							offset + extra_offset,
							prपूर्णांक, arg);

			अगर (is_output_full(browser, row))
				जाओ out;

			अगर (folded_sign == '+')
				अवरोध;
		पूर्ण

next:
		अगर (is_output_full(browser, row))
			अवरोध;
		node = next;
	पूर्ण
out:
	वापस row - first_row;
पूर्ण

अटल अक्षर *hist_browser__folded_callchain_str(काष्ठा hist_browser *browser,
						काष्ठा callchain_list *chain,
						अक्षर *value_str, अक्षर *old_str)
अणु
	अक्षर bf[1024];
	स्थिर अक्षर *str;
	अक्षर *new;

	str = callchain_list__sym_name(chain, bf, माप(bf),
				       browser->show_dso);
	अगर (old_str) अणु
		अगर (aप्र_लिखो(&new, "%s%s%s", old_str,
			     symbol_conf.field_sep ?: ";", str) < 0)
			new = शून्य;
	पूर्ण अन्यथा अणु
		अगर (value_str) अणु
			अगर (aप्र_लिखो(&new, "%s %s", value_str, str) < 0)
				new = शून्य;
		पूर्ण अन्यथा अणु
			अगर (aप्र_लिखो(&new, "%s", str) < 0)
				new = शून्य;
		पूर्ण
	पूर्ण
	वापस new;
पूर्ण

अटल पूर्णांक hist_browser__show_callchain_folded(काष्ठा hist_browser *browser,
					       काष्ठा rb_root *root,
					       अचिन्हित लघु row, u64 total,
					       u64 parent_total,
					       prपूर्णांक_callchain_entry_fn prपूर्णांक,
					       काष्ठा callchain_prपूर्णांक_arg *arg,
					       check_output_full_fn is_output_full)
अणु
	काष्ठा rb_node *node;
	पूर्णांक first_row = row, offset = LEVEL_OFFSET_STEP;
	bool need_percent;

	node = rb_first(root);
	need_percent = check_percent_display(node, parent_total);

	जबतक (node) अणु
		काष्ठा callchain_node *child = rb_entry(node, काष्ठा callchain_node, rb_node);
		काष्ठा rb_node *next = rb_next(node);
		काष्ठा callchain_list *chain, *first_chain = शून्य;
		पूर्णांक first = true;
		अक्षर *value_str = शून्य, *value_str_alloc = शून्य;
		अक्षर *chain_str = शून्य, *chain_str_alloc = शून्य;

		अगर (arg->row_offset != 0) अणु
			arg->row_offset--;
			जाओ next;
		पूर्ण

		अगर (need_percent) अणु
			अक्षर buf[64];

			callchain_node__scnम_लिखो_value(child, buf, माप(buf), total);
			अगर (aप्र_लिखो(&value_str, "%s", buf) < 0) अणु
				value_str = (अक्षर *)"<...>";
				जाओ करो_prपूर्णांक;
			पूर्ण
			value_str_alloc = value_str;
		पूर्ण

		list_क्रम_each_entry(chain, &child->parent_val, list) अणु
			chain_str = hist_browser__folded_callchain_str(browser,
						chain, value_str, chain_str);
			अगर (first) अणु
				first = false;
				first_chain = chain;
			पूर्ण

			अगर (chain_str == शून्य) अणु
				chain_str = (अक्षर *)"Not enough memory!";
				जाओ करो_prपूर्णांक;
			पूर्ण

			chain_str_alloc = chain_str;
		पूर्ण

		list_क्रम_each_entry(chain, &child->val, list) अणु
			chain_str = hist_browser__folded_callchain_str(browser,
						chain, value_str, chain_str);
			अगर (first) अणु
				first = false;
				first_chain = chain;
			पूर्ण

			अगर (chain_str == शून्य) अणु
				chain_str = (अक्षर *)"Not enough memory!";
				जाओ करो_prपूर्णांक;
			पूर्ण

			chain_str_alloc = chain_str;
		पूर्ण

करो_prपूर्णांक:
		prपूर्णांक(browser, first_chain, chain_str, offset, row++, arg);
		मुक्त(value_str_alloc);
		मुक्त(chain_str_alloc);

next:
		अगर (is_output_full(browser, row))
			अवरोध;
		node = next;
	पूर्ण

	वापस row - first_row;
पूर्ण

अटल पूर्णांक hist_browser__show_callchain_graph(काष्ठा hist_browser *browser,
					काष्ठा rb_root *root, पूर्णांक level,
					अचिन्हित लघु row, u64 total,
					u64 parent_total,
					prपूर्णांक_callchain_entry_fn prपूर्णांक,
					काष्ठा callchain_prपूर्णांक_arg *arg,
					check_output_full_fn is_output_full)
अणु
	काष्ठा rb_node *node;
	पूर्णांक first_row = row, offset = level * LEVEL_OFFSET_STEP;
	bool need_percent;
	u64 percent_total = total;

	अगर (callchain_param.mode == CHAIN_GRAPH_REL)
		percent_total = parent_total;

	node = rb_first(root);
	need_percent = check_percent_display(node, parent_total);

	जबतक (node) अणु
		काष्ठा callchain_node *child = rb_entry(node, काष्ठा callchain_node, rb_node);
		काष्ठा rb_node *next = rb_next(node);
		काष्ठा callchain_list *chain;
		अक्षर folded_sign = ' ';
		पूर्णांक first = true;
		पूर्णांक extra_offset = 0;

		list_क्रम_each_entry(chain, &child->val, list) अणु
			bool was_first = first;

			अगर (first)
				first = false;
			अन्यथा अगर (need_percent)
				extra_offset = LEVEL_OFFSET_STEP;

			folded_sign = callchain_list__folded(chain);

			row += hist_browser__show_callchain_list(browser, child,
							chain, row, percent_total,
							was_first && need_percent,
							offset + extra_offset,
							prपूर्णांक, arg);

			अगर (is_output_full(browser, row))
				जाओ out;

			अगर (folded_sign == '+')
				अवरोध;
		पूर्ण

		अगर (folded_sign == '-') अणु
			स्थिर पूर्णांक new_level = level + (extra_offset ? 2 : 1);

			row += hist_browser__show_callchain_graph(browser, &child->rb_root,
							    new_level, row, total,
							    child->children_hit,
							    prपूर्णांक, arg, is_output_full);
		पूर्ण
		अगर (is_output_full(browser, row))
			अवरोध;
		node = next;
	पूर्ण
out:
	वापस row - first_row;
पूर्ण

अटल पूर्णांक hist_browser__show_callchain(काष्ठा hist_browser *browser,
					काष्ठा hist_entry *entry, पूर्णांक level,
					अचिन्हित लघु row,
					prपूर्णांक_callchain_entry_fn prपूर्णांक,
					काष्ठा callchain_prपूर्णांक_arg *arg,
					check_output_full_fn is_output_full)
अणु
	u64 total = hists__total_period(entry->hists);
	u64 parent_total;
	पूर्णांक prपूर्णांकed;

	अगर (symbol_conf.cumulate_callchain)
		parent_total = entry->stat_acc->period;
	अन्यथा
		parent_total = entry->stat.period;

	अगर (callchain_param.mode == CHAIN_FLAT) अणु
		prपूर्णांकed = hist_browser__show_callchain_flat(browser,
						&entry->sorted_chain, row,
						total, parent_total, prपूर्णांक, arg,
						is_output_full);
	पूर्ण अन्यथा अगर (callchain_param.mode == CHAIN_FOLDED) अणु
		prपूर्णांकed = hist_browser__show_callchain_folded(browser,
						&entry->sorted_chain, row,
						total, parent_total, prपूर्णांक, arg,
						is_output_full);
	पूर्ण अन्यथा अणु
		prपूर्णांकed = hist_browser__show_callchain_graph(browser,
						&entry->sorted_chain, level, row,
						total, parent_total, prपूर्णांक, arg,
						is_output_full);
	पूर्ण

	अगर (arg->is_current_entry)
		browser->he_selection = entry;

	वापस prपूर्णांकed;
पूर्ण

काष्ठा hpp_arg अणु
	काष्ठा ui_browser *b;
	अक्षर folded_sign;
	bool current_entry;
पूर्ण;

पूर्णांक __hpp__slsmg_color_म_लिखो(काष्ठा perf_hpp *hpp, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा hpp_arg *arg = hpp->ptr;
	पूर्णांक ret, len;
	बहु_सूची args;
	द्विगुन percent;

	बहु_शुरू(args, fmt);
	len = बहु_तर्क(args, पूर्णांक);
	percent = बहु_तर्क(args, द्विगुन);
	बहु_पूर्ण(args);

	ui_browser__set_percent_color(arg->b, percent, arg->current_entry);

	ret = scnम_लिखो(hpp->buf, hpp->size, fmt, len, percent);
	ui_browser__म_लिखो(arg->b, "%s", hpp->buf);

	वापस ret;
पूर्ण

#घोषणा __HPP_COLOR_PERCENT_FN(_type, _field)				\
अटल u64 __hpp_get_##_field(काष्ठा hist_entry *he)			\
अणु									\
	वापस he->stat._field;						\
पूर्ण									\
									\
अटल पूर्णांक								\
hist_browser__hpp_color_##_type(काष्ठा perf_hpp_fmt *fmt,		\
				काष्ठा perf_hpp *hpp,			\
				काष्ठा hist_entry *he)			\
अणु									\
	वापस hpp__fmt(fmt, hpp, he, __hpp_get_##_field, " %*.2f%%",	\
			__hpp__slsmg_color_म_लिखो, true);		\
पूर्ण

#घोषणा __HPP_COLOR_ACC_PERCENT_FN(_type, _field)			\
अटल u64 __hpp_get_acc_##_field(काष्ठा hist_entry *he)		\
अणु									\
	वापस he->stat_acc->_field;					\
पूर्ण									\
									\
अटल पूर्णांक								\
hist_browser__hpp_color_##_type(काष्ठा perf_hpp_fmt *fmt,		\
				काष्ठा perf_hpp *hpp,			\
				काष्ठा hist_entry *he)			\
अणु									\
	अगर (!symbol_conf.cumulate_callchain) अणु				\
		काष्ठा hpp_arg *arg = hpp->ptr;				\
		पूर्णांक len = fmt->user_len ?: fmt->len;			\
		पूर्णांक ret = scnम_लिखो(hpp->buf, hpp->size,		\
				    "%*s", len, "N/A");			\
		ui_browser__म_लिखो(arg->b, "%s", hpp->buf);		\
									\
		वापस ret;						\
	पूर्ण								\
	वापस hpp__fmt(fmt, hpp, he, __hpp_get_acc_##_field,		\
			" %*.2f%%", __hpp__slsmg_color_म_लिखो, true);	\
पूर्ण

__HPP_COLOR_PERCENT_FN(overhead, period)
__HPP_COLOR_PERCENT_FN(overhead_sys, period_sys)
__HPP_COLOR_PERCENT_FN(overhead_us, period_us)
__HPP_COLOR_PERCENT_FN(overhead_guest_sys, period_guest_sys)
__HPP_COLOR_PERCENT_FN(overhead_guest_us, period_guest_us)
__HPP_COLOR_ACC_PERCENT_FN(overhead_acc, period)

#अघोषित __HPP_COLOR_PERCENT_FN
#अघोषित __HPP_COLOR_ACC_PERCENT_FN

व्योम hist_browser__init_hpp(व्योम)
अणु
	perf_hpp__क्रमmat[PERF_HPP__OVERHEAD].color =
				hist_browser__hpp_color_overhead;
	perf_hpp__क्रमmat[PERF_HPP__OVERHEAD_SYS].color =
				hist_browser__hpp_color_overhead_sys;
	perf_hpp__क्रमmat[PERF_HPP__OVERHEAD_US].color =
				hist_browser__hpp_color_overhead_us;
	perf_hpp__क्रमmat[PERF_HPP__OVERHEAD_GUEST_SYS].color =
				hist_browser__hpp_color_overhead_guest_sys;
	perf_hpp__क्रमmat[PERF_HPP__OVERHEAD_GUEST_US].color =
				hist_browser__hpp_color_overhead_guest_us;
	perf_hpp__क्रमmat[PERF_HPP__OVERHEAD_ACC].color =
				hist_browser__hpp_color_overhead_acc;

	res_sample_init();
पूर्ण

अटल पूर्णांक hist_browser__show_entry(काष्ठा hist_browser *browser,
				    काष्ठा hist_entry *entry,
				    अचिन्हित लघु row)
अणु
	पूर्णांक prपूर्णांकed = 0;
	पूर्णांक width = browser->b.width;
	अक्षर folded_sign = ' ';
	bool current_entry = ui_browser__is_current_entry(&browser->b, row);
	bool use_callchain = hist_entry__has_callchains(entry) && symbol_conf.use_callchain;
	off_t row_offset = entry->row_offset;
	bool first = true;
	काष्ठा perf_hpp_fmt *fmt;

	अगर (current_entry) अणु
		browser->he_selection = entry;
		browser->selection = &entry->ms;
	पूर्ण

	अगर (use_callchain) अणु
		hist_entry__init_have_children(entry);
		folded_sign = hist_entry__folded(entry);
	पूर्ण

	अगर (row_offset == 0) अणु
		काष्ठा hpp_arg arg = अणु
			.b		= &browser->b,
			.folded_sign	= folded_sign,
			.current_entry	= current_entry,
		पूर्ण;
		पूर्णांक column = 0;

		ui_browser__जाओrc(&browser->b, row, 0);

		hists__क्रम_each_क्रमmat(browser->hists, fmt) अणु
			अक्षर s[2048];
			काष्ठा perf_hpp hpp = अणु
				.buf	= s,
				.size	= माप(s),
				.ptr	= &arg,
			पूर्ण;

			अगर (perf_hpp__should_skip(fmt, entry->hists) ||
			    column++ < browser->b.horiz_scroll)
				जारी;

			अगर (current_entry && browser->b.navkeypressed) अणु
				ui_browser__set_color(&browser->b,
						      HE_COLORSET_SELECTED);
			पूर्ण अन्यथा अणु
				ui_browser__set_color(&browser->b,
						      HE_COLORSET_NORMAL);
			पूर्ण

			अगर (first) अणु
				अगर (use_callchain) अणु
					ui_browser__म_लिखो(&browser->b, "%c ", folded_sign);
					width -= 2;
				पूर्ण
				first = false;
			पूर्ण अन्यथा अणु
				ui_browser__म_लिखो(&browser->b, "  ");
				width -= 2;
			पूर्ण

			अगर (fmt->color) अणु
				पूर्णांक ret = fmt->color(fmt, &hpp, entry);
				hist_entry__snम_लिखो_alignment(entry, &hpp, fmt, ret);
				/*
				 * fmt->color() alपढ़ोy used ui_browser to
				 * prपूर्णांक the non alignment bits, skip it (+ret):
				 */
				ui_browser__म_लिखो(&browser->b, "%s", s + ret);
			पूर्ण अन्यथा अणु
				hist_entry__snम_लिखो_alignment(entry, &hpp, fmt, fmt->entry(fmt, &hpp, entry));
				ui_browser__म_लिखो(&browser->b, "%s", s);
			पूर्ण
			width -= hpp.buf - s;
		पूर्ण

		/* The scroll bar isn't being used */
		अगर (!browser->b.navkeypressed)
			width += 1;

		ui_browser__ग_लिखो_nstring(&browser->b, "", width);

		++row;
		++prपूर्णांकed;
	पूर्ण अन्यथा
		--row_offset;

	अगर (folded_sign == '-' && row != browser->b.rows) अणु
		काष्ठा callchain_prपूर्णांक_arg arg = अणु
			.row_offset = row_offset,
			.is_current_entry = current_entry,
		पूर्ण;

		prपूर्णांकed += hist_browser__show_callchain(browser,
				entry, 1, row,
				hist_browser__show_callchain_entry,
				&arg,
				hist_browser__check_output_full);
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक hist_browser__show_hierarchy_entry(काष्ठा hist_browser *browser,
					      काष्ठा hist_entry *entry,
					      अचिन्हित लघु row,
					      पूर्णांक level)
अणु
	पूर्णांक prपूर्णांकed = 0;
	पूर्णांक width = browser->b.width;
	अक्षर folded_sign = ' ';
	bool current_entry = ui_browser__is_current_entry(&browser->b, row);
	off_t row_offset = entry->row_offset;
	bool first = true;
	काष्ठा perf_hpp_fmt *fmt;
	काष्ठा perf_hpp_list_node *fmt_node;
	काष्ठा hpp_arg arg = अणु
		.b		= &browser->b,
		.current_entry	= current_entry,
	पूर्ण;
	पूर्णांक column = 0;
	पूर्णांक hierarchy_indent = (entry->hists->nr_hpp_node - 2) * HIERARCHY_INDENT;

	अगर (current_entry) अणु
		browser->he_selection = entry;
		browser->selection = &entry->ms;
	पूर्ण

	hist_entry__init_have_children(entry);
	folded_sign = hist_entry__folded(entry);
	arg.folded_sign = folded_sign;

	अगर (entry->leaf && row_offset) अणु
		row_offset--;
		जाओ show_callchain;
	पूर्ण

	ui_browser__जाओrc(&browser->b, row, 0);

	अगर (current_entry && browser->b.navkeypressed)
		ui_browser__set_color(&browser->b, HE_COLORSET_SELECTED);
	अन्यथा
		ui_browser__set_color(&browser->b, HE_COLORSET_NORMAL);

	ui_browser__ग_लिखो_nstring(&browser->b, "", level * HIERARCHY_INDENT);
	width -= level * HIERARCHY_INDENT;

	/* the first hpp_list_node is क्रम overhead columns */
	fmt_node = list_first_entry(&entry->hists->hpp_क्रमmats,
				    काष्ठा perf_hpp_list_node, list);
	perf_hpp_list__क्रम_each_क्रमmat(&fmt_node->hpp, fmt) अणु
		अक्षर s[2048];
		काष्ठा perf_hpp hpp = अणु
			.buf		= s,
			.size		= माप(s),
			.ptr		= &arg,
		पूर्ण;

		अगर (perf_hpp__should_skip(fmt, entry->hists) ||
		    column++ < browser->b.horiz_scroll)
			जारी;

		अगर (current_entry && browser->b.navkeypressed) अणु
			ui_browser__set_color(&browser->b,
					      HE_COLORSET_SELECTED);
		पूर्ण अन्यथा अणु
			ui_browser__set_color(&browser->b,
					      HE_COLORSET_NORMAL);
		पूर्ण

		अगर (first) अणु
			ui_browser__म_लिखो(&browser->b, "%c ", folded_sign);
			width -= 2;
			first = false;
		पूर्ण अन्यथा अणु
			ui_browser__म_लिखो(&browser->b, "  ");
			width -= 2;
		पूर्ण

		अगर (fmt->color) अणु
			पूर्णांक ret = fmt->color(fmt, &hpp, entry);
			hist_entry__snम_लिखो_alignment(entry, &hpp, fmt, ret);
			/*
			 * fmt->color() alपढ़ोy used ui_browser to
			 * prपूर्णांक the non alignment bits, skip it (+ret):
			 */
			ui_browser__म_लिखो(&browser->b, "%s", s + ret);
		पूर्ण अन्यथा अणु
			पूर्णांक ret = fmt->entry(fmt, &hpp, entry);
			hist_entry__snम_लिखो_alignment(entry, &hpp, fmt, ret);
			ui_browser__म_लिखो(&browser->b, "%s", s);
		पूर्ण
		width -= hpp.buf - s;
	पूर्ण

	अगर (!first) अणु
		ui_browser__ग_लिखो_nstring(&browser->b, "", hierarchy_indent);
		width -= hierarchy_indent;
	पूर्ण

	अगर (column >= browser->b.horiz_scroll) अणु
		अक्षर s[2048];
		काष्ठा perf_hpp hpp = अणु
			.buf		= s,
			.size		= माप(s),
			.ptr		= &arg,
		पूर्ण;

		अगर (current_entry && browser->b.navkeypressed) अणु
			ui_browser__set_color(&browser->b,
					      HE_COLORSET_SELECTED);
		पूर्ण अन्यथा अणु
			ui_browser__set_color(&browser->b,
					      HE_COLORSET_NORMAL);
		पूर्ण

		perf_hpp_list__क्रम_each_क्रमmat(entry->hpp_list, fmt) अणु
			अगर (first) अणु
				ui_browser__म_लिखो(&browser->b, "%c ", folded_sign);
				first = false;
			पूर्ण अन्यथा अणु
				ui_browser__ग_लिखो_nstring(&browser->b, "", 2);
			पूर्ण

			width -= 2;

			/*
			 * No need to call hist_entry__snम_लिखो_alignment()
			 * since this fmt is always the last column in the
			 * hierarchy mode.
			 */
			अगर (fmt->color) अणु
				width -= fmt->color(fmt, &hpp, entry);
			पूर्ण अन्यथा अणु
				पूर्णांक i = 0;

				width -= fmt->entry(fmt, &hpp, entry);
				ui_browser__म_लिखो(&browser->b, "%s", skip_spaces(s));

				जबतक (है_खाली(s[i++]))
					width++;
			पूर्ण
		पूर्ण
	पूर्ण

	/* The scroll bar isn't being used */
	अगर (!browser->b.navkeypressed)
		width += 1;

	ui_browser__ग_लिखो_nstring(&browser->b, "", width);

	++row;
	++prपूर्णांकed;

show_callchain:
	अगर (entry->leaf && folded_sign == '-' && row != browser->b.rows) अणु
		काष्ठा callchain_prपूर्णांक_arg carg = अणु
			.row_offset = row_offset,
		पूर्ण;

		prपूर्णांकed += hist_browser__show_callchain(browser, entry,
					level + 1, row,
					hist_browser__show_callchain_entry, &carg,
					hist_browser__check_output_full);
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक hist_browser__show_no_entry(काष्ठा hist_browser *browser,
				       अचिन्हित लघु row, पूर्णांक level)
अणु
	पूर्णांक width = browser->b.width;
	bool current_entry = ui_browser__is_current_entry(&browser->b, row);
	bool first = true;
	पूर्णांक column = 0;
	पूर्णांक ret;
	काष्ठा perf_hpp_fmt *fmt;
	काष्ठा perf_hpp_list_node *fmt_node;
	पूर्णांक indent = browser->hists->nr_hpp_node - 2;

	अगर (current_entry) अणु
		browser->he_selection = शून्य;
		browser->selection = शून्य;
	पूर्ण

	ui_browser__जाओrc(&browser->b, row, 0);

	अगर (current_entry && browser->b.navkeypressed)
		ui_browser__set_color(&browser->b, HE_COLORSET_SELECTED);
	अन्यथा
		ui_browser__set_color(&browser->b, HE_COLORSET_NORMAL);

	ui_browser__ग_लिखो_nstring(&browser->b, "", level * HIERARCHY_INDENT);
	width -= level * HIERARCHY_INDENT;

	/* the first hpp_list_node is क्रम overhead columns */
	fmt_node = list_first_entry(&browser->hists->hpp_क्रमmats,
				    काष्ठा perf_hpp_list_node, list);
	perf_hpp_list__क्रम_each_क्रमmat(&fmt_node->hpp, fmt) अणु
		अगर (perf_hpp__should_skip(fmt, browser->hists) ||
		    column++ < browser->b.horiz_scroll)
			जारी;

		ret = fmt->width(fmt, शून्य, browser->hists);

		अगर (first) अणु
			/* क्रम folded sign */
			first = false;
			ret++;
		पूर्ण अन्यथा अणु
			/* space between columns */
			ret += 2;
		पूर्ण

		ui_browser__ग_लिखो_nstring(&browser->b, "", ret);
		width -= ret;
	पूर्ण

	ui_browser__ग_लिखो_nstring(&browser->b, "", indent * HIERARCHY_INDENT);
	width -= indent * HIERARCHY_INDENT;

	अगर (column >= browser->b.horiz_scroll) अणु
		अक्षर buf[32];

		ret = snम_लिखो(buf, माप(buf), "no entry >= %.2f%%", browser->min_pcnt);
		ui_browser__म_लिखो(&browser->b, "  %s", buf);
		width -= ret + 2;
	पूर्ण

	/* The scroll bar isn't being used */
	अगर (!browser->b.navkeypressed)
		width += 1;

	ui_browser__ग_लिखो_nstring(&browser->b, "", width);
	वापस 1;
पूर्ण

अटल पूर्णांक advance_hpp_check(काष्ठा perf_hpp *hpp, पूर्णांक inc)
अणु
	advance_hpp(hpp, inc);
	वापस hpp->size <= 0;
पूर्ण

अटल पूर्णांक
hists_browser__scnम_लिखो_headers(काष्ठा hist_browser *browser, अक्षर *buf,
				 माप_प्रकार size, पूर्णांक line)
अणु
	काष्ठा hists *hists = browser->hists;
	काष्ठा perf_hpp dummy_hpp = अणु
		.buf    = buf,
		.size   = size,
	पूर्ण;
	काष्ठा perf_hpp_fmt *fmt;
	माप_प्रकार ret = 0;
	पूर्णांक column = 0;
	पूर्णांक span = 0;

	अगर (hists__has_callchains(hists) && symbol_conf.use_callchain) अणु
		ret = scnम_लिखो(buf, size, "  ");
		अगर (advance_hpp_check(&dummy_hpp, ret))
			वापस ret;
	पूर्ण

	hists__क्रम_each_क्रमmat(browser->hists, fmt) अणु
		अगर (perf_hpp__should_skip(fmt, hists)  || column++ < browser->b.horiz_scroll)
			जारी;

		ret = fmt->header(fmt, &dummy_hpp, hists, line, &span);
		अगर (advance_hpp_check(&dummy_hpp, ret))
			अवरोध;

		अगर (span)
			जारी;

		ret = scnम_लिखो(dummy_hpp.buf, dummy_hpp.size, "  ");
		अगर (advance_hpp_check(&dummy_hpp, ret))
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hists_browser__scnम_लिखो_hierarchy_headers(काष्ठा hist_browser *browser, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा hists *hists = browser->hists;
	काष्ठा perf_hpp dummy_hpp = अणु
		.buf    = buf,
		.size   = size,
	पूर्ण;
	काष्ठा perf_hpp_fmt *fmt;
	काष्ठा perf_hpp_list_node *fmt_node;
	माप_प्रकार ret = 0;
	पूर्णांक column = 0;
	पूर्णांक indent = hists->nr_hpp_node - 2;
	bool first_node, first_col;

	ret = scnम_लिखो(buf, size, "  ");
	अगर (advance_hpp_check(&dummy_hpp, ret))
		वापस ret;

	first_node = true;
	/* the first hpp_list_node is क्रम overhead columns */
	fmt_node = list_first_entry(&hists->hpp_क्रमmats,
				    काष्ठा perf_hpp_list_node, list);
	perf_hpp_list__क्रम_each_क्रमmat(&fmt_node->hpp, fmt) अणु
		अगर (column++ < browser->b.horiz_scroll)
			जारी;

		ret = fmt->header(fmt, &dummy_hpp, hists, 0, शून्य);
		अगर (advance_hpp_check(&dummy_hpp, ret))
			अवरोध;

		ret = scnम_लिखो(dummy_hpp.buf, dummy_hpp.size, "  ");
		अगर (advance_hpp_check(&dummy_hpp, ret))
			अवरोध;

		first_node = false;
	पूर्ण

	अगर (!first_node) अणु
		ret = scnम_लिखो(dummy_hpp.buf, dummy_hpp.size, "%*s",
				indent * HIERARCHY_INDENT, "");
		अगर (advance_hpp_check(&dummy_hpp, ret))
			वापस ret;
	पूर्ण

	first_node = true;
	list_क्रम_each_entry_जारी(fmt_node, &hists->hpp_क्रमmats, list) अणु
		अगर (!first_node) अणु
			ret = scnम_लिखो(dummy_hpp.buf, dummy_hpp.size, " / ");
			अगर (advance_hpp_check(&dummy_hpp, ret))
				अवरोध;
		पूर्ण
		first_node = false;

		first_col = true;
		perf_hpp_list__क्रम_each_क्रमmat(&fmt_node->hpp, fmt) अणु
			अक्षर *start;

			अगर (perf_hpp__should_skip(fmt, hists))
				जारी;

			अगर (!first_col) अणु
				ret = scnम_लिखो(dummy_hpp.buf, dummy_hpp.size, "+");
				अगर (advance_hpp_check(&dummy_hpp, ret))
					अवरोध;
			पूर्ण
			first_col = false;

			ret = fmt->header(fmt, &dummy_hpp, hists, 0, शून्य);
			dummy_hpp.buf[ret] = '\0';

			start = strim(dummy_hpp.buf);
			ret = म_माप(start);

			अगर (start != dummy_hpp.buf)
				स_हटाओ(dummy_hpp.buf, start, ret + 1);

			अगर (advance_hpp_check(&dummy_hpp, ret))
				अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम hists_browser__hierarchy_headers(काष्ठा hist_browser *browser)
अणु
	अक्षर headers[1024];

	hists_browser__scnम_लिखो_hierarchy_headers(browser, headers,
						   माप(headers));

	ui_browser__जाओrc(&browser->b, 0, 0);
	ui_browser__set_color(&browser->b, HE_COLORSET_ROOT);
	ui_browser__ग_लिखो_nstring(&browser->b, headers, browser->b.width + 1);
पूर्ण

अटल व्योम hists_browser__headers(काष्ठा hist_browser *browser)
अणु
	काष्ठा hists *hists = browser->hists;
	काष्ठा perf_hpp_list *hpp_list = hists->hpp_list;

	पूर्णांक line;

	क्रम (line = 0; line < hpp_list->nr_header_lines; line++) अणु
		अक्षर headers[1024];

		hists_browser__scnम_लिखो_headers(browser, headers,
						 माप(headers), line);

		ui_browser__जाओrc_title(&browser->b, line, 0);
		ui_browser__set_color(&browser->b, HE_COLORSET_ROOT);
		ui_browser__ग_लिखो_nstring(&browser->b, headers, browser->b.width + 1);
	पूर्ण
पूर्ण

अटल व्योम hist_browser__show_headers(काष्ठा hist_browser *browser)
अणु
	अगर (symbol_conf.report_hierarchy)
		hists_browser__hierarchy_headers(browser);
	अन्यथा
		hists_browser__headers(browser);
पूर्ण

अटल व्योम ui_browser__hists_init_top(काष्ठा ui_browser *browser)
अणु
	अगर (browser->top == शून्य) अणु
		काष्ठा hist_browser *hb;

		hb = container_of(browser, काष्ठा hist_browser, b);
		browser->top = rb_first_cached(&hb->hists->entries);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक hist_browser__refresh(काष्ठा ui_browser *browser)
अणु
	अचिन्हित row = 0;
	काष्ठा rb_node *nd;
	काष्ठा hist_browser *hb = container_of(browser, काष्ठा hist_browser, b);

	अगर (hb->show_headers)
		hist_browser__show_headers(hb);

	ui_browser__hists_init_top(browser);
	hb->he_selection = शून्य;
	hb->selection = शून्य;

	क्रम (nd = browser->top; nd; nd = rb_hierarchy_next(nd)) अणु
		काष्ठा hist_entry *h = rb_entry(nd, काष्ठा hist_entry, rb_node);
		भग्न percent;

		अगर (h->filtered) अणु
			/* let it move to sibling */
			h->unfolded = false;
			जारी;
		पूर्ण

		अगर (symbol_conf.report_inभागidual_block)
			percent = block_info__total_cycles_percent(h);
		अन्यथा
			percent = hist_entry__get_percent_limit(h);

		अगर (percent < hb->min_pcnt)
			जारी;

		अगर (symbol_conf.report_hierarchy) अणु
			row += hist_browser__show_hierarchy_entry(hb, h, row,
								  h->depth);
			अगर (row == browser->rows)
				अवरोध;

			अगर (h->has_no_entry) अणु
				hist_browser__show_no_entry(hb, row, h->depth + 1);
				row++;
			पूर्ण
		पूर्ण अन्यथा अणु
			row += hist_browser__show_entry(hb, h, row);
		पूर्ण

		अगर (row == browser->rows)
			अवरोध;
	पूर्ण

	वापस row;
पूर्ण

अटल काष्ठा rb_node *hists__filter_entries(काष्ठा rb_node *nd,
					     भग्न min_pcnt)
अणु
	जबतक (nd != शून्य) अणु
		काष्ठा hist_entry *h = rb_entry(nd, काष्ठा hist_entry, rb_node);
		भग्न percent = hist_entry__get_percent_limit(h);

		अगर (!h->filtered && percent >= min_pcnt)
			वापस nd;

		/*
		 * If it's filtered, its all children also were filtered.
		 * So move to sibling node.
		 */
		अगर (rb_next(nd))
			nd = rb_next(nd);
		अन्यथा
			nd = rb_hierarchy_next(nd);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा rb_node *hists__filter_prev_entries(काष्ठा rb_node *nd,
						  भग्न min_pcnt)
अणु
	जबतक (nd != शून्य) अणु
		काष्ठा hist_entry *h = rb_entry(nd, काष्ठा hist_entry, rb_node);
		भग्न percent = hist_entry__get_percent_limit(h);

		अगर (!h->filtered && percent >= min_pcnt)
			वापस nd;

		nd = rb_hierarchy_prev(nd);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम ui_browser__hists_seek(काष्ठा ui_browser *browser,
				   off_t offset, पूर्णांक whence)
अणु
	काष्ठा hist_entry *h;
	काष्ठा rb_node *nd;
	bool first = true;
	काष्ठा hist_browser *hb;

	hb = container_of(browser, काष्ठा hist_browser, b);

	अगर (browser->nr_entries == 0)
		वापस;

	ui_browser__hists_init_top(browser);

	चयन (whence) अणु
	हाल शुरू_से:
		nd = hists__filter_entries(rb_first(browser->entries),
					   hb->min_pcnt);
		अवरोध;
	हाल प्रस्तुत_से:
		nd = browser->top;
		जाओ करो_offset;
	हाल अंत_से:
		nd = rb_hierarchy_last(rb_last(browser->entries));
		nd = hists__filter_prev_entries(nd, hb->min_pcnt);
		first = false;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/*
	 * Moves not relative to the first visible entry invalidates its
	 * row_offset:
	 */
	h = rb_entry(browser->top, काष्ठा hist_entry, rb_node);
	h->row_offset = 0;

	/*
	 * Here we have to check अगर nd is expanded (+), अगर it is we can't go
	 * the next top level hist_entry, instead we must compute an offset of
	 * what _not_ to show and not change the first visible entry.
	 *
	 * This offset increments when we are going from top to bottom and
	 * decreases when we're going from bottom to top.
	 *
	 * As we करोn't have backpoपूर्णांकers to the top level in the callchains
	 * काष्ठाure, we need to always prपूर्णांक the whole hist_entry callchain,
	 * skipping the first ones that are beक्रमe the first visible entry
	 * and stop when we prपूर्णांकed enough lines to fill the screen.
	 */
करो_offset:
	अगर (!nd)
		वापस;

	अगर (offset > 0) अणु
		करो अणु
			h = rb_entry(nd, काष्ठा hist_entry, rb_node);
			अगर (h->unfolded && h->leaf) अणु
				u16 reमुख्यing = h->nr_rows - h->row_offset;
				अगर (offset > reमुख्यing) अणु
					offset -= reमुख्यing;
					h->row_offset = 0;
				पूर्ण अन्यथा अणु
					h->row_offset += offset;
					offset = 0;
					browser->top = nd;
					अवरोध;
				पूर्ण
			पूर्ण
			nd = hists__filter_entries(rb_hierarchy_next(nd),
						   hb->min_pcnt);
			अगर (nd == शून्य)
				अवरोध;
			--offset;
			browser->top = nd;
		पूर्ण जबतक (offset != 0);
	पूर्ण अन्यथा अगर (offset < 0) अणु
		जबतक (1) अणु
			h = rb_entry(nd, काष्ठा hist_entry, rb_node);
			अगर (h->unfolded && h->leaf) अणु
				अगर (first) अणु
					अगर (-offset > h->row_offset) अणु
						offset += h->row_offset;
						h->row_offset = 0;
					पूर्ण अन्यथा अणु
						h->row_offset += offset;
						offset = 0;
						browser->top = nd;
						अवरोध;
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (-offset > h->nr_rows) अणु
						offset += h->nr_rows;
						h->row_offset = 0;
					पूर्ण अन्यथा अणु
						h->row_offset = h->nr_rows + offset;
						offset = 0;
						browser->top = nd;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण

			nd = hists__filter_prev_entries(rb_hierarchy_prev(nd),
							hb->min_pcnt);
			अगर (nd == शून्य)
				अवरोध;
			++offset;
			browser->top = nd;
			अगर (offset == 0) अणु
				/*
				 * Last unfiltered hist_entry, check अगर it is
				 * unfolded, अगर it is then we should have
				 * row_offset at its last entry.
				 */
				h = rb_entry(nd, काष्ठा hist_entry, rb_node);
				अगर (h->unfolded && h->leaf)
					h->row_offset = h->nr_rows;
				अवरोध;
			पूर्ण
			first = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		browser->top = nd;
		h = rb_entry(nd, काष्ठा hist_entry, rb_node);
		h->row_offset = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक hist_browser__ख_लिखो_callchain(काष्ठा hist_browser *browser,
					   काष्ठा hist_entry *he, खाता *fp,
					   पूर्णांक level)
अणु
	काष्ठा callchain_prपूर्णांक_arg arg  = अणु
		.fp = fp,
	पूर्ण;

	hist_browser__show_callchain(browser, he, level, 0,
				     hist_browser__ख_लिखो_callchain_entry, &arg,
				     hist_browser__check_dump_full);
	वापस arg.prपूर्णांकed;
पूर्ण

अटल पूर्णांक hist_browser__ख_लिखो_entry(काष्ठा hist_browser *browser,
				       काष्ठा hist_entry *he, खाता *fp)
अणु
	अक्षर s[8192];
	पूर्णांक prपूर्णांकed = 0;
	अक्षर folded_sign = ' ';
	काष्ठा perf_hpp hpp = अणु
		.buf = s,
		.size = माप(s),
	पूर्ण;
	काष्ठा perf_hpp_fmt *fmt;
	bool first = true;
	पूर्णांक ret;

	अगर (hist_entry__has_callchains(he) && symbol_conf.use_callchain) अणु
		folded_sign = hist_entry__folded(he);
		prपूर्णांकed += ख_लिखो(fp, "%c ", folded_sign);
	पूर्ण

	hists__क्रम_each_क्रमmat(browser->hists, fmt) अणु
		अगर (perf_hpp__should_skip(fmt, he->hists))
			जारी;

		अगर (!first) अणु
			ret = scnम_लिखो(hpp.buf, hpp.size, "  ");
			advance_hpp(&hpp, ret);
		पूर्ण अन्यथा
			first = false;

		ret = fmt->entry(fmt, &hpp, he);
		ret = hist_entry__snम_लिखो_alignment(he, &hpp, fmt, ret);
		advance_hpp(&hpp, ret);
	पूर्ण
	prपूर्णांकed += ख_लिखो(fp, "%s\n", s);

	अगर (folded_sign == '-')
		prपूर्णांकed += hist_browser__ख_लिखो_callchain(browser, he, fp, 1);

	वापस prपूर्णांकed;
पूर्ण


अटल पूर्णांक hist_browser__ख_लिखो_hierarchy_entry(काष्ठा hist_browser *browser,
						 काष्ठा hist_entry *he,
						 खाता *fp, पूर्णांक level)
अणु
	अक्षर s[8192];
	पूर्णांक prपूर्णांकed = 0;
	अक्षर folded_sign = ' ';
	काष्ठा perf_hpp hpp = अणु
		.buf = s,
		.size = माप(s),
	पूर्ण;
	काष्ठा perf_hpp_fmt *fmt;
	काष्ठा perf_hpp_list_node *fmt_node;
	bool first = true;
	पूर्णांक ret;
	पूर्णांक hierarchy_indent = (he->hists->nr_hpp_node - 2) * HIERARCHY_INDENT;

	prपूर्णांकed = ख_लिखो(fp, "%*s", level * HIERARCHY_INDENT, "");

	folded_sign = hist_entry__folded(he);
	prपूर्णांकed += ख_लिखो(fp, "%c", folded_sign);

	/* the first hpp_list_node is क्रम overhead columns */
	fmt_node = list_first_entry(&he->hists->hpp_क्रमmats,
				    काष्ठा perf_hpp_list_node, list);
	perf_hpp_list__क्रम_each_क्रमmat(&fmt_node->hpp, fmt) अणु
		अगर (!first) अणु
			ret = scnम_लिखो(hpp.buf, hpp.size, "  ");
			advance_hpp(&hpp, ret);
		पूर्ण अन्यथा
			first = false;

		ret = fmt->entry(fmt, &hpp, he);
		advance_hpp(&hpp, ret);
	पूर्ण

	ret = scnम_लिखो(hpp.buf, hpp.size, "%*s", hierarchy_indent, "");
	advance_hpp(&hpp, ret);

	perf_hpp_list__क्रम_each_क्रमmat(he->hpp_list, fmt) अणु
		ret = scnम_लिखो(hpp.buf, hpp.size, "  ");
		advance_hpp(&hpp, ret);

		ret = fmt->entry(fmt, &hpp, he);
		advance_hpp(&hpp, ret);
	पूर्ण

	strim(s);
	prपूर्णांकed += ख_लिखो(fp, "%s\n", s);

	अगर (he->leaf && folded_sign == '-') अणु
		prपूर्णांकed += hist_browser__ख_लिखो_callchain(browser, he, fp,
							   he->depth + 1);
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक hist_browser__ख_लिखो(काष्ठा hist_browser *browser, खाता *fp)
अणु
	काष्ठा rb_node *nd = hists__filter_entries(rb_first(browser->b.entries),
						   browser->min_pcnt);
	पूर्णांक prपूर्णांकed = 0;

	जबतक (nd) अणु
		काष्ठा hist_entry *h = rb_entry(nd, काष्ठा hist_entry, rb_node);

		अगर (symbol_conf.report_hierarchy) अणु
			prपूर्णांकed += hist_browser__ख_लिखो_hierarchy_entry(browser,
									 h, fp,
									 h->depth);
		पूर्ण अन्यथा अणु
			prपूर्णांकed += hist_browser__ख_लिखो_entry(browser, h, fp);
		पूर्ण

		nd = hists__filter_entries(rb_hierarchy_next(nd),
					   browser->min_pcnt);
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक hist_browser__dump(काष्ठा hist_browser *browser)
अणु
	अक्षर filename[64];
	खाता *fp;

	जबतक (1) अणु
		scnम_लिखो(filename, माप(filename), "perf.hist.%d", browser->prपूर्णांक_seq);
		अगर (access(filename, F_OK))
			अवरोध;
		/*
 		 * XXX: Just an arbitrary lazy upper limit
 		 */
		अगर (++browser->prपूर्णांक_seq == 8192) अणु
			ui_helpline__fpush("Too many perf.hist.N files, nothing written!");
			वापस -1;
		पूर्ण
	पूर्ण

	fp = ख_खोलो(filename, "w");
	अगर (fp == शून्य) अणु
		अक्षर bf[64];
		स्थिर अक्षर *err = str_error_r(त्रुटि_सं, bf, माप(bf));
		ui_helpline__fpush("Couldn't write to %s: %s", filename, err);
		वापस -1;
	पूर्ण

	++browser->prपूर्णांक_seq;
	hist_browser__ख_लिखो(browser, fp);
	ख_बंद(fp);
	ui_helpline__fpush("%s written!", filename);

	वापस 0;
पूर्ण

व्योम hist_browser__init(काष्ठा hist_browser *browser,
			काष्ठा hists *hists)
अणु
	काष्ठा perf_hpp_fmt *fmt;

	browser->hists			= hists;
	browser->b.refresh		= hist_browser__refresh;
	browser->b.refresh_dimensions	= hist_browser__refresh_dimensions;
	browser->b.seek			= ui_browser__hists_seek;
	browser->b.use_navkeypressed	= true;
	browser->show_headers		= symbol_conf.show_hist_headers;
	hist_browser__set_title_space(browser);

	अगर (symbol_conf.report_hierarchy) अणु
		काष्ठा perf_hpp_list_node *fmt_node;

		/* count overhead columns (in the first node) */
		fmt_node = list_first_entry(&hists->hpp_क्रमmats,
					    काष्ठा perf_hpp_list_node, list);
		perf_hpp_list__क्रम_each_क्रमmat(&fmt_node->hpp, fmt)
			++browser->b.columns;

		/* add a single column क्रम whole hierarchy sort keys*/
		++browser->b.columns;
	पूर्ण अन्यथा अणु
		hists__क्रम_each_क्रमmat(hists, fmt)
			++browser->b.columns;
	पूर्ण

	hists__reset_column_width(hists);
पूर्ण

काष्ठा hist_browser *hist_browser__new(काष्ठा hists *hists)
अणु
	काष्ठा hist_browser *browser = zalloc(माप(*browser));

	अगर (browser)
		hist_browser__init(browser, hists);

	वापस browser;
पूर्ण

अटल काष्ठा hist_browser *
perf_evsel_browser__new(काष्ठा evsel *evsel,
			काष्ठा hist_browser_समयr *hbt,
			काष्ठा perf_env *env,
			काष्ठा annotation_options *annotation_opts)
अणु
	काष्ठा hist_browser *browser = hist_browser__new(evsel__hists(evsel));

	अगर (browser) अणु
		browser->hbt   = hbt;
		browser->env   = env;
		browser->title = hists_browser__scnम_लिखो_title;
		browser->annotation_opts = annotation_opts;
	पूर्ण
	वापस browser;
पूर्ण

व्योम hist_browser__delete(काष्ठा hist_browser *browser)
अणु
	मुक्त(browser);
पूर्ण

अटल काष्ठा hist_entry *hist_browser__selected_entry(काष्ठा hist_browser *browser)
अणु
	वापस browser->he_selection;
पूर्ण

अटल काष्ठा thपढ़ो *hist_browser__selected_thपढ़ो(काष्ठा hist_browser *browser)
अणु
	वापस browser->he_selection->thपढ़ो;
पूर्ण

अटल काष्ठा res_sample *hist_browser__selected_res_sample(काष्ठा hist_browser *browser)
अणु
	वापस browser->he_selection ? browser->he_selection->res_samples : शून्य;
पूर्ण

/* Check whether the browser is क्रम 'top' or 'report' */
अटल अंतरभूत bool is_report_browser(व्योम *समयr)
अणु
	वापस समयr == शून्य;
पूर्ण

अटल पूर्णांक hists_browser__scnम_लिखो_title(काष्ठा hist_browser *browser, अक्षर *bf, माप_प्रकार size)
अणु
	काष्ठा hist_browser_समयr *hbt = browser->hbt;
	पूर्णांक prपूर्णांकed = __hists__scnम_लिखो_title(browser->hists, bf, size, !is_report_browser(hbt));

	अगर (!is_report_browser(hbt)) अणु
		काष्ठा perf_top *top = hbt->arg;

		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed,
				     " lost: %" PRIu64 "/%" PRIu64,
				     top->lost, top->lost_total);

		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed,
				     " drop: %" PRIu64 "/%" PRIu64,
				     top->drop, top->drop_total);

		अगर (top->zero)
			prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, " [z]");

		perf_top__reset_sample_counters(top);
	पूर्ण


	वापस prपूर्णांकed;
पूर्ण

अटल अंतरभूत व्योम मुक्त_popup_options(अक्षर **options, पूर्णांक n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; ++i)
		zमुक्त(&options[i]);
पूर्ण

/*
 * Only runसमय चयनing of perf data file will make "input_name" poपूर्णांक
 * to a दो_स्मृतिed buffer. So add "is_input_name_malloced" flag to decide
 * whether we need to call मुक्त() क्रम current "input_name" during the चयन.
 */
अटल bool is_input_name_दो_स्मृतिed = false;

अटल पूर्णांक चयन_data_file(व्योम)
अणु
	अक्षर *pwd, *options[32], *असल_path[32], *पंचांगp;
	सूची *pwd_dir;
	पूर्णांक nr_options = 0, choice = -1, ret = -1;
	काष्ठा dirent *dent;

	pwd = दो_पर्या("PWD");
	अगर (!pwd)
		वापस ret;

	pwd_dir = सूची_खोलो(pwd);
	अगर (!pwd_dir)
		वापस ret;

	स_रखो(options, 0, माप(options));
	स_रखो(असल_path, 0, माप(असल_path));

	जबतक ((dent = सूची_पढ़ो(pwd_dir))) अणु
		अक्षर path[PATH_MAX];
		u64 magic;
		अक्षर *name = dent->d_name;
		खाता *file;

		अगर (!(dent->d_type == DT_REG))
			जारी;

		snम_लिखो(path, माप(path), "%s/%s", pwd, name);

		file = ख_खोलो(path, "r");
		अगर (!file)
			जारी;

		अगर (ख_पढ़ो(&magic, 1, 8, file) < 8)
			जाओ बंद_file_and_जारी;

		अगर (is_perf_magic(magic)) अणु
			options[nr_options] = strdup(name);
			अगर (!options[nr_options])
				जाओ बंद_file_and_जारी;

			असल_path[nr_options] = strdup(path);
			अगर (!असल_path[nr_options]) अणु
				zमुक्त(&options[nr_options]);
				ui__warning("Can't search all data files due to memory shortage.\n");
				ख_बंद(file);
				अवरोध;
			पूर्ण

			nr_options++;
		पूर्ण

बंद_file_and_जारी:
		ख_बंद(file);
		अगर (nr_options >= 32) अणु
			ui__warning("Too many perf data files in PWD!\n"
				    "Only the first 32 files will be listed.\n");
			अवरोध;
		पूर्ण
	पूर्ण
	बंद_सूची(pwd_dir);

	अगर (nr_options) अणु
		choice = ui__popup_menu(nr_options, options, शून्य);
		अगर (choice < nr_options && choice >= 0) अणु
			पंचांगp = strdup(असल_path[choice]);
			अगर (पंचांगp) अणु
				अगर (is_input_name_दो_स्मृतिed)
					मुक्त((व्योम *)input_name);
				input_name = पंचांगp;
				is_input_name_दो_स्मृतिed = true;
				ret = 0;
			पूर्ण अन्यथा
				ui__warning("Data switch failed due to memory shortage!\n");
		पूर्ण
	पूर्ण

	मुक्त_popup_options(options, nr_options);
	मुक्त_popup_options(असल_path, nr_options);
	वापस ret;
पूर्ण

काष्ठा popup_action अणु
	अचिन्हित दीर्घ		समय;
	काष्ठा thपढ़ो 		*thपढ़ो;
	काष्ठा map_symbol 	ms;
	पूर्णांक			socket;
	काष्ठा evsel	*evsel;
	क्रमागत rstype		rstype;

	पूर्णांक (*fn)(काष्ठा hist_browser *browser, काष्ठा popup_action *act);
पूर्ण;

अटल पूर्णांक
करो_annotate(काष्ठा hist_browser *browser, काष्ठा popup_action *act)
अणु
	काष्ठा evsel *evsel;
	काष्ठा annotation *notes;
	काष्ठा hist_entry *he;
	पूर्णांक err;

	अगर (!browser->annotation_opts->objdump_path &&
	    perf_env__lookup_objdump(browser->env, &browser->annotation_opts->objdump_path))
		वापस 0;

	notes = symbol__annotation(act->ms.sym);
	अगर (!notes->src)
		वापस 0;

	अगर (browser->block_evsel)
		evsel = browser->block_evsel;
	अन्यथा
		evsel = hists_to_evsel(browser->hists);

	err = map_symbol__tui_annotate(&act->ms, evsel, browser->hbt,
				       browser->annotation_opts);
	he = hist_browser__selected_entry(browser);
	/*
	 * offer option to annotate the other branch source or target
	 * (अगर they exists) when वापसing from annotate
	 */
	अगर ((err == 'q' || err == CTRL('c')) && he->branch_info)
		वापस 1;

	ui_browser__update_nr_entries(&browser->b, browser->hists->nr_entries);
	अगर (err)
		ui_browser__handle_resize(&browser->b);
	वापस 0;
पूर्ण

अटल काष्ठा symbol *symbol__new_unresolved(u64 addr, काष्ठा map *map)
अणु
	काष्ठा annotated_source *src;
	काष्ठा symbol *sym;
	अक्षर name[64];

	snम_लिखो(name, माप(name), "%.*" PRIx64, BITS_PER_LONG / 4, addr);

	sym = symbol__new(addr, ANNOTATION_DUMMY_LEN, 0, 0, name);
	अगर (sym) अणु
		src = symbol__hists(sym, 1);
		अगर (!src) अणु
			symbol__delete(sym);
			वापस शून्य;
		पूर्ण

		dso__insert_symbol(map->dso, sym);
	पूर्ण

	वापस sym;
पूर्ण

अटल पूर्णांक
add_annotate_opt(काष्ठा hist_browser *browser __maybe_unused,
		 काष्ठा popup_action *act, अक्षर **optstr,
		 काष्ठा map_symbol *ms,
		 u64 addr)
अणु
	अगर (!ms->map || !ms->map->dso || ms->map->dso->annotate_warned)
		वापस 0;

	अगर (!ms->sym)
		ms->sym = symbol__new_unresolved(addr, ms->map);

	अगर (ms->sym == शून्य || symbol__annotation(ms->sym)->src == शून्य)
		वापस 0;

	अगर (aप्र_लिखो(optstr, "Annotate %s", ms->sym->name) < 0)
		वापस 0;

	act->ms = *ms;
	act->fn = करो_annotate;
	वापस 1;
पूर्ण

अटल पूर्णांक
करो_zoom_thपढ़ो(काष्ठा hist_browser *browser, काष्ठा popup_action *act)
अणु
	काष्ठा thपढ़ो *thपढ़ो = act->thपढ़ो;

	अगर ((!hists__has(browser->hists, thपढ़ो) &&
	     !hists__has(browser->hists, comm)) || thपढ़ो == शून्य)
		वापस 0;

	अगर (browser->hists->thपढ़ो_filter) अणु
		pstack__हटाओ(browser->pstack, &browser->hists->thपढ़ो_filter);
		perf_hpp__set_elide(HISTC_THREAD, false);
		thपढ़ो__zput(browser->hists->thपढ़ो_filter);
		ui_helpline__pop();
	पूर्ण अन्यथा अणु
		अगर (hists__has(browser->hists, thपढ़ो)) अणु
			ui_helpline__fpush("To zoom out press ESC or ENTER + \"Zoom out of %s(%d) thread\"",
					   thपढ़ो->comm_set ? thपढ़ो__comm_str(thपढ़ो) : "",
					   thपढ़ो->tid);
		पूर्ण अन्यथा अणु
			ui_helpline__fpush("To zoom out press ESC or ENTER + \"Zoom out of %s thread\"",
					   thपढ़ो->comm_set ? thपढ़ो__comm_str(thपढ़ो) : "");
		पूर्ण

		browser->hists->thपढ़ो_filter = thपढ़ो__get(thपढ़ो);
		perf_hpp__set_elide(HISTC_THREAD, false);
		pstack__push(browser->pstack, &browser->hists->thपढ़ो_filter);
	पूर्ण

	hists__filter_by_thपढ़ो(browser->hists);
	hist_browser__reset(browser);
	वापस 0;
पूर्ण

अटल पूर्णांक
add_thपढ़ो_opt(काष्ठा hist_browser *browser, काष्ठा popup_action *act,
	       अक्षर **optstr, काष्ठा thपढ़ो *thपढ़ो)
अणु
	पूर्णांक ret;

	अगर ((!hists__has(browser->hists, thपढ़ो) &&
	     !hists__has(browser->hists, comm)) || thपढ़ो == शून्य)
		वापस 0;

	अगर (hists__has(browser->hists, thपढ़ो)) अणु
		ret = aप्र_लिखो(optstr, "Zoom %s %s(%d) thread",
			       browser->hists->thपढ़ो_filter ? "out of" : "into",
			       thपढ़ो->comm_set ? thपढ़ो__comm_str(thपढ़ो) : "",
			       thपढ़ो->tid);
	पूर्ण अन्यथा अणु
		ret = aप्र_लिखो(optstr, "Zoom %s %s thread",
			       browser->hists->thपढ़ो_filter ? "out of" : "into",
			       thपढ़ो->comm_set ? thपढ़ो__comm_str(thपढ़ो) : "");
	पूर्ण
	अगर (ret < 0)
		वापस 0;

	act->thपढ़ो = thपढ़ो;
	act->fn = करो_zoom_thपढ़ो;
	वापस 1;
पूर्ण

अटल पूर्णांक hists_browser__zoom_map(काष्ठा hist_browser *browser, काष्ठा map *map)
अणु
	अगर (!hists__has(browser->hists, dso) || map == शून्य)
		वापस 0;

	अगर (browser->hists->dso_filter) अणु
		pstack__हटाओ(browser->pstack, &browser->hists->dso_filter);
		perf_hpp__set_elide(HISTC_DSO, false);
		browser->hists->dso_filter = शून्य;
		ui_helpline__pop();
	पूर्ण अन्यथा अणु
		ui_helpline__fpush("To zoom out press ESC or ENTER + \"Zoom out of %s DSO\"",
				   __map__is_kernel(map) ? "the Kernel" : map->dso->लघु_name);
		browser->hists->dso_filter = map->dso;
		perf_hpp__set_elide(HISTC_DSO, true);
		pstack__push(browser->pstack, &browser->hists->dso_filter);
	पूर्ण

	hists__filter_by_dso(browser->hists);
	hist_browser__reset(browser);
	वापस 0;
पूर्ण

अटल पूर्णांक
करो_zoom_dso(काष्ठा hist_browser *browser, काष्ठा popup_action *act)
अणु
	वापस hists_browser__zoom_map(browser, act->ms.map);
पूर्ण

अटल पूर्णांक
add_dso_opt(काष्ठा hist_browser *browser, काष्ठा popup_action *act,
	    अक्षर **optstr, काष्ठा map *map)
अणु
	अगर (!hists__has(browser->hists, dso) || map == शून्य)
		वापस 0;

	अगर (aप्र_लिखो(optstr, "Zoom %s %s DSO (use the 'k' hotkey to zoom directly into the kernel)",
		     browser->hists->dso_filter ? "out of" : "into",
		     __map__is_kernel(map) ? "the Kernel" : map->dso->लघु_name) < 0)
		वापस 0;

	act->ms.map = map;
	act->fn = करो_zoom_dso;
	वापस 1;
पूर्ण

अटल पूर्णांक करो_toggle_callchain(काष्ठा hist_browser *browser, काष्ठा popup_action *act __maybe_unused)
अणु
	hist_browser__toggle_fold(browser);
	वापस 0;
पूर्ण

अटल पूर्णांक add_callchain_toggle_opt(काष्ठा hist_browser *browser, काष्ठा popup_action *act, अक्षर **optstr)
अणु
	अक्षर sym_name[512];

        अगर (!hist_browser__selection_has_children(browser))
                वापस 0;

	अगर (aप्र_लिखो(optstr, "%s [%s] callchain (one level, same as '+' hotkey, use 'e'/'c' for the whole main level entry)",
		     hist_browser__selection_unfolded(browser) ? "Collapse" : "Expand",
		     hist_browser__selection_sym_name(browser, sym_name, माप(sym_name))) < 0)
		वापस 0;

	act->fn = करो_toggle_callchain;
	वापस 1;
पूर्ण

अटल पूर्णांक
करो_browse_map(काष्ठा hist_browser *browser __maybe_unused,
	      काष्ठा popup_action *act)
अणु
	map__browse(act->ms.map);
	वापस 0;
पूर्ण

अटल पूर्णांक
add_map_opt(काष्ठा hist_browser *browser,
	    काष्ठा popup_action *act, अक्षर **optstr, काष्ठा map *map)
अणु
	अगर (!hists__has(browser->hists, dso) || map == शून्य)
		वापस 0;

	अगर (aप्र_लिखो(optstr, "Browse map details") < 0)
		वापस 0;

	act->ms.map = map;
	act->fn = करो_browse_map;
	वापस 1;
पूर्ण

अटल पूर्णांक
करो_run_script(काष्ठा hist_browser *browser __maybe_unused,
	      काष्ठा popup_action *act)
अणु
	अक्षर *script_opt;
	पूर्णांक len;
	पूर्णांक n = 0;

	len = 100;
	अगर (act->thपढ़ो)
		len += म_माप(thपढ़ो__comm_str(act->thपढ़ो));
	अन्यथा अगर (act->ms.sym)
		len += म_माप(act->ms.sym->name);
	script_opt = दो_स्मृति(len);
	अगर (!script_opt)
		वापस -1;

	script_opt[0] = 0;
	अगर (act->thपढ़ो) अणु
		n = scnम_लिखो(script_opt, len, " -c %s ",
			  thपढ़ो__comm_str(act->thपढ़ो));
	पूर्ण अन्यथा अगर (act->ms.sym) अणु
		n = scnम_लिखो(script_opt, len, " -S %s ",
			  act->ms.sym->name);
	पूर्ण

	अगर (act->समय) अणु
		अक्षर start[32], end[32];
		अचिन्हित दीर्घ startसमय = act->समय;
		अचिन्हित दीर्घ endसमय = act->समय + symbol_conf.समय_quantum;

		अगर (startसमय == endसमय) अणु /* Display 1ms as fallback */
			startसमय -= 1*NSEC_PER_MSEC;
			endसमय += 1*NSEC_PER_MSEC;
		पूर्ण
		बारtamp__scnम_लिखो_usec(startसमय, start, माप start);
		बारtamp__scnम_लिखो_usec(endसमय, end, माप end);
		n += snम_लिखो(script_opt + n, len - n, " --time %s,%s", start, end);
	पूर्ण

	script_browse(script_opt, act->evsel);
	मुक्त(script_opt);
	वापस 0;
पूर्ण

अटल पूर्णांक
करो_res_sample_script(काष्ठा hist_browser *browser __maybe_unused,
		     काष्ठा popup_action *act)
अणु
	काष्ठा hist_entry *he;

	he = hist_browser__selected_entry(browser);
	res_sample_browse(he->res_samples, he->num_res, act->evsel, act->rstype);
	वापस 0;
पूर्ण

अटल पूर्णांक
add_script_opt_2(काष्ठा hist_browser *browser __maybe_unused,
	       काष्ठा popup_action *act, अक्षर **optstr,
	       काष्ठा thपढ़ो *thपढ़ो, काष्ठा symbol *sym,
	       काष्ठा evsel *evsel, स्थिर अक्षर *tstr)
अणु

	अगर (thपढ़ो) अणु
		अगर (aप्र_लिखो(optstr, "Run scripts for samples of thread [%s]%s",
			     thपढ़ो__comm_str(thपढ़ो), tstr) < 0)
			वापस 0;
	पूर्ण अन्यथा अगर (sym) अणु
		अगर (aप्र_लिखो(optstr, "Run scripts for samples of symbol [%s]%s",
			     sym->name, tstr) < 0)
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (aप्र_लिखो(optstr, "Run scripts for all samples%s", tstr) < 0)
			वापस 0;
	पूर्ण

	act->thपढ़ो = thपढ़ो;
	act->ms.sym = sym;
	act->evsel = evsel;
	act->fn = करो_run_script;
	वापस 1;
पूर्ण

अटल पूर्णांक
add_script_opt(काष्ठा hist_browser *browser,
	       काष्ठा popup_action *act, अक्षर **optstr,
	       काष्ठा thपढ़ो *thपढ़ो, काष्ठा symbol *sym,
	       काष्ठा evsel *evsel)
अणु
	पूर्णांक n, j;
	काष्ठा hist_entry *he;

	n = add_script_opt_2(browser, act, optstr, thपढ़ो, sym, evsel, "");

	he = hist_browser__selected_entry(browser);
	अगर (sort_order && म_माला(sort_order, "time")) अणु
		अक्षर tstr[128];

		optstr++;
		act++;
		j = प्र_लिखो(tstr, " in ");
		j += बारtamp__scnम_लिखो_usec(he->समय, tstr + j,
					       माप tstr - j);
		j += प्र_लिखो(tstr + j, "-");
		बारtamp__scnम_लिखो_usec(he->समय + symbol_conf.समय_quantum,
				          tstr + j, माप tstr - j);
		n += add_script_opt_2(browser, act, optstr, thपढ़ो, sym,
					  evsel, tstr);
		act->समय = he->समय;
	पूर्ण
	वापस n;
पूर्ण

अटल पूर्णांक
add_res_sample_opt(काष्ठा hist_browser *browser __maybe_unused,
		   काष्ठा popup_action *act, अक्षर **optstr,
		   काष्ठा res_sample *res_sample,
		   काष्ठा evsel *evsel,
		   क्रमागत rstype type)
अणु
	अगर (!res_sample)
		वापस 0;

	अगर (aप्र_लिखो(optstr, "Show context for individual samples %s",
		type == A_ASM ? "with assembler" :
		type == A_SOURCE ? "with source" : "") < 0)
		वापस 0;

	act->fn = करो_res_sample_script;
	act->evsel = evsel;
	act->rstype = type;
	वापस 1;
पूर्ण

अटल पूर्णांक
करो_चयन_data(काष्ठा hist_browser *browser __maybe_unused,
	       काष्ठा popup_action *act __maybe_unused)
अणु
	अगर (चयन_data_file()) अणु
		ui__warning("Won't switch the data files due to\n"
			    "no valid data file get selected!\n");
		वापस 0;
	पूर्ण

	वापस K_SWITCH_INPUT_DATA;
पूर्ण

अटल पूर्णांक
add_चयन_opt(काष्ठा hist_browser *browser,
	       काष्ठा popup_action *act, अक्षर **optstr)
अणु
	अगर (!is_report_browser(browser->hbt))
		वापस 0;

	अगर (aप्र_लिखो(optstr, "Switch to another data file in PWD") < 0)
		वापस 0;

	act->fn = करो_चयन_data;
	वापस 1;
पूर्ण

अटल पूर्णांक
करो_निकास_browser(काष्ठा hist_browser *browser __maybe_unused,
		काष्ठा popup_action *act __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
add_निकास_opt(काष्ठा hist_browser *browser __maybe_unused,
	     काष्ठा popup_action *act, अक्षर **optstr)
अणु
	अगर (aप्र_लिखो(optstr, "Exit") < 0)
		वापस 0;

	act->fn = करो_निकास_browser;
	वापस 1;
पूर्ण

अटल पूर्णांक
करो_zoom_socket(काष्ठा hist_browser *browser, काष्ठा popup_action *act)
अणु
	अगर (!hists__has(browser->hists, socket) || act->socket < 0)
		वापस 0;

	अगर (browser->hists->socket_filter > -1) अणु
		pstack__हटाओ(browser->pstack, &browser->hists->socket_filter);
		browser->hists->socket_filter = -1;
		perf_hpp__set_elide(HISTC_SOCKET, false);
	पूर्ण अन्यथा अणु
		browser->hists->socket_filter = act->socket;
		perf_hpp__set_elide(HISTC_SOCKET, true);
		pstack__push(browser->pstack, &browser->hists->socket_filter);
	पूर्ण

	hists__filter_by_socket(browser->hists);
	hist_browser__reset(browser);
	वापस 0;
पूर्ण

अटल पूर्णांक
add_socket_opt(काष्ठा hist_browser *browser, काष्ठा popup_action *act,
	       अक्षर **optstr, पूर्णांक socket_id)
अणु
	अगर (!hists__has(browser->hists, socket) || socket_id < 0)
		वापस 0;

	अगर (aप्र_लिखो(optstr, "Zoom %s Processor Socket %d",
		     (browser->hists->socket_filter > -1) ? "out of" : "into",
		     socket_id) < 0)
		वापस 0;

	act->socket = socket_id;
	act->fn = करो_zoom_socket;
	वापस 1;
पूर्ण

अटल व्योम hist_browser__update_nr_entries(काष्ठा hist_browser *hb)
अणु
	u64 nr_entries = 0;
	काष्ठा rb_node *nd = rb_first_cached(&hb->hists->entries);

	अगर (hb->min_pcnt == 0 && !symbol_conf.report_hierarchy) अणु
		hb->nr_non_filtered_entries = hb->hists->nr_non_filtered_entries;
		वापस;
	पूर्ण

	जबतक ((nd = hists__filter_entries(nd, hb->min_pcnt)) != शून्य) अणु
		nr_entries++;
		nd = rb_hierarchy_next(nd);
	पूर्ण

	hb->nr_non_filtered_entries = nr_entries;
	hb->nr_hierarchy_entries = nr_entries;
पूर्ण

अटल व्योम hist_browser__update_percent_limit(काष्ठा hist_browser *hb,
					       द्विगुन percent)
अणु
	काष्ठा hist_entry *he;
	काष्ठा rb_node *nd = rb_first_cached(&hb->hists->entries);
	u64 total = hists__total_period(hb->hists);
	u64 min_callchain_hits = total * (percent / 100);

	hb->min_pcnt = callchain_param.min_percent = percent;

	जबतक ((nd = hists__filter_entries(nd, hb->min_pcnt)) != शून्य) अणु
		he = rb_entry(nd, काष्ठा hist_entry, rb_node);

		अगर (he->has_no_entry) अणु
			he->has_no_entry = false;
			he->nr_rows = 0;
		पूर्ण

		अगर (!he->leaf || !hist_entry__has_callchains(he) || !symbol_conf.use_callchain)
			जाओ next;

		अगर (callchain_param.mode == CHAIN_GRAPH_REL) अणु
			total = he->stat.period;

			अगर (symbol_conf.cumulate_callchain)
				total = he->stat_acc->period;

			min_callchain_hits = total * (percent / 100);
		पूर्ण

		callchain_param.sort(&he->sorted_chain, he->callchain,
				     min_callchain_hits, &callchain_param);

next:
		nd = __rb_hierarchy_next(nd, HMD_FORCE_CHILD);

		/* क्रमce to re-evaluate folding state of callchains */
		he->init_have_children = false;
		hist_entry__set_folding(he, hb, false);
	पूर्ण
पूर्ण

अटल पूर्णांक evsel__hists_browse(काष्ठा evsel *evsel, पूर्णांक nr_events, स्थिर अक्षर *helpline,
			       bool left_निकासs, काष्ठा hist_browser_समयr *hbt, भग्न min_pcnt,
			       काष्ठा perf_env *env, bool warn_lost_event,
			       काष्ठा annotation_options *annotation_opts)
अणु
	काष्ठा hists *hists = evsel__hists(evsel);
	काष्ठा hist_browser *browser = perf_evsel_browser__new(evsel, hbt, env, annotation_opts);
	काष्ठा branch_info *bi = शून्य;
#घोषणा MAX_OPTIONS  16
	अक्षर *options[MAX_OPTIONS];
	काष्ठा popup_action actions[MAX_OPTIONS];
	पूर्णांक nr_options = 0;
	पूर्णांक key = -1;
	अक्षर buf[128];
	पूर्णांक delay_secs = hbt ? hbt->refresh : 0;

#घोषणा HIST_BROWSER_HELP_COMMON					\
	"h/?/F1        Show this window\n"				\
	"UP/DOWN/PGUP\n"						\
	"PGDN/SPACE    Navigate\n"					\
	"q/ESC/CTRL+C  Exit browser or go back to previous screen\n\n"	\
	"For multiple event sessions:\n\n"				\
	"TAB/UNTAB     Switch events\n\n"				\
	"For symbolic views (--sort has sym):\n\n"			\
	"ENTER         Zoom into DSO/Threads & Annotate current symbol\n" \
	"ESC           Zoom out\n"					\
	"+             Expand/Collapse one callchain level\n"		\
	"a             Annotate current symbol\n"			\
	"C             Collapse all callchains\n"			\
	"d             Zoom into current DSO\n"				\
	"e             Expand/Collapse main entry callchains\n"	\
	"E             Expand all callchains\n"				\
	"F             Toggle percentage of filtered entries\n"		\
	"H             Display column headers\n"			\
	"k             Zoom into the kernel map\n"			\
	"L             Change percent limit\n"				\
	"m             Display context menu\n"				\
	"S             Zoom into current Processor Socket\n"		\

	/* help messages are sorted by lexical order of the hotkey */
	अटल स्थिर अक्षर report_help[] = HIST_BROWSER_HELP_COMMON
	"i             Show header information\n"
	"P             Print histograms to perf.hist.N\n"
	"r             Run available scripts\n"
	"s             Switch to another data file in PWD\n"
	"t             Zoom into current Thread\n"
	"V             Verbose (DSO names in callchains, etc)\n"
	"/             Filter symbol by name\n"
	"0-9           Sort by event n in group";
	अटल स्थिर अक्षर top_help[] = HIST_BROWSER_HELP_COMMON
	"P             Print histograms to perf.hist.N\n"
	"t             Zoom into current Thread\n"
	"V             Verbose (DSO names in callchains, etc)\n"
	"z             Toggle zeroing of samples\n"
	"f             Enable/Disable events\n"
	"/             Filter symbol by name";

	अगर (browser == शून्य)
		वापस -1;

	/* reset पात key so that it can get Ctrl-C as a key */
	SLang_reset_tty();
	SLang_init_tty(0, 0, 0);

	अगर (min_pcnt)
		browser->min_pcnt = min_pcnt;
	hist_browser__update_nr_entries(browser);

	browser->pstack = pstack__new(3);
	अगर (browser->pstack == शून्य)
		जाओ out;

	ui_helpline__push(helpline);

	स_रखो(options, 0, माप(options));
	स_रखो(actions, 0, माप(actions));

	अगर (symbol_conf.col_width_list_str)
		perf_hpp__set_user_width(symbol_conf.col_width_list_str);

	अगर (!is_report_browser(hbt))
		browser->b.no_samples_msg = "Collecting samples...";

	जबतक (1) अणु
		काष्ठा thपढ़ो *thपढ़ो = शून्य;
		काष्ठा map *map = शून्य;
		पूर्णांक choice;
		पूर्णांक socked_id = -1;

		key = 0; // reset key
करो_hotkey:		 // key came straight from options ui__popup_menu()
		choice = nr_options = 0;
		key = hist_browser__run(browser, helpline, warn_lost_event, key);

		अगर (browser->he_selection != शून्य) अणु
			thपढ़ो = hist_browser__selected_thपढ़ो(browser);
			map = browser->selection->map;
			socked_id = browser->he_selection->socket;
		पूर्ण
		चयन (key) अणु
		हाल K_TAB:
		हाल K_UNTAB:
			अगर (nr_events == 1)
				जारी;
			/*
			 * Exit the browser, let hists__browser_tree
			 * go to the next or previous
			 */
			जाओ out_मुक्त_stack;
		हाल '0' ... '9':
			अगर (!symbol_conf.event_group ||
			    evsel->core.nr_members < 2) अणु
				snम_लिखो(buf, माप(buf),
					 "Sort by index only available with group events!");
				helpline = buf;
				जारी;
			पूर्ण

			अगर (key - '0' == symbol_conf.group_sort_idx)
				जारी;

			symbol_conf.group_sort_idx = key - '0';

			अगर (symbol_conf.group_sort_idx >= evsel->core.nr_members) अणु
				snम_लिखो(buf, माप(buf),
					 "Max event group index to sort is %d (index from 0 to %d)",
					 evsel->core.nr_members - 1,
					 evsel->core.nr_members - 1);
				helpline = buf;
				जारी;
			पूर्ण

			key = K_RELOAD;
			जाओ out_मुक्त_stack;
		हाल 'a':
			अगर (!hists__has(hists, sym)) अणु
				ui_browser__warning(&browser->b, delay_secs * 2,
			"Annotation is only available for symbolic views, "
			"include \"sym*\" in --sort to use it.");
				जारी;
			पूर्ण

			अगर (!browser->selection ||
			    !browser->selection->map ||
			    !browser->selection->map->dso ||
			    browser->selection->map->dso->annotate_warned) अणु
				जारी;
			पूर्ण

			अगर (!browser->selection->sym) अणु
				अगर (!browser->he_selection)
					जारी;

				अगर (sort__mode == SORT_MODE__BRANCH) अणु
					bi = browser->he_selection->branch_info;
					अगर (!bi || !bi->to.ms.map)
						जारी;

					actions->ms.sym = symbol__new_unresolved(bi->to.al_addr, bi->to.ms.map);
					actions->ms.map = bi->to.ms.map;
				पूर्ण अन्यथा अणु
					actions->ms.sym = symbol__new_unresolved(browser->he_selection->ip,
										 browser->selection->map);
					actions->ms.map = browser->selection->map;
				पूर्ण

				अगर (!actions->ms.sym)
					जारी;
			पूर्ण अन्यथा अणु
				अगर (symbol__annotation(browser->selection->sym)->src == शून्य) अणु
					ui_browser__warning(&browser->b, delay_secs * 2,
						"No samples for the \"%s\" symbol.\n\n"
						"Probably appeared just in a callchain",
						browser->selection->sym->name);
					जारी;
				पूर्ण

				actions->ms.map = browser->selection->map;
				actions->ms.sym = browser->selection->sym;
			पूर्ण

			करो_annotate(browser, actions);
			जारी;
		हाल 'P':
			hist_browser__dump(browser);
			जारी;
		हाल 'd':
			actions->ms.map = map;
			करो_zoom_dso(browser, actions);
			जारी;
		हाल 'k':
			अगर (browser->selection != शून्य)
				hists_browser__zoom_map(browser, browser->selection->maps->machine->vmlinux_map);
			जारी;
		हाल 'V':
			verbose = (verbose + 1) % 4;
			browser->show_dso = verbose > 0;
			ui_helpline__fpush("Verbosity level set to %d\n",
					   verbose);
			जारी;
		हाल 't':
			actions->thपढ़ो = thपढ़ो;
			करो_zoom_thपढ़ो(browser, actions);
			जारी;
		हाल 'S':
			actions->socket = socked_id;
			करो_zoom_socket(browser, actions);
			जारी;
		हाल '/':
			अगर (ui_browser__input_winकरोw("Symbol to show",
					"Please enter the name of symbol you want to see.\n"
					"To remove the filter later, press / + ENTER.",
					buf, "ENTER: OK, ESC: Cancel",
					delay_secs * 2) == K_ENTER) अणु
				hists->symbol_filter_str = *buf ? buf : शून्य;
				hists__filter_by_symbol(hists);
				hist_browser__reset(browser);
			पूर्ण
			जारी;
		हाल 'r':
			अगर (is_report_browser(hbt)) अणु
				actions->thपढ़ो = शून्य;
				actions->ms.sym = शून्य;
				करो_run_script(browser, actions);
			पूर्ण
			जारी;
		हाल 's':
			अगर (is_report_browser(hbt)) अणु
				key = करो_चयन_data(browser, actions);
				अगर (key == K_SWITCH_INPUT_DATA)
					जाओ out_मुक्त_stack;
			पूर्ण
			जारी;
		हाल 'i':
			/* env->arch is शून्य क्रम live-mode (i.e. perf top) */
			अगर (env->arch)
				tui__header_winकरोw(env);
			जारी;
		हाल 'F':
			symbol_conf.filter_relative ^= 1;
			जारी;
		हाल 'z':
			अगर (!is_report_browser(hbt)) अणु
				काष्ठा perf_top *top = hbt->arg;

				top->zero = !top->zero;
			पूर्ण
			जारी;
		हाल 'L':
			अगर (ui_browser__input_winकरोw("Percent Limit",
					"Please enter the value you want to hide entries under that percent.",
					buf, "ENTER: OK, ESC: Cancel",
					delay_secs * 2) == K_ENTER) अणु
				अक्षर *end;
				द्विगुन new_percent = म_से_भग्न(buf, &end);

				अगर (new_percent < 0 || new_percent > 100) अणु
					ui_browser__warning(&browser->b, delay_secs * 2,
						"Invalid percent: %.2f", new_percent);
					जारी;
				पूर्ण

				hist_browser__update_percent_limit(browser, new_percent);
				hist_browser__reset(browser);
			पूर्ण
			जारी;
		हाल K_F1:
		हाल 'h':
		हाल '?':
			ui_browser__help_winकरोw(&browser->b,
				is_report_browser(hbt) ? report_help : top_help);
			जारी;
		हाल K_ENTER:
		हाल K_RIGHT:
		हाल 'm':
			/* menu */
			अवरोध;
		हाल K_ESC:
		हाल K_LEFT: अणु
			स्थिर व्योम *top;

			अगर (pstack__empty(browser->pstack)) अणु
				/*
				 * Go back to the perf_evsel_menu__run or other user
				 */
				अगर (left_निकासs)
					जाओ out_मुक्त_stack;

				अगर (key == K_ESC &&
				    ui_browser__dialog_yesno(&browser->b,
							     "Do you really want to exit?"))
					जाओ out_मुक्त_stack;

				जारी;
			पूर्ण
			actions->ms.map = map;
			top = pstack__peek(browser->pstack);
			अगर (top == &browser->hists->dso_filter) अणु
				/*
				 * No need to set actions->dso here since
				 * it's just to हटाओ the current filter.
				 * Ditto क्रम thपढ़ो below.
				 */
				करो_zoom_dso(browser, actions);
			पूर्ण अन्यथा अगर (top == &browser->hists->thपढ़ो_filter) अणु
				करो_zoom_thपढ़ो(browser, actions);
			पूर्ण अन्यथा अगर (top == &browser->hists->socket_filter) अणु
				करो_zoom_socket(browser, actions);
			पूर्ण
			जारी;
		पूर्ण
		हाल 'q':
		हाल CTRL('c'):
			जाओ out_मुक्त_stack;
		हाल 'f':
			अगर (!is_report_browser(hbt)) अणु
				काष्ठा perf_top *top = hbt->arg;

				evlist__toggle_enable(top->evlist);
				/*
				 * No need to refresh, resort/decay histogram
				 * entries अगर we are not collecting samples:
				 */
				अगर (top->evlist->enabled) अणु
					helpline = "Press 'f' to disable the events or 'h' to see other hotkeys";
					hbt->refresh = delay_secs;
				पूर्ण अन्यथा अणु
					helpline = "Press 'f' again to re-enable the events";
					hbt->refresh = 0;
				पूर्ण
				जारी;
			पूर्ण
			/* Fall thru */
		शेष:
			helpline = "Press '?' for help on key bindings";
			जारी;
		पूर्ण

		अगर (!hists__has(hists, sym) || browser->selection == शून्य)
			जाओ skip_annotation;

		अगर (sort__mode == SORT_MODE__BRANCH) अणु

			अगर (browser->he_selection)
				bi = browser->he_selection->branch_info;

			अगर (bi == शून्य)
				जाओ skip_annotation;

			nr_options += add_annotate_opt(browser,
						       &actions[nr_options],
						       &options[nr_options],
						       &bi->from.ms,
						       bi->from.al_addr);
			अगर (bi->to.ms.sym != bi->from.ms.sym)
				nr_options += add_annotate_opt(browser,
							&actions[nr_options],
							&options[nr_options],
							&bi->to.ms,
							bi->to.al_addr);
		पूर्ण अन्यथा अणु
			nr_options += add_annotate_opt(browser,
						       &actions[nr_options],
						       &options[nr_options],
						       browser->selection,
						       browser->he_selection->ip);
		पूर्ण
skip_annotation:
		nr_options += add_thपढ़ो_opt(browser, &actions[nr_options],
					     &options[nr_options], thपढ़ो);
		nr_options += add_dso_opt(browser, &actions[nr_options],
					  &options[nr_options], map);
		nr_options += add_callchain_toggle_opt(browser, &actions[nr_options], &options[nr_options]);
		nr_options += add_map_opt(browser, &actions[nr_options],
					  &options[nr_options],
					  browser->selection ?
						browser->selection->map : शून्य);
		nr_options += add_socket_opt(browser, &actions[nr_options],
					     &options[nr_options],
					     socked_id);
		/* perf script support */
		अगर (!is_report_browser(hbt))
			जाओ skip_scripting;

		अगर (browser->he_selection) अणु
			अगर (hists__has(hists, thपढ़ो) && thपढ़ो) अणु
				nr_options += add_script_opt(browser,
							     &actions[nr_options],
							     &options[nr_options],
							     thपढ़ो, शून्य, evsel);
			पूर्ण
			/*
			 * Note that browser->selection != शून्य
			 * when browser->he_selection is not शून्य,
			 * so we करोn't need to check browser->selection
			 * beक्रमe fetching browser->selection->sym like what
			 * we करो beक्रमe fetching browser->selection->map.
			 *
			 * See hist_browser__show_entry.
			 */
			अगर (hists__has(hists, sym) && browser->selection->sym) अणु
				nr_options += add_script_opt(browser,
							     &actions[nr_options],
							     &options[nr_options],
							     शून्य, browser->selection->sym,
							     evsel);
			पूर्ण
		पूर्ण
		nr_options += add_script_opt(browser, &actions[nr_options],
					     &options[nr_options], शून्य, शून्य, evsel);
		nr_options += add_res_sample_opt(browser, &actions[nr_options],
						 &options[nr_options],
						 hist_browser__selected_res_sample(browser),
						 evsel, A_NORMAL);
		nr_options += add_res_sample_opt(browser, &actions[nr_options],
						 &options[nr_options],
						 hist_browser__selected_res_sample(browser),
						 evsel, A_ASM);
		nr_options += add_res_sample_opt(browser, &actions[nr_options],
						 &options[nr_options],
						 hist_browser__selected_res_sample(browser),
						 evsel, A_SOURCE);
		nr_options += add_चयन_opt(browser, &actions[nr_options],
					     &options[nr_options]);
skip_scripting:
		nr_options += add_निकास_opt(browser, &actions[nr_options],
					   &options[nr_options]);

		करो अणु
			काष्ठा popup_action *act;

			choice = ui__popup_menu(nr_options, options, &key);
			अगर (choice == -1)
				अवरोध;

			अगर (choice == nr_options)
				जाओ करो_hotkey;

			act = &actions[choice];
			key = act->fn(browser, act);
		पूर्ण जबतक (key == 1);

		अगर (key == K_SWITCH_INPUT_DATA)
			अवरोध;
	पूर्ण
out_मुक्त_stack:
	pstack__delete(browser->pstack);
out:
	hist_browser__delete(browser);
	मुक्त_popup_options(options, MAX_OPTIONS);
	वापस key;
पूर्ण

काष्ठा evsel_menu अणु
	काष्ठा ui_browser b;
	काष्ठा evsel *selection;
	काष्ठा annotation_options *annotation_opts;
	bool lost_events, lost_events_warned;
	भग्न min_pcnt;
	काष्ठा perf_env *env;
पूर्ण;

अटल व्योम perf_evsel_menu__ग_लिखो(काष्ठा ui_browser *browser,
				   व्योम *entry, पूर्णांक row)
अणु
	काष्ठा evsel_menu *menu = container_of(browser,
						    काष्ठा evsel_menu, b);
	काष्ठा evsel *evsel = list_entry(entry, काष्ठा evsel, core.node);
	काष्ठा hists *hists = evsel__hists(evsel);
	bool current_entry = ui_browser__is_current_entry(browser, row);
	अचिन्हित दीर्घ nr_events = hists->stats.nr_samples;
	स्थिर अक्षर *ev_name = evsel__name(evsel);
	अक्षर bf[256], unit;
	स्थिर अक्षर *warn = " ";
	माप_प्रकार prपूर्णांकed;

	ui_browser__set_color(browser, current_entry ? HE_COLORSET_SELECTED :
						       HE_COLORSET_NORMAL);

	अगर (evsel__is_group_event(evsel)) अणु
		काष्ठा evsel *pos;

		ev_name = evsel__group_name(evsel);

		क्रम_each_group_member(pos, evsel) अणु
			काष्ठा hists *pos_hists = evsel__hists(pos);
			nr_events += pos_hists->stats.nr_samples;
		पूर्ण
	पूर्ण

	nr_events = convert_unit(nr_events, &unit);
	prपूर्णांकed = scnम_लिखो(bf, माप(bf), "%lu%c%s%s", nr_events,
			   unit, unit == ' ' ? "" : " ", ev_name);
	ui_browser__म_लिखो(browser, "%s", bf);

	nr_events = evsel->evlist->stats.nr_events[PERF_RECORD_LOST];
	अगर (nr_events != 0) अणु
		menu->lost_events = true;
		अगर (!current_entry)
			ui_browser__set_color(browser, HE_COLORSET_TOP);
		nr_events = convert_unit(nr_events, &unit);
		prपूर्णांकed += scnम_लिखो(bf, माप(bf), ": %ld%c%schunks LOST!",
				     nr_events, unit, unit == ' ' ? "" : " ");
		warn = bf;
	पूर्ण

	ui_browser__ग_लिखो_nstring(browser, warn, browser->width - prपूर्णांकed);

	अगर (current_entry)
		menu->selection = evsel;
पूर्ण

अटल पूर्णांक perf_evsel_menu__run(काष्ठा evsel_menu *menu,
				पूर्णांक nr_events, स्थिर अक्षर *help,
				काष्ठा hist_browser_समयr *hbt,
				bool warn_lost_event)
अणु
	काष्ठा evlist *evlist = menu->b.priv;
	काष्ठा evsel *pos;
	स्थिर अक्षर *title = "Available samples";
	पूर्णांक delay_secs = hbt ? hbt->refresh : 0;
	पूर्णांक key;

	अगर (ui_browser__show(&menu->b, title,
			     "ESC: exit, ENTER|->: Browse histograms") < 0)
		वापस -1;

	जबतक (1) अणु
		key = ui_browser__run(&menu->b, delay_secs);

		चयन (key) अणु
		हाल K_TIMER:
			अगर (hbt)
				hbt->समयr(hbt->arg);

			अगर (!menu->lost_events_warned &&
			    menu->lost_events &&
			    warn_lost_event) अणु
				ui_browser__warn_lost_events(&menu->b);
				menu->lost_events_warned = true;
			पूर्ण
			जारी;
		हाल K_RIGHT:
		हाल K_ENTER:
			अगर (!menu->selection)
				जारी;
			pos = menu->selection;
browse_hists:
			evlist__set_selected(evlist, pos);
			/*
			 * Give the calling tool a chance to populate the non
			 * शेष evsel resorted hists tree.
			 */
			अगर (hbt)
				hbt->समयr(hbt->arg);
			key = evsel__hists_browse(pos, nr_events, help, true, hbt,
						  menu->min_pcnt, menu->env,
						  warn_lost_event,
						  menu->annotation_opts);
			ui_browser__show_title(&menu->b, title);
			चयन (key) अणु
			हाल K_TAB:
				अगर (pos->core.node.next == &evlist->core.entries)
					pos = evlist__first(evlist);
				अन्यथा
					pos = evsel__next(pos);
				जाओ browse_hists;
			हाल K_UNTAB:
				अगर (pos->core.node.prev == &evlist->core.entries)
					pos = evlist__last(evlist);
				अन्यथा
					pos = evsel__prev(pos);
				जाओ browse_hists;
			हाल K_SWITCH_INPUT_DATA:
			हाल K_RELOAD:
			हाल 'q':
			हाल CTRL('c'):
				जाओ out;
			हाल K_ESC:
			शेष:
				जारी;
			पूर्ण
		हाल K_LEFT:
			जारी;
		हाल K_ESC:
			अगर (!ui_browser__dialog_yesno(&menu->b,
					       "Do you really want to exit?"))
				जारी;
			/* Fall thru */
		हाल 'q':
		हाल CTRL('c'):
			जाओ out;
		शेष:
			जारी;
		पूर्ण
	पूर्ण

out:
	ui_browser__hide(&menu->b);
	वापस key;
पूर्ण

अटल bool filter_group_entries(काष्ठा ui_browser *browser __maybe_unused,
				 व्योम *entry)
अणु
	काष्ठा evsel *evsel = list_entry(entry, काष्ठा evsel, core.node);

	अगर (symbol_conf.event_group && !evsel__is_group_leader(evsel))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक __evlist__tui_browse_hists(काष्ठा evlist *evlist, पूर्णांक nr_entries, स्थिर अक्षर *help,
				      काष्ठा hist_browser_समयr *hbt, भग्न min_pcnt, काष्ठा perf_env *env,
				      bool warn_lost_event, काष्ठा annotation_options *annotation_opts)
अणु
	काष्ठा evsel *pos;
	काष्ठा evsel_menu menu = अणु
		.b = अणु
			.entries    = &evlist->core.entries,
			.refresh    = ui_browser__list_head_refresh,
			.seek	    = ui_browser__list_head_seek,
			.ग_लिखो	    = perf_evsel_menu__ग_लिखो,
			.filter	    = filter_group_entries,
			.nr_entries = nr_entries,
			.priv	    = evlist,
		पूर्ण,
		.min_pcnt = min_pcnt,
		.env = env,
		.annotation_opts = annotation_opts,
	पूर्ण;

	ui_helpline__push("Press ESC to exit");

	evlist__क्रम_each_entry(evlist, pos) अणु
		स्थिर अक्षर *ev_name = evsel__name(pos);
		माप_प्रकार line_len = म_माप(ev_name) + 7;

		अगर (menu.b.width < line_len)
			menu.b.width = line_len;
	पूर्ण

	वापस perf_evsel_menu__run(&menu, nr_entries, help,
				    hbt, warn_lost_event);
पूर्ण

अटल bool evlist__single_entry(काष्ठा evlist *evlist)
अणु
	पूर्णांक nr_entries = evlist->core.nr_entries;

	अगर (nr_entries == 1)
	       वापस true;

	अगर (nr_entries == 2) अणु
		काष्ठा evsel *last = evlist__last(evlist);

		अगर (evsel__is_dummy_event(last))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक evlist__tui_browse_hists(काष्ठा evlist *evlist, स्थिर अक्षर *help, काष्ठा hist_browser_समयr *hbt,
			     भग्न min_pcnt, काष्ठा perf_env *env, bool warn_lost_event,
			     काष्ठा annotation_options *annotation_opts)
अणु
	पूर्णांक nr_entries = evlist->core.nr_entries;

	अगर (evlist__single_entry(evlist)) अणु
single_entry: अणु
		काष्ठा evsel *first = evlist__first(evlist);

		वापस evsel__hists_browse(first, nr_entries, help, false, hbt, min_pcnt,
					   env, warn_lost_event, annotation_opts);
	पूर्ण
	पूर्ण

	अगर (symbol_conf.event_group) अणु
		काष्ठा evsel *pos;

		nr_entries = 0;
		evlist__क्रम_each_entry(evlist, pos) अणु
			अगर (evsel__is_group_leader(pos))
				nr_entries++;
		पूर्ण

		अगर (nr_entries == 1)
			जाओ single_entry;
	पूर्ण

	वापस __evlist__tui_browse_hists(evlist, nr_entries, help, hbt, min_pcnt, env,
					  warn_lost_event, annotation_opts);
पूर्ण

अटल पूर्णांक block_hists_browser__title(काष्ठा hist_browser *browser, अक्षर *bf,
				      माप_प्रकार size)
अणु
	काष्ठा hists *hists = evsel__hists(browser->block_evsel);
	स्थिर अक्षर *evname = evsel__name(browser->block_evsel);
	अचिन्हित दीर्घ nr_samples = hists->stats.nr_samples;
	पूर्णांक ret;

	ret = scnम_लिखो(bf, size, "# Samples: %lu", nr_samples);
	अगर (evname)
		scnम_लिखो(bf + ret, size -  ret, " of event '%s'", evname);

	वापस 0;
पूर्ण

पूर्णांक block_hists_tui_browse(काष्ठा block_hist *bh, काष्ठा evsel *evsel,
			   भग्न min_percent, काष्ठा perf_env *env,
			   काष्ठा annotation_options *annotation_opts)
अणु
	काष्ठा hists *hists = &bh->block_hists;
	काष्ठा hist_browser *browser;
	पूर्णांक key = -1;
	काष्ठा popup_action action;
	अटल स्थिर अक्षर help[] =
	" q             Quit \n";

	browser = hist_browser__new(hists);
	अगर (!browser)
		वापस -1;

	browser->block_evsel = evsel;
	browser->title = block_hists_browser__title;
	browser->min_pcnt = min_percent;
	browser->env = env;
	browser->annotation_opts = annotation_opts;

	/* reset पात key so that it can get Ctrl-C as a key */
	SLang_reset_tty();
	SLang_init_tty(0, 0, 0);

	स_रखो(&action, 0, माप(action));

	जबतक (1) अणु
		key = hist_browser__run(browser, "? - help", true, 0);

		चयन (key) अणु
		हाल 'q':
			जाओ out;
		हाल '?':
			ui_browser__help_winकरोw(&browser->b, help);
			अवरोध;
		हाल 'a':
		हाल K_ENTER:
			अगर (!browser->selection ||
			    !browser->selection->sym) अणु
				जारी;
			पूर्ण

			action.ms.map = browser->selection->map;
			action.ms.sym = browser->selection->sym;
			करो_annotate(browser, &action);
			जारी;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

out:
	hist_browser__delete(browser);
	वापस 0;
पूर्ण
