<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * builtin-bench.c
 *
 * General benchmarking collections provided by perf
 *
 * Copyright (C) 2009, Hitoshi Mitake <mitake@dcl.info.waseda.ac.jp>
 */

/*
 * Available benchmark collection list:
 *
 *  sched ... scheduler and IPC perक्रमmance
 *  syscall ... System call perक्रमmance
 *  mem   ... memory access perक्रमmance
 *  numa  ... NUMA scheduling and MM perक्रमmance
 *  futex ... Futex perक्रमmance
 *  epoll ... Event poll perक्रमmance
 */
#समावेश <subcmd/parse-options.h>
#समावेश "builtin.h"
#समावेश "bench/bench.h"

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/prctl.h>
#समावेश <linux/zभाग.स>

प्रकार पूर्णांक (*bench_fn_t)(पूर्णांक argc, स्थिर अक्षर **argv);

काष्ठा bench अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*summary;
	bench_fn_t	fn;
पूर्ण;

#अगर_घोषित HAVE_LIBNUMA_SUPPORT
अटल काष्ठा bench numa_benchmarks[] = अणु
	अणु "mem",	"Benchmark for NUMA workloads",			bench_numa		पूर्ण,
	अणु "all",	"Run all NUMA benchmarks",			शून्य			पूर्ण,
	अणु शून्य,		शून्य,						शून्य			पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा bench sched_benchmarks[] = अणु
	अणु "messaging",	"Benchmark for scheduling and IPC",		bench_sched_messaging	पूर्ण,
	अणु "pipe",	"Benchmark for pipe() between two processes",	bench_sched_pipe	पूर्ण,
	अणु "all",	"Run all scheduler benchmarks",		शून्य			पूर्ण,
	अणु शून्य,		शून्य,						शून्य			पूर्ण
पूर्ण;

अटल काष्ठा bench syscall_benchmarks[] = अणु
	अणु "basic",	"Benchmark for basic getppid(2) calls",		bench_syscall_basic	पूर्ण,
	अणु "all",	"Run all syscall benchmarks",			शून्य			पूर्ण,
	अणु शून्य,		शून्य,						शून्य			पूर्ण,
पूर्ण;

अटल काष्ठा bench mem_benchmarks[] = अणु
	अणु "memcpy",	"Benchmark for memcpy() functions",		bench_mem_स_नकल	पूर्ण,
	अणु "memset",	"Benchmark for memset() functions",		bench_mem_स_रखो	पूर्ण,
	अणु "find_bit",	"Benchmark for find_bit() functions",		bench_mem_find_bit	पूर्ण,
	अणु "all",	"Run all memory access benchmarks",		शून्य			पूर्ण,
	अणु शून्य,		शून्य,						शून्य			पूर्ण
पूर्ण;

अटल काष्ठा bench futex_benchmarks[] = अणु
	अणु "hash",	"Benchmark for futex hash table",               bench_futex_hash	पूर्ण,
	अणु "wake",	"Benchmark for futex wake calls",               bench_futex_wake	पूर्ण,
	अणु "wake-parallel", "Benchmark for parallel futex wake calls",   bench_futex_wake_parallel पूर्ण,
	अणु "requeue",	"Benchmark for futex requeue calls",            bench_futex_requeue	पूर्ण,
	/* pi-futexes */
	अणु "lock-pi",	"Benchmark for futex lock_pi calls",            bench_futex_lock_pi	पूर्ण,
	अणु "all",	"Run all futex benchmarks",			शून्य			पूर्ण,
	अणु शून्य,		शून्य,						शून्य			पूर्ण
पूर्ण;

#अगर_घोषित HAVE_EVENTFD_SUPPORT
अटल काष्ठा bench epoll_benchmarks[] = अणु
	अणु "wait",	"Benchmark epoll concurrent epoll_waits",       bench_epoll_रुको	पूर्ण,
	अणु "ctl",	"Benchmark epoll concurrent epoll_ctls",        bench_epoll_ctl		पूर्ण,
	अणु "all",	"Run all futex benchmarks",			शून्य			पूर्ण,
	अणु शून्य,		शून्य,						शून्य			पूर्ण
पूर्ण;
#पूर्ण_अगर // HAVE_EVENTFD_SUPPORT

