<शैली गुरु>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <perf/cpumap.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <uapi/linux/mman.h> /* To get things like MAP_HUGETLB even on older libc headers */
#समावेश <linux/perf_event.h>
#समावेश <linux/zभाग.स>
#समावेश "cpumap.h"
#समावेश "dso.h"
#समावेश "event.h"
#समावेश "debug.h"
#समावेश "hist.h"
#समावेश "machine.h"
#समावेश "sort.h"
#समावेश "string2.h"
#समावेश "strlist.h"
#समावेश "thread.h"
#समावेश "thread_map.h"
#समावेश "time-utils.h"
#समावेश <linux/प्रकार.स>
#समावेश "map.h"
#समावेश "util/namespaces.h"
#समावेश "symbol.h"
#समावेश "symbol/kallsyms.h"
#समावेश "asm/bug.h"
#समावेश "stat.h"
#समावेश "session.h"
#समावेश "bpf-event.h"
#समावेश "print_binary.h"
#समावेश "tool.h"
#समावेश "../perf.h"

अटल स्थिर अक्षर *perf_event__names[] = अणु
	[0]					= "TOTAL",
	[PERF_RECORD_MMAP]			= "MMAP",
	[PERF_RECORD_MMAP2]			= "MMAP2",
	[PERF_RECORD_LOST]			= "LOST",
	[PERF_RECORD_COMM]			= "COMM",
	[PERF_RECORD_EXIT]			= "EXIT",
	[PERF_RECORD_THROTTLE]			= "THROTTLE",
	[PERF_RECORD_UNTHROTTLE]		= "UNTHROTTLE",
	[PERF_RECORD_FORK]			= "FORK",
	[PERF_RECORD_READ]			= "READ",
	[PERF_RECORD_SAMPLE]			= "SAMPLE",
	[PERF_RECORD_AUX]			= "AUX",
	[PERF_RECORD_ITRACE_START]		= "ITRACE_START",
	[PERF_RECORD_LOST_SAMPLES]		= "LOST_SAMPLES",
	[PERF_RECORD_SWITCH]			= "SWITCH",
	[PERF_RECORD_SWITCH_CPU_WIDE]		= "SWITCH_CPU_WIDE",
	[PERF_RECORD_NAMESPACES]		= "NAMESPACES",
	[PERF_RECORD_KSYMBOL]			= "KSYMBOL",
	[PERF_RECORD_BPF_EVENT]			= "BPF_EVENT",
	[PERF_RECORD_CGROUP]			= "CGROUP",
	[PERF_RECORD_TEXT_POKE]			= "TEXT_POKE",
	[PERF_RECORD_HEADER_ATTR]		= "ATTR",
	[PERF_RECORD_HEADER_EVENT_TYPE]		= "EVENT_TYPE",
	[PERF_RECORD_HEADER_TRACING_DATA]	= "TRACING_DATA",
	[PERF_RECORD_HEADER_BUILD_ID]		= "BUILD_ID",
	[PERF_RECORD_FINISHED_ROUND]		= "FINISHED_ROUND",
	[PERF_RECORD_ID_INDEX]			= "ID_INDEX",
	[PERF_RECORD_AUXTRACE_INFO]		= "AUXTRACE_INFO",
	[PERF_RECORD_AUXTRACE]			= "AUXTRACE",
	[PERF_RECORD_AUXTRACE_ERROR]		= "AUXTRACE_ERROR",
	[PERF_RECORD_THREAD_MAP]		= "THREAD_MAP",
	[PERF_RECORD_CPU_MAP]			= "CPU_MAP",
	[PERF_RECORD_STAT_CONFIG]		= "STAT_CONFIG",
	[PERF_RECORD_STAT]			= "STAT",
	[PERF_RECORD_STAT_ROUND]		= "STAT_ROUND",
	[PERF_RECORD_EVENT_UPDATE]		= "EVENT_UPDATE",
	[PERF_RECORD_TIME_CONV]			= "TIME_CONV",
	[PERF_RECORD_HEADER_FEATURE]		= "FEATURE",
	[PERF_RECORD_COMPRESSED]		= "COMPRESSED",
पूर्ण;

