<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * numa.c
 *
 * numa: Simulate NUMA-sensitive workload and measure their NUMA perक्रमmance
 */

#समावेश <पूर्णांकtypes.h>
/* For the CLR_() macros */
#समावेश <pthपढ़ो.h>

#समावेश <subcmd/parse-options.h>
#समावेश "../util/cloexec.h"

#समावेश "bench.h"

#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <निश्चित.स>
#समावेश <दो_स्मृति.h>
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/mman.h>
#समावेश <sys/समय.स>
#समावेश <sys/resource.h>
#समावेश <sys/रुको.h>
#समावेश <sys/prctl.h>
#समावेश <sys/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समय64.h>
#समावेश <linux/numa.h>
#समावेश <linux/zभाग.स>

#समावेश <numa.h>
#समावेश <numaअगर.h>

#अगर_अघोषित RUSAGE_THREAD
# define RUSAGE_THREAD 1
#पूर्ण_अगर

/*
 * Regular prपूर्णांकout to the terminal, suppressed अगर -q is specअगरied:
 */
#घोषणा tम_लिखो(x...) करो अणु अगर (g && g->p.show_details >= 0) म_लिखो(x); पूर्ण जबतक (0)

/*
 * Debug म_लिखो:
 */
#अघोषित dम_लिखो
#घोषणा dम_लिखो(x...) करो अणु अगर (g && g->p.show_details >= 1) म_लिखो(x); पूर्ण जबतक (0)

काष्ठा thपढ़ो_data अणु
	पूर्णांक			curr_cpu;
	cpu_set_t		bind_cpumask;
	पूर्णांक			bind_node;
	u8			*process_data;
	पूर्णांक			process_nr;
	पूर्णांक			thपढ़ो_nr;
	पूर्णांक			task_nr;
	अचिन्हित पूर्णांक		loops_करोne;
	u64			val;
	u64			runसमय_ns;
	u64			प्रणाली_समय_ns;
	u64			user_समय_ns;
	द्विगुन			speed_gbs;
	pthपढ़ो_mutex_t		*process_lock;
पूर्ण;

/* Parameters set by options: */

काष्ठा params अणु
	/* Startup synchronization: */
	bool			serialize_startup;

	/* Task hierarchy: */
	पूर्णांक			nr_proc;
	पूर्णांक			nr_thपढ़ोs;

	/* Working set sizes: */
	स्थिर अक्षर		*mb_global_str;
	स्थिर अक्षर		*mb_proc_str;
	स्थिर अक्षर		*mb_proc_locked_str;
	स्थिर अक्षर		*mb_thपढ़ो_str;

	द्विगुन			mb_global;
	द्विगुन			mb_proc;
	द्विगुन			mb_proc_locked;
	द्विगुन			mb_thपढ़ो;

	/* Access patterns to the working set: */
	bool			data_पढ़ोs;
	bool			data_ग_लिखोs;
	bool			data_backwards;
	bool			data_zero_स_रखो;
	bool			data_अक्रम_walk;
	u32			nr_loops;
	u32			nr_secs;
	u32			sleep_usecs;

	/* Working set initialization: */
	bool			init_zero;
	bool			init_अक्रमom;
	bool			init_cpu0;

	/* Misc options: */
	पूर्णांक			show_details;
	पूर्णांक			run_all;
	पूर्णांक			thp;

	दीर्घ			bytes_global;
	दीर्घ			bytes_process;
	दीर्घ			bytes_process_locked;
	दीर्घ			bytes_thपढ़ो;

	पूर्णांक			nr_tasks;
	bool			show_quiet;

	bool			show_convergence;
	bool			measure_convergence;

	पूर्णांक			perturb_secs;
	पूर्णांक			nr_cpus;
	पूर्णांक			nr_nodes;

	/* Affinity options -C and -N: */
	अक्षर			*cpu_list_str;
	अक्षर			*node_list_str;
पूर्ण;


/* Global, पढ़ो-writable area, accessible to all processes and thपढ़ोs: */

काष्ठा global_info अणु
	u8			*data;

	pthपढ़ो_mutex_t		startup_mutex;
	pthपढ़ो_cond_t		startup_cond;
	पूर्णांक			nr_tasks_started;

	pthपढ़ो_mutex_t		start_work_mutex;
	pthपढ़ो_cond_t		start_work_cond;
	पूर्णांक			nr_tasks_working;
	bool			start_work;

	pthपढ़ो_mutex_t		stop_work_mutex;
	u64			bytes_करोne;

	काष्ठा thपढ़ो_data	*thपढ़ोs;

	/* Convergence latency measurement: */
	bool			all_converged;
	bool			stop_work;

	पूर्णांक			prपूर्णांक_once;

	काष्ठा params		p;
पूर्ण;

अटल काष्ठा global_info	*g = शून्य;

अटल पूर्णांक parse_cpus_opt(स्थिर काष्ठा option *opt, स्थिर अक्षर *arg, पूर्णांक unset);
अटल पूर्णांक parse_nodes_opt(स्थिर काष्ठा option *opt, स्थिर अक्षर *arg, पूर्णांक unset);

काष्ठा params p0;

अटल स्थिर काष्ठा option options[] = अणु
	OPT_INTEGER('p', "nr_proc"	, &p0.nr_proc,		"number of processes"),
	OPT_INTEGER('t', "nr_threads"	, &p0.nr_thपढ़ोs,	"number of threads per process"),

	OPT_STRING('G', "mb_global"	, &p0.mb_global_str,	"MB", "global  memory (MBs)"),
	OPT_STRING('P', "mb_proc"	, &p0.mb_proc_str,	"MB", "process memory (MBs)"),
	OPT_STRING('L', "mb_proc_locked", &p0.mb_proc_locked_str,"MB", "process serialized/locked memory access (MBs), <= process_memory"),
	OPT_STRING('T', "mb_thread"	, &p0.mb_thपढ़ो_str,	"MB", "thread  memory (MBs)"),

	OPT_UINTEGER('l', "nr_loops"	, &p0.nr_loops,		"max number of loops to run (default: unlimited)"),
	OPT_UINTEGER('s', "nr_secs"	, &p0.nr_secs,		"max number of seconds to run (default: 5 secs)"),
	OPT_UINTEGER('u', "usleep"	, &p0.sleep_usecs,	"usecs to sleep per loop iteration"),

	OPT_BOOLEAN('R', "data_reads"	, &p0.data_पढ़ोs,	"access the data via reads (can be mixed with -W)"),
	OPT_BOOLEAN('W', "data_writes"	, &p0.data_ग_लिखोs,	"access the data via writes (can be mixed with -R)"),
	OPT_BOOLEAN('B', "data_backwards", &p0.data_backwards,	"access the data backwards as well"),
	OPT_BOOLEAN('Z', "data_zero_memset", &p0.data_zero_स_रखो,"access the data via glibc bzero only"),
	OPT_BOOLEAN('r', "data_rand_walk", &p0.data_अक्रम_walk,	"access the data with random (32bit LFSR) walk"),


	OPT_BOOLEAN('z', "init_zero"	, &p0.init_zero,	"bzero the initial allocations"),
	OPT_BOOLEAN('I', "init_random"	, &p0.init_अक्रमom,	"randomize the contents of the initial allocations"),
	OPT_BOOLEAN('0', "init_cpu0"	, &p0.init_cpu0,	"do the initial allocations on CPU#0"),
	OPT_INTEGER('x', "perturb_secs", &p0.perturb_secs,	"perturb thread 0/0 every X secs, to test convergence stability"),

	OPT_INCR   ('d', "show_details"	, &p0.show_details,	"Show details"),
	OPT_INCR   ('a', "all"		, &p0.run_all,		"Run all tests in the suite"),
	OPT_INTEGER('H', "thp"		, &p0.thp,		"MADV_NOHUGEPAGE < 0 < MADV_HUGEPAGE"),
	OPT_BOOLEAN('c', "show_convergence", &p0.show_convergence, "show convergence details, "
		    "convergence is reached when each process (all its threads) is running on a single NUMA node."),
	OPT_BOOLEAN('m', "measure_convergence",	&p0.measure_convergence, "measure convergence latency"),
	OPT_BOOLEAN('q', "quiet"	, &p0.show_quiet,	"quiet mode"),
	OPT_BOOLEAN('S', "serialize-startup", &p0.serialize_startup,"serialize thread startup"),

	/* Special option string parsing callbacks: */
        OPT_CALLBACK('C', "cpus", शून्य, "cpu[,cpu2,...cpuN]",
			"bind the first N tasks to these specific cpus (the rest is unbound)",
			parse_cpus_opt),
        OPT_CALLBACK('M', "memnodes", शून्य, "node[,node2,...nodeN]",
			"bind the first N tasks to these specific memory nodes (the rest is unbound)",
			parse_nodes_opt),
	OPT_END()
पूर्ण;

अटल स्थिर अक्षर * स्थिर bench_numa_usage[] = अणु
	"perf bench numa <options>",
	शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर numa_usage[] = अणु
	"perf bench numa mem [<options>]",
	शून्य
पूर्ण;

/*
 * To get number of numa nodes present.
 */
