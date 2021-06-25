<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Davidlohr Bueso.
 */

/* For the CLR_() macros */
#समावेश <माला.स>
#समावेश <pthपढ़ो.h>

#समावेश <संकेत.स>
#समावेश "../util/stat.h"
#समावेश <subcmd/parse-options.h>
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/zभाग.स>
#समावेश <त्रुटिसं.स>
#समावेश <perf/cpumap.h>
#समावेश "bench.h"
#समावेश "futex.h"

#समावेश <err.h>
#समावेश <मानककोष.स>
#समावेश <sys/समय.स>

काष्ठा worker अणु
	पूर्णांक tid;
	u_पूर्णांक32_t *futex;
	pthपढ़ो_t thपढ़ो;
	अचिन्हित दीर्घ ops;
पूर्ण;

अटल u_पूर्णांक32_t global_futex = 0;
अटल काष्ठा worker *worker;
अटल अचिन्हित पूर्णांक nsecs = 10;
अटल bool silent = false, multi = false;
अटल bool करोne = false, fshared = false;
अटल अचिन्हित पूर्णांक nthपढ़ोs = 0;
अटल पूर्णांक futex_flag = 0;
अटल pthपढ़ो_mutex_t thपढ़ो_lock;
अटल अचिन्हित पूर्णांक thपढ़ोs_starting;
अटल काष्ठा stats throughput_stats;
अटल pthपढ़ो_cond_t thपढ़ो_parent, thपढ़ो_worker;

अटल स्थिर काष्ठा option options[] = अणु
	OPT_UINTEGER('t', "threads",  &nthपढ़ोs, "Specify amount of threads"),
	OPT_UINTEGER('r', "runtime", &nsecs,     "Specify runtime (in seconds)"),
	OPT_BOOLEAN( 'M', "multi",   &multi,     "Use multiple futexes"),
	OPT_BOOLEAN( 's', "silent",  &silent,    "Silent mode: do not display data/details"),
	OPT_BOOLEAN( 'S', "shared",  &fshared,   "Use shared futexes instead of private ones"),
	OPT_END()
पूर्ण;

अटल स्थिर अक्षर * स्थिर bench_futex_lock_pi_usage[] = अणु
	"perf bench futex lock-pi <options>",
	शून्य
पूर्ण;

अटल व्योम prपूर्णांक_summary(व्योम)
अणु
	अचिन्हित दीर्घ avg = avg_stats(&throughput_stats);
	द्विगुन stddev = stddev_stats(&throughput_stats);

	म_लिखो("%sAveraged %ld operations/sec (+- %.2f%%), total secs = %d\n",
	       !silent ? "\n" : "", avg, rel_stddev_stats(stddev, avg),
	       (पूर्णांक)bench__runसमय.tv_sec);
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

अटल व्योम *workerfn(व्योम *arg)
अणु
	काष्ठा worker *w = (काष्ठा worker *) arg;
	अचिन्हित दीर्घ ops = w->ops;

	pthपढ़ो_mutex_lock(&thपढ़ो_lock);
	thपढ़ोs_starting--;
	अगर (!thपढ़ोs_starting)
		pthपढ़ो_cond_संकेत(&thपढ़ो_parent);
	pthपढ़ो_cond_रुको(&thपढ़ो_worker, &thपढ़ो_lock);
	pthपढ़ो_mutex_unlock(&thपढ़ो_lock);

	करो अणु
		पूर्णांक ret;
	again:
		ret = futex_lock_pi(w->futex, शून्य, futex_flag);

		अगर (ret) अणु /* handle lock acquisition */
			अगर (!silent)
				warn("thread %d: Could not lock pi-lock for %p (%d)",
				     w->tid, w->futex, ret);
			अगर (करोne)
				अवरोध;

			जाओ again;
		पूर्ण

		usleep(1);
		ret = futex_unlock_pi(w->futex, futex_flag);
		अगर (ret && !silent)
			warn("thread %d: Could not unlock pi-lock for %p (%d)",
			     w->tid, w->futex, ret);
		ops++; /* account क्रम thपढ़ो's share of work */
	पूर्ण  जबतक (!करोne);

	w->ops = ops;
	वापस शून्य;
पूर्ण

अटल व्योम create_thपढ़ोs(काष्ठा worker *w, pthपढ़ो_attr_t thपढ़ो_attr,
			   काष्ठा perf_cpu_map *cpu)
अणु
	cpu_set_t cpuset;
	अचिन्हित पूर्णांक i;

	thपढ़ोs_starting = nthपढ़ोs;

	क्रम (i = 0; i < nthपढ़ोs; i++) अणु
		worker[i].tid = i;

		अगर (multi) अणु
			worker[i].futex = सुस्मृति(1, माप(u_पूर्णांक32_t));
			अगर (!worker[i].futex)
				err(निकास_त्रुटि, "calloc");
		पूर्ण अन्यथा
			worker[i].futex = &global_futex;

		CPU_ZERO(&cpuset);
		CPU_SET(cpu->map[i % cpu->nr], &cpuset);

		अगर (pthपढ़ो_attr_setaffinity_np(&thपढ़ो_attr, माप(cpu_set_t), &cpuset))
			err(निकास_त्रुटि, "pthread_attr_setaffinity_np");

		अगर (pthपढ़ो_create(&w[i].thपढ़ो, &thपढ़ो_attr, workerfn, &worker[i]))
			err(निकास_त्रुटि, "pthread_create");
	पूर्ण
पूर्ण

पूर्णांक bench_futex_lock_pi(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i;
	काष्ठा sigaction act;
	pthपढ़ो_attr_t thपढ़ो_attr;
	काष्ठा perf_cpu_map *cpu;

	argc = parse_options(argc, argv, options, bench_futex_lock_pi_usage, 0);
	अगर (argc)
		जाओ err;

	cpu = perf_cpu_map__new(शून्य);
	अगर (!cpu)
		err(निकास_त्रुटि, "calloc");

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

	म_लिखो("Run summary [PID %d]: %d threads doing pi lock/unlock pairing for %d secs.\n\n",
	       getpid(), nthपढ़ोs, nsecs);

	init_stats(&throughput_stats);
	pthपढ़ो_mutex_init(&thपढ़ो_lock, शून्य);
	pthपढ़ो_cond_init(&thपढ़ो_parent, शून्य);
	pthपढ़ो_cond_init(&thपढ़ो_worker, शून्य);

	thपढ़ोs_starting = nthपढ़ोs;
	pthपढ़ो_attr_init(&thपढ़ो_attr);
	समय_लोofday(&bench__start, शून्य);

	create_thपढ़ोs(worker, thपढ़ो_attr, cpu);
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
		अगर (!silent)
			म_लिखो("[thread %3d] futex: %p [ %ld ops/sec ]\n",
			       worker[i].tid, worker[i].futex, t);

		अगर (multi)
			zमुक्त(&worker[i].futex);
	पूर्ण

	prपूर्णांक_summary();

	मुक्त(worker);
	वापस ret;
err:
	usage_with_options(bench_futex_lock_pi_usage, options);
	निकास(निकास_त्रुटि);
पूर्ण
