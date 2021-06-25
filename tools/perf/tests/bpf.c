<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <sys/epoll.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <util/record.h>
#समावेश <util/util.h>
#समावेश <util/bpf-loader.h>
#समावेश <util/evlist.h>
#समावेश <linux/filter.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <api/fs/fs.h>
#समावेश <perf/mmap.h>
#समावेश "tests.h"
#समावेश "llvm.h"
#समावेश "debug.h"
#समावेश "parse-events.h"
#समावेश "util/mmap.h"
#घोषणा NR_ITERS       111
#घोषणा PERF_TEST_BPF_PATH "/sys/fs/bpf/perf_test"

#अगर_घोषित HAVE_LIBBPF_SUPPORT
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf.h>

अटल पूर्णांक epoll_pरुको_loop(व्योम)
अणु
	पूर्णांक i;

	/* Should fail NR_ITERS बार */
	क्रम (i = 0; i < NR_ITERS; i++)
		epoll_pरुको(-(i + 1), शून्य, 0, 0, शून्य);
	वापस 0;
पूर्ण

#अगर_घोषित HAVE_BPF_PROLOGUE

अटल पूर्णांक llseek_loop(व्योम)
अणु
	पूर्णांक fds[2], i;

	fds[0] = खोलो("/dev/null", O_RDONLY);
	fds[1] = खोलो("/dev/null", O_RDWR);

	अगर (fds[0] < 0 || fds[1] < 0)
		वापस -1;

	क्रम (i = 0; i < NR_ITERS; i++) अणु
		lseek(fds[i % 2], i, (i / 2) % 2 ? प्रस्तुत_से : शुरू_से);
		lseek(fds[(i + 1) % 2], i, (i / 2) % 2 ? प्रस्तुत_से : शुरू_से);
	पूर्ण
	बंद(fds[0]);
	बंद(fds[1]);
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल काष्ठा अणु
	क्रमागत test_llvm__testहाल prog_id;
	स्थिर अक्षर *desc;
	स्थिर अक्षर *name;
	स्थिर अक्षर *msg_compile_fail;
	स्थिर अक्षर *msg_load_fail;
	पूर्णांक (*target_func)(व्योम);
	पूर्णांक expect_result;
	bool	pin;
पूर्ण bpf_testहाल_table[] = अणु
	अणु
		.prog_id	  = LLVM_TESTCASE_BASE,
		.desc		  = "Basic BPF filtering",
		.name		  = "[basic_bpf_test]",
		.msg_compile_fail = "fix 'perf test LLVM' first",
		.msg_load_fail	  = "load bpf object failed",
		.target_func	  = &epoll_pरुको_loop,
		.expect_result	  = (NR_ITERS + 1) / 2,
	पूर्ण,
	अणु
		.prog_id	  = LLVM_TESTCASE_BASE,
		.desc		  = "BPF pinning",
		.name		  = "[bpf_pinning]",
		.msg_compile_fail = "fix kbuild first",
		.msg_load_fail	  = "check your vmlinux setting?",
		.target_func	  = &epoll_pरुको_loop,
		.expect_result	  = (NR_ITERS + 1) / 2,
		.pin		  = true,
	पूर्ण,
#अगर_घोषित HAVE_BPF_PROLOGUE
	अणु
		.prog_id	  = LLVM_TESTCASE_BPF_PROLOGUE,
		.desc		  = "BPF prologue generation",
		.name		  = "[bpf_prologue_test]",
		.msg_compile_fail = "fix kbuild first",
		.msg_load_fail	  = "check your vmlinux setting?",
		.target_func	  = &llseek_loop,
		.expect_result	  = (NR_ITERS + 1) / 4,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक करो_test(काष्ठा bpf_object *obj, पूर्णांक (*func)(व्योम),
		   पूर्णांक expect)
