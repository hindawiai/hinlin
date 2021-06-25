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
	u32 cpu;
	u32 pid;
	u64 ip;
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा map *map;
	काष्ठा symbol *sym;
पूर्ण;

/* For the numbers, see hists_common.c */
अटल काष्ठा sample fake_samples[] = अणु
	/* perf [kernel] schedule() */
	अणु .cpu = 0, .pid = FAKE_PID_PERF1, .ip = FAKE_IP_KERNEL_SCHEDULE, पूर्ण,
	/* perf [perf]   मुख्य() */
	अणु .cpu = 1, .pid = FAKE_PID_PERF1, .ip = FAKE_IP_PERF_MAIN, पूर्ण,
	/* perf [perf]   cmd_record() */
	अणु .cpu = 1, .pid = FAKE_PID_PERF1, .ip = FAKE_IP_PERF_CMD_RECORD, पूर्ण,
	/* perf [libc]   दो_स्मृति() */
	अणु .cpu = 1, .pid = FAKE_PID_PERF1, .ip = FAKE_IP_LIBC_MALLOC, पूर्ण,
	/* perf [libc]   मुक्त() */
	अणु .cpu = 2, .pid = FAKE_PID_PERF1, .ip = FAKE_IP_LIBC_FREE, पूर्ण,
	/* perf [perf]   मुख्य() */
	अणु .cpu = 2, .pid = FAKE_PID_PERF2, .ip = FAKE_IP_PERF_MAIN, पूर्ण,
	/* perf [kernel] page_fault() */
	अणु .cpu = 2, .pid = FAKE_PID_PERF2, .ip = FAKE_IP_KERNEL_PAGE_FAULT, पूर्ण,
	/* bash [bash]   मुख्य() */
	अणु .cpu = 3, .pid = FAKE_PID_BASH,  .ip = FAKE_IP_BASH_MAIN, पूर्ण,
	/* bash [bash]   xदो_स्मृति() */
	अणु .cpu = 0, .pid = FAKE_PID_BASH,  .ip = FAKE_IP_BASH_XMALLOC, पूर्ण,
	/* bash [kernel] page_fault() */
	अणु .cpu = 1, .pid = FAKE_PID_BASH,  .ip = FAKE_IP_KERNEL_PAGE_FAULT, पूर्ण,
पूर्ण;

अटल पूर्णांक add_hist_entries(काष्ठा hists *hists, काष्ठा machine *machine)
अणु
	काष्ठा addr_location al;
	काष्ठा evsel *evsel = hists_to_evsel(hists);
	काष्ठा perf_sample sample = अणु .period = 100, पूर्ण;
	माप_प्रकार i;

	क्रम (i = 0; i < ARRAY_SIZE(fake_samples); i++) अणु
		काष्ठा hist_entry_iter iter = अणु
			.evsel = evsel,
			.sample = &sample,
			.ops = &hist_iter_normal,
			.hide_unresolved = false,
		पूर्ण;

		sample.cpumode = PERF_RECORD_MISC_USER;
		sample.cpu = fake_samples[i].cpu;
		sample.pid = fake_samples[i].pid;
		sample.tid = fake_samples[i].pid;
		sample.ip = fake_samples[i].ip;

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