स्थिर अक्षर *perf_event__name(अचिन्हित पूर्णांक id)
अणु
	अगर (id >= ARRAY_SIZE(perf_event__names))
		वापस "INVALID";
	अगर (!perf_event__names[id])
		वापस "UNKNOWN";
	वापस perf_event__names[id];
पूर्ण

काष्ठा process_symbol_args अणु
	स्थिर अक्षर *name;
	u64	   start;
पूर्ण;

अटल पूर्णांक find_symbol_cb(व्योम *arg, स्थिर अक्षर *name, अक्षर type,
			  u64 start)
अणु
	काष्ठा process_symbol_args *args = arg;

	/*
	 * Must be a function or at least an alias, as in PARISC64, where "_text" is
	 * an 'A' to the same address as "_stext".
	 */
	अगर (!(kallsyms__is_function(type) ||
	      type == 'A') || म_भेद(name, args->name))
		वापस 0;

	args->start = start;
	वापस 1;
पूर्ण

पूर्णांक kallsyms__get_function_start(स्थिर अक्षर *kallsyms_filename,
				 स्थिर अक्षर *symbol_name, u64 *addr)
अणु
	काष्ठा process_symbol_args args = अणु .name = symbol_name, पूर्ण;

	अगर (kallsyms__parse(kallsyms_filename, &args, find_symbol_cb) <= 0)
		वापस -1;

	*addr = args.start;
	वापस 0;
पूर्ण

व्योम perf_event__पढ़ो_stat_config(काष्ठा perf_stat_config *config,
				  काष्ठा perf_record_stat_config *event)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < event->nr; i++) अणु

		चयन (event->data[i].tag) अणु
#घोषणा CASE(__term, __val)					\
		हाल PERF_STAT_CONFIG_TERM__##__term:		\
			config->__val = event->data[i].val;	\
			अवरोध;

		CASE(AGGR_MODE, aggr_mode)
		CASE(SCALE,     scale)
		CASE(INTERVAL,  पूर्णांकerval)
#अघोषित CASE
		शेष:
			pr_warning("unknown stat config term %" PRI_lu64 "\n",
				   event->data[i].tag);
		पूर्ण
	पूर्ण
पूर्ण

माप_प्रकार perf_event__ख_लिखो_comm(जोड़ perf_event *event, खाता *fp)
अणु
	स्थिर अक्षर *s;

	अगर (event->header.misc & PERF_RECORD_MISC_COMM_EXEC)
		s = " exec";
	अन्यथा
		s = "";

	वापस ख_लिखो(fp, "%s: %s:%d/%d\n", s, event->comm.comm, event->comm.pid, event->comm.tid);
पूर्ण

माप_प्रकार perf_event__ख_लिखो_namespaces(जोड़ perf_event *event, खाता *fp)
अणु
	माप_प्रकार ret = 0;
	काष्ठा perf_ns_link_info *ns_link_info;
	u32 nr_namespaces, idx;

	ns_link_info = event->namespaces.link_info;
	nr_namespaces = event->namespaces.nr_namespaces;

	ret += ख_लिखो(fp, " %d/%d - nr_namespaces: %u\n\t\t[",
		       event->namespaces.pid,
		       event->namespaces.tid,
		       nr_namespaces);

	क्रम (idx = 0; idx < nr_namespaces; idx++) अणु
		अगर (idx && (idx % 4 == 0))
			ret += ख_लिखो(fp, "\n\t\t ");

		ret  += ख_लिखो(fp, "%u/%s: %" PRIu64 "/%#" PRIx64 "%s", idx,
				perf_ns__name(idx), (u64)ns_link_info[idx].dev,
				(u64)ns_link_info[idx].ino,
				((idx + 1) != nr_namespaces) ? ", " : "]\n");
	पूर्ण

	वापस ret;
पूर्ण

माप_प्रकार perf_event__ख_लिखो_cgroup(जोड़ perf_event *event, खाता *fp)
अणु
	वापस ख_लिखो(fp, " cgroup: %" PRI_lu64 " %s\n",
		       event->cgroup.id, event->cgroup.path);
पूर्ण

पूर्णांक perf_event__process_comm(काष्ठा perf_tool *tool __maybe_unused,
			     जोड़ perf_event *event,
			     काष्ठा perf_sample *sample,
			     काष्ठा machine *machine)
अणु
	वापस machine__process_comm_event(machine, event, sample);
पूर्ण