अटल पूर्णांक nr_numa_nodes(व्योम)
अणु
	पूर्णांक i, nr_nodes = 0;

	क्रम (i = 0; i < g->p.nr_nodes; i++) अणु
		अगर (numa_biपंचांगask_isbitset(numa_nodes_ptr, i))
			nr_nodes++;
	पूर्ण

	वापस nr_nodes;
पूर्ण

/*
 * To check अगर given numa node is present.
 */
अटल पूर्णांक is_node_present(पूर्णांक node)
अणु
	वापस numa_biपंचांगask_isbitset(numa_nodes_ptr, node);
पूर्ण

/*
 * To check given numa node has cpus.
 */
अटल bool node_has_cpus(पूर्णांक node)
अणु
	काष्ठा biपंचांगask *cpumask = numa_allocate_cpumask();
	bool ret = false; /* fall back to nocpus */
	पूर्णांक cpu;

	BUG_ON(!cpumask);
	अगर (!numa_node_to_cpus(node, cpumask)) अणु
		क्रम (cpu = 0; cpu < (पूर्णांक)cpumask->size; cpu++) अणु
			अगर (numa_biपंचांगask_isbitset(cpumask, cpu)) अणु
				ret = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	numa_मुक्त_cpumask(cpumask);

	वापस ret;
पूर्ण

अटल cpu_set_t bind_to_cpu(पूर्णांक target_cpu)
अणु
	cpu_set_t orig_mask, mask;
	पूर्णांक ret;

	ret = sched_getaffinity(0, माप(orig_mask), &orig_mask);
	BUG_ON(ret);

	CPU_ZERO(&mask);

	अगर (target_cpu == -1) अणु
		पूर्णांक cpu;

		क्रम (cpu = 0; cpu < g->p.nr_cpus; cpu++)
			CPU_SET(cpu, &mask);
	पूर्ण अन्यथा अणु
		BUG_ON(target_cpu < 0 || target_cpu >= g->p.nr_cpus);
		CPU_SET(target_cpu, &mask);
	पूर्ण

	ret = sched_setaffinity(0, माप(mask), &mask);
	BUG_ON(ret);

	वापस orig_mask;
पूर्ण

अटल cpu_set_t bind_to_node(पूर्णांक target_node)
अणु
	cpu_set_t orig_mask, mask;
	पूर्णांक cpu;
	पूर्णांक ret;

	ret = sched_getaffinity(0, माप(orig_mask), &orig_mask);
	BUG_ON(ret);

	CPU_ZERO(&mask);

	अगर (target_node == NUMA_NO_NODE) अणु
		क्रम (cpu = 0; cpu < g->p.nr_cpus; cpu++)
			CPU_SET(cpu, &mask);
	पूर्ण अन्यथा अणु
		काष्ठा biपंचांगask *cpumask = numa_allocate_cpumask();

		BUG_ON(!cpumask);
		अगर (!numa_node_to_cpus(target_node, cpumask)) अणु
			क्रम (cpu = 0; cpu < (पूर्णांक)cpumask->size; cpu++) अणु
				अगर (numa_biपंचांगask_isbitset(cpumask, cpu))
					CPU_SET(cpu, &mask);
			पूर्ण
		पूर्ण
		numa_मुक्त_cpumask(cpumask);
	पूर्ण

	ret = sched_setaffinity(0, माप(mask), &mask);
	BUG_ON(ret);

	वापस orig_mask;
पूर्ण

अटल व्योम bind_to_cpumask(cpu_set_t mask)
अणु
	पूर्णांक ret;

	ret = sched_setaffinity(0, माप(mask), &mask);
	BUG_ON(ret);
पूर्ण

अटल व्योम mempol_restore(व्योम)
अणु
	पूर्णांक ret;

	ret = set_mempolicy(MPOL_DEFAULT, शून्य, g->p.nr_nodes-1);

	BUG_ON(ret);
पूर्ण

अटल व्योम bind_to_memnode(पूर्णांक node)
अणु
	काष्ठा biपंचांगask *node_mask;
	पूर्णांक ret;

	अगर (node == NUMA_NO_NODE)
		वापस;

	node_mask = numa_allocate_nodemask();
	BUG_ON(!node_mask);

	numa_biपंचांगask_clearall(node_mask);
	numa_biपंचांगask_setbit(node_mask, node);

	ret = set_mempolicy(MPOL_BIND, node_mask->maskp, node_mask->size + 1);
	dम_लिखो("binding to node %d, mask: %016lx => %d\n", node, *node_mask->maskp, ret);

	numa_biपंचांगask_मुक्त(node_mask);
	BUG_ON(ret);
पूर्ण

#घोषणा HPSIZE (2*1024*1024)

#घोषणा set_taskname(fmt...)				\
करो अणु							\
	अक्षर name[20];					\
							\
	snम_लिखो(name, 20, fmt);			\
	prctl(PR_SET_NAME, name);			\
पूर्ण जबतक (0)

अटल u8 *alloc_data(sमाप_प्रकार bytes0, पूर्णांक map_flags,
		      पूर्णांक init_zero, पूर्णांक init_cpu0, पूर्णांक thp, पूर्णांक init_अक्रमom)
अणु
	cpu_set_t orig_mask;
	sमाप_प्रकार bytes;
	u8 *buf;
	पूर्णांक ret;

	अगर (!bytes0)
		वापस शून्य;

	/* Allocate and initialize all memory on CPU#0: */
	अगर (init_cpu0) अणु
		पूर्णांक node = numa_node_of_cpu(0);

		orig_mask = bind_to_node(node);
		bind_to_memnode(node);
	पूर्ण

	bytes = bytes0 + HPSIZE;

	buf = (व्योम *)mmap(0, bytes, PROT_READ|PROT_WRITE, MAP_ANON|map_flags, -1, 0);
	BUG_ON(buf == (व्योम *)-1);

	अगर (map_flags == MAP_PRIVATE) अणु
		अगर (thp > 0) अणु
			ret = madvise(buf, bytes, MADV_HUGEPAGE);
			अगर (ret && !g->prपूर्णांक_once) अणु
				g->prपूर्णांक_once = 1;
				म_लिखो("WARNING: Could not enable THP - do: 'echo madvise > /sys/kernel/mm/transparent_hugepage/enabled'\n");
			पूर्ण
		पूर्ण
		अगर (thp < 0) अणु
			ret = madvise(buf, bytes, MADV_NOHUGEPAGE);
			अगर (ret && !g->prपूर्णांक_once) अणु
				g->prपूर्णांक_once = 1;
				म_लिखो("WARNING: Could not disable THP: run a CONFIG_TRANSPARENT_HUGEPAGE kernel?\n");
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (init_zero) अणु
		bzero(buf, bytes);
	पूर्ण अन्यथा अणु
		/* Initialize अक्रमom contents, dअगरferent in each word: */
		अगर (init_अक्रमom) अणु
			u64 *wbuf = (व्योम *)buf;
			दीर्घ off = अक्रम();
			दीर्घ i;

			क्रम (i = 0; i < bytes/8; i++)
				wbuf[i] = i + off;
		पूर्ण
	पूर्ण

	/* Align to 2MB boundary: */
	buf = (व्योम *)(((अचिन्हित दीर्घ)buf + HPSIZE-1) & ~(HPSIZE-1));

	/* Restore affinity: */
	अगर (init_cpu0) अणु
		bind_to_cpumask(orig_mask);
		mempol_restore();
	पूर्ण

	वापस buf;
पूर्ण

अटल व्योम मुक्त_data(व्योम *data, sमाप_प्रकार bytes)
अणु
	पूर्णांक ret;

	अगर (!data)
		वापस;

	ret = munmap(data, bytes);
	BUG_ON(ret);
पूर्ण

/*
 * Create a shared memory buffer that can be shared between processes, zeroed:
 */
अटल व्योम * zalloc_shared_data(sमाप_प्रकार bytes)
अणु
	वापस alloc_data(bytes, MAP_SHARED, 1, g->p.init_cpu0,  g->p.thp, g->p.init_अक्रमom);
पूर्ण

/*
 * Create a shared memory buffer that can be shared between processes:
 */
अटल व्योम * setup_shared_data(sमाप_प्रकार bytes)
अणु
	वापस alloc_data(bytes, MAP_SHARED, 0, g->p.init_cpu0,  g->p.thp, g->p.init_अक्रमom);
पूर्ण

/*
 * Allocate process-local memory - this will either be shared between
 * thपढ़ोs of this process, or only be accessed by this thपढ़ो:
 */
अटल व्योम * setup_निजी_data(sमाप_प्रकार bytes)
अणु
	वापस alloc_data(bytes, MAP_PRIVATE, 0, g->p.init_cpu0,  g->p.thp, g->p.init_अक्रमom);
पूर्ण

/*
 * Return a process-shared (global) mutex:
 */
अटल व्योम init_global_mutex(pthपढ़ो_mutex_t *mutex)
अणु
	pthपढ़ो_mutexattr_t attr;

	pthपढ़ो_mutexattr_init(&attr);
	pthपढ़ो_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
	pthपढ़ो_mutex_init(mutex, &attr);
पूर्ण

/*
 * Return a process-shared (global) condition variable:
 */
अटल व्योम init_global_cond(pthपढ़ो_cond_t *cond)
अणु
	pthपढ़ो_condattr_t attr;

	pthपढ़ो_condattr_init(&attr);
	pthपढ़ो_condattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
	pthपढ़ो_cond_init(cond, &attr);
