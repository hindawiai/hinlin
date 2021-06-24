<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  checklist.c -- implements the checklist box
 *
 *  ORIGINAL AUTHOR: Savio Lam (lam836@cs.cuhk.hk)
 *     Stuart Herbert - S.Herbert@sheffield.ac.uk: radiolist extension
 *     Alessandro Rubini - rubini@ipvvis.unipv.it: merged the two
 *  MODIFIED FOR LINUX KERNEL CONFIG BY: William Roadcap (roadcap@cfw.com)
 */

#समावेश "dialog.h"

अटल पूर्णांक list_width, check_x, item_x;

/*
 * Prपूर्णांक list item
 */
अटल व्योम prपूर्णांक_item(WINDOW * win, पूर्णांक choice, पूर्णांक selected)
अणु
	पूर्णांक i;
	अक्षर *list_item = दो_स्मृति(list_width + 1);

	म_नकलन(list_item, item_str(), list_width - item_x);
	list_item[list_width - item_x] = '\0';

	/* Clear 'residue' of last item */
	wattrset(win, dlg.menubox.atr);
	wmove(win, choice, 0);
	क्रम (i = 0; i < list_width; i++)
		waddch(win, ' ');

	wmove(win, choice, check_x);
	wattrset(win, selected ? dlg.check_selected.atr
		 : dlg.check.atr);
	अगर (!item_is_tag(':'))
		wprपूर्णांकw(win, "(%c)", item_is_tag('X') ? 'X' : ' ');

	wattrset(win, selected ? dlg.tag_selected.atr : dlg.tag.atr);
	mvwaddch(win, choice, item_x, list_item[0]);
	wattrset(win, selected ? dlg.item_selected.atr : dlg.item.atr);
	waddstr(win, list_item + 1);
	अगर (selected) अणु
		wmove(win, choice, check_x + 1);
		wrefresh(win);
	पूर्ण
	मुक्त(list_item);
पूर्ण

/*
 * Prपूर्णांक the scroll indicators.
 */
अटल व्योम prपूर्णांक_arrows(WINDOW * win, पूर्णांक choice, पूर्णांक item_no, पूर्णांक scroll,
	     पूर्णांक y, पूर्णांक x, पूर्णांक height)
अणु
	wmove(win, y, x);

	अगर (scroll > 0) अणु
		wattrset(win, dlg.uarrow.atr);
		waddch(win, ACS_UARROW);
		waddstr(win, "(-)");
	पूर्ण अन्यथा अणु
		wattrset(win, dlg.menubox.atr);
		waddch(win, ACS_HLINE);
		waddch(win, ACS_HLINE);
		waddch(win, ACS_HLINE);
		waddch(win, ACS_HLINE);
	पूर्ण

	y = y + height + 1;
	wmove(win, y, x);

	अगर ((height < item_no) && (scroll + choice < item_no - 1)) अणु
		wattrset(win, dlg.darrow.atr);
		waddch(win, ACS_DARROW);
		waddstr(win, "(+)");
	पूर्ण अन्यथा अणु
		wattrset(win, dlg.menubox_border.atr);
		waddch(win, ACS_HLINE);
		waddch(win, ACS_HLINE);
		waddch(win, ACS_HLINE);
		waddch(win, ACS_HLINE);
	पूर्ण
पूर्ण

/*
 *  Display the termination buttons
 */
अटल व्योम prपूर्णांक_buttons(WINDOW * dialog, पूर्णांक height, पूर्णांक width, पूर्णांक selected)
अणु
	पूर्णांक x = width / 2 - 11;
	पूर्णांक y = height - 2;

	prपूर्णांक_button(dialog, "Select", y, x, selected == 0);
	prपूर्णांक_button(dialog, " Help ", y, x + 14, selected == 1);

	wmove(dialog, y, x + 1 + 14 * selected);
	wrefresh(dialog);
पूर्ण

/*
 * Display a dialog box with a list of options that can be turned on or off
 * in the style of radiolist (only one option turned on at a समय).
 */
पूर्णांक dialog_checklist(स्थिर अक्षर *title, स्थिर अक्षर *prompt, पूर्णांक height,
		     पूर्णांक width, पूर्णांक list_height)
अणु
	पूर्णांक i, x, y, box_x, box_y;
	पूर्णांक key = 0, button = 0, choice = 0, scroll = 0, max_choice;
	WINDOW *dialog, *list;

	/* which item to highlight */
	item_क्रमeach() अणु
		अगर (item_is_tag('X'))
			choice = item_n();
		अगर (item_is_selected()) अणु
			choice = item_n();
			अवरोध;
		पूर्ण
	पूर्ण

