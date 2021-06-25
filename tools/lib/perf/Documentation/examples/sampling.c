<शैली गुरु>
#समावेश <linux/perf_event.h>
#समावेश <perf/evlist.h>
#समावेश <perf/evsel.h>
#समावेश <perf/cpumap.h>
#समावेश <perf/thपढ़ोmap.h>
#समावेश <perf/mmap.h>
#समावेश <perf/core.h>
#समावेश <perf/event.h>
#समावेश <मानकपन.स>
#समावेश <unistd.h>

अटल पूर्णांक libperf_prपूर्णांक(क्रमागत libperf_prपूर्णांक_level level,
                         स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	वापस भख_लिखो(मानक_त्रुटि, fmt, ap);
पूर्ण

जोड़ u64_swap अणु
	__u64 val64;
	__u32 val32[2];
पूर्ण;

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा perf_evlist *evlist;
	काष्ठा perf_evsel *evsel;
	काष्ठा perf_mmap *map;
	काष्ठा perf_cpu_map *cpus;
	काष्ठा perf_event_attr attr = अणु
		.type        = PERF_TYPE_HARDWARE,
		.config      = PERF_COUNT_HW_CPU_CYCLES,
		.disabled    = 1,
		.freq        = 1,
		.sample_freq = 10,
		.sample_type = PERF_SAMPLE_IP|PERF_SAMPLE_TID|PERF_SAMPLE_CPU|PERF_SAMPLE_PERIOD,
	पूर्ण;
	पूर्णांक err = -1;
	जोड़ perf_event *event;

	libperf_init(libperf_prपूर्णांक);

	cpus = perf_cpu_map__new(शून्य);
	अगर (!cpus) अणु
		ख_लिखो(मानक_त्रुटि, "failed to create cpus\n");
		वापस -1;
	पूर्ण

	evlist = perf_evlist__new();
	अगर (!evlist) अणु
		ख_लिखो(मानक_त्रुटि, "failed to create evlist\n");
		जाओ out_cpus;
	पूर्ण

	evsel = perf_evsel__new(&attr);
	अगर (!evsel) अणु
		ख_लिखो(मानक_त्रुटि, "failed to create cycles\n");
		जाओ out_cpus;
	पूर्ण

	perf_evlist__add(evlist, evsel);

	perf_evlist__set_maps(evlist, cpus, शून्य);

	err = perf_evlist__खोलो(evlist);
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "failed to open evlist\n");
		जाओ out_evlist;
	पूर्ण

	err = perf_evlist__mmap(evlist, 4);
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "failed to mmap evlist\n");
		जाओ out_evlist;
	पूर्ण

	perf_evlist__enable(evlist);
	sleep(3);
	perf_evlist__disable(evlist);

	perf_evlist__क्रम_each_mmap(evlist, map, false) अणु
		अगर (perf_mmap__पढ़ो_init(map) < 0)
			जारी;

		जबतक ((event = perf_mmap__पढ़ो_event(map)) != शून्य) अणु
			पूर्णांक cpu, pid, tid;
			__u64 ip, period, *array;
			जोड़ u64_swap u;

			array = event->sample.array;

			ip = *array;
			array++;

			u.val64 = *array;
			pid = u.val32[0];
			tid = u.val32[1];
			array++;

			u.val64 = *array;
			cpu = u.val32[0];
			array++;

			period = *array;

			ख_लिखो(मानक_निकास, "cpu %3d, pid %6d, tid %6d, ip %20llx, period %20llu\n",
				cpu, pid, tid, ip, period);

			perf_mmap__consume(map);
		पूर्ण

		perf_mmap__पढ़ो_करोne(map);
	पूर्ण

out_evlist:
	perf_evlist__delete(evlist);
out_cpus:
	perf_cpu_map__put(cpus);
	वापस err;
पूर्ण
