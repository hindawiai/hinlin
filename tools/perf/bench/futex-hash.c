<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013  Davidlohr Bueso <davidlohr@hp.com>
 *
 * futex-hash: Stress the hell out of the Linux kernel futex uaddr hashing.
 *
 * This program is particularly useful क्रम measuring the kernel's futex hash
 * table/function implementation. In order क्रम it to make sense, use with as
 * many thपढ़ोs and futexes as possible.
 */

/* For the CLR_() macros */
#समावेश <माला.स>
#समावेश <pthपढ़ो.h>

#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/zभाग.स>
#समावेश <sys/समय.स>
#समावेश <perf/cpumap.h>

#समावेश "../util/stat.h"
#समावेश <subcmd/parse-options.h>
#समावेश "bench.h"
#समावेश "futex.h"

#समावेश <err.h>

अटल अचिन्हित पूर्णांक nthपढ़ोs = 0;
अटल अचिन्हित पूर्णांक nsecs    = 10;
/* amount of futexes per thपढ़ो */
अटल अचिन्हित पूर्णांक nfutexes = 1024;
अटल bool fshared = false, करोne = false, silent = false;
अटल पूर्णांक futex_flag = 0;

काष्ठा समयval bench__start, bench__end, bench__runसमय;
अटल pthपढ़ो_mutex_t thपढ़ो_lock;
अटल अचिन्हित पूर्णांक thपढ़ोs_starting;
अटल काष्ठा stats throughput_stats;
अटल pthपढ़ो_cond_t thपढ़ो_parent, thपढ़ो_worker;

काष्ठा worker अणु
	पूर्णांक tid;
	u_पूर्णांक32_t *futex;
	pthपढ़ो_t thपढ़ो;
	अचिन्हित दीर्घ ops;
पूर्ण;

अटल स्थिर काष्ठा option options[] = अणु
	OPT_UINTEGER('t', "threads", &nthपढ़ोs, "Specify amount of threads"),
	OPT_UINTEGER('r', "runtime", &nsecs,    "Specify runtime (in seconds)"),
	OPT_UINTEGER('f', "futexes", &nfutexes, "Specify amount of futexes per threads"),
	OPT_BOOLEAN( 's', "silent",  &silent,   "Silent mode: do not display data/details"),
	OPT_BOOLEAN( 'S', "shared",  &fshared,  "Use shared futexes instead of private ones"),
	OPT_END()
पूर्ण;

अटल स्थिर अक्षर * स्थिर bench_futex_hash_usage[] = अणु
	"perf bench futex hash <options>",
	शून्य
पूर्ण;

अटल व्योम *workerfn(व्योम *arg)
अणु
	पूर्णांक ret;
	काष्ठा worker *w = (काष्ठा worker *) arg;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ ops = w->ops; /* aव्योम cacheline bouncing */

	pthपढ़ो_mutex_lock(&thपढ़ो_lock);
	thपढ़ोs_starting--;
	अगर (!thपढ़ोs_starting)
		pthपढ़ो_cond_संकेत(&thपढ़ो_parent);
	pthपढ़ो_cond_रुको(&thपढ़ो_worker, &thपढ़ो_lock);
	pthपढ़ो_mutex_unlock(&thपढ़ो_lock);

	करो अणु
		क्रम (i = 0; i < nfutexes; i++, ops++) अणु
			/*
			 * We want the futex calls to fail in order to stress
			 * the hashing of uaddr and not measure other steps,
			 * such as पूर्णांकernal रुकोqueue handling, thus enlarging
			 * the critical region रक्षित by hb->lock.
			 */
			ret = futex_रुको(&w->futex[i], 1234, शून्य, futex_flag);
			अगर (!silent &&
			    (!ret || त्रुटि_सं != EAGAIN || त्रुटि_सं != EWOULDBLOCK))
				warn("Non-expected futex return call");
		पूर्ण
	पूर्ण  जबतक (!करोne);

	w->ops = ops;
	वापस शून्य;
पूर्ण

अटल व्योम toggle_करोne(पूर्णांक sig __maybe_unused,
			siginfo_t *info __maybe_unused,
			व्योम *uc __maybe_unused)
अणु
	/* inक्रमm all thपढ़ोs that we're करोne क्रम the day */
	करोne = true;
	समय_लोofday(&bench__end, शून्य);
	समयrsub(&bench__end, &bench__start, &bench__runसमय);
पूर्ण

अटल व्योम prपूर्णांक_summary(व्योम)
अणु
	अचिन्हित दीर्घ avg = avg_stats(&throughput_stats);
	द्विगुन stddev = stddev_stats(&throughput_stats);

	म_लिखो("%sAveraged %ld operations/sec (+- %.2f%%), total secs = %d\n",
	       !silent ? "\n" : "", avg, rel_stddev_stats(stddev, avg),
	       (पूर्णांक)bench__runसमय.tv_sec);
पूर्ण

