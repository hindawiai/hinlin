<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  textbox.c -- implements the text box
 *
 *  ORIGINAL AUTHOR: Savio Lam (lam836@cs.cuhk.hk)
 *  MODIFIED FOR LINUX KERNEL CONFIG BY: William Roadcap (roadcap@cfw.com)
 */

#समावेश "dialog.h"

अटल व्योम back_lines(पूर्णांक n);
अटल व्योम prपूर्णांक_page(WINDOW *win, पूर्णांक height, पूर्णांक width, update_text_fn
		       update_text, व्योम *data);
अटल व्योम prपूर्णांक_line(WINDOW *win, पूर्णांक row, पूर्णांक width);
अटल अक्षर *get_line(व्योम);
अटल व्योम prपूर्णांक_position(WINDOW * win);

अटल पूर्णांक hscroll;
अटल पूर्णांक begin_reached, end_reached, page_length;
अटल अक्षर *buf;
अटल अक्षर *page;

/*
 * refresh winकरोw content
 */
अटल व्योम refresh_text_box(WINDOW *dialog, WINDOW *box, पूर्णांक boxh, पूर्णांक boxw,
			     पूर्णांक cur_y, पूर्णांक cur_x, update_text_fn update_text,
			     व्योम *data)
अणु
	prपूर्णांक_page(box, boxh, boxw, update_text, data);
	prपूर्णांक_position(dialog);
	wmove(dialog, cur_y, cur_x);	/* Restore cursor position */
	wrefresh(dialog);
पूर्ण


/*
 * Display text from a file in a dialog box.
 *
 * keys is a null-terminated array
 * update_text() may not add or हटाओ any '\n' or '\0' in tbuf
 */
पूर्णांक dialog_textbox(स्थिर अक्षर *title, अक्षर *tbuf, पूर्णांक initial_height,
		   पूर्णांक initial_width, पूर्णांक *keys, पूर्णांक *_vscroll, पूर्णांक *_hscroll,
		   update_text_fn update_text, व्योम *data)
अणु
	पूर्णांक i, x, y, cur_x, cur_y, key = 0;
	पूर्णांक height, width, boxh, boxw;
	WINDOW *dialog, *box;
	bool करोne = false;

	begin_reached = 1;
	end_reached = 0;
	page_length = 0;
	hscroll = 0;
	buf = tbuf;
	page = buf;	/* page is poपूर्णांकer to start of page to be displayed */

	अगर (_vscroll && *_vscroll) अणु
		begin_reached = 0;

		क्रम (i = 0; i < *_vscroll; i++)
			get_line();
	पूर्ण
	अगर (_hscroll)
		hscroll = *_hscroll;

