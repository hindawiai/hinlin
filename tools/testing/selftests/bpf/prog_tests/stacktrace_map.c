<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>

व्योम test_stacktrace_map(व्योम)
अणु
	पूर्णांक control_map_fd, stackid_hmap_fd, stackmap_fd, stack_amap_fd;
	स्थिर अक्षर *prog_name = "tracepoint/sched/sched_switch";
	पूर्णांक err, prog_fd, stack_trace_len;
	स्थिर अक्षर *file = "./test_stacktrace_map.o";
	__u32 key, val, duration = 0;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_link *link;

	err = bpf_prog_load(file, BPF_PROG_TYPE_TRACEPOINT, &obj, &prog_fd);
	अगर (CHECK(err, "prog_load", "err %d errno %d\n", err, त्रुटि_सं))
		वापस;

	prog = bpf_object__find_program_by_title(obj, prog_name);
	अगर (CHECK(!prog, "find_prog", "prog '%s' not found\n", prog_name))
		जाओ बंद_prog;

	link = bpf_program__attach_tracepoपूर्णांक(prog, "sched", "sched_switch");
	अगर (CHECK(IS_ERR(link), "attach_tp", "err %ld\n", PTR_ERR(link)))
		जाओ बंद_prog;

	/* find map fds */
	control_map_fd = bpf_find_map(__func__, obj, "control_map");
	अगर (CHECK_FAIL(control_map_fd < 0))
		जाओ disable_pmu;

	stackid_hmap_fd = bpf_find_map(__func__, obj, "stackid_hmap");
	अगर (CHECK_FAIL(stackid_hmap_fd < 0))
		जाओ disable_pmu;

	stackmap_fd = bpf_find_map(__func__, obj, "stackmap");
	अगर (CHECK_FAIL(stackmap_fd < 0))
		जाओ disable_pmu;

	stack_amap_fd = bpf_find_map(__func__, obj, "stack_amap");
	अगर (CHECK_FAIL(stack_amap_fd < 0))
		जाओ disable_pmu;

	/* give some समय क्रम bpf program run */
	sleep(1);

	/* disable stack trace collection */
	key = 0;
	val = 1;
	bpf_map_update_elem(control_map_fd, &key, &val, 0);

	/* क्रम every element in stackid_hmap, we can find a corresponding one
	 * in stackmap, and vise versa.
	 */
	err = compare_map_keys(stackid_hmap_fd, stackmap_fd);
	अगर (CHECK(err, "compare_map_keys stackid_hmap vs. stackmap",
		  "err %d errno %d\n", err, त्रुटि_सं))
		जाओ disable_pmu;

	err = compare_map_keys(stackmap_fd, stackid_hmap_fd);
	अगर (CHECK(err, "compare_map_keys stackmap vs. stackid_hmap",
		  "err %d errno %d\n", err, त्रुटि_सं))
		जाओ disable_pmu;

	stack_trace_len = PERF_MAX_STACK_DEPTH * माप(__u64);
	err = compare_stack_ips(stackmap_fd, stack_amap_fd, stack_trace_len);
	अगर (CHECK(err, "compare_stack_ips stackmap vs. stack_amap",
		  "err %d errno %d\n", err, त्रुटि_सं))
		जाओ disable_pmu;

disable_pmu:
	bpf_link__destroy(link);
बंद_prog:
	bpf_object__बंद(obj);
पूर्ण
