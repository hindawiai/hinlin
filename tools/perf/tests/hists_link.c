<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "tests.h"
#समावेश "debug.h"
#समावेश "symbol.h"
#समावेश "sort.h"
#समावेश "evsel.h"
#समावेश "evlist.h"
#समावेश "machine.h"
#समावेश "parse-events.h"
#समावेश "hists_common.h"
#समावेश "util/mmap.h"
#समावेश <त्रुटिसं.स>
#समावेश <linux/kernel.h>

काष्ठा sample अणु
	u32 pid;
	u64 ip;
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा map *map;
	काष्ठा symbol *sym;
पूर्ण;

/* For the numbers, see hists_common.c */
अटल काष्ठा sample fake_common_samples[] = अणु
	/* perf [kernel] schedule() */
	अणु .pid = FAKE_PID_PERF1, .ip = FAKE_IP_KERNEL_SCHEDULE, पूर्ण,
	/* perf [perf]   मुख्य() */
	अणु .pid = FAKE_PID_PERF2, .ip = FAKE_IP_PERF_MAIN, पूर्ण,
	/* perf [perf]   cmd_record() */
	अणु .pid = FAKE_PID_PERF2, .ip = FAKE_IP_PERF_CMD_RECORD, पूर्ण,
	/* bash [bash]   xदो_स्मृति() */
	अणु .pid = FAKE_PID_BASH,  .ip = FAKE_IP_BASH_XMALLOC, पूर्ण,
	/* bash [libc]   दो_स्मृति() */
	अणु .pid = FAKE_PID_BASH,  .ip = FAKE_IP_LIBC_MALLOC, पूर्ण,
पूर्ण;

अटल काष्ठा sample fake_samples[][5] = अणु
	अणु
		/* perf [perf]   run_command() */
		अणु .pid = FAKE_PID_PERF1, .ip = FAKE_IP_PERF_RUN_COMMAND, पूर्ण,
		/* perf [libc]   दो_स्मृति() */
		अणु .pid = FAKE_PID_PERF1, .ip = FAKE_IP_LIBC_MALLOC, पूर्ण,
		/* perf [kernel] page_fault() */
		अणु .pid = FAKE_PID_PERF1, .ip = FAKE_IP_KERNEL_PAGE_FAULT, पूर्ण,
		/* perf [kernel] sys_perf_event_खोलो() */
		अणु .pid = FAKE_PID_PERF2, .ip = FAKE_IP_KERNEL_SYS_PERF_EVENT_OPEN, पूर्ण,
		/* bash [libc]   मुक्त() */
		अणु .pid = FAKE_PID_BASH,  .ip = FAKE_IP_LIBC_FREE, पूर्ण,
	पूर्ण,
	अणु
		/* perf [libc]   मुक्त() */
		अणु .pid = FAKE_PID_PERF2, .ip = FAKE_IP_LIBC_FREE, पूर्ण,
		/* bash [libc]   दो_स्मृति() */
		अणु .pid = FAKE_PID_BASH,  .ip = FAKE_IP_LIBC_MALLOC, पूर्ण, /* will be merged */
		/* bash [bash]   xfee() */
		अणु .pid = FAKE_PID_BASH,  .ip = FAKE_IP_BASH_XFREE, पूर्ण,
		/* bash [libc]   पुनः_स्मृति() */
		अणु .pid = FAKE_PID_BASH,  .ip = FAKE_IP_LIBC_REALLOC, पूर्ण,
		/* bash [kernel] page_fault() */
		अणु .pid = FAKE_PID_BASH,  .ip = FAKE_IP_KERNEL_PAGE_FAULT, पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक add_hist_entries(काष्ठा evlist *evlist, काष्ठा machine *machine)
