<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 ARM Limited
 *
 * Place a fake sigframe on the stack including an additional FPSIMD
 * record: on sigवापस Kernel must spot this attempt and the test
 * हाल is expected to be terminated via SEGV.
 */

#समावेश <संकेत.स>
#समावेश <ucontext.h>

#समावेश "test_signals_utils.h"
#समावेश "testcases.h"

काष्ठा fake_sigframe sf;

अटल पूर्णांक fake_sigवापस_duplicated_fpsimd_run(काष्ठा tdescr *td,
						siginfo_t *si, ucontext_t *uc)
अणु
	काष्ठा _aarch64_ctx *shead = GET_SF_RESV_HEAD(sf), *head;

	/* just to fill the ucontext_t with something real */
	अगर (!get_current_context(td, &sf.uc))
		वापस 1;

	head = get_starting_head(shead, माप(काष्ठा fpsimd_context) + HDR_SZ,
				 GET_SF_RESV_SIZE(sf), शून्य);
	अगर (!head)
		वापस 0;

	/* Add a spurious fpsimd_context */
	head->magic = FPSIMD_MAGIC;
	head->size = माप(काष्ठा fpsimd_context);
	/* and terminate */
	ग_लिखो_terminator_record(GET_RESV_NEXT_HEAD(head));

	ASSERT_BAD_CONTEXT(&sf.uc);
	fake_sigवापस(&sf, माप(sf), 0);

	वापस 1;
पूर्ण

काष्ठा tdescr tde = अणु
		.name = "FAKE_SIGRETURN_DUPLICATED_FPSIMD",
		.descr = "Triggers a sigreturn including two fpsimd_context",
		.sig_ok = संक_अंश,
		.समयout = 3,
		.run = fake_sigवापस_duplicated_fpsimd_run,
पूर्ण;
