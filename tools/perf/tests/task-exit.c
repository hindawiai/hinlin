<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "debug.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "target.h"
#समावेश "thread_map.h"
#समावेश "tests.h"
#समावेश "util/mmap.h"

#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <linux/माला.स>
#समावेश <perf/cpumap.h>
#समावेश <perf/evlist.h>
#समावेश <perf/mmap.h>

अटल पूर्णांक निकासed;
अटल पूर्णांक nr_निकास;

अटल व्योम sig_handler(पूर्णांक sig __maybe_unused)
अणु
	निकासed = 1;
पूर्ण

/*
 * evlist__prepare_workload will send a SIGUSR1 अगर the विभाजन fails, since
 * we asked by setting its exec_error to this handler.
 */
अटल व्योम workload_exec_failed_संकेत(पूर्णांक signo __maybe_unused,
					siginfo_t *info __maybe_unused,
					व्योम *ucontext __maybe_unused)
अणु
	निकासed	= 1;
	nr_निकास = -1;
पूर्ण

/*
 * This test will start a workload that करोes nothing then it checks
 * अगर the number of निकास event reported by the kernel is 1 or not
 * in order to check the kernel वापसs correct number of event.
 */
पूर्णांक test__task_निकास(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक err = -1;
	जोड़ perf_event *event;
	काष्ठा evsel *evsel;
	काष्ठा evlist *evlist;
	काष्ठा target target = अणु
		.uid		= अच_पूर्णांक_उच्च,
		.uses_mmap	= true,
	पूर्ण;
	स्थिर अक्षर *argv[] = अणु "true", शून्य पूर्ण;
	अक्षर sbuf[STRERR_बफ_मानE];
	काष्ठा perf_cpu_map *cpus;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
	काष्ठा mmap *md;
	पूर्णांक retry_count = 0;

	संकेत(SIGCHLD, sig_handler);

	evlist = evlist__new_शेष();
	अगर (evlist == शून्य) अणु
		pr_debug("evlist__new_default\n");
		वापस -1;
	पूर्ण

	/*
	 * Create maps of thपढ़ोs and cpus to monitor. In this हाल
	 * we start with all thपढ़ोs and cpus (-1, -1) but then in
	 * evlist__prepare_workload we'll fill in the only thपढ़ो
	 * we're monitoring, the one विभाजनed there.
	 */
	cpus = perf_cpu_map__dummy_new();
	thपढ़ोs = thपढ़ो_map__new_by_tid(-1);
	अगर (!cpus || !thपढ़ोs) अणु
		err = -ENOMEM;
		pr_debug("Not enough memory to create thread/cpu maps\n");
		जाओ out_delete_evlist;
	पूर्ण

	perf_evlist__set_maps(&evlist->core, cpus, thपढ़ोs);

	err = evlist__prepare_workload(evlist, &target, argv, false, workload_exec_failed_संकेत);
	अगर (err < 0) अणु
		pr_debug("Couldn't run the workload!\n");
		जाओ out_delete_evlist;
	पूर्ण

	evsel = evlist__first(evlist);
	evsel->core.attr.task = 1;
#अगर_घोषित __s390x__
	evsel->core.attr.sample_freq = 1000000;
#अन्यथा
	evsel->core.attr.sample_freq = 1;
#पूर्ण_अगर
	evsel->core.attr.inherit = 0;
	evsel->core.attr.watermark = 0;
	evsel->core.attr.wakeup_events = 1;
	evsel->core.attr.exclude_kernel = 1;

	err = evlist__खोलो(evlist);
	अगर (err < 0) अणु
		pr_debug("Couldn't open the evlist: %s\n",
			 str_error_r(-err, sbuf, माप(sbuf)));
		जाओ out_delete_evlist;
	पूर्ण

	अगर (evlist__mmap(evlist, 128) < 0) अणु
		pr_debug("failed to mmap events: %d (%s)\n", त्रुटि_सं,
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		err = -1;
		जाओ out_delete_evlist;
	पूर्ण

	evlist__start_workload(evlist);

retry:
	md = &evlist->mmap[0];
	अगर (perf_mmap__पढ़ो_init(&md->core) < 0)
		जाओ out_init;

	जबतक ((event = perf_mmap__पढ़ो_event(&md->core)) != शून्य) अणु
		अगर (event->header.type == PERF_RECORD_EXIT)
			nr_निकास++;

		perf_mmap__consume(&md->core);
	पूर्ण
	perf_mmap__पढ़ो_करोne(&md->core);

out_init:
	अगर (!निकासed || !nr_निकास) अणु
		evlist__poll(evlist, -1);

		अगर (retry_count++ > 1000) अणु
			pr_debug("Failed after retrying 1000 times\n");
			err = -1;
			जाओ out_delete_evlist;
		पूर्ण

		जाओ retry;
	पूर्ण

	अगर (nr_निकास != 1) अणु
		pr_debug("received %d EXIT records\n", nr_निकास);
		err = -1;
	पूर्ण

out_delete_evlist:
	perf_cpu_map__put(cpus);
	perf_thपढ़ो_map__put(thपढ़ोs);
	evlist__delete(evlist);
	वापस err;
पूर्ण