अणु
	काष्ठा evsel *evsel;
	काष्ठा addr_location al;
	काष्ठा hist_entry *he;
	काष्ठा perf_sample sample = अणु .period = 1, .weight = 1, पूर्ण;
	माप_प्रकार i = 0, k;

	/*
	 * each evsel will have 10 samples - 5 common and 5 distinct.
	 * However the second evsel also has a collapsed entry क्रम
	 * "bash [libc] malloc" so total 9 entries will be in the tree.
	 */
	evlist__क्रम_each_entry(evlist, evsel) अणु
		काष्ठा hists *hists = evsel__hists(evsel);

		क्रम (k = 0; k < ARRAY_SIZE(fake_common_samples); k++) अणु
			sample.cpumode = PERF_RECORD_MISC_USER;
			sample.pid = fake_common_samples[k].pid;
			sample.tid = fake_common_samples[k].pid;
			sample.ip = fake_common_samples[k].ip;

			अगर (machine__resolve(machine, &al, &sample) < 0)
				जाओ out;

			he = hists__add_entry(hists, &al, शून्य,
						शून्य, शून्य, &sample, true);
			अगर (he == शून्य) अणु
				addr_location__put(&al);
				जाओ out;
			पूर्ण

			fake_common_samples[k].thपढ़ो = al.thपढ़ो;
			fake_common_samples[k].map = al.map;
			fake_common_samples[k].sym = al.sym;
		पूर्ण

		क्रम (k = 0; k < ARRAY_SIZE(fake_samples[i]); k++) अणु
			sample.pid = fake_samples[i][k].pid;
			sample.tid = fake_samples[i][k].pid;
			sample.ip = fake_samples[i][k].ip;
			अगर (machine__resolve(machine, &al, &sample) < 0)
				जाओ out;

			he = hists__add_entry(hists, &al, शून्य,
						शून्य, शून्य, &sample, true);
			अगर (he == शून्य) अणु
				addr_location__put(&al);
				जाओ out;
			पूर्ण

			fake_samples[i][k].thपढ़ो = al.thपढ़ो;
			fake_samples[i][k].map = al.map;
			fake_samples[i][k].sym = al.sym;
		पूर्ण
		i++;
	पूर्ण

	वापस 0;

out:
	pr_debug("Not enough memory for adding a hist entry\n");
	वापस -1;
पूर्ण

अटल पूर्णांक find_sample(काष्ठा sample *samples, माप_प्रकार nr_samples,
		       काष्ठा thपढ़ो *t, काष्ठा map *m, काष्ठा symbol *s)
अणु
	जबतक (nr_samples--) अणु
		अगर (samples->thपढ़ो == t && samples->map == m &&
		    samples->sym == s)
			वापस 1;
		samples++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __validate_match(काष्ठा hists *hists)
अणु
	माप_प्रकार count = 0;
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node *node;

	/*
	 * Only entries from fake_common_samples should have a pair.
	 */
	अगर (hists__has(hists, need_collapse))
		root = &hists->entries_collapsed;
	अन्यथा
		root = hists->entries_in;

	node = rb_first_cached(root);
	जबतक (node) अणु
		काष्ठा hist_entry *he;

		he = rb_entry(node, काष्ठा hist_entry, rb_node_in);

		अगर (hist_entry__has_pairs(he)) अणु
			अगर (find_sample(fake_common_samples,
					ARRAY_SIZE(fake_common_samples),
					he->thपढ़ो, he->ms.map, he->ms.sym)) अणु
				count++;
			पूर्ण अन्यथा अणु
				pr_debug("Can't find the matched entry\n");
				वापस -1;
			पूर्ण
		पूर्ण

		node = rb_next(node);
	पूर्ण

	अगर (count != ARRAY_SIZE(fake_common_samples)) अणु
		pr_debug("Invalid count for matched entries: %zd of %zd\n",
			 count, ARRAY_SIZE(fake_common_samples));
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक validate_match(काष्ठा hists *leader, काष्ठा hists *other)
अणु
	वापस __validate_match(leader) || __validate_match(other);
