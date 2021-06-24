<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "util/debug.h"
#समावेश "util/dso.h"
#समावेश "util/event.h"
#समावेश "util/map.h"
#समावेश "util/symbol.h"
#समावेश "util/sort.h"
#समावेश "util/evsel.h"
#समावेश "util/evlist.h"
#समावेश "util/machine.h"
#समावेश "util/thread.h"
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
पूर्ण;

/* For the numbers, see hists_common.c */
अटल काष्ठा sample fake_samples[] = अणु
	/* perf [kernel] schedule() */
	अणु .pid = FAKE_PID_PERF1, .ip = FAKE_IP_KERNEL_SCHEDULE, पूर्ण,
	/* perf [perf]   मुख्य() */
	अणु .pid = FAKE_PID_PERF1, .ip = FAKE_IP_PERF_MAIN, पूर्ण,
	/* perf [perf]   cmd_record() */
	अणु .pid = FAKE_PID_PERF1, .ip = FAKE_IP_PERF_CMD_RECORD, पूर्ण,
	/* perf [libc]   दो_स्मृति() */
	अणु .pid = FAKE_PID_PERF1, .ip = FAKE_IP_LIBC_MALLOC, पूर्ण,
	/* perf [libc]   मुक्त() */
	अणु .pid = FAKE_PID_PERF1, .ip = FAKE_IP_LIBC_FREE, पूर्ण,
	/* perf [perf]   मुख्य() */
	अणु .pid = FAKE_PID_PERF2, .ip = FAKE_IP_PERF_MAIN, पूर्ण,
	/* perf [kernel] page_fault() */
	अणु .pid = FAKE_PID_PERF2, .ip = FAKE_IP_KERNEL_PAGE_FAULT, पूर्ण,
	/* bash [bash]   मुख्य() */
	अणु .pid = FAKE_PID_BASH,  .ip = FAKE_IP_BASH_MAIN, पूर्ण,
	/* bash [bash]   xदो_स्मृति() */
	अणु .pid = FAKE_PID_BASH,  .ip = FAKE_IP_BASH_XMALLOC, पूर्ण,
	/* bash [kernel] page_fault() */
	अणु .pid = FAKE_PID_BASH,  .ip = FAKE_IP_KERNEL_PAGE_FAULT, पूर्ण,
पूर्ण;

/*
 * Will be cast to काष्ठा ip_callchain which has all 64 bit entries
 * of nr and ips[].
 */
अटल u64 fake_callchains[][10] = अणु
	/*   schedule => run_command => मुख्य */
	अणु 3, FAKE_IP_KERNEL_SCHEDULE, FAKE_IP_PERF_RUN_COMMAND, FAKE_IP_PERF_MAIN, पूर्ण,
	/*   मुख्य  */
	अणु 1, FAKE_IP_PERF_MAIN, पूर्ण,
	/*   cmd_record => run_command => मुख्य */
	अणु 3, FAKE_IP_PERF_CMD_RECORD, FAKE_IP_PERF_RUN_COMMAND, FAKE_IP_PERF_MAIN, पूर्ण,
	/*   दो_स्मृति => cmd_record => run_command => मुख्य */
	अणु 4, FAKE_IP_LIBC_MALLOC, FAKE_IP_PERF_CMD_RECORD, FAKE_IP_PERF_RUN_COMMAND,
	     FAKE_IP_PERF_MAIN, पूर्ण,
	/*   मुक्त => cmd_record => run_command => मुख्य */
	अणु 4, FAKE_IP_LIBC_FREE, FAKE_IP_PERF_CMD_RECORD, FAKE_IP_PERF_RUN_COMMAND,
	     FAKE_IP_PERF_MAIN, पूर्ण,
	/*   मुख्य */
	अणु 1, FAKE_IP_PERF_MAIN, पूर्ण,
	/*   page_fault => sys_perf_event_खोलो => run_command => मुख्य */
	अणु 4, FAKE_IP_KERNEL_PAGE_FAULT, FAKE_IP_KERNEL_SYS_PERF_EVENT_OPEN,
	     FAKE_IP_PERF_RUN_COMMAND, FAKE_IP_PERF_MAIN, पूर्ण,
	/*   मुख्य */
	अणु 1, FAKE_IP_BASH_MAIN, पूर्ण,
	/*   xदो_स्मृति => दो_स्मृति => xदो_स्मृति => दो_स्मृति => xदो_स्मृति => मुख्य */
	अणु 6, FAKE_IP_BASH_XMALLOC, FAKE_IP_LIBC_MALLOC, FAKE_IP_BASH_XMALLOC,
	     FAKE_IP_LIBC_MALLOC, FAKE_IP_BASH_XMALLOC, FAKE_IP_BASH_MAIN, पूर्ण,
	/*   page_fault => दो_स्मृति => मुख्य */
	अणु 3, FAKE_IP_KERNEL_PAGE_FAULT, FAKE_IP_LIBC_MALLOC, FAKE_IP_BASH_MAIN, पूर्ण,
