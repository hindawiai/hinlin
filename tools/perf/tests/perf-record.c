<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/माला.स>
/* For the CLR_() macros */
#समावेश <pthपढ़ो.h>

#समावेश <sched.h>
#समावेश <perf/mmap.h>
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "debug.h"
#समावेश "record.h"
#समावेश "tests.h"
#समावेश "util/mmap.h"

अटल पूर्णांक sched__get_first_possible_cpu(pid_t pid, cpu_set_t *maskp)
अणु
	पूर्णांक i, cpu = -1, nrcpus = 1024;
पुनः_स्मृति:
	CPU_ZERO(maskp);

	अगर (sched_getaffinity(pid, माप(*maskp), maskp) == -1) अणु
		अगर (त्रुटि_सं == EINVAL && nrcpus < (1024 << 8)) अणु
			nrcpus = nrcpus << 2;
			जाओ पुनः_स्मृति;
		पूर्ण
		लिखो_त्रुटि("sched_getaffinity");
			वापस -1;
	पूर्ण

	क्रम (i = 0; i < nrcpus; i++) अणु
		अगर (CPU_ISSET(i, maskp)) अणु
			अगर (cpu == -1)
				cpu = i;
			अन्यथा
				CPU_CLR(i, maskp);
		पूर्ण
	पूर्ण

	वापस cpu;
पूर्ण

