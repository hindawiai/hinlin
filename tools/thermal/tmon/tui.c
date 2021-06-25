<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * tui.c ncurses text user पूर्णांकerface क्रम TMON program
 *
 * Copyright (C) 2013 Intel Corporation. All rights reserved.
 *
 * Author: Jacob Pan <jacob.jun.pan@linux.पूर्णांकel.com>
 */

#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानक_निवेशt.h>
#समावेश <ncurses.h>
#समावेश <समय.स>
#समावेश <syslog.h>
#समावेश <panel.h>
#समावेश <pthपढ़ो.h>
#समावेश <संकेत.स>

#समावेश "tmon.h"

#घोषणा min(x, y) (अणु				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(व्योम) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; पूर्ण)

#घोषणा max(x, y) (अणु				\
	typeof(x) _max1 = (x);			\
	typeof(y) _max2 = (y);			\
	(व्योम) (&_max1 == &_max2);		\
	_max1 > _max2 ? _max1 : _max2; पूर्ण)

अटल PANEL *data_panel;
अटल PANEL *dialogue_panel;
अटल PANEL *top;

अटल WINDOW *title_bar_winकरोw;
अटल WINDOW *tz_sensor_winकरोw;
अटल WINDOW *cooling_device_winकरोw;
अटल WINDOW *control_winकरोw;
अटल WINDOW *status_bar_winकरोw;
अटल WINDOW *thermal_data_winकरोw;
अटल WINDOW *dialogue_winकरोw;

अक्षर status_bar_slots[10][40];
अटल व्योम draw_hbar(WINDOW *win, पूर्णांक y, पूर्णांक start, पूर्णांक len,
		अचिन्हित दीर्घ pattern, bool end);

अटल पूर्णांक maxx, maxy;
अटल पूर्णांक maxwidth = 200;

#घोषणा TITLE_BAR_HIGHT 1
#घोषणा SENSOR_WIN_HIGHT 4 /* one row क्रम tz name, one क्रम trip poपूर्णांकs */


/* daemon mode flag (set by startup parameter -d) */
अटल पूर्णांक  tui_disabled;

अटल व्योम बंद_panel(PANEL *p)
अणु
	अगर (p) अणु
		del_panel(p);
		p = शून्य;
	पूर्ण
पूर्ण

अटल व्योम बंद_winकरोw(WINDOW *win)
अणु
	अगर (win) अणु
		delwin(win);
		win = शून्य;
	पूर्ण
पूर्ण

व्योम बंद_winकरोws(व्योम)
अणु
	अगर (tui_disabled)
		वापस;
	/* must delete panels beक्रमe their attached winकरोws */
	अगर (dialogue_winकरोw)
		बंद_panel(dialogue_panel);
	अगर (cooling_device_winकरोw)
		बंद_panel(data_panel);

	बंद_winकरोw(title_bar_winकरोw);
	बंद_winकरोw(tz_sensor_winकरोw);
	बंद_winकरोw(status_bar_winकरोw);
	बंद_winकरोw(cooling_device_winकरोw);
	बंद_winकरोw(control_winकरोw);
	बंद_winकरोw(thermal_data_winकरोw);
	बंद_winकरोw(dialogue_winकरोw);

पूर्ण

व्योम ग_लिखो_status_bar(पूर्णांक x, अक्षर *line)
अणु
	mvwprपूर्णांकw(status_bar_winकरोw, 0, x, "%s", line);
	wrefresh(status_bar_winकरोw);
पूर्ण

/* wrap at 5 */
#घोषणा DIAG_DEV_ROWS  5
/*
 * list cooling devices + "set temp" entry; wraps after 5 rows, अगर they fit
 */
अटल पूर्णांक diag_dev_rows(व्योम)
अणु
	पूर्णांक entries = ptdata.nr_cooling_dev + 1;
	पूर्णांक rows = max(DIAG_DEV_ROWS, (entries + 1) / 2);
	वापस min(rows, entries);
