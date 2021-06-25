<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  util.c
 *
 *  ORIGINAL AUTHOR: Savio Lam (lam836@cs.cuhk.hk)
 *  MODIFIED FOR LINUX KERNEL CONFIG BY: William Roadcap (roadcap@cfw.com)
 */

#समावेश <मानकतर्क.स>

#समावेश "dialog.h"

/* Needed in संकेत handler in mconf.c */
पूर्णांक saved_x, saved_y;

काष्ठा dialog_info dlg;

अटल व्योम set_mono_theme(व्योम)
अणु
	dlg.screen.atr = A_NORMAL;
	dlg.shaकरोw.atr = A_NORMAL;
	dlg.dialog.atr = A_NORMAL;
	dlg.title.atr = A_BOLD;
	dlg.border.atr = A_NORMAL;
	dlg.button_active.atr = A_REVERSE;
	dlg.button_inactive.atr = A_DIM;
	dlg.button_key_active.atr = A_REVERSE;
	dlg.button_key_inactive.atr = A_BOLD;
	dlg.button_label_active.atr = A_REVERSE;
	dlg.button_label_inactive.atr = A_NORMAL;
	dlg.inputbox.atr = A_NORMAL;
	dlg.inputbox_border.atr = A_NORMAL;
	dlg.searchbox.atr = A_NORMAL;
	dlg.searchbox_title.atr = A_BOLD;
	dlg.searchbox_border.atr = A_NORMAL;
	dlg.position_indicator.atr = A_BOLD;
	dlg.menubox.atr = A_NORMAL;
	dlg.menubox_border.atr = A_NORMAL;
	dlg.item.atr = A_NORMAL;
	dlg.item_selected.atr = A_REVERSE;
	dlg.tag.atr = A_BOLD;
	dlg.tag_selected.atr = A_REVERSE;
	dlg.tag_key.atr = A_BOLD;
	dlg.tag_key_selected.atr = A_REVERSE;
	dlg.check.atr = A_BOLD;
	dlg.check_selected.atr = A_REVERSE;
	dlg.uarrow.atr = A_BOLD;
	dlg.darrow.atr = A_BOLD;
पूर्ण

#घोषणा DLG_COLOR(dialog, f, b, h) \
करो अणु                               \
	dlg.dialog.fg = (f);       \
	dlg.dialog.bg = (b);       \
	dlg.dialog.hl = (h);       \
पूर्ण जबतक (0)