पूर्णांक perf_event__process_namespaces(काष्ठा perf_tool *tool __maybe_unused,
				   जोड़ perf_event *event,
				   काष्ठा perf_sample *sample,
				   काष्ठा machine *machine)
अणु
	वापस machine__process_namespaces_event(machine, event, sample);
पूर्ण

पूर्णांक perf_event__process_cgroup(काष्ठा perf_tool *tool __maybe_unused,
			       जोड़ perf_event *event,
			       काष्ठा perf_sample *sample,
			       काष्ठा machine *machine)
अणु
	वापस machine__process_cgroup_event(machine, event, sample);
पूर्ण

पूर्णांक perf_event__process_lost(काष्ठा perf_tool *tool __maybe_unused,
			     जोड़ perf_event *event,
			     काष्ठा perf_sample *sample,
			     काष्ठा machine *machine)
अणु
	वापस machine__process_lost_event(machine, event, sample);
पूर्ण

पूर्णांक perf_event__process_aux(काष्ठा perf_tool *tool __maybe_unused,
			    जोड़ perf_event *event,
			    काष्ठा perf_sample *sample __maybe_unused,
			    काष्ठा machine *machine)
अणु
	वापस machine__process_aux_event(machine, event);
पूर्ण

पूर्णांक perf_event__process_itrace_start(काष्ठा perf_tool *tool __maybe_unused,
				     जोड़ perf_event *event,
				     काष्ठा perf_sample *sample __maybe_unused,
				     काष्ठा machine *machine)
अणु
	वापस machine__process_itrace_start_event(machine, event);
पूर्ण

पूर्णांक perf_event__process_lost_samples(काष्ठा perf_tool *tool __maybe_unused,
				     जोड़ perf_event *event,
				     काष्ठा perf_sample *sample,
				     काष्ठा machine *machine)
अणु
	वापस machine__process_lost_samples_event(machine, event, sample);
पूर्ण

पूर्णांक perf_event__process_चयन(काष्ठा perf_tool *tool __maybe_unused,
			       जोड़ perf_event *event,
			       काष्ठा perf_sample *sample __maybe_unused,
			       काष्ठा machine *machine)
अणु
	वापस machine__process_चयन_event(machine, event);
पूर्ण

पूर्णांक perf_event__process_ksymbol(काष्ठा perf_tool *tool __maybe_unused,
				जोड़ perf_event *event,
				काष्ठा perf_sample *sample __maybe_unused,
				काष्ठा machine *machine)
अणु
	वापस machine__process_ksymbol(machine, event, sample);
पूर्ण

पूर्णांक perf_event__process_bpf(काष्ठा perf_tool *tool __maybe_unused,
			    जोड़ perf_event *event,
			    काष्ठा perf_sample *sample,
			    काष्ठा machine *machine)
अणु
	वापस machine__process_bpf(machine, event, sample);
पूर्ण

पूर्णांक perf_event__process_text_poke(काष्ठा perf_tool *tool __maybe_unused,
				  जोड़ perf_event *event,
				  काष्ठा perf_sample *sample,
				  काष्ठा machine *machine)
अणु
	वापस machine__process_text_poke(machine, event, sample);
पूर्ण

माप_प्रकार perf_event__ख_लिखो_mmap(जोड़ perf_event *event, खाता *fp)
अणु
	वापस ख_लिखो(fp, " %d/%d: [%#" PRI_lx64 "(%#" PRI_lx64 ") @ %#" PRI_lx64 "]: %c %s\n",
		       event->mmap.pid, event->mmap.tid, event->mmap.start,
		       event->mmap.len, event->mmap.pgoff,
		       (event->header.misc & PERF_RECORD_MISC_MMAP_DATA) ? 'r' : 'x',
		       event->mmap.filename);
पूर्ण

