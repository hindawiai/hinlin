<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "builtin.h"

#समावेश "util/counts.h"
#समावेश "util/debug.h"
#समावेश "util/dso.h"
#समावेश <subcmd/exec-cmd.h>
#समावेश "util/header.h"
#समावेश <subcmd/parse-options.h>
#समावेश "util/perf_regs.h"
#समावेश "util/session.h"
#समावेश "util/tool.h"
#समावेश "util/map.h"
#समावेश "util/srcline.h"
#समावेश "util/symbol.h"
#समावेश "util/thread.h"
#समावेश "util/trace-event.h"
#समावेश "util/evlist.h"
#समावेश "util/evsel.h"
#समावेश "util/evsel_fprintf.h"
#समावेश "util/evswitch.h"
#समावेश "util/sort.h"
#समावेश "util/data.h"
#समावेश "util/auxtrace.h"
#समावेश "util/cpumap.h"
#समावेश "util/thread_map.h"
#समावेश "util/stat.h"
#समावेश "util/color.h"
#समावेश "util/string2.h"
#समावेश "util/thread-stack.h"
#समावेश "util/time-utils.h"
#समावेश "util/path.h"
#समावेश "util/event.h"
#समावेश "ui/ui.h"
#समावेश "print_binary.h"
#समावेश "archinsn.h"
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/kernel.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/समय64.h>
#समावेश <linux/zभाग.स>
#समावेश <sys/utsname.h>
#समावेश "asm/bug.h"
#समावेश "util/mem-events.h"
#समावेश "util/dump-insn.h"
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <संकेत.स>
#समावेश <sys/param.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <subcmd/pager.h>
#समावेश <perf/evlist.h>
#समावेश <linux/err.h>
#समावेश "util/record.h"
#समावेश "util/util.h"
#समावेश "perf.h"

#समावेश <linux/प्रकार.स>

अटल अक्षर स्थिर		*script_name;
अटल अक्षर स्थिर		*generate_script_lang;
अटल bool			relसमय;
अटल bool			deltaसमय;
अटल u64			initial_समय;
अटल u64			previous_समय;
अटल bool			debug_mode;
अटल u64			last_बारtamp;
अटल u64			nr_unordered;
अटल bool			no_callchain;
अटल bool			latency_क्रमmat;
अटल bool			प्रणाली_wide;
अटल bool			prपूर्णांक_flags;
अटल स्थिर अक्षर		*cpu_list;
अटल DECLARE_BITMAP(cpu_biपंचांगap, MAX_NR_CPUS);
अटल काष्ठा perf_stat_config	stat_config;
अटल पूर्णांक			max_blocks;
अटल bool			native_arch;

अचिन्हित पूर्णांक scripting_max_stack = PERF_MAX_STACK_DEPTH;

क्रमागत perf_output_field अणु
	PERF_OUTPUT_COMM            = 1ULL << 0,
	PERF_OUTPUT_TID             = 1ULL << 1,
	PERF_OUTPUT_PID             = 1ULL << 2,
	PERF_OUTPUT_TIME            = 1ULL << 3,
	PERF_OUTPUT_CPU             = 1ULL << 4,
	PERF_OUTPUT_EVNAME          = 1ULL << 5,
	PERF_OUTPUT_TRACE           = 1ULL << 6,
	PERF_OUTPUT_IP              = 1ULL << 7,
	PERF_OUTPUT_SYM             = 1ULL << 8,
	PERF_OUTPUT_DSO             = 1ULL << 9,
	PERF_OUTPUT_ADDR            = 1ULL << 10,
	PERF_OUTPUT_SYMOFFSET       = 1ULL << 11,
	PERF_OUTPUT_SRCLINE         = 1ULL << 12,
	PERF_OUTPUT_PERIOD          = 1ULL << 13,
	PERF_OUTPUT_IREGS	    = 1ULL << 14,
	PERF_OUTPUT_BRSTACK	    = 1ULL << 15,
	PERF_OUTPUT_BRSTACKSYM	    = 1ULL << 16,
	PERF_OUTPUT_DATA_SRC	    = 1ULL << 17,
	PERF_OUTPUT_WEIGHT	    = 1ULL << 18,
	PERF_OUTPUT_BPF_OUTPUT	    = 1ULL << 19,
	PERF_OUTPUT_CALLINDENT	    = 1ULL << 20,
	PERF_OUTPUT_INSN	    = 1ULL << 21,
	PERF_OUTPUT_INSNLEN	    = 1ULL << 22,
	PERF_OUTPUT_BRSTACKINSN	    = 1ULL << 23,
	PERF_OUTPUT_BRSTACKOFF	    = 1ULL << 24,
	PERF_OUTPUT_SYNTH           = 1ULL << 25,
	PERF_OUTPUT_PHYS_ADDR       = 1ULL << 26,
	PERF_OUTPUT_UREGS	    = 1ULL << 27,
	PERF_OUTPUT_METRIC	    = 1ULL << 28,
	PERF_OUTPUT_MISC            = 1ULL << 29,
	PERF_OUTPUT_SRCCODE	    = 1ULL << 30,
	PERF_OUTPUT_IPC             = 1ULL << 31,
	PERF_OUTPUT_TOD             = 1ULL << 32,
	PERF_OUTPUT_DATA_PAGE_SIZE  = 1ULL << 33,
	PERF_OUTPUT_CODE_PAGE_SIZE  = 1ULL << 34,
पूर्ण;

काष्ठा perf_script अणु
	काष्ठा perf_tool	tool;
	काष्ठा perf_session	*session;
	bool			show_task_events;
	bool			show_mmap_events;
	bool			show_चयन_events;
	bool			show_namespace_events;
	bool			show_lost_events;
	bool			show_round_events;
	bool			show_bpf_events;
	bool			show_cgroup_events;
	bool			show_text_poke_events;
	bool			allocated;
	bool			per_event_dump;
	bool			stitch_lbr;
	काष्ठा evचयन		evचयन;
	काष्ठा perf_cpu_map	*cpus;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
	पूर्णांक			name_width;
	स्थिर अक्षर              *समय_str;
	काष्ठा perf_समय_पूर्णांकerval *pसमय_range;
	पूर्णांक			range_size;
	पूर्णांक			range_num;
पूर्ण;

काष्ठा output_option अणु
	स्थिर अक्षर *str;
	क्रमागत perf_output_field field;
पूर्ण all_output_options[] = अणु
	अणु.str = "comm",  .field = PERF_OUTPUT_COMMपूर्ण,
	अणु.str = "tid",   .field = PERF_OUTPUT_TIDपूर्ण,
	अणु.str = "pid",   .field = PERF_OUTPUT_PIDपूर्ण,
	अणु.str = "time",  .field = PERF_OUTPUT_TIMEपूर्ण,
	अणु.str = "cpu",   .field = PERF_OUTPUT_CPUपूर्ण,
	अणु.str = "event", .field = PERF_OUTPUT_EVNAMEपूर्ण,
	अणु.str = "trace", .field = PERF_OUTPUT_TRACEपूर्ण,
	अणु.str = "ip",    .field = PERF_OUTPUT_IPपूर्ण,
	अणु.str = "sym",   .field = PERF_OUTPUT_SYMपूर्ण,
	अणु.str = "dso",   .field = PERF_OUTPUT_DSOपूर्ण,
	अणु.str = "addr",  .field = PERF_OUTPUT_ADDRपूर्ण,
	अणु.str = "symoff", .field = PERF_OUTPUT_SYMOFFSETपूर्ण,
	अणु.str = "srcline", .field = PERF_OUTPUT_SRCLINEपूर्ण,
	अणु.str = "period", .field = PERF_OUTPUT_PERIODपूर्ण,
	अणु.str = "iregs", .field = PERF_OUTPUT_IREGSपूर्ण,
	अणु.str = "uregs", .field = PERF_OUTPUT_UREGSपूर्ण,
	अणु.str = "brstack", .field = PERF_OUTPUT_BRSTACKपूर्ण,
	अणु.str = "brstacksym", .field = PERF_OUTPUT_BRSTACKSYMपूर्ण,
	अणु.str = "data_src", .field = PERF_OUTPUT_DATA_SRCपूर्ण,
	अणु.str = "weight",   .field = PERF_OUTPUT_WEIGHTपूर्ण,
	अणु.str = "bpf-output",   .field = PERF_OUTPUT_BPF_OUTPUTपूर्ण,
	अणु.str = "callindent", .field = PERF_OUTPUT_CALLINDENTपूर्ण,
	अणु.str = "insn", .field = PERF_OUTPUT_INSNपूर्ण,
	अणु.str = "insnlen", .field = PERF_OUTPUT_INSNLENपूर्ण,
	अणु.str = "brstackinsn", .field = PERF_OUTPUT_BRSTACKINSNपूर्ण,
	अणु.str = "brstackoff", .field = PERF_OUTPUT_BRSTACKOFFपूर्ण,
	अणु.str = "synth", .field = PERF_OUTPUT_SYNTHपूर्ण,
	अणु.str = "phys_addr", .field = PERF_OUTPUT_PHYS_ADDRपूर्ण,
	अणु.str = "metric", .field = PERF_OUTPUT_METRICपूर्ण,
	अणु.str = "misc", .field = PERF_OUTPUT_MISCपूर्ण,
	अणु.str = "srccode", .field = PERF_OUTPUT_SRCCODEपूर्ण,
	अणु.str = "ipc", .field = PERF_OUTPUT_IPCपूर्ण,
	अणु.str = "tod", .field = PERF_OUTPUT_TODपूर्ण,
	अणु.str = "data_page_size", .field = PERF_OUTPUT_DATA_PAGE_SIZEपूर्ण,
	अणु.str = "code_page_size", .field = PERF_OUTPUT_CODE_PAGE_SIZEपूर्ण,
पूर्ण;

क्रमागत अणु
	OUTPUT_TYPE_SYNTH = PERF_TYPE_MAX,
	OUTPUT_TYPE_OTHER,
	OUTPUT_TYPE_MAX
पूर्ण;

/* शेष set to मुख्यtain compatibility with current क्रमmat */
अटल काष्ठा अणु
	bool user_set;
	bool wildcard_set;
	अचिन्हित पूर्णांक prपूर्णांक_ip_opts;
	u64 fields;
	u64 invalid_fields;
	u64 user_set_fields;
	u64 user_unset_fields;
पूर्ण output[OUTPUT_TYPE_MAX] = अणु

	[PERF_TYPE_HARDWARE] = अणु
		.user_set = false,

		.fields = PERF_OUTPUT_COMM | PERF_OUTPUT_TID |
			      PERF_OUTPUT_CPU | PERF_OUTPUT_TIME |
			      PERF_OUTPUT_EVNAME | PERF_OUTPUT_IP |
			      PERF_OUTPUT_SYM | PERF_OUTPUT_SYMOFFSET |
			      PERF_OUTPUT_DSO | PERF_OUTPUT_PERIOD,

		.invalid_fields = PERF_OUTPUT_TRACE | PERF_OUTPUT_BPF_OUTPUT,
	पूर्ण,

	[PERF_TYPE_SOFTWARE] = अणु
		.user_set = false,

		.fields = PERF_OUTPUT_COMM | PERF_OUTPUT_TID |
			      PERF_OUTPUT_CPU | PERF_OUTPUT_TIME |
			      PERF_OUTPUT_EVNAME | PERF_OUTPUT_IP |
			      PERF_OUTPUT_SYM | PERF_OUTPUT_SYMOFFSET |
			      PERF_OUTPUT_DSO | PERF_OUTPUT_PERIOD |
			      PERF_OUTPUT_BPF_OUTPUT,

		.invalid_fields = PERF_OUTPUT_TRACE,
	पूर्ण,

	[PERF_TYPE_TRACEPOINT] = अणु
		.user_set = false,

		.fields = PERF_OUTPUT_COMM | PERF_OUTPUT_TID |
				  PERF_OUTPUT_CPU | PERF_OUTPUT_TIME |
				  PERF_OUTPUT_EVNAME | PERF_OUTPUT_TRACE
	पूर्ण,

	[PERF_TYPE_HW_CACHE] = अणु
		.user_set = false,

		.fields = PERF_OUTPUT_COMM | PERF_OUTPUT_TID |
			      PERF_OUTPUT_CPU | PERF_OUTPUT_TIME |
			      PERF_OUTPUT_EVNAME | PERF_OUTPUT_IP |
			      PERF_OUTPUT_SYM | PERF_OUTPUT_SYMOFFSET |
			      PERF_OUTPUT_DSO | PERF_OUTPUT_PERIOD,

		.invalid_fields = PERF_OUTPUT_TRACE | PERF_OUTPUT_BPF_OUTPUT,
	पूर्ण,

	[PERF_TYPE_RAW] = अणु
		.user_set = false,

		.fields = PERF_OUTPUT_COMM | PERF_OUTPUT_TID |
			      PERF_OUTPUT_CPU | PERF_OUTPUT_TIME |
			      PERF_OUTPUT_EVNAME | PERF_OUTPUT_IP |
			      PERF_OUTPUT_SYM | PERF_OUTPUT_SYMOFFSET |
			      PERF_OUTPUT_DSO | PERF_OUTPUT_PERIOD |
			      PERF_OUTPUT_ADDR | PERF_OUTPUT_DATA_SRC |
			      PERF_OUTPUT_WEIGHT | PERF_OUTPUT_PHYS_ADDR |
			      PERF_OUTPUT_DATA_PAGE_SIZE | PERF_OUTPUT_CODE_PAGE_SIZE,

		.invalid_fields = PERF_OUTPUT_TRACE | PERF_OUTPUT_BPF_OUTPUT,
	पूर्ण,

	[PERF_TYPE_BREAKPOINT] = अणु
		.user_set = false,

		.fields = PERF_OUTPUT_COMM | PERF_OUTPUT_TID |
			      PERF_OUTPUT_CPU | PERF_OUTPUT_TIME |
			      PERF_OUTPUT_EVNAME | PERF_OUTPUT_IP |
			      PERF_OUTPUT_SYM | PERF_OUTPUT_SYMOFFSET |
			      PERF_OUTPUT_DSO | PERF_OUTPUT_PERIOD,

		.invalid_fields = PERF_OUTPUT_TRACE | PERF_OUTPUT_BPF_OUTPUT,
	पूर्ण,

	[OUTPUT_TYPE_SYNTH] = अणु
		.user_set = false,

		.fields = PERF_OUTPUT_COMM | PERF_OUTPUT_TID |
			      PERF_OUTPUT_CPU | PERF_OUTPUT_TIME |
			      PERF_OUTPUT_EVNAME | PERF_OUTPUT_IP |
			      PERF_OUTPUT_SYM | PERF_OUTPUT_SYMOFFSET |
			      PERF_OUTPUT_DSO | PERF_OUTPUT_SYNTH,

		.invalid_fields = PERF_OUTPUT_TRACE | PERF_OUTPUT_BPF_OUTPUT,
	पूर्ण,

	[OUTPUT_TYPE_OTHER] = अणु
		.user_set = false,

		.fields = PERF_OUTPUT_COMM | PERF_OUTPUT_TID |
			      PERF_OUTPUT_CPU | PERF_OUTPUT_TIME |
			      PERF_OUTPUT_EVNAME | PERF_OUTPUT_IP |
			      PERF_OUTPUT_SYM | PERF_OUTPUT_SYMOFFSET |
			      PERF_OUTPUT_DSO | PERF_OUTPUT_PERIOD,

		.invalid_fields = PERF_OUTPUT_TRACE | PERF_OUTPUT_BPF_OUTPUT,
	पूर्ण,
पूर्ण;

काष्ठा evsel_script अणु
       अक्षर *filename;
       खाता *fp;
       u64  samples;
       /* For metric output */
       u64  val;
       पूर्णांक  gnum;
पूर्ण;

अटल अंतरभूत काष्ठा evsel_script *evsel_script(काष्ठा evsel *evsel)
अणु
	वापस (काष्ठा evsel_script *)evsel->priv;
पूर्ण

अटल काष्ठा evsel_script *evsel_script__new(काष्ठा evsel *evsel, काष्ठा perf_data *data)
अणु
	काष्ठा evsel_script *es = zalloc(माप(*es));

	अगर (es != शून्य) अणु
		अगर (aप्र_लिखो(&es->filename, "%s.%s.dump", data->file.path, evsel__name(evsel)) < 0)
			जाओ out_मुक्त;
		es->fp = ख_खोलो(es->filename, "w");
		अगर (es->fp == शून्य)
			जाओ out_मुक्त_filename;
	पूर्ण

	वापस es;
out_मुक्त_filename:
	zमुक्त(&es->filename);
out_मुक्त:
	मुक्त(es);
	वापस शून्य;
पूर्ण

अटल व्योम evsel_script__delete(काष्ठा evsel_script *es)
अणु
	zमुक्त(&es->filename);
	ख_बंद(es->fp);
	es->fp = शून्य;
	मुक्त(es);
पूर्ण

अटल पूर्णांक evsel_script__ख_लिखो(काष्ठा evsel_script *es, खाता *fp)
अणु
	काष्ठा stat st;

	ख_स्थिति(fileno(es->fp), &st);
	वापस ख_लिखो(fp, "[ perf script: Wrote %.3f MB %s (%" PRIu64 " samples) ]\n",
		       st.st_size / 1024.0 / 1024.0, es->filename, es->samples);
पूर्ण

