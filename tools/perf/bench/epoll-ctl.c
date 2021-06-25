<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Davidlohr Bueso.
 *
 * Benchmark the various operations allowed क्रम epoll_ctl(2).
 * The idea is to concurrently stress a single epoll instance
 */
#अगर_घोषित HAVE_EVENTFD_SUPPORT
/* For the CLR_() macros */
#समावेश <माला.स>
#समावेश <pthपढ़ो.h>

#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <sys/समय.स>
#समावेश <sys/resource.h>
#समावेश <sys/epoll.h>
#समावेश <sys/eventfd.h>
#समावेश <perf/cpumap.h>

#समावेश "../util/stat.h"
#समावेश <subcmd/parse-options.h>
#समावेश "bench.h"

#समावेश <err.h>

#घोषणा prपूर्णांकinfo(fmt, arg...) \
	करो अणु अगर (__verbose) म_लिखो(fmt, ## arg); पूर्ण जबतक (0)

अटल अचिन्हित पूर्णांक nthपढ़ोs = 0;
अटल अचिन्हित पूर्णांक nsecs    = 8;
अटल bool करोne, __verbose, अक्रमomize;

/*
 * epoll related shared variables.
 */

/* Maximum number of nesting allowed inside epoll sets */
#घोषणा EPOLL_MAXNESTS 4

क्रमागत अणु
	OP_EPOLL_ADD,
	OP_EPOLL_MOD,
	OP_EPOLL_DEL,
	EPOLL_NR_OPS,
पूर्ण;

अटल पूर्णांक epollfd;
अटल पूर्णांक *epollfdp;
अटल bool noaffinity;
अटल अचिन्हित पूर्णांक nested = 0;

/* amount of fds to monitor, per thपढ़ो */
अटल अचिन्हित पूर्णांक nfds = 64;

अटल pthपढ़ो_mutex_t thपढ़ो_lock;
अटल अचिन्हित पूर्णांक thपढ़ोs_starting;
अटल काष्ठा stats all_stats[EPOLL_NR_OPS];
अटल pthपढ़ो_cond_t thपढ़ो_parent, thपढ़ो_worker;

काष्ठा worker अणु
	पूर्णांक tid;
	pthपढ़ो_t thपढ़ो;
	अचिन्हित दीर्घ ops[EPOLL_NR_OPS];
	पूर्णांक *fdmap;
पूर्ण;

अटल स्थिर काष्ठा option options[] = अणु
	OPT_UINTEGER('t', "threads", &nthपढ़ोs, "Specify amount of threads"),
	OPT_UINTEGER('r', "runtime", &nsecs,    "Specify runtime (in seconds)"),
	OPT_UINTEGER('f', "nfds", &nfds, "Specify amount of file descriptors to monitor for each thread"),
	OPT_BOOLEAN( 'n', "noaffinity",  &noaffinity,   "Disables CPU affinity"),
	OPT_UINTEGER( 'N', "nested",  &nested,   "Nesting level epoll hierarchy (default is 0, no nesting)"),
	OPT_BOOLEAN( 'R', "randomize", &अक्रमomize,   "Perform random operations on random fds"),
	OPT_BOOLEAN( 'v', "verbose",  &__verbose,   "Verbose mode"),
	OPT_END()
पूर्ण;

अटल स्थिर अक्षर * स्थिर bench_epoll_ctl_usage[] = अणु
	"perf bench epoll ctl <options>",
	शून्य
पूर्ण;

अटल व्योम toggle_करोne(पूर्णांक sig __maybe_unused,
			siginfo_t *info __maybe_unused,
			व्योम *uc __maybe_unused)
अणु
	/* inक्रमm all thपढ़ोs that we're करोne क्रम the day */
	करोne = true;
	समय_लोofday(&bench__end, शून्य);
	समयrsub(&bench__end, &bench__start, &bench__runसमय);
पूर्ण

अटल व्योम nest_epollfd(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा epoll_event ev;

	अगर (nested > EPOLL_MAXNESTS)
		nested = EPOLL_MAXNESTS;
	prपूर्णांकinfo("Nesting level(s): %d\n", nested);

	epollfdp = सुस्मृति(nested, माप(पूर्णांक));
	अगर (!epollfd)
		err(निकास_त्रुटि, "calloc");

	क्रम (i = 0; i < nested; i++) अणु
		epollfdp[i] = epoll_create(1);
		अगर (epollfd < 0)
			err(निकास_त्रुटि, "epoll_create");
	पूर्ण

	ev.events = EPOLLHUP; /* anything */
	ev.data.u64 = i; /* any number */

	क्रम (i = nested - 1; i; i--) अणु
		अगर (epoll_ctl(epollfdp[i - 1], EPOLL_CTL_ADD,
			      epollfdp[i], &ev) < 0)
			err(निकास_त्रुटि, "epoll_ctl");
	पूर्ण

	अगर (epoll_ctl(epollfd, EPOLL_CTL_ADD, *epollfdp, &ev) < 0)
		err(निकास_त्रुटि, "epoll_ctl");
पूर्ण

अटल अंतरभूत व्योम करो_epoll_op(काष्ठा worker *w, पूर्णांक op, पूर्णांक fd)
अणु
	पूर्णांक error;
	काष्ठा epoll_event ev;

	ev.events = EPOLLIN;
	ev.data.u64 = fd;

	चयन (op) अणु
	हाल OP_EPOLL_ADD:
		error = epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
		अवरोध;
	हाल OP_EPOLL_MOD:
		ev.events = EPOLLOUT;
		error = epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
		अवरोध;
	हाल OP_EPOLL_DEL:
		error = epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, शून्य);
		अवरोध;
	शेष:
		error = 1;
		अवरोध;
	पूर्ण

	अगर (!error)
		w->ops[op]++;
पूर्ण

अटल अंतरभूत व्योम करो_अक्रमom_epoll_op(काष्ठा worker *w)
अणु
	अचिन्हित दीर्घ rnd1 = अक्रमom(), rnd2 = अक्रमom();
	पूर्णांक op, fd;

	fd = w->fdmap[rnd1 % nfds];
	op = rnd2 % EPOLL_NR_OPS;

	करो_epoll_op(w, op, fd);
पूर्ण

अटल व्योम *workerfn(व्योम *arg)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा worker *w = (काष्ठा worker *) arg;
	काष्ठा बारpec ts = अणु .tv_sec = 0,
			       .tv_nsec = 250 पूर्ण;

	pthपढ़ो_mutex_lock(&thपढ़ो_lock);
	thपढ़ोs_starting--;
	अगर (!thपढ़ोs_starting)
		pthपढ़ो_cond_संकेत(&thपढ़ो_parent);
	pthपढ़ो_cond_रुको(&thपढ़ो_worker, &thपढ़ो_lock);
	pthपढ़ो_mutex_unlock(&thपढ़ो_lock);

	/* Let 'em loose */
	करो अणु
		/* अक्रमom */
		अगर (अक्रमomize) अणु
			करो_अक्रमom_epoll_op(w);
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < nfds; i++) अणु
				करो_epoll_op(w, OP_EPOLL_ADD, w->fdmap[i]);
				करो_epoll_op(w, OP_EPOLL_MOD, w->fdmap[i]);
				करो_epoll_op(w, OP_EPOLL_DEL, w->fdmap[i]);
			पूर्ण
		पूर्ण

		nanosleep(&ts, शून्य);
	पूर्ण  जबतक (!करोne);

	वापस शून्य;
