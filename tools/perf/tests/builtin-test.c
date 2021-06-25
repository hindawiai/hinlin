<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * builtin-test.c
 *
 * Builtin regression testing command: ever growing number of sanity tests
 */
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <sys/types.h>
#समावेश <dirent.h>
#समावेश <sys/रुको.h>
#समावेश <sys/स्थिति.स>
#समावेश "builtin.h"
#समावेश "hist.h"
#समावेश "intlist.h"
#समावेश "tests.h"
#समावेश "debug.h"
#समावेश "color.h"
#समावेश <subcmd/parse-options.h>
#समावेश "string2.h"
#समावेश "symbol.h"
#समावेश "util/rlimit.h"
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <subcmd/exec-cmd.h>

अटल bool करोnt_विभाजन;

काष्ठा test __weak arch_tests[] = अणु
	अणु
		.func = शून्य,
	पूर्ण,
पूर्ण;

अटल काष्ठा test generic_tests[] = अणु
	अणु
		.desc = "vmlinux symtab matches kallsyms",
		.func = test__vmlinux_matches_kallsyms,
	पूर्ण,
	अणु
		.desc = "Detect openat syscall event",
		.func = test__खोलोat_syscall_event,
	पूर्ण,
	अणु
		.desc = "Detect openat syscall event on all cpus",
		.func = test__खोलोat_syscall_event_on_all_cpus,
	पूर्ण,
	अणु
		.desc = "Read samples using the mmap interface",
		.func = test__basic_mmap,
	पूर्ण,
	अणु
		.desc = "Test data source output",
		.func = test__mem,
	पूर्ण,
	अणु
		.desc = "Parse event definition strings",
		.func = test__parse_events,
	पूर्ण,
	अणु
		.desc = "Simple expression parser",
		.func = test__expr,
	पूर्ण,
	अणु
		.desc = "PERF_RECORD_* events & perf_sample fields",
		.func = test__PERF_RECORD,
	पूर्ण,
	अणु
		.desc = "Parse perf pmu format",
		.func = test__pmu,
	पूर्ण,
	अणु
		.desc = "PMU events",
		.func = test__pmu_events,
		.subtest = अणु
			.skip_अगर_fail	= false,
			.get_nr		= test__pmu_events_subtest_get_nr,
			.get_desc	= test__pmu_events_subtest_get_desc,
			.skip_reason	= test__pmu_events_subtest_skip_reason,
		पूर्ण,

	पूर्ण,
	अणु
		.desc = "DSO data read",
		.func = test__dso_data,
	पूर्ण,
	अणु
		.desc = "DSO data cache",
		.func = test__dso_data_cache,
	पूर्ण,
	अणु
		.desc = "DSO data reopen",
		.func = test__dso_data_reखोलो,
	पूर्ण,
	अणु
		.desc = "Roundtrip evsel->name",
		.func = test__perf_evsel__roundtrip_name_test,
	पूर्ण,
	अणु
		.desc = "Parse sched tracepoints fields",
		.func = test__perf_evsel__tp_sched_test,
	पूर्ण,
	अणु
		.desc = "syscalls:sys_enter_openat event fields",
		.func = test__syscall_खोलोat_tp_fields,
	पूर्ण,
	अणु
		.desc = "Setup struct perf_event_attr",
		.func = test__attr,
	पूर्ण,
	अणु
		.desc = "Match and link multiple hists",
		.func = test__hists_link,
	पूर्ण,
	अणु
		.desc = "'import perf' in python",
		.func = test__python_use,
	पूर्ण,
	अणु
		.desc = "Breakpoint overflow signal handler",
		.func = test__bp_संकेत,
		.is_supported = test__bp_संकेत_is_supported,
	पूर्ण,
	अणु
		.desc = "Breakpoint overflow sampling",
		.func = test__bp_संकेत_overflow,
		.is_supported = test__bp_संकेत_is_supported,
	पूर्ण,
	अणु
		.desc = "Breakpoint accounting",
		.func = test__bp_accounting,
		.is_supported = test__bp_account_is_supported,
	पूर्ण,
	अणु
		.desc = "Watchpoint",
		.func = test__wp,
		.is_supported = test__wp_is_supported,
		.subtest = अणु
			.skip_अगर_fail	= false,
			.get_nr		= test__wp_subtest_get_nr,
			.get_desc	= test__wp_subtest_get_desc,
			.skip_reason    = test__wp_subtest_skip_reason,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = "Number of exit events of a simple workload",
		.func = test__task_निकास,
	पूर्ण,
	अणु
		.desc = "Software clock events period values",
		.func = test__sw_घड़ी_freq,
	पूर्ण,
	अणु
		.desc = "Object code reading",
		.func = test__code_पढ़ोing,
	पूर्ण,
	अणु
		.desc = "Sample parsing",
		.func = test__sample_parsing,
	पूर्ण,
	अणु
		.desc = "Use a dummy software event to keep tracking",
		.func = test__keep_tracking,
	पूर्ण,
	अणु
		.desc = "Parse with no sample_id_all bit set",
		.func = test__parse_no_sample_id_all,
	पूर्ण,
	अणु
		.desc = "Filter hist entries",
		.func = test__hists_filter,
	पूर्ण,
	अणु
		.desc = "Lookup mmap thread",
		.func = test__mmap_thपढ़ो_lookup,
	पूर्ण,
	अणु
		.desc = "Share thread maps",
		.func = test__thपढ़ो_maps_share,
	पूर्ण,
	अणु
		.desc = "Sort output of hist entries",
		.func = test__hists_output,
	पूर्ण,
	अणु
		.desc = "Cumulate child hist entries",
		.func = test__hists_cumulate,
	पूर्ण,
	अणु
		.desc = "Track with sched_switch",
		.func = test__चयन_tracking,
	पूर्ण,
	अणु
		.desc = "Filter fds with revents mask in a fdarray",
		.func = test__fdarray__filter,
	पूर्ण,
	अणु
		.desc = "Add fd to a fdarray, making it autogrow",
		.func = test__fdarray__add,
	पूर्ण,
	अणु
		.desc = "kmod_path__parse",
		.func = test__kmod_path__parse,
	पूर्ण,
	अणु
		.desc = "Thread map",
		.func = test__thपढ़ो_map,
	पूर्ण,
	अणु
		.desc = "LLVM search and compile",
		.func = test__llvm,
		.subtest = अणु
			.skip_अगर_fail	= true,
			.get_nr		= test__llvm_subtest_get_nr,
			.get_desc	= test__llvm_subtest_get_desc,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = "Session topology",
		.func = test__session_topology,
	पूर्ण,
	अणु
		.desc = "BPF filter",
		.func = test__bpf,
		.subtest = अणु
			.skip_अगर_fail	= true,
			.get_nr		= test__bpf_subtest_get_nr,
			.get_desc	= test__bpf_subtest_get_desc,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = "Synthesize thread map",
		.func = test__thपढ़ो_map_synthesize,
	पूर्ण,
	अणु
		.desc = "Remove thread map",
		.func = test__thपढ़ो_map_हटाओ,
	पूर्ण,
	अणु
		.desc = "Synthesize cpu map",
		.func = test__cpu_map_synthesize,
	पूर्ण,
	अणु
		.desc = "Synthesize stat config",
		.func = test__synthesize_stat_config,
	पूर्ण,
	अणु
		.desc = "Synthesize stat",
		.func = test__synthesize_stat,
	पूर्ण,
	अणु
		.desc = "Synthesize stat round",
		.func = test__synthesize_stat_round,
	पूर्ण,
	अणु
		.desc = "Synthesize attr update",
		.func = test__event_update,
	पूर्ण,
	अणु
		.desc = "Event times",
		.func = test__event_बार,
	पूर्ण,
	अणु
		.desc = "Read backward ring buffer",
		.func = test__backward_ring_buffer,
	पूर्ण,
	अणु
		.desc = "Print cpu map",
		.func = test__cpu_map_prपूर्णांक,
	पूर्ण,
	अणु
		.desc = "Merge cpu map",
		.func = test__cpu_map_merge,
	पूर्ण,

	अणु
		.desc = "Probe SDT events",
		.func = test__sdt_event,
	पूर्ण,
	अणु
		.desc = "is_printable_array",
		.func = test__is_prपूर्णांकable_array,
	पूर्ण,
	अणु
		.desc = "Print bitmap",
		.func = test__biपंचांगap_prपूर्णांक,
	पूर्ण,
	अणु
		.desc = "perf hooks",
		.func = test__perf_hooks,
	पूर्ण,
	अणु
		.desc = "builtin clang support",
		.func = test__clang,
		.subtest = अणु
			.skip_अगर_fail	= true,
			.get_nr		= test__clang_subtest_get_nr,
			.get_desc	= test__clang_subtest_get_desc,
		पूर्ण
	पूर्ण,
	अणु
		.desc = "unit_number__scnprintf",
		.func = test__unit_number__scnprपूर्णांक,
	पूर्ण,
	अणु
		.desc = "mem2node",
		.func = test__mem2node,
	पूर्ण,
	अणु
		.desc = "time utils",
		.func = test__समय_utils,
	पूर्ण,
	अणु
		.desc = "Test jit_write_elf",
		.func = test__jit_ग_लिखो_elf,
	पूर्ण,
	अणु
		.desc = "Test libpfm4 support",
		.func = test__pfm,
		.subtest = अणु
			.skip_अगर_fail	= true,
			.get_nr		= test__pfm_subtest_get_nr,
			.get_desc	= test__pfm_subtest_get_desc,
		पूर्ण
	पूर्ण,
	अणु
		.desc = "Test api io",
		.func = test__api_io,
	पूर्ण,
	अणु
		.desc = "maps__merge_in",
		.func = test__maps__merge_in,
	पूर्ण,
	अणु
		.desc = "Demangle Java",
		.func = test__demangle_java,
	पूर्ण,
	अणु
		.desc = "Demangle OCaml",
		.func = test__demangle_ocaml,
	पूर्ण,
	अणु
		.desc = "Parse and process metrics",
		.func = test__parse_metric,
	पूर्ण,
	अणु
		.desc = "PE file support",
		.func = test__pe_file_parsing,
	पूर्ण,
	अणु
		.desc = "Event expansion for cgroups",
		.func = test__expand_cgroup_events,
	पूर्ण,
	अणु
		.desc = "Convert perf time to TSC",
		.func = test__perf_समय_प्रकारo_tsc,
		.is_supported = test__tsc_is_supported,
	पूर्ण,
	अणु
		.func = शून्य,
	पूर्ण,