पूर्ण;

अटल पूर्णांक add_hist_entries(काष्ठा hists *hists, काष्ठा machine *machine)
अणु
	काष्ठा addr_location al;
	काष्ठा evsel *evsel = hists_to_evsel(hists);
	काष्ठा perf_sample sample = अणु .period = 1000, पूर्ण;
	माप_प्रकार i;

	क्रम (i = 0; i < ARRAY_SIZE(fake_samples); i++) अणु
		काष्ठा hist_entry_iter iter = अणु
			.evsel = evsel,
			.sample	= &sample,
			.hide_unresolved = false,
		पूर्ण;

		अगर (symbol_conf.cumulate_callchain)
			iter.ops = &hist_iter_cumulative;
		अन्यथा
			iter.ops = &hist_iter_normal;

		sample.cpumode = PERF_RECORD_MISC_USER;
		sample.pid = fake_samples[i].pid;
		sample.tid = fake_samples[i].pid;
		sample.ip = fake_samples[i].ip;
		sample.callchain = (काष्ठा ip_callchain *)fake_callchains[i];

		अगर (machine__resolve(machine, &al, &sample) < 0)
			जाओ out;

		अगर (hist_entry_iter__add(&iter, &al, sysctl_perf_event_max_stack,
					 शून्य) < 0) अणु
			addr_location__put(&al);
			जाओ out;
		पूर्ण

		fake_samples[i].thपढ़ो = al.thपढ़ो;
		fake_samples[i].map = al.map;
		fake_samples[i].sym = al.sym;
	पूर्ण

	वापस TEST_OK;

out:
	pr_debug("Not enough memory for adding a hist entry\n");
	वापस TEST_FAIL;
पूर्ण

अटल व्योम del_hist_entries(काष्ठा hists *hists)
अणु
	काष्ठा hist_entry *he;
	काष्ठा rb_root_cached *root_in;
	काष्ठा rb_root_cached *root_out;
	काष्ठा rb_node *node;

	अगर (hists__has(hists, need_collapse))
		root_in = &hists->entries_collapsed;
	अन्यथा
		root_in = hists->entries_in;

	root_out = &hists->entries;

	जबतक (!RB_EMPTY_ROOT(&root_out->rb_root)) अणु
		node = rb_first_cached(root_out);

		he = rb_entry(node, काष्ठा hist_entry, rb_node);
		rb_erase_cached(node, root_out);
		rb_erase_cached(&he->rb_node_in, root_in);
		hist_entry__delete(he);
	पूर्ण
पूर्ण

प्रकार पूर्णांक (*test_fn_t)(काष्ठा evsel *, काष्ठा machine *);

#घोषणा COMM(he)  (thपढ़ो__comm_str(he->thपढ़ो))
#घोषणा DSO(he)   (he->ms.map->dso->लघु_name)
#घोषणा SYM(he)   (he->ms.sym->name)
#घोषणा CPU(he)   (he->cpu)
#घोषणा PID(he)   (he->thपढ़ो->tid)
#घोषणा DEPTH(he) (he->callchain->max_depth)
#घोषणा CDSO(cl)  (cl->ms.map->dso->लघु_name)
#घोषणा CSYM(cl)  (cl->ms.sym->name)

काष्ठा result अणु
	u64 children;
	u64 self;
	स्थिर अक्षर *comm;
	स्थिर अक्षर *dso;
	स्थिर अक्षर *sym;
पूर्ण;

काष्ठा callchain_result अणु
	u64 nr;
	काष्ठा अणु
		स्थिर अक्षर *dso;
		स्थिर अक्षर *sym;
	पूर्ण node[10];
पूर्ण;

