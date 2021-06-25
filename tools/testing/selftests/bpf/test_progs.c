<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2017 Facebook
 */
#घोषणा _GNU_SOURCE
#समावेश "test_progs.h"
#समावेश "cgroup_helpers.h"
#समावेश "bpf_rlimit.h"
#समावेश <argp.h>
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <execinfo.h> /* backtrace */
#समावेश <linux/membarrier.h>

#घोषणा EXIT_NO_TEST		2
#घोषणा EXIT_ERR_SETUP_INFRA	3

/* defined in test_progs.h */
काष्ठा test_env env = अणुपूर्ण;

काष्ठा prog_test_def अणु
	स्थिर अक्षर *test_name;
	पूर्णांक test_num;
	व्योम (*run_test)(व्योम);
	bool क्रमce_log;
	पूर्णांक error_cnt;
	पूर्णांक skip_cnt;
	bool tested;
	bool need_cgroup_cleanup;

	अक्षर *subtest_name;
	पूर्णांक subtest_num;

	/* store counts beक्रमe subtest started */
	पूर्णांक old_error_cnt;
पूर्ण;

/* Override C runसमय library's usleep() implementation to ensure nanosleep()
 * is always called. Usleep is frequently used in selftests as a way to
 * trigger kprobe and tracepoपूर्णांकs.
 */
पूर्णांक usleep(useconds_t usec)
अणु
	काष्ठा बारpec ts = अणु
		.tv_sec = usec / 1000000,
		.tv_nsec = (usec % 1000000) * 1000,
	पूर्ण;

	वापस syscall(__NR_nanosleep, &ts, शून्य);
पूर्ण

अटल bool should_run(काष्ठा test_selector *sel, पूर्णांक num, स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sel->blacklist.cnt; i++) अणु
		अगर (म_माला(name, sel->blacklist.strs[i]))
			वापस false;
	पूर्ण

	क्रम (i = 0; i < sel->whitelist.cnt; i++) अणु
		अगर (म_माला(name, sel->whitelist.strs[i]))
			वापस true;
	पूर्ण

	अगर (!sel->whitelist.cnt && !sel->num_set)
		वापस true;

	वापस num < sel->num_set_len && sel->num_set[num];
पूर्ण

अटल व्योम dump_test_log(स्थिर काष्ठा prog_test_def *test, bool failed)
अणु
	अगर (मानक_निकास == env.मानक_निकास)
		वापस;

	ख_साफ(मानक_निकास); /* exports env.log_buf & env.log_cnt */

	अगर (env.verbosity > VERBOSE_NONE || test->क्रमce_log || failed) अणु
		अगर (env.log_cnt) अणु
			env.log_buf[env.log_cnt] = '\0';
			ख_लिखो(env.मानक_निकास, "%s", env.log_buf);
			अगर (env.log_buf[env.log_cnt - 1] != '\n')
				ख_लिखो(env.मानक_निकास, "\n");
		पूर्ण
	पूर्ण

	ख_जाओo(मानक_निकास, 0, शुरू_से); /* शुरुआत */
पूर्ण

अटल व्योम skip_account(व्योम)
अणु
	अगर (env.test->skip_cnt) अणु
		env.skip_cnt++;
		env.test->skip_cnt = 0;
	पूर्ण
पूर्ण

अटल व्योम stdio_restore(व्योम);

/* A bunch of tests set custom affinity per-thपढ़ो and/or per-process. Reset
 * it after each test/sub-test.
 */
अटल व्योम reset_affinity() अणु

	cpu_set_t cpuset;
	पूर्णांक i, err;

	CPU_ZERO(&cpuset);
	क्रम (i = 0; i < env.nr_cpus; i++)
		CPU_SET(i, &cpuset);

	err = sched_setaffinity(0, माप(cpuset), &cpuset);
	अगर (err < 0) अणु
		stdio_restore();
		ख_लिखो(मानक_त्रुटि, "Failed to reset process affinity: %d!\n", err);
		निकास(EXIT_ERR_SETUP_INFRA);
	पूर्ण
	err = pthपढ़ो_setaffinity_np(pthपढ़ो_self(), माप(cpuset), &cpuset);
	अगर (err < 0) अणु
		stdio_restore();
		ख_लिखो(मानक_त्रुटि, "Failed to reset thread affinity: %d!\n", err);
		निकास(EXIT_ERR_SETUP_INFRA);
	पूर्ण
