<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/******************************************************************************
 *
 *   Copyright तऊ International Business Machines  Corp., 2006-2008
 *
 * DESCRIPTION
 *      This test exercises the futex_रुको_requeue_pi() संकेत handling both
 *      beक्रमe and after the requeue. The first should be restarted by the
 *      kernel. The latter should वापस EWOULDBLOCK to the रुकोer.
 *
 * AUTHORS
 *      Darren Hart <dvhart@linux.पूर्णांकel.com>
 *
 * HISTORY
 *      2008-May-5: Initial version by Darren Hart <dvhart@linux.पूर्णांकel.com>
 *
 *****************************************************************************/

#समावेश <त्रुटिसं.स>
#समावेश <getopt.h>
#समावेश <सीमा.स>
#समावेश <pthपढ़ो.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश "atomic.h"
#समावेश "futextest.h"
#समावेश "logging.h"

#घोषणा TEST_NAME "futex-requeue-pi-signal-restart"
#घोषणा DELAY_US 100

futex_t f1 = FUTEX_INITIALIZER;
futex_t f2 = FUTEX_INITIALIZER;
atomic_t requeued = ATOMIC_INITIALIZER;

पूर्णांक रुकोer_ret = 0;

व्योम usage(अक्षर *prog)
अणु
	म_लिखो("Usage: %s\n", prog);
	म_लिखो("  -c	Use color\n");
	म_लिखो("  -h	Display this help message\n");
	म_लिखो("  -v L	Verbosity level: %d=QUIET %d=CRITICAL %d=INFO\n",
	       VQUIET, VCRITICAL, VINFO);
पूर्ण

पूर्णांक create_rt_thपढ़ो(pthपढ़ो_t *pth, व्योम*(*func)(व्योम *), व्योम *arg,
		     पूर्णांक policy, पूर्णांक prio)
अणु
	काष्ठा sched_param schedp;
	pthपढ़ो_attr_t attr;
	पूर्णांक ret;

	pthपढ़ो_attr_init(&attr);
	स_रखो(&schedp, 0, माप(schedp));

	ret = pthपढ़ो_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	अगर (ret) अणु
		error("pthread_attr_setinheritsched\n", ret);
		वापस -1;
	पूर्ण

	ret = pthपढ़ो_attr_setschedpolicy(&attr, policy);
	अगर (ret) अणु
		error("pthread_attr_setschedpolicy\n", ret);
		वापस -1;
	पूर्ण

	schedp.sched_priority = prio;
	ret = pthपढ़ो_attr_setschedparam(&attr, &schedp);
	अगर (ret) अणु
		error("pthread_attr_setschedparam\n", ret);
		वापस -1;
	पूर्ण

	ret = pthपढ़ो_create(pth, &attr, func, arg);
	अगर (ret) अणु
		error("pthread_create\n", ret);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

व्योम handle_संकेत(पूर्णांक signo)
अणु
	info("signal received %s requeue\n",
	     requeued.val ? "after" : "prior to");
पूर्ण

व्योम *रुकोerfn(व्योम *arg)
अणु
	अचिन्हित पूर्णांक old_val;
	पूर्णांक res;

	रुकोer_ret = RET_PASS;

	info("Waiter running\n");
	info("Calling FUTEX_LOCK_PI on f2=%x @ %p\n", f2, &f2);
	old_val = f1;
	res = futex_रुको_requeue_pi(&f1, old_val, &(f2), शून्य,
				    FUTEX_PRIVATE_FLAG);
	अगर (!requeued.val || त्रुटि_सं != EWOULDBLOCK) अणु
		fail("unexpected return from futex_wait_requeue_pi: %d (%s)\n",
		     res, म_त्रुटि(त्रुटि_सं));
		info("w2:futex: %x\n", f2);
		अगर (!res)
			futex_unlock_pi(&f2, FUTEX_PRIVATE_FLAG);
		रुकोer_ret = RET_FAIL;
	पूर्ण

	info("Waiter exiting with %d\n", रुकोer_ret);
	pthपढ़ो_निकास(शून्य);
पूर्ण


पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अचिन्हित पूर्णांक old_val;
	काष्ठा sigaction sa;
	pthपढ़ो_t रुकोer;
	पूर्णांक c, res, ret = RET_PASS;

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
	ksft_prपूर्णांक_msg("%s: Test signal handling during requeue_pi\n",
	       basename(argv[0]));
	ksft_prपूर्णांक_msg("\tArguments: <none>\n");

	sa.sa_handler = handle_संकेत;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	अगर (sigaction(SIGUSR1, &sa, शून्य)) अणु
		error("sigaction\n", त्रुटि_सं);
		निकास(1);
	पूर्ण

	info("m1:f2: %x\n", f2);
	info("Creating waiter\n");
	res = create_rt_thपढ़ो(&रुकोer, रुकोerfn, शून्य, SCHED_FIFO, 1);
	अगर (res) अणु
		error("Creating waiting thread failed", res);
		ret = RET_ERROR;
		जाओ out;
	पूर्ण

	info("Calling FUTEX_LOCK_PI on f2=%x @ %p\n", f2, &f2);
	info("m2:f2: %x\n", f2);
	futex_lock_pi(&f2, 0, 0, FUTEX_PRIVATE_FLAG);
	info("m3:f2: %x\n", f2);

	जबतक (1) अणु
		/*
		 * संकेत the रुकोer beक्रमe requeue, रुकोer should स्वतःmatically
		 * restart futex_रुको_requeue_pi() in the kernel. Wait क्रम the
		 * रुकोer to block on f1 again.
		 */
		info("Issuing SIGUSR1 to waiter\n");
		pthपढ़ो_समाप्त(रुकोer, SIGUSR1);
		usleep(DELAY_US);

		info("Requeueing waiter via FUTEX_CMP_REQUEUE_PI\n");
		old_val = f1;
		res = futex_cmp_requeue_pi(&f1, old_val, &(f2), 1, 0,
					   FUTEX_PRIVATE_FLAG);
		/*
		 * If res is non-zero, we either requeued the रुकोer or hit an
		 * error, अवरोध out and handle it. If it is zero, then the
		 * संकेत may have hit beक्रमe the the रुकोer was blocked on f1.
		 * Try again.
		 */
		अगर (res > 0) अणु
			atomic_set(&requeued, 1);
			अवरोध;
		पूर्ण अन्यथा अगर (res < 0) अणु
			error("FUTEX_CMP_REQUEUE_PI failed\n", त्रुटि_सं);
			ret = RET_ERROR;
			अवरोध;
		पूर्ण
	पूर्ण
	info("m4:f2: %x\n", f2);

	/*
	 * Signal the रुकोer after requeue, रुकोer should वापस from
	 * futex_रुको_requeue_pi() with EWOULDBLOCK. Join the thपढ़ो here so the
	 * futex_unlock_pi() can't happen beक्रमe the संकेत wakeup is detected
	 * in the kernel.
	 */
	info("Issuing SIGUSR1 to waiter\n");
	pthपढ़ो_समाप्त(रुकोer, SIGUSR1);
	info("Waiting for waiter to return\n");
	pthपढ़ो_join(रुकोer, शून्य);

	info("Calling FUTEX_UNLOCK_PI on mutex=%x @ %p\n", f2, &f2);
	futex_unlock_pi(&f2, FUTEX_PRIVATE_FLAG);
	info("m5:f2: %x\n", f2);

 out:
	अगर (ret == RET_PASS && रुकोer_ret)
		ret = रुकोer_ret;

	prपूर्णांक_result(TEST_NAME, ret);
	वापस ret;
पूर्ण