पूर्ण

व्योम setup_winकरोws(व्योम)
अणु
	पूर्णांक y_begin = 1;

	अगर (tui_disabled)
		वापस;

	geपंचांगaxyx(stdscr, maxy, maxx);
	resizeterm(maxy, maxx);

	title_bar_winकरोw = subwin(stdscr, TITLE_BAR_HIGHT, maxx, 0, 0);
	y_begin += TITLE_BAR_HIGHT;

	tz_sensor_winकरोw = subwin(stdscr, SENSOR_WIN_HIGHT, maxx, y_begin, 0);
	y_begin += SENSOR_WIN_HIGHT;

	cooling_device_winकरोw = subwin(stdscr, ptdata.nr_cooling_dev + 3, maxx,
				y_begin, 0);
	y_begin += ptdata.nr_cooling_dev + 3; /* 2 lines क्रम border */
	/* two lines to show borders, one line per tz show trip poपूर्णांक position
	 * and value.
	 * dialogue winकरोw is a pop-up, when needed it lays on top of cdev win
	 */

	dialogue_winकरोw = subwin(stdscr, diag_dev_rows() + 5, maxx-50,
				DIAG_Y, DIAG_X);

	thermal_data_winकरोw = subwin(stdscr, ptdata.nr_tz_sensor *
				NR_LINES_TZDATA + 3, maxx, y_begin, 0);
	y_begin += ptdata.nr_tz_sensor * NR_LINES_TZDATA + 3;
	control_winकरोw = subwin(stdscr, 4, maxx, y_begin, 0);

	scrollok(cooling_device_winकरोw, TRUE);
	maxwidth = maxx - 18;
	status_bar_winकरोw = subwin(stdscr, 1, maxx, maxy-1, 0);

	म_नकल(status_bar_slots[0], " Ctrl-c - Quit ");
	म_नकल(status_bar_slots[1], " TAB - Tuning ");
	wmove(status_bar_winकरोw, 1, 30);

	/* prepare panels क्रम dialogue, अगर panel alपढ़ोy created then we must
	 * be करोing resizing, so just replace winकरोws with new ones, old ones
	 * should have been deleted by बंद_winकरोw
	 */
	data_panel = new_panel(cooling_device_winकरोw);
	अगर (!data_panel)
		syslog(LOG_DEBUG, "No data panel\n");
	अन्यथा अणु
		अगर (dialogue_winकरोw) अणु
			dialogue_panel = new_panel(dialogue_winकरोw);
			अगर (!dialogue_panel)
				syslog(LOG_DEBUG, "No dialogue panel\n");
			अन्यथा अणु
				/* Set up the user poपूर्णांकer to the next panel*/
				set_panel_userptr(data_panel, dialogue_panel);
				set_panel_userptr(dialogue_panel, data_panel);
				top = data_panel;
			पूर्ण
		पूर्ण अन्यथा
			syslog(LOG_INFO, "no dialogue win, term too small\n");
	पूर्ण
	करोupdate();
	werase(stdscr);
	refresh();
पूर्ण

व्योम resize_handler(पूर्णांक sig)
अणु
	/* start over when term माला_लो resized, but first we clean up */
	बंद_winकरोws();
	endwin();
	refresh();
	clear();
	geपंचांगaxyx(stdscr, maxy, maxx);  /* get the new screen size */
	setup_winकरोws();
	/* rate limit */
	sleep(1);
	syslog(LOG_DEBUG, "SIG %d, term resized to %d x %d\n",
		sig, maxy, maxx);
	संकेत(SIGWINCH, resize_handler);
पूर्ण

