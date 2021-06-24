<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
/* For the CLR_() macros */
#समावेश <pthपढ़ो.h>
#समावेश <मानककोष.स>
#समावेश <perf/cpumap.h>

#समावेश "debug.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "thread_map.h"
#समावेश "tests.h"
#समावेश "util/mmap.h"
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <perf/evlist.h>
#समावेश <perf/mmap.h>

/*
 * This test will generate अक्रमom numbers of calls to some getpid syscalls,
 * then establish an mmap क्रम a group of events that are created to monitor
 * the syscalls.
 *
 * It will receive the events, using mmap, use its PERF_SAMPLE_ID generated
 * sample.id field to map back to its respective perf_evsel instance.
 *
 * Then it checks अगर the number of syscalls reported as perf events by
 * the kernel corresponds to the number of syscalls made.
 */
पूर्णांक test__basic_mmap(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक err = -1;
	जोड़ perf_event *event;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
	काष्ठा perf_cpu_map *cpus;
	काष्ठा evlist *evlist;
	cpu_set_t cpu_set;
	स्थिर अक्षर *syscall_names[] = अणु "getsid", "getppid", "getpgid", पूर्ण;
	pid_t (*syscalls[])(व्योम) = अणु (व्योम *)माला_लोid, getppid, (व्योम*)getpgid पूर्ण;
#घोषणा nsyscalls ARRAY_SIZE(syscall_names)
	अचिन्हित पूर्णांक nr_events[nsyscalls],
		     expected_nr_events[nsyscalls], i, j;
	काष्ठा evsel *evsels[nsyscalls], *evsel;
	अक्षर sbuf[STRERR_बफ_मानE];
	काष्ठा mmap *md;

	thपढ़ोs = thपढ़ो_map__new(-1, getpid(), अच_पूर्णांक_उच्च);
	अगर (thपढ़ोs == शून्य) अणु
		pr_debug("thread_map__new\n");
		वापस -1;
	पूर्ण

	cpus = perf_cpu_map__new(शून्य);
	अगर (cpus == शून्य) अणु
		pr_debug("perf_cpu_map__new\n");
		जाओ out_मुक्त_thपढ़ोs;
	पूर्ण

	CPU_ZERO(&cpu_set);
	CPU_SET(cpus->map[0], &cpu_set);
	sched_setaffinity(0, माप(cpu_set), &cpu_set);
	अगर (sched_setaffinity(0, माप(cpu_set), &cpu_set) < 0) अणु
		pr_debug("sched_setaffinity() failed on CPU %d: %s ",
			 cpus->map[0], str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out_मुक्त_cpus;
	पूर्ण

	evlist = evlist__new();
	अगर (evlist == शून्य) अणु
		pr_debug("evlist__new\n");
		जाओ out_मुक्त_cpus;
	पूर्ण

	perf_evlist__set_maps(&evlist->core, cpus, thपढ़ोs);

	क्रम (i = 0; i < nsyscalls; ++i) अणु
		अक्षर name[64];

		snम_लिखो(name, माप(name), "sys_enter_%s", syscall_names[i]);
		evsels[i] = evsel__newtp("syscalls", name);
		अगर (IS_ERR(evsels[i])) अणु
			pr_debug("evsel__new(%s)\n", name);
			जाओ out_delete_evlist;
		पूर्ण

		evsels[i]->core.attr.wakeup_events = 1;
		evsel__set_sample_id(evsels[i], false);

		evlist__add(evlist, evsels[i]);

		अगर (evsel__खोलो(evsels[i], cpus, thपढ़ोs) < 0) अणु
			pr_debug("failed to open counter: %s, "
				 "tweak /proc/sys/kernel/perf_event_paranoid?\n",
				 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
			जाओ out_delete_evlist;
		पूर्ण

		nr_events[i] = 0;
		expected_nr_events[i] = 1 + अक्रम() % 127;
	पूर्ण

	अगर (evlist__mmap(evlist, 128) < 0) अणु
		pr_debug("failed to mmap events: %d (%s)\n", त्रुटि_सं,
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out_delete_evlist;
	पूर्ण

	क्रम (i = 0; i < nsyscalls; ++i)
		क्रम (j = 0; j < expected_nr_events[i]; ++j) अणु
			पूर्णांक foo = syscalls[i]();
			++foo;
		पूर्ण

	md = &evlist->mmap[0];
	अगर (perf_mmap__पढ़ो_init(&md->core) < 0)
		जाओ out_init;

	जबतक ((event = perf_mmap__पढ़ो_event(&md->core)) != शून्य) अणु
		काष्ठा perf_sample sample;

		अगर (event->header.type != PERF_RECORD_SAMPLE) अणु
			pr_debug("unexpected %s event\n",
				 perf_event__name(event->header.type));
			जाओ out_delete_evlist;
		पूर्ण

		err = evlist__parse_sample(evlist, event, &sample);
		अगर (err) अणु
			pr_err("Can't parse sample, err = %d\n", err);
			जाओ out_delete_evlist;
		पूर्ण

		err = -1;
		evsel = evlist__id2evsel(evlist, sample.id);
		अगर (evsel == शून्य) अणु
			pr_debug("event with id %" PRIu64
				 " doesn't map to an evsel\n", sample.id);
			जाओ out_delete_evlist;
		पूर्ण
		nr_events[evsel->idx]++;
		perf_mmap__consume(&md->core);
	पूर्ण
	perf_mmap__पढ़ो_करोne(&md->core);

out_init:
	err = 0;
	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (nr_events[evsel->idx] != expected_nr_events[evsel->idx]) अणु
			pr_debug("expected %d %s events, got %d\n",
				 expected_nr_events[evsel->idx],
				 evsel__name(evsel), nr_events[evsel->idx]);
			err = -1;
			जाओ out_delete_evlist;
		पूर्ण
	पूर्ण

out_delete_evlist:
	evlist__delete(evlist);
out_मुक्त_cpus:
	perf_cpu_map__put(cpus);
out_मुक्त_thपढ़ोs:
	perf_thपढ़ो_map__put(thपढ़ोs);
	वापस err;
पूर्ण
