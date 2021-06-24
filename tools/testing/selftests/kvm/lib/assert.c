<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tools/testing/selftests/kvm/lib/निश्चित.c
 *
 * Copyright (C) 2018, Google LLC.
 */

#घोषणा _GNU_SOURCE /* क्रम getline(3) and म_अक्षरnul(3)*/

#समावेश "test_util.h"

#समावेश <execinfo.h>
#समावेश <sys/syscall.h>

#समावेश "kselftest.h"

/* Dumps the current stack trace to मानक_त्रुटि. */
अटल व्योम __attribute__((noअंतरभूत)) test_dump_stack(व्योम);
अटल व्योम test_dump_stack(व्योम)
अणु
	/*
	 * Build and run this command:
	 *
	 *	addr2line -s -e /proc/$PPID/exe -fpai अणुbacktrace addressesपूर्ण | \
	 *		grep -v test_dump_stack | cat -n 1>&2
	 *
	 * Note that the spacing is dअगरferent and there's no newline.
	 */
	माप_प्रकार i;
	माप_प्रकार n = 20;
	व्योम *stack[n];
	स्थिर अक्षर *addr2line = "addr2line -s -e /proc/$PPID/exe -fpai";
	स्थिर अक्षर *pipeline = "|cat -n 1>&2";
	अक्षर cmd[म_माप(addr2line) + म_माप(pipeline) +
		 /* N bytes per addr * 2 digits per byte + 1 space per addr: */
		 n * (((माप(व्योम *)) * 2) + 1) +
		 /* Null terminator: */
		 1];
	अक्षर *c;

	n = backtrace(stack, n);
	c = &cmd[0];
	c += प्र_लिखो(c, "%s", addr2line);
	/*
	 * Skip the first 3 frames: backtrace, test_dump_stack, and
	 * test_निश्चित. We hope that backtrace isn't अंतरभूतd and the other two
	 * we've declared noअंतरभूत.
	 */
	क्रम (i = 2; i < n; i++)
		c += प्र_लिखो(c, " %lx", ((अचिन्हित दीर्घ) stack[i]) - 1);
	c += प्र_लिखो(c, "%s", pipeline);
#आशय GCC diagnostic push
#आशय GCC diagnostic ignored "-Wunused-result"
	प्रणाली(cmd);
#आशय GCC diagnostic pop
पूर्ण

अटल pid_t _gettid(व्योम)
अणु
	वापस syscall(SYS_gettid);
पूर्ण

व्योम __attribute__((noअंतरभूत))
test_निश्चित(bool exp, स्थिर अक्षर *exp_str,
	स्थिर अक्षर *file, अचिन्हित पूर्णांक line, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	अगर (!(exp)) अणु
		बहु_शुरू(ap, fmt);

		ख_लिखो(मानक_त्रुटि, "==== Test Assertion Failure ====\n"
			"  %s:%u: %s\n"
			"  pid=%d tid=%d errno=%d - %s\n",
			file, line, exp_str, getpid(), _gettid(),
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		test_dump_stack();
		अगर (fmt) अणु
			ख_माला_दो("  ", मानक_त्रुटि);
			भख_लिखो(मानक_त्रुटि, fmt, ap);
			ख_माला_दो("\n", मानक_त्रुटि);
		पूर्ण
		बहु_पूर्ण(ap);

		अगर (त्रुटि_सं == EACCES) अणु
			prपूर्णांक_skip("Access denied - Exiting");
			निकास(KSFT_SKIP);
		पूर्ण
		निकास(254);
	पूर्ण

	वापस;
पूर्ण
