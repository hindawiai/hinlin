<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2008 Nir Tzaअक्षर <nir.tzaअक्षर@gmail.com>
 *
 * Derived from menuconfig.
 */
#समावेश "nconf.h"
#समावेश "lkc.h"

पूर्णांक attr_normal;
पूर्णांक attr_मुख्य_heading;
पूर्णांक attr_मुख्य_menu_box;
पूर्णांक attr_मुख्य_menu_क्रमe;
पूर्णांक attr_मुख्य_menu_back;
पूर्णांक attr_मुख्य_menu_grey;
पूर्णांक attr_मुख्य_menu_heading;
पूर्णांक attr_scrollwin_text;
पूर्णांक attr_scrollwin_heading;
पूर्णांक attr_scrollwin_box;
पूर्णांक attr_dialog_text;
पूर्णांक attr_dialog_menu_क्रमe;
पूर्णांक attr_dialog_menu_back;
पूर्णांक attr_dialog_box;
पूर्णांक attr_input_box;
पूर्णांक attr_input_heading;
पूर्णांक attr_input_text;
पूर्णांक attr_input_field;
पूर्णांक attr_function_text;
पूर्णांक attr_function_highlight;

#घोषणा COLOR_ATTR(_at, _fg, _bg, _hl) \
	अणु .attr = &(_at), .has_color = true, .color_fg = _fg, .color_bg = _bg, .highlight = _hl पूर्ण
#घोषणा NO_COLOR_ATTR(_at, _hl) \
	अणु .attr = &(_at), .has_color = false, .highlight = _hl पूर्ण
#घोषणा COLOR_DEFAULT		-1

काष्ठा nconf_attr_param अणु
	पूर्णांक *attr;
	bool has_color;
	पूर्णांक color_fg;
	पूर्णांक color_bg;
	पूर्णांक highlight;
पूर्ण;

