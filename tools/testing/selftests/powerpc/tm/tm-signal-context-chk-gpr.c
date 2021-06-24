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

#घोषणा NV_GPR_REGS 18 /* Number of non-अस्थिर GPR रेजिस्टरs */
#घोषणा R14 14 /* First non-अस्थिर रेजिस्टर to check in r14-r31 subset */

दीर्घ पंचांग_संकेत_self_context_load(pid_t pid, दीर्घ *gprs, द्विगुन *fps, vector पूर्णांक *vms, vector पूर्णांक *vss);

अटल संक_पूर्ण_प्रकार fail, broken;

/* Test only non-अस्थिर general purpose रेजिस्टरs, i.e. r14-r31 */
अटल दीर्घ gprs[] = अणु
	/* First context will be set with these values, i.e. non-speculative */
	/* R14, R15, ... */
	 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
	/* Second context will be set with these values, i.e. speculative */
	/* R14, R15, ... */
	-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14,-15,-16,-17,-18
पूर्ण;

अटल व्योम संकेत_usr1(पूर्णांक signum, siginfo_t *info, व्योम *uc)
अणु
	पूर्णांक i;
	ucontext_t *ucp = uc;
	ucontext_t *पंचांग_ucp = ucp->uc_link;

	/* Check first context. Prपूर्णांक all mismatches. */
	क्रम (i = 0; i < NV_GPR_REGS; i++) अणु
		fail = (ucp->uc_mcontext.gp_regs[R14 + i] != gprs[i]);
		अगर (fail) अणु
			broken = 1;
			म_लिखो("GPR%d (1st context) == %lu instead of %lu (expected)\n",
				R14 + i, ucp->uc_mcontext.gp_regs[R14 + i], gprs[i]);
		पूर्ण
	पूर्ण

	/* Check second context. Prपूर्णांक all mismatches. */
	क्रम (i = 0; i < NV_GPR_REGS; i++) अणु
		fail = (पंचांग_ucp->uc_mcontext.gp_regs[R14 + i] != gprs[NV_GPR_REGS + i]);
		अगर (fail) अणु
			broken = 1;
			म_लिखो("GPR%d (2nd context) == %lu instead of %lu (expected)\n",
				R14 + i, पंचांग_ucp->uc_mcontext.gp_regs[R14 + i], gprs[NV_GPR_REGS + i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक पंचांग_संकेत_context_chk_gpr()
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
                 * array poपूर्णांकers to it, in that हाल 'gprs', and invoke the
                 * संकेत handler installed क्रम SIGUSR1.
                 */
		rc = पंचांग_संकेत_self_context_load(pid, gprs, शून्य, शून्य, शून्य);
		FAIL_IF(rc != pid);
		i++;
	पूर्ण

	वापस broken;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(पंचांग_संकेत_context_chk_gpr, "tm_signal_context_chk_gpr");
पूर्ण
