<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015, Cyril Bur, IBM Corp.
 *
 * This test attempts to see अगर the VMX रेजिस्टरs are correctly reported in a
 * संकेत context. Each worker just spins checking its VMX रेजिस्टरs, at some
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
#समावेश <माला.स>
#समावेश <pthपढ़ो.h>
#समावेश <altivec.h>

#समावेश "utils.h"

/* Number of बार each thपढ़ो should receive the संकेत */
#घोषणा ITERATIONS 10
/*
 * Factor by which to multiply number of online CPUs क्रम total number of
 * worker thपढ़ोs
 */
#घोषणा THREAD_FACTOR 8

__thपढ़ो vector पूर्णांक varray[] = अणुअणु1, 2, 3, 4पूर्ण, अणु5, 6, 7, 8पूर्ण, अणु9, 10,11,12पूर्ण,
	अणु13,14,15,16पूर्ण,अणु17,18,19,20पूर्ण,अणु21,22,23,24पूर्ण,
	अणु25,26,27,28पूर्ण,अणु29,30,31,32पूर्ण,अणु33,34,35,36पूर्ण,
	अणु37,38,39,40पूर्ण,अणु41,42,43,44पूर्ण,अणु45,46,47,48पूर्णपूर्ण;

bool bad_context;
पूर्णांक running;
पूर्णांक thपढ़ोs_starting;

बाह्य पूर्णांक preempt_vmx(vector पूर्णांक *varray, पूर्णांक *thपढ़ोs_starting, पूर्णांक *sentinal);

व्योम संकेत_vmx_sig(पूर्णांक sig, siginfo_t *info, व्योम *context)
अणु
	पूर्णांक i;
	ucontext_t *uc = context;
	mcontext_t *mc = &uc->uc_mcontext;

	/* Only the non अस्थिरs were loaded up */
	क्रम (i = 20; i < 32; i++) अणु
		अगर (स_भेद(mc->v_regs->vrregs[i], &varray[i - 20], 16)) अणु
			पूर्णांक j;
			/*
			 * Shouldn't म_लिखो() in a संकेत handler, however, this is a
			 * test and we've detected failure. Understanding what failed
			 * is paramount. All that happens after this is tests निकास with
			 * failure.
			 */
			म_लिखो("VMX mismatch at reg %d!\n", i);
			म_लिखो("Reg | Actual                  | Expected\n");
			क्रम (j = 20; j < 32; j++) अणु
				म_लिखो("%d  | 0x%04x%04x%04x%04x      | 0x%04x%04x%04x%04x\n", j, mc->v_regs->vrregs[j][0],
					   mc->v_regs->vrregs[j][1], mc->v_regs->vrregs[j][2], mc->v_regs->vrregs[j][3],
					   varray[j - 20][0], varray[j - 20][1], varray[j - 20][2], varray[j - 20][3]);
			पूर्ण
			bad_context = true;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम *संकेत_vmx_c(व्योम *p)
अणु
	पूर्णांक i, j;
	दीर्घ rc;
	काष्ठा sigaction act;
	act.sa_sigaction = संकेत_vmx_sig;
	act.sa_flags = SA_SIGINFO;
	rc = sigaction(SIGUSR1, &act, शून्य);
	अगर (rc)
		वापस p;

	बेक्रम(pthपढ़ो_self());
	क्रम (i = 0; i < 12; i++)
		क्रम (j = 0; j < 4; j++)
			varray[i][j] = अक्रम();

	rc = preempt_vmx(varray, &thपढ़ोs_starting, &running);

	वापस (व्योम *) rc;
पूर्ण

पूर्णांक test_संकेत_vmx(व्योम)
अणु
	पूर्णांक i, j, rc, thपढ़ोs;
	व्योम *rc_p;
	pthपढ़ो_t *tids;

	// vcmpequd used in vmx_यंत्र.S is v2.07
	SKIP_IF(!have_hwcap2(PPC_FEATURE2_ARCH_2_07));

	thपढ़ोs = sysconf(_SC_NPROCESSORS_ONLN) * THREAD_FACTOR;
	tids = दो_स्मृति(thपढ़ोs * माप(pthपढ़ो_t));
	FAIL_IF(!tids);

	running = true;
	thपढ़ोs_starting = thपढ़ोs;
	क्रम (i = 0; i < thपढ़ोs; i++) अणु
		rc = pthपढ़ो_create(&tids[i], शून्य, संकेत_vmx_c, शून्य);
		FAIL_IF(rc);
	पूर्ण

	रखो_बफ(मानक_निकास, शून्य);
	म_लिखो("\tWaiting for %d workers to start... %d", thपढ़ोs, thपढ़ोs_starting);
	जबतक (thपढ़ोs_starting) अणु
		यंत्र अस्थिर("": : :"memory");
		usleep(1000);
		म_लिखो(", %d", thपढ़ोs_starting);
	पूर्ण
	म_लिखो(" ...done\n");

	म_लिखो("\tSending signals to all threads %d times...", ITERATIONS);
	क्रम (i = 0; i < ITERATIONS; i++) अणु
		क्रम (j = 0; j < thपढ़ोs; j++) अणु
			pthपढ़ो_समाप्त(tids[j], SIGUSR1);
		पूर्ण
		sleep(1);
	पूर्ण
	म_लिखो("done\n");

	म_लिखो("\tKilling workers...");
	running = 0;
	क्रम (i = 0; i < thपढ़ोs; i++) अणु
		pthपढ़ो_join(tids[i], &rc_p);

		/*
		 * Harness will say the fail was here, look at why संकेत_vmx
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
	वापस test_harness(test_संकेत_vmx, "vmx_signal");
पूर्ण
