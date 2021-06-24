<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * syscall_nt.c - checks syscalls with NT set
 * Copyright (c) 2014-2015 Andrew Lutomirski
 *
 * Some obscure user-space code requires the ability to make प्रणाली calls
 * with FLAGS.NT set.  Make sure it works.
 */

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <संकेत.स>
#समावेश <err.h>
#समावेश <sys/syscall.h>

#समावेश "helpers.h"

अटल अचिन्हित पूर्णांक nerrs;

अटल व्योम sethandler(पूर्णांक sig, व्योम (*handler)(पूर्णांक, siginfo_t *, व्योम *),
		       पूर्णांक flags)
अणु
	काष्ठा sigaction sa;
	स_रखो(&sa, 0, माप(sa));
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO | flags;
	sigemptyset(&sa.sa_mask);
	अगर (sigaction(sig, &sa, 0))
		err(1, "sigaction");
पूर्ण

अटल व्योम sigtrap(पूर्णांक sig, siginfo_t *si, व्योम *ctx_व्योम)
अणु
पूर्ण

अटल व्योम करो_it(अचिन्हित दीर्घ extraflags)
अणु
	अचिन्हित दीर्घ flags;

	set_eflags(get_eflags() | extraflags);
	syscall(SYS_getpid);
	flags = get_eflags();
	set_eflags(X86_EFLAGS_IF | X86_EFLAGS_FIXED);
	अगर ((flags & extraflags) == extraflags) अणु
		म_लिखो("[OK]\tThe syscall worked and flags are still set\n");
	पूर्ण अन्यथा अणु
		म_लिखो("[FAIL]\tThe syscall worked but flags were cleared (flags = 0x%lx but expected 0x%lx set)\n",
		       flags, extraflags);
		nerrs++;
	पूर्ण
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	म_लिखो("[RUN]\tSet NT and issue a syscall\n");
	करो_it(X86_EFLAGS_NT);

	म_लिखो("[RUN]\tSet AC and issue a syscall\n");
	करो_it(X86_EFLAGS_AC);

	म_लिखो("[RUN]\tSet NT|AC and issue a syscall\n");
	करो_it(X86_EFLAGS_NT | X86_EFLAGS_AC);

	/*
	 * Now try it again with TF set -- TF क्रमces वापसs via IRET in all
	 * हालs except non-ptregs-using 64-bit full fast path syscalls.
	 */

	sethandler(SIGTRAP, sigtrap, 0);

	म_लिखो("[RUN]\tSet TF and issue a syscall\n");
	करो_it(X86_EFLAGS_TF);

	म_लिखो("[RUN]\tSet NT|TF and issue a syscall\n");
	करो_it(X86_EFLAGS_NT | X86_EFLAGS_TF);

	म_लिखो("[RUN]\tSet AC|TF and issue a syscall\n");
	करो_it(X86_EFLAGS_AC | X86_EFLAGS_TF);

	म_लिखो("[RUN]\tSet NT|AC|TF and issue a syscall\n");
	करो_it(X86_EFLAGS_NT | X86_EFLAGS_AC | X86_EFLAGS_TF);

	/*
	 * Now try DF.  This is evil and it's plausible that we will crash
	 * glibc, but glibc would have to करो something rather surprising
	 * क्रम this to happen.
	 */
	म_लिखो("[RUN]\tSet DF and issue a syscall\n");
	करो_it(X86_EFLAGS_DF);

	म_लिखो("[RUN]\tSet TF|DF and issue a syscall\n");
	करो_it(X86_EFLAGS_TF | X86_EFLAGS_DF);

	वापस nerrs == 0 ? 0 : 1;
पूर्ण
