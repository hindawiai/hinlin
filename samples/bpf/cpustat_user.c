<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <sched.h>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <क्षेत्र.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/समय.स>
#समावेश <sys/resource.h>
#समावेश <sys/रुको.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

अटल पूर्णांक cstate_map_fd, pstate_map_fd;

#घोषणा MAX_CPU			8
#घोषणा MAX_PSTATE_ENTRIES	5
#घोषणा MAX_CSTATE_ENTRIES	3
#घोषणा MAX_STARS		40

#घोषणा CPUFREQ_MAX_SYSFS_PATH	"/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq"
#घोषणा CPUFREQ_LOWEST_FREQ	"208000"
#घोषणा CPUFREQ_HIGHEST_FREQ	"12000000"

काष्ठा cpu_stat_data अणु
	अचिन्हित दीर्घ cstate[MAX_CSTATE_ENTRIES];
	अचिन्हित दीर्घ pstate[MAX_PSTATE_ENTRIES];
पूर्ण;

अटल काष्ठा cpu_stat_data stat_data[MAX_CPU];

अटल व्योम cpu_stat_prपूर्णांक(व्योम)
अणु
	पूर्णांक i, j;
	अक्षर state_str[माप("cstate-9")];
	काष्ठा cpu_stat_data *data;

	/* Clear screen */
	म_लिखो("\033[2J");

	/* Header */
	म_लिखो("\nCPU states statistics:\n");
	म_लिखो("%-10s ", "state(ms)");

	क्रम (i = 0; i < MAX_CSTATE_ENTRIES; i++) अणु
		प्र_लिखो(state_str, "cstate-%d", i);
		म_लिखो("%-11s ", state_str);
	पूर्ण

	क्रम (i = 0; i < MAX_PSTATE_ENTRIES; i++) अणु
		प्र_लिखो(state_str, "pstate-%d", i);
		म_लिखो("%-11s ", state_str);
	पूर्ण

	म_लिखो("\n");

	क्रम (j = 0; j < MAX_CPU; j++) अणु
		data = &stat_data[j];

		म_लिखो("CPU-%-6d ", j);
		क्रम (i = 0; i < MAX_CSTATE_ENTRIES; i++)
			म_लिखो("%-11ld ", data->cstate[i] / 1000000);

		क्रम (i = 0; i < MAX_PSTATE_ENTRIES; i++)
			म_लिखो("%-11ld ", data->pstate[i] / 1000000);

		म_लिखो("\n");
	पूर्ण
पूर्ण

अटल व्योम cpu_stat_update(पूर्णांक cstate_fd, पूर्णांक pstate_fd)
अणु
	अचिन्हित दीर्घ key, value;
	पूर्णांक c, i;

	क्रम (c = 0; c < MAX_CPU; c++) अणु
		क्रम (i = 0; i < MAX_CSTATE_ENTRIES; i++) अणु
			key = c * MAX_CSTATE_ENTRIES + i;
			bpf_map_lookup_elem(cstate_fd, &key, &value);
			stat_data[c].cstate[i] = value;
		पूर्ण

		क्रम (i = 0; i < MAX_PSTATE_ENTRIES; i++) अणु
			key = c * MAX_PSTATE_ENTRIES + i;
			bpf_map_lookup_elem(pstate_fd, &key, &value);
			stat_data[c].pstate[i] = value;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This function is copied from 'idlestat' tool function
 * idlestat_wake_all() in idlestate.c.
 *
 * It sets the self running task affinity to cpus one by one so can wake up
 * the specअगरic CPU to handle scheduling; this results in all cpus can be
 * waken up once and produce ftrace event 'trace_cpu_idle'.
 */
