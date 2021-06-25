<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2017 John Sperbeck
 *
 * Test that an access to a mapped but inaccessible area causes a SEGV and
 * reports si_code == SEGV_ACCERR.
 */

#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <संकेत.स>
#समावेश <sys/mman.h>
#समावेश <निश्चित.स>
#समावेश <ucontext.h>

#समावेश "utils.h"

अटल bool faulted;
अटल पूर्णांक si_code;

अटल व्योम segv_handler(पूर्णांक n, siginfo_t *info, व्योम *ctxt_v)
अणु
	ucontext_t *ctxt = (ucontext_t *)ctxt_v;
	काष्ठा pt_regs *regs = ctxt->uc_mcontext.regs;

	faulted = true;
	si_code = info->si_code;
	regs->nip += 4;
पूर्ण

पूर्णांक test_segv_errors(व्योम)
अणु
	काष्ठा sigaction act = अणु
		.sa_sigaction = segv_handler,
		.sa_flags = SA_SIGINFO,
	पूर्ण;
	अक्षर c, *p = शून्य;

	p = mmap(शून्य, getpagesize(), 0, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	FAIL_IF(p == MAP_FAILED);

	FAIL_IF(sigaction(संक_अंश, &act, शून्य) != 0);

	faulted = false;
	si_code = 0;

	/*
	 * We just need a compiler barrier, but mb() works and has the nice
	 * property of being easy to spot in the disassembly.
	 */
	mb();
	c = *p;
	mb();

	FAIL_IF(!faulted);
	FAIL_IF(si_code != SEGV_ACCERR);

	faulted = false;
	si_code = 0;

	mb();
	*p = c;
	mb();

	FAIL_IF(!faulted);
	FAIL_IF(si_code != SEGV_ACCERR);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(test_segv_errors, "segv_errors");
पूर्ण
