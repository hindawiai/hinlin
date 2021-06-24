<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2017, Gustavo Romero, Breno Leitao, Cyril Bur, IBM Corp.
 *
 * Force FP, VEC and VSX unavailable exception during transaction in all
 * possible scenarios regarding the MSR.FP and MSR.VEC state, e.g. when FP
 * is enable and VEC is disable, when FP is disable and VEC is enable, and
 * so on. Then we check अगर the restored state is correctly set क्रम the
 * FP and VEC रेजिस्टरs to the previous state we set just beक्रमe we entered
 * in TM, i.e. we check अगर it corrupts somehow the recheckpoपूर्णांकed FP and
 * VEC/Altivec रेजिस्टरs on पातion due to an unavailable exception in TM.
 * N.B. In this test we करो not test all the FP/Altivec/VSX रेजिस्टरs क्रम
 * corruption, but only क्रम रेजिस्टरs vs0 and vs32, which are respectively
 * representatives of FP and VEC/Altivec reg sets.
 */

#घोषणा _GNU_SOURCE
#समावेश <error.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <stdbool.h>
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>

#समावेश "tm.h"

#घोषणा DEBUG 0

/* Unavailable exceptions to test in HTM */
#घोषणा FP_UNA_EXCEPTION	0
#घोषणा VEC_UNA_EXCEPTION	1
#घोषणा VSX_UNA_EXCEPTION	2

