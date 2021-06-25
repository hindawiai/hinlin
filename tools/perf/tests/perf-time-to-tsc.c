<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <सीमा.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <linux/types.h>
#समावेश <sys/prctl.h>
#समावेश <perf/cpumap.h>
#समावेश <perf/evlist.h>
#समावेश <perf/mmap.h>

#समावेश "debug.h"
#समावेश "parse-events.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "thread_map.h"
#समावेश "record.h"
#समावेश "tsc.h"
#समावेश "mmap.h"
#समावेश "tests.h"
#समावेश "pmu.h"

#घोषणा CHECK__(x) अणु				\
	जबतक ((x) < 0) अणु			\
		pr_debug(#x " failed!\n");	\
		जाओ out_err;			\
	पूर्ण					\
पूर्ण

#घोषणा CHECK_NOT_शून्य__(x) अणु			\
	जबतक ((x) == शून्य) अणु			\
		pr_debug(#x " failed!\n");	\
		जाओ out_err;			\
	पूर्ण					\
पूर्ण

/**
 * test__perf_समय_प्रकारo_tsc - test converting perf समय to TSC.
 *
 * This function implements a test that checks that the conversion of perf समय
 * to and from TSC is consistent with the order of events.  If the test passes
 * %0 is वापसed, otherwise %-1 is वापसed.  If TSC conversion is not
 * supported then then the test passes but " (not supported)" is prपूर्णांकed.
 */
पूर्णांक test__perf_समय_प्रकारo_tsc(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा record_opts opts = अणु
		.mmap_pages	     = अच_पूर्णांक_उच्च,
		.user_freq	     = अच_पूर्णांक_उच्च,
		.user_पूर्णांकerval	     = ULदीर्घ_उच्च,
		.target		     = अणु
			.uses_mmap   = true,
		पूर्ण,
		.sample_समय	     = true,
	पूर्ण;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs = शून्य;
	काष्ठा perf_cpu_map *cpus = शून्य;
	काष्ठा evlist *evlist = शून्य;
	काष्ठा evsel *evsel = शून्य;
	पूर्णांक err = -1, ret, i;
	स्थिर अक्षर *comm1, *comm2;
	काष्ठा perf_tsc_conversion tc;
	काष्ठा perf_event_mmap_page *pc;
	जोड़ perf_event *event;
	u64 test_tsc, comm1_tsc, comm2_tsc;
	u64 test_समय, comm1_समय = 0, comm2_समय = 0;
	काष्ठा mmap *md;

	thपढ़ोs = thपढ़ो_map__new(-1, getpid(), अच_पूर्णांक_उच्च);
	CHECK_NOT_शून्य__(thपढ़ोs);

	cpus = perf_cpu_map__new(शून्य);
	CHECK_NOT_शून्य__(cpus);

	evlist = evlist__new();
	CHECK_NOT_शून्य__(evlist);

	perf_evlist__set_maps(&evlist->core, cpus, thपढ़ोs);

	CHECK__(parse_events(evlist, "cycles:u", शून्य));

	evlist__config(evlist, &opts, शून्य);

	evsel = evlist__first(evlist);

	evsel->core.attr.comm = 1;
	evsel->core.attr.disabled = 1;
	evsel->core.attr.enable_on_exec = 0;

	/*
	 * For hybrid "cycles:u", it creates two events.
	 * Init the second evsel here.
	 */
	अगर (perf_pmu__has_hybrid()) अणु
		evsel = evsel__next(evsel);
		evsel->core.attr.comm = 1;
		evsel->core.attr.disabled = 1;
		evsel->core.attr.enable_on_exec = 0;
	पूर्ण

	CHECK__(evlist__खोलो(evlist));

	CHECK__(evlist__mmap(evlist, अच_पूर्णांक_उच्च));

	pc = evlist->mmap[0].core.base;
	ret = perf_पढ़ो_tsc_conversion(pc, &tc);
	अगर (ret) अणु
		अगर (ret == -EOPNOTSUPP) अणु
			ख_लिखो(मानक_त्रुटि, " (not supported)");
			वापस 0;
		पूर्ण
		जाओ out_err;
	पूर्ण

	evlist__enable(evlist);

	comm1 = "Test COMM 1";
	CHECK__(prctl(PR_SET_NAME, (अचिन्हित दीर्घ)comm1, 0, 0, 0));

	test_tsc = rdtsc();

	comm2 = "Test COMM 2";
	CHECK__(prctl(PR_SET_NAME, (अचिन्हित दीर्घ)comm2, 0, 0, 0));

	evlist__disable(evlist);

	क्रम (i = 0; i < evlist->core.nr_mmaps; i++) अणु
		md = &evlist->mmap[i];
		अगर (perf_mmap__पढ़ो_init(&md->core) < 0)
			जारी;

		जबतक ((event = perf_mmap__पढ़ो_event(&md->core)) != शून्य) अणु
			काष्ठा perf_sample sample;

			अगर (event->header.type != PERF_RECORD_COMM ||
			    (pid_t)event->comm.pid != getpid() ||
			    (pid_t)event->comm.tid != getpid())
				जाओ next_event;

			अगर (म_भेद(event->comm.comm, comm1) == 0) अणु
				CHECK__(evsel__parse_sample(evsel, event, &sample));
				comm1_समय = sample.समय;
			पूर्ण
			अगर (म_भेद(event->comm.comm, comm2) == 0) अणु
				CHECK__(evsel__parse_sample(evsel, event, &sample));
				comm2_समय = sample.समय;
			पूर्ण
next_event:
			perf_mmap__consume(&md->core);
		पूर्ण
		perf_mmap__पढ़ो_करोne(&md->core);
	पूर्ण

	अगर (!comm1_समय || !comm2_समय)
		जाओ out_err;

	test_समय = tsc_to_perf_समय(test_tsc, &tc);
	comm1_tsc = perf_समय_प्रकारo_tsc(comm1_समय, &tc);
	comm2_tsc = perf_समय_प्रकारo_tsc(comm2_समय, &tc);

	pr_debug("1st event perf time %"PRIu64" tsc %"PRIu64"\n",
		 comm1_समय, comm1_tsc);
	pr_debug("rdtsc          time %"PRIu64" tsc %"PRIu64"\n",
		 test_समय, test_tsc);
	pr_debug("2nd event perf time %"PRIu64" tsc %"PRIu64"\n",
		 comm2_समय, comm2_tsc);

	अगर (test_समय <= comm1_समय ||
	    test_समय >= comm2_समय)
		जाओ out_err;

	अगर (test_tsc <= comm1_tsc ||
	    test_tsc >= comm2_tsc)
		जाओ out_err;

	err = 0;

out_err:
	evlist__delete(evlist);
	perf_cpu_map__put(cpus);
	perf_thपढ़ो_map__put(thपढ़ोs);
	वापस err;
पूर्ण

bool test__tsc_is_supported(व्योम)
अणु
	/*
	 * Except x86_64/i386 and Arm64, other archs करोn't support TSC in perf.
	 * Just enable the test क्रम x86_64/i386 and Arm64 archs.
	 */
#अगर defined(__x86_64__) || defined(__i386__) || defined(__aarch64__)
	वापस true;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण
