<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *  dialog.h -- common declarations क्रम all dialog modules
 *
 *  AUTHOR: Savio Lam (lam836@cs.cuhk.hk)
 */

#समावेश <sys/types.h>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <प्रकार.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <stdbool.h>

#अगर_घोषित __sun__
#घोषणा CURS_MACROS
#पूर्ण_अगर
#समावेश <ncurses.h>

/*
 * Colors in ncurses 1.9.9e करो not work properly since क्रमeground and
 * background colors are OR'd rather than separately masked.  This version
 * of dialog was hacked to work with ncurses 1.9.9e, making it incompatible
 * with standard curses.  The simplest fix (to make this work with standard
 * curses) uses the wbkgdset() function, not used in the original hack.
 * Turn it off अगर we're building with 1.9.9e, since it just confuses things.
 */
#अगर defined(NCURSES_VERSION) && defined(_NEED_WRAP) && !defined(GCC_PRINTFLIKE)
#घोषणा OLD_NCURSES 1
#अघोषित  wbkgdset
#घोषणा wbkgdset(w,p)		/*nothing */
#अन्यथा
#घोषणा OLD_NCURSES 0
#पूर्ण_अगर

#घोषणा TR(params) _tracef params

#घोषणा KEY_ESC 27
#घोषणा TAB 9
#घोषणा MAX_LEN 2048
#घोषणा BUF_SIZE (10*1024)
#घोषणा MIN(x,y) (x < y ? x : y)
#घोषणा MAX(x,y) (x > y ? x : y)

#अगर_अघोषित ACS_ULCORNER
#घोषणा ACS_ULCORNER '+'
#पूर्ण_अगर
#अगर_अघोषित ACS_LLCORNER
#घोषणा ACS_LLCORNER '+'
#पूर्ण_अगर
#अगर_अघोषित ACS_URCORNER
#घोषणा ACS_URCORNER '+'
#पूर्ण_अगर
#अगर_अघोषित ACS_LRCORNER
#घोषणा ACS_LRCORNER '+'
#पूर्ण_अगर
#अगर_अघोषित ACS_HLINE
#घोषणा ACS_HLINE '-'
#पूर्ण_अगर
#अगर_अघोषित ACS_VLINE
#घोषणा ACS_VLINE '|'
#पूर्ण_अगर
#अगर_अघोषित ACS_LTEE
#घोषणा ACS_LTEE '+'
#पूर्ण_अगर
#अगर_अघोषित ACS_RTEE
#घोषणा ACS_RTEE '+'
#पूर्ण_अगर
#अगर_अघोषित ACS_UARROW
#घोषणा ACS_UARROW '^'
#पूर्ण_अगर
#अगर_अघोषित ACS_DARROW
#घोषणा ACS_DARROW 'v'
#पूर्ण_अगर

/* error वापस codes */
#घोषणा ERRDISPLAYTOOSMALL (KEY_MAX + 1)

/*
 *   Color definitions
 */
काष्ठा dialog_color अणु
	chtype atr;	/* Color attribute */
	पूर्णांक fg;		/* क्रमeground */
	पूर्णांक bg;		/* background */
	पूर्णांक hl;		/* highlight this item */
पूर्ण;

काष्ठा subtitle_list अणु
	काष्ठा subtitle_list *next;
	स्थिर अक्षर *text;
पूर्ण;

काष्ठा dialog_info अणु
	स्थिर अक्षर *backtitle;
	काष्ठा subtitle_list *subtitles;
	काष्ठा dialog_color screen;
	काष्ठा dialog_color shaकरोw;
	काष्ठा dialog_color dialog;
	काष्ठा dialog_color title;
	काष्ठा dialog_color border;
	काष्ठा dialog_color button_active;
	काष्ठा dialog_color button_inactive;
	काष्ठा dialog_color button_key_active;
	काष्ठा dialog_color button_key_inactive;
	काष्ठा dialog_color button_label_active;
	काष्ठा dialog_color button_label_inactive;
	काष्ठा dialog_color inputbox;
	काष्ठा dialog_color inputbox_border;
	काष्ठा dialog_color searchbox;
	काष्ठा dialog_color searchbox_title;
	काष्ठा dialog_color searchbox_border;
	काष्ठा dialog_color position_indicator;
	काष्ठा dialog_color menubox;
	काष्ठा dialog_color menubox_border;
	काष्ठा dialog_color item;
	काष्ठा dialog_color item_selected;
	काष्ठा dialog_color tag;
	काष्ठा dialog_color tag_selected;
	काष्ठा dialog_color tag_key;
	काष्ठा dialog_color tag_key_selected;
	काष्ठा dialog_color check;
	काष्ठा dialog_color check_selected;
	काष्ठा dialog_color uarrow;
	काष्ठा dialog_color darrow;
पूर्ण;

/*
 * Global variables
 */
बाह्य काष्ठा dialog_info dlg;
बाह्य अक्षर dialog_input_result[];
बाह्य पूर्णांक saved_x, saved_y;		/* Needed in संकेत handler in mconf.c */

/*
 * Function prototypes
 */

/* item list as used by checklist and menubox */
व्योम item_reset(व्योम);
व्योम item_make(स्थिर अक्षर *fmt, ...);
व्योम item_add_str(स्थिर अक्षर *fmt, ...);
व्योम item_set_tag(अक्षर tag);
व्योम item_set_data(व्योम *p);
व्योम item_set_selected(पूर्णांक val);
पूर्णांक item_activate_selected(व्योम);
व्योम *item_data(व्योम);
अक्षर item_tag(व्योम);

