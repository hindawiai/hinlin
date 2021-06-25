<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vdso_restorer.c - tests vDSO-based संकेत restore
 * Copyright (c) 2015 Andrew Lutomirski
 *
 * This makes sure that sa_restorer == शून्य keeps working on 32-bit
 * configurations.  Modern glibc करोesn't use it under any circumstances,
 * so it's easy to overlook अवरोधage.
 *
 * 64-bit userspace has never supported sa_restorer == शून्य, so this is
 * 32-bit only.
 */

#घोषणा _GNU_SOURCE

#समावेश <err.h>
#समावेश <मानकपन.स>
#समावेश <dlfcn.h>
#समावेश <माला.स>
#समावेश <संकेत.स>
#समावेश <unistd.h>
#समावेश <syscall.h>
#समावेश <sys/syscall.h>

/* Open-code this -- the headers are too messy to easily use them. */
काष्ठा real_sigaction अणु
	व्योम *handler;
	अचिन्हित दीर्घ flags;
	व्योम *restorer;
	अचिन्हित पूर्णांक mask[2];
पूर्ण;

अटल अस्थिर संक_पूर्ण_प्रकार handler_called;

अटल व्योम handler_with_siginfo(पूर्णांक sig, siginfo_t *info, व्योम *ctx_व्योम)
अणु
	handler_called = 1;
पूर्ण

अटल व्योम handler_without_siginfo(पूर्णांक sig)
अणु
	handler_called = 1;
पूर्ण

पूर्णांक मुख्य()
अणु
	पूर्णांक nerrs = 0;
	काष्ठा real_sigaction sa;

	व्योम *vdso = dlखोलो("linux-vdso.so.1",
			    RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD);
	अगर (!vdso)
		vdso = dlखोलो("linux-gate.so.1",
			      RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD);
	अगर (!vdso) अणु
		म_लिखो("[SKIP]\tFailed to find vDSO.  Tests are not expected to work.\n");
		वापस 0;
	पूर्ण

	स_रखो(&sa, 0, माप(sa));
	sa.handler = handler_with_siginfo;
	sa.flags = SA_SIGINFO;
	sa.restorer = शून्य;	/* request kernel-provided restorer */

	म_लिखो("[RUN]\tRaise a signal, SA_SIGINFO, sa.restorer == NULL\n");

	अगर (syscall(SYS_rt_sigaction, SIGUSR1, &sa, शून्य, 8) != 0)
		err(1, "raw rt_sigaction syscall");

	उठाओ(SIGUSR1);

	अगर (handler_called) अणु
		म_लिखो("[OK]\tSA_SIGINFO handler returned successfully\n");
	पूर्ण अन्यथा अणु
		म_लिखो("[FAIL]\tSA_SIGINFO handler was not called\n");
		nerrs++;
	पूर्ण

	म_लिखो("[RUN]\tRaise a signal, !SA_SIGINFO, sa.restorer == NULL\n");

	sa.flags = 0;
	sa.handler = handler_without_siginfo;
	अगर (syscall(SYS_sigaction, SIGUSR1, &sa, 0) != 0)
		err(1, "raw sigaction syscall");
	handler_called = 0;

	उठाओ(SIGUSR1);

	अगर (handler_called) अणु
		म_लिखो("[OK]\t!SA_SIGINFO handler returned successfully\n");
	पूर्ण अन्यथा अणु
		म_लिखो("[FAIL]\t!SA_SIGINFO handler was not called\n");
		nerrs++;
	पूर्ण
पूर्ण