अटल काष्ठा bench पूर्णांकernals_benchmarks[] = अणु
	अणु "synthesize", "Benchmark perf event synthesis",	bench_synthesize	पूर्ण,
	अणु "kallsyms-parse", "Benchmark kallsyms parsing",	bench_kallsyms_parse	पूर्ण,
	अणु "inject-build-id", "Benchmark build-id injection",	bench_inject_build_id	पूर्ण,
	अणु शून्य,		शून्य,					शून्य			पूर्ण
पूर्ण;

काष्ठा collection अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*summary;
	काष्ठा bench	*benchmarks;
पूर्ण;

अटल काष्ठा collection collections[] = अणु
	अणु "sched",	"Scheduler and IPC benchmarks",			sched_benchmarks	पूर्ण,
	अणु "syscall",	"System call benchmarks",			syscall_benchmarks	पूर्ण,
	अणु "mem",	"Memory access benchmarks",			mem_benchmarks		पूर्ण,
#अगर_घोषित HAVE_LIBNUMA_SUPPORT
	अणु "numa",	"NUMA scheduling and MM benchmarks",		numa_benchmarks		पूर्ण,
#पूर्ण_अगर
	अणु"futex",       "Futex stressing benchmarks",                   futex_benchmarks        पूर्ण,
#अगर_घोषित HAVE_EVENTFD_SUPPORT
	अणु"epoll",       "Epoll stressing benchmarks",                   epoll_benchmarks        पूर्ण,
#पूर्ण_अगर
	अणु "internals",	"Perf-internals benchmarks",			पूर्णांकernals_benchmarks	पूर्ण,
	अणु "all",	"All benchmarks",				शून्य			पूर्ण,
	अणु शून्य,		शून्य,						शून्य			पूर्ण
पूर्ण;

/* Iterate over all benchmark collections: */
#घोषणा क्रम_each_collection(coll) \
	क्रम (coll = collections; coll->name; coll++)

/* Iterate over all benchmarks within a collection: */
#घोषणा क्रम_each_bench(coll, bench) \
	क्रम (bench = coll->benchmarks; bench && bench->name; bench++)

अटल व्योम dump_benchmarks(काष्ठा collection *coll)
अणु
	काष्ठा bench *bench;

	म_लिखो("\n        # List of available benchmarks for collection '%s':\n\n", coll->name);

	क्रम_each_bench(coll, bench)
		म_लिखो("%14s: %s\n", bench->name, bench->summary);

	म_लिखो("\n");
पूर्ण

अटल स्थिर अक्षर *bench_क्रमmat_str;

/* Output/क्रमmatting style, exported to benchmark modules: */
पूर्णांक bench_क्रमmat = BENCH_FORMAT_DEFAULT;
अचिन्हित पूर्णांक bench_repeat = 10; /* शेष number of बार to repeat the run */

अटल स्थिर काष्ठा option bench_options[] = अणु
	OPT_STRING('f', "format", &bench_क्रमmat_str, "default|simple", "Specify the output formatting style"),
	OPT_UINTEGER('r', "repeat",  &bench_repeat,   "Specify amount of times to repeat the run"),
	OPT_END()
पूर्ण;

अटल स्थिर अक्षर * स्थिर bench_usage[] = अणु
	"perf bench [<common options>] <collection> <benchmark> [<options>]",
	शून्य
पूर्ण;

अटल व्योम prपूर्णांक_usage(व्योम)
अणु
	काष्ठा collection *coll;
	पूर्णांक i;

	म_लिखो("Usage: \n");
	क्रम (i = 0; bench_usage[i]; i++)
		म_लिखो("\t%s\n", bench_usage[i]);
	म_लिखो("\n");

	म_लिखो("        # List of all available benchmark collections:\n\n");

	क्रम_each_collection(coll)
		म_लिखो("%14s: %s\n", coll->name, coll->summary);
	म_लिखो("\n");
पूर्ण

अटल पूर्णांक bench_str2पूर्णांक(स्थिर अक्षर *str)
अणु
	अगर (!str)
		वापस BENCH_FORMAT_DEFAULT;

	अगर (!म_भेद(str, BENCH_FORMAT_DEFAULT_STR))
		वापस BENCH_FORMAT_DEFAULT;
	अन्यथा अगर (!म_भेद(str, BENCH_FORMAT_SIMPLE_STR))
		वापस BENCH_FORMAT_SIMPLE;

	वापस BENCH_FORMAT_UNKNOWN;