करो_resize:
	geपंचांगaxyx(stdscr, height, width);
	अगर (height < TEXTBOX_HEIGTH_MIN || width < TEXTBOX_WIDTH_MIN)
		वापस -ERRDISPLAYTOOSMALL;
	अगर (initial_height != 0)
		height = initial_height;
	अन्यथा
		अगर (height > 4)
			height -= 4;
		अन्यथा
			height = 0;
	अगर (initial_width != 0)
		width = initial_width;
	अन्यथा
		अगर (width > 5)
			width -= 5;
		अन्यथा
			width = 0;

	/* center dialog box on screen */
	x = (geपंचांगaxx(stdscr) - width) / 2;
	y = (geपंचांगaxy(stdscr) - height) / 2;

	draw_shaकरोw(stdscr, y, x, height, width);

	dialog = newwin(height, width, y, x);
	keypad(dialog, TRUE);

	/* Create winकरोw क्रम box region, used क्रम scrolling text */
	boxh = height - 4;
	boxw = width - 2;
	box = subwin(dialog, boxh, boxw, y + 1, x + 1);
	wattrset(box, dlg.dialog.atr);
	wbkgdset(box, dlg.dialog.atr & A_COLOR);

	keypad(box, TRUE);

	/* रेजिस्टर the new winकरोw, aदीर्घ with its borders */
	draw_box(dialog, 0, 0, height, width,
		 dlg.dialog.atr, dlg.border.atr);

	wattrset(dialog, dlg.border.atr);
	mvwaddch(dialog, height - 3, 0, ACS_LTEE);
	क्रम (i = 0; i < width - 2; i++)
		waddch(dialog, ACS_HLINE);
	wattrset(dialog, dlg.dialog.atr);
	wbkgdset(dialog, dlg.dialog.atr & A_COLOR);
	waddch(dialog, ACS_RTEE);

	prपूर्णांक_title(dialog, title, width);

	prपूर्णांक_button(dialog, " Exit ", height - 2, width / 2 - 4, TRUE);
	wnoutrefresh(dialog);
	getyx(dialog, cur_y, cur_x);	/* Save cursor position */

	/* Prपूर्णांक first page of text */
	attr_clear(box, boxh, boxw, dlg.dialog.atr);
	refresh_text_box(dialog, box, boxh, boxw, cur_y, cur_x, update_text,
			 data);

	जबतक (!करोne) अणु
		key = wअ_लोh(dialog);
		चयन (key) अणु
		हाल 'E':	/* Exit */
		हाल 'e':
		हाल 'X':
		हाल 'x':
		हाल 'q':
		हाल '\n':
			करोne = true;
			अवरोध;
		हाल 'g':	/* First page */
		हाल KEY_HOME:
			अगर (!begin_reached) अणु
				begin_reached = 1;
				page = buf;
				refresh_text_box(dialog, box, boxh, boxw,
						 cur_y, cur_x, update_text,
						 data);
			पूर्ण
			अवरोध;
		हाल 'G':	/* Last page */
		हाल KEY_END:

			end_reached = 1;
			/* poपूर्णांक to last अक्षर in buf */
			page = buf + म_माप(buf);
			back_lines(boxh);
			refresh_text_box(dialog, box, boxh, boxw, cur_y,
					 cur_x, update_text, data);
			अवरोध;
		हाल 'K':	/* Previous line */
		हाल 'k':
		हाल KEY_UP:
			अगर (begin_reached)
				अवरोध;

			back_lines(page_length + 1);
			refresh_text_box(dialog, box, boxh, boxw, cur_y,
					 cur_x, update_text, data);
			अवरोध;
		हाल 'B':	/* Previous page */
		हाल 'b':
		हाल 'u':
		हाल KEY_PPAGE:
			अगर (begin_reached)
				अवरोध;
			back_lines(page_length + boxh);
			refresh_text_box(dialog, box, boxh, boxw, cur_y,
					 cur_x, update_text, data);
			अवरोध;
		हाल 'J':	/* Next line */
		हाल 'j':
		हाल KEY_DOWN:
			अगर (end_reached)
				अवरोध;

			back_lines(page_length - 1);
			refresh_text_box(dialog, box, boxh, boxw, cur_y,
					 cur_x, update_text, data);
			अवरोध;
		हाल KEY_NPAGE:	/* Next page */
		हाल ' ':
		हाल 'd':
			अगर (end_reached)
				अवरोध;

			begin_reached = 0;
			refresh_text_box(dialog, box, boxh, boxw, cur_y,
					 cur_x, update_text, data);
			अवरोध;
		हाल '0':	/* Beginning of line */
		हाल 'H':	/* Scroll left */
		हाल 'h':
		हाल KEY_LEFT:
			अगर (hscroll <= 0)
				अवरोध;

			अगर (key == '0')
				hscroll = 0;
			अन्यथा
				hscroll--;
			/* Reprपूर्णांक current page to scroll horizontally */
			back_lines(page_length);
			refresh_text_box(dialog, box, boxh, boxw, cur_y,
					 cur_x, update_text, data);
			अवरोध;
		हाल 'L':	/* Scroll right */
		हाल 'l':
		हाल KEY_RIGHT:
			अगर (hscroll >= MAX_LEN)
				अवरोध;
			hscroll++;
			/* Reprपूर्णांक current page to scroll horizontally */
			back_lines(page_length);
			refresh_text_box(dialog, box, boxh, boxw, cur_y,
					 cur_x, update_text, data);
			अवरोध;
		हाल KEY_ESC:
			अगर (on_key_esc(dialog) == KEY_ESC)
				करोne = true;
			अवरोध;
		हाल KEY_RESIZE:
			back_lines(height);
			delwin(box);
			delwin(dialog);
			on_key_resize();
			जाओ करो_resize;
		शेष:
			क्रम (i = 0; keys[i]; i++) अणु
				अगर (key == keys[i]) अणु
					करोne = true;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	delwin(box);
	delwin(dialog);
	अगर (_vscroll) अणु
		स्थिर अक्षर *s;

		s = buf;
		*_vscroll = 0;
		back_lines(page_length);
		जबतक (s < page && (s = म_अक्षर(s, '\n'))) अणु
			(*_vscroll)++;
			s++;
		पूर्ण
	पूर्ण
	अगर (_hscroll)
		*_hscroll = hscroll;
	वापस key;
