<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013  Davidlohr Bueso <davidlohr@hp.com>
 *
 * futex-requeue: Block a bunch of thपढ़ोs on futex1 and requeue them
 *                on futex2, N at a समय.
 *
 * This program is particularly useful to measure the latency of nthपढ़ो
 * requeues without waking up any tasks -- thus mimicking a regular futex_रुको.
 */

/* For the CLR_() macros */
#समावेश <माला.स>
#समावेश <pthपढ़ो.h>

#समावेश <संकेत.स>
#समावेश "../util/stat.h"
#समावेश <subcmd/parse-options.h>
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समय64.h>
#समावेश <त्रुटिसं.स>
#समावेश <perf/cpumap.h>
#समावेश "bench.h"
#समावेश "futex.h"

#समावेश <err.h>
#समावेश <मानककोष.स>
#समावेश <sys/समय.स>

अटल u_पूर्णांक32_t futex1 = 0, futex2 = 0;

/*
 * How many tasks to requeue at a समय.
 * Default to 1 in order to make the kernel work more.
 */
अटल अचिन्हित पूर्णांक nrequeue = 1;

अटल pthपढ़ो_t *worker;
अटल bool करोne = false, silent = false, fshared = false;
अटल pthपढ़ो_mutex_t thपढ़ो_lock;
अटल pthपढ़ो_cond_t thपढ़ो_parent, thपढ़ो_worker;
अटल काष्ठा stats requeueसमय_stats, requeued_stats;
अटल अचिन्हित पूर्णांक thपढ़ोs_starting, nthपढ़ोs = 0;
अटल पूर्णांक futex_flag = 0;

अटल स्थिर काष्ठा option options[] = अणु
	OPT_UINTEGER('t', "threads",  &nthपढ़ोs, "Specify amount of threads"),
	OPT_UINTEGER('q', "nrequeue", &nrequeue, "Specify amount of threads to requeue at once"),
	OPT_BOOLEAN( 's', "silent",   &silent,   "Silent mode: do not display data/details"),
	OPT_BOOLEAN( 'S', "shared",   &fshared,  "Use shared futexes instead of private ones"),
	OPT_END()
पूर्ण;

अटल स्थिर अक्षर * स्थिर bench_futex_requeue_usage[] = अणु
	"perf bench futex requeue <options>",
	शून्य
पूर्ण;

अटल व्योम prपूर्णांक_summary(व्योम)
अणु
	द्विगुन requeueसमय_avg = avg_stats(&requeueसमय_stats);
	द्विगुन requeueसमय_stddev = stddev_stats(&requeueसमय_stats);
	अचिन्हित पूर्णांक requeued_avg = avg_stats(&requeued_stats);

	म_लिखो("Requeued %d of %d threads in %.4f ms (+-%.2f%%)\n",
	       requeued_avg,
	       nthपढ़ोs,
	       requeueसमय_avg / USEC_PER_MSEC,
	       rel_stddev_stats(requeueसमय_stddev, requeueसमय_avg));
पूर्ण

अटल व्योम *workerfn(व्योम *arg __maybe_unused)
अणु
	pthपढ़ो_mutex_lock(&thपढ़ो_lock);
	thपढ़ोs_starting--;
	अगर (!thपढ़ोs_starting)
		pthपढ़ो_cond_संकेत(&thपढ़ो_parent);
	pthपढ़ो_cond_रुको(&thपढ़ो_worker, &thपढ़ो_lock);
	pthपढ़ो_mutex_unlock(&thपढ़ो_lock);

	futex_रुको(&futex1, 0, शून्य, futex_flag);
	वापस शून्य;
पूर्ण

अटल व्योम block_thपढ़ोs(pthपढ़ो_t *w,
			  pthपढ़ो_attr_t thपढ़ो_attr, काष्ठा perf_cpu_map *cpu)
अणु
	cpu_set_t cpuset;
	अचिन्हित पूर्णांक i;

	thपढ़ोs_starting = nthपढ़ोs;

	/* create and block all thपढ़ोs */
	क्रम (i = 0; i < nthपढ़ोs; i++) अणु
		CPU_ZERO(&cpuset);
		CPU_SET(cpu->map[i % cpu->nr], &cpuset);

		अगर (pthपढ़ो_attr_setaffinity_np(&thपढ़ो_attr, माप(cpu_set_t), &cpuset))
			err(निकास_त्रुटि, "pthread_attr_setaffinity_np");

		अगर (pthपढ़ो_create(&w[i], &thपढ़ो_attr, workerfn, शून्य))
			err(निकास_त्रुटि, "pthread_create");
	पूर्ण
पूर्ण

अटल व्योम toggle_करोne(पूर्णांक sig __maybe_unused,
			siginfo_t *info __maybe_unused,
			व्योम *uc __maybe_unused)