अटल पूर्णांक करो_test(काष्ठा hists *hists, काष्ठा result *expected, माप_प्रकार nr_expected,
		   काष्ठा callchain_result *expected_callchain, माप_प्रकार nr_callchain)
अणु
	अक्षर buf[32];
	माप_प्रकार i, c;
	काष्ठा hist_entry *he;
	काष्ठा rb_root *root;
	काष्ठा rb_node *node;
	काष्ठा callchain_node *cnode;
	काष्ठा callchain_list *clist;

	/*
	 * adding and deleting hist entries must be करोne outside of this
	 * function since TEST_ASSERT_VAL() वापसs in हाल of failure.
	 */
	hists__collapse_resort(hists, शून्य);
	evsel__output_resort(hists_to_evsel(hists), शून्य);

	अगर (verbose > 2) अणु
		pr_info("use callchain: %d, cumulate callchain: %d\n",
			symbol_conf.use_callchain,
			symbol_conf.cumulate_callchain);
		prपूर्णांक_hists_out(hists);
	पूर्ण

	root = &hists->entries.rb_root;
	क्रम (node = rb_first(root), i = 0;
	     node && (he = rb_entry(node, काष्ठा hist_entry, rb_node));
	     node = rb_next(node), i++) अणु
		scnम_लिखो(buf, माप(buf), "Invalid hist entry #%zd", i);

		TEST_ASSERT_VAL("Incorrect number of hist entry",
				i < nr_expected);
		TEST_ASSERT_VAL(buf, he->stat.period == expected[i].self &&
				!म_भेद(COMM(he), expected[i].comm) &&
				!म_भेद(DSO(he), expected[i].dso) &&
				!म_भेद(SYM(he), expected[i].sym));

		अगर (symbol_conf.cumulate_callchain)
			TEST_ASSERT_VAL(buf, he->stat_acc->period == expected[i].children);

		अगर (!symbol_conf.use_callchain)
			जारी;

		/* check callchain entries */
		root = &he->callchain->node.rb_root;

		TEST_ASSERT_VAL("callchains expected", !RB_EMPTY_ROOT(root));
		cnode = rb_entry(rb_first(root), काष्ठा callchain_node, rb_node);

		c = 0;
		list_क्रम_each_entry(clist, &cnode->val, list) अणु
			scnम_लिखो(buf, माप(buf), "Invalid callchain entry #%zd/%zd", i, c);

			TEST_ASSERT_VAL("Incorrect number of callchain entry",
					c < expected_callchain[i].nr);
			TEST_ASSERT_VAL(buf,
				!म_भेद(CDSO(clist), expected_callchain[i].node[c].dso) &&
				!म_भेद(CSYM(clist), expected_callchain[i].node[c].sym));
			c++;
		पूर्ण
		/* TODO: handle multiple child nodes properly */
		TEST_ASSERT_VAL("Incorrect number of callchain entry",
				c <= expected_callchain[i].nr);
	पूर्ण
	TEST_ASSERT_VAL("Incorrect number of hist entry",
			i == nr_expected);
	TEST_ASSERT_VAL("Incorrect number of callchain entry",
			!symbol_conf.use_callchain || nr_expected == nr_callchain);
	वापस 0;
पूर्ण

/* NO callchain + NO children */
अटल पूर्णांक test1(काष्ठा evsel *evsel, काष्ठा machine *machine)
अणु
	पूर्णांक err;
	काष्ठा hists *hists = evsel__hists(evsel);
	/*
	 * expected output:
	 *
	 * Overhead  Command  Shared Object          Symbol
	 * ========  =======  =============  ==============
	 *   20.00%     perf  perf           [.] मुख्य
	 *   10.00%     bash  [kernel]       [k] page_fault
	 *   10.00%     bash  bash           [.] मुख्य
	 *   10.00%     bash  bash           [.] xदो_स्मृति
	 *   10.00%     perf  [kernel]       [k] page_fault
	 *   10.00%     perf  [kernel]       [k] schedule
	 *   10.00%     perf  libc           [.] मुक्त
	 *   10.00%     perf  libc           [.] दो_स्मृति
	 *   10.00%     perf  perf           [.] cmd_record
	 */
	काष्ठा result expected[] = अणु
		अणु 0, 2000, "perf", "perf",     "main" पूर्ण,
		अणु 0, 1000, "bash", "[kernel]", "page_fault" पूर्ण,
		अणु 0, 1000, "bash", "bash",     "main" पूर्ण,
		अणु 0, 1000, "bash", "bash",     "xmalloc" पूर्ण,
		अणु 0, 1000, "perf", "[kernel]", "page_fault" पूर्ण,
		अणु 0, 1000, "perf", "[kernel]", "schedule" पूर्ण,
		अणु 0, 1000, "perf", "libc",     "free" पूर्ण,
		अणु 0, 1000, "perf", "libc",     "malloc" पूर्ण,
		अणु 0, 1000, "perf", "perf",     "cmd_record" पूर्ण,
	पूर्ण;

	symbol_conf.use_callchain = false;
	symbol_conf.cumulate_callchain = false;
	evsel__reset_sample_bit(evsel, CALLCHAIN);

	setup_sorting(शून्य);
	callchain_रेजिस्टर_param(&callchain_param);

	err = add_hist_entries(hists, machine);
	अगर (err < 0)
		जाओ out;

	err = करो_test(hists, expected, ARRAY_SIZE(expected), शून्य, 0);

