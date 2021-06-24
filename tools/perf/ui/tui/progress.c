<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश "../progress.h"
#समावेश "../libslang.h"
#समावेश "../ui.h"
#समावेश "tui.h"
#समावेश "units.h"
#समावेश "../browser.h"

अटल व्योम __tui_progress__init(काष्ठा ui_progress *p)
अणु
	p->next = p->step = p->total / (SLtt_Screen_Cols - 2) ?: 1;
पूर्ण

अटल पूर्णांक get_title(काष्ठा ui_progress *p, अक्षर *buf, माप_प्रकार size)
अणु
	अक्षर buf_cur[20];
	अक्षर buf_tot[20];
	पूर्णांक ret;

	ret  = unit_number__scnम_लिखो(buf_cur, माप(buf_cur), p->curr);
	ret += unit_number__scnम_लिखो(buf_tot, माप(buf_tot), p->total);

	वापस ret + scnम_लिखो(buf, size, "%s [%s/%s]",
			       p->title, buf_cur, buf_tot);
पूर्ण

अटल व्योम tui_progress__update(काष्ठा ui_progress *p)
अणु
	अक्षर buf[100], *title = (अक्षर *) p->title;
	पूर्णांक bar, y;
	/*
	 * FIXME: We should have a per UI backend way of showing progress,
	 * stdio will just show a percentage as NN%, etc.
	 */
	अगर (use_browser <= 0)
		वापस;

	अगर (p->total == 0)
		वापस;

	अगर (p->size) अणु
		get_title(p, buf, माप(buf));
		title = buf;
	पूर्ण

	ui__refresh_dimensions(false);
	pthपढ़ो_mutex_lock(&ui__lock);
	y = SLtt_Screen_Rows / 2 - 2;
	SLsmg_set_color(0);
	SLsmg_draw_box(y, 0, 3, SLtt_Screen_Cols);
	SLsmg_जाओrc(y++, 1);
	SLsmg_ग_लिखो_string(title);
	SLsmg_fill_region(y, 1, 1, SLtt_Screen_Cols - 2, ' ');
	SLsmg_set_color(HE_COLORSET_SELECTED);
	bar = ((SLtt_Screen_Cols - 2) * p->curr) / p->total;
	SLsmg_fill_region(y, 1, 1, bar, ' ');
	SLsmg_refresh();
	pthपढ़ो_mutex_unlock(&ui__lock);
पूर्ण

अटल व्योम tui_progress__finish(व्योम)
अणु
	पूर्णांक y;

	अगर (use_browser <= 0)
		वापस;

	ui__refresh_dimensions(false);
	pthपढ़ो_mutex_lock(&ui__lock);
	y = SLtt_Screen_Rows / 2 - 2;
	SLsmg_set_color(0);
	SLsmg_fill_region(y, 0, 3, SLtt_Screen_Cols, ' ');
	SLsmg_refresh();
	pthपढ़ो_mutex_unlock(&ui__lock);
पूर्ण

अटल काष्ठा ui_progress_ops tui_progress__ops = अणु
	.init   = __tui_progress__init,
	.update = tui_progress__update,
	.finish = tui_progress__finish,
पूर्ण;

व्योम tui_progress__init(व्योम)
अणु
	ui_progress__ops = &tui_progress__ops;
पूर्ण
