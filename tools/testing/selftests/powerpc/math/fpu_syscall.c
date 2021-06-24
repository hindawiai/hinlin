<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015, Cyril Bur, IBM Corp.
 *
 * This test attempts to see अगर the FPU रेजिस्टरs change across a syscall (विभाजन).
 */

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <मानककोष.स>

#समावेश "utils.h"

बाह्य पूर्णांक test_fpu(द्विगुन *darray, pid_t *pid);

द्विगुन darray[] = अणु0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
		     1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0,
		     2.1पूर्ण;

पूर्णांक syscall_fpu(व्योम)
अणु
	pid_t विभाजन_pid;
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक child_ret;
	क्रम (i = 0; i < 1000; i++) अणु
		/* test_fpu will विभाजन() */
		ret = test_fpu(darray, &विभाजन_pid);
		अगर (विभाजन_pid == -1)
			वापस -1;
		अगर (विभाजन_pid == 0)
			निकास(ret);
		रुकोpid(विभाजन_pid, &child_ret, 0);
		अगर (ret || child_ret)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक test_syscall_fpu(व्योम)
अणु
	/*
	 * Setup an environment with much context चयनing
	 */
	pid_t pid2;
	pid_t pid = विभाजन();
	पूर्णांक ret;
	पूर्णांक child_ret;
	FAIL_IF(pid == -1);

	pid2 = विभाजन();
	/* Can't FAIL_IF(pid2 == -1); because alपढ़ोy विभाजनed once */
	अगर (pid2 == -1) अणु
		/*
		 * Couldn't विभाजन, ensure test is a fail
		 */
		child_ret = ret = 1;
	पूर्ण अन्यथा अणु
		ret = syscall_fpu();
		अगर (pid2)
			रुकोpid(pid2, &child_ret, 0);
		अन्यथा
			निकास(ret);
	पूर्ण

	ret |= child_ret;

	अगर (pid)
		रुकोpid(pid, &child_ret, 0);
	अन्यथा
		निकास(ret);

	FAIL_IF(ret || child_ret);
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(test_syscall_fpu, "syscall_fpu");

पूर्ण
