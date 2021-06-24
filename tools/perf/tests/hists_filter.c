<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "util/debug.h"
#समावेश "util/map.h"
#समावेश "util/symbol.h"
#समावेश "util/sort.h"
#समावेश "util/evsel.h"
#समावेश "util/event.h"
#समावेश "util/evlist.h"
#समावेश "util/machine.h"
#समावेश "util/parse-events.h"
#समावेश "tests/tests.h"
#समावेश "tests/hists_common.h"
#समावेश <linux/kernel.h>

काष्ठा sample अणु
	u32 pid;
	u64 ip;
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा map *map;
	काष्ठा symbol *sym;
	पूर्णांक socket;
पूर्ण;

/* For the numbers, see hists_common.c */
अटल काष्ठा sample fake_samples[] = अणु
	/* perf [kernel] schedule() */
	अणु .pid = FAKE_PID_PERF1, .ip = FAKE_IP_KERNEL_SCHEDULE, .socket = 0 पूर्ण,
	/* perf [perf]   मुख्य() */
	अणु .pid = FAKE_PID_PERF1, .ip = FAKE_IP_PERF_MAIN, .socket = 0 पूर्ण,
	/* perf [libc]   दो_स्मृति() */
	अणु .pid = FAKE_PID_PERF1, .ip = FAKE_IP_LIBC_MALLOC, .socket = 0 पूर्ण,
	/* perf [perf]   मुख्य() */
	अणु .pid = FAKE_PID_PERF2, .ip = FAKE_IP_PERF_MAIN, .socket = 0 पूर्ण, /* will be merged */
	/* perf [perf]   cmd_record() */
	अणु .pid = FAKE_PID_PERF2, .ip = FAKE_IP_PERF_CMD_RECORD, .socket = 1 पूर्ण,
	/* perf [kernel] page_fault() */
	अणु .pid = FAKE_PID_PERF2, .ip = FAKE_IP_KERNEL_PAGE_FAULT, .socket = 1 पूर्ण,
	/* bash [bash]   मुख्य() */
	अणु .pid = FAKE_PID_BASH,  .ip = FAKE_IP_BASH_MAIN, .socket = 2 पूर्ण,
	/* bash [bash]   xदो_स्मृति() */
	अणु .pid = FAKE_PID_BASH,  .ip = FAKE_IP_BASH_XMALLOC, .socket = 2 पूर्ण,
	/* bash [libc]   दो_स्मृति() */
	अणु .pid = FAKE_PID_BASH,  .ip = FAKE_IP_LIBC_MALLOC, .socket = 3 पूर्ण,
	/* bash [kernel] page_fault() */
	अणु .pid = FAKE_PID_BASH,  .ip = FAKE_IP_KERNEL_PAGE_FAULT, .socket = 3 पूर्ण,
पूर्ण;

अटल पूर्णांक add_hist_entries(काष्ठा evlist *evlist,
			    काष्ठा machine *machine)
अणु
	काष्ठा evsel *evsel;
	काष्ठा addr_location al;
	काष्ठा perf_sample sample = अणु .period = 100, पूर्ण;
	माप_प्रकार i;

	/*
	 * each evsel will have 10 samples but the 4th sample
	 * (perf [perf] मुख्य) will be collapsed to an existing entry
	 * so total 9 entries will be in the tree.
	 */
	evlist__क्रम_each_entry(evlist, evsel) अणु
		क्रम (i = 0; i < ARRAY_SIZE(fake_samples); i++) अणु
			काष्ठा hist_entry_iter iter = अणु
				.evsel = evsel,
				.sample = &sample,
				.ops = &hist_iter_normal,
				.hide_unresolved = false,
			पूर्ण;
			काष्ठा hists *hists = evsel__hists(evsel);

			/* make sure it has no filter at first */
			hists->thपढ़ो_filter = शून्य;
			hists->dso_filter = शून्य;
			hists->symbol_filter_str = शून्य;

			sample.cpumode = PERF_RECORD_MISC_USER;
			sample.pid = fake_samples[i].pid;
			sample.tid = fake_samples[i].pid;
			sample.ip = fake_samples[i].ip;

			अगर (machine__resolve(machine, &al, &sample) < 0)
				जाओ out;

			al.socket = fake_samples[i].socket;
			अगर (hist_entry_iter__add(&iter, &al,
						 sysctl_perf_event_max_stack, शून्य) < 0) अणु
				addr_location__put(&al);
				जाओ out;
			पूर्ण

			fake_samples[i].thपढ़ो = al.thपढ़ो;
			fake_samples[i].map = al.map;
			fake_samples[i].sym = al.sym;
		पूर्ण
	पूर्ण

	वापस 0;