अटल स्थिर काष्ठा nconf_attr_param color_theme_params[] = अणु
	COLOR_ATTR(attr_normal,			COLOR_DEFAULT,	COLOR_DEFAULT,	A_NORMAL),
	COLOR_ATTR(attr_मुख्य_heading,		COLOR_MAGENTA,	COLOR_DEFAULT,	A_BOLD | A_UNDERLINE),
	COLOR_ATTR(attr_मुख्य_menu_box,		COLOR_YELLOW,	COLOR_DEFAULT,	A_NORMAL),
	COLOR_ATTR(attr_मुख्य_menu_क्रमe,		COLOR_DEFAULT,	COLOR_DEFAULT,	A_REVERSE),
	COLOR_ATTR(attr_मुख्य_menu_back,		COLOR_DEFAULT,	COLOR_DEFAULT,	A_NORMAL),
	COLOR_ATTR(attr_मुख्य_menu_grey,		COLOR_DEFAULT,	COLOR_DEFAULT,	A_NORMAL),
	COLOR_ATTR(attr_मुख्य_menu_heading,	COLOR_GREEN,	COLOR_DEFAULT,	A_BOLD),
	COLOR_ATTR(attr_scrollwin_text,		COLOR_DEFAULT,	COLOR_DEFAULT,	A_NORMAL),
	COLOR_ATTR(attr_scrollwin_heading,	COLOR_GREEN,	COLOR_DEFAULT,	A_BOLD),
	COLOR_ATTR(attr_scrollwin_box,		COLOR_YELLOW,	COLOR_DEFAULT,	A_BOLD),
	COLOR_ATTR(attr_dialog_text,		COLOR_DEFAULT,	COLOR_DEFAULT,	A_BOLD),
	COLOR_ATTR(attr_dialog_menu_क्रमe,	COLOR_RED,	COLOR_DEFAULT,	A_STANDOUT),
	COLOR_ATTR(attr_dialog_menu_back,	COLOR_YELLOW,	COLOR_DEFAULT,	A_NORMAL),
	COLOR_ATTR(attr_dialog_box,		COLOR_YELLOW,	COLOR_DEFAULT,	A_BOLD),
	COLOR_ATTR(attr_input_box,		COLOR_YELLOW,	COLOR_DEFAULT,	A_NORMAL),
	COLOR_ATTR(attr_input_heading,		COLOR_GREEN,	COLOR_DEFAULT,	A_BOLD),
	COLOR_ATTR(attr_input_text,		COLOR_DEFAULT,	COLOR_DEFAULT,	A_NORMAL),
	COLOR_ATTR(attr_input_field,		COLOR_DEFAULT,	COLOR_DEFAULT,	A_UNDERLINE),
	COLOR_ATTR(attr_function_text,		COLOR_YELLOW,	COLOR_DEFAULT,	A_REVERSE),
	COLOR_ATTR(attr_function_highlight,	COLOR_DEFAULT,	COLOR_DEFAULT,	A_BOLD),
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा nconf_attr_param no_color_theme_params[] = अणु
	NO_COLOR_ATTR(attr_normal,		A_NORMAL),
	NO_COLOR_ATTR(attr_मुख्य_heading,	A_BOLD | A_UNDERLINE),
	NO_COLOR_ATTR(attr_मुख्य_menu_box,	A_NORMAL),
	NO_COLOR_ATTR(attr_मुख्य_menu_क्रमe,	A_STANDOUT),
	NO_COLOR_ATTR(attr_मुख्य_menu_back,	A_NORMAL),
	NO_COLOR_ATTR(attr_मुख्य_menu_grey,	A_NORMAL),
	NO_COLOR_ATTR(attr_मुख्य_menu_heading,	A_BOLD),
	NO_COLOR_ATTR(attr_scrollwin_text,	A_NORMAL),
	NO_COLOR_ATTR(attr_scrollwin_heading,	A_BOLD),
	NO_COLOR_ATTR(attr_scrollwin_box,	A_BOLD),
	NO_COLOR_ATTR(attr_dialog_text,		A_NORMAL),
	NO_COLOR_ATTR(attr_dialog_menu_क्रमe,	A_STANDOUT),
	NO_COLOR_ATTR(attr_dialog_menu_back,	A_NORMAL),
	NO_COLOR_ATTR(attr_dialog_box,		A_BOLD),
	NO_COLOR_ATTR(attr_input_box,		A_BOLD),
	NO_COLOR_ATTR(attr_input_heading,	A_BOLD),
	NO_COLOR_ATTR(attr_input_text,		A_NORMAL),
	NO_COLOR_ATTR(attr_input_field,		A_UNDERLINE),
	NO_COLOR_ATTR(attr_function_text,	A_REVERSE),
	NO_COLOR_ATTR(attr_function_highlight,	A_BOLD),
	अणु /* sentinel */ पूर्ण
पूर्ण;

व्योम set_colors(व्योम)
अणु
	स्थिर काष्ठा nconf_attr_param *p;
	पूर्णांक pair = 0;

	अगर (has_colors()) अणु
		start_color();
		use_शेष_colors();
		p = color_theme_params;
	पूर्ण अन्यथा अणु
		p = no_color_theme_params;
	पूर्ण

	क्रम (; p->attr; p++) अणु
		पूर्णांक attr = p->highlight;

		अगर (p->has_color) अणु
			pair++;
			init_pair(pair, p->color_fg, p->color_bg);
			attr |= COLOR_PAIR(pair);
		पूर्ण

		*p->attr = attr;
	पूर्ण
पूर्ण

/* this changes the winकरोws attributes !!! */
व्योम prपूर्णांक_in_middle(WINDOW *win, पूर्णांक y, पूर्णांक width, स्थिर अक्षर *str, पूर्णांक attrs)
अणु
	wattrset(win, attrs);
	mvwprपूर्णांकw(win, y, (width - म_माप(str)) / 2, "%s", str);
पूर्ण

पूर्णांक get_line_no(स्थिर अक्षर *text)
अणु
	पूर्णांक i;
	पूर्णांक total = 1;

	अगर (!text)
		वापस 0;

	क्रम (i = 0; text[i] != '\0'; i++)
		अगर (text[i] == '\n')
			total++;
	वापस total;
पूर्ण