पूर्ण

/*
 * Run a specअगरic benchmark but first नाम the running task's ->comm[]
 * to something meaningful:
 */
अटल पूर्णांक run_bench(स्थिर अक्षर *coll_name, स्थिर अक्षर *bench_name, bench_fn_t fn,
		     पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक size;
	अक्षर *name;
	पूर्णांक ret;

	size = म_माप(coll_name) + 1 + म_माप(bench_name) + 1;

	name = zalloc(size);
	BUG_ON(!name);

	scnम_लिखो(name, size, "%s-%s", coll_name, bench_name);

	prctl(PR_SET_NAME, name);
	argv[0] = name;

	ret = fn(argc, argv);

	मुक्त(name);

	वापस ret;
पूर्ण

अटल व्योम run_collection(काष्ठा collection *coll)
अणु
	काष्ठा bench *bench;
	स्थिर अक्षर *argv[2];

	argv[1] = शून्य;
	/*
	 * TODO:
	 *
	 * Preparing preset parameters क्रम
	 * embedded, ordinary PC, HPC, etc...
	 * would be helpful.
	 */
	क्रम_each_bench(coll, bench) अणु
		अगर (!bench->fn)
			अवरोध;
		म_लिखो("# Running %s/%s benchmark...\n", coll->name, bench->name);
		ख_साफ(मानक_निकास);

		argv[1] = bench->name;
		run_bench(coll->name, bench->name, bench->fn, 1, argv);
		म_लिखो("\n");
	पूर्ण
पूर्ण

अटल व्योम run_all_collections(व्योम)
अणु
	काष्ठा collection *coll;

	क्रम_each_collection(coll)
		run_collection(coll);
पूर्ण

पूर्णांक cmd_bench(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा collection *coll;
	पूर्णांक ret = 0;

	अगर (argc < 2) अणु
		/* No collection specअगरied. */
		prपूर्णांक_usage();
		जाओ end;
	पूर्ण

	argc = parse_options(argc, argv, bench_options, bench_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);

	bench_क्रमmat = bench_str2पूर्णांक(bench_क्रमmat_str);
	अगर (bench_क्रमmat == BENCH_FORMAT_UNKNOWN) अणु
		म_लिखो("Unknown format descriptor: '%s'\n", bench_क्रमmat_str);
		जाओ end;
	पूर्ण

	अगर (bench_repeat == 0) अणु
		म_लिखो("Invalid repeat option: Must specify a positive value\n");
		जाओ end;
	पूर्ण

	अगर (argc < 1) अणु
		prपूर्णांक_usage();
		जाओ end;
	पूर्ण

	अगर (!म_भेद(argv[0], "all")) अणु
		run_all_collections();
		जाओ end;
	पूर्ण

	क्रम_each_collection(coll) अणु
		काष्ठा bench *bench;

		अगर (म_भेद(coll->name, argv[0]))
			जारी;

		अगर (argc < 2) अणु
			/* No bench specअगरied. */
			dump_benchmarks(coll);
			जाओ end;
		पूर्ण

		अगर (!म_भेद(argv[1], "all")) अणु
			run_collection(coll);
			जाओ end;
		पूर्ण

		क्रम_each_bench(coll, bench) अणु
			अगर (म_भेद(bench->name, argv[1]))
				जारी;

			अगर (bench_क्रमmat == BENCH_FORMAT_DEFAULT)
				म_लिखो("# Running '%s/%s' benchmark:\n", coll->name, bench->name);
			ख_साफ(मानक_निकास);
			ret = run_bench(coll->name, bench->name, bench->fn, argc-1, argv+1);
			जाओ end;
		पूर्ण

		अगर (!म_भेद(argv[1], "-h") || !म_भेद(argv[1], "--help")) अणु
			dump_benchmarks(coll);
			जाओ end;
		पूर्ण

		म_लिखो("Unknown benchmark: '%s' for collection '%s'\n", argv[1], argv[0]);
		ret = 1;
		जाओ end;
	पूर्ण

	म_लिखो("Unknown collection: '%s'\n", argv[0]);
	ret = 1;

end:
	वापस ret;
पूर्ण