अटल व्योम set_classic_theme(व्योम)
अणु
	DLG_COLOR(screen,                COLOR_CYAN,   COLOR_BLUE,   true);
	DLG_COLOR(shaकरोw,                COLOR_BLACK,  COLOR_BLACK,  true);
	DLG_COLOR(dialog,                COLOR_BLACK,  COLOR_WHITE,  false);
	DLG_COLOR(title,                 COLOR_YELLOW, COLOR_WHITE,  true);
	DLG_COLOR(border,                COLOR_WHITE,  COLOR_WHITE,  true);
	DLG_COLOR(button_active,         COLOR_WHITE,  COLOR_BLUE,   true);
	DLG_COLOR(button_inactive,       COLOR_BLACK,  COLOR_WHITE,  false);
	DLG_COLOR(button_key_active,     COLOR_WHITE,  COLOR_BLUE,   true);
	DLG_COLOR(button_key_inactive,   COLOR_RED,    COLOR_WHITE,  false);
	DLG_COLOR(button_label_active,   COLOR_YELLOW, COLOR_BLUE,   true);
	DLG_COLOR(button_label_inactive, COLOR_BLACK,  COLOR_WHITE,  true);
	DLG_COLOR(inputbox,              COLOR_BLACK,  COLOR_WHITE,  false);
	DLG_COLOR(inputbox_border,       COLOR_BLACK,  COLOR_WHITE,  false);
	DLG_COLOR(searchbox,             COLOR_BLACK,  COLOR_WHITE,  false);
	DLG_COLOR(searchbox_title,       COLOR_YELLOW, COLOR_WHITE,  true);
	DLG_COLOR(searchbox_border,      COLOR_WHITE,  COLOR_WHITE,  true);
	DLG_COLOR(position_indicator,    COLOR_YELLOW, COLOR_WHITE,  true);
	DLG_COLOR(menubox,               COLOR_BLACK,  COLOR_WHITE,  false);
	DLG_COLOR(menubox_border,        COLOR_WHITE,  COLOR_WHITE,  true);
	DLG_COLOR(item,                  COLOR_BLACK,  COLOR_WHITE,  false);
	DLG_COLOR(item_selected,         COLOR_WHITE,  COLOR_BLUE,   true);
	DLG_COLOR(tag,                   COLOR_YELLOW, COLOR_WHITE,  true);
	DLG_COLOR(tag_selected,          COLOR_YELLOW, COLOR_BLUE,   true);
	DLG_COLOR(tag_key,               COLOR_YELLOW, COLOR_WHITE,  true);
	DLG_COLOR(tag_key_selected,      COLOR_YELLOW, COLOR_BLUE,   true);
	DLG_COLOR(check,                 COLOR_BLACK,  COLOR_WHITE,  false);
	DLG_COLOR(check_selected,        COLOR_WHITE,  COLOR_BLUE,   true);
	DLG_COLOR(uarrow,                COLOR_GREEN,  COLOR_WHITE,  true);
	DLG_COLOR(darrow,                COLOR_GREEN,  COLOR_WHITE,  true);
पूर्ण

अटल व्योम set_blackbg_theme(व्योम)
अणु
	DLG_COLOR(screen, COLOR_RED,   COLOR_BLACK, true);
	DLG_COLOR(shaकरोw, COLOR_BLACK, COLOR_BLACK, false);
	DLG_COLOR(dialog, COLOR_WHITE, COLOR_BLACK, false);
	DLG_COLOR(title,  COLOR_RED,   COLOR_BLACK, false);
	DLG_COLOR(border, COLOR_BLACK, COLOR_BLACK, true);

	DLG_COLOR(button_active,         COLOR_YELLOW, COLOR_RED,   false);
	DLG_COLOR(button_inactive,       COLOR_YELLOW, COLOR_BLACK, false);
	DLG_COLOR(button_key_active,     COLOR_YELLOW, COLOR_RED,   true);
	DLG_COLOR(button_key_inactive,   COLOR_RED,    COLOR_BLACK, false);
	DLG_COLOR(button_label_active,   COLOR_WHITE,  COLOR_RED,   false);
	DLG_COLOR(button_label_inactive, COLOR_BLACK,  COLOR_BLACK, true);

	DLG_COLOR(inputbox,         COLOR_YELLOW, COLOR_BLACK, false);
	DLG_COLOR(inputbox_border,  COLOR_YELLOW, COLOR_BLACK, false);

	DLG_COLOR(searchbox,        COLOR_YELLOW, COLOR_BLACK, false);
	DLG_COLOR(searchbox_title,  COLOR_YELLOW, COLOR_BLACK, true);
	DLG_COLOR(searchbox_border, COLOR_BLACK,  COLOR_BLACK, true);

	DLG_COLOR(position_indicator, COLOR_RED, COLOR_BLACK,  false);

	DLG_COLOR(menubox,          COLOR_YELLOW, COLOR_BLACK, false);
	DLG_COLOR(menubox_border,   COLOR_BLACK,  COLOR_BLACK, true);

	DLG_COLOR(item,             COLOR_WHITE, COLOR_BLACK, false);
	DLG_COLOR(item_selected,    COLOR_WHITE, COLOR_RED,   false);

	DLG_COLOR(tag,              COLOR_RED,    COLOR_BLACK, false);
	DLG_COLOR(tag_selected,     COLOR_YELLOW, COLOR_RED,   true);
	DLG_COLOR(tag_key,          COLOR_RED,    COLOR_BLACK, false);
	DLG_COLOR(tag_key_selected, COLOR_YELLOW, COLOR_RED,   true);

	DLG_COLOR(check,            COLOR_YELLOW, COLOR_BLACK, false);
	DLG_COLOR(check_selected,   COLOR_YELLOW, COLOR_RED,   true);

	DLG_COLOR(uarrow, COLOR_RED, COLOR_BLACK, false);
	DLG_COLOR(darrow, COLOR_RED, COLOR_BLACK, false);
