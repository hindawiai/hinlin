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

#घोषणा NV_VSX_REGS 12 /* Number of VSX रेजिस्टरs to check. */
#घोषणा VSX20 20 /* First VSX रेजिस्टर to check in vsr20-vsr31 subset */
#घोषणा FPR20 20 /* FPR20 overlaps VSX20 most signअगरicant द्विगुनword */

दीर्घ पंचांग_संकेत_self_context_load(pid_t pid, दीर्घ *gprs, द्विगुन *fps, vector पूर्णांक *vms, vector पूर्णांक *vss);

अटल संक_पूर्ण_प्रकार fail, broken;

/* Test only 12 vsx रेजिस्टरs from vsr20 to vsr31 */
vector पूर्णांक vsxs[] = अणु
	/* First context will be set with these values, i.e. non-speculative */
	/* VSX20     ,  VSX21      , ... */
	अणु 1, 2, 3, 4पूर्ण,अणु 5, 6, 7, 8पूर्ण,अणु 9,10,11,12पूर्ण,
	अणु13,14,15,16पूर्ण,अणु17,18,19,20पूर्ण,अणु21,22,23,24पूर्ण,
	अणु25,26,27,28पूर्ण,अणु29,30,31,32पूर्ण,अणु33,34,35,36पूर्ण,
	अणु37,38,39,40पूर्ण,अणु41,42,43,44पूर्ण,अणु45,46,47,48पूर्ण,
	/* Second context will be set with these values, i.e. speculative */
	/* VSX20         ,  VSX21          , ... */
	अणु-1, -2, -3, -4 पूर्ण,अणु-5, -6, -7, -8 पूर्ण,अणु-9, -10,-11,-12पूर्ण,
	अणु-13,-14,-15,-16पूर्ण,अणु-17,-18,-19,-20पूर्ण,अणु-21,-22,-23,-24पूर्ण,
	अणु-25,-26,-27,-28पूर्ण,अणु-29,-30,-31,-32पूर्ण,अणु-33,-34,-35,-36पूर्ण,
	अणु-37,-38,-39,-40पूर्ण,अणु-41,-42,-43,-44पूर्ण,अणु-45,-46,-47,-48पूर्ण
पूर्ण;

