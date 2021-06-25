<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "../browser.h"
#समावेश "../helpline.h"
#समावेश "../ui.h"
#समावेश "../../util/annotate.h"
#समावेश "../../util/debug.h"
#समावेश "../../util/dso.h"
#समावेश "../../util/hist.h"
#समावेश "../../util/sort.h"
#समावेश "../../util/map.h"
#समावेश "../../util/symbol.h"
#समावेश "../../util/evsel.h"
#समावेश "../../util/evlist.h"
#समावेश <पूर्णांकtypes.h>
#समावेश <pthपढ़ो.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>
#समावेश <sys/ttyशेषs.h>
#समावेश <यंत्र/bug.h>

काष्ठा disयंत्र_line_samples अणु
	द्विगुन		      percent;
	काष्ठा sym_hist_entry he;
पूर्ण;

काष्ठा arch;

काष्ठा annotate_browser अणु
	काष्ठा ui_browser	    b;
	काष्ठा rb_root		    entries;
	काष्ठा rb_node		   *curr_hot;
	काष्ठा annotation_line	   *selection;
	काष्ठा arch		   *arch;
	काष्ठा annotation_options  *opts;
	bool			    searching_backwards;
	अक्षर			    search_bf[128];
पूर्ण;

अटल अंतरभूत काष्ठा annotation *browser__annotation(काष्ठा ui_browser *browser)
अणु
	काष्ठा map_symbol *ms = browser->priv;
	वापस symbol__annotation(ms->sym);
पूर्ण

अटल bool disयंत्र_line__filter(काष्ठा ui_browser *browser, व्योम *entry)
अणु
	काष्ठा annotation *notes = browser__annotation(browser);
	काष्ठा annotation_line *al = list_entry(entry, काष्ठा annotation_line, node);
	वापस annotation_line__filter(al, notes);
पूर्ण

अटल पूर्णांक ui_browser__jumps_percent_color(काष्ठा ui_browser *browser, पूर्णांक nr, bool current)
अणु
	काष्ठा annotation *notes = browser__annotation(browser);

	अगर (current && (!browser->use_navkeypressed || browser->navkeypressed))
		वापस HE_COLORSET_SELECTED;
	अगर (nr == notes->max_jump_sources)
		वापस HE_COLORSET_TOP;
	अगर (nr > 1)
		वापस HE_COLORSET_MEDIUM;
	वापस HE_COLORSET_NORMAL;
पूर्ण

अटल पूर्णांक ui_browser__set_jumps_percent_color(व्योम *browser, पूर्णांक nr, bool current)
अणु
	 पूर्णांक color = ui_browser__jumps_percent_color(browser, nr, current);
	 वापस ui_browser__set_color(browser, color);
पूर्ण

अटल पूर्णांक annotate_browser__set_color(व्योम *browser, पूर्णांक color)
अणु
	वापस ui_browser__set_color(browser, color);
पूर्ण

अटल व्योम annotate_browser__ग_लिखो_graph(व्योम *browser, पूर्णांक graph)
अणु
	ui_browser__ग_लिखो_graph(browser, graph);
पूर्ण

अटल व्योम annotate_browser__set_percent_color(व्योम *browser, द्विगुन percent, bool current)
अणु
	ui_browser__set_percent_color(browser, percent, current);
पूर्ण

