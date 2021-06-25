<शैली गुरु>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <stdbool.h>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <linux/kernel.h>
#अगर_घोषित HAVE_BACKTRACE_SUPPORT
#समावेश <execinfo.h>
#पूर्ण_अगर

#समावेश "../../util/debug.h"
#समावेश "../../perf.h"
#समावेश "../browser.h"
#समावेश "../helpline.h"
#समावेश "../ui.h"
#समावेश "../util.h"
#समावेश "../libslang.h"
#समावेश "../keysyms.h"
#समावेश "tui.h"

अटल अस्थिर पूर्णांक ui__need_resize;

बाह्य काष्ठा perf_error_ops perf_tui_eops;
बाह्य bool tui_helpline__set;

बाह्य व्योम hist_browser__init_hpp(व्योम);

व्योम ui__refresh_dimensions(bool क्रमce)
अणु
	अगर (क्रमce || ui__need_resize) अणु
		ui__need_resize = 0;
		pthपढ़ो_mutex_lock(&ui__lock);
		SLtt_get_screen_size();
		SLsmg_reinit_smg();
		pthपढ़ो_mutex_unlock(&ui__lock);
	पूर्ण
पूर्ण

अटल व्योम ui__sigwinch(पूर्णांक sig __maybe_unused)
अणु
	ui__need_resize = 1;
पूर्ण

अटल व्योम ui__setup_sigwinch(व्योम)
अणु
	अटल bool करोne;

	अगर (करोne)
		वापस;

	करोne = true;
	pthपढ़ो__unblock_sigwinch();
	संकेत(SIGWINCH, ui__sigwinch);
पूर्ण

पूर्णांक ui__अ_लोh(पूर्णांक delay_secs)
अणु
	काष्ठा समयval समयout, *pसमयout = delay_secs ? &समयout : शून्य;
	fd_set पढ़ो_set;
	पूर्णांक err, key;

	ui__setup_sigwinch();

	FD_ZERO(&पढ़ो_set);
	FD_SET(0, &पढ़ो_set);

	अगर (delay_secs) अणु
		समयout.tv_sec = delay_secs;
		समयout.tv_usec = 0;
	पूर्ण

        err = select(1, &पढ़ो_set, शून्य, शून्य, pसमयout);

	अगर (err == 0)
		वापस K_TIMER;

	अगर (err == -1) अणु
		अगर (त्रुटि_सं == EINTR)
			वापस K_RESIZE;
		वापस K_ERROR;
	पूर्ण

	key = SLang_getkey();
	अगर (key != K_ESC)
		वापस key;

	FD_ZERO(&पढ़ो_set);
	FD_SET(0, &पढ़ो_set);
	समयout.tv_sec = 0;
	समयout.tv_usec = 20;
        err = select(1, &पढ़ो_set, शून्य, शून्य, &समयout);
	अगर (err == 0)
		वापस K_ESC;

	SLang_ungetkey(key);
	वापस SLkp_getkey();
पूर्ण

#अगर_घोषित HAVE_BACKTRACE_SUPPORT
अटल व्योम ui__संकेत_backtrace(पूर्णांक sig)
अणु
	व्योम *stackdump[32];
	माप_प्रकार size;

	ui__निकास(false);
	pसंकेत(sig, "perf");

	म_लिखो("-------- backtrace --------\n");
	size = backtrace(stackdump, ARRAY_SIZE(stackdump));
	backtrace_symbols_fd(stackdump, size, STDOUT_खाताNO);

	निकास(0);
पूर्ण
#अन्यथा
# define ui__संकेत_backtrace  ui__संकेत
#पूर्ण_अगर

अटल व्योम ui__संकेत(पूर्णांक sig)
अणु
	ui__निकास(false);
	pसंकेत(sig, "perf");
	निकास(0);
पूर्ण

पूर्णांक ui__init(व्योम)
अणु
	पूर्णांक err;

	SLutf8_enable(-1);
	SLtt_get_terminfo();
	SLtt_get_screen_size();

	err = SLsmg_init_smg();
	अगर (err < 0)
		जाओ out;
	err = SLang_init_tty(-1, 0, 0);
	अगर (err < 0)
		जाओ out;

	err = SLkp_init();
	अगर (err < 0) अणु
		pr_err("TUI initialization failed.\n");
		जाओ out;
	पूर्ण

	SLkp_define_keysym((अक्षर *)"^(kB)", SL_KEY_UNTAB);

	संकेत(संक_अंश, ui__संकेत_backtrace);
	संकेत(संक_भ_त्रुटि, ui__संकेत_backtrace);
	संकेत(संक_विघ्न, ui__संकेत);
	संकेत(SIGQUIT, ui__संकेत);
	संकेत(संक_इति, ui__संकेत);

	perf_error__रेजिस्टर(&perf_tui_eops);

	ui_helpline__init();
	ui_browser__init();
	tui_progress__init();

	hist_browser__init_hpp();
out:
	वापस err;
पूर्ण

व्योम ui__निकास(bool रुको_क्रम_ok)
अणु
	अगर (रुको_क्रम_ok && tui_helpline__set)
		ui__question_winकरोw("Fatal Error",
				    ui_helpline__last_msg,
				    "Press any key...", 0);

	SLtt_set_cursor_visibility(1);
	SLsmg_refresh();
	SLsmg_reset_smg();
	SLang_reset_tty();

	perf_error__unरेजिस्टर(&perf_tui_eops);
पूर्ण
