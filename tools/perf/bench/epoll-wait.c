<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_घोषित HAVE_EVENTFD_SUPPORT
/*
 * Copyright (C) 2018 Davidlohr Bueso.
 *
 * This program benchmarks concurrent epoll_रुको(2) monitoring multiple
 * file descriptors under one or two load balancing models. The first,
 * and शेष, is the single/combined queueing (which refers to a single
 * epoll instance क्रम N worker thपढ़ोs):
 *
 *                          |---> [worker A]
 *                          |---> [worker B]
 *        [combined queue]  .---> [worker C]
 *                          |---> [worker D]
 *                          |---> [worker E]
 *
 * While the second model, enabled via --multiq option, uses multiple
 * queueing (which refers to one epoll instance per worker). For example,
 * लघु lived tcp connections in a high throughput httpd server will
 * distribute the accept()'ing  connections across CPUs. In this हाल each
 * worker करोes a limited  amount of processing.
 *
 *             [queue A]  ---> [worker]
 *             [queue B]  ---> [worker]
 *             [queue C]  ---> [worker]
 *             [queue D]  ---> [worker]
 *             [queue E]  ---> [worker]
 *
 * Naturally, the single queue will enक्रमce more concurrency on the epoll
 * instance, and can thereक्रमe scale poorly compared to multiple queues.
 * However, this is a benchmark raw data and must be taken with a grain of
 * salt when choosing how to make use of sys_epoll.

 * Each thपढ़ो has a number of निजी, nonblocking file descriptors,
 * referred to as fdmap. A ग_लिखोr thपढ़ो will स्थिरantly be writing to
 * the fdmaps of all thपढ़ोs, minimizing each thपढ़ोs's chances of
 * epoll_रुको not finding any पढ़ोy पढ़ो events and blocking as this
 * is not what we want to stress. The size of the fdmap can be adjusted
 * by the user; enlarging the value will increase the chances of
 * epoll_रुको(2) blocking as the lineal ग_लिखोr thपढ़ो will take "longer",
 * at least at a high level.
 *
 * Note that because fds are निजी to each thपढ़ो, this workload करोes
 * not stress scenarios where multiple tasks are awoken per पढ़ोy IO; ie:
 * EPOLLEXCLUSIVE semantics.
 *
 * The end result/metric is throughput: number of ops/second where an
 * operation consists of:
 *
 *   epoll_रुको(2) + [others]
 *
 *        ... where [others] is the cost of re-adding the fd (EPOLLET),
 *            or rearming it (EPOLLONESHOT).
 *
 *
 * The purpose of this is program is that it be useful क्रम measuring
 * kernel related changes to the sys_epoll, and not comparing dअगरferent
 * IO polling methods, क्रम example. Hence everything is very adhoc and
 * outमाला_दो raw microbenchmark numbers. Also this uses eventfd, similar
 * tools tend to use pipes or sockets, but the result is the same.
 */

/* For the CLR_() macros */
#समावेश <माला.स>
#समावेश <pthपढ़ो.h>
#समावेश <unistd.h>

#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <sys/समय.स>
#समावेश <sys/resource.h>
#समावेश <sys/epoll.h>
#समावेश <sys/eventfd.h>
#समावेश <sys/types.h>
#समावेश <perf/cpumap.h>

#समावेश "../util/stat.h"
#समावेश <subcmd/parse-options.h>
#समावेश "bench.h"

#समावेश <err.h>

