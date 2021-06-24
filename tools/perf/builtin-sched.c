<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "builtin.h"
#समावेश "perf.h"
#समावेश "perf-sys.h"

#समावेश "util/cpumap.h"
#समावेश "util/evlist.h"
#समावेश "util/evsel.h"
#समावेश "util/evsel_fprintf.h"
#समावेश "util/symbol.h"
#समावेश "util/thread.h"
#समावेश "util/header.h"
#समावेश "util/session.h"
#समावेश "util/tool.h"
#समावेश "util/cloexec.h"
#समावेश "util/thread_map.h"
#समावेश "util/color.h"
#समावेश "util/stat.h"
#समावेश "util/string2.h"
#समावेश "util/callchain.h"
#समावेश "util/time-utils.h"

#समावेश <subcmd/pager.h>
#समावेश <subcmd/parse-options.h>
#समावेश "util/trace-event.h"

#समावेश "util/debug.h"
#समावेश "util/event.h"

#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/zभाग.स>
#समावेश <sys/prctl.h>
#समावेश <sys/resource.h>
#समावेश <पूर्णांकtypes.h>

#समावेश <त्रुटिसं.स>
#समावेश <semaphore.h>
#समावेश <pthपढ़ो.h>
#समावेश <गणित.स>
#समावेश <api/fs/fs.h>
#समावेश <perf/cpumap.h>
#समावेश <linux/समय64.h>
#समावेश <linux/err.h>

#समावेश <linux/प्रकार.स>

#घोषणा PR_SET_NAME		15               /* Set process name */
#घोषणा MAX_CPUS		4096
#घोषणा COMM_LEN		20
#घोषणा SYM_LEN			129
#घोषणा MAX_PID			1024000

अटल स्थिर अक्षर *cpu_list;
अटल DECLARE_BITMAP(cpu_biपंचांगap, MAX_NR_CPUS);

काष्ठा sched_atom;

काष्ठा task_desc अणु
	अचिन्हित दीर्घ		nr;
	अचिन्हित दीर्घ		pid;
	अक्षर			comm[COMM_LEN];

	अचिन्हित दीर्घ		nr_events;
	अचिन्हित दीर्घ		curr_event;
	काष्ठा sched_atom	**atoms;

	pthपढ़ो_t		thपढ़ो;
	sem_t			sleep_sem;

	sem_t			पढ़ोy_क्रम_work;
	sem_t			work_करोne_sem;

	u64			cpu_usage;
पूर्ण;

क्रमागत sched_event_type अणु
	SCHED_EVENT_RUN,
	SCHED_EVENT_SLEEP,
	SCHED_EVENT_WAKEUP,
	SCHED_EVENT_MIGRATION,
पूर्ण;

काष्ठा sched_atom अणु
	क्रमागत sched_event_type	type;
	पूर्णांक			specअगरic_रुको;
	u64			बारtamp;
	u64			duration;
	अचिन्हित दीर्घ		nr;
	sem_t			*रुको_sem;
	काष्ठा task_desc	*wakee;
पूर्ण;

#घोषणा TASK_STATE_TO_CHAR_STR "RSDTtZXxKWP"

/* task state biपंचांगask, copied from include/linux/sched.h */
#घोषणा TASK_RUNNING		0
#घोषणा TASK_INTERRUPTIBLE	1
#घोषणा TASK_UNINTERRUPTIBLE	2
#घोषणा __TASK_STOPPED		4
#घोषणा __TASK_TRACED		8
/* in tsk->निकास_state */
#घोषणा EXIT_DEAD		16
#घोषणा EXIT_ZOMBIE		32
#घोषणा EXIT_TRACE		(EXIT_ZOMBIE | EXIT_DEAD)
/* in tsk->state again */
#घोषणा TASK_DEAD		64
#घोषणा TASK_WAKEKILL		128
#घोषणा TASK_WAKING		256
#घोषणा TASK_PARKED		512

क्रमागत thपढ़ो_state अणु
	THREAD_SLEEPING = 0,
	THREAD_WAIT_CPU,
	THREAD_SCHED_IN,
	THREAD_IGNORE
पूर्ण;

काष्ठा work_atom अणु
	काष्ठा list_head	list;
	क्रमागत thपढ़ो_state	state;
	u64			sched_out_समय;
	u64			wake_up_समय;
	u64			sched_in_समय;
	u64			runसमय;
पूर्ण;

काष्ठा work_atoms अणु
	काष्ठा list_head	work_list;
	काष्ठा thपढ़ो		*thपढ़ो;
	काष्ठा rb_node		node;
	u64			max_lat;
	u64			max_lat_start;
	u64			max_lat_end;
	u64			total_lat;
	u64			nb_atoms;
	u64			total_runसमय;
	पूर्णांक			num_merged;
पूर्ण;

प्रकार पूर्णांक (*sort_fn_t)(काष्ठा work_atoms *, काष्ठा work_atoms *);

काष्ठा perf_sched;

काष्ठा trace_sched_handler अणु
	पूर्णांक (*चयन_event)(काष्ठा perf_sched *sched, काष्ठा evsel *evsel,
			    काष्ठा perf_sample *sample, काष्ठा machine *machine);

	पूर्णांक (*runसमय_event)(काष्ठा perf_sched *sched, काष्ठा evsel *evsel,
			     काष्ठा perf_sample *sample, काष्ठा machine *machine);

	पूर्णांक (*wakeup_event)(काष्ठा perf_sched *sched, काष्ठा evsel *evsel,
			    काष्ठा perf_sample *sample, काष्ठा machine *machine);

	/* PERF_RECORD_FORK event, not sched_process_विभाजन tracepoपूर्णांक */
	पूर्णांक (*विभाजन_event)(काष्ठा perf_sched *sched, जोड़ perf_event *event,
			  काष्ठा machine *machine);

	पूर्णांक (*migrate_task_event)(काष्ठा perf_sched *sched,
				  काष्ठा evsel *evsel,
				  काष्ठा perf_sample *sample,
				  काष्ठा machine *machine);
पूर्ण;

#घोषणा COLOR_PIDS PERF_COLOR_BLUE
#घोषणा COLOR_CPUS PERF_COLOR_BG_RED

काष्ठा perf_sched_map अणु
	DECLARE_BITMAP(comp_cpus_mask, MAX_CPUS);
	पूर्णांक			*comp_cpus;
	bool			 comp;
	काष्ठा perf_thपढ़ो_map *color_pids;
	स्थिर अक्षर		*color_pids_str;
	काष्ठा perf_cpu_map	*color_cpus;
	स्थिर अक्षर		*color_cpus_str;
	काष्ठा perf_cpu_map	*cpus;
	स्थिर अक्षर		*cpus_str;
पूर्ण;

काष्ठा perf_sched अणु
	काष्ठा perf_tool tool;
	स्थिर अक्षर	 *sort_order;
	अचिन्हित दीर्घ	 nr_tasks;
	काष्ठा task_desc **pid_to_task;
	काष्ठा task_desc **tasks;
	स्थिर काष्ठा trace_sched_handler *tp_handler;
	pthपढ़ो_mutex_t	 start_work_mutex;
	pthपढ़ो_mutex_t	 work_करोne_रुको_mutex;
	पूर्णांक		 profile_cpu;
/*
 * Track the current task - that way we can know whether there's any
 * weird events, such as a task being चयनed away that is not current.
 */
	पूर्णांक		 max_cpu;
	u32		 curr_pid[MAX_CPUS];
	काष्ठा thपढ़ो	 *curr_thपढ़ो[MAX_CPUS];
	अक्षर		 next_लघुname1;
	अक्षर		 next_लघुname2;
	अचिन्हित पूर्णांक	 replay_repeat;
	अचिन्हित दीर्घ	 nr_run_events;
	अचिन्हित दीर्घ	 nr_sleep_events;
	अचिन्हित दीर्घ	 nr_wakeup_events;
	अचिन्हित दीर्घ	 nr_sleep_corrections;
	अचिन्हित दीर्घ	 nr_run_events_optimized;
	अचिन्हित दीर्घ	 targetless_wakeups;
	अचिन्हित दीर्घ	 multitarget_wakeups;
	अचिन्हित दीर्घ	 nr_runs;
	अचिन्हित दीर्घ	 nr_बारtamps;
	अचिन्हित दीर्घ	 nr_unordered_बारtamps;
	अचिन्हित दीर्घ	 nr_context_चयन_bugs;
	अचिन्हित दीर्घ	 nr_events;
	अचिन्हित दीर्घ	 nr_lost_chunks;
	अचिन्हित दीर्घ	 nr_lost_events;
	u64		 run_measurement_overhead;
	u64		 sleep_measurement_overhead;
	u64		 start_समय;
	u64		 cpu_usage;
	u64		 runavg_cpu_usage;
	u64		 parent_cpu_usage;
	u64		 runavg_parent_cpu_usage;
	u64		 sum_runसमय;
	u64		 sum_fluct;
	u64		 run_avg;
	u64		 all_runसमय;
	u64		 all_count;
	u64		 cpu_last_चयनed[MAX_CPUS];
	काष्ठा rb_root_cached atom_root, sorted_atom_root, merged_atom_root;
	काष्ठा list_head sort_list, cmp_pid;
	bool क्रमce;
	bool skip_merge;
	काष्ठा perf_sched_map map;

	/* options क्रम समयhist command */
	bool		summary;
	bool		summary_only;
	bool		idle_hist;
	bool		show_callchain;
	अचिन्हित पूर्णांक	max_stack;
	bool		show_cpu_visual;
	bool		show_wakeups;
	bool		show_next;
	bool		show_migrations;
	bool		show_state;
	u64		skipped_samples;
	स्थिर अक्षर	*समय_str;
	काष्ठा perf_समय_पूर्णांकerval pसमय;
	काष्ठा perf_समय_पूर्णांकerval hist_समय;
पूर्ण;

/* per thपढ़ो run समय data */
काष्ठा thपढ़ो_runसमय अणु
	u64 last_समय;      /* समय of previous sched in/out event */
	u64 dt_run;         /* run समय */
	u64 dt_sleep;       /* समय between CPU access by sleep (off cpu) */
	u64 dt_ioरुको;      /* समय between CPU access by ioरुको (off cpu) */
	u64 dt_preempt;     /* समय between CPU access by preempt (off cpu) */
	u64 dt_delay;       /* समय between wakeup and sched-in */
	u64 पढ़ोy_to_run;   /* समय of wakeup */

	काष्ठा stats run_stats;
	u64 total_run_समय;
	u64 total_sleep_समय;
	u64 total_ioरुको_समय;
	u64 total_preempt_समय;
	u64 total_delay_समय;

	पूर्णांक last_state;

	अक्षर लघुname[3];
	bool comm_changed;

	u64 migrations;
पूर्ण;

/* per event run समय data */
काष्ठा evsel_runसमय अणु
	u64 *last_समय; /* समय this event was last seen per cpu */
	u32 ncpu;       /* highest cpu slot allocated */
पूर्ण;

/* per cpu idle समय data */
काष्ठा idle_thपढ़ो_runसमय अणु
	काष्ठा thपढ़ो_runसमय	tr;
	काष्ठा thपढ़ो		*last_thपढ़ो;
	काष्ठा rb_root_cached	sorted_root;
	काष्ठा callchain_root	callchain;
	काष्ठा callchain_cursor	cursor;
पूर्ण;

/* track idle बार per cpu */
अटल काष्ठा thपढ़ो **idle_thपढ़ोs;
अटल पूर्णांक idle_max_cpu;
अटल अक्षर idle_comm[] = "<idle>";

अटल u64 get_nsecs(व्योम)
अणु
	काष्ठा बारpec ts;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &ts);

	वापस ts.tv_sec * NSEC_PER_SEC + ts.tv_nsec;
पूर्ण

अटल व्योम burn_nsecs(काष्ठा perf_sched *sched, u64 nsecs)
अणु
	u64 T0 = get_nsecs(), T1;

	करो अणु
		T1 = get_nsecs();
	पूर्ण जबतक (T1 + sched->run_measurement_overhead < T0 + nsecs);
पूर्ण

अटल व्योम sleep_nsecs(u64 nsecs)
अणु
	काष्ठा बारpec ts;

	ts.tv_nsec = nsecs % 999999999;
	ts.tv_sec = nsecs / 999999999;

	nanosleep(&ts, शून्य);
पूर्ण

अटल व्योम calibrate_run_measurement_overhead(काष्ठा perf_sched *sched)
अणु
	u64 T0, T1, delta, min_delta = NSEC_PER_SEC;
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++) अणु
		T0 = get_nsecs();
		burn_nsecs(sched, 0);
		T1 = get_nsecs();
		delta = T1-T0;
		min_delta = min(min_delta, delta);
	पूर्ण
	sched->run_measurement_overhead = min_delta;

	म_लिखो("run measurement overhead: %" PRIu64 " nsecs\n", min_delta);
पूर्ण

अटल व्योम calibrate_sleep_measurement_overhead(काष्ठा perf_sched *sched)
अणु
	u64 T0, T1, delta, min_delta = NSEC_PER_SEC;
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++) अणु
		T0 = get_nsecs();
		sleep_nsecs(10000);
		T1 = get_nsecs();
		delta = T1-T0;
		min_delta = min(min_delta, delta);
	पूर्ण
	min_delta -= 10000;
	sched->sleep_measurement_overhead = min_delta;

	म_लिखो("sleep measurement overhead: %" PRIu64 " nsecs\n", min_delta);
पूर्ण

अटल काष्ठा sched_atom *
get_new_event(काष्ठा task_desc *task, u64 बारtamp)
अणु
	काष्ठा sched_atom *event = zalloc(माप(*event));
	अचिन्हित दीर्घ idx = task->nr_events;
	माप_प्रकार size;

	event->बारtamp = बारtamp;
	event->nr = idx;

	task->nr_events++;
	size = माप(काष्ठा sched_atom *) * task->nr_events;
	task->atoms = पुनः_स्मृति(task->atoms, size);
	BUG_ON(!task->atoms);

	task->atoms[idx] = event;

	वापस event;
पूर्ण

अटल काष्ठा sched_atom *last_event(काष्ठा task_desc *task)
अणु
	अगर (!task->nr_events)
		वापस शून्य;

	वापस task->atoms[task->nr_events - 1];
पूर्ण

अटल व्योम add_sched_event_run(काष्ठा perf_sched *sched, काष्ठा task_desc *task,
				u64 बारtamp, u64 duration)
अणु
	काष्ठा sched_atom *event, *curr_event = last_event(task);

	/*
	 * optimize an existing RUN event by merging this one
	 * to it:
	 */
	अगर (curr_event && curr_event->type == SCHED_EVENT_RUN) अणु
		sched->nr_run_events_optimized++;
		curr_event->duration += duration;
		वापस;
	पूर्ण

	event = get_new_event(task, बारtamp);

	event->type = SCHED_EVENT_RUN;
	event->duration = duration;

	sched->nr_run_events++;
पूर्ण

अटल व्योम add_sched_event_wakeup(काष्ठा perf_sched *sched, काष्ठा task_desc *task,
				   u64 बारtamp, काष्ठा task_desc *wakee)
अणु
	काष्ठा sched_atom *event, *wakee_event;

	event = get_new_event(task, बारtamp);
	event->type = SCHED_EVENT_WAKEUP;
	event->wakee = wakee;

	wakee_event = last_event(wakee);
	अगर (!wakee_event || wakee_event->type != SCHED_EVENT_SLEEP) अणु
		sched->targetless_wakeups++;
		वापस;
	पूर्ण
	अगर (wakee_event->रुको_sem) अणु
		sched->multitarget_wakeups++;
		वापस;
	पूर्ण

	wakee_event->रुको_sem = zalloc(माप(*wakee_event->रुको_sem));
	sem_init(wakee_event->रुको_sem, 0, 0);
	wakee_event->specअगरic_रुको = 1;
	event->रुको_sem = wakee_event->रुको_sem;

	sched->nr_wakeup_events++;
पूर्ण

अटल व्योम add_sched_event_sleep(काष्ठा perf_sched *sched, काष्ठा task_desc *task,
				  u64 बारtamp, u64 task_state __maybe_unused)
अणु
	काष्ठा sched_atom *event = get_new_event(task, बारtamp);

	event->type = SCHED_EVENT_SLEEP;

	sched->nr_sleep_events++;
पूर्ण

अटल काष्ठा task_desc *रेजिस्टर_pid(काष्ठा perf_sched *sched,
				      अचिन्हित दीर्घ pid, स्थिर अक्षर *comm)