माप_प्रकार perf_event__ख_लिखो_mmap2(जोड़ perf_event *event, खाता *fp)
अणु
	अगर (event->header.misc & PERF_RECORD_MISC_MMAP_BUILD_ID) अणु
		अक्षर sbuild_id[SBUILD_ID_SIZE];
		काष्ठा build_id bid;

		build_id__init(&bid, event->mmap2.build_id,
			       event->mmap2.build_id_size);
		build_id__प्र_लिखो(&bid, sbuild_id);

		वापस ख_लिखो(fp, " %d/%d: [%#" PRI_lx64 "(%#" PRI_lx64 ") @ %#" PRI_lx64
				   " <%s>]: %c%c%c%c %s\n",
			       event->mmap2.pid, event->mmap2.tid, event->mmap2.start,
			       event->mmap2.len, event->mmap2.pgoff, sbuild_id,
			       (event->mmap2.prot & PROT_READ) ? 'r' : '-',
			       (event->mmap2.prot & PROT_WRITE) ? 'w' : '-',
			       (event->mmap2.prot & PROT_EXEC) ? 'x' : '-',
			       (event->mmap2.flags & MAP_SHARED) ? 's' : 'p',
			       event->mmap2.filename);
	पूर्ण अन्यथा अणु
		वापस ख_लिखो(fp, " %d/%d: [%#" PRI_lx64 "(%#" PRI_lx64 ") @ %#" PRI_lx64
				   " %02x:%02x %"PRI_lu64" %"PRI_lu64"]: %c%c%c%c %s\n",
			       event->mmap2.pid, event->mmap2.tid, event->mmap2.start,
			       event->mmap2.len, event->mmap2.pgoff, event->mmap2.maj,
			       event->mmap2.min, event->mmap2.ino,
			       event->mmap2.ino_generation,
			       (event->mmap2.prot & PROT_READ) ? 'r' : '-',
			       (event->mmap2.prot & PROT_WRITE) ? 'w' : '-',
			       (event->mmap2.prot & PROT_EXEC) ? 'x' : '-',
			       (event->mmap2.flags & MAP_SHARED) ? 's' : 'p',
			       event->mmap2.filename);
	पूर्ण
पूर्ण

माप_प्रकार perf_event__ख_लिखो_thपढ़ो_map(जोड़ perf_event *event, खाता *fp)
अणु
	काष्ठा perf_thपढ़ो_map *thपढ़ोs = thपढ़ो_map__new_event(&event->thपढ़ो_map);
	माप_प्रकार ret;

	ret = ख_लिखो(fp, " nr: ");

	अगर (thपढ़ोs)
		ret += thपढ़ो_map__ख_लिखो(thपढ़ोs, fp);
	अन्यथा
		ret += ख_लिखो(fp, "failed to get threads from event\n");

	perf_thपढ़ो_map__put(thपढ़ोs);
	वापस ret;
पूर्ण

माप_प्रकार perf_event__ख_लिखो_cpu_map(जोड़ perf_event *event, खाता *fp)
अणु
	काष्ठा perf_cpu_map *cpus = cpu_map__new_data(&event->cpu_map.data);
	माप_प्रकार ret;

	ret = ख_लिखो(fp, ": ");

	अगर (cpus)
		ret += cpu_map__ख_लिखो(cpus, fp);
	अन्यथा
		ret += ख_लिखो(fp, "failed to get cpumap from event\n");

	perf_cpu_map__put(cpus);
	वापस ret;
पूर्ण

पूर्णांक perf_event__process_mmap(काष्ठा perf_tool *tool __maybe_unused,
			     जोड़ perf_event *event,
			     काष्ठा perf_sample *sample,
			     काष्ठा machine *machine)
अणु
	वापस machine__process_mmap_event(machine, event, sample);
पूर्ण

पूर्णांक perf_event__process_mmap2(काष्ठा perf_tool *tool __maybe_unused,
			     जोड़ perf_event *event,
			     काष्ठा perf_sample *sample,
			     काष्ठा machine *machine)
अणु
	वापस machine__process_mmap2_event(machine, event, sample);
पूर्ण

माप_प्रकार perf_event__ख_लिखो_task(जोड़ perf_event *event, खाता *fp)
अणु
	वापस ख_लिखो(fp, "(%d:%d):(%d:%d)\n",
		       event->विभाजन.pid, event->विभाजन.tid,
		       event->विभाजन.ppid, event->विभाजन.ptid);
पूर्ण

पूर्णांक perf_event__process_विभाजन(काष्ठा perf_tool *tool __maybe_unused,
			     जोड़ perf_event *event,
			     काष्ठा perf_sample *sample,
			     काष्ठा machine *machine)
अणु
	वापस machine__process_विभाजन_event(machine, event, sample);
पूर्ण