out:
	del_hist_entries(hists);
	reset_output_field();
	वापस err;
पूर्ण

/* callchain + NO children */
अटल पूर्णांक test2(काष्ठा evsel *evsel, काष्ठा machine *machine)
अणु
	पूर्णांक err;
	काष्ठा hists *hists = evsel__hists(evsel);
	/*
	 * expected output:
	 *
	 * Overhead  Command  Shared Object          Symbol
	 * ========  =======  =============  ==============
	 *   20.00%     perf  perf           [.] मुख्य
	 *              |
	 *              --- मुख्य
	 *
	 *   10.00%     bash  [kernel]       [k] page_fault
	 *              |
	 *              --- page_fault
	 *                  दो_स्मृति
	 *                  मुख्य
	 *
	 *   10.00%     bash  bash           [.] मुख्य
	 *              |
	 *              --- मुख्य
	 *
	 *   10.00%     bash  bash           [.] xदो_स्मृति
	 *              |
	 *              --- xदो_स्मृति
	 *                  दो_स्मृति
	 *                  xदो_स्मृति     <--- NOTE: there's a cycle
	 *                  दो_स्मृति
	 *                  xदो_स्मृति
	 *                  मुख्य
	 *
	 *   10.00%     perf  [kernel]       [k] page_fault
	 *              |
	 *              --- page_fault
	 *                  sys_perf_event_खोलो
	 *                  run_command
	 *                  मुख्य
	 *
	 *   10.00%     perf  [kernel]       [k] schedule
	 *              |
	 *              --- schedule
	 *                  run_command
	 *                  मुख्य
	 *
	 *   10.00%     perf  libc           [.] मुक्त
	 *              |
	 *              --- मुक्त
	 *                  cmd_record
	 *                  run_command
	 *                  मुख्य
	 *
	 *   10.00%     perf  libc           [.] दो_स्मृति
	 *              |
	 *              --- दो_स्मृति
	 *                  cmd_record
	 *                  run_command
	 *                  मुख्य
	 *
	 *   10.00%     perf  perf           [.] cmd_record
	 *              |
	 *              --- cmd_record
	 *                  run_command
	 *                  मुख्य
	 *
	 */
	काष्ठा result expected[] = अणु
		अणु 0, 2000, "perf", "perf",     "main" पूर्ण,
		अणु 0, 1000, "bash", "[kernel]", "page_fault" पूर्ण,
		अणु 0, 1000, "bash", "bash",     "main" पूर्ण,
		अणु 0, 1000, "bash", "bash",     "xmalloc" पूर्ण,
		अणु 0, 1000, "perf", "[kernel]", "page_fault" पूर्ण,
		अणु 0, 1000, "perf", "[kernel]", "schedule" पूर्ण,
		अणु 0, 1000, "perf", "libc",     "free" पूर्ण,
		अणु 0, 1000, "perf", "libc",     "malloc" पूर्ण,
		अणु 0, 1000, "perf", "perf",     "cmd_record" पूर्ण,
	पूर्ण;
	काष्ठा callchain_result expected_callchain[] = अणु
		अणु
			1, अणु	अणु "perf",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			3, अणु	अणु "[kernel]", "page_fault" पूर्ण,
				अणु "libc",     "malloc" पूर्ण,
				अणु "bash",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			1, अणु	अणु "bash",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			6, अणु	अणु "bash",     "xmalloc" पूर्ण,
				अणु "libc",     "malloc" पूर्ण,
				अणु "bash",     "xmalloc" पूर्ण,
				अणु "libc",     "malloc" पूर्ण,
				अणु "bash",     "xmalloc" पूर्ण,
				अणु "bash",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			4, अणु	अणु "[kernel]", "page_fault" पूर्ण,
				अणु "[kernel]", "sys_perf_event_open" पूर्ण,
				अणु "perf",     "run_command" पूर्ण,
				अणु "perf",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			3, अणु	अणु "[kernel]", "schedule" पूर्ण,
				अणु "perf",     "run_command" पूर्ण,
				अणु "perf",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			4, अणु	अणु "libc",     "free" पूर्ण,
				अणु "perf",     "cmd_record" पूर्ण,
				अणु "perf",     "run_command" पूर्ण,
				अणु "perf",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			4, अणु	अणु "libc",     "malloc" पूर्ण,
				अणु "perf",     "cmd_record" पूर्ण,
				अणु "perf",     "run_command" पूर्ण,
				अणु "perf",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			3, अणु	अणु "perf",     "cmd_record" पूर्ण,
				अणु "perf",     "run_command" पूर्ण,
				अणु "perf",     "main" पूर्ण, पूर्ण,
		पूर्ण,
	पूर्ण;

	symbol_conf.use_callchain = true;
	symbol_conf.cumulate_callchain = false;
	evsel__set_sample_bit(evsel, CALLCHAIN);

	setup_sorting(शून्य);
	callchain_रेजिस्टर_param(&callchain_param);

	err = add_hist_entries(hists, machine);
	अगर (err < 0)
		जाओ out;

	err = करो_test(hists, expected, ARRAY_SIZE(expected),
		      expected_callchain, ARRAY_SIZE(expected_callchain));

