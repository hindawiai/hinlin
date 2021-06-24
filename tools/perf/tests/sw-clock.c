<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <sys/mman.h>
#समावेश <linux/माला.स>

#समावेश "tests.h"
#समावेश "util/debug.h"
#समावेश "util/evsel.h"
#समावेश "util/evlist.h"
#समावेश "util/cpumap.h"
#समावेश "util/mmap.h"
#समावेश "util/thread_map.h"
#समावेश <perf/evlist.h>
#समावेश <perf/mmap.h>

#घोषणा NR_LOOPS  10000000

/*
 * This test will खोलो software घड़ी events (cpu-घड़ी, task-घड़ी)
 * then check their frequency -> period conversion has no artअगरact of
 * setting period to 1 क्रमcefully.
 */
अटल पूर्णांक __test__sw_घड़ी_freq(क्रमागत perf_sw_ids घड़ी_id)
अणु
	पूर्णांक i, err = -1;
	अस्थिर पूर्णांक पंचांगp = 0;
	u64 total_periods = 0;
	पूर्णांक nr_samples = 0;
	अक्षर sbuf[STRERR_बफ_मानE];
	जोड़ perf_event *event;
	काष्ठा evsel *evsel;
	काष्ठा evlist *evlist;
	काष्ठा perf_event_attr attr = अणु
		.type = PERF_TYPE_SOFTWARE,
		.config = घड़ी_id,
		.sample_type = PERF_SAMPLE_PERIOD,
		.exclude_kernel = 1,
		.disabled = 1,
		.freq = 1,
	पूर्ण;
	काष्ठा perf_cpu_map *cpus = शून्य;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs = शून्य;
	काष्ठा mmap *md;

	attr.sample_freq = 500;

	evlist = evlist__new();
	अगर (evlist == शून्य) अणु
		pr_debug("evlist__new\n");
		वापस -1;
	पूर्ण

	evsel = evsel__new(&attr);
	अगर (evsel == शून्य) अणु
		pr_debug("evsel__new\n");
		जाओ out_delete_evlist;
	पूर्ण
	evlist__add(evlist, evsel);

	cpus = perf_cpu_map__dummy_new();
	thपढ़ोs = thपढ़ो_map__new_by_tid(getpid());
	अगर (!cpus || !thपढ़ोs) अणु
		err = -ENOMEM;
		pr_debug("Not enough memory to create thread/cpu maps\n");
		जाओ out_delete_evlist;
	पूर्ण

	perf_evlist__set_maps(&evlist->core, cpus, thपढ़ोs);

	अगर (evlist__खोलो(evlist)) अणु
		स्थिर अक्षर *knob = "/proc/sys/kernel/perf_event_max_sample_rate";

		err = -त्रुटि_सं;
		pr_debug("Couldn't open evlist: %s\nHint: check %s, using %" PRIu64 " in this test.\n",
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)),
			 knob, (u64)attr.sample_freq);
		जाओ out_delete_evlist;
	पूर्ण

	err = evlist__mmap(evlist, 128);
	अगर (err < 0) अणु
		pr_debug("failed to mmap event: %d (%s)\n", त्रुटि_सं,
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out_delete_evlist;
	पूर्ण

	evlist__enable(evlist);

	/* collect samples */
	क्रम (i = 0; i < NR_LOOPS; i++)
		पंचांगp++;

	evlist__disable(evlist);

	md = &evlist->mmap[0];
	अगर (perf_mmap__पढ़ो_init(&md->core) < 0)
		जाओ out_init;

	जबतक ((event = perf_mmap__पढ़ो_event(&md->core)) != शून्य) अणु
		काष्ठा perf_sample sample;

		अगर (event->header.type != PERF_RECORD_SAMPLE)
			जाओ next_event;

		err = evlist__parse_sample(evlist, event, &sample);
		अगर (err < 0) अणु
			pr_debug("Error during parse sample\n");
			जाओ out_delete_evlist;
		पूर्ण

		total_periods += sample.period;
		nr_samples++;
next_event:
		perf_mmap__consume(&md->core);
	पूर्ण
	perf_mmap__पढ़ो_करोne(&md->core);

out_init:
	अगर ((u64) nr_samples == total_periods) अणु
		pr_debug("All (%d) samples have period value of 1!\n",
			 nr_samples);
		err = -1;
	पूर्ण

out_delete_evlist:
	perf_cpu_map__put(cpus);
	perf_thपढ़ो_map__put(thपढ़ोs);
	evlist__delete(evlist);
	वापस err;
पूर्ण

पूर्णांक test__sw_घड़ी_freq(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक ret;

	ret = __test__sw_घड़ी_freq(PERF_COUNT_SW_CPU_CLOCK);
	अगर (!ret)
		ret = __test__sw_घड़ी_freq(PERF_COUNT_SW_TASK_CLOCK);

	वापस ret;
पूर्ण