स्थिर अक्षर cdev_title[] = " COOLING DEVICES ";
व्योम show_cooling_device(व्योम)
अणु
	पूर्णांक i, j, x, y = 0;

	अगर (tui_disabled || !cooling_device_winकरोw)
		वापस;

	werase(cooling_device_winकरोw);
	wattron(cooling_device_winकरोw, A_BOLD);
	mvwprपूर्णांकw(cooling_device_winकरोw,  1, 1,
		"ID  Cooling Dev   Cur    Max   Thermal Zone Binding");
	wattroff(cooling_device_winकरोw, A_BOLD);
	क्रम (j = 0; j <	ptdata.nr_cooling_dev; j++) अणु
		/* draw cooling device list on the left in the order of
		 * cooling device instances. skip unused idr.
		 */
		mvwprपूर्णांकw(cooling_device_winकरोw, j + 2, 1,
			"%02d %12.12s%6d %6d",
			ptdata.cdi[j].instance,
			ptdata.cdi[j].type,
			ptdata.cdi[j].cur_state,
			ptdata.cdi[j].max_state);
	पूर्ण

	/* show cdev binding, y is the global cooling device instance */
	क्रम (i = 0; i < ptdata.nr_tz_sensor; i++) अणु
		पूर्णांक tz_inst = ptdata.tzi[i].instance;
		क्रम (j = 0; j < ptdata.nr_cooling_dev; j++) अणु
			पूर्णांक cdev_inst;
			y = j;
			x = tz_inst * TZONE_RECORD_SIZE + TZ_LEFT_ALIGN;

			draw_hbar(cooling_device_winकरोw, y+2, x,
				TZONE_RECORD_SIZE-1, ACS_VLINE, false);

			/* draw a column of spaces to separate thermal zones */
			mvwprपूर्णांकw(cooling_device_winकरोw, y+2, x-1, " ");
			अगर (ptdata.tzi[i].cdev_binding) अणु
				cdev_inst = ptdata.cdi[j].instance;
				अचिन्हित दीर्घ trip_binding =
					ptdata.tzi[i].trip_binding[cdev_inst];
				पूर्णांक k = 0; /* per zone trip poपूर्णांक id that
					    * binded to this cdev, one to
					    * many possible based on the
					    * binding biपंचांगask.
					    */
				syslog(LOG_DEBUG,
					"bind tz%d cdev%d tp%lx %d cdev%lx\n",
					i, j, trip_binding, y,
					ptdata.tzi[i].cdev_binding);
				/* draw each trip binding क्रम the cdev */
				जबतक (trip_binding >>= 1) अणु
					k++;
					अगर (!(trip_binding & 1))
						जारी;
					/* draw '*' to show binding */
					mvwprपूर्णांकw(cooling_device_winकरोw,
						y + 2,
						x + ptdata.tzi[i].nr_trip_pts -
						k - 1, "*");
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/* draw border after data so that border will not be messed up
	 * even there is not enough space क्रम all the data to be shown
	 */
	wborder(cooling_device_winकरोw, 0, 0, 0, 0, 0, 0, 0, 0);
	wattron(cooling_device_winकरोw, A_BOLD);
	mvwprपूर्णांकw(cooling_device_winकरोw, 0, maxx/2 - माप(cdev_title),
		cdev_title);
	wattroff(cooling_device_winकरोw, A_BOLD);

	wrefresh(cooling_device_winकरोw);
पूर्ण

