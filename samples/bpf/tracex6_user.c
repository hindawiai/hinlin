<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE

#समावेश <निश्चित.स>
#समावेश <fcntl.h>
#समावेश <linux/perf_event.h>
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/resource.h>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश "perf-sys.h"

#घोषणा SAMPLE_PERIOD  0x7fffffffffffffffULL

/* counters, values, values2 */
अटल पूर्णांक map_fd[3];

अटल व्योम check_on_cpu(पूर्णांक cpu, काष्ठा perf_event_attr *attr)
अणु
	काष्ठा bpf_perf_event_value value2;
	पूर्णांक pmu_fd, error = 0;
	cpu_set_t set;
	__u64 value;

	/* Move to target CPU */
	CPU_ZERO(&set);
	CPU_SET(cpu, &set);
	निश्चित(sched_setaffinity(0, माप(set), &set) == 0);
	/* Open perf event and attach to the perf_event_array */
	pmu_fd = sys_perf_event_खोलो(attr, -1/*pid*/, cpu/*cpu*/, -1/*group_fd*/, 0);
	अगर (pmu_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "sys_perf_event_open failed on CPU %d\n", cpu);
		error = 1;
		जाओ on_निकास;
	पूर्ण
	निश्चित(bpf_map_update_elem(map_fd[0], &cpu, &pmu_fd, BPF_ANY) == 0);
	निश्चित(ioctl(pmu_fd, PERF_EVENT_IOC_ENABLE, 0) == 0);
	/* Trigger the kprobe */
	bpf_map_get_next_key(map_fd[1], &cpu, शून्य);
	/* Check the value */
	अगर (bpf_map_lookup_elem(map_fd[1], &cpu, &value)) अणु
		ख_लिखो(मानक_त्रुटि, "Value missing for CPU %d\n", cpu);
		error = 1;
		जाओ on_निकास;
	पूर्ण अन्यथा अणु
		ख_लिखो(मानक_त्रुटि, "CPU %d: %llu\n", cpu, value);
	पूर्ण
	/* The above bpf_map_lookup_elem should trigger the second kprobe */
	अगर (bpf_map_lookup_elem(map_fd[2], &cpu, &value2)) अणु
		ख_लिखो(मानक_त्रुटि, "Value2 missing for CPU %d\n", cpu);
		error = 1;
		जाओ on_निकास;
	पूर्ण अन्यथा अणु
		ख_लिखो(मानक_त्रुटि, "CPU %d: counter: %llu, enabled: %llu, running: %llu\n", cpu,
			value2.counter, value2.enabled, value2.running);
	पूर्ण

on_निकास:
	निश्चित(bpf_map_delete_elem(map_fd[0], &cpu) == 0 || error);
	निश्चित(ioctl(pmu_fd, PERF_EVENT_IOC_DISABLE, 0) == 0 || error);
	निश्चित(बंद(pmu_fd) == 0 || error);
	निश्चित(bpf_map_delete_elem(map_fd[1], &cpu) == 0 || error);
	निकास(error);
पूर्ण

अटल व्योम test_perf_event_array(काष्ठा perf_event_attr *attr,
				  स्थिर अक्षर *name)
अणु
	पूर्णांक i, status, nr_cpus = sysconf(_SC_NPROCESSORS_CONF);
	pid_t pid[nr_cpus];
	पूर्णांक err = 0;

	म_लिखो("Test reading %s counters\n", name);

	क्रम (i = 0; i < nr_cpus; i++) अणु
		pid[i] = विभाजन();
		निश्चित(pid[i] >= 0);
		अगर (pid[i] == 0) अणु
			check_on_cpu(i, attr);
			निकास(1);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < nr_cpus; i++) अणु
		निश्चित(रुकोpid(pid[i], &status, 0) == pid[i]);
		err |= status;
	पूर्ण

	अगर (err)
		म_लिखो("Test: %s FAILED\n", name);
पूर्ण