पूर्णांक perf_event__process_निकास(काष्ठा perf_tool *tool __maybe_unused,
			     जोड़ perf_event *event,
			     काष्ठा perf_sample *sample,
			     काष्ठा machine *machine)
अणु
	वापस machine__process_निकास_event(machine, event, sample);
पूर्ण

माप_प्रकार perf_event__ख_लिखो_aux(जोड़ perf_event *event, खाता *fp)
अणु
	वापस ख_लिखो(fp, " offset: %#"PRI_lx64" size: %#"PRI_lx64" flags: %#"PRI_lx64" [%s%s%s]\n",
		       event->aux.aux_offset, event->aux.aux_size,
		       event->aux.flags,
		       event->aux.flags & PERF_AUX_FLAG_TRUNCATED ? "T" : "",
		       event->aux.flags & PERF_AUX_FLAG_OVERWRITE ? "O" : "",
		       event->aux.flags & PERF_AUX_FLAG_PARTIAL   ? "P" : "");
पूर्ण

माप_प्रकार perf_event__ख_लिखो_itrace_start(जोड़ perf_event *event, खाता *fp)
अणु
	वापस ख_लिखो(fp, " pid: %u tid: %u\n",
		       event->itrace_start.pid, event->itrace_start.tid);
पूर्ण

माप_प्रकार perf_event__ख_लिखो_चयन(जोड़ perf_event *event, खाता *fp)
अणु
	bool out = event->header.misc & PERF_RECORD_MISC_SWITCH_OUT;
	स्थिर अक्षर *in_out = !out ? "IN         " :
		!(event->header.misc & PERF_RECORD_MISC_SWITCH_OUT_PREEMPT) ?
				    "OUT        " : "OUT preempt";

	अगर (event->header.type == PERF_RECORD_SWITCH)
		वापस ख_लिखो(fp, " %s\n", in_out);

	वापस ख_लिखो(fp, " %s  %s pid/tid: %5d/%-5d\n",
		       in_out, out ? "next" : "prev",
		       event->context_चयन.next_prev_pid,
		       event->context_चयन.next_prev_tid);
पूर्ण

अटल माप_प्रकार perf_event__ख_लिखो_lost(जोड़ perf_event *event, खाता *fp)
अणु
	वापस ख_लिखो(fp, " lost %" PRI_lu64 "\n", event->lost.lost);
पूर्ण

माप_प्रकार perf_event__ख_लिखो_ksymbol(जोड़ perf_event *event, खाता *fp)
अणु
	वापस ख_लिखो(fp, " addr %" PRI_lx64 " len %u type %u flags 0x%x name %s\n",
		       event->ksymbol.addr, event->ksymbol.len,
		       event->ksymbol.ksym_type,
		       event->ksymbol.flags, event->ksymbol.name);
पूर्ण

माप_प्रकार perf_event__ख_लिखो_bpf(जोड़ perf_event *event, खाता *fp)
अणु
	वापस ख_लिखो(fp, " type %u, flags %u, id %u\n",
		       event->bpf.type, event->bpf.flags, event->bpf.id);
पूर्ण

अटल पूर्णांक text_poke_prपूर्णांकer(क्रमागत binary_prपूर्णांकer_ops op, अचिन्हित पूर्णांक val,
			     व्योम *extra, खाता *fp)
अणु
	bool old = *(bool *)extra;

	चयन ((पूर्णांक)op) अणु
	हाल BINARY_PRINT_LINE_BEGIN:
		वापस ख_लिखो(fp, "            %s bytes:", old ? "Old" : "New");
	हाल BINARY_PRINT_NUM_DATA:
		वापस ख_लिखो(fp, " %02x", val);
	हाल BINARY_PRINT_LINE_END:
		वापस ख_लिखो(fp, "\n");
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