स्थिर अक्षर *get_line(स्थिर अक्षर *text, पूर्णांक line_no)
अणु
	पूर्णांक i;
	पूर्णांक lines = 0;

	अगर (!text)
		वापस शून्य;

	क्रम (i = 0; text[i] != '\0' && lines < line_no; i++)
		अगर (text[i] == '\n')
			lines++;
	वापस text+i;
पूर्ण

पूर्णांक get_line_length(स्थिर अक्षर *line)
अणु
	पूर्णांक res = 0;
	जबतक (*line != '\0' && *line != '\n') अणु
		line++;
		res++;
	पूर्ण
	वापस res;
पूर्ण

/* prपूर्णांक all lines to the winकरोw. */
व्योम fill_winकरोw(WINDOW *win, स्थिर अक्षर *text)
अणु
	पूर्णांक x, y;
	पूर्णांक total_lines = get_line_no(text);
	पूर्णांक i;

	geपंचांगaxyx(win, y, x);
	/* करो not go over end of line */
	total_lines = min(total_lines, y);
	क्रम (i = 0; i < total_lines; i++) अणु
		अक्षर पंचांगp[x+10];
		स्थिर अक्षर *line = get_line(text, i);
		पूर्णांक len = get_line_length(line);
		म_नकलन(पंचांगp, line, min(len, x));
		पंचांगp[len] = '\0';
		mvwprपूर्णांकw(win, i, 0, "%s", पंचांगp);
	पूर्ण
पूर्ण

/* get the message, and buttons.
 * each button must be a अक्षर*
 * वापस the selected button
 *
 * this dialog is used क्रम 2 dअगरferent things:
 * 1) show a text box, no buttons.
 * 2) show a dialog, with horizontal buttons
 */
पूर्णांक btn_dialog(WINDOW *मुख्य_winकरोw, स्थिर अक्षर *msg, पूर्णांक btn_num, ...)
अणु
	बहु_सूची ap;
	अक्षर *btn;
	पूर्णांक btns_width = 0;
	पूर्णांक msg_lines = 0;
	पूर्णांक msg_width = 0;
	पूर्णांक total_width;
	पूर्णांक win_rows = 0;
	WINDOW *win;
	WINDOW *msg_win;
	WINDOW *menu_win;
	MENU *menu;
	ITEM *btns[btn_num+1];
	पूर्णांक i, x, y;
	पूर्णांक res = -1;


	बहु_शुरू(ap, btn_num);
	क्रम (i = 0; i < btn_num; i++) अणु
		btn = बहु_तर्क(ap, अक्षर *);
		btns[i] = new_item(btn, "");
		btns_width += म_माप(btn)+1;
	पूर्ण
	बहु_पूर्ण(ap);
	btns[btn_num] = शून्य;

	/* find the widest line of msg: */
	msg_lines = get_line_no(msg);
	क्रम (i = 0; i < msg_lines; i++) अणु
		स्थिर अक्षर *line = get_line(msg, i);
		पूर्णांक len = get_line_length(line);
		अगर (msg_width < len)
			msg_width = len;
	पूर्ण

	total_width = max(msg_width, btns_width);
	/* place dialog in middle of screen */
	y = (geपंचांगaxy(stdscr)-(msg_lines+4))/2;
	x = (geपंचांगaxx(stdscr)-(total_width+4))/2;


	/* create the winकरोws */
	अगर (btn_num > 0)
		win_rows = msg_lines+4;
	अन्यथा
		win_rows = msg_lines+2;

	win = newwin(win_rows, total_width+4, y, x);
	keypad(win, TRUE);
	menu_win = derwin(win, 1, btns_width, win_rows-2,
			1+(total_width+2-btns_width)/2);
	menu = new_menu(btns);
	msg_win = derwin(win, win_rows-2, msg_width, 1,
			1+(total_width+2-msg_width)/2);

	set_menu_क्रमe(menu, attr_dialog_menu_क्रमe);
	set_menu_back(menu, attr_dialog_menu_back);

	wattrset(win, attr_dialog_box);
	box(win, 0, 0);

	/* prपूर्णांक message */
	wattrset(msg_win, attr_dialog_text);
	fill_winकरोw(msg_win, msg);

	set_menu_win(menu, win);
	set_menu_sub(menu, menu_win);
	set_menu_क्रमmat(menu, 1, btn_num);
	menu_opts_off(menu, O_SHOWDESC);
	menu_opts_off(menu, O_SHOWMATCH);
	menu_opts_on(menu, O_ONEVALUE);
	menu_opts_on(menu, O_NONCYCLIC);
	set_menu_mark(menu, "");
	post_menu(menu);


	touchwin(win);
	refresh_all_winकरोws(मुख्य_winकरोw);
	जबतक ((res = wअ_लोh(win))) अणु
		चयन (res) अणु
		हाल KEY_LEFT:
			menu_driver(menu, REQ_LEFT_ITEM);
			अवरोध;
		हाल KEY_RIGHT:
			menu_driver(menu, REQ_RIGHT_ITEM);
			अवरोध;
		हाल 10: /* ENTER */
		हाल 27: /* ESCAPE */
		हाल ' ':
		हाल KEY_F(F_BACK):
		हाल KEY_F(F_EXIT):
			अवरोध;
		पूर्ण
		touchwin(win);
		refresh_all_winकरोws(मुख्य_winकरोw);

		अगर (res == 10 || res == ' ') अणु
			res = item_index(current_item(menu));
			अवरोध;
		पूर्ण अन्यथा अगर (res == 27 || res == KEY_F(F_BACK) ||
				res == KEY_F(F_EXIT)) अणु
			res = KEY_EXIT;
			अवरोध;
		पूर्ण
	पूर्ण

	unpost_menu(menu);
	मुक्त_menu(menu);
	क्रम (i = 0; i < btn_num; i++)
		मुक्त_item(btns[i]);

	delwin(win);
	वापस res;
