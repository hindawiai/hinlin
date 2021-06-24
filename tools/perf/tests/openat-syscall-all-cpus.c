<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
/* For the CPU_* macros */
#समावेश <pthपढ़ो.h>

#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <api/fs/fs.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <api/fs/tracing_path.h>
#समावेश "evsel.h"
#समावेश "tests.h"
#समावेश "thread_map.h"
#समावेश <perf/cpumap.h>
#समावेश "debug.h"
#समावेश "stat.h"
#समावेश "util/counts.h"

पूर्णांक test__खोलोat_syscall_event_on_all_cpus(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक err = -1, fd, cpu;
	काष्ठा perf_cpu_map *cpus;
	काष्ठा evsel *evsel;
	अचिन्हित पूर्णांक nr_खोलोat_calls = 111, i;
	cpu_set_t cpu_set;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs = thपढ़ो_map__new(-1, getpid(), अच_पूर्णांक_उच्च);
	अक्षर sbuf[STRERR_बफ_मानE];
	अक्षर errbuf[बफ_मान];

	अगर (thपढ़ोs == शून्य) अणु
		pr_debug("thread_map__new\n");
		वापस -1;
	पूर्ण

	cpus = perf_cpu_map__new(शून्य);
	अगर (cpus == शून्य) अणु
		pr_debug("perf_cpu_map__new\n");
		जाओ out_thपढ़ो_map_delete;
	पूर्ण

	CPU_ZERO(&cpu_set);

	evsel = evsel__newtp("syscalls", "sys_enter_openat");
	अगर (IS_ERR(evsel)) अणु
		tracing_path__म_त्रुटि_खोलो_tp(त्रुटि_सं, errbuf, माप(errbuf), "syscalls", "sys_enter_openat");
		pr_debug("%s\n", errbuf);
		जाओ out_cpu_map_delete;
	पूर्ण

	अगर (evsel__खोलो(evsel, cpus, thपढ़ोs) < 0) अणु
		pr_debug("failed to open counter: %s, "
			 "tweak /proc/sys/kernel/perf_event_paranoid?\n",
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out_evsel_delete;
	पूर्ण

	क्रम (cpu = 0; cpu < cpus->nr; ++cpu) अणु
		अचिन्हित पूर्णांक ncalls = nr_खोलोat_calls + cpu;
		/*
		 * XXX eventually lअगरt this restriction in a way that
		 * keeps perf building on older glibc installations
		 * without CPU_ALLOC. 1024 cpus in 2010 still seems
		 * a reasonable upper limit tho :-)
		 */
		अगर (cpus->map[cpu] >= CPU_SETSIZE) अणु
			pr_debug("Ignoring CPU %d\n", cpus->map[cpu]);
			जारी;
		पूर्ण

		CPU_SET(cpus->map[cpu], &cpu_set);
		अगर (sched_setaffinity(0, माप(cpu_set), &cpu_set) < 0) अणु
			pr_debug("sched_setaffinity() failed on CPU %d: %s ",
				 cpus->map[cpu],
				 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
			जाओ out_बंद_fd;
		पूर्ण
		क्रम (i = 0; i < ncalls; ++i) अणु
			fd = खोलोat(0, "/etc/passwd", O_RDONLY);
			बंद(fd);
		पूर्ण
		CPU_CLR(cpus->map[cpu], &cpu_set);
	पूर्ण

	/*
	 * Here we need to explicitly pपुनः_स्मृतिate the counts, as अगर
	 * we use the स्वतः allocation it will allocate just क्रम 1 cpu,
	 * as we start by cpu 0.
	 */
	अगर (evsel__alloc_counts(evsel, cpus->nr, 1) < 0) अणु
		pr_debug("evsel__alloc_counts(ncpus=%d)\n", cpus->nr);
		जाओ out_बंद_fd;
	पूर्ण

	err = 0;

	क्रम (cpu = 0; cpu < cpus->nr; ++cpu) अणु
		अचिन्हित पूर्णांक expected;

		अगर (cpus->map[cpu] >= CPU_SETSIZE)
			जारी;

		अगर (evsel__पढ़ो_on_cpu(evsel, cpu, 0) < 0) अणु
			pr_debug("evsel__read_on_cpu\n");
			err = -1;
			अवरोध;
		पूर्ण

		expected = nr_खोलोat_calls + cpu;
		अगर (perf_counts(evsel->counts, cpu, 0)->val != expected) अणु
			pr_debug("evsel__read_on_cpu: expected to intercept %d calls on cpu %d, got %" PRIu64 "\n",
				 expected, cpus->map[cpu], perf_counts(evsel->counts, cpu, 0)->val);
			err = -1;
		पूर्ण
	पूर्ण

	evsel__मुक्त_counts(evsel);
out_बंद_fd:
	perf_evsel__बंद_fd(&evsel->core);
out_evsel_delete:
	evsel__delete(evsel);
out_cpu_map_delete:
	perf_cpu_map__put(cpus);
out_thपढ़ो_map_delete:
	perf_thपढ़ो_map__put(thपढ़ोs);
	वापस err;
पूर्ण