करो_resize:
	अगर (geपंचांगaxy(stdscr) < (height + CHECKLIST_HEIGTH_MIN))
		वापस -ERRDISPLAYTOOSMALL;
	अगर (geपंचांगaxx(stdscr) < (width + CHECKLIST_WIDTH_MIN))
		वापस -ERRDISPLAYTOOSMALL;

	max_choice = MIN(list_height, item_count());

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

	list_width = width - 6;
	box_y = height - list_height - 5;
	box_x = (width - list_width) / 2 - 1;

	/* create new winकरोw क्रम the list */
	list = subwin(dialog, list_height, list_width, y + box_y + 1,
		      x + box_x + 1);

	keypad(list, TRUE);

	/* draw a box around the list items */
	draw_box(dialog, box_y, box_x, list_height + 2, list_width + 2,
		 dlg.menubox_border.atr, dlg.menubox.atr);

	/* Find length of दीर्घest item in order to center checklist */
	check_x = 0;
	item_क्रमeach()
		check_x = MAX(check_x, म_माप(item_str()) + 4);
	check_x = MIN(check_x, list_width);

	check_x = (list_width - check_x) / 2;
	item_x = check_x + 4;

	अगर (choice >= list_height) अणु
		scroll = choice - list_height + 1;
		choice -= scroll;
	पूर्ण

	/* Prपूर्णांक the list */
	क्रम (i = 0; i < max_choice; i++) अणु
		item_set(scroll + i);
		prपूर्णांक_item(list, i, i == choice);
	पूर्ण

	prपूर्णांक_arrows(dialog, choice, item_count(), scroll,
		     box_y, box_x + check_x + 5, list_height);

	prपूर्णांक_buttons(dialog, height, width, 0);

	wnoutrefresh(dialog);
	wnoutrefresh(list);
	करोupdate();

	जबतक (key != KEY_ESC) अणु
		key = wअ_लोh(dialog);

		क्रम (i = 0; i < max_choice; i++) अणु
			item_set(i + scroll);
			अगर (बड़े(key) == बड़े(item_str()[0]))
				अवरोध;
		पूर्ण

		अगर (i < max_choice || key == KEY_UP || key == KEY_DOWN ||
		    key == '+' || key == '-') अणु
			अगर (key == KEY_UP || key == '-') अणु
				अगर (!choice) अणु
					अगर (!scroll)
						जारी;
					/* Scroll list करोwn */
					अगर (list_height > 1) अणु
						/* De-highlight current first item */
						item_set(scroll);
						prपूर्णांक_item(list, 0, FALSE);
						scrollok(list, TRUE);
						wscrl(list, -1);
						scrollok(list, FALSE);
					पूर्ण
					scroll--;
					item_set(scroll);
					prपूर्णांक_item(list, 0, TRUE);
					prपूर्णांक_arrows(dialog, choice, item_count(),
						     scroll, box_y, box_x + check_x + 5, list_height);

					wnoutrefresh(dialog);
					wrefresh(list);

					जारी;	/* रुको क्रम another key press */
				पूर्ण अन्यथा
					i = choice - 1;
			पूर्ण अन्यथा अगर (key == KEY_DOWN || key == '+') अणु
				अगर (choice == max_choice - 1) अणु
					अगर (scroll + choice >= item_count() - 1)
						जारी;
					/* Scroll list up */
					अगर (list_height > 1) अणु
						/* De-highlight current last item beक्रमe scrolling up */
						item_set(scroll + max_choice - 1);
						prपूर्णांक_item(list,
							    max_choice - 1,
							    FALSE);
						scrollok(list, TRUE);
						wscrl(list, 1);
						scrollok(list, FALSE);
					पूर्ण
					scroll++;
					item_set(scroll + max_choice - 1);
					prपूर्णांक_item(list, max_choice - 1, TRUE);

					prपूर्णांक_arrows(dialog, choice, item_count(),
						     scroll, box_y, box_x + check_x + 5, list_height);

					wnoutrefresh(dialog);
					wrefresh(list);

					जारी;	/* रुको क्रम another key press */
				पूर्ण अन्यथा
					i = choice + 1;
			पूर्ण
			अगर (i != choice) अणु
				/* De-highlight current item */
				item_set(scroll + choice);
				prपूर्णांक_item(list, choice, FALSE);
				/* Highlight new item */
				choice = i;
				item_set(scroll + choice);
				prपूर्णांक_item(list, choice, TRUE);
				wnoutrefresh(dialog);
				wrefresh(list);
			पूर्ण
			जारी;	/* रुको क्रम another key press */
		पूर्ण
		चयन (key) अणु
		हाल 'H':
		हाल 'h':
		हाल '?':
			button = 1;
			/* fall-through */
		हाल 'S':
		हाल 's':
		हाल ' ':
		हाल '\n':
			item_क्रमeach()
				item_set_selected(0);
			item_set(scroll + choice);
			item_set_selected(1);
			delwin(list);
			delwin(dialog);
			वापस button;
		हाल TAB:
		हाल KEY_LEFT:
		हाल KEY_RIGHT:
			button = ((key == KEY_LEFT ? --button : ++button) < 0)
			    ? 1 : (button > 1 ? 0 : button);

			prपूर्णांक_buttons(dialog, height, width, button);
			wrefresh(dialog);
			अवरोध;
		हाल 'X':
		हाल 'x':
			key = KEY_ESC;
			अवरोध;
		हाल KEY_ESC:
			key = on_key_esc(dialog);
			अवरोध;
		हाल KEY_RESIZE:
			delwin(list);
			delwin(dialog);
			on_key_resize();
			जाओ करो_resize;
		पूर्ण

		/* Now, update everything... */
		करोupdate();
	पूर्ण
	delwin(list);
	delwin(dialog);
	वापस key;		/* ESC pressed */
पूर्ण
