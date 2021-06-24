<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook
#समावेश <test_progs.h>
#समावेश "test_stacktrace_build_id.skel.h"

व्योम test_get_stackid_cannot_attach(व्योम)
अणु
	काष्ठा perf_event_attr attr = अणु
		/* .type = PERF_TYPE_SOFTWARE, */
		.type = PERF_TYPE_HARDWARE,
		.config = PERF_COUNT_HW_CPU_CYCLES,
		.precise_ip = 1,
		.sample_type = PERF_SAMPLE_IP | PERF_SAMPLE_BRANCH_STACK,
		.branch_sample_type = PERF_SAMPLE_BRANCH_USER |
			PERF_SAMPLE_BRANCH_NO_FLAGS |
			PERF_SAMPLE_BRANCH_NO_CYCLES |
			PERF_SAMPLE_BRANCH_CALL_STACK,
		.sample_period = 5000,
		.size = माप(काष्ठा perf_event_attr),
	पूर्ण;
	काष्ठा test_stacktrace_build_id *skel;
	__u32 duration = 0;
	पूर्णांक pmu_fd, err;

	skel = test_stacktrace_build_id__खोलो();
	अगर (CHECK(!skel, "skel_open", "skeleton open failed\n"))
		वापस;

	/* override program type */
	bpf_program__set_perf_event(skel->progs.oncpu);

	err = test_stacktrace_build_id__load(skel);
	अगर (CHECK(err, "skel_load", "skeleton load failed: %d\n", err))
		जाओ cleanup;

	pmu_fd = syscall(__NR_perf_event_खोलो, &attr, -1 /* pid */,
			 0 /* cpu 0 */, -1 /* group id */,
			 0 /* flags */);
	अगर (pmu_fd < 0 && (त्रुटि_सं == ENOENT || त्रुटि_सं == EOPNOTSUPP)) अणु
		म_लिखो("%s:SKIP:cannot open PERF_COUNT_HW_CPU_CYCLES with precise_ip > 0\n",
		       __func__);
		test__skip();
		जाओ cleanup;
	पूर्ण
	अगर (CHECK(pmu_fd < 0, "perf_event_open", "err %d errno %d\n",
		  pmu_fd, त्रुटि_सं))
		जाओ cleanup;

	skel->links.oncpu = bpf_program__attach_perf_event(skel->progs.oncpu,
							   pmu_fd);
	CHECK(!IS_ERR(skel->links.oncpu), "attach_perf_event_no_callchain",
	      "should have failed\n");
	बंद(pmu_fd);

	/* add PERF_SAMPLE_CALLCHAIN, attach should succeed */
	attr.sample_type |= PERF_SAMPLE_CALLCHAIN;

	pmu_fd = syscall(__NR_perf_event_खोलो, &attr, -1 /* pid */,
			 0 /* cpu 0 */, -1 /* group id */,
			 0 /* flags */);

	अगर (CHECK(pmu_fd < 0, "perf_event_open", "err %d errno %d\n",
		  pmu_fd, त्रुटि_सं))
		जाओ cleanup;

	skel->links.oncpu = bpf_program__attach_perf_event(skel->progs.oncpu,
							   pmu_fd);
	CHECK(IS_ERR(skel->links.oncpu), "attach_perf_event_callchain",
	      "err: %ld\n", PTR_ERR(skel->links.oncpu));
	बंद(pmu_fd);

	/* add exclude_callchain_kernel, attach should fail */
	attr.exclude_callchain_kernel = 1;

	pmu_fd = syscall(__NR_perf_event_खोलो, &attr, -1 /* pid */,
			 0 /* cpu 0 */, -1 /* group id */,
			 0 /* flags */);

	अगर (CHECK(pmu_fd < 0, "perf_event_open", "err %d errno %d\n",
		  pmu_fd, त्रुटि_सं))
		जाओ cleanup;

	skel->links.oncpu = bpf_program__attach_perf_event(skel->progs.oncpu,
							   pmu_fd);
	CHECK(!IS_ERR(skel->links.oncpu), "attach_perf_event_exclude_callchain_kernel",
	      "should have failed\n");
	बंद(pmu_fd);

cleanup:
	test_stacktrace_build_id__destroy(skel);
पूर्ण
