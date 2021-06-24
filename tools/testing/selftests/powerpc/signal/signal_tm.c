<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2016, Cyril Bur, IBM Corp.
 *
 * Sending one self a संकेत should always get delivered.
 */

#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <संकेत.स>
#समावेश <unistd.h>

#समावेश <altivec.h>

#समावेश "utils.h"
#समावेश "../tm/tm.h"

#घोषणा MAX_ATTEMPT 500000
#घोषणा TIMEOUT 10

बाह्य दीर्घ पंचांग_संकेत_self(pid_t pid, पूर्णांक sig, दीर्घ *ret);

अटल संक_पूर्ण_प्रकार संकेतed;
अटल संक_पूर्ण_प्रकार fail;

अटल व्योम संकेत_handler(पूर्णांक sig)
अणु
	अगर (tcheck_active()) अणु
		fail = 2;
		वापस;
	पूर्ण

	अगर (sig == SIGUSR1)
		संकेतed = 1;
	अन्यथा
		fail = 1;
पूर्ण

अटल पूर्णांक test_संकेत_पंचांग()
अणु
	पूर्णांक i;
	काष्ठा sigaction act;

	act.sa_handler = संकेत_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	अगर (sigaction(SIGUSR1, &act, शून्य) < 0) अणु
		लिखो_त्रुटि("sigaction SIGUSR1");
		निकास(1);
	पूर्ण
	अगर (sigaction(SIGALRM, &act, शून्य) < 0) अणु
		लिखो_त्रुटि("sigaction SIGALRM");
		निकास(1);
	पूर्ण

	SKIP_IF(!have_hपंचांग());

	क्रम (i = 0; i < MAX_ATTEMPT; i++) अणु
		/*
		 * If anything bad happens in ASM and we fail to set ret
		 * because *handwave* TM this will cause failure
		 */
		दीर्घ ret = 0xdead;
		दीर्घ rc = 0xbeef;

		alarm(0); /* Disable any pending */
		संकेतed = 0;
		alarm(TIMEOUT);
		FAIL_IF(tcheck_transactional());
		rc = पंचांग_संकेत_self(getpid(), SIGUSR1, &ret);
		अगर (ret == 0xdead)
			/*
			 * This basically means the transaction पातed beक्रमe we
			 * even got to the suspend... this is crazy but it
			 * happens.
			 * Yes this also means we might never make क्रमward
			 * progress... the alarm() will trip eventually...
			 */
			जारी;

		अगर (rc || ret) अणु
			/* Ret is actually an त्रुटि_सं */
			म_लिखो("TEXASR 0x%016lx, TFIAR 0x%016lx\n",
					__builtin_get_texasr(), __builtin_get_tfiar());
			ख_लिखो(मानक_त्रुटि, "(%d) Fail reason: %d rc=0x%lx ret=0x%lx\n",
					i, fail, rc, ret);
			FAIL_IF(ret);
		पूर्ण
		जबतक(!संकेतed && !fail)
			यंत्र अस्थिर("": : :"memory");
		अगर (!संकेतed) अणु
			ख_लिखो(मानक_त्रुटि, "(%d) Fail reason: %d rc=0x%lx ret=0x%lx\n",
					i, fail, rc, ret);
			FAIL_IF(fail); /* For the line number */
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(test_संकेत_पंचांग, "signal_tm");
पूर्ण