#घोषणा NUM_EXCEPTIONS		3
#घोषणा err_at_line(status, errnum, क्रमmat, ...) \
	error_at_line(status, errnum,  __खाता__, __LINE__, क्रमmat ##__VA_ARGS__)

#घोषणा pr_warn(code, क्रमmat, ...) err_at_line(0, code, क्रमmat, ##__VA_ARGS__)
#घोषणा pr_err(code, क्रमmat, ...) err_at_line(1, code, क्रमmat, ##__VA_ARGS__)

काष्ठा Flags अणु
	पूर्णांक touch_fp;
	पूर्णांक touch_vec;
	पूर्णांक result;
	पूर्णांक exception;
पूर्ण flags;

bool expecting_failure(व्योम)
अणु
	अगर (flags.touch_fp && flags.exception == FP_UNA_EXCEPTION)
		वापस false;

	अगर (flags.touch_vec && flags.exception == VEC_UNA_EXCEPTION)
		वापस false;

	/*
	 * If both FP and VEC are touched it करोes not mean that touching VSX
	 * won't उठाओ an exception. However since FP and VEC state are alपढ़ोy
	 * correctly loaded, the transaction is not पातed (i.e.
	 * treclaimed/trecheckpoपूर्णांकed) and MSR.VSX is just set as 1, so a TM
	 * failure is not expected also in this हाल.
	 */
	अगर ((flags.touch_fp && flags.touch_vec) &&
	     flags.exception == VSX_UNA_EXCEPTION)
		वापस false;

	वापस true;
पूर्ण

/* Check अगर failure occurred whilst in transaction. */
bool is_failure(uपूर्णांक64_t condition_reg)
अणु
	/*
	 * When failure handling occurs, CR0 is set to 0b1010 (0xa). Otherwise
	 * transaction completes without failure and hence reaches out 'tend.'
	 * that sets CR0 to 0b0100 (0x4).
	 */
	वापस ((condition_reg >> 28) & 0xa) == 0xa;
पूर्ण

व्योम *पंचांग_una_ping(व्योम *input)
अणु

	/*
	 * Expected values क्रम vs0 and vs32 after a TM failure. They must never
	 * change, otherwise they got corrupted.
	 */
	uपूर्णांक64_t high_vs0 = 0x5555555555555555;
	uपूर्णांक64_t low_vs0 = 0xffffffffffffffff;
	uपूर्णांक64_t high_vs32 = 0x5555555555555555;
	uपूर्णांक64_t low_vs32 = 0xffffffffffffffff;

	/* Counter क्रम busy रुको */
	uपूर्णांक64_t counter = 0x1ff000000;

	/*
	 * Variable to keep a copy of CR रेजिस्टर content taken just after we
	 * leave the transactional state.
	 */
	uपूर्णांक64_t cr_ = 0;

	/*
	 * Wait a bit so thपढ़ो can get its name "ping". This is not important
	 * to reproduce the issue but it's nice to have क्रम प्रणालीtap debugging.
	 */
	अगर (DEBUG)
		sleep(1);

	म_लिखो("If MSR.FP=%d MSR.VEC=%d: ", flags.touch_fp, flags.touch_vec);

	अगर (flags.exception != FP_UNA_EXCEPTION &&
	    flags.exception != VEC_UNA_EXCEPTION &&
	    flags.exception != VSX_UNA_EXCEPTION) अणु
		म_लिखो("No valid exception specified to test.\n");
		वापस शून्य;
	पूर्ण

	यंत्र (
		/* Prepare to merge low and high. */
		"	mtvsrd		33, %[high_vs0]		;"
		"	mtvsrd		34, %[low_vs0]		;"

		/*
		 * Adjust VS0 expected value after an TM failure,
		 * i.e. vs0 = 0x5555555555555555555FFFFFFFFFFFFFFFF
		 */
		"	xxmrghd		0, 33, 34		;"

		/*
		 * Adjust VS32 expected value after an TM failure,
		 * i.e. vs32 = 0x5555555555555555555FFFFFFFFFFFFFFFF
		 */
		"	xxmrghd		32, 33, 34		;"

		/*
		 * Wait an amount of context चयनes so load_fp and load_vec
		 * overflow and MSR.FP, MSR.VEC, and MSR.VSX become zero (off).
		 */
		"	mtctr		%[counter]		;"

		/* Decrement CTR branch अगर CTR non zero. */
		"1:	bdnz 1b					;"

		/*
		 * Check अगर we want to touch FP prior to the test in order
		 * to set MSR.FP = 1 beक्रमe provoking an unavailable
		 * exception in TM.
		 */
		"	cmpldi		%[touch_fp], 0		;"
		"	beq		no_fp			;"
		"	fadd		10, 10, 10		;"
		"no_fp:						;"

		/*
		 * Check अगर we want to touch VEC prior to the test in order
		 * to set MSR.VEC = 1 beक्रमe provoking an unavailable
		 * exception in TM.
		 */
		"	cmpldi		%[touch_vec], 0		;"
		"	beq		no_vec			;"
		"	vaddcuw		10, 10, 10		;"
		"no_vec:					;"

		/*
		 * Perhaps it would be a better idea to करो the
		 * compares outside transactional context and simply
		 * duplicate code.
		 */
		"	tbegin.					;"
		"	beq		trans_fail		;"

		/* Do we करो FP Unavailable? */
		"	cmpldi		%[exception], %[ex_fp]	;"
		"	bne		1f			;"
		"	fadd		10, 10, 10		;"
		"	b		done			;"

		/* Do we करो VEC Unavailable? */
		"1:	cmpldi		%[exception], %[ex_vec]	;"
		"	bne		2f			;"
		"	vaddcuw		10, 10, 10		;"
		"	b		done			;"

		/*
		 * Not FP or VEC, thereक्रमe VSX. Ensure this
		 * inकाष्ठाion always generates a VSX Unavailable.
		 * ISA 3.0 is tricky here.
		 * (xxmrghd will on ISA 2.07 and ISA 3.0)
		 */
		"2:	xxmrghd		10, 10, 10		;"

		"done:	tend. ;"

		"trans_fail: ;"

		/* Give values back to C. */
		"	mfvsrd		%[high_vs0], 0		;"
		"	xxsldwi		3, 0, 0, 2		;"
		"	mfvsrd		%[low_vs0], 3		;"
		"	mfvsrd		%[high_vs32], 32	;"
		"	xxsldwi		3, 32, 32, 2		;"
		"	mfvsrd		%[low_vs32], 3		;"

		/* Give CR back to C so that it can check what happened. */
		"	mfcr		%[cr_]		;"

		: [high_vs0]  "+r" (high_vs0),
		  [low_vs0]   "+r" (low_vs0),
		  [high_vs32] "=r" (high_vs32),
		  [low_vs32]  "=r" (low_vs32),
		  [cr_]       "+r" (cr_)
		: [touch_fp]  "r"  (flags.touch_fp),
		  [touch_vec] "r"  (flags.touch_vec),
		  [exception] "r"  (flags.exception),
		  [ex_fp]     "i"  (FP_UNA_EXCEPTION),
		  [ex_vec]    "i"  (VEC_UNA_EXCEPTION),
		  [ex_vsx]    "i"  (VSX_UNA_EXCEPTION),
		  [counter]   "r"  (counter)

		: "cr0", "ctr", "v10", "vs0", "vs10", "vs3", "vs32", "vs33",
		  "vs34", "fr10"

		);

	/*
	 * Check अगर we were expecting a failure and it did not occur by checking
	 * CR0 state just after we leave the transaction. Either way we check अगर
	 * vs0 or vs32 got corrupted.
	 */
	अगर (expecting_failure() && !is_failure(cr_)) अणु
		म_लिखो("\n\tExpecting the transaction to fail, %s",
			"but it didn't\n\t");
		flags.result++;
	पूर्ण

	/* Check अगर we were not expecting a failure and a it occurred. */
	अगर (!expecting_failure() && is_failure(cr_) &&
	    !failure_is_reschedule()) अणु
		म_लिखो("\n\tUnexpected transaction failure 0x%02lx\n\t",
			failure_code());
		वापस (व्योम *) -1;
	पूर्ण

	/*
	 * Check अगर TM failed due to the cause we were expecting. 0xda is a
	 * TM_CAUSE_FAC_UNAV cause, otherwise it's an unexpected cause, unless
	 * it was caused by a reschedule.
	 */
	अगर (is_failure(cr_) && !failure_is_unavailable() &&
	    !failure_is_reschedule()) अणु
		म_लिखो("\n\tUnexpected failure cause 0x%02lx\n\t",
			failure_code());
		वापस (व्योम *) -1;
	पूर्ण

	/* 0x4 is a success and 0xa is a fail. See comment in is_failure(). */
	अगर (DEBUG)
		म_लिखो("CR0: 0x%1lx ", cr_ >> 28);

	/* Check FP (vs0) क्रम the expected value. */
	अगर (high_vs0 != 0x5555555555555555 || low_vs0 != 0xFFFFFFFFFFFFFFFF) अणु
		म_लिखो("FP corrupted!");
			म_लिखो("  high = %#16" PRIx64 "  low = %#16" PRIx64 " ",
				high_vs0, low_vs0);
		flags.result++;
	पूर्ण अन्यथा
		म_लिखो("FP ok ");

	/* Check VEC (vs32) क्रम the expected value. */
	अगर (high_vs32 != 0x5555555555555555 || low_vs32 != 0xFFFFFFFFFFFFFFFF) अणु
		म_लिखो("VEC corrupted!");
			म_लिखो("  high = %#16" PRIx64 "  low = %#16" PRIx64,
				high_vs32, low_vs32);
		flags.result++;
	पूर्ण अन्यथा
		म_लिखो("VEC ok");

	अक्षर_दो('\n');

	वापस शून्य;
पूर्ण

/* Thपढ़ो to क्रमce context चयन */
व्योम *पंचांग_una_pong(व्योम *not_used)
अणु
	/* Wait thपढ़ो get its name "pong". */
	अगर (DEBUG)
		sleep(1);

	/* Classed as an पूर्णांकeractive-like thपढ़ो. */
	जबतक (1)
		sched_yield();
पूर्ण

/* Function that creates a thपढ़ो and launches the "ping" task. */
व्योम test_fp_vec(पूर्णांक fp, पूर्णांक vec, pthपढ़ो_attr_t *attr)
अणु
	पूर्णांक retries = 2;
	व्योम *ret_value;
	pthपढ़ो_t t0;

	flags.touch_fp = fp;
	flags.touch_vec = vec;

	/*
	 * Without luck it's possible that the transaction is पातed not due to
	 * the unavailable exception caught in the middle as we expect but also,
	 * क्रम instance, due to a context चयन or due to a KVM reschedule (अगर
	 * it's running on a VM). Thus we try a few बार beक्रमe giving up,
	 * checking अगर the failure cause is the one we expect.
	 */
	करो अणु
		पूर्णांक rc;

		/* Bind to CPU 0, as specअगरied in 'attr'. */
		rc = pthपढ़ो_create(&t0, attr, पंचांग_una_ping, (व्योम *) &flags);
		अगर (rc)
			pr_err(rc, "pthread_create()");
		rc = pthपढ़ो_setname_np(t0, "tm_una_ping");
		अगर (rc)
			pr_warn(rc, "pthread_setname_np");
		rc = pthपढ़ो_join(t0, &ret_value);
		अगर (rc)
			pr_err(rc, "pthread_join");

		retries--;
	पूर्ण जबतक (ret_value != शून्य && retries);

	अगर (!retries) अणु
		flags.result = 1;
		अगर (DEBUG)
			म_लिखो("All transactions failed unexpectedly\n");

	पूर्ण
पूर्ण

पूर्णांक पंचांग_unavailable_test(व्योम)
अणु
	पूर्णांक cpu, rc, exception; /* FP = 0, VEC = 1, VSX = 2 */
	pthपढ़ो_t t1;
	pthपढ़ो_attr_t attr;
	cpu_set_t cpuset;

	SKIP_IF(!have_hपंचांग());

	cpu = pick_online_cpu();
	FAIL_IF(cpu < 0);

	// Set only one CPU in the mask. Both thपढ़ोs will be bound to that CPU.
	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);

	/* Init pthपढ़ो attribute. */
	rc = pthपढ़ो_attr_init(&attr);
	अगर (rc)
		pr_err(rc, "pthread_attr_init()");

	/* Set CPU 0 mask पूर्णांकo the pthपढ़ो attribute. */
	rc = pthपढ़ो_attr_setaffinity_np(&attr, माप(cpu_set_t), &cpuset);
	अगर (rc)
		pr_err(rc, "pthread_attr_setaffinity_np()");

	rc = pthपढ़ो_create(&t1, &attr /* Bind to CPU 0 */, पंचांग_una_pong, शून्य);
	अगर (rc)
		pr_err(rc, "pthread_create()");

	/* Name it क्रम प्रणालीtap convenience */
	rc = pthपढ़ो_setname_np(t1, "tm_una_pong");
	अगर (rc)
		pr_warn(rc, "pthread_create()");

	flags.result = 0;

	क्रम (exception = 0; exception < NUM_EXCEPTIONS; exception++) अणु
		म_लिखो("Checking if FP/VEC registers are sane after");

		अगर (exception == FP_UNA_EXCEPTION)
			म_लिखो(" a FP unavailable exception...\n");

		अन्यथा अगर (exception == VEC_UNA_EXCEPTION)
			म_लिखो(" a VEC unavailable exception...\n");

		अन्यथा
			म_लिखो(" a VSX unavailable exception...\n");

		flags.exception = exception;

		test_fp_vec(0, 0, &attr);
		test_fp_vec(1, 0, &attr);
		test_fp_vec(0, 1, &attr);
		test_fp_vec(1, 1, &attr);

	पूर्ण

	अगर (flags.result > 0) अणु
		म_लिखो("result: failed!\n");
		निकास(1);
	पूर्ण अन्यथा अणु
		म_लिखो("result: success\n");
		निकास(0);
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	test_harness_set_समयout(220);
	वापस test_harness(पंचांग_unavailable_test, "tm_unavailable_test");
पूर्ण
