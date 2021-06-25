<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <पूर्णांकtypes.h>
#समावेश "util/debug.h"
#समावेश "util/dso.h"
#समावेश "util/event.h" // काष्ठा perf_sample
#समावेश "util/map.h"
#समावेश "util/symbol.h"
#समावेश "util/sort.h"
#समावेश "util/evsel.h"
#समावेश "util/machine.h"
#समावेश "util/thread.h"
#समावेश "tests/hists_common.h"
#समावेश <linux/kernel.h>
#समावेश <linux/perf_event.h>

अटल काष्ठा अणु
	u32 pid;
	स्थिर अक्षर *comm;
पूर्ण fake_thपढ़ोs[] = अणु
	अणु FAKE_PID_PERF1, "perf" पूर्ण,
	अणु FAKE_PID_PERF2, "perf" पूर्ण,
	अणु FAKE_PID_BASH,  "bash" पूर्ण,
पूर्ण;

अटल काष्ठा अणु
	u32 pid;
	u64 start;
	स्थिर अक्षर *filename;
पूर्ण fake_mmap_info[] = अणु
	अणु FAKE_PID_PERF1, FAKE_MAP_PERF,   "perf" पूर्ण,
	अणु FAKE_PID_PERF1, FAKE_MAP_LIBC,   "libc" पूर्ण,
	अणु FAKE_PID_PERF1, FAKE_MAP_KERNEL, "[kernel]" पूर्ण,
	अणु FAKE_PID_PERF2, FAKE_MAP_PERF,   "perf" पूर्ण,
	अणु FAKE_PID_PERF2, FAKE_MAP_LIBC,   "libc" पूर्ण,
	अणु FAKE_PID_PERF2, FAKE_MAP_KERNEL, "[kernel]" पूर्ण,
	अणु FAKE_PID_BASH,  FAKE_MAP_BASH,   "bash" पूर्ण,
	अणु FAKE_PID_BASH,  FAKE_MAP_LIBC,   "libc" पूर्ण,
	अणु FAKE_PID_BASH,  FAKE_MAP_KERNEL, "[kernel]" पूर्ण,
पूर्ण;

काष्ठा fake_sym अणु
	u64 start;
	u64 length;
	स्थिर अक्षर *name;
पूर्ण;

अटल काष्ठा fake_sym perf_syms[] = अणु
	अणु FAKE_SYM_OFFSET1, FAKE_SYM_LENGTH, "main" पूर्ण,
	अणु FAKE_SYM_OFFSET2, FAKE_SYM_LENGTH, "run_command" पूर्ण,
	अणु FAKE_SYM_OFFSET3, FAKE_SYM_LENGTH, "cmd_record" पूर्ण,
पूर्ण;

अटल काष्ठा fake_sym bash_syms[] = अणु
	अणु FAKE_SYM_OFFSET1, FAKE_SYM_LENGTH, "main" पूर्ण,
	अणु FAKE_SYM_OFFSET2, FAKE_SYM_LENGTH, "xmalloc" पूर्ण,
	अणु FAKE_SYM_OFFSET3, FAKE_SYM_LENGTH, "xfree" पूर्ण,
पूर्ण;

अटल काष्ठा fake_sym libc_syms[] = अणु
	अणु 700, 100, "malloc" पूर्ण,
	अणु 800, 100, "free" पूर्ण,
	अणु 900, 100, "realloc" पूर्ण,
	अणु FAKE_SYM_OFFSET1, FAKE_SYM_LENGTH, "malloc" पूर्ण,
	अणु FAKE_SYM_OFFSET2, FAKE_SYM_LENGTH, "free" पूर्ण,
	अणु FAKE_SYM_OFFSET3, FAKE_SYM_LENGTH, "realloc" पूर्ण,
पूर्ण;

अटल काष्ठा fake_sym kernel_syms[] = अणु
	अणु FAKE_SYM_OFFSET1, FAKE_SYM_LENGTH, "schedule" पूर्ण,
	अणु FAKE_SYM_OFFSET2, FAKE_SYM_LENGTH, "page_fault" पूर्ण,
	अणु FAKE_SYM_OFFSET3, FAKE_SYM_LENGTH, "sys_perf_event_open" पूर्ण,
पूर्ण;

अटल काष्ठा अणु
	स्थिर अक्षर *dso_name;
	काष्ठा fake_sym *syms;
	माप_प्रकार nr_syms;
पूर्ण fake_symbols[] = अणु
	अणु "perf", perf_syms, ARRAY_SIZE(perf_syms) पूर्ण,
	अणु "bash", bash_syms, ARRAY_SIZE(bash_syms) पूर्ण,
	अणु "libc", libc_syms, ARRAY_SIZE(libc_syms) पूर्ण,
	अणु "[kernel]", kernel_syms, ARRAY_SIZE(kernel_syms) पूर्ण,