पूर्ण

अटल व्योम set_bluetitle_theme(व्योम)
अणु
	set_classic_theme();
	DLG_COLOR(title,               COLOR_BLUE,   COLOR_WHITE, true);
	DLG_COLOR(button_key_active,   COLOR_YELLOW, COLOR_BLUE,  true);
	DLG_COLOR(button_label_active, COLOR_WHITE,  COLOR_BLUE,  true);
	DLG_COLOR(searchbox_title,     COLOR_BLUE,   COLOR_WHITE, true);
	DLG_COLOR(position_indicator,  COLOR_BLUE,   COLOR_WHITE, true);
	DLG_COLOR(tag,                 COLOR_BLUE,   COLOR_WHITE, true);
	DLG_COLOR(tag_key,             COLOR_BLUE,   COLOR_WHITE, true);

पूर्ण

/*
 * Select color theme
 */
अटल पूर्णांक set_theme(स्थिर अक्षर *theme)
अणु
	पूर्णांक use_color = 1;
	अगर (!theme)
		set_bluetitle_theme();
	अन्यथा अगर (म_भेद(theme, "classic") == 0)
		set_classic_theme();
	अन्यथा अगर (म_भेद(theme, "bluetitle") == 0)
		set_bluetitle_theme();
	अन्यथा अगर (म_भेद(theme, "blackbg") == 0)
		set_blackbg_theme();
	अन्यथा अगर (म_भेद(theme, "mono") == 0)
		use_color = 0;

	वापस use_color;
पूर्ण

अटल व्योम init_one_color(काष्ठा dialog_color *color)
अणु
	अटल पूर्णांक pair = 0;

	pair++;
	init_pair(pair, color->fg, color->bg);
	अगर (color->hl)
		color->atr = A_BOLD | COLOR_PAIR(pair);
	अन्यथा
		color->atr = COLOR_PAIR(pair);
पूर्ण

अटल व्योम init_dialog_colors(व्योम)
अणु
	init_one_color(&dlg.screen);
	init_one_color(&dlg.shaकरोw);
	init_one_color(&dlg.dialog);
	init_one_color(&dlg.title);
	init_one_color(&dlg.border);
	init_one_color(&dlg.button_active);
	init_one_color(&dlg.button_inactive);
	init_one_color(&dlg.button_key_active);
	init_one_color(&dlg.button_key_inactive);
	init_one_color(&dlg.button_label_active);
	init_one_color(&dlg.button_label_inactive);
	init_one_color(&dlg.inputbox);
	init_one_color(&dlg.inputbox_border);
	init_one_color(&dlg.searchbox);
	init_one_color(&dlg.searchbox_title);
	init_one_color(&dlg.searchbox_border);
	init_one_color(&dlg.position_indicator);
	init_one_color(&dlg.menubox);
	init_one_color(&dlg.menubox_border);
	init_one_color(&dlg.item);
	init_one_color(&dlg.item_selected);
	init_one_color(&dlg.tag);
	init_one_color(&dlg.tag_selected);
	init_one_color(&dlg.tag_key);
	init_one_color(&dlg.tag_key_selected);
	init_one_color(&dlg.check);
	init_one_color(&dlg.check_selected);
	init_one_color(&dlg.uarrow);
	init_one_color(&dlg.darrow);
पूर्ण

/*
 * Setup क्रम color display
 */
