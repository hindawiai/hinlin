<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015, Cyril Bur, IBM Corp.
 *
 * This test attempts to see अगर the FPU रेजिस्टरs change across preemption.
 * Two things should be noted here a) The check_fpu function in यंत्र only checks
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


__thपढ़ो द्विगुन darray[] = अणु0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
		     1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0,
		     2.1पूर्ण;

पूर्णांक thपढ़ोs_starting;
पूर्णांक running;

बाह्य व्योम preempt_fpu(द्विगुन *darray, पूर्णांक *thपढ़ोs_starting, पूर्णांक *running);

व्योम *preempt_fpu_c(व्योम *p)
अणु
	पूर्णांक i;
	बेक्रम(pthपढ़ो_self());
	क्रम (i = 0; i < 21; i++)
		darray[i] = अक्रम();

	/* Test failed अगर it ever वापसs */
	preempt_fpu(darray, &thपढ़ोs_starting, &running);

	वापस p;
पूर्ण

पूर्णांक test_preempt_fpu(व्योम)
अणु
	पूर्णांक i, rc, thपढ़ोs;
	pthपढ़ो_t *tids;

	thपढ़ोs = sysconf(_SC_NPROCESSORS_ONLN) * THREAD_FACTOR;
	tids = दो_स्मृति((thपढ़ोs) * माप(pthपढ़ो_t));
	FAIL_IF(!tids);

	running = true;
	thपढ़ोs_starting = thपढ़ोs;
	क्रम (i = 0; i < thपढ़ोs; i++) अणु
		rc = pthपढ़ो_create(&tids[i], शून्य, preempt_fpu_c, शून्य);
		FAIL_IF(rc);
	पूर्ण

	रखो_बफ(मानक_निकास, शून्य);
	/* Not really necessary but nice to रुको क्रम every thपढ़ो to start */
	म_लिखो("\tWaiting for all workers to start...");
	जबतक(thपढ़ोs_starting)
		यंत्र अस्थिर("": : :"memory");
	म_लिखो("done\n");

	म_लिखो("\tWaiting for %d seconds to let some workers get preempted...", PREEMPT_TIME);
	sleep(PREEMPT_TIME);
	म_लिखो("done\n");

	म_लिखो("\tStopping workers...");
	/*
	 * Working are checking this value every loop. In preempt_fpu 'cmpwi r5,0; bne 2b'.
	 * r5 will have loaded the value of running.
	 */
	running = 0;
	क्रम (i = 0; i < thपढ़ोs; i++) अणु
		व्योम *rc_p;
		pthपढ़ो_join(tids[i], &rc_p);

		/*
		 * Harness will say the fail was here, look at why preempt_fpu
		 * वापसed
		 */
		अगर ((दीर्घ) rc_p)
			म_लिखो("oops\n");
		FAIL_IF((दीर्घ) rc_p);
	पूर्ण
	म_लिखो("done\n");

	मुक्त(tids);
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(test_preempt_fpu, "fpu_preempt");
पूर्ण