माप_प्रकार perf_event__ख_लिखो_text_poke(जोड़ perf_event *event, काष्ठा machine *machine, खाता *fp)
अणु
	काष्ठा perf_record_text_poke_event *tp = &event->text_poke;
	माप_प्रकार ret;
	bool old;

	ret = ख_लिखो(fp, " %" PRI_lx64 " ", tp->addr);
	अगर (machine) अणु
		काष्ठा addr_location al;

		al.map = maps__find(&machine->kmaps, tp->addr);
		अगर (al.map && map__load(al.map) >= 0) अणु
			al.addr = al.map->map_ip(al.map, tp->addr);
			al.sym = map__find_symbol(al.map, al.addr);
			अगर (al.sym)
				ret += symbol__ख_लिखो_symname_offs(al.sym, &al, fp);
		पूर्ण
	पूर्ण
	ret += ख_लिखो(fp, " old len %u new len %u\n", tp->old_len, tp->new_len);
	old = true;
	ret += binary__ख_लिखो(tp->bytes, tp->old_len, 16, text_poke_prपूर्णांकer,
			       &old, fp);
	old = false;
	ret += binary__ख_लिखो(tp->bytes + tp->old_len, tp->new_len, 16,
			       text_poke_prपूर्णांकer, &old, fp);
	वापस ret;
पूर्ण

माप_प्रकार perf_event__ख_लिखो(जोड़ perf_event *event, काष्ठा machine *machine, खाता *fp)
अणु
	माप_प्रकार ret = ख_लिखो(fp, "PERF_RECORD_%s",
			     perf_event__name(event->header.type));

	चयन (event->header.type) अणु
	हाल PERF_RECORD_COMM:
		ret += perf_event__ख_लिखो_comm(event, fp);
		अवरोध;
	हाल PERF_RECORD_FORK:
	हाल PERF_RECORD_EXIT:
		ret += perf_event__ख_लिखो_task(event, fp);
		अवरोध;
	हाल PERF_RECORD_MMAP:
		ret += perf_event__ख_लिखो_mmap(event, fp);
		अवरोध;
	हाल PERF_RECORD_NAMESPACES:
		ret += perf_event__ख_लिखो_namespaces(event, fp);
		अवरोध;
	हाल PERF_RECORD_CGROUP:
		ret += perf_event__ख_लिखो_cgroup(event, fp);
		अवरोध;
	हाल PERF_RECORD_MMAP2:
		ret += perf_event__ख_लिखो_mmap2(event, fp);
		अवरोध;
	हाल PERF_RECORD_AUX:
		ret += perf_event__ख_लिखो_aux(event, fp);
		अवरोध;
	हाल PERF_RECORD_ITRACE_START:
		ret += perf_event__ख_लिखो_itrace_start(event, fp);
		अवरोध;
	हाल PERF_RECORD_SWITCH:
	हाल PERF_RECORD_SWITCH_CPU_WIDE:
		ret += perf_event__ख_लिखो_चयन(event, fp);
		अवरोध;
	हाल PERF_RECORD_LOST:
		ret += perf_event__ख_लिखो_lost(event, fp);
		अवरोध;
	हाल PERF_RECORD_KSYMBOL:
		ret += perf_event__ख_लिखो_ksymbol(event, fp);
		अवरोध;
	हाल PERF_RECORD_BPF_EVENT:
		ret += perf_event__ख_लिखो_bpf(event, fp);
		अवरोध;
	हाल PERF_RECORD_TEXT_POKE:
		ret += perf_event__ख_लिखो_text_poke(event, machine, fp);
		अवरोध;
	शेष:
		ret += ख_लिखो(fp, "\n");
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक perf_event__process(काष्ठा perf_tool *tool __maybe_unused,
			जोड़ perf_event *event,
			काष्ठा perf_sample *sample,
			काष्ठा machine *machine)
अणु
	वापस machine__process_event(machine, event, sample);
पूर्ण

काष्ठा map *thपढ़ो__find_map(काष्ठा thपढ़ो *thपढ़ो, u8 cpumode, u64 addr,
			     काष्ठा addr_location *al)