#घोषणा prपूर्णांकinfo(fmt, arg...) \
	करो अणु अगर (__verbose) अणु म_लिखो(fmt, ## arg); ख_साफ(मानक_निकास); पूर्ण पूर्ण जबतक (0)

अटल अचिन्हित पूर्णांक nthपढ़ोs = 0;
अटल अचिन्हित पूर्णांक nsecs    = 8;
अटल bool wकरोne, करोne, __verbose, अक्रमomize, nonblocking;

/*
 * epoll related shared variables.
 */

/* Maximum number of nesting allowed inside epoll sets */
#घोषणा EPOLL_MAXNESTS 4

अटल पूर्णांक epollfd;
अटल पूर्णांक *epollfdp;
अटल bool noaffinity;
अटल अचिन्हित पूर्णांक nested = 0;
अटल bool et; /* edge-trigger */
अटल bool oneshot;
अटल bool multiq; /* use an epoll instance per thपढ़ो */

/* amount of fds to monitor, per thपढ़ो */
अटल अचिन्हित पूर्णांक nfds = 64;

अटल pthपढ़ो_mutex_t thपढ़ो_lock;
अटल अचिन्हित पूर्णांक thपढ़ोs_starting;
अटल काष्ठा stats throughput_stats;
अटल pthपढ़ो_cond_t thपढ़ो_parent, thपढ़ो_worker;

काष्ठा worker अणु
	पूर्णांक tid;
	पूर्णांक epollfd; /* क्रम --multiq */
	pthपढ़ो_t thपढ़ो;
	अचिन्हित दीर्घ ops;
	पूर्णांक *fdmap;
पूर्ण;

अटल स्थिर काष्ठा option options[] = अणु
	/* general benchmark options */
	OPT_UINTEGER('t', "threads", &nthपढ़ोs, "Specify amount of threads"),
	OPT_UINTEGER('r', "runtime", &nsecs, "Specify runtime (in seconds)"),
	OPT_UINTEGER('f', "nfds",    &nfds,  "Specify amount of file descriptors to monitor for each thread"),
	OPT_BOOLEAN( 'n', "noaffinity",  &noaffinity,   "Disables CPU affinity"),
	OPT_BOOLEAN('R', "randomize", &अक्रमomize,   "Enable random write behaviour (default is lineal)"),
	OPT_BOOLEAN( 'v', "verbose", &__verbose, "Verbose mode"),

	/* epoll specअगरic options */
	OPT_BOOLEAN( 'm', "multiq",  &multiq,   "Use multiple epoll instances (one per thread)"),
	OPT_BOOLEAN( 'B', "nonblocking", &nonblocking, "Nonblocking epoll_wait(2) behaviour"),
	OPT_UINTEGER( 'N', "nested",  &nested,   "Nesting level epoll hierarchy (default is 0, no nesting)"),
	OPT_BOOLEAN( 'S', "oneshot",  &oneshot,   "Use EPOLLONESHOT semantics"),
	OPT_BOOLEAN( 'E', "edge",  &et,   "Use Edge-triggered interface (default is LT)"),

	OPT_END()
पूर्ण;

अटल स्थिर अक्षर * स्थिर bench_epoll_रुको_usage[] = अणु
	"perf bench epoll wait <options>",
	शून्य
पूर्ण;


/*
 * Arrange the N elements of ARRAY in अक्रमom order.
 * Only effective अगर N is much smaller than अक्रम_उच्च;
 * अगर this may not be the हाल, use a better अक्रमom
 * number generator. -- Ben Pfaff.
 */
अटल व्योम shuffle(व्योम *array, माप_प्रकार n, माप_प्रकार size)
अणु
	अक्षर *carray = array;
	व्योम *aux;
	माप_प्रकार i;

	अगर (n <= 1)
		वापस;

	aux = सुस्मृति(1, size);
	अगर (!aux)
		err(निकास_त्रुटि, "calloc");

	क्रम (i = 1; i < n; ++i) अणु
		माप_प्रकार j =   i + अक्रम() / (अक्रम_उच्च / (n - i) + 1);
		j *= size;

		स_नकल(aux, &carray[j], size);
		स_नकल(&carray[j], &carray[i*size], size);
		स_नकल(&carray[i*size], aux, size);
	पूर्ण

	मुक्त(aux);
पूर्ण


अटल व्योम *workerfn(व्योम *arg)
अणु
	पूर्णांक fd, ret, r;
	काष्ठा worker *w = (काष्ठा worker *) arg;
	अचिन्हित दीर्घ ops = w->ops;
	काष्ठा epoll_event ev;
	uपूर्णांक64_t val;
	पूर्णांक to = nonblocking? 0 : -1;
	पूर्णांक efd = multiq ? w->epollfd : epollfd;

	pthपढ़ो_mutex_lock(&thपढ़ो_lock);
	thपढ़ोs_starting--;
	अगर (!thपढ़ोs_starting)
		pthपढ़ो_cond_संकेत(&thपढ़ो_parent);
	pthपढ़ो_cond_रुको(&thपढ़ो_worker, &thपढ़ो_lock);
	pthपढ़ो_mutex_unlock(&thपढ़ो_lock);

	करो अणु
		/*
		 * Block indefinitely रुकोing क्रम the IN event.
		 * In order to stress the epoll_रुको(2) syscall,
		 * call it event per event, instead of a larger
		 * batch (max)limit.
		 */
		करो अणु
			ret = epoll_रुको(efd, &ev, 1, to);
		पूर्ण जबतक (ret < 0 && त्रुटि_सं == EINTR);
		अगर (ret < 0)
			err(निकास_त्रुटि, "epoll_wait");

		fd = ev.data.fd;

		करो अणु
			r = पढ़ो(fd, &val, माप(val));
		पूर्ण जबतक (!करोne && (r < 0 && त्रुटि_सं == EAGAIN));

		अगर (et) अणु
			ev.events = EPOLLIN | EPOLLET;
			ret = epoll_ctl(efd, EPOLL_CTL_ADD, fd, &ev);
		पूर्ण

		अगर (oneshot) अणु
			/* rearm the file descriptor with a new event mask */
			ev.events |= EPOLLIN | EPOLLONESHOT;
			ret = epoll_ctl(efd, EPOLL_CTL_MOD, fd, &ev);
		पूर्ण

		ops++;
	पूर्ण  जबतक (!करोne);

	अगर (multiq)
		बंद(w->epollfd);

	w->ops = ops;
	वापस शून्य;
पूर्ण

अटल व्योम nest_epollfd(काष्ठा worker *w)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा epoll_event ev;
	पूर्णांक efd = multiq ? w->epollfd : epollfd;

	अगर (nested > EPOLL_MAXNESTS)
		nested = EPOLL_MAXNESTS;

	epollfdp = सुस्मृति(nested, माप(*epollfdp));
	अगर (!epollfdp)
		err(निकास_त्रुटि, "calloc");

	क्रम (i = 0; i < nested; i++) अणु
		epollfdp[i] = epoll_create(1);
		अगर (epollfdp[i] < 0)
			err(निकास_त्रुटि, "epoll_create");
	पूर्ण

	ev.events = EPOLLHUP; /* anything */
	ev.data.u64 = i; /* any number */

	क्रम (i = nested - 1; i; i--) अणु
		अगर (epoll_ctl(epollfdp[i - 1], EPOLL_CTL_ADD,
			      epollfdp[i], &ev) < 0)
			err(निकास_त्रुटि, "epoll_ctl");
	पूर्ण

	अगर (epoll_ctl(efd, EPOLL_CTL_ADD, *epollfdp, &ev) < 0)
		err(निकास_त्रुटि, "epoll_ctl");
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

	म_लिखो("\nAveraged %ld operations/sec (+- %.2f%%), total secs = %d\n",
	       avg, rel_stddev_stats(stddev, avg),
	       (पूर्णांक)bench__runसमय.tv_sec);
पूर्ण

अटल पूर्णांक करो_thपढ़ोs(काष्ठा worker *worker, काष्ठा perf_cpu_map *cpu)
अणु
	pthपढ़ो_attr_t thपढ़ो_attr, *attrp = शून्य;
	cpu_set_t cpuset;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक ret = 0, events = EPOLLIN;

	अगर (oneshot)
		events |= EPOLLONESHOT;
	अगर (et)
		events |= EPOLLET;

	prपूर्णांकinfo("starting worker/consumer %sthreads%s\n",
		  noaffinity ?  "":"CPU affinity ",
		  nonblocking ? " (nonblocking)":"");
	अगर (!noaffinity)
		pthपढ़ो_attr_init(&thपढ़ो_attr);

	क्रम (i = 0; i < nthपढ़ोs; i++) अणु
		काष्ठा worker *w = &worker[i];

		अगर (multiq) अणु
			w->epollfd = epoll_create(1);
			अगर (w->epollfd < 0)
				err(निकास_त्रुटि, "epoll_create");

			अगर (nested)
				nest_epollfd(w);
		पूर्ण

		w->tid = i;
		w->fdmap = सुस्मृति(nfds, माप(पूर्णांक));
		अगर (!w->fdmap)
			वापस 1;

		क्रम (j = 0; j < nfds; j++) अणु
			पूर्णांक efd = multiq ? w->epollfd : epollfd;
			काष्ठा epoll_event ev;

			w->fdmap[j] = eventfd(0, EFD_NONBLOCK);
			अगर (w->fdmap[j] < 0)
				err(निकास_त्रुटि, "eventfd");

			ev.data.fd = w->fdmap[j];
			ev.events = events;

			ret = epoll_ctl(efd, EPOLL_CTL_ADD,
					w->fdmap[j], &ev);
			अगर (ret < 0)
				err(निकास_त्रुटि, "epoll_ctl");
		पूर्ण

		अगर (!noaffinity) अणु
			CPU_ZERO(&cpuset);
			CPU_SET(cpu->map[i % cpu->nr], &cpuset);

			ret = pthपढ़ो_attr_setaffinity_np(&thपढ़ो_attr, माप(cpu_set_t), &cpuset);
			अगर (ret)
				err(निकास_त्रुटि, "pthread_attr_setaffinity_np");

			attrp = &thपढ़ो_attr;
		पूर्ण

		ret = pthपढ़ो_create(&w->thपढ़ो, attrp, workerfn,
				     (व्योम *)(काष्ठा worker *) w);
		अगर (ret)
			err(निकास_त्रुटि, "pthread_create");
	पूर्ण

	अगर (!noaffinity)
		pthपढ़ो_attr_destroy(&thपढ़ो_attr);

	वापस ret;
पूर्ण

अटल व्योम *ग_लिखोrfn(व्योम *p)
अणु
	काष्ठा worker *worker = p;
	माप_प्रकार i, j, iter;
	स्थिर uपूर्णांक64_t val = 1;
	sमाप_प्रकार sz;
	काष्ठा बारpec ts = अणु .tv_sec = 0,
			       .tv_nsec = 500 पूर्ण;

	prपूर्णांकinfo("starting writer-thread: doing %s writes ...\n",
		  अक्रमomize? "random":"lineal");

	क्रम (iter = 0; !wकरोne; iter++) अणु
		अगर (अक्रमomize) अणु
			shuffle((व्योम *)worker, nthपढ़ोs, माप(*worker));
		पूर्ण

		क्रम (i = 0; i < nthपढ़ोs; i++) अणु
			काष्ठा worker *w = &worker[i];

			अगर (अक्रमomize) अणु
				shuffle((व्योम *)w->fdmap, nfds, माप(पूर्णांक));
			पूर्ण

			क्रम (j = 0; j < nfds; j++) अणु
				करो अणु
					sz = ग_लिखो(w->fdmap[j], &val, माप(val));
				पूर्ण जबतक (!wकरोne && (sz < 0 && त्रुटि_सं == EAGAIN));
			पूर्ण
		पूर्ण

		nanosleep(&ts, शून्य);
	पूर्ण

	prपूर्णांकinfo("exiting writer-thread (total full-loops: %zd)\n", iter);
	वापस शून्य;
पूर्ण

अटल पूर्णांक cmpworker(स्थिर व्योम *p1, स्थिर व्योम *p2)
अणु

	काष्ठा worker *w1 = (काष्ठा worker *) p1;
	काष्ठा worker *w2 = (काष्ठा worker *) p2;
	वापस w1->tid > w2->tid;
पूर्ण

पूर्णांक bench_epoll_रुको(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक ret = 0;
	काष्ठा sigaction act;
	अचिन्हित पूर्णांक i;
	काष्ठा worker *worker = शून्य;
	काष्ठा perf_cpu_map *cpu;
	pthपढ़ो_t wthपढ़ो;
	काष्ठा rlimit rl, prevrl;

	argc = parse_options(argc, argv, options, bench_epoll_रुको_usage, 0);
	अगर (argc) अणु
		usage_with_options(bench_epoll_रुको_usage, options);
		निकास(निकास_त्रुटि);
	पूर्ण

	स_रखो(&act, 0, माप(act));
	sigfillset(&act.sa_mask);
	act.sa_sigaction = toggle_करोne;
	sigaction(संक_विघ्न, &act, शून्य);

	cpu = perf_cpu_map__new(शून्य);
	अगर (!cpu)
		जाओ errmem;

	/* a single, मुख्य epoll instance */
	अगर (!multiq) अणु
		epollfd = epoll_create(1);
		अगर (epollfd < 0)
			err(निकास_त्रुटि, "epoll_create");

		/*
		 * Deal with nested epolls, अगर any.
		 */
		अगर (nested)
			nest_epollfd(शून्य);
	पूर्ण

	prपूर्णांकinfo("Using %s queue model\n", multiq ? "multi" : "single");
	prपूर्णांकinfo("Nesting level(s): %d\n", nested);

	/* शेष to the number of CPUs and leave one क्रम the ग_लिखोr pthपढ़ो */
	अगर (!nthपढ़ोs)
		nthपढ़ोs = cpu->nr - 1;

	worker = सुस्मृति(nthपढ़ोs, माप(*worker));
	अगर (!worker) अणु
		जाओ errmem;
	पूर्ण

	अगर (getrlimit(RLIMIT_NOखाता, &prevrl))
		err(निकास_त्रुटि, "getrlimit");
	rl.rlim_cur = rl.rlim_max = nfds * nthपढ़ोs * 2 + 50;
	prपूर्णांकinfo("Setting RLIMIT_NOFILE rlimit from %" PRIu64 " to: %" PRIu64 "\n",
		  (uपूर्णांक64_t)prevrl.rlim_max, (uपूर्णांक64_t)rl.rlim_max);
	अगर (setrlimit(RLIMIT_NOखाता, &rl) < 0)
		err(निकास_त्रुटि, "setrlimit");

	म_लिखो("Run summary [PID %d]: %d threads monitoring%s on "
	       "%d file-descriptors for %d secs.\n\n",
	       getpid(), nthपढ़ोs, oneshot ? " (EPOLLONESHOT semantics)": "", nfds, nsecs);

	init_stats(&throughput_stats);
	pthपढ़ो_mutex_init(&thपढ़ो_lock, शून्य);
	pthपढ़ो_cond_init(&thपढ़ो_parent, शून्य);
	pthपढ़ो_cond_init(&thपढ़ो_worker, शून्य);

	thपढ़ोs_starting = nthपढ़ोs;

	समय_लोofday(&bench__start, शून्य);

	करो_thपढ़ोs(worker, cpu);

	pthपढ़ो_mutex_lock(&thपढ़ो_lock);
	जबतक (thपढ़ोs_starting)
		pthपढ़ो_cond_रुको(&thपढ़ो_parent, &thपढ़ो_lock);
	pthपढ़ो_cond_broadcast(&thपढ़ो_worker);
	pthपढ़ो_mutex_unlock(&thपढ़ो_lock);

	/*
	 * At this poपूर्णांक the workers should be blocked रुकोing क्रम पढ़ो events
	 * to become पढ़ोy. Launch the ग_लिखोr which will स्थिरantly be writing
	 * to each thपढ़ो's fdmap.
	 */
	ret = pthपढ़ो_create(&wthपढ़ो, शून्य, ग_लिखोrfn,
			     (व्योम *)(काष्ठा worker *) worker);
	अगर (ret)
		err(निकास_त्रुटि, "pthread_create");

	sleep(nsecs);
	toggle_करोne(0, शून्य, शून्य);
	prपूर्णांकinfo("main thread: toggling done\n");

	sleep(1); /* meh */
	wकरोne = true;
	ret = pthपढ़ो_join(wthपढ़ो, शून्य);
	अगर (ret)
		err(निकास_त्रुटि, "pthread_join");

	/* cleanup & report results */
	pthपढ़ो_cond_destroy(&thपढ़ो_parent);
	pthपढ़ो_cond_destroy(&thपढ़ो_worker);
	pthपढ़ो_mutex_destroy(&thपढ़ो_lock);

	/* sort the array back beक्रमe reporting */
	अगर (अक्रमomize)
		क्विक(worker, nthपढ़ोs, माप(काष्ठा worker), cmpworker);

	क्रम (i = 0; i < nthपढ़ोs; i++) अणु
		अचिन्हित दीर्घ t = bench__runसमय.tv_sec > 0 ?
			worker[i].ops / bench__runसमय.tv_sec : 0;

		update_stats(&throughput_stats, t);

		अगर (nfds == 1)
			म_लिखो("[thread %2d] fdmap: %p [ %04ld ops/sec ]\n",
			       worker[i].tid, &worker[i].fdmap[0], t);
		अन्यथा
			म_लिखो("[thread %2d] fdmap: %p ... %p [ %04ld ops/sec ]\n",
			       worker[i].tid, &worker[i].fdmap[0],
			       &worker[i].fdmap[nfds-1], t);
	पूर्ण

	prपूर्णांक_summary();

	बंद(epollfd);
	वापस ret;
errmem:
	err(निकास_त्रुटि, "calloc");
पूर्ण
#पूर्ण_अगर // HAVE_EVENTFD_SUPPORT
