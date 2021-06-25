<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <sys/select.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <संकेत.स>
#समावेश <sys/ioctl.h>
#समावेश "pager.h"
#समावेश "run-command.h"
#समावेश "sigchain.h"
#समावेश "subcmd-config.h"

/*
 * This is split up from the rest of git so that we can करो
 * something dअगरferent on Winकरोws.
 */

अटल पूर्णांक spawned_pager;
अटल पूर्णांक pager_columns;

व्योम pager_init(स्थिर अक्षर *pager_env)
अणु
	subcmd_config.pager_env = pager_env;
पूर्ण

अटल स्थिर अक्षर *क्रमced_pager;

व्योम क्रमce_pager(स्थिर अक्षर *pager)
अणु
	क्रमced_pager = pager;
पूर्ण

अटल व्योम pager_preexec(व्योम)
अणु
	/*
	 * Work around bug in "less" by not starting it until we
	 * have real input
	 */
	fd_set in;
	fd_set exception;

	FD_ZERO(&in);
	FD_ZERO(&exception);
	FD_SET(0, &in);
	FD_SET(0, &exception);
	select(1, &in, शून्य, &exception, शून्य);

	setenv("LESS", "FRSX", 0);
पूर्ण

अटल स्थिर अक्षर *pager_argv[] = अणु "sh", "-c", शून्य, शून्य पूर्ण;
अटल काष्ठा child_process pager_process;

अटल व्योम रुको_क्रम_pager(व्योम)
अणु
	ख_साफ(मानक_निकास);
	ख_साफ(मानक_त्रुटि);
	/* संकेत खातापूर्ण to pager */
	बंद(1);
	बंद(2);
	finish_command(&pager_process);
पूर्ण

अटल व्योम रुको_क्रम_pager_संकेत(पूर्णांक signo)
अणु
	रुको_क्रम_pager();
	sigchain_pop(signo);
	उठाओ(signo);
पूर्ण

व्योम setup_pager(व्योम)
अणु
	स्थिर अक्षर *pager = दो_पर्या(subcmd_config.pager_env);
	काष्ठा winsize sz;

	अगर (क्रमced_pager)
		pager = क्रमced_pager;
	अगर (!isatty(1) && !क्रमced_pager)
		वापस;
	अगर (ioctl(1, TIOCGWINSZ, &sz) == 0)
		pager_columns = sz.ws_col;
	अगर (!pager)
		pager = दो_पर्या("PAGER");
	अगर (!(pager || access("/usr/bin/pager", X_OK)))
		pager = "/usr/bin/pager";
	अगर (!(pager || access("/usr/bin/less", X_OK)))
		pager = "/usr/bin/less";
	अगर (!pager)
		pager = "cat";
	अगर (!*pager || !म_भेद(pager, "cat"))
		वापस;

	spawned_pager = 1; /* means we are emitting to terminal */

	/* spawn the pager */
	pager_argv[2] = pager;
	pager_process.argv = pager_argv;
	pager_process.in = -1;
	pager_process.preexec_cb = pager_preexec;

	अगर (start_command(&pager_process))
		वापस;

	/* original process जारीs, but ग_लिखोs to the pipe */
	dup2(pager_process.in, 1);
	अगर (isatty(2))
		dup2(pager_process.in, 2);
	बंद(pager_process.in);

	/* this makes sure that the parent terminates after the pager */
	sigchain_push_common(रुको_क्रम_pager_संकेत);
	निकास_पर(रुको_क्रम_pager);
पूर्ण

पूर्णांक pager_in_use(व्योम)
अणु
	वापस spawned_pager;
पूर्ण

पूर्णांक pager_get_columns(व्योम)
अणु
	अक्षर *s;

	s = दो_पर्या("COLUMNS");
	अगर (s)
		वापस म_से_प(s);

	वापस (pager_columns ? pager_columns : 80) - 2;
पूर्ण