/* शेष sort keys (no field) */
अटल पूर्णांक test1(काष्ठा evsel *evsel, काष्ठा machine *machine)
अणु
	पूर्णांक err;
	काष्ठा hists *hists = evsel__hists(evsel);
	काष्ठा hist_entry *he;
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node *node;

	field_order = शून्य;
	sort_order = शून्य; /* equivalent to sort_order = "comm,dso,sym" */

	setup_sorting(शून्य);

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
	err = add_hist_entries(hists, machine);
	अगर (err < 0)
		जाओ out;

	hists__collapse_resort(hists, शून्य);
	evsel__output_resort(evsel, शून्य);

	अगर (verbose > 2) अणु
		pr_info("[fields = %s, sort = %s]\n", field_order, sort_order);
		prपूर्णांक_hists_out(hists);
	पूर्ण

	root = &hists->entries;
	node = rb_first_cached(root);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(COMM(he), "perf") && !म_भेद(DSO(he), "perf") &&
			!म_भेद(SYM(he), "main") && he->stat.period == 200);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(COMM(he), "bash") && !म_भेद(DSO(he), "[kernel]") &&
			!म_भेद(SYM(he), "page_fault") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(COMM(he), "bash") && !म_भेद(DSO(he), "bash") &&
			!म_भेद(SYM(he), "main") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(COMM(he), "bash") && !म_भेद(DSO(he), "bash") &&
			!म_भेद(SYM(he), "xmalloc") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(COMM(he), "perf") && !म_भेद(DSO(he), "[kernel]") &&
			!म_भेद(SYM(he), "page_fault") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(COMM(he), "perf") && !म_भेद(DSO(he), "[kernel]") &&
			!म_भेद(SYM(he), "schedule") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(COMM(he), "perf") && !म_भेद(DSO(he), "libc") &&
			!म_भेद(SYM(he), "free") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(COMM(he), "perf") && !म_भेद(DSO(he), "libc") &&
			!म_भेद(SYM(he), "malloc") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(COMM(he), "perf") && !म_भेद(DSO(he), "perf") &&
			!म_भेद(SYM(he), "cmd_record") && he->stat.period == 100);

out:
	del_hist_entries(hists);
	reset_output_field();
	वापस err;
पूर्ण

/* mixed fields and sort keys */
अटल पूर्णांक test2(काष्ठा evsel *evsel, काष्ठा machine *machine)
अणु
	पूर्णांक err;
	काष्ठा hists *hists = evsel__hists(evsel);
	काष्ठा hist_entry *he;
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node *node;

	field_order = "overhead,cpu";
	sort_order = "pid";

	setup_sorting(शून्य);

	/*
	 * expected output:
	 *
	 * Overhead  CPU  Command:  Pid
	 * ========  ===  =============
	 *   30.00%    1  perf   :  100
	 *   10.00%    0  perf   :  100
	 *   10.00%    2  perf   :  100
	 *   20.00%    2  perf   :  200
	 *   10.00%    0  bash   :  300
	 *   10.00%    1  bash   :  300
	 *   10.00%    3  bash   :  300
	 */
	err = add_hist_entries(hists, machine);
	अगर (err < 0)
		जाओ out;

	hists__collapse_resort(hists, शून्य);
	evsel__output_resort(evsel, शून्य);

	अगर (verbose > 2) अणु
		pr_info("[fields = %s, sort = %s]\n", field_order, sort_order);
		prपूर्णांक_hists_out(hists);
	पूर्ण

	root = &hists->entries;
	node = rb_first_cached(root);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			CPU(he) == 1 && PID(he) == 100 && he->stat.period == 300);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			CPU(he) == 0 && PID(he) == 100 && he->stat.period == 100);

out:
	del_hist_entries(hists);
	reset_output_field();
	वापस err;
पूर्ण

/* fields only (no sort key) */
अटल पूर्णांक test3(काष्ठा evsel *evsel, काष्ठा machine *machine)
अणु
	पूर्णांक err;
	काष्ठा hists *hists = evsel__hists(evsel);
	काष्ठा hist_entry *he;
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node *node;

	field_order = "comm,overhead,dso";
	sort_order = शून्य;

	setup_sorting(शून्य);

	/*
	 * expected output:
	 *
	 * Command  Overhead  Shared Object
	 * =======  ========  =============
	 *    bash    20.00%  bash
	 *    bash    10.00%  [kernel]
	 *    perf    30.00%  perf
	 *    perf    20.00%  [kernel]
	 *    perf    20.00%  libc
	 */
	err = add_hist_entries(hists, machine);
	अगर (err < 0)
		जाओ out;

	hists__collapse_resort(hists, शून्य);
	evsel__output_resort(evsel, शून्य);

	अगर (verbose > 2) अणु
		pr_info("[fields = %s, sort = %s]\n", field_order, sort_order);
		prपूर्णांक_hists_out(hists);
	पूर्ण

	root = &hists->entries;
	node = rb_first_cached(root);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(COMM(he), "bash") && !म_भेद(DSO(he), "bash") &&
			he->stat.period == 200);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(COMM(he), "bash") && !म_भेद(DSO(he), "[kernel]") &&
			he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(COMM(he), "perf") && !म_भेद(DSO(he), "perf") &&
			he->stat.period == 300);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(COMM(he), "perf") && !म_भेद(DSO(he), "[kernel]") &&
			he->stat.period == 200);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(COMM(he), "perf") && !म_भेद(DSO(he), "libc") &&
			he->stat.period == 200);

