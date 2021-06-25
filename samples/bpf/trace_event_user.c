<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016 Facebook
 */
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <linux/perf_event.h>
#समावेश <linux/bpf.h>
#समावेश <संकेत.स>
#समावेश <त्रुटिसं.स>
#समावेश <sys/resource.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश "perf-sys.h"
#समावेश "trace_helpers.h"

#घोषणा SAMPLE_FREQ 50

अटल पूर्णांक pid;
/* counts, stackmap */
अटल पूर्णांक map_fd[2];
काष्ठा bpf_program *prog;
अटल bool sys_पढ़ो_seen, sys_ग_लिखो_seen;

अटल व्योम prपूर्णांक_ksym(__u64 addr)
अणु
	काष्ठा ksym *sym;

	अगर (!addr)
		वापस;
	sym = ksym_search(addr);
	अगर (!sym) अणु
		म_लिखो("ksym not found. Is kallsyms loaded?\n");
		वापस;
	पूर्ण

	म_लिखो("%s;", sym->name);
	अगर (!म_माला(sym->name, "sys_read"))
		sys_पढ़ो_seen = true;
	अन्यथा अगर (!म_माला(sym->name, "sys_write"))
		sys_ग_लिखो_seen = true;
पूर्ण

अटल व्योम prपूर्णांक_addr(__u64 addr)
अणु
	अगर (!addr)
		वापस;
	म_लिखो("%llx;", addr);
पूर्ण

#घोषणा TASK_COMM_LEN 16

काष्ठा key_t अणु
	अक्षर comm[TASK_COMM_LEN];
	__u32 kernstack;
	__u32 userstack;
पूर्ण;

अटल व्योम prपूर्णांक_stack(काष्ठा key_t *key, __u64 count)
अणु
	__u64 ip[PERF_MAX_STACK_DEPTH] = अणुपूर्ण;
	अटल bool warned;
	पूर्णांक i;

	म_लिखो("%3lld %s;", count, key->comm);
	अगर (bpf_map_lookup_elem(map_fd[1], &key->kernstack, ip) != 0) अणु
		म_लिखो("---;");
	पूर्ण अन्यथा अणु
		क्रम (i = PERF_MAX_STACK_DEPTH - 1; i >= 0; i--)
			prपूर्णांक_ksym(ip[i]);
	पूर्ण
	म_लिखो("-;");
	अगर (bpf_map_lookup_elem(map_fd[1], &key->userstack, ip) != 0) अणु
		म_लिखो("---;");
	पूर्ण अन्यथा अणु
		क्रम (i = PERF_MAX_STACK_DEPTH - 1; i >= 0; i--)
			prपूर्णांक_addr(ip[i]);
	पूर्ण
	अगर (count < 6)
		म_लिखो("\r");
	अन्यथा
		म_लिखो("\n");

	अगर (key->kernstack == -EEXIST && !warned) अणु
		म_लिखो("stackmap collisions seen. Consider increasing size\n");
		warned = true;
	पूर्ण अन्यथा अगर ((पूर्णांक)key->kernstack < 0 && (पूर्णांक)key->userstack < 0) अणु
		म_लिखो("err stackid %d %d\n", key->kernstack, key->userstack);
	पूर्ण
पूर्ण

अटल व्योम err_निकास(पूर्णांक err)
अणु
	समाप्त(pid, SIGKILL);
	निकास(err);
पूर्ण

अटल व्योम prपूर्णांक_stacks(व्योम)
अणु
	काष्ठा key_t key = अणुपूर्ण, next_key;
	__u64 value;
	__u32 stackid = 0, next_id;
	पूर्णांक error = 1, fd = map_fd[0], stack_map = map_fd[1];

	sys_पढ़ो_seen = sys_ग_लिखो_seen = false;
	जबतक (bpf_map_get_next_key(fd, &key, &next_key) == 0) अणु
		bpf_map_lookup_elem(fd, &next_key, &value);
		prपूर्णांक_stack(&next_key, value);
		bpf_map_delete_elem(fd, &next_key);
		key = next_key;
	पूर्ण
	म_लिखो("\n");
	अगर (!sys_पढ़ो_seen || !sys_ग_लिखो_seen) अणु
		म_लिखो("BUG kernel stack doesn't contain sys_read() and sys_write()\n");
		err_निकास(error);
	पूर्ण

	/* clear stack map */
	जबतक (bpf_map_get_next_key(stack_map, &stackid, &next_id) == 0) अणु
		bpf_map_delete_elem(stack_map, &next_id);
		stackid = next_id;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक generate_load(व्योम)