अणु
	काष्ठा maps *maps = thपढ़ो->maps;
	काष्ठा machine *machine = maps->machine;
	bool load_map = false;

	al->maps = maps;
	al->thपढ़ो = thपढ़ो;
	al->addr = addr;
	al->cpumode = cpumode;
	al->filtered = 0;

	अगर (machine == शून्य) अणु
		al->map = शून्य;
		वापस शून्य;
	पूर्ण

	अगर (cpumode == PERF_RECORD_MISC_KERNEL && perf_host) अणु
		al->level = 'k';
		al->maps = maps = &machine->kmaps;
		load_map = true;
	पूर्ण अन्यथा अगर (cpumode == PERF_RECORD_MISC_USER && perf_host) अणु
		al->level = '.';
	पूर्ण अन्यथा अगर (cpumode == PERF_RECORD_MISC_GUEST_KERNEL && perf_guest) अणु
		al->level = 'g';
		al->maps = maps = &machine->kmaps;
		load_map = true;
	पूर्ण अन्यथा अगर (cpumode == PERF_RECORD_MISC_GUEST_USER && perf_guest) अणु
		al->level = 'u';
	पूर्ण अन्यथा अणु
		al->level = 'H';
		al->map = शून्य;

		अगर ((cpumode == PERF_RECORD_MISC_GUEST_USER ||
			cpumode == PERF_RECORD_MISC_GUEST_KERNEL) &&
			!perf_guest)
			al->filtered |= (1 << HIST_FILTER__GUEST);
		अगर ((cpumode == PERF_RECORD_MISC_USER ||
			cpumode == PERF_RECORD_MISC_KERNEL) &&
			!perf_host)
			al->filtered |= (1 << HIST_FILTER__HOST);

		वापस शून्य;
	पूर्ण

	al->map = maps__find(maps, al->addr);
	अगर (al->map != शून्य) अणु
		/*
		 * Kernel maps might be changed when loading symbols so loading
		 * must be करोne prior to using kernel maps.
		 */
		अगर (load_map)
			map__load(al->map);
		al->addr = al->map->map_ip(al->map, al->addr);
	पूर्ण

	वापस al->map;
पूर्ण

/*
 * For branch stacks or branch samples, the sample cpumode might not be correct
 * because it applies only to the sample 'ip' and not necessary to 'addr' or
 * branch stack addresses. If possible, use a fallback to deal with those हालs.
 */
काष्ठा map *thपढ़ो__find_map_fb(काष्ठा thपढ़ो *thपढ़ो, u8 cpumode, u64 addr,
				काष्ठा addr_location *al)
अणु
	काष्ठा map *map = thपढ़ो__find_map(thपढ़ो, cpumode, addr, al);
	काष्ठा machine *machine = thपढ़ो->maps->machine;
	u8 addr_cpumode = machine__addr_cpumode(machine, cpumode, addr);

	अगर (map || addr_cpumode == cpumode)
		वापस map;

	वापस thपढ़ो__find_map(thपढ़ो, addr_cpumode, addr, al);
पूर्ण

काष्ठा symbol *thपढ़ो__find_symbol(काष्ठा thपढ़ो *thपढ़ो, u8 cpumode,
				   u64 addr, काष्ठा addr_location *al)
अणु
	al->sym = शून्य;
	अगर (thपढ़ो__find_map(thपढ़ो, cpumode, addr, al))
		al->sym = map__find_symbol(al->map, al->addr);
	वापस al->sym;
पूर्ण

काष्ठा symbol *thपढ़ो__find_symbol_fb(काष्ठा thपढ़ो *thपढ़ो, u8 cpumode,
				      u64 addr, काष्ठा addr_location *al)
अणु
	al->sym = शून्य;
	अगर (thपढ़ो__find_map_fb(thपढ़ो, cpumode, addr, al))
		al->sym = map__find_symbol(al->map, al->addr);
	वापस al->sym;
पूर्ण

अटल bool check_address_range(काष्ठा पूर्णांकlist *addr_list, पूर्णांक addr_range,
				अचिन्हित दीर्घ addr)
अणु
	काष्ठा पूर्णांक_node *pos;

	पूर्णांकlist__क्रम_each_entry(pos, addr_list) अणु
		अगर (addr >= pos->i && addr < pos->i + addr_range)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Callers need to drop the reference to al->thपढ़ो, obtained in
 * machine__findnew_thपढ़ो()
 */
पूर्णांक machine__resolve(काष्ठा machine *machine, काष्ठा addr_location *al,
		     काष्ठा perf_sample *sample)
