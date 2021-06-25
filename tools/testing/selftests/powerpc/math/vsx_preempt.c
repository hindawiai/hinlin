<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015, Cyril Bur, IBM Corp.
 *
 * This test attempts to see अगर the VSX रेजिस्टरs change across preemption.
 * There is no way to be sure preemption happened so this test just
 * uses many thपढ़ोs and a दीर्घ रुको. As such, a successful test
 * करोesn't mean much but a failure is bad.
 */

#समावेश <मानकपन.स>
#समावेश <माला.स>
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

/*
 * Ensure there is twice the number of non-अस्थिर VMX regs!
 * check_vmx() is going to use the other half as space to put the live
 * रेजिस्टरs beक्रमe calling vsx_स_भेद()
 */
__thपढ़ो vector पूर्णांक varray[24] = अणु
	अणु1, 2, 3, 4 पूर्ण, अणु5, 6, 7, 8 पूर्ण, अणु9, 10,11,12पूर्ण,
	अणु13,14,15,16पूर्ण, अणु17,18,19,20पूर्ण, अणु21,22,23,24पूर्ण,
	अणु25,26,27,28पूर्ण, अणु29,30,31,32पूर्ण, अणु33,34,35,36पूर्ण,
	अणु37,38,39,40पूर्ण, अणु41,42,43,44पूर्ण, अणु45,46,47,48पूर्ण
पूर्ण;

पूर्णांक thपढ़ोs_starting;
पूर्णांक running;

बाह्य दीर्घ preempt_vsx(vector पूर्णांक *varray, पूर्णांक *thपढ़ोs_starting, पूर्णांक *running);

दीर्घ vsx_स_भेद(vector पूर्णांक *a) अणु
	vector पूर्णांक zero = अणु0, 0, 0, 0पूर्ण;
	पूर्णांक i;

	FAIL_IF(a != varray);

	क्रम(i = 0; i < 12; i++) अणु
		अगर (स_भेद(&a[i + 12], &zero, माप(vector पूर्णांक)) == 0) अणु
			ख_लिखो(मानक_त्रुटि, "Detected zero from the VSX reg %d\n", i + 12);
			वापस 2;
		पूर्ण
	पूर्ण

	अगर (स_भेद(a, &a[12], 12 * माप(vector पूर्णांक))) अणु
		दीर्घ *p = (दीर्घ *)a;
		ख_लिखो(मानक_त्रुटि, "VSX mismatch\n");
		क्रम (i = 0; i < 24; i=i+2)
			ख_लिखो(मानक_त्रुटि, "%d: 0x%08lx%08lx | 0x%08lx%08lx\n",
					i/2 + i%2 + 20, p[i], p[i + 1], p[i + 24], p[i + 25]);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

व्योम *preempt_vsx_c(व्योम *p)
अणु
	पूर्णांक i, j;
	दीर्घ rc;
	बेक्रम(pthपढ़ो_self());
	क्रम (i = 0; i < 12; i++)
		क्रम (j = 0; j < 4; j++) अणु
			varray[i][j] = अक्रम();
			/* Don't want zero because it hides kernel problems */
			अगर (varray[i][j] == 0)
				j--;
		पूर्ण
	rc = preempt_vsx(varray, &thपढ़ोs_starting, &running);
	अगर (rc == 2)
		ख_लिखो(मानक_त्रुटि, "Caught zeros in VSX compares\n");
	वापस (व्योम *)rc;
पूर्ण

पूर्णांक test_preempt_vsx(व्योम)
अणु
	पूर्णांक i, rc, thपढ़ोs;
	pthपढ़ो_t *tids;

	SKIP_IF(!have_hwcap(PPC_FEATURE_HAS_VSX));

	thपढ़ोs = sysconf(_SC_NPROCESSORS_ONLN) * THREAD_FACTOR;
	tids = दो_स्मृति(thपढ़ोs * माप(pthपढ़ो_t));
	FAIL_IF(!tids);

	running = true;
	thपढ़ोs_starting = thपढ़ोs;
	क्रम (i = 0; i < thपढ़ोs; i++) अणु
		rc = pthपढ़ो_create(&tids[i], शून्य, preempt_vsx_c, शून्य);
		FAIL_IF(rc);
	पूर्ण

	रखो_बफ(मानक_निकास, शून्य);
	/* Not really nessesary but nice to रुको क्रम every thपढ़ो to start */
	म_लिखो("\tWaiting for %d workers to start...", thपढ़ोs_starting);
	जबतक(thपढ़ोs_starting)
		यंत्र अस्थिर("": : :"memory");
	म_लिखो("done\n");

	म_लिखो("\tWaiting for %d seconds to let some workers get preempted...", PREEMPT_TIME);
	sleep(PREEMPT_TIME);
	म_लिखो("done\n");

	म_लिखो("\tStopping workers...");
	/*
	 * Working are checking this value every loop. In preempt_vsx 'cmpwi r5,0; bne 2b'.
	 * r5 will have loaded the value of running.
	 */
	running = 0;
	क्रम (i = 0; i < thपढ़ोs; i++) अणु
		व्योम *rc_p;
		pthपढ़ो_join(tids[i], &rc_p);

		/*
		 * Harness will say the fail was here, look at why preempt_vsx
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
	वापस test_harness(test_preempt_vsx, "vsx_preempt");
पूर्ण
