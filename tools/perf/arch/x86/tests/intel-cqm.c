<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "tests/tests.h"
#समावेश "cloexec.h"
#समावेश "debug.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "arch-tests.h"
#समावेश <पूर्णांकernal/lib.h> // page_size

#समावेश <संकेत.स>
#समावेश <sys/mman.h>
#समावेश <sys/रुको.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>

अटल pid_t spawn(व्योम)
अणु
	pid_t pid;

	pid = विभाजन();
	अगर (pid)
		वापस pid;

	जबतक(1)
		sleep(5);
	वापस 0;
पूर्ण

/*
 * Create an event group that contains both a sampled hardware
 * (cpu-cycles) and software (पूर्णांकel_cqm/llc_occupancy/) event. We then
 * रुको क्रम the hardware perf counter to overflow and generate a PMI,
 * which triggers an event पढ़ो क्रम both of the events in the group.
 *
 * Since पढ़ोing Intel CQM event counters requires sending SMP IPIs, the
 * CQM pmu needs to handle the above situation gracefully, and वापस
 * the last पढ़ो counter value to aव्योम triggering a WARN_ON_ONCE() in
 * smp_call_function_many() caused by sending IPIs from NMI context.
 */
पूर्णांक test__पूर्णांकel_cqm_count_nmi_context(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा evlist *evlist = शून्य;
	काष्ठा evsel *evsel = शून्य;
	काष्ठा perf_event_attr pe;
	पूर्णांक i, fd[2], flag, ret;
	माप_प्रकार mmap_len;
	व्योम *event;
	pid_t pid;
	पूर्णांक err = TEST_FAIL;

	flag = perf_event_खोलो_cloexec_flag();

	evlist = evlist__new();
	अगर (!evlist) अणु
		pr_debug("evlist__new failed\n");
		वापस TEST_FAIL;
	पूर्ण

	ret = parse_events(evlist, "intel_cqm/llc_occupancy/", शून्य);
	अगर (ret) अणु
		pr_debug("parse_events failed, is \"intel_cqm/llc_occupancy/\" available?\n");
		err = TEST_SKIP;
		जाओ out;
	पूर्ण

	evsel = evlist__first(evlist);
	अगर (!evsel) अणु
		pr_debug("evlist__first failed\n");
		जाओ out;
	पूर्ण

	स_रखो(&pe, 0, माप(pe));
	pe.size = माप(pe);

	pe.type = PERF_TYPE_HARDWARE;
	pe.config = PERF_COUNT_HW_CPU_CYCLES;
	pe.पढ़ो_क्रमmat = PERF_FORMAT_GROUP;

	pe.sample_period = 128;
	pe.sample_type = PERF_SAMPLE_IP | PERF_SAMPLE_READ;

	pid = spawn();

	fd[0] = sys_perf_event_खोलो(&pe, pid, -1, -1, flag);
	अगर (fd[0] < 0) अणु
		pr_debug("failed to open event\n");
		जाओ out;
	पूर्ण

	स_रखो(&pe, 0, माप(pe));
	pe.size = माप(pe);

	pe.type = evsel->attr.type;
	pe.config = evsel->attr.config;

	fd[1] = sys_perf_event_खोलो(&pe, pid, -1, fd[0], flag);
	अगर (fd[1] < 0) अणु
		pr_debug("failed to open event\n");
		जाओ out;
	पूर्ण

	/*
	 * Pick a घातer-of-two number of pages + 1 क्रम the meta-data
	 * page (काष्ठा perf_event_mmap_page). See tools/perf/design.txt.
	 */
	mmap_len = page_size * 65;

	event = mmap(शून्य, mmap_len, PROT_READ, MAP_SHARED, fd[0], 0);
	अगर (event == (व्योम *)(-1)) अणु
		pr_debug("failed to mmap %d\n", त्रुटि_सं);
		जाओ out;
	पूर्ण

	sleep(1);

	err = TEST_OK;

	munmap(event, mmap_len);

	क्रम (i = 0; i < 2; i++)
		बंद(fd[i]);

	समाप्त(pid, SIGKILL);
	रुको(शून्य);
out:
	evlist__delete(evlist);
	वापस err;
पूर्ण
