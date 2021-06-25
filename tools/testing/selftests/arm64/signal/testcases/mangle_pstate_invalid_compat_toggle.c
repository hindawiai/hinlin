<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 ARM Limited
 *
 * Try to mangle the ucontext from inside a संकेत handler, toggling
 * the execution state bit: this attempt must be spotted by Kernel and
 * the test हाल is expected to be terminated via SEGV.
 */

#समावेश "test_signals_utils.h"
#समावेश "testcases.h"

अटल पूर्णांक mangle_invalid_pstate_run(काष्ठा tdescr *td, siginfo_t *si,
				     ucontext_t *uc)
अणु
	ASSERT_GOOD_CONTEXT(uc);

	/* This config should trigger a संक_अंश by Kernel */
	uc->uc_mcontext.pstate ^= PSR_MODE32_BIT;

	वापस 1;
पूर्ण

काष्ठा tdescr tde = अणु
		.sanity_disabled = true,
		.name = "MANGLE_PSTATE_INVALID_STATE_TOGGLE",
		.descr = "Mangling uc_mcontext with INVALID STATE_TOGGLE",
		.sig_trig = SIGUSR1,
		.sig_ok = संक_अंश,
		.run = mangle_invalid_pstate_run,
पूर्ण;