पूर्ण;

अटल काष्ठा test *tests[] = अणु
	generic_tests,
	arch_tests,
पूर्ण;

अटल bool perf_test__matches(स्थिर अक्षर *desc, पूर्णांक curr, पूर्णांक argc, स्थिर अक्षर *argv[])
अणु
	पूर्णांक i;

	अगर (argc == 0)
		वापस true;

	क्रम (i = 0; i < argc; ++i) अणु
		अक्षर *end;
		दीर्घ nr = म_से_अदीर्घ(argv[i], &end, 10);

		अगर (*end == '\0') अणु
			अगर (nr == curr + 1)
				वापस true;
			जारी;
		पूर्ण

		अगर (strहालstr(desc, argv[i]))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक run_test(काष्ठा test *test, पूर्णांक subtest)
अणु
	पूर्णांक status, err = -1, child = करोnt_विभाजन ? 0 : विभाजन();
	अक्षर sbuf[STRERR_बफ_मानE];

	अगर (child < 0) अणु
		pr_err("failed to fork test: %s\n",
			str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		वापस -1;
	पूर्ण

	अगर (!child) अणु
		अगर (!करोnt_विभाजन) अणु
			pr_debug("test child forked, pid %d\n", getpid());

			अगर (verbose <= 0) अणु
				पूर्णांक nullfd = खोलो("/dev/null", O_WRONLY);

				अगर (nullfd >= 0) अणु
					बंद(STDERR_खाताNO);
					बंद(STDOUT_खाताNO);

					dup2(nullfd, STDOUT_खाताNO);
					dup2(STDOUT_खाताNO, STDERR_खाताNO);
					बंद(nullfd);
				पूर्ण
			पूर्ण अन्यथा अणु
				संकेत(संक_अंश, sighandler_dump_stack);
				संकेत(संक_भ_त्रुटि, sighandler_dump_stack);
			पूर्ण
		पूर्ण

		err = test->func(test, subtest);
		अगर (!करोnt_विभाजन)
			निकास(err);
	पूर्ण

	अगर (!करोnt_विभाजन) अणु
		रुको(&status);

		अगर (WIFEXITED(status)) अणु
			err = (चिन्हित अक्षर)WEXITSTATUS(status);
			pr_debug("test child finished with %d\n", err);
		पूर्ण अन्यथा अगर (WIFSIGNALED(status)) अणु
			err = -1;
			pr_debug("test child interrupted\n");
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

#घोषणा क्रम_each_test(j, t)	 				\
	क्रम (j = 0; j < ARRAY_SIZE(tests); j++)	\
		क्रम (t = &tests[j][0]; t->func; t++)

अटल पूर्णांक test_and_prपूर्णांक(काष्ठा test *t, bool क्रमce_skip, पूर्णांक subtest)
अणु
	पूर्णांक err;

	अगर (!क्रमce_skip) अणु
		pr_debug("\n--- start ---\n");
		err = run_test(t, subtest);
		pr_debug("---- end ----\n");
	पूर्ण अन्यथा अणु
		pr_debug("\n--- force skipped ---\n");
		err = TEST_SKIP;
	पूर्ण

	अगर (!t->subtest.get_nr)
		pr_debug("%s:", t->desc);
	अन्यथा
		pr_debug("%s subtest %d:", t->desc, subtest + 1);

	चयन (err) अणु
	हाल TEST_OK:
		pr_info(" Ok\n");
		अवरोध;
	हाल TEST_SKIP: अणु
		स्थिर अक्षर *skip_reason = शून्य;
		अगर (t->subtest.skip_reason)
			skip_reason = t->subtest.skip_reason(subtest);
		अगर (skip_reason)
			color_ख_लिखो(मानक_त्रुटि, PERF_COLOR_YELLOW, " Skip (%s)\n", skip_reason);
		अन्यथा
			color_ख_लिखो(मानक_त्रुटि, PERF_COLOR_YELLOW, " Skip\n");
	पूर्ण
		अवरोध;
	हाल TEST_FAIL:
	शेष:
		color_ख_लिखो(मानक_त्रुटि, PERF_COLOR_RED, " FAILED!\n");
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर अक्षर *shell_test__description(अक्षर *description, माप_प्रकार size,
					   स्थिर अक्षर *path, स्थिर अक्षर *name)
अणु
	खाता *fp;
	अक्षर filename[PATH_MAX];

	path__join(filename, माप(filename), path, name);
	fp = ख_खोलो(filename, "r");
	अगर (!fp)
		वापस शून्य;

	/* Skip shebang */
	जबतक (ख_अक्षर_लो(fp) != '\n');

	description = ख_माला_लो(description, size, fp);
	ख_बंद(fp);

	वापस description ? strim(description + 1) : शून्य;
पूर्ण

#घोषणा क्रम_each_shell_test(dir, base, ent)	\
	जबतक ((ent = सूची_पढ़ो(dir)) != शून्य)	\
		अगर (!is_directory(base, ent) && ent->d_name[0] != '.')

अटल स्थिर अक्षर *shell_tests__dir(अक्षर *path, माप_प्रकार size)
अणु
	स्थिर अक्षर *devel_dirs[] = अणु "./tools/perf/tests", "./tests", पूर्ण;
        अक्षर *exec_path;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(devel_dirs); ++i) अणु
		काष्ठा stat st;
		अगर (!lstat(devel_dirs[i], &st)) अणु
			scnम_लिखो(path, size, "%s/shell", devel_dirs[i]);
			अगर (!lstat(devel_dirs[i], &st))
				वापस path;
		पूर्ण
	पूर्ण

        /* Then installed path. */
        exec_path = get_argv_exec_path();
        scnम_लिखो(path, size, "%s/tests/shell", exec_path);
	मुक्त(exec_path);
	वापस path;