पूर्ण

पूर्णांक dialog_inputbox(WINDOW *मुख्य_winकरोw,
		स्थिर अक्षर *title, स्थिर अक्षर *prompt,
		स्थिर अक्षर *init, अक्षर **resultp, पूर्णांक *result_len)
अणु
	पूर्णांक prompt_lines = 0;
	पूर्णांक prompt_width = 0;
	WINDOW *win;
	WINDOW *prompt_win;
	WINDOW *क्रमm_win;
	PANEL *panel;
	पूर्णांक i, x, y, lines, columns, win_lines, win_cols;
	पूर्णांक res = -1;
	पूर्णांक cursor_position = म_माप(init);
	पूर्णांक cursor_क्रमm_win;
	अक्षर *result = *resultp;

	geपंचांगaxyx(stdscr, lines, columns);

	अगर (म_माप(init)+1 > *result_len) अणु
		*result_len = म_माप(init)+1;
		*resultp = result = xपुनः_स्मृति(result, *result_len);
	पूर्ण

	/* find the widest line of msg: */
	prompt_lines = get_line_no(prompt);
	क्रम (i = 0; i < prompt_lines; i++) अणु
		स्थिर अक्षर *line = get_line(prompt, i);
		पूर्णांक len = get_line_length(line);
		prompt_width = max(prompt_width, len);
	पूर्ण

	अगर (title)
		prompt_width = max(prompt_width, म_माप(title));

	win_lines = min(prompt_lines+6, lines-2);
	win_cols = min(prompt_width+7, columns-2);
	prompt_lines = max(win_lines-6, 0);
	prompt_width = max(win_cols-7, 0);

	/* place dialog in middle of screen */
	y = (lines-win_lines)/2;
	x = (columns-win_cols)/2;

	म_नकलन(result, init, *result_len);

	/* create the winकरोws */
	win = newwin(win_lines, win_cols, y, x);
	prompt_win = derwin(win, prompt_lines+1, prompt_width, 2, 2);
	क्रमm_win = derwin(win, 1, prompt_width, prompt_lines+3, 2);
	keypad(क्रमm_win, TRUE);

	wattrset(क्रमm_win, attr_input_field);

	wattrset(win, attr_input_box);
	box(win, 0, 0);
	wattrset(win, attr_input_heading);
	अगर (title)
		mvwprपूर्णांकw(win, 0, 3, "%s", title);

	/* prपूर्णांक message */
	wattrset(prompt_win, attr_input_text);
	fill_winकरोw(prompt_win, prompt);

	mvwprपूर्णांकw(क्रमm_win, 0, 0, "%*s", prompt_width, " ");
	cursor_क्रमm_win = min(cursor_position, prompt_width-1);
	mvwprपूर्णांकw(क्रमm_win, 0, 0, "%s",
		  result + cursor_position-cursor_क्रमm_win);

	/* create panels */
	panel = new_panel(win);

	/* show the cursor */
	curs_set(1);

	touchwin(win);
	refresh_all_winकरोws(मुख्य_winकरोw);
	जबतक ((res = wअ_लोh(क्रमm_win))) अणु
		पूर्णांक len = म_माप(result);
		चयन (res) अणु
		हाल 10: /* ENTER */
		हाल 27: /* ESCAPE */
		हाल KEY_F(F_HELP):
		हाल KEY_F(F_EXIT):
		हाल KEY_F(F_BACK):
			अवरोध;
		हाल 8:   /* ^H */
		हाल 127: /* ^? */
		हाल KEY_BACKSPACE:
			अगर (cursor_position > 0) अणु
				स_हटाओ(&result[cursor_position-1],
						&result[cursor_position],
						len-cursor_position+1);
				cursor_position--;
				cursor_क्रमm_win--;
				len--;
			पूर्ण
			अवरोध;
		हाल KEY_DC:
			अगर (cursor_position >= 0 && cursor_position < len) अणु
				स_हटाओ(&result[cursor_position],
						&result[cursor_position+1],
						len-cursor_position+1);
				len--;
			पूर्ण
			अवरोध;
		हाल KEY_UP:
		हाल KEY_RIGHT:
			अगर (cursor_position < len) अणु
				cursor_position++;
				cursor_क्रमm_win++;
			पूर्ण
			अवरोध;
		हाल KEY_DOWN:
		हाल KEY_LEFT:
			अगर (cursor_position > 0) अणु
				cursor_position--;
				cursor_क्रमm_win--;
			पूर्ण
			अवरोध;
		हाल KEY_HOME:
			cursor_position = 0;
			cursor_क्रमm_win = 0;
			अवरोध;
		हाल KEY_END:
			cursor_position = len;
			cursor_क्रमm_win = min(cursor_position, prompt_width-1);
			अवरोध;
		शेष:
			अगर ((है_चित्र(res) || है_खाली(res))) अणु
				/* one क्रम new अक्षर, one क्रम '\0' */
				अगर (len+2 > *result_len) अणु
					*result_len = len+2;
					*resultp = result = पुनः_स्मृति(result,
								*result_len);
				पूर्ण
				/* insert the अक्षर at the proper position */
				स_हटाओ(&result[cursor_position+1],
						&result[cursor_position],
						len-cursor_position+1);
				result[cursor_position] = res;
				cursor_position++;
				cursor_क्रमm_win++;
				len++;
			पूर्ण अन्यथा अणु
				mvprपूर्णांकw(0, 0, "unknown key: %d\n", res);
			पूर्ण
			अवरोध;
		पूर्ण
		अगर (cursor_क्रमm_win < 0)
			cursor_क्रमm_win = 0;
		अन्यथा अगर (cursor_क्रमm_win > prompt_width-1)
			cursor_क्रमm_win = prompt_width-1;

		wmove(क्रमm_win, 0, 0);
		wclrtoeol(क्रमm_win);
		mvwprपूर्णांकw(क्रमm_win, 0, 0, "%*s", prompt_width, " ");
		mvwprपूर्णांकw(क्रमm_win, 0, 0, "%s",
			result + cursor_position-cursor_क्रमm_win);
		wmove(क्रमm_win, 0, cursor_क्रमm_win);
		touchwin(win);
		refresh_all_winकरोws(मुख्य_winकरोw);

		अगर (res == 10) अणु
			res = 0;
			अवरोध;
		पूर्ण अन्यथा अगर (res == 27 || res == KEY_F(F_BACK) ||
				res == KEY_F(F_EXIT)) अणु
			res = KEY_EXIT;
			अवरोध;
		पूर्ण अन्यथा अगर (res == KEY_F(F_HELP)) अणु
			res = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	/* hide the cursor */
	curs_set(0);
	del_panel(panel);
	delwin(prompt_win);
	delwin(क्रमm_win);
	delwin(win);
	वापस res;
