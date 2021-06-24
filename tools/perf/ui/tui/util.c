<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <संकेत.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <sys/ttyशेषs.h>

#समावेश "../browser.h"
#समावेश "../keysyms.h"
#समावेश "../helpline.h"
#समावेश "../ui.h"
#समावेश "../util.h"
#समावेश "../libslang.h"

अटल व्योम ui_browser__argv_ग_लिखो(काष्ठा ui_browser *browser,
				   व्योम *entry, पूर्णांक row)
अणु
	अक्षर **arg = entry;
	bool current_entry = ui_browser__is_current_entry(browser, row);

	ui_browser__set_color(browser, current_entry ? HE_COLORSET_SELECTED :
						       HE_COLORSET_NORMAL);
	ui_browser__ग_लिखो_nstring(browser, *arg, browser->width);
पूर्ण

अटल पूर्णांक popup_menu__run(काष्ठा ui_browser *menu, पूर्णांक *keyp)
अणु
	पूर्णांक key;

	अगर (ui_browser__show(menu, " ", "ESC: exit, ENTER|->: Select option") < 0)
		वापस -1;

	जबतक (1) अणु
		key = ui_browser__run(menu, 0);

		चयन (key) अणु
		हाल K_RIGHT:
		हाल K_ENTER:
			key = menu->index;
			अवरोध;
		हाल K_LEFT:
		हाल K_ESC:
		हाल 'q':
		हाल CTRL('c'):
			key = -1;
			अवरोध;
		शेष:
			अगर (keyp) अणु
				*keyp = key;
				key = menu->nr_entries;
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		अवरोध;
	पूर्ण

	ui_browser__hide(menu);
	वापस key;
पूर्ण

पूर्णांक ui__popup_menu(पूर्णांक argc, अक्षर * स्थिर argv[], पूर्णांक *keyp)
अणु
	काष्ठा ui_browser menu = अणु
		.entries    = (व्योम *)argv,
		.refresh    = ui_browser__argv_refresh,
		.seek	    = ui_browser__argv_seek,
		.ग_लिखो	    = ui_browser__argv_ग_लिखो,
		.nr_entries = argc,
	पूर्ण;
	वापस popup_menu__run(&menu, keyp);
पूर्ण

पूर्णांक ui_browser__input_winकरोw(स्थिर अक्षर *title, स्थिर अक्षर *text, अक्षर *input,
			     स्थिर अक्षर *निकास_msg, पूर्णांक delay_secs)
अणु
	पूर्णांक x, y, len, key;
	पूर्णांक max_len = 60, nr_lines = 0;
	अटल अक्षर buf[50];
	स्थिर अक्षर *t;

	t = text;
	जबतक (1) अणु
		स्थिर अक्षर *sep = म_अक्षर(t, '\n');

		अगर (sep == शून्य)
			sep = म_अक्षर(t, '\0');
		len = sep - t;
		अगर (max_len < len)
			max_len = len;
		++nr_lines;
		अगर (*sep == '\0')
			अवरोध;
		t = sep + 1;
	पूर्ण

	pthपढ़ो_mutex_lock(&ui__lock);

	max_len += 2;
	nr_lines += 8;
	y = SLtt_Screen_Rows / 2 - nr_lines / 2;
	x = SLtt_Screen_Cols / 2 - max_len / 2;

	SLsmg_set_color(0);
	SLsmg_draw_box(y, x++, nr_lines, max_len);
	अगर (title) अणु
		SLsmg_जाओrc(y, x + 1);
		SLsmg_ग_लिखो_string((अक्षर *)title);
	पूर्ण
	SLsmg_जाओrc(++y, x);
	nr_lines -= 7;
	max_len -= 2;
	SLsmg_ग_लिखो_wrapped_string((अचिन्हित अक्षर *)text, y, x,
				   nr_lines, max_len, 1);
	y += nr_lines;
	len = 5;
	जबतक (len--) अणु
		SLsmg_जाओrc(y + len - 1, x);
		SLsmg_ग_लिखो_nstring((अक्षर *)" ", max_len);
	पूर्ण
	SLsmg_draw_box(y++, x + 1, 3, max_len - 2);

	SLsmg_जाओrc(y + 3, x);
	SLsmg_ग_लिखो_nstring((अक्षर *)निकास_msg, max_len);
	SLsmg_refresh();

	pthपढ़ो_mutex_unlock(&ui__lock);

	x += 2;
	len = 0;
	key = ui__अ_लोh(delay_secs);
	जबतक (key != K_TIMER && key != K_ENTER && key != K_ESC) अणु
		pthपढ़ो_mutex_lock(&ui__lock);

		अगर (key == K_BKSPC) अणु
			अगर (len == 0) अणु
				pthपढ़ो_mutex_unlock(&ui__lock);
				जाओ next_key;
			पूर्ण
			SLsmg_जाओrc(y, x + --len);
			SLsmg_ग_लिखो_अक्षर(' ');
		पूर्ण अन्यथा अणु
			buf[len] = key;
			SLsmg_जाओrc(y, x + len++);
			SLsmg_ग_लिखो_अक्षर(key);
		पूर्ण
		SLsmg_refresh();

		pthपढ़ो_mutex_unlock(&ui__lock);

		/* XXX more graceful overflow handling needed */
		अगर (len == माप(buf) - 1) अणु
			ui_helpline__push("maximum size of symbol name reached!");
			key = K_ENTER;
			अवरोध;
		पूर्ण