अटल व्योम color_setup(स्थिर अक्षर *theme)
अणु
	पूर्णांक use_color;

	use_color = set_theme(theme);
	अगर (use_color && has_colors()) अणु
		start_color();
		init_dialog_colors();
	पूर्ण अन्यथा
		set_mono_theme();
पूर्ण

/*
 * Set winकरोw to attribute 'attr'
 */
व्योम attr_clear(WINDOW * win, पूर्णांक height, पूर्णांक width, chtype attr)
अणु
	पूर्णांक i, j;

	wattrset(win, attr);
	क्रम (i = 0; i < height; i++) अणु
		wmove(win, i, 0);
		क्रम (j = 0; j < width; j++)
			waddch(win, ' ');
	पूर्ण
	touchwin(win);
पूर्ण

व्योम dialog_clear(व्योम)
अणु
	पूर्णांक lines, columns;

	lines = geपंचांगaxy(stdscr);
	columns = geपंचांगaxx(stdscr);

	attr_clear(stdscr, lines, columns, dlg.screen.atr);
	/* Display background title अगर it exists ... - SLH */
	अगर (dlg.backtitle != शून्य) अणु
		पूर्णांक i, len = 0, skip = 0;
		काष्ठा subtitle_list *pos;

		wattrset(stdscr, dlg.screen.atr);
		mvwaddstr(stdscr, 0, 1, (अक्षर *)dlg.backtitle);

		क्रम (pos = dlg.subtitles; pos != शून्य; pos = pos->next) अणु
			/* 3 is क्रम the arrow and spaces */
			len += म_माप(pos->text) + 3;
		पूर्ण

		wmove(stdscr, 1, 1);
		अगर (len > columns - 2) अणु
			स्थिर अक्षर *ellipsis = "[...] ";
			waddstr(stdscr, ellipsis);
			skip = len - (columns - 2 - म_माप(ellipsis));
		पूर्ण

		क्रम (pos = dlg.subtitles; pos != शून्य; pos = pos->next) अणु
			अगर (skip == 0)
				waddch(stdscr, ACS_RARROW);
			अन्यथा
				skip--;

			अगर (skip == 0)
				waddch(stdscr, ' ');
			अन्यथा
				skip--;

			अगर (skip < म_माप(pos->text)) अणु
				waddstr(stdscr, pos->text + skip);
				skip = 0;
			पूर्ण अन्यथा
				skip -= म_माप(pos->text);

			अगर (skip == 0)
				waddch(stdscr, ' ');
			अन्यथा
				skip--;
		पूर्ण

		क्रम (i = len + 1; i < columns - 1; i++)
			waddch(stdscr, ACS_HLINE);
	पूर्ण
	wnoutrefresh(stdscr);
पूर्ण

/*
 * Do some initialization क्रम dialog
 */
पूर्णांक init_dialog(स्थिर अक्षर *backtitle)
अणु
	पूर्णांक height, width;

	initscr();		/* Init curses */

	/* Get current cursor position क्रम संकेत handler in mconf.c */
	getyx(stdscr, saved_y, saved_x);

	geपंचांगaxyx(stdscr, height, width);
	अगर (height < WINDOW_HEIGTH_MIN || width < WINDOW_WIDTH_MIN) अणु
		endwin();
		वापस -ERRDISPLAYTOOSMALL;
	पूर्ण

	dlg.backtitle = backtitle;
	color_setup(दो_पर्या("MENUCONFIG_COLOR"));

	keypad(stdscr, TRUE);
	cअवरोध();
	noecho();
	dialog_clear();

	वापस 0;
पूर्ण

व्योम set_dialog_backtitle(स्थिर अक्षर *backtitle)
अणु
	dlg.backtitle = backtitle;
पूर्ण

व्योम set_dialog_subtitles(काष्ठा subtitle_list *subtitles)
अणु
	dlg.subtitles = subtitles;
पूर्ण

/*
 * End using dialog functions.
 */
