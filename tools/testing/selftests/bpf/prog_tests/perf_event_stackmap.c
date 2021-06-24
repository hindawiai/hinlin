<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook
#घोषणा _GNU_SOURCE
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <test_progs.h>
#समावेश "perf_event_stackmap.skel.h"

#अगर_अघोषित noअंतरभूत
#घोषणा noअंतरभूत __attribute__((noअंतरभूत))
#पूर्ण_अगर

noअंतरभूत पूर्णांक func_1(व्योम)
अणु
	अटल पूर्णांक val = 1;

	val += 1;

	usleep(100);
	वापस val;
पूर्ण

noअंतरभूत पूर्णांक func_2(व्योम)
अणु
	वापस func_1();
पूर्ण

noअंतरभूत पूर्णांक func_3(व्योम)
अणु
	वापस func_2();
पूर्ण

noअंतरभूत पूर्णांक func_4(व्योम)
अणु
	वापस func_3();
पूर्ण

noअंतरभूत पूर्णांक func_5(व्योम)
अणु
	वापस func_4();
पूर्ण

noअंतरभूत पूर्णांक func_6(व्योम)
अणु
	पूर्णांक i, val = 1;

	क्रम (i = 0; i < 100; i++)
		val += func_5();

	वापस val;
पूर्ण

व्योम test_perf_event_stackmap(व्योम)
अणु
	काष्ठा perf_event_attr attr = अणु
		/* .type = PERF_TYPE_SOFTWARE, */
		.type = PERF_TYPE_HARDWARE,
		.config = PERF_COUNT_HW_CPU_CYCLES,
		.precise_ip = 2,
		.sample_type = PERF_SAMPLE_IP | PERF_SAMPLE_BRANCH_STACK |
			PERF_SAMPLE_CALLCHAIN,
		.branch_sample_type = PERF_SAMPLE_BRANCH_USER |
			PERF_SAMPLE_BRANCH_NO_FLAGS |
			PERF_SAMPLE_BRANCH_NO_CYCLES |
			PERF_SAMPLE_BRANCH_CALL_STACK,
		.sample_period = 5000,
		.size = माप(काष्ठा perf_event_attr),
	पूर्ण;
	काष्ठा perf_event_stackmap *skel;
	__u32 duration = 0;
	cpu_set_t cpu_set;
	पूर्णांक pmu_fd, err;

	skel = perf_event_stackmap__खोलो();

	अगर (CHECK(!skel, "skel_open", "skeleton open failed\n"))
		वापस;

	err = perf_event_stackmap__load(skel);
	अगर (CHECK(err, "skel_load", "skeleton load failed: %d\n", err))
		जाओ cleanup;

	CPU_ZERO(&cpu_set);
	CPU_SET(0, &cpu_set);
	err = pthपढ़ो_setaffinity_np(pthपढ़ो_self(), माप(cpu_set), &cpu_set);
	अगर (CHECK(err, "set_affinity", "err %d, errno %d\n", err, त्रुटि_सं))
		जाओ cleanup;

	pmu_fd = syscall(__NR_perf_event_खोलो, &attr, -1 /* pid */,
			 0 /* cpu 0 */, -1 /* group id */,
			 0 /* flags */);
	अगर (pmu_fd < 0) अणु
		म_लिखो("%s:SKIP:cpu doesn't support the event\n", __func__);
		test__skip();
		जाओ cleanup;
	पूर्ण

	skel->links.oncpu = bpf_program__attach_perf_event(skel->progs.oncpu,
							   pmu_fd);
	अगर (CHECK(IS_ERR(skel->links.oncpu), "attach_perf_event",
		  "err %ld\n", PTR_ERR(skel->links.oncpu))) अणु
		बंद(pmu_fd);
		जाओ cleanup;
	पूर्ण

	/* create kernel and user stack traces क्रम testing */
	func_6();

	CHECK(skel->data->stackid_kernel != 2, "get_stackid_kernel", "failed\n");
	CHECK(skel->data->stackid_user != 2, "get_stackid_user", "failed\n");
	CHECK(skel->data->stack_kernel != 2, "get_stack_kernel", "failed\n");
	CHECK(skel->data->stack_user != 2, "get_stack_user", "failed\n");

cleanup:
	perf_event_stackmap__destroy(skel);
पूर्ण
