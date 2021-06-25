<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2015, Michael Neuling, IBM Corp.
 *
 * Test the kernel's signal return code to ensure that it doesn't
 * crash when both the transactional and suspend MSR bits are set in
 * the संकेत context.
 *
 * For this test, we send ourselves a SIGUSR1.  In the SIGUSR1 handler
 * we modअगरy the संकेत context to set both MSR TM S and T bits (which
 * is "reserved" by the PowerISA). When we वापस from the संकेत
 * handler (implicit sigवापस), the kernel should detect reserved MSR
 * value and send us with a संक_अंश.
 */

#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <संकेत.स>
#समावेश <unistd.h>

#समावेश "utils.h"
#समावेश "tm.h"

पूर्णांक segv_expected = 0;

व्योम संकेत_segv(पूर्णांक signum)
अणु
	अगर (segv_expected && (signum == संक_अंश))
		_निकास(0);
	_निकास(1);
पूर्ण

व्योम संकेत_usr1(पूर्णांक signum, siginfo_t *info, व्योम *uc)
अणु
	ucontext_t *ucp = uc;

	/* Link पंचांग checkpoपूर्णांकed context to normal context */
	ucp->uc_link = ucp;
	/* Set all TM bits so that the context is now invalid */
#अगर_घोषित __घातerpc64__
	ucp->uc_mcontext.gp_regs[PT_MSR] |= (7ULL << 32);
#अन्यथा
	ucp->uc_mcontext.uc_regs->gregs[PT_MSR] |= (7ULL);
#पूर्ण_अगर
	/* Should segv on वापस becuase of invalid context */
	segv_expected = 1;
पूर्ण

पूर्णांक पंचांग_संकेत_msr_resv()
अणु
	काष्ठा sigaction act;

	SKIP_IF(!have_hपंचांग());

	act.sa_sigaction = संकेत_usr1;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	अगर (sigaction(SIGUSR1, &act, शून्य) < 0) अणु
		लिखो_त्रुटि("sigaction sigusr1");
		निकास(1);
	पूर्ण
	अगर (संकेत(संक_अंश, संकेत_segv) == संक_त्रुटि)
		निकास(1);

	उठाओ(SIGUSR1);

	/* We shouldn't get here as we निकास in the segv handler */
	वापस 1;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(पंचांग_संकेत_msr_resv, "tm_signal_msr_resv");
पूर्ण