अणु
	काष्ठा task_desc *task;
	अटल पूर्णांक pid_max;

	अगर (sched->pid_to_task == शून्य) अणु
		अगर (sysctl__पढ़ो_पूर्णांक("kernel/pid_max", &pid_max) < 0)
			pid_max = MAX_PID;
		BUG_ON((sched->pid_to_task = सुस्मृति(pid_max, माप(काष्ठा task_desc *))) == शून्य);
	पूर्ण
	अगर (pid >= (अचिन्हित दीर्घ)pid_max) अणु
		BUG_ON((sched->pid_to_task = पुनः_स्मृति(sched->pid_to_task, (pid + 1) *
			माप(काष्ठा task_desc *))) == शून्य);
		जबतक (pid >= (अचिन्हित दीर्घ)pid_max)
			sched->pid_to_task[pid_max++] = शून्य;
	पूर्ण

	task = sched->pid_to_task[pid];

	अगर (task)
		वापस task;

	task = zalloc(माप(*task));
	task->pid = pid;
	task->nr = sched->nr_tasks;
	म_नकल(task->comm, comm);
	/*
	 * every task starts in sleeping state - this माला_लो ignored
	 * अगर there's no wakeup poपूर्णांकing to this sleep state:
	 */
	add_sched_event_sleep(sched, task, 0, 0);

	sched->pid_to_task[pid] = task;
	sched->nr_tasks++;
	sched->tasks = पुनः_स्मृति(sched->tasks, sched->nr_tasks * माप(काष्ठा task_desc *));
	BUG_ON(!sched->tasks);
	sched->tasks[task->nr] = task;

	अगर (verbose > 0)
		म_लिखो("registered task #%ld, PID %ld (%s)\n", sched->nr_tasks, pid, comm);

	वापस task;
पूर्ण


अटल व्योम prपूर्णांक_task_traces(काष्ठा perf_sched *sched)
अणु
	काष्ठा task_desc *task;
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < sched->nr_tasks; i++) अणु
		task = sched->tasks[i];
		म_लिखो("task %6ld (%20s:%10ld), nr_events: %ld\n",
			task->nr, task->comm, task->pid, task->nr_events);
	पूर्ण
पूर्ण

अटल व्योम add_cross_task_wakeups(काष्ठा perf_sched *sched)
अणु
	काष्ठा task_desc *task1, *task2;
	अचिन्हित दीर्घ i, j;

	क्रम (i = 0; i < sched->nr_tasks; i++) अणु
		task1 = sched->tasks[i];
		j = i + 1;
		अगर (j == sched->nr_tasks)
			j = 0;
		task2 = sched->tasks[j];
		add_sched_event_wakeup(sched, task1, 0, task2);
	पूर्ण
पूर्ण

अटल व्योम perf_sched__process_event(काष्ठा perf_sched *sched,
				      काष्ठा sched_atom *atom)
अणु
	पूर्णांक ret = 0;

	चयन (atom->type) अणु
		हाल SCHED_EVENT_RUN:
			burn_nsecs(sched, atom->duration);
			अवरोध;
		हाल SCHED_EVENT_SLEEP:
			अगर (atom->रुको_sem)
				ret = sem_रुको(atom->रुको_sem);
			BUG_ON(ret);
			अवरोध;
		हाल SCHED_EVENT_WAKEUP:
			अगर (atom->रुको_sem)
				ret = sem_post(atom->रुको_sem);
			BUG_ON(ret);
			अवरोध;
		हाल SCHED_EVENT_MIGRATION:
			अवरोध;
		शेष:
			BUG_ON(1);
	पूर्ण
पूर्ण

अटल u64 get_cpu_usage_nsec_parent(व्योम)
अणु
	काष्ठा rusage ru;
	u64 sum;
	पूर्णांक err;

	err = getrusage(RUSAGE_SELF, &ru);
	BUG_ON(err);

	sum =  ru.ru_uसमय.tv_sec * NSEC_PER_SEC + ru.ru_uसमय.tv_usec * NSEC_PER_USEC;
	sum += ru.ru_sसमय.tv_sec * NSEC_PER_SEC + ru.ru_sसमय.tv_usec * NSEC_PER_USEC;

	वापस sum;
पूर्ण

अटल पूर्णांक self_खोलो_counters(काष्ठा perf_sched *sched, अचिन्हित दीर्घ cur_task)
अणु
	काष्ठा perf_event_attr attr;
	अक्षर sbuf[STRERR_बफ_मानE], info[STRERR_बफ_मानE];
	पूर्णांक fd;
	काष्ठा rlimit limit;
	bool need_privilege = false;

	स_रखो(&attr, 0, माप(attr));

	attr.type = PERF_TYPE_SOFTWARE;
	attr.config = PERF_COUNT_SW_TASK_CLOCK;

क्रमce_again:
	fd = sys_perf_event_खोलो(&attr, 0, -1, -1,
				 perf_event_खोलो_cloexec_flag());

	अगर (fd < 0) अणु
		अगर (त्रुटि_सं == EMखाता) अणु
			अगर (sched->क्रमce) अणु
				BUG_ON(getrlimit(RLIMIT_NOखाता, &limit) == -1);
				limit.rlim_cur += sched->nr_tasks - cur_task;
				अगर (limit.rlim_cur > limit.rlim_max) अणु
					limit.rlim_max = limit.rlim_cur;
					need_privilege = true;
				पूर्ण
				अगर (setrlimit(RLIMIT_NOखाता, &limit) == -1) अणु
					अगर (need_privilege && त्रुटि_सं == EPERM)
						म_नकल(info, "Need privilege\n");
				पूर्ण अन्यथा
					जाओ क्रमce_again;
			पूर्ण अन्यथा
				म_नकल(info, "Have a try with -f option\n");
		पूर्ण
		pr_err("Error: sys_perf_event_open() syscall returned "
		       "with %d (%s)\n%s", fd,
		       str_error_r(त्रुटि_सं, sbuf, माप(sbuf)), info);
		निकास(निकास_त्रुटि);
	पूर्ण
	वापस fd;
पूर्ण

अटल u64 get_cpu_usage_nsec_self(पूर्णांक fd)
अणु
	u64 runसमय;
	पूर्णांक ret;

	ret = पढ़ो(fd, &runसमय, माप(runसमय));
	BUG_ON(ret != माप(runसमय));

	वापस runसमय;
पूर्ण

काष्ठा sched_thपढ़ो_parms अणु
	काष्ठा task_desc  *task;
	काष्ठा perf_sched *sched;
	पूर्णांक fd;
पूर्ण;

अटल व्योम *thपढ़ो_func(व्योम *ctx)
अणु
	काष्ठा sched_thपढ़ो_parms *parms = ctx;
	काष्ठा task_desc *this_task = parms->task;
	काष्ठा perf_sched *sched = parms->sched;
	u64 cpu_usage_0, cpu_usage_1;
	अचिन्हित दीर्घ i, ret;
	अक्षर comm2[22];
	पूर्णांक fd = parms->fd;

	zमुक्त(&parms);

	प्र_लिखो(comm2, ":%s", this_task->comm);
	prctl(PR_SET_NAME, comm2);
	अगर (fd < 0)
		वापस शून्य;
again:
	ret = sem_post(&this_task->पढ़ोy_क्रम_work);
	BUG_ON(ret);
	ret = pthपढ़ो_mutex_lock(&sched->start_work_mutex);
	BUG_ON(ret);
	ret = pthपढ़ो_mutex_unlock(&sched->start_work_mutex);
	BUG_ON(ret);

	cpu_usage_0 = get_cpu_usage_nsec_self(fd);

	क्रम (i = 0; i < this_task->nr_events; i++) अणु
		this_task->curr_event = i;
		perf_sched__process_event(sched, this_task->atoms[i]);
	पूर्ण

	cpu_usage_1 = get_cpu_usage_nsec_self(fd);
	this_task->cpu_usage = cpu_usage_1 - cpu_usage_0;
	ret = sem_post(&this_task->work_करोne_sem);
	BUG_ON(ret);

	ret = pthपढ़ो_mutex_lock(&sched->work_करोne_रुको_mutex);
	BUG_ON(ret);
	ret = pthपढ़ो_mutex_unlock(&sched->work_करोne_रुको_mutex);
	BUG_ON(ret);

	जाओ again;
पूर्ण

अटल व्योम create_tasks(काष्ठा perf_sched *sched)
अणु
	काष्ठा task_desc *task;
	pthपढ़ो_attr_t attr;
	अचिन्हित दीर्घ i;
	पूर्णांक err;

	err = pthपढ़ो_attr_init(&attr);
	BUG_ON(err);
	err = pthपढ़ो_attr_setstacksize(&attr,
			(माप_प्रकार) max(16 * 1024, PTHREAD_STACK_MIN));
	BUG_ON(err);
	err = pthपढ़ो_mutex_lock(&sched->start_work_mutex);
	BUG_ON(err);
	err = pthपढ़ो_mutex_lock(&sched->work_करोne_रुको_mutex);
	BUG_ON(err);
	क्रम (i = 0; i < sched->nr_tasks; i++) अणु
		काष्ठा sched_thपढ़ो_parms *parms = दो_स्मृति(माप(*parms));
		BUG_ON(parms == शून्य);
		parms->task = task = sched->tasks[i];
		parms->sched = sched;
		parms->fd = self_खोलो_counters(sched, i);
		sem_init(&task->sleep_sem, 0, 0);
		sem_init(&task->पढ़ोy_क्रम_work, 0, 0);
		sem_init(&task->work_करोne_sem, 0, 0);
		task->curr_event = 0;
		err = pthपढ़ो_create(&task->thपढ़ो, &attr, thपढ़ो_func, parms);
		BUG_ON(err);
	पूर्ण
पूर्ण

अटल व्योम रुको_क्रम_tasks(काष्ठा perf_sched *sched)
अणु
	u64 cpu_usage_0, cpu_usage_1;
	काष्ठा task_desc *task;
	अचिन्हित दीर्घ i, ret;

	sched->start_समय = get_nsecs();
	sched->cpu_usage = 0;
	pthपढ़ो_mutex_unlock(&sched->work_करोne_रुको_mutex);

	क्रम (i = 0; i < sched->nr_tasks; i++) अणु
		task = sched->tasks[i];
		ret = sem_रुको(&task->पढ़ोy_क्रम_work);
		BUG_ON(ret);
		sem_init(&task->पढ़ोy_क्रम_work, 0, 0);
	पूर्ण
	ret = pthपढ़ो_mutex_lock(&sched->work_करोne_रुको_mutex);
	BUG_ON(ret);

	cpu_usage_0 = get_cpu_usage_nsec_parent();

	pthपढ़ो_mutex_unlock(&sched->start_work_mutex);

	क्रम (i = 0; i < sched->nr_tasks; i++) अणु
		task = sched->tasks[i];
		ret = sem_रुको(&task->work_करोne_sem);
		BUG_ON(ret);
		sem_init(&task->work_करोne_sem, 0, 0);
		sched->cpu_usage += task->cpu_usage;
		task->cpu_usage = 0;
	पूर्ण

	cpu_usage_1 = get_cpu_usage_nsec_parent();
	अगर (!sched->runavg_cpu_usage)
		sched->runavg_cpu_usage = sched->cpu_usage;
	sched->runavg_cpu_usage = (sched->runavg_cpu_usage * (sched->replay_repeat - 1) + sched->cpu_usage) / sched->replay_repeat;

	sched->parent_cpu_usage = cpu_usage_1 - cpu_usage_0;
	अगर (!sched->runavg_parent_cpu_usage)
		sched->runavg_parent_cpu_usage = sched->parent_cpu_usage;
	sched->runavg_parent_cpu_usage = (sched->runavg_parent_cpu_usage * (sched->replay_repeat - 1) +
					 sched->parent_cpu_usage)/sched->replay_repeat;

	ret = pthपढ़ो_mutex_lock(&sched->start_work_mutex);
	BUG_ON(ret);

	क्रम (i = 0; i < sched->nr_tasks; i++) अणु
		task = sched->tasks[i];
		sem_init(&task->sleep_sem, 0, 0);
		task->curr_event = 0;
	पूर्ण
पूर्ण

अटल व्योम run_one_test(काष्ठा perf_sched *sched)
अणु
	u64 T0, T1, delta, avg_delta, fluct;

	T0 = get_nsecs();
	रुको_क्रम_tasks(sched);
	T1 = get_nsecs();

	delta = T1 - T0;
	sched->sum_runसमय += delta;
	sched->nr_runs++;

	avg_delta = sched->sum_runसमय / sched->nr_runs;
	अगर (delta < avg_delta)
		fluct = avg_delta - delta;
	अन्यथा
		fluct = delta - avg_delta;
	sched->sum_fluct += fluct;
	अगर (!sched->run_avg)
		sched->run_avg = delta;
	sched->run_avg = (sched->run_avg * (sched->replay_repeat - 1) + delta) / sched->replay_repeat;

	म_लिखो("#%-3ld: %0.3f, ", sched->nr_runs, (द्विगुन)delta / NSEC_PER_MSEC);

	म_लिखो("ravg: %0.2f, ", (द्विगुन)sched->run_avg / NSEC_PER_MSEC);

	म_लिखो("cpu: %0.2f / %0.2f",
		(द्विगुन)sched->cpu_usage / NSEC_PER_MSEC, (द्विगुन)sched->runavg_cpu_usage / NSEC_PER_MSEC);

#अगर 0
	/*
	 * rusage statistics करोne by the parent, these are less
	 * accurate than the sched->sum_exec_runसमय based statistics:
	 */
	म_लिखो(" [%0.2f / %0.2f]",
		(द्विगुन)sched->parent_cpu_usage / NSEC_PER_MSEC,
		(द्विगुन)sched->runavg_parent_cpu_usage / NSEC_PER_MSEC);
#पूर्ण_अगर

	म_लिखो("\n");

	अगर (sched->nr_sleep_corrections)
		म_लिखो(" (%ld sleep corrections)\n", sched->nr_sleep_corrections);
	sched->nr_sleep_corrections = 0;
पूर्ण

अटल व्योम test_calibrations(काष्ठा perf_sched *sched)
अणु
	u64 T0, T1;

	T0 = get_nsecs();
	burn_nsecs(sched, NSEC_PER_MSEC);
	T1 = get_nsecs();

	म_लिखो("the run test took %" PRIu64 " nsecs\n", T1 - T0);

	T0 = get_nsecs();
	sleep_nsecs(NSEC_PER_MSEC);
	T1 = get_nsecs();

	म_लिखो("the sleep test took %" PRIu64 " nsecs\n", T1 - T0);
पूर्ण

अटल पूर्णांक
replay_wakeup_event(काष्ठा perf_sched *sched,
		    काष्ठा evsel *evsel, काष्ठा perf_sample *sample,
		    काष्ठा machine *machine __maybe_unused)
अणु
	स्थिर अक्षर *comm = evsel__strval(evsel, sample, "comm");
	स्थिर u32 pid	 = evsel__पूर्णांकval(evsel, sample, "pid");
	काष्ठा task_desc *waker, *wakee;

	अगर (verbose > 0) अणु
		म_लिखो("sched_wakeup event %p\n", evsel);

		म_लिखो(" ... pid %d woke up %s/%d\n", sample->tid, comm, pid);
	पूर्ण

	waker = रेजिस्टर_pid(sched, sample->tid, "<unknown>");
	wakee = रेजिस्टर_pid(sched, pid, comm);

	add_sched_event_wakeup(sched, waker, sample->समय, wakee);
	वापस 0;
पूर्ण

अटल पूर्णांक replay_चयन_event(काष्ठा perf_sched *sched,
			       काष्ठा evsel *evsel,
			       काष्ठा perf_sample *sample,
			       काष्ठा machine *machine __maybe_unused)
अणु
	स्थिर अक्षर *prev_comm  = evsel__strval(evsel, sample, "prev_comm"),
		   *next_comm  = evsel__strval(evsel, sample, "next_comm");
	स्थिर u32 prev_pid = evsel__पूर्णांकval(evsel, sample, "prev_pid"),
		  next_pid = evsel__पूर्णांकval(evsel, sample, "next_pid");
	स्थिर u64 prev_state = evsel__पूर्णांकval(evsel, sample, "prev_state");
	काष्ठा task_desc *prev, __maybe_unused *next;
	u64 बारtamp0, बारtamp = sample->समय;
	पूर्णांक cpu = sample->cpu;
	s64 delta;

	अगर (verbose > 0)
		म_लिखो("sched_switch event %p\n", evsel);

	अगर (cpu >= MAX_CPUS || cpu < 0)
		वापस 0;

	बारtamp0 = sched->cpu_last_चयनed[cpu];
	अगर (बारtamp0)
		delta = बारtamp - बारtamp0;
	अन्यथा
		delta = 0;

	अगर (delta < 0) अणु
		pr_err("hm, delta: %" PRIu64 " < 0 ?\n", delta);
		वापस -1;
	पूर्ण

	pr_debug(" ... switch from %s/%d to %s/%d [ran %" PRIu64 " nsecs]\n",
		 prev_comm, prev_pid, next_comm, next_pid, delta);

	prev = रेजिस्टर_pid(sched, prev_pid, prev_comm);
	next = रेजिस्टर_pid(sched, next_pid, next_comm);

	sched->cpu_last_चयनed[cpu] = बारtamp;

	add_sched_event_run(sched, prev, बारtamp, delta);
	add_sched_event_sleep(sched, prev, बारtamp, prev_state);

	वापस 0;
पूर्ण

