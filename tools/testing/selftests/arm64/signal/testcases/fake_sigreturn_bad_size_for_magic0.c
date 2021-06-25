<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 ARM Limited
 *
 * Place a fake sigframe on the stack including a badly sized terminator
 * record: on sigवापस Kernel must spot this attempt and the test हाल
 * is expected to be terminated via SEGV.
 */

#समावेश <संकेत.स>
#समावेश <ucontext.h>

#समावेश "test_signals_utils.h"
#समावेश "testcases.h"

काष्ठा fake_sigframe sf;

अटल पूर्णांक fake_sigवापस_bad_size_क्रम_magic0_run(काष्ठा tdescr *td,
						  siginfo_t *si, ucontext_t *uc)
अणु
	काष्ठा _aarch64_ctx *shead = GET_SF_RESV_HEAD(sf), *head;

	/* just to fill the ucontext_t with something real */
	अगर (!get_current_context(td, &sf.uc))
		वापस 1;

	/* at least HDR_SZ क्रम the badly sized terminator. */
	head = get_starting_head(shead, HDR_SZ, GET_SF_RESV_SIZE(sf), शून्य);
	अगर (!head)
		वापस 0;

	head->magic = 0;
	head->size = HDR_SZ;
	ASSERT_BAD_CONTEXT(&sf.uc);
	fake_sigवापस(&sf, माप(sf), 0);

	वापस 1;
पूर्ण

काष्ठा tdescr tde = अणु
		.name = "FAKE_SIGRETURN_BAD_SIZE_FOR_TERMINATOR",
		.descr = "Trigger a sigreturn using non-zero size terminator",
		.sig_ok = संक_अंश,
		.समयout = 3,
		.run = fake_sigवापस_bad_size_क्रम_magic0_run,
पूर्ण;
