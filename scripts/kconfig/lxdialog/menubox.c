<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  menubox.c -- implements the menu box
 *
 *  ORIGINAL AUTHOR: Savio Lam (lam836@cs.cuhk.hk)
 *  MODIFIED FOR LINUX KERNEL CONFIG BY: William Roadcap (roadcapw@cfw.com)
 */

/*
 *  Changes by Clअगरक्रमd Wolf (god@clअगरक्रमd.at)
 *
 *  [ 1998-06-13 ]
 *
 *    *)  A bugfix क्रम the Page-Down problem
 *
 *    *)  Formerly when I used Page Down and Page Up, the cursor would be set
 *        to the first position in the menu box.  Now lxdialog is a bit
 *        smarter and works more like other menu प्रणालीs (just have a look at
 *        it).
 *
 *    *)  Formerly अगर I selected something my scrolling would be broken because
 *        lxdialog is re-invoked by the Menuconfig shell script, can't
 *        remember the last scrolling position, and just sets it so that the
 *        cursor is at the bottom of the box.  Now it ग_लिखोs the temporary file
 *        lxdialog.scrlपंचांगp which contains this inक्रमmation. The file is
 *        deleted by lxdialog अगर the user leaves a submenu or enters a new
 *        one, but it would be nice अगर Menuconfig could make another "rm -f"
 *        just to be sure.  Just try it out - you will recognise a dअगरference!
 *
 *  [ 1998-06-14 ]
 *
 *    *)  Now lxdialog is crash-safe against broken "lxdialog.scrltmp" files
 *        and menus change their size on the fly.
 *
 *    *)  If क्रम some reason the last scrolling position is not saved by
 *        lxdialog, it sets the scrolling so that the selected item is in the
 *        middle of the menu box, not at the bottom.
 *
 * 02 January 1999, Michael Elizabeth Chastain (mec@shout.net)
 * Reset 'scroll' to 0 अगर the value from lxdialog.scrlपंचांगp is bogus.
 * This fixes a bug in Menuconfig where using ' ' to descend पूर्णांकo menus
 * would leave mis-synchronized lxdialog.scrlपंचांगp files lying around,
 * ख_पूछो would पढ़ो in 'scroll', and eventually that value would get used.
 */

#समावेश "dialog.h"

अटल पूर्णांक menu_width, item_x;

/*
 * Prपूर्णांक menu item
 */
अटल व्योम करो_prपूर्णांक_item(WINDOW * win, स्थिर अक्षर *item, पूर्णांक line_y,
			  पूर्णांक selected, पूर्णांक hotkey)
अणु
	पूर्णांक j;
	अक्षर *menu_item = दो_स्मृति(menu_width + 1);

	म_नकलन(menu_item, item, menu_width - item_x);
	menu_item[menu_width - item_x] = '\0';
	j = first_alpha(menu_item, "YyNnMmHh");

	/* Clear 'residue' of last item */
	wattrset(win, dlg.menubox.atr);
	wmove(win, line_y, 0);
#अगर OLD_NCURSES
	अणु
		पूर्णांक i;
		क्रम (i = 0; i < menu_width; i++)
			waddch(win, ' ');
	पूर्ण
#अन्यथा
	wclrtoeol(win);
#पूर्ण_अगर
	wattrset(win, selected ? dlg.item_selected.atr : dlg.item.atr);
	mvwaddstr(win, line_y, item_x, menu_item);
	अगर (hotkey) अणु
		wattrset(win, selected ? dlg.tag_key_selected.atr
			 : dlg.tag_key.atr);
		mvwaddch(win, line_y, item_x + j, menu_item[j]);
	पूर्ण
	अगर (selected) अणु
		wmove(win, line_y, item_x + 1);
	पूर्ण
	मुक्त(menu_item);
	wrefresh(win);
पूर्ण

#घोषणा prपूर्णांक_item(index, choice, selected)				\
करो अणु									\
	item_set(index);						\
	करो_prपूर्णांक_item(menu, item_str(), choice, selected, !item_is_tag(':')); \
पूर्ण जबतक (0)

/*
 * Prपूर्णांक the scroll indicators.
 */
अटल व्योम prपूर्णांक_arrows(WINDOW * win, पूर्णांक item_no, पूर्णांक scroll, पूर्णांक y, पूर्णांक x,
			 पूर्णांक height)
अणु
	पूर्णांक cur_y, cur_x;

	getyx(win, cur_y, cur_x);

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
	wrefresh(win);

	अगर ((height < item_no) && (scroll + height < item_no)) अणु
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

	wmove(win, cur_y, cur_x);
	wrefresh(win);
पूर्ण

/*
 * Display the termination buttons.
 */