पूर्ण

अटल व्योम init_fdmaps(काष्ठा worker *w, पूर्णांक pct)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक inc;
	काष्ठा epoll_event ev;

	अगर (!pct)
		वापस;

	inc = 100/pct;
	क्रम (i = 0; i < nfds; i+=inc) अणु
		ev.data.fd = w->fdmap[i];
		ev.events = EPOLLIN;

		अगर (epoll_ctl(epollfd, EPOLL_CTL_ADD, w->fdmap[i], &ev) < 0)
			err(निकास_त्रुटि, "epoll_ct");
	पूर्ण
पूर्ण

अटल पूर्णांक करो_thपढ़ोs(काष्ठा worker *worker, काष्ठा perf_cpu_map *cpu)
अणु
	pthपढ़ो_attr_t thपढ़ो_attr, *attrp = शून्य;
	cpu_set_t cpuset;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक ret = 0;

	अगर (!noaffinity)
		pthपढ़ो_attr_init(&thपढ़ो_attr);

	क्रम (i = 0; i < nthपढ़ोs; i++) अणु
		काष्ठा worker *w = &worker[i];

		w->tid = i;
		w->fdmap = सुस्मृति(nfds, माप(पूर्णांक));
		अगर (!w->fdmap)
			वापस 1;

		क्रम (j = 0; j < nfds; j++) अणु
			w->fdmap[j] = eventfd(0, EFD_NONBLOCK);
			अगर (w->fdmap[j] < 0)
				err(निकास_त्रुटि, "eventfd");
		पूर्ण

		/*
		 * Lets add 50% of the fdmap to the epoll instance, and
		 * करो it beक्रमe any thपढ़ोs are started; otherwise there is
		 * an initial bias of the call failing  (mod and del ops).
		 */
		अगर (अक्रमomize)
			init_fdmaps(w, 50);

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

