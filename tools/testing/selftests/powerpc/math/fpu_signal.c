<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015, Cyril Bur, IBM Corp.
 *
 * This test attempts to see अगर the FPU रेजिस्टरs are correctly reported in a
 * संकेत context. Each worker just spins checking its FPU रेजिस्टरs, at some
 * poपूर्णांक a संकेत will पूर्णांकerrupt it and C code will check the संकेत context
 * ensuring it is also the same.
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

/* Number of बार each thपढ़ो should receive the संकेत */
#घोषणा ITERATIONS 10
/*
 * Factor by which to multiply number of online CPUs क्रम total number of
 * worker thपढ़ोs
 */
#घोषणा THREAD_FACTOR 8

__thपढ़ो द्विगुन darray[] = अणु0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
		     1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0,
		     2.1पूर्ण;

bool bad_context;
पूर्णांक thपढ़ोs_starting;
पूर्णांक running;

बाह्य दीर्घ preempt_fpu(द्विगुन *darray, पूर्णांक *thपढ़ोs_starting, पूर्णांक *running);

व्योम संकेत_fpu_sig(पूर्णांक sig, siginfo_t *info, व्योम *context)
अणु
	पूर्णांक i;
	ucontext_t *uc = context;
	mcontext_t *mc = &uc->uc_mcontext;

	/* Only the non अस्थिरs were loaded up */
	क्रम (i = 14; i < 32; i++) अणु
		अगर (mc->fp_regs[i] != darray[i - 14]) अणु
			bad_context = true;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम *संकेत_fpu_c(व्योम *p)
अणु
	पूर्णांक i;
	दीर्घ rc;
	काष्ठा sigaction act;
	act.sa_sigaction = संकेत_fpu_sig;
	act.sa_flags = SA_SIGINFO;
	rc = sigaction(SIGUSR1, &act, शून्य);
	अगर (rc)
		वापस p;

	बेक्रम(pthपढ़ो_self());
	क्रम (i = 0; i < 21; i++)
		darray[i] = अक्रम();

	rc = preempt_fpu(darray, &thपढ़ोs_starting, &running);

	वापस (व्योम *) rc;
पूर्ण

पूर्णांक test_संकेत_fpu(व्योम)
अणु
	पूर्णांक i, j, rc, thपढ़ोs;
	व्योम *rc_p;
	pthपढ़ो_t *tids;

	thपढ़ोs = sysconf(_SC_NPROCESSORS_ONLN) * THREAD_FACTOR;
	tids = दो_स्मृति(thपढ़ोs * माप(pthपढ़ो_t));
	FAIL_IF(!tids);

	running = true;
	thपढ़ोs_starting = thपढ़ोs;
	क्रम (i = 0; i < thपढ़ोs; i++) अणु
		rc = pthपढ़ो_create(&tids[i], शून्य, संकेत_fpu_c, शून्य);
		FAIL_IF(rc);
	पूर्ण

	रखो_बफ(मानक_निकास, शून्य);
	म_लिखो("\tWaiting for all workers to start...");
	जबतक (thपढ़ोs_starting)
		यंत्र अस्थिर("": : :"memory");
	म_लिखो("done\n");

	म_लिखो("\tSending signals to all threads %d times...", ITERATIONS);
	क्रम (i = 0; i < ITERATIONS; i++) अणु
		क्रम (j = 0; j < thपढ़ोs; j++) अणु
			pthपढ़ो_समाप्त(tids[j], SIGUSR1);
		पूर्ण
		sleep(1);
	पूर्ण
	म_लिखो("done\n");

	म_लिखो("\tStopping workers...");
	running = 0;
	क्रम (i = 0; i < thपढ़ोs; i++) अणु
		pthपढ़ो_join(tids[i], &rc_p);

		/*
		 * Harness will say the fail was here, look at why संकेत_fpu
		 * वापसed
		 */
		अगर ((दीर्घ) rc_p || bad_context)
			म_लिखो("oops\n");
		अगर (bad_context)
			ख_लिखो(मानक_त्रुटि, "\t!! bad_context is true\n");
		FAIL_IF((दीर्घ) rc_p || bad_context);
	पूर्ण
	म_लिखो("done\n");

	मुक्त(tids);
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(test_संकेत_fpu, "fpu_signal");
पूर्ण