पूर्ण

अटल व्योम save_netns(व्योम)
अणु
	env.saved_netns_fd = खोलो("/proc/self/ns/net", O_RDONLY);
	अगर (env.saved_netns_fd == -1) अणु
		लिखो_त्रुटि("open(/proc/self/ns/net)");
		निकास(EXIT_ERR_SETUP_INFRA);
	पूर्ण
पूर्ण

अटल व्योम restore_netns(व्योम)
अणु
	अगर (setns(env.saved_netns_fd, CLONE_NEWNET) == -1) अणु
		stdio_restore();
		लिखो_त्रुटि("setns(CLONE_NEWNS)");
		निकास(EXIT_ERR_SETUP_INFRA);
	पूर्ण
पूर्ण

व्योम test__end_subtest()
अणु
	काष्ठा prog_test_def *test = env.test;
	पूर्णांक sub_error_cnt = test->error_cnt - test->old_error_cnt;

	अगर (sub_error_cnt)
		env.fail_cnt++;
	अन्यथा अगर (test->skip_cnt == 0)
		env.sub_succ_cnt++;
	skip_account();

	dump_test_log(test, sub_error_cnt);

	ख_लिखो(env.मानक_निकास, "#%d/%d %s:%s\n",
	       test->test_num, test->subtest_num, test->subtest_name,
	       sub_error_cnt ? "FAIL" : (test->skip_cnt ? "SKIP" : "OK"));

	मुक्त(test->subtest_name);
	test->subtest_name = शून्य;
पूर्ण

bool test__start_subtest(स्थिर अक्षर *name)
अणु
	काष्ठा prog_test_def *test = env.test;

	अगर (test->subtest_name)
		test__end_subtest();

	test->subtest_num++;

	अगर (!name || !name[0]) अणु
		ख_लिखो(env.मानक_त्रुटि,
			"Subtest #%d didn't provide sub-test name!\n",
			test->subtest_num);
		वापस false;
	पूर्ण

	अगर (!should_run(&env.subtest_selector, test->subtest_num, name))
		वापस false;

	test->subtest_name = strdup(name);
	अगर (!test->subtest_name) अणु
		ख_लिखो(env.मानक_त्रुटि,
			"Subtest #%d: failed to copy subtest name!\n",
			test->subtest_num);
		वापस false;
	पूर्ण
	env.test->old_error_cnt = env.test->error_cnt;

	वापस true;
पूर्ण

व्योम test__क्रमce_log() अणु
	env.test->क्रमce_log = true;
पूर्ण

व्योम test__skip(व्योम)
अणु
	env.test->skip_cnt++;
पूर्ण

व्योम test__fail(व्योम)
अणु
	env.test->error_cnt++;
पूर्ण

पूर्णांक test__join_cgroup(स्थिर अक्षर *path)
अणु
	पूर्णांक fd;

	अगर (!env.test->need_cgroup_cleanup) अणु
		अगर (setup_cgroup_environment()) अणु
			ख_लिखो(मानक_त्रुटि,
				"#%d %s: Failed to setup cgroup environment\n",
				env.test->test_num, env.test->test_name);
			वापस -1;
		पूर्ण

		env.test->need_cgroup_cleanup = true;
	पूर्ण

	fd = create_and_get_cgroup(path);
	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि,
			"#%d %s: Failed to create cgroup '%s' (errno=%d)\n",
			env.test->test_num, env.test->test_name, path, त्रुटि_सं);
		वापस fd;
	पूर्ण

	अगर (join_cgroup(path)) अणु
		ख_लिखो(मानक_त्रुटि,
			"#%d %s: Failed to join cgroup '%s' (errno=%d)\n",
			env.test->test_num, env.test->test_name, path, त्रुटि_सं);
		वापस -1;
	पूर्ण

	वापस fd;
पूर्ण

पूर्णांक bpf_find_map(स्थिर अक्षर *test, काष्ठा bpf_object *obj, स्थिर अक्षर *name)
अणु
	काष्ठा bpf_map *map;

	map = bpf_object__find_map_by_name(obj, name);
	अगर (!map) अणु
		ख_लिखो(मानक_निकास, "%s:FAIL:map '%s' not found\n", test, name);
		test__fail();
		वापस -1;
	पूर्ण
	वापस bpf_map__fd(map);