अणु
	करोne = true;
पूर्ण

पूर्णांक bench_futex_requeue(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i, j;
	काष्ठा sigaction act;
	pthपढ़ो_attr_t thपढ़ो_attr;
	काष्ठा perf_cpu_map *cpu;

	argc = parse_options(argc, argv, options, bench_futex_requeue_usage, 0);
	अगर (argc)
		जाओ err;

	cpu = perf_cpu_map__new(शून्य);
	अगर (!cpu)
		err(निकास_त्रुटि, "cpu_map__new");

	स_रखो(&act, 0, माप(act));
	sigfillset(&act.sa_mask);
	act.sa_sigaction = toggle_करोne;
	sigaction(संक_विघ्न, &act, शून्य);

	अगर (!nthपढ़ोs)
		nthपढ़ोs = cpu->nr;

	worker = सुस्मृति(nthपढ़ोs, माप(*worker));
	अगर (!worker)
		err(निकास_त्रुटि, "calloc");

	अगर (!fshared)
		futex_flag = FUTEX_PRIVATE_FLAG;

	अगर (nrequeue > nthपढ़ोs)
		nrequeue = nthपढ़ोs;

	म_लिखो("Run summary [PID %d]: Requeuing %d threads (from [%s] %p to %p), "
	       "%d at a time.\n\n",  getpid(), nthपढ़ोs,
	       fshared ? "shared":"private", &futex1, &futex2, nrequeue);

	init_stats(&requeued_stats);
	init_stats(&requeueसमय_stats);
	pthपढ़ो_attr_init(&thपढ़ो_attr);
	pthपढ़ो_mutex_init(&thपढ़ो_lock, शून्य);
	pthपढ़ो_cond_init(&thपढ़ो_parent, शून्य);
	pthपढ़ो_cond_init(&thपढ़ो_worker, शून्य);

	क्रम (j = 0; j < bench_repeat && !करोne; j++) अणु
		अचिन्हित पूर्णांक nrequeued = 0;
		काष्ठा समयval start, end, runसमय;

		/* create, launch & block all thपढ़ोs */
		block_thपढ़ोs(worker, thपढ़ो_attr, cpu);

		/* make sure all thपढ़ोs are alपढ़ोy blocked */
		pthपढ़ो_mutex_lock(&thपढ़ो_lock);
		जबतक (thपढ़ोs_starting)
			pthपढ़ो_cond_रुको(&thपढ़ो_parent, &thपढ़ो_lock);
		pthपढ़ो_cond_broadcast(&thपढ़ो_worker);
		pthपढ़ो_mutex_unlock(&thपढ़ो_lock);

		usleep(100000);

		/* Ok, all thपढ़ोs are patiently blocked, start requeueing */
		समय_लोofday(&start, शून्य);
		जबतक (nrequeued < nthपढ़ोs) अणु
			/*
			 * Do not wakeup any tasks blocked on futex1, allowing
			 * us to really measure futex_रुको functionality.
			 */
			nrequeued += futex_cmp_requeue(&futex1, 0, &futex2, 0,
						       nrequeue, futex_flag);
		पूर्ण

		समय_लोofday(&end, शून्य);
		समयrsub(&end, &start, &runसमय);

		update_stats(&requeued_stats, nrequeued);
		update_stats(&requeueसमय_stats, runसमय.tv_usec);

		अगर (!silent) अणु
			म_लिखो("[Run %d]: Requeued %d of %d threads in %.4f ms\n",
			       j + 1, nrequeued, nthपढ़ोs, runसमय.tv_usec / (द्विगुन)USEC_PER_MSEC);
		पूर्ण

		/* everybody should be blocked on futex2, wake'em up */
		nrequeued = futex_wake(&futex2, nrequeued, futex_flag);
		अगर (nthपढ़ोs != nrequeued)
			warnx("couldn't wakeup all tasks (%d/%d)", nrequeued, nthपढ़ोs);

		क्रम (i = 0; i < nthपढ़ोs; i++) अणु
			ret = pthपढ़ो_join(worker[i], शून्य);
			अगर (ret)
				err(निकास_त्रुटि, "pthread_join");
		पूर्ण
	पूर्ण

	/* cleanup & report results */
	pthपढ़ो_cond_destroy(&thपढ़ो_parent);
	pthपढ़ो_cond_destroy(&thपढ़ो_worker);
	pthपढ़ो_mutex_destroy(&thपढ़ो_lock);
	pthपढ़ो_attr_destroy(&thपढ़ो_attr);

	prपूर्णांक_summary();

	मुक्त(worker);
	वापस ret;
err:
	usage_with_options(bench_futex_requeue_usage, options);
	निकास(निकास_त्रुटि);
पूर्ण
