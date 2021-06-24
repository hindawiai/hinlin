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
#समावेश <माला.स>
#समावेश <संकेत.स>
#समावेश <unistd.h>

#समावेश <altivec.h>

#समावेश "utils.h"
#समावेश "tm.h"

#घोषणा MAX_ATTEMPT 500000

#घोषणा NV_VMX_REGS 12 /* Number of non-अस्थिर VMX रेजिस्टरs */
#घोषणा VMX20 20 /* First non-अस्थिर रेजिस्टर to check in vr20-31 subset */

दीर्घ पंचांग_संकेत_self_context_load(pid_t pid, दीर्घ *gprs, द्विगुन *fps, vector पूर्णांक *vms, vector पूर्णांक *vss);

अटल संक_पूर्ण_प्रकार fail, broken;

/* Test only non-अस्थिर रेजिस्टरs, i.e. 12 vmx रेजिस्टरs from vr20 to vr31 */
vector पूर्णांक vms[] = अणु
	/* First context will be set with these values, i.e. non-speculative */
	/* VMX20     ,  VMX21      , ... */
	अणु 1, 2, 3, 4पूर्ण,अणु 5, 6, 7, 8पूर्ण,अणु 9,10,11,12पूर्ण,
	अणु13,14,15,16पूर्ण,अणु17,18,19,20पूर्ण,अणु21,22,23,24पूर्ण,
	अणु25,26,27,28पूर्ण,अणु29,30,31,32पूर्ण,अणु33,34,35,36पूर्ण,
	अणु37,38,39,40पूर्ण,अणु41,42,43,44पूर्ण,अणु45,46,47,48पूर्ण,
	/* Second context will be set with these values, i.e. speculative */
	/* VMX20        , VMX21            , ... */
	अणु -1, -2, -3, -4पूर्ण,अणु -5, -6, -7, -8पूर्ण,अणु -9,-10,-11,-12पूर्ण,
	अणु-13,-14,-15,-16पूर्ण,अणु-17,-18,-19,-20पूर्ण,अणु-21,-22,-23,-24पूर्ण,
	अणु-25,-26,-27,-28पूर्ण,अणु-29,-30,-31,-32पूर्ण,अणु-33,-34,-35,-36पूर्ण,
	अणु-37,-38,-39,-40पूर्ण,अणु-41,-42,-43,-44पूर्ण,अणु-45,-46,-47,-48पूर्ण
पूर्ण;

अटल व्योम संकेत_usr1(पूर्णांक signum, siginfo_t *info, व्योम *uc)
अणु
	पूर्णांक i, j;
	ucontext_t *ucp = uc;
	ucontext_t *पंचांग_ucp = ucp->uc_link;

	क्रम (i = 0; i < NV_VMX_REGS; i++) अणु
		/* Check first context. Prपूर्णांक all mismatches. */
		fail = स_भेद(ucp->uc_mcontext.v_regs->vrregs[VMX20 + i],
				&vms[i], माप(vector पूर्णांक));
		अगर (fail) अणु
			broken = 1;
			म_लिखो("VMX%d (1st context) == 0x", VMX20 + i);
			/* Prपूर्णांक actual value in first context. */
			क्रम (j = 0; j < 4; j++)
				म_लिखो("%08x", ucp->uc_mcontext.v_regs->vrregs[VMX20 + i][j]);
			म_लिखो(" instead of 0x");
			/* Prपूर्णांक expected value. */
			क्रम (j = 0; j < 4; j++)
				म_लिखो("%08x", vms[i][j]);
			म_लिखो(" (expected)\n");
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < NV_VMX_REGS; i++)  अणु
		/* Check second context. Prपूर्णांक all mismatches. */
		fail = स_भेद(पंचांग_ucp->uc_mcontext.v_regs->vrregs[VMX20 + i],
				&vms[NV_VMX_REGS + i], माप (vector पूर्णांक));
		अगर (fail) अणु
			broken = 1;
			म_लिखो("VMX%d (2nd context) == 0x", NV_VMX_REGS + i);
			/* Prपूर्णांक actual value in second context. */
			क्रम (j = 0; j < 4; j++)
				म_लिखो("%08x", पंचांग_ucp->uc_mcontext.v_regs->vrregs[VMX20 + i][j]);
			म_लिखो(" instead of 0x");
			/* Prपूर्णांक expected value. */
			क्रम (j = 0; j < 4; j++)
				म_लिखो("%08x", vms[NV_VMX_REGS + i][j]);
			म_लिखो(" (expected)\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक पंचांग_संकेत_context_chk()
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
		 * array poपूर्णांकers to it, in that हाल 'vms', and invoke the
		 * संकेत handler installed क्रम SIGUSR1.
		 */
		rc = पंचांग_संकेत_self_context_load(pid, शून्य, शून्य, vms, शून्य);
		FAIL_IF(rc != pid);
		i++;
	पूर्ण

	वापस (broken);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(पंचांग_संकेत_context_chk, "tm_signal_context_chk_vmx");
पूर्ण
