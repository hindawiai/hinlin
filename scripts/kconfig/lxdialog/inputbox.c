<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  inputbox.c -- implements the input box
 *
 *  ORIGINAL AUTHOR: Savio Lam (lam836@cs.cuhk.hk)
 *  MODIFIED FOR LINUX KERNEL CONFIG BY: William Roadcap (roadcap@cfw.com)
 */

#समावेश "dialog.h"

अक्षर dialog_input_result[MAX_LEN + 1];

/*
 *  Prपूर्णांक the termination buttons
 */
अटल व्योम prपूर्णांक_buttons(WINDOW * dialog, पूर्णांक height, पूर्णांक width, पूर्णांक selected)
अणु
	पूर्णांक x = width / 2 - 11;
	पूर्णांक y = height - 2;

	prपूर्णांक_button(dialog, "  Ok  ", y, x, selected == 0);
	prपूर्णांक_button(dialog, " Help ", y, x + 14, selected == 1);

	wmove(dialog, y, x + 1 + 14 * selected);
	wrefresh(dialog);
पूर्ण

/*
 * Display a dialog box क्रम inputing a string
 */
पूर्णांक dialog_inputbox(स्थिर अक्षर *title, स्थिर अक्षर *prompt, पूर्णांक height, पूर्णांक width,
		    स्थिर अक्षर *init)
अणु
	पूर्णांक i, x, y, box_y, box_x, box_width;
	पूर्णांक input_x = 0, key = 0, button = -1;
	पूर्णांक show_x, len, pos;
	अक्षर *instr = dialog_input_result;
	WINDOW *dialog;

	अगर (!init)
		instr[0] = '\0';
	अन्यथा
		म_नकल(instr, init);

