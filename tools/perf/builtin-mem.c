<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <पूर्णांकtypes.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश "builtin.h"
#समावेश "perf.h"

#समावेश <subcmd/parse-options.h>
#समावेश "util/auxtrace.h"
#समावेश "util/trace-event.h"
#समावेश "util/tool.h"
#समावेश "util/session.h"
#समावेश "util/data.h"
#समावेश "util/map_symbol.h"
#समावेश "util/mem-events.h"
#समावेश "util/debug.h"
#समावेश "util/dso.h"
#समावेश "util/map.h"
#समावेश "util/symbol.h"
#समावेश <linux/err.h>

#घोषणा MEM_OPERATION_LOAD	0x1
#घोषणा MEM_OPERATION_STORE	0x2

काष्ठा perf_mem अणु
	काष्ठा perf_tool	tool;
	अक्षर स्थिर		*input_name;
	bool			hide_unresolved;
	bool			dump_raw;
	bool			क्रमce;
	bool			phys_addr;
	bool			data_page_size;
	पूर्णांक			operation;
	स्थिर अक्षर		*cpu_list;
	DECLARE_BITMAP(cpu_biपंचांगap, MAX_NR_CPUS);
पूर्ण;

अटल पूर्णांक parse_record_events(स्थिर काष्ठा option *opt,
			       स्थिर अक्षर *str, पूर्णांक unset __maybe_unused)
अणु
	काष्ठा perf_mem *mem = *(काष्ठा perf_mem **)opt->value;

	अगर (!म_भेद(str, "list")) अणु
		perf_mem_events__list();
		निकास(0);
	पूर्ण
	अगर (perf_mem_events__parse(str))
		निकास(-1);

	mem->operation = 0;
	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर __usage[] = अणु
	"perf mem record [<options>] [<command>]",
	"perf mem record [<options>] -- <command> [<options>]",
	शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर *record_mem_usage = __usage;

अटल पूर्णांक __cmd_record(पूर्णांक argc, स्थिर अक्षर **argv, काष्ठा perf_mem *mem)
अणु
	पूर्णांक rec_argc, i = 0, j;
	स्थिर अक्षर **rec_argv;
	पूर्णांक ret;
	bool all_user = false, all_kernel = false;
	काष्ठा perf_mem_event *e;
	काष्ठा option options[] = अणु
	OPT_CALLBACK('e', "event", &mem, "event",
		     "event selector. use 'perf mem record -e list' to list available events",
		     parse_record_events),
	OPT_UINTEGER(0, "ldlat", &perf_mem_events__loads_ldlat, "mem-loads latency"),
	OPT_INCR('v', "verbose", &verbose,
		 "be more verbose (show counter open errors, etc)"),
	OPT_BOOLEAN('U', "all-user", &all_user, "collect only user level data"),
	OPT_BOOLEAN('K', "all-kernel", &all_kernel, "collect only kernel level data"),
	OPT_END()
	पूर्ण;

	अगर (perf_mem_events__init()) अणु
		pr_err("failed: memory events not supported\n");
		वापस -1;
	पूर्ण

	argc = parse_options(argc, argv, options, record_mem_usage,
			     PARSE_OPT_KEEP_UNKNOWN);

	rec_argc = argc + 9; /* max number of arguments */
	rec_argv = सुस्मृति(rec_argc + 1, माप(अक्षर *));
	अगर (!rec_argv)
		वापस -1;

	rec_argv[i++] = "record";

	e = perf_mem_events__ptr(PERF_MEM_EVENTS__LOAD_STORE);

	/*
	 * The load and store operations are required, use the event
	 * PERF_MEM_EVENTS__LOAD_STORE अगर it is supported.
	 */
	अगर (e->tag &&
	    (mem->operation & MEM_OPERATION_LOAD) &&
	    (mem->operation & MEM_OPERATION_STORE)) अणु
		e->record = true;
	पूर्ण अन्यथा अणु
		अगर (mem->operation & MEM_OPERATION_LOAD) अणु
			e = perf_mem_events__ptr(PERF_MEM_EVENTS__LOAD);
			e->record = true;
		पूर्ण

		अगर (mem->operation & MEM_OPERATION_STORE) अणु
			e = perf_mem_events__ptr(PERF_MEM_EVENTS__STORE);
			e->record = true;
		पूर्ण
	पूर्ण

	e = perf_mem_events__ptr(PERF_MEM_EVENTS__LOAD);
	अगर (e->record)
		rec_argv[i++] = "-W";

	rec_argv[i++] = "-d";

	अगर (mem->phys_addr)
		rec_argv[i++] = "--phys-data";

	अगर (mem->data_page_size)
		rec_argv[i++] = "--data-page-size";

	क्रम (j = 0; j < PERF_MEM_EVENTS__MAX; j++) अणु
		e = perf_mem_events__ptr(j);
		अगर (!e->record)
			जारी;

		अगर (!e->supported) अणु
			pr_err("failed: event '%s' not supported\n",
			       perf_mem_events__name(j));
			मुक्त(rec_argv);
			वापस -1;
		पूर्ण

		rec_argv[i++] = "-e";
		rec_argv[i++] = perf_mem_events__name(j);
	पूर्ण

	अगर (all_user)
		rec_argv[i++] = "--all-user";

	अगर (all_kernel)
		rec_argv[i++] = "--all-kernel";

	क्रम (j = 0; j < argc; j++, i++)
		rec_argv[i] = argv[j];

	अगर (verbose > 0) अणु
		pr_debug("calling: record ");

		जबतक (rec_argv[j]) अणु
			pr_debug("%s ", rec_argv[j]);
			j++;
		पूर्ण
		pr_debug("\n");
	पूर्ण

	ret = cmd_record(i, rec_argv);
	मुक्त(rec_argv);
	वापस ret;
