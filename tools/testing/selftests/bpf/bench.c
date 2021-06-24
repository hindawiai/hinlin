<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#घोषणा _GNU_SOURCE
#समावेश <argp.h>
#समावेश <linux/compiler.h>
#समावेश <sys/समय.स>
#समावेश <sched.h>
#समावेश <fcntl.h>
#समावेश <pthपढ़ो.h>
#समावेश <sys/sysinfo.h>
#समावेश <sys/resource.h>
#समावेश <संकेत.स>
#समावेश "bench.h"
#समावेश "testing_helpers.h"

काष्ठा env env = अणु
	.warmup_sec = 1,
	.duration_sec = 5,
	.affinity = false,
	.consumer_cnt = 1,
	.producer_cnt = 1,
पूर्ण;

अटल पूर्णांक libbpf_prपूर्णांक_fn(क्रमागत libbpf_prपूर्णांक_level level,
		    स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	अगर (level == LIBBPF_DEBUG && !env.verbose)
		वापस 0;
	वापस भख_लिखो(मानक_त्रुटि, क्रमmat, args);
पूर्ण

अटल पूर्णांक bump_memlock_rlimit(व्योम)
अणु
	काष्ठा rlimit rlim_new = अणु
		.rlim_cur	= RLIM_अनन्त,
		.rlim_max	= RLIM_अनन्त,
	पूर्ण;

	वापस setrlimit(RLIMIT_MEMLOCK, &rlim_new);
पूर्ण

व्योम setup_libbpf()
अणु
	पूर्णांक err;

	libbpf_set_prपूर्णांक(libbpf_prपूर्णांक_fn);

	err = bump_memlock_rlimit();
	अगर (err)
		ख_लिखो(मानक_त्रुटि, "failed to increase RLIMIT_MEMLOCK: %d", err);
पूर्ण

व्योम hits_drops_report_progress(पूर्णांक iter, काष्ठा bench_res *res, दीर्घ delta_ns)
अणु
	द्विगुन hits_per_sec, drops_per_sec;
	द्विगुन hits_per_prod;

	hits_per_sec = res->hits / 1000000.0 / (delta_ns / 1000000000.0);
	hits_per_prod = hits_per_sec / env.producer_cnt;
	drops_per_sec = res->drops / 1000000.0 / (delta_ns / 1000000000.0);

	म_लिखो("Iter %3d (%7.3lfus): ",
	       iter, (delta_ns - 1000000000) / 1000.0);

	म_लिखो("hits %8.3lfM/s (%7.3lfM/prod), drops %8.3lfM/s\n",
	       hits_per_sec, hits_per_prod, drops_per_sec);
पूर्ण

व्योम hits_drops_report_final(काष्ठा bench_res res[], पूर्णांक res_cnt)
अणु
	पूर्णांक i;
	द्विगुन hits_mean = 0.0, drops_mean = 0.0;
	द्विगुन hits_stddev = 0.0, drops_stddev = 0.0;

	क्रम (i = 0; i < res_cnt; i++) अणु
		hits_mean += res[i].hits / 1000000.0 / (0.0 + res_cnt);
		drops_mean += res[i].drops / 1000000.0 / (0.0 + res_cnt);
	पूर्ण

	अगर (res_cnt > 1)  अणु
		क्रम (i = 0; i < res_cnt; i++) अणु
			hits_stddev += (hits_mean - res[i].hits / 1000000.0) *
				       (hits_mean - res[i].hits / 1000000.0) /
				       (res_cnt - 1.0);
			drops_stddev += (drops_mean - res[i].drops / 1000000.0) *
					(drops_mean - res[i].drops / 1000000.0) /
					(res_cnt - 1.0);
		पूर्ण
		hits_stddev = वर्ग_मूल(hits_stddev);
		drops_stddev = वर्ग_मूल(drops_stddev);
	पूर्ण
	म_लिखो("Summary: hits %8.3lf \u00B1 %5.3lfM/s (%7.3lfM/prod), ",
	       hits_mean, hits_stddev, hits_mean / env.producer_cnt);
	म_लिखो("drops %8.3lf \u00B1 %5.3lfM/s\n",
	       drops_mean, drops_stddev);
पूर्ण

स्थिर अक्षर *argp_program_version = "benchmark";
स्थिर अक्षर *argp_program_bug_address = "<bpf@vger.kernel.org>";
स्थिर अक्षर argp_program_करोc[] =
"benchmark    Generic benchmarking framework.\n"
"\n"
"This tool runs benchmarks.\n"
"\n"
"USAGE: benchmark <bench-name>\n"
"\n"
"EXAMPLES:\n"
"    # run 'count-local' benchmark with 1 producer and 1 consumer\n"
"    benchmark count-local\n"
"    # run 'count-local' with 16 producer and 8 consumer thread, pinned to CPUs\n"
"    benchmark -p16 -c8 -a count-local\n";

क्रमागत अणु
	ARG_PROD_AFFINITY_SET = 1000,
	ARG_CONS_AFFINITY_SET = 1001,
पूर्ण;

अटल स्थिर काष्ठा argp_option opts[] = अणु
	अणु "list", 'l', शून्य, 0, "List available benchmarks"पूर्ण,
	अणु "duration", 'd', "SEC", 0, "Duration of benchmark, seconds"पूर्ण,
	अणु "warmup", 'w', "SEC", 0, "Warm-up period, seconds"पूर्ण,
	अणु "producers", 'p', "NUM", 0, "Number of producer threads"पूर्ण,
	अणु "consumers", 'c', "NUM", 0, "Number of consumer threads"पूर्ण,
	अणु "verbose", 'v', शून्य, 0, "Verbose debug output"पूर्ण,
	अणु "affinity", 'a', शून्य, 0, "Set consumer/producer thread affinity"पूर्ण,
	अणु "prod-affinity", ARG_PROD_AFFINITY_SET, "CPUSET", 0,
	  "Set of CPUs for producer threads; implies --affinity"पूर्ण,
	अणु "cons-affinity", ARG_CONS_AFFINITY_SET, "CPUSET", 0,
	  "Set of CPUs for consumer threads; implies --affinity"पूर्ण,
	अणुपूर्ण,
पूर्ण;

बाह्य काष्ठा argp bench_ringbufs_argp;

अटल स्थिर काष्ठा argp_child bench_parsers[] = अणु
	अणु &bench_ringbufs_argp, 0, "Ring buffers benchmark", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल error_t parse_arg(पूर्णांक key, अक्षर *arg, काष्ठा argp_state *state)
अणु
	अटल पूर्णांक pos_args;

	चयन (key) अणु
	हाल 'v':
		env.verbose = true;
		अवरोध;
	हाल 'l':
		env.list = true;
		अवरोध;
	हाल 'd':
		env.duration_sec = म_से_दीर्घ(arg, शून्य, 10);
		अगर (env.duration_sec <= 0) अणु
			ख_लिखो(मानक_त्रुटि, "Invalid duration: %s\n", arg);
			argp_usage(state);
		पूर्ण
		अवरोध;
	हाल 'w':
		env.warmup_sec = म_से_दीर्घ(arg, शून्य, 10);
		अगर (env.warmup_sec <= 0) अणु
			ख_लिखो(मानक_त्रुटि, "Invalid warm-up duration: %s\n", arg);
			argp_usage(state);
		पूर्ण
		अवरोध;
	हाल 'p':
		env.producer_cnt = म_से_दीर्घ(arg, शून्य, 10);
		अगर (env.producer_cnt <= 0) अणु
			ख_लिखो(मानक_त्रुटि, "Invalid producer count: %s\n", arg);
			argp_usage(state);
		पूर्ण
		अवरोध;
	हाल 'c':
		env.consumer_cnt = म_से_दीर्घ(arg, शून्य, 10);
		अगर (env.consumer_cnt <= 0) अणु
			ख_लिखो(मानक_त्रुटि, "Invalid consumer count: %s\n", arg);
			argp_usage(state);
		पूर्ण
		अवरोध;
	हाल 'a':
		env.affinity = true;
		अवरोध;
	हाल ARG_PROD_AFFINITY_SET:
		env.affinity = true;
		अगर (parse_num_list(arg, &env.prod_cpus.cpus,
				   &env.prod_cpus.cpus_len)) अणु
			ख_लिखो(मानक_त्रुटि, "Invalid format of CPU set for producers.");
			argp_usage(state);
		पूर्ण
		अवरोध;
	हाल ARG_CONS_AFFINITY_SET:
		env.affinity = true;
		अगर (parse_num_list(arg, &env.cons_cpus.cpus,
				   &env.cons_cpus.cpus_len)) अणु
			ख_लिखो(मानक_त्रुटि, "Invalid format of CPU set for consumers.");
			argp_usage(state);
		पूर्ण
		अवरोध;
	हाल ARGP_KEY_ARG:
		अगर (pos_args++) अणु
			ख_लिखो(मानक_त्रुटि,
				"Unrecognized positional argument: %s\n", arg);
			argp_usage(state);
		पूर्ण
		env.bench_name = strdup(arg);
		अवरोध;
	शेष:
		वापस ARGP_ERR_UNKNOWN;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम parse_cmdline_args(पूर्णांक argc, अक्षर **argv)
अणु
	अटल स्थिर काष्ठा argp argp = अणु
		.options = opts,
		.parser = parse_arg,
		.करोc = argp_program_करोc,
		.children = bench_parsers,
	पूर्ण;
	अगर (argp_parse(&argp, argc, argv, 0, शून्य, शून्य))
		निकास(1);
	अगर (!env.list && !env.bench_name) अणु
		argp_help(&argp, मानक_त्रुटि, ARGP_HELP_DOC, "bench");
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम collect_measurements(दीर्घ delta_ns);

अटल __u64 last_समय_ns;
अटल व्योम sigalarm_handler(पूर्णांक signo)
अणु
	दीर्घ new_समय_ns = get_समय_ns();
	दीर्घ delta_ns = new_समय_ns - last_समय_ns;

	collect_measurements(delta_ns);

	last_समय_ns = new_समय_ns;
पूर्ण

/* set up periodic 1-second समयr */
अटल व्योम setup_समयr()
अणु
	अटल काष्ठा sigaction sigalarm_action = अणु
		.sa_handler = sigalarm_handler,
	पूर्ण;
	काष्ठा iसमयrval समयr_settings = अणुपूर्ण;
	पूर्णांक err;

	last_समय_ns = get_समय_ns();
	err = sigaction(SIGALRM, &sigalarm_action, शून्य);
	अगर (err < 0) अणु
		ख_लिखो(मानक_त्रुटि, "failed to install SIGALRM handler: %d\n", -त्रुटि_सं);
		निकास(1);
	पूर्ण
	समयr_settings.it_पूर्णांकerval.tv_sec = 1;
	समयr_settings.it_value.tv_sec = 1;
	err = setiसमयr(ITIMER_REAL, &समयr_settings, शून्य);
	अगर (err < 0) अणु
		ख_लिखो(मानक_त्रुटि, "failed to arm interval timer: %d\n", -त्रुटि_सं);
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम set_thपढ़ो_affinity(pthपढ़ो_t thपढ़ो, पूर्णांक cpu)
अणु
	cpu_set_t cpuset;

	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);
	अगर (pthपढ़ो_setaffinity_np(thपढ़ो, माप(cpuset), &cpuset)) अणु
		ख_लिखो(मानक_त्रुटि, "setting affinity to CPU #%d failed: %d\n",
			cpu, त्रुटि_सं);
		निकास(1);
	पूर्ण