अटल अंतरभूत पूर्णांक output_type(अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल PERF_TYPE_SYNTH:
		वापस OUTPUT_TYPE_SYNTH;
	शेष:
		अगर (type < PERF_TYPE_MAX)
			वापस type;
	पूर्ण

	वापस OUTPUT_TYPE_OTHER;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक attr_type(अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल OUTPUT_TYPE_SYNTH:
		वापस PERF_TYPE_SYNTH;
	शेष:
		वापस type;
	पूर्ण
पूर्ण

अटल bool output_set_by_user(व्योम)
अणु
	पूर्णांक j;
	क्रम (j = 0; j < OUTPUT_TYPE_MAX; ++j) अणु
		अगर (output[j].user_set)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर अक्षर *output_field2str(क्रमागत perf_output_field field)
अणु
	पूर्णांक i, imax = ARRAY_SIZE(all_output_options);
	स्थिर अक्षर *str = "";

	क्रम (i = 0; i < imax; ++i) अणु
		अगर (all_output_options[i].field == field) अणु
			str = all_output_options[i].str;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस str;
पूर्ण

#घोषणा PRINT_FIELD(x)  (output[output_type(attr->type)].fields & PERF_OUTPUT_##x)

अटल पूर्णांक evsel__करो_check_stype(काष्ठा evsel *evsel, u64 sample_type, स्थिर अक्षर *sample_msg,
				 क्रमागत perf_output_field field, bool allow_user_set)
अणु
	काष्ठा perf_event_attr *attr = &evsel->core.attr;
	पूर्णांक type = output_type(attr->type);
	स्थिर अक्षर *evname;

	अगर (attr->sample_type & sample_type)
		वापस 0;

	अगर (output[type].user_set_fields & field) अणु
		अगर (allow_user_set)
			वापस 0;
		evname = evsel__name(evsel);
		pr_err("Samples for '%s' event do not have %s attribute set. "
		       "Cannot print '%s' field.\n",
		       evname, sample_msg, output_field2str(field));
		वापस -1;
	पूर्ण

	/* user did not ask क्रम it explicitly so हटाओ from the शेष list */
	output[type].fields &= ~field;
	evname = evsel__name(evsel);
	pr_debug("Samples for '%s' event do not have %s attribute set. "
		 "Skipping '%s' field.\n",
		 evname, sample_msg, output_field2str(field));

	वापस 0;
पूर्ण

अटल पूर्णांक evsel__check_stype(काष्ठा evsel *evsel, u64 sample_type, स्थिर अक्षर *sample_msg,
			      क्रमागत perf_output_field field)
अणु
	वापस evsel__करो_check_stype(evsel, sample_type, sample_msg, field, false);
पूर्ण

अटल पूर्णांक evsel__check_attr(काष्ठा evsel *evsel, काष्ठा perf_session *session)
अणु
	काष्ठा perf_event_attr *attr = &evsel->core.attr;
	bool allow_user_set;

	अगर (perf_header__has_feat(&session->header, HEADER_STAT))
		वापस 0;

	allow_user_set = perf_header__has_feat(&session->header,
					       HEADER_AUXTRACE);

	अगर (PRINT_FIELD(TRACE) &&
	    !perf_session__has_traces(session, "record -R"))
		वापस -EINVAL;

	अगर (PRINT_FIELD(IP)) अणु
		अगर (evsel__check_stype(evsel, PERF_SAMPLE_IP, "IP", PERF_OUTPUT_IP))
			वापस -EINVAL;
	पूर्ण

	अगर (PRINT_FIELD(ADDR) &&
	    evsel__करो_check_stype(evsel, PERF_SAMPLE_ADDR, "ADDR", PERF_OUTPUT_ADDR, allow_user_set))
		वापस -EINVAL;

	अगर (PRINT_FIELD(DATA_SRC) &&
	    evsel__check_stype(evsel, PERF_SAMPLE_DATA_SRC, "DATA_SRC", PERF_OUTPUT_DATA_SRC))
		वापस -EINVAL;

	अगर (PRINT_FIELD(WEIGHT) &&
	    evsel__check_stype(evsel, PERF_SAMPLE_WEIGHT, "WEIGHT", PERF_OUTPUT_WEIGHT))
		वापस -EINVAL;

	अगर (PRINT_FIELD(SYM) &&
	    !(evsel->core.attr.sample_type & (PERF_SAMPLE_IP|PERF_SAMPLE_ADDR))) अणु
		pr_err("Display of symbols requested but neither sample IP nor "
			   "sample address\navailable. Hence, no addresses to convert "
		       "to symbols.\n");
		वापस -EINVAL;
	पूर्ण
	अगर (PRINT_FIELD(SYMOFFSET) && !PRINT_FIELD(SYM)) अणु
		pr_err("Display of offsets requested but symbol is not"
		       "selected.\n");
		वापस -EINVAL;
	पूर्ण
	अगर (PRINT_FIELD(DSO) &&
	    !(evsel->core.attr.sample_type & (PERF_SAMPLE_IP|PERF_SAMPLE_ADDR))) अणु
		pr_err("Display of DSO requested but no address to convert.\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((PRINT_FIELD(SRCLINE) || PRINT_FIELD(SRCCODE)) && !PRINT_FIELD(IP)) अणु
		pr_err("Display of source line number requested but sample IP is not\n"
		       "selected. Hence, no address to lookup the source line number.\n");
		वापस -EINVAL;
	पूर्ण
	अगर (PRINT_FIELD(BRSTACKINSN) && !allow_user_set &&
	    !(evlist__combined_branch_type(session->evlist) & PERF_SAMPLE_BRANCH_ANY)) अणु
		pr_err("Display of branch stack assembler requested, but non all-branch filter set\n"
		       "Hint: run 'perf record -b ...'\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((PRINT_FIELD(PID) || PRINT_FIELD(TID)) &&
	    evsel__check_stype(evsel, PERF_SAMPLE_TID, "TID", PERF_OUTPUT_TID|PERF_OUTPUT_PID))
		वापस -EINVAL;

	अगर (PRINT_FIELD(TIME) &&
	    evsel__check_stype(evsel, PERF_SAMPLE_TIME, "TIME", PERF_OUTPUT_TIME))
		वापस -EINVAL;

	अगर (PRINT_FIELD(CPU) &&
	    evsel__करो_check_stype(evsel, PERF_SAMPLE_CPU, "CPU", PERF_OUTPUT_CPU, allow_user_set))
		वापस -EINVAL;

	अगर (PRINT_FIELD(IREGS) &&
	    evsel__करो_check_stype(evsel, PERF_SAMPLE_REGS_INTR, "IREGS", PERF_OUTPUT_IREGS, allow_user_set))
		वापस -EINVAL;

	अगर (PRINT_FIELD(UREGS) &&
	    evsel__check_stype(evsel, PERF_SAMPLE_REGS_USER, "UREGS", PERF_OUTPUT_UREGS))
		वापस -EINVAL;

	अगर (PRINT_FIELD(PHYS_ADDR) &&
	    evsel__check_stype(evsel, PERF_SAMPLE_PHYS_ADDR, "PHYS_ADDR", PERF_OUTPUT_PHYS_ADDR))
		वापस -EINVAL;

	अगर (PRINT_FIELD(DATA_PAGE_SIZE) &&
	    evsel__check_stype(evsel, PERF_SAMPLE_DATA_PAGE_SIZE, "DATA_PAGE_SIZE", PERF_OUTPUT_DATA_PAGE_SIZE))
		वापस -EINVAL;

	अगर (PRINT_FIELD(CODE_PAGE_SIZE) &&
	    evsel__check_stype(evsel, PERF_SAMPLE_CODE_PAGE_SIZE, "CODE_PAGE_SIZE", PERF_OUTPUT_CODE_PAGE_SIZE))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम set_prपूर्णांक_ip_opts(काष्ठा perf_event_attr *attr)
अणु
	अचिन्हित पूर्णांक type = output_type(attr->type);

	output[type].prपूर्णांक_ip_opts = 0;
	अगर (PRINT_FIELD(IP))
		output[type].prपूर्णांक_ip_opts |= EVSEL__PRINT_IP;

	अगर (PRINT_FIELD(SYM))
		output[type].prपूर्णांक_ip_opts |= EVSEL__PRINT_SYM;

	अगर (PRINT_FIELD(DSO))
		output[type].prपूर्णांक_ip_opts |= EVSEL__PRINT_DSO;

	अगर (PRINT_FIELD(SYMOFFSET))
		output[type].prपूर्णांक_ip_opts |= EVSEL__PRINT_SYMOFFSET;

	अगर (PRINT_FIELD(SRCLINE))
		output[type].prपूर्णांक_ip_opts |= EVSEL__PRINT_SRCLINE;
पूर्ण

/*
 * verअगरy all user requested events exist and the samples
 * have the expected data
 */
अटल पूर्णांक perf_session__check_output_opt(काष्ठा perf_session *session)
अणु
	bool tod = false;
	अचिन्हित पूर्णांक j;
	काष्ठा evsel *evsel;

	क्रम (j = 0; j < OUTPUT_TYPE_MAX; ++j) अणु
		evsel = perf_session__find_first_evtype(session, attr_type(j));

		/*
		 * even अगर fields is set to 0 (ie., show nothing) event must
		 * exist अगर user explicitly includes it on the command line
		 */
		अगर (!evsel && output[j].user_set && !output[j].wildcard_set &&
		    j != OUTPUT_TYPE_SYNTH) अणु
			pr_err("%s events do not exist. "
			       "Remove corresponding -F option to proceed.\n",
			       event_type(j));
			वापस -1;
		पूर्ण

		अगर (evsel && output[j].fields &&
			evsel__check_attr(evsel, session))
			वापस -1;

		अगर (evsel == शून्य)
			जारी;

		set_prपूर्णांक_ip_opts(&evsel->core.attr);
		tod |= output[j].fields & PERF_OUTPUT_TOD;
	पूर्ण

	अगर (!no_callchain) अणु
		bool use_callchain = false;
		bool not_pipe = false;

		evlist__क्रम_each_entry(session->evlist, evsel) अणु
			not_pipe = true;
			अगर (evsel__has_callchain(evsel)) अणु
				use_callchain = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (not_pipe && !use_callchain)
			symbol_conf.use_callchain = false;
	पूर्ण

	/*
	 * set शेष क्रम tracepoपूर्णांकs to prपूर्णांक symbols only
	 * अगर callchains are present
	 */
	अगर (symbol_conf.use_callchain &&
	    !output[PERF_TYPE_TRACEPOINT].user_set) अणु
		j = PERF_TYPE_TRACEPOINT;

		evlist__क्रम_each_entry(session->evlist, evsel) अणु
			अगर (evsel->core.attr.type != j)
				जारी;

			अगर (evsel__has_callchain(evsel)) अणु
				output[j].fields |= PERF_OUTPUT_IP;
				output[j].fields |= PERF_OUTPUT_SYM;
				output[j].fields |= PERF_OUTPUT_SYMOFFSET;
				output[j].fields |= PERF_OUTPUT_DSO;
				set_prपूर्णांक_ip_opts(&evsel->core.attr);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (tod && !session->header.env.घड़ी.enabled) अणु
		pr_err("Can't provide 'tod' time, missing clock data. "
		       "Please record with -k/--clockid option.\n");
		वापस -1;
	पूर्ण
out:
	वापस 0;
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_regs(काष्ठा regs_dump *regs, uपूर्णांक64_t mask,
				     खाता *fp)
अणु
	अचिन्हित i = 0, r;
	पूर्णांक prपूर्णांकed = 0;

	अगर (!regs || !regs->regs)
		वापस 0;

	prपूर्णांकed += ख_लिखो(fp, " ABI:%" PRIu64 " ", regs->abi);

	क्रम_each_set_bit(r, (अचिन्हित दीर्घ *) &mask, माप(mask) * 8) अणु
		u64 val = regs->regs[i++];
		prपूर्णांकed += ख_लिखो(fp, "%5s:0x%"PRIx64" ", perf_reg_name(r), val);
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

#घोषणा DEFAULT_TOD_FMT "%F %H:%M:%S"

अटल अक्षर*
tod_scnम_लिखो(काष्ठा perf_script *script, अक्षर *buf, पूर्णांक buflen,
	     u64 बारtamp)
अणु
	u64 tod_ns, घड़ीid_ns;
	काष्ठा perf_env *env;
	अचिन्हित दीर्घ nsec;
	काष्ठा पंचांग lसमय;
	अक्षर date[64];
	समय_प्रकार sec;

	buf[0] = '\0';
	अगर (buflen < 64 || !script)
		वापस buf;

	env = &script->session->header.env;
	अगर (!env->घड़ी.enabled) अणु
		scnम_लिखो(buf, buflen, "disabled");
		वापस buf;
	पूर्ण

	घड़ीid_ns = env->घड़ी.घड़ीid_ns;
	tod_ns     = env->घड़ी.tod_ns;

	अगर (बारtamp > घड़ीid_ns)
		tod_ns += बारtamp - घड़ीid_ns;
	अन्यथा
		tod_ns -= घड़ीid_ns - बारtamp;

	sec  = (समय_प्रकार) (tod_ns / NSEC_PER_SEC);
	nsec = tod_ns - sec * NSEC_PER_SEC;

	अगर (स_स्थानीय_r(&sec, &lसमय) == शून्य) अणु
		scnम_लिखो(buf, buflen, "failed");
	पूर्ण अन्यथा अणु
		स_माला(date, माप(date), DEFAULT_TOD_FMT, &lसमय);

		अगर (symbol_conf.nanosecs) अणु
			snम_लिखो(buf, buflen, "%s.%09lu", date, nsec);
		पूर्ण अन्यथा अणु
			snम_लिखो(buf, buflen, "%s.%06lu",
				 date, nsec / NSEC_PER_USEC);
		पूर्ण
	पूर्ण

	वापस buf;
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_iregs(काष्ठा perf_sample *sample,
				      काष्ठा perf_event_attr *attr, खाता *fp)
अणु
	वापस perf_sample__ख_लिखो_regs(&sample->पूर्णांकr_regs,
					 attr->sample_regs_पूर्णांकr, fp);
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_uregs(काष्ठा perf_sample *sample,
				      काष्ठा perf_event_attr *attr, खाता *fp)
अणु
	वापस perf_sample__ख_लिखो_regs(&sample->user_regs,
					 attr->sample_regs_user, fp);
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_start(काष्ठा perf_script *script,
				      काष्ठा perf_sample *sample,
				      काष्ठा thपढ़ो *thपढ़ो,
				      काष्ठा evsel *evsel,
				      u32 type, खाता *fp)
अणु
	काष्ठा perf_event_attr *attr = &evsel->core.attr;
	अचिन्हित दीर्घ secs;
	अचिन्हित दीर्घ दीर्घ nsecs;
	पूर्णांक prपूर्णांकed = 0;
	अक्षर tstr[128];

	अगर (PRINT_FIELD(COMM)) अणु
		स्थिर अक्षर *comm = thपढ़ो ? thपढ़ो__comm_str(thपढ़ो) : ":-1";

		अगर (latency_क्रमmat)
			prपूर्णांकed += ख_लिखो(fp, "%8.8s ", comm);
		अन्यथा अगर (PRINT_FIELD(IP) && evsel__has_callchain(evsel) && symbol_conf.use_callchain)
			prपूर्णांकed += ख_लिखो(fp, "%s ", comm);
		अन्यथा
			prपूर्णांकed += ख_लिखो(fp, "%16s ", comm);
	पूर्ण

	अगर (PRINT_FIELD(PID) && PRINT_FIELD(TID))
		prपूर्णांकed += ख_लिखो(fp, "%5d/%-5d ", sample->pid, sample->tid);
	अन्यथा अगर (PRINT_FIELD(PID))
		prपूर्णांकed += ख_लिखो(fp, "%5d ", sample->pid);
	अन्यथा अगर (PRINT_FIELD(TID))
		prपूर्णांकed += ख_लिखो(fp, "%5d ", sample->tid);

	अगर (PRINT_FIELD(CPU)) अणु
		अगर (latency_क्रमmat)
			prपूर्णांकed += ख_लिखो(fp, "%3d ", sample->cpu);
		अन्यथा
			prपूर्णांकed += ख_लिखो(fp, "[%03d] ", sample->cpu);
	पूर्ण

	अगर (PRINT_FIELD(MISC)) अणु
		पूर्णांक ret = 0;

		#घोषणा has(m) \
			(sample->misc & PERF_RECORD_MISC_##m) == PERF_RECORD_MISC_##m

		अगर (has(KERNEL))
			ret += ख_लिखो(fp, "K");
		अगर (has(USER))
			ret += ख_लिखो(fp, "U");
		अगर (has(HYPERVISOR))
			ret += ख_लिखो(fp, "H");
		अगर (has(GUEST_KERNEL))
			ret += ख_लिखो(fp, "G");
		अगर (has(GUEST_USER))
			ret += ख_लिखो(fp, "g");

		चयन (type) अणु
		हाल PERF_RECORD_MMAP:
		हाल PERF_RECORD_MMAP2:
			अगर (has(MMAP_DATA))
				ret += ख_लिखो(fp, "M");
			अवरोध;
		हाल PERF_RECORD_COMM:
			अगर (has(COMM_EXEC))
				ret += ख_लिखो(fp, "E");
			अवरोध;
		हाल PERF_RECORD_SWITCH:
		हाल PERF_RECORD_SWITCH_CPU_WIDE:
			अगर (has(SWITCH_OUT)) अणु
				ret += ख_लिखो(fp, "S");
				अगर (sample->misc & PERF_RECORD_MISC_SWITCH_OUT_PREEMPT)
					ret += ख_लिखो(fp, "p");
			पूर्ण
		शेष:
			अवरोध;
		पूर्ण

		#अघोषित has

		ret += ख_लिखो(fp, "%*s", 6 - ret, " ");
		prपूर्णांकed += ret;
	पूर्ण

	अगर (PRINT_FIELD(TOD)) अणु
		tod_scnम_लिखो(script, tstr, माप(tstr), sample->समय);
		prपूर्णांकed += ख_लिखो(fp, "%s ", tstr);
	पूर्ण

	अगर (PRINT_FIELD(TIME)) अणु
		u64 t = sample->समय;
		अगर (relसमय) अणु
			अगर (!initial_समय)
				initial_समय = sample->समय;
			t = sample->समय - initial_समय;
		पूर्ण अन्यथा अगर (deltaसमय) अणु
			अगर (previous_समय)
				t = sample->समय - previous_समय;
			अन्यथा अणु
				t = 0;
			पूर्ण
			previous_समय = sample->समय;
		पूर्ण
		nsecs = t;
		secs = nsecs / NSEC_PER_SEC;
		nsecs -= secs * NSEC_PER_SEC;

		अगर (symbol_conf.nanosecs)
			prपूर्णांकed += ख_लिखो(fp, "%5lu.%09llu: ", secs, nsecs);
		अन्यथा अणु
			अक्षर sample_समय[32];
			बारtamp__scnम_लिखो_usec(t, sample_समय, माप(sample_समय));
			prपूर्णांकed += ख_लिखो(fp, "%12s: ", sample_समय);
		पूर्ण
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

अटल अंतरभूत अक्षर
mispred_str(काष्ठा branch_entry *br)
अणु
	अगर (!(br->flags.mispred  || br->flags.predicted))
		वापस '-';

	वापस br->flags.predicted ? 'P' : 'M';
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_brstack(काष्ठा perf_sample *sample,
					काष्ठा thपढ़ो *thपढ़ो,
					काष्ठा perf_event_attr *attr, खाता *fp)
अणु
	काष्ठा branch_stack *br = sample->branch_stack;
	काष्ठा branch_entry *entries = perf_sample__branch_entries(sample);
	काष्ठा addr_location alf, alt;
	u64 i, from, to;
	पूर्णांक prपूर्णांकed = 0;

	अगर (!(br && br->nr))
		वापस 0;

	क्रम (i = 0; i < br->nr; i++) अणु
		from = entries[i].from;
		to   = entries[i].to;

		अगर (PRINT_FIELD(DSO)) अणु
			स_रखो(&alf, 0, माप(alf));
			स_रखो(&alt, 0, माप(alt));
			thपढ़ो__find_map_fb(thपढ़ो, sample->cpumode, from, &alf);
			thपढ़ो__find_map_fb(thपढ़ो, sample->cpumode, to, &alt);
		पूर्ण

		prपूर्णांकed += ख_लिखो(fp, " 0x%"PRIx64, from);
		अगर (PRINT_FIELD(DSO)) अणु
			prपूर्णांकed += ख_लिखो(fp, "(");
			prपूर्णांकed += map__ख_लिखो_dsoname(alf.map, fp);
			prपूर्णांकed += ख_लिखो(fp, ")");
		पूर्ण

		prपूर्णांकed += ख_लिखो(fp, "/0x%"PRIx64, to);
		अगर (PRINT_FIELD(DSO)) अणु
			prपूर्णांकed += ख_लिखो(fp, "(");
			prपूर्णांकed += map__ख_लिखो_dsoname(alt.map, fp);
			prपूर्णांकed += ख_लिखो(fp, ")");
		पूर्ण

		prपूर्णांकed += ख_लिखो(fp, "/%c/%c/%c/%d ",
			mispred_str(entries + i),
			entries[i].flags.in_tx ? 'X' : '-',
			entries[i].flags.पात ? 'A' : '-',
			entries[i].flags.cycles);
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_brstacksym(काष्ठा perf_sample *sample,
					   काष्ठा thपढ़ो *thपढ़ो,
					   काष्ठा perf_event_attr *attr, खाता *fp)
अणु
	काष्ठा branch_stack *br = sample->branch_stack;
	काष्ठा branch_entry *entries = perf_sample__branch_entries(sample);
	काष्ठा addr_location alf, alt;
	u64 i, from, to;
	पूर्णांक prपूर्णांकed = 0;

	अगर (!(br && br->nr))
		वापस 0;

	क्रम (i = 0; i < br->nr; i++) अणु

		स_रखो(&alf, 0, माप(alf));
		स_रखो(&alt, 0, माप(alt));
		from = entries[i].from;
		to   = entries[i].to;

		thपढ़ो__find_symbol_fb(thपढ़ो, sample->cpumode, from, &alf);
		thपढ़ो__find_symbol_fb(thपढ़ो, sample->cpumode, to, &alt);

		prपूर्णांकed += symbol__ख_लिखो_symname_offs(alf.sym, &alf, fp);
		अगर (PRINT_FIELD(DSO)) अणु
			prपूर्णांकed += ख_लिखो(fp, "(");
			prपूर्णांकed += map__ख_लिखो_dsoname(alf.map, fp);
			prपूर्णांकed += ख_लिखो(fp, ")");
		पूर्ण
		prपूर्णांकed += ख_लिखो(fp, "%c", '/');
		prपूर्णांकed += symbol__ख_लिखो_symname_offs(alt.sym, &alt, fp);
		अगर (PRINT_FIELD(DSO)) अणु
			prपूर्णांकed += ख_लिखो(fp, "(");
			prपूर्णांकed += map__ख_लिखो_dsoname(alt.map, fp);
			prपूर्णांकed += ख_लिखो(fp, ")");
		पूर्ण
		prपूर्णांकed += ख_लिखो(fp, "/%c/%c/%c/%d ",
			mispred_str(entries + i),
			entries[i].flags.in_tx ? 'X' : '-',
			entries[i].flags.पात ? 'A' : '-',
			entries[i].flags.cycles);
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_brstackoff(काष्ठा perf_sample *sample,
					   काष्ठा thपढ़ो *thपढ़ो,
					   काष्ठा perf_event_attr *attr, खाता *fp)
अणु
	काष्ठा branch_stack *br = sample->branch_stack;
	काष्ठा branch_entry *entries = perf_sample__branch_entries(sample);
	काष्ठा addr_location alf, alt;
	u64 i, from, to;
	पूर्णांक prपूर्णांकed = 0;

	अगर (!(br && br->nr))
		वापस 0;

	क्रम (i = 0; i < br->nr; i++) अणु

		स_रखो(&alf, 0, माप(alf));
		स_रखो(&alt, 0, माप(alt));
		from = entries[i].from;
		to   = entries[i].to;

		अगर (thपढ़ो__find_map_fb(thपढ़ो, sample->cpumode, from, &alf) &&
		    !alf.map->dso->adjust_symbols)
			from = map__map_ip(alf.map, from);

		अगर (thपढ़ो__find_map_fb(thपढ़ो, sample->cpumode, to, &alt) &&
		    !alt.map->dso->adjust_symbols)
			to = map__map_ip(alt.map, to);

		prपूर्णांकed += ख_लिखो(fp, " 0x%"PRIx64, from);
		अगर (PRINT_FIELD(DSO)) अणु
			prपूर्णांकed += ख_लिखो(fp, "(");
			prपूर्णांकed += map__ख_लिखो_dsoname(alf.map, fp);
			prपूर्णांकed += ख_लिखो(fp, ")");
		पूर्ण
		prपूर्णांकed += ख_लिखो(fp, "/0x%"PRIx64, to);
		अगर (PRINT_FIELD(DSO)) अणु
			prपूर्णांकed += ख_लिखो(fp, "(");
			prपूर्णांकed += map__ख_लिखो_dsoname(alt.map, fp);
			prपूर्णांकed += ख_लिखो(fp, ")");
		पूर्ण
		prपूर्णांकed += ख_लिखो(fp, "/%c/%c/%c/%d ",
			mispred_str(entries + i),
			entries[i].flags.in_tx ? 'X' : '-',
			entries[i].flags.पात ? 'A' : '-',
			entries[i].flags.cycles);
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण
#घोषणा MAXBB 16384UL

अटल पूर्णांक grab_bb(u8 *buffer, u64 start, u64 end,
		    काष्ठा machine *machine, काष्ठा thपढ़ो *thपढ़ो,
		    bool *is64bit, u8 *cpumode, bool last)
अणु
	दीर्घ offset, len;
	काष्ठा addr_location al;
	bool kernel;

	अगर (!start || !end)
		वापस 0;

	kernel = machine__kernel_ip(machine, start);
	अगर (kernel)
		*cpumode = PERF_RECORD_MISC_KERNEL;
	अन्यथा
		*cpumode = PERF_RECORD_MISC_USER;

	/*
	 * Block overlaps between kernel and user.
	 * This can happen due to ring filtering
	 * On Intel CPUs the entry पूर्णांकo the kernel is filtered,
	 * but the निकास is not. Let the caller patch it up.
	 */
	अगर (kernel != machine__kernel_ip(machine, end)) अणु
		pr_debug("\tblock %" PRIx64 "-%" PRIx64 " transfers between kernel and user\n", start, end);
		वापस -ENXIO;
	पूर्ण

	स_रखो(&al, 0, माप(al));
	अगर (end - start > MAXBB - MAXINSN) अणु
		अगर (last)
			pr_debug("\tbrstack does not reach to final jump (%" PRIx64 "-%" PRIx64 ")\n", start, end);
		अन्यथा
			pr_debug("\tblock %" PRIx64 "-%" PRIx64 " (%" PRIu64 ") too long to dump\n", start, end, end - start);
		वापस 0;
	पूर्ण

	अगर (!thपढ़ो__find_map(thपढ़ो, *cpumode, start, &al) || !al.map->dso) अणु
		pr_debug("\tcannot resolve %" PRIx64 "-%" PRIx64 "\n", start, end);
		वापस 0;
	पूर्ण
	अगर (al.map->dso->data.status == DSO_DATA_STATUS_ERROR) अणु
		pr_debug("\tcannot resolve %" PRIx64 "-%" PRIx64 "\n", start, end);
		वापस 0;
	पूर्ण

	/* Load maps to ensure dso->is_64_bit has been updated */
	map__load(al.map);

	offset = al.map->map_ip(al.map, start);
	len = dso__data_पढ़ो_offset(al.map->dso, machine, offset, (u8 *)buffer,
				    end - start + MAXINSN);

	*is64bit = al.map->dso->is_64_bit;
	अगर (len <= 0)
		pr_debug("\tcannot fetch code for block at %" PRIx64 "-%" PRIx64 "\n",
			start, end);
	वापस len;
पूर्ण

अटल पूर्णांक map__ख_लिखो_srccode(काष्ठा map *map, u64 addr, खाता *fp, काष्ठा srccode_state *state)
अणु
	अक्षर *srcfile;
	पूर्णांक ret = 0;
	अचिन्हित line;
	पूर्णांक len;
	अक्षर *srccode;

	अगर (!map || !map->dso)
		वापस 0;
	srcfile = get_srcline_split(map->dso,
				    map__rip_2objdump(map, addr),
				    &line);
	अगर (!srcfile)
		वापस 0;

	/* Aव्योम redundant prपूर्णांकing */
	अगर (state &&
	    state->srcfile &&
	    !म_भेद(state->srcfile, srcfile) &&
	    state->line == line) अणु
		मुक्त(srcfile);
		वापस 0;
	पूर्ण

	srccode = find_sourceline(srcfile, line, &len);
	अगर (!srccode)
		जाओ out_मुक्त_line;

	ret = ख_लिखो(fp, "|%-8d %.*s", line, len, srccode);

	अगर (state) अणु
		state->srcfile = srcfile;
		state->line = line;
	पूर्ण
	वापस ret;

out_मुक्त_line:
	मुक्त(srcfile);
	वापस ret;
पूर्ण

अटल पूर्णांक prपूर्णांक_srccode(काष्ठा thपढ़ो *thपढ़ो, u8 cpumode, uपूर्णांक64_t addr)
अणु
	काष्ठा addr_location al;
	पूर्णांक ret = 0;

	स_रखो(&al, 0, माप(al));
	thपढ़ो__find_map(thपढ़ो, cpumode, addr, &al);
	अगर (!al.map)
		वापस 0;
	ret = map__ख_लिखो_srccode(al.map, al.addr, मानक_निकास,
		    &thपढ़ो->srccode_state);
	अगर (ret)
		ret += म_लिखो("\n");
	वापस ret;
पूर्ण

अटल पूर्णांक ip__ख_लिखो_jump(uपूर्णांक64_t ip, काष्ठा branch_entry *en,
			    काष्ठा perf_insn *x, u8 *inbuf, पूर्णांक len,
			    पूर्णांक insn, खाता *fp, पूर्णांक *total_cycles)
अणु
	पूर्णांक prपूर्णांकed = ख_लिखो(fp, "\t%016" PRIx64 "\t%-30s\t#%s%s%s%s", ip,
			      dump_insn(x, ip, inbuf, len, शून्य),
			      en->flags.predicted ? " PRED" : "",
			      en->flags.mispred ? " MISPRED" : "",
			      en->flags.in_tx ? " INTX" : "",
			      en->flags.पात ? " ABORT" : "");
	अगर (en->flags.cycles) अणु
		*total_cycles += en->flags.cycles;
		prपूर्णांकed += ख_लिखो(fp, " %d cycles [%d]", en->flags.cycles, *total_cycles);
		अगर (insn)
			prपूर्णांकed += ख_लिखो(fp, " %.2f IPC", (भग्न)insn / en->flags.cycles);
	पूर्ण
	वापस prपूर्णांकed + ख_लिखो(fp, "\n");
पूर्ण

अटल पूर्णांक ip__ख_लिखो_sym(uपूर्णांक64_t addr, काष्ठा thपढ़ो *thपढ़ो,
			   u8 cpumode, पूर्णांक cpu, काष्ठा symbol **lastsym,
			   काष्ठा perf_event_attr *attr, खाता *fp)
अणु
	काष्ठा addr_location al;
	पूर्णांक off, prपूर्णांकed = 0;

	स_रखो(&al, 0, माप(al));

	thपढ़ो__find_map(thपढ़ो, cpumode, addr, &al);

	अगर ((*lastsym) && al.addr >= (*lastsym)->start && al.addr < (*lastsym)->end)
		वापस 0;

	al.cpu = cpu;
	al.sym = शून्य;
	अगर (al.map)
		al.sym = map__find_symbol(al.map, al.addr);

	अगर (!al.sym)
		वापस 0;

	अगर (al.addr < al.sym->end)
		off = al.addr - al.sym->start;
	अन्यथा
		off = al.addr - al.map->start - al.sym->start;
	prपूर्णांकed += ख_लिखो(fp, "\t%s", al.sym->name);
	अगर (off)
		prपूर्णांकed += ख_लिखो(fp, "%+d", off);
	prपूर्णांकed += ख_लिखो(fp, ":");
	अगर (PRINT_FIELD(SRCLINE))
		prपूर्णांकed += map__ख_लिखो_srcline(al.map, al.addr, "\t", fp);
	prपूर्णांकed += ख_लिखो(fp, "\n");
	*lastsym = al.sym;

	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_brstackinsn(काष्ठा perf_sample *sample,
					    काष्ठा thपढ़ो *thपढ़ो,
					    काष्ठा perf_event_attr *attr,
					    काष्ठा machine *machine, खाता *fp)
अणु
	काष्ठा branch_stack *br = sample->branch_stack;
	काष्ठा branch_entry *entries = perf_sample__branch_entries(sample);
	u64 start, end;
	पूर्णांक i, insn, len, nr, ilen, prपूर्णांकed = 0;
	काष्ठा perf_insn x;
	u8 buffer[MAXBB];
	अचिन्हित off;
	काष्ठा symbol *lastsym = शून्य;
	पूर्णांक total_cycles = 0;

	अगर (!(br && br->nr))
		वापस 0;
	nr = br->nr;
	अगर (max_blocks && nr > max_blocks + 1)
		nr = max_blocks + 1;

	x.thपढ़ो = thपढ़ो;
	x.cpu = sample->cpu;

	prपूर्णांकed += ख_लिखो(fp, "%c", '\n');

	/* Handle first from jump, of which we करोn't know the entry. */
	len = grab_bb(buffer, entries[nr-1].from,
			entries[nr-1].from,
			machine, thपढ़ो, &x.is64bit, &x.cpumode, false);
	अगर (len > 0) अणु
		prपूर्णांकed += ip__ख_लिखो_sym(entries[nr - 1].from, thपढ़ो,
					   x.cpumode, x.cpu, &lastsym, attr, fp);
		prपूर्णांकed += ip__ख_लिखो_jump(entries[nr - 1].from, &entries[nr - 1],
					    &x, buffer, len, 0, fp, &total_cycles);
		अगर (PRINT_FIELD(SRCCODE))
			prपूर्णांकed += prपूर्णांक_srccode(thपढ़ो, x.cpumode, entries[nr - 1].from);
	पूर्ण

	/* Prपूर्णांक all blocks */
	क्रम (i = nr - 2; i >= 0; i--) अणु
		अगर (entries[i].from || entries[i].to)
			pr_debug("%d: %" PRIx64 "-%" PRIx64 "\n", i,
				 entries[i].from,
				 entries[i].to);
		start = entries[i + 1].to;
		end   = entries[i].from;

		len = grab_bb(buffer, start, end, machine, thपढ़ो, &x.is64bit, &x.cpumode, false);
		/* Patch up missing kernel transfers due to ring filters */
		अगर (len == -ENXIO && i > 0) अणु
			end = entries[--i].from;
			pr_debug("\tpatching up to %" PRIx64 "-%" PRIx64 "\n", start, end);
			len = grab_bb(buffer, start, end, machine, thपढ़ो, &x.is64bit, &x.cpumode, false);
		पूर्ण
		अगर (len <= 0)
			जारी;

		insn = 0;
		क्रम (off = 0; off < (अचिन्हित)len; off += ilen) अणु
			uपूर्णांक64_t ip = start + off;

			prपूर्णांकed += ip__ख_लिखो_sym(ip, thपढ़ो, x.cpumode, x.cpu, &lastsym, attr, fp);
			अगर (ip == end) अणु
				prपूर्णांकed += ip__ख_लिखो_jump(ip, &entries[i], &x, buffer + off, len - off, ++insn, fp,
							    &total_cycles);
				अगर (PRINT_FIELD(SRCCODE))
					prपूर्णांकed += prपूर्णांक_srccode(thपढ़ो, x.cpumode, ip);
				अवरोध;
			पूर्ण अन्यथा अणु
				ilen = 0;
				prपूर्णांकed += ख_लिखो(fp, "\t%016" PRIx64 "\t%s\n", ip,
						   dump_insn(&x, ip, buffer + off, len - off, &ilen));
				अगर (ilen == 0)
					अवरोध;
				अगर (PRINT_FIELD(SRCCODE))
					prपूर्णांक_srccode(thपढ़ो, x.cpumode, ip);
				insn++;
			पूर्ण
		पूर्ण
		अगर (off != end - start)
			prपूर्णांकed += ख_लिखो(fp, "\tmismatch of LBR data and executable\n");
	पूर्ण

	/*
	 * Hit the branch? In this हाल we are alपढ़ोy करोne, and the target
	 * has not been executed yet.
	 */
	अगर (entries[0].from == sample->ip)
		जाओ out;
	अगर (entries[0].flags.पात)
		जाओ out;

	/*
	 * Prपूर्णांक final block upto sample
	 *
	 * Due to pipeline delays the LBRs might be missing a branch
	 * or two, which can result in very large or negative blocks
	 * between final branch and sample. When this happens just
	 * जारी walking after the last TO until we hit a branch.
	 */
	start = entries[0].to;
	end = sample->ip;
	अगर (end < start) अणु
		/* Missing jump. Scan 128 bytes क्रम the next branch */
		end = start + 128;
	पूर्ण
	len = grab_bb(buffer, start, end, machine, thपढ़ो, &x.is64bit, &x.cpumode, true);
	prपूर्णांकed += ip__ख_लिखो_sym(start, thपढ़ो, x.cpumode, x.cpu, &lastsym, attr, fp);
	अगर (len <= 0) अणु
		/* Prपूर्णांक at least last IP अगर basic block did not work */
		len = grab_bb(buffer, sample->ip, sample->ip,
			      machine, thपढ़ो, &x.is64bit, &x.cpumode, false);
		अगर (len <= 0)
			जाओ out;
		prपूर्णांकed += ख_लिखो(fp, "\t%016" PRIx64 "\t%s\n", sample->ip,
			dump_insn(&x, sample->ip, buffer, len, शून्य));
		अगर (PRINT_FIELD(SRCCODE))
			prपूर्णांक_srccode(thपढ़ो, x.cpumode, sample->ip);
		जाओ out;
	पूर्ण
	क्रम (off = 0; off <= end - start; off += ilen) अणु
		ilen = 0;
		prपूर्णांकed += ख_लिखो(fp, "\t%016" PRIx64 "\t%s\n", start + off,
				   dump_insn(&x, start + off, buffer + off, len - off, &ilen));
		अगर (ilen == 0)
			अवरोध;
		अगर (arch_is_branch(buffer + off, len - off, x.is64bit) && start + off != sample->ip) अणु
			/*
			 * Hit a missing branch. Just stop.
			 */
			prपूर्णांकed += ख_लिखो(fp, "\t... not reaching sample ...\n");
			अवरोध;
		पूर्ण
		अगर (PRINT_FIELD(SRCCODE))
			prपूर्णांक_srccode(thपढ़ो, x.cpumode, start + off);
	पूर्ण
out:
	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_addr(काष्ठा perf_sample *sample,
				     काष्ठा thपढ़ो *thपढ़ो,
				     काष्ठा perf_event_attr *attr, खाता *fp)
अणु
	काष्ठा addr_location al;
	पूर्णांक prपूर्णांकed = ख_लिखो(fp, "%16" PRIx64, sample->addr);

	अगर (!sample_addr_correlates_sym(attr))
		जाओ out;

	thपढ़ो__resolve(thपढ़ो, &al, sample);

	अगर (PRINT_FIELD(SYM)) अणु
		prपूर्णांकed += ख_लिखो(fp, " ");
		अगर (PRINT_FIELD(SYMOFFSET))
			prपूर्णांकed += symbol__ख_लिखो_symname_offs(al.sym, &al, fp);
		अन्यथा
			prपूर्णांकed += symbol__ख_लिखो_symname(al.sym, fp);
	पूर्ण

	अगर (PRINT_FIELD(DSO)) अणु
		prपूर्णांकed += ख_लिखो(fp, " (");
		prपूर्णांकed += map__ख_लिखो_dsoname(al.map, fp);
		prपूर्णांकed += ख_लिखो(fp, ")");
	पूर्ण
out:
	वापस prपूर्णांकed;
पूर्ण

अटल स्थिर अक्षर *resolve_branch_sym(काष्ठा perf_sample *sample,
				      काष्ठा evsel *evsel,
				      काष्ठा thपढ़ो *thपढ़ो,
				      काष्ठा addr_location *al,
				      u64 *ip)
अणु
	काष्ठा addr_location addr_al;
	काष्ठा perf_event_attr *attr = &evsel->core.attr;
	स्थिर अक्षर *name = शून्य;

	अगर (sample->flags & (PERF_IP_FLAG_CALL | PERF_IP_FLAG_TRACE_BEGIN)) अणु
		अगर (sample_addr_correlates_sym(attr)) अणु
			thपढ़ो__resolve(thपढ़ो, &addr_al, sample);
			अगर (addr_al.sym)
				name = addr_al.sym->name;
			अन्यथा
				*ip = sample->addr;
		पूर्ण अन्यथा अणु
			*ip = sample->addr;
		पूर्ण
	पूर्ण अन्यथा अगर (sample->flags & (PERF_IP_FLAG_RETURN | PERF_IP_FLAG_TRACE_END)) अणु
		अगर (al->sym)
			name = al->sym->name;
		अन्यथा
			*ip = sample->ip;
	पूर्ण
	वापस name;
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_callindent(काष्ठा perf_sample *sample,
					   काष्ठा evsel *evsel,
					   काष्ठा thपढ़ो *thपढ़ो,
					   काष्ठा addr_location *al, खाता *fp)
अणु
	काष्ठा perf_event_attr *attr = &evsel->core.attr;
	माप_प्रकार depth = thपढ़ो_stack__depth(thपढ़ो, sample->cpu);
	स्थिर अक्षर *name = शून्य;
	अटल पूर्णांक spacing;
	पूर्णांक len = 0;
	पूर्णांक dlen = 0;
	u64 ip = 0;

	/*
	 * The 'return' has alपढ़ोy been popped off the stack so the depth has
	 * to be adjusted to match the 'call'.
	 */
	अगर (thपढ़ो->ts && sample->flags & PERF_IP_FLAG_RETURN)
		depth += 1;

	name = resolve_branch_sym(sample, evsel, thपढ़ो, al, &ip);

	अगर (PRINT_FIELD(DSO) && !(PRINT_FIELD(IP) || PRINT_FIELD(ADDR))) अणु
		dlen += ख_लिखो(fp, "(");
		dlen += map__ख_लिखो_dsoname(al->map, fp);
		dlen += ख_लिखो(fp, ")\t");
	पूर्ण

	अगर (name)
		len = ख_लिखो(fp, "%*s%s", (पूर्णांक)depth * 4, "", name);
	अन्यथा अगर (ip)
		len = ख_लिखो(fp, "%*s%16" PRIx64, (पूर्णांक)depth * 4, "", ip);

	अगर (len < 0)
		वापस len;

	/*
	 * Try to keep the output length from changing frequently so that the
	 * output lines up more nicely.
	 */
	अगर (len > spacing || (len && len < spacing - 52))
		spacing = round_up(len + 4, 32);

	अगर (len < spacing)
		len += ख_लिखो(fp, "%*s", spacing - len, "");

	वापस len + dlen;
पूर्ण

__weak व्योम arch_fetch_insn(काष्ठा perf_sample *sample __maybe_unused,
			    काष्ठा thपढ़ो *thपढ़ो __maybe_unused,
			    काष्ठा machine *machine __maybe_unused)
अणु
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_insn(काष्ठा perf_sample *sample,
				     काष्ठा perf_event_attr *attr,
				     काष्ठा thपढ़ो *thपढ़ो,
				     काष्ठा machine *machine, खाता *fp)
अणु
	पूर्णांक prपूर्णांकed = 0;

	अगर (sample->insn_len == 0 && native_arch)
		arch_fetch_insn(sample, thपढ़ो, machine);

	अगर (PRINT_FIELD(INSNLEN))
		prपूर्णांकed += ख_लिखो(fp, " ilen: %d", sample->insn_len);
	अगर (PRINT_FIELD(INSN) && sample->insn_len) अणु
		पूर्णांक i;

		prपूर्णांकed += ख_लिखो(fp, " insn:");
		क्रम (i = 0; i < sample->insn_len; i++)
			prपूर्णांकed += ख_लिखो(fp, " %02x", (अचिन्हित अक्षर)sample->insn[i]);
	पूर्ण
	अगर (PRINT_FIELD(BRSTACKINSN))
		prपूर्णांकed += perf_sample__ख_लिखो_brstackinsn(sample, thपढ़ो, attr, machine, fp);

	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_ipc(काष्ठा perf_sample *sample,
				    काष्ठा perf_event_attr *attr, खाता *fp)
अणु
	अचिन्हित पूर्णांक ipc;

	अगर (!PRINT_FIELD(IPC) || !sample->cyc_cnt || !sample->insn_cnt)
		वापस 0;

	ipc = (sample->insn_cnt * 100) / sample->cyc_cnt;

	वापस ख_लिखो(fp, " \t IPC: %u.%02u (%" PRIu64 "/%" PRIu64 ") ",
		       ipc / 100, ipc % 100, sample->insn_cnt, sample->cyc_cnt);
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_bts(काष्ठा perf_sample *sample,
				    काष्ठा evsel *evsel,
				    काष्ठा thपढ़ो *thपढ़ो,
				    काष्ठा addr_location *al,
				    काष्ठा machine *machine, खाता *fp)
अणु
	काष्ठा perf_event_attr *attr = &evsel->core.attr;
	अचिन्हित पूर्णांक type = output_type(attr->type);
	bool prपूर्णांक_srcline_last = false;
	पूर्णांक prपूर्णांकed = 0;

	अगर (PRINT_FIELD(CALLINDENT))
		prपूर्णांकed += perf_sample__ख_लिखो_callindent(sample, evsel, thपढ़ो, al, fp);

	/* prपूर्णांक branch_from inक्रमmation */
	अगर (PRINT_FIELD(IP)) अणु
		अचिन्हित पूर्णांक prपूर्णांक_opts = output[type].prपूर्णांक_ip_opts;
		काष्ठा callchain_cursor *cursor = शून्य;

		अगर (symbol_conf.use_callchain && sample->callchain &&
		    thपढ़ो__resolve_callchain(al->thपढ़ो, &callchain_cursor, evsel,
					      sample, शून्य, शून्य, scripting_max_stack) == 0)
			cursor = &callchain_cursor;

		अगर (cursor == शून्य) अणु
			prपूर्णांकed += ख_लिखो(fp, " ");
			अगर (prपूर्णांक_opts & EVSEL__PRINT_SRCLINE) अणु
				prपूर्णांक_srcline_last = true;
				prपूर्णांक_opts &= ~EVSEL__PRINT_SRCLINE;
			पूर्ण
		पूर्ण अन्यथा
			prपूर्णांकed += ख_लिखो(fp, "\n");

		prपूर्णांकed += sample__ख_लिखो_sym(sample, al, 0, prपूर्णांक_opts, cursor,
					       symbol_conf.bt_stop_list, fp);
	पूर्ण

	/* prपूर्णांक branch_to inक्रमmation */
	अगर (PRINT_FIELD(ADDR) ||
	    ((evsel->core.attr.sample_type & PERF_SAMPLE_ADDR) &&
	     !output[type].user_set)) अणु
		prपूर्णांकed += ख_लिखो(fp, " => ");
		prपूर्णांकed += perf_sample__ख_लिखो_addr(sample, thपढ़ो, attr, fp);
	पूर्ण

	prपूर्णांकed += perf_sample__ख_लिखो_ipc(sample, attr, fp);

	अगर (prपूर्णांक_srcline_last)
		prपूर्णांकed += map__ख_लिखो_srcline(al->map, al->addr, "\n  ", fp);

	prपूर्णांकed += perf_sample__ख_लिखो_insn(sample, attr, thपढ़ो, machine, fp);
	prपूर्णांकed += ख_लिखो(fp, "\n");
	अगर (PRINT_FIELD(SRCCODE)) अणु
		पूर्णांक ret = map__ख_लिखो_srccode(al->map, al->addr, मानक_निकास,
					 &thपढ़ो->srccode_state);
		अगर (ret) अणु
			prपूर्णांकed += ret;
			prपूर्णांकed += म_लिखो("\n");
		पूर्ण
	पूर्ण
	वापस prपूर्णांकed;
पूर्ण

अटल काष्ठा अणु
	u32 flags;
	स्थिर अक्षर *name;
पूर्ण sample_flags[] = अणु
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL, "call"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_RETURN, "return"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CONDITIONAL, "jcc"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH, "jmp"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL | PERF_IP_FLAG_INTERRUPT, "int"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_RETURN | PERF_IP_FLAG_INTERRUPT, "iret"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL | PERF_IP_FLAG_SYSCALLRET, "syscall"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_RETURN | PERF_IP_FLAG_SYSCALLRET, "sysret"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_ASYNC, "async"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL | PERF_IP_FLAG_ASYNC |	PERF_IP_FLAG_INTERRUPT, "hw int"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_TX_ABORT, "tx abrt"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_TRACE_BEGIN, "tr strt"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_TRACE_END, "tr end"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL | PERF_IP_FLAG_VMENTRY, "vmentry"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL | PERF_IP_FLAG_VMEXIT, "vmexit"पूर्ण,
	अणु0, शून्यपूर्ण
पूर्ण;

अटल स्थिर अक्षर *sample_flags_to_name(u32 flags)
अणु
	पूर्णांक i;

	क्रम (i = 0; sample_flags[i].name ; i++) अणु
		अगर (sample_flags[i].flags == flags)
			वापस sample_flags[i].name;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_flags(u32 flags, खाता *fp)
अणु
	स्थिर अक्षर *अक्षरs = PERF_IP_FLAG_CHARS;
	स्थिर पूर्णांक n = म_माप(PERF_IP_FLAG_CHARS);
	bool in_tx = flags & PERF_IP_FLAG_IN_TX;
	स्थिर अक्षर *name = शून्य;
	अक्षर str[33];
	पूर्णांक i, pos = 0;

	name = sample_flags_to_name(flags & ~PERF_IP_FLAG_IN_TX);
	अगर (name)
		वापस ख_लिखो(fp, "  %-15s%4s ", name, in_tx ? "(x)" : "");

	अगर (flags & PERF_IP_FLAG_TRACE_BEGIN) अणु
		name = sample_flags_to_name(flags & ~(PERF_IP_FLAG_IN_TX | PERF_IP_FLAG_TRACE_BEGIN));
		अगर (name)
			वापस ख_लिखो(fp, "  tr strt %-7s%4s ", name, in_tx ? "(x)" : "");
	पूर्ण

	अगर (flags & PERF_IP_FLAG_TRACE_END) अणु
		name = sample_flags_to_name(flags & ~(PERF_IP_FLAG_IN_TX | PERF_IP_FLAG_TRACE_END));
		अगर (name)
			वापस ख_लिखो(fp, "  tr end  %-7s%4s ", name, in_tx ? "(x)" : "");
	पूर्ण

	क्रम (i = 0; i < n; i++, flags >>= 1) अणु
		अगर (flags & 1)
			str[pos++] = अक्षरs[i];
	पूर्ण
	क्रम (; i < 32; i++, flags >>= 1) अणु
		अगर (flags & 1)
			str[pos++] = '?';
	पूर्ण
	str[pos] = 0;

	वापस ख_लिखो(fp, "  %-19s ", str);
पूर्ण

काष्ठा prपूर्णांकer_data अणु
	पूर्णांक line_no;
	bool hit_nul;
	bool is_prपूर्णांकable;
पूर्ण;

अटल पूर्णांक sample__ख_लिखो_bpf_output(क्रमागत binary_prपूर्णांकer_ops op,
				      अचिन्हित पूर्णांक val,
				      व्योम *extra, खाता *fp)
अणु
	अचिन्हित अक्षर ch = (अचिन्हित अक्षर)val;
	काष्ठा prपूर्णांकer_data *prपूर्णांकer_data = extra;
	पूर्णांक prपूर्णांकed = 0;

	चयन (op) अणु
	हाल BINARY_PRINT_DATA_BEGIN:
		prपूर्णांकed += ख_लिखो(fp, "\n");
		अवरोध;
	हाल BINARY_PRINT_LINE_BEGIN:
		prपूर्णांकed += ख_लिखो(fp, "%17s", !prपूर्णांकer_data->line_no ? "BPF output:" :
						        "           ");
		अवरोध;
	हाल BINARY_PRINT_ADDR:
		prपूर्णांकed += ख_लिखो(fp, " %04x:", val);
		अवरोध;
	हाल BINARY_PRINT_NUM_DATA:
		prपूर्णांकed += ख_लिखो(fp, " %02x", val);
		अवरोध;
	हाल BINARY_PRINT_NUM_PAD:
		prपूर्णांकed += ख_लिखो(fp, "   ");
		अवरोध;
	हाल BINARY_PRINT_SEP:
		prपूर्णांकed += ख_लिखो(fp, "  ");
		अवरोध;
	हाल BINARY_PRINT_CHAR_DATA:
		अगर (prपूर्णांकer_data->hit_nul && ch)
			prपूर्णांकer_data->is_prपूर्णांकable = false;

		अगर (!है_छाप(ch)) अणु
			prपूर्णांकed += ख_लिखो(fp, "%c", '.');

			अगर (!prपूर्णांकer_data->is_prपूर्णांकable)
				अवरोध;

			अगर (ch == '\0')
				prपूर्णांकer_data->hit_nul = true;
			अन्यथा
				prपूर्णांकer_data->is_prपूर्णांकable = false;
		पूर्ण अन्यथा अणु
			prपूर्णांकed += ख_लिखो(fp, "%c", ch);
		पूर्ण
		अवरोध;
	हाल BINARY_PRINT_CHAR_PAD:
		prपूर्णांकed += ख_लिखो(fp, " ");
		अवरोध;
	हाल BINARY_PRINT_LINE_END:
		prपूर्णांकed += ख_लिखो(fp, "\n");
		prपूर्णांकer_data->line_no++;
		अवरोध;
	हाल BINARY_PRINT_DATA_END:
	शेष:
		अवरोध;
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_bpf_output(काष्ठा perf_sample *sample, खाता *fp)
अणु
	अचिन्हित पूर्णांक nr_bytes = sample->raw_size;
	काष्ठा prपूर्णांकer_data prपूर्णांकer_data = अणु0, false, trueपूर्ण;
	पूर्णांक prपूर्णांकed = binary__ख_लिखो(sample->raw_data, nr_bytes, 8,
				      sample__ख_लिखो_bpf_output, &prपूर्णांकer_data, fp);

	अगर (prपूर्णांकer_data.is_prपूर्णांकable && prपूर्णांकer_data.hit_nul)
		prपूर्णांकed += ख_लिखो(fp, "%17s \"%s\"\n", "BPF string:", (अक्षर *)(sample->raw_data));

	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_spacing(पूर्णांक len, पूर्णांक spacing, खाता *fp)
अणु
	अगर (len > 0 && len < spacing)
		वापस ख_लिखो(fp, "%*s", spacing - len, "");

	वापस 0;
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_pt_spacing(पूर्णांक len, खाता *fp)
अणु
	वापस perf_sample__ख_लिखो_spacing(len, 34, fp);
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_synth_ptग_लिखो(काष्ठा perf_sample *sample, खाता *fp)
अणु
	काष्ठा perf_synth_पूर्णांकel_ptग_लिखो *data = perf_sample__synth_ptr(sample);
	पूर्णांक len;

	अगर (perf_sample__bad_synth_size(sample, *data))
		वापस 0;

	len = ख_लिखो(fp, " IP: %u payload: %#" PRIx64 " ",
		     data->ip, le64_to_cpu(data->payload));
	वापस len + perf_sample__ख_लिखो_pt_spacing(len, fp);
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_synth_mरुको(काष्ठा perf_sample *sample, खाता *fp)
अणु
	काष्ठा perf_synth_पूर्णांकel_mरुको *data = perf_sample__synth_ptr(sample);
	पूर्णांक len;

	अगर (perf_sample__bad_synth_size(sample, *data))
		वापस 0;

	len = ख_लिखो(fp, " hints: %#x extensions: %#x ",
		      data->hपूर्णांकs, data->extensions);
	वापस len + perf_sample__ख_लिखो_pt_spacing(len, fp);
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_synth_pwre(काष्ठा perf_sample *sample, खाता *fp)
अणु
	काष्ठा perf_synth_पूर्णांकel_pwre *data = perf_sample__synth_ptr(sample);
	पूर्णांक len;

	अगर (perf_sample__bad_synth_size(sample, *data))
		वापस 0;

	len = ख_लिखो(fp, " hw: %u cstate: %u sub-cstate: %u ",
		      data->hw, data->cstate, data->subcstate);
	वापस len + perf_sample__ख_लिखो_pt_spacing(len, fp);
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_synth_exstop(काष्ठा perf_sample *sample, खाता *fp)
अणु
	काष्ठा perf_synth_पूर्णांकel_exstop *data = perf_sample__synth_ptr(sample);
	पूर्णांक len;

	अगर (perf_sample__bad_synth_size(sample, *data))
		वापस 0;

	len = ख_लिखो(fp, " IP: %u ", data->ip);
	वापस len + perf_sample__ख_लिखो_pt_spacing(len, fp);
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_synth_pwrx(काष्ठा perf_sample *sample, खाता *fp)
अणु
	काष्ठा perf_synth_पूर्णांकel_pwrx *data = perf_sample__synth_ptr(sample);
	पूर्णांक len;

	अगर (perf_sample__bad_synth_size(sample, *data))
		वापस 0;

	len = ख_लिखो(fp, " deepest cstate: %u last cstate: %u wake reason: %#x ",
		     data->deepest_cstate, data->last_cstate,
		     data->wake_reason);
	वापस len + perf_sample__ख_लिखो_pt_spacing(len, fp);
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_synth_cbr(काष्ठा perf_sample *sample, खाता *fp)
अणु
	काष्ठा perf_synth_पूर्णांकel_cbr *data = perf_sample__synth_ptr(sample);
	अचिन्हित पूर्णांक percent, freq;
	पूर्णांक len;

	अगर (perf_sample__bad_synth_size(sample, *data))
		वापस 0;

	freq = (le32_to_cpu(data->freq) + 500) / 1000;
	len = ख_लिखो(fp, " cbr: %2u freq: %4u MHz ", data->cbr, freq);
	अगर (data->max_nonturbo) अणु
		percent = (5 + (1000 * data->cbr) / data->max_nonturbo) / 10;
		len += ख_लिखो(fp, "(%3u%%) ", percent);
	पूर्ण
	वापस len + perf_sample__ख_लिखो_pt_spacing(len, fp);
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_synth_psb(काष्ठा perf_sample *sample, खाता *fp)
अणु
	काष्ठा perf_synth_पूर्णांकel_psb *data = perf_sample__synth_ptr(sample);
	पूर्णांक len;

	अगर (perf_sample__bad_synth_size(sample, *data))
		वापस 0;

	len = ख_लिखो(fp, " psb offs: %#" PRIx64, data->offset);
	वापस len + perf_sample__ख_लिखो_pt_spacing(len, fp);
पूर्ण

अटल पूर्णांक perf_sample__ख_लिखो_synth(काष्ठा perf_sample *sample,
				      काष्ठा evsel *evsel, खाता *fp)
अणु
	चयन (evsel->core.attr.config) अणु
	हाल PERF_SYNTH_INTEL_PTWRITE:
		वापस perf_sample__ख_लिखो_synth_ptग_लिखो(sample, fp);
	हाल PERF_SYNTH_INTEL_MWAIT:
		वापस perf_sample__ख_लिखो_synth_mरुको(sample, fp);
	हाल PERF_SYNTH_INTEL_PWRE:
		वापस perf_sample__ख_लिखो_synth_pwre(sample, fp);
	हाल PERF_SYNTH_INTEL_EXSTOP:
		वापस perf_sample__ख_लिखो_synth_exstop(sample, fp);
	हाल PERF_SYNTH_INTEL_PWRX:
		वापस perf_sample__ख_लिखो_synth_pwrx(sample, fp);
	हाल PERF_SYNTH_INTEL_CBR:
		वापस perf_sample__ख_लिखो_synth_cbr(sample, fp);
	हाल PERF_SYNTH_INTEL_PSB:
		वापस perf_sample__ख_लिखो_synth_psb(sample, fp);
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक evlist__max_name_len(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;
	पूर्णांक max = 0;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		पूर्णांक len = म_माप(evsel__name(evsel));

		max = MAX(len, max);
	पूर्ण

	वापस max;
पूर्ण

अटल पूर्णांक data_src__ख_लिखो(u64 data_src, खाता *fp)
अणु
	काष्ठा mem_info mi = अणु .data_src.val = data_src पूर्ण;
	अक्षर decode[100];
	अक्षर out[100];
	अटल पूर्णांक maxlen;
	पूर्णांक len;

	perf_script__meminfo_scnम_लिखो(decode, 100, &mi);

	len = scnम_लिखो(out, 100, "%16" PRIx64 " %s", data_src, decode);
	अगर (maxlen < len)
		maxlen = len;

	वापस ख_लिखो(fp, "%-*s", maxlen, out);
पूर्ण

काष्ठा metric_ctx अणु
	काष्ठा perf_sample	*sample;
	काष्ठा thपढ़ो		*thपढ़ो;
	काष्ठा evsel	*evsel;
	खाता 			*fp;
पूर्ण;

अटल व्योम script_prपूर्णांक_metric(काष्ठा perf_stat_config *config __maybe_unused,
				व्योम *ctx, स्थिर अक्षर *color,
			        स्थिर अक्षर *fmt,
			        स्थिर अक्षर *unit, द्विगुन val)
अणु
	काष्ठा metric_ctx *mctx = ctx;

	अगर (!fmt)
		वापस;
	perf_sample__ख_लिखो_start(शून्य, mctx->sample, mctx->thपढ़ो, mctx->evsel,
				   PERF_RECORD_SAMPLE, mctx->fp);
	ख_माला_दो("\tmetric: ", mctx->fp);
	अगर (color)
		color_ख_लिखो(mctx->fp, color, fmt, val);
	अन्यथा
		म_लिखो(fmt, val);
	ख_लिखो(mctx->fp, " %s\n", unit);
पूर्ण

अटल व्योम script_new_line(काष्ठा perf_stat_config *config __maybe_unused,
			    व्योम *ctx)
अणु
	काष्ठा metric_ctx *mctx = ctx;

	perf_sample__ख_लिखो_start(शून्य, mctx->sample, mctx->thपढ़ो, mctx->evsel,
				   PERF_RECORD_SAMPLE, mctx->fp);
	ख_माला_दो("\tmetric: ", mctx->fp);
पूर्ण

अटल व्योम perf_sample__fprपूर्णांक_metric(काष्ठा perf_script *script,
				       काष्ठा thपढ़ो *thपढ़ो,
				       काष्ठा evsel *evsel,
				       काष्ठा perf_sample *sample,
				       खाता *fp)
अणु
	काष्ठा perf_stat_output_ctx ctx = अणु
		.prपूर्णांक_metric = script_prपूर्णांक_metric,
		.new_line = script_new_line,
		.ctx = &(काष्ठा metric_ctx) अणु
				.sample = sample,
				.thपढ़ो = thपढ़ो,
				.evsel  = evsel,
				.fp     = fp,
			 पूर्ण,
		.क्रमce_header = false,
	पूर्ण;
	काष्ठा evsel *ev2;
	u64 val;

	अगर (!evsel->stats)
		evlist__alloc_stats(script->session->evlist, false);
	अगर (evsel_script(evsel->leader)->gnum++ == 0)
		perf_stat__reset_shaकरोw_stats();
	val = sample->period * evsel->scale;
	perf_stat__update_shaकरोw_stats(evsel,
				       val,
				       sample->cpu,
				       &rt_stat);
	evsel_script(evsel)->val = val;
	अगर (evsel_script(evsel->leader)->gnum == evsel->leader->core.nr_members) अणु
		क्रम_each_group_member (ev2, evsel->leader) अणु
			perf_stat__prपूर्णांक_shaकरोw_stats(&stat_config, ev2,
						      evsel_script(ev2)->val,
						      sample->cpu,
						      &ctx,
						      शून्य,
						      &rt_stat);
		पूर्ण
		evsel_script(evsel->leader)->gnum = 0;
	पूर्ण
पूर्ण

अटल bool show_event(काष्ठा perf_sample *sample,
		       काष्ठा evsel *evsel,
		       काष्ठा thपढ़ो *thपढ़ो,
		       काष्ठा addr_location *al)
अणु
	पूर्णांक depth = thपढ़ो_stack__depth(thपढ़ो, sample->cpu);

	अगर (!symbol_conf.graph_function)
		वापस true;

	अगर (thपढ़ो->filter) अणु
		अगर (depth <= thपढ़ो->filter_entry_depth) अणु
			thपढ़ो->filter = false;
			वापस false;
		पूर्ण
		वापस true;
	पूर्ण अन्यथा अणु
		स्थिर अक्षर *s = symbol_conf.graph_function;
		u64 ip;
		स्थिर अक्षर *name = resolve_branch_sym(sample, evsel, thपढ़ो, al,
				&ip);
		अचिन्हित nlen;

		अगर (!name)
			वापस false;
		nlen = म_माप(name);
		जबतक (*s) अणु
			अचिन्हित len = म_खोज(s, ",");
			अगर (nlen == len && !म_भेदन(name, s, len)) अणु
				thपढ़ो->filter = true;
				thपढ़ो->filter_entry_depth = depth;
				वापस true;
			पूर्ण
			s += len;
			अगर (*s == ',')
				s++;
		पूर्ण
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम process_event(काष्ठा perf_script *script,
			  काष्ठा perf_sample *sample, काष्ठा evsel *evsel,
			  काष्ठा addr_location *al,
			  काष्ठा machine *machine)
अणु
	काष्ठा thपढ़ो *thपढ़ो = al->thपढ़ो;
	काष्ठा perf_event_attr *attr = &evsel->core.attr;
	अचिन्हित पूर्णांक type = output_type(attr->type);
	काष्ठा evsel_script *es = evsel->priv;
	खाता *fp = es->fp;
	अक्षर str[PAGE_SIZE_NAME_LEN];

	अगर (output[type].fields == 0)
		वापस;

	अगर (!show_event(sample, evsel, thपढ़ो, al))
		वापस;

	अगर (evचयन__discard(&script->evचयन, evsel))
		वापस;

	++es->samples;

	perf_sample__ख_लिखो_start(script, sample, thपढ़ो, evsel,
				   PERF_RECORD_SAMPLE, fp);

	अगर (PRINT_FIELD(PERIOD))
		ख_लिखो(fp, "%10" PRIu64 " ", sample->period);

	अगर (PRINT_FIELD(EVNAME)) अणु
		स्थिर अक्षर *evname = evsel__name(evsel);

		अगर (!script->name_width)
			script->name_width = evlist__max_name_len(script->session->evlist);

		ख_लिखो(fp, "%*s: ", script->name_width, evname ?: "[unknown]");
	पूर्ण

	अगर (prपूर्णांक_flags)
		perf_sample__ख_लिखो_flags(sample->flags, fp);

	अगर (is_bts_event(attr)) अणु
		perf_sample__ख_लिखो_bts(sample, evsel, thपढ़ो, al, machine, fp);
		वापस;
	पूर्ण

	अगर (PRINT_FIELD(TRACE) && sample->raw_data) अणु
		event_क्रमmat__ख_लिखो(evsel->tp_क्रमmat, sample->cpu,
				      sample->raw_data, sample->raw_size, fp);
	पूर्ण

	अगर (attr->type == PERF_TYPE_SYNTH && PRINT_FIELD(SYNTH))
		perf_sample__ख_लिखो_synth(sample, evsel, fp);

	अगर (PRINT_FIELD(ADDR))
		perf_sample__ख_लिखो_addr(sample, thपढ़ो, attr, fp);

	अगर (PRINT_FIELD(DATA_SRC))
		data_src__ख_लिखो(sample->data_src, fp);

	अगर (PRINT_FIELD(WEIGHT))
		ख_लिखो(fp, "%16" PRIu64, sample->weight);

	अगर (PRINT_FIELD(IP)) अणु
		काष्ठा callchain_cursor *cursor = शून्य;

		अगर (script->stitch_lbr)
			al->thपढ़ो->lbr_stitch_enable = true;

		अगर (symbol_conf.use_callchain && sample->callchain &&
		    thपढ़ो__resolve_callchain(al->thपढ़ो, &callchain_cursor, evsel,
					      sample, शून्य, शून्य, scripting_max_stack) == 0)
			cursor = &callchain_cursor;

		ख_अक्षर_दो(cursor ? '\n' : ' ', fp);
		sample__ख_लिखो_sym(sample, al, 0, output[type].prपूर्णांक_ip_opts, cursor,
				    symbol_conf.bt_stop_list, fp);
	पूर्ण

	अगर (PRINT_FIELD(IREGS))
		perf_sample__ख_लिखो_iregs(sample, attr, fp);

	अगर (PRINT_FIELD(UREGS))
		perf_sample__ख_लिखो_uregs(sample, attr, fp);

	अगर (PRINT_FIELD(BRSTACK))
		perf_sample__ख_लिखो_brstack(sample, thपढ़ो, attr, fp);
	अन्यथा अगर (PRINT_FIELD(BRSTACKSYM))
		perf_sample__ख_लिखो_brstacksym(sample, thपढ़ो, attr, fp);
	अन्यथा अगर (PRINT_FIELD(BRSTACKOFF))
		perf_sample__ख_लिखो_brstackoff(sample, thपढ़ो, attr, fp);

	अगर (evsel__is_bpf_output(evsel) && PRINT_FIELD(BPF_OUTPUT))
		perf_sample__ख_लिखो_bpf_output(sample, fp);
	perf_sample__ख_लिखो_insn(sample, attr, thपढ़ो, machine, fp);

	अगर (PRINT_FIELD(PHYS_ADDR))
		ख_लिखो(fp, "%16" PRIx64, sample->phys_addr);

	अगर (PRINT_FIELD(DATA_PAGE_SIZE))
		ख_लिखो(fp, " %s", get_page_size_name(sample->data_page_size, str));

	अगर (PRINT_FIELD(CODE_PAGE_SIZE))
		ख_लिखो(fp, " %s", get_page_size_name(sample->code_page_size, str));

	perf_sample__ख_लिखो_ipc(sample, attr, fp);

	ख_लिखो(fp, "\n");

	अगर (PRINT_FIELD(SRCCODE)) अणु
		अगर (map__ख_लिखो_srccode(al->map, al->addr, मानक_निकास,
					 &thपढ़ो->srccode_state))
			म_लिखो("\n");
	पूर्ण

	अगर (PRINT_FIELD(METRIC))
		perf_sample__fprपूर्णांक_metric(script, thपढ़ो, evsel, sample, fp);

	अगर (verbose)
		ख_साफ(fp);
पूर्ण

अटल काष्ठा scripting_ops	*scripting_ops;

अटल व्योम __process_stat(काष्ठा evsel *counter, u64 tstamp)
अणु
	पूर्णांक nthपढ़ोs = perf_thपढ़ो_map__nr(counter->core.thपढ़ोs);
	पूर्णांक ncpus = evsel__nr_cpus(counter);
	पूर्णांक cpu, thपढ़ो;
	अटल पूर्णांक header_prपूर्णांकed;

	अगर (counter->core.प्रणाली_wide)
		nthपढ़ोs = 1;

	अगर (!header_prपूर्णांकed) अणु
		म_लिखो("%3s %8s %15s %15s %15s %15s %s\n",
		       "CPU", "THREAD", "VAL", "ENA", "RUN", "TIME", "EVENT");
		header_prपूर्णांकed = 1;
	पूर्ण

	क्रम (thपढ़ो = 0; thपढ़ो < nthपढ़ोs; thपढ़ो++) अणु
		क्रम (cpu = 0; cpu < ncpus; cpu++) अणु
			काष्ठा perf_counts_values *counts;

			counts = perf_counts(counter->counts, cpu, thपढ़ो);

			म_लिखो("%3d %8d %15" PRIu64 " %15" PRIu64 " %15" PRIu64 " %15" PRIu64 " %s\n",
				counter->core.cpus->map[cpu],
				perf_thपढ़ो_map__pid(counter->core.thपढ़ोs, thपढ़ो),
				counts->val,
				counts->ena,
				counts->run,
				tstamp,
				evsel__name(counter));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम process_stat(काष्ठा evsel *counter, u64 tstamp)
अणु
	अगर (scripting_ops && scripting_ops->process_stat)
		scripting_ops->process_stat(&stat_config, counter, tstamp);
	अन्यथा
		__process_stat(counter, tstamp);
पूर्ण

अटल व्योम process_stat_पूर्णांकerval(u64 tstamp)
अणु
	अगर (scripting_ops && scripting_ops->process_stat_पूर्णांकerval)
		scripting_ops->process_stat_पूर्णांकerval(tstamp);
पूर्ण

अटल व्योम setup_scripting(व्योम)
अणु
	setup_perl_scripting();
	setup_python_scripting();
पूर्ण

अटल पूर्णांक flush_scripting(व्योम)
अणु
	वापस scripting_ops ? scripting_ops->flush_script() : 0;
पूर्ण

अटल पूर्णांक cleanup_scripting(व्योम)
अणु
	pr_debug("\nperf script stopped\n");

	वापस scripting_ops ? scripting_ops->stop_script() : 0;
पूर्ण

अटल bool filter_cpu(काष्ठा perf_sample *sample)
अणु
	अगर (cpu_list && sample->cpu != (u32)-1)
		वापस !test_bit(sample->cpu, cpu_biपंचांगap);
	वापस false;
पूर्ण

अटल पूर्णांक process_sample_event(काष्ठा perf_tool *tool,
				जोड़ perf_event *event,
				काष्ठा perf_sample *sample,
				काष्ठा evsel *evsel,
				काष्ठा machine *machine)
अणु
	काष्ठा perf_script *scr = container_of(tool, काष्ठा perf_script, tool);
	काष्ठा addr_location al;

	अगर (perf_समय__ranges_skip_sample(scr->pसमय_range, scr->range_num,
					  sample->समय)) अणु
		वापस 0;
	पूर्ण

	अगर (debug_mode) अणु
		अगर (sample->समय < last_बारtamp) अणु
			pr_err("Samples misordered, previous: %" PRIu64
				" this: %" PRIu64 "\n", last_बारtamp,
				sample->समय);
			nr_unordered++;
		पूर्ण
		last_बारtamp = sample->समय;
		वापस 0;
	पूर्ण

	अगर (machine__resolve(machine, &al, sample) < 0) अणु
		pr_err("problem processing %d event, skipping it.\n",
		       event->header.type);
		वापस -1;
	पूर्ण

	अगर (al.filtered)
		जाओ out_put;

	अगर (filter_cpu(sample))
		जाओ out_put;

	अगर (scripting_ops)
		scripting_ops->process_event(event, sample, evsel, &al);
	अन्यथा
		process_event(scr, sample, evsel, &al, machine);

out_put:
	addr_location__put(&al);
	वापस 0;
पूर्ण

अटल पूर्णांक process_attr(काष्ठा perf_tool *tool, जोड़ perf_event *event,
			काष्ठा evlist **pevlist)
अणु
	काष्ठा perf_script *scr = container_of(tool, काष्ठा perf_script, tool);
	काष्ठा evlist *evlist;
	काष्ठा evsel *evsel, *pos;
	u64 sample_type;
	पूर्णांक err;
	अटल काष्ठा evsel_script *es;

	err = perf_event__process_attr(tool, event, pevlist);
	अगर (err)
		वापस err;

	evlist = *pevlist;
	evsel = evlist__last(*pevlist);

	अगर (!evsel->priv) अणु
		अगर (scr->per_event_dump) अणु
			evsel->priv = evsel_script__new(evsel, scr->session->data);
		पूर्ण अन्यथा अणु
			es = zalloc(माप(*es));
			अगर (!es)
				वापस -ENOMEM;
			es->fp = मानक_निकास;
			evsel->priv = es;
		पूर्ण
	पूर्ण

	अगर (evsel->core.attr.type >= PERF_TYPE_MAX &&
	    evsel->core.attr.type != PERF_TYPE_SYNTH)
		वापस 0;

	evlist__क्रम_each_entry(evlist, pos) अणु
		अगर (pos->core.attr.type == evsel->core.attr.type && pos != evsel)
			वापस 0;
	पूर्ण

	अगर (evsel->core.attr.sample_type) अणु
		err = evsel__check_attr(evsel, scr->session);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * Check अगर we need to enable callchains based
	 * on events sample_type.
	 */
	sample_type = evlist__combined_sample_type(evlist);
	callchain_param_setup(sample_type);

	/* Enable fields क्रम callchain entries */
	अगर (symbol_conf.use_callchain &&
	    (sample_type & PERF_SAMPLE_CALLCHAIN ||
	     sample_type & PERF_SAMPLE_BRANCH_STACK ||
	     (sample_type & PERF_SAMPLE_REGS_USER &&
	      sample_type & PERF_SAMPLE_STACK_USER))) अणु
		पूर्णांक type = output_type(evsel->core.attr.type);

		अगर (!(output[type].user_unset_fields & PERF_OUTPUT_IP))
			output[type].fields |= PERF_OUTPUT_IP;
		अगर (!(output[type].user_unset_fields & PERF_OUTPUT_SYM))
			output[type].fields |= PERF_OUTPUT_SYM;
	पूर्ण
	set_prपूर्णांक_ip_opts(&evsel->core.attr);
	वापस 0;
पूर्ण

अटल पूर्णांक prपूर्णांक_event_with_समय(काष्ठा perf_tool *tool,
				 जोड़ perf_event *event,
				 काष्ठा perf_sample *sample,
				 काष्ठा machine *machine,
				 pid_t pid, pid_t tid, u64 बारtamp)
अणु
	काष्ठा perf_script *script = container_of(tool, काष्ठा perf_script, tool);
	काष्ठा perf_session *session = script->session;
	काष्ठा evsel *evsel = evlist__id2evsel(session->evlist, sample->id);
	काष्ठा thपढ़ो *thपढ़ो = शून्य;

	अगर (evsel && !evsel->core.attr.sample_id_all) अणु
		sample->cpu = 0;
		sample->समय = बारtamp;
		sample->pid = pid;
		sample->tid = tid;
	पूर्ण

	अगर (filter_cpu(sample))
		वापस 0;

	अगर (tid != -1)
		thपढ़ो = machine__findnew_thपढ़ो(machine, pid, tid);

	अगर (evsel) अणु
		perf_sample__ख_लिखो_start(script, sample, thपढ़ो, evsel,
					   event->header.type, मानक_निकास);
	पूर्ण

	perf_event__ख_लिखो(event, machine, मानक_निकास);

	thपढ़ो__put(thपढ़ो);

	वापस 0;
पूर्ण

अटल पूर्णांक prपूर्णांक_event(काष्ठा perf_tool *tool, जोड़ perf_event *event,
		       काष्ठा perf_sample *sample, काष्ठा machine *machine,
		       pid_t pid, pid_t tid)
अणु
	वापस prपूर्णांक_event_with_समय(tool, event, sample, machine, pid, tid, 0);
पूर्ण

अटल पूर्णांक process_comm_event(काष्ठा perf_tool *tool,
			      जोड़ perf_event *event,
			      काष्ठा perf_sample *sample,
			      काष्ठा machine *machine)
अणु
	अगर (perf_event__process_comm(tool, event, sample, machine) < 0)
		वापस -1;

	वापस prपूर्णांक_event(tool, event, sample, machine, event->comm.pid,
			   event->comm.tid);
पूर्ण

अटल पूर्णांक process_namespaces_event(काष्ठा perf_tool *tool,
				    जोड़ perf_event *event,
				    काष्ठा perf_sample *sample,
				    काष्ठा machine *machine)
अणु
	अगर (perf_event__process_namespaces(tool, event, sample, machine) < 0)
		वापस -1;

	वापस prपूर्णांक_event(tool, event, sample, machine, event->namespaces.pid,
			   event->namespaces.tid);
पूर्ण

अटल पूर्णांक process_cgroup_event(काष्ठा perf_tool *tool,
				जोड़ perf_event *event,
				काष्ठा perf_sample *sample,
				काष्ठा machine *machine)
अणु
	अगर (perf_event__process_cgroup(tool, event, sample, machine) < 0)
		वापस -1;

	वापस prपूर्णांक_event(tool, event, sample, machine, sample->pid,
			    sample->tid);
पूर्ण

अटल पूर्णांक process_विभाजन_event(काष्ठा perf_tool *tool,
			      जोड़ perf_event *event,
			      काष्ठा perf_sample *sample,
			      काष्ठा machine *machine)
अणु
	अगर (perf_event__process_विभाजन(tool, event, sample, machine) < 0)
		वापस -1;

	वापस prपूर्णांक_event_with_समय(tool, event, sample, machine,
				     event->विभाजन.pid, event->विभाजन.tid,
				     event->विभाजन.समय);
पूर्ण
अटल पूर्णांक process_निकास_event(काष्ठा perf_tool *tool,
			      जोड़ perf_event *event,
			      काष्ठा perf_sample *sample,
			      काष्ठा machine *machine)
अणु
	/* Prपूर्णांक beक्रमe 'exit' deletes anything */
	अगर (prपूर्णांक_event_with_समय(tool, event, sample, machine, event->विभाजन.pid,
				  event->विभाजन.tid, event->विभाजन.समय))
		वापस -1;

	वापस perf_event__process_निकास(tool, event, sample, machine);
पूर्ण

अटल पूर्णांक process_mmap_event(काष्ठा perf_tool *tool,
			      जोड़ perf_event *event,
			      काष्ठा perf_sample *sample,
			      काष्ठा machine *machine)
अणु
	अगर (perf_event__process_mmap(tool, event, sample, machine) < 0)
		वापस -1;

	वापस prपूर्णांक_event(tool, event, sample, machine, event->mmap.pid,
			   event->mmap.tid);
पूर्ण

अटल पूर्णांक process_mmap2_event(काष्ठा perf_tool *tool,
			      जोड़ perf_event *event,
			      काष्ठा perf_sample *sample,
			      काष्ठा machine *machine)
अणु
	अगर (perf_event__process_mmap2(tool, event, sample, machine) < 0)
		वापस -1;

	वापस prपूर्णांक_event(tool, event, sample, machine, event->mmap2.pid,
			   event->mmap2.tid);
पूर्ण

अटल पूर्णांक process_चयन_event(काष्ठा perf_tool *tool,
				जोड़ perf_event *event,
				काष्ठा perf_sample *sample,
				काष्ठा machine *machine)
अणु
	काष्ठा perf_script *script = container_of(tool, काष्ठा perf_script, tool);

	अगर (perf_event__process_चयन(tool, event, sample, machine) < 0)
		वापस -1;

	अगर (scripting_ops && scripting_ops->process_चयन)
		scripting_ops->process_चयन(event, sample, machine);

	अगर (!script->show_चयन_events)
		वापस 0;

	वापस prपूर्णांक_event(tool, event, sample, machine, sample->pid,
			   sample->tid);
पूर्ण

अटल पूर्णांक
process_lost_event(काष्ठा perf_tool *tool,
		   जोड़ perf_event *event,
		   काष्ठा perf_sample *sample,
		   काष्ठा machine *machine)
अणु
	वापस prपूर्णांक_event(tool, event, sample, machine, sample->pid,
			   sample->tid);
पूर्ण

अटल पूर्णांक
process_finished_round_event(काष्ठा perf_tool *tool __maybe_unused,
			     जोड़ perf_event *event,
			     काष्ठा ordered_events *oe __maybe_unused)

अणु
	perf_event__ख_लिखो(event, शून्य, मानक_निकास);
	वापस 0;
पूर्ण

अटल पूर्णांक
process_bpf_events(काष्ठा perf_tool *tool __maybe_unused,
		   जोड़ perf_event *event,
		   काष्ठा perf_sample *sample,
		   काष्ठा machine *machine)
अणु
	अगर (machine__process_ksymbol(machine, event, sample) < 0)
		वापस -1;

	वापस prपूर्णांक_event(tool, event, sample, machine, sample->pid,
			   sample->tid);
पूर्ण

अटल पूर्णांक process_text_poke_events(काष्ठा perf_tool *tool,
				    जोड़ perf_event *event,
				    काष्ठा perf_sample *sample,
				    काष्ठा machine *machine)
अणु
	अगर (perf_event__process_text_poke(tool, event, sample, machine) < 0)
		वापस -1;

	वापस prपूर्णांक_event(tool, event, sample, machine, sample->pid,
			   sample->tid);
पूर्ण

अटल व्योम sig_handler(पूर्णांक sig __maybe_unused)
अणु
	session_करोne = 1;
पूर्ण

अटल व्योम perf_script__ख_बंद_per_event_dump(काष्ठा perf_script *script)
अणु
	काष्ठा evlist *evlist = script->session->evlist;
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (!evsel->priv)
			अवरोध;
		evsel_script__delete(evsel->priv);
		evsel->priv = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक perf_script__ख_खोलो_per_event_dump(काष्ठा perf_script *script)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(script->session->evlist, evsel) अणु
		/*
		 * Alपढ़ोy setup? I.e. we may be called twice in हालs like
		 * Intel PT, one क्रम the पूर्णांकel_pt// and dummy events, then
		 * क्रम the evsels synthesized from the auxtrace info.
		 *
		 * Ses perf_script__process_auxtrace_info.
		 */
		अगर (evsel->priv != शून्य)
			जारी;

		evsel->priv = evsel_script__new(evsel, script->session->data);
		अगर (evsel->priv == शून्य)
			जाओ out_err_ख_बंद;
	पूर्ण

	वापस 0;

out_err_ख_बंद:
	perf_script__ख_बंद_per_event_dump(script);
	वापस -1;
पूर्ण

अटल पूर्णांक perf_script__setup_per_event_dump(काष्ठा perf_script *script)
अणु
	काष्ठा evsel *evsel;
	अटल काष्ठा evsel_script es_मानक_निकास;

	अगर (script->per_event_dump)
		वापस perf_script__ख_खोलो_per_event_dump(script);

	es_मानक_निकास.fp = मानक_निकास;

	evlist__क्रम_each_entry(script->session->evlist, evsel)
		evsel->priv = &es_मानक_निकास;

	वापस 0;
पूर्ण

अटल व्योम perf_script__निकास_per_event_dump_stats(काष्ठा perf_script *script)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(script->session->evlist, evsel) अणु
		काष्ठा evsel_script *es = evsel->priv;

		evsel_script__ख_लिखो(es, मानक_निकास);
		evsel_script__delete(es);
		evsel->priv = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक __cmd_script(काष्ठा perf_script *script)
अणु
	पूर्णांक ret;

	संकेत(संक_विघ्न, sig_handler);

	perf_stat__init_shaकरोw_stats();

	/* override event processing functions */
	अगर (script->show_task_events) अणु
		script->tool.comm = process_comm_event;
		script->tool.विभाजन = process_विभाजन_event;
		script->tool.निकास = process_निकास_event;
	पूर्ण
	अगर (script->show_mmap_events) अणु
		script->tool.mmap = process_mmap_event;
		script->tool.mmap2 = process_mmap2_event;
	पूर्ण
	अगर (script->show_चयन_events || (scripting_ops && scripting_ops->process_चयन))
		script->tool.context_चयन = process_चयन_event;
	अगर (script->show_namespace_events)
		script->tool.namespaces = process_namespaces_event;
	अगर (script->show_cgroup_events)
		script->tool.cgroup = process_cgroup_event;
	अगर (script->show_lost_events)
		script->tool.lost = process_lost_event;
	अगर (script->show_round_events) अणु
		script->tool.ordered_events = false;
		script->tool.finished_round = process_finished_round_event;
	पूर्ण
	अगर (script->show_bpf_events) अणु
		script->tool.ksymbol = process_bpf_events;
		script->tool.bpf     = process_bpf_events;
	पूर्ण
	अगर (script->show_text_poke_events) अणु
		script->tool.ksymbol   = process_bpf_events;
		script->tool.text_poke = process_text_poke_events;
	पूर्ण

	अगर (perf_script__setup_per_event_dump(script)) अणु
		pr_err("Couldn't create the per event dump files\n");
		वापस -1;
	पूर्ण

	ret = perf_session__process_events(script->session);

	अगर (script->per_event_dump)
		perf_script__निकास_per_event_dump_stats(script);

	अगर (debug_mode)
		pr_err("Misordered timestamps: %" PRIu64 "\n", nr_unordered);

	वापस ret;
पूर्ण

काष्ठा script_spec अणु
	काष्ठा list_head	node;
	काष्ठा scripting_ops	*ops;
	अक्षर			spec[];
पूर्ण;

अटल LIST_HEAD(script_specs);

अटल काष्ठा script_spec *script_spec__new(स्थिर अक्षर *spec,
					    काष्ठा scripting_ops *ops)
अणु
	काष्ठा script_spec *s = दो_स्मृति(माप(*s) + म_माप(spec) + 1);

	अगर (s != शून्य) अणु
		म_नकल(s->spec, spec);
		s->ops = ops;
	पूर्ण

	वापस s;
पूर्ण

अटल व्योम script_spec__add(काष्ठा script_spec *s)
अणु
	list_add_tail(&s->node, &script_specs);
पूर्ण

अटल काष्ठा script_spec *script_spec__find(स्थिर अक्षर *spec)
अणु
	काष्ठा script_spec *s;

	list_क्रम_each_entry(s, &script_specs, node)
		अगर (strहालcmp(s->spec, spec) == 0)
			वापस s;
	वापस शून्य;
पूर्ण

पूर्णांक script_spec_रेजिस्टर(स्थिर अक्षर *spec, काष्ठा scripting_ops *ops)
अणु
	काष्ठा script_spec *s;

	s = script_spec__find(spec);
	अगर (s)
		वापस -1;

	s = script_spec__new(spec, ops);
	अगर (!s)
		वापस -1;
	अन्यथा
		script_spec__add(s);

	वापस 0;
पूर्ण

अटल काष्ठा scripting_ops *script_spec__lookup(स्थिर अक्षर *spec)
अणु
	काष्ठा script_spec *s = script_spec__find(spec);
	अगर (!s)
		वापस शून्य;

	वापस s->ops;
पूर्ण

अटल व्योम list_available_languages(व्योम)
अणु
	काष्ठा script_spec *s;

	ख_लिखो(मानक_त्रुटि, "\n");
	ख_लिखो(मानक_त्रुटि, "Scripting language extensions (used in "
		"perf script -s [spec:]script.[spec]):\n\n");

	list_क्रम_each_entry(s, &script_specs, node)
		ख_लिखो(मानक_त्रुटि, "  %-42s [%s]\n", s->spec, s->ops->name);

	ख_लिखो(मानक_त्रुटि, "\n");
पूर्ण

अटल पूर्णांक parse_scriptname(स्थिर काष्ठा option *opt __maybe_unused,
			    स्थिर अक्षर *str, पूर्णांक unset __maybe_unused)
अणु
	अक्षर spec[PATH_MAX];
	स्थिर अक्षर *script, *ext;
	पूर्णांक len;

	अगर (म_भेद(str, "lang") == 0) अणु
		list_available_languages();
		निकास(0);
	पूर्ण

	script = म_अक्षर(str, ':');
	अगर (script) अणु
		len = script - str;
		अगर (len >= PATH_MAX) अणु
			ख_लिखो(मानक_त्रुटि, "invalid language specifier");
			वापस -1;
		पूर्ण
		म_नकलन(spec, str, len);
		spec[len] = '\0';
		scripting_ops = script_spec__lookup(spec);
		अगर (!scripting_ops) अणु
			ख_लिखो(मानक_त्रुटि, "invalid language specifier");
			वापस -1;
		पूर्ण
		script++;
	पूर्ण अन्यथा अणु
		script = str;
		ext = म_खोजप(script, '.');
		अगर (!ext) अणु
			ख_लिखो(मानक_त्रुटि, "invalid script extension");
			वापस -1;
		पूर्ण
		scripting_ops = script_spec__lookup(++ext);
		अगर (!scripting_ops) अणु
			ख_लिखो(मानक_त्रुटि, "invalid script extension");
			वापस -1;
		पूर्ण
	पूर्ण

	script_name = strdup(script);

	वापस 0;
पूर्ण

अटल पूर्णांक parse_output_fields(स्थिर काष्ठा option *opt __maybe_unused,
			    स्थिर अक्षर *arg, पूर्णांक unset __maybe_unused)
अणु
	अक्षर *tok, *म_मोहर_saveptr = शून्य;
	पूर्णांक i, imax = ARRAY_SIZE(all_output_options);
	पूर्णांक j;
	पूर्णांक rc = 0;
	अक्षर *str = strdup(arg);
	पूर्णांक type = -1;
	क्रमागत अणु DEFAULT, SET, ADD, REMOVE पूर्ण change = DEFAULT;

	अगर (!str)
		वापस -ENOMEM;

	/* first word can state क्रम which event type the user is specअगरying
	 * the fields. If no type exists, the specअगरied fields apply to all
	 * event types found in the file minus the invalid fields क्रम a type.
	 */
	tok = म_अक्षर(str, ':');
	अगर (tok) अणु
		*tok = '\0';
		tok++;
		अगर (!म_भेद(str, "hw"))
			type = PERF_TYPE_HARDWARE;
		अन्यथा अगर (!म_भेद(str, "sw"))
			type = PERF_TYPE_SOFTWARE;
		अन्यथा अगर (!म_भेद(str, "trace"))
			type = PERF_TYPE_TRACEPOINT;
		अन्यथा अगर (!म_भेद(str, "raw"))
			type = PERF_TYPE_RAW;
		अन्यथा अगर (!म_भेद(str, "break"))
			type = PERF_TYPE_BREAKPOINT;
		अन्यथा अगर (!म_भेद(str, "synth"))
			type = OUTPUT_TYPE_SYNTH;
		अन्यथा अणु
			ख_लिखो(मानक_त्रुटि, "Invalid event type in field string.\n");
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (output[type].user_set)
			pr_warning("Overriding previous field request for %s events.\n",
				   event_type(type));

		/* Don't override शेषs क्रम +- */
		अगर (म_अक्षर(tok, '+') || strchr(tok, '-'))
			जाओ parse;

		output[type].fields = 0;
		output[type].user_set = true;
		output[type].wildcard_set = false;

	पूर्ण अन्यथा अणु
		tok = str;
		अगर (म_माप(str) == 0) अणु
			ख_लिखो(मानक_त्रुटि,
				"Cannot set fields to 'none' for all event types.\n");
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		/* Don't override शेषs क्रम +- */
		अगर (म_अक्षर(str, '+') || strchr(str, '-'))
			जाओ parse;

		अगर (output_set_by_user())
			pr_warning("Overriding previous field request for all events.\n");

		क्रम (j = 0; j < OUTPUT_TYPE_MAX; ++j) अणु
			output[j].fields = 0;
			output[j].user_set = true;
			output[j].wildcard_set = true;
		पूर्ण
	पूर्ण

parse:
	क्रम (tok = म_मोहर_r(tok, ",", &म_मोहर_saveptr); tok; tok = म_मोहर_r(शून्य, ",", &म_मोहर_saveptr)) अणु
		अगर (*tok == '+') अणु
			अगर (change == SET)
				जाओ out_badmix;
			change = ADD;
			tok++;
		पूर्ण अन्यथा अगर (*tok == '-') अणु
			अगर (change == SET)
				जाओ out_badmix;
			change = REMOVE;
			tok++;
		पूर्ण अन्यथा अणु
			अगर (change != SET && change != DEFAULT)
				जाओ out_badmix;
			change = SET;
		पूर्ण

		क्रम (i = 0; i < imax; ++i) अणु
			अगर (म_भेद(tok, all_output_options[i].str) == 0)
				अवरोध;
		पूर्ण
		अगर (i == imax && म_भेद(tok, "flags") == 0) अणु
			prपूर्णांक_flags = change != REMOVE;
			जारी;
		पूर्ण
		अगर (i == imax) अणु
			ख_लिखो(मानक_त्रुटि, "Invalid field requested.\n");
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (type == -1) अणु
			/* add user option to all events types क्रम
			 * which it is valid
			 */
			क्रम (j = 0; j < OUTPUT_TYPE_MAX; ++j) अणु
				अगर (output[j].invalid_fields & all_output_options[i].field) अणु
					pr_warning("\'%s\' not valid for %s events. Ignoring.\n",
						   all_output_options[i].str, event_type(j));
				पूर्ण अन्यथा अणु
					अगर (change == REMOVE) अणु
						output[j].fields &= ~all_output_options[i].field;
						output[j].user_set_fields &= ~all_output_options[i].field;
						output[j].user_unset_fields |= all_output_options[i].field;
					पूर्ण अन्यथा अणु
						output[j].fields |= all_output_options[i].field;
						output[j].user_set_fields |= all_output_options[i].field;
						output[j].user_unset_fields &= ~all_output_options[i].field;
					पूर्ण
					output[j].user_set = true;
					output[j].wildcard_set = true;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (output[type].invalid_fields & all_output_options[i].field) अणु
				ख_लिखो(मानक_त्रुटि, "\'%s\' not valid for %s events.\n",
					 all_output_options[i].str, event_type(type));

				rc = -EINVAL;
				जाओ out;
			पूर्ण
			अगर (change == REMOVE)
				output[type].fields &= ~all_output_options[i].field;
			अन्यथा
				output[type].fields |= all_output_options[i].field;
			output[type].user_set = true;
			output[type].wildcard_set = true;
		पूर्ण
	पूर्ण

	अगर (type >= 0) अणु
		अगर (output[type].fields == 0) अणु
			pr_debug("No fields requested for %s type. "
				 "Events will not be displayed.\n", event_type(type));
		पूर्ण
	पूर्ण
	जाओ out;

out_badmix:
	ख_लिखो(मानक_त्रुटि, "Cannot mix +-field with overridden fields\n");
	rc = -EINVAL;
out:
	मुक्त(str);
	वापस rc;
पूर्ण

#घोषणा क्रम_each_lang(scripts_path, scripts_dir, lang_dirent)		\
	जबतक ((lang_dirent = सूची_पढ़ो(scripts_dir)) != शून्य)		\
		अगर ((lang_dirent->d_type == DT_सूची ||			\
		     (lang_dirent->d_type == DT_UNKNOWN &&		\
		      is_directory(scripts_path, lang_dirent))) &&	\
		    (म_भेद(lang_dirent->d_name, ".")) &&		\
		    (म_भेद(lang_dirent->d_name, "..")))

#घोषणा क्रम_each_script(lang_path, lang_dir, script_dirent)		\
	जबतक ((script_dirent = सूची_पढ़ो(lang_dir)) != शून्य)		\
		अगर (script_dirent->d_type != DT_सूची &&			\
		    (script_dirent->d_type != DT_UNKNOWN ||		\
		     !is_directory(lang_path, script_dirent)))


#घोषणा RECORD_SUFFIX			"-record"
#घोषणा REPORT_SUFFIX			"-report"

काष्ठा script_desc अणु
	काष्ठा list_head	node;
	अक्षर			*name;
	अक्षर			*half_liner;
	अक्षर			*args;
पूर्ण;

अटल LIST_HEAD(script_descs);

अटल काष्ठा script_desc *script_desc__new(स्थिर अक्षर *name)
अणु
	काष्ठा script_desc *s = zalloc(माप(*s));

	अगर (s != शून्य && name)
		s->name = strdup(name);

	वापस s;
पूर्ण

अटल व्योम script_desc__delete(काष्ठा script_desc *s)
अणु
	zमुक्त(&s->name);
	zमुक्त(&s->half_liner);
	zमुक्त(&s->args);
	मुक्त(s);
पूर्ण

अटल व्योम script_desc__add(काष्ठा script_desc *s)
अणु
	list_add_tail(&s->node, &script_descs);
पूर्ण

अटल काष्ठा script_desc *script_desc__find(स्थिर अक्षर *name)
अणु
	काष्ठा script_desc *s;

	list_क्रम_each_entry(s, &script_descs, node)
		अगर (strहालcmp(s->name, name) == 0)
			वापस s;
	वापस शून्य;
पूर्ण

अटल काष्ठा script_desc *script_desc__findnew(स्थिर अक्षर *name)
अणु
	काष्ठा script_desc *s = script_desc__find(name);

	अगर (s)
		वापस s;

	s = script_desc__new(name);
	अगर (!s)
		वापस शून्य;

	script_desc__add(s);

	वापस s;
पूर्ण

अटल स्थिर अक्षर *ends_with(स्थिर अक्षर *str, स्थिर अक्षर *suffix)
अणु
	माप_प्रकार suffix_len = म_माप(suffix);
	स्थिर अक्षर *p = str;

	अगर (म_माप(str) > suffix_len) अणु
		p = str + म_माप(str) - suffix_len;
		अगर (!म_भेदन(p, suffix, suffix_len))
			वापस p;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक पढ़ो_script_info(काष्ठा script_desc *desc, स्थिर अक्षर *filename)
अणु
	अक्षर line[बफ_मान], *p;
	खाता *fp;

	fp = ख_खोलो(filename, "r");
	अगर (!fp)
		वापस -1;

	जबतक (ख_माला_लो(line, माप(line), fp)) अणु
		p = skip_spaces(line);
		अगर (म_माप(p) == 0)
			जारी;
		अगर (*p != '#')
			जारी;
		p++;
		अगर (म_माप(p) && *p == '!')
			जारी;

		p = skip_spaces(p);
		अगर (म_माप(p) && p[म_माप(p) - 1] == '\n')
			p[म_माप(p) - 1] = '\0';

		अगर (!म_भेदन(p, "description:", म_माप("description:"))) अणु
			p += म_माप("description:");
			desc->half_liner = strdup(skip_spaces(p));
			जारी;
		पूर्ण

		अगर (!म_भेदन(p, "args:", म_माप("args:"))) अणु
			p += म_माप("args:");
			desc->args = strdup(skip_spaces(p));
			जारी;
		पूर्ण
	पूर्ण

	ख_बंद(fp);

	वापस 0;
पूर्ण

अटल अक्षर *get_script_root(काष्ठा dirent *script_dirent, स्थिर अक्षर *suffix)
अणु
	अक्षर *script_root, *str;

	script_root = strdup(script_dirent->d_name);
	अगर (!script_root)
		वापस शून्य;

	str = (अक्षर *)ends_with(script_root, suffix);
	अगर (!str) अणु
		मुक्त(script_root);
		वापस शून्य;
	पूर्ण

	*str = '\0';
	वापस script_root;
पूर्ण

अटल पूर्णांक list_available_scripts(स्थिर काष्ठा option *opt __maybe_unused,
				  स्थिर अक्षर *s __maybe_unused,
				  पूर्णांक unset __maybe_unused)
अणु
	काष्ठा dirent *script_dirent, *lang_dirent;
	अक्षर scripts_path[MAXPATHLEN];
	सूची *scripts_dir, *lang_dir;
	अक्षर script_path[MAXPATHLEN];
	अक्षर lang_path[MAXPATHLEN];
	काष्ठा script_desc *desc;
	अक्षर first_half[बफ_मान];
	अक्षर *script_root;

	snम_लिखो(scripts_path, MAXPATHLEN, "%s/scripts", get_argv_exec_path());

	scripts_dir = सूची_खोलो(scripts_path);
	अगर (!scripts_dir) अणु
		ख_लिखो(मानक_निकास,
			"open(%s) failed.\n"
			"Check \"PERF_EXEC_PATH\" env to set scripts dir.\n",
			scripts_path);
		निकास(-1);
	पूर्ण

	क्रम_each_lang(scripts_path, scripts_dir, lang_dirent) अणु
		scnम_लिखो(lang_path, MAXPATHLEN, "%s/%s/bin", scripts_path,
			  lang_dirent->d_name);
		lang_dir = सूची_खोलो(lang_path);
		अगर (!lang_dir)
			जारी;

		क्रम_each_script(lang_path, lang_dir, script_dirent) अणु
			script_root = get_script_root(script_dirent, REPORT_SUFFIX);
			अगर (script_root) अणु
				desc = script_desc__findnew(script_root);
				scnम_लिखो(script_path, MAXPATHLEN, "%s/%s",
					  lang_path, script_dirent->d_name);
				पढ़ो_script_info(desc, script_path);
				मुक्त(script_root);
			पूर्ण
		पूर्ण
	पूर्ण

	ख_लिखो(मानक_निकास, "List of available trace scripts:\n");
	list_क्रम_each_entry(desc, &script_descs, node) अणु
		प्र_लिखो(first_half, "%s %s", desc->name,
			desc->args ? desc->args : "");
		ख_लिखो(मानक_निकास, "  %-36s %s\n", first_half,
			desc->half_liner ? desc->half_liner : "");
	पूर्ण

	निकास(0);
पूर्ण

/*
 * Some scripts specअगरy the required events in their "xxx-record" file,
 * this function will check अगर the events in perf.data match those
 * mentioned in the "xxx-record".
 *
 * Fixme: All existing "xxx-record" are all in good क्रमmats "-e event ",
 * which is covered well now. And new parsing code should be added to
 * cover the future complex क्रमmats like event groups etc.
 */
अटल पूर्णांक check_ev_match(अक्षर *dir_name, अक्षर *scriptname,
			काष्ठा perf_session *session)
अणु
	अक्षर filename[MAXPATHLEN], evname[128];
	अक्षर line[बफ_मान], *p;
	काष्ठा evsel *pos;
	पूर्णांक match, len;
	खाता *fp;

	scnम_लिखो(filename, MAXPATHLEN, "%s/bin/%s-record", dir_name, scriptname);

	fp = ख_खोलो(filename, "r");
	अगर (!fp)
		वापस -1;

	जबतक (ख_माला_लो(line, माप(line), fp)) अणु
		p = skip_spaces(line);
		अगर (*p == '#')
			जारी;

		जबतक (म_माप(p)) अणु
			p = म_माला(p, "-e");
			अगर (!p)
				अवरोध;

			p += 2;
			p = skip_spaces(p);
			len = म_खोज(p, " \t");
			अगर (!len)
				अवरोध;

			snम_लिखो(evname, len + 1, "%s", p);

			match = 0;
			evlist__क्रम_each_entry(session->evlist, pos) अणु
				अगर (!म_भेद(evsel__name(pos), evname)) अणु
					match = 1;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (!match) अणु
				ख_बंद(fp);
				वापस -1;
			पूर्ण
		पूर्ण
	पूर्ण

	ख_बंद(fp);
	वापस 0;
पूर्ण

/*
 * Return -1 अगर none is found, otherwise the actual scripts number.
 *
 * Currently the only user of this function is the script browser, which
 * will list all अटलally runnable scripts, select one, execute it and
 * show the output in a perf browser.
 */
पूर्णांक find_scripts(अक्षर **scripts_array, अक्षर **scripts_path_array, पूर्णांक num,
		 पूर्णांक pathlen)
अणु
	काष्ठा dirent *script_dirent, *lang_dirent;
	अक्षर scripts_path[MAXPATHLEN], lang_path[MAXPATHLEN];
	सूची *scripts_dir, *lang_dir;
	काष्ठा perf_session *session;
	काष्ठा perf_data data = अणु
		.path = input_name,
		.mode = PERF_DATA_MODE_READ,
	पूर्ण;
	अक्षर *temp;
	पूर्णांक i = 0;

	session = perf_session__new(&data, false, शून्य);
	अगर (IS_ERR(session))
		वापस PTR_ERR(session);

	snम_लिखो(scripts_path, MAXPATHLEN, "%s/scripts", get_argv_exec_path());

	scripts_dir = सूची_खोलो(scripts_path);
	अगर (!scripts_dir) अणु
		perf_session__delete(session);
		वापस -1;
	पूर्ण

	क्रम_each_lang(scripts_path, scripts_dir, lang_dirent) अणु
		scnम_लिखो(lang_path, MAXPATHLEN, "%s/%s", scripts_path,
			  lang_dirent->d_name);
#अगर_अघोषित HAVE_LIBPERL_SUPPORT
		अगर (म_माला(lang_path, "perl"))
			जारी;
#पूर्ण_अगर
#अगर_अघोषित HAVE_LIBPYTHON_SUPPORT
		अगर (म_माला(lang_path, "python"))
			जारी;
#पूर्ण_अगर

		lang_dir = सूची_खोलो(lang_path);
		अगर (!lang_dir)
			जारी;

		क्रम_each_script(lang_path, lang_dir, script_dirent) अणु
			/* Skip those real समय scripts: xxxtop.p[yl] */
			अगर (म_माला(script_dirent->d_name, "top."))
				जारी;
			अगर (i >= num)
				अवरोध;
			snम_लिखो(scripts_path_array[i], pathlen, "%s/%s",
				lang_path,
				script_dirent->d_name);
			temp = म_अक्षर(script_dirent->d_name, '.');
			snम_लिखो(scripts_array[i],
				(temp - script_dirent->d_name) + 1,
				"%s", script_dirent->d_name);

			अगर (check_ev_match(lang_path,
					scripts_array[i], session))
				जारी;

			i++;
		पूर्ण
		बंद_सूची(lang_dir);
	पूर्ण

	बंद_सूची(scripts_dir);
	perf_session__delete(session);
	वापस i;
पूर्ण

अटल अक्षर *get_script_path(स्थिर अक्षर *script_root, स्थिर अक्षर *suffix)
अणु
	काष्ठा dirent *script_dirent, *lang_dirent;
	अक्षर scripts_path[MAXPATHLEN];
	अक्षर script_path[MAXPATHLEN];
	सूची *scripts_dir, *lang_dir;
	अक्षर lang_path[MAXPATHLEN];
	अक्षर *__script_root;

	snम_लिखो(scripts_path, MAXPATHLEN, "%s/scripts", get_argv_exec_path());

	scripts_dir = सूची_खोलो(scripts_path);
	अगर (!scripts_dir)
		वापस शून्य;

	क्रम_each_lang(scripts_path, scripts_dir, lang_dirent) अणु
		scnम_लिखो(lang_path, MAXPATHLEN, "%s/%s/bin", scripts_path,
			  lang_dirent->d_name);
		lang_dir = सूची_खोलो(lang_path);
		अगर (!lang_dir)
			जारी;

		क्रम_each_script(lang_path, lang_dir, script_dirent) अणु
			__script_root = get_script_root(script_dirent, suffix);
			अगर (__script_root && !म_भेद(script_root, __script_root)) अणु
				मुक्त(__script_root);
				बंद_सूची(scripts_dir);
				scnम_लिखो(script_path, MAXPATHLEN, "%s/%s",
					  lang_path, script_dirent->d_name);
				बंद_सूची(lang_dir);
				वापस strdup(script_path);
			पूर्ण
			मुक्त(__script_root);
		पूर्ण
		बंद_सूची(lang_dir);
	पूर्ण
	बंद_सूची(scripts_dir);

	वापस शून्य;
पूर्ण

अटल bool is_top_script(स्थिर अक्षर *script_path)
अणु
	वापस ends_with(script_path, "top") != शून्य;
पूर्ण

अटल पूर्णांक has_required_arg(अक्षर *script_path)
अणु
	काष्ठा script_desc *desc;
	पूर्णांक n_args = 0;
	अक्षर *p;

	desc = script_desc__new(शून्य);

	अगर (पढ़ो_script_info(desc, script_path))
		जाओ out;

	अगर (!desc->args)
		जाओ out;

	क्रम (p = desc->args; *p; p++)
		अगर (*p == '<')
			n_args++;
out:
	script_desc__delete(desc);

	वापस n_args;
पूर्ण

अटल पूर्णांक have_cmd(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अक्षर **__argv = दो_स्मृति(माप(स्थिर अक्षर *) * argc);

	अगर (!__argv) अणु
		pr_err("malloc failed\n");
		वापस -1;
	पूर्ण

	स_नकल(__argv, argv, माप(स्थिर अक्षर *) * argc);
	argc = parse_options(argc, (स्थिर अक्षर **)__argv, record_options,
			     शून्य, PARSE_OPT_STOP_AT_NON_OPTION);
	मुक्त(__argv);

	प्रणाली_wide = (argc == 0);

	वापस 0;
पूर्ण

अटल व्योम script__setup_sample_type(काष्ठा perf_script *script)
अणु
	काष्ठा perf_session *session = script->session;
	u64 sample_type = evlist__combined_sample_type(session->evlist);

	अगर (symbol_conf.use_callchain || symbol_conf.cumulate_callchain) अणु
		अगर ((sample_type & PERF_SAMPLE_REGS_USER) &&
		    (sample_type & PERF_SAMPLE_STACK_USER)) अणु
			callchain_param.record_mode = CALLCHAIN_DWARF;
			dwarf_callchain_users = true;
		पूर्ण अन्यथा अगर (sample_type & PERF_SAMPLE_BRANCH_STACK)
			callchain_param.record_mode = CALLCHAIN_LBR;
		अन्यथा
			callchain_param.record_mode = CALLCHAIN_FP;
	पूर्ण

	अगर (script->stitch_lbr && (callchain_param.record_mode != CALLCHAIN_LBR)) अणु
		pr_warning("Can't find LBR callchain. Switch off --stitch-lbr.\n"
			   "Please apply --call-graph lbr when recording.\n");
		script->stitch_lbr = false;
	पूर्ण
पूर्ण

अटल पूर्णांक process_stat_round_event(काष्ठा perf_session *session,
				    जोड़ perf_event *event)
अणु
	काष्ठा perf_record_stat_round *round = &event->stat_round;
	काष्ठा evsel *counter;

	evlist__क्रम_each_entry(session->evlist, counter) अणु
		perf_stat_process_counter(&stat_config, counter);
		process_stat(counter, round->समय);
	पूर्ण

	process_stat_पूर्णांकerval(round->समय);
	वापस 0;
पूर्ण

अटल पूर्णांक process_stat_config_event(काष्ठा perf_session *session __maybe_unused,
				     जोड़ perf_event *event)
अणु
	perf_event__पढ़ो_stat_config(&stat_config, &event->stat_config);
	वापस 0;
पूर्ण

अटल पूर्णांक set_maps(काष्ठा perf_script *script)
अणु
	काष्ठा evlist *evlist = script->session->evlist;

	अगर (!script->cpus || !script->thपढ़ोs)
		वापस 0;

	अगर (WARN_ONCE(script->allocated, "stats double allocation\n"))
		वापस -EINVAL;

	perf_evlist__set_maps(&evlist->core, script->cpus, script->thपढ़ोs);

	अगर (evlist__alloc_stats(evlist, true))
		वापस -ENOMEM;

	script->allocated = true;
	वापस 0;
पूर्ण

अटल
पूर्णांक process_thपढ़ो_map_event(काष्ठा perf_session *session,
			     जोड़ perf_event *event)
अणु
	काष्ठा perf_tool *tool = session->tool;
	काष्ठा perf_script *script = container_of(tool, काष्ठा perf_script, tool);

	अगर (script->thपढ़ोs) अणु
		pr_warning("Extra thread map event, ignoring.\n");
		वापस 0;
	पूर्ण

	script->thपढ़ोs = thपढ़ो_map__new_event(&event->thपढ़ो_map);
	अगर (!script->thपढ़ोs)
		वापस -ENOMEM;

	वापस set_maps(script);
पूर्ण

अटल
पूर्णांक process_cpu_map_event(काष्ठा perf_session *session,
			  जोड़ perf_event *event)
अणु
	काष्ठा perf_tool *tool = session->tool;
	काष्ठा perf_script *script = container_of(tool, काष्ठा perf_script, tool);

	अगर (script->cpus) अणु
		pr_warning("Extra cpu map event, ignoring.\n");
		वापस 0;
	पूर्ण

	script->cpus = cpu_map__new_data(&event->cpu_map.data);
	अगर (!script->cpus)
		वापस -ENOMEM;

	वापस set_maps(script);
पूर्ण

अटल पूर्णांक process_feature_event(काष्ठा perf_session *session,
				 जोड़ perf_event *event)
अणु
	अगर (event->feat.feat_id < HEADER_LAST_FEATURE)
		वापस perf_event__process_feature(session, event);
	वापस 0;
पूर्ण

#अगर_घोषित HAVE_AUXTRACE_SUPPORT
अटल पूर्णांक perf_script__process_auxtrace_info(काष्ठा perf_session *session,
					      जोड़ perf_event *event)
अणु
	काष्ठा perf_tool *tool = session->tool;

	पूर्णांक ret = perf_event__process_auxtrace_info(session, event);

	अगर (ret == 0) अणु
		काष्ठा perf_script *script = container_of(tool, काष्ठा perf_script, tool);

		ret = perf_script__setup_per_event_dump(script);
	पूर्ण

	वापस ret;
पूर्ण
#अन्यथा
#घोषणा perf_script__process_auxtrace_info 0
#पूर्ण_अगर

अटल पूर्णांक parse_insn_trace(स्थिर काष्ठा option *opt __maybe_unused,
			    स्थिर अक्षर *str __maybe_unused,
			    पूर्णांक unset __maybe_unused)
अणु
	parse_output_fields(शून्य, "+insn,-event,-period", 0);
	itrace_parse_synth_opts(opt, "i0ns", 0);
	symbol_conf.nanosecs = true;
	वापस 0;
पूर्ण

अटल पूर्णांक parse_xed(स्थिर काष्ठा option *opt __maybe_unused,
		     स्थिर अक्षर *str __maybe_unused,
		     पूर्णांक unset __maybe_unused)
अणु
	अगर (isatty(1))
		क्रमce_pager("xed -F insn: -A -64 | less");
	अन्यथा
		क्रमce_pager("xed -F insn: -A -64");
	वापस 0;
पूर्ण

अटल पूर्णांक parse_call_trace(स्थिर काष्ठा option *opt __maybe_unused,
			    स्थिर अक्षर *str __maybe_unused,
			    पूर्णांक unset __maybe_unused)
अणु
	parse_output_fields(शून्य, "-ip,-addr,-event,-period,+callindent", 0);
	itrace_parse_synth_opts(opt, "cewp", 0);
	symbol_conf.nanosecs = true;
	symbol_conf.pad_output_len_dso = 50;
	वापस 0;
पूर्ण

अटल पूर्णांक parse_callret_trace(स्थिर काष्ठा option *opt __maybe_unused,
			    स्थिर अक्षर *str __maybe_unused,
			    पूर्णांक unset __maybe_unused)
अणु
	parse_output_fields(शून्य, "-ip,-addr,-event,-period,+callindent,+flags", 0);
	itrace_parse_synth_opts(opt, "crewp", 0);
	symbol_conf.nanosecs = true;
	वापस 0;
पूर्ण

पूर्णांक cmd_script(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	bool show_full_info = false;
	bool header = false;
	bool header_only = false;
	bool script_started = false;
	अक्षर *rec_script_path = शून्य;
	अक्षर *rep_script_path = शून्य;
	काष्ठा perf_session *session;
	काष्ठा itrace_synth_opts itrace_synth_opts = अणु
		.set = false,
		.शेष_no_sample = true,
	पूर्ण;
	काष्ठा utsname uts;
	अक्षर *script_path = शून्य;
	स्थिर अक्षर **__argv;
	पूर्णांक i, j, err = 0;
	काष्ठा perf_script script = अणु
		.tool = अणु
			.sample		 = process_sample_event,
			.mmap		 = perf_event__process_mmap,
			.mmap2		 = perf_event__process_mmap2,
			.comm		 = perf_event__process_comm,
			.namespaces	 = perf_event__process_namespaces,
			.cgroup		 = perf_event__process_cgroup,
			.निकास		 = perf_event__process_निकास,
			.विभाजन		 = perf_event__process_विभाजन,
			.attr		 = process_attr,
			.event_update   = perf_event__process_event_update,
			.tracing_data	 = perf_event__process_tracing_data,
			.feature	 = process_feature_event,
			.build_id	 = perf_event__process_build_id,
			.id_index	 = perf_event__process_id_index,
			.auxtrace_info	 = perf_script__process_auxtrace_info,
			.auxtrace	 = perf_event__process_auxtrace,
			.auxtrace_error	 = perf_event__process_auxtrace_error,
			.stat		 = perf_event__process_stat_event,
			.stat_round	 = process_stat_round_event,
			.stat_config	 = process_stat_config_event,
			.thपढ़ो_map	 = process_thपढ़ो_map_event,
			.cpu_map	 = process_cpu_map_event,
			.ordered_events	 = true,
			.ordering_requires_बारtamps = true,
		पूर्ण,
	पूर्ण;
	काष्ठा perf_data data = अणु
		.mode = PERF_DATA_MODE_READ,
	पूर्ण;
	स्थिर काष्ठा option options[] = अणु
	OPT_BOOLEAN('D', "dump-raw-trace", &dump_trace,
		    "dump raw trace in ASCII"),
	OPT_INCR('v', "verbose", &verbose,
		 "be more verbose (show symbol address, etc)"),
	OPT_BOOLEAN('L', "Latency", &latency_क्रमmat,
		    "show latency attributes (irqs/preemption disabled, etc)"),
	OPT_CALLBACK_NOOPT('l', "list", शून्य, शून्य, "list available scripts",
			   list_available_scripts),
	OPT_CALLBACK('s', "script", शून्य, "name",
		     "script file name (lang:script name, script name, or *)",
		     parse_scriptname),
	OPT_STRING('g', "gen-script", &generate_script_lang, "lang",
		   "generate perf-script.xx script in specified language"),
	OPT_STRING('i', "input", &input_name, "file", "input file name"),
	OPT_BOOLEAN('d', "debug-mode", &debug_mode,
		   "do various checks like samples ordering and lost events"),
	OPT_BOOLEAN(0, "header", &header, "Show data header."),
	OPT_BOOLEAN(0, "header-only", &header_only, "Show only data header."),
	OPT_STRING('k', "vmlinux", &symbol_conf.vmlinux_name,
		   "file", "vmlinux pathname"),
	OPT_STRING(0, "kallsyms", &symbol_conf.kallsyms_name,
		   "file", "kallsyms pathname"),
	OPT_BOOLEAN('G', "hide-call-graph", &no_callchain,
		    "When printing symbols do not display call chain"),
	OPT_CALLBACK(0, "symfs", शून्य, "directory",
		     "Look for files with symbols relative to this directory",
		     symbol__config_symfs),
	OPT_CALLBACK('F', "fields", शून्य, "str",
		     "comma separated output fields prepend with 'type:'. "
		     "+field to add and -field to remove."
		     "Valid types: hw,sw,trace,raw,synth. "
		     "Fields: comm,tid,pid,time,cpu,event,trace,ip,sym,dso,"
		     "addr,symoff,srcline,period,iregs,uregs,brstack,"
		     "brstacksym,flags,bpf-output,brstackinsn,brstackoff,"
		     "callindent,insn,insnlen,synth,phys_addr,metric,misc,ipc,tod,"
		     "data_page_size,code_page_size",
		     parse_output_fields),
	OPT_BOOLEAN('a', "all-cpus", &प्रणाली_wide,
		    "system-wide collection from all CPUs"),
	OPT_STRING(0, "dsos", &symbol_conf.dso_list_str, "dso[,dso...]",
		   "only consider symbols in these DSOs"),
	OPT_STRING('S', "symbols", &symbol_conf.sym_list_str, "symbol[,symbol...]",
		   "only consider these symbols"),
	OPT_INTEGER(0, "addr-range", &symbol_conf.addr_range,
		    "Use with -S to list traced records within address range"),
	OPT_CALLBACK_OPTARG(0, "insn-trace", &itrace_synth_opts, शून्य, शून्य,
			"Decode instructions from itrace", parse_insn_trace),
	OPT_CALLBACK_OPTARG(0, "xed", शून्य, शून्य, शून्य,
			"Run xed disassembler on output", parse_xed),
	OPT_CALLBACK_OPTARG(0, "call-trace", &itrace_synth_opts, शून्य, शून्य,
			"Decode calls from from itrace", parse_call_trace),
	OPT_CALLBACK_OPTARG(0, "call-ret-trace", &itrace_synth_opts, शून्य, शून्य,
			"Decode calls and returns from itrace", parse_callret_trace),
	OPT_STRING(0, "graph-function", &symbol_conf.graph_function, "symbol[,symbol...]",
			"Only print symbols and callees with --call-trace/--call-ret-trace"),
	OPT_STRING(0, "stop-bt", &symbol_conf.bt_stop_list_str, "symbol[,symbol...]",
		   "Stop display of callgraph at these symbols"),
	OPT_STRING('C', "cpu", &cpu_list, "cpu", "list of cpus to profile"),
	OPT_STRING('c', "comms", &symbol_conf.comm_list_str, "comm[,comm...]",
		   "only display events for these comms"),
	OPT_STRING(0, "pid", &symbol_conf.pid_list_str, "pid[,pid...]",
		   "only consider symbols in these pids"),
	OPT_STRING(0, "tid", &symbol_conf.tid_list_str, "tid[,tid...]",
		   "only consider symbols in these tids"),
	OPT_UINTEGER(0, "max-stack", &scripting_max_stack,
		     "Set the maximum stack depth when parsing the callchain, "
		     "anything beyond the specified depth will be ignored. "
		     "Default: kernel.perf_event_max_stack or " __stringअगरy(PERF_MAX_STACK_DEPTH)),
	OPT_BOOLEAN(0, "reltime", &relसमय, "Show time stamps relative to start"),
	OPT_BOOLEAN(0, "deltatime", &deltaसमय, "Show time stamps relative to previous event"),
	OPT_BOOLEAN('I', "show-info", &show_full_info,
		    "display extended information from perf.data file"),
	OPT_BOOLEAN('\0', "show-kernel-path", &symbol_conf.show_kernel_path,
		    "Show the path of [kernel.kallsyms]"),
	OPT_BOOLEAN('\0', "show-task-events", &script.show_task_events,
		    "Show the fork/comm/exit events"),
	OPT_BOOLEAN('\0', "show-mmap-events", &script.show_mmap_events,
		    "Show the mmap events"),
	OPT_BOOLEAN('\0', "show-switch-events", &script.show_चयन_events,
		    "Show context switch events (if recorded)"),
	OPT_BOOLEAN('\0', "show-namespace-events", &script.show_namespace_events,
		    "Show namespace events (if recorded)"),
	OPT_BOOLEAN('\0', "show-cgroup-events", &script.show_cgroup_events,
		    "Show cgroup events (if recorded)"),
	OPT_BOOLEAN('\0', "show-lost-events", &script.show_lost_events,
		    "Show lost events (if recorded)"),
	OPT_BOOLEAN('\0', "show-round-events", &script.show_round_events,
		    "Show round events (if recorded)"),
	OPT_BOOLEAN('\0', "show-bpf-events", &script.show_bpf_events,
		    "Show bpf related events (if recorded)"),
	OPT_BOOLEAN('\0', "show-text-poke-events", &script.show_text_poke_events,
		    "Show text poke related events (if recorded)"),
	OPT_BOOLEAN('\0', "per-event-dump", &script.per_event_dump,
		    "Dump trace output to files named by the monitored events"),
	OPT_BOOLEAN('f', "force", &symbol_conf.force, "don't complain, करो it"),
	OPT_INTEGER(0, "max-blocks", &max_blocks,
		    "Maximum number of code blocks to dump with brstackinsn"),
	OPT_BOOLEAN(0, "ns", &symbol_conf.nanosecs,
		    "Use 9 decimal places when displaying time"),
	OPT_CALLBACK_OPTARG(0, "itrace", &itrace_synth_opts, शून्य, "opts",
			    "Instruction Tracing options\n" ITRACE_HELP,
			    itrace_parse_synth_opts),
	OPT_BOOLEAN(0, "full-source-path", &srcline_full_filename,
			"Show full source file name path for source lines"),
	OPT_BOOLEAN(0, "demangle", &symbol_conf.demangle,
			"Enable symbol demangling"),
	OPT_BOOLEAN(0, "demangle-kernel", &symbol_conf.demangle_kernel,
			"Enable kernel symbol demangling"),
	OPT_STRING(0, "time", &script.समय_str, "str",
		   "Time span of interest (start,stop)"),
	OPT_BOOLEAN(0, "inline", &symbol_conf.अंतरभूत_name,
		    "Show inline function"),
	OPT_STRING(0, "guestmount", &symbol_conf.guesपंचांगount, "directory",
		   "guest mount directory under which every guest os"
		   " instance has a subdir"),
	OPT_STRING(0, "guestvmlinux", &symbol_conf.शेष_guest_vmlinux_name,
		   "file", "file saving guest os vmlinux"),
	OPT_STRING(0, "guestkallsyms", &symbol_conf.शेष_guest_kallsyms,
		   "file", "file saving guest os /proc/kallsyms"),
	OPT_STRING(0, "guestmodules", &symbol_conf.शेष_guest_modules,
		   "file", "file saving guest os /proc/modules"),
	OPT_BOOLEAN('\0', "stitch-lbr", &script.stitch_lbr,
		    "Enable LBR callgraph stitching approach"),
	OPTS_EVSWITCH(&script.evचयन),
	OPT_END()
	पूर्ण;
	स्थिर अक्षर * स्थिर script_subcommands[] = अणु "record", "report", शून्य पूर्ण;
	स्थिर अक्षर *script_usage[] = अणु
		"perf script [<options>]",
		"perf script [<options>] record <script> [<record-options>] <command>",
		"perf script [<options>] report <script> [script-args]",
		"perf script [<options>] <script> [<record-options>] <command>",
		"perf script [<options>] <top-script> [script-args]",
		शून्य
	पूर्ण;

	perf_set_singlethपढ़ोed();

	setup_scripting();

	argc = parse_options_subcommand(argc, argv, options, script_subcommands, script_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);

	अगर (symbol_conf.guesपंचांगount ||
	    symbol_conf.शेष_guest_vmlinux_name ||
	    symbol_conf.शेष_guest_kallsyms ||
	    symbol_conf.शेष_guest_modules) अणु
		/*
		 * Enable guest sample processing.
		 */
		perf_guest = true;
	पूर्ण

	data.path  = input_name;
	data.क्रमce = symbol_conf.क्रमce;

	अगर (argc > 1 && !म_भेदन(argv[0], "rec", म_माप("rec"))) अणु
		rec_script_path = get_script_path(argv[1], RECORD_SUFFIX);
		अगर (!rec_script_path)
			वापस cmd_record(argc, argv);
	पूर्ण

	अगर (argc > 1 && !म_भेदन(argv[0], "rep", म_माप("rep"))) अणु
		rep_script_path = get_script_path(argv[1], REPORT_SUFFIX);
		अगर (!rep_script_path) अणु
			ख_लिखो(मानक_त्रुटि,
				"Please specify a valid report script"
				"(see 'perf script -l' for listing)\n");
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (relसमय && deltaसमय) अणु
		ख_लिखो(मानक_त्रुटि,
			"reltime and deltatime - the two don't get along well. "
			"Please limit to --reltime or --deltatime.\n");
		वापस -1;
	पूर्ण

	अगर ((itrace_synth_opts.callchain || itrace_synth_opts.add_callchain) &&
	    itrace_synth_opts.callchain_sz > scripting_max_stack)
		scripting_max_stack = itrace_synth_opts.callchain_sz;

	/* make sure PERF_EXEC_PATH is set क्रम scripts */
	set_argv_exec_path(get_argv_exec_path());

	अगर (argc && !script_name && !rec_script_path && !rep_script_path) अणु
		पूर्णांक live_pipe[2];
		पूर्णांक rep_args;
		pid_t pid;

		rec_script_path = get_script_path(argv[0], RECORD_SUFFIX);
		rep_script_path = get_script_path(argv[0], REPORT_SUFFIX);

		अगर (!rec_script_path && !rep_script_path) अणु
			usage_with_options_msg(script_usage, options,
				"Couldn't find script `%s'\n\n See perf"
				" script -l for available scripts.\n", argv[0]);
		पूर्ण

		अगर (is_top_script(argv[0])) अणु
			rep_args = argc - 1;
		पूर्ण अन्यथा अणु
			पूर्णांक rec_args;

			rep_args = has_required_arg(rep_script_path);
			rec_args = (argc - 1) - rep_args;
			अगर (rec_args < 0) अणु
				usage_with_options_msg(script_usage, options,
					"`%s' script requires options."
					"\n\n See perf script -l for available "
					"scripts and options.\n", argv[0]);
			पूर्ण
		पूर्ण

		अगर (pipe(live_pipe) < 0) अणु
			लिखो_त्रुटि("failed to create pipe");
			वापस -1;
		पूर्ण

		pid = विभाजन();
		अगर (pid < 0) अणु
			लिखो_त्रुटि("failed to fork");
			वापस -1;
		पूर्ण

		अगर (!pid) अणु
			j = 0;

			dup2(live_pipe[1], 1);
			बंद(live_pipe[0]);

			अगर (is_top_script(argv[0])) अणु
				प्रणाली_wide = true;
			पूर्ण अन्यथा अगर (!प्रणाली_wide) अणु
				अगर (have_cmd(argc - rep_args, &argv[rep_args]) != 0) अणु
					err = -1;
					जाओ out;
				पूर्ण
			पूर्ण

			__argv = दो_स्मृति((argc + 6) * माप(स्थिर अक्षर *));
			अगर (!__argv) अणु
				pr_err("malloc failed\n");
				err = -ENOMEM;
				जाओ out;
			पूर्ण

			__argv[j++] = "/bin/sh";
			__argv[j++] = rec_script_path;
			अगर (प्रणाली_wide)
				__argv[j++] = "-a";
			__argv[j++] = "-q";
			__argv[j++] = "-o";
			__argv[j++] = "-";
			क्रम (i = rep_args + 1; i < argc; i++)
				__argv[j++] = argv[i];
			__argv[j++] = शून्य;

			execvp("/bin/sh", (अक्षर **)__argv);
			मुक्त(__argv);
			निकास(-1);
		पूर्ण

		dup2(live_pipe[0], 0);
		बंद(live_pipe[1]);

		__argv = दो_स्मृति((argc + 4) * माप(स्थिर अक्षर *));
		अगर (!__argv) अणु
			pr_err("malloc failed\n");
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		j = 0;
		__argv[j++] = "/bin/sh";
		__argv[j++] = rep_script_path;
		क्रम (i = 1; i < rep_args + 1; i++)
			__argv[j++] = argv[i];
		__argv[j++] = "-i";
		__argv[j++] = "-";
		__argv[j++] = शून्य;

		execvp("/bin/sh", (अक्षर **)__argv);
		मुक्त(__argv);
		निकास(-1);
	पूर्ण

	अगर (rec_script_path)
		script_path = rec_script_path;
	अगर (rep_script_path)
		script_path = rep_script_path;

	अगर (script_path) अणु
		j = 0;

		अगर (!rec_script_path)
			प्रणाली_wide = false;
		अन्यथा अगर (!प्रणाली_wide) अणु
			अगर (have_cmd(argc - 1, &argv[1]) != 0) अणु
				err = -1;
				जाओ out;
			पूर्ण
		पूर्ण

		__argv = दो_स्मृति((argc + 2) * माप(स्थिर अक्षर *));
		अगर (!__argv) अणु
			pr_err("malloc failed\n");
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		__argv[j++] = "/bin/sh";
		__argv[j++] = script_path;
		अगर (प्रणाली_wide)
			__argv[j++] = "-a";
		क्रम (i = 2; i < argc; i++)
			__argv[j++] = argv[i];
		__argv[j++] = शून्य;

		execvp("/bin/sh", (अक्षर **)__argv);
		मुक्त(__argv);
		निकास(-1);
	पूर्ण

	अगर (!script_name) अणु
		setup_pager();
		use_browser = 0;
	पूर्ण

	session = perf_session__new(&data, false, &script.tool);
	अगर (IS_ERR(session))
		वापस PTR_ERR(session);

	अगर (header || header_only) अणु
		script.tool.show_feat_hdr = SHOW_FEAT_HEADER;
		perf_session__ख_लिखो_info(session, मानक_निकास, show_full_info);
		अगर (header_only)
			जाओ out_delete;
	पूर्ण
	अगर (show_full_info)
		script.tool.show_feat_hdr = SHOW_FEAT_HEADER_FULL_INFO;

	अगर (symbol__init(&session->header.env) < 0)
		जाओ out_delete;

	uname(&uts);
	अगर (data.is_pipe ||  /* assume pipe_mode indicates native_arch */
	    !म_भेद(uts.machine, session->header.env.arch) ||
	    (!म_भेद(uts.machine, "x86_64") &&
	     !म_भेद(session->header.env.arch, "i386")))
		native_arch = true;

	script.session = session;
	script__setup_sample_type(&script);

	अगर ((output[PERF_TYPE_HARDWARE].fields & PERF_OUTPUT_CALLINDENT) ||
	    symbol_conf.graph_function)
		itrace_synth_opts.thपढ़ो_stack = true;

	session->itrace_synth_opts = &itrace_synth_opts;

	अगर (cpu_list) अणु
		err = perf_session__cpu_biपंचांगap(session, cpu_list, cpu_biपंचांगap);
		अगर (err < 0)
			जाओ out_delete;
		itrace_synth_opts.cpu_biपंचांगap = cpu_biपंचांगap;
	पूर्ण

	अगर (!no_callchain)
		symbol_conf.use_callchain = true;
	अन्यथा
		symbol_conf.use_callchain = false;

	अगर (session->tevent.pevent &&
	    tep_set_function_resolver(session->tevent.pevent,
				      machine__resolve_kernel_addr,
				      &session->machines.host) < 0) अणु
		pr_err("%s: failed to set libtraceevent function resolver\n", __func__);
		err = -1;
		जाओ out_delete;
	पूर्ण

	अगर (generate_script_lang) अणु
		काष्ठा stat perf_stat;
		पूर्णांक input;

		अगर (output_set_by_user()) अणु
			ख_लिखो(मानक_त्रुटि,
				"custom fields not supported for generated scripts");
			err = -EINVAL;
			जाओ out_delete;
		पूर्ण

		input = खोलो(data.path, O_RDONLY);	/* input_name */
		अगर (input < 0) अणु
			err = -त्रुटि_सं;
			लिखो_त्रुटि("failed to open file");
			जाओ out_delete;
		पूर्ण

		err = ख_स्थिति(input, &perf_stat);
		अगर (err < 0) अणु
			लिखो_त्रुटि("failed to stat file");
			जाओ out_delete;
		पूर्ण

		अगर (!perf_stat.st_size) अणु
			ख_लिखो(मानक_त्रुटि, "zero-sized file, nothing to do!\n");
			जाओ out_delete;
		पूर्ण

		scripting_ops = script_spec__lookup(generate_script_lang);
		अगर (!scripting_ops) अणु
			ख_लिखो(मानक_त्रुटि, "invalid language specifier");
			err = -ENOENT;
			जाओ out_delete;
		पूर्ण

		err = scripting_ops->generate_script(session->tevent.pevent,
						     "perf-script");
		जाओ out_delete;
	पूर्ण

	अगर (script_name) अणु
		err = scripting_ops->start_script(script_name, argc, argv);
		अगर (err)
			जाओ out_delete;
		pr_debug("perf script started with script %s\n\n", script_name);
		script_started = true;
	पूर्ण


	err = perf_session__check_output_opt(session);
	अगर (err < 0)
		जाओ out_delete;

	अगर (script.समय_str) अणु
		err = perf_समय__parse_क्रम_ranges_relसमय(script.समय_str, session,
						  &script.pसमय_range,
						  &script.range_size,
						  &script.range_num,
						  relसमय);
		अगर (err < 0)
			जाओ out_delete;

		itrace_synth_opts__set_समय_range(&itrace_synth_opts,
						  script.pसमय_range,
						  script.range_num);
	पूर्ण

	err = evचयन__init(&script.evचयन, session->evlist, मानक_त्रुटि);
	अगर (err)
		जाओ out_delete;

	अगर (zstd_init(&(session->zstd_data), 0) < 0)
		pr_warning("Decompression initialization failed. Reported data may be incomplete.\n");

	err = __cmd_script(&script);

	flush_scripting();

out_delete:
	अगर (script.pसमय_range) अणु
		itrace_synth_opts__clear_समय_range(&itrace_synth_opts);
		zमुक्त(&script.pसमय_range);
	पूर्ण

	evlist__मुक्त_stats(session->evlist);
	perf_session__delete(session);

	अगर (script_started)
		cleanup_scripting();
out:
	वापस err;
पूर्ण