अटल व्योम संकेत_usr1(पूर्णांक signum, siginfo_t *info, व्योम *uc)
अणु
	पूर्णांक i, j;
	uपूर्णांक8_t vsx[माप(vector पूर्णांक)];
	uपूर्णांक8_t vsx_पंचांग[माप(vector पूर्णांक)];
	ucontext_t *ucp = uc;
	ucontext_t *पंचांग_ucp = ucp->uc_link;

	/*
	 * FP रेजिस्टरs and VMX रेजिस्टरs overlap the VSX रेजिस्टरs.
	 *
	 * FP रेजिस्टरs (f0-31) overlap the most signअगरicant 64 bits of VSX
	 * रेजिस्टरs vsr0-31, whilst VMX रेजिस्टरs vr0-31, being 128-bit like
	 * the VSX रेजिस्टरs, overlap fully the other half of VSX रेजिस्टरs,
	 * i.e. vr0-31 overlaps fully vsr32-63.
	 *
	 * Due to compatibility and historical reasons (VMX/Altivec support
	 * appeared first on the architecture), VMX रेजिस्टरs vr0-31 (so VSX
	 * half vsr32-63 too) are stored right after the v_regs poपूर्णांकer, in an
	 * area allocated क्रम 'vmx_reverse' array (please see
	 * arch/घातerpc/include/uapi/यंत्र/sigcontext.h क्रम details about the
	 * mcontext_t काष्ठाure on Power).
	 *
	 * The other VSX half (vsr0-31) is hence stored below vr0-31/vsr32-63
	 * रेजिस्टरs, but only the least signअगरicant 64 bits of vsr0-31. The
	 * most signअगरicant 64 bits of vsr0-31 (f0-31), as it overlaps the FP
	 * रेजिस्टरs, is kept in fp_regs.
	 *
	 * v_regs is a 16 byte aligned poपूर्णांकer at the start of vmx_reserve
	 * (vmx_reserve may or may not be 16 aligned) where the v_regs काष्ठाure
	 * exists, so v_regs poपूर्णांकs to where vr0-31 / vsr32-63 रेजिस्टरs are
	 * fully stored. Since v_regs type is elf_vrregset_t, v_regs + 1
	 * skips all the slots used to store vr0-31 / vsr32-64 and poपूर्णांकs to
	 * part of one VSX half, i.e. v_regs + 1 poपूर्णांकs to the least signअगरicant
	 * 64 bits of vsr0-31. The other part of this half (the most signअगरicant
	 * part of vsr0-31) is stored in fp_regs.
	 *
	 */
	/* Get poपूर्णांकer to least signअगरicant द्विगुनword of vsr0-31 */
	दीर्घ *vsx_ptr = (दीर्घ *)(ucp->uc_mcontext.v_regs + 1);
	दीर्घ *पंचांग_vsx_ptr = (दीर्घ *)(पंचांग_ucp->uc_mcontext.v_regs + 1);

	/* Check first context. Prपूर्णांक all mismatches. */
	क्रम (i = 0; i < NV_VSX_REGS; i++) अणु
		/*
		 * Copy VSX most signअगरicant द्विगुनword from fp_regs and
		 * copy VSX least signअगरicant one from 64-bit slots below
		 * saved VMX रेजिस्टरs.
		 */
		स_नकल(vsx, &ucp->uc_mcontext.fp_regs[FPR20 + i], 8);
		स_नकल(vsx + 8, &vsx_ptr[VSX20 + i], 8);

		fail = स_भेद(vsx, &vsxs[i], माप(vector पूर्णांक));

		अगर (fail) अणु
			broken = 1;
			म_लिखो("VSX%d (1st context) == 0x", VSX20 + i);
			क्रम (j = 0; j < 16; j++)
				म_लिखो("%02x", vsx[j]);
			म_लिखो(" instead of 0x");
			क्रम (j = 0; j < 4; j++)
				म_लिखो("%08x", vsxs[i][j]);
			म_लिखो(" (expected)\n");
		पूर्ण
	पूर्ण

	/* Check second context. Prपूर्णांक all mismatches. */
	क्रम (i = 0; i < NV_VSX_REGS; i++) अणु
		/*
		 * Copy VSX most signअगरicant द्विगुनword from fp_regs and
		 * copy VSX least signअगरicant one from 64-bit slots below
		 * saved VMX रेजिस्टरs.
		 */
		स_नकल(vsx_पंचांग, &पंचांग_ucp->uc_mcontext.fp_regs[FPR20 + i], 8);
		स_नकल(vsx_पंचांग + 8, &पंचांग_vsx_ptr[VSX20 + i], 8);

		fail = स_भेद(vsx_पंचांग, &vsxs[NV_VSX_REGS + i], माप(vector पूर्णांक));

		अगर (fail) अणु
			broken = 1;
			म_लिखो("VSX%d (2nd context) == 0x", VSX20 + i);
			क्रम (j = 0; j < 16; j++)
				म_लिखो("%02x", vsx_पंचांग[j]);
			म_लिखो(" instead of 0x");
			क्रम (j = 0; j < 4; j++)
				म_लिखो("%08x", vsxs[NV_VSX_REGS + i][j]);
			म_लिखो("(expected)\n");
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
                * array poपूर्णांकers to it, in that हाल 'vsxs', and invoke the
                * संकेत handler installed क्रम SIGUSR1.
                */
		rc = पंचांग_संकेत_self_context_load(pid, शून्य, शून्य, शून्य, vsxs);
		FAIL_IF(rc != pid);
		i++;
	पूर्ण

	वापस (broken);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(पंचांग_संकेत_context_chk, "tm_signal_context_chk_vsx");
पूर्ण