व्योम end_dialog(पूर्णांक x, पूर्णांक y)
अणु
	/* move cursor back to original position */
	move(y, x);
	refresh();
	endwin();
पूर्ण

/* Prपूर्णांक the title of the dialog. Center the title and truncate
 * tile अगर wider than dialog (- 2 अक्षरs).
 **/
व्योम prपूर्णांक_title(WINDOW *dialog, स्थिर अक्षर *title, पूर्णांक width)
अणु
	अगर (title) अणु
		पूर्णांक tlen = MIN(width - 2, म_माप(title));
		wattrset(dialog, dlg.title.atr);
		mvwaddch(dialog, 0, (width - tlen) / 2 - 1, ' ');
		mvwaddnstr(dialog, 0, (width - tlen)/2, title, tlen);
		waddch(dialog, ' ');
	पूर्ण
पूर्ण

/*
 * Prपूर्णांक a string of text in a winकरोw, स्वतःmatically wrap around to the
 * next line अगर the string is too दीर्घ to fit on one line. Newline
 * अक्षरacters '\n' are properly processed.  We start on a new line
 * अगर there is no room क्रम at least 4 nonblanks following a द्विगुन-space.
 */
व्योम prपूर्णांक_स्वतःwrap(WINDOW * win, स्थिर अक्षर *prompt, पूर्णांक width, पूर्णांक y, पूर्णांक x)
अणु
	पूर्णांक newl, cur_x, cur_y;
	पूर्णांक prompt_len, room, wlen;
	अक्षर tempstr[MAX_LEN + 1], *word, *sp, *sp2, *newline_separator = 0;

	म_नकल(tempstr, prompt);

	prompt_len = म_माप(tempstr);

	अगर (prompt_len <= width - x * 2) अणु	/* If prompt is लघु */
		wmove(win, y, (width - prompt_len) / 2);
		waddstr(win, tempstr);
	पूर्ण अन्यथा अणु
		cur_x = x;
		cur_y = y;
		newl = 1;
		word = tempstr;
		जबतक (word && *word) अणु
			sp = strpbrk(word, "\n ");
			अगर (sp && *sp == '\n')
				newline_separator = sp;

			अगर (sp)
				*sp++ = 0;

			/* Wrap to next line अगर either the word करोes not fit,
			   or it is the first word of a new sentence, and it is
			   लघु, and the next word करोes not fit. */
			room = width - cur_x;
			wlen = म_माप(word);
			अगर (wlen > room ||
			    (newl && wlen < 4 && sp
			     && wlen + 1 + म_माप(sp) > room
			     && (!(sp2 = strpbrk(sp, "\n "))
				 || wlen + 1 + (sp2 - sp) > room))) अणु
				cur_y++;
				cur_x = x;
			पूर्ण
			wmove(win, cur_y, cur_x);
			waddstr(win, word);
			getyx(win, cur_y, cur_x);

			/* Move to the next line अगर the word separator was a newline */
			अगर (newline_separator) अणु
				cur_y++;
				cur_x = x;
				newline_separator = 0;
			पूर्ण अन्यथा
				cur_x++;

			अगर (sp && *sp == ' ') अणु
				cur_x++;	/* द्विगुन space */
				जबतक (*++sp == ' ') ;
				newl = 1;
			पूर्ण अन्यथा
				newl = 0;
			word = sp;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Prपूर्णांक a button
 */
व्योम prपूर्णांक_button(WINDOW * win, स्थिर अक्षर *label, पूर्णांक y, पूर्णांक x, पूर्णांक selected)
अणु
	पूर्णांक i, temp;

	wmove(win, y, x);
	wattrset(win, selected ? dlg.button_active.atr
		 : dlg.button_inactive.atr);
	waddstr(win, "<");
	temp = म_अखोज(label, " ");
	label += temp;
	wattrset(win, selected ? dlg.button_label_active.atr
		 : dlg.button_label_inactive.atr);
	क्रम (i = 0; i < temp; i++)
		waddch(win, ' ');
	wattrset(win, selected ? dlg.button_key_active.atr
		 : dlg.button_key_inactive.atr);
	waddch(win, label[0]);
	wattrset(win, selected ? dlg.button_label_active.atr
		 : dlg.button_label_inactive.atr);
	waddstr(win, (अक्षर *)label + 1);
	wattrset(win, selected ? dlg.button_active.atr
		 : dlg.button_inactive.atr);
	waddstr(win, ">");
	wmove(win, y, x + temp + 1);