out:
	del_hist_entries(hists);
	reset_output_field();
	वापस err;
पूर्ण

/* NO callchain + children */
अटल पूर्णांक test3(काष्ठा evsel *evsel, काष्ठा machine *machine)
अणु
	पूर्णांक err;
	काष्ठा hists *hists = evsel__hists(evsel);
	/*
	 * expected output:
	 *
	 * Children      Self  Command  Shared Object                   Symbol
	 * ========  ========  =======  =============  =======================
	 *   70.00%    20.00%     perf  perf           [.] मुख्य
	 *   50.00%     0.00%     perf  perf           [.] run_command
	 *   30.00%    10.00%     bash  bash           [.] मुख्य
	 *   30.00%    10.00%     perf  perf           [.] cmd_record
	 *   20.00%     0.00%     bash  libc           [.] दो_स्मृति
	 *   10.00%    10.00%     bash  [kernel]       [k] page_fault
	 *   10.00%    10.00%     bash  bash           [.] xदो_स्मृति
	 *   10.00%    10.00%     perf  [kernel]       [k] page_fault
	 *   10.00%    10.00%     perf  libc           [.] दो_स्मृति
	 *   10.00%    10.00%     perf  [kernel]       [k] schedule
	 *   10.00%    10.00%     perf  libc           [.] मुक्त
	 *   10.00%     0.00%     perf  [kernel]       [k] sys_perf_event_खोलो
	 */
	काष्ठा result expected[] = अणु
		अणु 7000, 2000, "perf", "perf",     "main" पूर्ण,
		अणु 5000,    0, "perf", "perf",     "run_command" पूर्ण,
		अणु 3000, 1000, "bash", "bash",     "main" पूर्ण,
		अणु 3000, 1000, "perf", "perf",     "cmd_record" पूर्ण,
		अणु 2000,    0, "bash", "libc",     "malloc" पूर्ण,
		अणु 1000, 1000, "bash", "[kernel]", "page_fault" पूर्ण,
		अणु 1000, 1000, "bash", "bash",     "xmalloc" पूर्ण,
		अणु 1000, 1000, "perf", "[kernel]", "page_fault" पूर्ण,
		अणु 1000, 1000, "perf", "[kernel]", "schedule" पूर्ण,
		अणु 1000, 1000, "perf", "libc",     "free" पूर्ण,
		अणु 1000, 1000, "perf", "libc",     "malloc" पूर्ण,
		अणु 1000,    0, "perf", "[kernel]", "sys_perf_event_open" पूर्ण,
	पूर्ण;

	symbol_conf.use_callchain = false;
	symbol_conf.cumulate_callchain = true;
	evsel__reset_sample_bit(evsel, CALLCHAIN);

	setup_sorting(शून्य);
	callchain_रेजिस्टर_param(&callchain_param);

	err = add_hist_entries(hists, machine);
	अगर (err < 0)
		जाओ out;

	err = करो_test(hists, expected, ARRAY_SIZE(expected), शून्य, 0);