पूर्ण

अटल bool is_jit_enabled(व्योम)
अणु
	स्थिर अक्षर *jit_sysctl = "/proc/sys/net/core/bpf_jit_enable";
	bool enabled = false;
	पूर्णांक sysctl_fd;

	sysctl_fd = खोलो(jit_sysctl, 0, O_RDONLY);
	अगर (sysctl_fd != -1) अणु
		अक्षर पंचांगpc;

		अगर (पढ़ो(sysctl_fd, &पंचांगpc, माप(पंचांगpc)) == 1)
			enabled = (पंचांगpc != '0');
		बंद(sysctl_fd);
	पूर्ण

	वापस enabled;
पूर्ण

पूर्णांक compare_map_keys(पूर्णांक map1_fd, पूर्णांक map2_fd)
अणु
	__u32 key, next_key;
	अक्षर val_buf[PERF_MAX_STACK_DEPTH *
		     माप(काष्ठा bpf_stack_build_id)];
	पूर्णांक err;

	err = bpf_map_get_next_key(map1_fd, शून्य, &key);
	अगर (err)
		वापस err;
	err = bpf_map_lookup_elem(map2_fd, &key, val_buf);
	अगर (err)
		वापस err;

	जबतक (bpf_map_get_next_key(map1_fd, &key, &next_key) == 0) अणु
		err = bpf_map_lookup_elem(map2_fd, &next_key, val_buf);
		अगर (err)
			वापस err;

		key = next_key;
	पूर्ण
	अगर (त्रुटि_सं != ENOENT)
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक compare_stack_ips(पूर्णांक smap_fd, पूर्णांक amap_fd, पूर्णांक stack_trace_len)
अणु
	__u32 key, next_key, *cur_key_p, *next_key_p;
	अक्षर *val_buf1, *val_buf2;
	पूर्णांक i, err = 0;

	val_buf1 = दो_स्मृति(stack_trace_len);
	val_buf2 = दो_स्मृति(stack_trace_len);
	cur_key_p = शून्य;
	next_key_p = &key;
	जबतक (bpf_map_get_next_key(smap_fd, cur_key_p, next_key_p) == 0) अणु
		err = bpf_map_lookup_elem(smap_fd, next_key_p, val_buf1);
		अगर (err)
			जाओ out;
		err = bpf_map_lookup_elem(amap_fd, next_key_p, val_buf2);
		अगर (err)
			जाओ out;
		क्रम (i = 0; i < stack_trace_len; i++) अणु
			अगर (val_buf1[i] != val_buf2[i]) अणु
				err = -1;
				जाओ out;
			पूर्ण
		पूर्ण
		key = *next_key_p;
		cur_key_p = &key;
		next_key_p = &next_key;
	पूर्ण
	अगर (त्रुटि_सं != ENOENT)
		err = -1;

out:
	मुक्त(val_buf1);
	मुक्त(val_buf2);
	वापस err;
पूर्ण

पूर्णांक extract_build_id(अक्षर *build_id, माप_प्रकार size)
अणु
	खाता *fp;
	अक्षर *line = शून्य;
	माप_प्रकार len = 0;

	fp = pखोलो("readelf -n ./urandom_read | grep 'Build ID'", "r");
	अगर (fp == शून्य)
		वापस -1;

	अगर (getline(&line, &len, fp) == -1)
		जाओ err;
	ख_बंद(fp);

	अगर (len > size)
		len = size;
	स_नकल(build_id, line, len);
	build_id[len] = '\0';
	मुक्त(line);
	वापस 0;
err:
	ख_बंद(fp);
	वापस -1;
पूर्ण

अटल पूर्णांक finit_module(पूर्णांक fd, स्थिर अक्षर *param_values, पूर्णांक flags)
अणु
	वापस syscall(__NR_finit_module, fd, param_values, flags);
पूर्ण

अटल पूर्णांक delete_module(स्थिर अक्षर *name, पूर्णांक flags)
अणु
	वापस syscall(__NR_delete_module, name, flags);
पूर्ण

