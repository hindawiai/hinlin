<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <sys/समय.स>
#समावेश <sys/prctl.h>
#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>
#समावेश <समय.स>
#समावेश <मानककोष.स>
#समावेश <linux/zभाग.स>
#समावेश <perf/cpumap.h>
#समावेश <perf/evlist.h>
#समावेश <perf/mmap.h>

#समावेश "debug.h"
#समावेश "parse-events.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "thread_map.h"
#समावेश "record.h"
#समावेश "tests.h"
#समावेश "util/mmap.h"
#समावेश "pmu.h"

अटल पूर्णांक spin_sleep(व्योम)
अणु
	काष्ठा समयval start, now, dअगरf, maxसमय;
	काष्ठा बारpec ts;
	पूर्णांक err, i;

	maxसमय.tv_sec = 0;
	maxसमय.tv_usec = 50000;

	err = समय_लोofday(&start, शून्य);
	अगर (err)
		वापस err;

	/* Spin क्रम 50ms */
	जबतक (1) अणु
		क्रम (i = 0; i < 1000; i++)
			barrier();

		err = समय_लोofday(&now, शून्य);
		अगर (err)
			वापस err;

		समयrsub(&now, &start, &dअगरf);
		अगर (समयrcmp(&dअगरf, &maxसमय, > /* For checkpatch */))
			अवरोध;
	पूर्ण

	ts.tv_nsec = 50 * 1000 * 1000;
	ts.tv_sec = 0;

	/* Sleep क्रम 50ms */
	err = nanosleep(&ts, शून्य);
	अगर (err == EINTR)
		err = 0;

	वापस err;
पूर्ण

काष्ठा चयन_tracking अणु
	काष्ठा evsel *चयन_evsel;
	काष्ठा evsel *cycles_evsel;
	pid_t *tids;
	पूर्णांक nr_tids;
	पूर्णांक comm_seen[4];
	पूर्णांक cycles_beक्रमe_comm_1;
	पूर्णांक cycles_between_comm_2_and_comm_3;
	पूर्णांक cycles_after_comm_4;
पूर्ण;

अटल पूर्णांक check_comm(काष्ठा चयन_tracking *चयन_tracking,
		      जोड़ perf_event *event, स्थिर अक्षर *comm, पूर्णांक nr)
अणु
	अगर (event->header.type == PERF_RECORD_COMM &&
	    (pid_t)event->comm.pid == getpid() &&
	    (pid_t)event->comm.tid == getpid() &&
	    म_भेद(event->comm.comm, comm) == 0) अणु
		अगर (चयन_tracking->comm_seen[nr]) अणु
			pr_debug("Duplicate comm event\n");
			वापस -1;
		पूर्ण
		चयन_tracking->comm_seen[nr] = 1;
		pr_debug3("comm event: %s nr: %d\n", event->comm.comm, nr);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_cpu(काष्ठा चयन_tracking *चयन_tracking, पूर्णांक cpu)
अणु
	पूर्णांक i, nr = cpu + 1;

	अगर (cpu < 0)
		वापस -1;

	अगर (!चयन_tracking->tids) अणु
		चयन_tracking->tids = सुस्मृति(nr, माप(pid_t));
		अगर (!चयन_tracking->tids)
			वापस -1;
		क्रम (i = 0; i < nr; i++)
			चयन_tracking->tids[i] = -1;
		चयन_tracking->nr_tids = nr;
		वापस 0;
	पूर्ण

	अगर (cpu >= चयन_tracking->nr_tids) अणु
		व्योम *addr;

		addr = पुनः_स्मृति(चयन_tracking->tids, nr * माप(pid_t));
		अगर (!addr)
			वापस -1;
		चयन_tracking->tids = addr;
		क्रम (i = चयन_tracking->nr_tids; i < nr; i++)
			चयन_tracking->tids[i] = -1;
		चयन_tracking->nr_tids = nr;
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_sample_event(काष्ठा evlist *evlist,
				जोड़ perf_event *event,
				काष्ठा चयन_tracking *चयन_tracking)