अटल व्योम prपूर्णांक_buttons(WINDOW * win, पूर्णांक height, पूर्णांक width, पूर्णांक selected)
अणु
	पूर्णांक x = width / 2 - 28;
	पूर्णांक y = height - 2;

	prपूर्णांक_button(win, "Select", y, x, selected == 0);
	prपूर्णांक_button(win, " Exit ", y, x + 12, selected == 1);
	prपूर्णांक_button(win, " Help ", y, x + 24, selected == 2);
	prपूर्णांक_button(win, " Save ", y, x + 36, selected == 3);
	prपूर्णांक_button(win, " Load ", y, x + 48, selected == 4);

	wmove(win, y, x + 1 + 12 * selected);
	wrefresh(win);
पूर्ण

/* scroll up n lines (n may be negative) */
अटल व्योम करो_scroll(WINDOW *win, पूर्णांक *scroll, पूर्णांक n)
अणु
	/* Scroll menu up */
	scrollok(win, TRUE);
	wscrl(win, n);
	scrollok(win, FALSE);
	*scroll = *scroll + n;
	wrefresh(win);
पूर्ण

/*
 * Display a menu क्रम choosing among a number of options
 */
पूर्णांक dialog_menu(स्थिर अक्षर *title, स्थिर अक्षर *prompt,
		स्थिर व्योम *selected, पूर्णांक *s_scroll)
अणु
	पूर्णांक i, j, x, y, box_x, box_y;
	पूर्णांक height, width, menu_height;
	पूर्णांक key = 0, button = 0, scroll = 0, choice = 0;
	पूर्णांक first_item =  0, max_choice;
	WINDOW *dialog, *menu;

