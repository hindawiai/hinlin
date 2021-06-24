<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2016, Cyril Bur, IBM Corp.
 *
 * Test the kernel's संकेत frame code.
 *
 * The kernel sets up two sets of ucontexts अगर the संकेत was to be
 * delivered जबतक the thपढ़ो was in a transaction (referred too as
 * first and second contexts).
 * Expected behaviour is that the checkpoपूर्णांकed state is in the user
 * context passed to the संकेत handler (first context). The speculated
 * state can be accessed with the uc_link poपूर्णांकer (second context).
 *
 * The rationale क्रम this is that अगर TM unaware code (which linked
 * against TM libs) installs a संकेत handler it will not know of the
 * speculative nature of the 'live' रेजिस्टरs and may infer the wrong
 * thing.
 */

#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <संकेत.स>
#समावेश <unistd.h>

#समावेश <altivec.h>

#समावेश "utils.h"
#समावेश "tm.h"

#घोषणा MAX_ATTEMPT 500000

#घोषणा NV_FPU_REGS 18 /* Number of non-अस्थिर FP रेजिस्टरs */
#घोषणा FPR14 14 /* First non-अस्थिर FP रेजिस्टर to check in f14-31 subset */

दीर्घ पंचांग_संकेत_self_context_load(pid_t pid, दीर्घ *gprs, द्विगुन *fps, vector पूर्णांक *vms, vector पूर्णांक *vss);

/* Test only non-अस्थिर रेजिस्टरs, i.e. 18 fpr रेजिस्टरs from f14 to f31 */
अटल द्विगुन fps[] = अणु
	/* First context will be set with these values, i.e. non-speculative */
	 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
	/* Second context will be set with these values, i.e. speculative */
	-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14,-15,-16,-17,-18
पूर्ण;

अटल संक_पूर्ण_प्रकार fail, broken;

अटल व्योम संकेत_usr1(पूर्णांक signum, siginfo_t *info, व्योम *uc)
अणु
	पूर्णांक i;
	ucontext_t *ucp = uc;
	ucontext_t *पंचांग_ucp = ucp->uc_link;

	क्रम (i = 0; i < NV_FPU_REGS; i++) अणु
		/* Check first context. Prपूर्णांक all mismatches. */
		fail = (ucp->uc_mcontext.fp_regs[FPR14 + i] != fps[i]);
		अगर (fail) अणु
			broken = 1;
			म_लिखो("FPR%d (1st context) == %g instead of %g (expected)\n",
				FPR14 + i, ucp->uc_mcontext.fp_regs[FPR14 + i], fps[i]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < NV_FPU_REGS; i++) अणु
		/* Check second context. Prपूर्णांक all mismatches. */
		fail = (पंचांग_ucp->uc_mcontext.fp_regs[FPR14 + i] != fps[NV_FPU_REGS + i]);
		अगर (fail) अणु
			broken = 1;
			म_लिखो("FPR%d (2nd context) == %g instead of %g (expected)\n",
				FPR14 + i, पंचांग_ucp->uc_mcontext.fp_regs[FPR14 + i], fps[NV_FPU_REGS + i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक पंचांग_संकेत_context_chk_fpu()
अणु
	काष्ठा sigaction act;
	पूर्णांक i;
	दीर्घ rc;
	pid_t pid = getpid();

	SKIP_IF(!have_hपंचांग());

	act.sa_sigaction = संकेत_usr1;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	अगर (sigaction(SIGUSR1, &act, शून्य) < 0) अणु
		लिखो_त्रुटि("sigaction sigusr1");
		निकास(1);
	पूर्ण

	i = 0;
	जबतक (i < MAX_ATTEMPT && !broken) अणु
		/*
		 * पंचांग_संकेत_self_context_load will set both first and second
		 * contexts accordingly to the values passed through non-शून्य
		 * array poपूर्णांकers to it, in that हाल 'fps', and invoke the
		 * संकेत handler installed क्रम SIGUSR1.
		 */
		rc = पंचांग_संकेत_self_context_load(pid, शून्य, fps, शून्य, शून्य);
		FAIL_IF(rc != pid);
		i++;
	पूर्ण

	वापस (broken);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(पंचांग_संकेत_context_chk_fpu, "tm_signal_context_chk_fpu");
पूर्ण