पूर्ण

अटल पूर्णांक __validate_link(काष्ठा hists *hists, पूर्णांक idx)
अणु
	माप_प्रकार count = 0;
	माप_प्रकार count_pair = 0;
	माप_प्रकार count_dummy = 0;
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node *node;

	/*
	 * Leader hists (idx = 0) will have dummy entries from other,
	 * and some entries will have no pair.  However every entry
	 * in other hists should have (dummy) pair.
	 */
	अगर (hists__has(hists, need_collapse))
		root = &hists->entries_collapsed;
	अन्यथा
		root = hists->entries_in;

	node = rb_first_cached(root);
	जबतक (node) अणु
		काष्ठा hist_entry *he;

		he = rb_entry(node, काष्ठा hist_entry, rb_node_in);

		अगर (hist_entry__has_pairs(he)) अणु
			अगर (!find_sample(fake_common_samples,
					 ARRAY_SIZE(fake_common_samples),
					 he->thपढ़ो, he->ms.map, he->ms.sym) &&
			    !find_sample(fake_samples[idx],
					 ARRAY_SIZE(fake_samples[idx]),
					 he->thपढ़ो, he->ms.map, he->ms.sym)) अणु
				count_dummy++;
			पूर्ण
			count_pair++;
		पूर्ण अन्यथा अगर (idx) अणु
			pr_debug("A entry from the other hists should have pair\n");
			वापस -1;
		पूर्ण

		count++;
		node = rb_next(node);
	पूर्ण

	/*
	 * Note that we have a entry collapsed in the other (idx = 1) hists.
	 */
	अगर (idx == 0) अणु
		अगर (count_dummy != ARRAY_SIZE(fake_samples[1]) - 1) अणु
			pr_debug("Invalid count of dummy entries: %zd of %zd\n",
				 count_dummy, ARRAY_SIZE(fake_samples[1]) - 1);
			वापस -1;
		पूर्ण
		अगर (count != count_pair + ARRAY_SIZE(fake_samples[0])) अणु
			pr_debug("Invalid count of total leader entries: %zd of %zd\n",
				 count, count_pair + ARRAY_SIZE(fake_samples[0]));
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (count != count_pair) अणु
			pr_debug("Invalid count of total other entries: %zd of %zd\n",
				 count, count_pair);
			वापस -1;
		पूर्ण
		अगर (count_dummy > 0) अणु
			pr_debug("Other hists should not have dummy entries: %zd\n",
				 count_dummy);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक validate_link(काष्ठा hists *leader, काष्ठा hists *other)
अणु
	वापस __validate_link(leader, 0) || __validate_link(other, 1);
पूर्ण

पूर्णांक test__hists_link(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक err = -1;
	काष्ठा hists *hists, *first_hists;
	काष्ठा machines machines;
	काष्ठा machine *machine = शून्य;
	काष्ठा evsel *evsel, *first;
	काष्ठा evlist *evlist = evlist__new();

	अगर (evlist == शून्य)
                वापस -ENOMEM;

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
		hists = evsel__hists(evsel);
		hists__collapse_resort(hists, शून्य);

		अगर (verbose > 2)
			prपूर्णांक_hists_in(hists);
	पूर्ण

	first = evlist__first(evlist);
	evsel = evlist__last(evlist);

	first_hists = evsel__hists(first);
	hists = evsel__hists(evsel);

	/* match common entries */
	hists__match(first_hists, hists);
	err = validate_match(first_hists, hists);
	अगर (err)
		जाओ out;

	/* link common and/or dummy entries */
	hists__link(first_hists, hists);
	err = validate_link(first_hists, hists);
	अगर (err)
		जाओ out;

	err = 0;

out:
	/* tear करोwn everything */
	evlist__delete(evlist);
	reset_output_field();
	machines__निकास(&machines);

	वापस err;
पूर्ण