करो_resize:
	height = geपंचांगaxy(stdscr);
	width = geपंचांगaxx(stdscr);
	अगर (height < MENUBOX_HEIGTH_MIN || width < MENUBOX_WIDTH_MIN)
		वापस -ERRDISPLAYTOOSMALL;

	height -= 4;
	width  -= 5;
	menu_height = height - 10;

	max_choice = MIN(menu_height, item_count());

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
	wbkgdset(dialog, dlg.dialog.atr & A_COLOR);
	waddch(dialog, ACS_RTEE);

	prपूर्णांक_title(dialog, title, width);

	wattrset(dialog, dlg.dialog.atr);
	prपूर्णांक_स्वतःwrap(dialog, prompt, width - 2, 1, 3);

	menu_width = width - 6;
	box_y = height - menu_height - 5;
	box_x = (width - menu_width) / 2 - 1;

	/* create new winकरोw क्रम the menu */
	menu = subwin(dialog, menu_height, menu_width,
		      y + box_y + 1, x + box_x + 1);
	keypad(menu, TRUE);

	/* draw a box around the menu items */
	draw_box(dialog, box_y, box_x, menu_height + 2, menu_width + 2,
		 dlg.menubox_border.atr, dlg.menubox.atr);

	अगर (menu_width >= 80)
		item_x = (menu_width - 70) / 2;
	अन्यथा
		item_x = 4;

	/* Set choice to शेष item */
	item_क्रमeach()
		अगर (selected && (selected == item_data()))
			choice = item_n();
	/* get the saved scroll info */
	scroll = *s_scroll;
	अगर ((scroll <= choice) && (scroll + max_choice > choice) &&
	   (scroll >= 0) && (scroll + max_choice <= item_count())) अणु
		first_item = scroll;
		choice = choice - scroll;
	पूर्ण अन्यथा अणु
		scroll = 0;
	पूर्ण
	अगर ((choice >= max_choice)) अणु
		अगर (choice >= item_count() - max_choice / 2)
			scroll = first_item = item_count() - max_choice;
		अन्यथा
			scroll = first_item = choice - max_choice / 2;
		choice = choice - scroll;
	पूर्ण

	/* Prपूर्णांक the menu */
	क्रम (i = 0; i < max_choice; i++) अणु
		prपूर्णांक_item(first_item + i, i, i == choice);
	पूर्ण

	wnoutrefresh(menu);

	prपूर्णांक_arrows(dialog, item_count(), scroll,
		     box_y, box_x + item_x + 1, menu_height);

	prपूर्णांक_buttons(dialog, height, width, 0);
	wmove(menu, choice, item_x + 1);
	wrefresh(menu);

	जबतक (key != KEY_ESC) अणु
		key = wअ_लोh(menu);

		अगर (key < 256 && है_अक्षर(key))
			key = छोटे(key);

		अगर (म_अक्षर("ynmh", key))
			i = max_choice;
		अन्यथा अणु
			क्रम (i = choice + 1; i < max_choice; i++) अणु
				item_set(scroll + i);
				j = first_alpha(item_str(), "YyNnMmHh");
				अगर (key == छोटे(item_str()[j]))
					अवरोध;
			पूर्ण
			अगर (i == max_choice)
				क्रम (i = 0; i < max_choice; i++) अणु
					item_set(scroll + i);
					j = first_alpha(item_str(), "YyNnMmHh");
					अगर (key == छोटे(item_str()[j]))
						अवरोध;
				पूर्ण
		पूर्ण

		अगर (item_count() != 0 &&
		    (i < max_choice ||
		     key == KEY_UP || key == KEY_DOWN ||
		     key == '-' || key == '+' ||
		     key == KEY_PPAGE || key == KEY_NPAGE)) अणु
			/* Remove highligt of current item */
			prपूर्णांक_item(scroll + choice, choice, FALSE);

			अगर (key == KEY_UP || key == '-') अणु
				अगर (choice < 2 && scroll) अणु
					/* Scroll menu करोwn */
					करो_scroll(menu, &scroll, -1);

					prपूर्णांक_item(scroll, 0, FALSE);
				पूर्ण अन्यथा
					choice = MAX(choice - 1, 0);

			पूर्ण अन्यथा अगर (key == KEY_DOWN || key == '+') अणु
				prपूर्णांक_item(scroll+choice, choice, FALSE);

				अगर ((choice > max_choice - 3) &&
				    (scroll + max_choice < item_count())) अणु
					/* Scroll menu up */
					करो_scroll(menu, &scroll, 1);

					prपूर्णांक_item(scroll+max_choice - 1,
						   max_choice - 1, FALSE);
				पूर्ण अन्यथा
					choice = MIN(choice + 1, max_choice - 1);

			पूर्ण अन्यथा अगर (key == KEY_PPAGE) अणु
				scrollok(menu, TRUE);
				क्रम (i = 0; (i < max_choice); i++) अणु
					अगर (scroll > 0) अणु
						करो_scroll(menu, &scroll, -1);
						prपूर्णांक_item(scroll, 0, FALSE);
					पूर्ण अन्यथा अणु
						अगर (choice > 0)
							choice--;
					पूर्ण
				पूर्ण

			पूर्ण अन्यथा अगर (key == KEY_NPAGE) अणु
				क्रम (i = 0; (i < max_choice); i++) अणु
					अगर (scroll + max_choice < item_count()) अणु
						करो_scroll(menu, &scroll, 1);
						prपूर्णांक_item(scroll+max_choice-1,
							   max_choice - 1, FALSE);
					पूर्ण अन्यथा अणु
						अगर (choice + 1 < max_choice)
							choice++;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा
				choice = i;

			prपूर्णांक_item(scroll + choice, choice, TRUE);

			prपूर्णांक_arrows(dialog, item_count(), scroll,
				     box_y, box_x + item_x + 1, menu_height);

			wnoutrefresh(dialog);
			wrefresh(menu);

			जारी;	/* रुको क्रम another key press */
		पूर्ण

		चयन (key) अणु
		हाल KEY_LEFT:
		हाल TAB:
		हाल KEY_RIGHT:
			button = ((key == KEY_LEFT ? --button : ++button) < 0)
			    ? 4 : (button > 4 ? 0 : button);

			prपूर्णांक_buttons(dialog, height, width, button);
			wrefresh(menu);
			अवरोध;
		हाल ' ':
		हाल 's':
		हाल 'y':
		हाल 'n':
		हाल 'm':
		हाल '/':
		हाल 'h':
		हाल '?':
		हाल 'z':
		हाल '\n':
			/* save scroll info */
			*s_scroll = scroll;
			delwin(menu);
			delwin(dialog);
			item_set(scroll + choice);
			item_set_selected(1);
			चयन (key) अणु
			हाल 'h':
			हाल '?':
				वापस 2;
			हाल 's':
			हाल 'y':
				वापस 5;
			हाल 'n':
				वापस 6;
			हाल 'm':
				वापस 7;
			हाल ' ':
				वापस 8;
			हाल '/':
				वापस 9;
			हाल 'z':
				वापस 10;
			हाल '\n':
				वापस button;
			पूर्ण
			वापस 0;
		हाल 'e':
		हाल 'x':
			key = KEY_ESC;
			अवरोध;
		हाल KEY_ESC:
			key = on_key_esc(menu);
			अवरोध;
		हाल KEY_RESIZE:
			on_key_resize();
			delwin(menu);
			delwin(dialog);
			जाओ करो_resize;
		पूर्ण
	पूर्ण
	delwin(menu);
	delwin(dialog);
	वापस key;		/* ESC pressed */
पूर्ण