पूर्ण;

काष्ठा machine *setup_fake_machine(काष्ठा machines *machines)
अणु
	काष्ठा machine *machine = machines__find(machines, HOST_KERNEL_ID);
	माप_प्रकार i;

	अगर (machine == शून्य) अणु
		pr_debug("Not enough memory for machine setup\n");
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(fake_thपढ़ोs); i++) अणु
		काष्ठा thपढ़ो *thपढ़ो;

		thपढ़ो = machine__findnew_thपढ़ो(machine, fake_thपढ़ोs[i].pid,
						 fake_thपढ़ोs[i].pid);
		अगर (thपढ़ो == शून्य)
			जाओ out;

		thपढ़ो__set_comm(thपढ़ो, fake_thपढ़ोs[i].comm, 0);
		thपढ़ो__put(thपढ़ो);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(fake_mmap_info); i++) अणु
		काष्ठा perf_sample sample = अणु
			.cpumode = PERF_RECORD_MISC_USER,
		पूर्ण;
		जोड़ perf_event fake_mmap_event = अणु
			.mmap = अणु
				.pid = fake_mmap_info[i].pid,
				.tid = fake_mmap_info[i].pid,
				.start = fake_mmap_info[i].start,
				.len = FAKE_MAP_LENGTH,
				.pgoff = 0ULL,
			पूर्ण,
		पूर्ण;

		म_नकल(fake_mmap_event.mmap.filename,
		       fake_mmap_info[i].filename);

		machine__process_mmap_event(machine, &fake_mmap_event, &sample);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(fake_symbols); i++) अणु
		माप_प्रकार k;
		काष्ठा dso *dso;

		dso = machine__findnew_dso(machine, fake_symbols[i].dso_name);
		अगर (dso == शून्य)
			जाओ out;

		/* emulate dso__load() */
		dso__set_loaded(dso);

		क्रम (k = 0; k < fake_symbols[i].nr_syms; k++) अणु
			काष्ठा symbol *sym;
			काष्ठा fake_sym *fsym = &fake_symbols[i].syms[k];

			sym = symbol__new(fsym->start, fsym->length,
					  STB_GLOBAL, STT_FUNC, fsym->name);
			अगर (sym == शून्य) अणु
				dso__put(dso);
				जाओ out;
			पूर्ण

			symbols__insert(&dso->symbols, sym);
		पूर्ण

		dso__put(dso);
	पूर्ण

	वापस machine;

out:
	pr_debug("Not enough memory for machine setup\n");
	machine__delete_thपढ़ोs(machine);
	वापस शून्य;
पूर्ण

व्योम prपूर्णांक_hists_in(काष्ठा hists *hists)
अणु
	पूर्णांक i = 0;
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node *node;

	अगर (hists__has(hists, need_collapse))
		root = &hists->entries_collapsed;
	अन्यथा
		root = hists->entries_in;

	pr_info("----- %s --------\n", __func__);
	node = rb_first_cached(root);
	जबतक (node) अणु
		काष्ठा hist_entry *he;

		he = rb_entry(node, काष्ठा hist_entry, rb_node_in);

		अगर (!he->filtered) अणु
			pr_info("%2d: entry: %-8s [%-8s] %20s: period = %"PRIu64"\n",
				i, thपढ़ो__comm_str(he->thपढ़ो),
				he->ms.map->dso->लघु_name,
				he->ms.sym->name, he->stat.period);
		पूर्ण

		i++;
		node = rb_next(node);
	पूर्ण
पूर्ण

व्योम prपूर्णांक_hists_out(काष्ठा hists *hists)
अणु
	पूर्णांक i = 0;
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node *node;

	root = &hists->entries;

	pr_info("----- %s --------\n", __func__);
	node = rb_first_cached(root);
	जबतक (node) अणु
		काष्ठा hist_entry *he;

		he = rb_entry(node, काष्ठा hist_entry, rb_node);

		अगर (!he->filtered) अणु
			pr_info("%2d: entry: %8s:%5d [%-8s] %20s: period = %"PRIu64"/%"PRIu64"\n",
				i, thपढ़ो__comm_str(he->thपढ़ो), he->thपढ़ो->tid,
				he->ms.map->dso->लघु_name,
				he->ms.sym->name, he->stat.period,
				he->stat_acc ? he->stat_acc->period : 0);
		पूर्ण

		i++;
		node = rb_next(node);
	पूर्ण
पूर्ण