out:
	del_hist_entries(hists);
	reset_output_field();
	वापस err;
पूर्ण

/* callchain + children */
अटल पूर्णांक test4(काष्ठा evsel *evsel, काष्ठा machine *machine)
अणु
	पूर्णांक err;
	काष्ठा hists *hists = evsel__hists(evsel);
	/*
	 * expected output:
	 *
	 * Children      Self  Command  Shared Object                   Symbol
	 * ========  ========  =======  =============  =======================
	 *   70.00%    20.00%     perf  perf           [.] मुख्य
	 *              |
	 *              --- मुख्य
	 *
	 *   50.00%     0.00%     perf  perf           [.] run_command
	 *              |
	 *              --- run_command
	 *                  मुख्य
	 *
	 *   30.00%    10.00%     bash  bash           [.] मुख्य
	 *              |
	 *              --- मुख्य
	 *
	 *   30.00%    10.00%     perf  perf           [.] cmd_record
	 *              |
	 *              --- cmd_record
	 *                  run_command
	 *                  मुख्य
	 *
	 *   20.00%     0.00%     bash  libc           [.] दो_स्मृति
	 *              |
	 *              --- दो_स्मृति
	 *                 |
	 *                 |--50.00%-- xदो_स्मृति
	 *                 |           मुख्य
	 *                  --50.00%-- मुख्य
	 *
	 *   10.00%    10.00%     bash  [kernel]       [k] page_fault
	 *              |
	 *              --- page_fault
	 *                  दो_स्मृति
	 *                  मुख्य
	 *
	 *   10.00%    10.00%     bash  bash           [.] xदो_स्मृति
	 *              |
	 *              --- xदो_स्मृति
	 *                  दो_स्मृति
	 *                  xदो_स्मृति     <--- NOTE: there's a cycle
	 *                  दो_स्मृति
	 *                  xदो_स्मृति
	 *                  मुख्य
	 *
	 *   10.00%     0.00%     perf  [kernel]       [k] sys_perf_event_खोलो
	 *              |
	 *              --- sys_perf_event_खोलो
	 *                  run_command
	 *                  मुख्य
	 *
	 *   10.00%    10.00%     perf  [kernel]       [k] page_fault
	 *              |
	 *              --- page_fault
	 *                  sys_perf_event_खोलो
	 *                  run_command
	 *                  मुख्य
	 *
	 *   10.00%    10.00%     perf  [kernel]       [k] schedule
	 *              |
	 *              --- schedule
	 *                  run_command
	 *                  मुख्य
	 *
	 *   10.00%    10.00%     perf  libc           [.] मुक्त
	 *              |
	 *              --- मुक्त
	 *                  cmd_record
	 *                  run_command
	 *                  मुख्य
	 *
	 *   10.00%    10.00%     perf  libc           [.] दो_स्मृति
	 *              |
	 *              --- दो_स्मृति
	 *                  cmd_record
	 *                  run_command
	 *                  मुख्य
	 *
	 */
	काष्ठा result expected[] = अणु
		अणु 7000, 2000, "perf", "perf",     "main" पूर्ण,
		अणु 5000,    0, "perf", "perf",     "run_command" पूर्ण,
		अणु 3000, 1000, "bash", "bash",     "main" पूर्ण,
		अणु 3000, 1000, "perf", "perf",     "cmd_record" पूर्ण,
		अणु 2000,    0, "bash", "libc",     "malloc" पूर्ण,
		अणु 1000, 1000, "bash", "[kernel]", "page_fault" पूर्ण,
		अणु 1000, 1000, "bash", "bash",     "xmalloc" पूर्ण,
		अणु 1000,    0, "perf", "[kernel]", "sys_perf_event_open" पूर्ण,
		अणु 1000, 1000, "perf", "[kernel]", "page_fault" पूर्ण,
		अणु 1000, 1000, "perf", "[kernel]", "schedule" पूर्ण,
		अणु 1000, 1000, "perf", "libc",     "free" पूर्ण,
		अणु 1000, 1000, "perf", "libc",     "malloc" पूर्ण,
	पूर्ण;
	काष्ठा callchain_result expected_callchain[] = अणु
		अणु
			1, अणु	अणु "perf",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			2, अणु	अणु "perf",     "run_command" पूर्ण,
				अणु "perf",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			1, अणु	अणु "bash",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			3, अणु	अणु "perf",     "cmd_record" पूर्ण,
				अणु "perf",     "run_command" पूर्ण,
				अणु "perf",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			4, अणु	अणु "libc",     "malloc" पूर्ण,
				अणु "bash",     "xmalloc" पूर्ण,
				अणु "bash",     "main" पूर्ण,
				अणु "bash",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			3, अणु	अणु "[kernel]", "page_fault" पूर्ण,
				अणु "libc",     "malloc" पूर्ण,
				अणु "bash",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			6, अणु	अणु "bash",     "xmalloc" पूर्ण,
				अणु "libc",     "malloc" पूर्ण,
				अणु "bash",     "xmalloc" पूर्ण,
				अणु "libc",     "malloc" पूर्ण,
				अणु "bash",     "xmalloc" पूर्ण,
				अणु "bash",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			3, अणु	अणु "[kernel]", "sys_perf_event_open" पूर्ण,
				अणु "perf",     "run_command" पूर्ण,
				अणु "perf",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			4, अणु	अणु "[kernel]", "page_fault" पूर्ण,
				अणु "[kernel]", "sys_perf_event_open" पूर्ण,
				अणु "perf",     "run_command" पूर्ण,
				अणु "perf",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			3, अणु	अणु "[kernel]", "schedule" पूर्ण,
				अणु "perf",     "run_command" पूर्ण,
				अणु "perf",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			4, अणु	अणु "libc",     "free" पूर्ण,
				अणु "perf",     "cmd_record" पूर्ण,
				अणु "perf",     "run_command" पूर्ण,
				अणु "perf",     "main" पूर्ण, पूर्ण,
		पूर्ण,
		अणु
			4, अणु	अणु "libc",     "malloc" पूर्ण,
				अणु "perf",     "cmd_record" पूर्ण,
				अणु "perf",     "run_command" पूर्ण,
				अणु "perf",     "main" पूर्ण, पूर्ण,
		पूर्ण,
	पूर्ण;

	symbol_conf.use_callchain = true;
	symbol_conf.cumulate_callchain = true;
	evsel__set_sample_bit(evsel, CALLCHAIN);

	setup_sorting(शून्य);

	callchain_param = callchain_param_शेष;
	callchain_रेजिस्टर_param(&callchain_param);

	err = add_hist_entries(hists, machine);
	अगर (err < 0)
		जाओ out;

	err = करो_test(hists, expected, ARRAY_SIZE(expected),
		      expected_callchain, ARRAY_SIZE(expected_callchain));

