<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015, Cyril Bur, IBM Corp.
 *
 * This test attempts to see अगर the VMX रेजिस्टरs change across a syscall (विभाजन).
 */

#समावेश <altivec.h>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <sys/समय.स>
#समावेश <मानककोष.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश "utils.h"

vector पूर्णांक varray[] = अणुअणु1, 2, 3, 4पूर्ण, अणु5, 6, 7, 8पूर्ण, अणु9, 10,11,12पूर्ण,
	अणु13,14,15,16पूर्ण,अणु17,18,19,20पूर्ण,अणु21,22,23,24पूर्ण,
	अणु25,26,27,28पूर्ण,अणु29,30,31,32पूर्ण,अणु33,34,35,36पूर्ण,
	अणु37,38,39,40पूर्ण,अणु41,42,43,44पूर्ण,अणु45,46,47,48पूर्णपूर्ण;

बाह्य पूर्णांक test_vmx(vector पूर्णांक *varray, pid_t *pid);

पूर्णांक vmx_syscall(व्योम)
अणु
	pid_t विभाजन_pid;
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक child_ret;
	क्रम (i = 0; i < 1000; i++) अणु
		/* test_vmx will विभाजन() */
		ret = test_vmx(varray, &विभाजन_pid);
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

पूर्णांक test_vmx_syscall(व्योम)
अणु
	/*
	 * Setup an environment with much context चयनing
	 */
	pid_t pid2;
	pid_t pid;
	पूर्णांक ret;
	पूर्णांक child_ret;

	// vcmpequd used in vmx_यंत्र.S is v2.07
	SKIP_IF(!have_hwcap2(PPC_FEATURE2_ARCH_2_07));

	pid = विभाजन();
	FAIL_IF(pid == -1);

	pid2 = विभाजन();
	ret = vmx_syscall();
	/* Can't FAIL_IF(pid2 == -1); because we've alपढ़ोy विभाजनed */
	अगर (pid2 == -1) अणु
		/*
		 * Couldn't विभाजन, ensure child_ret is set and is a fail
		 */
		ret = child_ret = 1;
	पूर्ण अन्यथा अणु
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
	वापस test_harness(test_vmx_syscall, "vmx_syscall");

पूर्ण