पूर्ण

अटल पूर्णांक
dump_raw_samples(काष्ठा perf_tool *tool,
		 जोड़ perf_event *event,
		 काष्ठा perf_sample *sample,
		 काष्ठा machine *machine)
अणु
	काष्ठा perf_mem *mem = container_of(tool, काष्ठा perf_mem, tool);
	काष्ठा addr_location al;
	स्थिर अक्षर *fmt, *field_sep;
	अक्षर str[PAGE_SIZE_NAME_LEN];

	अगर (machine__resolve(machine, &al, sample) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "problem processing %d event, skipping it.\n",
				event->header.type);
		वापस -1;
	पूर्ण

	अगर (al.filtered || (mem->hide_unresolved && al.sym == शून्य))
		जाओ out_put;

	अगर (al.map != शून्य)
		al.map->dso->hit = 1;

	field_sep = symbol_conf.field_sep;
	अगर (field_sep) अणु
		fmt = "%d%s%d%s0x%"PRIx64"%s0x%"PRIx64"%s";
	पूर्ण अन्यथा अणु
		fmt = "%5d%s%5d%s0x%016"PRIx64"%s0x016%"PRIx64"%s";
		symbol_conf.field_sep = " ";
	पूर्ण
	म_लिखो(fmt,
		sample->pid,
		symbol_conf.field_sep,
		sample->tid,
		symbol_conf.field_sep,
		sample->ip,
		symbol_conf.field_sep,
		sample->addr,
		symbol_conf.field_sep);

	अगर (mem->phys_addr) अणु
		म_लिखो("0x%016"PRIx64"%s",
			sample->phys_addr,
			symbol_conf.field_sep);
	पूर्ण

	अगर (mem->data_page_size) अणु
		म_लिखो("%s%s",
			get_page_size_name(sample->data_page_size, str),
			symbol_conf.field_sep);
	पूर्ण

	अगर (field_sep)
		fmt = "%"PRIu64"%s0x%"PRIx64"%s%s:%s\n";
	अन्यथा
		fmt = "%5"PRIu64"%s0x%06"PRIx64"%s%s:%s\n";

	म_लिखो(fmt,
		sample->weight,
		symbol_conf.field_sep,
		sample->data_src,
		symbol_conf.field_sep,
		al.map ? (al.map->dso ? al.map->dso->दीर्घ_name : "???") : "???",
		al.sym ? al.sym->name : "???");
out_put:
	addr_location__put(&al);
	वापस 0;
पूर्ण

अटल पूर्णांक process_sample_event(काष्ठा perf_tool *tool,
				जोड़ perf_event *event,
				काष्ठा perf_sample *sample,
				काष्ठा evsel *evsel __maybe_unused,
				काष्ठा machine *machine)
अणु
	वापस dump_raw_samples(tool, event, sample, machine);
पूर्ण

