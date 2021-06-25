<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008 Nir Tzaअक्षर <nir.tzaअक्षर@gmail.com>
 *
 * Derived from menuconfig.
 */

#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <सीमा.स>
#समावेश <मानकतर्क.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <ncurses.h>
#समावेश <menu.h>
#समावेश <panel.h>
#समावेश <क्रमm.h>

#समावेश <मानकपन.स>
#समावेश <समय.स>
#समावेश <sys/समय.स>

#घोषणा max(a, b) (अणु\
		typeof(a) _a = a;\
		typeof(b) _b = b;\
		_a > _b ? _a : _b; पूर्ण)

#घोषणा min(a, b) (अणु\
		typeof(a) _a = a;\
		typeof(b) _b = b;\
		_a < _b ? _a : _b; पूर्ण)

बाह्य पूर्णांक attr_normal;
बाह्य पूर्णांक attr_मुख्य_heading;
बाह्य पूर्णांक attr_मुख्य_menu_box;
बाह्य पूर्णांक attr_मुख्य_menu_क्रमe;
बाह्य पूर्णांक attr_मुख्य_menu_back;
बाह्य पूर्णांक attr_मुख्य_menu_grey;
बाह्य पूर्णांक attr_मुख्य_menu_heading;
बाह्य पूर्णांक attr_scrollwin_text;
बाह्य पूर्णांक attr_scrollwin_heading;
बाह्य पूर्णांक attr_scrollwin_box;
बाह्य पूर्णांक attr_dialog_text;
बाह्य पूर्णांक attr_dialog_menu_क्रमe;
बाह्य पूर्णांक attr_dialog_menu_back;
बाह्य पूर्णांक attr_dialog_box;
बाह्य पूर्णांक attr_input_box;
बाह्य पूर्णांक attr_input_heading;
बाह्य पूर्णांक attr_input_text;
बाह्य पूर्णांक attr_input_field;
बाह्य पूर्णांक attr_function_text;
बाह्य पूर्णांक attr_function_highlight;

प्रकार क्रमागत अणु
	F_HELP = 1,
	F_SYMBOL = 2,
	F_INSTS = 3,
	F_CONF = 4,
	F_BACK = 5,
	F_SAVE = 6,
	F_LOAD = 7,
	F_SEARCH = 8,
	F_EXIT = 9,
पूर्ण function_key;

व्योम set_colors(व्योम);

/* this changes the winकरोws attributes !!! */
व्योम prपूर्णांक_in_middle(WINDOW *win, पूर्णांक y, पूर्णांक width, स्थिर अक्षर *str, पूर्णांक attrs);
पूर्णांक get_line_length(स्थिर अक्षर *line);
पूर्णांक get_line_no(स्थिर अक्षर *text);
स्थिर अक्षर *get_line(स्थिर अक्षर *text, पूर्णांक line_no);
व्योम fill_winकरोw(WINDOW *win, स्थिर अक्षर *text);
पूर्णांक btn_dialog(WINDOW *मुख्य_winकरोw, स्थिर अक्षर *msg, पूर्णांक btn_num, ...);
पूर्णांक dialog_inputbox(WINDOW *मुख्य_winकरोw,
		स्थिर अक्षर *title, स्थिर अक्षर *prompt,
		स्थिर अक्षर *init, अक्षर **resultp, पूर्णांक *result_len);
व्योम refresh_all_winकरोws(WINDOW *मुख्य_winकरोw);
व्योम show_scroll_win(WINDOW *मुख्य_winकरोw,
		स्थिर अक्षर *title,
		स्थिर अक्षर *text);