पूर्ण

अटल पूर्णांक shell_tests__max_desc_width(व्योम)
अणु
	सूची *dir;
	काष्ठा dirent *ent;
	अक्षर path_dir[PATH_MAX];
	स्थिर अक्षर *path = shell_tests__dir(path_dir, माप(path_dir));
	पूर्णांक width = 0;

	अगर (path == शून्य)
		वापस -1;

	dir = सूची_खोलो(path);
	अगर (!dir)
		वापस -1;

	क्रम_each_shell_test(dir, path, ent) अणु
		अक्षर bf[256];
		स्थिर अक्षर *desc = shell_test__description(bf, माप(bf), path, ent->d_name);

		अगर (desc) अणु
			पूर्णांक len = म_माप(desc);

			अगर (width < len)
				width = len;
		पूर्ण
	पूर्ण

	बंद_सूची(dir);
	वापस width;
पूर्ण

काष्ठा shell_test अणु
	स्थिर अक्षर *dir;
	स्थिर अक्षर *file;
पूर्ण;

अटल पूर्णांक shell_test__run(काष्ठा test *test, पूर्णांक subdir __maybe_unused)
अणु
	पूर्णांक err;
	अक्षर script[PATH_MAX];
	काष्ठा shell_test *st = test->priv;

	path__join(script, माप(script), st->dir, st->file);

	err = प्रणाली(script);
	अगर (!err)
		वापस TEST_OK;

	वापस WEXITSTATUS(err) == 2 ? TEST_SKIP : TEST_FAIL;
