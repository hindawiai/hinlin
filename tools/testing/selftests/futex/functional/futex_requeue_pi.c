<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/******************************************************************************
 *
 *   Copyright तऊ International Business Machines  Corp., 2006-2008
 *
 * DESCRIPTION
 *      This test excercises the futex syscall op codes needed क्रम requeuing
 *      priority inheritance aware POSIX condition variables and mutexes.
 *
 * AUTHORS
 *      Sripathi Kodi <sripathik@in.ibm.com>
 *      Darren Hart <dvhart@linux.पूर्णांकel.com>
 *
 * HISTORY
 *      2008-Jan-13: Initial version by Sripathi Kodi <sripathik@in.ibm.com>
 *      2009-Nov-6: futex test adaptation by Darren Hart <dvhart@linux.पूर्णांकel.com>
 *
 *****************************************************************************/

#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>
#समावेश <pthपढ़ो.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश "atomic.h"
#समावेश "futextest.h"
#समावेश "logging.h"

#घोषणा TEST_NAME "futex-requeue-pi"
#घोषणा MAX_WAKE_ITERS 1000
#घोषणा THREAD_MAX 10
#घोषणा SIGNAL_PERIOD_US 100

atomic_t रुकोers_blocked = ATOMIC_INITIALIZER;
atomic_t रुकोers_woken = ATOMIC_INITIALIZER;

futex_t f1 = FUTEX_INITIALIZER;
futex_t f2 = FUTEX_INITIALIZER;
futex_t wake_complete = FUTEX_INITIALIZER;

/* Test option शेषs */
अटल दीर्घ समयout_ns;
अटल पूर्णांक broadcast;
अटल पूर्णांक owner;
अटल पूर्णांक locked;

काष्ठा thपढ़ो_arg अणु
	दीर्घ id;
	काष्ठा बारpec *समयout;
	पूर्णांक lock;
	पूर्णांक ret;
पूर्ण;
#घोषणा THREAD_ARG_INITIALIZER अणु 0, शून्य, 0, 0 पूर्ण

व्योम usage(अक्षर *prog)
अणु
	म_लिखो("Usage: %s\n", prog);
	म_लिखो("  -b	Broadcast wakeup (all waiters)\n");
	म_लिखो("  -c	Use color\n");
	म_लिखो("  -h	Display this help message\n");
	म_लिखो("  -l	Lock the pi futex across requeue\n");
	म_लिखो("  -o	Use a third party pi futex owner during requeue (cancels -l)\n");
	म_लिखो("  -t N	Timeout in nanoseconds (default: 0)\n");
	म_लिखो("  -v L	Verbosity level: %d=QUIET %d=CRITICAL %d=INFO\n",
	       VQUIET, VCRITICAL, VINFO);
पूर्ण

पूर्णांक create_rt_thपढ़ो(pthपढ़ो_t *pth, व्योम*(*func)(व्योम *), व्योम *arg,
		     पूर्णांक policy, पूर्णांक prio)
अणु
	पूर्णांक ret;
	काष्ठा sched_param schedp;
	pthपढ़ो_attr_t attr;

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