पूर्ण

/* refresh all winकरोws in the correct order */
व्योम refresh_all_winकरोws(WINDOW *मुख्य_winकरोw)
अणु
	update_panels();
	touchwin(मुख्य_winकरोw);
	refresh();
पूर्ण

/* layman's scrollable winकरोw... */
व्योम show_scroll_win(WINDOW *मुख्य_winकरोw,
		स्थिर अक्षर *title,
		स्थिर अक्षर *text)
अणु
	पूर्णांक res;
	पूर्णांक total_lines = get_line_no(text);
	पूर्णांक x, y, lines, columns;
	पूर्णांक start_x = 0, start_y = 0;
	पूर्णांक text_lines = 0, text_cols = 0;
	पूर्णांक total_cols = 0;
	पूर्णांक win_cols = 0;
	पूर्णांक win_lines = 0;
	पूर्णांक i = 0;
	WINDOW *win;
	WINDOW *pad;
	PANEL *panel;

	geपंचांगaxyx(stdscr, lines, columns);

	/* find the widest line of msg: */
	total_lines = get_line_no(text);
	क्रम (i = 0; i < total_lines; i++) अणु
		स्थिर अक्षर *line = get_line(text, i);
		पूर्णांक len = get_line_length(line);
		total_cols = max(total_cols, len+2);
	पूर्ण

	/* create the pad */
	pad = newpad(total_lines+10, total_cols+10);
	wattrset(pad, attr_scrollwin_text);
	fill_winकरोw(pad, text);

	win_lines = min(total_lines+4, lines-2);
	win_cols = min(total_cols+2, columns-2);
	text_lines = max(win_lines-4, 0);
	text_cols = max(win_cols-2, 0);

	/* place winकरोw in middle of screen */
	y = (lines-win_lines)/2;
	x = (columns-win_cols)/2;

	win = newwin(win_lines, win_cols, y, x);
	keypad(win, TRUE);
	/* show the help in the help winकरोw, and show the help panel */
	wattrset(win, attr_scrollwin_box);
	box(win, 0, 0);
	wattrset(win, attr_scrollwin_heading);
	mvwprपूर्णांकw(win, 0, 3, " %s ", title);
	panel = new_panel(win);

	/* handle scrolling */
	करो अणु

		copywin(pad, win, start_y, start_x, 2, 2, text_lines,
				text_cols, 0);
		prपूर्णांक_in_middle(win,
				text_lines+2,
				text_cols,
				"<OK>",
				attr_dialog_menu_क्रमe);
		wrefresh(win);

		res = wअ_लोh(win);
		चयन (res) अणु
		हाल KEY_NPAGE:
		हाल ' ':
		हाल 'd':
			start_y += text_lines-2;
			अवरोध;
		हाल KEY_PPAGE:
		हाल 'u':
			start_y -= text_lines+2;
			अवरोध;
		हाल KEY_HOME:
			start_y = 0;
			अवरोध;
		हाल KEY_END:
			start_y = total_lines-text_lines;
			अवरोध;
		हाल KEY_DOWN:
		हाल 'j':
			start_y++;
			अवरोध;
		हाल KEY_UP:
		हाल 'k':
			start_y--;
			अवरोध;
		हाल KEY_LEFT:
		हाल 'h':
			start_x--;
			अवरोध;
		हाल KEY_RIGHT:
		हाल 'l':
			start_x++;
			अवरोध;
		पूर्ण
		अगर (res == 10 || res == 27 || res == 'q' ||
			res == KEY_F(F_HELP) || res == KEY_F(F_BACK) ||
			res == KEY_F(F_EXIT))
			अवरोध;
		अगर (start_y < 0)
			start_y = 0;
		अगर (start_y >= total_lines-text_lines)
			start_y = total_lines-text_lines;
		अगर (start_x < 0)
			start_x = 0;
		अगर (start_x >= total_cols-text_cols)
			start_x = total_cols-text_cols;
	पूर्ण जबतक (res);

	del_panel(panel);
	delwin(win);
	refresh_all_winकरोws(मुख्य_winकरोw);
पूर्ण