पूर्ण

अटल पूर्णांक run_shell_tests(पूर्णांक argc, स्थिर अक्षर *argv[], पूर्णांक i, पूर्णांक width)
अणु
	सूची *dir;
	काष्ठा dirent *ent;
	अक्षर path_dir[PATH_MAX];
	काष्ठा shell_test st = अणु
		.dir = shell_tests__dir(path_dir, माप(path_dir)),
	पूर्ण;

	अगर (st.dir == शून्य)
		वापस -1;

	dir = सूची_खोलो(st.dir);
	अगर (!dir) अणु
		pr_err("failed to open shell test directory: %s\n",
			st.dir);
		वापस -1;
	पूर्ण

	क्रम_each_shell_test(dir, st.dir, ent) अणु
		पूर्णांक curr = i++;
		अक्षर desc[256];
		काष्ठा test test = अणु
			.desc = shell_test__description(desc, माप(desc), st.dir, ent->d_name),
			.func = shell_test__run,
			.priv = &st,
		पूर्ण;

		अगर (!perf_test__matches(test.desc, curr, argc, argv))
			जारी;

		st.file = ent->d_name;
		pr_info("%2d: %-*s:", i, width, test.desc);
		test_and_prपूर्णांक(&test, false, -1);
	पूर्ण

	बंद_सूची(dir);
	वापस 0;
