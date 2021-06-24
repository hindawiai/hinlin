<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019 ARM Limited
 *
 * Utility macro to ease definition of testहालs toggling mode EL
 */

#घोषणा DEFINE_TESTCASE_MANGLE_PSTATE_INVALID_MODE(_mode)		\
									\
अटल पूर्णांक mangle_invalid_pstate_run(काष्ठा tdescr *td, siginfo_t *si,	\
				     ucontext_t *uc)			\
अणु									\
	ASSERT_GOOD_CONTEXT(uc);					\
									\
	uc->uc_mcontext.pstate &= ~PSR_MODE_MASK;			\
	uc->uc_mcontext.pstate |= PSR_MODE_EL ## _mode;			\
									\
	वापस 1;							\
पूर्ण									\
									\
काष्ठा tdescr tde = अणु							\
		.sanity_disabled = true,				\
		.name = "MANGLE_PSTATE_INVALID_MODE_EL"#_mode,		\
		.descr = "Mangling uc_mcontext INVALID MODE EL"#_mode,	\
		.sig_trig = SIGUSR1,					\
		.sig_ok = संक_अंश,					\
		.run = mangle_invalid_pstate_run,			\
पूर्ण