अटल पूर्णांक replay_विभाजन_event(काष्ठा perf_sched *sched,
			     जोड़ perf_event *event,
			     काष्ठा machine *machine)
अणु
	काष्ठा thपढ़ो *child, *parent;

	child = machine__findnew_thपढ़ो(machine, event->विभाजन.pid,
					event->विभाजन.tid);
	parent = machine__findnew_thपढ़ो(machine, event->विभाजन.ppid,
					 event->विभाजन.ptid);

	अगर (child == शून्य || parent == शून्य) अणु
		pr_debug("thread does not exist on fork event: child %p, parent %p\n",
				 child, parent);
		जाओ out_put;
	पूर्ण

	अगर (verbose > 0) अणु
		म_लिखो("fork event\n");
		म_लिखो("... parent: %s/%d\n", thपढ़ो__comm_str(parent), parent->tid);
		म_लिखो("...  child: %s/%d\n", thपढ़ो__comm_str(child), child->tid);
	पूर्ण

	रेजिस्टर_pid(sched, parent->tid, thपढ़ो__comm_str(parent));
	रेजिस्टर_pid(sched, child->tid, thपढ़ो__comm_str(child));
out_put:
	thपढ़ो__put(child);
	thपढ़ो__put(parent);
	वापस 0;
पूर्ण

काष्ठा sort_dimension अणु
	स्थिर अक्षर		*name;
	sort_fn_t		cmp;
	काष्ठा list_head	list;
पूर्ण;

/*
 * handle runसमय stats saved per thपढ़ो
 */