पूर्ण

अटल पूर्णांक __cmd_test(पूर्णांक argc, स्थिर अक्षर *argv[], काष्ठा पूर्णांकlist *skiplist)
अणु
	काष्ठा test *t;
	अचिन्हित पूर्णांक j;
	पूर्णांक i = 0;
	पूर्णांक width = shell_tests__max_desc_width();

	क्रम_each_test(j, t) अणु
		पूर्णांक len = म_माप(t->desc);

		अगर (width < len)
			width = len;
	पूर्ण

	क्रम_each_test(j, t) अणु
		पूर्णांक curr = i++, err;
		पूर्णांक subi;

		अगर (!perf_test__matches(t->desc, curr, argc, argv)) अणु
			bool skip = true;
			पूर्णांक subn;

			अगर (!t->subtest.get_nr)
				जारी;

			subn = t->subtest.get_nr();

			क्रम (subi = 0; subi < subn; subi++) अणु
				अगर (perf_test__matches(t->subtest.get_desc(subi), curr, argc, argv))
					skip = false;
			पूर्ण

			अगर (skip)
				जारी;
		पूर्ण

		अगर (t->is_supported && !t->is_supported()) अणु
			pr_debug("%2d: %-*s: Disabled\n", i, width, t->desc);
			जारी;
		पूर्ण

		pr_info("%2d: %-*s:", i, width, t->desc);

		अगर (पूर्णांकlist__find(skiplist, i)) अणु
			color_ख_लिखो(मानक_त्रुटि, PERF_COLOR_YELLOW, " Skip (user override)\n");
			जारी;
		पूर्ण

		अगर (!t->subtest.get_nr) अणु
			test_and_prपूर्णांक(t, false, -1);
		पूर्ण अन्यथा अणु
			पूर्णांक subn = t->subtest.get_nr();
			/*
			 * minus 2 to align with normal testहालs.
			 * For subtest we prपूर्णांक additional '.x' in number.
			 * क्रम example:
			 *
			 * 35: Test LLVM searching and compiling                        :
			 * 35.1: Basic BPF llvm compiling test                          : Ok
			 */
			पूर्णांक subw = width > 2 ? width - 2 : width;
			bool skip = false;

			अगर (subn <= 0) अणु
				color_ख_लिखो(मानक_त्रुटि, PERF_COLOR_YELLOW,
					      " Skip (not compiled in)\n");
				जारी;
			पूर्ण
			pr_info("\n");

			क्रम (subi = 0; subi < subn; subi++) अणु
				पूर्णांक len = म_माप(t->subtest.get_desc(subi));

				अगर (subw < len)
					subw = len;
			पूर्ण

			क्रम (subi = 0; subi < subn; subi++) अणु
				अगर (!perf_test__matches(t->subtest.get_desc(subi), curr, argc, argv))
					जारी;

				pr_info("%2d.%1d: %-*s:", i, subi + 1, subw,
					t->subtest.get_desc(subi));
				err = test_and_prपूर्णांक(t, skip, subi);
				अगर (err != TEST_OK && t->subtest.skip_अगर_fail)
					skip = true;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस run_shell_tests(argc, argv, i, width);