/*
 * Trigger synchronize_rcu() in kernel.
 */
पूर्णांक kern_sync_rcu(व्योम)
अणु
	वापस syscall(__NR_membarrier, MEMBARRIER_CMD_SHARED, 0, 0);
पूर्ण

अटल व्योम unload_bpf_tesपंचांगod(व्योम)
अणु
	अगर (kern_sync_rcu())
		ख_लिखो(env.मानक_त्रुटि, "Failed to trigger kernel-side RCU sync!\n");
	अगर (delete_module("bpf_testmod", 0)) अणु
		अगर (त्रुटि_सं == ENOENT) अणु
			अगर (env.verbosity > VERBOSE_NONE)
				ख_लिखो(मानक_निकास, "bpf_testmod.ko is already unloaded.\n");
			वापस;
		पूर्ण
		ख_लिखो(env.मानक_त्रुटि, "Failed to unload bpf_testmod.ko from kernel: %d\n", -त्रुटि_सं);
		वापस;
	पूर्ण
	अगर (env.verbosity > VERBOSE_NONE)
		ख_लिखो(मानक_निकास, "Successfully unloaded bpf_testmod.ko.\n");
पूर्ण

अटल पूर्णांक load_bpf_tesपंचांगod(व्योम)
अणु
	पूर्णांक fd;

	/* ensure previous instance of the module is unloaded */
	unload_bpf_tesपंचांगod();

	अगर (env.verbosity > VERBOSE_NONE)
		ख_लिखो(मानक_निकास, "Loading bpf_testmod.ko...\n");

	fd = खोलो("bpf_testmod.ko", O_RDONLY);
	अगर (fd < 0) अणु
		ख_लिखो(env.मानक_त्रुटि, "Can't find bpf_testmod.ko kernel module: %d\n", -त्रुटि_सं);
		वापस -ENOENT;
	पूर्ण
	अगर (finit_module(fd, "", 0)) अणु
		ख_लिखो(env.मानक_त्रुटि, "Failed to load bpf_testmod.ko into the kernel: %d\n", -त्रुटि_सं);
		बंद(fd);
		वापस -EINVAL;
	पूर्ण
	बंद(fd);

	अगर (env.verbosity > VERBOSE_NONE)
		ख_लिखो(मानक_निकास, "Successfully loaded bpf_testmod.ko.\n");
	वापस 0;
पूर्ण

/* बाह्य declarations क्रम test funcs */
#घोषणा DEFINE_TEST(name) बाह्य व्योम test_##name(व्योम);
#समावेश <prog_tests/tests.h>
#अघोषित DEFINE_TEST

अटल काष्ठा prog_test_def prog_test_defs[] = अणु
#घोषणा DEFINE_TEST(name) अणु		\
	.test_name = #name,		\
	.run_test = &test_##name,	\
पूर्ण,
#समावेश <prog_tests/tests.h>
#अघोषित DEFINE_TEST
पूर्ण;
स्थिर पूर्णांक prog_test_cnt = ARRAY_SIZE(prog_test_defs);

स्थिर अक्षर *argp_program_version = "test_progs 0.1";
स्थिर अक्षर *argp_program_bug_address = "<bpf@vger.kernel.org>";
स्थिर अक्षर argp_program_करोc[] = "BPF selftests test runner";

क्रमागत ARG_KEYS अणु
	ARG_TEST_NUM = 'n',
	ARG_TEST_NAME = 't',
	ARG_TEST_NAME_BLACKLIST = 'b',
	ARG_VERIFIER_STATS = 's',
	ARG_VERBOSE = 'v',
	ARG_GET_TEST_CNT = 'c',
	ARG_LIST_TEST_NAMES = 'l',
पूर्ण;