स्थिर अक्षर DIAG_TITLE[] = "[ TUNABLES ]";
व्योम show_dialogue(व्योम)
अणु
	पूर्णांक j, x = 0, y = 0;
	पूर्णांक rows, cols;
	WINDOW *w = dialogue_winकरोw;

	अगर (tui_disabled || !w)
		वापस;

	geपंचांगaxyx(w, rows, cols);

	/* Silence compiler 'unused' warnings */
	(व्योम)cols;

	werase(w);
	box(w, 0, 0);
	mvwprपूर्णांकw(w, 0, maxx/4, DIAG_TITLE);
	/* list all the available tunables */
	क्रम (j = 0; j <= ptdata.nr_cooling_dev; j++) अणु
		y = j % diag_dev_rows();
		अगर (y == 0 && j != 0)
			x += 20;
		अगर (j == ptdata.nr_cooling_dev)
			/* save last choice क्रम target temp */
			mvwprपूर्णांकw(w, y+1, x+1, "%C-%.12s", 'A'+j, "Set Temp");
		अन्यथा
			mvwprपूर्णांकw(w, y+1, x+1, "%C-%.10s-%2d", 'A'+j,
				ptdata.cdi[j].type, ptdata.cdi[j].instance);
	पूर्ण
	wattron(w, A_BOLD);
	mvwprपूर्णांकw(w, diag_dev_rows()+1, 1, "Enter Choice [A-Z]?");
	wattroff(w, A_BOLD);
	/* prपूर्णांक legend at the bottom line */
	mvwprपूर्णांकw(w, rows - 2, 1,
		"Legend: A=Active, P=Passive, C=Critical");

	wrefresh(dialogue_winकरोw);
पूर्ण

व्योम ग_लिखो_dialogue_win(अक्षर *buf, पूर्णांक y, पूर्णांक x)
अणु
	WINDOW *w = dialogue_winकरोw;

	mvwprपूर्णांकw(w, y, x, "%s", buf);
पूर्ण

स्थिर अक्षर control_title[] = " CONTROLS ";
व्योम show_control_w(व्योम)
अणु
	अचिन्हित दीर्घ state;

	get_ctrl_state(&state);

	अगर (tui_disabled || !control_winकरोw)
		वापस;

	werase(control_winकरोw);
	mvwprपूर्णांकw(control_winकरोw, 1, 1,
		"PID gain: kp=%2.2f ki=%2.2f kd=%2.2f Output %2.2f",
		p_param.kp, p_param.ki, p_param.kd, p_param.y_k);

	mvwprपूर्णांकw(control_winकरोw, 2, 1,
		"Target Temp: %2.1fC, Zone: %d, Control Device: %.12s",
		p_param.t_target, target_thermal_zone, ctrl_cdev);

	/* draw border last such that everything is within boundary */
	wborder(control_winकरोw, 0, 0, 0, 0, 0, 0, 0, 0);
	wattron(control_winकरोw, A_BOLD);
	mvwprपूर्णांकw(control_winकरोw, 0, maxx/2 - माप(control_title),
		control_title);
	wattroff(control_winकरोw, A_BOLD);

	wrefresh(control_winकरोw);
पूर्ण

व्योम initialize_curses(व्योम)
अणु
	अगर (tui_disabled)
		वापस;

	initscr();
	start_color();
	keypad(stdscr, TRUE);	/* enable keyboard mapping */
	nonl();			/* tell curses not to करो NL->CR/NL on output */
	cअवरोध();		/* take input अक्षरs one at a समय */
	noecho();		/* करोnt echo input */
	curs_set(0);		/* turn off cursor */
	use_शेष_colors();

	init_pair(PT_COLOR_DEFAULT, COLOR_WHITE, COLOR_BLACK);
	init_pair(PT_COLOR_HEADER_BAR, COLOR_BLACK, COLOR_WHITE);
	init_pair(PT_COLOR_ERROR, COLOR_BLACK, COLOR_RED);
	init_pair(PT_COLOR_RED, COLOR_WHITE, COLOR_RED);
	init_pair(PT_COLOR_YELLOW, COLOR_WHITE, COLOR_YELLOW);
	init_pair(PT_COLOR_GREEN, COLOR_WHITE, COLOR_GREEN);
	init_pair(PT_COLOR_BLUE, COLOR_WHITE, COLOR_BLUE);
	init_pair(PT_COLOR_BRIGHT, COLOR_WHITE, COLOR_BLACK);

पूर्ण