पूर्ण

अटल पूर्णांक next_cpu(काष्ठा cpu_set *cpu_set)
अणु
	अगर (cpu_set->cpus) अणु
		पूर्णांक i;

		/* find next available CPU */
		क्रम (i = cpu_set->next_cpu; i < cpu_set->cpus_len; i++) अणु
			अगर (cpu_set->cpus[i]) अणु
				cpu_set->next_cpu = i + 1;
				वापस i;
			पूर्ण
		पूर्ण
		ख_लिखो(मानक_त्रुटि, "Not enough CPUs specified, need CPU #%d or higher.\n", i);
		निकास(1);
	पूर्ण

	वापस cpu_set->next_cpu++;
पूर्ण

अटल काष्ठा bench_state अणु
	पूर्णांक res_cnt;
	काष्ठा bench_res *results;
	pthपढ़ो_t *consumers;
	pthपढ़ो_t *producers;
पूर्ण state;

स्थिर काष्ठा bench *bench = शून्य;

बाह्य स्थिर काष्ठा bench bench_count_global;
बाह्य स्थिर काष्ठा bench bench_count_local;
बाह्य स्थिर काष्ठा bench bench_नाम_base;
बाह्य स्थिर काष्ठा bench bench_नाम_kprobe;
बाह्य स्थिर काष्ठा bench bench_नाम_kretprobe;
बाह्य स्थिर काष्ठा bench bench_नाम_rawtp;
बाह्य स्थिर काष्ठा bench bench_नाम_fentry;
बाह्य स्थिर काष्ठा bench bench_नाम_fनिकास;
बाह्य स्थिर काष्ठा bench bench_trig_base;
बाह्य स्थिर काष्ठा bench bench_trig_tp;
बाह्य स्थिर काष्ठा bench bench_trig_rawtp;
बाह्य स्थिर काष्ठा bench bench_trig_kprobe;
बाह्य स्थिर काष्ठा bench bench_trig_fentry;
बाह्य स्थिर काष्ठा bench bench_trig_fentry_sleep;
बाह्य स्थिर काष्ठा bench bench_trig_भ_शेषret;
बाह्य स्थिर काष्ठा bench bench_rb_libbpf;
बाह्य स्थिर काष्ठा bench bench_rb_custom;
बाह्य स्थिर काष्ठा bench bench_pb_libbpf;
बाह्य स्थिर काष्ठा bench bench_pb_custom;

