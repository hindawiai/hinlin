<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 ARM Limited
 *
 * Place a fake sigframe on the stack including a BAD Unknown magic
 * record: on sigवापस Kernel must spot this attempt and the test
 * हाल is expected to be terminated via SEGV.
 */

#समावेश <संकेत.स>
#समावेश <ucontext.h>

#समावेश "test_signals_utils.h"
#समावेश "testcases.h"

काष्ठा fake_sigframe sf;

अटल पूर्णांक fake_sigवापस_bad_magic_run(काष्ठा tdescr *td,
					siginfo_t *si, ucontext_t *uc)
अणु
	काष्ठा _aarch64_ctx *shead = GET_SF_RESV_HEAD(sf), *head;

	/* just to fill the ucontext_t with something real */
	अगर (!get_current_context(td, &sf.uc))
		वापस 1;

	/* need at least 2*HDR_SZ space: KSFT_BAD_MAGIC + terminator. */
	head = get_starting_head(shead, HDR_SZ * 2, GET_SF_RESV_SIZE(sf), शून्य);
	अगर (!head)
		वापस 0;

	/*
	 * use a well known NON existent bad magic...something
	 * we should pretty sure won't be ever defined in Kernel
	 */
	head->magic = KSFT_BAD_MAGIC;
	head->size = HDR_SZ;
	ग_लिखो_terminator_record(GET_RESV_NEXT_HEAD(head));

	ASSERT_BAD_CONTEXT(&sf.uc);
	fake_sigवापस(&sf, माप(sf), 0);

	वापस 1;
पूर्ण

काष्ठा tdescr tde = अणु
		.name = "FAKE_SIGRETURN_BAD_MAGIC",
		.descr = "Trigger a sigreturn with a sigframe with a bad magic",
		.sig_ok = संक_अंश,
		.समयout = 3,
		.run = fake_sigवापस_bad_magic_run,
पूर्ण;
