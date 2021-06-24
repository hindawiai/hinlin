<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2019 ARM Limited */

#अगर_अघोषित __TEST_SIGNALS_H__
#घोषणा __TEST_SIGNALS_H__

#समावेश <संकेत.स>
#समावेश <stdbool.h>
#समावेश <ucontext.h>

/*
 * Using ARCH specअगरic and sanitized Kernel headers installed by KSFT
 * framework since we asked क्रम it by setting flag KSFT_KHDR_INSTALL
 * in our Makefile.
 */
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/hwcap.h>

#घोषणा __stringअगरy_1(x...)	#x
#घोषणा __stringअगरy(x...)	__stringअगरy_1(x)

#घोषणा get_regval(regname, out)			\
अणु							\
	यंत्र अस्थिर("mrs %0, " __stringअगरy(regname)	\
	: "=r" (out)					\
	:						\
	: "memory");					\
पूर्ण

/*
 * Feature flags used in tdescr.feats_required to specअगरy
 * any feature by the test
 */
क्रमागत अणु
	FSSBS_BIT,
	FMAX_END
पूर्ण;

#घोषणा FEAT_SSBS		(1UL << FSSBS_BIT)

/*
 * A descriptor used to describe and configure a test हाल.
 * Fields with a non-trivial meaning are described अंतरभूत in the following.
 */
काष्ठा tdescr अणु
	/* KEEP THIS FIELD FIRST क्रम easier lookup from assembly */
	व्योम			*token;
	/* when disabled token based sanity checking is skipped in handler */
	bool			sanity_disabled;
	/* just a name क्रम the test-हाल; manadatory field */
	अक्षर			*name;
	अक्षर			*descr;
	अचिन्हित दीर्घ		feats_required;
	/* biपंचांगask of effectively supported feats: populated at run-समय */
	अचिन्हित दीर्घ		feats_supported;
	bool			initialized;
	अचिन्हित पूर्णांक		minsigstksz;
	/* signum used as a test trigger. Zero अगर no trigger-संकेत is used */
	पूर्णांक			sig_trig;
	/*
	 * signum considered as a successful test completion.
	 * Zero when no संकेत is expected on success
	 */
	पूर्णांक			sig_ok;
	/* signum expected on unsupported CPU features. */
	पूर्णांक			sig_unsupp;
	/* a समयout in second क्रम test completion */
	अचिन्हित पूर्णांक		समयout;
	bool			triggered;
	bool			pass;
	अचिन्हित पूर्णांक		result;
	/* optional sa_flags क्रम the installed handler */
	पूर्णांक			sa_flags;
	ucontext_t		saved_uc;
	/* used by get_current_ctx() */
	माप_प्रकार			live_sz;
	ucontext_t		*live_uc;
	अस्थिर संक_पूर्ण_प्रकार	live_uc_valid;
	/* optional test निजी data */
	व्योम			*priv;

	/* a custom setup: called alternatively to शेष_setup */
	पूर्णांक (*setup)(काष्ठा tdescr *td);
	/* a custom init: called by शेष test init after test_setup */
	bool (*init)(काष्ठा tdescr *td);
	/* a custom cleanup function called beक्रमe test निकासs */
	व्योम (*cleanup)(काष्ठा tdescr *td);
	/* an optional function to be used as a trigger क्रम starting test */
	पूर्णांक (*trigger)(काष्ठा tdescr *td);
	/*
	 * the actual test-core: invoked dअगरferently depending on the
	 * presence of the trigger function above; this is mandatory
	 */
	पूर्णांक (*run)(काष्ठा tdescr *td, siginfo_t *si, ucontext_t *uc);
	/* an optional function क्रम custom results' processing */
	व्योम (*check_result)(काष्ठा tdescr *td);
पूर्ण;

बाह्य काष्ठा tdescr tde;
#पूर्ण_अगर