/* item list manipulation क्रम lxdialog use */
#घोषणा MAXITEMSTR 200
काष्ठा dialog_item अणु
	अक्षर str[MAXITEMSTR];	/* prompt displayed */
	अक्षर tag;
	व्योम *data;	/* poपूर्णांकer to menu item - used by menubox+checklist */
	पूर्णांक selected;	/* Set to 1 by dialog_*() function अगर selected. */
पूर्ण;

/* list of lialog_items */
काष्ठा dialog_list अणु
	काष्ठा dialog_item node;
	काष्ठा dialog_list *next;
पूर्ण;

बाह्य काष्ठा dialog_list *item_cur;
बाह्य काष्ठा dialog_list item_nil;
बाह्य काष्ठा dialog_list *item_head;

पूर्णांक item_count(व्योम);
व्योम item_set(पूर्णांक n);
पूर्णांक item_n(व्योम);
स्थिर अक्षर *item_str(व्योम);
पूर्णांक item_is_selected(व्योम);
पूर्णांक item_is_tag(अक्षर tag);
#घोषणा item_क्रमeach() \
	क्रम (item_cur = item_head ? item_head: item_cur; \
	     item_cur && (item_cur != &item_nil); item_cur = item_cur->next)

/* generic key handlers */
पूर्णांक on_key_esc(WINDOW *win);
पूर्णांक on_key_resize(व्योम);

/* minimum (re)size values */
#घोषणा CHECKLIST_HEIGTH_MIN 6	/* For dialog_checklist() */
#घोषणा CHECKLIST_WIDTH_MIN 6
#घोषणा INPUTBOX_HEIGTH_MIN 2	/* For dialog_inputbox() */
#घोषणा INPUTBOX_WIDTH_MIN 2
#घोषणा MENUBOX_HEIGTH_MIN 15	/* For dialog_menu() */
#घोषणा MENUBOX_WIDTH_MIN 65
#घोषणा TEXTBOX_HEIGTH_MIN 8	/* For dialog_textbox() */
#घोषणा TEXTBOX_WIDTH_MIN 8
#घोषणा YESNO_HEIGTH_MIN 4	/* For dialog_yesno() */
#घोषणा YESNO_WIDTH_MIN 4
#घोषणा WINDOW_HEIGTH_MIN 19	/* For init_dialog() */
#घोषणा WINDOW_WIDTH_MIN 80

पूर्णांक init_dialog(स्थिर अक्षर *backtitle);
व्योम set_dialog_backtitle(स्थिर अक्षर *backtitle);
व्योम set_dialog_subtitles(काष्ठा subtitle_list *subtitles);
व्योम end_dialog(पूर्णांक x, पूर्णांक y);
व्योम attr_clear(WINDOW * win, पूर्णांक height, पूर्णांक width, chtype attr);
व्योम dialog_clear(व्योम);
व्योम prपूर्णांक_स्वतःwrap(WINDOW * win, स्थिर अक्षर *prompt, पूर्णांक width, पूर्णांक y, पूर्णांक x);
व्योम prपूर्णांक_button(WINDOW * win, स्थिर अक्षर *label, पूर्णांक y, पूर्णांक x, पूर्णांक selected);
व्योम prपूर्णांक_title(WINDOW *dialog, स्थिर अक्षर *title, पूर्णांक width);
व्योम draw_box(WINDOW * win, पूर्णांक y, पूर्णांक x, पूर्णांक height, पूर्णांक width, chtype box,
	      chtype border);
व्योम draw_shaकरोw(WINDOW * win, पूर्णांक y, पूर्णांक x, पूर्णांक height, पूर्णांक width);

पूर्णांक first_alpha(स्थिर अक्षर *string, स्थिर अक्षर *exempt);
पूर्णांक dialog_yesno(स्थिर अक्षर *title, स्थिर अक्षर *prompt, पूर्णांक height, पूर्णांक width);
पूर्णांक dialog_msgbox(स्थिर अक्षर *title, स्थिर अक्षर *prompt, पूर्णांक height,
		  पूर्णांक width, पूर्णांक छोड़ो);


प्रकार व्योम (*update_text_fn)(अक्षर *buf, माप_प्रकार start, माप_प्रकार end, व्योम
			       *_data);
पूर्णांक dialog_textbox(स्थिर अक्षर *title, अक्षर *tbuf, पूर्णांक initial_height,
		   पूर्णांक initial_width, पूर्णांक *keys, पूर्णांक *_vscroll, पूर्णांक *_hscroll,
		   update_text_fn update_text, व्योम *data);
पूर्णांक dialog_menu(स्थिर अक्षर *title, स्थिर अक्षर *prompt,
		स्थिर व्योम *selected, पूर्णांक *s_scroll);
पूर्णांक dialog_checklist(स्थिर अक्षर *title, स्थिर अक्षर *prompt, पूर्णांक height,
		     पूर्णांक width, पूर्णांक list_height);
पूर्णांक dialog_inputbox(स्थिर अक्षर *title, स्थिर अक्षर *prompt, पूर्णांक height,
		    पूर्णांक width, स्थिर अक्षर *init);

/*
 * This is the base क्रम fictitious keys, which activate
 * the buttons.
 *
 * Mouse-generated keys are the following:
 *   -- the first 32 are used as numbers, in addition to '0'-'9'
 *   -- the lowerहाल are used to संकेत mouse-enter events (M_EVENT + 'o')
 *   -- upperहाल अक्षरs are used to invoke the button (M_EVENT + 'O')
 */
#घोषणा M_EVENT (KEY_MAX+1)
