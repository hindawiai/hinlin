<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 ARM Limited
 *
 * Place a fake sigframe on the stack missing the mandatory FPSIMD
 * record: on sigवापस Kernel must spot this attempt and the test
 * हाल is expected to be terminated via SEGV.
 */

#समावेश <मानकपन.स>
#समावेश <संकेत.स>
#समावेश <ucontext.h>

#समावेश "test_signals_utils.h"
#समावेश "testcases.h"

काष्ठा fake_sigframe sf;

अटल पूर्णांक fake_sigवापस_missing_fpsimd_run(काष्ठा tdescr *td,
					     siginfo_t *si, ucontext_t *uc)
अणु
	माप_प्रकार resv_sz, offset;
	काष्ठा _aarch64_ctx *head = GET_SF_RESV_HEAD(sf);

	/* just to fill the ucontext_t with something real */
	अगर (!get_current_context(td, &sf.uc))
		वापस 1;

	resv_sz = GET_SF_RESV_SIZE(sf);
	head = get_header(head, FPSIMD_MAGIC, resv_sz, &offset);
	अगर (head && resv_sz - offset >= HDR_SZ) अणु
		ख_लिखो(मानक_त्रुटि, "Mangling template header. Spare space:%zd\n",
			resv_sz - offset);
		/* Just overग_लिखो fpsmid_context */
		ग_लिखो_terminator_record(head);

		ASSERT_BAD_CONTEXT(&sf.uc);
		fake_sigवापस(&sf, माप(sf), 0);
	पूर्ण

	वापस 1;
पूर्ण

काष्ठा tdescr tde = अणु
		.name = "FAKE_SIGRETURN_MISSING_FPSIMD",
		.descr = "Triggers a sigreturn with a missing fpsimd_context",
		.sig_ok = संक_अंश,
		.समयout = 3,
		.run = fake_sigवापस_missing_fpsimd_run,
पूर्ण;