व्योम *रुकोerfn(व्योम *arg)
अणु
	काष्ठा thपढ़ो_arg *args = (काष्ठा thपढ़ो_arg *)arg;
	futex_t old_val;

	info("Waiter %ld: running\n", args->id);
	/* Each thपढ़ो sleeps क्रम a dअगरferent amount of समय
	 * This is to aव्योम races, because we करोn't lock the
	 * बाह्यal mutex here */
	usleep(1000 * (दीर्घ)args->id);

	old_val = f1;
	atomic_inc(&रुकोers_blocked);
	info("Calling futex_wait_requeue_pi: %p (%u) -> %p\n",
	     &f1, f1, &f2);
	args->ret = futex_रुको_requeue_pi(&f1, old_val, &f2, args->समयout,
					  FUTEX_PRIVATE_FLAG);

	info("waiter %ld woke with %d %s\n", args->id, args->ret,
	     args->ret < 0 ? म_त्रुटि(त्रुटि_सं) : "");
	atomic_inc(&रुकोers_woken);
	अगर (args->ret < 0) अणु
		अगर (args->समयout && त्रुटि_सं == ETIMEDOUT)
			args->ret = 0;
		अन्यथा अणु
			args->ret = RET_ERROR;
			error("futex_wait_requeue_pi\n", त्रुटि_सं);
		पूर्ण
		futex_lock_pi(&f2, शून्य, 0, FUTEX_PRIVATE_FLAG);
	पूर्ण
	futex_unlock_pi(&f2, FUTEX_PRIVATE_FLAG);

	info("Waiter %ld: exiting with %d\n", args->id, args->ret);
	pthपढ़ो_निकास((व्योम *)&args->ret);
पूर्ण

व्योम *broadcast_wakerfn(व्योम *arg)
अणु
	काष्ठा thपढ़ो_arg *args = (काष्ठा thपढ़ो_arg *)arg;
	पूर्णांक nr_requeue = पूर्णांक_उच्च;
	पूर्णांक task_count = 0;
	futex_t old_val;
	पूर्णांक nr_wake = 1;
	पूर्णांक i = 0;

	info("Waker: waiting for waiters to block\n");
	जबतक (रुकोers_blocked.val < THREAD_MAX)
		usleep(1000);
	usleep(1000);

	info("Waker: Calling broadcast\n");
	अगर (args->lock) अणु
		info("Calling FUTEX_LOCK_PI on mutex=%x @ %p\n", f2, &f2);
		futex_lock_pi(&f2, शून्य, 0, FUTEX_PRIVATE_FLAG);
	पूर्ण
 जारी_requeue:
	old_val = f1;
	args->ret = futex_cmp_requeue_pi(&f1, old_val, &f2, nr_wake, nr_requeue,
				   FUTEX_PRIVATE_FLAG);
	अगर (args->ret < 0) अणु
		args->ret = RET_ERROR;
		error("FUTEX_CMP_REQUEUE_PI failed\n", त्रुटि_सं);
	पूर्ण अन्यथा अगर (++i < MAX_WAKE_ITERS) अणु
		task_count += args->ret;
		अगर (task_count < THREAD_MAX - रुकोers_woken.val)
			जाओ जारी_requeue;
	पूर्ण अन्यथा अणु
		error("max broadcast iterations (%d) reached with %d/%d tasks woken or requeued\n",
		       0, MAX_WAKE_ITERS, task_count, THREAD_MAX);
		args->ret = RET_ERROR;
	पूर्ण

	futex_wake(&wake_complete, 1, FUTEX_PRIVATE_FLAG);

	अगर (args->lock)
		futex_unlock_pi(&f2, FUTEX_PRIVATE_FLAG);

	अगर (args->ret > 0)
		args->ret = task_count;

	info("Waker: exiting with %d\n", args->ret);
	pthपढ़ो_निकास((व्योम *)&args->ret);
पूर्ण

