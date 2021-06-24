<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  yesno.c -- implements the yes/no box
 *
 *  ORIGINAL AUTHOR: Savio Lam (lam836@cs.cuhk.hk)
 *  MODIFIED FOR LINUX KERNEL CONFIG BY: William Roadcap (roadcap@cfw.com)
 */

#समावेश "dialog.h"

/*
 * Display termination buttons
 */
अटल व्योम prपूर्णांक_buttons(WINDOW * dialog, पूर्णांक height, पूर्णांक width, पूर्णांक selected)
अणु
	पूर्णांक x = width / 2 - 10;
	पूर्णांक y = height - 2;

	prपूर्णांक_button(dialog, " Yes ", y, x, selected == 0);
	prपूर्णांक_button(dialog, "  No  ", y, x + 13, selected == 1);

	wmove(dialog, y, x + 1 + 13 * selected);
	wrefresh(dialog);
पूर्ण

/*
 * Display a dialog box with two buttons - Yes and No
 */
पूर्णांक dialog_yesno(स्थिर अक्षर *title, स्थिर अक्षर *prompt, पूर्णांक height, पूर्णांक width)
अणु
	पूर्णांक i, x, y, key = 0, button = 0;
	WINDOW *dialog;

करो_resize:
	अगर (geपंचांगaxy(stdscr) < (height + YESNO_HEIGTH_MIN))
		वापस -ERRDISPLAYTOOSMALL;
	अगर (geपंचांगaxx(stdscr) < (width + YESNO_WIDTH_MIN))
		वापस -ERRDISPLAYTOOSMALL;

	/* center dialog box on screen */
	x = (geपंचांगaxx(stdscr) - width) / 2;
	y = (geपंचांगaxy(stdscr) - height) / 2;

	draw_shaकरोw(stdscr, y, x, height, width);

	dialog = newwin(height, width, y, x);
	keypad(dialog, TRUE);

	draw_box(dialog, 0, 0, height, width,
		 dlg.dialog.atr, dlg.border.atr);
	wattrset(dialog, dlg.border.atr);
	mvwaddch(dialog, height - 3, 0, ACS_LTEE);
	क्रम (i = 0; i < width - 2; i++)
		waddch(dialog, ACS_HLINE);
	wattrset(dialog, dlg.dialog.atr);
	waddch(dialog, ACS_RTEE);

	prपूर्णांक_title(dialog, title, width);

	wattrset(dialog, dlg.dialog.atr);
	prपूर्णांक_स्वतःwrap(dialog, prompt, width - 2, 1, 3);

	prपूर्णांक_buttons(dialog, height, width, 0);

	जबतक (key != KEY_ESC) अणु
		key = wअ_लोh(dialog);
		चयन (key) अणु
		हाल 'Y':
		हाल 'y':
			delwin(dialog);
			वापस 0;
		हाल 'N':
		हाल 'n':
			delwin(dialog);
			वापस 1;

		हाल TAB:
		हाल KEY_LEFT:
		हाल KEY_RIGHT:
			button = ((key == KEY_LEFT ? --button : ++button) < 0) ? 1 : (button > 1 ? 0 : button);

			prपूर्णांक_buttons(dialog, height, width, button);
			wrefresh(dialog);
			अवरोध;
		हाल ' ':
		हाल '\n':
			delwin(dialog);
			वापस button;
		हाल KEY_ESC:
			key = on_key_esc(dialog);
			अवरोध;
		हाल KEY_RESIZE:
			delwin(dialog);
			on_key_resize();
			जाओ करो_resize;
		पूर्ण
	पूर्ण

	delwin(dialog);
	वापस key;		/* ESC pressed */
पूर्ण