out:
	del_hist_entries(hists);
	reset_output_field();
	वापस err;
पूर्ण

पूर्णांक test__hists_cumulate(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक err = TEST_FAIL;
	काष्ठा machines machines;
	काष्ठा machine *machine;
	काष्ठा evsel *evsel;
	काष्ठा evlist *evlist = evlist__new();
	माप_प्रकार i;
	test_fn_t testहालs[] = अणु
		test1,
		test2,
		test3,
		test4,
	पूर्ण;

	TEST_ASSERT_VAL("No memory", evlist);

	err = parse_events(evlist, "cpu-clock", शून्य);
	अगर (err)
		जाओ out;
	err = TEST_FAIL;

	machines__init(&machines);

	/* setup thपढ़ोs/dso/map/symbols also */
	machine = setup_fake_machine(&machines);
	अगर (!machine)
		जाओ out;

	अगर (verbose > 1)
		machine__ख_लिखो(machine, मानक_त्रुटि);

	evsel = evlist__first(evlist);

	क्रम (i = 0; i < ARRAY_SIZE(testहालs); i++) अणु
		err = testहालs[i](evsel, machine);
		अगर (err < 0)
			अवरोध;
	पूर्ण

out:
	/* tear करोwn everything */
	evlist__delete(evlist);
	machines__निकास(&machines);

	वापस err;
पूर्ण
