<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <linux/माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <माला.स>
#समावेश <sys/रुको.h>
#समावेश <perf/cpumap.h>
#समावेश "tests.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "debug.h"
#समावेश "parse-events.h"
#समावेश "thread_map.h"
#समावेश "target.h"

अटल पूर्णांक attach__enable_on_exec(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__last(evlist);
	काष्ठा target target = अणु
		.uid = अच_पूर्णांक_उच्च,
	पूर्ण;
	स्थिर अक्षर *argv[] = अणु "true", शून्य, पूर्ण;
	अक्षर sbuf[STRERR_बफ_मानE];
	पूर्णांक err;

	pr_debug("attaching to spawned child, enable on exec\n");

	err = evlist__create_maps(evlist, &target);
	अगर (err < 0) अणु
		pr_debug("Not enough memory to create thread/cpu maps\n");
		वापस err;
	पूर्ण

	err = evlist__prepare_workload(evlist, &target, argv, false, शून्य);
	अगर (err < 0) अणु
		pr_debug("Couldn't run the workload!\n");
		वापस err;
	पूर्ण

	evsel->core.attr.enable_on_exec = 1;

	err = evlist__खोलो(evlist);
	अगर (err < 0) अणु
		pr_debug("perf_evlist__open: %s\n",
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		वापस err;
	पूर्ण

	वापस evlist__start_workload(evlist) == 1 ? TEST_OK : TEST_FAIL;
पूर्ण

अटल पूर्णांक detach__enable_on_exec(काष्ठा evlist *evlist)
अणु
	रुकोpid(evlist->workload.pid, शून्य, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक attach__current_disabled(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__last(evlist);
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
	पूर्णांक err;

	pr_debug("attaching to current thread as disabled\n");

	thपढ़ोs = thपढ़ो_map__new(-1, getpid(), अच_पूर्णांक_उच्च);
	अगर (thपढ़ोs == शून्य) अणु
		pr_debug("thread_map__new\n");
		वापस -1;
	पूर्ण

	evsel->core.attr.disabled = 1;

	err = evsel__खोलो_per_thपढ़ो(evsel, thपढ़ोs);
	अगर (err) अणु
		pr_debug("Failed to open event cpu-clock:u\n");
		वापस err;
	पूर्ण

	perf_thपढ़ो_map__put(thपढ़ोs);
	वापस evsel__enable(evsel) == 0 ? TEST_OK : TEST_FAIL;
पूर्ण

अटल पूर्णांक attach__current_enabled(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__last(evlist);
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
	पूर्णांक err;

	pr_debug("attaching to current thread as enabled\n");

	thपढ़ोs = thपढ़ो_map__new(-1, getpid(), अच_पूर्णांक_उच्च);
	अगर (thपढ़ोs == शून्य) अणु
		pr_debug("failed to call thread_map__new\n");
		वापस -1;
	पूर्ण

	err = evsel__खोलो_per_thपढ़ो(evsel, thपढ़ोs);

	perf_thपढ़ो_map__put(thपढ़ोs);
	वापस err == 0 ? TEST_OK : TEST_FAIL;
पूर्ण

अटल पूर्णांक detach__disable(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__last(evlist);

	वापस evsel__enable(evsel);
पूर्ण

अटल पूर्णांक attach__cpu_disabled(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__last(evlist);
	काष्ठा perf_cpu_map *cpus;
	पूर्णांक err;

	pr_debug("attaching to CPU 0 as enabled\n");

	cpus = perf_cpu_map__new("0");
	अगर (cpus == शून्य) अणु
		pr_debug("failed to call perf_cpu_map__new\n");
		वापस -1;
	पूर्ण

	evsel->core.attr.disabled = 1;

	err = evsel__खोलो_per_cpu(evsel, cpus, -1);
	अगर (err) अणु
		अगर (err == -EACCES)
			वापस TEST_SKIP;

		pr_debug("Failed to open event cpu-clock:u\n");
		वापस err;
	पूर्ण

	perf_cpu_map__put(cpus);
	वापस evsel__enable(evsel);
पूर्ण

अटल पूर्णांक attach__cpu_enabled(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel = evlist__last(evlist);
	काष्ठा perf_cpu_map *cpus;
	पूर्णांक err;

	pr_debug("attaching to CPU 0 as enabled\n");

	cpus = perf_cpu_map__new("0");
	अगर (cpus == शून्य) अणु
		pr_debug("failed to call perf_cpu_map__new\n");
		वापस -1;
	पूर्ण

	err = evsel__खोलो_per_cpu(evsel, cpus, -1);
	अगर (err == -EACCES)
		वापस TEST_SKIP;

	perf_cpu_map__put(cpus);
	वापस err ? TEST_FAIL : TEST_OK;
पूर्ण

अटल पूर्णांक test_बार(पूर्णांक (attach)(काष्ठा evlist *),
		      पूर्णांक (detach)(काष्ठा evlist *))
अणु
	काष्ठा perf_counts_values count;
	काष्ठा evlist *evlist = शून्य;
	काष्ठा evsel *evsel;
	पूर्णांक err = -1, i;

	evlist = evlist__new();
	अगर (!evlist) अणु
		pr_debug("failed to create event list\n");
		जाओ out_err;
	पूर्ण

	err = parse_events(evlist, "cpu-clock:u", शून्य);
	अगर (err) अणु
		pr_debug("failed to parse event cpu-clock:u\n");
		जाओ out_err;
	पूर्ण

	evsel = evlist__last(evlist);
	evsel->core.attr.पढ़ो_क्रमmat |=
		PERF_FORMAT_TOTAL_TIME_ENABLED |
		PERF_FORMAT_TOTAL_TIME_RUNNING;

	err = attach(evlist);
	अगर (err == TEST_SKIP) अणु
		pr_debug("  SKIP  : not enough rights\n");
		वापस err;
	पूर्ण

	TEST_ASSERT_VAL("failed to attach", !err);

	क्रम (i = 0; i < 100000000; i++) अणु पूर्ण

	TEST_ASSERT_VAL("failed to detach", !detach(evlist));

	perf_evsel__पढ़ो(&evsel->core, 0, 0, &count);

	err = !(count.ena == count.run);

	pr_debug("  %s: ena %" PRIu64", run %" PRIu64"\n",
		 !err ? "OK    " : "FAILED",
		 count.ena, count.run);

out_err:
	evlist__delete(evlist);
	वापस !err ? TEST_OK : TEST_FAIL;
पूर्ण

/*
 * This test creates software event 'cpu-clock'
 * attaches it in several ways (explained below)
 * and checks that enabled and running बार
 * match.
 */
पूर्णांक test__event_बार(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक err, ret = 0;

#घोषणा _T(attach, detach)			\
	err = test_बार(attach, detach);	\
	अगर (err && (ret == TEST_OK || ret == TEST_SKIP))	\
		ret = err;

	/* attach on newly spawned process after exec */
	_T(attach__enable_on_exec,   detach__enable_on_exec)
	/* attach on current process as enabled */
	_T(attach__current_enabled,  detach__disable)
	/* attach on current process as disabled */
	_T(attach__current_disabled, detach__disable)
	/* attach on cpu as disabled */
	_T(attach__cpu_disabled,     detach__disable)
	/* attach on cpu as enabled */
	_T(attach__cpu_enabled,      detach__disable)

#अघोषित _T
	वापस ret;
पूर्ण
