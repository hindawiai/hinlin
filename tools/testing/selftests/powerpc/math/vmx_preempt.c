<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015, Cyril Bur, IBM Corp.
 *
 * This test attempts to see अगर the VMX रेजिस्टरs change across preemption.
 * Two things should be noted here a) The check_vmx function in यंत्र only checks
 * the non अस्थिर रेजिस्टरs as it is reused from the syscall test b) There is
 * no way to be sure preemption happened so this test just uses many thपढ़ोs
 * and a दीर्घ रुको. As such, a successful test करोesn't mean much but a failure
 * is bad.
 */

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <मानककोष.स>
#समावेश <pthपढ़ो.h>

#समावेश "utils.h"

/* Time to रुको क्रम workers to get preempted (seconds) */
#घोषणा PREEMPT_TIME 20
/*
 * Factor by which to multiply number of online CPUs क्रम total number of
 * worker thपढ़ोs
 */
#घोषणा THREAD_FACTOR 8

__thपढ़ो vector पूर्णांक varray[] = अणुअणु1, 2, 3, 4पूर्ण, अणु5, 6, 7, 8पूर्ण, अणु9, 10,11,12पूर्ण,
	अणु13,14,15,16पूर्ण,अणु17,18,19,20पूर्ण,अणु21,22,23,24पूर्ण,
	अणु25,26,27,28पूर्ण,अणु29,30,31,32पूर्ण,अणु33,34,35,36पूर्ण,
	अणु37,38,39,40पूर्ण,अणु41,42,43,44पूर्ण,अणु45,46,47,48पूर्णपूर्ण;

पूर्णांक thपढ़ोs_starting;
पूर्णांक running;

बाह्य व्योम preempt_vmx(vector पूर्णांक *varray, पूर्णांक *thपढ़ोs_starting, पूर्णांक *running);

व्योम *preempt_vmx_c(व्योम *p)
अणु
	पूर्णांक i, j;
	बेक्रम(pthपढ़ो_self());
	क्रम (i = 0; i < 12; i++)
		क्रम (j = 0; j < 4; j++)
			varray[i][j] = अक्रम();

	/* Test fails अगर it ever वापसs */
	preempt_vmx(varray, &thपढ़ोs_starting, &running);
	वापस p;
पूर्ण

पूर्णांक test_preempt_vmx(व्योम)
अणु
	पूर्णांक i, rc, thपढ़ोs;
	pthपढ़ो_t *tids;

	// vcmpequd used in vmx_यंत्र.S is v2.07
	SKIP_IF(!have_hwcap2(PPC_FEATURE2_ARCH_2_07));

	thपढ़ोs = sysconf(_SC_NPROCESSORS_ONLN) * THREAD_FACTOR;
	tids = दो_स्मृति(thपढ़ोs * माप(pthपढ़ो_t));
	FAIL_IF(!tids);

	running = true;
	thपढ़ोs_starting = thपढ़ोs;
	क्रम (i = 0; i < thपढ़ोs; i++) अणु
		rc = pthपढ़ो_create(&tids[i], शून्य, preempt_vmx_c, शून्य);
		FAIL_IF(rc);
	पूर्ण

	रखो_बफ(मानक_निकास, शून्य);
	/* Not really nessesary but nice to रुको क्रम every thपढ़ो to start */
	म_लिखो("\tWaiting for all workers to start...");
	जबतक(thपढ़ोs_starting)
		यंत्र अस्थिर("": : :"memory");
	म_लिखो("done\n");

	म_लिखो("\tWaiting for %d seconds to let some workers get preempted...", PREEMPT_TIME);
	sleep(PREEMPT_TIME);
	म_लिखो("done\n");

	म_लिखो("\tStopping workers...");
	/*
	 * Working are checking this value every loop. In preempt_vmx 'cmpwi r5,0; bne 2b'.
	 * r5 will have loaded the value of running.
	 */
	running = 0;
	क्रम (i = 0; i < thपढ़ोs; i++) अणु
		व्योम *rc_p;
		pthपढ़ो_join(tids[i], &rc_p);

		/*
		 * Harness will say the fail was here, look at why preempt_vmx
		 * वापसed
		 */
		अगर ((दीर्घ) rc_p)
			म_लिखो("oops\n");
		FAIL_IF((दीर्घ) rc_p);
	पूर्ण
	म_लिखो("done\n");

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(test_preempt_vmx, "vmx_preempt");
पूर्ण
