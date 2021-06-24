<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017, 2018, 2019, 2021 BMW Car IT GmbH
 * Author: Viktor Rosendahl (viktor.rosendahl@bmw.de)
 */

#घोषणा _GNU_SOURCE
#घोषणा _POSIX_C_SOURCE 200809L

#समावेश <प्रकार.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश <err.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <getopt.h>
#समावेश <sched.h>
#समावेश <linux/unistd.h>
#समावेश <संकेत.स>
#समावेश <sys/inotअगरy.h>
#समावेश <unistd.h>
#समावेश <pthपढ़ो.h>
#समावेश <tracefs.h>

अटल स्थिर अक्षर *prg_name;
अटल स्थिर अक्षर *prg_unknown = "unknown program name";

अटल पूर्णांक fd_मानक_निकास;

अटल पूर्णांक sched_policy;
अटल bool sched_policy_set;

अटल पूर्णांक sched_pri;
अटल bool sched_pri_set;

अटल bool trace_enable = true;
अटल bool setup_ftrace = true;
अटल bool use_अक्रमom_sleep;

#घोषणा TRACE_OPTS				\
	C(FUNC_TR, "function-trace"),		\
	C(DISP_GR, "display-graph"),		\
	C(NR,       शून्य)

#अघोषित C
#घोषणा C(a, b) OPTIDX_##a

क्रमागत traceopt अणु
	TRACE_OPTS
पूर्ण;

#अघोषित C
#घोषणा C(a, b)  b

अटल स्थिर अक्षर *स्थिर optstr[] = अणु
	TRACE_OPTS
पूर्ण;

क्रमागत errhandling अणु
	ERR_EXIT = 0,
	ERR_WARN,
	ERR_CLEANUP,
पूर्ण;

अटल bool use_options[OPTIDX_NR];

अटल अक्षर inotअगरy_buffer[655360];

#घोषणा likely(x)      __builtin_expect(!!(x), 1)
#घोषणा unlikely(x)    __builtin_expect(!!(x), 0)
#घोषणा bool2str(x)    (x ? "true":"false")

#घोषणा DEFAULT_NR_PRINTER_THREADS (3)
अटल अचिन्हित पूर्णांक nr_thपढ़ोs = DEFAULT_NR_PRINTER_THREADS;

#घोषणा DEFAULT_TABLE_SIZE (2)
अटल अचिन्हित पूर्णांक table_startsize = DEFAULT_TABLE_SIZE;

अटल पूर्णांक verbosity;

#घोषणा verbose_sizechange() (verbosity >= 1)
#घोषणा verbose_lostevent()  (verbosity >= 2)
#घोषणा verbose_ftrace()     (verbosity >= 1)

#घोषणा was_changed(ORIG, CUR) (म_भेद(ORIG, CUR) != 0)
#घोषणा needs_change(CUR, WANTED) (म_भेद(CUR, WANTED) != 0)

अटल स्थिर अक्षर *debug_tracefile;
अटल स्थिर अक्षर *debug_tracefile_dflt;
अटल स्थिर अक्षर *debug_maxlat;
अटल स्थिर अक्षर *debug_maxlat_dflt;
अटल स्थिर अक्षर * स्थिर DEBUG_NOखाता = "[file not found]";

अटल स्थिर अक्षर * स्थिर TR_MAXLAT  = "tracing_max_latency";
अटल स्थिर अक्षर * स्थिर TR_THRESH  = "tracing_thresh";
अटल स्थिर अक्षर * स्थिर TR_CURRENT = "current_tracer";
अटल स्थिर अक्षर * स्थिर TR_OPTIONS = "trace_options";

अटल स्थिर अक्षर * स्थिर NOP_TRACER = "nop";

अटल स्थिर अक्षर * स्थिर OPT_NO_PREFIX = "no";

#घोषणा DFLT_THRESHOLD_US "0"
अटल स्थिर अक्षर *threshold = DFLT_THRESHOLD_US;

#घोषणा DEV_URANDOM     "/dev/urandom"
#घोषणा RT_DEFAULT_PRI (99)
#घोषणा DEFAULT_PRI    (0)

#घोषणा USEC_PER_MSEC (1000L)
#घोषणा NSEC_PER_USEC (1000L)
#घोषणा NSEC_PER_MSEC (USEC_PER_MSEC * NSEC_PER_USEC)

#घोषणा MSEC_PER_SEC (1000L)
#घोषणा USEC_PER_SEC (USEC_PER_MSEC * MSEC_PER_SEC)
#घोषणा NSEC_PER_SEC (NSEC_PER_MSEC * MSEC_PER_SEC)

#घोषणा SLEEP_TIME_MS_DEFAULT (1000L)
#घोषणा TRY_PRINTMUTEX_MS (1000)

अटल दीर्घ sleep_समय = (USEC_PER_MSEC * SLEEP_TIME_MS_DEFAULT);

अटल स्थिर अक्षर * स्थिर queue_full_warning =
"Could not queue trace for printing. It is likely that events happen faster\n"
"than what they can be printed. Probably partly because of random sleeping\n";

अटल स्थिर अक्षर * स्थिर no_tracer_msg =
"Could not find any tracers! Running this program as root may help!\n";

अटल स्थिर अक्षर * स्थिर no_latency_tr_msg =
"No latency tracers are supported by your kernel!\n";

काष्ठा policy अणु
	स्थिर अक्षर *name;
	पूर्णांक policy;
	पूर्णांक शेष_pri;
पूर्ण;

अटल स्थिर काष्ठा policy policies[] = अणु
	अणु "other", SCHED_OTHER, DEFAULT_PRI    पूर्ण,
	अणु "batch", SCHED_BATCH, DEFAULT_PRI    पूर्ण,
	अणु "idle",  SCHED_IDLE,  DEFAULT_PRI    पूर्ण,
	अणु "rr",    SCHED_RR,    RT_DEFAULT_PRI पूर्ण,
	अणु "fifo",  SCHED_FIFO,  RT_DEFAULT_PRI पूर्ण,
	अणु शून्य,    0,           DEFAULT_PRI    पूर्ण
पूर्ण;

/*
 * The शेष tracer will be the first on this list that is supported by the
 * currently running Linux kernel.
 */
अटल स्थिर अक्षर * स्थिर relevant_tracers[] = अणु
	"preemptirqsoff",
	"preemptoff",
	"irqsoff",
	"wakeup",
	"wakeup_rt",
	"wakeup_dl",
	शून्य
पूर्ण;

/* This is the list of tracers क्रम which अक्रमom sleep makes sense */
अटल स्थिर अक्षर * स्थिर अक्रमom_tracers[] = अणु
	"preemptirqsoff",
	"preemptoff",
	"irqsoff",
	शून्य
पूर्ण;

अटल स्थिर अक्षर *current_tracer;
अटल bool क्रमce_tracer;

काष्ठा ftrace_state अणु
	अक्षर *tracer;
	अक्षर *thresh;
	bool opt[OPTIDX_NR];
	bool opt_valid[OPTIDX_NR];
	pthपढ़ो_mutex_t mutex;
पूर्ण;

काष्ठा entry अणु
	पूर्णांक ticket;
	पूर्णांक ticket_completed_ref;
पूर्ण;

काष्ठा prपूर्णांक_state अणु
	पूर्णांक ticket_counter;
	पूर्णांक ticket_completed;
	pthपढ़ो_mutex_t mutex;
	pthपढ़ो_cond_t cond;
	पूर्णांक cnt;
	pthपढ़ो_mutex_t cnt_mutex;
पूर्ण;

काष्ठा लघु_msg अणु
	अक्षर buf[160];
	पूर्णांक len;
पूर्ण;

अटल काष्ठा prपूर्णांक_state prपूर्णांकstate;
अटल काष्ठा ftrace_state save_state;
अस्थिर संक_पूर्ण_प्रकार संकेत_flag;

#घोषणा PROB_TABLE_MAX_SIZE (1000)

पूर्णांक probabilities[PROB_TABLE_MAX_SIZE];

काष्ठा sleep_table अणु
	पूर्णांक *table;
	पूर्णांक size;
	pthपढ़ो_mutex_t mutex;
पूर्ण;

अटल काष्ठा sleep_table sleeptable;

#घोषणा QUEUE_SIZE (10)

काष्ठा queue अणु
	काष्ठा entry entries[QUEUE_SIZE];
	पूर्णांक next_prod_idx;
	पूर्णांक next_cons_idx;
	pthपढ़ो_mutex_t mutex;
	pthपढ़ो_cond_t cond;
पूर्ण;

#घोषणा MAX_THREADS (40)

काष्ठा queue prपूर्णांकqueue;
pthपढ़ो_t prपूर्णांकthपढ़ो[MAX_THREADS];
pthपढ़ो_mutex_t prपूर्णांक_mtx;
#घोषणा PRINT_BUFFER_SIZE (16 * 1024 * 1024)

अटल व्योम cleanup_निकास(पूर्णांक status);
अटल पूर्णांक set_trace_opt(स्थिर अक्षर *opt, bool value);

अटल __always_अंतरभूत व्योम *दो_स्मृति_or_die(माप_प्रकार size)
अणु
	व्योम *ptr = दो_स्मृति(size);

	अगर (unlikely(ptr == शून्य)) अणु
		warn("malloc() failed");
		cleanup_निकास(निकास_त्रुटि);
	पूर्ण
	वापस ptr;
पूर्ण

अटल __always_अंतरभूत व्योम *दो_स्मृति_or_die_nocleanup(माप_प्रकार size)
अणु
	व्योम *ptr = दो_स्मृति(size);

	अगर (unlikely(ptr == शून्य))
		err(0, "malloc() failed");
	वापस ptr;
पूर्ण

