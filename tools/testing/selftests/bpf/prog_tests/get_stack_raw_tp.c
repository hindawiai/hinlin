<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <sys/socket.h>
#समावेश <test_progs.h>

#घोषणा MAX_CNT_RAWTP	10ull
#घोषणा MAX_STACK_RAWTP	100

अटल पूर्णांक duration = 0;

काष्ठा get_stack_trace_t अणु
	पूर्णांक pid;
	पूर्णांक kern_stack_size;
	पूर्णांक user_stack_size;
	पूर्णांक user_stack_buildid_size;
	__u64 kern_stack[MAX_STACK_RAWTP];
	__u64 user_stack[MAX_STACK_RAWTP];
	काष्ठा bpf_stack_build_id user_stack_buildid[MAX_STACK_RAWTP];
पूर्ण;

अटल व्योम get_stack_prपूर्णांक_output(व्योम *ctx, पूर्णांक cpu, व्योम *data, __u32 size)
अणु
	bool good_kern_stack = false, good_user_stack = false;
	स्थिर अक्षर *nonjit_func = "___bpf_prog_run";
	काष्ठा get_stack_trace_t *e = data;
	पूर्णांक i, num_stack;
	अटल __u64 cnt;
	काष्ठा ksym *ks;

	cnt++;

	अगर (size < माप(काष्ठा get_stack_trace_t)) अणु
		__u64 *raw_data = data;
		bool found = false;

		num_stack = size / माप(__u64);
		/* If jit is enabled, we करो not have a good way to
		 * verअगरy the sanity of the kernel stack. So we
		 * just assume it is good अगर the stack is not empty.
		 * This could be improved in the future.
		 */
		अगर (env.jit_enabled) अणु
			found = num_stack > 0;
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < num_stack; i++) अणु
				ks = ksym_search(raw_data[i]);
				अगर (ks && (म_भेद(ks->name, nonjit_func) == 0)) अणु
					found = true;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (found) अणु
			good_kern_stack = true;
			good_user_stack = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		num_stack = e->kern_stack_size / माप(__u64);
		अगर (env.jit_enabled) अणु
			good_kern_stack = num_stack > 0;
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < num_stack; i++) अणु
				ks = ksym_search(e->kern_stack[i]);
				अगर (ks && (म_भेद(ks->name, nonjit_func) == 0)) अणु
					good_kern_stack = true;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (e->user_stack_size > 0 && e->user_stack_buildid_size > 0)
			good_user_stack = true;
	पूर्ण

	अगर (!good_kern_stack)
	    CHECK(!good_kern_stack, "kern_stack", "corrupted kernel stack\n");
	अगर (!good_user_stack)
	    CHECK(!good_user_stack, "user_stack", "corrupted user stack\n");
पूर्ण

व्योम test_get_stack_raw_tp(व्योम)
अणु
	स्थिर अक्षर *file = "./test_get_stack_rawtp.o";
	स्थिर अक्षर *file_err = "./test_get_stack_rawtp_err.o";
	स्थिर अक्षर *prog_name = "raw_tracepoint/sys_enter";
	पूर्णांक i, err, prog_fd, exp_cnt = MAX_CNT_RAWTP;
	काष्ठा perf_buffer_opts pb_opts = अणुपूर्ण;
	काष्ठा perf_buffer *pb = शून्य;
	काष्ठा bpf_link *link = शून्य;
	काष्ठा बारpec tv = अणु0, 10पूर्ण;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_map *map;
	cpu_set_t cpu_set;

	err = bpf_prog_load(file_err, BPF_PROG_TYPE_RAW_TRACEPOINT, &obj, &prog_fd);
	अगर (CHECK(err >= 0, "prog_load raw tp", "err %d errno %d\n", err, त्रुटि_सं))
		वापस;

	err = bpf_prog_load(file, BPF_PROG_TYPE_RAW_TRACEPOINT, &obj, &prog_fd);
	अगर (CHECK(err, "prog_load raw tp", "err %d errno %d\n", err, त्रुटि_सं))
		वापस;

	prog = bpf_object__find_program_by_title(obj, prog_name);
	अगर (CHECK(!prog, "find_probe", "prog '%s' not found\n", prog_name))
		जाओ बंद_prog;

	map = bpf_object__find_map_by_name(obj, "perfmap");
	अगर (CHECK(!map, "bpf_find_map", "not found\n"))
		जाओ बंद_prog;

	err = load_kallsyms();
	अगर (CHECK(err < 0, "load_kallsyms", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ बंद_prog;

	CPU_ZERO(&cpu_set);
	CPU_SET(0, &cpu_set);
	err = pthपढ़ो_setaffinity_np(pthपढ़ो_self(), माप(cpu_set), &cpu_set);
	अगर (CHECK(err, "set_affinity", "err %d, errno %d\n", err, त्रुटि_सं))
		जाओ बंद_prog;

	link = bpf_program__attach_raw_tracepoपूर्णांक(prog, "sys_enter");
	अगर (CHECK(IS_ERR(link), "attach_raw_tp", "err %ld\n", PTR_ERR(link)))
		जाओ बंद_prog;

	pb_opts.sample_cb = get_stack_prपूर्णांक_output;
	pb = perf_buffer__new(bpf_map__fd(map), 8, &pb_opts);
	अगर (CHECK(IS_ERR(pb), "perf_buf__new", "err %ld\n", PTR_ERR(pb)))
		जाओ बंद_prog;

	/* trigger some syscall action */
	क्रम (i = 0; i < MAX_CNT_RAWTP; i++)
		nanosleep(&tv, शून्य);

	जबतक (exp_cnt > 0) अणु
		err = perf_buffer__poll(pb, 100);
		अगर (err < 0 && CHECK(err < 0, "pb__poll", "err %d\n", err))
			जाओ बंद_prog;
		exp_cnt -= err;
	पूर्ण

बंद_prog:
	अगर (!IS_ERR_OR_शून्य(link))
		bpf_link__destroy(link);
	अगर (!IS_ERR_OR_शून्य(pb))
		perf_buffer__मुक्त(pb);
	bpf_object__बंद(obj);
पूर्ण