अटल व्योम prपूर्णांक_summary(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ avg[EPOLL_NR_OPS];
	द्विगुन stddev[EPOLL_NR_OPS];

	क्रम (i = 0; i < EPOLL_NR_OPS; i++) अणु
		avg[i] = avg_stats(&all_stats[i]);
		stddev[i] = stddev_stats(&all_stats[i]);
	पूर्ण

	म_लिखो("\nAveraged %ld ADD operations (+- %.2f%%)\n",
	       avg[OP_EPOLL_ADD], rel_stddev_stats(stddev[OP_EPOLL_ADD],
						   avg[OP_EPOLL_ADD]));
	म_लिखो("Averaged %ld MOD operations (+- %.2f%%)\n",
	       avg[OP_EPOLL_MOD], rel_stddev_stats(stddev[OP_EPOLL_MOD],
						   avg[OP_EPOLL_MOD]));
	म_लिखो("Averaged %ld DEL operations (+- %.2f%%)\n",
	       avg[OP_EPOLL_DEL], rel_stddev_stats(stddev[OP_EPOLL_DEL],
						   avg[OP_EPOLL_DEL]));
पूर्ण

पूर्णांक bench_epoll_ctl(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक j, ret = 0;
	काष्ठा sigaction act;
	काष्ठा worker *worker = शून्य;
	काष्ठा perf_cpu_map *cpu;
	काष्ठा rlimit rl, prevrl;
	अचिन्हित पूर्णांक i;

	argc = parse_options(argc, argv, options, bench_epoll_ctl_usage, 0);
	अगर (argc) अणु
		usage_with_options(bench_epoll_ctl_usage, options);
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
	epollfd = epoll_create(1);
	अगर (epollfd < 0)
		err(निकास_त्रुटि, "epoll_create");

	/*
	 * Deal with nested epolls, अगर any.
	 */
	अगर (nested)
		nest_epollfd();

	/* शेष to the number of CPUs */
	अगर (!nthपढ़ोs)
		nthपढ़ोs = cpu->nr;

	worker = सुस्मृति(nthपढ़ोs, माप(*worker));
	अगर (!worker)
		जाओ errmem;

	अगर (getrlimit(RLIMIT_NOखाता, &prevrl))
	    err(निकास_त्रुटि, "getrlimit");
	rl.rlim_cur = rl.rlim_max = nfds * nthपढ़ोs * 2 + 50;
	prपूर्णांकinfo("Setting RLIMIT_NOFILE rlimit from %" PRIu64 " to: %" PRIu64 "\n",
		  (uपूर्णांक64_t)prevrl.rlim_max, (uपूर्णांक64_t)rl.rlim_max);
	अगर (setrlimit(RLIMIT_NOखाता, &rl) < 0)
		err(निकास_त्रुटि, "setrlimit");

	म_लिखो("Run summary [PID %d]: %d threads doing epoll_ctl ops "
	       "%d file-descriptors for %d secs.\n\n",
	       getpid(), nthपढ़ोs, nfds, nsecs);

	क्रम (i = 0; i < EPOLL_NR_OPS; i++)
		init_stats(&all_stats[i]);

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

	sleep(nsecs);
	toggle_करोne(0, शून्य, शून्य);
	prपूर्णांकinfo("main thread: toggling done\n");

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
		अचिन्हित दीर्घ t[EPOLL_NR_OPS];

		क्रम (j = 0; j < EPOLL_NR_OPS; j++) अणु
			t[j] = worker[i].ops[j];
			update_stats(&all_stats[j], t[j]);
		पूर्ण

		अगर (nfds == 1)
			म_लिखो("[thread %2d] fdmap: %p [ add: %04ld; mod: %04ld; del: %04lds ops ]\n",
			       worker[i].tid, &worker[i].fdmap[0],
			       t[OP_EPOLL_ADD], t[OP_EPOLL_MOD], t[OP_EPOLL_DEL]);
		अन्यथा
			म_लिखो("[thread %2d] fdmap: %p ... %p [ add: %04ld ops; mod: %04ld ops; del: %04ld ops ]\n",
			       worker[i].tid, &worker[i].fdmap[0],
			       &worker[i].fdmap[nfds-1],
			       t[OP_EPOLL_ADD], t[OP_EPOLL_MOD], t[OP_EPOLL_DEL]);
	पूर्ण

	prपूर्णांक_summary();

	बंद(epollfd);
	वापस ret;
errmem:
	err(निकास_त्रुटि, "calloc");
पूर्ण
#पूर्ण_अगर // HAVE_EVENTFD_SUPPORT
