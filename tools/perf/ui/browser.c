<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "../util/string2.h"
#समावेश "../util/config.h"
#समावेश "libslang.h"
#समावेश "ui.h"
#समावेश "util.h"
#समावेश <linux/compiler.h>
#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/माला.स>
#समावेश <मानककोष.स>
#समावेश <sys/ttyशेषs.h>
#समावेश "browser.h"
#समावेश "helpline.h"
#समावेश "keysyms.h"
#समावेश "../util/color.h"
#समावेश <linux/प्रकार.स>
#समावेश <linux/zभाग.स>

अटल पूर्णांक ui_browser__percent_color(काष्ठा ui_browser *browser,
				     द्विगुन percent, bool current)
अणु
	अगर (current && (!browser->use_navkeypressed || browser->navkeypressed))
		वापस HE_COLORSET_SELECTED;
	अगर (percent >= MIN_RED)
		वापस HE_COLORSET_TOP;
	अगर (percent >= MIN_GREEN)
		वापस HE_COLORSET_MEDIUM;
	वापस HE_COLORSET_NORMAL;
पूर्ण

पूर्णांक ui_browser__set_color(काष्ठा ui_browser *browser, पूर्णांक color)
अणु
	पूर्णांक ret = browser->current_color;
	browser->current_color = color;
	SLsmg_set_color(color);
	वापस ret;
पूर्ण

व्योम ui_browser__set_percent_color(काष्ठा ui_browser *browser,
				   द्विगुन percent, bool current)
अणु
	 पूर्णांक color = ui_browser__percent_color(browser, percent, current);
	 ui_browser__set_color(browser, color);
पूर्ण

व्योम ui_browser__जाओrc_title(काष्ठा ui_browser *browser, पूर्णांक y, पूर्णांक x)
अणु
	SLsmg_जाओrc(browser->y + y, browser->x + x);
पूर्ण

व्योम ui_browser__जाओrc(काष्ठा ui_browser *browser, पूर्णांक y, पूर्णांक x)
अणु
	SLsmg_जाओrc(browser->y + y + browser->extra_title_lines, browser->x + x);
पूर्ण

व्योम ui_browser__ग_लिखो_nstring(काष्ठा ui_browser *browser __maybe_unused, स्थिर अक्षर *msg,
			       अचिन्हित पूर्णांक width)
अणु
	slsmg_ग_लिखो_nstring(msg, width);
पूर्ण