पूर्ण

अटल पूर्णांक parse_cpu_list(स्थिर अक्षर *arg)
अणु
	p0.cpu_list_str = strdup(arg);

	dम_लिखो("got CPU list: {%s}\n", p0.cpu_list_str);

	वापस 0;
पूर्ण

अटल पूर्णांक parse_setup_cpu_list(व्योम)
अणु
	काष्ठा thपढ़ो_data *td;
	अक्षर *str0, *str;
	पूर्णांक t;

	अगर (!g->p.cpu_list_str)
		वापस 0;

	dम_लिखो("g->p.nr_tasks: %d\n", g->p.nr_tasks);

	str0 = str = strdup(g->p.cpu_list_str);
	t = 0;

	BUG_ON(!str);

	tम_लिखो("# binding tasks to CPUs:\n");
	tम_लिखो("#  ");

	जबतक (true) अणु
		पूर्णांक bind_cpu, bind_cpu_0, bind_cpu_1;
		अक्षर *tok, *tok_end, *tok_step, *tok_len, *tok_mul;
		पूर्णांक bind_len;
		पूर्णांक step;
		पूर्णांक mul;

		tok = strsep(&str, ",");
		अगर (!tok)
			अवरोध;

		tok_end = म_माला(tok, "-");

		dम_लिखो("\ntoken: {%s}, end: {%s}\n", tok, tok_end);
		अगर (!tok_end) अणु
			/* Single CPU specअगरied: */
			bind_cpu_0 = bind_cpu_1 = म_से_द(tok);
		पूर्ण अन्यथा अणु
			/* CPU range specअगरied (क्रम example: "5-11"): */
			bind_cpu_0 = म_से_द(tok);
			bind_cpu_1 = म_से_द(tok_end + 1);
		पूर्ण

		step = 1;
		tok_step = म_माला(tok, "#");
		अगर (tok_step) अणु
			step = म_से_द(tok_step + 1);
			BUG_ON(step <= 0 || step >= g->p.nr_cpus);
		पूर्ण

		/*
		 * Mask length.
		 * Eg: "--cpus 8_4-16#4" means: '--cpus 8_4,12_4,16_4',
		 * where the _4 means the next 4 CPUs are allowed.
		 */
		bind_len = 1;
		tok_len = म_माला(tok, "_");
		अगर (tok_len) अणु
			bind_len = म_से_द(tok_len + 1);
			BUG_ON(bind_len <= 0 || bind_len > g->p.nr_cpus);
		पूर्ण

		/* Multiplicator लघुcut, "0x8" is a लघुcut क्रम: "0,0,0,0,0,0,0,0" */
		mul = 1;
		tok_mul = म_माला(tok, "x");
		अगर (tok_mul) अणु
			mul = म_से_द(tok_mul + 1);
			BUG_ON(mul <= 0);
		पूर्ण

		dम_लिखो("CPUs: %d_%d-%d#%dx%d\n", bind_cpu_0, bind_len, bind_cpu_1, step, mul);

		अगर (bind_cpu_0 >= g->p.nr_cpus || bind_cpu_1 >= g->p.nr_cpus) अणु
			म_लिखो("\nTest not applicable, system has only %d CPUs.\n", g->p.nr_cpus);
			वापस -1;
		पूर्ण

		BUG_ON(bind_cpu_0 < 0 || bind_cpu_1 < 0);
		BUG_ON(bind_cpu_0 > bind_cpu_1);

		क्रम (bind_cpu = bind_cpu_0; bind_cpu <= bind_cpu_1; bind_cpu += step) अणु
			पूर्णांक i;

			क्रम (i = 0; i < mul; i++) अणु
				पूर्णांक cpu;

				अगर (t >= g->p.nr_tasks) अणु
					म_लिखो("\n# NOTE: ignoring bind CPUs starting at CPU#%d\n #", bind_cpu);
					जाओ out;
				पूर्ण
				td = g->thपढ़ोs + t;

				अगर (t)
					tम_लिखो(",");
				अगर (bind_len > 1) अणु
					tम_लिखो("%2d/%d", bind_cpu, bind_len);
				पूर्ण अन्यथा अणु
					tम_लिखो("%2d", bind_cpu);
				पूर्ण

				CPU_ZERO(&td->bind_cpumask);
				क्रम (cpu = bind_cpu; cpu < bind_cpu+bind_len; cpu++) अणु
					BUG_ON(cpu < 0 || cpu >= g->p.nr_cpus);
					CPU_SET(cpu, &td->bind_cpumask);
				पूर्ण
				t++;
			पूर्ण
		पूर्ण
	पूर्ण
out:

	tम_लिखो("\n");

	अगर (t < g->p.nr_tasks)
		म_लिखो("# NOTE: %d tasks bound, %d tasks unbound\n", t, g->p.nr_tasks - t);

	मुक्त(str0);
	वापस 0;
पूर्ण

अटल पूर्णांक parse_cpus_opt(स्थिर काष्ठा option *opt __maybe_unused,
			  स्थिर अक्षर *arg, पूर्णांक unset __maybe_unused)
अणु
	अगर (!arg)
		वापस -1;

	वापस parse_cpu_list(arg);
पूर्ण

अटल पूर्णांक parse_node_list(स्थिर अक्षर *arg)
अणु
	p0.node_list_str = strdup(arg);

	dम_लिखो("got NODE list: {%s}\n", p0.node_list_str);

	वापस 0;
पूर्ण

अटल पूर्णांक parse_setup_node_list(व्योम)
अणु
	काष्ठा thपढ़ो_data *td;
	अक्षर *str0, *str;
	पूर्णांक t;

	अगर (!g->p.node_list_str)
		वापस 0;

	dम_लिखो("g->p.nr_tasks: %d\n", g->p.nr_tasks);

	str0 = str = strdup(g->p.node_list_str);
	t = 0;

	BUG_ON(!str);

	tम_लिखो("# binding tasks to NODEs:\n");
	tम_लिखो("# ");

	जबतक (true) अणु
		पूर्णांक bind_node, bind_node_0, bind_node_1;
		अक्षर *tok, *tok_end, *tok_step, *tok_mul;
		पूर्णांक step;
		पूर्णांक mul;

		tok = strsep(&str, ",");
		अगर (!tok)
			अवरोध;

		tok_end = म_माला(tok, "-");

		dम_लिखो("\ntoken: {%s}, end: {%s}\n", tok, tok_end);
		अगर (!tok_end) अणु
			/* Single NODE specअगरied: */
			bind_node_0 = bind_node_1 = म_से_द(tok);
		पूर्ण अन्यथा अणु
			/* NODE range specअगरied (क्रम example: "5-11"): */
			bind_node_0 = म_से_द(tok);
			bind_node_1 = म_से_द(tok_end + 1);
		पूर्ण

		step = 1;
		tok_step = म_माला(tok, "#");
		अगर (tok_step) अणु
			step = म_से_द(tok_step + 1);
			BUG_ON(step <= 0 || step >= g->p.nr_nodes);
		पूर्ण

		/* Multiplicator लघुcut, "0x8" is a लघुcut क्रम: "0,0,0,0,0,0,0,0" */
		mul = 1;
		tok_mul = म_माला(tok, "x");
		अगर (tok_mul) अणु
			mul = म_से_द(tok_mul + 1);
			BUG_ON(mul <= 0);
		पूर्ण

		dम_लिखो("NODEs: %d-%d #%d\n", bind_node_0, bind_node_1, step);

		अगर (bind_node_0 >= g->p.nr_nodes || bind_node_1 >= g->p.nr_nodes) अणु
			म_लिखो("\nTest not applicable, system has only %d nodes.\n", g->p.nr_nodes);
			वापस -1;
		पूर्ण

		BUG_ON(bind_node_0 < 0 || bind_node_1 < 0);
		BUG_ON(bind_node_0 > bind_node_1);

		क्रम (bind_node = bind_node_0; bind_node <= bind_node_1; bind_node += step) अणु
			पूर्णांक i;

			क्रम (i = 0; i < mul; i++) अणु
				अगर (t >= g->p.nr_tasks || !node_has_cpus(bind_node)) अणु
					म_लिखो("\n# NOTE: ignoring bind NODEs starting at NODE#%d\n", bind_node);
					जाओ out;
				पूर्ण
				td = g->thपढ़ोs + t;

				अगर (!t)
					tम_लिखो(" %2d", bind_node);
				अन्यथा
					tम_लिखो(",%2d", bind_node);

				td->bind_node = bind_node;
				t++;
			पूर्ण
		पूर्ण
	पूर्ण
out:

	tम_लिखो("\n");

	अगर (t < g->p.nr_tasks)
		म_लिखो("# NOTE: %d tasks mem-bound, %d tasks unbound\n", t, g->p.nr_tasks - t);

	मुक्त(str0);
	वापस 0;
पूर्ण

अटल पूर्णांक parse_nodes_opt(स्थिर काष्ठा option *opt __maybe_unused,
			  स्थिर अक्षर *arg, पूर्णांक unset __maybe_unused)
अणु
	अगर (!arg)
		वापस -1;

	वापस parse_node_list(arg);
पूर्ण

#घोषणा BIT(x) (1ul << x)