व्योम *संकेत_wakerfn(व्योम *arg)
अणु
	काष्ठा thपढ़ो_arg *args = (काष्ठा thपढ़ो_arg *)arg;
	अचिन्हित पूर्णांक old_val;
	पूर्णांक nr_requeue = 0;
	पूर्णांक task_count = 0;
	पूर्णांक nr_wake = 1;
	पूर्णांक i = 0;

	info("Waker: waiting for waiters to block\n");
	जबतक (रुकोers_blocked.val < THREAD_MAX)
		usleep(1000);
	usleep(1000);

	जबतक (task_count < THREAD_MAX && रुकोers_woken.val < THREAD_MAX) अणु
		info("task_count: %d, waiters_woken: %d\n",
		     task_count, रुकोers_woken.val);
		अगर (args->lock) अणु
			info("Calling FUTEX_LOCK_PI on mutex=%x @ %p\n",
			     f2, &f2);
			futex_lock_pi(&f2, शून्य, 0, FUTEX_PRIVATE_FLAG);
		पूर्ण
		info("Waker: Calling signal\n");
		/* cond_संकेत */
		old_val = f1;
		args->ret = futex_cmp_requeue_pi(&f1, old_val, &f2,
						 nr_wake, nr_requeue,
						 FUTEX_PRIVATE_FLAG);
		अगर (args->ret < 0)
			args->ret = -त्रुटि_सं;
		info("futex: %x\n", f2);
		अगर (args->lock) अणु
			info("Calling FUTEX_UNLOCK_PI on mutex=%x @ %p\n",
			     f2, &f2);
			futex_unlock_pi(&f2, FUTEX_PRIVATE_FLAG);
		पूर्ण
		info("futex: %x\n", f2);
		अगर (args->ret < 0) अणु
			error("FUTEX_CMP_REQUEUE_PI failed\n", त्रुटि_सं);
			args->ret = RET_ERROR;
			अवरोध;
		पूर्ण

		task_count += args->ret;
		usleep(SIGNAL_PERIOD_US);
		i++;
		/* we have to loop at least THREAD_MAX बार */
		अगर (i > MAX_WAKE_ITERS + THREAD_MAX) अणु
			error("max signaling iterations (%d) reached, giving up on pending waiters.\n",
			      0, MAX_WAKE_ITERS + THREAD_MAX);
			args->ret = RET_ERROR;
			अवरोध;
		पूर्ण
	पूर्ण

	futex_wake(&wake_complete, 1, FUTEX_PRIVATE_FLAG);

	अगर (args->ret >= 0)
		args->ret = task_count;

	info("Waker: exiting with %d\n", args->ret);
	info("Waker: waiters_woken: %d\n", रुकोers_woken.val);
	pthपढ़ो_निकास((व्योम *)&args->ret);
पूर्ण

व्योम *third_party_blocker(व्योम *arg)
अणु
	काष्ठा thपढ़ो_arg *args = (काष्ठा thपढ़ो_arg *)arg;
	पूर्णांक ret2 = 0;

	args->ret = futex_lock_pi(&f2, शून्य, 0, FUTEX_PRIVATE_FLAG);
	अगर (args->ret)
		जाओ out;
	args->ret = futex_रुको(&wake_complete, wake_complete, शून्य,
			       FUTEX_PRIVATE_FLAG);
	ret2 = futex_unlock_pi(&f2, FUTEX_PRIVATE_FLAG);

 out:
	अगर (args->ret || ret2) अणु
		error("third_party_blocker() futex error", 0);
		args->ret = RET_ERROR;
	पूर्ण

	pthपढ़ो_निकास((व्योम *)&args->ret);
पूर्ण

