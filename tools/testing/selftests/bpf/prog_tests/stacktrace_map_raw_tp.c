<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>

व्योम test_stacktrace_map_raw_tp(व्योम)
अणु
	स्थिर अक्षर *prog_name = "tracepoint/sched/sched_switch";
	पूर्णांक control_map_fd, stackid_hmap_fd, stackmap_fd;
	स्थिर अक्षर *file = "./test_stacktrace_map.o";
	__u32 key, val, duration = 0;
	पूर्णांक err, prog_fd;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_link *link = शून्य;

	err = bpf_prog_load(file, BPF_PROG_TYPE_RAW_TRACEPOINT, &obj, &prog_fd);
	अगर (CHECK(err, "prog_load raw tp", "err %d errno %d\n", err, त्रुटि_सं))
		वापस;

	prog = bpf_object__find_program_by_title(obj, prog_name);
	अगर (CHECK(!prog, "find_prog", "prog '%s' not found\n", prog_name))
		जाओ बंद_prog;

	link = bpf_program__attach_raw_tracepoपूर्णांक(prog, "sched_switch");
	अगर (CHECK(IS_ERR(link), "attach_raw_tp", "err %ld\n", PTR_ERR(link)))
		जाओ बंद_prog;

	/* find map fds */
	control_map_fd = bpf_find_map(__func__, obj, "control_map");
	अगर (CHECK_FAIL(control_map_fd < 0))
		जाओ बंद_prog;

	stackid_hmap_fd = bpf_find_map(__func__, obj, "stackid_hmap");
	अगर (CHECK_FAIL(stackid_hmap_fd < 0))
		जाओ बंद_prog;

	stackmap_fd = bpf_find_map(__func__, obj, "stackmap");
	अगर (CHECK_FAIL(stackmap_fd < 0))
		जाओ बंद_prog;

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
		जाओ बंद_prog;

	err = compare_map_keys(stackmap_fd, stackid_hmap_fd);
	अगर (CHECK(err, "compare_map_keys stackmap vs. stackid_hmap",
		  "err %d errno %d\n", err, त्रुटि_सं))
		जाओ बंद_prog;

बंद_prog:
	अगर (!IS_ERR_OR_शून्य(link))
		bpf_link__destroy(link);
	bpf_object__बंद(obj);
पूर्ण