अटल अंतरभूत uपूर्णांक32_t lfsr_32(uपूर्णांक32_t lfsr)
अणु
	स्थिर uपूर्णांक32_t taps = BIT(1) | BIT(5) | BIT(6) | BIT(31);
	वापस (lfsr>>1) ^ ((0x0u - (lfsr & 0x1u)) & taps);
पूर्ण

/*
 * Make sure there's real data dependency to RAM (when पढ़ो
 * accesses are enabled), so the compiler, the CPU and the
 * kernel (KSM, zero page, etc.) cannot optimize away RAM
 * accesses:
 */
अटल अंतरभूत u64 access_data(u64 *data, u64 val)
अणु
	अगर (g->p.data_पढ़ोs)
		val += *data;
	अगर (g->p.data_ग_लिखोs)
		*data = val + 1;
	वापस val;
पूर्ण

/*
 * The worker process करोes two types of work, a क्रमwards going
 * loop and a backwards going loop.
 *
 * We करो this so that on multiprocessor प्रणालीs we करो not create
 * a 'train' of processing, with highly synchronized processes,
 * skewing the whole benchmark.
 */
अटल u64 करो_work(u8 *__data, दीर्घ bytes, पूर्णांक nr, पूर्णांक nr_max, पूर्णांक loop, u64 val)
अणु
	दीर्घ words = bytes/माप(u64);
	u64 *data = (व्योम *)__data;
	दीर्घ chunk_0, chunk_1;
	u64 *d0, *d, *d1;
	दीर्घ off;
	दीर्घ i;

	BUG_ON(!data && words);
	BUG_ON(data && !words);

	अगर (!data)
		वापस val;

	/* Very simple स_रखो() work variant: */
	अगर (g->p.data_zero_स_रखो && !g->p.data_अक्रम_walk) अणु
		bzero(data, bytes);
		वापस val;
	पूर्ण

	/* Spपढ़ो out by PID/TID nr and by loop nr: */
	chunk_0 = words/nr_max;
	chunk_1 = words/g->p.nr_loops;
	off = nr*chunk_0 + loop*chunk_1;

	जबतक (off >= words)
		off -= words;

	अगर (g->p.data_अक्रम_walk) अणु
		u32 lfsr = nr + loop + val;
		पूर्णांक j;

		क्रम (i = 0; i < words/1024; i++) अणु
			दीर्घ start, end;

			lfsr = lfsr_32(lfsr);

			start = lfsr % words;
			end = min(start + 1024, words-1);

			अगर (g->p.data_zero_स_रखो) अणु
				bzero(data + start, (end-start) * माप(u64));
			पूर्ण अन्यथा अणु
				क्रम (j = start; j < end; j++)
					val = access_data(data + j, val);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (!g->p.data_backwards || (nr + loop) & 1) अणु
		/* Process data क्रमwards: */

		d0 = data + off;
		d  = data + off + 1;
		d1 = data + words;

		क्रम (;;) अणु
			अगर (unlikely(d >= d1))
				d = data;
			अगर (unlikely(d == d0))
				अवरोध;

			val = access_data(d, val);

			d++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Process data backwards: */

		d0 = data + off;
		d  = data + off - 1;
		d1 = data + words;

		क्रम (;;) अणु
			अगर (unlikely(d < data))
				d = data + words-1;
			अगर (unlikely(d == d0))
				अवरोध;

			val = access_data(d, val);

			d--;
		पूर्ण
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम update_curr_cpu(पूर्णांक task_nr, अचिन्हित दीर्घ bytes_worked)
अणु
	अचिन्हित पूर्णांक cpu;

	cpu = sched_अ_लोpu();

	g->thपढ़ोs[task_nr].curr_cpu = cpu;
	prctl(0, bytes_worked);
पूर्ण

/*
 * Count the number of nodes a process's thपढ़ोs
 * are spपढ़ो out on.
 *
 * A count of 1 means that the process is compressed
 * to a single node. A count of g->p.nr_nodes means it's
 * spपढ़ो out on the whole प्रणाली.
 */
अटल पूर्णांक count_process_nodes(पूर्णांक process_nr)
अणु
	अक्षर *node_present;
	पूर्णांक nodes;
	पूर्णांक n, t;

	node_present = (अक्षर *)दो_स्मृति(g->p.nr_nodes * माप(अक्षर));
	BUG_ON(!node_present);
	क्रम (nodes = 0; nodes < g->p.nr_nodes; nodes++)
		node_present[nodes] = 0;

	क्रम (t = 0; t < g->p.nr_thपढ़ोs; t++) अणु
		काष्ठा thपढ़ो_data *td;
		पूर्णांक task_nr;
		पूर्णांक node;

		task_nr = process_nr*g->p.nr_thपढ़ोs + t;
		td = g->thपढ़ोs + task_nr;

		node = numa_node_of_cpu(td->curr_cpu);
		अगर (node < 0) /* curr_cpu was likely still -1 */ अणु
			मुक्त(node_present);
			वापस 0;
		पूर्ण

		node_present[node] = 1;
	पूर्ण

	nodes = 0;

	क्रम (n = 0; n < g->p.nr_nodes; n++)
		nodes += node_present[n];

	मुक्त(node_present);
	वापस nodes;
पूर्ण

/*
 * Count the number of distinct process-thपढ़ोs a node contains.
 *
 * A count of 1 means that the node contains only a single
 * process. If all nodes on the प्रणाली contain at most one
 * process then we are well-converged.
 */
अटल पूर्णांक count_node_processes(पूर्णांक node)
अणु
	पूर्णांक processes = 0;
	पूर्णांक t, p;

	क्रम (p = 0; p < g->p.nr_proc; p++) अणु
		क्रम (t = 0; t < g->p.nr_thपढ़ोs; t++) अणु
			काष्ठा thपढ़ो_data *td;
			पूर्णांक task_nr;
			पूर्णांक n;

			task_nr = p*g->p.nr_thपढ़ोs + t;
			td = g->thपढ़ोs + task_nr;

			n = numa_node_of_cpu(td->curr_cpu);
			अगर (n == node) अणु
				processes++;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस processes;
पूर्ण

अटल व्योम calc_convergence_compression(पूर्णांक *strong)
अणु
	अचिन्हित पूर्णांक nodes_min, nodes_max;
	पूर्णांक p;

	nodes_min = -1;
	nodes_max =  0;

	क्रम (p = 0; p < g->p.nr_proc; p++) अणु
		अचिन्हित पूर्णांक nodes = count_process_nodes(p);

		अगर (!nodes) अणु
			*strong = 0;
			वापस;
		पूर्ण

		nodes_min = min(nodes, nodes_min);
		nodes_max = max(nodes, nodes_max);
	पूर्ण

	/* Strong convergence: all thपढ़ोs compress on a single node: */
	अगर (nodes_min == 1 && nodes_max == 1) अणु
		*strong = 1;
	पूर्ण अन्यथा अणु
		*strong = 0;
		tम_लिखो(" {%d-%d}", nodes_min, nodes_max);
	पूर्ण
पूर्ण

अटल व्योम calc_convergence(द्विगुन runसमय_ns_max, द्विगुन *convergence)
अणु
	अचिन्हित पूर्णांक loops_करोne_min, loops_करोne_max;
	पूर्णांक process_groups;
	पूर्णांक *nodes;
	पूर्णांक distance;
	पूर्णांक nr_min;
	पूर्णांक nr_max;
	पूर्णांक strong;
	पूर्णांक sum;
	पूर्णांक nr;
	पूर्णांक node;
	पूर्णांक cpu;
	पूर्णांक t;

	अगर (!g->p.show_convergence && !g->p.measure_convergence)
		वापस;

	nodes = (पूर्णांक *)दो_स्मृति(g->p.nr_nodes * माप(पूर्णांक));
	BUG_ON(!nodes);
	क्रम (node = 0; node < g->p.nr_nodes; node++)
		nodes[node] = 0;

	loops_करोne_min = -1;
	loops_करोne_max = 0;

	क्रम (t = 0; t < g->p.nr_tasks; t++) अणु
		काष्ठा thपढ़ो_data *td = g->thपढ़ोs + t;
		अचिन्हित पूर्णांक loops_करोne;

		cpu = td->curr_cpu;

		/* Not all thपढ़ोs have written it yet: */
		अगर (cpu < 0)
			जारी;

		node = numa_node_of_cpu(cpu);

		nodes[node]++;

		loops_करोne = td->loops_करोne;
		loops_करोne_min = min(loops_करोne, loops_करोne_min);
		loops_करोne_max = max(loops_करोne, loops_करोne_max);
	पूर्ण

	nr_max = 0;
	nr_min = g->p.nr_tasks;
	sum = 0;

	क्रम (node = 0; node < g->p.nr_nodes; node++) अणु
		अगर (!is_node_present(node))
			जारी;
		nr = nodes[node];
		nr_min = min(nr, nr_min);
		nr_max = max(nr, nr_max);
		sum += nr;
	पूर्ण
	BUG_ON(nr_min > nr_max);

	BUG_ON(sum > g->p.nr_tasks);

	अगर (0 && (sum < g->p.nr_tasks)) अणु
		मुक्त(nodes);
		वापस;
	पूर्ण

	/*
	 * Count the number of distinct process groups present
	 * on nodes - when we are converged this will decrease
	 * to g->p.nr_proc:
	 */
	process_groups = 0;

	क्रम (node = 0; node < g->p.nr_nodes; node++) अणु
		पूर्णांक processes;

		अगर (!is_node_present(node))
			जारी;
		processes = count_node_processes(node);
		nr = nodes[node];
		tम_लिखो(" %2d/%-2d", nr, processes);

		process_groups += processes;
	पूर्ण

	distance = nr_max - nr_min;

	tम_लिखो(" [%2d/%-2d]", distance, process_groups);

	tम_लिखो(" l:%3d-%-3d (%3d)",
		loops_करोne_min, loops_करोne_max, loops_करोne_max-loops_करोne_min);

	अगर (loops_करोne_min && loops_करोne_max) अणु
		द्विगुन skew = 1.0 - (द्विगुन)loops_करोne_min/loops_करोne_max;

		tम_लिखो(" [%4.1f%%]", skew * 100.0);
	पूर्ण

	calc_convergence_compression(&strong);

	अगर (strong && process_groups == g->p.nr_proc) अणु
		अगर (!*convergence) अणु
			*convergence = runसमय_ns_max;
			tम_लिखो(" (%6.1fs converged)\n", *convergence / NSEC_PER_SEC);
			अगर (g->p.measure_convergence) अणु
				g->all_converged = true;
				g->stop_work = true;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (*convergence) अणु
			tम_लिखो(" (%6.1fs de-converged)", runसमय_ns_max / NSEC_PER_SEC);
			*convergence = 0;
		पूर्ण
		tम_लिखो("\n");
	पूर्ण

	मुक्त(nodes);