पूर्णांक unit_test(पूर्णांक broadcast, दीर्घ lock, पूर्णांक third_party_owner, दीर्घ समयout_ns)
अणु
	व्योम *(*wakerfn)(व्योम *) = संकेत_wakerfn;
	काष्ठा thपढ़ो_arg blocker_arg = THREAD_ARG_INITIALIZER;
	काष्ठा thपढ़ो_arg waker_arg = THREAD_ARG_INITIALIZER;
	pthपढ़ो_t रुकोer[THREAD_MAX], waker, blocker;
	काष्ठा बारpec ts, *tsp = शून्य;
	काष्ठा thपढ़ो_arg args[THREAD_MAX];
	पूर्णांक *रुकोer_ret;
	पूर्णांक i, ret = RET_PASS;

	अगर (समयout_ns) अणु
		समय_प्रकार secs;

		info("timeout_ns = %ld\n", समयout_ns);
		ret = घड़ी_समय_लो(CLOCK_MONOTONIC, &ts);
		secs = (ts.tv_nsec + समयout_ns) / 1000000000;
		ts.tv_nsec = ((पूर्णांक64_t)ts.tv_nsec + समयout_ns) % 1000000000;
		ts.tv_sec += secs;
		info("ts.tv_sec  = %ld\n", ts.tv_sec);
		info("ts.tv_nsec = %ld\n", ts.tv_nsec);
		tsp = &ts;
	पूर्ण

	अगर (broadcast)
		wakerfn = broadcast_wakerfn;

	अगर (third_party_owner) अणु
		अगर (create_rt_thपढ़ो(&blocker, third_party_blocker,
				     (व्योम *)&blocker_arg, SCHED_FIFO, 1)) अणु
			error("Creating third party blocker thread failed\n",
			      त्रुटि_सं);
			ret = RET_ERROR;
			जाओ out;
		पूर्ण
	पूर्ण

	atomic_set(&रुकोers_woken, 0);
	क्रम (i = 0; i < THREAD_MAX; i++) अणु
		args[i].id = i;
		args[i].समयout = tsp;
		info("Starting thread %d\n", i);
		अगर (create_rt_thपढ़ो(&रुकोer[i], रुकोerfn, (व्योम *)&args[i],
				     SCHED_FIFO, 1)) अणु
			error("Creating waiting thread failed\n", त्रुटि_सं);
			ret = RET_ERROR;
			जाओ out;
		पूर्ण
	पूर्ण
	waker_arg.lock = lock;
	अगर (create_rt_thपढ़ो(&waker, wakerfn, (व्योम *)&waker_arg,
			     SCHED_FIFO, 1)) अणु
		error("Creating waker thread failed\n", त्रुटि_सं);
		ret = RET_ERROR;
		जाओ out;
	पूर्ण

	/* Wait क्रम thपढ़ोs to finish */
	/* Store the first error or failure encountered in रुकोer_ret */
	रुकोer_ret = &args[0].ret;
	क्रम (i = 0; i < THREAD_MAX; i++)
		pthपढ़ो_join(रुकोer[i],
			     *रुकोer_ret ? शून्य : (व्योम **)&रुकोer_ret);

	अगर (third_party_owner)
		pthपढ़ो_join(blocker, शून्य);
	pthपढ़ो_join(waker, शून्य);

out:
	अगर (!ret) अणु
		अगर (*रुकोer_ret)
			ret = *रुकोer_ret;
		अन्यथा अगर (waker_arg.ret < 0)
			ret = waker_arg.ret;
		अन्यथा अगर (blocker_arg.ret)
			ret = blocker_arg.ret;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक c, ret;

	जबतक ((c = getopt(argc, argv, "bchlot:v:")) != -1) अणु
		चयन (c) अणु
		हाल 'b':
			broadcast = 1;
			अवरोध;
		हाल 'c':
			log_color(1);
			अवरोध;
		हाल 'h':
			usage(basename(argv[0]));
			निकास(0);
		हाल 'l':
			locked = 1;
			अवरोध;
		हाल 'o':
			owner = 1;
			locked = 0;
			अवरोध;
		हाल 't':
			समयout_ns = म_से_प(optarg);
			अवरोध;
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
	ksft_prपूर्णांक_msg("%s: Test requeue functionality\n", basename(argv[0]));
	ksft_prपूर्णांक_msg(
		"\tArguments: broadcast=%d locked=%d owner=%d timeout=%ldns\n",
		broadcast, locked, owner, समयout_ns);

	/*
	 * FIXME: unit_test is obsolete now that we parse options and the
	 * various style of runs are करोne by run.sh - simplअगरy the code and move
	 * unit_test पूर्णांकo मुख्य()
	 */
	ret = unit_test(broadcast, locked, owner, समयout_ns);

	prपूर्णांक_result(TEST_NAME, ret);
	वापस ret;
पूर्ण
