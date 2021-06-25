<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2013, Michael Ellerman, IBM Corp.
 */

#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>
#समावेश <elf.h>
#समावेश <fcntl.h>
#समावेश <link.h>
#समावेश <sys/स्थिति.स>

#समावेश "subunit.h"
#समावेश "utils.h"

#घोषणा KILL_TIMEOUT	5

/* Setting समयout to -1 disables the alarm */
अटल uपूर्णांक64_t समयout = 120;

पूर्णांक run_test(पूर्णांक (test_function)(व्योम), अक्षर *name)
अणु
	bool terminated;
	पूर्णांक rc, status;
	pid_t pid;

	/* Make sure output is flushed beक्रमe विभाजनing */
	ख_साफ(मानक_निकास);

	pid = विभाजन();
	अगर (pid == 0) अणु
		setpgid(0, 0);
		निकास(test_function());
	पूर्ण अन्यथा अगर (pid == -1) अणु
		लिखो_त्रुटि("fork");
		वापस 1;
	पूर्ण

	setpgid(pid, pid);

	अगर (समयout != -1)
		/* Wake us up in समयout seconds */
		alarm(समयout);
	terminated = false;

रुको:
	rc = रुकोpid(pid, &status, 0);
	अगर (rc == -1) अणु
		अगर (त्रुटि_सं != EINTR) अणु
			म_लिखो("unknown error from waitpid\n");
			वापस 1;
		पूर्ण

		अगर (terminated) अणु
			म_लिखो("!! force killing %s\n", name);
			समाप्त(-pid, SIGKILL);
			वापस 1;
		पूर्ण अन्यथा अणु
			म_लिखो("!! killing %s\n", name);
			समाप्त(-pid, संक_इति);
			terminated = true;
			alarm(KILL_TIMEOUT);
			जाओ रुको;
		पूर्ण
	पूर्ण

	/* Kill anything अन्यथा in the process group that is still running */
	समाप्त(-pid, संक_इति);

	अगर (WIFEXITED(status))
		status = WEXITSTATUS(status);
	अन्यथा अणु
		अगर (WIFSIGNALED(status))
			म_लिखो("!! child died by signal %d\n", WTERMSIG(status));
		अन्यथा
			म_लिखो("!! child died by unknown cause\n");

		status = 1; /* Signal or other */
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम sig_handler(पूर्णांक signum)
अणु
	/* Just wake us up from रुकोpid */
पूर्ण

अटल काष्ठा sigaction sig_action = अणु
	.sa_handler = sig_handler,
पूर्ण;

व्योम test_harness_set_समयout(uपूर्णांक64_t समय)
अणु
	समयout = समय;
पूर्ण

पूर्णांक test_harness(पूर्णांक (test_function)(व्योम), अक्षर *name)
अणु
	पूर्णांक rc;

	test_start(name);
	test_set_git_version(GIT_VERSION);

	अगर (sigaction(संक_विघ्न, &sig_action, शून्य)) अणु
		लिखो_त्रुटि("sigaction (sigint)");
		test_error(name);
		वापस 1;
	पूर्ण

	अगर (sigaction(SIGALRM, &sig_action, शून्य)) अणु
		लिखो_त्रुटि("sigaction (sigalrm)");
		test_error(name);
		वापस 1;
	पूर्ण

	rc = run_test(test_function, name);

	अगर (rc == MAGIC_SKIP_RETURN_VALUE) अणु
		test_skip(name);
		/* so that skipped test is not marked as failed */
		rc = 0;
	पूर्ण अन्यथा
		test_finish(name, rc);

	वापस rc;
पूर्ण
