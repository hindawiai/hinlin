<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * iopl.c - Test हाल क्रम a Linux on Xen 64-bit bug
 * Copyright (c) 2015 Andrew Lutomirski
 */

#घोषणा _GNU_SOURCE
#समावेश <err.h>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <संकेत.स>
#समावेश <समलाँघ.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <stdbool.h>
#समावेश <sched.h>
#समावेश <sys/पन.स>

अटल पूर्णांक nerrs = 0;

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

अटल व्योम clearhandler(पूर्णांक sig)
अणु
	काष्ठा sigaction sa;
	स_रखो(&sa, 0, माप(sa));
	sa.sa_handler = संक_पूर्व;
	sigemptyset(&sa.sa_mask);
	अगर (sigaction(sig, &sa, 0))
		err(1, "sigaction");
पूर्ण

अटल लाँघ_बफ jmpbuf;

अटल व्योम sigsegv(पूर्णांक sig, siginfo_t *si, व्योम *ctx_व्योम)
अणु
	sigदीर्घ_लाँघ(jmpbuf, 1);
पूर्ण

अटल bool try_outb(अचिन्हित लघु port)
अणु
	sethandler(संक_अंश, sigsegv, SA_RESETHAND);
	अगर (sigबनाओ_लाँघ(jmpbuf, 1) != 0) अणु
		वापस false;
	पूर्ण अन्यथा अणु
		यंत्र अस्थिर ("outb %%al, %w[port]"
			      : : [port] "Nd" (port), "a" (0));
		वापस true;
	पूर्ण
	clearhandler(संक_अंश);
पूर्ण

अटल व्योम expect_ok_outb(अचिन्हित लघु port)
अणु
	अगर (!try_outb(port)) अणु
		म_लिखो("[FAIL]\toutb to 0x%02hx failed\n", port);
		निकास(1);
	पूर्ण

	म_लिखो("[OK]\toutb to 0x%02hx worked\n", port);
पूर्ण

अटल व्योम expect_gp_outb(अचिन्हित लघु port)
अणु
	अगर (try_outb(port)) अणु
		म_लिखो("[FAIL]\toutb to 0x%02hx worked\n", port);
		nerrs++;
	पूर्ण

	म_लिखो("[OK]\toutb to 0x%02hx failed\n", port);
पूर्ण

अटल bool try_cli(व्योम)
अणु
	sethandler(संक_अंश, sigsegv, SA_RESETHAND);
	अगर (sigबनाओ_लाँघ(jmpbuf, 1) != 0) अणु
		वापस false;
	पूर्ण अन्यथा अणु
		यंत्र अस्थिर ("cli");
		वापस true;
	पूर्ण
	clearhandler(संक_अंश);
पूर्ण

अटल bool try_sti(व्योम)
अणु
	sethandler(संक_अंश, sigsegv, SA_RESETHAND);
	अगर (sigबनाओ_लाँघ(jmpbuf, 1) != 0) अणु
		वापस false;
	पूर्ण अन्यथा अणु
		यंत्र अस्थिर ("sti");
		वापस true;
	पूर्ण
	clearhandler(संक_अंश);
पूर्ण

अटल व्योम expect_gp_sti(व्योम)
अणु
	अगर (try_sti()) अणु
		म_लिखो("[FAIL]\tSTI worked\n");
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tSTI faulted\n");
	पूर्ण
पूर्ण

अटल व्योम expect_gp_cli(व्योम)
अणु
	अगर (try_cli()) अणु
		म_लिखो("[FAIL]\tCLI worked\n");
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tCLI faulted\n");
	पूर्ण
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	cpu_set_t cpuset;

	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);
	अगर (sched_setaffinity(0, माप(cpuset), &cpuset) != 0)
		err(1, "sched_setaffinity to CPU 0");

	/* Probe क्रम iopl support.  Note that iopl(0) works even as nonroot. */
	चयन(iopl(3)) अणु
	हाल 0:
		अवरोध;
	हाल -ENOSYS:
		म_लिखो("[OK]\tiopl() nor supported\n");
		वापस 0;
	शेष:
		म_लिखो("[OK]\tiopl(3) failed (%d) -- try running as root\n",
		       त्रुटि_सं);
		वापस 0;
	पूर्ण

	/* Make sure that CLI/STI are blocked even with IOPL level 3 */
	expect_gp_cli();
	expect_gp_sti();
	expect_ok_outb(0x80);

	/* Establish an I/O biपंचांगap to test the restore */
	अगर (ioperm(0x80, 1, 1) != 0)
		err(1, "ioperm(0x80, 1, 1) failed\n");

	/* Restore our original state prior to starting the विभाजन test. */
	अगर (iopl(0) != 0)
		err(1, "iopl(0)");

	/*
	 * Verअगरy that IOPL emulation is disabled and the I/O biपंचांगap still
	 * works.
	 */
	expect_ok_outb(0x80);
	expect_gp_outb(0xed);
	/* Drop the I/O biपंचांगap */
	अगर (ioperm(0x80, 1, 0) != 0)
		err(1, "ioperm(0x80, 1, 0) failed\n");

	pid_t child = विभाजन();
	अगर (child == -1)
		err(1, "fork");

	अगर (child == 0) अणु
		म_लिखो("\tchild: set IOPL to 3\n");
		अगर (iopl(3) != 0)
			err(1, "iopl");

		म_लिखो("[RUN]\tchild: write to 0x80\n");
		यंत्र अस्थिर ("outb %%al, $0x80" : : "a" (0));

		वापस 0;
	पूर्ण अन्यथा अणु
		पूर्णांक status;
		अगर (रुकोpid(child, &status, 0) != child ||
		    !WIFEXITED(status)) अणु
			म_लिखो("[FAIL]\tChild died\n");
			nerrs++;
		पूर्ण अन्यथा अगर (WEXITSTATUS(status) != 0) अणु
			म_लिखो("[FAIL]\tChild failed\n");
			nerrs++;
		पूर्ण अन्यथा अणु
			म_लिखो("[OK]\tChild succeeded\n");
		पूर्ण
	पूर्ण

	म_लिखो("[RUN]\tparent: write to 0x80 (should fail)\n");

	expect_gp_outb(0x80);
	expect_gp_cli();
	expect_gp_sti();

	/* Test the capability checks. */
	म_लिखो("\tiopl(3)\n");
	अगर (iopl(3) != 0)
		err(1, "iopl(3)");

	म_लिखो("\tDrop privileges\n");
	अगर (setresuid(1, 1, 1) != 0) अणु
		म_लिखो("[WARN]\tDropping privileges failed\n");
		जाओ करोne;
	पूर्ण

	म_लिखो("[RUN]\tiopl(3) unprivileged but with IOPL==3\n");
	अगर (iopl(3) != 0) अणु
		म_लिखो("[FAIL]\tiopl(3) should work if iopl is already 3 even if unprivileged\n");
		nerrs++;
	पूर्ण

	म_लिखो("[RUN]\tiopl(0) unprivileged\n");
	अगर (iopl(0) != 0) अणु
		म_लिखो("[FAIL]\tiopl(0) should work if iopl is already 3 even if unprivileged\n");
		nerrs++;
	पूर्ण

	म_लिखो("[RUN]\tiopl(3) unprivileged\n");
	अगर (iopl(3) == 0) अणु
		म_लिखो("[FAIL]\tiopl(3) should fail if when unprivileged if iopl==0\n");
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tFailed as expected\n");
	पूर्ण

करोne:
	वापस nerrs ? 1 : 0;
पूर्ण