अटल व्योम test_bpf_perf_event(व्योम)
अणु
	काष्ठा perf_event_attr attr_cycles = अणु
		.freq = 0,
		.sample_period = SAMPLE_PERIOD,
		.inherit = 0,
		.type = PERF_TYPE_HARDWARE,
		.पढ़ो_क्रमmat = 0,
		.sample_type = 0,
		.config = PERF_COUNT_HW_CPU_CYCLES,
	पूर्ण;
	काष्ठा perf_event_attr attr_घड़ी = अणु
		.freq = 0,
		.sample_period = SAMPLE_PERIOD,
		.inherit = 0,
		.type = PERF_TYPE_SOFTWARE,
		.पढ़ो_क्रमmat = 0,
		.sample_type = 0,
		.config = PERF_COUNT_SW_CPU_CLOCK,
	पूर्ण;
	काष्ठा perf_event_attr attr_raw = अणु
		.freq = 0,
		.sample_period = SAMPLE_PERIOD,
		.inherit = 0,
		.type = PERF_TYPE_RAW,
		.पढ़ो_क्रमmat = 0,
		.sample_type = 0,
		/* Intel Inकाष्ठाion Retired */
		.config = 0xc0,
	पूर्ण;
	काष्ठा perf_event_attr attr_l1d_load = अणु
		.freq = 0,
		.sample_period = SAMPLE_PERIOD,
		.inherit = 0,
		.type = PERF_TYPE_HW_CACHE,
		.पढ़ो_क्रमmat = 0,
		.sample_type = 0,
		.config =
			PERF_COUNT_HW_CACHE_L1D |
			(PERF_COUNT_HW_CACHE_OP_READ << 8) |
			(PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16),
	पूर्ण;
	काष्ठा perf_event_attr attr_llc_miss = अणु
		.freq = 0,
		.sample_period = SAMPLE_PERIOD,
		.inherit = 0,
		.type = PERF_TYPE_HW_CACHE,
		.पढ़ो_क्रमmat = 0,
		.sample_type = 0,
		.config =
			PERF_COUNT_HW_CACHE_LL |
			(PERF_COUNT_HW_CACHE_OP_READ << 8) |
			(PERF_COUNT_HW_CACHE_RESULT_MISS << 16),
	पूर्ण;
	काष्ठा perf_event_attr attr_msr_tsc = अणु
		.freq = 0,
		.sample_period = 0,
		.inherit = 0,
		/* From /sys/bus/event_source/devices/msr/ */
		.type = 7,
		.पढ़ो_क्रमmat = 0,
		.sample_type = 0,
		.config = 0,
	पूर्ण;

	test_perf_event_array(&attr_cycles, "HARDWARE-cycles");
	test_perf_event_array(&attr_घड़ी, "SOFTWARE-clock");
	test_perf_event_array(&attr_raw, "RAW-instruction-retired");
	test_perf_event_array(&attr_l1d_load, "HW_CACHE-L1D-load");

	/* below tests may fail in qemu */
	test_perf_event_array(&attr_llc_miss, "HW_CACHE-LLC-miss");
	test_perf_event_array(&attr_msr_tsc, "Dynamic-msr-tsc");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_link *links[2];
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	अक्षर filename[256];
	पूर्णांक i = 0;

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	obj = bpf_object__खोलो_file(filename, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: opening BPF object file failed\n");
		वापस 0;
	पूर्ण

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: loading BPF object file failed\n");
		जाओ cleanup;
	पूर्ण

	map_fd[0] = bpf_object__find_map_fd_by_name(obj, "counters");
	map_fd[1] = bpf_object__find_map_fd_by_name(obj, "values");
	map_fd[2] = bpf_object__find_map_fd_by_name(obj, "values2");
	अगर (map_fd[0] < 0 || map_fd[1] < 0 || map_fd[2] < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	bpf_object__क्रम_each_program(prog, obj) अणु
		links[i] = bpf_program__attach(prog);
		अगर (libbpf_get_error(links[i])) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: bpf_program__attach failed\n");
			links[i] = शून्य;
			जाओ cleanup;
		पूर्ण
		i++;
	पूर्ण

	test_bpf_perf_event();

cleanup:
	क्रम (i--; i >= 0; i--)
		bpf_link__destroy(links[i]);

	bpf_object__बंद(obj);
	वापस 0;
पूर्ण