पूर्ण

/*
 * Draw a rectangular box with line drawing अक्षरacters
 */
व्योम
draw_box(WINDOW * win, पूर्णांक y, पूर्णांक x, पूर्णांक height, पूर्णांक width,
	 chtype box, chtype border)
अणु
	पूर्णांक i, j;

	wattrset(win, 0);
	क्रम (i = 0; i < height; i++) अणु
		wmove(win, y + i, x);
		क्रम (j = 0; j < width; j++)
			अगर (!i && !j)
				waddch(win, border | ACS_ULCORNER);
			अन्यथा अगर (i == height - 1 && !j)
				waddch(win, border | ACS_LLCORNER);
			अन्यथा अगर (!i && j == width - 1)
				waddch(win, box | ACS_URCORNER);
			अन्यथा अगर (i == height - 1 && j == width - 1)
				waddch(win, box | ACS_LRCORNER);
			अन्यथा अगर (!i)
				waddch(win, border | ACS_HLINE);
			अन्यथा अगर (i == height - 1)
				waddch(win, box | ACS_HLINE);
			अन्यथा अगर (!j)
				waddch(win, border | ACS_VLINE);
			अन्यथा अगर (j == width - 1)
				waddch(win, box | ACS_VLINE);
			अन्यथा
				waddch(win, box | ' ');
	पूर्ण
पूर्ण

/*
 * Draw shaकरोws aदीर्घ the right and bottom edge to give a more 3D look
 * to the boxes
 */
व्योम draw_shaकरोw(WINDOW * win, पूर्णांक y, पूर्णांक x, पूर्णांक height, पूर्णांक width)
अणु
	पूर्णांक i;

	अगर (has_colors()) अणु	/* Whether terminal supports color? */
		wattrset(win, dlg.shaकरोw.atr);
		wmove(win, y + height, x + 2);
		क्रम (i = 0; i < width; i++)
			waddch(win, winch(win) & A_CHARTEXT);
		क्रम (i = y + 1; i < y + height + 1; i++) अणु
			wmove(win, i, x + width);
			waddch(win, winch(win) & A_CHARTEXT);
			waddch(win, winch(win) & A_CHARTEXT);
		पूर्ण
		wnoutrefresh(win);
	पूर्ण
पूर्ण

/*
 *  Return the position of the first alphabetic अक्षरacter in a string.
 */
पूर्णांक first_alpha(स्थिर अक्षर *string, स्थिर अक्षर *exempt)
अणु
	पूर्णांक i, in_paren = 0, c;

	क्रम (i = 0; i < म_माप(string); i++) अणु
		c = छोटे(string[i]);

		अगर (म_अक्षर("<[(", c))
			++in_paren;
		अगर (म_अक्षर(">])", c) && in_paren > 0)
			--in_paren;

		अगर ((!in_paren) && है_अक्षर(c) && म_अक्षर(exempt, c) == 0)
			वापस i;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * ncurses uses ESC to detect escaped अक्षर sequences. This resutl in
 * a small समयout beक्रमe ESC is actually delivered to the application.
 * lxdialog suggest <ESC> <ESC> which is correctly translated to two
 * बार esc. But then we need to ignore the second esc to aव्योम stepping
 * out one menu too much. Filter away all escaped key sequences since
 * keypad(FALSE) turn off ncurses support क्रम escape sequences - and that's
 * needed to make noसमयout() करो as expected.
 */
