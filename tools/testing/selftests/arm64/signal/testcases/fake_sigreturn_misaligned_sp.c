<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 ARM Limited
 *
 * Place a fake sigframe on the stack at a misaligned SP: on sigवापस
 * Kernel must spot this attempt and the test हाल is expected to be
 * terminated via SEGV.
 */

#समावेश <संकेत.स>
#समावेश <ucontext.h>

#समावेश "test_signals_utils.h"
#समावेश "testcases.h"

काष्ठा fake_sigframe sf;

अटल पूर्णांक fake_sigवापस_misaligned_run(काष्ठा tdescr *td,
					 siginfo_t *si, ucontext_t *uc)
अणु
	/* just to fill the ucontext_t with something real */
	अगर (!get_current_context(td, &sf.uc))
		वापस 1;

	/* Forcing sigframe on misaligned SP (16 + 3) */
	fake_sigवापस(&sf, माप(sf), 3);

	वापस 1;
पूर्ण

काष्ठा tdescr tde = अणु
		.name = "FAKE_SIGRETURN_MISALIGNED_SP",
		.descr = "Triggers a sigreturn with a misaligned sigframe",
		.sig_ok = संक_अंश,
		.समयout = 3,
		.run = fake_sigवापस_misaligned_run,
पूर्ण;