अटल स्थिर काष्ठा bench *benchs[] = अणु
	&bench_count_global,
	&bench_count_local,
	&bench_नाम_base,
	&bench_नाम_kprobe,
	&bench_नाम_kretprobe,
	&bench_नाम_rawtp,
	&bench_नाम_fentry,
	&bench_नाम_fनिकास,
	&bench_trig_base,
	&bench_trig_tp,
	&bench_trig_rawtp,
	&bench_trig_kprobe,
	&bench_trig_fentry,
	&bench_trig_fentry_sleep,
	&bench_trig_भ_शेषret,
	&bench_rb_libbpf,
	&bench_rb_custom,
	&bench_pb_libbpf,
	&bench_pb_custom,
पूर्ण;

अटल व्योम setup_benchmark()
अणु
	पूर्णांक i, err;

	अगर (!env.bench_name) अणु
		ख_लिखो(मानक_त्रुटि, "benchmark name is not specified\n");
		निकास(1);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(benchs); i++) अणु
		अगर (म_भेद(benchs[i]->name, env.bench_name) == 0) अणु
			bench = benchs[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!bench) अणु
		ख_लिखो(मानक_त्रुटि, "benchmark '%s' not found\n", env.bench_name);
		निकास(1);
	पूर्ण

	म_लिखो("Setting up benchmark '%s'...\n", bench->name);

	state.producers = सुस्मृति(env.producer_cnt, माप(*state.producers));
	state.consumers = सुस्मृति(env.consumer_cnt, माप(*state.consumers));
	state.results = सुस्मृति(env.duration_sec + env.warmup_sec + 2,
			       माप(*state.results));
	अगर (!state.producers || !state.consumers || !state.results)
		निकास(1);

	अगर (bench->validate)
		bench->validate();
	अगर (bench->setup)
		bench->setup();

	क्रम (i = 0; i < env.consumer_cnt; i++) अणु
		err = pthपढ़ो_create(&state.consumers[i], शून्य,
				     bench->consumer_thपढ़ो, (व्योम *)(दीर्घ)i);
		अगर (err) अणु
			ख_लिखो(मानक_त्रुटि, "failed to create consumer thread #%d: %d\n",
				i, -त्रुटि_सं);
			निकास(1);
		पूर्ण
		अगर (env.affinity)
			set_thपढ़ो_affinity(state.consumers[i],
					    next_cpu(&env.cons_cpus));
	पूर्ण

	/* unless explicit producer CPU list is specअगरied, जारी after
	 * last consumer CPU
	 */
	अगर (!env.prod_cpus.cpus)
		env.prod_cpus.next_cpu = env.cons_cpus.next_cpu;

	क्रम (i = 0; i < env.producer_cnt; i++) अणु
		err = pthपढ़ो_create(&state.producers[i], शून्य,
				     bench->producer_thपढ़ो, (व्योम *)(दीर्घ)i);
		अगर (err) अणु
			ख_लिखो(मानक_त्रुटि, "failed to create producer thread #%d: %d\n",
				i, -त्रुटि_सं);
			निकास(1);
		पूर्ण
		अगर (env.affinity)
			set_thपढ़ो_affinity(state.producers[i],
					    next_cpu(&env.prod_cpus));
	पूर्ण

	म_लिखो("Benchmark '%s' started.\n", bench->name);