पूर्णांक bench_futex_hash(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक ret = 0;
	cpu_set_t cpuset;
	काष्ठा sigaction act;
	अचिन्हित पूर्णांक i;
	pthपढ़ो_attr_t thपढ़ो_attr;
	काष्ठा worker *worker = शून्य;
	काष्ठा perf_cpu_map *cpu;

	argc = parse_options(argc, argv, options, bench_futex_hash_usage, 0);
	अगर (argc) अणु
		usage_with_options(bench_futex_hash_usage, options);
		निकास(निकास_त्रुटि);
	पूर्ण

	cpu = perf_cpu_map__new(शून्य);
	अगर (!cpu)
		जाओ errmem;

	स_रखो(&act, 0, माप(act));
	sigfillset(&act.sa_mask);
	act.sa_sigaction = toggle_करोne;
	sigaction(संक_विघ्न, &act, शून्य);

	अगर (!nthपढ़ोs) /* शेष to the number of CPUs */
		nthपढ़ोs = cpu->nr;

	worker = सुस्मृति(nthपढ़ोs, माप(*worker));
	अगर (!worker)
		जाओ errmem;

	अगर (!fshared)
		futex_flag = FUTEX_PRIVATE_FLAG;

	म_लिखो("Run summary [PID %d]: %d threads, each operating on %d [%s] futexes for %d secs.\n\n",
	       getpid(), nthपढ़ोs, nfutexes, fshared ? "shared":"private", nsecs);

	init_stats(&throughput_stats);
	pthपढ़ो_mutex_init(&thपढ़ो_lock, शून्य);
	pthपढ़ो_cond_init(&thपढ़ो_parent, शून्य);
	pthपढ़ो_cond_init(&thपढ़ो_worker, शून्य);

	thपढ़ोs_starting = nthपढ़ोs;
	pthपढ़ो_attr_init(&thपढ़ो_attr);
	समय_लोofday(&bench__start, शून्य);
	क्रम (i = 0; i < nthपढ़ोs; i++) अणु
		worker[i].tid = i;
		worker[i].futex = सुस्मृति(nfutexes, माप(*worker[i].futex));
		अगर (!worker[i].futex)
			जाओ errmem;

		CPU_ZERO(&cpuset);
		CPU_SET(cpu->map[i % cpu->nr], &cpuset);

		ret = pthपढ़ो_attr_setaffinity_np(&thपढ़ो_attr, माप(cpu_set_t), &cpuset);
		अगर (ret)
			err(निकास_त्रुटि, "pthread_attr_setaffinity_np");

		ret = pthपढ़ो_create(&worker[i].thपढ़ो, &thपढ़ो_attr, workerfn,
				     (व्योम *)(काष्ठा worker *) &worker[i]);
		अगर (ret)
			err(निकास_त्रुटि, "pthread_create");

	पूर्ण
	pthपढ़ो_attr_destroy(&thपढ़ो_attr);

	pthपढ़ो_mutex_lock(&thपढ़ो_lock);
	जबतक (thपढ़ोs_starting)
		pthपढ़ो_cond_रुको(&thपढ़ो_parent, &thपढ़ो_lock);
	pthपढ़ो_cond_broadcast(&thपढ़ो_worker);
	pthपढ़ो_mutex_unlock(&thपढ़ो_lock);

	sleep(nsecs);
	toggle_करोne(0, शून्य, शून्य);

	क्रम (i = 0; i < nthपढ़ोs; i++) अणु
		ret = pthपढ़ो_join(worker[i].thपढ़ो, शून्य);
		अगर (ret)
			err(निकास_त्रुटि, "pthread_join");
	पूर्ण

	/* cleanup & report results */
	pthपढ़ो_cond_destroy(&thपढ़ो_parent);
	pthपढ़ो_cond_destroy(&thपढ़ो_worker);
	pthपढ़ो_mutex_destroy(&thपढ़ो_lock);

	क्रम (i = 0; i < nthपढ़ोs; i++) अणु
		अचिन्हित दीर्घ t = bench__runसमय.tv_sec > 0 ?
			worker[i].ops / bench__runसमय.tv_sec : 0;
		update_stats(&throughput_stats, t);
		अगर (!silent) अणु
			अगर (nfutexes == 1)
				म_लिखो("[thread %2d] futex: %p [ %ld ops/sec ]\n",
				       worker[i].tid, &worker[i].futex[0], t);
			अन्यथा
				म_लिखो("[thread %2d] futexes: %p ... %p [ %ld ops/sec ]\n",
				       worker[i].tid, &worker[i].futex[0],
				       &worker[i].futex[nfutexes-1], t);
		पूर्ण

		zमुक्त(&worker[i].futex);
	पूर्ण

	prपूर्णांक_summary();

	मुक्त(worker);
	मुक्त(cpu);
	वापस ret;
errmem:
	err(निकास_त्रुटि, "calloc");
पूर्ण