out:
	del_hist_entries(hists);
	reset_output_field();
	वापस err;
पूर्ण

/* handle duplicate 'dso' field */
अटल पूर्णांक test4(काष्ठा evsel *evsel, काष्ठा machine *machine)
अणु
	पूर्णांक err;
	काष्ठा hists *hists = evsel__hists(evsel);
	काष्ठा hist_entry *he;
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node *node;

	field_order = "dso,sym,comm,overhead,dso";
	sort_order = "sym";

	setup_sorting(शून्य);

	/*
	 * expected output:
	 *
	 * Shared Object          Symbol  Command  Overhead
	 * =============  ==============  =======  ========
	 *          perf  [.] cmd_record     perf    10.00%
	 *          libc  [.] मुक्त           perf    10.00%
	 *          bash  [.] मुख्य           bash    10.00%
	 *          perf  [.] मुख्य           perf    20.00%
	 *          libc  [.] दो_स्मृति         perf    10.00%
	 *      [kernel]  [k] page_fault     bash    10.00%
	 *      [kernel]  [k] page_fault     perf    10.00%
	 *      [kernel]  [k] schedule       perf    10.00%
	 *          bash  [.] xदो_स्मृति        bash    10.00%
	 */
	err = add_hist_entries(hists, machine);
	अगर (err < 0)
		जाओ out;

	hists__collapse_resort(hists, शून्य);
	evsel__output_resort(evsel, शून्य);

	अगर (verbose > 2) अणु
		pr_info("[fields = %s, sort = %s]\n", field_order, sort_order);
		prपूर्णांक_hists_out(hists);
	पूर्ण

	root = &hists->entries;
	node = rb_first_cached(root);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(DSO(he), "perf") && !म_भेद(SYM(he), "cmd_record") &&
			!म_भेद(COMM(he), "perf") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(DSO(he), "libc") && !म_भेद(SYM(he), "free") &&
			!म_भेद(COMM(he), "perf") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(DSO(he), "bash") && !म_भेद(SYM(he), "main") &&
			!म_भेद(COMM(he), "bash") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(DSO(he), "perf") && !म_भेद(SYM(he), "main") &&
			!म_भेद(COMM(he), "perf") && he->stat.period == 200);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(DSO(he), "libc") && !म_भेद(SYM(he), "malloc") &&
			!म_भेद(COMM(he), "perf") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(DSO(he), "[kernel]") && !म_भेद(SYM(he), "page_fault") &&
			!म_भेद(COMM(he), "bash") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(DSO(he), "[kernel]") && !म_भेद(SYM(he), "page_fault") &&
			!म_भेद(COMM(he), "perf") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(DSO(he), "[kernel]") && !म_भेद(SYM(he), "schedule") &&
			!म_भेद(COMM(he), "perf") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			!म_भेद(DSO(he), "bash") && !म_भेद(SYM(he), "xmalloc") &&
			!म_भेद(COMM(he), "bash") && he->stat.period == 100);

out:
	del_hist_entries(hists);
	reset_output_field();
	वापस err;
पूर्ण

