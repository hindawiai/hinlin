<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <sys/socket.h>
#समावेश <test_progs.h>
#समावेश "bpf/libbpf_internal.h"
#समावेश "test_perf_branches.skel.h"

अटल व्योम check_good_sample(काष्ठा test_perf_branches *skel)
अणु
	पूर्णांक written_global = skel->bss->written_global_out;
	पूर्णांक required_size = skel->bss->required_size_out;
	पूर्णांक written_stack = skel->bss->written_stack_out;
	पूर्णांक pbe_size = माप(काष्ठा perf_branch_entry);
	पूर्णांक duration = 0;

	अगर (CHECK(!skel->bss->valid, "output not valid",
		 "no valid sample from prog"))
		वापस;

	/*
	 * It's hard to validate the contents of the branch entries b/c it
	 * would require some kind of disassembler and also encoding the
	 * valid jump inकाष्ठाions क्रम supported architectures. So just check
	 * the easy stuff क्रम now.
	 */
	CHECK(required_size <= 0, "read_branches_size", "err %d\n", required_size);
	CHECK(written_stack < 0, "read_branches_stack", "err %d\n", written_stack);
	CHECK(written_stack % pbe_size != 0, "read_branches_stack",
	      "stack bytes written=%d not multiple of struct size=%d\n",
	      written_stack, pbe_size);
	CHECK(written_global < 0, "read_branches_global", "err %d\n", written_global);
	CHECK(written_global % pbe_size != 0, "read_branches_global",
	      "global bytes written=%d not multiple of struct size=%d\n",
	      written_global, pbe_size);
	CHECK(written_global < written_stack, "read_branches_size",
	      "written_global=%d < written_stack=%d\n", written_global, written_stack);
पूर्ण

अटल व्योम check_bad_sample(काष्ठा test_perf_branches *skel)
अणु
	पूर्णांक written_global = skel->bss->written_global_out;
	पूर्णांक required_size = skel->bss->required_size_out;
	पूर्णांक written_stack = skel->bss->written_stack_out;
	पूर्णांक duration = 0;

	अगर (CHECK(!skel->bss->valid, "output not valid",
		 "no valid sample from prog"))
		वापस;

	CHECK((required_size != -EINVAL && required_size != -ENOENT),
	      "read_branches_size", "err %d\n", required_size);
	CHECK((written_stack != -EINVAL && written_stack != -ENOENT),
	      "read_branches_stack", "written %d\n", written_stack);
	CHECK((written_global != -EINVAL && written_global != -ENOENT),
	      "read_branches_global", "written %d\n", written_global);
पूर्ण

अटल व्योम test_perf_branches_common(पूर्णांक perf_fd,
				      व्योम (*cb)(काष्ठा test_perf_branches *))
अणु
	काष्ठा test_perf_branches *skel;
	पूर्णांक err, i, duration = 0;
	bool detached = false;
	काष्ठा bpf_link *link;
	अस्थिर पूर्णांक j = 0;
	cpu_set_t cpu_set;

	skel = test_perf_branches__खोलो_and_load();
	अगर (CHECK(!skel, "test_perf_branches_load",
		  "perf_branches skeleton failed\n"))
		वापस;

	/* attach perf_event */
	link = bpf_program__attach_perf_event(skel->progs.perf_branches, perf_fd);
	अगर (CHECK(IS_ERR(link), "attach_perf_event", "err %ld\n", PTR_ERR(link)))
		जाओ out_destroy_skel;

	/* generate some branches on cpu 0 */
	CPU_ZERO(&cpu_set);
	CPU_SET(0, &cpu_set);
	err = pthपढ़ो_setaffinity_np(pthपढ़ो_self(), माप(cpu_set), &cpu_set);
	अगर (CHECK(err, "set_affinity", "cpu #0, err %d\n", err))
		जाओ out_destroy;
	/* spin the loop क्रम a जबतक (अक्रमom high number) */
	क्रम (i = 0; i < 1000000; ++i)
		++j;

	test_perf_branches__detach(skel);
	detached = true;

	cb(skel);
out_destroy:
	bpf_link__destroy(link);
out_destroy_skel:
	अगर (!detached)
		test_perf_branches__detach(skel);
	test_perf_branches__destroy(skel);
पूर्ण

अटल व्योम test_perf_branches_hw(व्योम)
अणु
	काष्ठा perf_event_attr attr = अणु0पूर्ण;
	पूर्णांक duration = 0;
	पूर्णांक pfd;

	/* create perf event */
	attr.size = माप(attr);
	attr.type = PERF_TYPE_HARDWARE;
	attr.config = PERF_COUNT_HW_CPU_CYCLES;
	attr.freq = 1;
	attr.sample_freq = 4000;
	attr.sample_type = PERF_SAMPLE_BRANCH_STACK;
	attr.branch_sample_type = PERF_SAMPLE_BRANCH_USER | PERF_SAMPLE_BRANCH_ANY;
	pfd = syscall(__NR_perf_event_खोलो, &attr, -1, 0, -1, PERF_FLAG_FD_CLOEXEC);

	/*
	 * Some setups करोn't support branch records (भव machines, !x86),
	 * so skip test in this हाल.
	 */
	अगर (pfd == -1) अणु
		अगर (त्रुटि_सं == ENOENT || त्रुटि_सं == EOPNOTSUPP) अणु
			म_लिखो("%s:SKIP:no PERF_SAMPLE_BRANCH_STACK\n",
			       __func__);
			test__skip();
			वापस;
		पूर्ण
		अगर (CHECK(pfd < 0, "perf_event_open", "err %d errno %d\n",
			  pfd, त्रुटि_सं))
			वापस;
	पूर्ण

	test_perf_branches_common(pfd, check_good_sample);

	बंद(pfd);
पूर्ण

/*
 * Tests negative हाल -- run bpf_पढ़ो_branch_records() on improperly configured
 * perf event.
 */
अटल व्योम test_perf_branches_no_hw(व्योम)
अणु
	काष्ठा perf_event_attr attr = अणु0पूर्ण;
	पूर्णांक duration = 0;
	पूर्णांक pfd;

	/* create perf event */
	attr.size = माप(attr);
	attr.type = PERF_TYPE_SOFTWARE;
	attr.config = PERF_COUNT_SW_CPU_CLOCK;
	attr.freq = 1;
	attr.sample_freq = 4000;
	pfd = syscall(__NR_perf_event_खोलो, &attr, -1, 0, -1, PERF_FLAG_FD_CLOEXEC);
	अगर (CHECK(pfd < 0, "perf_event_open", "err %d\n", pfd))
		वापस;

	test_perf_branches_common(pfd, check_bad_sample);

	बंद(pfd);
पूर्ण

व्योम test_perf_branches(व्योम)
अणु
	अगर (test__start_subtest("perf_branches_hw"))
		test_perf_branches_hw();
	अगर (test__start_subtest("perf_branches_no_hw"))
		test_perf_branches_no_hw();
पूर्ण