अणु
	काष्ठा thपढ़ो *thपढ़ो = machine__findnew_thपढ़ो(machine, sample->pid,
							sample->tid);

	अगर (thपढ़ो == शून्य)
		वापस -1;

	dump_म_लिखो(" ... thread: %s:%d\n", thपढ़ो__comm_str(thपढ़ो), thपढ़ो->tid);
	thपढ़ो__find_map(thपढ़ो, sample->cpumode, sample->ip, al);
	dump_म_लिखो(" ...... dso: %s\n",
		    al->map ? al->map->dso->दीर्घ_name :
			al->level == 'H' ? "[hypervisor]" : "<not found>");

	अगर (thपढ़ो__is_filtered(thपढ़ो))
		al->filtered |= (1 << HIST_FILTER__THREAD);

	al->sym = शून्य;
	al->cpu = sample->cpu;
	al->socket = -1;
	al->srcline = शून्य;

	अगर (al->cpu >= 0) अणु
		काष्ठा perf_env *env = machine->env;

		अगर (env && env->cpu)
			al->socket = env->cpu[al->cpu].socket_id;
	पूर्ण

	अगर (al->map) अणु
		काष्ठा dso *dso = al->map->dso;

		अगर (symbol_conf.dso_list &&
		    (!dso || !(strlist__has_entry(symbol_conf.dso_list,
						  dso->लघु_name) ||
			       (dso->लघु_name != dso->दीर्घ_name &&
				strlist__has_entry(symbol_conf.dso_list,
						   dso->दीर्घ_name))))) अणु
			al->filtered |= (1 << HIST_FILTER__DSO);
		पूर्ण

		al->sym = map__find_symbol(al->map, al->addr);
	पूर्ण अन्यथा अगर (symbol_conf.dso_list) अणु
		al->filtered |= (1 << HIST_FILTER__DSO);
	पूर्ण

	अगर (symbol_conf.sym_list) अणु
		पूर्णांक ret = 0;
		अक्षर al_addr_str[32];
		माप_प्रकार sz = माप(al_addr_str);

		अगर (al->sym) अणु
			ret = strlist__has_entry(symbol_conf.sym_list,
						al->sym->name);
		पूर्ण
		अगर (!ret && al->sym) अणु
			snम_लिखो(al_addr_str, sz, "0x%"PRIx64,
				al->map->unmap_ip(al->map, al->sym->start));
			ret = strlist__has_entry(symbol_conf.sym_list,
						al_addr_str);
		पूर्ण
		अगर (!ret && symbol_conf.addr_list && al->map) अणु
			अचिन्हित दीर्घ addr = al->map->unmap_ip(al->map, al->addr);

			ret = पूर्णांकlist__has_entry(symbol_conf.addr_list, addr);
			अगर (!ret && symbol_conf.addr_range) अणु
				ret = check_address_range(symbol_conf.addr_list,
							  symbol_conf.addr_range,
							  addr);
			पूर्ण
		पूर्ण

		अगर (!ret)
			al->filtered |= (1 << HIST_FILTER__SYMBOL);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The preprocess_sample method will वापस with reference counts क्रम the
 * in it, when करोne using (and perhaps getting ref counts अगर needing to
 * keep a poपूर्णांकer to one of those entries) it must be paired with
 * addr_location__put(), so that the refcounts can be decremented.
 */
व्योम addr_location__put(काष्ठा addr_location *al)
अणु
	thपढ़ो__zput(al->thपढ़ो);
पूर्ण

bool is_bts_event(काष्ठा perf_event_attr *attr)
अणु
	वापस attr->type == PERF_TYPE_HARDWARE &&
	       (attr->config & PERF_COUNT_HW_BRANCH_INSTRUCTIONS) &&
	       attr->sample_period == 1;
पूर्ण

bool sample_addr_correlates_sym(काष्ठा perf_event_attr *attr)
अणु
	अगर (attr->type == PERF_TYPE_SOFTWARE &&
	    (attr->config == PERF_COUNT_SW_PAGE_FAULTS ||
	     attr->config == PERF_COUNT_SW_PAGE_FAULTS_MIN ||
	     attr->config == PERF_COUNT_SW_PAGE_FAULTS_MAJ))
		वापस true;

	अगर (is_bts_event(attr))
		वापस true;

	वापस false;
पूर्ण

व्योम thपढ़ो__resolve(काष्ठा thपढ़ो *thपढ़ो, काष्ठा addr_location *al,
		     काष्ठा perf_sample *sample)
अणु
	thपढ़ो__find_map_fb(thपढ़ो, sample->cpumode, sample->addr, al);

	al->cpu = sample->cpu;
	al->sym = शून्य;

	अगर (al->map)
		al->sym = map__find_symbol(al->map, al->addr);
पूर्ण