पूर्णांक test__PERF_RECORD(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा record_opts opts = अणु
		.target = अणु
			.uid = अच_पूर्णांक_उच्च,
			.uses_mmap = true,
		पूर्ण,
		.no_buffering = true,
		.mmap_pages   = 256,
	पूर्ण;
	cpu_set_t cpu_mask;
	माप_प्रकार cpu_mask_size = माप(cpu_mask);
	काष्ठा evlist *evlist = evlist__new_dummy();
	काष्ठा evsel *evsel;
	काष्ठा perf_sample sample;
	स्थिर अक्षर *cmd = "sleep";
	स्थिर अक्षर *argv[] = अणु cmd, "1", शून्य, पूर्ण;
	अक्षर *bname, *mmap_filename;
	u64 prev_समय = 0;
	bool found_cmd_mmap = false,
	     found_coreutils_mmap = false,
	     found_libc_mmap = false,
	     found_vdso_mmap = false,
	     found_ld_mmap = false;
	पूर्णांक err = -1, errs = 0, i, wakeups = 0;
	u32 cpu;
	पूर्णांक total_events = 0, nr_events[PERF_RECORD_MAX] = अणु 0, पूर्ण;
	अक्षर sbuf[STRERR_बफ_मानE];

	अगर (evlist == शून्य) /* Fallback क्रम kernels lacking PERF_COUNT_SW_DUMMY */
		evlist = evlist__new_शेष();

	अगर (evlist == शून्य) अणु
		pr_debug("Not enough memory to create evlist\n");
		जाओ out;
	पूर्ण

	/*
	 * Create maps of thपढ़ोs and cpus to monitor. In this हाल
	 * we start with all thपढ़ोs and cpus (-1, -1) but then in
	 * evlist__prepare_workload we'll fill in the only thपढ़ो
	 * we're monitoring, the one विभाजनed there.
	 */
	err = evlist__create_maps(evlist, &opts.target);
	अगर (err < 0) अणु
		pr_debug("Not enough memory to create thread/cpu maps\n");
		जाओ out_delete_evlist;
	पूर्ण

	/*
	 * Prepare the workload in argv[] to run, it'll विभाजन it, and then रुको
	 * क्रम evlist__start_workload() to exec it. This is करोne this way
	 * so that we have समय to खोलो the evlist (calling sys_perf_event_खोलो
	 * on all the fds) and then mmap them.
	 */
	err = evlist__prepare_workload(evlist, &opts.target, argv, false, शून्य);
	अगर (err < 0) अणु
		pr_debug("Couldn't run the workload!\n");
		जाओ out_delete_evlist;
	पूर्ण

	/*
	 * Config the evsels, setting attr->comm on the first one, etc.
	 */
	evsel = evlist__first(evlist);
	evsel__set_sample_bit(evsel, CPU);
	evsel__set_sample_bit(evsel, TID);
	evsel__set_sample_bit(evsel, TIME);
	evlist__config(evlist, &opts, शून्य);

	err = sched__get_first_possible_cpu(evlist->workload.pid, &cpu_mask);
	अगर (err < 0) अणु
		pr_debug("sched__get_first_possible_cpu: %s\n",
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out_delete_evlist;
	पूर्ण

	cpu = err;

	/*
	 * So that we can check perf_sample.cpu on all the samples.
	 */
	अगर (sched_setaffinity(evlist->workload.pid, cpu_mask_size, &cpu_mask) < 0) अणु
		pr_debug("sched_setaffinity: %s\n",
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out_delete_evlist;
	पूर्ण

	/*
	 * Call sys_perf_event_खोलो on all the fds on all the evsels,
	 * grouping them अगर asked to.
	 */
	err = evlist__खोलो(evlist);
	अगर (err < 0) अणु
		pr_debug("perf_evlist__open: %s\n",
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out_delete_evlist;
	पूर्ण

	/*
	 * mmap the first fd on a given CPU and ask क्रम events क्रम the other
	 * fds in the same CPU to be injected in the same mmap ring buffer
	 * (using ioctl(PERF_EVENT_IOC_SET_OUTPUT)).
	 */
	err = evlist__mmap(evlist, opts.mmap_pages);
	अगर (err < 0) अणु
		pr_debug("evlist__mmap: %s\n",
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out_delete_evlist;
	पूर्ण

	/*
	 * Now that all is properly set up, enable the events, they will
	 * count just on workload.pid, which will start...
	 */
	evlist__enable(evlist);

	/*
	 * Now!
	 */
	evlist__start_workload(evlist);

	जबतक (1) अणु
		पूर्णांक beक्रमe = total_events;

		क्रम (i = 0; i < evlist->core.nr_mmaps; i++) अणु
			जोड़ perf_event *event;
			काष्ठा mmap *md;

			md = &evlist->mmap[i];
			अगर (perf_mmap__पढ़ो_init(&md->core) < 0)
				जारी;

			जबतक ((event = perf_mmap__पढ़ो_event(&md->core)) != शून्य) अणु
				स्थिर u32 type = event->header.type;
				स्थिर अक्षर *name = perf_event__name(type);

				++total_events;
				अगर (type < PERF_RECORD_MAX)
					nr_events[type]++;

				err = evlist__parse_sample(evlist, event, &sample);
				अगर (err < 0) अणु
					अगर (verbose > 0)
						perf_event__ख_लिखो(event, शून्य, मानक_त्रुटि);
					pr_debug("Couldn't parse sample\n");
					जाओ out_delete_evlist;
				पूर्ण

				अगर (verbose > 0) अणु
					pr_info("%" PRIu64" %d ", sample.समय, sample.cpu);
					perf_event__ख_लिखो(event, शून्य, मानक_त्रुटि);
				पूर्ण

				अगर (prev_समय > sample.समय) अणु
					pr_debug("%s going backwards in time, prev=%" PRIu64 ", curr=%" PRIu64 "\n",
						 name, prev_समय, sample.समय);
					++errs;
				पूर्ण

				prev_समय = sample.समय;

				अगर (sample.cpu != cpu) अणु
					pr_debug("%s with unexpected cpu, expected %d, got %d\n",
						 name, cpu, sample.cpu);
					++errs;
				पूर्ण

				अगर ((pid_t)sample.pid != evlist->workload.pid) अणु
					pr_debug("%s with unexpected pid, expected %d, got %d\n",
						 name, evlist->workload.pid, sample.pid);
					++errs;
				पूर्ण

				अगर ((pid_t)sample.tid != evlist->workload.pid) अणु
					pr_debug("%s with unexpected tid, expected %d, got %d\n",
						 name, evlist->workload.pid, sample.tid);
					++errs;
				पूर्ण

				अगर ((type == PERF_RECORD_COMM ||
				     type == PERF_RECORD_MMAP ||
				     type == PERF_RECORD_MMAP2 ||
				     type == PERF_RECORD_FORK ||
				     type == PERF_RECORD_EXIT) &&
				     (pid_t)event->comm.pid != evlist->workload.pid) अणु
					pr_debug("%s with unexpected pid/tid\n", name);
					++errs;
				पूर्ण

				अगर ((type == PERF_RECORD_COMM ||
				     type == PERF_RECORD_MMAP ||
				     type == PERF_RECORD_MMAP2) &&
				     event->comm.pid != event->comm.tid) अणु
					pr_debug("%s with different pid/tid!\n", name);
					++errs;
				पूर्ण

				चयन (type) अणु
				हाल PERF_RECORD_COMM:
					अगर (म_भेद(event->comm.comm, cmd)) अणु
						pr_debug("%s with unexpected comm!\n", name);
						++errs;
					पूर्ण
					अवरोध;
				हाल PERF_RECORD_EXIT:
					जाओ found_निकास;
				हाल PERF_RECORD_MMAP:
					mmap_filename = event->mmap.filename;
					जाओ check_bname;
				हाल PERF_RECORD_MMAP2:
					mmap_filename = event->mmap2.filename;
				check_bname:
					bname = म_खोजप(mmap_filename, '/');
					अगर (bname != शून्य) अणु
						अगर (!found_cmd_mmap)
							found_cmd_mmap = !म_भेद(bname + 1, cmd);
						अगर (!found_coreutils_mmap)
							found_coreutils_mmap = !म_भेद(bname + 1, "coreutils");
						अगर (!found_libc_mmap)
							found_libc_mmap = !म_भेदन(bname + 1, "libc", 4);
						अगर (!found_ld_mmap)
							found_ld_mmap = !म_भेदन(bname + 1, "ld", 2);
					पूर्ण अन्यथा अगर (!found_vdso_mmap)
						found_vdso_mmap = !म_भेद(mmap_filename, "[vdso]");
					अवरोध;

				हाल PERF_RECORD_SAMPLE:
					/* Just ignore samples क्रम now */
					अवरोध;
				शेष:
					pr_debug("Unexpected perf_event->header.type %d!\n",
						 type);
					++errs;
				पूर्ण

				perf_mmap__consume(&md->core);
			पूर्ण
			perf_mmap__पढ़ो_करोne(&md->core);
		पूर्ण

		/*
		 * We करोn't use poll here because at least at 3.1 बार the
		 * PERF_RECORD_अणु!SAMPLEपूर्ण events करोn't honour
		 * perf_event_attr.wakeup_events, just PERF_EVENT_SAMPLE करोes.
		 */
		अगर (total_events == beक्रमe && false)
			evlist__poll(evlist, -1);

		sleep(1);
		अगर (++wakeups > 5) अणु
			pr_debug("No PERF_RECORD_EXIT event!\n");
			अवरोध;
		पूर्ण
	पूर्ण

found_निकास:
	अगर (nr_events[PERF_RECORD_COMM] > 1 + !!found_coreutils_mmap) अणु
		pr_debug("Excessive number of PERF_RECORD_COMM events!\n");
		++errs;
	पूर्ण

	अगर (nr_events[PERF_RECORD_COMM] == 0) अणु
		pr_debug("Missing PERF_RECORD_COMM for %s!\n", cmd);
		++errs;
	पूर्ण

	अगर (!found_cmd_mmap && !found_coreutils_mmap) अणु
		pr_debug("PERF_RECORD_MMAP for %s missing!\n", cmd);
		++errs;
	पूर्ण

	अगर (!found_libc_mmap) अणु
		pr_debug("PERF_RECORD_MMAP for %s missing!\n", "libc");
		++errs;
	पूर्ण

	अगर (!found_ld_mmap) अणु
		pr_debug("PERF_RECORD_MMAP for %s missing!\n", "ld");
		++errs;
	पूर्ण

	अगर (!found_vdso_mmap) अणु
		pr_debug("PERF_RECORD_MMAP for %s missing!\n", "[vdso]");
		++errs;
	पूर्ण
out_delete_evlist:
	evlist__delete(evlist);
out:
	वापस (err < 0 || errs > 0) ? -1 : 0;
पूर्ण