व्योम ui_browser__भ_लिखो(काष्ठा ui_browser *browser __maybe_unused, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	slsmg_भ_लिखो(fmt, args);
पूर्ण

व्योम ui_browser__म_लिखो(काष्ठा ui_browser *browser __maybe_unused, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	ui_browser__भ_लिखो(browser, fmt, args);
	बहु_पूर्ण(args);
पूर्ण

अटल काष्ठा list_head *
ui_browser__list_head_filter_entries(काष्ठा ui_browser *browser,
				     काष्ठा list_head *pos)
अणु
	करो अणु
		अगर (!browser->filter || !browser->filter(browser, pos))
			वापस pos;
		pos = pos->next;
	पूर्ण जबतक (pos != browser->entries);

	वापस शून्य;
पूर्ण

अटल काष्ठा list_head *
ui_browser__list_head_filter_prev_entries(काष्ठा ui_browser *browser,
					  काष्ठा list_head *pos)
अणु
	करो अणु
		अगर (!browser->filter || !browser->filter(browser, pos))
			वापस pos;
		pos = pos->prev;
	पूर्ण जबतक (pos != browser->entries);

	वापस शून्य;
पूर्ण

व्योम ui_browser__list_head_seek(काष्ठा ui_browser *browser, off_t offset, पूर्णांक whence)
अणु
	काष्ठा list_head *head = browser->entries;
	काष्ठा list_head *pos;

	अगर (browser->nr_entries == 0)
		वापस;

	चयन (whence) अणु
	हाल शुरू_से:
		pos = ui_browser__list_head_filter_entries(browser, head->next);
		अवरोध;
	हाल प्रस्तुत_से:
		pos = browser->top;
		अवरोध;
	हाल अंत_से:
		pos = ui_browser__list_head_filter_prev_entries(browser, head->prev);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	निश्चित(pos != शून्य);

	अगर (offset > 0) अणु
		जबतक (offset-- != 0)
			pos = ui_browser__list_head_filter_entries(browser, pos->next);
	पूर्ण अन्यथा अणु
		जबतक (offset++ != 0)
			pos = ui_browser__list_head_filter_prev_entries(browser, pos->prev);
	पूर्ण

	browser->top = pos;
पूर्ण

व्योम ui_browser__rb_tree_seek(काष्ठा ui_browser *browser, off_t offset, पूर्णांक whence)
अणु
	काष्ठा rb_root *root = browser->entries;
	काष्ठा rb_node *nd;

	चयन (whence) अणु
	हाल शुरू_से:
		nd = rb_first(root);
		अवरोध;
	हाल प्रस्तुत_से:
		nd = browser->top;
		अवरोध;
	हाल अंत_से:
		nd = rb_last(root);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (offset > 0) अणु
		जबतक (offset-- != 0)
			nd = rb_next(nd);
	पूर्ण अन्यथा अणु
		जबतक (offset++ != 0)
			nd = rb_prev(nd);
	पूर्ण

	browser->top = nd;
पूर्ण

अचिन्हित पूर्णांक ui_browser__rb_tree_refresh(काष्ठा ui_browser *browser)
अणु
	काष्ठा rb_node *nd;
	पूर्णांक row = 0;

	अगर (browser->top == शून्य)
                browser->top = rb_first(browser->entries);

	nd = browser->top;

	जबतक (nd != शून्य) अणु
		ui_browser__जाओrc(browser, row, 0);
		browser->ग_लिखो(browser, nd, row);
		अगर (++row == browser->rows)
			अवरोध;
		nd = rb_next(nd);
	पूर्ण

	वापस row;
पूर्ण

bool ui_browser__is_current_entry(काष्ठा ui_browser *browser, अचिन्हित row)
अणु
	वापस browser->top_idx + row == browser->index;
पूर्ण

व्योम ui_browser__refresh_dimensions(काष्ठा ui_browser *browser)
अणु
	browser->width = SLtt_Screen_Cols - 1;
	browser->height = browser->rows = SLtt_Screen_Rows - 2;
	browser->rows -= browser->extra_title_lines;
	browser->y = 1;
	browser->x = 0;
पूर्ण

व्योम ui_browser__handle_resize(काष्ठा ui_browser *browser)
अणु
	ui__refresh_dimensions(false);
	ui_browser__show(browser, browser->title, ui_helpline__current);
	ui_browser__refresh(browser);
पूर्ण

पूर्णांक ui_browser__warning(काष्ठा ui_browser *browser, पूर्णांक समयout,
			स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची args;
	अक्षर *text;
	पूर्णांक key = 0, err;

	बहु_शुरू(args, क्रमmat);
	err = vaप्र_लिखो(&text, क्रमmat, args);
	बहु_पूर्ण(args);

	अगर (err < 0) अणु
		बहु_शुरू(args, क्रमmat);
		ui_helpline__vpush(क्रमmat, args);
		बहु_पूर्ण(args);
	पूर्ण अन्यथा अणु
		जबतक ((key = ui__question_winकरोw("Warning!", text,
						   "Press any key...",
						   समयout)) == K_RESIZE)
			ui_browser__handle_resize(browser);
		मुक्त(text);
	पूर्ण

	वापस key;
पूर्ण

पूर्णांक ui_browser__help_winकरोw(काष्ठा ui_browser *browser, स्थिर अक्षर *text)
अणु
	पूर्णांक key;

	जबतक ((key = ui__help_winकरोw(text)) == K_RESIZE)
		ui_browser__handle_resize(browser);

	वापस key;
पूर्ण

bool ui_browser__dialog_yesno(काष्ठा ui_browser *browser, स्थिर अक्षर *text)
अणु
	पूर्णांक key;

	जबतक ((key = ui__dialog_yesno(text)) == K_RESIZE)
		ui_browser__handle_resize(browser);

	वापस key == K_ENTER || बड़े(key) == 'Y';
पूर्ण

व्योम ui_browser__reset_index(काष्ठा ui_browser *browser)
अणु
	browser->index = browser->top_idx = 0;
	browser->seek(browser, 0, शुरू_से);
पूर्ण

व्योम __ui_browser__show_title(काष्ठा ui_browser *browser, स्थिर अक्षर *title)
अणु
	SLsmg_जाओrc(0, 0);
	ui_browser__set_color(browser, HE_COLORSET_ROOT);
	ui_browser__ग_लिखो_nstring(browser, title, browser->width + 1);
पूर्ण

व्योम ui_browser__show_title(काष्ठा ui_browser *browser, स्थिर अक्षर *title)
अणु
	pthपढ़ो_mutex_lock(&ui__lock);
	__ui_browser__show_title(browser, title);
	pthपढ़ो_mutex_unlock(&ui__lock);
पूर्ण

पूर्णांक ui_browser__show(काष्ठा ui_browser *browser, स्थिर अक्षर *title,
		     स्थिर अक्षर *helpline, ...)
अणु
	पूर्णांक err;
	बहु_सूची ap;

	अगर (browser->refresh_dimensions == शून्य)
		browser->refresh_dimensions = ui_browser__refresh_dimensions;

	browser->refresh_dimensions(browser);

	pthपढ़ो_mutex_lock(&ui__lock);
	__ui_browser__show_title(browser, title);

	browser->title = title;
	zमुक्त(&browser->helpline);

	बहु_शुरू(ap, helpline);
	err = vaप्र_लिखो(&browser->helpline, helpline, ap);
	बहु_पूर्ण(ap);
	अगर (err > 0)
		ui_helpline__push(browser->helpline);
	pthपढ़ो_mutex_unlock(&ui__lock);
	वापस err ? 0 : -1;
पूर्ण

व्योम ui_browser__hide(काष्ठा ui_browser *browser)
अणु
	pthपढ़ो_mutex_lock(&ui__lock);
	ui_helpline__pop();
	zमुक्त(&browser->helpline);
	pthपढ़ो_mutex_unlock(&ui__lock);
पूर्ण

अटल व्योम ui_browser__scrollbar_set(काष्ठा ui_browser *browser)
अणु
	पूर्णांक height = browser->height, h = 0, pct = 0,
	    col = browser->width,
	    row = 0;

	अगर (browser->nr_entries > 1) अणु
		pct = ((browser->index * (browser->height - 1)) /
		       (browser->nr_entries - 1));
	पूर्ण

	SLsmg_set_अक्षर_set(1);

	जबतक (h < height) अणु
	        ui_browser__जाओrc(browser, row++, col);
		SLsmg_ग_लिखो_अक्षर(h == pct ? SLSMG_DIAMOND_CHAR : SLSMG_CKBRD_CHAR);
		++h;
	पूर्ण

	SLsmg_set_अक्षर_set(0);
पूर्ण

अटल पूर्णांक __ui_browser__refresh(काष्ठा ui_browser *browser)
अणु
	पूर्णांक row;
	पूर्णांक width = browser->width;

	row = browser->refresh(browser);
	ui_browser__set_color(browser, HE_COLORSET_NORMAL);

	अगर (!browser->use_navkeypressed || browser->navkeypressed)
		ui_browser__scrollbar_set(browser);
	अन्यथा
		width += 1;

	SLsmg_fill_region(browser->y + row + browser->extra_title_lines, browser->x,
			  browser->rows - row, width, ' ');

	अगर (browser->nr_entries == 0 && browser->no_samples_msg)
		__ui__info_winकरोw(शून्य, browser->no_samples_msg, शून्य);
	वापस 0;
पूर्ण

पूर्णांक ui_browser__refresh(काष्ठा ui_browser *browser)
अणु
	pthपढ़ो_mutex_lock(&ui__lock);
	__ui_browser__refresh(browser);
	pthपढ़ो_mutex_unlock(&ui__lock);

	वापस 0;
पूर्ण

/*
 * Here we're updating nr_entries _after_ we started browsing, i.e.  we have to
 * क्रमget about any reference to any entry in the underlying data काष्ठाure,
 * that is why we करो a शुरू_से. Think about 'perf top' in the hists browser
 * after an output_resort and hist decay.
 */
व्योम ui_browser__update_nr_entries(काष्ठा ui_browser *browser, u32 nr_entries)
अणु
	off_t offset = nr_entries - browser->nr_entries;

	browser->nr_entries = nr_entries;

	अगर (offset < 0) अणु
		अगर (browser->top_idx < (u64)-offset)
			offset = -browser->top_idx;

		browser->index += offset;
		browser->top_idx += offset;
	पूर्ण

	browser->top = शून्य;
	browser->seek(browser, browser->top_idx, शुरू_से);
पूर्ण

पूर्णांक ui_browser__run(काष्ठा ui_browser *browser, पूर्णांक delay_secs)
अणु
	पूर्णांक err, key;

	जबतक (1) अणु
		off_t offset;

		pthपढ़ो_mutex_lock(&ui__lock);
		err = __ui_browser__refresh(browser);
		SLsmg_refresh();
		pthपढ़ो_mutex_unlock(&ui__lock);
		अगर (err < 0)
			अवरोध;

		key = ui__अ_लोh(delay_secs);

		अगर (key == K_RESIZE) अणु
			ui__refresh_dimensions(false);
			browser->refresh_dimensions(browser);
			__ui_browser__show_title(browser, browser->title);
			ui_helpline__माला_दो(browser->helpline);
			जारी;
		पूर्ण

		अगर (browser->use_navkeypressed && !browser->navkeypressed) अणु
			अगर (key == K_DOWN || key == K_UP ||
			    (browser->columns && (key == K_LEFT || key == K_RIGHT)) ||
			    key == K_PGDN || key == K_PGUP ||
			    key == K_HOME || key == K_END ||
			    key == ' ') अणु
				browser->navkeypressed = true;
				जारी;
			पूर्ण अन्यथा
				वापस key;
		पूर्ण

		चयन (key) अणु
		हाल K_DOWN:
			अगर (browser->index == browser->nr_entries - 1)
				अवरोध;
			++browser->index;
			अगर (browser->index == browser->top_idx + browser->rows) अणु
				++browser->top_idx;
				browser->seek(browser, +1, प्रस्तुत_से);
			पूर्ण
			अवरोध;
		हाल K_UP:
			अगर (browser->index == 0)
				अवरोध;
			--browser->index;
			अगर (browser->index < browser->top_idx) अणु
				--browser->top_idx;
				browser->seek(browser, -1, प्रस्तुत_से);
			पूर्ण
			अवरोध;
		हाल K_RIGHT:
			अगर (!browser->columns)
				जाओ out;
			अगर (browser->horiz_scroll < browser->columns - 1)
				++browser->horiz_scroll;
			अवरोध;
		हाल K_LEFT:
			अगर (!browser->columns)
				जाओ out;
			अगर (browser->horiz_scroll != 0)
				--browser->horiz_scroll;
			अवरोध;
		हाल K_PGDN:
		हाल ' ':
			अगर (browser->top_idx + browser->rows > browser->nr_entries - 1)
				अवरोध;

			offset = browser->rows;
			अगर (browser->index + offset > browser->nr_entries - 1)
				offset = browser->nr_entries - 1 - browser->index;
			browser->index += offset;
			browser->top_idx += offset;
			browser->seek(browser, +offset, प्रस्तुत_से);
			अवरोध;
		हाल K_PGUP:
			अगर (browser->top_idx == 0)
				अवरोध;

			अगर (browser->top_idx < browser->rows)
				offset = browser->top_idx;
			अन्यथा
				offset = browser->rows;

			browser->index -= offset;
			browser->top_idx -= offset;
			browser->seek(browser, -offset, प्रस्तुत_से);
			अवरोध;
		हाल K_HOME:
			ui_browser__reset_index(browser);
			अवरोध;
		हाल K_END:
			offset = browser->rows - 1;
			अगर (offset >= browser->nr_entries)
				offset = browser->nr_entries - 1;

			browser->index = browser->nr_entries - 1;
			browser->top_idx = browser->index - offset;
			browser->seek(browser, -offset, अंत_से);
			अवरोध;
		शेष:
		out:
			वापस key;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अचिन्हित पूर्णांक ui_browser__list_head_refresh(काष्ठा ui_browser *browser)
अणु
	काष्ठा list_head *pos;
	काष्ठा list_head *head = browser->entries;
	पूर्णांक row = 0;

	अगर (browser->top == शून्य || browser->top == browser->entries)
                browser->top = ui_browser__list_head_filter_entries(browser, head->next);

	pos = browser->top;

	list_क्रम_each_from(pos, head) अणु
		अगर (!browser->filter || !browser->filter(browser, pos)) अणु
			ui_browser__जाओrc(browser, row, 0);
			browser->ग_लिखो(browser, pos, row);
			अगर (++row == browser->rows)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस row;
पूर्ण

अटल काष्ठा ui_browser_colorset अणु
	स्थिर अक्षर *name, *fg, *bg;
	पूर्णांक colorset;
पूर्ण ui_browser__colorsets[] = अणु
	अणु
		.colorset = HE_COLORSET_TOP,
		.name	  = "top",
		.fg	  = "red",
		.bg	  = "default",
	पूर्ण,
	अणु
		.colorset = HE_COLORSET_MEDIUM,
		.name	  = "medium",
		.fg	  = "green",
		.bg	  = "default",
	पूर्ण,
	अणु
		.colorset = HE_COLORSET_NORMAL,
		.name	  = "normal",
		.fg	  = "default",
		.bg	  = "default",
	पूर्ण,
	अणु
		.colorset = HE_COLORSET_SELECTED,
		.name	  = "selected",
		.fg	  = "black",
		.bg	  = "yellow",
	पूर्ण,
	अणु
		.colorset = HE_COLORSET_JUMP_ARROWS,
		.name	  = "jump_arrows",
		.fg	  = "blue",
		.bg	  = "default",
	पूर्ण,
	अणु
		.colorset = HE_COLORSET_ADDR,
		.name	  = "addr",
		.fg	  = "magenta",
		.bg	  = "default",
	पूर्ण,
	अणु
		.colorset = HE_COLORSET_ROOT,
		.name	  = "root",
		.fg	  = "white",
		.bg	  = "blue",
	पूर्ण,
	अणु
		.name = शून्य,
	पूर्ण
पूर्ण;


अटल पूर्णांक ui_browser__color_config(स्थिर अक्षर *var, स्थिर अक्षर *value,
				    व्योम *data __maybe_unused)
अणु
	अक्षर *fg = शून्य, *bg;
	पूर्णांक i;

	/* same dir क्रम all commands */
	अगर (!strstarts(var, "colors.") != 0)
		वापस 0;

	क्रम (i = 0; ui_browser__colorsets[i].name != शून्य; ++i) अणु
		स्थिर अक्षर *name = var + 7;

		अगर (म_भेद(ui_browser__colorsets[i].name, name) != 0)
			जारी;

		fg = strdup(value);
		अगर (fg == शून्य)
			अवरोध;

		bg = म_अक्षर(fg, ',');
		अगर (bg == शून्य)
			अवरोध;

		*bg = '\0';
		bg = skip_spaces(bg + 1);
		ui_browser__colorsets[i].bg = bg;
		ui_browser__colorsets[i].fg = fg;
		वापस 0;
	पूर्ण

	मुक्त(fg);
	वापस -1;
पूर्ण

व्योम ui_browser__argv_seek(काष्ठा ui_browser *browser, off_t offset, पूर्णांक whence)
अणु
	चयन (whence) अणु
	हाल शुरू_से:
		browser->top = browser->entries;
		अवरोध;
	हाल प्रस्तुत_से:
		browser->top = (अक्षर **)browser->top + offset;
		अवरोध;
	हाल अंत_से:
		browser->top = (अक्षर **)browser->entries + browser->nr_entries - 1 + offset;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	निश्चित((अक्षर **)browser->top < (अक्षर **)browser->entries + browser->nr_entries);
	निश्चित((अक्षर **)browser->top >= (अक्षर **)browser->entries);
पूर्ण

अचिन्हित पूर्णांक ui_browser__argv_refresh(काष्ठा ui_browser *browser)
अणु
	अचिन्हित पूर्णांक row = 0, idx = browser->top_idx;
	अक्षर **pos;

	अगर (browser->top == शून्य)
		browser->top = browser->entries;

	pos = (अक्षर **)browser->top;
	जबतक (idx < browser->nr_entries &&
	       row < (अचिन्हित)SLtt_Screen_Rows - 1) अणु
		निश्चित(pos < (अक्षर **)browser->entries + browser->nr_entries);
		अगर (!browser->filter || !browser->filter(browser, *pos)) अणु
			ui_browser__जाओrc(browser, row, 0);
			browser->ग_लिखो(browser, pos, row);
			अगर (++row == browser->rows)
				अवरोध;
		पूर्ण

		++idx;
		++pos;
	पूर्ण

	वापस row;
पूर्ण

व्योम __ui_browser__vline(काष्ठा ui_browser *browser, अचिन्हित पूर्णांक column,
			 u16 start, u16 end)
अणु
	SLsmg_set_अक्षर_set(1);
	ui_browser__जाओrc(browser, start, column);
	SLsmg_draw_vline(end - start + 1);
	SLsmg_set_अक्षर_set(0);
पूर्ण

व्योम ui_browser__ग_लिखो_graph(काष्ठा ui_browser *browser __maybe_unused,
			     पूर्णांक graph)
अणु
	SLsmg_set_अक्षर_set(1);
	SLsmg_ग_लिखो_अक्षर(graph);
	SLsmg_set_अक्षर_set(0);
पूर्ण

अटल व्योम __ui_browser__line_arrow_up(काष्ठा ui_browser *browser,
					अचिन्हित पूर्णांक column,
					u64 start, u64 end)
अणु
	अचिन्हित पूर्णांक row, end_row;

	SLsmg_set_अक्षर_set(1);

	अगर (start < browser->top_idx + browser->rows) अणु
		row = start - browser->top_idx;
		ui_browser__जाओrc(browser, row, column);
		SLsmg_ग_लिखो_अक्षर(SLSMG_LLCORN_CHAR);
		ui_browser__जाओrc(browser, row, column + 1);
		SLsmg_draw_hline(2);

		अगर (row-- == 0)
			जाओ out;
	पूर्ण अन्यथा
		row = browser->rows - 1;

	अगर (end > browser->top_idx)
		end_row = end - browser->top_idx;
	अन्यथा
		end_row = 0;

	ui_browser__जाओrc(browser, end_row, column);
	SLsmg_draw_vline(row - end_row + 1);

	ui_browser__जाओrc(browser, end_row, column);
	अगर (end >= browser->top_idx) अणु
		SLsmg_ग_लिखो_अक्षर(SLSMG_ULCORN_CHAR);
		ui_browser__जाओrc(browser, end_row, column + 1);
		SLsmg_ग_लिखो_अक्षर(SLSMG_HLINE_CHAR);
		ui_browser__जाओrc(browser, end_row, column + 2);
		SLsmg_ग_लिखो_अक्षर(SLSMG_RARROW_CHAR);
	पूर्ण
out:
	SLsmg_set_अक्षर_set(0);
पूर्ण

अटल व्योम __ui_browser__line_arrow_करोwn(काष्ठा ui_browser *browser,
					  अचिन्हित पूर्णांक column,
					  u64 start, u64 end)
अणु
	अचिन्हित पूर्णांक row, end_row;

	SLsmg_set_अक्षर_set(1);

	अगर (start >= browser->top_idx) अणु
		row = start - browser->top_idx;
		ui_browser__जाओrc(browser, row, column);
		SLsmg_ग_लिखो_अक्षर(SLSMG_ULCORN_CHAR);
		ui_browser__जाओrc(browser, row, column + 1);
		SLsmg_draw_hline(2);

		अगर (++row == 0)
			जाओ out;
	पूर्ण अन्यथा
		row = 0;

	अगर (end >= browser->top_idx + browser->rows)
		end_row = browser->rows - 1;
	अन्यथा
		end_row = end - browser->top_idx;

	ui_browser__जाओrc(browser, row, column);
	SLsmg_draw_vline(end_row - row + 1);

	ui_browser__जाओrc(browser, end_row, column);
	अगर (end < browser->top_idx + browser->rows) अणु
		SLsmg_ग_लिखो_अक्षर(SLSMG_LLCORN_CHAR);
		ui_browser__जाओrc(browser, end_row, column + 1);
		SLsmg_ग_लिखो_अक्षर(SLSMG_HLINE_CHAR);
		ui_browser__जाओrc(browser, end_row, column + 2);
		SLsmg_ग_लिखो_अक्षर(SLSMG_RARROW_CHAR);
	पूर्ण
out:
	SLsmg_set_अक्षर_set(0);
पूर्ण

व्योम __ui_browser__line_arrow(काष्ठा ui_browser *browser, अचिन्हित पूर्णांक column,
			      u64 start, u64 end)
अणु
	अगर (start > end)
		__ui_browser__line_arrow_up(browser, column, start, end);
	अन्यथा
		__ui_browser__line_arrow_करोwn(browser, column, start, end);
पूर्ण

व्योम ui_browser__mark_fused(काष्ठा ui_browser *browser, अचिन्हित पूर्णांक column,
			    अचिन्हित पूर्णांक row, bool arrow_करोwn)
अणु
	अचिन्हित पूर्णांक end_row;

	अगर (row >= browser->top_idx)
		end_row = row - browser->top_idx;
	अन्यथा
		वापस;

	SLsmg_set_अक्षर_set(1);

	अगर (arrow_करोwn) अणु
		ui_browser__जाओrc(browser, end_row, column - 1);
		SLsmg_ग_लिखो_अक्षर(SLSMG_ULCORN_CHAR);
		ui_browser__जाओrc(browser, end_row, column);
		SLsmg_draw_hline(2);
		ui_browser__जाओrc(browser, end_row + 1, column - 1);
		SLsmg_ग_लिखो_अक्षर(SLSMG_LTEE_CHAR);
	पूर्ण अन्यथा अणु
		ui_browser__जाओrc(browser, end_row, column - 1);
		SLsmg_ग_लिखो_अक्षर(SLSMG_LTEE_CHAR);
		ui_browser__जाओrc(browser, end_row, column);
		SLsmg_draw_hline(2);
	पूर्ण

	SLsmg_set_अक्षर_set(0);
पूर्ण

व्योम ui_browser__init(व्योम)
अणु
	पूर्णांक i = 0;

	perf_config(ui_browser__color_config, शून्य);

	जबतक (ui_browser__colorsets[i].name) अणु
		काष्ठा ui_browser_colorset *c = &ui_browser__colorsets[i++];
		sltt_set_color(c->colorset, c->name, c->fg, c->bg);
	पूर्ण
पूर्ण