अटल व्योम annotate_browser__म_लिखो(व्योम *browser, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	ui_browser__भ_लिखो(browser, fmt, args);
	बहु_पूर्ण(args);
पूर्ण

अटल व्योम annotate_browser__ग_लिखो(काष्ठा ui_browser *browser, व्योम *entry, पूर्णांक row)
अणु
	काष्ठा annotate_browser *ab = container_of(browser, काष्ठा annotate_browser, b);
	काष्ठा annotation *notes = browser__annotation(browser);
	काष्ठा annotation_line *al = list_entry(entry, काष्ठा annotation_line, node);
	स्थिर bool is_current_entry = ui_browser__is_current_entry(browser, row);
	काष्ठा annotation_ग_लिखो_ops ops = अणु
		.first_line		 = row == 0,
		.current_entry		 = is_current_entry,
		.change_color		 = (!notes->options->hide_src_code &&
					    (!is_current_entry ||
					     (browser->use_navkeypressed &&
					      !browser->navkeypressed))),
		.width			 = browser->width,
		.obj			 = browser,
		.set_color		 = annotate_browser__set_color,
		.set_percent_color	 = annotate_browser__set_percent_color,
		.set_jumps_percent_color = ui_browser__set_jumps_percent_color,
		.म_लिखो			 = annotate_browser__म_लिखो,
		.ग_लिखो_graph		 = annotate_browser__ग_लिखो_graph,
	पूर्ण;

	/* The scroll bar isn't being used */
	अगर (!browser->navkeypressed)
		ops.width += 1;

	annotation_line__ग_लिखो(al, notes, &ops, ab->opts);

	अगर (ops.current_entry)
		ab->selection = al;
पूर्ण

अटल bool is_fused(काष्ठा annotate_browser *ab, काष्ठा disयंत्र_line *cursor)
अणु
	काष्ठा disयंत्र_line *pos = list_prev_entry(cursor, al.node);
	स्थिर अक्षर *name;

	अगर (!pos)
		वापस false;

	अगर (ins__is_lock(&pos->ins))
		name = pos->ops.locked.ins.name;
	अन्यथा
		name = pos->ins.name;

	अगर (!name || !cursor->ins.name)
		वापस false;

	वापस ins__is_fused(ab->arch, name, cursor->ins.name);
पूर्ण

अटल व्योम annotate_browser__draw_current_jump(काष्ठा ui_browser *browser)
अणु
	काष्ठा annotate_browser *ab = container_of(browser, काष्ठा annotate_browser, b);
	काष्ठा disयंत्र_line *cursor = disयंत्र_line(ab->selection);
	काष्ठा annotation_line *target;
	अचिन्हित पूर्णांक from, to;
	काष्ठा map_symbol *ms = ab->b.priv;
	काष्ठा symbol *sym = ms->sym;
	काष्ठा annotation *notes = symbol__annotation(sym);
	u8 pcnt_width = annotation__pcnt_width(notes);
	पूर्णांक width;

	/* PLT symbols contain बाह्यal offsets */
	अगर (म_माला(sym->name, "@plt"))
		वापस;

	अगर (!disयंत्र_line__is_valid_local_jump(cursor, sym))
		वापस;

	/*
	 * This first was seen with a gcc function, _cpp_lex_token, that
	 * has the usual jumps:
	 *
	 *  ै1159e6c: ै jne    115aa32 <_cpp_lex_token@@Base+0xf92>
	 *
	 * I.e. jumps to a label inside that function (_cpp_lex_token), and
	 * those works, but also this kind:
	 *
	 *  ै1159e8b: ै jne    c469be <cpp_named_चालक2name@@Base+0xa72>
	 *
	 *  I.e. jumps to another function, outside _cpp_lex_token, which
	 *  are not being correctly handled generating as a side effect references
	 *  to ab->offset[] entries that are set to शून्य, so to make this code
	 *  more robust, check that here.
	 *
	 *  A proper fix क्रम will be put in place, looking at the function
	 *  name right after the '<' token and probably treating this like a
	 *  'call' inकाष्ठाion.
	 */
	target = notes->offsets[cursor->ops.target.offset];
	अगर (target == शून्य) अणु
		ui_helpline__म_लिखो("WARN: jump target inconsistency, press 'o', notes->offsets[%#x] = NULL\n",
				    cursor->ops.target.offset);
		वापस;
	पूर्ण

	अगर (notes->options->hide_src_code) अणु
		from = cursor->al.idx_यंत्र;
		to = target->idx_यंत्र;
	पूर्ण अन्यथा अणु
		from = (u64)cursor->al.idx;
		to = (u64)target->idx;
	पूर्ण

	width = annotation__cycles_width(notes);

	ui_browser__set_color(browser, HE_COLORSET_JUMP_ARROWS);
	__ui_browser__line_arrow(browser,
				 pcnt_width + 2 + notes->widths.addr + width,
				 from, to);

	अगर (is_fused(ab, cursor)) अणु
		ui_browser__mark_fused(browser,
				       pcnt_width + 3 + notes->widths.addr + width,
				       from - 1,
				       to > from);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक annotate_browser__refresh(काष्ठा ui_browser *browser)
अणु
	काष्ठा annotation *notes = browser__annotation(browser);
	पूर्णांक ret = ui_browser__list_head_refresh(browser);
	पूर्णांक pcnt_width = annotation__pcnt_width(notes);

	अगर (notes->options->jump_arrows)
		annotate_browser__draw_current_jump(browser);

	ui_browser__set_color(browser, HE_COLORSET_NORMAL);
	__ui_browser__vline(browser, pcnt_width, 0, browser->rows - 1);
	वापस ret;
पूर्ण

अटल द्विगुन disयंत्र__cmp(काष्ठा annotation_line *a, काष्ठा annotation_line *b,
						  पूर्णांक percent_type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < a->data_nr; i++) अणु
		अगर (a->data[i].percent[percent_type] == b->data[i].percent[percent_type])
			जारी;
		वापस a->data[i].percent[percent_type] -
			   b->data[i].percent[percent_type];
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम disयंत्र_rb_tree__insert(काष्ठा annotate_browser *browser,
				काष्ठा annotation_line *al)
अणु
	काष्ठा rb_root *root = &browser->entries;
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा annotation_line *l;

	जबतक (*p != शून्य) अणु
		parent = *p;
		l = rb_entry(parent, काष्ठा annotation_line, rb_node);

		अगर (disयंत्र__cmp(al, l, browser->opts->percent_type) < 0)
			p = &(*p)->rb_left;
		अन्यथा
			p = &(*p)->rb_right;
	पूर्ण
	rb_link_node(&al->rb_node, parent, p);
	rb_insert_color(&al->rb_node, root);
पूर्ण

अटल व्योम annotate_browser__set_top(काष्ठा annotate_browser *browser,
				      काष्ठा annotation_line *pos, u32 idx)
अणु
	काष्ठा annotation *notes = browser__annotation(&browser->b);
	अचिन्हित back;

	ui_browser__refresh_dimensions(&browser->b);
	back = browser->b.height / 2;
	browser->b.top_idx = browser->b.index = idx;

	जबतक (browser->b.top_idx != 0 && back != 0) अणु
		pos = list_entry(pos->node.prev, काष्ठा annotation_line, node);

		अगर (annotation_line__filter(pos, notes))
			जारी;

		--browser->b.top_idx;
		--back;
	पूर्ण

	browser->b.top = pos;
	browser->b.navkeypressed = true;
पूर्ण

अटल व्योम annotate_browser__set_rb_top(काष्ठा annotate_browser *browser,
					 काष्ठा rb_node *nd)
अणु
	काष्ठा annotation *notes = browser__annotation(&browser->b);
	काष्ठा annotation_line * pos = rb_entry(nd, काष्ठा annotation_line, rb_node);
	u32 idx = pos->idx;

	अगर (notes->options->hide_src_code)
		idx = pos->idx_यंत्र;
	annotate_browser__set_top(browser, pos, idx);
	browser->curr_hot = nd;
पूर्ण

अटल व्योम annotate_browser__calc_percent(काष्ठा annotate_browser *browser,
					   काष्ठा evsel *evsel)
अणु
	काष्ठा map_symbol *ms = browser->b.priv;
	काष्ठा symbol *sym = ms->sym;
	काष्ठा annotation *notes = symbol__annotation(sym);
	काष्ठा disयंत्र_line *pos;

	browser->entries = RB_ROOT;

	pthपढ़ो_mutex_lock(&notes->lock);

	symbol__calc_percent(sym, evsel);

	list_क्रम_each_entry(pos, &notes->src->source, al.node) अणु
		द्विगुन max_percent = 0.0;
		पूर्णांक i;

		अगर (pos->al.offset == -1) अणु
			RB_CLEAR_NODE(&pos->al.rb_node);
			जारी;
		पूर्ण

		क्रम (i = 0; i < pos->al.data_nr; i++) अणु
			द्विगुन percent;

			percent = annotation_data__percent(&pos->al.data[i],
							   browser->opts->percent_type);

			अगर (max_percent < percent)
				max_percent = percent;
		पूर्ण

		अगर (max_percent < 0.01 && pos->al.ipc == 0) अणु
			RB_CLEAR_NODE(&pos->al.rb_node);
			जारी;
		पूर्ण
		disयंत्र_rb_tree__insert(browser, &pos->al);
	पूर्ण
	pthपढ़ो_mutex_unlock(&notes->lock);

	browser->curr_hot = rb_last(&browser->entries);
पूर्ण

अटल bool annotate_browser__toggle_source(काष्ठा annotate_browser *browser)
अणु
	काष्ठा annotation *notes = browser__annotation(&browser->b);
	काष्ठा annotation_line *al;
	off_t offset = browser->b.index - browser->b.top_idx;

	browser->b.seek(&browser->b, offset, प्रस्तुत_से);
	al = list_entry(browser->b.top, काष्ठा annotation_line, node);

	अगर (notes->options->hide_src_code) अणु
		अगर (al->idx_यंत्र < offset)
			offset = al->idx;

		browser->b.nr_entries = notes->nr_entries;
		notes->options->hide_src_code = false;
		browser->b.seek(&browser->b, -offset, प्रस्तुत_से);
		browser->b.top_idx = al->idx - offset;
		browser->b.index = al->idx;
	पूर्ण अन्यथा अणु
		अगर (al->idx_यंत्र < 0) अणु
			ui_helpline__माला_दो("Only available for assembly lines.");
			browser->b.seek(&browser->b, -offset, प्रस्तुत_से);
			वापस false;
		पूर्ण

		अगर (al->idx_यंत्र < offset)
			offset = al->idx_यंत्र;

		browser->b.nr_entries = notes->nr_यंत्र_entries;
		notes->options->hide_src_code = true;
		browser->b.seek(&browser->b, -offset, प्रस्तुत_से);
		browser->b.top_idx = al->idx_यंत्र - offset;
		browser->b.index = al->idx_यंत्र;
	पूर्ण

	वापस true;
पूर्ण

#घोषणा SYM_TITLE_MAX_SIZE (PATH_MAX + 64)

अटल व्योम annotate_browser__show_full_location(काष्ठा ui_browser *browser)
अणु
	काष्ठा annotate_browser *ab = container_of(browser, काष्ठा annotate_browser, b);
	काष्ठा disयंत्र_line *cursor = disयंत्र_line(ab->selection);
	काष्ठा annotation_line *al = &cursor->al;

	अगर (al->offset != -1)
		ui_helpline__माला_दो("Only available for source code lines.");
	अन्यथा अगर (al->fileloc == शून्य)
		ui_helpline__माला_दो("No source file location.");
	अन्यथा अणु
		अक्षर help_line[SYM_TITLE_MAX_SIZE];
		प्र_लिखो (help_line, "Source file location: %s", al->fileloc);
		ui_helpline__माला_दो(help_line);
	पूर्ण
पूर्ण

अटल व्योम ui_browser__init_यंत्र_mode(काष्ठा ui_browser *browser)
अणु
	काष्ठा annotation *notes = browser__annotation(browser);
	ui_browser__reset_index(browser);
	browser->nr_entries = notes->nr_यंत्र_entries;
पूर्ण

अटल पूर्णांक sym_title(काष्ठा symbol *sym, काष्ठा map *map, अक्षर *title,
		     माप_प्रकार sz, पूर्णांक percent_type)
अणु
	वापस snम_लिखो(title, sz, "%s  %s [Percent: %s]", sym->name, map->dso->दीर्घ_name,
			percent_type_str(percent_type));
पूर्ण

/*
 * This can be called from बाह्यal jumps, i.e. jumps from one function
 * to another, like from the kernel's entry_SYSCALL_64 function to the
 * swapgs_restore_regs_and_वापस_to_usermode() function.
 *
 * So all we check here is that dl->ops.target.sym is set, अगर it is, just
 * go to that function and when निकासing from its disassembly, come back
 * to the calling function.
 */
अटल bool annotate_browser__callq(काष्ठा annotate_browser *browser,
				    काष्ठा evsel *evsel,
				    काष्ठा hist_browser_समयr *hbt)
अणु
	काष्ठा map_symbol *ms = browser->b.priv, target_ms;
	काष्ठा disयंत्र_line *dl = disयंत्र_line(browser->selection);
	काष्ठा annotation *notes;
	अक्षर title[SYM_TITLE_MAX_SIZE];

	अगर (!dl->ops.target.sym) अणु
		ui_helpline__माला_दो("The called function was not found.");
		वापस true;
	पूर्ण

	notes = symbol__annotation(dl->ops.target.sym);
	pthपढ़ो_mutex_lock(&notes->lock);

	अगर (!symbol__hists(dl->ops.target.sym, evsel->evlist->core.nr_entries)) अणु
		pthपढ़ो_mutex_unlock(&notes->lock);
		ui__warning("Not enough memory for annotating '%s' symbol!\n",
			    dl->ops.target.sym->name);
		वापस true;
	पूर्ण

	target_ms.maps = ms->maps;
	target_ms.map = ms->map;
	target_ms.sym = dl->ops.target.sym;
	pthपढ़ो_mutex_unlock(&notes->lock);
	symbol__tui_annotate(&target_ms, evsel, hbt, browser->opts);
	sym_title(ms->sym, ms->map, title, माप(title), browser->opts->percent_type);
	ui_browser__show_title(&browser->b, title);
	वापस true;
पूर्ण

अटल
काष्ठा disयंत्र_line *annotate_browser__find_offset(काष्ठा annotate_browser *browser,
					  s64 offset, s64 *idx)
अणु
	काष्ठा annotation *notes = browser__annotation(&browser->b);
	काष्ठा disयंत्र_line *pos;

	*idx = 0;
	list_क्रम_each_entry(pos, &notes->src->source, al.node) अणु
		अगर (pos->al.offset == offset)
			वापस pos;
		अगर (!annotation_line__filter(&pos->al, notes))
			++*idx;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool annotate_browser__jump(काष्ठा annotate_browser *browser,
				   काष्ठा evsel *evsel,
				   काष्ठा hist_browser_समयr *hbt)
अणु
	काष्ठा disयंत्र_line *dl = disयंत्र_line(browser->selection);
	u64 offset;
	s64 idx;

	अगर (!ins__is_jump(&dl->ins))
		वापस false;

	अगर (dl->ops.target.outside) अणु
		annotate_browser__callq(browser, evsel, hbt);
		वापस true;
	पूर्ण

	offset = dl->ops.target.offset;
	dl = annotate_browser__find_offset(browser, offset, &idx);
	अगर (dl == शून्य) अणु
		ui_helpline__म_लिखो("Invalid jump offset: %" PRIx64, offset);
		वापस true;
	पूर्ण

	annotate_browser__set_top(browser, &dl->al, idx);

	वापस true;
पूर्ण

अटल
काष्ठा annotation_line *annotate_browser__find_string(काष्ठा annotate_browser *browser,
					  अक्षर *s, s64 *idx)
अणु
	काष्ठा annotation *notes = browser__annotation(&browser->b);
	काष्ठा annotation_line *al = browser->selection;

	*idx = browser->b.index;
	list_क्रम_each_entry_जारी(al, &notes->src->source, node) अणु
		अगर (annotation_line__filter(al, notes))
			जारी;

		++*idx;

		अगर (al->line && म_माला(al->line, s) != शून्य)
			वापस al;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool __annotate_browser__search(काष्ठा annotate_browser *browser)
अणु
	काष्ठा annotation_line *al;
	s64 idx;

	al = annotate_browser__find_string(browser, browser->search_bf, &idx);
	अगर (al == शून्य) अणु
		ui_helpline__माला_दो("String not found!");
		वापस false;
	पूर्ण

	annotate_browser__set_top(browser, al, idx);
	browser->searching_backwards = false;
	वापस true;
पूर्ण

अटल
काष्ठा annotation_line *annotate_browser__find_string_reverse(काष्ठा annotate_browser *browser,
						  अक्षर *s, s64 *idx)
अणु
	काष्ठा annotation *notes = browser__annotation(&browser->b);
	काष्ठा annotation_line *al = browser->selection;

	*idx = browser->b.index;
	list_क्रम_each_entry_जारी_reverse(al, &notes->src->source, node) अणु
		अगर (annotation_line__filter(al, notes))
			जारी;

		--*idx;

		अगर (al->line && म_माला(al->line, s) != शून्य)
			वापस al;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool __annotate_browser__search_reverse(काष्ठा annotate_browser *browser)
अणु
	काष्ठा annotation_line *al;
	s64 idx;

	al = annotate_browser__find_string_reverse(browser, browser->search_bf, &idx);
	अगर (al == शून्य) अणु
		ui_helpline__माला_दो("String not found!");
		वापस false;
	पूर्ण

	annotate_browser__set_top(browser, al, idx);
	browser->searching_backwards = true;
	वापस true;
पूर्ण

अटल bool annotate_browser__search_winकरोw(काष्ठा annotate_browser *browser,
					    पूर्णांक delay_secs)
अणु
	अगर (ui_browser__input_winकरोw("Search", "String: ", browser->search_bf,
				     "ENTER: OK, ESC: Cancel",
				     delay_secs * 2) != K_ENTER ||
	    !*browser->search_bf)
		वापस false;

	वापस true;
पूर्ण

अटल bool annotate_browser__search(काष्ठा annotate_browser *browser, पूर्णांक delay_secs)
अणु
	अगर (annotate_browser__search_winकरोw(browser, delay_secs))
		वापस __annotate_browser__search(browser);

	वापस false;
पूर्ण

अटल bool annotate_browser__जारी_search(काष्ठा annotate_browser *browser,
					      पूर्णांक delay_secs)
अणु
	अगर (!*browser->search_bf)
		वापस annotate_browser__search(browser, delay_secs);

	वापस __annotate_browser__search(browser);
पूर्ण

अटल bool annotate_browser__search_reverse(काष्ठा annotate_browser *browser,
					   पूर्णांक delay_secs)
अणु
	अगर (annotate_browser__search_winकरोw(browser, delay_secs))
		वापस __annotate_browser__search_reverse(browser);

	वापस false;
पूर्ण

अटल
bool annotate_browser__जारी_search_reverse(काष्ठा annotate_browser *browser,
					       पूर्णांक delay_secs)
अणु
	अगर (!*browser->search_bf)
		वापस annotate_browser__search_reverse(browser, delay_secs);

	वापस __annotate_browser__search_reverse(browser);
पूर्ण

अटल पूर्णांक annotate_browser__show(काष्ठा ui_browser *browser, अक्षर *title, स्थिर अक्षर *help)
अणु
	काष्ठा annotate_browser *ab = container_of(browser, काष्ठा annotate_browser, b);
	काष्ठा map_symbol *ms = browser->priv;
	काष्ठा symbol *sym = ms->sym;
	अक्षर symbol_dso[SYM_TITLE_MAX_SIZE];

	अगर (ui_browser__show(browser, title, help) < 0)
		वापस -1;

	sym_title(sym, ms->map, symbol_dso, माप(symbol_dso), ab->opts->percent_type);

	ui_browser__जाओrc_title(browser, 0, 0);
	ui_browser__set_color(browser, HE_COLORSET_ROOT);
	ui_browser__ग_लिखो_nstring(browser, symbol_dso, browser->width + 1);
	वापस 0;
पूर्ण

अटल व्योम
चयन_percent_type(काष्ठा annotation_options *opts, bool base)
अणु
	चयन (opts->percent_type) अणु
	हाल PERCENT_HITS_LOCAL:
		अगर (base)
			opts->percent_type = PERCENT_PERIOD_LOCAL;
		अन्यथा
			opts->percent_type = PERCENT_HITS_GLOBAL;
		अवरोध;
	हाल PERCENT_HITS_GLOBAL:
		अगर (base)
			opts->percent_type = PERCENT_PERIOD_GLOBAL;
		अन्यथा
			opts->percent_type = PERCENT_HITS_LOCAL;
		अवरोध;
	हाल PERCENT_PERIOD_LOCAL:
		अगर (base)
			opts->percent_type = PERCENT_HITS_LOCAL;
		अन्यथा
			opts->percent_type = PERCENT_PERIOD_GLOBAL;
		अवरोध;
	हाल PERCENT_PERIOD_GLOBAL:
		अगर (base)
			opts->percent_type = PERCENT_HITS_GLOBAL;
		अन्यथा
			opts->percent_type = PERCENT_PERIOD_LOCAL;
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

अटल पूर्णांक annotate_browser__run(काष्ठा annotate_browser *browser,
				 काष्ठा evsel *evsel,
				 काष्ठा hist_browser_समयr *hbt)
अणु
	काष्ठा rb_node *nd = शून्य;
	काष्ठा hists *hists = evsel__hists(evsel);
	काष्ठा map_symbol *ms = browser->b.priv;
	काष्ठा symbol *sym = ms->sym;
	काष्ठा annotation *notes = symbol__annotation(ms->sym);
	स्थिर अक्षर *help = "Press 'h' for help on key bindings";
	पूर्णांक delay_secs = hbt ? hbt->refresh : 0;
	अक्षर title[256];
	पूर्णांक key;

	hists__scnम_लिखो_title(hists, title, माप(title));
	अगर (annotate_browser__show(&browser->b, title, help) < 0)
		वापस -1;

	annotate_browser__calc_percent(browser, evsel);

	अगर (browser->curr_hot) अणु
		annotate_browser__set_rb_top(browser, browser->curr_hot);
		browser->b.navkeypressed = false;
	पूर्ण

	nd = browser->curr_hot;

	जबतक (1) अणु
		key = ui_browser__run(&browser->b, delay_secs);

		अगर (delay_secs != 0) अणु
			annotate_browser__calc_percent(browser, evsel);
			/*
			 * Current line focus got out of the list of most active
			 * lines, शून्य it so that अगर TAB|UNTAB is pressed, we
			 * move to curr_hot (current hottest line).
			 */
			अगर (nd != शून्य && RB_EMPTY_NODE(nd))
				nd = शून्य;
		पूर्ण

		चयन (key) अणु
		हाल K_TIMER:
			अगर (hbt)
				hbt->समयr(hbt->arg);

			अगर (delay_secs != 0) अणु
				symbol__annotate_decay_histogram(sym, evsel->idx);
				hists__scnम_लिखो_title(hists, title, माप(title));
				annotate_browser__show(&browser->b, title, help);
			पूर्ण
			जारी;
		हाल K_TAB:
			अगर (nd != शून्य) अणु
				nd = rb_prev(nd);
				अगर (nd == शून्य)
					nd = rb_last(&browser->entries);
			पूर्ण अन्यथा
				nd = browser->curr_hot;
			अवरोध;
		हाल K_UNTAB:
			अगर (nd != शून्य) अणु
				nd = rb_next(nd);
				अगर (nd == शून्य)
					nd = rb_first(&browser->entries);
			पूर्ण अन्यथा
				nd = browser->curr_hot;
			अवरोध;
		हाल K_F1:
		हाल 'h':
			ui_browser__help_winकरोw(&browser->b,
		"UP/DOWN/PGUP\n"
		"PGDN/SPACE    Navigate\n"
		"q/ESC/CTRL+C  Exit\n\n"
		"ENTER         Go to target\n"
		"ESC           Exit\n"
		"H             Go to hottest instruction\n"
		"TAB/shift+TAB Cycle thru hottest instructions\n"
		"j             Toggle showing jump to target arrows\n"
		"J             Toggle showing number of jump sources on targets\n"
		"n             Search next string\n"
		"o             Toggle disassembler output/simplified view\n"
		"O             Bump offset level (jump targets -> +call -> all -> cycle thru)\n"
		"s             Toggle source code view\n"
		"t             Circulate percent, total period, samples view\n"
		"c             Show min/max cycle\n"
		"/             Search string\n"
		"k             Toggle line numbers\n"
		"l             Show full source file location\n"
		"P             Print to [symbol_name].annotation file.\n"
		"r             Run available scripts\n"
		"p             Toggle percent type [local/global]\n"
		"b             Toggle percent base [period/hits]\n"
		"?             Search string backwards\n");
			जारी;
		हाल 'r':
			script_browse(शून्य, शून्य);
			annotate_browser__show(&browser->b, title, help);
			जारी;
		हाल 'k':
			notes->options->show_linenr = !notes->options->show_linenr;
			जारी;
		हाल 'l':
			annotate_browser__show_full_location (&browser->b);
			जारी;
		हाल 'H':
			nd = browser->curr_hot;
			अवरोध;
		हाल 's':
			अगर (annotate_browser__toggle_source(browser))
				ui_helpline__माला_दो(help);
			जारी;
		हाल 'o':
			notes->options->use_offset = !notes->options->use_offset;
			annotation__update_column_widths(notes);
			जारी;
		हाल 'O':
			अगर (++notes->options->offset_level > ANNOTATION__MAX_OFFSET_LEVEL)
				notes->options->offset_level = ANNOTATION__MIN_OFFSET_LEVEL;
			जारी;
		हाल 'j':
			notes->options->jump_arrows = !notes->options->jump_arrows;
			जारी;
		हाल 'J':
			notes->options->show_nr_jumps = !notes->options->show_nr_jumps;
			annotation__update_column_widths(notes);
			जारी;
		हाल '/':
			अगर (annotate_browser__search(browser, delay_secs)) अणु
show_help:
				ui_helpline__माला_दो(help);
			पूर्ण
			जारी;
		हाल 'n':
			अगर (browser->searching_backwards ?
			    annotate_browser__जारी_search_reverse(browser, delay_secs) :
			    annotate_browser__जारी_search(browser, delay_secs))
				जाओ show_help;
			जारी;
		हाल '?':
			अगर (annotate_browser__search_reverse(browser, delay_secs))
				जाओ show_help;
			जारी;
		हाल 'D': अणु
			अटल पूर्णांक seq;
			ui_helpline__pop();
			ui_helpline__fpush("%d: nr_ent=%d, height=%d, idx=%d, top_idx=%d, nr_asm_entries=%d",
					   seq++, browser->b.nr_entries,
					   browser->b.height,
					   browser->b.index,
					   browser->b.top_idx,
					   notes->nr_यंत्र_entries);
		पूर्ण
			जारी;
		हाल K_ENTER:
		हाल K_RIGHT:
		अणु
			काष्ठा disयंत्र_line *dl = disयंत्र_line(browser->selection);

			अगर (browser->selection == शून्य)
				ui_helpline__माला_दो("Huh? No selection. Report to linux-kernel@vger.kernel.org");
			अन्यथा अगर (browser->selection->offset == -1)
				ui_helpline__माला_दो("Actions are only available for assembly lines.");
			अन्यथा अगर (!dl->ins.ops)
				जाओ show_sup_ins;
			अन्यथा अगर (ins__is_ret(&dl->ins))
				जाओ out;
			अन्यथा अगर (!(annotate_browser__jump(browser, evsel, hbt) ||
				     annotate_browser__callq(browser, evsel, hbt))) अणु
show_sup_ins:
				ui_helpline__माला_दो("Actions are only available for function call/return & jump/branch instructions.");
			पूर्ण
			जारी;
		पूर्ण
		हाल 'P':
			map_symbol__annotation_dump(ms, evsel, browser->opts);
			जारी;
		हाल 't':
			अगर (symbol_conf.show_total_period) अणु
				symbol_conf.show_total_period = false;
				symbol_conf.show_nr_samples = true;
			पूर्ण अन्यथा अगर (symbol_conf.show_nr_samples)
				symbol_conf.show_nr_samples = false;
			अन्यथा
				symbol_conf.show_total_period = true;
			annotation__update_column_widths(notes);
			जारी;
		हाल 'c':
			अगर (notes->options->show_minmax_cycle)
				notes->options->show_minmax_cycle = false;
			अन्यथा
				notes->options->show_minmax_cycle = true;
			annotation__update_column_widths(notes);
			जारी;
		हाल 'p':
		हाल 'b':
			चयन_percent_type(browser->opts, key == 'b');
			hists__scnम_लिखो_title(hists, title, माप(title));
			annotate_browser__show(&browser->b, title, help);
			जारी;
		हाल K_LEFT:
		हाल K_ESC:
		हाल 'q':
		हाल CTRL('c'):
			जाओ out;
		शेष:
			जारी;
		पूर्ण

		अगर (nd != शून्य)
			annotate_browser__set_rb_top(browser, nd);
	पूर्ण
out:
	ui_browser__hide(&browser->b);
	वापस key;
पूर्ण

पूर्णांक map_symbol__tui_annotate(काष्ठा map_symbol *ms, काष्ठा evsel *evsel,
			     काष्ठा hist_browser_समयr *hbt,
			     काष्ठा annotation_options *opts)
अणु
	वापस symbol__tui_annotate(ms, evsel, hbt, opts);
पूर्ण

पूर्णांक hist_entry__tui_annotate(काष्ठा hist_entry *he, काष्ठा evsel *evsel,
			     काष्ठा hist_browser_समयr *hbt,
			     काष्ठा annotation_options *opts)
अणु
	/* reset पात key so that it can get Ctrl-C as a key */
	SLang_reset_tty();
	SLang_init_tty(0, 0, 0);

	वापस map_symbol__tui_annotate(&he->ms, evsel, hbt, opts);
पूर्ण

पूर्णांक symbol__tui_annotate(काष्ठा map_symbol *ms, काष्ठा evsel *evsel,
			 काष्ठा hist_browser_समयr *hbt,
			 काष्ठा annotation_options *opts)
अणु
	काष्ठा symbol *sym = ms->sym;
	काष्ठा annotation *notes = symbol__annotation(sym);
	काष्ठा annotate_browser browser = अणु
		.b = अणु
			.refresh = annotate_browser__refresh,
			.seek	 = ui_browser__list_head_seek,
			.ग_लिखो	 = annotate_browser__ग_लिखो,
			.filter  = disयंत्र_line__filter,
			.extra_title_lines = 1, /* क्रम hists__scnम_लिखो_title() */
			.priv	 = ms,
			.use_navkeypressed = true,
		पूर्ण,
		.opts = opts,
	पूर्ण;
	पूर्णांक ret = -1, err;

	अगर (sym == शून्य)
		वापस -1;

	अगर (ms->map->dso->annotate_warned)
		वापस -1;

	err = symbol__annotate2(ms, evsel, opts, &browser.arch);
	अगर (err) अणु
		अक्षर msg[बफ_मान];
		symbol__म_त्रुटि_disassemble(ms, err, msg, माप(msg));
		ui__error("Couldn't annotate %s:\n%s", sym->name, msg);
		जाओ out_मुक्त_offsets;
	पूर्ण

	ui_helpline__push("Press ESC to exit");

	browser.b.width = notes->max_line_len;
	browser.b.nr_entries = notes->nr_entries;
	browser.b.entries = &notes->src->source,
	browser.b.width += 18; /* Percentage */

	अगर (notes->options->hide_src_code)
		ui_browser__init_यंत्र_mode(&browser.b);

	ret = annotate_browser__run(&browser, evsel, hbt);

	annotated_source__purge(notes->src);

out_मुक्त_offsets:
	zमुक्त(&notes->offsets);
	वापस ret;
पूर्ण
