<शैली गुरु>
/*
 * builtin-trace.c
 *
 * Builtin 'trace' command:
 *
 * Display a continuously updated trace of any workload, CPU, specअगरic PID,
 * प्रणाली wide, etc.  Default क्रमmat is loosely strace like, but any other
 * event may be specअगरied using --event.
 *
 * Copyright (C) 2012, 2013, 2014, 2015 Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 *
 * Initially based on the 'trace' prototype by Thomas Gleixner:
 *
 * http://lwn.net/Articles/415728/ ("Announcing a new utility: 'trace'")
 */

#समावेश "util/record.h"
#समावेश <traceevent/event-parse.h>
#समावेश <api/fs/tracing_path.h>
#समावेश <bpf/bpf.h>
#समावेश "util/bpf_map.h"
#समावेश "util/rlimit.h"
#समावेश "builtin.h"
#समावेश "util/cgroup.h"
#समावेश "util/color.h"
#समावेश "util/config.h"
#समावेश "util/debug.h"
#समावेश "util/dso.h"
#समावेश "util/env.h"
#समावेश "util/event.h"
#समावेश "util/evsel.h"
#समावेश "util/evsel_fprintf.h"
#समावेश "util/synthetic-events.h"
#समावेश "util/evlist.h"
#समावेश "util/evswitch.h"
#समावेश "util/mmap.h"
#समावेश <subcmd/pager.h>
#समावेश <subcmd/exec-cmd.h>
#समावेश "util/machine.h"
#समावेश "util/map.h"
#समावेश "util/symbol.h"
#समावेश "util/path.h"
#समावेश "util/session.h"
#समावेश "util/thread.h"
#समावेश <subcmd/parse-options.h>
#समावेश "util/strlist.h"
#समावेश "util/intlist.h"
#समावेश "util/thread_map.h"
#समावेश "util/stat.h"
#समावेश "util/tool.h"
#समावेश "util/util.h"
#समावेश "trace/beauty/beauty.h"
#समावेश "trace-event.h"
#समावेश "util/parse-events.h"
#समावेश "util/bpf-loader.h"
#समावेश "callchain.h"
#समावेश "print_binary.h"
#समावेश "string2.h"
#समावेश "syscalltbl.h"
#समावेश "rb_resort.h"
#समावेश "../perf.h"

#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <poll.h>
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/err.h>
#समावेश <linux/filter.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/समय64.h>
#समावेश <linux/zभाग.स>
#समावेश <fcntl.h>
#समावेश <sys/sysmacros.h>

#समावेश <linux/प्रकार.स>
#समावेश <perf/mmap.h>

#अगर_अघोषित O_CLOEXEC
# define O_CLOEXEC		02000000
#पूर्ण_अगर

#अगर_अघोषित F_LINUX_SPECIFIC_BASE
# define F_LINUX_SPECIFIC_BASE	1024
#पूर्ण_अगर

/*
 * म_से_अदीर्घ: Go from a string to a value, i.e. क्रम msr: MSR_FS_BASE to 0xc0000100
 */
काष्ठा syscall_arg_fmt अणु
	माप_प्रकार	   (*scnम_लिखो)(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
	bool	   (*म_से_अदीर्घ)(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg, u64 *val);
	अचिन्हित दीर्घ (*mask_val)(काष्ठा syscall_arg *arg, अचिन्हित दीर्घ val);
	व्योम	   *parm;
	स्थिर अक्षर *name;
	u16	   nr_entries; // क्रम arrays
	bool	   show_zero;
पूर्ण;

काष्ठा syscall_fmt अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *alias;
	काष्ठा अणु
		स्थिर अक्षर *sys_enter,
			   *sys_निकास;
	पूर्ण	   bpf_prog_name;
	काष्ठा syscall_arg_fmt arg[6];
	u8	   nr_args;
	bool	   errpid;
	bool	   समयout;
	bool	   hexret;
पूर्ण;

काष्ठा trace अणु
	काष्ठा perf_tool	tool;
	काष्ठा syscalltbl	*sctbl;
	काष्ठा अणु
		काष्ठा syscall  *table;
		काष्ठा bpf_map  *map;
		काष्ठा अणु // per syscall BPF_MAP_TYPE_PROG_ARRAY
			काष्ठा bpf_map  *sys_enter,
					*sys_निकास;
		पूर्ण		prog_array;
		काष्ठा अणु
			काष्ठा evsel *sys_enter,
					  *sys_निकास,
					  *augmented;
		पूर्ण		events;
		काष्ठा bpf_program *unaugmented_prog;
	पूर्ण syscalls;
	काष्ठा अणु
		काष्ठा bpf_map *map;
	पूर्ण dump;
	काष्ठा record_opts	opts;
	काष्ठा evlist	*evlist;
	काष्ठा machine		*host;
	काष्ठा thपढ़ो		*current;
	काष्ठा bpf_object	*bpf_obj;
	काष्ठा cgroup		*cgroup;
	u64			base_समय;
	खाता			*output;
	अचिन्हित दीर्घ		nr_events;
	अचिन्हित दीर्घ		nr_events_prपूर्णांकed;
	अचिन्हित दीर्घ		max_events;
	काष्ठा evचयन		evचयन;
	काष्ठा strlist		*ev_qualअगरier;
	काष्ठा अणु
		माप_प्रकार		nr;
		पूर्णांक		*entries;
	पूर्ण			ev_qualअगरier_ids;
	काष्ठा अणु
		माप_प्रकार		nr;
		pid_t		*entries;
		काष्ठा bpf_map  *map;
	पूर्ण			filter_pids;
	द्विगुन			duration_filter;
	द्विगुन			runसमय_ms;
	काष्ठा अणु
		u64		vfs_getname,
				proc_getname;
	पूर्ण stats;
	अचिन्हित पूर्णांक		max_stack;
	अचिन्हित पूर्णांक		min_stack;
	पूर्णांक			raw_augmented_syscalls_args_size;
	bool			raw_augmented_syscalls;
	bool			fd_path_disabled;
	bool			sort_events;
	bool			not_ev_qualअगरier;
	bool			live;
	bool			full_समय;
	bool			sched;
	bool			multiple_thपढ़ोs;
	bool			summary;
	bool			summary_only;
	bool			त्रुटि_सं_summary;
	bool			failure_only;
	bool			show_comm;
	bool			prपूर्णांक_sample;
	bool			show_tool_stats;
	bool			trace_syscalls;
	bool			libtraceevent_prपूर्णांक;
	bool			kernel_syscallchains;
	s16			args_alignment;
	bool			show_tstamp;
	bool			show_duration;
	bool			show_zeros;
	bool			show_arg_names;
	bool			show_string_prefix;
	bool			क्रमce;
	bool			vfs_getname;
	पूर्णांक			trace_pgfaults;
	अक्षर			*perfconfig_events;
	काष्ठा अणु
		काष्ठा ordered_events	data;
		u64			last;
	पूर्ण oe;
पूर्ण;

काष्ठा tp_field अणु
	पूर्णांक offset;
	जोड़ अणु
		u64 (*पूर्णांकeger)(काष्ठा tp_field *field, काष्ठा perf_sample *sample);
		व्योम *(*poपूर्णांकer)(काष्ठा tp_field *field, काष्ठा perf_sample *sample);
	पूर्ण;
पूर्ण;

#घोषणा TP_UINT_FIELD(bits) \
अटल u64 tp_field__u##bits(काष्ठा tp_field *field, काष्ठा perf_sample *sample) \
अणु \
	u##bits value; \
	स_नकल(&value, sample->raw_data + field->offset, माप(value)); \
	वापस value;  \
पूर्ण

TP_UINT_FIELD(8);
TP_UINT_FIELD(16);
TP_UINT_FIELD(32);
TP_UINT_FIELD(64);

#घोषणा TP_UINT_FIELD__SWAPPED(bits) \
अटल u64 tp_field__swapped_u##bits(काष्ठा tp_field *field, काष्ठा perf_sample *sample) \
अणु \
	u##bits value; \
	स_नकल(&value, sample->raw_data + field->offset, माप(value)); \
	वापस bswap_##bits(value);\
पूर्ण

TP_UINT_FIELD__SWAPPED(16);
TP_UINT_FIELD__SWAPPED(32);
TP_UINT_FIELD__SWAPPED(64);

अटल पूर्णांक __tp_field__init_uपूर्णांक(काष्ठा tp_field *field, पूर्णांक size, पूर्णांक offset, bool needs_swap)
अणु
	field->offset = offset;

	चयन (size) अणु
	हाल 1:
		field->पूर्णांकeger = tp_field__u8;
		अवरोध;
	हाल 2:
		field->पूर्णांकeger = needs_swap ? tp_field__swapped_u16 : tp_field__u16;
		अवरोध;
	हाल 4:
		field->पूर्णांकeger = needs_swap ? tp_field__swapped_u32 : tp_field__u32;
		अवरोध;
	हाल 8:
		field->पूर्णांकeger = needs_swap ? tp_field__swapped_u64 : tp_field__u64;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tp_field__init_uपूर्णांक(काष्ठा tp_field *field, काष्ठा tep_क्रमmat_field *क्रमmat_field, bool needs_swap)
अणु
	वापस __tp_field__init_uपूर्णांक(field, क्रमmat_field->size, क्रमmat_field->offset, needs_swap);
पूर्ण

अटल व्योम *tp_field__ptr(काष्ठा tp_field *field, काष्ठा perf_sample *sample)
अणु
	वापस sample->raw_data + field->offset;
पूर्ण

अटल पूर्णांक __tp_field__init_ptr(काष्ठा tp_field *field, पूर्णांक offset)
अणु
	field->offset = offset;
	field->poपूर्णांकer = tp_field__ptr;
	वापस 0;
पूर्ण

अटल पूर्णांक tp_field__init_ptr(काष्ठा tp_field *field, काष्ठा tep_क्रमmat_field *क्रमmat_field)
अणु
	वापस __tp_field__init_ptr(field, क्रमmat_field->offset);
पूर्ण

काष्ठा syscall_tp अणु
	काष्ठा tp_field id;
	जोड़ अणु
		काष्ठा tp_field args, ret;
	पूर्ण;
पूर्ण;

/*
 * The evsel->priv as used by 'perf trace'
 * sc:	क्रम raw_syscalls:sys_अणुenter,निकासपूर्ण and syscalls:sys_अणुenter,निकासपूर्ण_SYSCALLNAME
 * fmt: क्रम all the other tracepoपूर्णांकs
 */
काष्ठा evsel_trace अणु
	काष्ठा syscall_tp	sc;
	काष्ठा syscall_arg_fmt  *fmt;
पूर्ण;

अटल काष्ठा evsel_trace *evsel_trace__new(व्योम)
अणु
	वापस zalloc(माप(काष्ठा evsel_trace));
पूर्ण

अटल व्योम evsel_trace__delete(काष्ठा evsel_trace *et)
अणु
	अगर (et == शून्य)
		वापस;

	zमुक्त(&et->fmt);
	मुक्त(et);
पूर्ण

/*
 * Used with raw_syscalls:sys_अणुenter,निकासपूर्ण and with the
 * syscalls:sys_अणुenter,निकासपूर्ण_SYSCALL tracepoपूर्णांकs
 */
अटल अंतरभूत काष्ठा syscall_tp *__evsel__syscall_tp(काष्ठा evsel *evsel)
अणु
	काष्ठा evsel_trace *et = evsel->priv;

	वापस &et->sc;
पूर्ण

अटल काष्ठा syscall_tp *evsel__syscall_tp(काष्ठा evsel *evsel)
अणु
	अगर (evsel->priv == शून्य) अणु
		evsel->priv = evsel_trace__new();
		अगर (evsel->priv == शून्य)
			वापस शून्य;
	पूर्ण

	वापस __evsel__syscall_tp(evsel);
पूर्ण

/*
 * Used with all the other tracepoपूर्णांकs.
 */
अटल अंतरभूत काष्ठा syscall_arg_fmt *__evsel__syscall_arg_fmt(काष्ठा evsel *evsel)
अणु
	काष्ठा evsel_trace *et = evsel->priv;

	वापस et->fmt;
पूर्ण

अटल काष्ठा syscall_arg_fmt *evsel__syscall_arg_fmt(काष्ठा evsel *evsel)
अणु
	काष्ठा evsel_trace *et = evsel->priv;

	अगर (evsel->priv == शून्य) अणु
		et = evsel->priv = evsel_trace__new();

		अगर (et == शून्य)
			वापस शून्य;
	पूर्ण

	अगर (et->fmt == शून्य) अणु
		et->fmt = सुस्मृति(evsel->tp_क्रमmat->क्रमmat.nr_fields, माप(काष्ठा syscall_arg_fmt));
		अगर (et->fmt == शून्य)
			जाओ out_delete;
	पूर्ण

	वापस __evsel__syscall_arg_fmt(evsel);

out_delete:
	evsel_trace__delete(evsel->priv);
	evsel->priv = शून्य;
	वापस शून्य;
पूर्ण

अटल पूर्णांक evsel__init_tp_uपूर्णांक_field(काष्ठा evsel *evsel, काष्ठा tp_field *field, स्थिर अक्षर *name)
अणु
	काष्ठा tep_क्रमmat_field *क्रमmat_field = evsel__field(evsel, name);

	अगर (क्रमmat_field == शून्य)
		वापस -1;

	वापस tp_field__init_uपूर्णांक(field, क्रमmat_field, evsel->needs_swap);
पूर्ण

#घोषणा perf_evsel__init_sc_tp_uपूर्णांक_field(evsel, name) \
	(अणु काष्ठा syscall_tp *sc = __evsel__syscall_tp(evsel);\
	   evsel__init_tp_uपूर्णांक_field(evsel, &sc->name, #name); पूर्ण)

अटल पूर्णांक evsel__init_tp_ptr_field(काष्ठा evsel *evsel, काष्ठा tp_field *field, स्थिर अक्षर *name)
अणु
	काष्ठा tep_क्रमmat_field *क्रमmat_field = evsel__field(evsel, name);

	अगर (क्रमmat_field == शून्य)
		वापस -1;

	वापस tp_field__init_ptr(field, क्रमmat_field);
पूर्ण

#घोषणा perf_evsel__init_sc_tp_ptr_field(evsel, name) \
	(अणु काष्ठा syscall_tp *sc = __evsel__syscall_tp(evsel);\
	   evsel__init_tp_ptr_field(evsel, &sc->name, #name); पूर्ण)

अटल व्योम evsel__delete_priv(काष्ठा evsel *evsel)
अणु
	zमुक्त(&evsel->priv);
	evsel__delete(evsel);
पूर्ण

अटल पूर्णांक evsel__init_syscall_tp(काष्ठा evsel *evsel)
अणु
	काष्ठा syscall_tp *sc = evsel__syscall_tp(evsel);

	अगर (sc != शून्य) अणु
		अगर (evsel__init_tp_uपूर्णांक_field(evsel, &sc->id, "__syscall_nr") &&
		    evsel__init_tp_uपूर्णांक_field(evsel, &sc->id, "nr"))
			वापस -ENOENT;
		वापस 0;
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक evsel__init_augmented_syscall_tp(काष्ठा evsel *evsel, काष्ठा evsel *tp)
अणु
	काष्ठा syscall_tp *sc = evsel__syscall_tp(evsel);

	अगर (sc != शून्य) अणु
		काष्ठा tep_क्रमmat_field *syscall_id = evsel__field(tp, "id");
		अगर (syscall_id == शून्य)
			syscall_id = evsel__field(tp, "__syscall_nr");
		अगर (syscall_id == शून्य ||
		    __tp_field__init_uपूर्णांक(&sc->id, syscall_id->size, syscall_id->offset, evsel->needs_swap))
			वापस -EINVAL;

		वापस 0;
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक evsel__init_augmented_syscall_tp_args(काष्ठा evsel *evsel)
अणु
	काष्ठा syscall_tp *sc = __evsel__syscall_tp(evsel);

	वापस __tp_field__init_ptr(&sc->args, sc->id.offset + माप(u64));
पूर्ण

अटल पूर्णांक evsel__init_augmented_syscall_tp_ret(काष्ठा evsel *evsel)
अणु
	काष्ठा syscall_tp *sc = __evsel__syscall_tp(evsel);

	वापस __tp_field__init_uपूर्णांक(&sc->ret, माप(u64), sc->id.offset + माप(u64), evsel->needs_swap);
पूर्ण

अटल पूर्णांक evsel__init_raw_syscall_tp(काष्ठा evsel *evsel, व्योम *handler)
अणु
	अगर (evsel__syscall_tp(evsel) != शून्य) अणु
		अगर (perf_evsel__init_sc_tp_uपूर्णांक_field(evsel, id))
			वापस -ENOENT;

		evsel->handler = handler;
		वापस 0;
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल काष्ठा evsel *perf_evsel__raw_syscall_newtp(स्थिर अक्षर *direction, व्योम *handler)
अणु
	काष्ठा evsel *evsel = evsel__newtp("raw_syscalls", direction);

	/* older kernel (e.g., RHEL6) use syscalls:अणुenter,निकासपूर्ण */
	अगर (IS_ERR(evsel))
		evsel = evsel__newtp("syscalls", direction);

	अगर (IS_ERR(evsel))
		वापस शून्य;

	अगर (evsel__init_raw_syscall_tp(evsel, handler))
		जाओ out_delete;

	वापस evsel;

out_delete:
	evsel__delete_priv(evsel);
	वापस शून्य;
पूर्ण

#घोषणा perf_evsel__sc_tp_uपूर्णांक(evsel, name, sample) \
	(अणु काष्ठा syscall_tp *fields = __evsel__syscall_tp(evsel); \
	   fields->name.पूर्णांकeger(&fields->name, sample); पूर्ण)

#घोषणा perf_evsel__sc_tp_ptr(evsel, name, sample) \
	(अणु काष्ठा syscall_tp *fields = __evsel__syscall_tp(evsel); \
	   fields->name.poपूर्णांकer(&fields->name, sample); पूर्ण)

माप_प्रकार strarray__scnम_लिखो_suffix(काष्ठा strarray *sa, अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *पूर्णांकfmt, bool show_suffix, पूर्णांक val)
अणु
	पूर्णांक idx = val - sa->offset;

	अगर (idx < 0 || idx >= sa->nr_entries || sa->entries[idx] == शून्य) अणु
		माप_प्रकार prपूर्णांकed = scnम_लिखो(bf, size, पूर्णांकfmt, val);
		अगर (show_suffix)
			prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, " /* %s??? */", sa->prefix);
		वापस prपूर्णांकed;
	पूर्ण

	वापस scnम_लिखो(bf, size, "%s%s", sa->entries[idx], show_suffix ? sa->prefix : "");
पूर्ण

माप_प्रकार strarray__scnम_लिखो(काष्ठा strarray *sa, अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *पूर्णांकfmt, bool show_prefix, पूर्णांक val)
अणु
	पूर्णांक idx = val - sa->offset;

	अगर (idx < 0 || idx >= sa->nr_entries || sa->entries[idx] == शून्य) अणु
		माप_प्रकार prपूर्णांकed = scnम_लिखो(bf, size, पूर्णांकfmt, val);
		अगर (show_prefix)
			prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, " /* %s??? */", sa->prefix);
		वापस prपूर्णांकed;
	पूर्ण

	वापस scnम_लिखो(bf, size, "%s%s", show_prefix ? sa->prefix : "", sa->entries[idx]);
पूर्ण

अटल माप_प्रकार __syscall_arg__scnम_लिखो_strarray(अक्षर *bf, माप_प्रकार size,
						स्थिर अक्षर *पूर्णांकfmt,
					        काष्ठा syscall_arg *arg)
अणु
	वापस strarray__scnम_लिखो(arg->parm, bf, size, पूर्णांकfmt, arg->show_string_prefix, arg->val);
पूर्ण

अटल माप_प्रकार syscall_arg__scnम_लिखो_strarray(अक्षर *bf, माप_प्रकार size,
					      काष्ठा syscall_arg *arg)
अणु
	वापस __syscall_arg__scnम_लिखो_strarray(bf, size, "%d", arg);
पूर्ण

#घोषणा SCA_STRARRAY syscall_arg__scnम_लिखो_strarray

bool syscall_arg__म_से_अदीर्घ_strarray(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg, u64 *ret)
अणु
	वापस strarray__म_से_अदीर्घ(arg->parm, bf, size, ret);
पूर्ण

bool syscall_arg__म_से_अदीर्घ_strarray_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg, u64 *ret)
अणु
	वापस strarray__म_से_अदीर्घ_flags(arg->parm, bf, size, ret);
पूर्ण

bool syscall_arg__म_से_अदीर्घ_strarrays(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg, u64 *ret)
अणु
	वापस strarrays__म_से_अदीर्घ(arg->parm, bf, size, ret);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_strarray_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	वापस strarray__scnम_लिखो_flags(arg->parm, bf, size, arg->show_string_prefix, arg->val);
पूर्ण

माप_प्रकार strarrays__scnम_लिखो(काष्ठा strarrays *sas, अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *पूर्णांकfmt, bool show_prefix, पूर्णांक val)
अणु
	माप_प्रकार prपूर्णांकed;
	पूर्णांक i;

	क्रम (i = 0; i < sas->nr_entries; ++i) अणु
		काष्ठा strarray *sa = sas->entries[i];
		पूर्णांक idx = val - sa->offset;

		अगर (idx >= 0 && idx < sa->nr_entries) अणु
			अगर (sa->entries[idx] == शून्य)
				अवरोध;
			वापस scnम_लिखो(bf, size, "%s%s", show_prefix ? sa->prefix : "", sa->entries[idx]);
		पूर्ण
	पूर्ण

	prपूर्णांकed = scnम_लिखो(bf, size, पूर्णांकfmt, val);
	अगर (show_prefix)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, " /* %s??? */", sas->entries[0]->prefix);
	वापस prपूर्णांकed;
पूर्ण

bool strarray__म_से_अदीर्घ(काष्ठा strarray *sa, अक्षर *bf, माप_प्रकार size, u64 *ret)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sa->nr_entries; ++i) अणु
		अगर (sa->entries[i] && म_भेदन(sa->entries[i], bf, size) == 0 && sa->entries[i][size] == '\0') अणु
			*ret = sa->offset + i;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

bool strarray__म_से_अदीर्घ_flags(काष्ठा strarray *sa, अक्षर *bf, माप_प्रकार size, u64 *ret)
अणु
	u64 val = 0;
	अक्षर *tok = bf, *sep, *end;

	*ret = 0;

	जबतक (size != 0) अणु
		पूर्णांक toklen = size;

		sep = स_प्रथम(tok, '|', size);
		अगर (sep != शून्य) अणु
			size -= sep - tok + 1;

			end = sep - 1;
			जबतक (end > tok && है_खाली(*end))
				--end;

			toklen = end - tok + 1;
		पूर्ण

		जबतक (है_खाली(*tok))
			++tok;

		अगर (है_अक्षर(*tok) || *tok == '_') अणु
			अगर (!strarray__म_से_अदीर्घ(sa, tok, toklen, &val))
				वापस false;
		पूर्ण अन्यथा अणु
			bool is_hexa = tok[0] == 0 && (tok[1] = 'x' || tok[1] == 'X');

			val = म_से_अदीर्घ(tok, शून्य, is_hexa ? 16 : 0);
		पूर्ण

		*ret |= (1 << (val - 1));

		अगर (sep == शून्य)
			अवरोध;
		tok = sep + 1;
	पूर्ण

	वापस true;
पूर्ण

bool strarrays__म_से_अदीर्घ(काष्ठा strarrays *sas, अक्षर *bf, माप_प्रकार size, u64 *ret)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sas->nr_entries; ++i) अणु
		काष्ठा strarray *sa = sas->entries[i];

		अगर (strarray__म_से_अदीर्घ(sa, bf, size, ret))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_strarrays(अक्षर *bf, माप_प्रकार size,
					काष्ठा syscall_arg *arg)
अणु
	वापस strarrays__scnम_लिखो(arg->parm, bf, size, "%d", arg->show_string_prefix, arg->val);
पूर्ण

#अगर_अघोषित AT_FDCWD
#घोषणा AT_FDCWD	-100
#पूर्ण_अगर

अटल माप_प्रकार syscall_arg__scnम_लिखो_fd_at(अक्षर *bf, माप_प्रकार size,
					   काष्ठा syscall_arg *arg)
अणु
	पूर्णांक fd = arg->val;
	स्थिर अक्षर *prefix = "AT_FD";

	अगर (fd == AT_FDCWD)
		वापस scnम_लिखो(bf, size, "%s%s", arg->show_string_prefix ? prefix : "", "CWD");

	वापस syscall_arg__scnम_लिखो_fd(bf, size, arg);
पूर्ण

#घोषणा SCA_FDAT syscall_arg__scnम_लिखो_fd_at

अटल माप_प्रकार syscall_arg__scnम_लिखो_बंद_fd(अक्षर *bf, माप_प्रकार size,
					      काष्ठा syscall_arg *arg);

#घोषणा SCA_CLOSE_FD syscall_arg__scnम_लिखो_बंद_fd