next_key:
		key = ui__अ_लोh(delay_secs);
	पूर्ण

	buf[len] = '\0';
	म_नकलन(input, buf, len+1);
	वापस key;
पूर्ण

व्योम __ui__info_winकरोw(स्थिर अक्षर *title, स्थिर अक्षर *text, स्थिर अक्षर *निकास_msg)
अणु
	पूर्णांक x, y;
	पूर्णांक max_len = 0, nr_lines = 0;
	स्थिर अक्षर *t;

	t = text;
	जबतक (1) अणु
		स्थिर अक्षर *sep = म_अक्षर(t, '\n');
		पूर्णांक len;

		अगर (sep == शून्य)
			sep = म_अक्षर(t, '\0');
		len = sep - t;
		अगर (max_len < len)
			max_len = len;
		++nr_lines;
		अगर (*sep == '\0')
			अवरोध;
		t = sep + 1;
	पूर्ण

	max_len += 2;
	nr_lines += 2;
	अगर (निकास_msg)
		nr_lines += 2;
	y = SLtt_Screen_Rows / 2 - nr_lines / 2,
	x = SLtt_Screen_Cols / 2 - max_len / 2;

	SLsmg_set_color(0);
	SLsmg_draw_box(y, x++, nr_lines, max_len);
	अगर (title) अणु
		SLsmg_जाओrc(y, x + 1);
		SLsmg_ग_लिखो_string((अक्षर *)title);
	पूर्ण
	SLsmg_जाओrc(++y, x);
	अगर (निकास_msg)
		nr_lines -= 2;
	max_len -= 2;
	SLsmg_ग_लिखो_wrapped_string((अचिन्हित अक्षर *)text, y, x,
				   nr_lines, max_len, 1);
	अगर (निकास_msg) अणु
		SLsmg_जाओrc(y + nr_lines - 2, x);
		SLsmg_ग_लिखो_nstring((अक्षर *)" ", max_len);
		SLsmg_जाओrc(y + nr_lines - 1, x);
		SLsmg_ग_लिखो_nstring((अक्षर *)निकास_msg, max_len);
	पूर्ण
पूर्ण

व्योम ui__info_winकरोw(स्थिर अक्षर *title, स्थिर अक्षर *text)
अणु
	pthपढ़ो_mutex_lock(&ui__lock);
	__ui__info_winकरोw(title, text, शून्य);
	SLsmg_refresh();
	pthपढ़ो_mutex_unlock(&ui__lock);
पूर्ण

पूर्णांक ui__question_winकरोw(स्थिर अक्षर *title, स्थिर अक्षर *text,
			स्थिर अक्षर *निकास_msg, पूर्णांक delay_secs)
अणु
	pthपढ़ो_mutex_lock(&ui__lock);
	__ui__info_winकरोw(title, text, निकास_msg);
	SLsmg_refresh();
	pthपढ़ो_mutex_unlock(&ui__lock);
	वापस ui__अ_लोh(delay_secs);
पूर्ण

पूर्णांक ui__help_winकरोw(स्थिर अक्षर *text)
अणु
	वापस ui__question_winकरोw("Help", text, "Press any key...", 0);
पूर्ण

पूर्णांक ui__dialog_yesno(स्थिर अक्षर *msg)
अणु
	वापस ui__question_winकरोw(शून्य, msg, "Enter: Yes, ESC: No", 0);
पूर्ण

अटल पूर्णांक __ui__warning(स्थिर अक्षर *title, स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	अक्षर *s;

	अगर (vaप्र_लिखो(&s, क्रमmat, args) > 0) अणु
		पूर्णांक key;

		key = ui__question_winकरोw(title, s, "Press any key...", 0);
		मुक्त(s);
		वापस key;
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "%s\n", title);
	भख_लिखो(मानक_त्रुटि, क्रमmat, args);
	वापस K_ESC;
पूर्ण

अटल पूर्णांक perf_tui__error(स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	वापस __ui__warning("Error:", क्रमmat, args);
पूर्ण

अटल पूर्णांक perf_tui__warning(स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	वापस __ui__warning("Warning:", क्रमmat, args);
पूर्ण

काष्ठा perf_error_ops perf_tui_eops = अणु
	.error		= perf_tui__error,
	.warning	= perf_tui__warning,
पूर्ण;