अटल पूर्णांक report_raw_events(काष्ठा perf_mem *mem)
अणु
	काष्ठा itrace_synth_opts itrace_synth_opts = अणु
		.set = true,
		.mem = true,	/* Only enable memory event */
		.शेष_no_sample = true,
	पूर्ण;

	काष्ठा perf_data data = अणु
		.path  = input_name,
		.mode  = PERF_DATA_MODE_READ,
		.क्रमce = mem->क्रमce,
	पूर्ण;
	पूर्णांक ret;
	काष्ठा perf_session *session = perf_session__new(&data, false,
							 &mem->tool);

	अगर (IS_ERR(session))
		वापस PTR_ERR(session);

	session->itrace_synth_opts = &itrace_synth_opts;

	अगर (mem->cpu_list) अणु
		ret = perf_session__cpu_biपंचांगap(session, mem->cpu_list,
					       mem->cpu_biपंचांगap);
		अगर (ret < 0)
			जाओ out_delete;
	पूर्ण

	ret = symbol__init(&session->header.env);
	अगर (ret < 0)
		जाओ out_delete;

	म_लिखो("# PID, TID, IP, ADDR, ");

	अगर (mem->phys_addr)
		म_लिखो("PHYS ADDR, ");

	अगर (mem->data_page_size)
		म_लिखो("DATA PAGE SIZE, ");

	म_लिखो("LOCAL WEIGHT, DSRC, SYMBOL\n");

	ret = perf_session__process_events(session);

out_delete:
	perf_session__delete(session);
	वापस ret;
पूर्ण
अटल अक्षर *get_sort_order(काष्ठा perf_mem *mem)
अणु
	bool has_extra_options = (mem->phys_addr | mem->data_page_size) ? true : false;
	अक्षर sort[128];

	/*
	 * there is no weight (cost) associated with stores, so करोn't prपूर्णांक
	 * the column
	 */
	अगर (!(mem->operation & MEM_OPERATION_LOAD)) अणु
		म_नकल(sort, "--sort=mem,sym,dso,symbol_daddr,"
			     "dso_daddr,tlb,locked");
	पूर्ण अन्यथा अगर (has_extra_options) अणु
		म_नकल(sort, "--sort=local_weight,mem,sym,dso,symbol_daddr,"
			     "dso_daddr,snoop,tlb,locked,blocked");
	पूर्ण अन्यथा
		वापस शून्य;

	अगर (mem->phys_addr)
		म_जोड़ो(sort, ",phys_daddr");

	अगर (mem->data_page_size)
		म_जोड़ो(sort, ",data_page_size");

	वापस strdup(sort);
पूर्ण

अटल पूर्णांक report_events(पूर्णांक argc, स्थिर अक्षर **argv, काष्ठा perf_mem *mem)
अणु
	स्थिर अक्षर **rep_argv;
	पूर्णांक ret, i = 0, j, rep_argc;
	अक्षर *new_sort_order;

	अगर (mem->dump_raw)
		वापस report_raw_events(mem);

	rep_argc = argc + 3;
	rep_argv = सुस्मृति(rep_argc + 1, माप(अक्षर *));
	अगर (!rep_argv)
		वापस -1;

	rep_argv[i++] = "report";
	rep_argv[i++] = "--mem-mode";
	rep_argv[i++] = "-n"; /* display number of samples */

	new_sort_order = get_sort_order(mem);
	अगर (new_sort_order)
		rep_argv[i++] = new_sort_order;

	क्रम (j = 1; j < argc; j++, i++)
		rep_argv[i] = argv[j];

	ret = cmd_report(i, rep_argv);
	मुक्त(rep_argv);
	वापस ret;
पूर्ण

काष्ठा mem_mode अणु
	स्थिर अक्षर *name;
	पूर्णांक mode;
पूर्ण;

#घोषणा MEM_OPT(n, m) \
	अणु .name = n, .mode = (m) पूर्ण

#घोषणा MEM_END अणु .name = शून्य पूर्ण

अटल स्थिर काष्ठा mem_mode mem_modes[]=अणु
	MEM_OPT("load", MEM_OPERATION_LOAD),
	MEM_OPT("store", MEM_OPERATION_STORE),
	MEM_END
पूर्ण;