पूर्ण

अटल व्योम show_summary(द्विगुन runसमय_ns_max, पूर्णांक l, द्विगुन *convergence)
अणु
	tम_लिखो("\r #  %5.1f%%  [%.1f mins]",
		(द्विगुन)(l+1)/g->p.nr_loops*100.0, runसमय_ns_max / NSEC_PER_SEC / 60.0);

	calc_convergence(runसमय_ns_max, convergence);

	अगर (g->p.show_details >= 0)
		ख_साफ(मानक_निकास);
पूर्ण

अटल व्योम *worker_thपढ़ो(व्योम *__tdata)
अणु
	काष्ठा thपढ़ो_data *td = __tdata;
	काष्ठा समयval start0, start, stop, dअगरf;
	पूर्णांक process_nr = td->process_nr;
	पूर्णांक thपढ़ो_nr = td->thपढ़ो_nr;
	अचिन्हित दीर्घ last_perturbance;
	पूर्णांक task_nr = td->task_nr;
	पूर्णांक details = g->p.show_details;
	पूर्णांक first_task, last_task;
	द्विगुन convergence = 0;
	u64 val = td->val;
	द्विगुन runसमय_ns_max;
	u8 *global_data;
	u8 *process_data;
	u8 *thपढ़ो_data;
	u64 bytes_करोne, secs;
	दीर्घ work_करोne;
	u32 l;
	काष्ठा rusage rusage;

	bind_to_cpumask(td->bind_cpumask);
	bind_to_memnode(td->bind_node);

	set_taskname("thread %d/%d", process_nr, thपढ़ो_nr);

	global_data = g->data;
	process_data = td->process_data;
	thपढ़ो_data = setup_निजी_data(g->p.bytes_thपढ़ो);

	bytes_करोne = 0;

	last_task = 0;
	अगर (process_nr == g->p.nr_proc-1 && thपढ़ो_nr == g->p.nr_thपढ़ोs-1)
		last_task = 1;

	first_task = 0;
	अगर (process_nr == 0 && thपढ़ो_nr == 0)
		first_task = 1;

	अगर (details >= 2) अणु
		म_लिखो("#  thread %2d / %2d global mem: %p, process mem: %p, thread mem: %p\n",
			process_nr, thपढ़ो_nr, global_data, process_data, thपढ़ो_data);
	पूर्ण

	अगर (g->p.serialize_startup) अणु
		pthपढ़ो_mutex_lock(&g->startup_mutex);
		g->nr_tasks_started++;
		/* The last thपढ़ो wakes the मुख्य process. */
		अगर (g->nr_tasks_started == g->p.nr_tasks)
			pthपढ़ो_cond_संकेत(&g->startup_cond);

		pthपढ़ो_mutex_unlock(&g->startup_mutex);

		/* Here we will रुको क्रम the मुख्य process to start us all at once: */
		pthपढ़ो_mutex_lock(&g->start_work_mutex);
		g->start_work = false;
		g->nr_tasks_working++;
		जबतक (!g->start_work)
			pthपढ़ो_cond_रुको(&g->start_work_cond, &g->start_work_mutex);

		pthपढ़ो_mutex_unlock(&g->start_work_mutex);
	पूर्ण

	समय_लोofday(&start0, शून्य);

	start = stop = start0;
	last_perturbance = start.tv_sec;

	क्रम (l = 0; l < g->p.nr_loops; l++) अणु
		start = stop;

		अगर (g->stop_work)
			अवरोध;

		val += करो_work(global_data,  g->p.bytes_global,  process_nr, g->p.nr_proc,	l, val);
		val += करो_work(process_data, g->p.bytes_process, thपढ़ो_nr,  g->p.nr_thपढ़ोs,	l, val);
		val += करो_work(thपढ़ो_data,  g->p.bytes_thपढ़ो,  0,          1,		l, val);

		अगर (g->p.sleep_usecs) अणु
			pthपढ़ो_mutex_lock(td->process_lock);
			usleep(g->p.sleep_usecs);
			pthपढ़ो_mutex_unlock(td->process_lock);
		पूर्ण
		/*
		 * Amount of work to be करोne under a process-global lock:
		 */
		अगर (g->p.bytes_process_locked) अणु
			pthपढ़ो_mutex_lock(td->process_lock);
			val += करो_work(process_data, g->p.bytes_process_locked, thपढ़ो_nr,  g->p.nr_thपढ़ोs,	l, val);
			pthपढ़ो_mutex_unlock(td->process_lock);
		पूर्ण

		work_करोne = g->p.bytes_global + g->p.bytes_process +
			    g->p.bytes_process_locked + g->p.bytes_thपढ़ो;

		update_curr_cpu(task_nr, work_करोne);
		bytes_करोne += work_करोne;

		अगर (details < 0 && !g->p.perturb_secs && !g->p.measure_convergence && !g->p.nr_secs)
			जारी;

		td->loops_करोne = l;

		समय_लोofday(&stop, शून्य);

		/* Check whether our max runसमय समयd out: */
		अगर (g->p.nr_secs) अणु
			समयrsub(&stop, &start0, &dअगरf);
			अगर ((u32)dअगरf.tv_sec >= g->p.nr_secs) अणु
				g->stop_work = true;
				अवरोध;
			पूर्ण
		पूर्ण

		/* Update the summary at most once per second: */
		अगर (start.tv_sec == stop.tv_sec)
			जारी;

		/*
		 * Perturb the first task's equilibrium every g->p.perturb_secs seconds,
		 * by migrating to CPU#0:
		 */
		अगर (first_task && g->p.perturb_secs && (पूर्णांक)(stop.tv_sec - last_perturbance) >= g->p.perturb_secs) अणु
			cpu_set_t orig_mask;
			पूर्णांक target_cpu;
			पूर्णांक this_cpu;

			last_perturbance = stop.tv_sec;

			/*
			 * Depending on where we are running, move पूर्णांकo
			 * the other half of the प्रणाली, to create some
			 * real disturbance:
			 */
			this_cpu = g->thपढ़ोs[task_nr].curr_cpu;
			अगर (this_cpu < g->p.nr_cpus/2)
				target_cpu = g->p.nr_cpus-1;
			अन्यथा
				target_cpu = 0;

			orig_mask = bind_to_cpu(target_cpu);

			/* Here we are running on the target CPU alपढ़ोy */
			अगर (details >= 1)
				म_लिखो(" (injecting perturbalance, moved to CPU#%d)\n", target_cpu);

			bind_to_cpumask(orig_mask);
		पूर्ण

		अगर (details >= 3) अणु
			समयrsub(&stop, &start, &dअगरf);
			runसमय_ns_max = dअगरf.tv_sec * NSEC_PER_SEC;
			runसमय_ns_max += dअगरf.tv_usec * NSEC_PER_USEC;

			अगर (details >= 0) अणु
				म_लिखो(" #%2d / %2d: %14.2lf nsecs/op [val: %016"PRIx64"]\n",
					process_nr, thपढ़ो_nr, runसमय_ns_max / bytes_करोne, val);
			पूर्ण
			ख_साफ(मानक_निकास);
		पूर्ण
		अगर (!last_task)
			जारी;

		समयrsub(&stop, &start0, &dअगरf);
		runसमय_ns_max = dअगरf.tv_sec * NSEC_PER_SEC;
		runसमय_ns_max += dअगरf.tv_usec * NSEC_PER_USEC;

		show_summary(runसमय_ns_max, l, &convergence);
	पूर्ण

	समय_लोofday(&stop, शून्य);
	समयrsub(&stop, &start0, &dअगरf);
	td->runसमय_ns = dअगरf.tv_sec * NSEC_PER_SEC;
	td->runसमय_ns += dअगरf.tv_usec * NSEC_PER_USEC;
	secs = td->runसमय_ns / NSEC_PER_SEC;
	td->speed_gbs = secs ? bytes_करोne / secs / 1e9 : 0;

	getrusage(RUSAGE_THREAD, &rusage);
	td->प्रणाली_समय_ns = rusage.ru_sसमय.tv_sec * NSEC_PER_SEC;
	td->प्रणाली_समय_ns += rusage.ru_sसमय.tv_usec * NSEC_PER_USEC;
	td->user_समय_ns = rusage.ru_uसमय.tv_sec * NSEC_PER_SEC;
	td->user_समय_ns += rusage.ru_uसमय.tv_usec * NSEC_PER_USEC;

	मुक्त_data(thपढ़ो_data, g->p.bytes_thपढ़ो);

	pthपढ़ो_mutex_lock(&g->stop_work_mutex);
	g->bytes_करोne += bytes_करोne;
	pthपढ़ो_mutex_unlock(&g->stop_work_mutex);

	वापस शून्य;
