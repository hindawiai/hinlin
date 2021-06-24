<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE // needed क्रम sched.h to get sched_[gs]etaffinity and CPU_(ZERO,SET)
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <मानकतर्क.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <linux/perf_event.h>
#समावेश <linux/सीमा.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <sys/prctl.h>
#समावेश <perf/cpumap.h>
#समावेश <perf/thपढ़ोmap.h>
#समावेश <perf/evlist.h>
#समावेश <perf/evsel.h>
#समावेश <perf/mmap.h>
#समावेश <perf/event.h>
#समावेश <पूर्णांकernal/tests.h>
#समावेश <api/fs/fs.h>

अटल पूर्णांक libperf_prपूर्णांक(क्रमागत libperf_prपूर्णांक_level level,
			 स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	वापस भख_लिखो(मानक_त्रुटि, fmt, ap);
पूर्ण

अटल पूर्णांक test_stat_cpu(व्योम)
अणु
	काष्ठा perf_cpu_map *cpus;
	काष्ठा perf_evlist *evlist;
	काष्ठा perf_evsel *evsel;
	काष्ठा perf_event_attr attr1 = अणु
		.type	= PERF_TYPE_SOFTWARE,
		.config	= PERF_COUNT_SW_CPU_CLOCK,
	पूर्ण;
	काष्ठा perf_event_attr attr2 = अणु
		.type	= PERF_TYPE_SOFTWARE,
		.config	= PERF_COUNT_SW_TASK_CLOCK,
	पूर्ण;
	पूर्णांक err, cpu, पंचांगp;

	cpus = perf_cpu_map__new(शून्य);
	__T("failed to create cpus", cpus);

	evlist = perf_evlist__new();
	__T("failed to create evlist", evlist);

	evsel = perf_evsel__new(&attr1);
	__T("failed to create evsel1", evsel);

	perf_evlist__add(evlist, evsel);

	evsel = perf_evsel__new(&attr2);
	__T("failed to create evsel2", evsel);

	perf_evlist__add(evlist, evsel);

	perf_evlist__set_maps(evlist, cpus, शून्य);

	err = perf_evlist__खोलो(evlist);
	__T("failed to open evsel", err == 0);

	perf_evlist__क्रम_each_evsel(evlist, evsel) अणु
		cpus = perf_evsel__cpus(evsel);

		perf_cpu_map__क्रम_each_cpu(cpu, पंचांगp, cpus) अणु
			काष्ठा perf_counts_values counts = अणु .val = 0 पूर्ण;

			perf_evsel__पढ़ो(evsel, cpu, 0, &counts);
			__T("failed to read value for evsel", counts.val != 0);
		पूर्ण
	पूर्ण

	perf_evlist__बंद(evlist);
	perf_evlist__delete(evlist);

	perf_cpu_map__put(cpus);
	वापस 0;
पूर्ण

अटल पूर्णांक test_stat_thपढ़ो(व्योम)
अणु
	काष्ठा perf_counts_values counts = अणु .val = 0 पूर्ण;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
	काष्ठा perf_evlist *evlist;
	काष्ठा perf_evsel *evsel;
	काष्ठा perf_event_attr attr1 = अणु
		.type	= PERF_TYPE_SOFTWARE,
		.config	= PERF_COUNT_SW_CPU_CLOCK,
	पूर्ण;
	काष्ठा perf_event_attr attr2 = अणु
		.type	= PERF_TYPE_SOFTWARE,
		.config	= PERF_COUNT_SW_TASK_CLOCK,
	पूर्ण;
	पूर्णांक err;

	thपढ़ोs = perf_thपढ़ो_map__new_dummy();
	__T("failed to create threads", thपढ़ोs);

	perf_thपढ़ो_map__set_pid(thपढ़ोs, 0, 0);

	evlist = perf_evlist__new();
	__T("failed to create evlist", evlist);

	evsel = perf_evsel__new(&attr1);
	__T("failed to create evsel1", evsel);

	perf_evlist__add(evlist, evsel);

	evsel = perf_evsel__new(&attr2);
	__T("failed to create evsel2", evsel);

	perf_evlist__add(evlist, evsel);

	perf_evlist__set_maps(evlist, शून्य, thपढ़ोs);

	err = perf_evlist__खोलो(evlist);
	__T("failed to open evsel", err == 0);

	perf_evlist__क्रम_each_evsel(evlist, evsel) अणु
		perf_evsel__पढ़ो(evsel, 0, 0, &counts);
		__T("failed to read value for evsel", counts.val != 0);
	पूर्ण

	perf_evlist__बंद(evlist);
	perf_evlist__delete(evlist);

	perf_thपढ़ो_map__put(thपढ़ोs);
	वापस 0;
पूर्ण

अटल पूर्णांक test_stat_thपढ़ो_enable(व्योम)
अणु
	काष्ठा perf_counts_values counts = अणु .val = 0 पूर्ण;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
	काष्ठा perf_evlist *evlist;
	काष्ठा perf_evsel *evsel;
	काष्ठा perf_event_attr attr1 = अणु
		.type	  = PERF_TYPE_SOFTWARE,
		.config	  = PERF_COUNT_SW_CPU_CLOCK,
		.disabled = 1,
	पूर्ण;
	काष्ठा perf_event_attr attr2 = अणु
		.type	  = PERF_TYPE_SOFTWARE,
		.config	  = PERF_COUNT_SW_TASK_CLOCK,
		.disabled = 1,
	पूर्ण;
	पूर्णांक err;

	thपढ़ोs = perf_thपढ़ो_map__new_dummy();
	__T("failed to create threads", thपढ़ोs);

	perf_thपढ़ो_map__set_pid(thपढ़ोs, 0, 0);

	evlist = perf_evlist__new();
	__T("failed to create evlist", evlist);

	evsel = perf_evsel__new(&attr1);
	__T("failed to create evsel1", evsel);

	perf_evlist__add(evlist, evsel);

	evsel = perf_evsel__new(&attr2);
	__T("failed to create evsel2", evsel);

	perf_evlist__add(evlist, evsel);

	perf_evlist__set_maps(evlist, शून्य, thपढ़ोs);

	err = perf_evlist__खोलो(evlist);
	__T("failed to open evsel", err == 0);

	perf_evlist__क्रम_each_evsel(evlist, evsel) अणु
		perf_evsel__पढ़ो(evsel, 0, 0, &counts);
		__T("failed to read value for evsel", counts.val == 0);
	पूर्ण

	perf_evlist__enable(evlist);

	perf_evlist__क्रम_each_evsel(evlist, evsel) अणु
		perf_evsel__पढ़ो(evsel, 0, 0, &counts);
		__T("failed to read value for evsel", counts.val != 0);
	पूर्ण

	perf_evlist__disable(evlist);

	perf_evlist__बंद(evlist);
	perf_evlist__delete(evlist);

	perf_thपढ़ो_map__put(thपढ़ोs);
	वापस 0;
पूर्ण

अटल पूर्णांक test_mmap_thपढ़ो(व्योम)
अणु
	काष्ठा perf_evlist *evlist;
	काष्ठा perf_evsel *evsel;
	काष्ठा perf_mmap *map;
	काष्ठा perf_cpu_map *cpus;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
	काष्ठा perf_event_attr attr = अणु
		.type             = PERF_TYPE_TRACEPOINT,
		.sample_period    = 1,
		.wakeup_watermark = 1,
		.disabled         = 1,
	पूर्ण;
	अक्षर path[PATH_MAX];
	पूर्णांक id, err, pid, go_pipe[2];
	जोड़ perf_event *event;
	पूर्णांक count = 0;

	snम_लिखो(path, PATH_MAX, "%s/kernel/debug/tracing/events/syscalls/sys_enter_prctl/id",
		 sysfs__mountpoपूर्णांक());

	अगर (filename__पढ़ो_पूर्णांक(path, &id)) अणु
		tests_failed++;
		ख_लिखो(मानक_त्रुटि, "error: failed to get tracepoint id: %s\n", path);
		वापस -1;
	पूर्ण

	attr.config = id;

	err = pipe(go_pipe);
	__T("failed to create pipe", err == 0);

	ख_साफ(शून्य);

	pid = विभाजन();
	अगर (!pid) अणु
		पूर्णांक i;
		अक्षर bf;

		पढ़ो(go_pipe[0], &bf, 1);

		/* Generate 100 prctl calls. */
		क्रम (i = 0; i < 100; i++)
			prctl(0, 0, 0, 0, 0);

		निकास(0);
	पूर्ण

	thपढ़ोs = perf_thपढ़ो_map__new_dummy();
	__T("failed to create threads", thपढ़ोs);

	cpus = perf_cpu_map__dummy_new();
	__T("failed to create cpus", cpus);

	perf_thपढ़ो_map__set_pid(thपढ़ोs, 0, pid);

	evlist = perf_evlist__new();
	__T("failed to create evlist", evlist);

	evsel = perf_evsel__new(&attr);
	__T("failed to create evsel1", evsel);

	perf_evlist__add(evlist, evsel);

	perf_evlist__set_maps(evlist, cpus, thपढ़ोs);

	err = perf_evlist__खोलो(evlist);
	__T("failed to open evlist", err == 0);

	err = perf_evlist__mmap(evlist, 4);
	__T("failed to mmap evlist", err == 0);

	perf_evlist__enable(evlist);

	/* kick the child and रुको क्रम it to finish */
	ग_लिखो(go_pipe[1], "A", 1);
	रुकोpid(pid, शून्य, 0);

	/*
	 * There's no need to call perf_evlist__disable,
	 * monitored process is dead now.
	 */

	perf_evlist__क्रम_each_mmap(evlist, map, false) अणु
		अगर (perf_mmap__पढ़ो_init(map) < 0)
			जारी;

		जबतक ((event = perf_mmap__पढ़ो_event(map)) != शून्य) अणु
			count++;
			perf_mmap__consume(map);
		पूर्ण

		perf_mmap__पढ़ो_करोne(map);
	पूर्ण

	/* calls perf_evlist__munmap/perf_evlist__बंद */
	perf_evlist__delete(evlist);

	perf_thपढ़ो_map__put(thपढ़ोs);
	perf_cpu_map__put(cpus);

	/*
	 * The generated prctl calls should match the
	 * number of events in the buffer.
	 */
	__T("failed count", count == 100);

	वापस 0;
पूर्ण

अटल पूर्णांक test_mmap_cpus(व्योम)
अणु
	काष्ठा perf_evlist *evlist;
	काष्ठा perf_evsel *evsel;
	काष्ठा perf_mmap *map;
	काष्ठा perf_cpu_map *cpus;
	काष्ठा perf_event_attr attr = अणु
		.type             = PERF_TYPE_TRACEPOINT,
		.sample_period    = 1,
		.wakeup_watermark = 1,
		.disabled         = 1,
	पूर्ण;
	cpu_set_t saved_mask;
	अक्षर path[PATH_MAX];
	पूर्णांक id, err, cpu, पंचांगp;
	जोड़ perf_event *event;
	पूर्णांक count = 0;

	snम_लिखो(path, PATH_MAX, "%s/kernel/debug/tracing/events/syscalls/sys_enter_prctl/id",
		 sysfs__mountpoपूर्णांक());

	अगर (filename__पढ़ो_पूर्णांक(path, &id)) अणु
		ख_लिखो(मानक_त्रुटि, "error: failed to get tracepoint id: %s\n", path);
		वापस -1;
	पूर्ण

	attr.config = id;

	cpus = perf_cpu_map__new(शून्य);
	__T("failed to create cpus", cpus);

	evlist = perf_evlist__new();
	__T("failed to create evlist", evlist);

	evsel = perf_evsel__new(&attr);
	__T("failed to create evsel1", evsel);

	perf_evlist__add(evlist, evsel);

	perf_evlist__set_maps(evlist, cpus, शून्य);

	err = perf_evlist__खोलो(evlist);
	__T("failed to open evlist", err == 0);

	err = perf_evlist__mmap(evlist, 4);
	__T("failed to mmap evlist", err == 0);

	perf_evlist__enable(evlist);

	err = sched_getaffinity(0, माप(saved_mask), &saved_mask);
	__T("sched_getaffinity failed", err == 0);

	perf_cpu_map__क्रम_each_cpu(cpu, पंचांगp, cpus) अणु
		cpu_set_t mask;

		CPU_ZERO(&mask);
		CPU_SET(cpu, &mask);

		err = sched_setaffinity(0, माप(mask), &mask);
		__T("sched_setaffinity failed", err == 0);

		prctl(0, 0, 0, 0, 0);
	पूर्ण

	err = sched_setaffinity(0, माप(saved_mask), &saved_mask);
	__T("sched_setaffinity failed", err == 0);

	perf_evlist__disable(evlist);

	perf_evlist__क्रम_each_mmap(evlist, map, false) अणु
		अगर (perf_mmap__पढ़ो_init(map) < 0)
			जारी;

		जबतक ((event = perf_mmap__पढ़ो_event(map)) != शून्य) अणु
			count++;
			perf_mmap__consume(map);
		पूर्ण

		perf_mmap__पढ़ो_करोne(map);
	पूर्ण

	/* calls perf_evlist__munmap/perf_evlist__बंद */
	perf_evlist__delete(evlist);

	/*
	 * The generated prctl events should match the
	 * number of cpus or be bigger (we are प्रणाली-wide).
	 */
	__T("failed count", count >= perf_cpu_map__nr(cpus));

	perf_cpu_map__put(cpus);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	__T_START;

	libperf_init(libperf_prपूर्णांक);

	test_stat_cpu();
	test_stat_thपढ़ो();
	test_stat_thपढ़ो_enable();
	test_mmap_thपढ़ो();
	test_mmap_cpus();

	__T_END;
	वापस tests_failed == 0 ? 0 : -1;
पूर्ण