/* full sort keys w/o overhead field */
अटल पूर्णांक test5(काष्ठा evsel *evsel, काष्ठा machine *machine)
अणु
	पूर्णांक err;
	काष्ठा hists *hists = evsel__hists(evsel);
	काष्ठा hist_entry *he;
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node *node;

	field_order = "cpu,pid,comm,dso,sym";
	sort_order = "dso,pid";

	setup_sorting(शून्य);

	/*
	 * expected output:
	 *
	 * CPU  Command:  Pid  Command  Shared Object          Symbol
	 * ===  =============  =======  =============  ==============
	 *   0     perf:  100     perf       [kernel]  [k] schedule
	 *   2     perf:  200     perf       [kernel]  [k] page_fault
	 *   1     bash:  300     bash       [kernel]  [k] page_fault
	 *   0     bash:  300     bash           bash  [.] xदो_स्मृति
	 *   3     bash:  300     bash           bash  [.] मुख्य
	 *   1     perf:  100     perf           libc  [.] दो_स्मृति
	 *   2     perf:  100     perf           libc  [.] मुक्त
	 *   1     perf:  100     perf           perf  [.] cmd_record
	 *   1     perf:  100     perf           perf  [.] मुख्य
	 *   2     perf:  200     perf           perf  [.] मुख्य
	 */
	err = add_hist_entries(hists, machine);
	अगर (err < 0)
		जाओ out;

	hists__collapse_resort(hists, शून्य);
	evsel__output_resort(evsel, शून्य);

	अगर (verbose > 2) अणु
		pr_info("[fields = %s, sort = %s]\n", field_order, sort_order);
		prपूर्णांक_hists_out(hists);
	पूर्ण

	root = &hists->entries;
	node = rb_first_cached(root);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);

	TEST_ASSERT_VAL("Invalid hist entry",
			CPU(he) == 0 && PID(he) == 100 &&
			!म_भेद(COMM(he), "perf") && !म_भेद(DSO(he), "[kernel]") &&
			!म_भेद(SYM(he), "schedule") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			CPU(he) == 2 && PID(he) == 200 &&
			!म_भेद(COMM(he), "perf") && !म_भेद(DSO(he), "[kernel]") &&
			!म_भेद(SYM(he), "page_fault") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			CPU(he) == 1 && PID(he) == 300 &&
			!म_भेद(COMM(he), "bash") && !म_भेद(DSO(he), "[kernel]") &&
			!म_भेद(SYM(he), "page_fault") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			CPU(he) == 0 && PID(he) == 300 &&
			!म_भेद(COMM(he), "bash") && !म_भेद(DSO(he), "bash") &&
			!म_भेद(SYM(he), "xmalloc") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			CPU(he) == 3 && PID(he) == 300 &&
			!म_भेद(COMM(he), "bash") && !म_भेद(DSO(he), "bash") &&
			!म_भेद(SYM(he), "main") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			CPU(he) == 1 && PID(he) == 100 &&
			!म_भेद(COMM(he), "perf") && !म_भेद(DSO(he), "libc") &&
			!म_भेद(SYM(he), "malloc") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			CPU(he) == 2 && PID(he) == 100 &&
			!म_भेद(COMM(he), "perf") && !म_भेद(DSO(he), "libc") &&
			!म_भेद(SYM(he), "free") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			CPU(he) == 1 && PID(he) == 100 &&
			!म_भेद(COMM(he), "perf") && !म_भेद(DSO(he), "perf") &&
			!म_भेद(SYM(he), "cmd_record") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			CPU(he) == 1 && PID(he) == 100 &&
			!म_भेद(COMM(he), "perf") && !म_भेद(DSO(he), "perf") &&
			!म_भेद(SYM(he), "main") && he->stat.period == 100);

	node = rb_next(node);
	he = rb_entry(node, काष्ठा hist_entry, rb_node);
	TEST_ASSERT_VAL("Invalid hist entry",
			CPU(he) == 2 && PID(he) == 200 &&
			!म_भेद(COMM(he), "perf") && !म_भेद(DSO(he), "perf") &&
			!म_भेद(SYM(he), "main") && he->stat.period == 100);

out:
	del_hist_entries(hists);
	reset_output_field();
	वापस err;
पूर्ण

पूर्णांक test__hists_output(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
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
		test5,
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