पूर्णांक on_key_esc(WINDOW *win)
अणु
	पूर्णांक key;
	पूर्णांक key2;
	पूर्णांक key3;

	nodelay(win, TRUE);
	keypad(win, FALSE);
	key = wअ_लोh(win);
	key2 = wअ_लोh(win);
	करो अणु
		key3 = wअ_लोh(win);
	पूर्ण जबतक (key3 != ERR);
	nodelay(win, FALSE);
	keypad(win, TRUE);
	अगर (key == KEY_ESC && key2 == ERR)
		वापस KEY_ESC;
	अन्यथा अगर (key != ERR && key != KEY_ESC && key2 == ERR)
		अक्षर_वापसh(key);

	वापस -1;
पूर्ण

/* redraw screen in new size */
पूर्णांक on_key_resize(व्योम)
अणु
	dialog_clear();
	वापस KEY_RESIZE;
पूर्ण

काष्ठा dialog_list *item_cur;
काष्ठा dialog_list item_nil;
काष्ठा dialog_list *item_head;

व्योम item_reset(व्योम)
अणु
	काष्ठा dialog_list *p, *next;

	क्रम (p = item_head; p; p = next) अणु
		next = p->next;
		मुक्त(p);
	पूर्ण
	item_head = शून्य;
	item_cur = &item_nil;
पूर्ण

व्योम item_make(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	काष्ठा dialog_list *p = दो_स्मृति(माप(*p));

	अगर (item_head)
		item_cur->next = p;
	अन्यथा
		item_head = p;
	item_cur = p;
	स_रखो(p, 0, माप(*p));

	बहु_शुरू(ap, fmt);
	vsnम_लिखो(item_cur->node.str, माप(item_cur->node.str), fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण

व्योम item_add_str(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	माप_प्रकार avail;

	avail = माप(item_cur->node.str) - म_माप(item_cur->node.str);

	बहु_शुरू(ap, fmt);
	vsnम_लिखो(item_cur->node.str + म_माप(item_cur->node.str),
		  avail, fmt, ap);
	item_cur->node.str[माप(item_cur->node.str) - 1] = '\0';
	बहु_पूर्ण(ap);
पूर्ण

व्योम item_set_tag(अक्षर tag)
अणु
	item_cur->node.tag = tag;
पूर्ण
व्योम item_set_data(व्योम *ptr)
अणु
	item_cur->node.data = ptr;
पूर्ण

व्योम item_set_selected(पूर्णांक val)
अणु
	item_cur->node.selected = val;
पूर्ण

पूर्णांक item_activate_selected(व्योम)
अणु
	item_क्रमeach()
		अगर (item_is_selected())
			वापस 1;
	वापस 0;
पूर्ण

व्योम *item_data(व्योम)
अणु
	वापस item_cur->node.data;
पूर्ण

अक्षर item_tag(व्योम)
अणु
	वापस item_cur->node.tag;
पूर्ण

पूर्णांक item_count(व्योम)
अणु
	पूर्णांक n = 0;
	काष्ठा dialog_list *p;

	क्रम (p = item_head; p; p = p->next)
		n++;
	वापस n;
पूर्ण

व्योम item_set(पूर्णांक n)
अणु
	पूर्णांक i = 0;
	item_क्रमeach()
		अगर (i++ == n)
			वापस;
पूर्ण

पूर्णांक item_n(व्योम)
अणु
	पूर्णांक n = 0;
	काष्ठा dialog_list *p;

	क्रम (p = item_head; p; p = p->next) अणु
		अगर (p == item_cur)
			वापस n;
		n++;
	पूर्ण
	वापस 0;
पूर्ण

स्थिर अक्षर *item_str(व्योम)
अणु
	वापस item_cur->node.str;
पूर्ण

पूर्णांक item_is_selected(व्योम)
अणु
	वापस (item_cur->node.selected != 0);
पूर्ण

पूर्णांक item_is_tag(अक्षर tag)
अणु
	वापस (item_cur->node.tag == tag);
पूर्ण
