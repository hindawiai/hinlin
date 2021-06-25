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

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक count = 100000, err = 0;
	काष्ठा perf_evlist *evlist;
	काष्ठा perf_evsel *evsel;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
	काष्ठा perf_counts_values counts;

	काष्ठा perf_event_attr attr1 = अणु
		.type        = PERF_TYPE_SOFTWARE,
		.config      = PERF_COUNT_SW_CPU_CLOCK,
		.पढ़ो_क्रमmat = PERF_FORMAT_TOTAL_TIME_ENABLED|PERF_FORMAT_TOTAL_TIME_RUNNING,
		.disabled    = 1,
	पूर्ण;
	काष्ठा perf_event_attr attr2 = अणु
		.type        = PERF_TYPE_SOFTWARE,
		.config      = PERF_COUNT_SW_TASK_CLOCK,
		.पढ़ो_क्रमmat = PERF_FORMAT_TOTAL_TIME_ENABLED|PERF_FORMAT_TOTAL_TIME_RUNNING,
		.disabled    = 1,
	पूर्ण;

	libperf_init(libperf_prपूर्णांक);
	thपढ़ोs = perf_thपढ़ो_map__new_dummy();
	अगर (!thपढ़ोs) अणु
		ख_लिखो(मानक_त्रुटि, "failed to create threads\n");
		वापस -1;
	पूर्ण
	perf_thपढ़ो_map__set_pid(thपढ़ोs, 0, 0);
	evlist = perf_evlist__new();
	अगर (!evlist) अणु
		ख_लिखो(मानक_त्रुटि, "failed to create evlist\n");
		जाओ out_thपढ़ोs;
	पूर्ण
	evsel = perf_evsel__new(&attr1);
	अगर (!evsel) अणु
		ख_लिखो(मानक_त्रुटि, "failed to create evsel1\n");
		जाओ out_evlist;
	पूर्ण
	perf_evlist__add(evlist, evsel);
	evsel = perf_evsel__new(&attr2);
	अगर (!evsel) अणु
		ख_लिखो(मानक_त्रुटि, "failed to create evsel2\n");
		जाओ out_evlist;
	पूर्ण
	perf_evlist__add(evlist, evsel);
	perf_evlist__set_maps(evlist, शून्य, thपढ़ोs);
	err = perf_evlist__खोलो(evlist);
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "failed to open evsel\n");
		जाओ out_evlist;
	पूर्ण
	perf_evlist__enable(evlist);
	जबतक (count--);
	perf_evlist__disable(evlist);
	perf_evlist__क्रम_each_evsel(evlist, evsel) अणु
		perf_evsel__पढ़ो(evsel, 0, 0, &counts);
		ख_लिखो(मानक_निकास, "count %llu, enabled %llu, run %llu\n",
				counts.val, counts.ena, counts.run);
	पूर्ण
	perf_evlist__बंद(evlist);
out_evlist:
	perf_evlist__delete(evlist);
out_thपढ़ोs:
	perf_thपढ़ो_map__put(thपढ़ोs);
	वापस err;
पूर्ण