पूर्ण

अटल pthपढ़ो_mutex_t bench_करोne_mtx = PTHREAD_MUTEX_INITIALIZER;
अटल pthपढ़ो_cond_t bench_करोne = PTHREAD_COND_INITIALIZER;

अटल व्योम collect_measurements(दीर्घ delta_ns) अणु
	पूर्णांक iter = state.res_cnt++;
	काष्ठा bench_res *res = &state.results[iter];

	bench->measure(res);

	अगर (bench->report_progress)
		bench->report_progress(iter, res, delta_ns);

	अगर (iter == env.duration_sec + env.warmup_sec) अणु
		pthपढ़ो_mutex_lock(&bench_करोne_mtx);
		pthपढ़ो_cond_संकेत(&bench_करोne);
		pthपढ़ो_mutex_unlock(&bench_करोne_mtx);
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	parse_cmdline_args(argc, argv);

	अगर (env.list) अणु
		पूर्णांक i;

		म_लिखो("Available benchmarks:\n");
		क्रम (i = 0; i < ARRAY_SIZE(benchs); i++) अणु
			म_लिखो("- %s\n", benchs[i]->name);
		पूर्ण
		वापस 0;
	पूर्ण

	setup_benchmark();

	setup_समयr();

	pthपढ़ो_mutex_lock(&bench_करोne_mtx);
	pthपढ़ो_cond_रुको(&bench_करोne, &bench_करोne_mtx);
	pthपढ़ो_mutex_unlock(&bench_करोne_mtx);

	अगर (bench->report_final)
		/* skip first sample */
		bench->report_final(state.results + env.warmup_sec,
				    state.res_cnt - env.warmup_sec);

	वापस 0;
पूर्ण
