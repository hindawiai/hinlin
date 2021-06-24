<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>
#समावेश <linux/perf_event.h>
#समावेश <perf/cpumap.h>
#समावेश <perf/thपढ़ोmap.h>
#समावेश <perf/evsel.h>
#समावेश <पूर्णांकernal/tests.h>

अटल पूर्णांक libperf_prपूर्णांक(क्रमागत libperf_prपूर्णांक_level level,
			 स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	वापस भख_लिखो(मानक_त्रुटि, fmt, ap);
पूर्ण

अटल पूर्णांक test_stat_cpu(व्योम)
अणु
	काष्ठा perf_cpu_map *cpus;
	काष्ठा perf_evsel *evsel;
	काष्ठा perf_event_attr attr = अणु
		.type	= PERF_TYPE_SOFTWARE,
		.config	= PERF_COUNT_SW_CPU_CLOCK,
	पूर्ण;
	पूर्णांक err, cpu, पंचांगp;

	cpus = perf_cpu_map__new(शून्य);
	__T("failed to create cpus", cpus);

	evsel = perf_evsel__new(&attr);
	__T("failed to create evsel", evsel);

	err = perf_evsel__खोलो(evsel, cpus, शून्य);
	__T("failed to open evsel", err == 0);

	perf_cpu_map__क्रम_each_cpu(cpu, पंचांगp, cpus) अणु
		काष्ठा perf_counts_values counts = अणु .val = 0 पूर्ण;

		perf_evsel__पढ़ो(evsel, cpu, 0, &counts);
		__T("failed to read value for evsel", counts.val != 0);
	पूर्ण

	perf_evsel__बंद(evsel);
	perf_evsel__delete(evsel);

	perf_cpu_map__put(cpus);
	वापस 0;
पूर्ण

अटल पूर्णांक test_stat_thपढ़ो(व्योम)
अणु
	काष्ठा perf_counts_values counts = अणु .val = 0 पूर्ण;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
	काष्ठा perf_evsel *evsel;
	काष्ठा perf_event_attr attr = अणु
		.type	= PERF_TYPE_SOFTWARE,
		.config	= PERF_COUNT_SW_TASK_CLOCK,
	पूर्ण;
	पूर्णांक err;

	thपढ़ोs = perf_thपढ़ो_map__new_dummy();
	__T("failed to create threads", thपढ़ोs);

	perf_thपढ़ो_map__set_pid(thपढ़ोs, 0, 0);

	evsel = perf_evsel__new(&attr);
	__T("failed to create evsel", evsel);

	err = perf_evsel__खोलो(evsel, शून्य, thपढ़ोs);
	__T("failed to open evsel", err == 0);

	perf_evsel__पढ़ो(evsel, 0, 0, &counts);
	__T("failed to read value for evsel", counts.val != 0);

	perf_evsel__बंद(evsel);
	perf_evsel__delete(evsel);

	perf_thपढ़ो_map__put(thपढ़ोs);
	वापस 0;
पूर्ण

अटल पूर्णांक test_stat_thपढ़ो_enable(व्योम)
अणु
	काष्ठा perf_counts_values counts = अणु .val = 0 पूर्ण;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
	काष्ठा perf_evsel *evsel;
	काष्ठा perf_event_attr attr = अणु
		.type	  = PERF_TYPE_SOFTWARE,
		.config	  = PERF_COUNT_SW_TASK_CLOCK,
		.disabled = 1,
	पूर्ण;
	पूर्णांक err;

	thपढ़ोs = perf_thपढ़ो_map__new_dummy();
	__T("failed to create threads", thपढ़ोs);

	perf_thपढ़ो_map__set_pid(thपढ़ोs, 0, 0);

	evsel = perf_evsel__new(&attr);
	__T("failed to create evsel", evsel);

	err = perf_evsel__खोलो(evsel, शून्य, thपढ़ोs);
	__T("failed to open evsel", err == 0);

	perf_evsel__पढ़ो(evsel, 0, 0, &counts);
	__T("failed to read value for evsel", counts.val == 0);

	err = perf_evsel__enable(evsel);
	__T("failed to enable evsel", err == 0);

	perf_evsel__पढ़ो(evsel, 0, 0, &counts);
	__T("failed to read value for evsel", counts.val != 0);

	err = perf_evsel__disable(evsel);
	__T("failed to enable evsel", err == 0);

	perf_evsel__बंद(evsel);
	perf_evsel__delete(evsel);

	perf_thपढ़ो_map__put(thपढ़ोs);
	वापस 0;
पूर्ण

अटल पूर्णांक test_stat_user_पढ़ो(पूर्णांक event)
अणु
	काष्ठा perf_counts_values counts = अणु .val = 0 पूर्ण;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
	काष्ठा perf_evsel *evsel;
	काष्ठा perf_event_mmap_page *pc;
	काष्ठा perf_event_attr attr = अणु
		.type	= PERF_TYPE_HARDWARE,
		.config	= event,
	पूर्ण;
	पूर्णांक err, i;

	thपढ़ोs = perf_thपढ़ो_map__new_dummy();
	__T("failed to create threads", thपढ़ोs);

	perf_thपढ़ो_map__set_pid(thपढ़ोs, 0, 0);

	evsel = perf_evsel__new(&attr);
	__T("failed to create evsel", evsel);

	err = perf_evsel__खोलो(evsel, शून्य, thपढ़ोs);
	__T("failed to open evsel", err == 0);

	err = perf_evsel__mmap(evsel, 0);
	__T("failed to mmap evsel", err == 0);

	pc = perf_evsel__mmap_base(evsel, 0, 0);

#अगर defined(__i386__) || defined(__x86_64__)
	__T("userspace counter access not supported", pc->cap_user_rdpmc);
	__T("userspace counter access not enabled", pc->index);
	__T("userspace counter width not set", pc->pmc_width >= 32);
#पूर्ण_अगर

	perf_evsel__पढ़ो(evsel, 0, 0, &counts);
	__T("failed to read value for evsel", counts.val != 0);

	क्रम (i = 0; i < 5; i++) अणु
		अस्थिर पूर्णांक count = 0x10000 << i;
		__u64 start, end, last = 0;

		__T_VERBOSE("\tloop = %u, ", count);

		perf_evsel__पढ़ो(evsel, 0, 0, &counts);
		start = counts.val;

		जबतक (count--) ;

		perf_evsel__पढ़ो(evsel, 0, 0, &counts);
		end = counts.val;

		__T("invalid counter data", (end - start) > last);
		last = end - start;
		__T_VERBOSE("count = %llu\n", end - start);
	पूर्ण

	perf_evsel__munmap(evsel);
	perf_evsel__बंद(evsel);
	perf_evsel__delete(evsel);

	perf_thपढ़ो_map__put(thपढ़ोs);
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	__T_START;

	libperf_init(libperf_prपूर्णांक);

	test_stat_cpu();
	test_stat_thपढ़ो();
	test_stat_thपढ़ो_enable();
	test_stat_user_पढ़ो(PERF_COUNT_HW_INSTRUCTIONS);
	test_stat_user_पढ़ो(PERF_COUNT_HW_CPU_CYCLES);

	__T_END;
	वापस tests_failed == 0 ? 0 : -1;
पूर्ण