अणु
	काष्ठा perf_sample sample;
	काष्ठा evsel *evsel;
	pid_t next_tid, prev_tid;
	पूर्णांक cpu, err;

	अगर (evlist__parse_sample(evlist, event, &sample)) अणु
		pr_debug("evlist__parse_sample failed\n");
		वापस -1;
	पूर्ण

	evsel = evlist__id2evsel(evlist, sample.id);
	अगर (evsel == चयन_tracking->चयन_evsel) अणु
		next_tid = evsel__पूर्णांकval(evsel, &sample, "next_pid");
		prev_tid = evsel__पूर्णांकval(evsel, &sample, "prev_pid");
		cpu = sample.cpu;
		pr_debug3("sched_switch: cpu: %d prev_tid %d next_tid %d\n",
			  cpu, prev_tid, next_tid);
		err = check_cpu(चयन_tracking, cpu);
		अगर (err)
			वापस err;
		/*
		 * Check क्रम no missing sched_चयन events i.e. that the
		 * evsel->core.प्रणाली_wide flag has worked.
		 */
		अगर (चयन_tracking->tids[cpu] != -1 &&
		    चयन_tracking->tids[cpu] != prev_tid) अणु
			pr_debug("Missing sched_switch events\n");
			वापस -1;
		पूर्ण
		चयन_tracking->tids[cpu] = next_tid;
	पूर्ण

	अगर (evsel == चयन_tracking->cycles_evsel) अणु
		pr_debug3("cycles event\n");
		अगर (!चयन_tracking->comm_seen[0])
			चयन_tracking->cycles_beक्रमe_comm_1 = 1;
		अगर (चयन_tracking->comm_seen[1] &&
		    !चयन_tracking->comm_seen[2])
			चयन_tracking->cycles_between_comm_2_and_comm_3 = 1;
		अगर (चयन_tracking->comm_seen[3])
			चयन_tracking->cycles_after_comm_4 = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_event(काष्ठा evlist *evlist, जोड़ perf_event *event,
			 काष्ठा चयन_tracking *चयन_tracking)
अणु
	अगर (event->header.type == PERF_RECORD_SAMPLE)
		वापस process_sample_event(evlist, event, चयन_tracking);

	अगर (event->header.type == PERF_RECORD_COMM) अणु
		पूर्णांक err, करोne = 0;

		err = check_comm(चयन_tracking, event, "Test COMM 1", 0);
		अगर (err < 0)
			वापस -1;
		करोne += err;
		err = check_comm(चयन_tracking, event, "Test COMM 2", 1);
		अगर (err < 0)
			वापस -1;
		करोne += err;
		err = check_comm(चयन_tracking, event, "Test COMM 3", 2);
		अगर (err < 0)
			वापस -1;
		करोne += err;
		err = check_comm(चयन_tracking, event, "Test COMM 4", 3);
		अगर (err < 0)
			वापस -1;
		करोne += err;
		अगर (करोne != 1) अणु
			pr_debug("Unexpected comm event\n");
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा event_node अणु
	काष्ठा list_head list;
	जोड़ perf_event *event;
	u64 event_समय;
पूर्ण;

अटल पूर्णांक add_event(काष्ठा evlist *evlist, काष्ठा list_head *events,
		     जोड़ perf_event *event)
अणु
	काष्ठा perf_sample sample;
	काष्ठा event_node *node;

	node = दो_स्मृति(माप(काष्ठा event_node));
	अगर (!node) अणु
		pr_debug("malloc failed\n");
		वापस -1;
	पूर्ण
	node->event = event;
	list_add(&node->list, events);

	अगर (evlist__parse_sample(evlist, event, &sample)) अणु
		pr_debug("evlist__parse_sample failed\n");
		वापस -1;
	पूर्ण

	अगर (!sample.समय) अणु
		pr_debug("event with no time\n");
		वापस -1;
	पूर्ण

	node->event_समय = sample.समय;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_event_nodes(काष्ठा list_head *events)