पूर्ण

/*
 * Go back 'n' lines in text. Called by dialog_textbox().
 * 'page' will be updated to point to the desired line in 'buf'.
 */
अटल व्योम back_lines(पूर्णांक n)
अणु
	पूर्णांक i;

	begin_reached = 0;
	/* Go back 'n' lines */
	क्रम (i = 0; i < n; i++) अणु
		अगर (*page == '\0') अणु
			अगर (end_reached) अणु
				end_reached = 0;
				जारी;
			पूर्ण
		पूर्ण
		अगर (page == buf) अणु
			begin_reached = 1;
			वापस;
		पूर्ण
		page--;
		करो अणु
			अगर (page == buf) अणु
				begin_reached = 1;
				वापस;
			पूर्ण
			page--;
		पूर्ण जबतक (*page != '\n');
		page++;
	पूर्ण
पूर्ण

/*
 * Prपूर्णांक a new page of text.
 */
अटल व्योम prपूर्णांक_page(WINDOW *win, पूर्णांक height, पूर्णांक width, update_text_fn
		       update_text, व्योम *data)
अणु
	पूर्णांक i, passed_end = 0;

	अगर (update_text) अणु
		अक्षर *end;

		क्रम (i = 0; i < height; i++)
			get_line();
		end = page;
		back_lines(height);
		update_text(buf, page - buf, end - buf, data);
	पूर्ण

	page_length = 0;
	क्रम (i = 0; i < height; i++) अणु
		prपूर्णांक_line(win, i, width);
		अगर (!passed_end)
			page_length++;
		अगर (end_reached && !passed_end)
			passed_end = 1;
	पूर्ण
	wnoutrefresh(win);
पूर्ण

/*
 * Prपूर्णांक a new line of text.
 */
अटल व्योम prपूर्णांक_line(WINDOW * win, पूर्णांक row, पूर्णांक width)
अणु
	अक्षर *line;

	line = get_line();
	line += MIN(म_माप(line), hscroll);	/* Scroll horizontally */
	wmove(win, row, 0);	/* move cursor to correct line */
	waddch(win, ' ');
	waddnstr(win, line, MIN(म_माप(line), width - 2));

	/* Clear 'residue' of previous line */
#अगर OLD_NCURSES
	अणु
		पूर्णांक x = अ_लोurx(win);
		पूर्णांक i;
		क्रम (i = 0; i < width - x; i++)
			waddch(win, ' ');
	पूर्ण
#अन्यथा
	wclrtoeol(win);
#पूर्ण_अगर
पूर्ण

/*
 * Return current line of text. Called by dialog_textbox() and prपूर्णांक_line().
 * 'page' should poपूर्णांक to start of current line beक्रमe calling, and will be
 * updated to poपूर्णांक to start of next line.
 */
अटल अक्षर *get_line(व्योम)
अणु
	पूर्णांक i = 0;
	अटल अक्षर line[MAX_LEN + 1];

	end_reached = 0;
	जबतक (*page != '\n') अणु
		अगर (*page == '\0') अणु
			end_reached = 1;
			अवरोध;
		पूर्ण अन्यथा अगर (i < MAX_LEN)
			line[i++] = *(page++);
		अन्यथा अणु
			/* Truncate lines दीर्घer than MAX_LEN अक्षरacters */
			अगर (i == MAX_LEN)
				line[i++] = '\0';
			page++;
		पूर्ण
	पूर्ण
	अगर (i <= MAX_LEN)
		line[i] = '\0';
	अगर (!end_reached)
		page++;		/* move past '\n' */

	वापस line;
पूर्ण

/*
 * Prपूर्णांक current position
 */
अटल व्योम prपूर्णांक_position(WINDOW * win)
अणु
	पूर्णांक percent;

	wattrset(win, dlg.position_indicator.atr);
	wbkgdset(win, dlg.position_indicator.atr & A_COLOR);
	percent = (page - buf) * 100 / म_माप(buf);
	wmove(win, geपंचांगaxy(win) - 3, geपंचांगaxx(win) - 9);
	wprपूर्णांकw(win, "(%3d%%)", percent);
पूर्ण
