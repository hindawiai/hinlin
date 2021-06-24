<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/******************************************************************************
 *
 *   Copyright तऊ International Business Machines  Corp., 2009
 *
 * DESCRIPTION
 *      1. Block a thपढ़ो using FUTEX_WAIT
 *      2. Attempt to use FUTEX_CMP_REQUEUE_PI on the futex from 1.
 *      3. The kernel must detect the mismatch and वापस -EINVAL.
 *
 * AUTHOR
 *      Darren Hart <dvhart@linux.पूर्णांकel.com>
 *
 * HISTORY
 *      2009-Nov-9: Initial version by Darren Hart <dvhart@linux.पूर्णांकel.com>
 *
 *****************************************************************************/

#समावेश <त्रुटिसं.स>
#समावेश <getopt.h>
#समावेश <pthपढ़ो.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश "futextest.h"
#समावेश "logging.h"

#घोषणा TEST_NAME "futex-requeue-pi-mismatched-ops"

futex_t f1 = FUTEX_INITIALIZER;
futex_t f2 = FUTEX_INITIALIZER;
पूर्णांक child_ret = 0;

व्योम usage(अक्षर *prog)
अणु
	म_लिखो("Usage: %s\n", prog);
	म_लिखो("  -c	Use color\n");
	म_लिखो("  -h	Display this help message\n");
	म_लिखो("  -v L	Verbosity level: %d=QUIET %d=CRITICAL %d=INFO\n",
	       VQUIET, VCRITICAL, VINFO);
पूर्ण

व्योम *blocking_child(व्योम *arg)
अणु
	child_ret = futex_रुको(&f1, f1, शून्य, FUTEX_PRIVATE_FLAG);
	अगर (child_ret < 0) अणु
		child_ret = -त्रुटि_सं;
		error("futex_wait\n", त्रुटि_सं);
	पूर्ण
	वापस (व्योम *)&child_ret;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक ret = RET_PASS;
	pthपढ़ो_t child;
	पूर्णांक c;

	जबतक ((c = getopt(argc, argv, "chv:")) != -1) अणु
		चयन (c) अणु
		हाल 'c':
			log_color(1);
			अवरोध;
		हाल 'h':
			usage(basename(argv[0]));
			निकास(0);
		हाल 'v':
			log_verbosity(म_से_प(optarg));
			अवरोध;
		शेष:
			usage(basename(argv[0]));
			निकास(1);
		पूर्ण
	पूर्ण

	ksft_prपूर्णांक_header();
	ksft_set_plan(1);
	ksft_prपूर्णांक_msg("%s: Detect mismatched requeue_pi operations\n",
	       basename(argv[0]));

	अगर (pthपढ़ो_create(&child, शून्य, blocking_child, शून्य)) अणु
		error("pthread_create\n", त्रुटि_सं);
		ret = RET_ERROR;
		जाओ out;
	पूर्ण
	/* Allow the child to block in the kernel. */
	sleep(1);

	/*
	 * The kernel should detect the रुकोer did not setup the
	 * q->requeue_pi_key and वापस -EINVAL. If it करोes not,
	 * it likely gave the lock to the child, which is now hung
	 * in the kernel.
	 */
	ret = futex_cmp_requeue_pi(&f1, f1, &f2, 1, 0, FUTEX_PRIVATE_FLAG);
	अगर (ret < 0) अणु
		अगर (त्रुटि_सं == EINVAL) अणु
			/*
			 * The kernel correctly detected the mismatched
			 * requeue_pi target and पातed. Wake the child with
			 * FUTEX_WAKE.
			 */
			ret = futex_wake(&f1, 1, FUTEX_PRIVATE_FLAG);
			अगर (ret == 1) अणु
				ret = RET_PASS;
			पूर्ण अन्यथा अगर (ret < 0) अणु
				error("futex_wake\n", त्रुटि_सं);
				ret = RET_ERROR;
			पूर्ण अन्यथा अणु
				error("futex_wake did not wake the child\n", 0);
				ret = RET_ERROR;
			पूर्ण
		पूर्ण अन्यथा अणु
			error("futex_cmp_requeue_pi\n", त्रुटि_सं);
			ret = RET_ERROR;
		पूर्ण
	पूर्ण अन्यथा अगर (ret > 0) अणु
		fail("futex_cmp_requeue_pi failed to detect the mismatch\n");
		ret = RET_FAIL;
	पूर्ण अन्यथा अणु
		error("futex_cmp_requeue_pi found no waiters\n", 0);
		ret = RET_ERROR;
	पूर्ण

	pthपढ़ो_join(child, शून्य);

	अगर (!ret)
		ret = child_ret;

 out:
	/* If the kernel crashes, we shouldn't वापस at all. */
	prपूर्णांक_result(TEST_NAME, ret);
	वापस ret;
पूर्ण