अटल __always_अंतरभूत व्योम ग_लिखो_or_die(पूर्णांक fd, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार r;

	करो अणु
		r = ग_लिखो(fd, buf, count);
		अगर (unlikely(r < 0)) अणु
			अगर (त्रुटि_सं == EINTR)
				जारी;
			warn("write() failed");
			cleanup_निकास(निकास_त्रुटि);
		पूर्ण
		count -= r;
		buf += r;
	पूर्ण जबतक (count > 0);
पूर्ण

अटल __always_अंतरभूत व्योम घड़ी_समय_लो_or_die(घड़ीid_t clk_id,
						 काष्ठा बारpec *tp)
अणु
	पूर्णांक r = घड़ी_समय_लो(clk_id, tp);

	अगर (unlikely(r != 0))
		err(निकास_त्रुटि, "clock_gettime() failed");
पूर्ण

अटल __always_अंतरभूत व्योम sigemptyset_or_die(sigset_t *s)
अणु
	अगर (unlikely(sigemptyset(s) != 0)) अणु
		warn("sigemptyset() failed");
		cleanup_निकास(निकास_त्रुटि);
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम sigaddset_or_die(sigset_t *s, पूर्णांक signum)
अणु
	अगर (unlikely(sigaddset(s, signum) != 0)) अणु
		warn("sigemptyset() failed");
		cleanup_निकास(निकास_त्रुटि);
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम sigaction_or_die(पूर्णांक signum,
					     स्थिर काष्ठा sigaction *act,
					     काष्ठा sigaction *oldact)
अणु
	अगर (unlikely(sigaction(signum, act, oldact) != 0)) अणु
		warn("sigaction() failed");
		cleanup_निकास(निकास_त्रुटि);
	पूर्ण
पूर्ण

अटल व्योम खोलो_मानक_निकास(व्योम)
अणु
	अगर (रखो_भबफ(मानक_निकास, शून्य, _IONBF, 0) != 0)
		err(निकास_त्रुटि, "setvbuf() failed");
	fd_मानक_निकास = fileno(मानक_निकास);
	अगर (fd_मानक_निकास < 0)
		err(निकास_त्रुटि, "fileno() failed");
पूर्ण

/*
 * It's not worth it to call cleanup_निकास() from mutex functions because
 * cleanup_निकास() uses mutexes.
 */
अटल __always_अंतरभूत व्योम mutex_lock(pthपढ़ो_mutex_t *mtx)
अणु
	त्रुटि_सं = pthपढ़ो_mutex_lock(mtx);
	अगर (unlikely(त्रुटि_सं))
		err(निकास_त्रुटि, "pthread_mutex_lock() failed");
पूर्ण


अटल __always_अंतरभूत व्योम mutex_unlock(pthपढ़ो_mutex_t *mtx)
अणु
	त्रुटि_सं = pthपढ़ो_mutex_unlock(mtx);
	अगर (unlikely(त्रुटि_सं))
		err(निकास_त्रुटि, "pthread_mutex_unlock() failed");
पूर्ण

अटल __always_अंतरभूत व्योम cond_संकेत(pthपढ़ो_cond_t *cond)
अणु
	त्रुटि_सं = pthपढ़ो_cond_संकेत(cond);
	अगर (unlikely(त्रुटि_सं))
		err(निकास_त्रुटि, "pthread_cond_signal() failed");
पूर्ण

अटल __always_अंतरभूत व्योम cond_रुको(pthपढ़ो_cond_t *restrict cond,
				      pthपढ़ो_mutex_t *restrict mutex)
अणु
	त्रुटि_सं = pthपढ़ो_cond_रुको(cond, mutex);
	अगर (unlikely(त्रुटि_सं))
		err(निकास_त्रुटि, "pthread_cond_wait() failed");
पूर्ण

अटल __always_अंतरभूत व्योम cond_broadcast(pthपढ़ो_cond_t *cond)
अणु
	त्रुटि_सं = pthपढ़ो_cond_broadcast(cond);
	अगर (unlikely(त्रुटि_सं))
		err(निकास_त्रुटि, "pthread_cond_broadcast() failed");
पूर्ण

अटल __always_अंतरभूत व्योम
mutex_init(pthपढ़ो_mutex_t *mutex,
	   स्थिर pthपढ़ो_mutexattr_t *attr)
अणु
	त्रुटि_सं = pthपढ़ो_mutex_init(mutex, attr);
	अगर (त्रुटि_सं)
		err(निकास_त्रुटि, "pthread_mutex_init() failed");
पूर्ण

अटल __always_अंतरभूत व्योम mutexattr_init(pthपढ़ो_mutexattr_t *attr)
अणु
	त्रुटि_सं = pthपढ़ो_mutexattr_init(attr);
	अगर (त्रुटि_सं)
		err(निकास_त्रुटि, "pthread_mutexattr_init() failed");
पूर्ण

अटल __always_अंतरभूत व्योम mutexattr_destroy(pthपढ़ो_mutexattr_t *attr)
अणु
	त्रुटि_सं = pthपढ़ो_mutexattr_destroy(attr);
	अगर (त्रुटि_सं)
		err(निकास_त्रुटि, "pthread_mutexattr_destroy() failed");
पूर्ण

अटल __always_अंतरभूत व्योम mutexattr_settype(pthपढ़ो_mutexattr_t *attr,
					      पूर्णांक type)
अणु
	त्रुटि_सं = pthपढ़ो_mutexattr_settype(attr, type);
	अगर (त्रुटि_सं)
		err(निकास_त्रुटि, "pthread_mutexattr_settype() failed");
पूर्ण

अटल __always_अंतरभूत व्योम condattr_init(pthपढ़ो_condattr_t *attr)
अणु
	त्रुटि_सं = pthपढ़ो_condattr_init(attr);
	अगर (त्रुटि_सं)
		err(निकास_त्रुटि, "pthread_condattr_init() failed");
पूर्ण

अटल __always_अंतरभूत व्योम condattr_destroy(pthपढ़ो_condattr_t *attr)
अणु
	त्रुटि_सं = pthपढ़ो_condattr_destroy(attr);
	अगर (त्रुटि_सं)
		err(निकास_त्रुटि, "pthread_condattr_destroy() failed");
पूर्ण

अटल __always_अंतरभूत व्योम condattr_setघड़ी(pthपढ़ो_condattr_t *attr,
					      घड़ीid_t घड़ी_id)
अणु
	त्रुटि_सं = pthपढ़ो_condattr_setघड़ी(attr, घड़ी_id);
	अगर (unlikely(त्रुटि_सं))
		err(निकास_त्रुटि, "pthread_condattr_setclock() failed");
पूर्ण

अटल __always_अंतरभूत व्योम cond_init(pthपढ़ो_cond_t *cond,
				      स्थिर pthपढ़ो_condattr_t *attr)
अणु
	त्रुटि_सं = pthपढ़ो_cond_init(cond, attr);
	अगर (त्रुटि_सं)
		err(निकास_त्रुटि, "pthread_cond_init() failed");
पूर्ण

अटल __always_अंतरभूत पूर्णांक
cond_समयdरुको(pthपढ़ो_cond_t *restrict cond,
	       pthपढ़ो_mutex_t *restrict mutex,
	       स्थिर काष्ठा बारpec *restrict असलसमय)
अणु
	त्रुटि_सं = pthपढ़ो_cond_समयdरुको(cond, mutex, असलसमय);
	अगर (त्रुटि_सं && त्रुटि_सं != ETIMEDOUT)
		err(निकास_त्रुटि, "pthread_cond_timedwait() failed");
	वापस त्रुटि_सं;
पूर्ण

अटल व्योम init_prपूर्णांकstate(व्योम)
अणु
	pthपढ़ो_condattr_t cattr;

	prपूर्णांकstate.ticket_counter = 0;
	prपूर्णांकstate.ticket_completed = 0;
	prपूर्णांकstate.cnt = 0;

	mutex_init(&prपूर्णांकstate.mutex, शून्य);

	condattr_init(&cattr);
	condattr_setघड़ी(&cattr, CLOCK_MONOTONIC);
	cond_init(&prपूर्णांकstate.cond, &cattr);
	condattr_destroy(&cattr);
पूर्ण

अटल व्योम init_prपूर्णांक_mtx(व्योम)
अणु
	pthपढ़ो_mutexattr_t mattr;

	mutexattr_init(&mattr);
	mutexattr_settype(&mattr, PTHREAD_MUTEX_RECURSIVE);
	mutex_init(&prपूर्णांक_mtx, &mattr);
	mutexattr_destroy(&mattr);

पूर्ण

अटल व्योम संकेत_blocking(पूर्णांक how)
अणु
	sigset_t s;

	sigemptyset_or_die(&s);
	sigaddset_or_die(&s, SIGHUP);
	sigaddset_or_die(&s, संक_इति);
	sigaddset_or_die(&s, संक_विघ्न);

	त्रुटि_सं = pthपढ़ो_sigmask(how, &s, शून्य);
	अगर (unlikely(त्रुटि_सं)) अणु
		warn("pthread_sigmask() failed");
		cleanup_निकास(निकास_त्रुटि);
	पूर्ण
पूर्ण

अटल व्योम संकेत_handler(पूर्णांक num)
अणु
	संकेत_flag = num;
पूर्ण

अटल व्योम setup_sig_handler(व्योम)
अणु
	काष्ठा sigaction sa;

	स_रखो(&sa, 0, माप(sa));
	sa.sa_handler = संकेत_handler;

	sigaction_or_die(SIGHUP, &sa, शून्य);
	sigaction_or_die(संक_इति, &sa, शून्य);
	sigaction_or_die(संक_विघ्न, &sa, शून्य);
पूर्ण

अटल व्योम process_संकेत(पूर्णांक संकेत)
अणु
	अक्षर *name;

	name = strसंकेत(संकेत);
	अगर (name == शून्य)
		म_लिखो("Received signal %d\n", संकेत);
	अन्यथा
		म_लिखो("Received signal %d (%s)\n", संकेत, name);
	cleanup_निकास(निकास_सफल);
पूर्ण

अटल __always_अंतरभूत व्योम check_संकेतs(व्योम)
अणु
	पूर्णांक संकेत = संकेत_flag;

	अगर (unlikely(संकेत))
		process_संकेत(संकेत);
पूर्ण

अटल __always_अंतरभूत व्योम get_समय_in_future(काष्ठा बारpec *future,
					       दीर्घ समय_us)
अणु
	दीर्घ nsec;

	घड़ी_समय_लो_or_die(CLOCK_MONOTONIC, future);
	future->tv_sec += समय_us / USEC_PER_SEC;
	nsec = future->tv_nsec + (समय_us * NSEC_PER_USEC) % NSEC_PER_SEC;
	अगर (nsec >= NSEC_PER_SEC) अणु
		future->tv_nsec = nsec % NSEC_PER_SEC;
		future->tv_sec += 1;
	पूर्ण
पूर्ण

अटल __always_अंतरभूत bool समय_has_passed(स्थिर काष्ठा बारpec *समय)
अणु
	काष्ठा बारpec now;

	घड़ी_समय_लो_or_die(CLOCK_MONOTONIC, &now);
	अगर (now.tv_sec > समय->tv_sec)
		वापस true;
	अगर (now.tv_sec < समय->tv_sec)
		वापस false;
	वापस (now.tv_nsec >= समय->tv_nsec);
पूर्ण

अटल bool mutex_trylock_limit(pthपढ़ो_mutex_t *mutex, पूर्णांक समय_ms)
अणु
	दीर्घ समय_us = समय_ms * USEC_PER_MSEC;
	काष्ठा बारpec limit;

	get_समय_in_future(&limit, समय_us);
	करो अणु
		त्रुटि_सं =  pthपढ़ो_mutex_trylock(mutex);
		अगर (त्रुटि_सं && त्रुटि_सं != EBUSY)
			err(निकास_त्रुटि, "pthread_mutex_trylock() failed");
	पूर्ण जबतक (त्रुटि_सं && !समय_has_passed(&limit));
	वापस त्रुटि_सं == 0;
पूर्ण

अटल व्योम restore_trace_opts(स्थिर काष्ठा ftrace_state *state,
				स्थिर bool *cur)
अणु
	पूर्णांक i;
	पूर्णांक r;

	क्रम (i = 0; i < OPTIDX_NR; i++)
		अगर (state->opt_valid[i] && state->opt[i] != cur[i]) अणु
			r = set_trace_opt(optstr[i], state->opt[i]);
			अगर (r < 0)
				warnx("Failed to restore the %s option to %s",
				      optstr[i], bool2str(state->opt[i]));
			अन्यथा अगर (verbose_ftrace())
				म_लिखो("Restored the %s option in %s to %s\n",
				       optstr[i], TR_OPTIONS,
				       bool2str(state->opt[i]));
		पूर्ण
पूर्ण

अटल अक्षर *पढ़ो_file(स्थिर अक्षर *file, क्रमागत errhandling h)
अणु
	पूर्णांक psize;
	अक्षर *r;
	अटल स्थिर अक्षर *emsg = "Failed to read the %s file";

	r = tracefs_instance_file_पढ़ो(शून्य, file, &psize);
	अगर (!r) अणु
		अगर (h) अणु
			warn(emsg, file);
			अगर (h == ERR_CLEANUP)
				cleanup_निकास(निकास_त्रुटि);
		पूर्ण अन्यथा
			errx(निकास_त्रुटि, emsg, file);
	पूर्ण

	अगर (r && r[psize - 1] == '\n')
		r[psize - 1] = '\0';
	वापस r;
पूर्ण

अटल व्योम restore_file(स्थिर अक्षर *file, अक्षर **saved, स्थिर अक्षर *cur)
अणु
	अगर (*saved && was_changed(*saved, cur)) अणु
		अगर (tracefs_instance_file_ग_लिखो(शून्य, file, *saved) < 0)
			warnx("Failed to restore %s to %s!", file, *saved);
		अन्यथा अगर (verbose_ftrace())
			म_लिखो("Restored %s to %s\n", file, *saved);
		मुक्त(*saved);
		*saved = शून्य;
	पूर्ण
पूर्ण

अटल व्योम restore_ftrace(व्योम)
अणु
	mutex_lock(&save_state.mutex);

	restore_file(TR_CURRENT, &save_state.tracer, current_tracer);
	restore_file(TR_THRESH, &save_state.thresh, threshold);
	restore_trace_opts(&save_state, use_options);

	mutex_unlock(&save_state.mutex);
पूर्ण

अटल व्योम cleanup_निकास(पूर्णांक status)
अणु
	अक्षर *maxlat;

	अगर (!setup_ftrace)
		निकास(status);

	/*
	 * We try the prपूर्णांक_mtx क्रम 1 sec in order to aव्योम garbled
	 * output अगर possible, but अगर it cannot be obtained we proceed anyway.
	 */
	mutex_trylock_limit(&prपूर्णांक_mtx, TRY_PRINTMUTEX_MS);

	maxlat = पढ़ो_file(TR_MAXLAT, ERR_WARN);
	अगर (maxlat) अणु
		म_लिखो("The maximum detected latency was: %sus\n", maxlat);
		मुक्त(maxlat);
	पूर्ण

	restore_ftrace();
	/*
	 * We करो not need to unlock the prपूर्णांक_mtx here because we will निकास at
	 * the end of this function. Unlocking prपूर्णांक_mtx causes problems अगर a
	 * prपूर्णांक thपढ़ो happens to be रुकोing क्रम the mutex because we have
	 * just changed the ftrace settings to the original and thus the
	 * prपूर्णांक thपढ़ो would output incorrect data from ftrace.
	 */
	निकास(status);
पूर्ण

अटल व्योम init_save_state(व्योम)
अणु
	pthपढ़ो_mutexattr_t mattr;

	mutexattr_init(&mattr);
	mutexattr_settype(&mattr, PTHREAD_MUTEX_RECURSIVE);
	mutex_init(&save_state.mutex, &mattr);
	mutexattr_destroy(&mattr);

	save_state.tracer = शून्य;
	save_state.thresh = शून्य;
	save_state.opt_valid[OPTIDX_FUNC_TR] = false;
	save_state.opt_valid[OPTIDX_DISP_GR] = false;
पूर्ण

अटल पूर्णांक prपूर्णांकstate_next_ticket(काष्ठा entry *req)
अणु
	पूर्णांक r;

	r = ++(prपूर्णांकstate.ticket_counter);
	req->ticket = r;
	req->ticket_completed_ref = prपूर्णांकstate.ticket_completed;
	cond_broadcast(&prपूर्णांकstate.cond);
	वापस r;
पूर्ण

अटल __always_अंतरभूत
व्योम prपूर्णांकstate_mark_req_completed(स्थिर काष्ठा entry *req)
अणु
	अगर (req->ticket > prपूर्णांकstate.ticket_completed)
		prपूर्णांकstate.ticket_completed = req->ticket;
पूर्ण

अटल __always_अंतरभूत
bool prपूर्णांकstate_has_new_req_arrived(स्थिर काष्ठा entry *req)
अणु
	वापस (prपूर्णांकstate.ticket_counter != req->ticket);
पूर्ण

अटल __always_अंतरभूत पूर्णांक prपूर्णांकstate_cnt_inc(व्योम)
अणु
	पूर्णांक value;

	mutex_lock(&prपूर्णांकstate.cnt_mutex);
	value = ++prपूर्णांकstate.cnt;
	mutex_unlock(&prपूर्णांकstate.cnt_mutex);
	वापस value;
पूर्ण

अटल __always_अंतरभूत पूर्णांक prपूर्णांकstate_cnt_dec(व्योम)
अणु
	पूर्णांक value;

	mutex_lock(&prपूर्णांकstate.cnt_mutex);
	value = --prपूर्णांकstate.cnt;
	mutex_unlock(&prपूर्णांकstate.cnt_mutex);
	वापस value;
पूर्ण

अटल __always_अंतरभूत पूर्णांक prपूर्णांकstate_cnt_पढ़ो(व्योम)
अणु
	पूर्णांक value;

	mutex_lock(&prपूर्णांकstate.cnt_mutex);
	value = prपूर्णांकstate.cnt;
	mutex_unlock(&prपूर्णांकstate.cnt_mutex);
	वापस value;
पूर्ण

अटल __always_अंतरभूत
bool prev_req_won_race(स्थिर काष्ठा entry *req)
अणु
	वापस (prपूर्णांकstate.ticket_completed != req->ticket_completed_ref);
पूर्ण

अटल व्योम sleeptable_resize(पूर्णांक size, bool prपूर्णांकout, काष्ठा लघु_msg *msg)
अणु
	पूर्णांक bytes;

	अगर (prपूर्णांकout) अणु
		msg->len = 0;
		अगर (unlikely(size > PROB_TABLE_MAX_SIZE))
			bytes = snम_लिखो(msg->buf, माप(msg->buf),
"Cannot increase probability table to %d (maximum size reached)\n", size);
		अन्यथा
			bytes = snम_लिखो(msg->buf, माप(msg->buf),
"Increasing probability table to %d\n", size);
		अगर (bytes < 0)
			warn("snprintf() failed");
		अन्यथा
			msg->len = bytes;
	पूर्ण

	अगर (unlikely(size < 0)) अणु
		/* Should never happen */
		warnx("Bad program state at %s:%d", __खाता__, __LINE__);
		cleanup_निकास(निकास_त्रुटि);
		वापस;
	पूर्ण
	sleeptable.size = size;
	sleeptable.table = &probabilities[PROB_TABLE_MAX_SIZE - size];
पूर्ण

अटल व्योम init_probabilities(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक j = 1000;

	क्रम (i = 0; i < PROB_TABLE_MAX_SIZE; i++) अणु
		probabilities[i] = 1000 / j;
		j--;
	पूर्ण
	mutex_init(&sleeptable.mutex, शून्य);
पूर्ण

अटल पूर्णांक table_get_probability(स्थिर काष्ठा entry *req,
				 काष्ठा लघु_msg *msg)
अणु
	पूर्णांक dअगरf = req->ticket - req->ticket_completed_ref;
	पूर्णांक rval = 0;

	msg->len = 0;
	dअगरf--;
	/* Should never happen...*/
	अगर (unlikely(dअगरf < 0)) अणु
		warnx("Programmer assumption error at %s:%d\n", __खाता__,
		      __LINE__);
		cleanup_निकास(निकास_त्रुटि);
	पूर्ण
	mutex_lock(&sleeptable.mutex);
	अगर (dअगरf >= (sleeptable.size - 1)) अणु
		rval = sleeptable.table[sleeptable.size - 1];
		sleeptable_resize(sleeptable.size + 1, verbose_sizechange(),
				  msg);
	पूर्ण अन्यथा अणु
		rval = sleeptable.table[dअगरf];
	पूर्ण
	mutex_unlock(&sleeptable.mutex);
	वापस rval;
पूर्ण

अटल व्योम init_queue(काष्ठा queue *q)
अणु
	q->next_prod_idx = 0;
	q->next_cons_idx = 0;
	mutex_init(&q->mutex, शून्य);
	त्रुटि_सं = pthपढ़ो_cond_init(&q->cond, शून्य);
	अगर (त्रुटि_सं)
		err(निकास_त्रुटि, "pthread_cond_init() failed");
पूर्ण

अटल __always_अंतरभूत पूर्णांक queue_len(स्थिर काष्ठा queue *q)
अणु
	अगर (q->next_prod_idx >= q->next_cons_idx)
		वापस q->next_prod_idx - q->next_cons_idx;
	अन्यथा
		वापस QUEUE_SIZE - q->next_cons_idx + q->next_prod_idx;
पूर्ण

अटल __always_अंतरभूत पूर्णांक queue_nr_मुक्त(स्थिर काष्ठा queue *q)
अणु
	पूर्णांक nr_मुक्त = QUEUE_SIZE - queue_len(q);

	/*
	 * If there is only one slot left we will anyway lie and claim that the
	 * queue is full because adding an element will make it appear empty
	 */
	अगर (nr_मुक्त == 1)
		nr_मुक्त = 0;
	वापस nr_मुक्त;
पूर्ण

अटल __always_अंतरभूत व्योम queue_idx_inc(पूर्णांक *idx)
अणु
	*idx = (*idx + 1) % QUEUE_SIZE;
पूर्ण

अटल __always_अंतरभूत व्योम queue_push_to_back(काष्ठा queue *q,
					      स्थिर काष्ठा entry *e)
अणु
	q->entries[q->next_prod_idx] = *e;
	queue_idx_inc(&q->next_prod_idx);
पूर्ण

अटल __always_अंतरभूत काष्ठा entry queue_pop_from_front(काष्ठा queue *q)
अणु
	काष्ठा entry e = q->entries[q->next_cons_idx];

	queue_idx_inc(&q->next_cons_idx);
	वापस e;
पूर्ण

अटल __always_अंतरभूत व्योम queue_cond_संकेत(काष्ठा queue *q)
अणु
	cond_संकेत(&q->cond);
पूर्ण

अटल __always_अंतरभूत व्योम queue_cond_रुको(काष्ठा queue *q)
अणु
	cond_रुको(&q->cond, &q->mutex);
पूर्ण

अटल __always_अंतरभूत पूर्णांक queue_try_to_add_entry(काष्ठा queue *q,
						  स्थिर काष्ठा entry *e)
अणु
	पूर्णांक r = 0;

	mutex_lock(&q->mutex);
	अगर (queue_nr_मुक्त(q) > 0) अणु
		queue_push_to_back(q, e);
		cond_संकेत(&q->cond);
	पूर्ण अन्यथा
		r = -1;
	mutex_unlock(&q->mutex);
	वापस r;
पूर्ण

अटल काष्ठा entry queue_रुको_क्रम_entry(काष्ठा queue *q)
अणु
	काष्ठा entry e;

	mutex_lock(&q->mutex);
	जबतक (true) अणु
		अगर (queue_len(&prपूर्णांकqueue) > 0) अणु
			e = queue_pop_from_front(q);
			अवरोध;
		पूर्ण
		queue_cond_रुको(q);
	पूर्ण
	mutex_unlock(&q->mutex);

	वापस e;
पूर्ण

अटल स्थिर काष्ठा policy *policy_from_name(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा policy *p = &policies[0];

	जबतक (p->name != शून्य) अणु
		अगर (!म_भेद(name, p->name))
			वापस p;
		p++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर *policy_name(पूर्णांक policy)
अणु
	स्थिर काष्ठा policy *p = &policies[0];
	अटल स्थिर अक्षर *rval = "unknown";

	जबतक (p->name != शून्य) अणु
		अगर (p->policy == policy)
			वापस p->name;
		p++;
	पूर्ण
	वापस rval;
पूर्ण

अटल bool is_relevant_tracer(स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; relevant_tracers[i]; i++)
		अगर (!म_भेद(name, relevant_tracers[i]))
			वापस true;
	वापस false;
पूर्ण

अटल bool अक्रमom_makes_sense(स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; अक्रमom_tracers[i]; i++)
		अगर (!म_भेद(name, अक्रमom_tracers[i]))
			वापस true;
	वापस false;
पूर्ण

अटल व्योम show_available(व्योम)
अणु
	अक्षर **tracers;
	पूर्णांक found = 0;
	पूर्णांक i;

	tracers = tracefs_tracers(शून्य);
	क्रम (i = 0; tracers && tracers[i]; i++) अणु
		अगर (is_relevant_tracer(tracers[i]))
			found++;
	पूर्ण

	अगर (!tracers) अणु
		warnx(no_tracer_msg);
		वापस;
	पूर्ण

	अगर (!found) अणु
		warnx(no_latency_tr_msg);
		tracefs_list_मुक्त(tracers);
		वापस;
	पूर्ण

	म_लिखो("The following latency tracers are available on your system:\n");
	क्रम (i = 0; tracers[i]; i++) अणु
		अगर (is_relevant_tracer(tracers[i]))
			म_लिखो("%s\n", tracers[i]);
	पूर्ण
	tracefs_list_मुक्त(tracers);
पूर्ण

अटल bool tracer_valid(स्थिर अक्षर *name, bool *notracer)
अणु
	अक्षर **tracers;
	पूर्णांक i;
	bool rval = false;

	*notracer = false;
	tracers = tracefs_tracers(शून्य);
	अगर (!tracers) अणु
		*notracer = true;
		वापस false;
	पूर्ण
	क्रम (i = 0; tracers[i]; i++)
		अगर (!म_भेद(tracers[i], name)) अणु
			rval = true;
			अवरोध;
		पूर्ण
	tracefs_list_मुक्त(tracers);
	वापस rval;
पूर्ण

अटल स्थिर अक्षर *find_शेष_tracer(व्योम)
अणु
	पूर्णांक i;
	bool notracer;
	bool valid;

	क्रम (i = 0; relevant_tracers[i]; i++) अणु
		valid = tracer_valid(relevant_tracers[i], &notracer);
		अगर (notracer)
			errx(निकास_त्रुटि, no_tracer_msg);
		अगर (valid)
			वापस relevant_tracers[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल bool toss_coin(काष्ठा dअक्रम48_data *buffer, अचिन्हित पूर्णांक prob)
अणु
	दीर्घ r;

	अगर (unlikely(lअक्रम48_r(buffer, &r))) अणु
		warnx("lrand48_r() failed");
		cleanup_निकास(निकास_त्रुटि);
	पूर्ण
	r = r % 1000L;
	अगर (r < prob)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण


अटल दीर्घ go_to_sleep(स्थिर काष्ठा entry *req)
अणु
	काष्ठा बारpec future;
	दीर्घ delay = sleep_समय;

	get_समय_in_future(&future, delay);

	mutex_lock(&prपूर्णांकstate.mutex);
	जबतक (!prपूर्णांकstate_has_new_req_arrived(req)) अणु
		cond_समयdरुको(&prपूर्णांकstate.cond, &prपूर्णांकstate.mutex, &future);
		अगर (समय_has_passed(&future))
			अवरोध;
	पूर्ण

	अगर (prपूर्णांकstate_has_new_req_arrived(req))
		delay = -1;
	mutex_unlock(&prपूर्णांकstate.mutex);

	वापस delay;
पूर्ण


अटल व्योम set_priority(व्योम)
अणु
	पूर्णांक r;
	pid_t pid;
	काष्ठा sched_param param;

	स_रखो(&param, 0, माप(param));
	param.sched_priority = sched_pri;

	pid = getpid();
	r = sched_setscheduler(pid, sched_policy, &param);

	अगर (r != 0)
		err(निकास_त्रुटि, "sched_setscheduler() failed");
पूर्ण

pid_t latency_collector_gettid(व्योम)
अणु
	वापस (pid_t) syscall(__NR_gettid);
पूर्ण

अटल व्योम prपूर्णांक_priority(व्योम)
अणु
	pid_t tid;
	पूर्णांक policy;
	पूर्णांक r;
	काष्ठा sched_param param;

	tid = latency_collector_gettid();
	r = pthपढ़ो_माला_लोchedparam(pthपढ़ो_self(), &policy, &param);
	अगर (r != 0) अणु
		warn("pthread_getschedparam() failed");
		cleanup_निकास(निकास_त्रुटि);
	पूर्ण
	mutex_lock(&prपूर्णांक_mtx);
	म_लिखो("Thread %d runs with scheduling policy %s and priority %d\n",
	       tid, policy_name(policy), param.sched_priority);
	mutex_unlock(&prपूर्णांक_mtx);
पूर्ण

अटल __always_अंतरभूत
व्योम __prपूर्णांक_skipmessage(स्थिर काष्ठा लघु_msg *resize_msg,
			 स्थिर काष्ठा बारpec *बारtamp, अक्षर *buffer,
			 माप_प्रकार bufspace, स्थिर काष्ठा entry *req, bool excuse,
			 स्थिर अक्षर *str)
अणु
	sमाप_प्रकार bytes = 0;
	अक्षर *p = &buffer[0];
	दीर्घ us, sec;
	पूर्णांक r;

	sec = बारtamp->tv_sec;
	us = बारtamp->tv_nsec / 1000;

	अगर (resize_msg != शून्य && resize_msg->len > 0) अणु
		म_नकलन(p, resize_msg->buf, resize_msg->len);
		bytes += resize_msg->len;
		p += resize_msg->len;
		bufspace -= resize_msg->len;
	पूर्ण

	अगर (excuse)
		r = snम_लिखो(p, bufspace,
"%ld.%06ld Latency %d printout skipped due to %s\n",
			     sec, us, req->ticket, str);
	अन्यथा
		r = snम_लिखो(p, bufspace, "%ld.%06ld Latency %d detected\n",
			    sec, us, req->ticket);

	अगर (r < 0)
		warn("snprintf() failed");
	अन्यथा
		bytes += r;

	/* These prपूर्णांकs could happen concurrently */
	mutex_lock(&prपूर्णांक_mtx);
	ग_लिखो_or_die(fd_मानक_निकास, buffer, bytes);
	mutex_unlock(&prपूर्णांक_mtx);
पूर्ण

अटल व्योम prपूर्णांक_skipmessage(स्थिर काष्ठा लघु_msg *resize_msg,
			      स्थिर काष्ठा बारpec *बारtamp, अक्षर *buffer,
			      माप_प्रकार bufspace, स्थिर काष्ठा entry *req,
			      bool excuse)
अणु
	__prपूर्णांक_skipmessage(resize_msg, बारtamp, buffer, bufspace, req,
			    excuse, "random delay");
पूर्ण

अटल व्योम prपूर्णांक_losपंचांगessage(स्थिर काष्ठा बारpec *बारtamp, अक्षर *buffer,
			      माप_प्रकार bufspace, स्थिर काष्ठा entry *req,
			      स्थिर अक्षर *reason)
अणु
	__prपूर्णांक_skipmessage(शून्य, बारtamp, buffer, bufspace, req, true,
			    reason);
पूर्ण

अटल व्योम prपूर्णांक_tracefile(स्थिर काष्ठा लघु_msg *resize_msg,
			    स्थिर काष्ठा बारpec *बारtamp, अक्षर *buffer,
			    माप_प्रकार bufspace, दीर्घ slept,
			    स्थिर काष्ठा entry *req)
अणु
	अटल स्थिर पूर्णांक reserve = 256;
	अक्षर *p = &buffer[0];
	sमाप_प्रकार bytes = 0;
	sमाप_प्रकार bytes_tot = 0;
	दीर्घ us, sec;
	दीर्घ slept_ms;
	पूर्णांक trace_fd;

	/* Save some space क्रम the final string and final null अक्षर */
	bufspace = bufspace - reserve - 1;

	अगर (resize_msg != शून्य && resize_msg->len > 0) अणु
		bytes = resize_msg->len;
		म_नकलन(p, resize_msg->buf, bytes);
		bytes_tot += bytes;
		p += bytes;
		bufspace -= bytes;
	पूर्ण

	trace_fd = खोलो(debug_tracefile, O_RDONLY);

	अगर (trace_fd < 0) अणु
		warn("open() failed on %s", debug_tracefile);
		वापस;
	पूर्ण

	sec = बारtamp->tv_sec;
	us = बारtamp->tv_nsec / 1000;

	अगर (slept != 0) अणु
		slept_ms = slept / 1000;
		bytes = snम_लिखो(p, bufspace,
"%ld.%06ld Latency %d randomly sleep for %ld ms before print\n",
				 sec, us, req->ticket, slept_ms);
	पूर्ण अन्यथा अणु
		bytes = snम_लिखो(p, bufspace,
				 "%ld.%06ld Latency %d immediate print\n", sec,
				 us, req->ticket);
	पूर्ण

	अगर (bytes < 0) अणु
		warn("snprintf() failed");
		वापस;
	पूर्ण
	p += bytes;
	bufspace -= bytes;
	bytes_tot += bytes;

	bytes = snम_लिखो(p, bufspace,
">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BEGIN <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n"
		);

	अगर (bytes < 0) अणु
		warn("snprintf() failed");
		वापस;
	पूर्ण

	p += bytes;
	bufspace -= bytes;
	bytes_tot += bytes;

	करो अणु
		bytes = पढ़ो(trace_fd, p, bufspace);
		अगर (bytes < 0) अणु
			अगर (त्रुटि_सं == EINTR)
				जारी;
			warn("read() failed on %s", debug_tracefile);
			अगर (unlikely(बंद(trace_fd) != 0))
				warn("close() failed on %s", debug_tracefile);
			वापस;
		पूर्ण
		अगर (bytes == 0)
			अवरोध;
		p += bytes;
		bufspace -= bytes;
		bytes_tot += bytes;
	पूर्ण जबतक (true);

	अगर (unlikely(बंद(trace_fd) != 0))
		warn("close() failed on %s", debug_tracefile);

	prपूर्णांकstate_cnt_dec();
	/* Add the reserve space back to the budget क्रम the final string */
	bufspace += reserve;

	bytes = snम_लिखो(p, bufspace,
			 ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");

	अगर (bytes < 0) अणु
		warn("snprintf() failed");
		वापस;
	पूर्ण

	bytes_tot += bytes;

	/* These prपूर्णांकs could happen concurrently */
	mutex_lock(&prपूर्णांक_mtx);
	ग_लिखो_or_die(fd_मानक_निकास, buffer, bytes_tot);
	mutex_unlock(&prपूर्णांक_mtx);
पूर्ण

अटल अक्षर *get_no_opt(स्थिर अक्षर *opt)
अणु
	अक्षर *no_opt;
	पूर्णांक s;

	s = म_माप(opt) + म_माप(OPT_NO_PREFIX) + 1;
	/* We may be called from cleanup_निकास() via set_trace_opt() */
	no_opt = दो_स्मृति_or_die_nocleanup(s);
	म_नकल(no_opt, OPT_NO_PREFIX);
	म_जोड़ो(no_opt, opt);
	वापस no_opt;
पूर्ण

अटल अक्षर *find_next_optstr(स्थिर अक्षर *allopt, स्थिर अक्षर **next)
अणु
	स्थिर अक्षर *begin;
	स्थिर अक्षर *end;
	अक्षर *r;
	पूर्णांक s = 0;

	अगर (allopt == शून्य)
		वापस शून्य;

	क्रम (begin = allopt; *begin != '\0'; begin++) अणु
		अगर (है_चित्र(*begin))
			अवरोध;
	पूर्ण

	अगर (*begin == '\0')
		वापस शून्य;

	क्रम (end = begin; *end != '\0' && है_चित्र(*end); end++)
		s++;

	r = दो_स्मृति_or_die_nocleanup(s + 1);
	म_नकलन(r, begin, s);
	r[s] = '\0';
	*next = begin + s;
	वापस r;
पूर्ण

अटल bool get_trace_opt(स्थिर अक्षर *allopt, स्थिर अक्षर *opt, bool *found)
अणु
	*found = false;
	अक्षर *no_opt;
	अक्षर *str;
	स्थिर अक्षर *next = allopt;
	bool rval = false;

	no_opt = get_no_opt(opt);

	करो अणु
		str = find_next_optstr(next, &next);
		अगर (str == शून्य)
			अवरोध;
		अगर (!म_भेद(str, opt)) अणु
			*found = true;
			rval = true;
			मुक्त(str);
			अवरोध;
		पूर्ण
		अगर (!म_भेद(str, no_opt)) अणु
			*found = true;
			rval = false;
			मुक्त(str);
			अवरोध;
		पूर्ण
		मुक्त(str);
	पूर्ण जबतक (true);
	मुक्त(no_opt);

	वापस rval;
पूर्ण

अटल पूर्णांक set_trace_opt(स्थिर अक्षर *opt, bool value)
अणु
	अक्षर *str;
	पूर्णांक r;

	अगर (value)
		str = strdup(opt);
	अन्यथा
		str = get_no_opt(opt);

	r = tracefs_instance_file_ग_लिखो(शून्य, TR_OPTIONS, str);
	मुक्त(str);
	वापस r;
पूर्ण

व्योम save_trace_opts(काष्ठा ftrace_state *state)
अणु
	अक्षर *allopt;
	पूर्णांक psize;
	पूर्णांक i;

	allopt = tracefs_instance_file_पढ़ो(शून्य, TR_OPTIONS, &psize);
	अगर (!allopt)
		errx(निकास_त्रुटि, "Failed to read the %s file\n", TR_OPTIONS);

	क्रम (i = 0; i < OPTIDX_NR; i++)
		state->opt[i] = get_trace_opt(allopt, optstr[i],
					      &state->opt_valid[i]);

	मुक्त(allopt);
पूर्ण

अटल व्योम ग_लिखो_file(स्थिर अक्षर *file, स्थिर अक्षर *cur, स्थिर अक्षर *new,
		       क्रमागत errhandling h)
अणु
	पूर्णांक r;
	अटल स्थिर अक्षर *emsg = "Failed to write to the %s file!";

	/* Do nothing अगर we now that the current and new value are equal */
	अगर (cur && !needs_change(cur, new))
		वापस;

	r = tracefs_instance_file_ग_लिखो(शून्य, file, new);
	अगर (r < 0) अणु
		अगर (h) अणु
			warnx(emsg, file);
			अगर (h == ERR_CLEANUP)
				cleanup_निकास(निकास_त्रुटि);
		पूर्ण अन्यथा
			errx(निकास_त्रुटि, emsg, file);
	पूर्ण
	अगर (verbose_ftrace()) अणु
		mutex_lock(&prपूर्णांक_mtx);
		म_लिखो("%s was set to %s\n", file, new);
		mutex_unlock(&prपूर्णांक_mtx);
	पूर्ण
पूर्ण

अटल व्योम reset_max_latency(व्योम)
अणु
	ग_लिखो_file(TR_MAXLAT, शून्य, "0", ERR_CLEANUP);
पूर्ण

अटल व्योम save_and_disable_tracer(व्योम)
अणु
	अक्षर *orig_th;
	अक्षर *tracer;
	bool need_nop = false;

	mutex_lock(&save_state.mutex);

	save_trace_opts(&save_state);
	tracer = पढ़ो_file(TR_CURRENT, ERR_EXIT);
	orig_th = पढ़ो_file(TR_THRESH, ERR_EXIT);

	अगर (needs_change(tracer, NOP_TRACER)) अणु
		mutex_lock(&prपूर्णांक_mtx);
		अगर (क्रमce_tracer) अणु
			म_लिखो(
				"The %s tracer is already in use but proceeding anyway!\n",
				tracer);
		पूर्ण अन्यथा अणु
			म_लिखो(
				"The %s tracer is already in use, cowardly bailing out!\n"
				"This could indicate that another program or instance is tracing.\n"
				"Use the -F [--force] option to disregard the current tracer.\n", tracer);
			निकास(0);
		पूर्ण
		mutex_unlock(&prपूर्णांक_mtx);
		need_nop = true;
	पूर्ण

	save_state.tracer =  tracer;
	save_state.thresh = orig_th;

	अगर (need_nop)
		ग_लिखो_file(TR_CURRENT, शून्य, NOP_TRACER, ERR_EXIT);

	mutex_unlock(&save_state.mutex);
पूर्ण

व्योम set_trace_opts(काष्ठा ftrace_state *state, bool *new)
अणु
	पूर्णांक i;
	पूर्णांक r;

	/*
	 * We only set options अगर we earlier detected that the option exists in
	 * the trace_options file and that the wanted setting is dअगरferent from
	 * the one we saw in save_and_disable_tracer()
	 */
	क्रम (i = 0; i < OPTIDX_NR; i++)
		अगर (state->opt_valid[i] &&
		    state->opt[i] != new[i]) अणु
			r = set_trace_opt(optstr[i], new[i]);
			अगर (r < 0) अणु
				warnx("Failed to set the %s option to %s",
				      optstr[i], bool2str(new[i]));
				cleanup_निकास(निकास_त्रुटि);
			पूर्ण
			अगर (verbose_ftrace()) अणु
				mutex_lock(&prपूर्णांक_mtx);
				म_लिखो("%s in %s was set to %s\n", optstr[i],
				       TR_OPTIONS, bool2str(new[i]));
				mutex_unlock(&prपूर्णांक_mtx);
			पूर्ण
		पूर्ण
पूर्ण

अटल व्योम enable_tracer(व्योम)
अणु
	mutex_lock(&save_state.mutex);
	set_trace_opts(&save_state, use_options);

	ग_लिखो_file(TR_THRESH, save_state.thresh, threshold, ERR_CLEANUP);
	ग_लिखो_file(TR_CURRENT, NOP_TRACER, current_tracer, ERR_CLEANUP);

	mutex_unlock(&save_state.mutex);
पूर्ण

अटल व्योम tracing_loop(व्योम)
अणु
	पूर्णांक अगरd = inotअगरy_init();
	पूर्णांक wd;
	स्थिर sमाप_प्रकार bufsize = माप(inotअगरy_buffer);
	स्थिर sमाप_प्रकार iकाष्ठाsize = माप(काष्ठा inotअगरy_event);
	अक्षर *buf = &inotअगरy_buffer[0];
	sमाप_प्रकार nr_पढ़ो;
	अक्षर *p;
	पूर्णांक modअगरied;
	काष्ठा inotअगरy_event *event;
	काष्ठा entry req;
	अक्षर *buffer;
	स्थिर माप_प्रकार bufspace = PRINT_BUFFER_SIZE;
	काष्ठा बारpec बारtamp;

	prपूर्णांक_priority();

	buffer = दो_स्मृति_or_die(bufspace);

	अगर (अगरd < 0)
		err(निकास_त्रुटि, "inotify_init() failed!");


	अगर (setup_ftrace) अणु
		/*
		 * We must disable the tracer beक्रमe resetting the max_latency
		 */
		save_and_disable_tracer();
		/*
		 * We must reset the max_latency beक्रमe the inotअगरy_add_watch()
		 * call.
		 */
		reset_max_latency();
	पूर्ण

	wd = inotअगरy_add_watch(अगरd, debug_maxlat, IN_MODIFY);
	अगर (wd < 0)
		err(निकास_त्रुटि, "inotify_add_watch() failed!");

	अगर (setup_ftrace)
		enable_tracer();

	संकेत_blocking(SIG_UNBLOCK);

	जबतक (true) अणु
		modअगरied = 0;
		check_संकेतs();
		nr_पढ़ो = पढ़ो(अगरd, buf, bufsize);
		check_संकेतs();
		अगर (nr_पढ़ो < 0) अणु
			अगर (त्रुटि_सं == EINTR)
				जारी;
			warn("read() failed on inotify fd!");
			cleanup_निकास(निकास_त्रुटि);
		पूर्ण
		अगर (nr_पढ़ो == bufsize)
			warnx("inotify() buffer filled, skipping events");
		अगर (nr_पढ़ो < iकाष्ठाsize) अणु
			warnx("read() returned too few bytes on inotify fd");
			cleanup_निकास(निकास_त्रुटि);
		पूर्ण

		क्रम (p = buf; p < buf + nr_पढ़ो;) अणु
			event = (काष्ठा inotअगरy_event *) p;
			अगर ((event->mask & IN_MODIFY) != 0)
				modअगरied++;
			p += iकाष्ठाsize + event->len;
		पूर्ण
		जबतक (modअगरied > 0) अणु
			check_संकेतs();
			mutex_lock(&prपूर्णांकstate.mutex);
			check_संकेतs();
			prपूर्णांकstate_next_ticket(&req);
			अगर (prपूर्णांकstate_cnt_पढ़ो() > 0) अणु
				prपूर्णांकstate_mark_req_completed(&req);
				mutex_unlock(&prपूर्णांकstate.mutex);
				अगर (verbose_lostevent()) अणु
					घड़ी_समय_लो_or_die(CLOCK_MONOTONIC,
							     &बारtamp);
					prपूर्णांक_losपंचांगessage(&बारtamp, buffer,
							  bufspace, &req,
							  "inotify loop");
				पूर्ण
				अवरोध;
			पूर्ण
			mutex_unlock(&prपूर्णांकstate.mutex);
			अगर (queue_try_to_add_entry(&prपूर्णांकqueue, &req) != 0) अणु
				/* These prपूर्णांकs could happen concurrently */
				check_संकेतs();
				mutex_lock(&prपूर्णांक_mtx);
				check_संकेतs();
				ग_लिखो_or_die(fd_मानक_निकास, queue_full_warning,
					     माप(queue_full_warning));
				mutex_unlock(&prपूर्णांक_mtx);
			पूर्ण
			modअगरied--;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम *करो_prपूर्णांकloop(व्योम *arg)
अणु
	स्थिर माप_प्रकार bufspace = PRINT_BUFFER_SIZE;
	अक्षर *buffer;
	दीर्घ *rseed = (दीर्घ *) arg;
	काष्ठा dअक्रम48_data dअक्रमbuf;
	दीर्घ slept = 0;
	काष्ठा entry req;
	पूर्णांक prob = 0;
	काष्ठा बारpec बारtamp;
	काष्ठा लघु_msg resize_msg;

	prपूर्णांक_priority();

	अगर (बेक्रम48_r(*rseed, &dअक्रमbuf) != 0) अणु
		warn("srand48_r() failed!\n");
		cleanup_निकास(निकास_त्रुटि);
	पूर्ण

	buffer = दो_स्मृति_or_die(bufspace);

	जबतक (true) अणु
		req = queue_रुको_क्रम_entry(&prपूर्णांकqueue);
		घड़ी_समय_लो_or_die(CLOCK_MONOTONIC, &बारtamp);
		mutex_lock(&prपूर्णांकstate.mutex);
		अगर (prev_req_won_race(&req)) अणु
			prपूर्णांकstate_mark_req_completed(&req);
			mutex_unlock(&prपूर्णांकstate.mutex);
			अगर (verbose_lostevent())
				prपूर्णांक_losपंचांगessage(&बारtamp, buffer, bufspace,
						  &req, "print loop");
			जारी;
		पूर्ण
		mutex_unlock(&prपूर्णांकstate.mutex);

		/*
		 * Toss a coin to decide अगर we want to sleep beक्रमe prपूर्णांकing
		 * out the backtrace. The reason क्रम this is that खोलोing
		 * /sys/kernel/debug/tracing/trace will cause a blackout of
		 * hundreds of ms, where no latencies will be noted by the
		 * latency tracer. Thus by अक्रमomly sleeping we try to aव्योम
		 * missing traces प्रणालीatically due to this. With this option
		 * we will someबार get the first latency, some other बार
		 * some of the later ones, in हाल of बंदly spaced traces.
		 */
		अगर (trace_enable && use_अक्रमom_sleep) अणु
			slept = 0;
			prob = table_get_probability(&req, &resize_msg);
			अगर (!toss_coin(&dअक्रमbuf, prob))
				slept = go_to_sleep(&req);
			अगर (slept >= 0) अणु
				/* A prपूर्णांक is ongoing */
				prपूर्णांकstate_cnt_inc();
				/*
				 * We will करो the prपूर्णांकout below so we have to
				 * mark it as completed जबतक we still have the
				 * mutex.
				 */
				mutex_lock(&prपूर्णांकstate.mutex);
				prपूर्णांकstate_mark_req_completed(&req);
				mutex_unlock(&prपूर्णांकstate.mutex);
			पूर्ण
		पूर्ण
		अगर (trace_enable) अणु
			/*
			 * slept < 0  means that we detected another
			 * notअगरication in go_to_sleep() above
			 */
			अगर (slept >= 0)
				/*
				 * N.B. prपूर्णांकstate_cnt_dec(); will be called
				 * inside prपूर्णांक_tracefile()
				 */
				prपूर्णांक_tracefile(&resize_msg, &बारtamp, buffer,
						bufspace, slept, &req);
			अन्यथा
				prपूर्णांक_skipmessage(&resize_msg, &बारtamp,
						  buffer, bufspace, &req, true);
		पूर्ण अन्यथा अणु
			prपूर्णांक_skipmessage(&resize_msg, &बारtamp, buffer,
					  bufspace, &req, false);
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम start_prपूर्णांकthपढ़ो(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	दीर्घ *seed;
	पूर्णांक ufd;

	ufd = खोलो(DEV_URANDOM, O_RDONLY);
	अगर (nr_thपढ़ोs > MAX_THREADS) अणु
		warnx(
"Number of requested print threads was %d, max number is %d\n",
		      nr_thपढ़ोs, MAX_THREADS);
		nr_thपढ़ोs = MAX_THREADS;
	पूर्ण
	क्रम (i = 0; i < nr_thपढ़ोs; i++) अणु
		seed = दो_स्मृति_or_die(माप(*seed));
		अगर (ufd <  0 ||
		    पढ़ो(ufd, seed, माप(*seed)) != माप(*seed)) अणु
			म_लिखो(
"Warning! Using trivial random number seed, since %s not available\n",
			DEV_URANDOM);
			ख_साफ(मानक_निकास);
			*seed = i;
		पूर्ण
		त्रुटि_सं = pthपढ़ो_create(&prपूर्णांकthपढ़ो[i], शून्य, करो_prपूर्णांकloop,
				       seed);
		अगर (त्रुटि_सं)
			err(निकास_त्रुटि, "pthread_create()");
	पूर्ण
	अगर (ufd > 0 && बंद(ufd) != 0)
		warn("close() failed");
पूर्ण

अटल व्योम show_usage(व्योम)
अणु
	म_लिखो(
"Usage: %s [OPTION]...\n\n"
"Collect closely occurring latencies from %s\n"
"with any of the following tracers: preemptirqsoff, preemptoff, irqsoff, "
"wakeup,\nwakeup_dl, or wakeup_rt.\n\n"

"The occurrence of a latency is detected by monitoring the file\n"
"%s with inotify.\n\n"

"The following options are supported:\n\n"

"-l, --list\t\tList the latency tracers that are supported by the\n"
"\t\t\tcurrently running Linux kernel. If you don't see the\n"
"\t\t\ttracer that you want, you will probably need to\n"
"\t\t\tchange your kernel config and build a new kernel.\n\n"

"-t, --tracer TR\t\tUse the tracer TR. The default is to use the first\n"
"\t\t\ttracer that is supported by the kernel in the following\n"
"\t\t\torder of precedence:\n\n"
"\t\t\tpreemptirqsoff\n"
"\t\t\tpreemptoff\n"
"\t\t\tirqsoff\n"
"\t\t\twakeup\n"
"\t\t\twakeup_rt\n"
"\t\t\twakeup_dl\n"
"\n"
"\t\t\tIf TR is not on the list above, then a warning will be\n"
"\t\t\tprinted.\n\n"

"-F, --force\t\tProceed even if another ftrace tracer is active. Without\n"
"\t\t\tthis option, the program will refuse to start tracing if\n"
"\t\t\tany other tracer than the nop tracer is active.\n\n"

"-s, --threshold TH\tConfigure ftrace to use a threshold of TH microseconds\n"
"\t\t\tfor the tracer. The default is 0, which means that\n"
"\t\t\ttracing_max_latency will be used. tracing_max_latency is\n"
"\t\t\tset to 0 when the program is started and contains the\n"
"\t\t\tmaximum of the latencies that have been encountered.\n\n"

"-f, --function\t\tEnable the function-trace option in trace_options. With\n"
"\t\t\tthis option, ftrace will trace the functions that are\n"
"\t\t\texecuted during a latency, without it we only get the\n"
"\t\t\tbeginning, end, and backtrace.\n\n"

"-g, --graph\t\tEnable the display-graph option in trace_option. This\n"
"\t\t\toption causes ftrace to show the graph of how functions\n"
"\t\t\tare calling other functions.\n\n"

"-c, --policy POL\tRun the program with scheduling policy POL. POL can be\n"
"\t\t\tother, batch, idle, rr or fifo. The default is rr. When\n"
"\t\t\tusing rr or fifo, remember that these policies may cause\n"
"\t\t\tother tasks to experience latencies.\n\n"

"-p, --priority PRI\tRun the program with priority PRI. The acceptable range\n"
"\t\t\tof PRI depends on the scheduling policy.\n\n"

"-n, --notrace\t\tIf latency is detected, do not print out the content of\n"
"\t\t\tthe trace file to standard output\n\n"

"-t, --threads NRTHR\tRun NRTHR threads for printing. Default is %d.\n\n"

"-r, --random\t\tArbitrarily sleep a certain amount of time, default\n"
"\t\t\t%ld ms, before reading the trace file. The\n"
"\t\t\tprobabilities for sleep are chosen so that the\n"
"\t\t\tprobability of obtaining any of a cluster of closely\n"
"\t\t\toccurring latencies are equal, i.e. we will randomly\n"
"\t\t\tchoose which one we collect from the trace file.\n\n"
"\t\t\tThis option is probably only useful with the irqsoff,\n"
"\t\t\tpreemptoff, and preemptirqsoff tracers.\n\n"

"-a, --nrlat NRLAT\tFor the purpose of arbitrary delay, assume that there\n"
"\t\t\tare no more than NRLAT clustered latencies. If NRLAT\n"
"\t\t\tlatencies are detected during a run, this value will\n"
"\t\t\tautomatically be increased to NRLAT + 1 and then to\n"
"\t\t\tNRLAT + 2 and so on. The default is %d. This option\n"
"\t\t\timplies -r. We need to know this number in order to\n"
"\t\t\tbe able to calculate the probabilities of sleeping.\n"
"\t\t\tSpecifically, the probabilities of not sleeping, i.e. to\n"
"\t\t\tdo an immediate printout will be:\n\n"
"\t\t\t1/NRLAT  1/(NRLAT - 1) ... 1/3  1/2  1\n\n"
"\t\t\tThe probability of sleeping will be:\n\n"
"\t\t\t1 - P, where P is from the series above\n\n"
"\t\t\tThis descending probability will cause us to choose\n"
"\t\t\tan occurrence at random. Observe that the final\n"
"\t\t\tprobability is 0, it is when we reach this probability\n"
"\t\t\tthat we increase NRLAT automatically. As an example,\n"
"\t\t\twith the default value of 2, the probabilities will be:\n\n"
"\t\t\t1/2  0\n\n"
"\t\t\tThis means, when a latency is detected we will sleep\n"
"\t\t\twith 50%% probability. If we ever detect another latency\n"
"\t\t\tduring the sleep period, then the probability of sleep\n"
"\t\t\twill be 0%% and the table will be expanded to:\n\n"
"\t\t\t1/3  1/2  0\n\n"

"-v, --verbose\t\tIncrease the verbosity. If this option is given once,\n"
"\t\t\tthen print a message every time that the NRLAT value\n"
"\t\t\tis automatically increased. It also causes a message to\n"
"\t\t\tbe printed when the ftrace settings are changed. If this\n"
"\t\t\toption is given at least twice, then also print a\n"
"\t\t\twarning for lost events.\n\n"

"-u, --time TIME\t\tArbitrarily sleep for a specified time TIME ms before\n"
"\t\t\tprinting out the trace from the trace file. The default\n"
"\t\t\tis %ld ms. This option implies -r.\n\n"

"-x, --no-ftrace\t\tDo not configure ftrace. This assume that the user\n"
"\t\t\tconfigures the ftrace files in sysfs such as\n"
"\t\t\t/sys/kernel/tracing/current_tracer or equivalent.\n\n"

"-i, --tracefile FILE\tUse FILE as trace file. The default is\n"
"\t\t\t%s.\n"
"\t\t\tThis options implies -x\n\n"

"-m, --max-lat FILE\tUse FILE as tracing_max_latency file. The default is\n"
"\t\t\t%s.\n"
"\t\t\tThis options implies -x\n\n"
,
prg_name, debug_tracefile_dflt, debug_maxlat_dflt, DEFAULT_NR_PRINTER_THREADS,
SLEEP_TIME_MS_DEFAULT, DEFAULT_TABLE_SIZE, SLEEP_TIME_MS_DEFAULT,
debug_tracefile_dflt, debug_maxlat_dflt);
पूर्ण

अटल व्योम find_tracefiles(व्योम)
अणु
	debug_tracefile_dflt = tracefs_get_tracing_file("trace");
	अगर (debug_tracefile_dflt == शून्य) अणु
		/* This is needed in show_usage() */
		debug_tracefile_dflt = DEBUG_NOखाता;
	पूर्ण

	debug_maxlat_dflt = tracefs_get_tracing_file("tracing_max_latency");
	अगर (debug_maxlat_dflt == शून्य) अणु
		/* This is needed in show_usage() */
		debug_maxlat_dflt = DEBUG_NOखाता;
	पूर्ण

	debug_tracefile = debug_tracefile_dflt;
	debug_maxlat = debug_maxlat_dflt;
पूर्ण

bool alldigits(स्थिर अक्षर *s)
अणु
	क्रम (; *s != '\0'; s++)
		अगर (!है_अंक(*s))
			वापस false;
	वापस true;
पूर्ण

व्योम check_alldigits(स्थिर अक्षर *optarg, स्थिर अक्षर *argname)
अणु
	अगर (!alldigits(optarg))
		errx(निकास_त्रुटि,
		     "The %s parameter expects a decimal argument\n", argname);
पूर्ण

अटल व्योम scan_arguments(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक c;
	पूर्णांक i;
	पूर्णांक option_idx = 0;

	अटल काष्ठा option दीर्घ_options[] = अणु
		अणु "list",       no_argument,            0, 'l' पूर्ण,
		अणु "tracer",	required_argument,	0, 't' पूर्ण,
		अणु "force",      no_argument,            0, 'F' पूर्ण,
		अणु "threshold",  required_argument,      0, 's' पूर्ण,
		अणु "function",   no_argument,            0, 'f' पूर्ण,
		अणु "graph",      no_argument,            0, 'g' पूर्ण,
		अणु "policy",	required_argument,	0, 'c' पूर्ण,
		अणु "priority",	required_argument,	0, 'p' पूर्ण,
		अणु "help",	no_argument,		0, 'h' पूर्ण,
		अणु "notrace",	no_argument,		0, 'n' पूर्ण,
		अणु "random",	no_argument,		0, 'r' पूर्ण,
		अणु "nrlat",	required_argument,	0, 'a' पूर्ण,
		अणु "threads",	required_argument,	0, 'e' पूर्ण,
		अणु "time",	required_argument,	0, 'u' पूर्ण,
		अणु "verbose",	no_argument,		0, 'v' पूर्ण,
		अणु "no-ftrace",  no_argument,            0, 'x' पूर्ण,
		अणु "tracefile",	required_argument,	0, 'i' पूर्ण,
		अणु "max-lat",	required_argument,	0, 'm' पूर्ण,
		अणु 0,		0,			0,  0  पूर्ण
	पूर्ण;
	स्थिर काष्ठा policy *p;
	पूर्णांक max, min;
	पूर्णांक value;
	bool notracer, valid;

	/*
	 * We must करो this beक्रमe parsing the arguments because show_usage()
	 * needs to display these.
	 */
	find_tracefiles();

	जबतक (true) अणु
		c = getopt_दीर्घ(argc, argv, "lt:Fs:fgc:p:hnra:e:u:vxi:m:",
				दीर्घ_options, &option_idx);
		अगर (c == -1)
			अवरोध;

		चयन (c) अणु
		हाल 'l':
			show_available();
			निकास(0);
			अवरोध;
		हाल 't':
			current_tracer = strdup(optarg);
			अगर (!is_relevant_tracer(current_tracer)) अणु
				warnx("%s is not a known latency tracer!\n",
				      current_tracer);
			पूर्ण
			valid = tracer_valid(current_tracer, &notracer);
			अगर (notracer)
				errx(निकास_त्रुटि, no_tracer_msg);
			अगर (!valid)
				errx(निकास_त्रुटि,
"The tracer %s is not supported by your kernel!\n", current_tracer);
			अवरोध;
		हाल 'F':
			क्रमce_tracer = true;
			अवरोध;
		हाल 's':
			check_alldigits(optarg, "-s [--threshold]");
			threshold = strdup(optarg);
			अवरोध;
		हाल 'f':
			use_options[OPTIDX_FUNC_TR] = true;
			अवरोध;
		हाल 'g':
			use_options[OPTIDX_DISP_GR] = true;
			अवरोध;
		हाल 'c':
			p = policy_from_name(optarg);
			अगर (p != शून्य) अणु
				sched_policy = p->policy;
				sched_policy_set = true;
				अगर (!sched_pri_set) अणु
					sched_pri = p->शेष_pri;
					sched_pri_set = true;
				पूर्ण
			पूर्ण अन्यथा अणु
				warnx("Unknown scheduling %s\n", optarg);
				show_usage();
				निकास(0);
			पूर्ण
			अवरोध;
		हाल 'p':
			check_alldigits(optarg, "-p [--priority]");
			sched_pri = म_से_प(optarg);
			sched_pri_set = true;
			अवरोध;
		हाल 'h':
			show_usage();
			निकास(0);
			अवरोध;
		हाल 'n':
			trace_enable = false;
			use_अक्रमom_sleep = false;
			अवरोध;
		हाल 'e':
			check_alldigits(optarg, "-e [--threads]");
			value = म_से_प(optarg);
			अगर (value > 0)
				nr_thपढ़ोs = value;
			अन्यथा अणु
				warnx("NRTHR must be > 0\n");
				show_usage();
				निकास(0);
			पूर्ण
			अवरोध;
		हाल 'u':
			check_alldigits(optarg, "-u [--time]");
			value = म_से_प(optarg);
			अगर (value < 0) अणु
				warnx("TIME must be >= 0\n");
				show_usage();
				निकास(0);
			पूर्ण
			trace_enable = true;
			use_अक्रमom_sleep = true;
			sleep_समय = value * USEC_PER_MSEC;
			अवरोध;
		हाल 'v':
			verbosity++;
			अवरोध;
		हाल 'r':
			trace_enable = true;
			use_अक्रमom_sleep = true;
			अवरोध;
		हाल 'a':
			check_alldigits(optarg, "-a [--nrlat]");
			value = म_से_प(optarg);
			अगर (value <= 0) अणु
				warnx("NRLAT must be > 0\n");
				show_usage();
				निकास(0);
			पूर्ण
			trace_enable = true;
			use_अक्रमom_sleep = true;
			table_startsize = value;
			अवरोध;
		हाल 'x':
			setup_ftrace = false;
			अवरोध;
		हाल 'i':
			setup_ftrace = false;
			debug_tracefile = strdup(optarg);
			अवरोध;
		हाल 'm':
			setup_ftrace = false;
			debug_maxlat = strdup(optarg);
			अवरोध;
		शेष:
			show_usage();
			निकास(0);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (setup_ftrace) अणु
		अगर (!current_tracer) अणु
			current_tracer = find_शेष_tracer();
			अगर (!current_tracer)
				errx(निकास_त्रुटि,
"No default tracer found and tracer not specified\n");
		पूर्ण

		अगर (use_अक्रमom_sleep && !अक्रमom_makes_sense(current_tracer)) अणु
			warnx("WARNING: The tracer is %s and random sleep has",
			      current_tracer);
			ख_लिखो(मानक_त्रुटि,
"been enabled. Random sleep is intended for the following tracers:\n");
			क्रम (i = 0; अक्रमom_tracers[i]; i++)
				ख_लिखो(मानक_त्रुटि, "%s\n", अक्रमom_tracers[i]);
			ख_लिखो(मानक_त्रुटि, "\n");
		पूर्ण
	पूर्ण

	अगर (debug_tracefile == DEBUG_NOखाता ||
	    debug_maxlat == DEBUG_NOखाता)
		errx(निकास_त्रुटि,
"Could not find tracing directory e.g. /sys/kernel/tracing\n");

	अगर (!sched_policy_set) अणु
		sched_policy = SCHED_RR;
		sched_policy_set = true;
		अगर (!sched_pri_set) अणु
			sched_pri = RT_DEFAULT_PRI;
			sched_pri_set = true;
		पूर्ण
	पूर्ण

	max = sched_get_priority_max(sched_policy);
	min = sched_get_priority_min(sched_policy);

	अगर (sched_pri < min) अणु
		म_लिखो(
"ATTENTION: Increasing priority to minimum, which is %d\n", min);
		sched_pri = min;
	पूर्ण
	अगर (sched_pri > max) अणु
		म_लिखो(
"ATTENTION: Reducing priority to maximum, which is %d\n", max);
		sched_pri = max;
	पूर्ण
पूर्ण

अटल व्योम show_params(व्योम)
अणु
	म_लिखो(
"\n"
"Running with scheduling policy %s and priority %d. Using %d print threads.\n",
		policy_name(sched_policy), sched_pri, nr_thपढ़ोs);
	अगर (trace_enable) अणु
		अगर (use_अक्रमom_sleep) अणु
			म_लिखो(
"%s will be printed with random delay\n"
"Start size of the probability table:\t\t\t%d\n"
"Print a message when the prob. table changes size:\t%s\n"
"Print a warning when an event has been lost:\t\t%s\n"
"Sleep time is:\t\t\t\t\t\t%ld ms\n",
debug_tracefile,
table_startsize,
bool2str(verbose_sizechange()),
bool2str(verbose_lostevent()),
sleep_समय / USEC_PER_MSEC);
		पूर्ण अन्यथा अणु
			म_लिखो("%s will be printed immediately\n",
			       debug_tracefile);
		पूर्ण
	पूर्ण अन्यथा अणु
		म_लिखो("%s will not be printed\n",
		       debug_tracefile);
	पूर्ण
	अगर (setup_ftrace) अणु
		म_लिखो("Tracer:\t\t\t\t\t\t\t%s\n"
		       "%s option:\t\t\t\t\t%s\n"
		       "%s option:\t\t\t\t\t%s\n",
		       current_tracer,
		       optstr[OPTIDX_FUNC_TR],
		       bool2str(use_options[OPTIDX_FUNC_TR]),
		       optstr[OPTIDX_DISP_GR],
		       bool2str(use_options[OPTIDX_DISP_GR]));
		अगर (!म_भेद(threshold, "0"))
			म_लिखो("Threshold:\t\t\t\t\t\ttracing_max_latency\n");
		अन्यथा
			म_लिखो("Threshold:\t\t\t\t\t\t%s\n", threshold);
	पूर्ण
	म_लिखो("\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	init_save_state();
	संकेत_blocking(SIG_BLOCK);
	setup_sig_handler();
	खोलो_मानक_निकास();

	अगर (argc >= 1)
		prg_name = argv[0];
	अन्यथा
		prg_name = prg_unknown;

	scan_arguments(argc, argv);
	show_params();

	init_prपूर्णांकstate();
	init_prपूर्णांक_mtx();
	अगर (use_अक्रमom_sleep) अणु
		init_probabilities();
		अगर (verbose_sizechange())
			म_लिखो("Initializing probability table to %d\n",
			       table_startsize);
		sleeptable_resize(table_startsize, false, शून्य);
	पूर्ण
	set_priority();
	init_queue(&prपूर्णांकqueue);
	start_prपूर्णांकthपढ़ो();
	tracing_loop();
	वापस 0;
पूर्ण