करो_resize:
	अगर (geपंचांगaxy(stdscr) <= (height - INPUTBOX_HEIGTH_MIN))
		वापस -ERRDISPLAYTOOSMALL;
	अगर (geपंचांगaxx(stdscr) <= (width - INPUTBOX_WIDTH_MIN))
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

	/* Draw the input field box */
	box_width = width - 6;
	getyx(dialog, y, x);
	box_y = y + 2;
	box_x = (width - box_width) / 2;
	draw_box(dialog, y + 1, box_x - 1, 3, box_width + 2,
		 dlg.dialog.atr, dlg.border.atr);

	prपूर्णांक_buttons(dialog, height, width, 0);

	/* Set up the initial value */
	wmove(dialog, box_y, box_x);
	wattrset(dialog, dlg.inputbox.atr);

	len = म_माप(instr);
	pos = len;

	अगर (len >= box_width) अणु
		show_x = len - box_width + 1;
		input_x = box_width - 1;
		क्रम (i = 0; i < box_width - 1; i++)
			waddch(dialog, instr[show_x + i]);
	पूर्ण अन्यथा अणु
		show_x = 0;
		input_x = len;
		waddstr(dialog, instr);
	पूर्ण

	wmove(dialog, box_y, box_x + input_x);

	wrefresh(dialog);

	जबतक (key != KEY_ESC) अणु
		key = wअ_लोh(dialog);

		अगर (button == -1) अणु	/* Input box selected */
			चयन (key) अणु
			हाल TAB:
			हाल KEY_UP:
			हाल KEY_DOWN:
				अवरोध;
			हाल KEY_BACKSPACE:
			हाल 8:   /* ^H */
			हाल 127: /* ^? */
				अगर (pos) अणु
					wattrset(dialog, dlg.inputbox.atr);
					अगर (input_x == 0) अणु
						show_x--;
					पूर्ण अन्यथा
						input_x--;

					अगर (pos < len) अणु
						क्रम (i = pos - 1; i < len; i++) अणु
							instr[i] = instr[i+1];
						पूर्ण
					पूर्ण

					pos--;
					len--;
					instr[len] = '\0';
					wmove(dialog, box_y, box_x);
					क्रम (i = 0; i < box_width; i++) अणु
						अगर (!instr[show_x + i]) अणु
							waddch(dialog, ' ');
							अवरोध;
						पूर्ण
						waddch(dialog, instr[show_x + i]);
					पूर्ण
					wmove(dialog, box_y, input_x + box_x);
					wrefresh(dialog);
				पूर्ण
				जारी;
			हाल KEY_LEFT:
				अगर (pos > 0) अणु
					अगर (input_x > 0) अणु
						wmove(dialog, box_y, --input_x + box_x);
					पूर्ण अन्यथा अगर (input_x == 0) अणु
						show_x--;
						wmove(dialog, box_y, box_x);
						क्रम (i = 0; i < box_width; i++) अणु
							अगर (!instr[show_x + i]) अणु
								waddch(dialog, ' ');
								अवरोध;
							पूर्ण
							waddch(dialog, instr[show_x + i]);
						पूर्ण
						wmove(dialog, box_y, box_x);
					पूर्ण
					pos--;
				पूर्ण
				जारी;
			हाल KEY_RIGHT:
				अगर (pos < len) अणु
					अगर (input_x < box_width - 1) अणु
						wmove(dialog, box_y, ++input_x + box_x);
					पूर्ण अन्यथा अगर (input_x == box_width - 1) अणु
						show_x++;
						wmove(dialog, box_y, box_x);
						क्रम (i = 0; i < box_width; i++) अणु
							अगर (!instr[show_x + i]) अणु
								waddch(dialog, ' ');
								अवरोध;
							पूर्ण
							waddch(dialog, instr[show_x + i]);
						पूर्ण
						wmove(dialog, box_y, input_x + box_x);
					पूर्ण
					pos++;
				पूर्ण
				जारी;
			शेष:
				अगर (key < 0x100 && है_छाप(key)) अणु
					अगर (len < MAX_LEN) अणु
						wattrset(dialog, dlg.inputbox.atr);
						अगर (pos < len) अणु
							क्रम (i = len; i > pos; i--)
								instr[i] = instr[i-1];
							instr[pos] = key;
						पूर्ण अन्यथा अणु
							instr[len] = key;
						पूर्ण
						pos++;
						len++;
						instr[len] = '\0';

						अगर (input_x == box_width - 1) अणु
							show_x++;
						पूर्ण अन्यथा अणु
							input_x++;
						पूर्ण

						wmove(dialog, box_y, box_x);
						क्रम (i = 0; i < box_width; i++) अणु
							अगर (!instr[show_x + i]) अणु
								waddch(dialog, ' ');
								अवरोध;
							पूर्ण
							waddch(dialog, instr[show_x + i]);
						पूर्ण
						wmove(dialog, box_y, input_x + box_x);
						wrefresh(dialog);
					पूर्ण अन्यथा
						flash();	/* Alarm user about overflow */
					जारी;
				पूर्ण
			पूर्ण
		पूर्ण
		चयन (key) अणु
		हाल 'O':
		हाल 'o':
			delwin(dialog);
			वापस 0;
		हाल 'H':
		हाल 'h':
			delwin(dialog);
			वापस 1;
		हाल KEY_UP:
		हाल KEY_LEFT:
			चयन (button) अणु
			हाल -1:
				button = 1;	/* Indicates "Help" button is selected */
				prपूर्णांक_buttons(dialog, height, width, 1);
				अवरोध;
			हाल 0:
				button = -1;	/* Indicates input box is selected */
				prपूर्णांक_buttons(dialog, height, width, 0);
				wmove(dialog, box_y, box_x + input_x);
				wrefresh(dialog);
				अवरोध;
			हाल 1:
				button = 0;	/* Indicates "OK" button is selected */
				prपूर्णांक_buttons(dialog, height, width, 0);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल TAB:
		हाल KEY_DOWN:
		हाल KEY_RIGHT:
			चयन (button) अणु
			हाल -1:
				button = 0;	/* Indicates "OK" button is selected */
				prपूर्णांक_buttons(dialog, height, width, 0);
				अवरोध;
			हाल 0:
				button = 1;	/* Indicates "Help" button is selected */
				prपूर्णांक_buttons(dialog, height, width, 1);
				अवरोध;
			हाल 1:
				button = -1;	/* Indicates input box is selected */
				prपूर्णांक_buttons(dialog, height, width, 0);
				wmove(dialog, box_y, box_x + input_x);
				wrefresh(dialog);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल ' ':
		हाल '\n':
			delwin(dialog);
			वापस (button == -1 ? 0 : button);
		हाल 'X':
		हाल 'x':
			key = KEY_ESC;
			अवरोध;
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
	वापस KEY_ESC;		/* ESC pressed */
पूर्ण