अटल पूर्णांक cpu_stat_inject_cpu_idle_event(व्योम)
अणु
	पूर्णांक rcpu, i, ret;
	cpu_set_t cpumask;
	cpu_set_t original_cpumask;

	ret = sysconf(_SC_NPROCESSORS_CONF);
	अगर (ret < 0)
		वापस -1;

	rcpu = sched_अ_लोpu();
	अगर (rcpu < 0)
		वापस -1;

	/* Keep track of the CPUs we will run on */
	sched_getaffinity(0, माप(original_cpumask), &original_cpumask);

	क्रम (i = 0; i < ret; i++) अणु

		/* Poपूर्णांकless to wake up ourself */
		अगर (i == rcpu)
			जारी;

		/* Poपूर्णांकless to wake CPUs we will not run on */
		अगर (!CPU_ISSET(i, &original_cpumask))
			जारी;

		CPU_ZERO(&cpumask);
		CPU_SET(i, &cpumask);

		sched_setaffinity(0, माप(cpumask), &cpumask);
	पूर्ण

	/* Enable all the CPUs of the original mask */
	sched_setaffinity(0, माप(original_cpumask), &original_cpumask);
	वापस 0;
पूर्ण

/*
 * It's possible to have no any frequency change क्रम दीर्घ समय and cannot
 * get ftrace event 'trace_cpu_frequency' क्रम दीर्घ period, this पूर्णांकroduces
 * big deviation क्रम pstate statistics.
 *
 * To solve this issue, below code क्रमces to set 'scaling_max_freq' to 208MHz
 * क्रम triggering ftrace event 'trace_cpu_frequency' and then recovery back to
 * the maximum frequency value 1.2GHz.
 */
अटल पूर्णांक cpu_stat_inject_cpu_frequency_event(व्योम)
अणु
	पूर्णांक len, fd;

	fd = खोलो(CPUFREQ_MAX_SYSFS_PATH, O_WRONLY);
	अगर (fd < 0) अणु
		म_लिखो("failed to open scaling_max_freq, errno=%d\n", त्रुटि_सं);
		वापस fd;
	पूर्ण

	len = ग_लिखो(fd, CPUFREQ_LOWEST_FREQ, म_माप(CPUFREQ_LOWEST_FREQ));
	अगर (len < 0) अणु
		म_लिखो("failed to open scaling_max_freq, errno=%d\n", त्रुटि_सं);
		जाओ err;
	पूर्ण

	len = ग_लिखो(fd, CPUFREQ_HIGHEST_FREQ, म_माप(CPUFREQ_HIGHEST_FREQ));
	अगर (len < 0) अणु
		म_लिखो("failed to open scaling_max_freq, errno=%d\n", त्रुटि_सं);
		जाओ err;
	पूर्ण

err:
	बंद(fd);
	वापस len;
पूर्ण

अटल व्योम पूर्णांक_निकास(पूर्णांक sig)
अणु
	cpu_stat_inject_cpu_idle_event();
	cpu_stat_inject_cpu_frequency_event();
	cpu_stat_update(cstate_map_fd, pstate_map_fd);
	cpu_stat_prपूर्णांक();
	निकास(0);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_link *link = शून्य;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	अक्षर filename[256];
	पूर्णांक ret;

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	obj = bpf_object__खोलो_file(filename, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: opening BPF object file failed\n");
		वापस 0;
	पूर्ण

	prog = bpf_object__find_program_by_name(obj, "bpf_prog1");
	अगर (!prog) अणु
		म_लिखो("finding a prog in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: loading BPF object file failed\n");
		जाओ cleanup;
	पूर्ण

	cstate_map_fd = bpf_object__find_map_fd_by_name(obj, "cstate_duration");
	pstate_map_fd = bpf_object__find_map_fd_by_name(obj, "pstate_duration");
	अगर (cstate_map_fd < 0 || pstate_map_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	link = bpf_program__attach(prog);
	अगर (libbpf_get_error(link)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: bpf_program__attach failed\n");
		link = शून्य;
		जाओ cleanup;
	पूर्ण

	ret = cpu_stat_inject_cpu_idle_event();
	अगर (ret < 0)
		वापस 1;

	ret = cpu_stat_inject_cpu_frequency_event();
	अगर (ret < 0)
		वापस 1;

	संकेत(संक_विघ्न, पूर्णांक_निकास);
	संकेत(संक_इति, पूर्णांक_निकास);

	जबतक (1) अणु
		cpu_stat_update(cstate_map_fd, pstate_map_fd);
		cpu_stat_prपूर्णांक();
		sleep(5);
	पूर्ण

cleanup:
	bpf_link__destroy(link);
	bpf_object__बंद(obj);
	वापस 0;
पूर्ण