पूर्ण

/*
 * A worker process starts a couple of thपढ़ोs:
 */
अटल व्योम worker_process(पूर्णांक process_nr)
अणु
	pthपढ़ो_mutex_t process_lock;
	काष्ठा thपढ़ो_data *td;
	pthपढ़ो_t *pthपढ़ोs;
	u8 *process_data;
	पूर्णांक task_nr;
	पूर्णांक ret;
	पूर्णांक t;

	pthपढ़ो_mutex_init(&process_lock, शून्य);
	set_taskname("process %d", process_nr);

	/*
	 * Pick up the memory policy and the CPU binding of our first thपढ़ो,
	 * so that we initialize memory accordingly:
	 */
	task_nr = process_nr*g->p.nr_thपढ़ोs;
	td = g->thपढ़ोs + task_nr;

	bind_to_memnode(td->bind_node);
	bind_to_cpumask(td->bind_cpumask);

	pthपढ़ोs = zalloc(g->p.nr_thपढ़ोs * माप(pthपढ़ो_t));
	process_data = setup_निजी_data(g->p.bytes_process);

	अगर (g->p.show_details >= 3) अणु
		म_लिखो(" # process %2d global mem: %p, process mem: %p\n",
			process_nr, g->data, process_data);
	पूर्ण

	क्रम (t = 0; t < g->p.nr_thपढ़ोs; t++) अणु
		task_nr = process_nr*g->p.nr_thपढ़ोs + t;
		td = g->thपढ़ोs + task_nr;

		td->process_data = process_data;
		td->process_nr   = process_nr;
		td->thपढ़ो_nr    = t;
		td->task_nr	 = task_nr;
		td->val          = अक्रम();
		td->curr_cpu	 = -1;
		td->process_lock = &process_lock;

		ret = pthपढ़ो_create(pthपढ़ोs + t, शून्य, worker_thपढ़ो, td);
		BUG_ON(ret);
	पूर्ण

	क्रम (t = 0; t < g->p.nr_thपढ़ोs; t++) अणु
                ret = pthपढ़ो_join(pthपढ़ोs[t], शून्य);
		BUG_ON(ret);
	पूर्ण

	मुक्त_data(process_data, g->p.bytes_process);
	मुक्त(pthपढ़ोs);
पूर्ण

अटल व्योम prपूर्णांक_summary(व्योम)
अणु
	अगर (g->p.show_details < 0)
		वापस;

	म_लिखो("\n ###\n");
	म_लिखो(" # %d %s will execute (on %d nodes, %d CPUs):\n",
		g->p.nr_tasks, g->p.nr_tasks == 1 ? "task" : "tasks", nr_numa_nodes(), g->p.nr_cpus);
	म_लिखो(" #      %5dx %5ldMB global  shared mem operations\n",
			g->p.nr_loops, g->p.bytes_global/1024/1024);
	म_लिखो(" #      %5dx %5ldMB process shared mem operations\n",
			g->p.nr_loops, g->p.bytes_process/1024/1024);
	म_लिखो(" #      %5dx %5ldMB thread  local  mem operations\n",
			g->p.nr_loops, g->p.bytes_thपढ़ो/1024/1024);

	म_लिखो(" ###\n");

	म_लिखो("\n ###\n"); ख_साफ(मानक_निकास);
पूर्ण

अटल व्योम init_thपढ़ो_data(व्योम)
अणु
	sमाप_प्रकार size = माप(*g->thपढ़ोs)*g->p.nr_tasks;
	पूर्णांक t;

	g->thपढ़ोs = zalloc_shared_data(size);

	क्रम (t = 0; t < g->p.nr_tasks; t++) अणु
		काष्ठा thपढ़ो_data *td = g->thपढ़ोs + t;
		पूर्णांक cpu;

		/* Allow all nodes by शेष: */
		td->bind_node = NUMA_NO_NODE;

		/* Allow all CPUs by शेष: */
		CPU_ZERO(&td->bind_cpumask);
		क्रम (cpu = 0; cpu < g->p.nr_cpus; cpu++)
			CPU_SET(cpu, &td->bind_cpumask);
	पूर्ण
पूर्ण

अटल व्योम deinit_thपढ़ो_data(व्योम)
अणु
	sमाप_प्रकार size = माप(*g->thपढ़ोs)*g->p.nr_tasks;

	मुक्त_data(g->thपढ़ोs, size);
पूर्ण

अटल पूर्णांक init(व्योम)
अणु
	g = (व्योम *)alloc_data(माप(*g), MAP_SHARED, 1, 0, 0 /* THP */, 0);

	/* Copy over options: */
	g->p = p0;

	g->p.nr_cpus = numa_num_configured_cpus();

	g->p.nr_nodes = numa_max_node() + 1;

	/* अक्षर array in count_process_nodes(): */
	BUG_ON(g->p.nr_nodes < 0);

	अगर (g->p.show_quiet && !g->p.show_details)
		g->p.show_details = -1;

	/* Some memory should be specअगरied: */
	अगर (!g->p.mb_global_str && !g->p.mb_proc_str && !g->p.mb_thपढ़ो_str)
		वापस -1;

	अगर (g->p.mb_global_str) अणु
		g->p.mb_global = म_से_भ(g->p.mb_global_str);
		BUG_ON(g->p.mb_global < 0);
	पूर्ण

	अगर (g->p.mb_proc_str) अणु
		g->p.mb_proc = म_से_भ(g->p.mb_proc_str);
		BUG_ON(g->p.mb_proc < 0);
	पूर्ण

	अगर (g->p.mb_proc_locked_str) अणु
		g->p.mb_proc_locked = म_से_भ(g->p.mb_proc_locked_str);
		BUG_ON(g->p.mb_proc_locked < 0);
		BUG_ON(g->p.mb_proc_locked > g->p.mb_proc);
	पूर्ण

	अगर (g->p.mb_thपढ़ो_str) अणु
		g->p.mb_thपढ़ो = म_से_भ(g->p.mb_thपढ़ो_str);
		BUG_ON(g->p.mb_thपढ़ो < 0);
	पूर्ण

	BUG_ON(g->p.nr_thपढ़ोs <= 0);
	BUG_ON(g->p.nr_proc <= 0);

	g->p.nr_tasks = g->p.nr_proc*g->p.nr_thपढ़ोs;

	g->p.bytes_global		= g->p.mb_global	*1024L*1024L;
	g->p.bytes_process		= g->p.mb_proc		*1024L*1024L;
	g->p.bytes_process_locked	= g->p.mb_proc_locked	*1024L*1024L;
	g->p.bytes_thपढ़ो		= g->p.mb_thपढ़ो	*1024L*1024L;

	g->data = setup_shared_data(g->p.bytes_global);

	/* Startup serialization: */
	init_global_mutex(&g->start_work_mutex);
	init_global_cond(&g->start_work_cond);
	init_global_mutex(&g->startup_mutex);
	init_global_cond(&g->startup_cond);
	init_global_mutex(&g->stop_work_mutex);

	init_thपढ़ो_data();

	tम_लिखो("#\n");
	अगर (parse_setup_cpu_list() || parse_setup_node_list())
		वापस -1;
	tम_लिखो("#\n");

	prपूर्णांक_summary();

	वापस 0;
पूर्ण

अटल व्योम deinit(व्योम)
अणु
	मुक्त_data(g->data, g->p.bytes_global);
	g->data = शून्य;

	deinit_thपढ़ो_data();

	मुक्त_data(g, माप(*g));
	g = शून्य;
पूर्ण

/*
 * Prपूर्णांक a लघु or दीर्घ result, depending on the verbosity setting:
 */
अटल व्योम prपूर्णांक_res(स्थिर अक्षर *name, द्विगुन val,
		      स्थिर अक्षर *txt_unit, स्थिर अक्षर *txt_लघु, स्थिर अक्षर *txt_दीर्घ)
अणु
	अगर (!name)
		name = "main,";

	अगर (!g->p.show_quiet)
		म_लिखो(" %-30s %15.3f, %-15s %s\n", name, val, txt_unit, txt_लघु);
	अन्यथा
		म_लिखो(" %14.3f %s\n", val, txt_दीर्घ);
पूर्ण