माप_प्रकार syscall_arg__scnम_लिखो_hex(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	वापस scnम_लिखो(bf, size, "%#lx", arg->val);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_ptr(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अगर (arg->val == 0)
		वापस scnम_लिखो(bf, size, "NULL");
	वापस syscall_arg__scnम_लिखो_hex(bf, size, arg);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_पूर्णांक(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	वापस scnम_लिखो(bf, size, "%d", arg->val);
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_दीर्घ(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	वापस scnम_लिखो(bf, size, "%ld", arg->val);
पूर्ण

अटल माप_प्रकार syscall_arg__scnम_लिखो_अक्षर_array(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	// XXX Hey, maybe क्रम sched:sched_चयन prev/next comm fields we can
	//     fill missing comms using thपढ़ो__set_comm()...
	//     here or in a special syscall_arg__scnम_लिखो_pid_sched_tp...
	वापस scnम_लिखो(bf, size, "\"%-.*s\"", arg->fmt->nr_entries ?: arg->len, arg->val);
पूर्ण

#घोषणा SCA_CHAR_ARRAY syscall_arg__scnम_लिखो_अक्षर_array

अटल स्थिर अक्षर *bpf_cmd[] = अणु
	"MAP_CREATE", "MAP_LOOKUP_ELEM", "MAP_UPDATE_ELEM", "MAP_DELETE_ELEM",
	"MAP_GET_NEXT_KEY", "PROG_LOAD",
पूर्ण;
अटल DEFINE_STRARRAY(bpf_cmd, "BPF_");

अटल स्थिर अक्षर *fsmount_flags[] = अणु
	[1] = "CLOEXEC",
पूर्ण;
अटल DEFINE_STRARRAY(fsmount_flags, "FSMOUNT_");

#समावेश "trace/beauty/generated/fsconfig_arrays.c"

अटल DEFINE_STRARRAY(fsconfig_cmds, "FSCONFIG_");

अटल स्थिर अक्षर *epoll_ctl_ops[] = अणु "ADD", "DEL", "MOD", पूर्ण;
अटल DEFINE_STRARRAY_OFFSET(epoll_ctl_ops, "EPOLL_CTL_", 1);

अटल स्थिर अक्षर *iसमयrs[] = अणु "REAL", "VIRTUAL", "PROF", पूर्ण;
अटल DEFINE_STRARRAY(iसमयrs, "ITIMER_");

अटल स्थिर अक्षर *keyctl_options[] = अणु
	"GET_KEYRING_ID", "JOIN_SESSION_KEYRING", "UPDATE", "REVOKE", "CHOWN",
	"SETPERM", "DESCRIBE", "CLEAR", "LINK", "UNLINK", "SEARCH", "READ",
	"INSTANTIATE", "NEGATE", "SET_REQKEY_KEYRING", "SET_TIMEOUT",
	"ASSUME_AUTHORITY", "GET_SECURITY", "SESSION_TO_PARENT", "REJECT",
	"INSTANTIATE_IOV", "INVALIDATE", "GET_PERSISTENT",
पूर्ण;
अटल DEFINE_STRARRAY(keyctl_options, "KEYCTL_");

अटल स्थिर अक्षर *whences[] = अणु "SET", "CUR", "END",
#अगर_घोषित SEEK_DATA
"DATA",
#पूर्ण_अगर
#अगर_घोषित SEEK_HOLE
"HOLE",
#पूर्ण_अगर
पूर्ण;
अटल DEFINE_STRARRAY(whences, "SEEK_");

अटल स्थिर अक्षर *fcntl_cmds[] = अणु
	"DUPFD", "GETFD", "SETFD", "GETFL", "SETFL", "GETLK", "SETLK",
	"SETLKW", "SETOWN", "GETOWN", "SETSIG", "GETSIG", "GETLK64",
	"SETLK64", "SETLKW64", "SETOWN_EX", "GETOWN_EX",
	"GETOWNER_UIDS",
पूर्ण;
अटल DEFINE_STRARRAY(fcntl_cmds, "F_");

अटल स्थिर अक्षर *fcntl_linux_specअगरic_cmds[] = अणु
	"SETLEASE", "GETLEASE", "NOTIFY", [5] =	"CANCELLK", "DUPFD_CLOEXEC",
	"SETPIPE_SZ", "GETPIPE_SZ", "ADD_SEALS", "GET_SEALS",
	"GET_RW_HINT", "SET_RW_HINT", "GET_FILE_RW_HINT", "SET_FILE_RW_HINT",
पूर्ण;

अटल DEFINE_STRARRAY_OFFSET(fcntl_linux_specअगरic_cmds, "F_", F_LINUX_SPECIFIC_BASE);

अटल काष्ठा strarray *fcntl_cmds_arrays[] = अणु
	&strarray__fcntl_cmds,
	&strarray__fcntl_linux_specअगरic_cmds,
पूर्ण;

अटल DEFINE_STRARRAYS(fcntl_cmds_arrays);

अटल स्थिर अक्षर *rlimit_resources[] = अणु
	"CPU", "FSIZE", "DATA", "STACK", "CORE", "RSS", "NPROC", "NOFILE",
	"MEMLOCK", "AS", "LOCKS", "SIGPENDING", "MSGQUEUE", "NICE", "RTPRIO",
	"RTTIME",
पूर्ण;
अटल DEFINE_STRARRAY(rlimit_resources, "RLIMIT_");

अटल स्थिर अक्षर *sighow[] = अणु "BLOCK", "UNBLOCK", "SETMASK", पूर्ण;
अटल DEFINE_STRARRAY(sighow, "SIG_");

अटल स्थिर अक्षर *घड़ीid[] = अणु
	"REALTIME", "MONOTONIC", "PROCESS_CPUTIME_ID", "THREAD_CPUTIME_ID",
	"MONOTONIC_RAW", "REALTIME_COARSE", "MONOTONIC_COARSE", "BOOTTIME",
	"REALTIME_ALARM", "BOOTTIME_ALARM", "SGI_CYCLE", "TAI"
पूर्ण;
अटल DEFINE_STRARRAY(घड़ीid, "CLOCK_");

अटल माप_प्रकार syscall_arg__scnम_लिखो_access_mode(अक्षर *bf, माप_प्रकार size,
						 काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	स्थिर अक्षर *suffix = "_OK";
	माप_प्रकार prपूर्णांकed = 0;
	पूर्णांक mode = arg->val;

	अगर (mode == F_OK) /* 0 */
		वापस scnम_लिखो(bf, size, "F%s", show_prefix ? suffix : "");
#घोषणा	P_MODE(n) \
	अगर (mode & n##_OK) अणु \
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s", #n, show_prefix ? suffix : ""); \
		mode &= ~n##_OK; \
	पूर्ण

	P_MODE(R);
	P_MODE(W);
	P_MODE(X);
#अघोषित P_MODE

	अगर (mode)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "|%#x", mode);

	वापस prपूर्णांकed;
पूर्ण

#घोषणा SCA_ACCMODE syscall_arg__scnम_लिखो_access_mode

अटल माप_प्रकार syscall_arg__scnम_लिखो_filename(अक्षर *bf, माप_प्रकार size,
					      काष्ठा syscall_arg *arg);

#घोषणा SCA_खाताNAME syscall_arg__scnम_लिखो_filename

अटल माप_प्रकार syscall_arg__scnम_लिखो_pipe_flags(अक्षर *bf, माप_प्रकार size,
						काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	स्थिर अक्षर *prefix = "O_";
	पूर्णांक prपूर्णांकed = 0, flags = arg->val;

#घोषणा	P_FLAG(n) \
	अगर (flags & O_##n) अणु \
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s%s", prपूर्णांकed ? "|" : "", show_prefix ? prefix : "", #n); \
		flags &= ~O_##n; \
	पूर्ण

	P_FLAG(CLOEXEC);
	P_FLAG(NONBLOCK);
#अघोषित P_FLAG

	अगर (flags)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%#x", prपूर्णांकed ? "|" : "", flags);

	वापस prपूर्णांकed;
पूर्ण

#घोषणा SCA_PIPE_FLAGS syscall_arg__scnम_लिखो_pipe_flags

#अगर_अघोषित GRND_NONBLOCK
#घोषणा GRND_NONBLOCK	0x0001
#पूर्ण_अगर
#अगर_अघोषित GRND_RANDOM
#घोषणा GRND_RANDOM	0x0002
#पूर्ण_अगर

अटल माप_प्रकार syscall_arg__scnम_लिखो_getअक्रमom_flags(अक्षर *bf, माप_प्रकार size,
						   काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	स्थिर अक्षर *prefix = "GRND_";
	पूर्णांक prपूर्णांकed = 0, flags = arg->val;

#घोषणा	P_FLAG(n) \
	अगर (flags & GRND_##n) अणु \
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s%s", prपूर्णांकed ? "|" : "", show_prefix ? prefix : "", #n); \
		flags &= ~GRND_##n; \
	पूर्ण

	P_FLAG(RANDOM);
	P_FLAG(NONBLOCK);
#अघोषित P_FLAG

	अगर (flags)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%#x", prपूर्णांकed ? "|" : "", flags);

	वापस prपूर्णांकed;
पूर्ण

#घोषणा SCA_GETRANDOM_FLAGS syscall_arg__scnम_लिखो_getअक्रमom_flags

#घोषणा STRARRAY(name, array) \
	  अणु .scnम_लिखो	= SCA_STRARRAY, \
	    .म_से_अदीर्घ	= STUL_STRARRAY, \
	    .parm	= &strarray__##array, पूर्ण

#घोषणा STRARRAY_FLAGS(name, array) \
	  अणु .scnम_लिखो	= SCA_STRARRAY_FLAGS, \
	    .म_से_अदीर्घ	= STUL_STRARRAY_FLAGS, \
	    .parm	= &strarray__##array, पूर्ण

#समावेश "trace/beauty/arch_errno_names.c"
#समावेश "trace/beauty/eventfd.c"
#समावेश "trace/beauty/futex_op.c"
#समावेश "trace/beauty/futex_val3.c"
#समावेश "trace/beauty/mmap.c"
#समावेश "trace/beauty/mode_t.c"
#समावेश "trace/beauty/msg_flags.c"
#समावेश "trace/beauty/open_flags.c"
#समावेश "trace/beauty/perf_event_open.c"
#समावेश "trace/beauty/pid.c"
#समावेश "trace/beauty/sched_policy.c"
#समावेश "trace/beauty/seccomp.c"
#समावेश "trace/beauty/signum.c"
#समावेश "trace/beauty/socket_type.c"
#समावेश "trace/beauty/waitid_options.c"

अटल काष्ठा syscall_fmt syscall_fmts[] = अणु
	अणु .name	    = "access",
	  .arg = अणु [1] = अणु .scnम_लिखो = SCA_ACCMODE,  /* mode */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "arch_prctl",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_X86_ARCH_PRCTL_CODE, /* code */ पूर्ण,
		   [1] = अणु .scnम_लिखो = SCA_PTR, /* arg2 */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "bind",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_INT, /* fd */ पूर्ण,
		   [1] = अणु .scnम_लिखो = SCA_SOCKADDR, /* umyaddr */ पूर्ण,
		   [2] = अणु .scnम_लिखो = SCA_INT, /* addrlen */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "bpf",
	  .arg = अणु [0] = STRARRAY(cmd, bpf_cmd), पूर्ण, पूर्ण,
	अणु .name	    = "brk",	    .hexret = true,
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_PTR, /* brk */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name     = "clock_gettime",
	  .arg = अणु [0] = STRARRAY(clk_id, घड़ीid), पूर्ण, पूर्ण,
	अणु .name	    = "clone",	    .errpid = true, .nr_args = 5,
	  .arg = अणु [0] = अणु .name = "flags",	    .scnम_लिखो = SCA_CLONE_FLAGS, पूर्ण,
		   [1] = अणु .name = "child_stack",   .scnम_लिखो = SCA_HEX, पूर्ण,
		   [2] = अणु .name = "parent_tidptr", .scnम_लिखो = SCA_HEX, पूर्ण,
		   [3] = अणु .name = "child_tidptr",  .scnम_लिखो = SCA_HEX, पूर्ण,
		   [4] = अणु .name = "tls",	    .scnम_लिखो = SCA_HEX, पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "close",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_CLOSE_FD, /* fd */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "connect",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_INT, /* fd */ पूर्ण,
		   [1] = अणु .scnम_लिखो = SCA_SOCKADDR, /* servaddr */ पूर्ण,
		   [2] = अणु .scnम_लिखो = SCA_INT, /* addrlen */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "epoll_ctl",
	  .arg = अणु [1] = STRARRAY(op, epoll_ctl_ops), पूर्ण, पूर्ण,
	अणु .name	    = "eventfd2",
	  .arg = अणु [1] = अणु .scnम_लिखो = SCA_EFD_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "fchmodat",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT, /* fd */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "fchownat",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT, /* fd */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "fcntl",
	  .arg = अणु [1] = अणु .scnम_लिखो = SCA_FCNTL_CMD,  /* cmd */
			   .म_से_अदीर्घ   = STUL_STRARRAYS,
			   .parm      = &strarrays__fcntl_cmds_arrays,
			   .show_zero = true, पूर्ण,
		   [2] = अणु .scnम_लिखो =  SCA_FCNTL_ARG, /* arg */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "flock",
	  .arg = अणु [1] = अणु .scnम_लिखो = SCA_FLOCK, /* cmd */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name     = "fsconfig",
	  .arg = अणु [1] = STRARRAY(cmd, fsconfig_cmds), पूर्ण, पूर्ण,
	अणु .name     = "fsmount",
	  .arg = अणु [1] = STRARRAY_FLAGS(flags, fsmount_flags),
		   [2] = अणु .scnम_लिखो = SCA_FSMOUNT_ATTR_FLAGS, /* attr_flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name     = "fspick",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT,	  /* dfd */ पूर्ण,
		   [1] = अणु .scnम_लिखो = SCA_खाताNAME,	  /* path */ पूर्ण,
		   [2] = अणु .scnम_लिखो = SCA_FSPICK_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "fstat", .alias = "newfstat", पूर्ण,
	अणु .name	    = "fstatat", .alias = "newfstatat", पूर्ण,
	अणु .name	    = "futex",
	  .arg = अणु [1] = अणु .scnम_लिखो = SCA_FUTEX_OP, /* op */ पूर्ण,
		   [5] = अणु .scnम_लिखो = SCA_FUTEX_VAL3, /* val3 */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "futimesat",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT, /* fd */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "getitimer",
	  .arg = अणु [0] = STRARRAY(which, iसमयrs), पूर्ण, पूर्ण,
	अणु .name	    = "getpid",	    .errpid = true, पूर्ण,
	अणु .name	    = "getpgid",    .errpid = true, पूर्ण,
	अणु .name	    = "getppid",    .errpid = true, पूर्ण,
	अणु .name	    = "getrandom",
	  .arg = अणु [2] = अणु .scnम_लिखो = SCA_GETRANDOM_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "getrlimit",
	  .arg = अणु [0] = STRARRAY(resource, rlimit_resources), पूर्ण, पूर्ण,
	अणु .name	    = "gettid",	    .errpid = true, पूर्ण,
	अणु .name	    = "ioctl",
	  .arg = अणु
#अगर defined(__i386__) || defined(__x86_64__)
/*
 * FIXME: Make this available to all arches.
 */
		   [1] = अणु .scnम_लिखो = SCA_IOCTL_CMD, /* cmd */ पूर्ण,
		   [2] = अणु .scnम_लिखो = SCA_HEX, /* arg */ पूर्ण, पूर्ण, पूर्ण,
#अन्यथा
		   [2] = अणु .scnम_लिखो = SCA_HEX, /* arg */ पूर्ण, पूर्ण, पूर्ण,
#पूर्ण_अगर
	अणु .name	    = "kcmp",	    .nr_args = 5,
	  .arg = अणु [0] = अणु .name = "pid1",	.scnम_लिखो = SCA_PID, पूर्ण,
		   [1] = अणु .name = "pid2",	.scnम_लिखो = SCA_PID, पूर्ण,
		   [2] = अणु .name = "type",	.scnम_लिखो = SCA_KCMP_TYPE, पूर्ण,
		   [3] = अणु .name = "idx1",	.scnम_लिखो = SCA_KCMP_IDX, पूर्ण,
		   [4] = अणु .name = "idx2",	.scnम_लिखो = SCA_KCMP_IDX, पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "keyctl",
	  .arg = अणु [0] = STRARRAY(option, keyctl_options), पूर्ण, पूर्ण,
	अणु .name	    = "kill",
	  .arg = अणु [1] = अणु .scnम_लिखो = SCA_SIGNUM, /* sig */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "linkat",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT, /* fd */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "lseek",
	  .arg = अणु [2] = STRARRAY(whence, whences), पूर्ण, पूर्ण,
	अणु .name	    = "lstat", .alias = "newlstat", पूर्ण,
	अणु .name     = "madvise",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_HEX,      /* start */ पूर्ण,
		   [2] = अणु .scnम_लिखो = SCA_MADV_BHV, /* behavior */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "mkdirat",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT, /* fd */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "mknodat",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT, /* fd */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "mmap",	    .hexret = true,
/* The standard mmap maps to old_mmap on s390x */
#अगर defined(__s390x__)
	.alias = "old_mmap",
#पूर्ण_अगर
	  .arg = अणु [2] = अणु .scnम_लिखो = SCA_MMAP_PROT,	/* prot */ पूर्ण,
		   [3] = अणु .scnम_लिखो = SCA_MMAP_FLAGS,	/* flags */
			   .म_से_अदीर्घ   = STUL_STRARRAY_FLAGS,
			   .parm      = &strarray__mmap_flags, पूर्ण,
		   [5] = अणु .scnम_लिखो = SCA_HEX,	/* offset */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "mount",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_खाताNAME, /* dev_name */ पूर्ण,
		   [3] = अणु .scnम_लिखो = SCA_MOUNT_FLAGS, /* flags */
			   .mask_val  = SCAMV_MOUNT_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "move_mount",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT,	/* from_dfd */ पूर्ण,
		   [1] = अणु .scnम_लिखो = SCA_खाताNAME, /* from_pathname */ पूर्ण,
		   [2] = अणु .scnम_लिखो = SCA_FDAT,	/* to_dfd */ पूर्ण,
		   [3] = अणु .scnम_लिखो = SCA_खाताNAME, /* to_pathname */ पूर्ण,
		   [4] = अणु .scnम_लिखो = SCA_MOVE_MOUNT_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "mprotect",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_HEX,	/* start */ पूर्ण,
		   [2] = अणु .scnम_लिखो = SCA_MMAP_PROT,	/* prot */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "mq_unlink",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_खाताNAME, /* u_name */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "mremap",	    .hexret = true,
	  .arg = अणु [3] = अणु .scnम_लिखो = SCA_MREMAP_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "name_to_handle_at",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT, /* dfd */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "newfstatat",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT, /* dfd */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "open",
	  .arg = अणु [1] = अणु .scnम_लिखो = SCA_OPEN_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "open_by_handle_at",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT,	/* dfd */ पूर्ण,
		   [2] = अणु .scnम_लिखो = SCA_OPEN_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "openat",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT,	/* dfd */ पूर्ण,
		   [2] = अणु .scnम_लिखो = SCA_OPEN_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "perf_event_open",
	  .arg = अणु [2] = अणु .scnम_लिखो = SCA_INT,	/* cpu */ पूर्ण,
		   [3] = अणु .scnम_लिखो = SCA_FD,		/* group_fd */ पूर्ण,
		   [4] = अणु .scnम_लिखो = SCA_PERF_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "pipe2",
	  .arg = अणु [1] = अणु .scnम_लिखो = SCA_PIPE_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "pkey_alloc",
	  .arg = अणु [1] = अणु .scnम_लिखो = SCA_PKEY_ALLOC_ACCESS_RIGHTS,	/* access_rights */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "pkey_free",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_INT,	/* key */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "pkey_mprotect",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_HEX,	/* start */ पूर्ण,
		   [2] = अणु .scnम_लिखो = SCA_MMAP_PROT,	/* prot */ पूर्ण,
		   [3] = अणु .scnम_लिखो = SCA_INT,	/* pkey */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "poll", .समयout = true, पूर्ण,
	अणु .name	    = "ppoll", .समयout = true, पूर्ण,
	अणु .name	    = "prctl",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_PRCTL_OPTION, /* option */
			   .म_से_अदीर्घ   = STUL_STRARRAY,
			   .parm      = &strarray__prctl_options, पूर्ण,
		   [1] = अणु .scnम_लिखो = SCA_PRCTL_ARG2, /* arg2 */ पूर्ण,
		   [2] = अणु .scnम_लिखो = SCA_PRCTL_ARG3, /* arg3 */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "pread", .alias = "pread64", पूर्ण,
	अणु .name	    = "preadv", .alias = "pread", पूर्ण,
	अणु .name	    = "prlimit64",
	  .arg = अणु [1] = STRARRAY(resource, rlimit_resources), पूर्ण, पूर्ण,
	अणु .name	    = "pwrite", .alias = "pwrite64", पूर्ण,
	अणु .name	    = "readlinkat",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT, /* dfd */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "recvfrom",
	  .arg = अणु [3] = अणु .scnम_लिखो = SCA_MSG_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "recvmmsg",
	  .arg = अणु [3] = अणु .scnम_लिखो = SCA_MSG_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "recvmsg",
	  .arg = अणु [2] = अणु .scnम_लिखो = SCA_MSG_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "renameat",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT, /* olddirfd */ पूर्ण,
		   [2] = अणु .scnम_लिखो = SCA_FDAT, /* newdirfd */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "renameat2",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT, /* olddirfd */ पूर्ण,
		   [2] = अणु .scnम_लिखो = SCA_FDAT, /* newdirfd */ पूर्ण,
		   [4] = अणु .scnम_लिखो = SCA_RENAMEAT2_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "rt_sigaction",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_SIGNUM, /* sig */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "rt_sigprocmask",
	  .arg = अणु [0] = STRARRAY(how, sighow), पूर्ण, पूर्ण,
	अणु .name	    = "rt_sigqueueinfo",
	  .arg = अणु [1] = अणु .scnम_लिखो = SCA_SIGNUM, /* sig */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "rt_tgsigqueueinfo",
	  .arg = अणु [2] = अणु .scnम_लिखो = SCA_SIGNUM, /* sig */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "sched_setscheduler",
	  .arg = अणु [1] = अणु .scnम_लिखो = SCA_SCHED_POLICY, /* policy */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "seccomp",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_SECCOMP_OP,	   /* op */ पूर्ण,
		   [1] = अणु .scnम_लिखो = SCA_SECCOMP_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "select", .समयout = true, पूर्ण,
	अणु .name	    = "sendfile", .alias = "sendfile64", पूर्ण,
	अणु .name	    = "sendmmsg",
	  .arg = अणु [3] = अणु .scnम_लिखो = SCA_MSG_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "sendmsg",
	  .arg = अणु [2] = अणु .scnम_लिखो = SCA_MSG_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "sendto",
	  .arg = अणु [3] = अणु .scnम_लिखो = SCA_MSG_FLAGS, /* flags */ पूर्ण,
		   [4] = अणु .scnम_लिखो = SCA_SOCKADDR, /* addr */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "set_tid_address", .errpid = true, पूर्ण,
	अणु .name	    = "setitimer",
	  .arg = अणु [0] = STRARRAY(which, iसमयrs), पूर्ण, पूर्ण,
	अणु .name	    = "setrlimit",
	  .arg = अणु [0] = STRARRAY(resource, rlimit_resources), पूर्ण, पूर्ण,
	अणु .name	    = "socket",
	  .arg = अणु [0] = STRARRAY(family, socket_families),
		   [1] = अणु .scnम_लिखो = SCA_SK_TYPE, /* type */ पूर्ण,
		   [2] = अणु .scnम_लिखो = SCA_SK_PROTO, /* protocol */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "socketpair",
	  .arg = अणु [0] = STRARRAY(family, socket_families),
		   [1] = अणु .scnम_लिखो = SCA_SK_TYPE, /* type */ पूर्ण,
		   [2] = अणु .scnम_लिखो = SCA_SK_PROTO, /* protocol */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "stat", .alias = "newstat", पूर्ण,
	अणु .name	    = "statx",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT,	 /* fdat */ पूर्ण,
		   [2] = अणु .scnम_लिखो = SCA_STATX_FLAGS, /* flags */ पूर्ण ,
		   [3] = अणु .scnम_लिखो = SCA_STATX_MASK,	 /* mask */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "swapoff",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_खाताNAME, /* specialfile */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "swapon",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_खाताNAME, /* specialfile */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "symlinkat",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT, /* dfd */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "sync_file_range",
	  .arg = अणु [3] = अणु .scnम_लिखो = SCA_SYNC_खाता_RANGE_FLAGS, /* flags */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "tgkill",
	  .arg = अणु [2] = अणु .scnम_लिखो = SCA_SIGNUM, /* sig */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "tkill",
	  .arg = अणु [1] = अणु .scnम_लिखो = SCA_SIGNUM, /* sig */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name     = "umount2", .alias = "umount",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_खाताNAME, /* name */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "uname", .alias = "newuname", पूर्ण,
	अणु .name	    = "unlinkat",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT, /* dfd */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "utimensat",
	  .arg = अणु [0] = अणु .scnम_लिखो = SCA_FDAT, /* dirfd */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "wait4",	    .errpid = true,
	  .arg = अणु [2] = अणु .scnम_लिखो = SCA_WAITID_OPTIONS, /* options */ पूर्ण, पूर्ण, पूर्ण,
	अणु .name	    = "waitid",	    .errpid = true,
	  .arg = अणु [3] = अणु .scnम_लिखो = SCA_WAITID_OPTIONS, /* options */ पूर्ण, पूर्ण, पूर्ण,
पूर्ण;

अटल पूर्णांक syscall_fmt__cmp(स्थिर व्योम *name, स्थिर व्योम *fmtp)
अणु
	स्थिर काष्ठा syscall_fmt *fmt = fmtp;
	वापस म_भेद(name, fmt->name);
पूर्ण

अटल काष्ठा syscall_fmt *__syscall_fmt__find(काष्ठा syscall_fmt *fmts, स्थिर पूर्णांक nmemb, स्थिर अक्षर *name)
अणु
	वापस द्वा_खोज(name, fmts, nmemb, माप(काष्ठा syscall_fmt), syscall_fmt__cmp);
पूर्ण

अटल काष्ठा syscall_fmt *syscall_fmt__find(स्थिर अक्षर *name)
अणु
	स्थिर पूर्णांक nmemb = ARRAY_SIZE(syscall_fmts);
	वापस __syscall_fmt__find(syscall_fmts, nmemb, name);
पूर्ण

अटल काष्ठा syscall_fmt *__syscall_fmt__find_by_alias(काष्ठा syscall_fmt *fmts, स्थिर पूर्णांक nmemb, स्थिर अक्षर *alias)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nmemb; ++i) अणु
		अगर (fmts[i].alias && म_भेद(fmts[i].alias, alias) == 0)
			वापस &fmts[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा syscall_fmt *syscall_fmt__find_by_alias(स्थिर अक्षर *alias)
अणु
	स्थिर पूर्णांक nmemb = ARRAY_SIZE(syscall_fmts);
	वापस __syscall_fmt__find_by_alias(syscall_fmts, nmemb, alias);
पूर्ण

/*
 * is_निकास: is this "exit" or "exit_group"?
 * is_खोलो: is this "open" or "openat"? To associate the fd वापसed in sys_निकास with the pathname in sys_enter.
 * args_size: sum of the sizes of the syscall arguments, anything after that is augmented stuff: pathname क्रम खोलोat, etc.
 * nonexistent: Just a hole in the syscall table, syscall id not allocated
 */
काष्ठा syscall अणु
	काष्ठा tep_event    *tp_क्रमmat;
	पूर्णांक		    nr_args;
	पूर्णांक		    args_size;
	काष्ठा अणु
		काष्ठा bpf_program *sys_enter,
				   *sys_निकास;
	पूर्ण		    bpf_prog;
	bool		    is_निकास;
	bool		    is_खोलो;
	bool		    nonexistent;
	काष्ठा tep_क्रमmat_field *args;
	स्थिर अक्षर	    *name;
	काष्ठा syscall_fmt  *fmt;
	काष्ठा syscall_arg_fmt *arg_fmt;
पूर्ण;

/*
 * Must match what is in the BPF program:
 *
 * tools/perf/examples/bpf/augmented_raw_syscalls.c
 */
काष्ठा bpf_map_syscall_entry अणु
	bool	enabled;
	u16	string_args_len[6];
पूर्ण;

/*
 * We need to have this 'calculated' boolean because in some हालs we really
 * करोn't know what is the duration of a syscall, क्रम instance, when we start
 * a session and some thपढ़ोs are रुकोing क्रम a syscall to finish, say 'poll',
 * in which हाल all we can करो is to prपूर्णांक "( ? ) क्रम duration and क्रम the
 * start बारtamp.
 */
अटल माप_प्रकार ख_लिखो_duration(अचिन्हित दीर्घ t, bool calculated, खाता *fp)
अणु
	द्विगुन duration = (द्विगुन)t / NSEC_PER_MSEC;
	माप_प्रकार prपूर्णांकed = ख_लिखो(fp, "(");

	अगर (!calculated)
		prपूर्णांकed += ख_लिखो(fp, "         ");
	अन्यथा अगर (duration >= 1.0)
		prपूर्णांकed += color_ख_लिखो(fp, PERF_COLOR_RED, "%6.3f ms", duration);
	अन्यथा अगर (duration >= 0.01)
		prपूर्णांकed += color_ख_लिखो(fp, PERF_COLOR_YELLOW, "%6.3f ms", duration);
	अन्यथा
		prपूर्णांकed += color_ख_लिखो(fp, PERF_COLOR_NORMAL, "%6.3f ms", duration);
	वापस prपूर्णांकed + ख_लिखो(fp, "): ");
पूर्ण

/**
 * filename.ptr: The filename अक्षर poपूर्णांकer that will be vfs_getname'd
 * filename.entry_str_pos: Where to insert the string translated from
 *                         filename.ptr by the vfs_getname tracepoपूर्णांक/kprobe.
 * ret_scnम_लिखो: syscall args may set this to a dअगरferent syscall वापस
 *                क्रमmatter, क्रम instance, fcntl may वापस fds, file flags, etc.
 */
काष्ठा thपढ़ो_trace अणु
	u64		  entry_समय;
	bool		  entry_pending;
	अचिन्हित दीर्घ	  nr_events;
	अचिन्हित दीर्घ	  pfmaj, pfmin;
	अक्षर		  *entry_str;
	द्विगुन		  runसमय_ms;
	माप_प्रकार		  (*ret_scnम_लिखो)(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg);
        काष्ठा अणु
		अचिन्हित दीर्घ ptr;
		लघु पूर्णांक     entry_str_pos;
		bool	      pending_खोलो;
		अचिन्हित पूर्णांक  namelen;
		अक्षर	      *name;
	पूर्ण filename;
	काष्ठा अणु
		पूर्णांक	      max;
		काष्ठा file   *table;
	पूर्ण files;

	काष्ठा पूर्णांकlist *syscall_stats;
पूर्ण;

अटल काष्ठा thपढ़ो_trace *thपढ़ो_trace__new(व्योम)
अणु
	काष्ठा thपढ़ो_trace *ttrace =  zalloc(माप(काष्ठा thपढ़ो_trace));

	अगर (ttrace) अणु
		ttrace->files.max = -1;
		ttrace->syscall_stats = पूर्णांकlist__new(शून्य);
	पूर्ण

	वापस ttrace;
पूर्ण

अटल काष्ठा thपढ़ो_trace *thपढ़ो__trace(काष्ठा thपढ़ो *thपढ़ो, खाता *fp)
अणु
	काष्ठा thपढ़ो_trace *ttrace;

	अगर (thपढ़ो == शून्य)
		जाओ fail;

	अगर (thपढ़ो__priv(thपढ़ो) == शून्य)
		thपढ़ो__set_priv(thपढ़ो, thपढ़ो_trace__new());

	अगर (thपढ़ो__priv(thपढ़ो) == शून्य)
		जाओ fail;

	ttrace = thपढ़ो__priv(thपढ़ो);
	++ttrace->nr_events;

	वापस ttrace;
fail:
	color_ख_लिखो(fp, PERF_COLOR_RED,
		      "WARNING: not enough memory, dropping samples!\n");
	वापस शून्य;
पूर्ण


व्योम syscall_arg__set_ret_scnम_लिखो(काष्ठा syscall_arg *arg,
				    माप_प्रकार (*ret_scnम_लिखो)(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg))
अणु
	काष्ठा thपढ़ो_trace *ttrace = thपढ़ो__priv(arg->thपढ़ो);

	ttrace->ret_scnम_लिखो = ret_scnम_लिखो;
पूर्ण

#घोषणा TRACE_PFMAJ		(1 << 0)
#घोषणा TRACE_PFMIN		(1 << 1)

अटल स्थिर माप_प्रकार trace__entry_str_size = 2048;

अटल काष्ठा file *thपढ़ो_trace__files_entry(काष्ठा thपढ़ो_trace *ttrace, पूर्णांक fd)
अणु
	अगर (fd < 0)
		वापस शून्य;

	अगर (fd > ttrace->files.max) अणु
		काष्ठा file *nfiles = पुनः_स्मृति(ttrace->files.table, (fd + 1) * माप(काष्ठा file));

		अगर (nfiles == शून्य)
			वापस शून्य;

		अगर (ttrace->files.max != -1) अणु
			स_रखो(nfiles + ttrace->files.max + 1, 0,
			       (fd - ttrace->files.max) * माप(काष्ठा file));
		पूर्ण अन्यथा अणु
			स_रखो(nfiles, 0, (fd + 1) * माप(काष्ठा file));
		पूर्ण

		ttrace->files.table = nfiles;
		ttrace->files.max   = fd;
	पूर्ण

	वापस ttrace->files.table + fd;
पूर्ण

काष्ठा file *thपढ़ो__files_entry(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक fd)
अणु
	वापस thपढ़ो_trace__files_entry(thपढ़ो__priv(thपढ़ो), fd);
पूर्ण

अटल पूर्णांक trace__set_fd_pathname(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक fd, स्थिर अक्षर *pathname)
अणु
	काष्ठा thपढ़ो_trace *ttrace = thपढ़ो__priv(thपढ़ो);
	काष्ठा file *file = thपढ़ो_trace__files_entry(ttrace, fd);

	अगर (file != शून्य) अणु
		काष्ठा stat st;
		अगर (stat(pathname, &st) == 0)
			file->dev_maj = major(st.st_rdev);
		file->pathname = strdup(pathname);
		अगर (file->pathname)
			वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक thपढ़ो__पढ़ो_fd_path(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक fd)
अणु
	अक्षर linkname[PATH_MAX], pathname[PATH_MAX];
	काष्ठा stat st;
	पूर्णांक ret;

	अगर (thपढ़ो->pid_ == thपढ़ो->tid) अणु
		scnम_लिखो(linkname, माप(linkname),
			  "/proc/%d/fd/%d", thपढ़ो->pid_, fd);
	पूर्ण अन्यथा अणु
		scnम_लिखो(linkname, माप(linkname),
			  "/proc/%d/task/%d/fd/%d", thपढ़ो->pid_, thपढ़ो->tid, fd);
	पूर्ण

	अगर (lstat(linkname, &st) < 0 || st.st_size + 1 > (off_t)माप(pathname))
		वापस -1;

	ret = पढ़ोlink(linkname, pathname, माप(pathname));

	अगर (ret < 0 || ret > st.st_size)
		वापस -1;

	pathname[ret] = '\0';
	वापस trace__set_fd_pathname(thपढ़ो, fd, pathname);
पूर्ण

अटल स्थिर अक्षर *thपढ़ो__fd_path(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक fd,
				   काष्ठा trace *trace)
अणु
	काष्ठा thपढ़ो_trace *ttrace = thपढ़ो__priv(thपढ़ो);

	अगर (ttrace == शून्य || trace->fd_path_disabled)
		वापस शून्य;

	अगर (fd < 0)
		वापस शून्य;

	अगर ((fd > ttrace->files.max || ttrace->files.table[fd].pathname == शून्य)) अणु
		अगर (!trace->live)
			वापस शून्य;
		++trace->stats.proc_getname;
		अगर (thपढ़ो__पढ़ो_fd_path(thपढ़ो, fd))
			वापस शून्य;
	पूर्ण

	वापस ttrace->files.table[fd].pathname;
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_fd(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	पूर्णांक fd = arg->val;
	माप_प्रकार prपूर्णांकed = scnम_लिखो(bf, size, "%d", fd);
	स्थिर अक्षर *path = thपढ़ो__fd_path(arg->thपढ़ो, fd, arg->trace);

	अगर (path)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "<%s>", path);

	वापस prपूर्णांकed;
पूर्ण

माप_प्रकार pid__scnम_लिखो_fd(काष्ठा trace *trace, pid_t pid, पूर्णांक fd, अक्षर *bf, माप_प्रकार size)
अणु
        माप_प्रकार prपूर्णांकed = scnम_लिखो(bf, size, "%d", fd);
	काष्ठा thपढ़ो *thपढ़ो = machine__find_thपढ़ो(trace->host, pid, pid);

	अगर (thपढ़ो) अणु
		स्थिर अक्षर *path = thपढ़ो__fd_path(thपढ़ो, fd, trace);

		अगर (path)
			prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "<%s>", path);

		thपढ़ो__put(thपढ़ो);
	पूर्ण

        वापस prपूर्णांकed;
पूर्ण

अटल माप_प्रकार syscall_arg__scnम_लिखो_बंद_fd(अक्षर *bf, माप_प्रकार size,
					      काष्ठा syscall_arg *arg)
अणु
	पूर्णांक fd = arg->val;
	माप_प्रकार prपूर्णांकed = syscall_arg__scnम_लिखो_fd(bf, size, arg);
	काष्ठा thपढ़ो_trace *ttrace = thपढ़ो__priv(arg->thपढ़ो);

	अगर (ttrace && fd >= 0 && fd <= ttrace->files.max)
		zमुक्त(&ttrace->files.table[fd].pathname);

	वापस prपूर्णांकed;
पूर्ण

अटल व्योम thपढ़ो__set_filename_pos(काष्ठा thपढ़ो *thपढ़ो, स्थिर अक्षर *bf,
				     अचिन्हित दीर्घ ptr)
अणु
	काष्ठा thपढ़ो_trace *ttrace = thपढ़ो__priv(thपढ़ो);

	ttrace->filename.ptr = ptr;
	ttrace->filename.entry_str_pos = bf - ttrace->entry_str;
पूर्ण

अटल माप_प्रकार syscall_arg__scnम_लिखो_augmented_string(काष्ठा syscall_arg *arg, अक्षर *bf, माप_प्रकार size)
अणु
	काष्ठा augmented_arg *augmented_arg = arg->augmented.args;
	माप_प्रकार prपूर्णांकed = scnम_लिखो(bf, size, "\"%.*s\"", augmented_arg->size, augmented_arg->value);
	/*
	 * So that the next arg with a payload can consume its augmented arg, i.e. क्रम नाम* syscalls
	 * we would have two strings, each prefixed by its size.
	 */
	पूर्णांक consumed = माप(*augmented_arg) + augmented_arg->size;

	arg->augmented.args = ((व्योम *)arg->augmented.args) + consumed;
	arg->augmented.size -= consumed;

	वापस prपूर्णांकed;
पूर्ण

अटल माप_प्रकार syscall_arg__scnम_लिखो_filename(अक्षर *bf, माप_प्रकार size,
					      काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ ptr = arg->val;

	अगर (arg->augmented.args)
		वापस syscall_arg__scnम_लिखो_augmented_string(arg, bf, size);

	अगर (!arg->trace->vfs_getname)
		वापस scnम_लिखो(bf, size, "%#x", ptr);

	thपढ़ो__set_filename_pos(arg->thपढ़ो, bf, ptr);
	वापस 0;
पूर्ण

अटल bool trace__filter_duration(काष्ठा trace *trace, द्विगुन t)
अणु
	वापस t < (trace->duration_filter * NSEC_PER_MSEC);
पूर्ण

अटल माप_प्रकार __trace__ख_लिखो_tstamp(काष्ठा trace *trace, u64 tstamp, खाता *fp)
अणु
	द्विगुन ts = (द्विगुन)(tstamp - trace->base_समय) / NSEC_PER_MSEC;

	वापस ख_लिखो(fp, "%10.3f ", ts);
पूर्ण

/*
 * We're handling tstamp=0 as an undefined tstamp, i.e. like when we are
 * using ttrace->entry_समय क्रम a thपढ़ो that receives a sys_निकास without
 * first having received a sys_enter ("poll" issued beक्रमe tracing session
 * starts, lost sys_enter निकास due to ring buffer overflow).
 */
अटल माप_प्रकार trace__ख_लिखो_tstamp(काष्ठा trace *trace, u64 tstamp, खाता *fp)
अणु
	अगर (tstamp > 0)
		वापस __trace__ख_लिखो_tstamp(trace, tstamp, fp);

	वापस ख_लिखो(fp, "         ? ");
पूर्ण

अटल bool करोne = false;
अटल bool पूर्णांकerrupted = false;

अटल व्योम sig_handler(पूर्णांक sig)
अणु
	करोne = true;
	पूर्णांकerrupted = sig == संक_विघ्न;
पूर्ण

अटल माप_प्रकार trace__ख_लिखो_comm_tid(काष्ठा trace *trace, काष्ठा thपढ़ो *thपढ़ो, खाता *fp)
अणु
	माप_प्रकार prपूर्णांकed = 0;

	अगर (trace->multiple_thपढ़ोs) अणु
		अगर (trace->show_comm)
			prपूर्णांकed += ख_लिखो(fp, "%.14s/", thपढ़ो__comm_str(thपढ़ो));
		prपूर्णांकed += ख_लिखो(fp, "%d ", thपढ़ो->tid);
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

अटल माप_प्रकार trace__ख_लिखो_entry_head(काष्ठा trace *trace, काष्ठा thपढ़ो *thपढ़ो,
					u64 duration, bool duration_calculated, u64 tstamp, खाता *fp)
अणु
	माप_प्रकार prपूर्णांकed = 0;

	अगर (trace->show_tstamp)
		prपूर्णांकed = trace__ख_लिखो_tstamp(trace, tstamp, fp);
	अगर (trace->show_duration)
		prपूर्णांकed += ख_लिखो_duration(duration, duration_calculated, fp);
	वापस prपूर्णांकed + trace__ख_लिखो_comm_tid(trace, thपढ़ो, fp);
पूर्ण

अटल पूर्णांक trace__process_event(काष्ठा trace *trace, काष्ठा machine *machine,
				जोड़ perf_event *event, काष्ठा perf_sample *sample)
अणु
	पूर्णांक ret = 0;

	चयन (event->header.type) अणु
	हाल PERF_RECORD_LOST:
		color_ख_लिखो(trace->output, PERF_COLOR_RED,
			      "LOST %" PRIu64 " events!\n", event->lost.lost);
		ret = machine__process_lost_event(machine, event, sample);
		अवरोध;
	शेष:
		ret = machine__process_event(machine, event, sample);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक trace__tool_process(काष्ठा perf_tool *tool,
			       जोड़ perf_event *event,
			       काष्ठा perf_sample *sample,
			       काष्ठा machine *machine)
अणु
	काष्ठा trace *trace = container_of(tool, काष्ठा trace, tool);
	वापस trace__process_event(trace, machine, event, sample);
पूर्ण

अटल अक्षर *trace__machine__resolve_kernel_addr(व्योम *vmachine, अचिन्हित दीर्घ दीर्घ *addrp, अक्षर **modp)
अणु
	काष्ठा machine *machine = vmachine;

	अगर (machine->kptr_restrict_warned)
		वापस शून्य;

	अगर (symbol_conf.kptr_restrict) अणु
		pr_warning("Kernel address maps (/proc/{kallsyms,modules}) are restricted.\n\n"
			   "Check /proc/sys/kernel/kptr_restrict and /proc/sys/kernel/perf_event_paranoid.\n\n"
			   "Kernel samples will not be resolved.\n");
		machine->kptr_restrict_warned = true;
		वापस शून्य;
	पूर्ण

	वापस machine__resolve_kernel_addr(vmachine, addrp, modp);
पूर्ण

अटल पूर्णांक trace__symbols_init(काष्ठा trace *trace, काष्ठा evlist *evlist)
अणु
	पूर्णांक err = symbol__init(शून्य);

	अगर (err)
		वापस err;

	trace->host = machine__new_host();
	अगर (trace->host == शून्य)
		वापस -ENOMEM;

	err = trace_event__रेजिस्टर_resolver(trace->host, trace__machine__resolve_kernel_addr);
	अगर (err < 0)
		जाओ out;

	err = __machine__syntheमाप_प्रकारhपढ़ोs(trace->host, &trace->tool, &trace->opts.target,
					    evlist->core.thपढ़ोs, trace__tool_process, false,
					    1);
out:
	अगर (err)
		symbol__निकास();

	वापस err;
पूर्ण

अटल व्योम trace__symbols__निकास(काष्ठा trace *trace)
अणु
	machine__निकास(trace->host);
	trace->host = शून्य;

	symbol__निकास();
पूर्ण

अटल पूर्णांक syscall__alloc_arg_fmts(काष्ठा syscall *sc, पूर्णांक nr_args)
अणु
	पूर्णांक idx;

	अगर (nr_args == 6 && sc->fmt && sc->fmt->nr_args != 0)
		nr_args = sc->fmt->nr_args;

	sc->arg_fmt = सुस्मृति(nr_args, माप(*sc->arg_fmt));
	अगर (sc->arg_fmt == शून्य)
		वापस -1;

	क्रम (idx = 0; idx < nr_args; ++idx) अणु
		अगर (sc->fmt)
			sc->arg_fmt[idx] = sc->fmt->arg[idx];
	पूर्ण

	sc->nr_args = nr_args;
	वापस 0;
पूर्ण

अटल काष्ठा syscall_arg_fmt syscall_arg_fmts__by_name[] = अणु
	अणु .name = "msr",	.scnम_लिखो = SCA_X86_MSR,	  .म_से_अदीर्घ = STUL_X86_MSR,	   पूर्ण,
	अणु .name = "vector",	.scnम_लिखो = SCA_X86_IRQ_VECTORS, .म_से_अदीर्घ = STUL_X86_IRQ_VECTORS, पूर्ण,
पूर्ण;

अटल पूर्णांक syscall_arg_fmt__cmp(स्थिर व्योम *name, स्थिर व्योम *fmtp)
अणु
       स्थिर काष्ठा syscall_arg_fmt *fmt = fmtp;
       वापस म_भेद(name, fmt->name);
पूर्ण

अटल काष्ठा syscall_arg_fmt *
__syscall_arg_fmt__find_by_name(काष्ठा syscall_arg_fmt *fmts, स्थिर पूर्णांक nmemb, स्थिर अक्षर *name)
अणु
       वापस द्वा_खोज(name, fmts, nmemb, माप(काष्ठा syscall_arg_fmt), syscall_arg_fmt__cmp);
पूर्ण

अटल काष्ठा syscall_arg_fmt *syscall_arg_fmt__find_by_name(स्थिर अक्षर *name)
अणु
       स्थिर पूर्णांक nmemb = ARRAY_SIZE(syscall_arg_fmts__by_name);
       वापस __syscall_arg_fmt__find_by_name(syscall_arg_fmts__by_name, nmemb, name);
पूर्ण

अटल काष्ठा tep_क्रमmat_field *
syscall_arg_fmt__init_array(काष्ठा syscall_arg_fmt *arg, काष्ठा tep_क्रमmat_field *field)
अणु
	काष्ठा tep_क्रमmat_field *last_field = शून्य;
	पूर्णांक len;

	क्रम (; field; field = field->next, ++arg) अणु
		last_field = field;

		अगर (arg->scnम_लिखो)
			जारी;

		len = म_माप(field->name);

		अगर (म_भेद(field->type, "const char *") == 0 &&
		    ((len >= 4 && म_भेद(field->name + len - 4, "name") == 0) ||
		     म_माला(field->name, "path") != शून्य))
			arg->scnम_लिखो = SCA_खाताNAME;
		अन्यथा अगर ((field->flags & TEP_FIELD_IS_POINTER) || म_माला(field->name, "addr"))
			arg->scnम_लिखो = SCA_PTR;
		अन्यथा अगर (म_भेद(field->type, "pid_t") == 0)
			arg->scnम_लिखो = SCA_PID;
		अन्यथा अगर (म_भेद(field->type, "umode_t") == 0)
			arg->scnम_लिखो = SCA_MODE_T;
		अन्यथा अगर ((field->flags & TEP_FIELD_IS_ARRAY) && म_माला(field->type, "char")) अणु
			arg->scnम_लिखो = SCA_CHAR_ARRAY;
			arg->nr_entries = field->arraylen;
		पूर्ण अन्यथा अगर ((म_भेद(field->type, "int") == 0 ||
			  म_भेद(field->type, "unsigned int") == 0 ||
			  म_भेद(field->type, "long") == 0) &&
			 len >= 2 && म_भेद(field->name + len - 2, "fd") == 0) अणु
			/*
			 * /sys/kernel/tracing/events/syscalls/sys_enter*
			 * egrep 'field:.*fd;' .../format|sed -r 's/.*field:([a-z ]+) [a-z_]*fd.+/\1/g'|sort|uniq -c
			 * 65 पूर्णांक
			 * 23 अचिन्हित पूर्णांक
			 * 7 अचिन्हित दीर्घ
			 */
			arg->scnम_लिखो = SCA_FD;
               पूर्ण अन्यथा अणु
			काष्ठा syscall_arg_fmt *fmt = syscall_arg_fmt__find_by_name(field->name);

			अगर (fmt) अणु
				arg->scnम_लिखो = fmt->scnम_लिखो;
				arg->म_से_अदीर्घ   = fmt->म_से_अदीर्घ;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस last_field;
पूर्ण

अटल पूर्णांक syscall__set_arg_fmts(काष्ठा syscall *sc)
अणु
	काष्ठा tep_क्रमmat_field *last_field = syscall_arg_fmt__init_array(sc->arg_fmt, sc->args);

	अगर (last_field)
		sc->args_size = last_field->offset + last_field->size;

	वापस 0;
पूर्ण

अटल पूर्णांक trace__पढ़ो_syscall_info(काष्ठा trace *trace, पूर्णांक id)
अणु
	अक्षर tp_name[128];
	काष्ठा syscall *sc;
	स्थिर अक्षर *name = syscalltbl__name(trace->sctbl, id);

#अगर_घोषित HAVE_SYSCALL_TABLE_SUPPORT
	अगर (trace->syscalls.table == शून्य) अणु
		trace->syscalls.table = सुस्मृति(trace->sctbl->syscalls.max_id + 1, माप(*sc));
		अगर (trace->syscalls.table == शून्य)
			वापस -ENOMEM;
	पूर्ण
#अन्यथा
	अगर (id > trace->sctbl->syscalls.max_id || (id == 0 && trace->syscalls.table == शून्य)) अणु
		// When using libaudit we करोn't know beक्रमehand what is the max syscall id
		काष्ठा syscall *table = पुनः_स्मृति(trace->syscalls.table, (id + 1) * माप(*sc));

		अगर (table == शून्य)
			वापस -ENOMEM;

		// Need to स_रखो from offset 0 and +1 members अगर bअक्रम new
		अगर (trace->syscalls.table == शून्य)
			स_रखो(table, 0, (id + 1) * माप(*sc));
		अन्यथा
			स_रखो(table + trace->sctbl->syscalls.max_id + 1, 0, (id - trace->sctbl->syscalls.max_id) * माप(*sc));

		trace->syscalls.table	      = table;
		trace->sctbl->syscalls.max_id = id;
	पूर्ण
#पूर्ण_अगर
	sc = trace->syscalls.table + id;
	अगर (sc->nonexistent)
		वापस 0;

	अगर (name == शून्य) अणु
		sc->nonexistent = true;
		वापस 0;
	पूर्ण

	sc->name = name;
	sc->fmt  = syscall_fmt__find(sc->name);

	snम_लिखो(tp_name, माप(tp_name), "sys_enter_%s", sc->name);
	sc->tp_क्रमmat = trace_event__tp_क्रमmat("syscalls", tp_name);

	अगर (IS_ERR(sc->tp_क्रमmat) && sc->fmt && sc->fmt->alias) अणु
		snम_लिखो(tp_name, माप(tp_name), "sys_enter_%s", sc->fmt->alias);
		sc->tp_क्रमmat = trace_event__tp_क्रमmat("syscalls", tp_name);
	पूर्ण

	अगर (syscall__alloc_arg_fmts(sc, IS_ERR(sc->tp_क्रमmat) ? 6 : sc->tp_क्रमmat->क्रमmat.nr_fields))
		वापस -ENOMEM;

	अगर (IS_ERR(sc->tp_क्रमmat))
		वापस PTR_ERR(sc->tp_क्रमmat);

	sc->args = sc->tp_क्रमmat->क्रमmat.fields;
	/*
	 * We need to check and discard the first variable '__syscall_nr'
	 * or 'nr' that mean the syscall number. It is needless here.
	 * So drop '__syscall_nr' or 'nr' field but करोes not exist on older kernels.
	 */
	अगर (sc->args && (!म_भेद(sc->args->name, "__syscall_nr") || !म_भेद(sc->args->name, "nr"))) अणु
		sc->args = sc->args->next;
		--sc->nr_args;
	पूर्ण

	sc->is_निकास = !म_भेद(name, "exit_group") || !म_भेद(name, "exit");
	sc->is_खोलो = !म_भेद(name, "open") || !म_भेद(name, "openat");

	वापस syscall__set_arg_fmts(sc);
पूर्ण

अटल पूर्णांक evsel__init_tp_arg_scnम_लिखो(काष्ठा evsel *evsel)
अणु
	काष्ठा syscall_arg_fmt *fmt = evsel__syscall_arg_fmt(evsel);

	अगर (fmt != शून्य) अणु
		syscall_arg_fmt__init_array(fmt, evsel->tp_क्रमmat->क्रमmat.fields);
		वापस 0;
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक पूर्णांकcmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर पूर्णांक *one = a, *another = b;

	वापस *one - *another;
पूर्ण

अटल पूर्णांक trace__validate_ev_qualअगरier(काष्ठा trace *trace)
अणु
	पूर्णांक err = 0;
	bool prपूर्णांकed_invalid_prefix = false;
	काष्ठा str_node *pos;
	माप_प्रकार nr_used = 0, nr_allocated = strlist__nr_entries(trace->ev_qualअगरier);

	trace->ev_qualअगरier_ids.entries = दो_स्मृति(nr_allocated *
						 माप(trace->ev_qualअगरier_ids.entries[0]));

	अगर (trace->ev_qualअगरier_ids.entries == शून्य) अणु
		ख_माला_दो("Error:\tNot enough memory for allocating events qualifier ids\n",
		       trace->output);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	strlist__क्रम_each_entry(pos, trace->ev_qualअगरier) अणु
		स्थिर अक्षर *sc = pos->s;
		पूर्णांक id = syscalltbl__id(trace->sctbl, sc), match_next = -1;

		अगर (id < 0) अणु
			id = syscalltbl__strglobmatch_first(trace->sctbl, sc, &match_next);
			अगर (id >= 0)
				जाओ matches;

			अगर (!prपूर्णांकed_invalid_prefix) अणु
				pr_debug("Skipping unknown syscalls: ");
				prपूर्णांकed_invalid_prefix = true;
			पूर्ण अन्यथा अणु
				pr_debug(", ");
			पूर्ण

			pr_debug("%s", sc);
			जारी;
		पूर्ण
matches:
		trace->ev_qualअगरier_ids.entries[nr_used++] = id;
		अगर (match_next == -1)
			जारी;

		जबतक (1) अणु
			id = syscalltbl__strglobmatch_next(trace->sctbl, sc, &match_next);
			अगर (id < 0)
				अवरोध;
			अगर (nr_allocated == nr_used) अणु
				व्योम *entries;

				nr_allocated += 8;
				entries = पुनः_स्मृति(trace->ev_qualअगरier_ids.entries,
						  nr_allocated * माप(trace->ev_qualअगरier_ids.entries[0]));
				अगर (entries == शून्य) अणु
					err = -ENOMEM;
					ख_माला_दो("\nError:\t Not enough memory for parsing\n", trace->output);
					जाओ out_मुक्त;
				पूर्ण
				trace->ev_qualअगरier_ids.entries = entries;
			पूर्ण
			trace->ev_qualअगरier_ids.entries[nr_used++] = id;
		पूर्ण
	पूर्ण

	trace->ev_qualअगरier_ids.nr = nr_used;
	क्विक(trace->ev_qualअगरier_ids.entries, nr_used, माप(पूर्णांक), पूर्णांकcmp);
out:
	अगर (prपूर्णांकed_invalid_prefix)
		pr_debug("\n");
	वापस err;
out_मुक्त:
	zमुक्त(&trace->ev_qualअगरier_ids.entries);
	trace->ev_qualअगरier_ids.nr = 0;
	जाओ out;
पूर्ण

अटल __maybe_unused bool trace__syscall_enabled(काष्ठा trace *trace, पूर्णांक id)
अणु
	bool in_ev_qualअगरier;

	अगर (trace->ev_qualअगरier_ids.nr == 0)
		वापस true;

	in_ev_qualअगरier = द्वा_खोज(&id, trace->ev_qualअगरier_ids.entries,
				  trace->ev_qualअगरier_ids.nr, माप(पूर्णांक), पूर्णांकcmp) != शून्य;

	अगर (in_ev_qualअगरier)
	       वापस !trace->not_ev_qualअगरier;

	वापस trace->not_ev_qualअगरier;
पूर्ण

/*
 * args is to be पूर्णांकerpreted as a series of दीर्घs but we need to handle
 * 8-byte unaligned accesses. args poपूर्णांकs to raw_data within the event
 * and raw_data is guaranteed to be 8-byte unaligned because it is
 * preceded by raw_size which is a u32. So we need to copy args to a temp
 * variable to पढ़ो it. Most notably this aव्योमs extended load inकाष्ठाions
 * on unaligned addresses
 */
अचिन्हित दीर्घ syscall_arg__val(काष्ठा syscall_arg *arg, u8 idx)
अणु
	अचिन्हित दीर्घ val;
	अचिन्हित अक्षर *p = arg->args + माप(अचिन्हित दीर्घ) * idx;

	स_नकल(&val, p, माप(val));
	वापस val;
पूर्ण

अटल माप_प्रकार syscall__scnम_लिखो_name(काष्ठा syscall *sc, अक्षर *bf, माप_प्रकार size,
				      काष्ठा syscall_arg *arg)
अणु
	अगर (sc->arg_fmt && sc->arg_fmt[arg->idx].name)
		वापस scnम_लिखो(bf, size, "%s: ", sc->arg_fmt[arg->idx].name);

	वापस scnम_लिखो(bf, size, "arg%d: ", arg->idx);
पूर्ण

/*
 * Check अगर the value is in fact zero, i.e. mask whatever needs masking, such
 * as mount 'flags' argument that needs ignoring some magic flag, see comment
 * in tools/perf/trace/beauty/mount_flags.c
 */
अटल अचिन्हित दीर्घ syscall_arg_fmt__mask_val(काष्ठा syscall_arg_fmt *fmt, काष्ठा syscall_arg *arg, अचिन्हित दीर्घ val)
अणु
	अगर (fmt && fmt->mask_val)
		वापस fmt->mask_val(arg, val);

	वापस val;
पूर्ण

अटल माप_प्रकार syscall_arg_fmt__scnम_लिखो_val(काष्ठा syscall_arg_fmt *fmt, अक्षर *bf, माप_प्रकार size,
					     काष्ठा syscall_arg *arg, अचिन्हित दीर्घ val)
अणु
	अगर (fmt && fmt->scnम_लिखो) अणु
		arg->val = val;
		अगर (fmt->parm)
			arg->parm = fmt->parm;
		वापस fmt->scnम_लिखो(bf, size, arg);
	पूर्ण
	वापस scnम_लिखो(bf, size, "%ld", val);
पूर्ण

अटल माप_प्रकार syscall__scnम_लिखो_args(काष्ठा syscall *sc, अक्षर *bf, माप_प्रकार size,
				      अचिन्हित अक्षर *args, व्योम *augmented_args, पूर्णांक augmented_args_size,
				      काष्ठा trace *trace, काष्ठा thपढ़ो *thपढ़ो)
अणु
	माप_प्रकार prपूर्णांकed = 0;
	अचिन्हित दीर्घ val;
	u8 bit = 1;
	काष्ठा syscall_arg arg = अणु
		.args	= args,
		.augmented = अणु
			.size = augmented_args_size,
			.args = augmented_args,
		पूर्ण,
		.idx	= 0,
		.mask	= 0,
		.trace  = trace,
		.thपढ़ो = thपढ़ो,
		.show_string_prefix = trace->show_string_prefix,
	पूर्ण;
	काष्ठा thपढ़ो_trace *ttrace = thपढ़ो__priv(thपढ़ो);

	/*
	 * Things like fcntl will set this in its 'cmd' क्रमmatter to pick the
	 * right क्रमmatter क्रम the वापस value (an fd? file flags?), which is
	 * not needed क्रम syscalls that always वापस a given type, say an fd.
	 */
	ttrace->ret_scnम_लिखो = शून्य;

	अगर (sc->args != शून्य) अणु
		काष्ठा tep_क्रमmat_field *field;

		क्रम (field = sc->args; field;
		     field = field->next, ++arg.idx, bit <<= 1) अणु
			अगर (arg.mask & bit)
				जारी;

			arg.fmt = &sc->arg_fmt[arg.idx];
			val = syscall_arg__val(&arg, arg.idx);
			/*
			 * Some syscall args need some mask, most करोn't and
			 * वापस val untouched.
			 */
			val = syscall_arg_fmt__mask_val(&sc->arg_fmt[arg.idx], &arg, val);

			/*
 			 * Suppress this argument अगर its value is zero and
 			 * and we करोn't have a string associated in an
 			 * strarray क्रम it.
 			 */
			अगर (val == 0 &&
			    !trace->show_zeros &&
			    !(sc->arg_fmt &&
			      (sc->arg_fmt[arg.idx].show_zero ||
			       sc->arg_fmt[arg.idx].scnम_लिखो == SCA_STRARRAY ||
			       sc->arg_fmt[arg.idx].scnम_लिखो == SCA_STRARRAYS) &&
			      sc->arg_fmt[arg.idx].parm))
				जारी;

			prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s", prपूर्णांकed ? ", " : "");

			अगर (trace->show_arg_names)
				prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s: ", field->name);

			prपूर्णांकed += syscall_arg_fmt__scnम_लिखो_val(&sc->arg_fmt[arg.idx],
								  bf + prपूर्णांकed, size - prपूर्णांकed, &arg, val);
		पूर्ण
	पूर्ण अन्यथा अगर (IS_ERR(sc->tp_क्रमmat)) अणु
		/*
		 * If we managed to पढ़ो the tracepoपूर्णांक /क्रमmat file, then we
		 * may end up not having any args, like with gettid(), so only
		 * prपूर्णांक the raw args when we didn't manage to पढ़ो it.
		 */
		जबतक (arg.idx < sc->nr_args) अणु
			अगर (arg.mask & bit)
				जाओ next_arg;
			val = syscall_arg__val(&arg, arg.idx);
			अगर (prपूर्णांकed)
				prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, ", ");
			prपूर्णांकed += syscall__scnम_लिखो_name(sc, bf + prपूर्णांकed, size - prपूर्णांकed, &arg);
			prपूर्णांकed += syscall_arg_fmt__scnम_लिखो_val(&sc->arg_fmt[arg.idx], bf + prपूर्णांकed, size - prपूर्णांकed, &arg, val);
next_arg:
			++arg.idx;
			bit <<= 1;
		पूर्ण
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

प्रकार पूर्णांक (*tracepoपूर्णांक_handler)(काष्ठा trace *trace, काष्ठा evsel *evsel,
				  जोड़ perf_event *event,
				  काष्ठा perf_sample *sample);

अटल काष्ठा syscall *trace__syscall_info(काष्ठा trace *trace,
					   काष्ठा evsel *evsel, पूर्णांक id)
अणु
	पूर्णांक err = 0;

	अगर (id < 0) अणु

		/*
		 * XXX: Noticed on x86_64, reproduced as far back as 3.0.36, haven't tried
		 * beक्रमe that, leaving at a higher verbosity level till that is
		 * explained. Reproduced with plain ftrace with:
		 *
		 * echo 1 > /t/events/raw_syscalls/sys_निकास/enable
		 * grep "NR -1 " /t/trace_pipe
		 *
		 * After generating some load on the machine.
 		 */
		अगर (verbose > 1) अणु
			अटल u64 n;
			ख_लिखो(trace->output, "Invalid syscall %d id, skipping (%s, %" PRIu64 ") ...\n",
				id, evsel__name(evsel), ++n);
		पूर्ण
		वापस शून्य;
	पूर्ण

	err = -EINVAL;

#अगर_घोषित HAVE_SYSCALL_TABLE_SUPPORT
	अगर (id > trace->sctbl->syscalls.max_id) अणु
#अन्यथा
	अगर (id >= trace->sctbl->syscalls.max_id) अणु
		/*
		 * With libaudit we करोn't know beक्रमehand what is the max_id,
		 * so we let trace__पढ़ो_syscall_info() figure that out as we
		 * go on पढ़ोing syscalls.
		 */
		err = trace__पढ़ो_syscall_info(trace, id);
		अगर (err)
#पूर्ण_अगर
		जाओ out_cant_पढ़ो;
	पूर्ण

	अगर ((trace->syscalls.table == शून्य || trace->syscalls.table[id].name == शून्य) &&
	    (err = trace__पढ़ो_syscall_info(trace, id)) != 0)
		जाओ out_cant_पढ़ो;

	अगर (trace->syscalls.table[id].name == शून्य) अणु
		अगर (trace->syscalls.table[id].nonexistent)
			वापस शून्य;
		जाओ out_cant_पढ़ो;
	पूर्ण

	वापस &trace->syscalls.table[id];

out_cant_पढ़ो:
	अगर (verbose > 0) अणु
		अक्षर sbuf[STRERR_बफ_मानE];
		ख_लिखो(trace->output, "Problems reading syscall %d: %d (%s)", id, -err, str_error_r(-err, sbuf, माप(sbuf)));
		अगर (id <= trace->sctbl->syscalls.max_id && trace->syscalls.table[id].name != शून्य)
			ख_लिखो(trace->output, "(%s)", trace->syscalls.table[id].name);
		ख_माला_दो(" information\n", trace->output);
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा syscall_stats अणु
	काष्ठा stats stats;
	u64	     nr_failures;
	पूर्णांक	     max_त्रुटि_सं;
	u32	     *त्रुटि_संs;
पूर्ण;

अटल व्योम thपढ़ो__update_stats(काष्ठा thपढ़ो *thपढ़ो, काष्ठा thपढ़ो_trace *ttrace,
				 पूर्णांक id, काष्ठा perf_sample *sample, दीर्घ err, bool त्रुटि_सं_summary)
अणु
	काष्ठा पूर्णांक_node *inode;
	काष्ठा syscall_stats *stats;
	u64 duration = 0;

	inode = पूर्णांकlist__findnew(ttrace->syscall_stats, id);
	अगर (inode == शून्य)
		वापस;

	stats = inode->priv;
	अगर (stats == शून्य) अणु
		stats = दो_स्मृति(माप(*stats));
		अगर (stats == शून्य)
			वापस;

		stats->nr_failures = 0;
		stats->max_त्रुटि_सं   = 0;
		stats->त्रुटि_संs	   = शून्य;
		init_stats(&stats->stats);
		inode->priv = stats;
	पूर्ण

	अगर (ttrace->entry_समय && sample->समय > ttrace->entry_समय)
		duration = sample->समय - ttrace->entry_समय;

	update_stats(&stats->stats, duration);

	अगर (err < 0) अणु
		++stats->nr_failures;

		अगर (!त्रुटि_सं_summary)
			वापस;

		err = -err;
		अगर (err > stats->max_त्रुटि_सं) अणु
			u32 *new_त्रुटि_संs = पुनः_स्मृति(stats->त्रुटि_संs, err * माप(u32));

			अगर (new_त्रुटि_संs) अणु
				स_रखो(new_त्रुटि_संs + stats->max_त्रुटि_सं, 0, (err - stats->max_त्रुटि_सं) * माप(u32));
			पूर्ण अन्यथा अणु
				pr_debug("Not enough memory for errno stats for thread \"%s\"(%d/%d), results will be incomplete\n",
					 thपढ़ो__comm_str(thपढ़ो), thपढ़ो->pid_, thपढ़ो->tid);
				वापस;
			पूर्ण

			stats->त्रुटि_संs = new_त्रुटि_संs;
			stats->max_त्रुटि_सं = err;
		पूर्ण

		++stats->त्रुटि_संs[err - 1];
	पूर्ण
पूर्ण

अटल पूर्णांक trace__म_लिखो_पूर्णांकerrupted_entry(काष्ठा trace *trace)
अणु
	काष्ठा thपढ़ो_trace *ttrace;
	माप_प्रकार prपूर्णांकed;
	पूर्णांक len;

	अगर (trace->failure_only || trace->current == शून्य)
		वापस 0;

	ttrace = thपढ़ो__priv(trace->current);

	अगर (!ttrace->entry_pending)
		वापस 0;

	prपूर्णांकed  = trace__ख_लिखो_entry_head(trace, trace->current, 0, false, ttrace->entry_समय, trace->output);
	prपूर्णांकed += len = ख_लिखो(trace->output, "%s)", ttrace->entry_str);

	अगर (len < trace->args_alignment - 4)
		prपूर्णांकed += ख_लिखो(trace->output, "%-*s", trace->args_alignment - 4 - len, " ");

	prपूर्णांकed += ख_लिखो(trace->output, " ...\n");

	ttrace->entry_pending = false;
	++trace->nr_events_prपूर्णांकed;

	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक trace__ख_लिखो_sample(काष्ठा trace *trace, काष्ठा evsel *evsel,
				 काष्ठा perf_sample *sample, काष्ठा thपढ़ो *thपढ़ो)
अणु
	पूर्णांक prपूर्णांकed = 0;

	अगर (trace->prपूर्णांक_sample) अणु
		द्विगुन ts = (द्विगुन)sample->समय / NSEC_PER_MSEC;

		prपूर्णांकed += ख_लिखो(trace->output, "%22s %10.3f %s %d/%d [%d]\n",
				   evsel__name(evsel), ts,
				   thपढ़ो__comm_str(thपढ़ो),
				   sample->pid, sample->tid, sample->cpu);
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

अटल व्योम *syscall__augmented_args(काष्ठा syscall *sc, काष्ठा perf_sample *sample, पूर्णांक *augmented_args_size, पूर्णांक raw_augmented_args_size)
अणु
	व्योम *augmented_args = शून्य;
	/*
	 * For now with BPF raw_augmented we hook पूर्णांकo raw_syscalls:sys_enter
	 * and there we get all 6 syscall args plus the tracepoपूर्णांक common fields
	 * that माला_लो calculated at the start and the syscall_nr (another दीर्घ).
	 * So we check अगर that is the हाल and अगर so करोn't look after the
	 * sc->args_size but always after the full raw_syscalls:sys_enter payload,
	 * which is fixed.
	 *
	 * We'll revisit this later to pass s->args_size to the BPF augmenter
	 * (now tools/perf/examples/bpf/augmented_raw_syscalls.c, so that it
	 * copies only what we need क्रम each syscall, like what happens when we
	 * use syscalls:sys_enter_NAME, so that we reduce the kernel/userspace
	 * traffic to just what is needed क्रम each syscall.
	 */
	पूर्णांक args_size = raw_augmented_args_size ?: sc->args_size;

	*augmented_args_size = sample->raw_size - args_size;
	अगर (*augmented_args_size > 0)
		augmented_args = sample->raw_data + args_size;

	वापस augmented_args;
पूर्ण

अटल पूर्णांक trace__sys_enter(काष्ठा trace *trace, काष्ठा evsel *evsel,
			    जोड़ perf_event *event __maybe_unused,
			    काष्ठा perf_sample *sample)
अणु
	अक्षर *msg;
	व्योम *args;
	पूर्णांक prपूर्णांकed = 0;
	काष्ठा thपढ़ो *thपढ़ो;
	पूर्णांक id = perf_evsel__sc_tp_uपूर्णांक(evsel, id, sample), err = -1;
	पूर्णांक augmented_args_size = 0;
	व्योम *augmented_args = शून्य;
	काष्ठा syscall *sc = trace__syscall_info(trace, evsel, id);
	काष्ठा thपढ़ो_trace *ttrace;

	अगर (sc == शून्य)
		वापस -1;

	thपढ़ो = machine__findnew_thपढ़ो(trace->host, sample->pid, sample->tid);
	ttrace = thपढ़ो__trace(thपढ़ो, trace->output);
	अगर (ttrace == शून्य)
		जाओ out_put;

	trace__ख_लिखो_sample(trace, evsel, sample, thपढ़ो);

	args = perf_evsel__sc_tp_ptr(evsel, args, sample);

	अगर (ttrace->entry_str == शून्य) अणु
		ttrace->entry_str = दो_स्मृति(trace__entry_str_size);
		अगर (!ttrace->entry_str)
			जाओ out_put;
	पूर्ण

	अगर (!(trace->duration_filter || trace->summary_only || trace->min_stack))
		trace__म_लिखो_पूर्णांकerrupted_entry(trace);
	/*
	 * If this is raw_syscalls.sys_enter, then it always comes with the 6 possible
	 * arguments, even अगर the syscall being handled, say "openat", uses only 4 arguments
	 * this अवरोधs syscall__augmented_args() check क्रम augmented args, as we calculate
	 * syscall->args_size using each syscalls:sys_enter_NAME tracefs क्रमmat file,
	 * so when handling, say the खोलोat syscall, we end up getting 6 args क्रम the
	 * raw_syscalls:sys_enter event, when we expected just 4, we end up mistakenly
	 * thinking that the extra 2 u64 args are the augmented filename, so just check
	 * here and aव्योम using augmented syscalls when the evsel is the raw_syscalls one.
	 */
	अगर (evsel != trace->syscalls.events.sys_enter)
		augmented_args = syscall__augmented_args(sc, sample, &augmented_args_size, trace->raw_augmented_syscalls_args_size);
	ttrace->entry_समय = sample->समय;
	msg = ttrace->entry_str;
	prपूर्णांकed += scnम_लिखो(msg + prपूर्णांकed, trace__entry_str_size - prपूर्णांकed, "%s(", sc->name);

	prपूर्णांकed += syscall__scnम_लिखो_args(sc, msg + prपूर्णांकed, trace__entry_str_size - prपूर्णांकed,
					   args, augmented_args, augmented_args_size, trace, thपढ़ो);

	अगर (sc->is_निकास) अणु
		अगर (!(trace->duration_filter || trace->summary_only || trace->failure_only || trace->min_stack)) अणु
			पूर्णांक alignment = 0;

			trace__ख_लिखो_entry_head(trace, thपढ़ो, 0, false, ttrace->entry_समय, trace->output);
			prपूर्णांकed = ख_लिखो(trace->output, "%s)", ttrace->entry_str);
			अगर (trace->args_alignment > prपूर्णांकed)
				alignment = trace->args_alignment - prपूर्णांकed;
			ख_लिखो(trace->output, "%*s= ?\n", alignment, " ");
		पूर्ण
	पूर्ण अन्यथा अणु
		ttrace->entry_pending = true;
		/* See trace__vfs_getname & trace__sys_निकास */
		ttrace->filename.pending_खोलो = false;
	पूर्ण

	अगर (trace->current != thपढ़ो) अणु
		thपढ़ो__put(trace->current);
		trace->current = thपढ़ो__get(thपढ़ो);
	पूर्ण
	err = 0;
out_put:
	thपढ़ो__put(thपढ़ो);
	वापस err;
पूर्ण

अटल पूर्णांक trace__ख_लिखो_sys_enter(काष्ठा trace *trace, काष्ठा evsel *evsel,
				    काष्ठा perf_sample *sample)
अणु
	काष्ठा thपढ़ो_trace *ttrace;
	काष्ठा thपढ़ो *thपढ़ो;
	पूर्णांक id = perf_evsel__sc_tp_uपूर्णांक(evsel, id, sample), err = -1;
	काष्ठा syscall *sc = trace__syscall_info(trace, evsel, id);
	अक्षर msg[1024];
	व्योम *args, *augmented_args = शून्य;
	पूर्णांक augmented_args_size;

	अगर (sc == शून्य)
		वापस -1;

	thपढ़ो = machine__findnew_thपढ़ो(trace->host, sample->pid, sample->tid);
	ttrace = thपढ़ो__trace(thपढ़ो, trace->output);
	/*
	 * We need to get ttrace just to make sure it is there when syscall__scnम_लिखो_args()
	 * and the rest of the beautअगरiers accessing it via काष्ठा syscall_arg touches it.
	 */
	अगर (ttrace == शून्य)
		जाओ out_put;

	args = perf_evsel__sc_tp_ptr(evsel, args, sample);
	augmented_args = syscall__augmented_args(sc, sample, &augmented_args_size, trace->raw_augmented_syscalls_args_size);
	syscall__scnम_लिखो_args(sc, msg, माप(msg), args, augmented_args, augmented_args_size, trace, thपढ़ो);
	ख_लिखो(trace->output, "%s", msg);
	err = 0;
out_put:
	thपढ़ो__put(thपढ़ो);
	वापस err;
पूर्ण

अटल पूर्णांक trace__resolve_callchain(काष्ठा trace *trace, काष्ठा evsel *evsel,
				    काष्ठा perf_sample *sample,
				    काष्ठा callchain_cursor *cursor)
अणु
	काष्ठा addr_location al;
	पूर्णांक max_stack = evsel->core.attr.sample_max_stack ?
			evsel->core.attr.sample_max_stack :
			trace->max_stack;
	पूर्णांक err;

	अगर (machine__resolve(trace->host, &al, sample) < 0)
		वापस -1;

	err = thपढ़ो__resolve_callchain(al.thपढ़ो, cursor, evsel, sample, शून्य, शून्य, max_stack);
	addr_location__put(&al);
	वापस err;
पूर्ण

अटल पूर्णांक trace__ख_लिखो_callchain(काष्ठा trace *trace, काष्ठा perf_sample *sample)
अणु
	/* TODO: user-configurable prपूर्णांक_opts */
	स्थिर अचिन्हित पूर्णांक prपूर्णांक_opts = EVSEL__PRINT_SYM |
				        EVSEL__PRINT_DSO |
				        EVSEL__PRINT_UNKNOWN_AS_ADDR;

	वापस sample__ख_लिखो_callchain(sample, 38, prपूर्णांक_opts, &callchain_cursor, symbol_conf.bt_stop_list, trace->output);
पूर्ण

अटल स्थिर अक्षर *त्रुटि_सं_to_name(काष्ठा evsel *evsel, पूर्णांक err)
अणु
	काष्ठा perf_env *env = evsel__env(evsel);
	स्थिर अक्षर *arch_name = perf_env__arch(env);

	वापस arch_syscalls__strत्रुटि_सं(arch_name, err);
पूर्ण

अटल पूर्णांक trace__sys_निकास(काष्ठा trace *trace, काष्ठा evsel *evsel,
			   जोड़ perf_event *event __maybe_unused,
			   काष्ठा perf_sample *sample)
अणु
	दीर्घ ret;
	u64 duration = 0;
	bool duration_calculated = false;
	काष्ठा thपढ़ो *thपढ़ो;
	पूर्णांक id = perf_evsel__sc_tp_uपूर्णांक(evsel, id, sample), err = -1, callchain_ret = 0, prपूर्णांकed = 0;
	पूर्णांक alignment = trace->args_alignment;
	काष्ठा syscall *sc = trace__syscall_info(trace, evsel, id);
	काष्ठा thपढ़ो_trace *ttrace;

	अगर (sc == शून्य)
		वापस -1;

	thपढ़ो = machine__findnew_thपढ़ो(trace->host, sample->pid, sample->tid);
	ttrace = thपढ़ो__trace(thपढ़ो, trace->output);
	अगर (ttrace == शून्य)
		जाओ out_put;

	trace__ख_लिखो_sample(trace, evsel, sample, thपढ़ो);

	ret = perf_evsel__sc_tp_uपूर्णांक(evsel, ret, sample);

	अगर (trace->summary)
		thपढ़ो__update_stats(thपढ़ो, ttrace, id, sample, ret, trace->त्रुटि_सं_summary);

	अगर (!trace->fd_path_disabled && sc->is_खोलो && ret >= 0 && ttrace->filename.pending_खोलो) अणु
		trace__set_fd_pathname(thपढ़ो, ret, ttrace->filename.name);
		ttrace->filename.pending_खोलो = false;
		++trace->stats.vfs_getname;
	पूर्ण

	अगर (ttrace->entry_समय) अणु
		duration = sample->समय - ttrace->entry_समय;
		अगर (trace__filter_duration(trace, duration))
			जाओ out;
		duration_calculated = true;
	पूर्ण अन्यथा अगर (trace->duration_filter)
		जाओ out;

	अगर (sample->callchain) अणु
		callchain_ret = trace__resolve_callchain(trace, evsel, sample, &callchain_cursor);
		अगर (callchain_ret == 0) अणु
			अगर (callchain_cursor.nr < trace->min_stack)
				जाओ out;
			callchain_ret = 1;
		पूर्ण
	पूर्ण

	अगर (trace->summary_only || (ret >= 0 && trace->failure_only))
		जाओ out;

	trace__ख_लिखो_entry_head(trace, thपढ़ो, duration, duration_calculated, ttrace->entry_समय, trace->output);

	अगर (ttrace->entry_pending) अणु
		prपूर्णांकed = ख_लिखो(trace->output, "%s", ttrace->entry_str);
	पूर्ण अन्यथा अणु
		prपूर्णांकed += ख_लिखो(trace->output, " ... [");
		color_ख_लिखो(trace->output, PERF_COLOR_YELLOW, "continued");
		prपूर्णांकed += 9;
		prपूर्णांकed += ख_लिखो(trace->output, "]: %s()", sc->name);
	पूर्ण

	prपूर्णांकed++; /* the closing ')' */

	अगर (alignment > prपूर्णांकed)
		alignment -= prपूर्णांकed;
	अन्यथा
		alignment = 0;

	ख_लिखो(trace->output, ")%*s= ", alignment, " ");

	अगर (sc->fmt == शून्य) अणु
		अगर (ret < 0)
			जाओ त्रुटि_सं_prपूर्णांक;
चिन्हित_prपूर्णांक:
		ख_लिखो(trace->output, "%ld", ret);
	पूर्ण अन्यथा अगर (ret < 0) अणु
त्रुटि_सं_prपूर्णांक: अणु
		अक्षर bf[STRERR_बफ_मानE];
		स्थिर अक्षर *emsg = str_error_r(-ret, bf, माप(bf)),
			   *e = त्रुटि_सं_to_name(evsel, -ret);

		ख_लिखो(trace->output, "-1 %s (%s)", e, emsg);
	पूर्ण
	पूर्ण अन्यथा अगर (ret == 0 && sc->fmt->समयout)
		ख_लिखो(trace->output, "0 (Timeout)");
	अन्यथा अगर (ttrace->ret_scnम_लिखो) अणु
		अक्षर bf[1024];
		काष्ठा syscall_arg arg = अणु
			.val	= ret,
			.thपढ़ो	= thपढ़ो,
			.trace	= trace,
		पूर्ण;
		ttrace->ret_scnम_लिखो(bf, माप(bf), &arg);
		ttrace->ret_scnम_लिखो = शून्य;
		ख_लिखो(trace->output, "%s", bf);
	पूर्ण अन्यथा अगर (sc->fmt->hexret)
		ख_लिखो(trace->output, "%#lx", ret);
	अन्यथा अगर (sc->fmt->errpid) अणु
		काष्ठा thपढ़ो *child = machine__find_thपढ़ो(trace->host, ret, ret);

		अगर (child != शून्य) अणु
			ख_लिखो(trace->output, "%ld", ret);
			अगर (child->comm_set)
				ख_लिखो(trace->output, " (%s)", thपढ़ो__comm_str(child));
			thपढ़ो__put(child);
		पूर्ण
	पूर्ण अन्यथा
		जाओ चिन्हित_prपूर्णांक;

	ख_अक्षर_दो('\n', trace->output);

	/*
	 * We only consider an 'event' क्रम the sake of --max-events a non-filtered
	 * sys_enter + sys_निकास and other tracepoपूर्णांक events.
	 */
	अगर (++trace->nr_events_prपूर्णांकed == trace->max_events && trace->max_events != अच_दीर्घ_उच्च)
		पूर्णांकerrupted = true;

	अगर (callchain_ret > 0)
		trace__ख_लिखो_callchain(trace, sample);
	अन्यथा अगर (callchain_ret < 0)
		pr_err("Problem processing %s callchain, skipping...\n", evsel__name(evsel));
out:
	ttrace->entry_pending = false;
	err = 0;
out_put:
	thपढ़ो__put(thपढ़ो);
	वापस err;
पूर्ण

अटल पूर्णांक trace__vfs_getname(काष्ठा trace *trace, काष्ठा evsel *evsel,
			      जोड़ perf_event *event __maybe_unused,
			      काष्ठा perf_sample *sample)
अणु
	काष्ठा thपढ़ो *thपढ़ो = machine__findnew_thपढ़ो(trace->host, sample->pid, sample->tid);
	काष्ठा thपढ़ो_trace *ttrace;
	माप_प्रकार filename_len, entry_str_len, to_move;
	sमाप_प्रकार reमुख्यing_space;
	अक्षर *pos;
	स्थिर अक्षर *filename = evsel__rawptr(evsel, sample, "pathname");

	अगर (!thपढ़ो)
		जाओ out;

	ttrace = thपढ़ो__priv(thपढ़ो);
	अगर (!ttrace)
		जाओ out_put;

	filename_len = म_माप(filename);
	अगर (filename_len == 0)
		जाओ out_put;

	अगर (ttrace->filename.namelen < filename_len) अणु
		अक्षर *f = पुनः_स्मृति(ttrace->filename.name, filename_len + 1);

		अगर (f == शून्य)
			जाओ out_put;

		ttrace->filename.namelen = filename_len;
		ttrace->filename.name = f;
	पूर्ण

	म_नकल(ttrace->filename.name, filename);
	ttrace->filename.pending_खोलो = true;

	अगर (!ttrace->filename.ptr)
		जाओ out_put;

	entry_str_len = म_माप(ttrace->entry_str);
	reमुख्यing_space = trace__entry_str_size - entry_str_len - 1; /* \0 */
	अगर (reमुख्यing_space <= 0)
		जाओ out_put;

	अगर (filename_len > (माप_प्रकार)reमुख्यing_space) अणु
		filename += filename_len - reमुख्यing_space;
		filename_len = reमुख्यing_space;
	पूर्ण

	to_move = entry_str_len - ttrace->filename.entry_str_pos + 1; /* \0 */
	pos = ttrace->entry_str + ttrace->filename.entry_str_pos;
	स_हटाओ(pos + filename_len, pos, to_move);
	स_नकल(pos, filename, filename_len);

	ttrace->filename.ptr = 0;
	ttrace->filename.entry_str_pos = 0;
out_put:
	thपढ़ो__put(thपढ़ो);
out:
	वापस 0;
पूर्ण

अटल पूर्णांक trace__sched_stat_runसमय(काष्ठा trace *trace, काष्ठा evsel *evsel,
				     जोड़ perf_event *event __maybe_unused,
				     काष्ठा perf_sample *sample)
अणु
        u64 runसमय = evsel__पूर्णांकval(evsel, sample, "runtime");
	द्विगुन runसमय_ms = (द्विगुन)runसमय / NSEC_PER_MSEC;
	काष्ठा thपढ़ो *thपढ़ो = machine__findnew_thपढ़ो(trace->host,
							sample->pid,
							sample->tid);
	काष्ठा thपढ़ो_trace *ttrace = thपढ़ो__trace(thपढ़ो, trace->output);

	अगर (ttrace == शून्य)
		जाओ out_dump;

	ttrace->runसमय_ms += runसमय_ms;
	trace->runसमय_ms += runसमय_ms;
out_put:
	thपढ़ो__put(thपढ़ो);
	वापस 0;

out_dump:
	ख_लिखो(trace->output, "%s: comm=%s,pid=%u,runtime=%" PRIu64 ",vruntime=%" PRIu64 ")\n",
	       evsel->name,
	       evsel__strval(evsel, sample, "comm"),
	       (pid_t)evsel__पूर्णांकval(evsel, sample, "pid"),
	       runसमय,
	       evsel__पूर्णांकval(evsel, sample, "vruntime"));
	जाओ out_put;
पूर्ण

अटल पूर्णांक bpf_output__prपूर्णांकer(क्रमागत binary_prपूर्णांकer_ops op,
			       अचिन्हित पूर्णांक val, व्योम *extra __maybe_unused, खाता *fp)
अणु
	अचिन्हित अक्षर ch = (अचिन्हित अक्षर)val;

	चयन (op) अणु
	हाल BINARY_PRINT_CHAR_DATA:
		वापस ख_लिखो(fp, "%c", है_छाप(ch) ? ch : '.');
	हाल BINARY_PRINT_DATA_BEGIN:
	हाल BINARY_PRINT_LINE_BEGIN:
	हाल BINARY_PRINT_ADDR:
	हाल BINARY_PRINT_NUM_DATA:
	हाल BINARY_PRINT_NUM_PAD:
	हाल BINARY_PRINT_SEP:
	हाल BINARY_PRINT_CHAR_PAD:
	हाल BINARY_PRINT_LINE_END:
	हाल BINARY_PRINT_DATA_END:
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bpf_output__ख_लिखो(काष्ठा trace *trace,
				काष्ठा perf_sample *sample)
अणु
	binary__ख_लिखो(sample->raw_data, sample->raw_size, 8,
			bpf_output__prपूर्णांकer, शून्य, trace->output);
	++trace->nr_events_prपूर्णांकed;
पूर्ण

अटल माप_प्रकार trace__ख_लिखो_tp_fields(काष्ठा trace *trace, काष्ठा evsel *evsel, काष्ठा perf_sample *sample,
				       काष्ठा thपढ़ो *thपढ़ो, व्योम *augmented_args, पूर्णांक augmented_args_size)
अणु
	अक्षर bf[2048];
	माप_प्रकार size = माप(bf);
	काष्ठा tep_क्रमmat_field *field = evsel->tp_क्रमmat->क्रमmat.fields;
	काष्ठा syscall_arg_fmt *arg = __evsel__syscall_arg_fmt(evsel);
	माप_प्रकार prपूर्णांकed = 0;
	अचिन्हित दीर्घ val;
	u8 bit = 1;
	काष्ठा syscall_arg syscall_arg = अणु
		.augmented = अणु
			.size = augmented_args_size,
			.args = augmented_args,
		पूर्ण,
		.idx	= 0,
		.mask	= 0,
		.trace  = trace,
		.thपढ़ो = thपढ़ो,
		.show_string_prefix = trace->show_string_prefix,
	पूर्ण;

	क्रम (; field && arg; field = field->next, ++syscall_arg.idx, bit <<= 1, ++arg) अणु
		अगर (syscall_arg.mask & bit)
			जारी;

		syscall_arg.len = 0;
		syscall_arg.fmt = arg;
		अगर (field->flags & TEP_FIELD_IS_ARRAY) अणु
			पूर्णांक offset = field->offset;

			अगर (field->flags & TEP_FIELD_IS_DYNAMIC) अणु
				offset = क्रमmat_field__पूर्णांकval(field, sample, evsel->needs_swap);
				syscall_arg.len = offset >> 16;
				offset &= 0xffff;
			पूर्ण

			val = (uपूर्णांकptr_t)(sample->raw_data + offset);
		पूर्ण अन्यथा
			val = क्रमmat_field__पूर्णांकval(field, sample, evsel->needs_swap);
		/*
		 * Some syscall args need some mask, most करोn't and
		 * वापस val untouched.
		 */
		val = syscall_arg_fmt__mask_val(arg, &syscall_arg, val);

		/*
		 * Suppress this argument अगर its value is zero and
		 * and we करोn't have a string associated in an
		 * strarray क्रम it.
		 */
		अगर (val == 0 &&
		    !trace->show_zeros &&
		    !((arg->show_zero ||
		       arg->scnम_लिखो == SCA_STRARRAY ||
		       arg->scnम_लिखो == SCA_STRARRAYS) &&
		      arg->parm))
			जारी;

		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s", prपूर्णांकed ? ", " : "");

		/*
		 * XXX Perhaps we should have a show_tp_arg_names,
		 * leaving show_arg_names just क्रम syscalls?
		 */
		अगर (1 || trace->show_arg_names)
			prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s: ", field->name);

		prपूर्णांकed += syscall_arg_fmt__scnम_लिखो_val(arg, bf + prपूर्णांकed, size - prपूर्णांकed, &syscall_arg, val);
	पूर्ण

	वापस prपूर्णांकed + ख_लिखो(trace->output, "%s", bf);
पूर्ण

अटल पूर्णांक trace__event_handler(काष्ठा trace *trace, काष्ठा evsel *evsel,
				जोड़ perf_event *event __maybe_unused,
				काष्ठा perf_sample *sample)
अणु
	काष्ठा thपढ़ो *thपढ़ो;
	पूर्णांक callchain_ret = 0;
	/*
	 * Check अगर we called perf_evsel__disable(evsel) due to, क्रम instance,
	 * this event's max_events having been hit and this is an entry coming
	 * from the ring buffer that we should discard, since the max events
	 * have alपढ़ोy been considered/prपूर्णांकed.
	 */
	अगर (evsel->disabled)
		वापस 0;

	thपढ़ो = machine__findnew_thपढ़ो(trace->host, sample->pid, sample->tid);

	अगर (sample->callchain) अणु
		callchain_ret = trace__resolve_callchain(trace, evsel, sample, &callchain_cursor);
		अगर (callchain_ret == 0) अणु
			अगर (callchain_cursor.nr < trace->min_stack)
				जाओ out;
			callchain_ret = 1;
		पूर्ण
	पूर्ण

	trace__म_लिखो_पूर्णांकerrupted_entry(trace);
	trace__ख_लिखो_tstamp(trace, sample->समय, trace->output);

	अगर (trace->trace_syscalls && trace->show_duration)
		ख_लिखो(trace->output, "(         ): ");

	अगर (thपढ़ो)
		trace__ख_लिखो_comm_tid(trace, thपढ़ो, trace->output);

	अगर (evsel == trace->syscalls.events.augmented) अणु
		पूर्णांक id = perf_evsel__sc_tp_uपूर्णांक(evsel, id, sample);
		काष्ठा syscall *sc = trace__syscall_info(trace, evsel, id);

		अगर (sc) अणु
			ख_लिखो(trace->output, "%s(", sc->name);
			trace__ख_लिखो_sys_enter(trace, evsel, sample);
			ख_अक्षर_दो(')', trace->output);
			जाओ newline;
		पूर्ण

		/*
		 * XXX: Not having the associated syscall info or not finding/adding
		 * 	the thपढ़ो should never happen, but अगर it करोes...
		 * 	fall thru and prपूर्णांक it as a bpf_output event.
		 */
	पूर्ण

	ख_लिखो(trace->output, "%s(", evsel->name);

	अगर (evsel__is_bpf_output(evsel)) अणु
		bpf_output__ख_लिखो(trace, sample);
	पूर्ण अन्यथा अगर (evsel->tp_क्रमmat) अणु
		अगर (म_भेदन(evsel->tp_क्रमmat->name, "sys_enter_", 10) ||
		    trace__ख_लिखो_sys_enter(trace, evsel, sample)) अणु
			अगर (trace->libtraceevent_prपूर्णांक) अणु
				event_क्रमmat__ख_लिखो(evsel->tp_क्रमmat, sample->cpu,
						      sample->raw_data, sample->raw_size,
						      trace->output);
			पूर्ण अन्यथा अणु
				trace__ख_लिखो_tp_fields(trace, evsel, sample, thपढ़ो, शून्य, 0);
			पूर्ण
		पूर्ण
	पूर्ण

newline:
	ख_लिखो(trace->output, ")\n");

	अगर (callchain_ret > 0)
		trace__ख_लिखो_callchain(trace, sample);
	अन्यथा अगर (callchain_ret < 0)
		pr_err("Problem processing %s callchain, skipping...\n", evsel__name(evsel));

	++trace->nr_events_prपूर्णांकed;

	अगर (evsel->max_events != अच_दीर्घ_उच्च && ++evsel->nr_events_prपूर्णांकed == evsel->max_events) अणु
		evsel__disable(evsel);
		evsel__बंद(evsel);
	पूर्ण
out:
	thपढ़ो__put(thपढ़ो);
	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_location(खाता *f, काष्ठा perf_sample *sample,
			   काष्ठा addr_location *al,
			   bool prपूर्णांक_dso, bool prपूर्णांक_sym)
अणु

	अगर ((verbose > 0 || prपूर्णांक_dso) && al->map)
		ख_लिखो(f, "%s@", al->map->dso->दीर्घ_name);

	अगर ((verbose > 0 || prपूर्णांक_sym) && al->sym)
		ख_लिखो(f, "%s+0x%" PRIx64, al->sym->name,
			al->addr - al->sym->start);
	अन्यथा अगर (al->map)
		ख_लिखो(f, "0x%" PRIx64, al->addr);
	अन्यथा
		ख_लिखो(f, "0x%" PRIx64, sample->addr);
पूर्ण

अटल पूर्णांक trace__pgfault(काष्ठा trace *trace,
			  काष्ठा evsel *evsel,
			  जोड़ perf_event *event __maybe_unused,
			  काष्ठा perf_sample *sample)
अणु
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा addr_location al;
	अक्षर map_type = 'd';
	काष्ठा thपढ़ो_trace *ttrace;
	पूर्णांक err = -1;
	पूर्णांक callchain_ret = 0;

	thपढ़ो = machine__findnew_thपढ़ो(trace->host, sample->pid, sample->tid);

	अगर (sample->callchain) अणु
		callchain_ret = trace__resolve_callchain(trace, evsel, sample, &callchain_cursor);
		अगर (callchain_ret == 0) अणु
			अगर (callchain_cursor.nr < trace->min_stack)
				जाओ out_put;
			callchain_ret = 1;
		पूर्ण
	पूर्ण

	ttrace = thपढ़ो__trace(thपढ़ो, trace->output);
	अगर (ttrace == शून्य)
		जाओ out_put;

	अगर (evsel->core.attr.config == PERF_COUNT_SW_PAGE_FAULTS_MAJ)
		ttrace->pfmaj++;
	अन्यथा
		ttrace->pfmin++;

	अगर (trace->summary_only)
		जाओ out;

	thपढ़ो__find_symbol(thपढ़ो, sample->cpumode, sample->ip, &al);

	trace__ख_लिखो_entry_head(trace, thपढ़ो, 0, true, sample->समय, trace->output);

	ख_लिखो(trace->output, "%sfault [",
		evsel->core.attr.config == PERF_COUNT_SW_PAGE_FAULTS_MAJ ?
		"maj" : "min");

	prपूर्णांक_location(trace->output, sample, &al, false, true);

	ख_लिखो(trace->output, "] => ");

	thपढ़ो__find_symbol(thपढ़ो, sample->cpumode, sample->addr, &al);

	अगर (!al.map) अणु
		thपढ़ो__find_symbol(thपढ़ो, sample->cpumode, sample->addr, &al);

		अगर (al.map)
			map_type = 'x';
		अन्यथा
			map_type = '?';
	पूर्ण

	prपूर्णांक_location(trace->output, sample, &al, true, false);

	ख_लिखो(trace->output, " (%c%c)\n", map_type, al.level);

	अगर (callchain_ret > 0)
		trace__ख_लिखो_callchain(trace, sample);
	अन्यथा अगर (callchain_ret < 0)
		pr_err("Problem processing %s callchain, skipping...\n", evsel__name(evsel));

	++trace->nr_events_prपूर्णांकed;
out:
	err = 0;
out_put:
	thपढ़ो__put(thपढ़ो);
	वापस err;
पूर्ण

अटल व्योम trace__set_base_समय(काष्ठा trace *trace,
				 काष्ठा evsel *evsel,
				 काष्ठा perf_sample *sample)
अणु
	/*
	 * BPF events were not setting PERF_SAMPLE_TIME, so be more robust
	 * and करोn't use sample->समय unconditionally, we may end up having
	 * some other event in the future without PERF_SAMPLE_TIME क्रम good
	 * reason, i.e. we may not be पूर्णांकerested in its बारtamps, just in
	 * it taking place, picking some piece of inक्रमmation when it
	 * appears in our event stream (vfs_getname comes to mind).
	 */
	अगर (trace->base_समय == 0 && !trace->full_समय &&
	    (evsel->core.attr.sample_type & PERF_SAMPLE_TIME))
		trace->base_समय = sample->समय;
पूर्ण

अटल पूर्णांक trace__process_sample(काष्ठा perf_tool *tool,
				 जोड़ perf_event *event,
				 काष्ठा perf_sample *sample,
				 काष्ठा evsel *evsel,
				 काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा trace *trace = container_of(tool, काष्ठा trace, tool);
	काष्ठा thपढ़ो *thपढ़ो;
	पूर्णांक err = 0;

	tracepoपूर्णांक_handler handler = evsel->handler;

	thपढ़ो = machine__findnew_thपढ़ो(trace->host, sample->pid, sample->tid);
	अगर (thपढ़ो && thपढ़ो__is_filtered(thपढ़ो))
		जाओ out;

	trace__set_base_समय(trace, evsel, sample);

	अगर (handler) अणु
		++trace->nr_events;
		handler(trace, evsel, event, sample);
	पूर्ण
out:
	thपढ़ो__put(thपढ़ो);
	वापस err;
पूर्ण

अटल पूर्णांक trace__record(काष्ठा trace *trace, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अचिन्हित पूर्णांक rec_argc, i, j;
	स्थिर अक्षर **rec_argv;
	स्थिर अक्षर * स्थिर record_args[] = अणु
		"record",
		"-R",
		"-m", "1024",
		"-c", "1",
	पूर्ण;
	pid_t pid = getpid();
	अक्षर *filter = aप्र_लिखो__tp_filter_pids(1, &pid);
	स्थिर अक्षर * स्थिर sc_args[] = अणु "-e", पूर्ण;
	अचिन्हित पूर्णांक sc_args_nr = ARRAY_SIZE(sc_args);
	स्थिर अक्षर * स्थिर majpf_args[] = अणु "-e", "major-faults" पूर्ण;
	अचिन्हित पूर्णांक majpf_args_nr = ARRAY_SIZE(majpf_args);
	स्थिर अक्षर * स्थिर minpf_args[] = अणु "-e", "minor-faults" पूर्ण;
	अचिन्हित पूर्णांक minpf_args_nr = ARRAY_SIZE(minpf_args);
	पूर्णांक err = -1;

	/* +3 is क्रम the event string below and the pid filter */
	rec_argc = ARRAY_SIZE(record_args) + sc_args_nr + 3 +
		majpf_args_nr + minpf_args_nr + argc;
	rec_argv = सुस्मृति(rec_argc + 1, माप(अक्षर *));

	अगर (rec_argv == शून्य || filter == शून्य)
		जाओ out_मुक्त;

	j = 0;
	क्रम (i = 0; i < ARRAY_SIZE(record_args); i++)
		rec_argv[j++] = record_args[i];

	अगर (trace->trace_syscalls) अणु
		क्रम (i = 0; i < sc_args_nr; i++)
			rec_argv[j++] = sc_args[i];

		/* event string may be dअगरferent क्रम older kernels - e.g., RHEL6 */
		अगर (is_valid_tracepoपूर्णांक("raw_syscalls:sys_enter"))
			rec_argv[j++] = "raw_syscalls:sys_enter,raw_syscalls:sys_exit";
		अन्यथा अगर (is_valid_tracepoपूर्णांक("syscalls:sys_enter"))
			rec_argv[j++] = "syscalls:sys_enter,syscalls:sys_exit";
		अन्यथा अणु
			pr_err("Neither raw_syscalls nor syscalls events exist.\n");
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	rec_argv[j++] = "--filter";
	rec_argv[j++] = filter;

	अगर (trace->trace_pgfaults & TRACE_PFMAJ)
		क्रम (i = 0; i < majpf_args_nr; i++)
			rec_argv[j++] = majpf_args[i];

	अगर (trace->trace_pgfaults & TRACE_PFMIN)
		क्रम (i = 0; i < minpf_args_nr; i++)
			rec_argv[j++] = minpf_args[i];

	क्रम (i = 0; i < (अचिन्हित पूर्णांक)argc; i++)
		rec_argv[j++] = argv[i];

	err = cmd_record(j, rec_argv);
out_मुक्त:
	मुक्त(filter);
	मुक्त(rec_argv);
	वापस err;
पूर्ण

अटल माप_प्रकार trace__ख_लिखो_thपढ़ो_summary(काष्ठा trace *trace, खाता *fp);

अटल bool evlist__add_vfs_getname(काष्ठा evlist *evlist)
अणु
	bool found = false;
	काष्ठा evsel *evsel, *पंचांगp;
	काष्ठा parse_events_error err;
	पूर्णांक ret;

	bzero(&err, माप(err));
	ret = parse_events(evlist, "probe:vfs_getname*", &err);
	अगर (ret) अणु
		मुक्त(err.str);
		मुक्त(err.help);
		मुक्त(err.first_str);
		मुक्त(err.first_help);
		वापस false;
	पूर्ण

	evlist__क्रम_each_entry_safe(evlist, evsel, पंचांगp) अणु
		अगर (!strstarts(evsel__name(evsel), "probe:vfs_getname"))
			जारी;

		अगर (evsel__field(evsel, "pathname")) अणु
			evsel->handler = trace__vfs_getname;
			found = true;
			जारी;
		पूर्ण

		list_del_init(&evsel->core.node);
		evsel->evlist = शून्य;
		evsel__delete(evsel);
	पूर्ण

	वापस found;
पूर्ण

अटल काष्ठा evsel *evsel__new_pgfault(u64 config)
अणु
	काष्ठा evsel *evsel;
	काष्ठा perf_event_attr attr = अणु
		.type = PERF_TYPE_SOFTWARE,
		.mmap_data = 1,
	पूर्ण;

	attr.config = config;
	attr.sample_period = 1;

	event_attr_init(&attr);

	evsel = evsel__new(&attr);
	अगर (evsel)
		evsel->handler = trace__pgfault;

	वापस evsel;
पूर्ण

अटल व्योम trace__handle_event(काष्ठा trace *trace, जोड़ perf_event *event, काष्ठा perf_sample *sample)
अणु
	स्थिर u32 type = event->header.type;
	काष्ठा evsel *evsel;

	अगर (type != PERF_RECORD_SAMPLE) अणु
		trace__process_event(trace, trace->host, event, sample);
		वापस;
	पूर्ण

	evsel = evlist__id2evsel(trace->evlist, sample->id);
	अगर (evsel == शून्य) अणु
		ख_लिखो(trace->output, "Unknown tp ID %" PRIu64 ", skipping...\n", sample->id);
		वापस;
	पूर्ण

	अगर (evचयन__discard(&trace->evचयन, evsel))
		वापस;

	trace__set_base_समय(trace, evsel, sample);

	अगर (evsel->core.attr.type == PERF_TYPE_TRACEPOINT &&
	    sample->raw_data == शून्य) अणु
		ख_लिखो(trace->output, "%s sample with no payload for tid: %d, cpu %d, raw_size=%d, skipping...\n",
		       evsel__name(evsel), sample->tid,
		       sample->cpu, sample->raw_size);
	पूर्ण अन्यथा अणु
		tracepoपूर्णांक_handler handler = evsel->handler;
		handler(trace, evsel, event, sample);
	पूर्ण

	अगर (trace->nr_events_prपूर्णांकed >= trace->max_events && trace->max_events != अच_दीर्घ_उच्च)
		पूर्णांकerrupted = true;
पूर्ण

अटल पूर्णांक trace__add_syscall_newtp(काष्ठा trace *trace)
अणु
	पूर्णांक ret = -1;
	काष्ठा evlist *evlist = trace->evlist;
	काष्ठा evsel *sys_enter, *sys_निकास;

	sys_enter = perf_evsel__raw_syscall_newtp("sys_enter", trace__sys_enter);
	अगर (sys_enter == शून्य)
		जाओ out;

	अगर (perf_evsel__init_sc_tp_ptr_field(sys_enter, args))
		जाओ out_delete_sys_enter;

	sys_निकास = perf_evsel__raw_syscall_newtp("sys_exit", trace__sys_निकास);
	अगर (sys_निकास == शून्य)
		जाओ out_delete_sys_enter;

	अगर (perf_evsel__init_sc_tp_uपूर्णांक_field(sys_निकास, ret))
		जाओ out_delete_sys_निकास;

	evsel__config_callchain(sys_enter, &trace->opts, &callchain_param);
	evsel__config_callchain(sys_निकास, &trace->opts, &callchain_param);

	evlist__add(evlist, sys_enter);
	evlist__add(evlist, sys_निकास);

	अगर (callchain_param.enabled && !trace->kernel_syscallchains) अणु
		/*
		 * We're पूर्णांकerested only in the user space callchain
		 * leading to the syscall, allow overriding that क्रम
		 * debugging reasons using --kernel_syscall_callchains
		 */
		sys_निकास->core.attr.exclude_callchain_kernel = 1;
	पूर्ण

	trace->syscalls.events.sys_enter = sys_enter;
	trace->syscalls.events.sys_निकास  = sys_निकास;

	ret = 0;
out:
	वापस ret;

out_delete_sys_निकास:
	evsel__delete_priv(sys_निकास);
out_delete_sys_enter:
	evsel__delete_priv(sys_enter);
	जाओ out;
पूर्ण

अटल पूर्णांक trace__set_ev_qualअगरier_tp_filter(काष्ठा trace *trace)
अणु
	पूर्णांक err = -1;
	काष्ठा evsel *sys_निकास;
	अक्षर *filter = aप्र_लिखो_expr_inout_पूर्णांकs("id", !trace->not_ev_qualअगरier,
						trace->ev_qualअगरier_ids.nr,
						trace->ev_qualअगरier_ids.entries);

	अगर (filter == शून्य)
		जाओ out_enomem;

	अगर (!evsel__append_tp_filter(trace->syscalls.events.sys_enter, filter)) अणु
		sys_निकास = trace->syscalls.events.sys_निकास;
		err = evsel__append_tp_filter(sys_निकास, filter);
	पूर्ण

	मुक्त(filter);
out:
	वापस err;
out_enomem:
	त्रुटि_सं = ENOMEM;
	जाओ out;
पूर्ण

#अगर_घोषित HAVE_LIBBPF_SUPPORT
अटल काष्ठा bpf_map *trace__find_bpf_map_by_name(काष्ठा trace *trace, स्थिर अक्षर *name)
अणु
	अगर (trace->bpf_obj == शून्य)
		वापस शून्य;

	वापस bpf_object__find_map_by_name(trace->bpf_obj, name);
पूर्ण

अटल व्योम trace__set_bpf_map_filtered_pids(काष्ठा trace *trace)
अणु
	trace->filter_pids.map = trace__find_bpf_map_by_name(trace, "pids_filtered");
पूर्ण

अटल व्योम trace__set_bpf_map_syscalls(काष्ठा trace *trace)
अणु
	trace->syscalls.map = trace__find_bpf_map_by_name(trace, "syscalls");
	trace->syscalls.prog_array.sys_enter = trace__find_bpf_map_by_name(trace, "syscalls_sys_enter");
	trace->syscalls.prog_array.sys_निकास  = trace__find_bpf_map_by_name(trace, "syscalls_sys_exit");
पूर्ण

अटल काष्ठा bpf_program *trace__find_bpf_program_by_title(काष्ठा trace *trace, स्थिर अक्षर *name)
अणु
	अगर (trace->bpf_obj == शून्य)
		वापस शून्य;

	वापस bpf_object__find_program_by_title(trace->bpf_obj, name);
पूर्ण

अटल काष्ठा bpf_program *trace__find_syscall_bpf_prog(काष्ठा trace *trace, काष्ठा syscall *sc,
							स्थिर अक्षर *prog_name, स्थिर अक्षर *type)
अणु
	काष्ठा bpf_program *prog;

	अगर (prog_name == शून्य) अणु
		अक्षर शेष_prog_name[256];
		scnम_लिखो(शेष_prog_name, माप(शेष_prog_name), "!syscalls:sys_%s_%s", type, sc->name);
		prog = trace__find_bpf_program_by_title(trace, शेष_prog_name);
		अगर (prog != शून्य)
			जाओ out_found;
		अगर (sc->fmt && sc->fmt->alias) अणु
			scnम_लिखो(शेष_prog_name, माप(शेष_prog_name), "!syscalls:sys_%s_%s", type, sc->fmt->alias);
			prog = trace__find_bpf_program_by_title(trace, शेष_prog_name);
			अगर (prog != शून्य)
				जाओ out_found;
		पूर्ण
		जाओ out_unaugmented;
	पूर्ण

	prog = trace__find_bpf_program_by_title(trace, prog_name);

	अगर (prog != शून्य) अणु
out_found:
		वापस prog;
	पूर्ण

	pr_debug("Couldn't find BPF prog \"%s\" to associate with syscalls:sys_%s_%s, not augmenting it\n",
		 prog_name, type, sc->name);
out_unaugmented:
	वापस trace->syscalls.unaugmented_prog;
पूर्ण

अटल व्योम trace__init_syscall_bpf_progs(काष्ठा trace *trace, पूर्णांक id)
अणु
	काष्ठा syscall *sc = trace__syscall_info(trace, शून्य, id);

	अगर (sc == शून्य)
		वापस;

	sc->bpf_prog.sys_enter = trace__find_syscall_bpf_prog(trace, sc, sc->fmt ? sc->fmt->bpf_prog_name.sys_enter : शून्य, "enter");
	sc->bpf_prog.sys_निकास  = trace__find_syscall_bpf_prog(trace, sc, sc->fmt ? sc->fmt->bpf_prog_name.sys_निकास  : शून्य,  "exit");
पूर्ण

अटल पूर्णांक trace__bpf_prog_sys_enter_fd(काष्ठा trace *trace, पूर्णांक id)
अणु
	काष्ठा syscall *sc = trace__syscall_info(trace, शून्य, id);
	वापस sc ? bpf_program__fd(sc->bpf_prog.sys_enter) : bpf_program__fd(trace->syscalls.unaugmented_prog);
पूर्ण

अटल पूर्णांक trace__bpf_prog_sys_निकास_fd(काष्ठा trace *trace, पूर्णांक id)
अणु
	काष्ठा syscall *sc = trace__syscall_info(trace, शून्य, id);
	वापस sc ? bpf_program__fd(sc->bpf_prog.sys_निकास) : bpf_program__fd(trace->syscalls.unaugmented_prog);
पूर्ण

अटल व्योम trace__init_bpf_map_syscall_args(काष्ठा trace *trace, पूर्णांक id, काष्ठा bpf_map_syscall_entry *entry)
अणु
	काष्ठा syscall *sc = trace__syscall_info(trace, शून्य, id);
	पूर्णांक arg = 0;

	अगर (sc == शून्य)
		जाओ out;

	क्रम (; arg < sc->nr_args; ++arg) अणु
		entry->string_args_len[arg] = 0;
		अगर (sc->arg_fmt[arg].scnम_लिखो == SCA_खाताNAME) अणु
			/* Should be set like strace -s strsize */
			entry->string_args_len[arg] = PATH_MAX;
		पूर्ण
	पूर्ण
out:
	क्रम (; arg < 6; ++arg)
		entry->string_args_len[arg] = 0;
पूर्ण
अटल पूर्णांक trace__set_ev_qualअगरier_bpf_filter(काष्ठा trace *trace)
अणु
	पूर्णांक fd = bpf_map__fd(trace->syscalls.map);
	काष्ठा bpf_map_syscall_entry value = अणु
		.enabled = !trace->not_ev_qualअगरier,
	पूर्ण;
	पूर्णांक err = 0;
	माप_प्रकार i;

	क्रम (i = 0; i < trace->ev_qualअगरier_ids.nr; ++i) अणु
		पूर्णांक key = trace->ev_qualअगरier_ids.entries[i];

		अगर (value.enabled) अणु
			trace__init_bpf_map_syscall_args(trace, key, &value);
			trace__init_syscall_bpf_progs(trace, key);
		पूर्ण

		err = bpf_map_update_elem(fd, &key, &value, BPF_EXIST);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक __trace__init_syscalls_bpf_map(काष्ठा trace *trace, bool enabled)
अणु
	पूर्णांक fd = bpf_map__fd(trace->syscalls.map);
	काष्ठा bpf_map_syscall_entry value = अणु
		.enabled = enabled,
	पूर्ण;
	पूर्णांक err = 0, key;

	क्रम (key = 0; key < trace->sctbl->syscalls.nr_entries; ++key) अणु
		अगर (enabled)
			trace__init_bpf_map_syscall_args(trace, key, &value);

		err = bpf_map_update_elem(fd, &key, &value, BPF_ANY);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक trace__init_syscalls_bpf_map(काष्ठा trace *trace)
अणु
	bool enabled = true;

	अगर (trace->ev_qualअगरier_ids.nr)
		enabled = trace->not_ev_qualअगरier;

	वापस __trace__init_syscalls_bpf_map(trace, enabled);
पूर्ण

अटल काष्ठा bpf_program *trace__find_usable_bpf_prog_entry(काष्ठा trace *trace, काष्ठा syscall *sc)
अणु
	काष्ठा tep_क्रमmat_field *field, *candidate_field;
	पूर्णांक id;

	/*
	 * We're only पूर्णांकerested in syscalls that have a poपूर्णांकer:
	 */
	क्रम (field = sc->args; field; field = field->next) अणु
		अगर (field->flags & TEP_FIELD_IS_POINTER)
			जाओ try_to_find_pair;
	पूर्ण

	वापस शून्य;

try_to_find_pair:
	क्रम (id = 0; id < trace->sctbl->syscalls.nr_entries; ++id) अणु
		काष्ठा syscall *pair = trace__syscall_info(trace, शून्य, id);
		काष्ठा bpf_program *pair_prog;
		bool is_candidate = false;

		अगर (pair == शून्य || pair == sc ||
		    pair->bpf_prog.sys_enter == trace->syscalls.unaugmented_prog)
			जारी;

		क्रम (field = sc->args, candidate_field = pair->args;
		     field && candidate_field; field = field->next, candidate_field = candidate_field->next) अणु
			bool is_poपूर्णांकer = field->flags & TEP_FIELD_IS_POINTER,
			     candidate_is_poपूर्णांकer = candidate_field->flags & TEP_FIELD_IS_POINTER;

			अगर (is_poपूर्णांकer) अणु
			       अगर (!candidate_is_poपूर्णांकer) अणु
					// The candidate just करोesn't copies our poपूर्णांकer arg, might copy other poपूर्णांकers we want.
					जारी;
			       पूर्ण
			पूर्ण अन्यथा अणु
				अगर (candidate_is_poपूर्णांकer) अणु
					// The candidate might copy a poपूर्णांकer we करोn't have, skip it.
					जाओ next_candidate;
				पूर्ण
				जारी;
			पूर्ण

			अगर (म_भेद(field->type, candidate_field->type))
				जाओ next_candidate;

			is_candidate = true;
		पूर्ण

		अगर (!is_candidate)
			जाओ next_candidate;

		/*
		 * Check अगर the tentative pair syscall augmenter has more poपूर्णांकers, अगर it has,
		 * then it may be collecting that and we then can't use it, as it would collect
		 * more than what is common to the two syscalls.
		 */
		अगर (candidate_field) अणु
			क्रम (candidate_field = candidate_field->next; candidate_field; candidate_field = candidate_field->next)
				अगर (candidate_field->flags & TEP_FIELD_IS_POINTER)
					जाओ next_candidate;
		पूर्ण

		pair_prog = pair->bpf_prog.sys_enter;
		/*
		 * If the pair isn't enabled, then its bpf_prog.sys_enter will not
		 * have been searched क्रम, so search it here and अगर it वापसs the
		 * unaugmented one, then ignore it, otherwise we'll reuse that BPF
		 * program क्रम a filtered syscall on a non-filtered one.
		 *
		 * For instance, we have "!syscalls:sys_enter_renameat" and that is
		 * useful क्रम "renameat2".
		 */
		अगर (pair_prog == शून्य) अणु
			pair_prog = trace__find_syscall_bpf_prog(trace, pair, pair->fmt ? pair->fmt->bpf_prog_name.sys_enter : शून्य, "enter");
			अगर (pair_prog == trace->syscalls.unaugmented_prog)
				जाओ next_candidate;
		पूर्ण

		pr_debug("Reusing \"%s\" BPF sys_enter augmenter for \"%s\"\n", pair->name, sc->name);
		वापस pair_prog;
	next_candidate:
		जारी;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक trace__init_syscalls_bpf_prog_array_maps(काष्ठा trace *trace)
अणु
	पूर्णांक map_enter_fd = bpf_map__fd(trace->syscalls.prog_array.sys_enter),
	    map_निकास_fd  = bpf_map__fd(trace->syscalls.prog_array.sys_निकास);
	पूर्णांक err = 0, key;

	क्रम (key = 0; key < trace->sctbl->syscalls.nr_entries; ++key) अणु
		पूर्णांक prog_fd;

		अगर (!trace__syscall_enabled(trace, key))
			जारी;

		trace__init_syscall_bpf_progs(trace, key);

		// It'll get at least the "!raw_syscalls:unaugmented"
		prog_fd = trace__bpf_prog_sys_enter_fd(trace, key);
		err = bpf_map_update_elem(map_enter_fd, &key, &prog_fd, BPF_ANY);
		अगर (err)
			अवरोध;
		prog_fd = trace__bpf_prog_sys_निकास_fd(trace, key);
		err = bpf_map_update_elem(map_निकास_fd, &key, &prog_fd, BPF_ANY);
		अगर (err)
			अवरोध;
	पूर्ण

	/*
	 * Now lets करो a second pass looking क्रम enabled syscalls without
	 * an augmenter that have a signature that is a superset of another
	 * syscall with an augmenter so that we can स्वतः-reuse it.
	 *
	 * I.e. अगर we have an augmenter क्रम the "open" syscall that has
	 * this signature:
	 *
	 *   पूर्णांक खोलो(स्थिर अक्षर *pathname, पूर्णांक flags, mode_t mode);
	 *
	 * I.e. that will collect just the first string argument, then we
	 * can reuse it क्रम the 'creat' syscall, that has this signature:
	 *
	 *   पूर्णांक creat(स्थिर अक्षर *pathname, mode_t mode);
	 *
	 * and क्रम:
	 *
	 *   पूर्णांक stat(स्थिर अक्षर *pathname, काष्ठा stat *statbuf);
	 *   पूर्णांक lstat(स्थिर अक्षर *pathname, काष्ठा stat *statbuf);
	 *
	 * Because the 'open' augmenter will collect the first arg as a string,
	 * and leave alone all the other args, which alपढ़ोy helps with
	 * beautअगरying 'stat' and 'lstat''s pathname arg.
	 *
	 * Then, in समय, when 'stat' माला_लो an augmenter that collects both
	 * first and second arg (this one on the raw_syscalls:sys_निकास prog
	 * array tail call, then that one will be used.
	 */
	क्रम (key = 0; key < trace->sctbl->syscalls.nr_entries; ++key) अणु
		काष्ठा syscall *sc = trace__syscall_info(trace, शून्य, key);
		काष्ठा bpf_program *pair_prog;
		पूर्णांक prog_fd;

		अगर (sc == शून्य || sc->bpf_prog.sys_enter == शून्य)
			जारी;

		/*
		 * For now we're just reusing the sys_enter prog, and अगर it
		 * alपढ़ोy has an augmenter, we करोn't need to find one.
		 */
		अगर (sc->bpf_prog.sys_enter != trace->syscalls.unaugmented_prog)
			जारी;

		/*
		 * Look at all the other syscalls क्रम one that has a signature
		 * that is बंद enough that we can share:
		 */
		pair_prog = trace__find_usable_bpf_prog_entry(trace, sc);
		अगर (pair_prog == शून्य)
			जारी;

		sc->bpf_prog.sys_enter = pair_prog;

		/*
		 * Update the BPF_MAP_TYPE_PROG_SHARED क्रम raw_syscalls:sys_enter
		 * with the fd क्रम the program we're reusing:
		 */
		prog_fd = bpf_program__fd(sc->bpf_prog.sys_enter);
		err = bpf_map_update_elem(map_enter_fd, &key, &prog_fd, BPF_ANY);
		अगर (err)
			अवरोध;
	पूर्ण


	वापस err;
पूर्ण

अटल व्योम trace__delete_augmented_syscalls(काष्ठा trace *trace)
अणु
	काष्ठा evsel *evsel, *पंचांगp;

	evlist__हटाओ(trace->evlist, trace->syscalls.events.augmented);
	evsel__delete(trace->syscalls.events.augmented);
	trace->syscalls.events.augmented = शून्य;

	evlist__क्रम_each_entry_safe(trace->evlist, पंचांगp, evsel) अणु
		अगर (evsel->bpf_obj == trace->bpf_obj) अणु
			evlist__हटाओ(trace->evlist, evsel);
			evsel__delete(evsel);
		पूर्ण

	पूर्ण

	bpf_object__बंद(trace->bpf_obj);
	trace->bpf_obj = शून्य;
पूर्ण
#अन्यथा // HAVE_LIBBPF_SUPPORT
अटल काष्ठा bpf_map *trace__find_bpf_map_by_name(काष्ठा trace *trace __maybe_unused,
						   स्थिर अक्षर *name __maybe_unused)
अणु
	वापस शून्य;
पूर्ण

अटल व्योम trace__set_bpf_map_filtered_pids(काष्ठा trace *trace __maybe_unused)
अणु
पूर्ण

अटल व्योम trace__set_bpf_map_syscalls(काष्ठा trace *trace __maybe_unused)
अणु
पूर्ण

अटल पूर्णांक trace__set_ev_qualअगरier_bpf_filter(काष्ठा trace *trace __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक trace__init_syscalls_bpf_map(काष्ठा trace *trace __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा bpf_program *trace__find_bpf_program_by_title(काष्ठा trace *trace __maybe_unused,
							    स्थिर अक्षर *name __maybe_unused)
अणु
	वापस शून्य;
पूर्ण

अटल पूर्णांक trace__init_syscalls_bpf_prog_array_maps(काष्ठा trace *trace __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल व्योम trace__delete_augmented_syscalls(काष्ठा trace *trace __maybe_unused)
अणु
पूर्ण
#पूर्ण_अगर // HAVE_LIBBPF_SUPPORT

अटल bool trace__only_augmented_syscalls_evsels(काष्ठा trace *trace)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(trace->evlist, evsel) अणु
		अगर (evsel == trace->syscalls.events.augmented ||
		    evsel->bpf_obj == trace->bpf_obj)
			जारी;

		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक trace__set_ev_qualअगरier_filter(काष्ठा trace *trace)
अणु
	अगर (trace->syscalls.map)
		वापस trace__set_ev_qualअगरier_bpf_filter(trace);
	अगर (trace->syscalls.events.sys_enter)
		वापस trace__set_ev_qualअगरier_tp_filter(trace);
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_map__set_filter_pids(काष्ठा bpf_map *map __maybe_unused,
				    माप_प्रकार npids __maybe_unused, pid_t *pids __maybe_unused)
अणु
	पूर्णांक err = 0;
#अगर_घोषित HAVE_LIBBPF_SUPPORT
	bool value = true;
	पूर्णांक map_fd = bpf_map__fd(map);
	माप_प्रकार i;

	क्रम (i = 0; i < npids; ++i) अणु
		err = bpf_map_update_elem(map_fd, &pids[i], &value, BPF_ANY);
		अगर (err)
			अवरोध;
	पूर्ण
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल पूर्णांक trace__set_filter_loop_pids(काष्ठा trace *trace)
अणु
	अचिन्हित पूर्णांक nr = 1, err;
	pid_t pids[32] = अणु
		getpid(),
	पूर्ण;
	काष्ठा thपढ़ो *thपढ़ो = machine__find_thपढ़ो(trace->host, pids[0], pids[0]);

	जबतक (thपढ़ो && nr < ARRAY_SIZE(pids)) अणु
		काष्ठा thपढ़ो *parent = machine__find_thपढ़ो(trace->host, thपढ़ो->ppid, thपढ़ो->ppid);

		अगर (parent == शून्य)
			अवरोध;

		अगर (!म_भेद(thपढ़ो__comm_str(parent), "sshd") ||
		    strstarts(thपढ़ो__comm_str(parent), "gnome-terminal")) अणु
			pids[nr++] = parent->tid;
			अवरोध;
		पूर्ण
		thपढ़ो = parent;
	पूर्ण

	err = evlist__append_tp_filter_pids(trace->evlist, nr, pids);
	अगर (!err && trace->filter_pids.map)
		err = bpf_map__set_filter_pids(trace->filter_pids.map, nr, pids);

	वापस err;
पूर्ण

अटल पूर्णांक trace__set_filter_pids(काष्ठा trace *trace)
अणु
	पूर्णांक err = 0;
	/*
	 * Better not use !target__has_task() here because we need to cover the
	 * हाल where no thपढ़ोs were specअगरied in the command line, but a
	 * workload was, and in that हाल we will fill in the thपढ़ो_map when
	 * we विभाजन the workload in evlist__prepare_workload.
	 */
	अगर (trace->filter_pids.nr > 0) अणु
		err = evlist__append_tp_filter_pids(trace->evlist, trace->filter_pids.nr,
						    trace->filter_pids.entries);
		अगर (!err && trace->filter_pids.map) अणु
			err = bpf_map__set_filter_pids(trace->filter_pids.map, trace->filter_pids.nr,
						       trace->filter_pids.entries);
		पूर्ण
	पूर्ण अन्यथा अगर (perf_thपढ़ो_map__pid(trace->evlist->core.thपढ़ोs, 0) == -1) अणु
		err = trace__set_filter_loop_pids(trace);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक __trace__deliver_event(काष्ठा trace *trace, जोड़ perf_event *event)
अणु
	काष्ठा evlist *evlist = trace->evlist;
	काष्ठा perf_sample sample;
	पूर्णांक err = evlist__parse_sample(evlist, event, &sample);

	अगर (err)
		ख_लिखो(trace->output, "Can't parse sample, err = %d, skipping...\n", err);
	अन्यथा
		trace__handle_event(trace, event, &sample);

	वापस 0;
पूर्ण

अटल पूर्णांक __trace__flush_events(काष्ठा trace *trace)
अणु
	u64 first = ordered_events__first_समय(&trace->oe.data);
	u64 flush = trace->oe.last - NSEC_PER_SEC;

	/* Is there some thing to flush.. */
	अगर (first && first < flush)
		वापस ordered_events__flush_समय(&trace->oe.data, flush);

	वापस 0;
पूर्ण

अटल पूर्णांक trace__flush_events(काष्ठा trace *trace)
अणु
	वापस !trace->sort_events ? 0 : __trace__flush_events(trace);
पूर्ण

अटल पूर्णांक trace__deliver_event(काष्ठा trace *trace, जोड़ perf_event *event)
अणु
	पूर्णांक err;

	अगर (!trace->sort_events)
		वापस __trace__deliver_event(trace, event);

	err = evlist__parse_sample_बारtamp(trace->evlist, event, &trace->oe.last);
	अगर (err && err != -1)
		वापस err;

	err = ordered_events__queue(&trace->oe.data, event, trace->oe.last, 0);
	अगर (err)
		वापस err;

	वापस trace__flush_events(trace);
पूर्ण

अटल पूर्णांक ordered_events__deliver_event(काष्ठा ordered_events *oe,
					 काष्ठा ordered_event *event)
अणु
	काष्ठा trace *trace = container_of(oe, काष्ठा trace, oe.data);

	वापस __trace__deliver_event(trace, event->event);
पूर्ण

अटल काष्ठा syscall_arg_fmt *evsel__find_syscall_arg_fmt_by_name(काष्ठा evsel *evsel, अक्षर *arg)
अणु
	काष्ठा tep_क्रमmat_field *field;
	काष्ठा syscall_arg_fmt *fmt = __evsel__syscall_arg_fmt(evsel);

	अगर (evsel->tp_क्रमmat == शून्य || fmt == शून्य)
		वापस शून्य;

	क्रम (field = evsel->tp_क्रमmat->क्रमmat.fields; field; field = field->next, ++fmt)
		अगर (म_भेद(field->name, arg) == 0)
			वापस fmt;

	वापस शून्य;
पूर्ण

अटल पूर्णांक trace__expand_filter(काष्ठा trace *trace __maybe_unused, काष्ठा evsel *evsel)
अणु
	अक्षर *tok, *left = evsel->filter, *new_filter = evsel->filter;

	जबतक ((tok = strpbrk(left, "=<>!")) != शून्य) अणु
		अक्षर *right = tok + 1, *right_end;

		अगर (*right == '=')
			++right;

		जबतक (है_खाली(*right))
			++right;

		अगर (*right == '\0')
			अवरोध;

		जबतक (!है_अक्षर(*left))
			अगर (++left == tok) अणु
				/*
				 * Bail out, can't find the name of the argument that is being
				 * used in the filter, let it try to set this filter, will fail later.
				 */
				वापस 0;
			पूर्ण

		right_end = right + 1;
		जबतक (है_अक्षर_अंक(*right_end) || *right_end == '_' || *right_end == '|')
			++right_end;

		अगर (है_अक्षर(*right)) अणु
			काष्ठा syscall_arg_fmt *fmt;
			पूर्णांक left_size = tok - left,
			    right_size = right_end - right;
			अक्षर arg[128];

			जबतक (है_खाली(left[left_size - 1]))
				--left_size;

			scnम_लिखो(arg, माप(arg), "%.*s", left_size, left);

			fmt = evsel__find_syscall_arg_fmt_by_name(evsel, arg);
			अगर (fmt == शून्य) अणु
				pr_err("\"%s\" not found in \"%s\", can't set filter \"%s\"\n",
				       arg, evsel->name, evsel->filter);
				वापस -1;
			पूर्ण

			pr_debug2("trying to expand \"%s\" \"%.*s\" \"%.*s\" -> ",
				 arg, (पूर्णांक)(right - tok), tok, right_size, right);

			अगर (fmt->म_से_अदीर्घ) अणु
				u64 val;
				काष्ठा syscall_arg syscall_arg = अणु
					.parm = fmt->parm,
				पूर्ण;

				अगर (fmt->म_से_अदीर्घ(right, right_size, &syscall_arg, &val)) अणु
					अक्षर *n, expansion[19];
					पूर्णांक expansion_lenght = scnम_लिखो(expansion, माप(expansion), "%#" PRIx64, val);
					पूर्णांक expansion_offset = right - new_filter;

					pr_debug("%s", expansion);

					अगर (aप्र_लिखो(&n, "%.*s%s%s", expansion_offset, new_filter, expansion, right_end) < 0) अणु
						pr_debug(" out of memory!\n");
						मुक्त(new_filter);
						वापस -1;
					पूर्ण
					अगर (new_filter != evsel->filter)
						मुक्त(new_filter);
					left = n + expansion_offset + expansion_lenght;
					new_filter = n;
				पूर्ण अन्यथा अणु
					pr_err("\"%.*s\" not found for \"%s\" in \"%s\", can't set filter \"%s\"\n",
					       right_size, right, arg, evsel->name, evsel->filter);
					वापस -1;
				पूर्ण
			पूर्ण अन्यथा अणु
				pr_err("No resolver (strtoul) for \"%s\" in \"%s\", can't set filter \"%s\"\n",
				       arg, evsel->name, evsel->filter);
				वापस -1;
			पूर्ण

			pr_debug("\n");
		पूर्ण अन्यथा अणु
			left = right_end;
		पूर्ण
	पूर्ण

	अगर (new_filter != evsel->filter) अणु
		pr_debug("New filter for %s: %s\n", evsel->name, new_filter);
		evsel__set_filter(evsel, new_filter);
		मुक्त(new_filter);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक trace__expand_filters(काष्ठा trace *trace, काष्ठा evsel **err_evsel)
अणु
	काष्ठा evlist *evlist = trace->evlist;
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->filter == शून्य)
			जारी;

		अगर (trace__expand_filter(trace, evsel)) अणु
			*err_evsel = evsel;
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक trace__run(काष्ठा trace *trace, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा evlist *evlist = trace->evlist;
	काष्ठा evsel *evsel, *pgfault_maj = शून्य, *pgfault_min = शून्य;
	पूर्णांक err = -1, i;
	अचिन्हित दीर्घ beक्रमe;
	स्थिर bool विभाजनs = argc > 0;
	bool draining = false;

	trace->live = true;

	अगर (!trace->raw_augmented_syscalls) अणु
		अगर (trace->trace_syscalls && trace__add_syscall_newtp(trace))
			जाओ out_error_raw_syscalls;

		अगर (trace->trace_syscalls)
			trace->vfs_getname = evlist__add_vfs_getname(evlist);
	पूर्ण

	अगर ((trace->trace_pgfaults & TRACE_PFMAJ)) अणु
		pgfault_maj = evsel__new_pgfault(PERF_COUNT_SW_PAGE_FAULTS_MAJ);
		अगर (pgfault_maj == शून्य)
			जाओ out_error_mem;
		evsel__config_callchain(pgfault_maj, &trace->opts, &callchain_param);
		evlist__add(evlist, pgfault_maj);
	पूर्ण

	अगर ((trace->trace_pgfaults & TRACE_PFMIN)) अणु
		pgfault_min = evsel__new_pgfault(PERF_COUNT_SW_PAGE_FAULTS_MIN);
		अगर (pgfault_min == शून्य)
			जाओ out_error_mem;
		evsel__config_callchain(pgfault_min, &trace->opts, &callchain_param);
		evlist__add(evlist, pgfault_min);
	पूर्ण

	अगर (trace->sched &&
	    evlist__add_newtp(evlist, "sched", "sched_stat_runtime", trace__sched_stat_runसमय))
		जाओ out_error_sched_stat_runसमय;
	/*
	 * If a global cgroup was set, apply it to all the events without an
	 * explicit cgroup. I.e.:
	 *
	 * 	trace -G A -e sched:*चयन
	 *
	 * Will set all raw_syscalls:sys_अणुenter,निकासपूर्ण, pgfault, vfs_getname, etc
	 * _and_ sched:sched_चयन to the 'A' cgroup, जबतक:
	 *
	 * trace -e sched:*चयन -G A
	 *
	 * will only set the sched:sched_चयन event to the 'A' cgroup, all the
	 * other events (raw_syscalls:sys_अणुenter,निकासपूर्ण, etc are left "without"
	 * a cgroup (on the root cgroup, sys wide, etc).
	 *
	 * Multiple cgroups:
	 *
	 * trace -G A -e sched:*चयन -G B
	 *
	 * the syscall ones go to the 'A' cgroup, the sched:sched_चयन goes
	 * to the 'B' cgroup.
	 *
	 * evlist__set_शेष_cgroup() grअसल a reference of the passed cgroup
	 * only क्रम the evsels still without a cgroup, i.e. evsel->cgroup == शून्य.
	 */
	अगर (trace->cgroup)
		evlist__set_शेष_cgroup(trace->evlist, trace->cgroup);

	err = evlist__create_maps(evlist, &trace->opts.target);
	अगर (err < 0) अणु
		ख_लिखो(trace->output, "Problems parsing the target to trace, check your options!\n");
		जाओ out_delete_evlist;
	पूर्ण

	err = trace__symbols_init(trace, evlist);
	अगर (err < 0) अणु
		ख_लिखो(trace->output, "Problems initializing symbol libraries!\n");
		जाओ out_delete_evlist;
	पूर्ण

	evlist__config(evlist, &trace->opts, &callchain_param);

	अगर (विभाजनs) अणु
		err = evlist__prepare_workload(evlist, &trace->opts.target, argv, false, शून्य);
		अगर (err < 0) अणु
			ख_लिखो(trace->output, "Couldn't run the workload!\n");
			जाओ out_delete_evlist;
		पूर्ण
	पूर्ण

	err = evlist__खोलो(evlist);
	अगर (err < 0)
		जाओ out_error_खोलो;

	err = bpf__apply_obj_config();
	अगर (err) अणु
		अक्षर errbuf[बफ_मान];

		bpf__म_त्रुटि_apply_obj_config(err, errbuf, माप(errbuf));
		pr_err("ERROR: Apply config to BPF failed: %s\n",
			 errbuf);
		जाओ out_error_खोलो;
	पूर्ण

	err = trace__set_filter_pids(trace);
	अगर (err < 0)
		जाओ out_error_mem;

	अगर (trace->syscalls.map)
		trace__init_syscalls_bpf_map(trace);

	अगर (trace->syscalls.prog_array.sys_enter)
		trace__init_syscalls_bpf_prog_array_maps(trace);

	अगर (trace->ev_qualअगरier_ids.nr > 0) अणु
		err = trace__set_ev_qualअगरier_filter(trace);
		अगर (err < 0)
			जाओ out_त्रुटि_सं;

		अगर (trace->syscalls.events.sys_निकास) अणु
			pr_debug("event qualifier tracepoint filter: %s\n",
				 trace->syscalls.events.sys_निकास->filter);
		पूर्ण
	पूर्ण

	/*
	 * If the "close" syscall is not traced, then we will not have the
	 * opportunity to, in syscall_arg__scnम_लिखो_बंद_fd() invalidate the
	 * fd->pathname table and were ending up showing the last value set by
	 * syscalls खोलोing a pathname and associating it with a descriptor or
	 * पढ़ोing it from /proc/pid/fd/ in हालs where that करोesn't make
	 * sense.
	 *
	 *  So just disable this beautअगरier (SCA_FD, SCA_FDAT) when 'close' is
	 *  not in use.
	 */
	trace->fd_path_disabled = !trace__syscall_enabled(trace, syscalltbl__id(trace->sctbl, "close"));

	err = trace__expand_filters(trace, &evsel);
	अगर (err)
		जाओ out_delete_evlist;
	err = evlist__apply_filters(evlist, &evsel);
	अगर (err < 0)
		जाओ out_error_apply_filters;

	अगर (trace->dump.map)
		bpf_map__ख_लिखो(trace->dump.map, trace->output);

	err = evlist__mmap(evlist, trace->opts.mmap_pages);
	अगर (err < 0)
		जाओ out_error_mmap;

	अगर (!target__none(&trace->opts.target) && !trace->opts.initial_delay)
		evlist__enable(evlist);

	अगर (विभाजनs)
		evlist__start_workload(evlist);

	अगर (trace->opts.initial_delay) अणु
		usleep(trace->opts.initial_delay * 1000);
		evlist__enable(evlist);
	पूर्ण

	trace->multiple_thपढ़ोs = perf_thपढ़ो_map__pid(evlist->core.thपढ़ोs, 0) == -1 ||
				  evlist->core.thपढ़ोs->nr > 1 ||
				  evlist__first(evlist)->core.attr.inherit;

	/*
	 * Now that we alपढ़ोy used evsel->core.attr to ask the kernel to setup the
	 * events, lets reuse evsel->core.attr.sample_max_stack as the limit in
	 * trace__resolve_callchain(), allowing per-event max-stack settings
	 * to override an explicitly set --max-stack global setting.
	 */
	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel__has_callchain(evsel) &&
		    evsel->core.attr.sample_max_stack == 0)
			evsel->core.attr.sample_max_stack = trace->max_stack;
	पूर्ण
again:
	beक्रमe = trace->nr_events;

	क्रम (i = 0; i < evlist->core.nr_mmaps; i++) अणु
		जोड़ perf_event *event;
		काष्ठा mmap *md;

		md = &evlist->mmap[i];
		अगर (perf_mmap__पढ़ो_init(&md->core) < 0)
			जारी;

		जबतक ((event = perf_mmap__पढ़ो_event(&md->core)) != शून्य) अणु
			++trace->nr_events;

			err = trace__deliver_event(trace, event);
			अगर (err)
				जाओ out_disable;

			perf_mmap__consume(&md->core);

			अगर (पूर्णांकerrupted)
				जाओ out_disable;

			अगर (करोne && !draining) अणु
				evlist__disable(evlist);
				draining = true;
			पूर्ण
		पूर्ण
		perf_mmap__पढ़ो_करोne(&md->core);
	पूर्ण

	अगर (trace->nr_events == beक्रमe) अणु
		पूर्णांक समयout = करोne ? 100 : -1;

		अगर (!draining && evlist__poll(evlist, समयout) > 0) अणु
			अगर (evlist__filter_pollfd(evlist, POLLERR | POLLHUP | POLLNVAL) == 0)
				draining = true;

			जाओ again;
		पूर्ण अन्यथा अणु
			अगर (trace__flush_events(trace))
				जाओ out_disable;
		पूर्ण
	पूर्ण अन्यथा अणु
		जाओ again;
	पूर्ण

out_disable:
	thपढ़ो__zput(trace->current);

	evlist__disable(evlist);

	अगर (trace->sort_events)
		ordered_events__flush(&trace->oe.data, OE_FLUSH__FINAL);

	अगर (!err) अणु
		अगर (trace->summary)
			trace__ख_लिखो_thपढ़ो_summary(trace, trace->output);

		अगर (trace->show_tool_stats) अणु
			ख_लिखो(trace->output, "Stats:\n "
					       " vfs_getname : %" PRIu64 "\n"
					       " proc_getname: %" PRIu64 "\n",
				trace->stats.vfs_getname,
				trace->stats.proc_getname);
		पूर्ण
	पूर्ण

out_delete_evlist:
	trace__symbols__निकास(trace);

	evlist__delete(evlist);
	cgroup__put(trace->cgroup);
	trace->evlist = शून्य;
	trace->live = false;
	वापस err;
अणु
	अक्षर errbuf[बफ_मान];

out_error_sched_stat_runसमय:
	tracing_path__म_त्रुटि_खोलो_tp(त्रुटि_सं, errbuf, माप(errbuf), "sched", "sched_stat_runtime");
	जाओ out_error;

out_error_raw_syscalls:
	tracing_path__म_त्रुटि_खोलो_tp(त्रुटि_सं, errbuf, माप(errbuf), "raw_syscalls", "sys_(enter|exit)");
	जाओ out_error;

out_error_mmap:
	evlist__म_त्रुटि_mmap(evlist, त्रुटि_सं, errbuf, माप(errbuf));
	जाओ out_error;

out_error_खोलो:
	evlist__म_त्रुटि_खोलो(evlist, त्रुटि_सं, errbuf, माप(errbuf));

out_error:
	ख_लिखो(trace->output, "%s\n", errbuf);
	जाओ out_delete_evlist;

out_error_apply_filters:
	ख_लिखो(trace->output,
		"Failed to set filter \"%s\" on event %s with %d (%s)\n",
		evsel->filter, evsel__name(evsel), त्रुटि_सं,
		str_error_r(त्रुटि_सं, errbuf, माप(errbuf)));
	जाओ out_delete_evlist;
पूर्ण
out_error_mem:
	ख_लिखो(trace->output, "Not enough memory to run!\n");
	जाओ out_delete_evlist;

out_त्रुटि_सं:
	ख_लिखो(trace->output, "errno=%d,%s\n", त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
	जाओ out_delete_evlist;
पूर्ण

अटल पूर्णांक trace__replay(काष्ठा trace *trace)
अणु
	स्थिर काष्ठा evsel_str_handler handlers[] = अणु
		अणु "probe:vfs_getname",	     trace__vfs_getname, पूर्ण,
	पूर्ण;
	काष्ठा perf_data data = अणु
		.path  = input_name,
		.mode  = PERF_DATA_MODE_READ,
		.क्रमce = trace->क्रमce,
	पूर्ण;
	काष्ठा perf_session *session;
	काष्ठा evsel *evsel;
	पूर्णांक err = -1;

	trace->tool.sample	  = trace__process_sample;
	trace->tool.mmap	  = perf_event__process_mmap;
	trace->tool.mmap2	  = perf_event__process_mmap2;
	trace->tool.comm	  = perf_event__process_comm;
	trace->tool.निकास	  = perf_event__process_निकास;
	trace->tool.विभाजन	  = perf_event__process_विभाजन;
	trace->tool.attr	  = perf_event__process_attr;
	trace->tool.tracing_data  = perf_event__process_tracing_data;
	trace->tool.build_id	  = perf_event__process_build_id;
	trace->tool.namespaces	  = perf_event__process_namespaces;

	trace->tool.ordered_events = true;
	trace->tool.ordering_requires_बारtamps = true;

	/* add tid to output */
	trace->multiple_thपढ़ोs = true;

	session = perf_session__new(&data, false, &trace->tool);
	अगर (IS_ERR(session))
		वापस PTR_ERR(session);

	अगर (trace->opts.target.pid)
		symbol_conf.pid_list_str = strdup(trace->opts.target.pid);

	अगर (trace->opts.target.tid)
		symbol_conf.tid_list_str = strdup(trace->opts.target.tid);

	अगर (symbol__init(&session->header.env) < 0)
		जाओ out;

	trace->host = &session->machines.host;

	err = perf_session__set_tracepoपूर्णांकs_handlers(session, handlers);
	अगर (err)
		जाओ out;

	evsel = evlist__find_tracepoपूर्णांक_by_name(session->evlist, "raw_syscalls:sys_enter");
	/* older kernels have syscalls tp versus raw_syscalls */
	अगर (evsel == शून्य)
		evsel = evlist__find_tracepoपूर्णांक_by_name(session->evlist, "syscalls:sys_enter");

	अगर (evsel &&
	    (evsel__init_raw_syscall_tp(evsel, trace__sys_enter) < 0 ||
	    perf_evsel__init_sc_tp_ptr_field(evsel, args))) अणु
		pr_err("Error during initialize raw_syscalls:sys_enter event\n");
		जाओ out;
	पूर्ण

	evsel = evlist__find_tracepoपूर्णांक_by_name(session->evlist, "raw_syscalls:sys_exit");
	अगर (evsel == शून्य)
		evsel = evlist__find_tracepoपूर्णांक_by_name(session->evlist, "syscalls:sys_exit");
	अगर (evsel &&
	    (evsel__init_raw_syscall_tp(evsel, trace__sys_निकास) < 0 ||
	    perf_evsel__init_sc_tp_uपूर्णांक_field(evsel, ret))) अणु
		pr_err("Error during initialize raw_syscalls:sys_exit event\n");
		जाओ out;
	पूर्ण

	evlist__क्रम_each_entry(session->evlist, evsel) अणु
		अगर (evsel->core.attr.type == PERF_TYPE_SOFTWARE &&
		    (evsel->core.attr.config == PERF_COUNT_SW_PAGE_FAULTS_MAJ ||
		     evsel->core.attr.config == PERF_COUNT_SW_PAGE_FAULTS_MIN ||
		     evsel->core.attr.config == PERF_COUNT_SW_PAGE_FAULTS))
			evsel->handler = trace__pgfault;
	पूर्ण

	setup_pager();

	err = perf_session__process_events(session);
	अगर (err)
		pr_err("Failed to process events, error %d", err);

	अन्यथा अगर (trace->summary)
		trace__ख_लिखो_thपढ़ो_summary(trace, trace->output);

out:
	perf_session__delete(session);

	वापस err;
पूर्ण

अटल माप_प्रकार trace__ख_लिखो_thपढ़ोs_header(खाता *fp)
अणु
	माप_प्रकार prपूर्णांकed;

	prपूर्णांकed  = ख_लिखो(fp, "\n Summary of events:\n\n");

	वापस prपूर्णांकed;
पूर्ण

DEFINE_RESORT_RB(syscall_stats, a->msecs > b->msecs,
	काष्ठा syscall_stats *stats;
	द्विगुन		     msecs;
	पूर्णांक		     syscall;
)
अणु
	काष्ठा पूर्णांक_node *source = rb_entry(nd, काष्ठा पूर्णांक_node, rb_node);
	काष्ठा syscall_stats *stats = source->priv;

	entry->syscall = source->i;
	entry->stats   = stats;
	entry->msecs   = stats ? (u64)stats->stats.n * (avg_stats(&stats->stats) / NSEC_PER_MSEC) : 0;
पूर्ण

अटल माप_प्रकार thपढ़ो__dump_stats(काष्ठा thपढ़ो_trace *ttrace,
				 काष्ठा trace *trace, खाता *fp)
अणु
	माप_प्रकार prपूर्णांकed = 0;
	काष्ठा syscall *sc;
	काष्ठा rb_node *nd;
	DECLARE_RESORT_RB_INTLIST(syscall_stats, ttrace->syscall_stats);

	अगर (syscall_stats == शून्य)
		वापस 0;

	prपूर्णांकed += ख_लिखो(fp, "\n");

	prपूर्णांकed += ख_लिखो(fp, "   syscall            calls  errors  total       min       avg       max       stddev\n");
	prपूर्णांकed += ख_लिखो(fp, "                                     (msec)    (msec)    (msec)    (msec)        (%%)\n");
	prपूर्णांकed += ख_लिखो(fp, "   --------------- --------  ------ -------- --------- --------- ---------     ------\n");

	resort_rb__क्रम_each_entry(nd, syscall_stats) अणु
		काष्ठा syscall_stats *stats = syscall_stats_entry->stats;
		अगर (stats) अणु
			द्विगुन min = (द्विगुन)(stats->stats.min) / NSEC_PER_MSEC;
			द्विगुन max = (द्विगुन)(stats->stats.max) / NSEC_PER_MSEC;
			द्विगुन avg = avg_stats(&stats->stats);
			द्विगुन pct;
			u64 n = (u64)stats->stats.n;

			pct = avg ? 100.0 * stddev_stats(&stats->stats) / avg : 0.0;
			avg /= NSEC_PER_MSEC;

			sc = &trace->syscalls.table[syscall_stats_entry->syscall];
			prपूर्णांकed += ख_लिखो(fp, "   %-15s", sc->name);
			prपूर्णांकed += ख_लिखो(fp, " %8" PRIu64 " %6" PRIu64 " %9.3f %9.3f %9.3f",
					   n, stats->nr_failures, syscall_stats_entry->msecs, min, avg);
			prपूर्णांकed += ख_लिखो(fp, " %9.3f %9.2f%%\n", max, pct);

			अगर (trace->त्रुटि_सं_summary && stats->nr_failures) अणु
				स्थिर अक्षर *arch_name = perf_env__arch(trace->host->env);
				पूर्णांक e;

				क्रम (e = 0; e < stats->max_त्रुटि_सं; ++e) अणु
					अगर (stats->त्रुटि_संs[e] != 0)
						ख_लिखो(fp, "\t\t\t\t%s: %d\n", arch_syscalls__strत्रुटि_सं(arch_name, e + 1), stats->त्रुटि_संs[e]);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	resort_rb__delete(syscall_stats);
	prपूर्णांकed += ख_लिखो(fp, "\n\n");

	वापस prपूर्णांकed;
पूर्ण

अटल माप_प्रकार trace__ख_लिखो_thपढ़ो(खाता *fp, काष्ठा thपढ़ो *thपढ़ो, काष्ठा trace *trace)
अणु
	माप_प्रकार prपूर्णांकed = 0;
	काष्ठा thपढ़ो_trace *ttrace = thपढ़ो__priv(thपढ़ो);
	द्विगुन ratio;

	अगर (ttrace == शून्य)
		वापस 0;

	ratio = (द्विगुन)ttrace->nr_events / trace->nr_events * 100.0;

	prपूर्णांकed += ख_लिखो(fp, " %s (%d), ", thपढ़ो__comm_str(thपढ़ो), thपढ़ो->tid);
	prपूर्णांकed += ख_लिखो(fp, "%lu events, ", ttrace->nr_events);
	prपूर्णांकed += ख_लिखो(fp, "%.1f%%", ratio);
	अगर (ttrace->pfmaj)
		prपूर्णांकed += ख_लिखो(fp, ", %lu majfaults", ttrace->pfmaj);
	अगर (ttrace->pfmin)
		prपूर्णांकed += ख_लिखो(fp, ", %lu minfaults", ttrace->pfmin);
	अगर (trace->sched)
		prपूर्णांकed += ख_लिखो(fp, ", %.3f msec\n", ttrace->runसमय_ms);
	अन्यथा अगर (ख_अक्षर_दो('\n', fp) != खातापूर्ण)
		++prपूर्णांकed;

	prपूर्णांकed += thपढ़ो__dump_stats(ttrace, trace, fp);

	वापस prपूर्णांकed;
पूर्ण

अटल अचिन्हित दीर्घ thपढ़ो__nr_events(काष्ठा thपढ़ो_trace *ttrace)
अणु
	वापस ttrace ? ttrace->nr_events : 0;
पूर्ण

DEFINE_RESORT_RB(thपढ़ोs, (thपढ़ो__nr_events(a->thपढ़ो->priv) < thपढ़ो__nr_events(b->thपढ़ो->priv)),
	काष्ठा thपढ़ो *thपढ़ो;
)
अणु
	entry->thपढ़ो = rb_entry(nd, काष्ठा thपढ़ो, rb_node);
पूर्ण

अटल माप_प्रकार trace__ख_लिखो_thपढ़ो_summary(काष्ठा trace *trace, खाता *fp)
अणु
	माप_प्रकार prपूर्णांकed = trace__ख_लिखो_thपढ़ोs_header(fp);
	काष्ठा rb_node *nd;
	पूर्णांक i;

	क्रम (i = 0; i < THREADS__TABLE_SIZE; i++) अणु
		DECLARE_RESORT_RB_MACHINE_THREADS(thपढ़ोs, trace->host, i);

		अगर (thपढ़ोs == शून्य) अणु
			ख_लिखो(fp, "%s", "Error sorting output by nr_events!\n");
			वापस 0;
		पूर्ण

		resort_rb__क्रम_each_entry(nd, thपढ़ोs)
			prपूर्णांकed += trace__ख_लिखो_thपढ़ो(fp, thपढ़ोs_entry->thपढ़ो, trace);

		resort_rb__delete(thपढ़ोs);
	पूर्ण
	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक trace__set_duration(स्थिर काष्ठा option *opt, स्थिर अक्षर *str,
			       पूर्णांक unset __maybe_unused)
अणु
	काष्ठा trace *trace = opt->value;

	trace->duration_filter = म_से_भ(str);
	वापस 0;
पूर्ण

अटल पूर्णांक trace__set_filter_pids_from_option(स्थिर काष्ठा option *opt, स्थिर अक्षर *str,
					      पूर्णांक unset __maybe_unused)
अणु
	पूर्णांक ret = -1;
	माप_प्रकार i;
	काष्ठा trace *trace = opt->value;
	/*
	 * FIXME: पूर्णांकroduce a पूर्णांकarray class, plain parse csv and create a
	 * अणु पूर्णांक nr, पूर्णांक entries[] पूर्ण काष्ठा...
	 */
	काष्ठा पूर्णांकlist *list = पूर्णांकlist__new(str);

	अगर (list == शून्य)
		वापस -1;

	i = trace->filter_pids.nr = पूर्णांकlist__nr_entries(list) + 1;
	trace->filter_pids.entries = सुस्मृति(i, माप(pid_t));

	अगर (trace->filter_pids.entries == शून्य)
		जाओ out;

	trace->filter_pids.entries[0] = getpid();

	क्रम (i = 1; i < trace->filter_pids.nr; ++i)
		trace->filter_pids.entries[i] = पूर्णांकlist__entry(list, i - 1)->i;

	पूर्णांकlist__delete(list);
	ret = 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक trace__खोलो_output(काष्ठा trace *trace, स्थिर अक्षर *filename)
अणु
	काष्ठा stat st;

	अगर (!stat(filename, &st) && st.st_size) अणु
		अक्षर oldname[PATH_MAX];

		scnम_लिखो(oldname, माप(oldname), "%s.old", filename);
		unlink(oldname);
		नाम(filename, oldname);
	पूर्ण

	trace->output = ख_खोलो(filename, "w");

	वापस trace->output == शून्य ? -त्रुटि_सं : 0;
पूर्ण

अटल पूर्णांक parse_pagefaults(स्थिर काष्ठा option *opt, स्थिर अक्षर *str,
			    पूर्णांक unset __maybe_unused)
अणु
	पूर्णांक *trace_pgfaults = opt->value;

	अगर (म_भेद(str, "all") == 0)
		*trace_pgfaults |= TRACE_PFMAJ | TRACE_PFMIN;
	अन्यथा अगर (म_भेद(str, "maj") == 0)
		*trace_pgfaults |= TRACE_PFMAJ;
	अन्यथा अगर (म_भेद(str, "min") == 0)
		*trace_pgfaults |= TRACE_PFMIN;
	अन्यथा
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम evlist__set_शेष_evsel_handler(काष्ठा evlist *evlist, व्योम *handler)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->handler == शून्य)
			evsel->handler = handler;
	पूर्ण
पूर्ण

अटल व्योम evsel__set_syscall_arg_fmt(काष्ठा evsel *evsel, स्थिर अक्षर *name)
अणु
	काष्ठा syscall_arg_fmt *fmt = evsel__syscall_arg_fmt(evsel);

	अगर (fmt) अणु
		काष्ठा syscall_fmt *scfmt = syscall_fmt__find(name);

		अगर (scfmt) अणु
			पूर्णांक skip = 0;

			अगर (म_भेद(evsel->tp_क्रमmat->क्रमmat.fields->name, "__syscall_nr") == 0 ||
			    म_भेद(evsel->tp_क्रमmat->क्रमmat.fields->name, "nr") == 0)
				++skip;

			स_नकल(fmt + skip, scfmt->arg, (evsel->tp_क्रमmat->क्रमmat.nr_fields - skip) * माप(*fmt));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक evlist__set_syscall_tp_fields(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->priv || !evsel->tp_क्रमmat)
			जारी;

		अगर (म_भेद(evsel->tp_क्रमmat->प्रणाली, "syscalls")) अणु
			evsel__init_tp_arg_scnम_लिखो(evsel);
			जारी;
		पूर्ण

		अगर (evsel__init_syscall_tp(evsel))
			वापस -1;

		अगर (!म_भेदन(evsel->tp_क्रमmat->name, "sys_enter_", 10)) अणु
			काष्ठा syscall_tp *sc = __evsel__syscall_tp(evsel);

			अगर (__tp_field__init_ptr(&sc->args, sc->id.offset + माप(u64)))
				वापस -1;

			evsel__set_syscall_arg_fmt(evsel, evsel->tp_क्रमmat->name + माप("sys_enter_") - 1);
		पूर्ण अन्यथा अगर (!म_भेदन(evsel->tp_क्रमmat->name, "sys_exit_", 9)) अणु
			काष्ठा syscall_tp *sc = __evsel__syscall_tp(evsel);

			अगर (__tp_field__init_uपूर्णांक(&sc->ret, माप(u64), sc->id.offset + माप(u64), evsel->needs_swap))
				वापस -1;

			evsel__set_syscall_arg_fmt(evsel, evsel->tp_क्रमmat->name + माप("sys_exit_") - 1);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * XXX: Hackish, just splitting the combined -e+--event (syscalls
 * (raw_syscalls:अणुsys_अणुenter,निकासपूर्णपूर्ण + events (tracepoपूर्णांकs, HW, SW, etc) to use
 * existing facilities unchanged (trace->ev_qualअगरier + parse_options()).
 *
 * It'd be better to पूर्णांकroduce a parse_options() variant that would वापस a
 * list with the terms it didn't match to an event...
 */
अटल पूर्णांक trace__parse_events_option(स्थिर काष्ठा option *opt, स्थिर अक्षर *str,
				      पूर्णांक unset __maybe_unused)
अणु
	काष्ठा trace *trace = (काष्ठा trace *)opt->value;
	स्थिर अक्षर *s = str;
	अक्षर *sep = शून्य, *lists[2] = अणु शून्य, शून्य, पूर्ण;
	पूर्णांक len = म_माप(str) + 1, err = -1, list, idx;
	अक्षर *strace_groups_dir = प्रणाली_path(STRACE_GROUPS_सूची);
	अक्षर group_name[PATH_MAX];
	काष्ठा syscall_fmt *fmt;

	अगर (strace_groups_dir == शून्य)
		वापस -1;

	अगर (*s == '!') अणु
		++s;
		trace->not_ev_qualअगरier = true;
	पूर्ण

	जबतक (1) अणु
		अगर ((sep = म_अक्षर(s, ',')) != शून्य)
			*sep = '\0';

		list = 0;
		अगर (syscalltbl__id(trace->sctbl, s) >= 0 ||
		    syscalltbl__strglobmatch_first(trace->sctbl, s, &idx) >= 0) अणु
			list = 1;
			जाओ करो_concat;
		पूर्ण

		fmt = syscall_fmt__find_by_alias(s);
		अगर (fmt != शून्य) अणु
			list = 1;
			s = fmt->name;
		पूर्ण अन्यथा अणु
			path__join(group_name, माप(group_name), strace_groups_dir, s);
			अगर (access(group_name, R_OK) == 0)
				list = 1;
		पूर्ण
करो_concat:
		अगर (lists[list]) अणु
			प्र_लिखो(lists[list] + म_माप(lists[list]), ",%s", s);
		पूर्ण अन्यथा अणु
			lists[list] = दो_स्मृति(len);
			अगर (lists[list] == शून्य)
				जाओ out;
			म_नकल(lists[list], s);
		पूर्ण

		अगर (!sep)
			अवरोध;

		*sep = ',';
		s = sep + 1;
	पूर्ण

	अगर (lists[1] != शून्य) अणु
		काष्ठा strlist_config slist_config = अणु
			.स_नाम = strace_groups_dir,
		पूर्ण;

		trace->ev_qualअगरier = strlist__new(lists[1], &slist_config);
		अगर (trace->ev_qualअगरier == शून्य) अणु
			ख_माला_दो("Not enough memory to parse event qualifier", trace->output);
			जाओ out;
		पूर्ण

		अगर (trace__validate_ev_qualअगरier(trace))
			जाओ out;
		trace->trace_syscalls = true;
	पूर्ण

	err = 0;

	अगर (lists[0]) अणु
		काष्ठा option o = अणु
			.value = &trace->evlist,
		पूर्ण;
		err = parse_events_option(&o, lists[0], 0);
	पूर्ण
out:
	अगर (sep)
		*sep = ',';

	वापस err;
पूर्ण

अटल पूर्णांक trace__parse_cgroups(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset)
अणु
	काष्ठा trace *trace = opt->value;

	अगर (!list_empty(&trace->evlist->core.entries)) अणु
		काष्ठा option o = अणु
			.value = &trace->evlist,
		पूर्ण;
		वापस parse_cgroups(&o, str, unset);
	पूर्ण
	trace->cgroup = evlist__findnew_cgroup(trace->evlist, str);

	वापस 0;
पूर्ण

अटल पूर्णांक trace__config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *arg)
अणु
	काष्ठा trace *trace = arg;
	पूर्णांक err = 0;

	अगर (!म_भेद(var, "trace.add_events")) अणु
		trace->perfconfig_events = strdup(value);
		अगर (trace->perfconfig_events == शून्य) अणु
			pr_err("Not enough memory for %s\n", "trace.add_events");
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेद(var, "trace.show_timestamp")) अणु
		trace->show_tstamp = perf_config_bool(var, value);
	पूर्ण अन्यथा अगर (!म_भेद(var, "trace.show_duration")) अणु
		trace->show_duration = perf_config_bool(var, value);
	पूर्ण अन्यथा अगर (!म_भेद(var, "trace.show_arg_names")) अणु
		trace->show_arg_names = perf_config_bool(var, value);
		अगर (!trace->show_arg_names)
			trace->show_zeros = true;
	पूर्ण अन्यथा अगर (!म_भेद(var, "trace.show_zeros")) अणु
		bool new_show_zeros = perf_config_bool(var, value);
		अगर (!trace->show_arg_names && !new_show_zeros) अणु
			pr_warning("trace.show_zeros has to be set when trace.show_arg_names=no\n");
			जाओ out;
		पूर्ण
		trace->show_zeros = new_show_zeros;
	पूर्ण अन्यथा अगर (!म_भेद(var, "trace.show_prefix")) अणु
		trace->show_string_prefix = perf_config_bool(var, value);
	पूर्ण अन्यथा अगर (!म_भेद(var, "trace.no_inherit")) अणु
		trace->opts.no_inherit = perf_config_bool(var, value);
	पूर्ण अन्यथा अगर (!म_भेद(var, "trace.args_alignment")) अणु
		पूर्णांक args_alignment = 0;
		अगर (perf_config_पूर्णांक(&args_alignment, var, value) == 0)
			trace->args_alignment = args_alignment;
	पूर्ण अन्यथा अगर (!म_भेद(var, "trace.tracepoint_beautifiers")) अणु
		अगर (strहालcmp(value, "libtraceevent") == 0)
			trace->libtraceevent_prपूर्णांक = true;
		अन्यथा अगर (strहालcmp(value, "libbeauty") == 0)
			trace->libtraceevent_prपूर्णांक = false;
	पूर्ण
out:
	वापस err;
पूर्ण

पूर्णांक cmd_trace(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर अक्षर *trace_usage[] = अणु
		"perf trace [<options>] [<command>]",
		"perf trace [<options>] -- <command> [<options>]",
		"perf trace record [<options>] [<command>]",
		"perf trace record [<options>] -- <command> [<options>]",
		शून्य
	पूर्ण;
	काष्ठा trace trace = अणु
		.opts = अणु
			.target = अणु
				.uid	   = अच_पूर्णांक_उच्च,
				.uses_mmap = true,
			पूर्ण,
			.user_freq     = अच_पूर्णांक_उच्च,
			.user_पूर्णांकerval = ULदीर्घ_उच्च,
			.no_buffering  = true,
			.mmap_pages    = अच_पूर्णांक_उच्च,
		पूर्ण,
		.output = मानक_त्रुटि,
		.show_comm = true,
		.show_tstamp = true,
		.show_duration = true,
		.show_arg_names = true,
		.args_alignment = 70,
		.trace_syscalls = false,
		.kernel_syscallchains = false,
		.max_stack = अच_पूर्णांक_उच्च,
		.max_events = अच_दीर्घ_उच्च,
	पूर्ण;
	स्थिर अक्षर *map_dump_str = शून्य;
	स्थिर अक्षर *output_name = शून्य;
	स्थिर काष्ठा option trace_options[] = अणु
	OPT_CALLBACK('e', "event", &trace, "event",
		     "event/syscall selector. use 'perf list' to list available events",
		     trace__parse_events_option),
	OPT_CALLBACK(0, "filter", &trace.evlist, "filter",
		     "event filter", parse_filter),
	OPT_BOOLEAN(0, "comm", &trace.show_comm,
		    "show the thread COMM next to its id"),
	OPT_BOOLEAN(0, "tool_stats", &trace.show_tool_stats, "show tool stats"),
	OPT_CALLBACK(0, "expr", &trace, "expr", "list of syscalls/events to trace",
		     trace__parse_events_option),
	OPT_STRING('o', "output", &output_name, "file", "output file name"),
	OPT_STRING('i', "input", &input_name, "file", "Analyze events in file"),
	OPT_STRING('p', "pid", &trace.opts.target.pid, "pid",
		    "trace events on existing process id"),
	OPT_STRING('t', "tid", &trace.opts.target.tid, "tid",
		    "trace events on existing thread id"),
	OPT_CALLBACK(0, "filter-pids", &trace, "CSV list of pids",
		     "pids to filter (by the kernel)", trace__set_filter_pids_from_option),
	OPT_BOOLEAN('a', "all-cpus", &trace.opts.target.प्रणाली_wide,
		    "system-wide collection from all CPUs"),
	OPT_STRING('C', "cpu", &trace.opts.target.cpu_list, "cpu",
		    "list of cpus to monitor"),
	OPT_BOOLEAN(0, "no-inherit", &trace.opts.no_inherit,
		    "child tasks do not inherit counters"),
	OPT_CALLBACK('m', "mmap-pages", &trace.opts.mmap_pages, "pages",
		     "number of mmap data pages", evlist__parse_mmap_pages),
	OPT_STRING('u', "uid", &trace.opts.target.uid_str, "user",
		   "user to profile"),
	OPT_CALLBACK(0, "duration", &trace, "float",
		     "show only events with duration > N.M ms",
		     trace__set_duration),
#अगर_घोषित HAVE_LIBBPF_SUPPORT
	OPT_STRING(0, "map-dump", &map_dump_str, "BPF map", "BPF map to periodically dump"),
#पूर्ण_अगर
	OPT_BOOLEAN(0, "sched", &trace.sched, "show blocking scheduler events"),
	OPT_INCR('v', "verbose", &verbose, "be more verbose"),
	OPT_BOOLEAN('T', "time", &trace.full_समय,
		    "Show full timestamp, not time relative to first start"),
	OPT_BOOLEAN(0, "failure", &trace.failure_only,
		    "Show only syscalls that failed"),
	OPT_BOOLEAN('s', "summary", &trace.summary_only,
		    "Show only syscall summary with statistics"),
	OPT_BOOLEAN('S', "with-summary", &trace.summary,
		    "Show all syscalls and summary with statistics"),
	OPT_BOOLEAN(0, "errno-summary", &trace.त्रुटि_सं_summary,
		    "Show errno stats per syscall, use with -s or -S"),
	OPT_CALLBACK_DEFAULT('F', "pf", &trace.trace_pgfaults, "all|maj|min",
		     "Trace pagefaults", parse_pagefaults, "maj"),
	OPT_BOOLEAN(0, "syscalls", &trace.trace_syscalls, "Trace syscalls"),
	OPT_BOOLEAN('f', "force", &trace.force, "don't complain, करो it"),
	OPT_CALLBACK(0, "call-graph", &trace.opts,
		     "record_mode[,record_size]", record_callchain_help,
		     &record_parse_callchain_opt),
	OPT_BOOLEAN(0, "libtraceevent_print", &trace.libtraceevent_prपूर्णांक,
		    "Use libtraceevent to print the tracepoint arguments."),
	OPT_BOOLEAN(0, "kernel-syscall-graph", &trace.kernel_syscallchains,
		    "Show the kernel callchains on the syscall exit path"),
	OPT_ULONG(0, "max-events", &trace.max_events,
		"Set the maximum number of events to print, exit after that is reached. "),
	OPT_UINTEGER(0, "min-stack", &trace.min_stack,
		     "Set the minimum stack depth when parsing the callchain, "
		     "anything below the specified depth will be ignored."),
	OPT_UINTEGER(0, "max-stack", &trace.max_stack,
		     "Set the maximum stack depth when parsing the callchain, "
		     "anything beyond the specified depth will be ignored. "
		     "Default: kernel.perf_event_max_stack or " __stringअगरy(PERF_MAX_STACK_DEPTH)),
	OPT_BOOLEAN(0, "sort-events", &trace.sort_events,
			"Sort batch of events before processing, use if getting out of order events"),
	OPT_BOOLEAN(0, "print-sample", &trace.prपूर्णांक_sample,
			"print the PERF_RECORD_SAMPLE PERF_SAMPLE_ info, for debugging"),
	OPT_UINTEGER(0, "proc-map-timeout", &proc_map_समयout,
			"per thread proc mmap processing timeout in ms"),
	OPT_CALLBACK('G', "cgroup", &trace, "name", "monitor event in cgroup name only",
		     trace__parse_cgroups),
	OPT_INTEGER('D', "delay", &trace.opts.initial_delay,
		     "ms to wait before starting measurement after program "
		     "start"),
	OPTS_EVSWITCH(&trace.evचयन),
	OPT_END()
	पूर्ण;
	bool __maybe_unused max_stack_user_set = true;
	bool mmap_pages_user_set = true;
	काष्ठा evsel *evsel;
	स्थिर अक्षर * स्थिर trace_subcommands[] = अणु "record", शून्य पूर्ण;
	पूर्णांक err = -1;
	अक्षर bf[बफ_मान];

	संकेत(संक_अंश, sighandler_dump_stack);
	संकेत(संक_भ_त्रुटि, sighandler_dump_stack);
	संकेत(SIGCHLD, sig_handler);
	संकेत(संक_विघ्न, sig_handler);

	trace.evlist = evlist__new();
	trace.sctbl = syscalltbl__new();

	अगर (trace.evlist == शून्य || trace.sctbl == शून्य) अणु
		pr_err("Not enough memory to run!\n");
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * Parsing .perfconfig may entail creating a BPF event, that may need
	 * to create BPF maps, so bump RLIM_MEMLOCK as the शेष 64K setting
	 * is too small. This affects just this process, not touching the
	 * global setting. If it fails we'll get something in 'perf trace -v'
	 * to help diagnose the problem.
	 */
	rlimit__bump_memlock();

	err = perf_config(trace__config, &trace);
	अगर (err)
		जाओ out;

	argc = parse_options_subcommand(argc, argv, trace_options, trace_subcommands,
				 trace_usage, PARSE_OPT_STOP_AT_NON_OPTION);

	/*
	 * Here we alपढ़ोy passed thru trace__parse_events_option() and it has
	 * alपढ़ोy figured out अगर -e syscall_name, अगर not but अगर --event
	 * foo:bar was used, the user is पूर्णांकerested _just_ in those, say,
	 * tracepoपूर्णांक events, not in the strace-like syscall-name-based mode.
	 *
	 * This is important because we need to check अगर strace-like mode is
	 * needed to decided अगर we should filter out the eBPF
	 * __augmented_syscalls__ code, अगर it is in the mix, say, via
	 * .perfconfig trace.add_events, and filter those out.
	 */
	अगर (!trace.trace_syscalls && !trace.trace_pgfaults &&
	    trace.evlist->core.nr_entries == 0 /* Was --events used? */) अणु
		trace.trace_syscalls = true;
	पूर्ण
	/*
	 * Now that we have --verbose figured out, lets see अगर we need to parse
	 * events from .perfconfig, so that अगर those events fail parsing, say some
	 * BPF program fails, then we'll be able to use --verbose to see what went
	 * wrong in more detail.
	 */
	अगर (trace.perfconfig_events != शून्य) अणु
		काष्ठा parse_events_error parse_err;

		bzero(&parse_err, माप(parse_err));
		err = parse_events(trace.evlist, trace.perfconfig_events, &parse_err);
		अगर (err) अणु
			parse_events_prपूर्णांक_error(&parse_err, trace.perfconfig_events);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर ((nr_cgroups || trace.cgroup) && !trace.opts.target.प्रणाली_wide) अणु
		usage_with_options_msg(trace_usage, trace_options,
				       "cgroup monitoring only available in system-wide mode");
	पूर्ण

	evsel = bpf__setup_output_event(trace.evlist, "__augmented_syscalls__");
	अगर (IS_ERR(evsel)) अणु
		bpf__म_त्रुटि_setup_output_event(trace.evlist, PTR_ERR(evsel), bf, माप(bf));
		pr_err("ERROR: Setup trace syscalls enter failed: %s\n", bf);
		जाओ out;
	पूर्ण

	अगर (evsel) अणु
		trace.syscalls.events.augmented = evsel;

		evsel = evlist__find_tracepoपूर्णांक_by_name(trace.evlist, "raw_syscalls:sys_enter");
		अगर (evsel == शून्य) अणु
			pr_err("ERROR: raw_syscalls:sys_enter not found in the augmented BPF object\n");
			जाओ out;
		पूर्ण

		अगर (evsel->bpf_obj == शून्य) अणु
			pr_err("ERROR: raw_syscalls:sys_enter not associated to a BPF object\n");
			जाओ out;
		पूर्ण

		trace.bpf_obj = evsel->bpf_obj;

		/*
		 * If we have _just_ the augmenter event but करोn't have a
		 * explicit --syscalls, then assume we want all strace-like
		 * syscalls:
		 */
		अगर (!trace.trace_syscalls && trace__only_augmented_syscalls_evsels(&trace))
			trace.trace_syscalls = true;
		/*
		 * So, अगर we have a syscall augmenter, but trace_syscalls, aka
		 * strace-like syscall tracing is not set, then we need to trow
		 * away the augmenter, i.e. all the events that were created
		 * from that BPF object file.
		 *
		 * This is more to fix the current .perfconfig trace.add_events
		 * style of setting up the strace-like eBPF based syscall poपूर्णांक
		 * payload augmenter.
		 *
		 * All this complनिकासy will be aव्योमed by adding an alternative
		 * to trace.add_events in the क्रमm of
		 * trace.bpf_augmented_syscalls, that will be only parsed अगर we
		 * need it.
		 *
		 * .perfconfig trace.add_events is still useful अगर we want, क्रम
		 * instance, have msr_ग_लिखो.msr in some .perfconfig profile based
		 * 'perf trace --config determinism.profile' mode, where क्रम some
		 * particular goal/workload type we want a set of events and
		 * output mode (with timings, etc) instead of having to add
		 * all via the command line.
		 *
		 * Also --config to specअगरy an alternate .perfconfig file needs
		 * to be implemented.
		 */
		अगर (!trace.trace_syscalls) अणु
			trace__delete_augmented_syscalls(&trace);
		पूर्ण अन्यथा अणु
			trace__set_bpf_map_filtered_pids(&trace);
			trace__set_bpf_map_syscalls(&trace);
			trace.syscalls.unaugmented_prog = trace__find_bpf_program_by_title(&trace, "!raw_syscalls:unaugmented");
		पूर्ण
	पूर्ण

	err = bpf__setup_मानक_निकास(trace.evlist);
	अगर (err) अणु
		bpf__म_त्रुटि_setup_मानक_निकास(trace.evlist, err, bf, माप(bf));
		pr_err("ERROR: Setup BPF stdout failed: %s\n", bf);
		जाओ out;
	पूर्ण

	err = -1;

	अगर (map_dump_str) अणु
		trace.dump.map = trace__find_bpf_map_by_name(&trace, map_dump_str);
		अगर (trace.dump.map == शून्य) अणु
			pr_err("ERROR: BPF map \"%s\" not found\n", map_dump_str);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (trace.trace_pgfaults) अणु
		trace.opts.sample_address = true;
		trace.opts.sample_समय = true;
	पूर्ण

	अगर (trace.opts.mmap_pages == अच_पूर्णांक_उच्च)
		mmap_pages_user_set = false;

	अगर (trace.max_stack == अच_पूर्णांक_उच्च) अणु
		trace.max_stack = input_name ? PERF_MAX_STACK_DEPTH : sysctl__max_stack();
		max_stack_user_set = false;
	पूर्ण

#अगर_घोषित HAVE_DWARF_UNWIND_SUPPORT
	अगर ((trace.min_stack || max_stack_user_set) && !callchain_param.enabled) अणु
		record_opts__parse_callchain(&trace.opts, &callchain_param, "dwarf", false);
	पूर्ण
#पूर्ण_अगर

	अगर (callchain_param.enabled) अणु
		अगर (!mmap_pages_user_set && geteuid() == 0)
			trace.opts.mmap_pages = perf_event_mlock_kb_in_pages() * 4;

		symbol_conf.use_callchain = true;
	पूर्ण

	अगर (trace.evlist->core.nr_entries > 0) अणु
		evlist__set_शेष_evsel_handler(trace.evlist, trace__event_handler);
		अगर (evlist__set_syscall_tp_fields(trace.evlist)) अणु
			लिखो_त्रुटि("failed to set syscalls:* tracepoint fields");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (trace.sort_events) अणु
		ordered_events__init(&trace.oe.data, ordered_events__deliver_event, &trace);
		ordered_events__set_copy_on_queue(&trace.oe.data, true);
	पूर्ण

	/*
	 * If we are augmenting syscalls, then combine what we put in the
	 * __augmented_syscalls__ BPF map with what is in the
	 * syscalls:sys_निकास_FOO tracepoपूर्णांकs, i.e. just like we करो without BPF,
	 * combining raw_syscalls:sys_enter with raw_syscalls:sys_निकास.
	 *
	 * We'll चयन to look at two BPF maps, one क्रम sys_enter and the
	 * other क्रम sys_निकास when we start augmenting the sys_निकास paths with
	 * buffers that are being copied from kernel to userspace, think 'read'
	 * syscall.
	 */
	अगर (trace.syscalls.events.augmented) अणु
		evlist__क्रम_each_entry(trace.evlist, evsel) अणु
			bool raw_syscalls_sys_निकास = म_भेद(evsel__name(evsel), "raw_syscalls:sys_exit") == 0;

			अगर (raw_syscalls_sys_निकास) अणु
				trace.raw_augmented_syscalls = true;
				जाओ init_augmented_syscall_tp;
			पूर्ण

			अगर (trace.syscalls.events.augmented->priv == शून्य &&
			    म_माला(evsel__name(evsel), "syscalls:sys_enter")) अणु
				काष्ठा evsel *augmented = trace.syscalls.events.augmented;
				अगर (evsel__init_augmented_syscall_tp(augmented, evsel) ||
				    evsel__init_augmented_syscall_tp_args(augmented))
					जाओ out;
				/*
				 * Augmented is __augmented_syscalls__ BPF_OUTPUT event
				 * Above we made sure we can get from the payload the tp fields
				 * that we get from syscalls:sys_enter tracefs क्रमmat file.
				 */
				augmented->handler = trace__sys_enter;
				/*
				 * Now we करो the same क्रम the *syscalls:sys_enter event so that
				 * अगर we handle it directly, i.e. अगर the BPF prog वापसs 0 so
				 * as not to filter it, then we'll handle it just like we would
				 * क्रम the BPF_OUTPUT one:
				 */
				अगर (evsel__init_augmented_syscall_tp(evsel, evsel) ||
				    evsel__init_augmented_syscall_tp_args(evsel))
					जाओ out;
				evsel->handler = trace__sys_enter;
			पूर्ण

			अगर (strstarts(evsel__name(evsel), "syscalls:sys_exit_")) अणु
				काष्ठा syscall_tp *sc;
init_augmented_syscall_tp:
				अगर (evsel__init_augmented_syscall_tp(evsel, evsel))
					जाओ out;
				sc = __evsel__syscall_tp(evsel);
				/*
				 * For now with BPF raw_augmented we hook पूर्णांकo
				 * raw_syscalls:sys_enter and there we get all
				 * 6 syscall args plus the tracepoपूर्णांक common
				 * fields and the syscall_nr (another दीर्घ).
				 * So we check अगर that is the हाल and अगर so
				 * करोn't look after the sc->args_size but
				 * always after the full raw_syscalls:sys_enter
				 * payload, which is fixed.
				 *
				 * We'll revisit this later to pass
				 * s->args_size to the BPF augmenter (now
				 * tools/perf/examples/bpf/augmented_raw_syscalls.c,
				 * so that it copies only what we need क्रम each
				 * syscall, like what happens when we use
				 * syscalls:sys_enter_NAME, so that we reduce
				 * the kernel/userspace traffic to just what is
				 * needed क्रम each syscall.
				 */
				अगर (trace.raw_augmented_syscalls)
					trace.raw_augmented_syscalls_args_size = (6 + 1) * माप(दीर्घ) + sc->id.offset;
				evsel__init_augmented_syscall_tp_ret(evsel);
				evsel->handler = trace__sys_निकास;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((argc >= 1) && (म_भेद(argv[0], "record") == 0))
		वापस trace__record(&trace, argc-1, &argv[1]);

	/* Using just --त्रुटि_सं-summary will trigger --summary */
	अगर (trace.त्रुटि_सं_summary && !trace.summary && !trace.summary_only)
		trace.summary_only = true;

	/* summary_only implies summary option, but करोn't overग_लिखो summary अगर set */
	अगर (trace.summary_only)
		trace.summary = trace.summary_only;

	अगर (output_name != शून्य) अणु
		err = trace__खोलो_output(&trace, output_name);
		अगर (err < 0) अणु
			लिखो_त्रुटि("failed to create output file");
			जाओ out;
		पूर्ण
	पूर्ण

	err = evचयन__init(&trace.evचयन, trace.evlist, मानक_त्रुटि);
	अगर (err)
		जाओ out_बंद;

	err = target__validate(&trace.opts.target);
	अगर (err) अणु
		target__म_त्रुटि(&trace.opts.target, err, bf, माप(bf));
		ख_लिखो(trace.output, "%s", bf);
		जाओ out_बंद;
	पूर्ण

	err = target__parse_uid(&trace.opts.target);
	अगर (err) अणु
		target__म_त्रुटि(&trace.opts.target, err, bf, माप(bf));
		ख_लिखो(trace.output, "%s", bf);
		जाओ out_बंद;
	पूर्ण

	अगर (!argc && target__none(&trace.opts.target))
		trace.opts.target.प्रणाली_wide = true;

	अगर (input_name)
		err = trace__replay(&trace);
	अन्यथा
		err = trace__run(&trace, argc, argv);

out_बंद:
	अगर (output_name != शून्य)
		ख_बंद(trace.output);
out:
	zमुक्त(&trace.perfconfig_events);
	वापस err;
पूर्ण
