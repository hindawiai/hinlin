<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2015, Michael Neuling, IBM Corp.
 *
 * Test the kernel's signal delievery code to ensure that we don't
 * trelaim twice in the kernel संकेत delivery code.  This can happen
 * अगर we trigger a संकेत when in a transaction and the stack poपूर्णांकer
 * is bogus.
 *
 * This test हाल रेजिस्टरs a SEGV handler, sets the stack poपूर्णांकer
 * (r1) to शून्य, starts a transaction and then generates a SEGV.  The
 * SEGV should be handled but we निकास here as the stack poपूर्णांकer is
 * invalid and hance we can't sigवापस.  We only need to check that
 * this flow करोesn't crash the kernel.
 */

#समावेश <unistd.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <संकेत.स>

#समावेश "utils.h"
#समावेश "tm.h"

व्योम संकेत_segv(पूर्णांक signum)
अणु
	/* This should never actually run since stack is foobar */
	निकास(1);
पूर्ण

पूर्णांक पंचांग_संकेत_stack()
अणु
	पूर्णांक pid;

	SKIP_IF(!have_hपंचांग());

	pid = विभाजन();
	अगर (pid < 0)
		निकास(1);

	अगर (pid) अणु /* Parent */
		/*
		 * It's likely the whole machine will crash here so अगर
		 * the child ever निकासs, we are good.
		 */
		रुको(शून्य);
		वापस 0;
	पूर्ण

	/*
	 * The flow here is:
	 * 1) रेजिस्टर a संकेत handler (so संकेत delievery occurs)
	 * 2) make stack poपूर्णांकer (r1) = शून्य
	 * 3) start transaction
	 * 4) cause segv
	 */
	अगर (संकेत(संक_अंश, संकेत_segv) == संक_त्रुटि)
		निकास(1);
	यंत्र अस्थिर("li 1, 0 ;"		/* stack ptr == शून्य */
		     "1:"
		     "tbegin.;"
		     "beq 1b ;"			/* retry क्रमever */
		     "tsuspend.;"
		     "ld 2, 0(1) ;"		/* trigger segv" */
		     : : : "memory");

	/* This should never get here due to above segv */
	वापस 1;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(पंचांग_संकेत_stack, "tm_signal_stack");
पूर्ण