अटल पूर्णांक
parse_mem_ops(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset)
अणु
	पूर्णांक *mode = (पूर्णांक *)opt->value;
	स्थिर काष्ठा mem_mode *m;
	अक्षर *s, *os = शून्य, *p;
	पूर्णांक ret = -1;

	अगर (unset)
		वापस 0;

	/* str may be शून्य in हाल no arg is passed to -t */
	अगर (str) अणु
		/* because str is पढ़ो-only */
		s = os = strdup(str);
		अगर (!s)
			वापस -1;

		/* reset mode */
		*mode = 0;

		क्रम (;;) अणु
			p = म_अक्षर(s, ',');
			अगर (p)
				*p = '\0';

			क्रम (m = mem_modes; m->name; m++) अणु
				अगर (!strहालcmp(s, m->name))
					अवरोध;
			पूर्ण
			अगर (!m->name) अणु
				ख_लिखो(मानक_त्रुटि, "unknown sampling op %s,"
					    " check man page\n", s);
				जाओ error;
			पूर्ण

			*mode |= m->mode;

			अगर (!p)
				अवरोध;

			s = p + 1;
		पूर्ण
	पूर्ण
	ret = 0;

	अगर (*mode == 0)
		*mode = MEM_OPERATION_LOAD;
error:
	मुक्त(os);
	वापस ret;
पूर्ण

पूर्णांक cmd_mem(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा stat st;
	काष्ठा perf_mem mem = अणु
		.tool = अणु
			.sample		= process_sample_event,
			.mmap		= perf_event__process_mmap,
			.mmap2		= perf_event__process_mmap2,
			.comm		= perf_event__process_comm,
			.lost		= perf_event__process_lost,
			.विभाजन		= perf_event__process_विभाजन,
			.attr		= perf_event__process_attr,
			.build_id	= perf_event__process_build_id,
			.namespaces	= perf_event__process_namespaces,
			.auxtrace_info  = perf_event__process_auxtrace_info,
			.auxtrace       = perf_event__process_auxtrace,
			.auxtrace_error = perf_event__process_auxtrace_error,
			.ordered_events	= true,
		पूर्ण,
		.input_name		 = "perf.data",
		/*
		 * शेष to both load an store sampling
		 */
		.operation		 = MEM_OPERATION_LOAD | MEM_OPERATION_STORE,
	पूर्ण;
	स्थिर काष्ठा option mem_options[] = अणु
	OPT_CALLBACK('t', "type", &mem.operation,
		   "type", "memory operations(load,store) Default load,store",
		    parse_mem_ops),
	OPT_BOOLEAN('D', "dump-raw-samples", &mem.dump_raw,
		    "dump raw samples in ASCII"),
	OPT_BOOLEAN('U', "hide-unresolved", &स्मृति.सide_unresolved,
		    "Only display entries resolved to a symbol"),
	OPT_STRING('i', "input", &input_name, "file",
		   "input file name"),
	OPT_STRING('C', "cpu", &mem.cpu_list, "cpu",
		   "list of cpus to profile"),
	OPT_STRING_NOEMPTY('x', "field-separator", &symbol_conf.field_sep,
		   "separator",
		   "separator for columns, no spaces will be added"
		   " between columns '.' is reserved."),
	OPT_BOOLEAN('f', "force", &mem.force, "don't complain, करो it"),
	OPT_BOOLEAN('p', "phys-data", &mem.phys_addr, "Record/Report sample physical addresses"),
	OPT_BOOLEAN(0, "data-page-size", &mem.data_page_size, "Record/Report sample data address page size"),
	OPT_END()
	पूर्ण;
	स्थिर अक्षर *स्थिर mem_subcommands[] = अणु "record", "report", शून्य पूर्ण;
	स्थिर अक्षर *mem_usage[] = अणु
		शून्य,
		शून्य
	पूर्ण;

	argc = parse_options_subcommand(argc, argv, mem_options, mem_subcommands,
					mem_usage, PARSE_OPT_KEEP_UNKNOWN);

	अगर (!argc || !(म_भेदन(argv[0], "rec", 3) || mem.operation))
		usage_with_options(mem_usage, mem_options);

	अगर (!mem.input_name || !म_माप(mem.input_name)) अणु
		अगर (!ख_स्थिति(STDIN_खाताNO, &st) && S_ISFIFO(st.st_mode))
			mem.input_name = "-";
		अन्यथा
			mem.input_name = "perf.data";
	पूर्ण

	अगर (!म_भेदन(argv[0], "rec", 3))
		वापस __cmd_record(argc, argv, &mem);
	अन्यथा अगर (!म_भेदन(argv[0], "rep", 3))
		वापस report_events(argc, argv, &mem);
	अन्यथा
		usage_with_options(mem_usage, mem_options);

	वापस 0;
पूर्ण
