<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "term.h"
#समावेश <मानककोष.स>
#समावेश <termios.h>
#समावेश <unistd.h>
#समावेश <sys/ioctl.h>

व्योम get_term_dimensions(काष्ठा winsize *ws)
अणु
	अक्षर *s = दो_पर्या("LINES");

	अगर (s != शून्य) अणु
		ws->ws_row = म_से_प(s);
		s = दो_पर्या("COLUMNS");
		अगर (s != शून्य) अणु
			ws->ws_col = म_से_प(s);
			अगर (ws->ws_row && ws->ws_col)
				वापस;
		पूर्ण
	पूर्ण
#अगर_घोषित TIOCGWINSZ
	अगर (ioctl(1, TIOCGWINSZ, ws) == 0 &&
	    ws->ws_row && ws->ws_col)
		वापस;
#पूर्ण_अगर
	ws->ws_row = 25;
	ws->ws_col = 80;
पूर्ण

व्योम set_term_quiet_input(काष्ठा termios *old)
अणु
	काष्ठा termios tc;

	tcgetattr(0, old);
	tc = *old;
	tc.c_lflag &= ~(ICANON | ECHO);
	tc.c_cc[VMIN] = 0;
	tc.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &tc);
पूर्ण
