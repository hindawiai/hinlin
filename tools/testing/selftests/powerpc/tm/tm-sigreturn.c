<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2015, Laurent Dufour, IBM Corp.
 *
 * Test the kernel's संकेत वापसing code to check reclaim is करोne अगर the
 * sigवापस() is called जबतक in a transaction (suspended since active is
 * alपढ़ोy dropped trough the प्रणाली call path).
 *
 * The kernel must discard the transaction when entering sigवापस, since
 * restoring the potential TM SPRS from the संकेत frame is requiring to not be
 * in a transaction.
 */

#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#समावेश "tm.h"
#समावेश "utils.h"


व्योम handler(पूर्णांक sig)
अणु
	uपूर्णांक64_t ret;

	यंत्र __अस्थिर__(
		"li             3,1             ;"
		"tbegin.                        ;"
		"beq            1f              ;"
		"li             3,0             ;"
		"tsuspend.                      ;"
		"1:                             ;"
		"std%X[ret]     3, %[ret]       ;"
		: [ret] "=m"(ret)
		:
		: "memory", "3", "cr0");

	अगर (ret)
		निकास(1);

	/*
	 * We वापस from the संकेत handle जबतक in a suspended transaction
	 */
पूर्ण


पूर्णांक पंचांग_sigवापस(व्योम)
अणु
	काष्ठा sigaction sa;
	uपूर्णांक64_t ret = 0;

	SKIP_IF(!have_hपंचांग());
	SKIP_IF(!is_ppc64le());

	स_रखो(&sa, 0, माप(sa));
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);

	अगर (sigaction(संक_अंश, &sa, शून्य))
		निकास(1);

	यंत्र __अस्थिर__(
		"tbegin.                        ;"
		"beq            1f              ;"
		"li             3,0             ;"
		"std            3,0(3)          ;" /* trigger SEGV */
		"li             3,1             ;"
		"std%X[ret]     3,%[ret]        ;"
		"tend.                          ;"
		"b              2f              ;"
		"1:                             ;"
		"li             3,2             ;"
		"std%X[ret]     3,%[ret]        ;"
		"2:                             ;"
		: [ret] "=m"(ret)
		:
		: "memory", "3", "cr0");

	अगर (ret != 2)
		निकास(1);

	निकास(0);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(पंचांग_sigवापस, "tm_sigreturn");
पूर्ण