अटल काष्ठा thपढ़ो_runसमय *thपढ़ो__init_runसमय(काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा thपढ़ो_runसमय *r;

	r = zalloc(माप(काष्ठा thपढ़ो_runसमय));
	अगर (!r)
		वापस शून्य;

	init_stats(&r->run_stats);
	thपढ़ो__set_priv(thपढ़ो, r);

	वापस r;
पूर्ण

अटल काष्ठा thपढ़ो_runसमय *thपढ़ो__get_runसमय(काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा thपढ़ो_runसमय *tr;

	tr = thपढ़ो__priv(thपढ़ो);
	अगर (tr == शून्य) अणु
		tr = thपढ़ो__init_runसमय(thपढ़ो);
		अगर (tr == शून्य)
			pr_debug("Failed to malloc memory for runtime data.\n");
	पूर्ण

	वापस tr;
पूर्ण

अटल पूर्णांक
thपढ़ो_lat_cmp(काष्ठा list_head *list, काष्ठा work_atoms *l, काष्ठा work_atoms *r)
अणु
	काष्ठा sort_dimension *sort;
	पूर्णांक ret = 0;

	BUG_ON(list_empty(list));

	list_क्रम_each_entry(sort, list, list) अणु
		ret = sort->cmp(l, r);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा work_atoms *
thपढ़ो_atoms_search(काष्ठा rb_root_cached *root, काष्ठा thपढ़ो *thपढ़ो,
			 काष्ठा list_head *sort_list)
अणु
	काष्ठा rb_node *node = root->rb_root.rb_node;
	काष्ठा work_atoms key = अणु .thपढ़ो = thपढ़ो पूर्ण;

	जबतक (node) अणु
		काष्ठा work_atoms *atoms;
		पूर्णांक cmp;

		atoms = container_of(node, काष्ठा work_atoms, node);

		cmp = thपढ़ो_lat_cmp(sort_list, &key, atoms);
		अगर (cmp > 0)
			node = node->rb_left;
		अन्यथा अगर (cmp < 0)
			node = node->rb_right;
		अन्यथा अणु
			BUG_ON(thपढ़ो != atoms->thपढ़ो);
			वापस atoms;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम
__thपढ़ो_latency_insert(काष्ठा rb_root_cached *root, काष्ठा work_atoms *data,
			 काष्ठा list_head *sort_list)
अणु
	काष्ठा rb_node **new = &(root->rb_root.rb_node), *parent = शून्य;
	bool lefपंचांगost = true;

	जबतक (*new) अणु
		काष्ठा work_atoms *this;
		पूर्णांक cmp;

		this = container_of(*new, काष्ठा work_atoms, node);
		parent = *new;

		cmp = thपढ़ो_lat_cmp(sort_list, data, this);

		अगर (cmp > 0)
			new = &((*new)->rb_left);
		अन्यथा अणु
			new = &((*new)->rb_right);
			lefपंचांगost = false;
		पूर्ण
	पूर्ण

	rb_link_node(&data->node, parent, new);
	rb_insert_color_cached(&data->node, root, lefपंचांगost);
पूर्ण

अटल पूर्णांक thपढ़ो_atoms_insert(काष्ठा perf_sched *sched, काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा work_atoms *atoms = zalloc(माप(*atoms));
	अगर (!atoms) अणु
		pr_err("No memory at %s\n", __func__);
		वापस -1;
	पूर्ण

	atoms->thपढ़ो = thपढ़ो__get(thपढ़ो);
	INIT_LIST_HEAD(&atoms->work_list);
	__thपढ़ो_latency_insert(&sched->atom_root, atoms, &sched->cmp_pid);
	वापस 0;
पूर्ण

अटल अक्षर sched_out_state(u64 prev_state)
अणु
	स्थिर अक्षर *str = TASK_STATE_TO_CHAR_STR;

	वापस str[prev_state];
पूर्ण

अटल पूर्णांक
add_sched_out_event(काष्ठा work_atoms *atoms,
		    अक्षर run_state,
		    u64 बारtamp)
अणु
	काष्ठा work_atom *atom = zalloc(माप(*atom));
	अगर (!atom) अणु
		pr_err("Non memory at %s", __func__);
		वापस -1;
	पूर्ण

	atom->sched_out_समय = बारtamp;

	अगर (run_state == 'R') अणु
		atom->state = THREAD_WAIT_CPU;
		atom->wake_up_समय = atom->sched_out_समय;
	पूर्ण

	list_add_tail(&atom->list, &atoms->work_list);
	वापस 0;
पूर्ण

अटल व्योम
add_runसमय_event(काष्ठा work_atoms *atoms, u64 delta,
		  u64 बारtamp __maybe_unused)
अणु
	काष्ठा work_atom *atom;

	BUG_ON(list_empty(&atoms->work_list));

	atom = list_entry(atoms->work_list.prev, काष्ठा work_atom, list);

	atom->runसमय += delta;
	atoms->total_runसमय += delta;
पूर्ण

अटल व्योम
add_sched_in_event(काष्ठा work_atoms *atoms, u64 बारtamp)
अणु
	काष्ठा work_atom *atom;
	u64 delta;

	अगर (list_empty(&atoms->work_list))
		वापस;

	atom = list_entry(atoms->work_list.prev, काष्ठा work_atom, list);

	अगर (atom->state != THREAD_WAIT_CPU)
		वापस;

	अगर (बारtamp < atom->wake_up_समय) अणु
		atom->state = THREAD_IGNORE;
		वापस;
	पूर्ण

	atom->state = THREAD_SCHED_IN;
	atom->sched_in_समय = बारtamp;

	delta = atom->sched_in_समय - atom->wake_up_समय;
	atoms->total_lat += delta;
	अगर (delta > atoms->max_lat) अणु
		atoms->max_lat = delta;
		atoms->max_lat_start = atom->wake_up_समय;
		atoms->max_lat_end = बारtamp;
	पूर्ण
	atoms->nb_atoms++;
पूर्ण

अटल पूर्णांक latency_चयन_event(काष्ठा perf_sched *sched,
				काष्ठा evsel *evsel,
				काष्ठा perf_sample *sample,
				काष्ठा machine *machine)
अणु
	स्थिर u32 prev_pid = evsel__पूर्णांकval(evsel, sample, "prev_pid"),
		  next_pid = evsel__पूर्णांकval(evsel, sample, "next_pid");
	स्थिर u64 prev_state = evsel__पूर्णांकval(evsel, sample, "prev_state");
	काष्ठा work_atoms *out_events, *in_events;
	काष्ठा thपढ़ो *sched_out, *sched_in;
	u64 बारtamp0, बारtamp = sample->समय;
	पूर्णांक cpu = sample->cpu, err = -1;
	s64 delta;

	BUG_ON(cpu >= MAX_CPUS || cpu < 0);

	बारtamp0 = sched->cpu_last_चयनed[cpu];
	sched->cpu_last_चयनed[cpu] = बारtamp;
	अगर (बारtamp0)
		delta = बारtamp - बारtamp0;
	अन्यथा
		delta = 0;

	अगर (delta < 0) अणु
		pr_err("hm, delta: %" PRIu64 " < 0 ?\n", delta);
		वापस -1;
	पूर्ण

	sched_out = machine__findnew_thपढ़ो(machine, -1, prev_pid);
	sched_in = machine__findnew_thपढ़ो(machine, -1, next_pid);
	अगर (sched_out == शून्य || sched_in == शून्य)
		जाओ out_put;

	out_events = thपढ़ो_atoms_search(&sched->atom_root, sched_out, &sched->cmp_pid);
	अगर (!out_events) अणु
		अगर (thपढ़ो_atoms_insert(sched, sched_out))
			जाओ out_put;
		out_events = thपढ़ो_atoms_search(&sched->atom_root, sched_out, &sched->cmp_pid);
		अगर (!out_events) अणु
			pr_err("out-event: Internal tree error");
			जाओ out_put;
		पूर्ण
	पूर्ण
	अगर (add_sched_out_event(out_events, sched_out_state(prev_state), बारtamp))
		वापस -1;

	in_events = thपढ़ो_atoms_search(&sched->atom_root, sched_in, &sched->cmp_pid);
	अगर (!in_events) अणु
		अगर (thपढ़ो_atoms_insert(sched, sched_in))
			जाओ out_put;
		in_events = thपढ़ो_atoms_search(&sched->atom_root, sched_in, &sched->cmp_pid);
		अगर (!in_events) अणु
			pr_err("in-event: Internal tree error");
			जाओ out_put;
		पूर्ण
		/*
		 * Take came in we have not heard about yet,
		 * add in an initial atom in runnable state:
		 */
		अगर (add_sched_out_event(in_events, 'R', बारtamp))
			जाओ out_put;
	पूर्ण
	add_sched_in_event(in_events, बारtamp);
	err = 0;
out_put:
	thपढ़ो__put(sched_out);
	thपढ़ो__put(sched_in);
	वापस err;
पूर्ण

अटल पूर्णांक latency_runसमय_event(काष्ठा perf_sched *sched,
				 काष्ठा evsel *evsel,
				 काष्ठा perf_sample *sample,
				 काष्ठा machine *machine)
अणु
	स्थिर u32 pid	   = evsel__पूर्णांकval(evsel, sample, "pid");
	स्थिर u64 runसमय  = evsel__पूर्णांकval(evsel, sample, "runtime");
	काष्ठा thपढ़ो *thपढ़ो = machine__findnew_thपढ़ो(machine, -1, pid);
	काष्ठा work_atoms *atoms = thपढ़ो_atoms_search(&sched->atom_root, thपढ़ो, &sched->cmp_pid);
	u64 बारtamp = sample->समय;
	पूर्णांक cpu = sample->cpu, err = -1;

	अगर (thपढ़ो == शून्य)
		वापस -1;

	BUG_ON(cpu >= MAX_CPUS || cpu < 0);
	अगर (!atoms) अणु
		अगर (thपढ़ो_atoms_insert(sched, thपढ़ो))
			जाओ out_put;
		atoms = thपढ़ो_atoms_search(&sched->atom_root, thपढ़ो, &sched->cmp_pid);
		अगर (!atoms) अणु
			pr_err("in-event: Internal tree error");
			जाओ out_put;
		पूर्ण
		अगर (add_sched_out_event(atoms, 'R', बारtamp))
			जाओ out_put;
	पूर्ण

	add_runसमय_event(atoms, runसमय, बारtamp);
	err = 0;
out_put:
	thपढ़ो__put(thपढ़ो);
	वापस err;
पूर्ण

अटल पूर्णांक latency_wakeup_event(काष्ठा perf_sched *sched,
				काष्ठा evsel *evsel,
				काष्ठा perf_sample *sample,
				काष्ठा machine *machine)
अणु
	स्थिर u32 pid	  = evsel__पूर्णांकval(evsel, sample, "pid");
	काष्ठा work_atoms *atoms;
	काष्ठा work_atom *atom;
	काष्ठा thपढ़ो *wakee;
	u64 बारtamp = sample->समय;
	पूर्णांक err = -1;

	wakee = machine__findnew_thपढ़ो(machine, -1, pid);
	अगर (wakee == शून्य)
		वापस -1;
	atoms = thपढ़ो_atoms_search(&sched->atom_root, wakee, &sched->cmp_pid);
	अगर (!atoms) अणु
		अगर (thपढ़ो_atoms_insert(sched, wakee))
			जाओ out_put;
		atoms = thपढ़ो_atoms_search(&sched->atom_root, wakee, &sched->cmp_pid);
		अगर (!atoms) अणु
			pr_err("wakeup-event: Internal tree error");
			जाओ out_put;
		पूर्ण
		अगर (add_sched_out_event(atoms, 'S', बारtamp))
			जाओ out_put;
	पूर्ण

	BUG_ON(list_empty(&atoms->work_list));

	atom = list_entry(atoms->work_list.prev, काष्ठा work_atom, list);

	/*
	 * As we करो not guarantee the wakeup event happens when
	 * task is out of run queue, also may happen when task is
	 * on run queue and wakeup only change ->state to TASK_RUNNING,
	 * then we should not set the ->wake_up_समय when wake up a
	 * task which is on run queue.
	 *
	 * You WILL be missing events अगर you've recorded only
	 * one CPU, or are only looking at only one, so करोn't
	 * skip in this हाल.
	 */
	अगर (sched->profile_cpu == -1 && atom->state != THREAD_SLEEPING)
		जाओ out_ok;

	sched->nr_बारtamps++;
	अगर (atom->sched_out_समय > बारtamp) अणु
		sched->nr_unordered_बारtamps++;
		जाओ out_ok;
	पूर्ण

	atom->state = THREAD_WAIT_CPU;
	atom->wake_up_समय = बारtamp;
out_ok:
	err = 0;
out_put:
	thपढ़ो__put(wakee);
	वापस err;
पूर्ण

अटल पूर्णांक latency_migrate_task_event(काष्ठा perf_sched *sched,
				      काष्ठा evsel *evsel,
				      काष्ठा perf_sample *sample,
				      काष्ठा machine *machine)
अणु
	स्थिर u32 pid = evsel__पूर्णांकval(evsel, sample, "pid");
	u64 बारtamp = sample->समय;
	काष्ठा work_atoms *atoms;
	काष्ठा work_atom *atom;
	काष्ठा thपढ़ो *migrant;
	पूर्णांक err = -1;

	/*
	 * Only need to worry about migration when profiling one CPU.
	 */
	अगर (sched->profile_cpu == -1)
		वापस 0;

	migrant = machine__findnew_thपढ़ो(machine, -1, pid);
	अगर (migrant == शून्य)
		वापस -1;
	atoms = thपढ़ो_atoms_search(&sched->atom_root, migrant, &sched->cmp_pid);
	अगर (!atoms) अणु
		अगर (thपढ़ो_atoms_insert(sched, migrant))
			जाओ out_put;
		रेजिस्टर_pid(sched, migrant->tid, thपढ़ो__comm_str(migrant));
		atoms = thपढ़ो_atoms_search(&sched->atom_root, migrant, &sched->cmp_pid);
		अगर (!atoms) अणु
			pr_err("migration-event: Internal tree error");
			जाओ out_put;
		पूर्ण
		अगर (add_sched_out_event(atoms, 'R', बारtamp))
			जाओ out_put;
	पूर्ण

	BUG_ON(list_empty(&atoms->work_list));

	atom = list_entry(atoms->work_list.prev, काष्ठा work_atom, list);
	atom->sched_in_समय = atom->sched_out_समय = atom->wake_up_समय = बारtamp;

	sched->nr_बारtamps++;

	अगर (atom->sched_out_समय > बारtamp)
		sched->nr_unordered_बारtamps++;
	err = 0;
out_put:
	thपढ़ो__put(migrant);
	वापस err;
पूर्ण

अटल व्योम output_lat_thपढ़ो(काष्ठा perf_sched *sched, काष्ठा work_atoms *work_list)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	u64 avg;
	अक्षर max_lat_start[32], max_lat_end[32];

	अगर (!work_list->nb_atoms)
		वापस;
	/*
	 * Ignore idle thपढ़ोs:
	 */
	अगर (!म_भेद(thपढ़ो__comm_str(work_list->thपढ़ो), "swapper"))
		वापस;

	sched->all_runसमय += work_list->total_runसमय;
	sched->all_count   += work_list->nb_atoms;

	अगर (work_list->num_merged > 1)
		ret = म_लिखो("  %s:(%d) ", thपढ़ो__comm_str(work_list->thपढ़ो), work_list->num_merged);
	अन्यथा
		ret = म_लिखो("  %s:%d ", thपढ़ो__comm_str(work_list->thपढ़ो), work_list->thपढ़ो->tid);

	क्रम (i = 0; i < 24 - ret; i++)
		म_लिखो(" ");

	avg = work_list->total_lat / work_list->nb_atoms;
	बारtamp__scnम_लिखो_usec(work_list->max_lat_start, max_lat_start, माप(max_lat_start));
	बारtamp__scnम_लिखो_usec(work_list->max_lat_end, max_lat_end, माप(max_lat_end));

	म_लिखो("|%11.3f ms |%9" PRIu64 " | avg:%8.3f ms | max:%8.3f ms | max start: %12s s | max end: %12s s\n",
	      (द्विगुन)work_list->total_runसमय / NSEC_PER_MSEC,
		 work_list->nb_atoms, (द्विगुन)avg / NSEC_PER_MSEC,
		 (द्विगुन)work_list->max_lat / NSEC_PER_MSEC,
		 max_lat_start, max_lat_end);
पूर्ण

अटल पूर्णांक pid_cmp(काष्ठा work_atoms *l, काष्ठा work_atoms *r)
अणु
	अगर (l->thपढ़ो == r->thपढ़ो)
		वापस 0;
	अगर (l->thपढ़ो->tid < r->thपढ़ो->tid)
		वापस -1;
	अगर (l->thपढ़ो->tid > r->thपढ़ो->tid)
		वापस 1;
	वापस (पूर्णांक)(l->thपढ़ो - r->thपढ़ो);
पूर्ण

अटल पूर्णांक avg_cmp(काष्ठा work_atoms *l, काष्ठा work_atoms *r)
अणु
	u64 avgl, avgr;

	अगर (!l->nb_atoms)
		वापस -1;

	अगर (!r->nb_atoms)
		वापस 1;

	avgl = l->total_lat / l->nb_atoms;
	avgr = r->total_lat / r->nb_atoms;

	अगर (avgl < avgr)
		वापस -1;
	अगर (avgl > avgr)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक max_cmp(काष्ठा work_atoms *l, काष्ठा work_atoms *r)
अणु
	अगर (l->max_lat < r->max_lat)
		वापस -1;
	अगर (l->max_lat > r->max_lat)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक चयन_cmp(काष्ठा work_atoms *l, काष्ठा work_atoms *r)
अणु
	अगर (l->nb_atoms < r->nb_atoms)
		वापस -1;
	अगर (l->nb_atoms > r->nb_atoms)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक runसमय_cmp(काष्ठा work_atoms *l, काष्ठा work_atoms *r)
अणु
	अगर (l->total_runसमय < r->total_runसमय)
		वापस -1;
	अगर (l->total_runसमय > r->total_runसमय)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक sort_dimension__add(स्थिर अक्षर *tok, काष्ठा list_head *list)
अणु
	माप_प्रकार i;
	अटल काष्ठा sort_dimension avg_sort_dimension = अणु
		.name = "avg",
		.cmp  = avg_cmp,
	पूर्ण;
	अटल काष्ठा sort_dimension max_sort_dimension = अणु
		.name = "max",
		.cmp  = max_cmp,
	पूर्ण;
	अटल काष्ठा sort_dimension pid_sort_dimension = अणु
		.name = "pid",
		.cmp  = pid_cmp,
	पूर्ण;
	अटल काष्ठा sort_dimension runसमय_sort_dimension = अणु
		.name = "runtime",
		.cmp  = runसमय_cmp,
	पूर्ण;
	अटल काष्ठा sort_dimension चयन_sort_dimension = अणु
		.name = "switch",
		.cmp  = चयन_cmp,
	पूर्ण;
	काष्ठा sort_dimension *available_sorts[] = अणु
		&pid_sort_dimension,
		&avg_sort_dimension,
		&max_sort_dimension,
		&चयन_sort_dimension,
		&runसमय_sort_dimension,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(available_sorts); i++) अणु
		अगर (!म_भेद(available_sorts[i]->name, tok)) अणु
			list_add_tail(&available_sorts[i]->list, list);

			वापस 0;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम perf_sched__sort_lat(काष्ठा perf_sched *sched)
अणु
	काष्ठा rb_node *node;
	काष्ठा rb_root_cached *root = &sched->atom_root;
again:
	क्रम (;;) अणु
		काष्ठा work_atoms *data;
		node = rb_first_cached(root);
		अगर (!node)
			अवरोध;

		rb_erase_cached(node, root);
		data = rb_entry(node, काष्ठा work_atoms, node);
		__thपढ़ो_latency_insert(&sched->sorted_atom_root, data, &sched->sort_list);
	पूर्ण
	अगर (root == &sched->atom_root) अणु
		root = &sched->merged_atom_root;
		जाओ again;
	पूर्ण
पूर्ण

अटल पूर्णांक process_sched_wakeup_event(काष्ठा perf_tool *tool,
				      काष्ठा evsel *evsel,
				      काष्ठा perf_sample *sample,
				      काष्ठा machine *machine)
अणु
	काष्ठा perf_sched *sched = container_of(tool, काष्ठा perf_sched, tool);

	अगर (sched->tp_handler->wakeup_event)
		वापस sched->tp_handler->wakeup_event(sched, evsel, sample, machine);

	वापस 0;
पूर्ण

जोड़ map_priv अणु
	व्योम	*ptr;
	bool	 color;
पूर्ण;

अटल bool thपढ़ो__has_color(काष्ठा thपढ़ो *thपढ़ो)
अणु
	जोड़ map_priv priv = अणु
		.ptr = thपढ़ो__priv(thपढ़ो),
	पूर्ण;

	वापस priv.color;
पूर्ण

अटल काष्ठा thपढ़ो*
map__findnew_thपढ़ो(काष्ठा perf_sched *sched, काष्ठा machine *machine, pid_t pid, pid_t tid)
अणु
	काष्ठा thपढ़ो *thपढ़ो = machine__findnew_thपढ़ो(machine, pid, tid);
	जोड़ map_priv priv = अणु
		.color = false,
	पूर्ण;

	अगर (!sched->map.color_pids || !thपढ़ो || thपढ़ो__priv(thपढ़ो))
		वापस thपढ़ो;

	अगर (thपढ़ो_map__has(sched->map.color_pids, tid))
		priv.color = true;

	thपढ़ो__set_priv(thपढ़ो, priv.ptr);
	वापस thपढ़ो;
पूर्ण

अटल पूर्णांक map_चयन_event(काष्ठा perf_sched *sched, काष्ठा evsel *evsel,
			    काष्ठा perf_sample *sample, काष्ठा machine *machine)
अणु
	स्थिर u32 next_pid = evsel__पूर्णांकval(evsel, sample, "next_pid");
	काष्ठा thपढ़ो *sched_in;
	काष्ठा thपढ़ो_runसमय *tr;
	पूर्णांक new_लघुname;
	u64 बारtamp0, बारtamp = sample->समय;
	s64 delta;
	पूर्णांक i, this_cpu = sample->cpu;
	पूर्णांक cpus_nr;
	bool new_cpu = false;
	स्थिर अक्षर *color = PERF_COLOR_NORMAL;
	अक्षर sबारtamp[32];

	BUG_ON(this_cpu >= MAX_CPUS || this_cpu < 0);

	अगर (this_cpu > sched->max_cpu)
		sched->max_cpu = this_cpu;

	अगर (sched->map.comp) अणु
		cpus_nr = biपंचांगap_weight(sched->map.comp_cpus_mask, MAX_CPUS);
		अगर (!test_and_set_bit(this_cpu, sched->map.comp_cpus_mask)) अणु
			sched->map.comp_cpus[cpus_nr++] = this_cpu;
			new_cpu = true;
		पूर्ण
	पूर्ण अन्यथा
		cpus_nr = sched->max_cpu;

	बारtamp0 = sched->cpu_last_चयनed[this_cpu];
	sched->cpu_last_चयनed[this_cpu] = बारtamp;
	अगर (बारtamp0)
		delta = बारtamp - बारtamp0;
	अन्यथा
		delta = 0;

	अगर (delta < 0) अणु
		pr_err("hm, delta: %" PRIu64 " < 0 ?\n", delta);
		वापस -1;
	पूर्ण

	sched_in = map__findnew_thपढ़ो(sched, machine, -1, next_pid);
	अगर (sched_in == शून्य)
		वापस -1;

	tr = thपढ़ो__get_runसमय(sched_in);
	अगर (tr == शून्य) अणु
		thपढ़ो__put(sched_in);
		वापस -1;
	पूर्ण

	sched->curr_thपढ़ो[this_cpu] = thपढ़ो__get(sched_in);

	म_लिखो("  ");

	new_लघुname = 0;
	अगर (!tr->लघुname[0]) अणु
		अगर (!म_भेद(thपढ़ो__comm_str(sched_in), "swapper")) अणु
			/*
			 * Don't allocate a letter-number क्रम swapper:0
			 * as a लघुname. Instead, we use '.' क्रम it.
			 */
			tr->लघुname[0] = '.';
			tr->लघुname[1] = ' ';
		पूर्ण अन्यथा अणु
			tr->लघुname[0] = sched->next_लघुname1;
			tr->लघुname[1] = sched->next_लघुname2;

			अगर (sched->next_लघुname1 < 'Z') अणु
				sched->next_लघुname1++;
			पूर्ण अन्यथा अणु
				sched->next_लघुname1 = 'A';
				अगर (sched->next_लघुname2 < '9')
					sched->next_लघुname2++;
				अन्यथा
					sched->next_लघुname2 = '0';
			पूर्ण
		पूर्ण
		new_लघुname = 1;
	पूर्ण

	क्रम (i = 0; i < cpus_nr; i++) अणु
		पूर्णांक cpu = sched->map.comp ? sched->map.comp_cpus[i] : i;
		काष्ठा thपढ़ो *curr_thपढ़ो = sched->curr_thपढ़ो[cpu];
		काष्ठा thपढ़ो_runसमय *curr_tr;
		स्थिर अक्षर *pid_color = color;
		स्थिर अक्षर *cpu_color = color;

		अगर (curr_thपढ़ो && thपढ़ो__has_color(curr_thपढ़ो))
			pid_color = COLOR_PIDS;

		अगर (sched->map.cpus && !cpu_map__has(sched->map.cpus, cpu))
			जारी;

		अगर (sched->map.color_cpus && cpu_map__has(sched->map.color_cpus, cpu))
			cpu_color = COLOR_CPUS;

		अगर (cpu != this_cpu)
			color_ख_लिखो(मानक_निकास, color, " ");
		अन्यथा
			color_ख_लिखो(मानक_निकास, cpu_color, "*");

		अगर (sched->curr_thपढ़ो[cpu]) अणु
			curr_tr = thपढ़ो__get_runसमय(sched->curr_thपढ़ो[cpu]);
			अगर (curr_tr == शून्य) अणु
				thपढ़ो__put(sched_in);
				वापस -1;
			पूर्ण
			color_ख_लिखो(मानक_निकास, pid_color, "%2s ", curr_tr->लघुname);
		पूर्ण अन्यथा
			color_ख_लिखो(मानक_निकास, color, "   ");
	पूर्ण

	अगर (sched->map.cpus && !cpu_map__has(sched->map.cpus, this_cpu))
		जाओ out;

	बारtamp__scnम_लिखो_usec(बारtamp, sबारtamp, माप(sबारtamp));
	color_ख_लिखो(मानक_निकास, color, "  %12s secs ", sबारtamp);
	अगर (new_लघुname || tr->comm_changed || (verbose > 0 && sched_in->tid)) अणु
		स्थिर अक्षर *pid_color = color;

		अगर (thपढ़ो__has_color(sched_in))
			pid_color = COLOR_PIDS;

		color_ख_लिखो(मानक_निकास, pid_color, "%s => %s:%d",
		       tr->लघुname, thपढ़ो__comm_str(sched_in), sched_in->tid);
		tr->comm_changed = false;
	पूर्ण

	अगर (sched->map.comp && new_cpu)
		color_ख_लिखो(मानक_निकास, color, " (CPU %d)", this_cpu);

out:
	color_ख_लिखो(मानक_निकास, color, "\n");

	thपढ़ो__put(sched_in);

	वापस 0;
पूर्ण

अटल पूर्णांक process_sched_चयन_event(काष्ठा perf_tool *tool,
				      काष्ठा evsel *evsel,
				      काष्ठा perf_sample *sample,
				      काष्ठा machine *machine)
अणु
	काष्ठा perf_sched *sched = container_of(tool, काष्ठा perf_sched, tool);
	पूर्णांक this_cpu = sample->cpu, err = 0;
	u32 prev_pid = evsel__पूर्णांकval(evsel, sample, "prev_pid"),
	    next_pid = evsel__पूर्णांकval(evsel, sample, "next_pid");

	अगर (sched->curr_pid[this_cpu] != (u32)-1) अणु
		/*
		 * Are we trying to चयन away a PID that is
		 * not current?
		 */
		अगर (sched->curr_pid[this_cpu] != prev_pid)
			sched->nr_context_चयन_bugs++;
	पूर्ण

	अगर (sched->tp_handler->चयन_event)
		err = sched->tp_handler->चयन_event(sched, evsel, sample, machine);

	sched->curr_pid[this_cpu] = next_pid;
	वापस err;
पूर्ण

अटल पूर्णांक process_sched_runसमय_event(काष्ठा perf_tool *tool,
				       काष्ठा evsel *evsel,
				       काष्ठा perf_sample *sample,
				       काष्ठा machine *machine)
अणु
	काष्ठा perf_sched *sched = container_of(tool, काष्ठा perf_sched, tool);

	अगर (sched->tp_handler->runसमय_event)
		वापस sched->tp_handler->runसमय_event(sched, evsel, sample, machine);

	वापस 0;
पूर्ण

अटल पूर्णांक perf_sched__process_विभाजन_event(काष्ठा perf_tool *tool,
					  जोड़ perf_event *event,
					  काष्ठा perf_sample *sample,
					  काष्ठा machine *machine)
अणु
	काष्ठा perf_sched *sched = container_of(tool, काष्ठा perf_sched, tool);

	/* run the विभाजन event through the perf machinery */
	perf_event__process_विभाजन(tool, event, sample, machine);

	/* and then run additional processing needed क्रम this command */
	अगर (sched->tp_handler->विभाजन_event)
		वापस sched->tp_handler->विभाजन_event(sched, event, machine);

	वापस 0;
पूर्ण

अटल पूर्णांक process_sched_migrate_task_event(काष्ठा perf_tool *tool,
					    काष्ठा evsel *evsel,
					    काष्ठा perf_sample *sample,
					    काष्ठा machine *machine)
अणु
	काष्ठा perf_sched *sched = container_of(tool, काष्ठा perf_sched, tool);

	अगर (sched->tp_handler->migrate_task_event)
		वापस sched->tp_handler->migrate_task_event(sched, evsel, sample, machine);

	वापस 0;
पूर्ण

प्रकार पूर्णांक (*tracepoपूर्णांक_handler)(काष्ठा perf_tool *tool,
				  काष्ठा evsel *evsel,
				  काष्ठा perf_sample *sample,
				  काष्ठा machine *machine);

अटल पूर्णांक perf_sched__process_tracepoपूर्णांक_sample(काष्ठा perf_tool *tool __maybe_unused,
						 जोड़ perf_event *event __maybe_unused,
						 काष्ठा perf_sample *sample,
						 काष्ठा evsel *evsel,
						 काष्ठा machine *machine)
अणु
	पूर्णांक err = 0;

	अगर (evsel->handler != शून्य) अणु
		tracepoपूर्णांक_handler f = evsel->handler;
		err = f(tool, evsel, sample, machine);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक perf_sched__process_comm(काष्ठा perf_tool *tool __maybe_unused,
				    जोड़ perf_event *event,
				    काष्ठा perf_sample *sample,
				    काष्ठा machine *machine)
अणु
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा thपढ़ो_runसमय *tr;
	पूर्णांक err;

	err = perf_event__process_comm(tool, event, sample, machine);
	अगर (err)
		वापस err;

	thपढ़ो = machine__find_thपढ़ो(machine, sample->pid, sample->tid);
	अगर (!thपढ़ो) अणु
		pr_err("Internal error: can't find thread\n");
		वापस -1;
	पूर्ण

	tr = thपढ़ो__get_runसमय(thपढ़ो);
	अगर (tr == शून्य) अणु
		thपढ़ो__put(thपढ़ो);
		वापस -1;
	पूर्ण

	tr->comm_changed = true;
	thपढ़ो__put(thपढ़ो);

	वापस 0;
पूर्ण

अटल पूर्णांक perf_sched__पढ़ो_events(काष्ठा perf_sched *sched)
अणु
	स्थिर काष्ठा evsel_str_handler handlers[] = अणु
		अणु "sched:sched_switch",	      process_sched_चयन_event, पूर्ण,
		अणु "sched:sched_stat_runtime", process_sched_runसमय_event, पूर्ण,
		अणु "sched:sched_wakeup",	      process_sched_wakeup_event, पूर्ण,
		अणु "sched:sched_wakeup_new",   process_sched_wakeup_event, पूर्ण,
		अणु "sched:sched_migrate_task", process_sched_migrate_task_event, पूर्ण,
	पूर्ण;
	काष्ठा perf_session *session;
	काष्ठा perf_data data = अणु
		.path  = input_name,
		.mode  = PERF_DATA_MODE_READ,
		.क्रमce = sched->क्रमce,
	पूर्ण;
	पूर्णांक rc = -1;

	session = perf_session__new(&data, false, &sched->tool);
	अगर (IS_ERR(session)) अणु
		pr_debug("Error creating perf session");
		वापस PTR_ERR(session);
	पूर्ण

	symbol__init(&session->header.env);

	अगर (perf_session__set_tracepoपूर्णांकs_handlers(session, handlers))
		जाओ out_delete;

	अगर (perf_session__has_traces(session, "record -R")) अणु
		पूर्णांक err = perf_session__process_events(session);
		अगर (err) अणु
			pr_err("Failed to process events, error %d", err);
			जाओ out_delete;
		पूर्ण

		sched->nr_events      = session->evlist->stats.nr_events[0];
		sched->nr_lost_events = session->evlist->stats.total_lost;
		sched->nr_lost_chunks = session->evlist->stats.nr_events[PERF_RECORD_LOST];
	पूर्ण

	rc = 0;
out_delete:
	perf_session__delete(session);
	वापस rc;
पूर्ण

/*
 * scheduling बार are prपूर्णांकed as msec.usec
 */
अटल अंतरभूत व्योम prपूर्णांक_sched_समय(अचिन्हित दीर्घ दीर्घ nsecs, पूर्णांक width)
अणु
	अचिन्हित दीर्घ msecs;
	अचिन्हित दीर्घ usecs;

	msecs  = nsecs / NSEC_PER_MSEC;
	nsecs -= msecs * NSEC_PER_MSEC;
	usecs  = nsecs / NSEC_PER_USEC;
	म_लिखो("%*lu.%03lu ", width, msecs, usecs);
पूर्ण

/*
 * वापसs runसमय data क्रम event, allocating memory क्रम it the
 * first समय it is used.
 */
अटल काष्ठा evsel_runसमय *evsel__get_runसमय(काष्ठा evsel *evsel)
अणु
	काष्ठा evsel_runसमय *r = evsel->priv;

	अगर (r == शून्य) अणु
		r = zalloc(माप(काष्ठा evsel_runसमय));
		evsel->priv = r;
	पूर्ण

	वापस r;
पूर्ण

/*
 * save last समय event was seen per cpu
 */
अटल व्योम evsel__save_समय(काष्ठा evsel *evsel, u64 बारtamp, u32 cpu)
अणु
	काष्ठा evsel_runसमय *r = evsel__get_runसमय(evsel);

	अगर (r == शून्य)
		वापस;

	अगर ((cpu >= r->ncpu) || (r->last_समय == शून्य)) अणु
		पूर्णांक i, n = __roundup_घात_of_two(cpu+1);
		व्योम *p = r->last_समय;

		p = पुनः_स्मृति(r->last_समय, n * माप(u64));
		अगर (!p)
			वापस;

		r->last_समय = p;
		क्रम (i = r->ncpu; i < n; ++i)
			r->last_समय[i] = (u64) 0;

		r->ncpu = n;
	पूर्ण

	r->last_समय[cpu] = बारtamp;
पूर्ण

/* वापसs last समय this event was seen on the given cpu */
अटल u64 evsel__get_समय(काष्ठा evsel *evsel, u32 cpu)
अणु
	काष्ठा evsel_runसमय *r = evsel__get_runसमय(evsel);

	अगर ((r == शून्य) || (r->last_समय == शून्य) || (cpu >= r->ncpu))
		वापस 0;

	वापस r->last_समय[cpu];
पूर्ण

अटल पूर्णांक comm_width = 30;

अटल अक्षर *समयhist_get_commstr(काष्ठा thपढ़ो *thपढ़ो)
अणु
	अटल अक्षर str[32];
	स्थिर अक्षर *comm = thपढ़ो__comm_str(thपढ़ो);
	pid_t tid = thपढ़ो->tid;
	pid_t pid = thपढ़ो->pid_;
	पूर्णांक n;

	अगर (pid == 0)
		n = scnम_लिखो(str, माप(str), "%s", comm);

	अन्यथा अगर (tid != pid)
		n = scnम_लिखो(str, माप(str), "%s[%d/%d]", comm, tid, pid);

	अन्यथा
		n = scnम_लिखो(str, माप(str), "%s[%d]", comm, tid);

	अगर (n > comm_width)
		comm_width = n;

	वापस str;
पूर्ण

अटल व्योम समयhist_header(काष्ठा perf_sched *sched)
अणु
	u32 ncpus = sched->max_cpu + 1;
	u32 i, j;

	म_लिखो("%15s %6s ", "time", "cpu");

	अगर (sched->show_cpu_visual) अणु
		म_लिखो(" ");
		क्रम (i = 0, j = 0; i < ncpus; ++i) अणु
			म_लिखो("%x", j++);
			अगर (j > 15)
				j = 0;
		पूर्ण
		म_लिखो(" ");
	पूर्ण

	म_लिखो(" %-*s  %9s  %9s  %9s", comm_width,
		"task name", "wait time", "sch delay", "run time");

	अगर (sched->show_state)
		म_लिखो("  %s", "state");

	म_लिखो("\n");

	/*
	 * units row
	 */
	म_लिखो("%15s %-6s ", "", "");

	अगर (sched->show_cpu_visual)
		म_लिखो(" %*s ", ncpus, "");

	म_लिखो(" %-*s  %9s  %9s  %9s", comm_width,
	       "[tid/pid]", "(msec)", "(msec)", "(msec)");

	अगर (sched->show_state)
		म_लिखो("  %5s", "");

	म_लिखो("\n");

	/*
	 * separator
	 */
	म_लिखो("%.15s %.6s ", graph_करोtted_line, graph_करोtted_line);

	अगर (sched->show_cpu_visual)
		म_लिखो(" %.*s ", ncpus, graph_करोtted_line);

	म_लिखो(" %.*s  %.9s  %.9s  %.9s", comm_width,
		graph_करोtted_line, graph_करोtted_line, graph_करोtted_line,
		graph_करोtted_line);

	अगर (sched->show_state)
		म_लिखो("  %.5s", graph_करोtted_line);

	म_लिखो("\n");
पूर्ण

अटल अक्षर task_state_अक्षर(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक state)
अणु
	अटल स्थिर अक्षर state_to_अक्षर[] = TASK_STATE_TO_CHAR_STR;
	अचिन्हित bit = state ? ffs(state) : 0;

	/* 'I' क्रम idle */
	अगर (thपढ़ो->tid == 0)
		वापस 'I';

	वापस bit < माप(state_to_अक्षर) - 1 ? state_to_अक्षर[bit] : '?';
पूर्ण

अटल व्योम समयhist_prपूर्णांक_sample(काष्ठा perf_sched *sched,
				  काष्ठा evsel *evsel,
				  काष्ठा perf_sample *sample,
				  काष्ठा addr_location *al,
				  काष्ठा thपढ़ो *thपढ़ो,
				  u64 t, पूर्णांक state)
अणु
	काष्ठा thपढ़ो_runसमय *tr = thपढ़ो__priv(thपढ़ो);
	स्थिर अक्षर *next_comm = evsel__strval(evsel, sample, "next_comm");
	स्थिर u32 next_pid = evsel__पूर्णांकval(evsel, sample, "next_pid");
	u32 max_cpus = sched->max_cpu + 1;
	अक्षर tstr[64];
	अक्षर nstr[30];
	u64 रुको_समय;

	अगर (cpu_list && !test_bit(sample->cpu, cpu_biपंचांगap))
		वापस;

	बारtamp__scnम_लिखो_usec(t, tstr, माप(tstr));
	म_लिखो("%15s [%04d] ", tstr, sample->cpu);

	अगर (sched->show_cpu_visual) अणु
		u32 i;
		अक्षर c;

		म_लिखो(" ");
		क्रम (i = 0; i < max_cpus; ++i) अणु
			/* flag idle बार with 'i'; others are sched events */
			अगर (i == sample->cpu)
				c = (thपढ़ो->tid == 0) ? 'i' : 's';
			अन्यथा
				c = ' ';
			म_लिखो("%c", c);
		पूर्ण
		म_लिखो(" ");
	पूर्ण

	म_लिखो(" %-*s ", comm_width, समयhist_get_commstr(thपढ़ो));

	रुको_समय = tr->dt_sleep + tr->dt_ioरुको + tr->dt_preempt;
	prपूर्णांक_sched_समय(रुको_समय, 6);

	prपूर्णांक_sched_समय(tr->dt_delay, 6);
	prपूर्णांक_sched_समय(tr->dt_run, 6);

	अगर (sched->show_state)
		म_लिखो(" %5c ", task_state_अक्षर(thपढ़ो, state));

	अगर (sched->show_next) अणु
		snम_लिखो(nstr, माप(nstr), "next: %s[%d]", next_comm, next_pid);
		म_लिखो(" %-*s", comm_width, nstr);
	पूर्ण

	अगर (sched->show_wakeups && !sched->show_next)
		म_लिखो("  %-*s", comm_width, "");

	अगर (thपढ़ो->tid == 0)
		जाओ out;

	अगर (sched->show_callchain)
		म_लिखो("  ");

	sample__ख_लिखो_sym(sample, al, 0,
			    EVSEL__PRINT_SYM | EVSEL__PRINT_ONELINE |
			    EVSEL__PRINT_CALLCHAIN_ARROW |
			    EVSEL__PRINT_SKIP_IGNORED,
			    &callchain_cursor, symbol_conf.bt_stop_list,  मानक_निकास);

out:
	म_लिखो("\n");
पूर्ण

/*
 * Explanation of delta-समय stats:
 *
 *            t = समय of current schedule out event
 *        tprev = समय of previous sched out event
 *                also समय of schedule-in event क्रम current task
 *    last_समय = समय of last sched change event क्रम current task
 *                (i.e, समय process was last scheduled out)
 * पढ़ोy_to_run = समय of wakeup क्रम current task
 *
 * -----|------------|------------|------------|------
 *    last         पढ़ोy        tprev          t
 *    समय         to run
 *
 *      |-------- dt_रुको --------|
 *                   |- dt_delay -|-- dt_run --|
 *
 *   dt_run = run समय of current task
 *  dt_रुको = समय between last schedule out event क्रम task and tprev
 *            represents समय spent off the cpu
 * dt_delay = समय between wakeup and schedule-in of task
 */

अटल व्योम समयhist_update_runसमय_stats(काष्ठा thपढ़ो_runसमय *r,
					 u64 t, u64 tprev)
अणु
	r->dt_delay   = 0;
	r->dt_sleep   = 0;
	r->dt_ioरुको  = 0;
	r->dt_preempt = 0;
	r->dt_run     = 0;

	अगर (tprev) अणु
		r->dt_run = t - tprev;
		अगर (r->पढ़ोy_to_run) अणु
			अगर (r->पढ़ोy_to_run > tprev)
				pr_debug("time travel: wakeup time for task > previous sched_switch event\n");
			अन्यथा
				r->dt_delay = tprev - r->पढ़ोy_to_run;
		पूर्ण

		अगर (r->last_समय > tprev)
			pr_debug("time travel: last sched out time for task > previous sched_switch event\n");
		अन्यथा अगर (r->last_समय) अणु
			u64 dt_रुको = tprev - r->last_समय;

			अगर (r->last_state == TASK_RUNNING)
				r->dt_preempt = dt_रुको;
			अन्यथा अगर (r->last_state == TASK_UNINTERRUPTIBLE)
				r->dt_ioरुको = dt_रुको;
			अन्यथा
				r->dt_sleep = dt_रुको;
		पूर्ण
	पूर्ण

	update_stats(&r->run_stats, r->dt_run);

	r->total_run_समय     += r->dt_run;
	r->total_delay_समय   += r->dt_delay;
	r->total_sleep_समय   += r->dt_sleep;
	r->total_ioरुको_समय  += r->dt_ioरुको;
	r->total_preempt_समय += r->dt_preempt;
पूर्ण

अटल bool is_idle_sample(काष्ठा perf_sample *sample,
			   काष्ठा evsel *evsel)
अणु
	/* pid 0 == swapper == idle task */
	अगर (म_भेद(evsel__name(evsel), "sched:sched_switch") == 0)
		वापस evsel__पूर्णांकval(evsel, sample, "prev_pid") == 0;

	वापस sample->pid == 0;
पूर्ण

अटल व्योम save_task_callchain(काष्ठा perf_sched *sched,
				काष्ठा perf_sample *sample,
				काष्ठा evsel *evsel,
				काष्ठा machine *machine)
अणु
	काष्ठा callchain_cursor *cursor = &callchain_cursor;
	काष्ठा thपढ़ो *thपढ़ो;

	/* want मुख्य thपढ़ो क्रम process - has maps */
	thपढ़ो = machine__findnew_thपढ़ो(machine, sample->pid, sample->pid);
	अगर (thपढ़ो == शून्य) अणु
		pr_debug("Failed to get thread for pid %d.\n", sample->pid);
		वापस;
	पूर्ण

	अगर (!sched->show_callchain || sample->callchain == शून्य)
		वापस;

	अगर (thपढ़ो__resolve_callchain(thपढ़ो, cursor, evsel, sample,
				      शून्य, शून्य, sched->max_stack + 2) != 0) अणु
		अगर (verbose > 0)
			pr_err("Failed to resolve callchain. Skipping\n");

		वापस;
	पूर्ण

	callchain_cursor_commit(cursor);

	जबतक (true) अणु
		काष्ठा callchain_cursor_node *node;
		काष्ठा symbol *sym;

		node = callchain_cursor_current(cursor);
		अगर (node == शून्य)
			अवरोध;

		sym = node->ms.sym;
		अगर (sym) अणु
			अगर (!म_भेद(sym->name, "schedule") ||
			    !म_भेद(sym->name, "__schedule") ||
			    !म_भेद(sym->name, "preempt_schedule"))
				sym->ignore = 1;
		पूर्ण

		callchain_cursor_advance(cursor);
	पूर्ण
पूर्ण

अटल पूर्णांक init_idle_thपढ़ो(काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा idle_thपढ़ो_runसमय *itr;

	thपढ़ो__set_comm(thपढ़ो, idle_comm, 0);

	itr = zalloc(माप(*itr));
	अगर (itr == शून्य)
		वापस -ENOMEM;

	init_stats(&itr->tr.run_stats);
	callchain_init(&itr->callchain);
	callchain_cursor_reset(&itr->cursor);
	thपढ़ो__set_priv(thपढ़ो, itr);

	वापस 0;
पूर्ण

/*
 * Track idle stats per cpu by मुख्यtaining a local thपढ़ो
 * काष्ठा क्रम the idle task on each cpu.
 */
अटल पूर्णांक init_idle_thपढ़ोs(पूर्णांक ncpu)
अणु
	पूर्णांक i, ret;

	idle_thपढ़ोs = zalloc(ncpu * माप(काष्ठा thपढ़ो *));
	अगर (!idle_thपढ़ोs)
		वापस -ENOMEM;

	idle_max_cpu = ncpu;

	/* allocate the actual thपढ़ो काष्ठा अगर needed */
	क्रम (i = 0; i < ncpu; ++i) अणु
		idle_thपढ़ोs[i] = thपढ़ो__new(0, 0);
		अगर (idle_thपढ़ोs[i] == शून्य)
			वापस -ENOMEM;

		ret = init_idle_thपढ़ो(idle_thपढ़ोs[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम मुक्त_idle_thपढ़ोs(व्योम)
अणु
	पूर्णांक i;

	अगर (idle_thपढ़ोs == शून्य)
		वापस;

	क्रम (i = 0; i < idle_max_cpu; ++i) अणु
		अगर ((idle_thपढ़ोs[i]))
			thपढ़ो__delete(idle_thपढ़ोs[i]);
	पूर्ण

	मुक्त(idle_thपढ़ोs);
पूर्ण

अटल काष्ठा thपढ़ो *get_idle_thपढ़ो(पूर्णांक cpu)
अणु
	/*
	 * expand/allocate array of poपूर्णांकers to local thपढ़ो
	 * काष्ठाs अगर needed
	 */
	अगर ((cpu >= idle_max_cpu) || (idle_thपढ़ोs == शून्य)) अणु
		पूर्णांक i, j = __roundup_घात_of_two(cpu+1);
		व्योम *p;

		p = पुनः_स्मृति(idle_thपढ़ोs, j * माप(काष्ठा thपढ़ो *));
		अगर (!p)
			वापस शून्य;

		idle_thपढ़ोs = (काष्ठा thपढ़ो **) p;
		क्रम (i = idle_max_cpu; i < j; ++i)
			idle_thपढ़ोs[i] = शून्य;

		idle_max_cpu = j;
	पूर्ण

	/* allocate a new thपढ़ो काष्ठा अगर needed */
	अगर (idle_thपढ़ोs[cpu] == शून्य) अणु
		idle_thपढ़ोs[cpu] = thपढ़ो__new(0, 0);

		अगर (idle_thपढ़ोs[cpu]) अणु
			अगर (init_idle_thपढ़ो(idle_thपढ़ोs[cpu]) < 0)
				वापस शून्य;
		पूर्ण
	पूर्ण

	वापस idle_thपढ़ोs[cpu];
पूर्ण

अटल व्योम save_idle_callchain(काष्ठा perf_sched *sched,
				काष्ठा idle_thपढ़ो_runसमय *itr,
				काष्ठा perf_sample *sample)
अणु
	अगर (!sched->show_callchain || sample->callchain == शून्य)
		वापस;

	callchain_cursor__copy(&itr->cursor, &callchain_cursor);
पूर्ण

अटल काष्ठा thपढ़ो *समयhist_get_thपढ़ो(काष्ठा perf_sched *sched,
					  काष्ठा perf_sample *sample,
					  काष्ठा machine *machine,
					  काष्ठा evsel *evsel)
अणु
	काष्ठा thपढ़ो *thपढ़ो;

	अगर (is_idle_sample(sample, evsel)) अणु
		thपढ़ो = get_idle_thपढ़ो(sample->cpu);
		अगर (thपढ़ो == शून्य)
			pr_err("Failed to get idle thread for cpu %d.\n", sample->cpu);

	पूर्ण अन्यथा अणु
		/* there were samples with tid 0 but non-zero pid */
		thपढ़ो = machine__findnew_thपढ़ो(machine, sample->pid,
						 sample->tid ?: sample->pid);
		अगर (thपढ़ो == शून्य) अणु
			pr_debug("Failed to get thread for tid %d. skipping sample.\n",
				 sample->tid);
		पूर्ण

		save_task_callchain(sched, sample, evsel, machine);
		अगर (sched->idle_hist) अणु
			काष्ठा thपढ़ो *idle;
			काष्ठा idle_thपढ़ो_runसमय *itr;

			idle = get_idle_thपढ़ो(sample->cpu);
			अगर (idle == शून्य) अणु
				pr_err("Failed to get idle thread for cpu %d.\n", sample->cpu);
				वापस शून्य;
			पूर्ण

			itr = thपढ़ो__priv(idle);
			अगर (itr == शून्य)
				वापस शून्य;

			itr->last_thपढ़ो = thपढ़ो;

			/* copy task callchain when entering to idle */
			अगर (evsel__पूर्णांकval(evsel, sample, "next_pid") == 0)
				save_idle_callchain(sched, itr, sample);
		पूर्ण
	पूर्ण

	वापस thपढ़ो;
पूर्ण

अटल bool समयhist_skip_sample(काष्ठा perf_sched *sched,
				 काष्ठा thपढ़ो *thपढ़ो,
				 काष्ठा evsel *evsel,
				 काष्ठा perf_sample *sample)
अणु
	bool rc = false;

	अगर (thपढ़ो__is_filtered(thपढ़ो)) अणु
		rc = true;
		sched->skipped_samples++;
	पूर्ण

	अगर (sched->idle_hist) अणु
		अगर (म_भेद(evsel__name(evsel), "sched:sched_switch"))
			rc = true;
		अन्यथा अगर (evsel__पूर्णांकval(evsel, sample, "prev_pid") != 0 &&
			 evsel__पूर्णांकval(evsel, sample, "next_pid") != 0)
			rc = true;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम समयhist_prपूर्णांक_wakeup_event(काष्ठा perf_sched *sched,
					काष्ठा evsel *evsel,
					काष्ठा perf_sample *sample,
					काष्ठा machine *machine,
					काष्ठा thपढ़ो *awakened)
अणु
	काष्ठा thपढ़ो *thपढ़ो;
	अक्षर tstr[64];

	thपढ़ो = machine__findnew_thपढ़ो(machine, sample->pid, sample->tid);
	अगर (thपढ़ो == शून्य)
		वापस;

	/* show wakeup unless both awakee and awaker are filtered */
	अगर (समयhist_skip_sample(sched, thपढ़ो, evsel, sample) &&
	    समयhist_skip_sample(sched, awakened, evsel, sample)) अणु
		वापस;
	पूर्ण

	बारtamp__scnम_लिखो_usec(sample->समय, tstr, माप(tstr));
	म_लिखो("%15s [%04d] ", tstr, sample->cpu);
	अगर (sched->show_cpu_visual)
		म_लिखो(" %*s ", sched->max_cpu + 1, "");

	म_लिखो(" %-*s ", comm_width, समयhist_get_commstr(thपढ़ो));

	/* dt spacer */
	म_लिखो("  %9s  %9s  %9s ", "", "", "");

	म_लिखो("awakened: %s", समयhist_get_commstr(awakened));

	म_लिखो("\n");
पूर्ण

अटल पूर्णांक समयhist_sched_wakeup_ignore(काष्ठा perf_tool *tool __maybe_unused,
					जोड़ perf_event *event __maybe_unused,
					काष्ठा evsel *evsel __maybe_unused,
					काष्ठा perf_sample *sample __maybe_unused,
					काष्ठा machine *machine __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक समयhist_sched_wakeup_event(काष्ठा perf_tool *tool,
				       जोड़ perf_event *event __maybe_unused,
				       काष्ठा evsel *evsel,
				       काष्ठा perf_sample *sample,
				       काष्ठा machine *machine)
अणु
	काष्ठा perf_sched *sched = container_of(tool, काष्ठा perf_sched, tool);
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा thपढ़ो_runसमय *tr = शून्य;
	/* want pid of awakened task not pid in sample */
	स्थिर u32 pid = evsel__पूर्णांकval(evsel, sample, "pid");

	thपढ़ो = machine__findnew_thपढ़ो(machine, 0, pid);
	अगर (thपढ़ो == शून्य)
		वापस -1;

	tr = thपढ़ो__get_runसमय(thपढ़ो);
	अगर (tr == शून्य)
		वापस -1;

	अगर (tr->पढ़ोy_to_run == 0)
		tr->पढ़ोy_to_run = sample->समय;

	/* show wakeups अगर requested */
	अगर (sched->show_wakeups &&
	    !perf_समय__skip_sample(&sched->pसमय, sample->समय))
		समयhist_prपूर्णांक_wakeup_event(sched, evsel, sample, machine, thपढ़ो);

	वापस 0;
पूर्ण

अटल व्योम समयhist_prपूर्णांक_migration_event(काष्ठा perf_sched *sched,
					काष्ठा evsel *evsel,
					काष्ठा perf_sample *sample,
					काष्ठा machine *machine,
					काष्ठा thपढ़ो *migrated)
अणु
	काष्ठा thपढ़ो *thपढ़ो;
	अक्षर tstr[64];
	u32 max_cpus = sched->max_cpu + 1;
	u32 ocpu, dcpu;

	अगर (sched->summary_only)
		वापस;

	max_cpus = sched->max_cpu + 1;
	ocpu = evsel__पूर्णांकval(evsel, sample, "orig_cpu");
	dcpu = evsel__पूर्णांकval(evsel, sample, "dest_cpu");

	thपढ़ो = machine__findnew_thपढ़ो(machine, sample->pid, sample->tid);
	अगर (thपढ़ो == शून्य)
		वापस;

	अगर (समयhist_skip_sample(sched, thपढ़ो, evsel, sample) &&
	    समयhist_skip_sample(sched, migrated, evsel, sample)) अणु
		वापस;
	पूर्ण

	बारtamp__scnम_लिखो_usec(sample->समय, tstr, माप(tstr));
	म_लिखो("%15s [%04d] ", tstr, sample->cpu);

	अगर (sched->show_cpu_visual) अणु
		u32 i;
		अक्षर c;

		म_लिखो("  ");
		क्रम (i = 0; i < max_cpus; ++i) अणु
			c = (i == sample->cpu) ? 'm' : ' ';
			म_लिखो("%c", c);
		पूर्ण
		म_लिखो("  ");
	पूर्ण

	म_लिखो(" %-*s ", comm_width, समयhist_get_commstr(thपढ़ो));

	/* dt spacer */
	म_लिखो("  %9s  %9s  %9s ", "", "", "");

	म_लिखो("migrated: %s", समयhist_get_commstr(migrated));
	म_लिखो(" cpu %d => %d", ocpu, dcpu);

	म_लिखो("\n");
पूर्ण

अटल पूर्णांक समयhist_migrate_task_event(काष्ठा perf_tool *tool,
				       जोड़ perf_event *event __maybe_unused,
				       काष्ठा evsel *evsel,
				       काष्ठा perf_sample *sample,
				       काष्ठा machine *machine)
अणु
	काष्ठा perf_sched *sched = container_of(tool, काष्ठा perf_sched, tool);
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा thपढ़ो_runसमय *tr = शून्य;
	/* want pid of migrated task not pid in sample */
	स्थिर u32 pid = evsel__पूर्णांकval(evsel, sample, "pid");

	thपढ़ो = machine__findnew_thपढ़ो(machine, 0, pid);
	अगर (thपढ़ो == शून्य)
		वापस -1;

	tr = thपढ़ो__get_runसमय(thपढ़ो);
	अगर (tr == शून्य)
		वापस -1;

	tr->migrations++;

	/* show migrations अगर requested */
	समयhist_prपूर्णांक_migration_event(sched, evsel, sample, machine, thपढ़ो);

	वापस 0;
पूर्ण

अटल पूर्णांक समयhist_sched_change_event(काष्ठा perf_tool *tool,
				       जोड़ perf_event *event,
				       काष्ठा evsel *evsel,
				       काष्ठा perf_sample *sample,
				       काष्ठा machine *machine)
अणु
	काष्ठा perf_sched *sched = container_of(tool, काष्ठा perf_sched, tool);
	काष्ठा perf_समय_पूर्णांकerval *pसमय = &sched->pसमय;
	काष्ठा addr_location al;
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा thपढ़ो_runसमय *tr = शून्य;
	u64 tprev, t = sample->समय;
	पूर्णांक rc = 0;
	पूर्णांक state = evsel__पूर्णांकval(evsel, sample, "prev_state");

	अगर (machine__resolve(machine, &al, sample) < 0) अणु
		pr_err("problem processing %d event. skipping it\n",
		       event->header.type);
		rc = -1;
		जाओ out;
	पूर्ण

	thपढ़ो = समयhist_get_thपढ़ो(sched, sample, machine, evsel);
	अगर (thपढ़ो == शून्य) अणु
		rc = -1;
		जाओ out;
	पूर्ण

	अगर (समयhist_skip_sample(sched, thपढ़ो, evsel, sample))
		जाओ out;

	tr = thपढ़ो__get_runसमय(thपढ़ो);
	अगर (tr == शून्य) अणु
		rc = -1;
		जाओ out;
	पूर्ण

	tprev = evsel__get_समय(evsel, sample->cpu);

	/*
	 * If start समय given:
	 * - sample समय is under winकरोw user cares about - skip sample
	 * - tprev is under winकरोw user cares about  - reset to start of winकरोw
	 */
	अगर (pसमय->start && pसमय->start > t)
		जाओ out;

	अगर (tprev && pसमय->start > tprev)
		tprev = pसमय->start;

	/*
	 * If end समय given:
	 * - previous sched event is out of winकरोw - we are करोne
	 * - sample समय is beyond winकरोw user cares about - reset it
	 *   to बंद out stats क्रम समय winकरोw पूर्णांकerest
	 */
	अगर (pसमय->end) अणु
		अगर (tprev > pसमय->end)
			जाओ out;

		अगर (t > pसमय->end)
			t = pसमय->end;
	पूर्ण

	अगर (!sched->idle_hist || thपढ़ो->tid == 0) अणु
		अगर (!cpu_list || test_bit(sample->cpu, cpu_biपंचांगap))
			समयhist_update_runसमय_stats(tr, t, tprev);

		अगर (sched->idle_hist) अणु
			काष्ठा idle_thपढ़ो_runसमय *itr = (व्योम *)tr;
			काष्ठा thपढ़ो_runसमय *last_tr;

			BUG_ON(thपढ़ो->tid != 0);

			अगर (itr->last_thपढ़ो == शून्य)
				जाओ out;

			/* add current idle समय as last thपढ़ो's runसमय */
			last_tr = thपढ़ो__get_runसमय(itr->last_thपढ़ो);
			अगर (last_tr == शून्य)
				जाओ out;

			समयhist_update_runसमय_stats(last_tr, t, tprev);
			/*
			 * हटाओ delta समय of last thपढ़ो as it's not updated
			 * and otherwise it will show an invalid value next
			 * समय.  we only care total run समय and run stat.
			 */
			last_tr->dt_run = 0;
			last_tr->dt_delay = 0;
			last_tr->dt_sleep = 0;
			last_tr->dt_ioरुको = 0;
			last_tr->dt_preempt = 0;

			अगर (itr->cursor.nr)
				callchain_append(&itr->callchain, &itr->cursor, t - tprev);

			itr->last_thपढ़ो = शून्य;
		पूर्ण
	पूर्ण

	अगर (!sched->summary_only)
		समयhist_prपूर्णांक_sample(sched, evsel, sample, &al, thपढ़ो, t, state);

out:
	अगर (sched->hist_समय.start == 0 && t >= pसमय->start)
		sched->hist_समय.start = t;
	अगर (pसमय->end == 0 || t <= pसमय->end)
		sched->hist_समय.end = t;

	अगर (tr) अणु
		/* समय of this sched_चयन event becomes last समय task seen */
		tr->last_समय = sample->समय;

		/* last state is used to determine where to account रुको समय */
		tr->last_state = state;

		/* sched out event क्रम task so reset पढ़ोy to run समय */
		tr->पढ़ोy_to_run = 0;
	पूर्ण

	evsel__save_समय(evsel, sample->समय, sample->cpu);

	वापस rc;
पूर्ण

अटल पूर्णांक समयhist_sched_चयन_event(काष्ठा perf_tool *tool,
			     जोड़ perf_event *event,
			     काष्ठा evsel *evsel,
			     काष्ठा perf_sample *sample,
			     काष्ठा machine *machine __maybe_unused)
अणु
	वापस समयhist_sched_change_event(tool, event, evsel, sample, machine);
पूर्ण

अटल पूर्णांक process_lost(काष्ठा perf_tool *tool __maybe_unused,
			जोड़ perf_event *event,
			काष्ठा perf_sample *sample,
			काष्ठा machine *machine __maybe_unused)
अणु
	अक्षर tstr[64];

	बारtamp__scnम_लिखो_usec(sample->समय, tstr, माप(tstr));
	म_लिखो("%15s ", tstr);
	म_लिखो("lost %" PRI_lu64 " events on cpu %d\n", event->lost.lost, sample->cpu);

	वापस 0;
पूर्ण


अटल व्योम prपूर्णांक_thपढ़ो_runसमय(काष्ठा thपढ़ो *t,
				 काष्ठा thपढ़ो_runसमय *r)
अणु
	द्विगुन mean = avg_stats(&r->run_stats);
	भग्न stddev;

	म_लिखो("%*s   %5d  %9" PRIu64 " ",
	       comm_width, समयhist_get_commstr(t), t->ppid,
	       (u64) r->run_stats.n);

	prपूर्णांक_sched_समय(r->total_run_समय, 8);
	stddev = rel_stddev_stats(stddev_stats(&r->run_stats), mean);
	prपूर्णांक_sched_समय(r->run_stats.min, 6);
	म_लिखो(" ");
	prपूर्णांक_sched_समय((u64) mean, 6);
	म_लिखो(" ");
	prपूर्णांक_sched_समय(r->run_stats.max, 6);
	म_लिखो("  ");
	म_लिखो("%5.2f", stddev);
	म_लिखो("   %5" PRIu64, r->migrations);
	म_लिखो("\n");
पूर्ण

अटल व्योम prपूर्णांक_thपढ़ो_रुकोसमय(काष्ठा thपढ़ो *t,
				  काष्ठा thपढ़ो_runसमय *r)
अणु
	म_लिखो("%*s   %5d  %9" PRIu64 " ",
	       comm_width, समयhist_get_commstr(t), t->ppid,
	       (u64) r->run_stats.n);

	prपूर्णांक_sched_समय(r->total_run_समय, 8);
	prपूर्णांक_sched_समय(r->total_sleep_समय, 6);
	म_लिखो(" ");
	prपूर्णांक_sched_समय(r->total_ioरुको_समय, 6);
	म_लिखो(" ");
	prपूर्णांक_sched_समय(r->total_preempt_समय, 6);
	म_लिखो(" ");
	prपूर्णांक_sched_समय(r->total_delay_समय, 6);
	म_लिखो("\n");
पूर्ण

काष्ठा total_run_stats अणु
	काष्ठा perf_sched *sched;
	u64  sched_count;
	u64  task_count;
	u64  total_run_समय;
पूर्ण;

अटल पूर्णांक __show_thपढ़ो_runसमय(काष्ठा thपढ़ो *t, व्योम *priv)
अणु
	काष्ठा total_run_stats *stats = priv;
	काष्ठा thपढ़ो_runसमय *r;

	अगर (thपढ़ो__is_filtered(t))
		वापस 0;

	r = thपढ़ो__priv(t);
	अगर (r && r->run_stats.n) अणु
		stats->task_count++;
		stats->sched_count += r->run_stats.n;
		stats->total_run_समय += r->total_run_समय;

		अगर (stats->sched->show_state)
			prपूर्णांक_thपढ़ो_रुकोसमय(t, r);
		अन्यथा
			prपूर्णांक_thपढ़ो_runसमय(t, r);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक show_thपढ़ो_runसमय(काष्ठा thपढ़ो *t, व्योम *priv)
अणु
	अगर (t->dead)
		वापस 0;

	वापस __show_thपढ़ो_runसमय(t, priv);
पूर्ण

अटल पूर्णांक show_deadthपढ़ो_runसमय(काष्ठा thपढ़ो *t, व्योम *priv)
अणु
	अगर (!t->dead)
		वापस 0;

	वापस __show_thपढ़ो_runसमय(t, priv);
पूर्ण

अटल माप_प्रकार callchain__ख_लिखो_folded(खाता *fp, काष्ठा callchain_node *node)
अणु
	स्थिर अक्षर *sep = " <- ";
	काष्ठा callchain_list *chain;
	माप_प्रकार ret = 0;
	अक्षर bf[1024];
	bool first;

	अगर (node == शून्य)
		वापस 0;

	ret = callchain__ख_लिखो_folded(fp, node->parent);
	first = (ret == 0);

	list_क्रम_each_entry(chain, &node->val, list) अणु
		अगर (chain->ip >= PERF_CONTEXT_MAX)
			जारी;
		अगर (chain->ms.sym && chain->ms.sym->ignore)
			जारी;
		ret += ख_लिखो(fp, "%s%s", first ? "" : sep,
			       callchain_list__sym_name(chain, bf, माप(bf),
							false));
		first = false;
	पूर्ण

	वापस ret;
पूर्ण

अटल माप_प्रकार समयhist_prपूर्णांक_idlehist_callchain(काष्ठा rb_root_cached *root)
अणु
	माप_प्रकार ret = 0;
	खाता *fp = मानक_निकास;
	काष्ठा callchain_node *chain;
	काष्ठा rb_node *rb_node = rb_first_cached(root);

	म_लिखो("  %16s  %8s  %s\n", "Idle time (msec)", "Count", "Callchains");
	म_लिखो("  %.16s  %.8s  %.50s\n", graph_करोtted_line, graph_करोtted_line,
	       graph_करोtted_line);

	जबतक (rb_node) अणु
		chain = rb_entry(rb_node, काष्ठा callchain_node, rb_node);
		rb_node = rb_next(rb_node);

		ret += ख_लिखो(fp, "  ");
		prपूर्णांक_sched_समय(chain->hit, 12);
		ret += 16;  /* prपूर्णांक_sched_समय वापसs 2nd arg + 4 */
		ret += ख_लिखो(fp, " %8d  ", chain->count);
		ret += callchain__ख_लिखो_folded(fp, chain);
		ret += ख_लिखो(fp, "\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम समयhist_prपूर्णांक_summary(काष्ठा perf_sched *sched,
				   काष्ठा perf_session *session)
अणु
	काष्ठा machine *m = &session->machines.host;
	काष्ठा total_run_stats totals;
	u64 task_count;
	काष्ठा thपढ़ो *t;
	काष्ठा thपढ़ो_runसमय *r;
	पूर्णांक i;
	u64 hist_समय = sched->hist_समय.end - sched->hist_समय.start;

	स_रखो(&totals, 0, माप(totals));
	totals.sched = sched;

	अगर (sched->idle_hist) अणु
		म_लिखो("\nIdle-time summary\n");
		म_लिखो("%*s  parent  sched-out  ", comm_width, "comm");
		म_लिखो("  idle-time   min-idle    avg-idle    max-idle  stddev  migrations\n");
	पूर्ण अन्यथा अगर (sched->show_state) अणु
		म_लिखो("\nWait-time summary\n");
		म_लिखो("%*s  parent   sched-in  ", comm_width, "comm");
		म_लिखो("   run-time      sleep      iowait     preempt       delay\n");
	पूर्ण अन्यथा अणु
		म_लिखो("\nRuntime summary\n");
		म_लिखो("%*s  parent   sched-in  ", comm_width, "comm");
		म_लिखो("   run-time    min-run     avg-run     max-run  stddev  migrations\n");
	पूर्ण
	म_लिखो("%*s            (count)  ", comm_width, "");
	म_लिखो("     (msec)     (msec)      (msec)      (msec)       %s\n",
	       sched->show_state ? "(msec)" : "%");
	म_लिखो("%.117s\n", graph_करोtted_line);

	machine__क्रम_each_thपढ़ो(m, show_thपढ़ो_runसमय, &totals);
	task_count = totals.task_count;
	अगर (!task_count)
		म_लिखो("<no still running tasks>\n");

	म_लिखो("\nTerminated tasks:\n");
	machine__क्रम_each_thपढ़ो(m, show_deadthपढ़ो_runसमय, &totals);
	अगर (task_count == totals.task_count)
		म_लिखो("<no terminated tasks>\n");

	/* CPU idle stats not tracked when samples were skipped */
	अगर (sched->skipped_samples && !sched->idle_hist)
		वापस;

	म_लिखो("\nIdle stats:\n");
	क्रम (i = 0; i < idle_max_cpu; ++i) अणु
		अगर (cpu_list && !test_bit(i, cpu_biपंचांगap))
			जारी;

		t = idle_thपढ़ोs[i];
		अगर (!t)
			जारी;

		r = thपढ़ो__priv(t);
		अगर (r && r->run_stats.n) अणु
			totals.sched_count += r->run_stats.n;
			म_लिखो("    CPU %2d idle for ", i);
			prपूर्णांक_sched_समय(r->total_run_समय, 6);
			म_लिखो(" msec  (%6.2f%%)\n", 100.0 * r->total_run_समय / hist_समय);
		पूर्ण अन्यथा
			म_लिखो("    CPU %2d idle entire time window\n", i);
	पूर्ण

	अगर (sched->idle_hist && sched->show_callchain) अणु
		callchain_param.mode  = CHAIN_FOLDED;
		callchain_param.value = CCVAL_PERIOD;

		callchain_रेजिस्टर_param(&callchain_param);

		म_लिखो("\nIdle stats by callchain:\n");
		क्रम (i = 0; i < idle_max_cpu; ++i) अणु
			काष्ठा idle_thपढ़ो_runसमय *itr;

			t = idle_thपढ़ोs[i];
			अगर (!t)
				जारी;

			itr = thपढ़ो__priv(t);
			अगर (itr == शून्य)
				जारी;

			callchain_param.sort(&itr->sorted_root.rb_root, &itr->callchain,
					     0, &callchain_param);

			म_लिखो("  CPU %2d:", i);
			prपूर्णांक_sched_समय(itr->tr.total_run_समय, 6);
			म_लिखो(" msec\n");
			समयhist_prपूर्णांक_idlehist_callchain(&itr->sorted_root);
			म_लिखो("\n");
		पूर्ण
	पूर्ण

	म_लिखो("\n"
	       "    Total number of unique tasks: %" PRIu64 "\n"
	       "Total number of context switches: %" PRIu64 "\n",
	       totals.task_count, totals.sched_count);

	म_लिखो("           Total run time (msec): ");
	prपूर्णांक_sched_समय(totals.total_run_समय, 2);
	म_लिखो("\n");

	म_लिखो("    Total scheduling time (msec): ");
	prपूर्णांक_sched_समय(hist_समय, 2);
	म_लिखो(" (x %d)\n", sched->max_cpu);
पूर्ण

प्रकार पूर्णांक (*sched_handler)(काष्ठा perf_tool *tool,
			  जोड़ perf_event *event,
			  काष्ठा evsel *evsel,
			  काष्ठा perf_sample *sample,
			  काष्ठा machine *machine);

अटल पूर्णांक perf_समयhist__process_sample(काष्ठा perf_tool *tool,
					 जोड़ perf_event *event,
					 काष्ठा perf_sample *sample,
					 काष्ठा evsel *evsel,
					 काष्ठा machine *machine)
अणु
	काष्ठा perf_sched *sched = container_of(tool, काष्ठा perf_sched, tool);
	पूर्णांक err = 0;
	पूर्णांक this_cpu = sample->cpu;

	अगर (this_cpu > sched->max_cpu)
		sched->max_cpu = this_cpu;

	अगर (evsel->handler != शून्य) अणु
		sched_handler f = evsel->handler;

		err = f(tool, event, evsel, sample, machine);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक समयhist_check_attr(काष्ठा perf_sched *sched,
			       काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;
	काष्ठा evsel_runसमय *er;

	list_क्रम_each_entry(evsel, &evlist->core.entries, core.node) अणु
		er = evsel__get_runसमय(evsel);
		अगर (er == शून्य) अणु
			pr_err("Failed to allocate memory for evsel runtime data\n");
			वापस -1;
		पूर्ण

		अगर (sched->show_callchain && !evsel__has_callchain(evsel)) अणु
			pr_info("Samples do not have callchains.\n");
			sched->show_callchain = 0;
			symbol_conf.use_callchain = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक perf_sched__समयhist(काष्ठा perf_sched *sched)
अणु
	काष्ठा evsel_str_handler handlers[] = अणु
		अणु "sched:sched_switch",       समयhist_sched_चयन_event, पूर्ण,
		अणु "sched:sched_wakeup",	      समयhist_sched_wakeup_event, पूर्ण,
		अणु "sched:sched_waking",       समयhist_sched_wakeup_event, पूर्ण,
		अणु "sched:sched_wakeup_new",   समयhist_sched_wakeup_event, पूर्ण,
	पूर्ण;
	स्थिर काष्ठा evsel_str_handler migrate_handlers[] = अणु
		अणु "sched:sched_migrate_task", समयhist_migrate_task_event, पूर्ण,
	पूर्ण;
	काष्ठा perf_data data = अणु
		.path  = input_name,
		.mode  = PERF_DATA_MODE_READ,
		.क्रमce = sched->क्रमce,
	पूर्ण;

	काष्ठा perf_session *session;
	काष्ठा evlist *evlist;
	पूर्णांक err = -1;

	/*
	 * event handlers क्रम समयhist option
	 */
	sched->tool.sample	 = perf_समयhist__process_sample;
	sched->tool.mmap	 = perf_event__process_mmap;
	sched->tool.comm	 = perf_event__process_comm;
	sched->tool.निकास	 = perf_event__process_निकास;
	sched->tool.विभाजन	 = perf_event__process_विभाजन;
	sched->tool.lost	 = process_lost;
	sched->tool.attr	 = perf_event__process_attr;
	sched->tool.tracing_data = perf_event__process_tracing_data;
	sched->tool.build_id	 = perf_event__process_build_id;

	sched->tool.ordered_events = true;
	sched->tool.ordering_requires_बारtamps = true;

	symbol_conf.use_callchain = sched->show_callchain;

	session = perf_session__new(&data, false, &sched->tool);
	अगर (IS_ERR(session))
		वापस PTR_ERR(session);

	अगर (cpu_list) अणु
		err = perf_session__cpu_biपंचांगap(session, cpu_list, cpu_biपंचांगap);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	evlist = session->evlist;

	symbol__init(&session->header.env);

	अगर (perf_समय__parse_str(&sched->pसमय, sched->समय_str) != 0) अणु
		pr_err("Invalid time string\n");
		वापस -EINVAL;
	पूर्ण

	अगर (समयhist_check_attr(sched, evlist) != 0)
		जाओ out;

	setup_pager();

	/* prefer sched_waking अगर it is captured */
	अगर (evlist__find_tracepoपूर्णांक_by_name(session->evlist, "sched:sched_waking"))
		handlers[1].handler = समयhist_sched_wakeup_ignore;

	/* setup per-evsel handlers */
	अगर (perf_session__set_tracepoपूर्णांकs_handlers(session, handlers))
		जाओ out;

	/* sched_चयन event at a minimum needs to exist */
	अगर (!evlist__find_tracepoपूर्णांक_by_name(session->evlist, "sched:sched_switch")) अणु
		pr_err("No sched_switch events found. Have you run 'perf sched record'?\n");
		जाओ out;
	पूर्ण

	अगर (sched->show_migrations &&
	    perf_session__set_tracepoपूर्णांकs_handlers(session, migrate_handlers))
		जाओ out;

	/* pre-allocate काष्ठा क्रम per-CPU idle stats */
	sched->max_cpu = session->header.env.nr_cpus_online;
	अगर (sched->max_cpu == 0)
		sched->max_cpu = 4;
	अगर (init_idle_thपढ़ोs(sched->max_cpu))
		जाओ out;

	/* summary_only implies summary option, but करोn't overग_लिखो summary अगर set */
	अगर (sched->summary_only)
		sched->summary = sched->summary_only;

	अगर (!sched->summary_only)
		समयhist_header(sched);

	err = perf_session__process_events(session);
	अगर (err) अणु
		pr_err("Failed to process events, error %d", err);
		जाओ out;
	पूर्ण

	sched->nr_events      = evlist->stats.nr_events[0];
	sched->nr_lost_events = evlist->stats.total_lost;
	sched->nr_lost_chunks = evlist->stats.nr_events[PERF_RECORD_LOST];

	अगर (sched->summary)
		समयhist_prपूर्णांक_summary(sched, session);

out:
	मुक्त_idle_thपढ़ोs();
	perf_session__delete(session);

	वापस err;
पूर्ण


अटल व्योम prपूर्णांक_bad_events(काष्ठा perf_sched *sched)
अणु
	अगर (sched->nr_unordered_बारtamps && sched->nr_बारtamps) अणु
		म_लिखो("  INFO: %.3f%% unordered timestamps (%ld out of %ld)\n",
			(द्विगुन)sched->nr_unordered_बारtamps/(द्विगुन)sched->nr_बारtamps*100.0,
			sched->nr_unordered_बारtamps, sched->nr_बारtamps);
	पूर्ण
	अगर (sched->nr_lost_events && sched->nr_events) अणु
		म_लिखो("  INFO: %.3f%% lost events (%ld out of %ld, in %ld chunks)\n",
			(द्विगुन)sched->nr_lost_events/(द्विगुन)sched->nr_events * 100.0,
			sched->nr_lost_events, sched->nr_events, sched->nr_lost_chunks);
	पूर्ण
	अगर (sched->nr_context_चयन_bugs && sched->nr_बारtamps) अणु
		म_लिखो("  INFO: %.3f%% context switch bugs (%ld out of %ld)",
			(द्विगुन)sched->nr_context_चयन_bugs/(द्विगुन)sched->nr_बारtamps*100.0,
			sched->nr_context_चयन_bugs, sched->nr_बारtamps);
		अगर (sched->nr_lost_events)
			म_लिखो(" (due to lost events?)");
		म_लिखो("\n");
	पूर्ण
पूर्ण

अटल व्योम __merge_work_atoms(काष्ठा rb_root_cached *root, काष्ठा work_atoms *data)
अणु
	काष्ठा rb_node **new = &(root->rb_root.rb_node), *parent = शून्य;
	काष्ठा work_atoms *this;
	स्थिर अक्षर *comm = thपढ़ो__comm_str(data->thपढ़ो), *this_comm;
	bool lefपंचांगost = true;

	जबतक (*new) अणु
		पूर्णांक cmp;

		this = container_of(*new, काष्ठा work_atoms, node);
		parent = *new;

		this_comm = thपढ़ो__comm_str(this->thपढ़ो);
		cmp = म_भेद(comm, this_comm);
		अगर (cmp > 0) अणु
			new = &((*new)->rb_left);
		पूर्ण अन्यथा अगर (cmp < 0) अणु
			new = &((*new)->rb_right);
			lefपंचांगost = false;
		पूर्ण अन्यथा अणु
			this->num_merged++;
			this->total_runसमय += data->total_runसमय;
			this->nb_atoms += data->nb_atoms;
			this->total_lat += data->total_lat;
			list_splice(&data->work_list, &this->work_list);
			अगर (this->max_lat < data->max_lat) अणु
				this->max_lat = data->max_lat;
				this->max_lat_start = data->max_lat_start;
				this->max_lat_end = data->max_lat_end;
			पूर्ण
			zमुक्त(&data);
			वापस;
		पूर्ण
	पूर्ण

	data->num_merged++;
	rb_link_node(&data->node, parent, new);
	rb_insert_color_cached(&data->node, root, lefपंचांगost);
पूर्ण

अटल व्योम perf_sched__merge_lat(काष्ठा perf_sched *sched)
अणु
	काष्ठा work_atoms *data;
	काष्ठा rb_node *node;

	अगर (sched->skip_merge)
		वापस;

	जबतक ((node = rb_first_cached(&sched->atom_root))) अणु
		rb_erase_cached(node, &sched->atom_root);
		data = rb_entry(node, काष्ठा work_atoms, node);
		__merge_work_atoms(&sched->merged_atom_root, data);
	पूर्ण
पूर्ण

अटल पूर्णांक perf_sched__lat(काष्ठा perf_sched *sched)
अणु
	काष्ठा rb_node *next;

	setup_pager();

	अगर (perf_sched__पढ़ो_events(sched))
		वापस -1;

	perf_sched__merge_lat(sched);
	perf_sched__sort_lat(sched);

	म_लिखो("\n -------------------------------------------------------------------------------------------------------------------------------------------\n");
	म_लिखो("  Task                  |   Runtime ms  | Switches | Avg delay ms    | Max delay ms    | Max delay start           | Max delay end          |\n");
	म_लिखो(" -------------------------------------------------------------------------------------------------------------------------------------------\n");

	next = rb_first_cached(&sched->sorted_atom_root);

	जबतक (next) अणु
		काष्ठा work_atoms *work_list;

		work_list = rb_entry(next, काष्ठा work_atoms, node);
		output_lat_thपढ़ो(sched, work_list);
		next = rb_next(next);
		thपढ़ो__zput(work_list->thपढ़ो);
	पूर्ण

	म_लिखो(" -----------------------------------------------------------------------------------------------------------------\n");
	म_लिखो("  TOTAL:                |%11.3f ms |%9" PRIu64 " |\n",
		(द्विगुन)sched->all_runसमय / NSEC_PER_MSEC, sched->all_count);

	म_लिखो(" ---------------------------------------------------\n");

	prपूर्णांक_bad_events(sched);
	म_लिखो("\n");

	वापस 0;
पूर्ण

अटल पूर्णांक setup_map_cpus(काष्ठा perf_sched *sched)
अणु
	काष्ठा perf_cpu_map *map;

	sched->max_cpu  = sysconf(_SC_NPROCESSORS_CONF);

	अगर (sched->map.comp) अणु
		sched->map.comp_cpus = zalloc(sched->max_cpu * माप(पूर्णांक));
		अगर (!sched->map.comp_cpus)
			वापस -1;
	पूर्ण

	अगर (!sched->map.cpus_str)
		वापस 0;

	map = perf_cpu_map__new(sched->map.cpus_str);
	अगर (!map) अणु
		pr_err("failed to get cpus map from %s\n", sched->map.cpus_str);
		वापस -1;
	पूर्ण

	sched->map.cpus = map;
	वापस 0;
पूर्ण

अटल पूर्णांक setup_color_pids(काष्ठा perf_sched *sched)
अणु
	काष्ठा perf_thपढ़ो_map *map;

	अगर (!sched->map.color_pids_str)
		वापस 0;

	map = thपढ़ो_map__new_by_tid_str(sched->map.color_pids_str);
	अगर (!map) अणु
		pr_err("failed to get thread map from %s\n", sched->map.color_pids_str);
		वापस -1;
	पूर्ण

	sched->map.color_pids = map;
	वापस 0;
पूर्ण

अटल पूर्णांक setup_color_cpus(काष्ठा perf_sched *sched)
अणु
	काष्ठा perf_cpu_map *map;

	अगर (!sched->map.color_cpus_str)
		वापस 0;

	map = perf_cpu_map__new(sched->map.color_cpus_str);
	अगर (!map) अणु
		pr_err("failed to get thread map from %s\n", sched->map.color_cpus_str);
		वापस -1;
	पूर्ण

	sched->map.color_cpus = map;
	वापस 0;
पूर्ण

अटल पूर्णांक perf_sched__map(काष्ठा perf_sched *sched)
अणु
	अगर (setup_map_cpus(sched))
		वापस -1;

	अगर (setup_color_pids(sched))
		वापस -1;

	अगर (setup_color_cpus(sched))
		वापस -1;

	setup_pager();
	अगर (perf_sched__पढ़ो_events(sched))
		वापस -1;
	prपूर्णांक_bad_events(sched);
	वापस 0;
पूर्ण

अटल पूर्णांक perf_sched__replay(काष्ठा perf_sched *sched)
अणु
	अचिन्हित दीर्घ i;

	calibrate_run_measurement_overhead(sched);
	calibrate_sleep_measurement_overhead(sched);

	test_calibrations(sched);

	अगर (perf_sched__पढ़ो_events(sched))
		वापस -1;

	म_लिखो("nr_run_events:        %ld\n", sched->nr_run_events);
	म_लिखो("nr_sleep_events:      %ld\n", sched->nr_sleep_events);
	म_लिखो("nr_wakeup_events:     %ld\n", sched->nr_wakeup_events);

	अगर (sched->targetless_wakeups)
		म_लिखो("target-less wakeups:  %ld\n", sched->targetless_wakeups);
	अगर (sched->multitarget_wakeups)
		म_लिखो("multi-target wakeups: %ld\n", sched->multitarget_wakeups);
	अगर (sched->nr_run_events_optimized)
		म_लिखो("run atoms optimized: %ld\n",
			sched->nr_run_events_optimized);

	prपूर्णांक_task_traces(sched);
	add_cross_task_wakeups(sched);

	create_tasks(sched);
	म_लिखो("------------------------------------------------------------\n");
	क्रम (i = 0; i < sched->replay_repeat; i++)
		run_one_test(sched);

	वापस 0;
पूर्ण

अटल व्योम setup_sorting(काष्ठा perf_sched *sched, स्थिर काष्ठा option *options,
			  स्थिर अक्षर * स्थिर usage_msg[])
अणु
	अक्षर *पंचांगp, *tok, *str = strdup(sched->sort_order);

	क्रम (tok = म_मोहर_r(str, ", ", &पंचांगp);
			tok; tok = म_मोहर_r(शून्य, ", ", &पंचांगp)) अणु
		अगर (sort_dimension__add(tok, &sched->sort_list) < 0) अणु
			usage_with_options_msg(usage_msg, options,
					"Unknown --sort key: `%s'", tok);
		पूर्ण
	पूर्ण

	मुक्त(str);

	sort_dimension__add("pid", &sched->cmp_pid);
पूर्ण

अटल पूर्णांक __cmd_record(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अचिन्हित पूर्णांक rec_argc, i, j;
	स्थिर अक्षर **rec_argv;
	स्थिर अक्षर * स्थिर record_args[] = अणु
		"record",
		"-a",
		"-R",
		"-m", "1024",
		"-c", "1",
		"-e", "sched:sched_switch",
		"-e", "sched:sched_stat_wait",
		"-e", "sched:sched_stat_sleep",
		"-e", "sched:sched_stat_iowait",
		"-e", "sched:sched_stat_runtime",
		"-e", "sched:sched_process_fork",
		"-e", "sched:sched_wakeup_new",
		"-e", "sched:sched_migrate_task",
	पूर्ण;
	काष्ठा tep_event *waking_event;

	/*
	 * +2 क्रम either "-e", "sched:sched_wakeup" or
	 * "-e", "sched:sched_waking"
	 */
	rec_argc = ARRAY_SIZE(record_args) + 2 + argc - 1;
	rec_argv = सुस्मृति(rec_argc + 1, माप(अक्षर *));

	अगर (rec_argv == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(record_args); i++)
		rec_argv[i] = strdup(record_args[i]);

	rec_argv[i++] = "-e";
	waking_event = trace_event__tp_क्रमmat("sched", "sched_waking");
	अगर (!IS_ERR(waking_event))
		rec_argv[i++] = strdup("sched:sched_waking");
	अन्यथा
		rec_argv[i++] = strdup("sched:sched_wakeup");

	क्रम (j = 1; j < (अचिन्हित पूर्णांक)argc; j++, i++)
		rec_argv[i] = argv[j];

	BUG_ON(i != rec_argc);

	वापस cmd_record(i, rec_argv);
पूर्ण

पूर्णांक cmd_sched(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अटल स्थिर अक्षर शेष_sort_order[] = "avg, max, switch, runtime";
	काष्ठा perf_sched sched = अणु
		.tool = अणु
			.sample		 = perf_sched__process_tracepoपूर्णांक_sample,
			.comm		 = perf_sched__process_comm,
			.namespaces	 = perf_event__process_namespaces,
			.lost		 = perf_event__process_lost,
			.विभाजन		 = perf_sched__process_विभाजन_event,
			.ordered_events = true,
		पूर्ण,
		.cmp_pid	      = LIST_HEAD_INIT(sched.cmp_pid),
		.sort_list	      = LIST_HEAD_INIT(sched.sort_list),
		.start_work_mutex     = PTHREAD_MUTEX_INITIALIZER,
		.work_करोne_रुको_mutex = PTHREAD_MUTEX_INITIALIZER,
		.sort_order	      = शेष_sort_order,
		.replay_repeat	      = 10,
		.profile_cpu	      = -1,
		.next_लघुname1      = 'A',
		.next_लघुname2      = '0',
		.skip_merge           = 0,
		.show_callchain	      = 1,
		.max_stack            = 5,
	पूर्ण;
	स्थिर काष्ठा option sched_options[] = अणु
	OPT_STRING('i', "input", &input_name, "file",
		    "input file name"),
	OPT_INCR('v', "verbose", &verbose,
		    "be more verbose (show symbol address, etc)"),
	OPT_BOOLEAN('D', "dump-raw-trace", &dump_trace,
		    "dump raw trace in ASCII"),
	OPT_BOOLEAN('f', "force", &sched.force, "don't complain, करो it"),
	OPT_END()
	पूर्ण;
	स्थिर काष्ठा option latency_options[] = अणु
	OPT_STRING('s', "sort", &sched.sort_order, "key[,key2...]",
		   "sort by key(s): runtime, switch, avg, max"),
	OPT_INTEGER('C', "CPU", &sched.profile_cpu,
		    "CPU to profile on"),
	OPT_BOOLEAN('p', "pids", &sched.skip_merge,
		    "latency stats per pid instead of per comm"),
	OPT_PARENT(sched_options)
	पूर्ण;
	स्थिर काष्ठा option replay_options[] = अणु
	OPT_UINTEGER('r', "repeat", &sched.replay_repeat,
		     "repeat the workload replay N times (-1: infinite)"),
	OPT_PARENT(sched_options)
	पूर्ण;
	स्थिर काष्ठा option map_options[] = अणु
	OPT_BOOLEAN(0, "compact", &sched.map.comp,
		    "map output in compact mode"),
	OPT_STRING(0, "color-pids", &sched.map.color_pids_str, "pids",
		   "highlight given pids in map"),
	OPT_STRING(0, "color-cpus", &sched.map.color_cpus_str, "cpus",
                    "highlight given CPUs in map"),
	OPT_STRING(0, "cpus", &sched.map.cpus_str, "cpus",
                    "display given CPUs in map"),
	OPT_PARENT(sched_options)
	पूर्ण;
	स्थिर काष्ठा option समयhist_options[] = अणु
	OPT_STRING('k', "vmlinux", &symbol_conf.vmlinux_name,
		   "file", "vmlinux pathname"),
	OPT_STRING(0, "kallsyms", &symbol_conf.kallsyms_name,
		   "file", "kallsyms pathname"),
	OPT_BOOLEAN('g', "call-graph", &sched.show_callchain,
		    "Display call chains if present (default on)"),
	OPT_UINTEGER(0, "max-stack", &sched.max_stack,
		   "Maximum number of functions to display backtrace."),
	OPT_STRING(0, "symfs", &symbol_conf.symfs, "directory",
		    "Look for files with symbols relative to this directory"),
	OPT_BOOLEAN('s', "summary", &sched.summary_only,
		    "Show only syscall summary with statistics"),
	OPT_BOOLEAN('S', "with-summary", &sched.summary,
		    "Show all syscalls and summary with statistics"),
	OPT_BOOLEAN('w', "wakeups", &sched.show_wakeups, "Show wakeup events"),
	OPT_BOOLEAN('n', "next", &sched.show_next, "Show next task"),
	OPT_BOOLEAN('M', "migrations", &sched.show_migrations, "Show migration events"),
	OPT_BOOLEAN('V', "cpu-visual", &sched.show_cpu_visual, "Add CPU visual"),
	OPT_BOOLEAN('I', "idle-hist", &sched.idle_hist, "Show idle events only"),
	OPT_STRING(0, "time", &sched.समय_str, "str",
		   "Time span for analysis (start,stop)"),
	OPT_BOOLEAN(0, "state", &sched.show_state, "Show task state when sched-out"),
	OPT_STRING('p', "pid", &symbol_conf.pid_list_str, "pid[,pid...]",
		   "analyze events only for given process id(s)"),
	OPT_STRING('t', "tid", &symbol_conf.tid_list_str, "tid[,tid...]",
		   "analyze events only for given thread id(s)"),
	OPT_STRING('C', "cpu", &cpu_list, "cpu", "list of cpus to profile"),
	OPT_PARENT(sched_options)
	पूर्ण;

	स्थिर अक्षर * स्थिर latency_usage[] = अणु
		"perf sched latency [<options>]",
		शून्य
	पूर्ण;
	स्थिर अक्षर * स्थिर replay_usage[] = अणु
		"perf sched replay [<options>]",
		शून्य
	पूर्ण;
	स्थिर अक्षर * स्थिर map_usage[] = अणु
		"perf sched map [<options>]",
		शून्य
	पूर्ण;
	स्थिर अक्षर * स्थिर समयhist_usage[] = अणु
		"perf sched timehist [<options>]",
		शून्य
	पूर्ण;
	स्थिर अक्षर *स्थिर sched_subcommands[] = अणु "record", "latency", "map",
						  "replay", "script",
						  "timehist", शून्य पूर्ण;
	स्थिर अक्षर *sched_usage[] = अणु
		शून्य,
		शून्य
	पूर्ण;
	काष्ठा trace_sched_handler lat_ops  = अणु
		.wakeup_event	    = latency_wakeup_event,
		.चयन_event	    = latency_चयन_event,
		.runसमय_event	    = latency_runसमय_event,
		.migrate_task_event = latency_migrate_task_event,
	पूर्ण;
	काष्ठा trace_sched_handler map_ops  = अणु
		.चयन_event	    = map_चयन_event,
	पूर्ण;
	काष्ठा trace_sched_handler replay_ops  = अणु
		.wakeup_event	    = replay_wakeup_event,
		.चयन_event	    = replay_चयन_event,
		.विभाजन_event	    = replay_विभाजन_event,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sched.curr_pid); i++)
		sched.curr_pid[i] = -1;

	argc = parse_options_subcommand(argc, argv, sched_options, sched_subcommands,
					sched_usage, PARSE_OPT_STOP_AT_NON_OPTION);
	अगर (!argc)
		usage_with_options(sched_usage, sched_options);

	/*
	 * Aliased to 'perf script' क्रम now:
	 */
	अगर (!म_भेद(argv[0], "script"))
		वापस cmd_script(argc, argv);

	अगर (!म_भेदन(argv[0], "rec", 3)) अणु
		वापस __cmd_record(argc, argv);
	पूर्ण अन्यथा अगर (!म_भेदन(argv[0], "lat", 3)) अणु
		sched.tp_handler = &lat_ops;
		अगर (argc > 1) अणु
			argc = parse_options(argc, argv, latency_options, latency_usage, 0);
			अगर (argc)
				usage_with_options(latency_usage, latency_options);
		पूर्ण
		setup_sorting(&sched, latency_options, latency_usage);
		वापस perf_sched__lat(&sched);
	पूर्ण अन्यथा अगर (!म_भेद(argv[0], "map")) अणु
		अगर (argc) अणु
			argc = parse_options(argc, argv, map_options, map_usage, 0);
			अगर (argc)
				usage_with_options(map_usage, map_options);
		पूर्ण
		sched.tp_handler = &map_ops;
		setup_sorting(&sched, latency_options, latency_usage);
		वापस perf_sched__map(&sched);
	पूर्ण अन्यथा अगर (!म_भेदन(argv[0], "rep", 3)) अणु
		sched.tp_handler = &replay_ops;
		अगर (argc) अणु
			argc = parse_options(argc, argv, replay_options, replay_usage, 0);
			अगर (argc)
				usage_with_options(replay_usage, replay_options);
		पूर्ण
		वापस perf_sched__replay(&sched);
	पूर्ण अन्यथा अगर (!म_भेद(argv[0], "timehist")) अणु
		अगर (argc) अणु
			argc = parse_options(argc, argv, समयhist_options,
					     समयhist_usage, 0);
			अगर (argc)
				usage_with_options(समयhist_usage, समयhist_options);
		पूर्ण
		अगर ((sched.show_wakeups || sched.show_next) &&
		    sched.summary_only) अणु
			pr_err(" Error: -s and -[n|w] are mutually exclusive.\n");
			parse_options_usage(समयhist_usage, समयhist_options, "s", true);
			अगर (sched.show_wakeups)
				parse_options_usage(शून्य, समयhist_options, "w", true);
			अगर (sched.show_next)
				parse_options_usage(शून्य, समयhist_options, "n", true);
			वापस -EINVAL;
		पूर्ण

		वापस perf_sched__समयhist(&sched);
	पूर्ण अन्यथा अणु
		usage_with_options(sched_usage, sched_options);
	पूर्ण

	वापस 0;
पूर्ण
