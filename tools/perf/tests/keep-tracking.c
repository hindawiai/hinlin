<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <सीमा.स>
#समावेश <unistd.h>
#समावेश <sys/prctl.h>
#समावेश <perf/cpumap.h>
#समावेश <perf/evlist.h>
#समावेश <perf/mmap.h>

#समावेश "debug.h"
#समावेश "parse-events.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "record.h"
#समावेश "thread_map.h"
#समावेश "tests.h"
#समावेश "util/mmap.h"

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

अटल पूर्णांक find_comm(काष्ठा evlist *evlist, स्थिर अक्षर *comm)
अणु
	जोड़ perf_event *event;
	काष्ठा mmap *md;
	पूर्णांक i, found;

	found = 0;
	क्रम (i = 0; i < evlist->core.nr_mmaps; i++) अणु
		md = &evlist->mmap[i];
		अगर (perf_mmap__पढ़ो_init(&md->core) < 0)
			जारी;
		जबतक ((event = perf_mmap__पढ़ो_event(&md->core)) != शून्य) अणु
			अगर (event->header.type == PERF_RECORD_COMM &&
			    (pid_t)event->comm.pid == getpid() &&
			    (pid_t)event->comm.tid == getpid() &&
			    म_भेद(event->comm.comm, comm) == 0)
				found += 1;
			perf_mmap__consume(&md->core);
		पूर्ण
		perf_mmap__पढ़ो_करोne(&md->core);
	पूर्ण
	वापस found;
पूर्ण

/**
 * test__keep_tracking - test using a dummy software event to keep tracking.
 *
 * This function implements a test that checks that tracking events जारी
 * when an event is disabled but a dummy software event is not disabled.  If the
 * test passes %0 is वापसed, otherwise %-1 is वापसed.
 */
पूर्णांक test__keep_tracking(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा record_opts opts = अणु
		.mmap_pages	     = अच_पूर्णांक_उच्च,
		.user_freq	     = अच_पूर्णांक_उच्च,
		.user_पूर्णांकerval	     = ULदीर्घ_उच्च,
		.target		     = अणु
			.uses_mmap   = true,
		पूर्ण,
	पूर्ण;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs = शून्य;
	काष्ठा perf_cpu_map *cpus = शून्य;
	काष्ठा evlist *evlist = शून्य;
	काष्ठा evsel *evsel = शून्य;
	पूर्णांक found, err = -1;
	स्थिर अक्षर *comm;

	thपढ़ोs = thपढ़ो_map__new(-1, getpid(), अच_पूर्णांक_उच्च);
	CHECK_NOT_शून्य__(thपढ़ोs);

	cpus = perf_cpu_map__new(शून्य);
	CHECK_NOT_शून्य__(cpus);

	evlist = evlist__new();
	CHECK_NOT_शून्य__(evlist);

	perf_evlist__set_maps(&evlist->core, cpus, thपढ़ोs);

	CHECK__(parse_events(evlist, "dummy:u", शून्य));
	CHECK__(parse_events(evlist, "cycles:u", शून्य));

	evlist__config(evlist, &opts, शून्य);

	evsel = evlist__first(evlist);

	evsel->core.attr.comm = 1;
	evsel->core.attr.disabled = 1;
	evsel->core.attr.enable_on_exec = 0;

	अगर (evlist__खोलो(evlist) < 0) अणु
		pr_debug("Unable to open dummy and cycles event\n");
		err = TEST_SKIP;
		जाओ out_err;
	पूर्ण

	CHECK__(evlist__mmap(evlist, अच_पूर्णांक_उच्च));

	/*
	 * First, test that a 'comm' event can be found when the event is
	 * enabled.
	 */

	evlist__enable(evlist);

	comm = "Test COMM 1";
	CHECK__(prctl(PR_SET_NAME, (अचिन्हित दीर्घ)comm, 0, 0, 0));

	evlist__disable(evlist);

	found = find_comm(evlist, comm);
	अगर (found != 1) अणु
		pr_debug("First time, failed to find tracking event.\n");
		जाओ out_err;
	पूर्ण

	/*
	 * Secondly, test that a 'comm' event can be found when the event is
	 * disabled with the dummy event still enabled.
	 */

	evlist__enable(evlist);

	evsel = evlist__last(evlist);

	CHECK__(evsel__disable(evsel));

	comm = "Test COMM 2";
	CHECK__(prctl(PR_SET_NAME, (अचिन्हित दीर्घ)comm, 0, 0, 0));

	evlist__disable(evlist);

	found = find_comm(evlist, comm);
	अगर (found != 1) अणु
		pr_debug("Second time, failed to find tracking event.\n");
		जाओ out_err;
	पूर्ण

	err = 0;

out_err:
	अगर (evlist) अणु
		evlist__disable(evlist);
		evlist__delete(evlist);
	पूर्ण
	perf_cpu_map__put(cpus);
	perf_thपढ़ो_map__put(thपढ़ोs);

	वापस err;
पूर्ण
