<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ioperm.c - Test हाल क्रम ioperm(2)
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

अटल व्योम expect_ok(अचिन्हित लघु port)
अणु
	अगर (!try_outb(port)) अणु
		म_लिखो("[FAIL]\toutb to 0x%02hx failed\n", port);
		निकास(1);
	पूर्ण

	म_लिखो("[OK]\toutb to 0x%02hx worked\n", port);
पूर्ण

अटल व्योम expect_gp(अचिन्हित लघु port)
अणु
	अगर (try_outb(port)) अणु
		म_लिखो("[FAIL]\toutb to 0x%02hx worked\n", port);
		निकास(1);
	पूर्ण

	म_लिखो("[OK]\toutb to 0x%02hx failed\n", port);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);
	अगर (sched_setaffinity(0, माप(cpuset), &cpuset) != 0)
		err(1, "sched_setaffinity to CPU 0");

	expect_gp(0x80);
	expect_gp(0xed);

	/*
	 * Probe क्रम ioperm support.  Note that clearing ioperm bits
	 * works even as nonroot.
	 */
	म_लिखो("[RUN]\tenable 0x80\n");
	अगर (ioperm(0x80, 1, 1) != 0) अणु
		म_लिखो("[OK]\tioperm(0x80, 1, 1) failed (%d) -- try running as root\n",
		       त्रुटि_सं);
		वापस 0;
	पूर्ण
	expect_ok(0x80);
	expect_gp(0xed);

	म_लिखो("[RUN]\tdisable 0x80\n");
	अगर (ioperm(0x80, 1, 0) != 0) अणु
		म_लिखो("[FAIL]\tioperm(0x80, 1, 0) failed (%d)", त्रुटि_सं);
		वापस 1;
	पूर्ण
	expect_gp(0x80);
	expect_gp(0xed);

	/* Make sure that विभाजन() preserves ioperm. */
	अगर (ioperm(0x80, 1, 1) != 0) अणु
		म_लिखो("[FAIL]\tioperm(0x80, 1, 0) failed (%d)", त्रुटि_सं);
		वापस 1;
	पूर्ण

	pid_t child = विभाजन();
	अगर (child == -1)
		err(1, "fork");

	अगर (child == 0) अणु
		म_लिखो("[RUN]\tchild: check that we inherited permissions\n");
		expect_ok(0x80);
		expect_gp(0xed);
		म_लिखो("[RUN]\tchild: Extend permissions to 0x81\n");
		अगर (ioperm(0x81, 1, 1) != 0) अणु
			म_लिखो("[FAIL]\tioperm(0x81, 1, 1) failed (%d)", त्रुटि_सं);
			वापस 1;
		पूर्ण
		म_लिखो("[RUN]\tchild: Drop permissions to 0x80\n");
		अगर (ioperm(0x80, 1, 0) != 0) अणु
			म_लिखो("[FAIL]\tioperm(0x80, 1, 0) failed (%d)", त्रुटि_सं);
			वापस 1;
		पूर्ण
		expect_gp(0x80);
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

	/* Verअगरy that the child dropping 0x80 did not affect the parent */
	म_लिखो("\tVerify that unsharing the bitmap worked\n");
	expect_ok(0x80);

	/* Test the capability checks. */
	म_लिखो("\tDrop privileges\n");
	अगर (setresuid(1, 1, 1) != 0) अणु
		म_लिखो("[WARN]\tDropping privileges failed\n");
		वापस 0;
	पूर्ण

	म_लिखो("[RUN]\tdisable 0x80\n");
	अगर (ioperm(0x80, 1, 0) != 0) अणु
		म_लिखो("[FAIL]\tioperm(0x80, 1, 0) failed (%d)", त्रुटि_सं);
		वापस 1;
	पूर्ण
	म_लिखो("[OK]\tit worked\n");

	म_लिखो("[RUN]\tenable 0x80 again\n");
	अगर (ioperm(0x80, 1, 1) == 0) अणु
		म_लिखो("[FAIL]\tit succeeded but should have failed.\n");
		वापस 1;
	पूर्ण
	म_लिखो("[OK]\tit failed\n");
	वापस 0;
पूर्ण