व्योम show_title_bar(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक x = 0;

	अगर (tui_disabled || !title_bar_winकरोw)
		वापस;

	wattrset(title_bar_winकरोw, COLOR_PAIR(PT_COLOR_HEADER_BAR));
	wbkgd(title_bar_winकरोw, COLOR_PAIR(PT_COLOR_HEADER_BAR));
	werase(title_bar_winकरोw);

	mvwprपूर्णांकw(title_bar_winकरोw, 0, 0,
		"     TMON v%s", VERSION);

	wrefresh(title_bar_winकरोw);

	werase(status_bar_winकरोw);

	क्रम (i = 0; i < 10; i++) अणु
		अगर (म_माप(status_bar_slots[i]) == 0)
			जारी;
		wattron(status_bar_winकरोw, A_REVERSE);
		mvwprपूर्णांकw(status_bar_winकरोw, 0, x, "%s", status_bar_slots[i]);
		wattroff(status_bar_winकरोw, A_REVERSE);
		x += म_माप(status_bar_slots[i]) + 1;
	पूर्ण
	wrefresh(status_bar_winकरोw);
पूर्ण

अटल व्योम handle_input_val(पूर्णांक ch)
अणु
	अक्षर buf[32];
	पूर्णांक val;
	अक्षर path[256];
	WINDOW *w = dialogue_winकरोw;

	echo();
	keypad(w, TRUE);
	wgetnstr(w, buf, 31);
	val = म_से_प(buf);

	अगर (ch == ptdata.nr_cooling_dev) अणु
		snम_लिखो(buf, 31, "Invalid Temp %d! %d-%d", val,
			MIN_CTRL_TEMP, MAX_CTRL_TEMP);
		अगर (val < MIN_CTRL_TEMP || val > MAX_CTRL_TEMP)
			ग_लिखो_status_bar(40, buf);
		अन्यथा अणु
			p_param.t_target = val;
			snम_लिखो(buf, 31, "Set New Target Temp %d", val);
			ग_लिखो_status_bar(40, buf);
		पूर्ण
	पूर्ण अन्यथा अणु
		snम_लिखो(path, 256, "%s/%s%d", THERMAL_SYSFS,
			CDEV, ptdata.cdi[ch].instance);
		sysfs_set_uदीर्घ(path, "cur_state", val);
	पूर्ण
	noecho();
	dialogue_on = 0;
	show_data_w();
	show_control_w();

	top = (PANEL *)panel_userptr(top);
	top_panel(top);
पूर्ण

अटल व्योम handle_input_choice(पूर्णांक ch)
अणु
	अक्षर buf[48];
	पूर्णांक base = 0;
	पूर्णांक cdev_id = 0;

	अगर ((ch >= 'A' && ch <= 'A' + ptdata.nr_cooling_dev) ||
		(ch >= 'a' && ch <= 'a' + ptdata.nr_cooling_dev)) अणु
		base = (ch < 'a') ? 'A' : 'a';
		cdev_id = ch - base;
		अगर (ptdata.nr_cooling_dev == cdev_id)
			snम_लिखो(buf, माप(buf), "New Target Temp:");
		अन्यथा
			snम_लिखो(buf, माप(buf), "New Value for %.10s-%2d: ",
				ptdata.cdi[cdev_id].type,
				ptdata.cdi[cdev_id].instance);
		ग_लिखो_dialogue_win(buf, diag_dev_rows() + 2, 2);
		handle_input_val(cdev_id);
	पूर्ण अन्यथा अणु
		snम_लिखो(buf, माप(buf), "Invalid selection %d", ch);
		ग_लिखो_dialogue_win(buf, 8, 2);
	पूर्ण
पूर्ण

व्योम *handle_tui_events(व्योम *arg)
अणु
	पूर्णांक ch;

	keypad(cooling_device_winकरोw, TRUE);
	जबतक ((ch = wअ_लोh(cooling_device_winकरोw)) != खातापूर्ण) अणु
		अगर (पंचांगon_निकास)
			अवरोध;
		/* when term size is too small, no dialogue panels are set.
		 * we need to filter out such हालs.
		 */
		अगर (!data_panel || !dialogue_panel ||
			!cooling_device_winकरोw ||
			!dialogue_winकरोw) अणु

			जारी;
		पूर्ण
		pthपढ़ो_mutex_lock(&input_lock);
		अगर (dialogue_on) अणु
			handle_input_choice(ch);
			/* top panel filter */
			अगर (ch == 'q' || ch == 'Q')
				ch = 0;
		पूर्ण
		चयन (ch) अणु
		हाल KEY_LEFT:
			box(cooling_device_winकरोw, 10, 0);
			अवरोध;
		हाल 9: /* TAB */
			top = (PANEL *)panel_userptr(top);
			top_panel(top);
			अगर (top == dialogue_panel) अणु
				dialogue_on = 1;
				show_dialogue();
			पूर्ण अन्यथा अणु
				dialogue_on = 0;
				/* क्रमce refresh */
				show_data_w();
				show_control_w();
			पूर्ण
			अवरोध;
		हाल 'q':
		हाल 'Q':
			पंचांगon_निकास = 1;
			अवरोध;
		पूर्ण
		update_panels();
		करोupdate();
		pthपढ़ो_mutex_unlock(&input_lock);
	पूर्ण

	अगर (arg)
		*(पूर्णांक *)arg = 0; /* make gcc happy */

	वापस शून्य;
पूर्ण

/* draw a horizontal bar in given pattern */
अटल व्योम draw_hbar(WINDOW *win, पूर्णांक y, पूर्णांक start, पूर्णांक len, अचिन्हित दीर्घ ptn,
		bool end)
अणु
	mvwaddch(win, y, start, ptn);
	whline(win, ptn, len);
	अगर (end)
		mvwaddch(win, y, MAX_DISP_TEMP+TDATA_LEFT, ']');
पूर्ण

अटल अक्षर trip_type_to_अक्षर(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल THERMAL_TRIP_CRITICAL: वापस 'C';
	हाल THERMAL_TRIP_HOT: वापस 'H';
	हाल THERMAL_TRIP_PASSIVE: वापस 'P';
	हाल THERMAL_TRIP_ACTIVE: वापस 'A';
	शेष:
		वापस '?';
	पूर्ण
पूर्ण

/* fill a string with trip poपूर्णांक type and value in one line
 * e.g.      P(56)    C(106)
 * मुख्यtain the distance one degree per अक्षर
 */
अटल व्योम draw_tp_line(पूर्णांक tz, पूर्णांक y)
अणु
	पूर्णांक j;
	पूर्णांक x;

	क्रम (j = 0; j < ptdata.tzi[tz].nr_trip_pts; j++) अणु
		x = ptdata.tzi[tz].tp[j].temp / 1000;
		mvwprपूर्णांकw(thermal_data_winकरोw, y + 0, x + TDATA_LEFT,
			"%c%d", trip_type_to_अक्षर(ptdata.tzi[tz].tp[j].type),
			x);
		syslog(LOG_INFO, "%s:tz %d tp %d temp = %lu\n", __func__,
			tz, j, ptdata.tzi[tz].tp[j].temp);
	पूर्ण
पूर्ण

स्थिर अक्षर data_win_title[] = " THERMAL DATA ";
व्योम show_data_w(व्योम)
अणु
	पूर्णांक i;


	अगर (tui_disabled || !thermal_data_winकरोw)
		वापस;

	werase(thermal_data_winकरोw);
	wattron(thermal_data_winकरोw, A_BOLD);
	mvwprपूर्णांकw(thermal_data_winकरोw, 0, maxx/2 - माप(data_win_title),
		data_win_title);
	wattroff(thermal_data_winकरोw, A_BOLD);
	/* draw a line as ruler */
	क्रम (i = 10; i < MAX_DISP_TEMP; i += 10)
		mvwprपूर्णांकw(thermal_data_winकरोw, 1, i+TDATA_LEFT, "%2d", i);

	क्रम (i = 0; i < ptdata.nr_tz_sensor; i++) अणु
		पूर्णांक temp = trec[cur_thermal_record].temp[i] / 1000;
		पूर्णांक y = 0;

		y = i * NR_LINES_TZDATA + 2;
		/* y at tz temp data line */
		mvwprपूर्णांकw(thermal_data_winकरोw, y, 1, "%6.6s%2d:[%3d][",
			ptdata.tzi[i].type,
			ptdata.tzi[i].instance, temp);
		draw_hbar(thermal_data_winकरोw, y, TDATA_LEFT, temp, ACS_RARROW,
			true);
		draw_tp_line(i, y);
	पूर्ण
	wborder(thermal_data_winकरोw, 0, 0, 0, 0, 0, 0, 0, 0);
	wrefresh(thermal_data_winकरोw);
पूर्ण

स्थिर अक्षर tz_title[] = "THERMAL ZONES(SENSORS)";

व्योम show_sensors_w(व्योम)
अणु
	पूर्णांक i, j;
	अक्षर buffer[512];

	अगर (tui_disabled || !tz_sensor_winकरोw)
		वापस;

	werase(tz_sensor_winकरोw);

	स_रखो(buffer, 0, माप(buffer));
	wattron(tz_sensor_winकरोw, A_BOLD);
	mvwprपूर्णांकw(tz_sensor_winकरोw, 1, 1, "Thermal Zones:");
	wattroff(tz_sensor_winकरोw, A_BOLD);

	mvwprपूर्णांकw(tz_sensor_winकरोw, 1, TZ_LEFT_ALIGN, "%s", buffer);
	/* fill trip poपूर्णांकs क्रम each tzone */
	wattron(tz_sensor_winकरोw, A_BOLD);
	mvwprपूर्णांकw(tz_sensor_winकरोw, 2, 1, "Trip Points:");
	wattroff(tz_sensor_winकरोw, A_BOLD);

	/* draw trip poपूर्णांक from low to high क्रम each tz */
	क्रम (i = 0; i < ptdata.nr_tz_sensor; i++) अणु
		पूर्णांक inst = ptdata.tzi[i].instance;

		mvwprपूर्णांकw(tz_sensor_winकरोw, 1,
			TZ_LEFT_ALIGN+TZONE_RECORD_SIZE * inst, "%.9s%02d",
			ptdata.tzi[i].type, ptdata.tzi[i].instance);
		क्रम (j = ptdata.tzi[i].nr_trip_pts - 1; j >= 0; j--) अणु
			/* loop through all trip poपूर्णांकs */
			अक्षर type;
			पूर्णांक tp_pos;
			/* reverse the order here since trips are sorted
			 * in ascending order in terms of temperature.
			 */
			tp_pos = ptdata.tzi[i].nr_trip_pts - j - 1;

			type = trip_type_to_अक्षर(ptdata.tzi[i].tp[j].type);
			mvwaddch(tz_sensor_winकरोw, 2,
				inst * TZONE_RECORD_SIZE + TZ_LEFT_ALIGN +
				tp_pos,	type);
			syslog(LOG_DEBUG, "draw tz %d tp %d ch:%c\n",
				inst, j, type);
		पूर्ण
	पूर्ण
	wborder(tz_sensor_winकरोw, 0, 0, 0, 0, 0, 0, 0, 0);
	wattron(tz_sensor_winकरोw, A_BOLD);
	mvwprपूर्णांकw(tz_sensor_winकरोw, 0, maxx/2 - माप(tz_title), tz_title);
	wattroff(tz_sensor_winकरोw, A_BOLD);
	wrefresh(tz_sensor_winकरोw);
पूर्ण

व्योम disable_tui(व्योम)
अणु
	tui_disabled = 1;
पूर्ण
