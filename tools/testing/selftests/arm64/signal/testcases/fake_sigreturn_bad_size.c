<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 ARM Limited
 *
 * Place a fake sigframe on the stack including a bad record overflowing
 * the __reserved space: on sigवापस Kernel must spot this attempt and
 * the test हाल is expected to be terminated via SEGV.
 */

#समावेश <संकेत.स>
#समावेश <ucontext.h>

#समावेश "test_signals_utils.h"
#समावेश "testcases.h"

काष्ठा fake_sigframe sf;

#घोषणा MIN_SZ_ALIGN	16

अटल पूर्णांक fake_sigवापस_bad_size_run(काष्ठा tdescr *td,
				       siginfo_t *si, ucontext_t *uc)
अणु
	माप_प्रकार resv_sz, need_sz, offset;
	काष्ठा _aarch64_ctx *shead = GET_SF_RESV_HEAD(sf), *head;

	/* just to fill the ucontext_t with something real */
	अगर (!get_current_context(td, &sf.uc))
		वापस 1;

	resv_sz = GET_SF_RESV_SIZE(sf);
	/* at least HDR_SZ + bad sized esr_context needed */
	need_sz = माप(काष्ठा esr_context) + HDR_SZ;
	head = get_starting_head(shead, need_sz, resv_sz, &offset);
	अगर (!head)
		वापस 0;

	/*
	 * Use an esr_context to build a fake header with a
	 * size greater then the मुक्त __reserved area minus HDR_SZ;
	 * using ESR_MAGIC here since it is not checked क्रम size nor
	 * is limited to one instance.
	 *
	 * At first inject an additional normal esr_context
	 */
	head->magic = ESR_MAGIC;
	head->size = माप(काष्ठा esr_context);
	/* and terminate properly */
	ग_लिखो_terminator_record(GET_RESV_NEXT_HEAD(head));
	ASSERT_GOOD_CONTEXT(&sf.uc);

	/*
	 * now mess with fake esr_context size: leaving less space than
	 * needed जबतक keeping size value 16-aligned
	 *
	 * It must trigger a SEGV from Kernel on:
	 *
	 *	resv_sz - offset < माप(*head)
	 */
	/* at first set the maximum good 16-aligned size */
	head->size = (resv_sz - offset - need_sz + MIN_SZ_ALIGN) & ~0xfUL;
	/* plus a bit more of 16-aligned sized stuff */
	head->size += MIN_SZ_ALIGN;
	/* and terminate properly */
	ग_लिखो_terminator_record(GET_RESV_NEXT_HEAD(head));
	ASSERT_BAD_CONTEXT(&sf.uc);
	fake_sigवापस(&sf, माप(sf), 0);

	वापस 1;
पूर्ण

काष्ठा tdescr tde = अणु
		.name = "FAKE_SIGRETURN_BAD_SIZE",
		.descr = "Triggers a sigreturn with a overrun __reserved area",
		.sig_ok = संक_अंश,
		.समयout = 3,
		.run = fake_sigवापस_bad_size_run,
पूर्ण;