अटल पूर्णांक __bench_numa(स्थिर अक्षर *name)
अणु
	काष्ठा समयval start, stop, dअगरf;
	u64 runसमय_ns_min, runसमय_ns_sum;
	pid_t *pids, pid, wpid;
	द्विगुन delta_runसमय;
	द्विगुन runसमय_avg;
	द्विगुन runसमय_sec_max;
	द्विगुन runसमय_sec_min;
	पूर्णांक रुको_stat;
	द्विगुन bytes;
	पूर्णांक i, t, p;

	अगर (init())
		वापस -1;

	pids = zalloc(g->p.nr_proc * माप(*pids));
	pid = -1;

	अगर (g->p.serialize_startup) अणु
		tम_लिखो(" #\n");
		tम_लिखो(" # Startup synchronization: ..."); ख_साफ(मानक_निकास);
	पूर्ण

	समय_लोofday(&start, शून्य);

	क्रम (i = 0; i < g->p.nr_proc; i++) अणु
		pid = विभाजन();
		dम_लिखो(" # process %2d: PID %d\n", i, pid);

		BUG_ON(pid < 0);
		अगर (!pid) अणु
			/* Child process: */
			worker_process(i);

			निकास(0);
		पूर्ण
		pids[i] = pid;

	पूर्ण

	अगर (g->p.serialize_startup) अणु
		bool thपढ़ोs_पढ़ोy = false;
		द्विगुन startup_sec;

		/*
		 * Wait क्रम all the thपढ़ोs to start up. The last thपढ़ो will
		 * संकेत this process.
		 */
		pthपढ़ो_mutex_lock(&g->startup_mutex);
		जबतक (g->nr_tasks_started != g->p.nr_tasks)
			pthपढ़ो_cond_रुको(&g->startup_cond, &g->startup_mutex);

		pthपढ़ो_mutex_unlock(&g->startup_mutex);

		/* Wait क्रम all thपढ़ोs to be at the start_work_cond. */
		जबतक (!thपढ़ोs_पढ़ोy) अणु
			pthपढ़ो_mutex_lock(&g->start_work_mutex);
			thपढ़ोs_पढ़ोy = (g->nr_tasks_working == g->p.nr_tasks);
			pthपढ़ो_mutex_unlock(&g->start_work_mutex);
			अगर (!thपढ़ोs_पढ़ोy)
				usleep(1);
		पूर्ण

		समय_लोofday(&stop, शून्य);

		समयrsub(&stop, &start, &dअगरf);

		startup_sec = dअगरf.tv_sec * NSEC_PER_SEC;
		startup_sec += dअगरf.tv_usec * NSEC_PER_USEC;
		startup_sec /= NSEC_PER_SEC;

		tम_लिखो(" threads initialized in %.6f seconds.\n", startup_sec);
		tम_लिखो(" #\n");

		start = stop;
		/* Start all thपढ़ोs running. */
		pthपढ़ो_mutex_lock(&g->start_work_mutex);
		g->start_work = true;
		pthपढ़ो_mutex_unlock(&g->start_work_mutex);
		pthपढ़ो_cond_broadcast(&g->start_work_cond);
	पूर्ण अन्यथा अणु
		समय_लोofday(&start, शून्य);
	पूर्ण

	/* Parent process: */


	क्रम (i = 0; i < g->p.nr_proc; i++) अणु
		wpid = रुकोpid(pids[i], &रुको_stat, 0);
		BUG_ON(wpid < 0);
		BUG_ON(!WIFEXITED(रुको_stat));

	पूर्ण

	runसमय_ns_sum = 0;
	runसमय_ns_min = -1LL;

	क्रम (t = 0; t < g->p.nr_tasks; t++) अणु
		u64 thपढ़ो_runसमय_ns = g->thपढ़ोs[t].runसमय_ns;

		runसमय_ns_sum += thपढ़ो_runसमय_ns;
		runसमय_ns_min = min(thपढ़ो_runसमय_ns, runसमय_ns_min);
	पूर्ण

	समय_लोofday(&stop, शून्य);
	समयrsub(&stop, &start, &dअगरf);

	BUG_ON(bench_क्रमmat != BENCH_FORMAT_DEFAULT);

	tम_लिखो("\n ###\n");
	tम_लिखो("\n");

	runसमय_sec_max = dअगरf.tv_sec * NSEC_PER_SEC;
	runसमय_sec_max += dअगरf.tv_usec * NSEC_PER_USEC;
	runसमय_sec_max /= NSEC_PER_SEC;

	runसमय_sec_min = runसमय_ns_min / NSEC_PER_SEC;

	bytes = g->bytes_करोne;
	runसमय_avg = (द्विगुन)runसमय_ns_sum / g->p.nr_tasks / NSEC_PER_SEC;

	अगर (g->p.measure_convergence) अणु
		prपूर्णांक_res(name, runसमय_sec_max,
			"secs,", "NUMA-convergence-latency", "secs latency to NUMA-converge");
	पूर्ण

	prपूर्णांक_res(name, runसमय_sec_max,
		"secs,", "runtime-max/thread",	"secs slowest (max) thread-runtime");

	prपूर्णांक_res(name, runसमय_sec_min,
		"secs,", "runtime-min/thread",	"secs fastest (min) thread-runtime");

	prपूर्णांक_res(name, runसमय_avg,
		"secs,", "runtime-avg/thread",	"secs average thread-runtime");

	delta_runसमय = (runसमय_sec_max - runसमय_sec_min)/2.0;
	prपूर्णांक_res(name, delta_runसमय / runसमय_sec_max * 100.0,
		"%,", "spread-runtime/thread",	"% difference between max/avg runtime");

	prपूर्णांक_res(name, bytes / g->p.nr_tasks / 1e9,
		"GB,", "data/thread",		"GB data processed, per thread");

	prपूर्णांक_res(name, bytes / 1e9,
		"GB,", "data-total",		"GB data processed, total");

	prपूर्णांक_res(name, runसमय_sec_max * NSEC_PER_SEC / (bytes / g->p.nr_tasks),
		"nsecs,", "runtime/byte/thread","nsecs/byte/thread runtime");

	prपूर्णांक_res(name, bytes / g->p.nr_tasks / 1e9 / runसमय_sec_max,
		"GB/sec,", "thread-speed",	"GB/sec/thread speed");

	prपूर्णांक_res(name, bytes / runसमय_sec_max / 1e9,
		"GB/sec,", "total-speed",	"GB/sec total speed");

	अगर (g->p.show_details >= 2) अणु
		अक्षर tname[14 + 2 * 10 + 1];
		काष्ठा thपढ़ो_data *td;
		क्रम (p = 0; p < g->p.nr_proc; p++) अणु
			क्रम (t = 0; t < g->p.nr_thपढ़ोs; t++) अणु
				स_रखो(tname, 0, माप(tname));
				td = g->thपढ़ोs + p*g->p.nr_thपढ़ोs + t;
				snम_लिखो(tname, माप(tname), "process%d:thread%d", p, t);
				prपूर्णांक_res(tname, td->speed_gbs,
					"GB/sec",	"thread-speed", "GB/sec/thread speed");
				prपूर्णांक_res(tname, td->प्रणाली_समय_ns / NSEC_PER_SEC,
					"secs",	"thread-system-time", "system CPU time/thread");
				prपूर्णांक_res(tname, td->user_समय_ns / NSEC_PER_SEC,
					"secs",	"thread-user-time", "user CPU time/thread");
			पूर्ण
		पूर्ण
	पूर्ण

	मुक्त(pids);

	deinit();

	वापस 0;
पूर्ण

#घोषणा MAX_ARGS 50

अटल पूर्णांक command_size(स्थिर अक्षर **argv)
अणु
	पूर्णांक size = 0;

	जबतक (*argv) अणु
		size++;
		argv++;
	पूर्ण

	BUG_ON(size >= MAX_ARGS);

	वापस size;
पूर्ण