अणु
	काष्ठा record_opts opts = अणु
		.target = अणु
			.uid = अच_पूर्णांक_उच्च,
			.uses_mmap = true,
		पूर्ण,
		.freq	      = 0,
		.mmap_pages   = 256,
		.शेष_पूर्णांकerval = 1,
	पूर्ण;

	अक्षर pid[16];
	अक्षर sbuf[STRERR_बफ_मानE];
	काष्ठा evlist *evlist;
	पूर्णांक i, ret = TEST_FAIL, err = 0, count = 0;

	काष्ठा parse_events_state parse_state;
	काष्ठा parse_events_error parse_error;

	bzero(&parse_error, माप(parse_error));
	bzero(&parse_state, माप(parse_state));
	parse_state.error = &parse_error;
	INIT_LIST_HEAD(&parse_state.list);

	err = parse_events_load_bpf_obj(&parse_state, &parse_state.list, obj, शून्य);
	अगर (err || list_empty(&parse_state.list)) अणु
		pr_debug("Failed to add events selected by BPF\n");
		वापस TEST_FAIL;
	पूर्ण

	snम_लिखो(pid, माप(pid), "%d", getpid());
	pid[माप(pid) - 1] = '\0';
	opts.target.tid = opts.target.pid = pid;

	/* Instead of evlist__new_शेष, करोn't add शेष events */
	evlist = evlist__new();
	अगर (!evlist) अणु
		pr_debug("Not enough memory to create evlist\n");
		वापस TEST_FAIL;
	पूर्ण

	err = evlist__create_maps(evlist, &opts.target);
	अगर (err < 0) अणु
		pr_debug("Not enough memory to create thread/cpu maps\n");
		जाओ out_delete_evlist;
	पूर्ण

	evlist__splice_list_tail(evlist, &parse_state.list);
	evlist->nr_groups = parse_state.nr_groups;

	evlist__config(evlist, &opts, शून्य);

	err = evlist__खोलो(evlist);
	अगर (err < 0) अणु
		pr_debug("perf_evlist__open: %s\n",
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out_delete_evlist;
	पूर्ण

	err = evlist__mmap(evlist, opts.mmap_pages);
	अगर (err < 0) अणु
		pr_debug("evlist__mmap: %s\n",
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out_delete_evlist;
	पूर्ण

	evlist__enable(evlist);
	(*func)();
	evlist__disable(evlist);

	क्रम (i = 0; i < evlist->core.nr_mmaps; i++) अणु
		जोड़ perf_event *event;
		काष्ठा mmap *md;

		md = &evlist->mmap[i];
		अगर (perf_mmap__पढ़ो_init(&md->core) < 0)
			जारी;

		जबतक ((event = perf_mmap__पढ़ो_event(&md->core)) != शून्य) अणु
			स्थिर u32 type = event->header.type;

			अगर (type == PERF_RECORD_SAMPLE)
				count ++;
		पूर्ण
		perf_mmap__पढ़ो_करोne(&md->core);
	पूर्ण

	अगर (count != expect * evlist->core.nr_entries) अणु
		pr_debug("BPF filter result incorrect, expected %d, got %d samples\n", expect, count);
		जाओ out_delete_evlist;
	पूर्ण

	ret = TEST_OK;

out_delete_evlist:
	evlist__delete(evlist);
	वापस ret;
पूर्ण

अटल काष्ठा bpf_object *
prepare_bpf(व्योम *obj_buf, माप_प्रकार obj_buf_sz, स्थिर अक्षर *name)
अणु
	काष्ठा bpf_object *obj;

	obj = bpf__prepare_load_buffer(obj_buf, obj_buf_sz, name);
	अगर (IS_ERR(obj)) अणु
		pr_debug("Compile BPF program failed.\n");
		वापस शून्य;
	पूर्ण
	वापस obj;
पूर्ण

अटल पूर्णांक __test__bpf(पूर्णांक idx)
अणु
	पूर्णांक ret;
	व्योम *obj_buf;
	माप_प्रकार obj_buf_sz;
	काष्ठा bpf_object *obj;

	ret = test_llvm__fetch_bpf_obj(&obj_buf, &obj_buf_sz,
				       bpf_testहाल_table[idx].prog_id,
				       true, शून्य);
	अगर (ret != TEST_OK || !obj_buf || !obj_buf_sz) अणु
		pr_debug("Unable to get BPF object, %s\n",
			 bpf_testहाल_table[idx].msg_compile_fail);
		अगर (idx == 0)
			वापस TEST_SKIP;
		अन्यथा
			वापस TEST_FAIL;
	पूर्ण

	obj = prepare_bpf(obj_buf, obj_buf_sz,
			  bpf_testहाल_table[idx].name);
	अगर ((!!bpf_testहाल_table[idx].target_func) != (!!obj)) अणु
		अगर (!obj)
			pr_debug("Fail to load BPF object: %s\n",
				 bpf_testहाल_table[idx].msg_load_fail);
		अन्यथा
			pr_debug("Success unexpectedly: %s\n",
				 bpf_testहाल_table[idx].msg_load_fail);
		ret = TEST_FAIL;
		जाओ out;
	पूर्ण

	अगर (obj) अणु
		ret = करो_test(obj,
			      bpf_testहाल_table[idx].target_func,
			      bpf_testहाल_table[idx].expect_result);
		अगर (ret != TEST_OK)
			जाओ out;
		अगर (bpf_testहाल_table[idx].pin) अणु
			पूर्णांक err;

			अगर (!bpf_fs__mount()) अणु
				pr_debug("BPF filesystem not mounted\n");
				ret = TEST_FAIL;
				जाओ out;
			पूर्ण
			err = सूची_गढ़ो(PERF_TEST_BPF_PATH, 0777);
			अगर (err && त्रुटि_सं != EEXIST) अणु
				pr_debug("Failed to make perf_test dir: %s\n",
					 म_त्रुटि(त्रुटि_सं));
				ret = TEST_FAIL;
				जाओ out;
			पूर्ण
			अगर (bpf_object__pin(obj, PERF_TEST_BPF_PATH))
				ret = TEST_FAIL;
			अगर (rm_rf(PERF_TEST_BPF_PATH))
				ret = TEST_FAIL;
		पूर्ण
	पूर्ण

out:
	bpf__clear();
	वापस ret;
पूर्ण

पूर्णांक test__bpf_subtest_get_nr(व्योम)
अणु
	वापस (पूर्णांक)ARRAY_SIZE(bpf_testहाल_table);
पूर्ण

स्थिर अक्षर *test__bpf_subtest_get_desc(पूर्णांक i)
अणु
	अगर (i < 0 || i >= (पूर्णांक)ARRAY_SIZE(bpf_testहाल_table))
		वापस शून्य;
	वापस bpf_testहाल_table[i].desc;
पूर्ण

अटल पूर्णांक check_env(व्योम)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक kver_पूर्णांक;
	अक्षर license[] = "GPL";

	काष्ठा bpf_insn insns[] = अणु
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण;

	err = fetch_kernel_version(&kver_पूर्णांक, शून्य, 0);
	अगर (err) अणु
		pr_debug("Unable to get kernel version\n");
		वापस err;
	पूर्ण

	err = bpf_load_program(BPF_PROG_TYPE_KPROBE, insns,
			       माप(insns) / माप(insns[0]),
			       license, kver_पूर्णांक, शून्य, 0);
	अगर (err < 0) अणु
		pr_err("Missing basic BPF support, skip this test: %s\n",
		       म_त्रुटि(त्रुटि_सं));
		वापस err;
	पूर्ण
	बंद(err);

	वापस 0;
पूर्ण

पूर्णांक test__bpf(काष्ठा test *test __maybe_unused, पूर्णांक i)
अणु
	पूर्णांक err;

	अगर (i < 0 || i >= (पूर्णांक)ARRAY_SIZE(bpf_testहाल_table))
		वापस TEST_FAIL;

	अगर (geteuid() != 0) अणु
		pr_debug("Only root can run BPF test\n");
		वापस TEST_SKIP;
	पूर्ण

	अगर (check_env())
		वापस TEST_SKIP;

	err = __test__bpf(i);
	वापस err;
पूर्ण

#अन्यथा
पूर्णांक test__bpf_subtest_get_nr(व्योम)
अणु
	वापस 0;
पूर्ण

स्थिर अक्षर *test__bpf_subtest_get_desc(पूर्णांक i __maybe_unused)
अणु
	वापस शून्य;
पूर्ण

पूर्णांक test__bpf(काष्ठा test *test __maybe_unused, पूर्णांक i __maybe_unused)
अणु
	pr_debug("Skip BPF test because BPF support is not compiled\n");
	वापस TEST_SKIP;
पूर्ण
#पूर्ण_अगर