अटल स्थिर काष्ठा argp_option opts[] = अणु
	अणु "num", ARG_TEST_NUM, "NUM", 0,
	  "Run test number NUM only " पूर्ण,
	अणु "name", ARG_TEST_NAME, "NAMES", 0,
	  "Run tests with names containing any string from NAMES list" पूर्ण,
	अणु "name-blacklist", ARG_TEST_NAME_BLACKLIST, "NAMES", 0,
	  "Don't run tests with names containing any string from NAMES list" पूर्ण,
	अणु "verifier-stats", ARG_VERIFIER_STATS, शून्य, 0,
	  "Output verifier statistics", पूर्ण,
	अणु "verbose", ARG_VERBOSE, "LEVEL", OPTION_ARG_OPTIONAL,
	  "Verbose output (use -vv or -vvv for progressively verbose output)" पूर्ण,
	अणु "count", ARG_GET_TEST_CNT, शून्य, 0,
	  "Get number of selected top-level tests " पूर्ण,
	अणु "list", ARG_LIST_TEST_NAMES, शून्य, 0,
	  "List test names that would run (without running them) " पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक libbpf_prपूर्णांक_fn(क्रमागत libbpf_prपूर्णांक_level level,
			   स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	अगर (env.verbosity < VERBOSE_VERY && level == LIBBPF_DEBUG)
		वापस 0;
	भख_लिखो(मानक_निकास, क्रमmat, args);
	वापस 0;
पूर्ण

अटल व्योम मुक्त_str_set(स्थिर काष्ठा str_set *set)
अणु
	पूर्णांक i;

	अगर (!set)
		वापस;

	क्रम (i = 0; i < set->cnt; i++)
		मुक्त((व्योम *)set->strs[i]);
	मुक्त(set->strs);
पूर्ण

अटल पूर्णांक parse_str_list(स्थिर अक्षर *s, काष्ठा str_set *set)
अणु
	अक्षर *input, *state = शून्य, *next, **पंचांगp, **strs = शून्य;
	पूर्णांक cnt = 0;

	input = strdup(s);
	अगर (!input)
		वापस -ENOMEM;

	set->cnt = 0;
	set->strs = शून्य;

	जबतक ((next = म_मोहर_r(state ? शून्य : input, ",", &state))) अणु
		पंचांगp = पुनः_स्मृति(strs, माप(*strs) * (cnt + 1));
		अगर (!पंचांगp)
			जाओ err;
		strs = पंचांगp;

		strs[cnt] = strdup(next);
		अगर (!strs[cnt])
			जाओ err;

		cnt++;
	पूर्ण

	set->cnt = cnt;
	set->strs = (स्थिर अक्षर **)strs;
	मुक्त(input);
	वापस 0;
err:
	मुक्त(strs);
	मुक्त(input);
	वापस -ENOMEM;
पूर्ण

बाह्य पूर्णांक extra_prog_load_log_flags;

अटल error_t parse_arg(पूर्णांक key, अक्षर *arg, काष्ठा argp_state *state)
अणु
	काष्ठा test_env *env = state->input;

	चयन (key) अणु
	हाल ARG_TEST_NUM: अणु
		अक्षर *subtest_str = म_अक्षर(arg, '/');

		अगर (subtest_str) अणु
			*subtest_str = '\0';
			अगर (parse_num_list(subtest_str + 1,
					   &env->subtest_selector.num_set,
					   &env->subtest_selector.num_set_len)) अणु
				ख_लिखो(मानक_त्रुटि,
					"Failed to parse subtest numbers.\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अगर (parse_num_list(arg, &env->test_selector.num_set,
				   &env->test_selector.num_set_len)) अणु
			ख_लिखो(मानक_त्रुटि, "Failed to parse test numbers.\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल ARG_TEST_NAME: अणु
		अक्षर *subtest_str = म_अक्षर(arg, '/');

		अगर (subtest_str) अणु
			*subtest_str = '\0';
			अगर (parse_str_list(subtest_str + 1,
					   &env->subtest_selector.whitelist))
				वापस -ENOMEM;
		पूर्ण
		अगर (parse_str_list(arg, &env->test_selector.whitelist))
			वापस -ENOMEM;
		अवरोध;
	पूर्ण
	हाल ARG_TEST_NAME_BLACKLIST: अणु
		अक्षर *subtest_str = म_अक्षर(arg, '/');

		अगर (subtest_str) अणु
			*subtest_str = '\0';
			अगर (parse_str_list(subtest_str + 1,
					   &env->subtest_selector.blacklist))
				वापस -ENOMEM;
		पूर्ण
		अगर (parse_str_list(arg, &env->test_selector.blacklist))
			वापस -ENOMEM;
		अवरोध;
	पूर्ण
	हाल ARG_VERIFIER_STATS:
		env->verअगरier_stats = true;
		अवरोध;
	हाल ARG_VERBOSE:
		env->verbosity = VERBOSE_NORMAL;
		अगर (arg) अणु
			अगर (म_भेद(arg, "v") == 0) अणु
				env->verbosity = VERBOSE_VERY;
				extra_prog_load_log_flags = 1;
			पूर्ण अन्यथा अगर (म_भेद(arg, "vv") == 0) अणु
				env->verbosity = VERBOSE_SUPER;
				extra_prog_load_log_flags = 2;
			पूर्ण अन्यथा अणु
				ख_लिखो(मानक_त्रुटि,
					"Unrecognized verbosity setting ('%s'), only -v and -vv are supported\n",
					arg);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		अगर (env->verbosity > VERBOSE_NONE) अणु
			अगर (setenv("SELFTESTS_VERBOSE", "1", 1) == -1) अणु
				ख_लिखो(मानक_त्रुटि,
					"Unable to setenv SELFTESTS_VERBOSE=1 (errno=%d)",
					त्रुटि_सं);
				वापस -1;
			पूर्ण
		पूर्ण

		अवरोध;
	हाल ARG_GET_TEST_CNT:
		env->get_test_cnt = true;
		अवरोध;
	हाल ARG_LIST_TEST_NAMES:
		env->list_test_names = true;
		अवरोध;
	हाल ARGP_KEY_ARG:
		argp_usage(state);
		अवरोध;
	हाल ARGP_KEY_END:
		अवरोध;
	शेष:
		वापस ARGP_ERR_UNKNOWN;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम stdio_hijack(व्योम)
अणु
#अगर_घोषित __GLIBC__
	env.मानक_निकास = मानक_निकास;
	env.मानक_त्रुटि = मानक_त्रुटि;

	अगर (env.verbosity > VERBOSE_NONE) अणु
		/* nothing to करो, output to मानक_निकास by शेष */
		वापस;
	पूर्ण

	/* मानक_निकास and मानक_त्रुटि -> buffer */
	ख_साफ(मानक_निकास);

	मानक_निकास = खोलो_memstream(&env.log_buf, &env.log_cnt);
	अगर (!मानक_निकास) अणु
		मानक_निकास = env.मानक_निकास;
		लिखो_त्रुटि("open_memstream");
		वापस;
	पूर्ण

	मानक_त्रुटि = मानक_निकास;
#पूर्ण_अगर
पूर्ण

अटल व्योम stdio_restore(व्योम)
अणु
#अगर_घोषित __GLIBC__
	अगर (मानक_निकास == env.मानक_निकास)
		वापस;

	ख_बंद(मानक_निकास);
	मुक्त(env.log_buf);

	env.log_buf = शून्य;
	env.log_cnt = 0;

	मानक_निकास = env.मानक_निकास;
	मानक_त्रुटि = env.मानक_त्रुटि;
#पूर्ण_अगर
पूर्ण

/*
 * Determine अगर test_progs is running as a "flavored" test runner and चयन
 * पूर्णांकo corresponding sub-directory to load correct BPF objects.
 *
 * This is करोne by looking at executable name. If it contains "-flavor"
 * suffix, then we are running as a flavored test runner.
 */
पूर्णांक cd_flavor_subdir(स्थिर अक्षर *exec_name)
अणु
	/* General क्रमm of argv[0] passed here is:
	 * some/path/to/test_progs[-flavor], where -flavor part is optional.
	 * First cut out "test_progs[-flavor]" part, then extract "flavor"
	 * part, अगर it's there.
	 */
	स्थिर अक्षर *flavor = म_खोजप(exec_name, '/');

	अगर (!flavor)
		वापस 0;
	flavor++;
	flavor = म_खोजप(flavor, '-');
	अगर (!flavor)
		वापस 0;
	flavor++;
	अगर (env.verbosity > VERBOSE_NONE)
		ख_लिखो(मानक_निकास,	"Switching to flavor '%s' subdirectory...\n", flavor);

	वापस स_बदलो(flavor);
पूर्ण

#घोषणा MAX_BACKTRACE_SZ 128
व्योम crash_handler(पूर्णांक signum)
अणु
	व्योम *bt[MAX_BACKTRACE_SZ];
	माप_प्रकार sz;

	sz = backtrace(bt, ARRAY_SIZE(bt));

	अगर (env.test)
		dump_test_log(env.test, true);
	अगर (env.मानक_निकास)
		stdio_restore();

	ख_लिखो(मानक_त्रुटि, "Caught signal #%d!\nStack trace:\n", signum);
	backtrace_symbols_fd(bt, sz, STDERR_खाताNO);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अटल स्थिर काष्ठा argp argp = अणु
		.options = opts,
		.parser = parse_arg,
		.करोc = argp_program_करोc,
	पूर्ण;
	काष्ठा sigaction sigact = अणु
		.sa_handler = crash_handler,
		.sa_flags = SA_RESETHAND,
	पूर्ण;
	पूर्णांक err, i;

	sigaction(संक_अंश, &sigact, शून्य);

	err = argp_parse(&argp, argc, argv, 0, शून्य, &env);
	अगर (err)
		वापस err;

	err = cd_flavor_subdir(argv[0]);
	अगर (err)
		वापस err;

	libbpf_set_prपूर्णांक(libbpf_prपूर्णांक_fn);

	बेक्रम(समय(शून्य));

	env.jit_enabled = is_jit_enabled();
	env.nr_cpus = libbpf_num_possible_cpus();
	अगर (env.nr_cpus < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to get number of CPUs: %d!\n",
			env.nr_cpus);
		वापस -1;
	पूर्ण

	save_netns();
	stdio_hijack();
	env.has_tesपंचांगod = true;
	अगर (load_bpf_tesपंचांगod()) अणु
		ख_लिखो(env.मानक_त्रुटि, "WARNING! Selftests relying on bpf_testmod.ko will be skipped.\n");
		env.has_tesपंचांगod = false;
	पूर्ण
	क्रम (i = 0; i < prog_test_cnt; i++) अणु
		काष्ठा prog_test_def *test = &prog_test_defs[i];

		env.test = test;
		test->test_num = i + 1;

		अगर (!should_run(&env.test_selector,
				test->test_num, test->test_name))
			जारी;

		अगर (env.get_test_cnt) अणु
			env.succ_cnt++;
			जारी;
		पूर्ण

		अगर (env.list_test_names) अणु
			ख_लिखो(env.मानक_निकास, "%s\n", test->test_name);
			env.succ_cnt++;
			जारी;
		पूर्ण

		test->run_test();
		/* ensure last sub-test is finalized properly */
		अगर (test->subtest_name)
			test__end_subtest();

		test->tested = true;
		अगर (test->error_cnt)
			env.fail_cnt++;
		अन्यथा
			env.succ_cnt++;
		skip_account();

		dump_test_log(test, test->error_cnt);

		ख_लिखो(env.मानक_निकास, "#%d %s:%s\n",
			test->test_num, test->test_name,
			test->error_cnt ? "FAIL" : "OK");

		reset_affinity();
		restore_netns();
		अगर (test->need_cgroup_cleanup)
			cleanup_cgroup_environment();
	पूर्ण
	अगर (env.has_tesपंचांगod)
		unload_bpf_tesपंचांगod();
	stdio_restore();

	अगर (env.get_test_cnt) अणु
		म_लिखो("%d\n", env.succ_cnt);
		जाओ out;
	पूर्ण

	अगर (env.list_test_names)
		जाओ out;

	ख_लिखो(मानक_निकास, "Summary: %d/%d PASSED, %d SKIPPED, %d FAILED\n",
		env.succ_cnt, env.sub_succ_cnt, env.skip_cnt, env.fail_cnt);

out:
	मुक्त_str_set(&env.test_selector.blacklist);
	मुक्त_str_set(&env.test_selector.whitelist);
	मुक्त(env.test_selector.num_set);
	मुक्त_str_set(&env.subtest_selector.blacklist);
	मुक्त_str_set(&env.subtest_selector.whitelist);
	मुक्त(env.subtest_selector.num_set);
	बंद(env.saved_netns_fd);

	अगर (env.succ_cnt + env.fail_cnt + env.skip_cnt == 0)
		वापस EXIT_NO_TEST;

	वापस env.fail_cnt ? निकास_त्रुटि : निकास_सफल;
पूर्ण