पूर्ण

अटल पूर्णांक perf_test__list_shell(पूर्णांक argc, स्थिर अक्षर **argv, पूर्णांक i)
अणु
	सूची *dir;
	काष्ठा dirent *ent;
	अक्षर path_dir[PATH_MAX];
	स्थिर अक्षर *path = shell_tests__dir(path_dir, माप(path_dir));

	अगर (path == शून्य)
		वापस -1;

	dir = सूची_खोलो(path);
	अगर (!dir)
		वापस -1;

	क्रम_each_shell_test(dir, path, ent) अणु
		पूर्णांक curr = i++;
		अक्षर bf[256];
		काष्ठा test t = अणु
			.desc = shell_test__description(bf, माप(bf), path, ent->d_name),
		पूर्ण;

		अगर (!perf_test__matches(t.desc, curr, argc, argv))
			जारी;

		pr_info("%2d: %s\n", i, t.desc);
	पूर्ण

	बंद_सूची(dir);
	वापस 0;
पूर्ण

अटल पूर्णांक perf_test__list(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अचिन्हित पूर्णांक j;
	काष्ठा test *t;
	पूर्णांक i = 0;

	क्रम_each_test(j, t) अणु
		पूर्णांक curr = i++;

		अगर (!perf_test__matches(t->desc, curr, argc, argv) ||
		    (t->is_supported && !t->is_supported()))
			जारी;

		pr_info("%2d: %s\n", i, t->desc);

		अगर (t->subtest.get_nr) अणु
			पूर्णांक subn = t->subtest.get_nr();
			पूर्णांक subi;

			क्रम (subi = 0; subi < subn; subi++)
				pr_info("%2d:%1d: %s\n", i, subi + 1,
					t->subtest.get_desc(subi));
		पूर्ण
	पूर्ण

	perf_test__list_shell(argc, argv, i);

	वापस 0;
पूर्ण

पूर्णांक cmd_test(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर अक्षर *test_usage[] = अणु
	"perf test [<options>] [{list <test-name-fragment>|[<test-name-fragments>|<test-numbers>]}]",
	शून्य,
	पूर्ण;
	स्थिर अक्षर *skip = शून्य;
	स्थिर काष्ठा option test_options[] = अणु
	OPT_STRING('s', "skip", &skip, "tests", "tests to skip"),
	OPT_INCR('v', "verbose", &verbose,
		    "be more verbose (show symbol address, etc)"),
	OPT_BOOLEAN('F', "dont-fork", &करोnt_विभाजन,
		    "Do not fork for testcase"),
	OPT_END()
	पूर्ण;
	स्थिर अक्षर * स्थिर test_subcommands[] = अणु "list", शून्य पूर्ण;
	काष्ठा पूर्णांकlist *skiplist = शून्य;
        पूर्णांक ret = hists__init();

        अगर (ret < 0)
                वापस ret;

	argc = parse_options_subcommand(argc, argv, test_options, test_subcommands, test_usage, 0);
	अगर (argc >= 1 && !म_भेद(argv[0], "list"))
		वापस perf_test__list(argc - 1, argv + 1);

	symbol_conf.priv_size = माप(पूर्णांक);
	symbol_conf.sort_by_name = true;
	symbol_conf.try_vmlinux_path = true;

	अगर (symbol__init(शून्य) < 0)
		वापस -1;

	अगर (skip != शून्य)
		skiplist = पूर्णांकlist__new(skip);
	/*
	 * Tests that create BPF maps, क्रम instance, need more than the 64K
	 * शेष:
	 */
	rlimit__bump_memlock();

	वापस __cmd_test(argc, argv, skiplist);
पूर्ण