अटल व्योम init_params(काष्ठा params *p, स्थिर अक्षर *name, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक i;

	म_लिखो("\n # Running %s \"perf bench numa", name);

	क्रम (i = 0; i < argc; i++)
		म_लिखो(" %s", argv[i]);

	म_लिखो("\"\n");

	स_रखो(p, 0, माप(*p));

	/* Initialize nonzero शेषs: */

	p->serialize_startup		= 1;
	p->data_पढ़ोs			= true;
	p->data_ग_लिखोs			= true;
	p->data_backwards		= true;
	p->data_अक्रम_walk		= true;
	p->nr_loops			= -1;
	p->init_अक्रमom			= true;
	p->mb_global_str		= "1";
	p->nr_proc			= 1;
	p->nr_thपढ़ोs			= 1;
	p->nr_secs			= 5;
	p->run_all			= argc == 1;
पूर्ण

अटल पूर्णांक run_bench_numa(स्थिर अक्षर *name, स्थिर अक्षर **argv)
अणु
	पूर्णांक argc = command_size(argv);

	init_params(&p0, name, argc, argv);
	argc = parse_options(argc, argv, options, bench_numa_usage, 0);
	अगर (argc)
		जाओ err;

	अगर (__bench_numa(name))
		जाओ err;

	वापस 0;

err:
	वापस -1;
पूर्ण

#घोषणा OPT_BW_RAM		"-s",  "20", "-zZq",    "--thp", " 1", "--no-data_rand_walk"
#घोषणा OPT_BW_RAM_NOTHP	OPT_BW_RAM,		"--thp", "-1"

#घोषणा OPT_CONV		"-s", "100", "-zZ0qcm", "--thp", " 1"
#घोषणा OPT_CONV_NOTHP		OPT_CONV,		"--thp", "-1"

#घोषणा OPT_BW			"-s",  "20", "-zZ0q",   "--thp", " 1"
#घोषणा OPT_BW_NOTHP		OPT_BW,			"--thp", "-1"

/*
 * The built-in test-suite executed by "perf bench numa -a".
 *
 * (A minimum of 4 nodes and 16 GB of RAM is recommended.)
 */
अटल स्थिर अक्षर *tests[][MAX_ARGS] = अणु
   /* Basic single-stream NUMA bandwidth measurements: */
   अणु "RAM-bw-local,",     "mem",  "-p",  "1",  "-t",  "1", "-P", "1024",
			  "-C" ,   "0", "-M",   "0", OPT_BW_RAM पूर्ण,
   अणु "RAM-bw-local-NOTHP,",
			  "mem",  "-p",  "1",  "-t",  "1", "-P", "1024",
			  "-C" ,   "0", "-M",   "0", OPT_BW_RAM_NOTHP पूर्ण,
   अणु "RAM-bw-remote,",    "mem",  "-p",  "1",  "-t",  "1", "-P", "1024",
			  "-C" ,   "0", "-M",   "1", OPT_BW_RAM पूर्ण,

   /* 2-stream NUMA bandwidth measurements: */
   अणु "RAM-bw-local-2x,",  "mem",  "-p",  "2",  "-t",  "1", "-P", "1024",
			   "-C", "0,2", "-M", "0x2", OPT_BW_RAM पूर्ण,
   अणु "RAM-bw-remote-2x,", "mem",  "-p",  "2",  "-t",  "1", "-P", "1024",
		 	   "-C", "0,2", "-M", "1x2", OPT_BW_RAM पूर्ण,

   /* Cross-stream NUMA bandwidth measurement: */
   अणु "RAM-bw-cross,",     "mem",  "-p",  "2",  "-t",  "1", "-P", "1024",
		 	   "-C", "0,8", "-M", "1,0", OPT_BW_RAM पूर्ण,

   /* Convergence latency measurements: */
   अणु " 1x3-convergence,", "mem",  "-p",  "1", "-t",  "3", "-P",  "512", OPT_CONV पूर्ण,
   अणु " 1x4-convergence,", "mem",  "-p",  "1", "-t",  "4", "-P",  "512", OPT_CONV पूर्ण,
   अणु " 1x6-convergence,", "mem",  "-p",  "1", "-t",  "6", "-P", "1020", OPT_CONV पूर्ण,
   अणु " 2x3-convergence,", "mem",  "-p",  "2", "-t",  "3", "-P", "1020", OPT_CONV पूर्ण,
   अणु " 3x3-convergence,", "mem",  "-p",  "3", "-t",  "3", "-P", "1020", OPT_CONV पूर्ण,
   अणु " 4x4-convergence,", "mem",  "-p",  "4", "-t",  "4", "-P",  "512", OPT_CONV पूर्ण,
   अणु " 4x4-convergence-NOTHP,",
			  "mem",  "-p",  "4", "-t",  "4", "-P",  "512", OPT_CONV_NOTHP पूर्ण,
   अणु " 4x6-convergence,", "mem",  "-p",  "4", "-t",  "6", "-P", "1020", OPT_CONV पूर्ण,
   अणु " 4x8-convergence,", "mem",  "-p",  "4", "-t",  "8", "-P",  "512", OPT_CONV पूर्ण,
   अणु " 8x4-convergence,", "mem",  "-p",  "8", "-t",  "4", "-P",  "512", OPT_CONV पूर्ण,
   अणु " 8x4-convergence-NOTHP,",
			  "mem",  "-p",  "8", "-t",  "4", "-P",  "512", OPT_CONV_NOTHP पूर्ण,
   अणु " 3x1-convergence,", "mem",  "-p",  "3", "-t",  "1", "-P",  "512", OPT_CONV पूर्ण,
   अणु " 4x1-convergence,", "mem",  "-p",  "4", "-t",  "1", "-P",  "512", OPT_CONV पूर्ण,
   अणु " 8x1-convergence,", "mem",  "-p",  "8", "-t",  "1", "-P",  "512", OPT_CONV पूर्ण,
   अणु "16x1-convergence,", "mem",  "-p", "16", "-t",  "1", "-P",  "256", OPT_CONV पूर्ण,
   अणु "32x1-convergence,", "mem",  "-p", "32", "-t",  "1", "-P",  "128", OPT_CONV पूर्ण,

   /* Various NUMA process/thपढ़ो layout bandwidth measurements: */
   अणु " 2x1-bw-process,",  "mem",  "-p",  "2", "-t",  "1", "-P", "1024", OPT_BW पूर्ण,
   अणु " 3x1-bw-process,",  "mem",  "-p",  "3", "-t",  "1", "-P", "1024", OPT_BW पूर्ण,
   अणु " 4x1-bw-process,",  "mem",  "-p",  "4", "-t",  "1", "-P", "1024", OPT_BW पूर्ण,
   अणु " 8x1-bw-process,",  "mem",  "-p",  "8", "-t",  "1", "-P", " 512", OPT_BW पूर्ण,
   अणु " 8x1-bw-process-NOTHP,",
			  "mem",  "-p",  "8", "-t",  "1", "-P", " 512", OPT_BW_NOTHP पूर्ण,
   अणु "16x1-bw-process,",  "mem",  "-p", "16", "-t",  "1", "-P",  "256", OPT_BW पूर्ण,

   अणु " 1x4-bw-thread,",   "mem",  "-p",  "1", "-t",  "4", "-T",  "256", OPT_BW पूर्ण,
   अणु " 1x8-bw-thread,",   "mem",  "-p",  "1", "-t",  "8", "-T",  "256", OPT_BW पूर्ण,
   अणु "1x16-bw-thread,",   "mem",  "-p",  "1", "-t", "16", "-T",  "128", OPT_BW पूर्ण,
   अणु "1x32-bw-thread,",   "mem",  "-p",  "1", "-t", "32", "-T",   "64", OPT_BW पूर्ण,

   अणु " 2x3-bw-process,",  "mem",  "-p",  "2", "-t",  "3", "-P",  "512", OPT_BW पूर्ण,
   अणु " 4x4-bw-process,",  "mem",  "-p",  "4", "-t",  "4", "-P",  "512", OPT_BW पूर्ण,
   अणु " 4x6-bw-process,",  "mem",  "-p",  "4", "-t",  "6", "-P",  "512", OPT_BW पूर्ण,
   अणु " 4x8-bw-process,",  "mem",  "-p",  "4", "-t",  "8", "-P",  "512", OPT_BW पूर्ण,
   अणु " 4x8-bw-process-NOTHP,",
			  "mem",  "-p",  "4", "-t",  "8", "-P",  "512", OPT_BW_NOTHP पूर्ण,
   अणु " 3x3-bw-process,",  "mem",  "-p",  "3", "-t",  "3", "-P",  "512", OPT_BW पूर्ण,
   अणु " 5x5-bw-process,",  "mem",  "-p",  "5", "-t",  "5", "-P",  "512", OPT_BW पूर्ण,

   अणु "2x16-bw-process,",  "mem",  "-p",  "2", "-t", "16", "-P",  "512", OPT_BW पूर्ण,
   अणु "1x32-bw-process,",  "mem",  "-p",  "1", "-t", "32", "-P", "2048", OPT_BW पूर्ण,

   अणु "numa02-bw,",        "mem",  "-p",  "1", "-t", "32", "-T",   "32", OPT_BW पूर्ण,
   अणु "numa02-bw-NOTHP,",  "mem",  "-p",  "1", "-t", "32", "-T",   "32", OPT_BW_NOTHP पूर्ण,
   अणु "numa01-bw-thread,", "mem",  "-p",  "2", "-t", "16", "-T",  "192", OPT_BW पूर्ण,
   अणु "numa01-bw-thread-NOTHP,",
			  "mem",  "-p",  "2", "-t", "16", "-T",  "192", OPT_BW_NOTHP पूर्ण,
पूर्ण;

अटल पूर्णांक bench_all(व्योम)
अणु
	पूर्णांक nr = ARRAY_SIZE(tests);
	पूर्णांक ret;
	पूर्णांक i;

	ret = प्रणाली("echo ' #'; echo ' # Running test on: '$(uname -a); echo ' #'");
	BUG_ON(ret < 0);

	क्रम (i = 0; i < nr; i++) अणु
		run_bench_numa(tests[i][0], tests[i] + 1);
	पूर्ण

	म_लिखो("\n");

	वापस 0;
पूर्ण

पूर्णांक bench_numa(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	init_params(&p0, "main,", argc, argv);
	argc = parse_options(argc, argv, options, bench_numa_usage, 0);
	अगर (argc)
		जाओ err;

	अगर (p0.run_all)
		वापस bench_all();

	अगर (__bench_numa(शून्य))
		जाओ err;

	वापस 0;

err:
	usage_with_options(numa_usage, options);
	वापस -1;
पूर्ण
