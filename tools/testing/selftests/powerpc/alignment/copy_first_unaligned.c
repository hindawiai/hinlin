<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2016, Chris Smart, IBM Corporation.
 *
 * Calls to copy_first which are not 128-byte aligned should be
 * caught and sent a SIGBUS.
 */

#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश "utils.h"
#समावेश "instructions.h"

अचिन्हित पूर्णांक expected_inकाष्ठाion = PPC_INST_COPY_FIRST;
अचिन्हित पूर्णांक inकाष्ठाion_mask = 0xfc2007fe;

व्योम संकेत_action_handler(पूर्णांक संकेत_num, siginfo_t *info, व्योम *ptr)
अणु
	ucontext_t *ctx = ptr;
#अगर_घोषित __घातerpc64__
	अचिन्हित पूर्णांक *pc = (अचिन्हित पूर्णांक *)ctx->uc_mcontext.gp_regs[PT_NIP];
#अन्यथा
	अचिन्हित पूर्णांक *pc = (अचिन्हित पूर्णांक *)ctx->uc_mcontext.uc_regs->gregs[PT_NIP];
#पूर्ण_अगर

	/*
	 * Check that the संकेत was on the correct inकाष्ठाion, using a
	 * mask because the compiler assigns the रेजिस्टर at RB.
	 */
	अगर ((*pc & inकाष्ठाion_mask) == expected_inकाष्ठाion)
		_निकास(0); /* We hit the right inकाष्ठाion */

	_निकास(1);
पूर्ण

व्योम setup_संकेत_handler(व्योम)
अणु
	काष्ठा sigaction संकेत_action;

	स_रखो(&संकेत_action, 0, माप(संकेत_action));
	संकेत_action.sa_sigaction = संकेत_action_handler;
	संकेत_action.sa_flags = SA_SIGINFO;
	sigaction(SIGBUS, &संकेत_action, शून्य);
पूर्ण

अक्षर cacheline_buf[128] __cacheline_aligned;

पूर्णांक test_copy_first_unaligned(व्योम)
अणु
	/* Only run this test on a P9 or later */
	SKIP_IF(!have_hwcap2(PPC_FEATURE2_ARCH_3_00));

	/* Register our संकेत handler with SIGBUS */
	setup_संकेत_handler();

	/* +1 makes buf unaligned */
	copy_first(cacheline_buf+1);

	/* We should not get here */
	वापस 1;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(test_copy_first_unaligned, "test_copy_first_unaligned");
पूर्ण