अणु
	काष्ठा event_node *node;

	जबतक (!list_empty(events)) अणु
		node = list_entry(events->next, काष्ठा event_node, list);
		list_del_init(&node->list);
		मुक्त(node);
	पूर्ण
पूर्ण

अटल पूर्णांक compar(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा event_node *nodea = a;
	स्थिर काष्ठा event_node *nodeb = b;
	s64 cmp = nodea->event_समय - nodeb->event_समय;

	वापस cmp;
पूर्ण

अटल पूर्णांक process_events(काष्ठा evlist *evlist,
			  काष्ठा चयन_tracking *चयन_tracking)
अणु
	जोड़ perf_event *event;
	अचिन्हित pos, cnt = 0;
	LIST_HEAD(events);
	काष्ठा event_node *events_array, *node;
	काष्ठा mmap *md;
	पूर्णांक i, ret;

	क्रम (i = 0; i < evlist->core.nr_mmaps; i++) अणु
		md = &evlist->mmap[i];
		अगर (perf_mmap__पढ़ो_init(&md->core) < 0)
			जारी;

		जबतक ((event = perf_mmap__पढ़ो_event(&md->core)) != शून्य) अणु
			cnt += 1;
			ret = add_event(evlist, &events, event);
			 perf_mmap__consume(&md->core);
			अगर (ret < 0)
				जाओ out_मुक्त_nodes;
		पूर्ण
		perf_mmap__पढ़ो_करोne(&md->core);
	पूर्ण

	events_array = सुस्मृति(cnt, माप(काष्ठा event_node));
	अगर (!events_array) अणु
		pr_debug("calloc failed\n");
		ret = -1;
		जाओ out_मुक्त_nodes;
	पूर्ण

	pos = 0;
	list_क्रम_each_entry(node, &events, list)
		events_array[pos++] = *node;

	क्विक(events_array, cnt, माप(काष्ठा event_node), compar);

	क्रम (pos = 0; pos < cnt; pos++) अणु
		ret = process_event(evlist, events_array[pos].event,
				    चयन_tracking);
		अगर (ret < 0)
			जाओ out_मुक्त;
	पूर्ण

	ret = 0;
out_मुक्त:
	pr_debug("%u events recorded\n", cnt);
	मुक्त(events_array);
out_मुक्त_nodes:
	मुक्त_event_nodes(&events);
	वापस ret;
पूर्ण

/**
 * test__चयन_tracking - test using sched_चयन and tracking events.
 *
 * This function implements a test that checks that sched_चयन events and
 * tracking events can be recorded क्रम a workload (current process) using the
 * evsel->core.प्रणाली_wide and evsel->tracking flags (respectively) with other events
 * someबार enabled or disabled.
 */
पूर्णांक test__चयन_tracking(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	स्थिर अक्षर *sched_चयन = "sched:sched_switch";
	काष्ठा चयन_tracking चयन_tracking = अणु .tids = शून्य, पूर्ण;
	काष्ठा record_opts opts = अणु
		.mmap_pages	     = अच_पूर्णांक_उच्च,
		.user_freq	     = अच_पूर्णांक_उच्च,
		.user_पूर्णांकerval	     = ULदीर्घ_उच्च,
		.freq		     = 4000,
		.target		     = अणु
			.uses_mmap   = true,
		पूर्ण,
	पूर्ण;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs = शून्य;
	काष्ठा perf_cpu_map *cpus = शून्य;
	काष्ठा evlist *evlist = शून्य;
	काष्ठा evsel *evsel, *cpu_घड़ीs_evsel, *cycles_evsel;
	काष्ठा evsel *चयन_evsel, *tracking_evsel;
	स्थिर अक्षर *comm;
	पूर्णांक err = -1;

	thपढ़ोs = thपढ़ो_map__new(-1, getpid(), अच_पूर्णांक_उच्च);
	अगर (!thपढ़ोs) अणु
		pr_debug("thread_map__new failed!\n");
		जाओ out_err;
	पूर्ण

	cpus = perf_cpu_map__new(शून्य);
	अगर (!cpus) अणु
		pr_debug("perf_cpu_map__new failed!\n");
		जाओ out_err;
	पूर्ण

	evlist = evlist__new();
	अगर (!evlist) अणु
		pr_debug("evlist__new failed!\n");
		जाओ out_err;
	पूर्ण

	perf_evlist__set_maps(&evlist->core, cpus, thपढ़ोs);

	/* First event */
	err = parse_events(evlist, "cpu-clock:u", शून्य);
	अगर (err) अणु
		pr_debug("Failed to parse event dummy:u\n");
		जाओ out_err;
	पूर्ण

	cpu_घड़ीs_evsel = evlist__last(evlist);

	/* Second event */
	अगर (perf_pmu__has_hybrid())
		err = parse_events(evlist, "cpu_core/cycles/u", शून्य);
	अन्यथा
		err = parse_events(evlist, "cycles:u", शून्य);
	अगर (err) अणु
		pr_debug("Failed to parse event cycles:u\n");
		जाओ out_err;
	पूर्ण

	cycles_evsel = evlist__last(evlist);

	/* Third event */
	अगर (!evlist__can_select_event(evlist, sched_चयन)) अणु
		pr_debug("No sched_switch\n");
		err = 0;
		जाओ out;
	पूर्ण

	err = parse_events(evlist, sched_चयन, शून्य);
	अगर (err) अणु
		pr_debug("Failed to parse event %s\n", sched_चयन);
		जाओ out_err;
	पूर्ण

	चयन_evsel = evlist__last(evlist);

	evsel__set_sample_bit(चयन_evsel, CPU);
	evsel__set_sample_bit(चयन_evsel, TIME);

	चयन_evsel->core.प्रणाली_wide = true;
	चयन_evsel->no_aux_samples = true;
	चयन_evsel->immediate = true;

	/* Test moving an event to the front */
	अगर (cycles_evsel == evlist__first(evlist)) अणु
		pr_debug("cycles event already at front");
		जाओ out_err;
	पूर्ण
	evlist__to_front(evlist, cycles_evsel);
	अगर (cycles_evsel != evlist__first(evlist)) अणु
		pr_debug("Failed to move cycles event to front");
		जाओ out_err;
	पूर्ण

	evsel__set_sample_bit(cycles_evsel, CPU);
	evsel__set_sample_bit(cycles_evsel, TIME);

	/* Fourth event */
	err = parse_events(evlist, "dummy:u", शून्य);
	अगर (err) अणु
		pr_debug("Failed to parse event dummy:u\n");
		जाओ out_err;
	पूर्ण

	tracking_evsel = evlist__last(evlist);

	evlist__set_tracking_event(evlist, tracking_evsel);

	tracking_evsel->core.attr.freq = 0;
	tracking_evsel->core.attr.sample_period = 1;

	evsel__set_sample_bit(tracking_evsel, TIME);

	/* Config events */
	evlist__config(evlist, &opts, शून्य);

	/* Check moved event is still at the front */
	अगर (cycles_evsel != evlist__first(evlist)) अणु
		pr_debug("Front event no longer at front");
		जाओ out_err;
	पूर्ण

	/* Check tracking event is tracking */
	अगर (!tracking_evsel->core.attr.mmap || !tracking_evsel->core.attr.comm) अणु
		pr_debug("Tracking event not tracking\n");
		जाओ out_err;
	पूर्ण

	/* Check non-tracking events are not tracking */
	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel != tracking_evsel) अणु
			अगर (evsel->core.attr.mmap || evsel->core.attr.comm) अणु
				pr_debug("Non-tracking event is tracking\n");
				जाओ out_err;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (evlist__खोलो(evlist) < 0) अणु
		pr_debug("Not supported\n");
		err = 0;
		जाओ out;
	पूर्ण

	err = evlist__mmap(evlist, अच_पूर्णांक_उच्च);
	अगर (err) अणु
		pr_debug("evlist__mmap failed!\n");
		जाओ out_err;
	पूर्ण

	evlist__enable(evlist);

	err = evsel__disable(cpu_घड़ीs_evsel);
	अगर (err) अणु
		pr_debug("perf_evlist__disable_event failed!\n");
		जाओ out_err;
	पूर्ण

	err = spin_sleep();
	अगर (err) अणु
		pr_debug("spin_sleep failed!\n");
		जाओ out_err;
	पूर्ण

	comm = "Test COMM 1";
	err = prctl(PR_SET_NAME, (अचिन्हित दीर्घ)comm, 0, 0, 0);
	अगर (err) अणु
		pr_debug("PR_SET_NAME failed!\n");
		जाओ out_err;
	पूर्ण

	err = evsel__disable(cycles_evsel);
	अगर (err) अणु
		pr_debug("perf_evlist__disable_event failed!\n");
		जाओ out_err;
	पूर्ण

	comm = "Test COMM 2";
	err = prctl(PR_SET_NAME, (अचिन्हित दीर्घ)comm, 0, 0, 0);
	अगर (err) अणु
		pr_debug("PR_SET_NAME failed!\n");
		जाओ out_err;
	पूर्ण

	err = spin_sleep();
	अगर (err) अणु
		pr_debug("spin_sleep failed!\n");
		जाओ out_err;
	पूर्ण

	comm = "Test COMM 3";
	err = prctl(PR_SET_NAME, (अचिन्हित दीर्घ)comm, 0, 0, 0);
	अगर (err) अणु
		pr_debug("PR_SET_NAME failed!\n");
		जाओ out_err;
	पूर्ण

	err = evsel__enable(cycles_evsel);
	अगर (err) अणु
		pr_debug("perf_evlist__disable_event failed!\n");
		जाओ out_err;
	पूर्ण

	comm = "Test COMM 4";
	err = prctl(PR_SET_NAME, (अचिन्हित दीर्घ)comm, 0, 0, 0);
	अगर (err) अणु
		pr_debug("PR_SET_NAME failed!\n");
		जाओ out_err;
	पूर्ण

	err = spin_sleep();
	अगर (err) अणु
		pr_debug("spin_sleep failed!\n");
		जाओ out_err;
	पूर्ण

	evlist__disable(evlist);

	चयन_tracking.चयन_evsel = चयन_evsel;
	चयन_tracking.cycles_evsel = cycles_evsel;

	err = process_events(evlist, &चयन_tracking);

	zमुक्त(&चयन_tracking.tids);

	अगर (err)
		जाओ out_err;

	/* Check all 4 comm events were seen i.e. that evsel->tracking works */
	अगर (!चयन_tracking.comm_seen[0] || !चयन_tracking.comm_seen[1] ||
	    !चयन_tracking.comm_seen[2] || !चयन_tracking.comm_seen[3]) अणु
		pr_debug("Missing comm events\n");
		जाओ out_err;
	पूर्ण

	/* Check cycles event got enabled */
	अगर (!चयन_tracking.cycles_beक्रमe_comm_1) अणु
		pr_debug("Missing cycles events\n");
		जाओ out_err;
	पूर्ण

	/* Check cycles event got disabled */
	अगर (चयन_tracking.cycles_between_comm_2_and_comm_3) अणु
		pr_debug("cycles events even though event was disabled\n");
		जाओ out_err;
	पूर्ण

	/* Check cycles event got enabled again */
	अगर (!चयन_tracking.cycles_after_comm_4) अणु
		pr_debug("Missing cycles events\n");
		जाओ out_err;
	पूर्ण
out:
	अगर (evlist) अणु
		evlist__disable(evlist);
		evlist__delete(evlist);
	पूर्ण
	perf_cpu_map__put(cpus);
	perf_thपढ़ो_map__put(thपढ़ोs);

	वापस err;

out_err:
	err = -1;
	जाओ out;
पूर्ण