अणु
	अगर (प्रणाली("dd if=/dev/zero of=/dev/null count=5000k status=none") < 0) अणु
		म_लिखो("failed to generate some load with dd: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम test_perf_event_all_cpu(काष्ठा perf_event_attr *attr)
अणु
	पूर्णांक nr_cpus = sysconf(_SC_NPROCESSORS_ONLN);
	काष्ठा bpf_link **links = सुस्मृति(nr_cpus, माप(काष्ठा bpf_link *));
	पूर्णांक i, pmu_fd, error = 1;

	अगर (!links) अणु
		म_लिखो("malloc of links failed\n");
		जाओ err;
	पूर्ण

	/* प्रणाली wide perf event, no need to inherit */
	attr->inherit = 0;

	/* खोलो perf_event on all cpus */
	क्रम (i = 0; i < nr_cpus; i++) अणु
		pmu_fd = sys_perf_event_खोलो(attr, -1, i, -1, 0);
		अगर (pmu_fd < 0) अणु
			म_लिखो("sys_perf_event_open failed\n");
			जाओ all_cpu_err;
		पूर्ण
		links[i] = bpf_program__attach_perf_event(prog, pmu_fd);
		अगर (libbpf_get_error(links[i])) अणु
			म_लिखो("bpf_program__attach_perf_event failed\n");
			links[i] = शून्य;
			बंद(pmu_fd);
			जाओ all_cpu_err;
		पूर्ण
	पूर्ण

	अगर (generate_load() < 0)
		जाओ all_cpu_err;

	prपूर्णांक_stacks();
	error = 0;
all_cpu_err:
	क्रम (i--; i >= 0; i--)
		bpf_link__destroy(links[i]);
err:
	मुक्त(links);
	अगर (error)
		err_निकास(error);
पूर्ण

अटल व्योम test_perf_event_task(काष्ठा perf_event_attr *attr)
अणु
	काष्ठा bpf_link *link = शून्य;
	पूर्णांक pmu_fd, error = 1;

	/* per task perf event, enable inherit so the "dd ..." command can be traced properly.
	 * Enabling inherit will cause bpf_perf_prog_पढ़ो_समय helper failure.
	 */
	attr->inherit = 1;

	/* खोलो task bound event */
	pmu_fd = sys_perf_event_खोलो(attr, 0, -1, -1, 0);
	अगर (pmu_fd < 0) अणु
		म_लिखो("sys_perf_event_open failed\n");
		जाओ err;
	पूर्ण
	link = bpf_program__attach_perf_event(prog, pmu_fd);
	अगर (libbpf_get_error(link)) अणु
		म_लिखो("bpf_program__attach_perf_event failed\n");
		link = शून्य;
		बंद(pmu_fd);
		जाओ err;
	पूर्ण

	अगर (generate_load() < 0)
		जाओ err;

	prपूर्णांक_stacks();
	error = 0;
err:
	bpf_link__destroy(link);
	अगर (error)
		err_निकास(error);
पूर्ण

अटल व्योम test_bpf_perf_event(व्योम)
अणु
	काष्ठा perf_event_attr attr_type_hw = अणु
		.sample_freq = SAMPLE_FREQ,
		.freq = 1,
		.type = PERF_TYPE_HARDWARE,
		.config = PERF_COUNT_HW_CPU_CYCLES,
	पूर्ण;
	काष्ठा perf_event_attr attr_type_sw = अणु
		.sample_freq = SAMPLE_FREQ,
		.freq = 1,
		.type = PERF_TYPE_SOFTWARE,
		.config = PERF_COUNT_SW_CPU_CLOCK,
	पूर्ण;
	काष्ठा perf_event_attr attr_hw_cache_l1d = अणु
		.sample_freq = SAMPLE_FREQ,
		.freq = 1,
		.type = PERF_TYPE_HW_CACHE,
		.config =
			PERF_COUNT_HW_CACHE_L1D |
			(PERF_COUNT_HW_CACHE_OP_READ << 8) |
			(PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16),
	पूर्ण;
	काष्ठा perf_event_attr attr_hw_cache_branch_miss = अणु
		.sample_freq = SAMPLE_FREQ,
		.freq = 1,
		.type = PERF_TYPE_HW_CACHE,
		.config =
			PERF_COUNT_HW_CACHE_BPU |
			(PERF_COUNT_HW_CACHE_OP_READ << 8) |
			(PERF_COUNT_HW_CACHE_RESULT_MISS << 16),
	पूर्ण;
	काष्ठा perf_event_attr attr_type_raw = अणु
		.sample_freq = SAMPLE_FREQ,
		.freq = 1,
		.type = PERF_TYPE_RAW,
		/* Intel Inकाष्ठाion Retired */
		.config = 0xc0,
	पूर्ण;
	काष्ठा perf_event_attr attr_type_raw_lock_load = अणु
		.sample_freq = SAMPLE_FREQ,
		.freq = 1,
		.type = PERF_TYPE_RAW,
		/* Intel MEM_UOPS_RETIRED.LOCK_LOADS */
		.config = 0x21d0,
		/* Request to record lock address from PEBS */
		.sample_type = PERF_SAMPLE_ADDR,
		/* Record address value requires precise event */
		.precise_ip = 2,
	पूर्ण;

	म_लिखो("Test HW_CPU_CYCLES\n");
	test_perf_event_all_cpu(&attr_type_hw);
	test_perf_event_task(&attr_type_hw);

	म_लिखो("Test SW_CPU_CLOCK\n");
	test_perf_event_all_cpu(&attr_type_sw);
	test_perf_event_task(&attr_type_sw);

	म_लिखो("Test HW_CACHE_L1D\n");
	test_perf_event_all_cpu(&attr_hw_cache_l1d);
	test_perf_event_task(&attr_hw_cache_l1d);

	म_लिखो("Test HW_CACHE_BPU\n");
	test_perf_event_all_cpu(&attr_hw_cache_branch_miss);
	test_perf_event_task(&attr_hw_cache_branch_miss);

	म_लिखो("Test Instruction Retired\n");
	test_perf_event_all_cpu(&attr_type_raw);
	test_perf_event_task(&attr_type_raw);

	म_लिखो("Test Lock Load\n");
	test_perf_event_all_cpu(&attr_type_raw_lock_load);
	test_perf_event_task(&attr_type_raw_lock_load);

	म_लिखो("*** PASS ***\n");
पूर्ण


पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_object *obj = शून्य;
	अक्षर filename[256];
	पूर्णांक error = 1;

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);

	संकेत(संक_विघ्न, err_निकास);
	संकेत(संक_इति, err_निकास);

	अगर (load_kallsyms()) अणु
		म_लिखो("failed to process /proc/kallsyms\n");
		जाओ cleanup;
	पूर्ण

	obj = bpf_object__खोलो_file(filename, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		म_लिखो("opening BPF object file failed\n");
		obj = शून्य;
		जाओ cleanup;
	पूर्ण

	prog = bpf_object__find_program_by_name(obj, "bpf_prog1");
	अगर (!prog) अणु
		म_लिखो("finding a prog in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		म_लिखो("loading BPF object file failed\n");
		जाओ cleanup;
	पूर्ण

	map_fd[0] = bpf_object__find_map_fd_by_name(obj, "counts");
	map_fd[1] = bpf_object__find_map_fd_by_name(obj, "stackmap");
	अगर (map_fd[0] < 0 || map_fd[1] < 0) अणु
		म_लिखो("finding a counts/stackmap map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	pid = विभाजन();
	अगर (pid == 0) अणु
		पढ़ो_trace_pipe();
		वापस 0;
	पूर्ण अन्यथा अगर (pid == -1) अणु
		म_लिखो("couldn't spawn process\n");
		जाओ cleanup;
	पूर्ण

	test_bpf_perf_event();
	error = 0;

cleanup:
	bpf_object__बंद(obj);
	err_निकास(error);
पूर्ण