out:
	pr_debug("Not enough memory for adding a hist entry\n");
	वापस TEST_FAIL;
पूर्ण

पूर्णांक test__hists_filter(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक err = TEST_FAIL;
	काष्ठा machines machines;
	काष्ठा machine *machine;
	काष्ठा evsel *evsel;
	काष्ठा evlist *evlist = evlist__new();

	TEST_ASSERT_VAL("No memory", evlist);

	err = parse_events(evlist, "cpu-clock", शून्य);
	अगर (err)
		जाओ out;
	err = parse_events(evlist, "task-clock", शून्य);
	अगर (err)
		जाओ out;
	err = TEST_FAIL;

	/* शेष sort order (comm,dso,sym) will be used */
	अगर (setup_sorting(शून्य) < 0)
		जाओ out;

	machines__init(&machines);

	/* setup thपढ़ोs/dso/map/symbols also */
	machine = setup_fake_machine(&machines);
	अगर (!machine)
		जाओ out;

	अगर (verbose > 1)
		machine__ख_लिखो(machine, मानक_त्रुटि);

	/* process sample events */
	err = add_hist_entries(evlist, machine);
	अगर (err < 0)
		जाओ out;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		काष्ठा hists *hists = evsel__hists(evsel);

		hists__collapse_resort(hists, शून्य);
		evsel__output_resort(evsel, शून्य);

		अगर (verbose > 2) अणु
			pr_info("Normal histogram\n");
			prपूर्णांक_hists_out(hists);
		पूर्ण

		TEST_ASSERT_VAL("Invalid nr samples",
				hists->stats.nr_samples == 10);
		TEST_ASSERT_VAL("Invalid nr hist entries",
				hists->nr_entries == 9);
		TEST_ASSERT_VAL("Invalid total period",
				hists->stats.total_period == 1000);
		TEST_ASSERT_VAL("Unmatched nr samples",
				hists->stats.nr_samples ==
				hists->stats.nr_non_filtered_samples);
		TEST_ASSERT_VAL("Unmatched nr hist entries",
				hists->nr_entries == hists->nr_non_filtered_entries);
		TEST_ASSERT_VAL("Unmatched total period",
				hists->stats.total_period ==
				hists->stats.total_non_filtered_period);

		/* now applying thपढ़ो filter क्रम 'bash' */
		hists->thपढ़ो_filter = fake_samples[9].thपढ़ो;
		hists__filter_by_thपढ़ो(hists);

		अगर (verbose > 2) अणु
			pr_info("Histogram for thread filter\n");
			prपूर्णांक_hists_out(hists);
		पूर्ण

		/* normal stats should be invariant */
		TEST_ASSERT_VAL("Invalid nr samples",
				hists->stats.nr_samples == 10);
		TEST_ASSERT_VAL("Invalid nr hist entries",
				hists->nr_entries == 9);
		TEST_ASSERT_VAL("Invalid total period",
				hists->stats.total_period == 1000);

		/* but filter stats are changed */
		TEST_ASSERT_VAL("Unmatched nr samples for thread filter",
				hists->stats.nr_non_filtered_samples == 4);
		TEST_ASSERT_VAL("Unmatched nr hist entries for thread filter",
				hists->nr_non_filtered_entries == 4);
		TEST_ASSERT_VAL("Unmatched total period for thread filter",
				hists->stats.total_non_filtered_period == 400);

		/* हटाओ thपढ़ो filter first */
		hists->thपढ़ो_filter = शून्य;
		hists__filter_by_thपढ़ो(hists);

		/* now applying dso filter क्रम 'kernel' */
		hists->dso_filter = fake_samples[0].map->dso;
		hists__filter_by_dso(hists);

		अगर (verbose > 2) अणु
			pr_info("Histogram for dso filter\n");
			prपूर्णांक_hists_out(hists);
		पूर्ण

		/* normal stats should be invariant */
		TEST_ASSERT_VAL("Invalid nr samples",
				hists->stats.nr_samples == 10);
		TEST_ASSERT_VAL("Invalid nr hist entries",
				hists->nr_entries == 9);
		TEST_ASSERT_VAL("Invalid total period",
				hists->stats.total_period == 1000);

		/* but filter stats are changed */
		TEST_ASSERT_VAL("Unmatched nr samples for dso filter",
				hists->stats.nr_non_filtered_samples == 3);
		TEST_ASSERT_VAL("Unmatched nr hist entries for dso filter",
				hists->nr_non_filtered_entries == 3);
		TEST_ASSERT_VAL("Unmatched total period for dso filter",
				hists->stats.total_non_filtered_period == 300);

		/* हटाओ dso filter first */
		hists->dso_filter = शून्य;
		hists__filter_by_dso(hists);

		/*
		 * now applying symbol filter क्रम 'main'.  Also note that
		 * there's 3 samples that have 'main' symbol but the 4th
		 * entry of fake_samples was collapsed alपढ़ोy so it won't
		 * be counted as a separate entry but the sample count and
		 * total period will be reमुख्यed.
		 */
		hists->symbol_filter_str = "main";
		hists__filter_by_symbol(hists);

		अगर (verbose > 2) अणु
			pr_info("Histogram for symbol filter\n");
			prपूर्णांक_hists_out(hists);
		पूर्ण

		/* normal stats should be invariant */
		TEST_ASSERT_VAL("Invalid nr samples",
				hists->stats.nr_samples == 10);
		TEST_ASSERT_VAL("Invalid nr hist entries",
				hists->nr_entries == 9);
		TEST_ASSERT_VAL("Invalid total period",
				hists->stats.total_period == 1000);

		/* but filter stats are changed */
		TEST_ASSERT_VAL("Unmatched nr samples for symbol filter",
				hists->stats.nr_non_filtered_samples == 3);
		TEST_ASSERT_VAL("Unmatched nr hist entries for symbol filter",
				hists->nr_non_filtered_entries == 2);
		TEST_ASSERT_VAL("Unmatched total period for symbol filter",
				hists->stats.total_non_filtered_period == 300);

		/* हटाओ symbol filter first */
		hists->symbol_filter_str = शून्य;
		hists__filter_by_symbol(hists);

		/* now applying socket filters */
		hists->socket_filter = 2;
		hists__filter_by_socket(hists);

		अगर (verbose > 2) अणु
			pr_info("Histogram for socket filters\n");
			prपूर्णांक_hists_out(hists);
		पूर्ण

		/* normal stats should be invariant */
		TEST_ASSERT_VAL("Invalid nr samples",
				hists->stats.nr_samples == 10);
		TEST_ASSERT_VAL("Invalid nr hist entries",
				hists->nr_entries == 9);
		TEST_ASSERT_VAL("Invalid total period",
				hists->stats.total_period == 1000);

		/* but filter stats are changed */
		TEST_ASSERT_VAL("Unmatched nr samples for socket filter",
				hists->stats.nr_non_filtered_samples == 2);
		TEST_ASSERT_VAL("Unmatched nr hist entries for socket filter",
				hists->nr_non_filtered_entries == 2);
		TEST_ASSERT_VAL("Unmatched total period for socket filter",
				hists->stats.total_non_filtered_period == 200);

		/* हटाओ socket filter first */
		hists->socket_filter = -1;
		hists__filter_by_socket(hists);

		/* now applying all filters at once. */
		hists->thपढ़ो_filter = fake_samples[1].thपढ़ो;
		hists->dso_filter = fake_samples[1].map->dso;
		hists__filter_by_thपढ़ो(hists);
		hists__filter_by_dso(hists);

		अगर (verbose > 2) अणु
			pr_info("Histogram for all filters\n");
			prपूर्णांक_hists_out(hists);
		पूर्ण

		/* normal stats should be invariant */
		TEST_ASSERT_VAL("Invalid nr samples",
				hists->stats.nr_samples == 10);
		TEST_ASSERT_VAL("Invalid nr hist entries",
				hists->nr_entries == 9);
		TEST_ASSERT_VAL("Invalid total period",
				hists->stats.total_period == 1000);

		/* but filter stats are changed */
		TEST_ASSERT_VAL("Unmatched nr samples for all filter",
				hists->stats.nr_non_filtered_samples == 2);
		TEST_ASSERT_VAL("Unmatched nr hist entries for all filter",
				hists->nr_non_filtered_entries == 1);
		TEST_ASSERT_VAL("Unmatched total period for all filter",
				hists->stats.total_non_filtered_period == 200);
	पूर्ण


	err = TEST_OK;

out:
	/* tear करोwn everything */
	evlist__delete(evlist);
	reset_output_field();
	machines__निकास(&machines);

	वापस err;
पूर्ण
