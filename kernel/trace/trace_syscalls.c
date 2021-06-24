<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <trace/syscall.h>
#समावेश <trace/events/syscalls.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>	/* क्रम MODULE_NAME_LEN via KSYM_SYMBOL_LEN */
#समावेश <linux/ftrace.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/xarray.h>
#समावेश <यंत्र/syscall.h>

#समावेश "trace_output.h"
#समावेश "trace.h"

अटल DEFINE_MUTEX(syscall_trace_lock);

अटल पूर्णांक syscall_enter_रेजिस्टर(काष्ठा trace_event_call *event,
				 क्रमागत trace_reg type, व्योम *data);
अटल पूर्णांक syscall_निकास_रेजिस्टर(काष्ठा trace_event_call *event,
				 क्रमागत trace_reg type, व्योम *data);

अटल काष्ठा list_head *
syscall_get_enter_fields(काष्ठा trace_event_call *call)
अणु
	काष्ठा syscall_metadata *entry = call->data;

	वापस &entry->enter_fields;
पूर्ण

बाह्य काष्ठा syscall_metadata *__start_syscalls_metadata[];
बाह्य काष्ठा syscall_metadata *__stop_syscalls_metadata[];

अटल DEFINE_XARRAY(syscalls_metadata_sparse);
अटल काष्ठा syscall_metadata **syscalls_metadata;

#अगर_अघोषित ARCH_HAS_SYSCALL_MATCH_SYM_NAME
अटल अंतरभूत bool arch_syscall_match_sym_name(स्थिर अक्षर *sym, स्थिर अक्षर *name)
अणु
	/*
	 * Only compare after the "sys" prefix. Archs that use
	 * syscall wrappers may have syscalls symbols aliases prefixed
	 * with ".SyS" or ".sys" instead of "sys", leading to an unwanted
	 * mismatch.
	 */
	वापस !म_भेद(sym + 3, name + 3);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित ARCH_TRACE_IGNORE_COMPAT_SYSCALLS
/*
 * Some architectures that allow क्रम 32bit applications
 * to run on a 64bit kernel, करो not map the syscalls क्रम
 * the 32bit tasks the same as they करो क्रम 64bit tasks.
 *
 *     *cough*x86*cough*
 *
 * In such a हाल, instead of reporting the wrong syscalls,
 * simply ignore them.
 *
 * For an arch to ignore the compat syscalls it needs to
 * define ARCH_TRACE_IGNORE_COMPAT_SYSCALLS as well as
 * define the function arch_trace_is_compat_syscall() to let
 * the tracing प्रणाली know that it should ignore it.
 */
अटल पूर्णांक
trace_get_syscall_nr(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	अगर (unlikely(arch_trace_is_compat_syscall(regs)))
		वापस -1;

	वापस syscall_get_nr(task, regs);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक
trace_get_syscall_nr(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	वापस syscall_get_nr(task, regs);
पूर्ण
#पूर्ण_अगर /* ARCH_TRACE_IGNORE_COMPAT_SYSCALLS */

अटल __init काष्ठा syscall_metadata *
find_syscall_meta(अचिन्हित दीर्घ syscall)
अणु
	काष्ठा syscall_metadata **start;
	काष्ठा syscall_metadata **stop;
	अक्षर str[KSYM_SYMBOL_LEN];


	start = __start_syscalls_metadata;
	stop = __stop_syscalls_metadata;
	kallsyms_lookup(syscall, शून्य, शून्य, शून्य, str);

	अगर (arch_syscall_match_sym_name(str, "sys_ni_syscall"))
		वापस शून्य;

	क्रम ( ; start < stop; start++) अणु
		अगर ((*start)->name && arch_syscall_match_sym_name(str, (*start)->name))
			वापस *start;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा syscall_metadata *syscall_nr_to_meta(पूर्णांक nr)
अणु
	अगर (IS_ENABLED(CONFIG_HAVE_SPARSE_SYSCALL_NR))
		वापस xa_load(&syscalls_metadata_sparse, (अचिन्हित दीर्घ)nr);

	अगर (!syscalls_metadata || nr >= NR_syscalls || nr < 0)
		वापस शून्य;

	वापस syscalls_metadata[nr];
पूर्ण

स्थिर अक्षर *get_syscall_name(पूर्णांक syscall)
अणु
	काष्ठा syscall_metadata *entry;

	entry = syscall_nr_to_meta(syscall);
	अगर (!entry)
		वापस शून्य;

	वापस entry->name;
पूर्ण

अटल क्रमागत prपूर्णांक_line_t
prपूर्णांक_syscall_enter(काष्ठा trace_iterator *iter, पूर्णांक flags,
		    काष्ठा trace_event *event)
अणु
	काष्ठा trace_array *tr = iter->tr;
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा trace_entry *ent = iter->ent;
	काष्ठा syscall_trace_enter *trace;
	काष्ठा syscall_metadata *entry;
	पूर्णांक i, syscall;

	trace = (typeof(trace))ent;
	syscall = trace->nr;
	entry = syscall_nr_to_meta(syscall);

	अगर (!entry)
		जाओ end;

	अगर (entry->enter_event->event.type != ent->type) अणु
		WARN_ON_ONCE(1);
		जाओ end;
	पूर्ण

	trace_seq_म_लिखो(s, "%s(", entry->name);

	क्रम (i = 0; i < entry->nb_args; i++) अणु

		अगर (trace_seq_has_overflowed(s))
			जाओ end;

		/* parameter types */
		अगर (tr->trace_flags & TRACE_ITER_VERBOSE)
			trace_seq_म_लिखो(s, "%s ", entry->types[i]);

		/* parameter values */
		trace_seq_म_लिखो(s, "%s: %lx%s", entry->args[i],
				 trace->args[i],
				 i == entry->nb_args - 1 ? "" : ", ");
	पूर्ण

	trace_seq_अ_दो(s, ')');
end:
	trace_seq_अ_दो(s, '\n');

	वापस trace_handle_वापस(s);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t
prपूर्णांक_syscall_निकास(काष्ठा trace_iterator *iter, पूर्णांक flags,
		   काष्ठा trace_event *event)
अणु
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा trace_entry *ent = iter->ent;
	काष्ठा syscall_trace_निकास *trace;
	पूर्णांक syscall;
	काष्ठा syscall_metadata *entry;

	trace = (typeof(trace))ent;
	syscall = trace->nr;
	entry = syscall_nr_to_meta(syscall);

	अगर (!entry) अणु
		trace_seq_अ_दो(s, '\n');
		जाओ out;
	पूर्ण

	अगर (entry->निकास_event->event.type != ent->type) अणु
		WARN_ON_ONCE(1);
		वापस TRACE_TYPE_UNHANDLED;
	पूर्ण

	trace_seq_म_लिखो(s, "%s -> 0x%lx\n", entry->name,
				trace->ret);

 out:
	वापस trace_handle_वापस(s);
पूर्ण

बाह्य अक्षर *__bad_type_size(व्योम);

#घोषणा SYSCALL_FIELD(_type, _name) अणु					\
	.type = #_type, .name = #_name,					\
	.size = माप(_type), .align = __alignof__(_type),		\
	.is_चिन्हित = is_चिन्हित_type(_type), .filter_type = FILTER_OTHER पूर्ण

अटल पूर्णांक __init
__set_enter_prपूर्णांक_fmt(काष्ठा syscall_metadata *entry, अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक i;
	पूर्णांक pos = 0;

	/* When len=0, we just calculate the needed length */
#घोषणा LEN_OR_ZERO (len ? len - pos : 0)

	pos += snम_लिखो(buf + pos, LEN_OR_ZERO, "\"");
	क्रम (i = 0; i < entry->nb_args; i++) अणु
		pos += snम_लिखो(buf + pos, LEN_OR_ZERO, "%s: 0x%%0%zulx%s",
				entry->args[i], माप(अचिन्हित दीर्घ),
				i == entry->nb_args - 1 ? "" : ", ");
	पूर्ण
	pos += snम_लिखो(buf + pos, LEN_OR_ZERO, "\"");

	क्रम (i = 0; i < entry->nb_args; i++) अणु
		pos += snम_लिखो(buf + pos, LEN_OR_ZERO,
				", ((unsigned long)(REC->%s))", entry->args[i]);
	पूर्ण

#अघोषित LEN_OR_ZERO

	/* वापस the length of prपूर्णांक_fmt */
	वापस pos;
पूर्ण

अटल पूर्णांक __init set_syscall_prपूर्णांक_fmt(काष्ठा trace_event_call *call)
अणु
	अक्षर *prपूर्णांक_fmt;
	पूर्णांक len;
	काष्ठा syscall_metadata *entry = call->data;

	अगर (entry->enter_event != call) अणु
		call->prपूर्णांक_fmt = "\"0x%lx\", REC->ret";
		वापस 0;
	पूर्ण

	/* First: called with 0 length to calculate the needed length */
	len = __set_enter_prपूर्णांक_fmt(entry, शून्य, 0);

	prपूर्णांक_fmt = kदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (!prपूर्णांक_fmt)
		वापस -ENOMEM;

	/* Second: actually ग_लिखो the @prपूर्णांक_fmt */
	__set_enter_prपूर्णांक_fmt(entry, prपूर्णांक_fmt, len + 1);
	call->prपूर्णांक_fmt = prपूर्णांक_fmt;

	वापस 0;
पूर्ण

अटल व्योम __init मुक्त_syscall_prपूर्णांक_fmt(काष्ठा trace_event_call *call)
अणु
	काष्ठा syscall_metadata *entry = call->data;

	अगर (entry->enter_event == call)
		kमुक्त(call->prपूर्णांक_fmt);
पूर्ण

अटल पूर्णांक __init syscall_enter_define_fields(काष्ठा trace_event_call *call)
अणु
	काष्ठा syscall_trace_enter trace;
	काष्ठा syscall_metadata *meta = call->data;
	पूर्णांक offset = दुरत्व(typeof(trace), args);
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < meta->nb_args; i++) अणु
		ret = trace_define_field(call, meta->types[i],
					 meta->args[i], offset,
					 माप(अचिन्हित दीर्घ), 0,
					 FILTER_OTHER);
		अगर (ret)
			अवरोध;
		offset += माप(अचिन्हित दीर्घ);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ftrace_syscall_enter(व्योम *data, काष्ठा pt_regs *regs, दीर्घ id)
अणु
	काष्ठा trace_array *tr = data;
	काष्ठा trace_event_file *trace_file;
	काष्ठा syscall_trace_enter *entry;
	काष्ठा syscall_metadata *sys_data;
	काष्ठा ring_buffer_event *event;
	काष्ठा trace_buffer *buffer;
	अचिन्हित पूर्णांक trace_ctx;
	अचिन्हित दीर्घ args[6];
	पूर्णांक syscall_nr;
	पूर्णांक size;

	syscall_nr = trace_get_syscall_nr(current, regs);
	अगर (syscall_nr < 0 || syscall_nr >= NR_syscalls)
		वापस;

	/* Here we're inside tp handler's rcu_पढ़ो_lock_sched (__DO_TRACE) */
	trace_file = rcu_dereference_sched(tr->enter_syscall_files[syscall_nr]);
	अगर (!trace_file)
		वापस;

	अगर (trace_trigger_soft_disabled(trace_file))
		वापस;

	sys_data = syscall_nr_to_meta(syscall_nr);
	अगर (!sys_data)
		वापस;

	size = माप(*entry) + माप(अचिन्हित दीर्घ) * sys_data->nb_args;

	trace_ctx = tracing_gen_ctx();

	buffer = tr->array_buffer.buffer;
	event = trace_buffer_lock_reserve(buffer,
			sys_data->enter_event->event.type, size, trace_ctx);
	अगर (!event)
		वापस;

	entry = ring_buffer_event_data(event);
	entry->nr = syscall_nr;
	syscall_get_arguments(current, regs, args);
	स_नकल(entry->args, args, माप(अचिन्हित दीर्घ) * sys_data->nb_args);

	event_trigger_unlock_commit(trace_file, buffer, event, entry,
				    trace_ctx);
पूर्ण

अटल व्योम ftrace_syscall_निकास(व्योम *data, काष्ठा pt_regs *regs, दीर्घ ret)
अणु
	काष्ठा trace_array *tr = data;
	काष्ठा trace_event_file *trace_file;
	काष्ठा syscall_trace_निकास *entry;
	काष्ठा syscall_metadata *sys_data;
	काष्ठा ring_buffer_event *event;
	काष्ठा trace_buffer *buffer;
	अचिन्हित पूर्णांक trace_ctx;
	पूर्णांक syscall_nr;

	syscall_nr = trace_get_syscall_nr(current, regs);
	अगर (syscall_nr < 0 || syscall_nr >= NR_syscalls)
		वापस;

	/* Here we're inside tp handler's rcu_पढ़ो_lock_sched (__DO_TRACE()) */
	trace_file = rcu_dereference_sched(tr->निकास_syscall_files[syscall_nr]);
	अगर (!trace_file)
		वापस;

	अगर (trace_trigger_soft_disabled(trace_file))
		वापस;

	sys_data = syscall_nr_to_meta(syscall_nr);
	अगर (!sys_data)
		वापस;

	trace_ctx = tracing_gen_ctx();

	buffer = tr->array_buffer.buffer;
	event = trace_buffer_lock_reserve(buffer,
			sys_data->निकास_event->event.type, माप(*entry),
			trace_ctx);
	अगर (!event)
		वापस;

	entry = ring_buffer_event_data(event);
	entry->nr = syscall_nr;
	entry->ret = syscall_get_वापस_value(current, regs);

	event_trigger_unlock_commit(trace_file, buffer, event, entry,
				    trace_ctx);
पूर्ण

अटल पूर्णांक reg_event_syscall_enter(काष्ठा trace_event_file *file,
				   काष्ठा trace_event_call *call)
अणु
	काष्ठा trace_array *tr = file->tr;
	पूर्णांक ret = 0;
	पूर्णांक num;

	num = ((काष्ठा syscall_metadata *)call->data)->syscall_nr;
	अगर (WARN_ON_ONCE(num < 0 || num >= NR_syscalls))
		वापस -ENOSYS;
	mutex_lock(&syscall_trace_lock);
	अगर (!tr->sys_refcount_enter)
		ret = रेजिस्टर_trace_sys_enter(ftrace_syscall_enter, tr);
	अगर (!ret) अणु
		rcu_assign_poपूर्णांकer(tr->enter_syscall_files[num], file);
		tr->sys_refcount_enter++;
	पूर्ण
	mutex_unlock(&syscall_trace_lock);
	वापस ret;
पूर्ण

अटल व्योम unreg_event_syscall_enter(काष्ठा trace_event_file *file,
				      काष्ठा trace_event_call *call)
अणु
	काष्ठा trace_array *tr = file->tr;
	पूर्णांक num;

	num = ((काष्ठा syscall_metadata *)call->data)->syscall_nr;
	अगर (WARN_ON_ONCE(num < 0 || num >= NR_syscalls))
		वापस;
	mutex_lock(&syscall_trace_lock);
	tr->sys_refcount_enter--;
	RCU_INIT_POINTER(tr->enter_syscall_files[num], शून्य);
	अगर (!tr->sys_refcount_enter)
		unरेजिस्टर_trace_sys_enter(ftrace_syscall_enter, tr);
	mutex_unlock(&syscall_trace_lock);
पूर्ण

अटल पूर्णांक reg_event_syscall_निकास(काष्ठा trace_event_file *file,
				  काष्ठा trace_event_call *call)
अणु
	काष्ठा trace_array *tr = file->tr;
	पूर्णांक ret = 0;
	पूर्णांक num;

	num = ((काष्ठा syscall_metadata *)call->data)->syscall_nr;
	अगर (WARN_ON_ONCE(num < 0 || num >= NR_syscalls))
		वापस -ENOSYS;
	mutex_lock(&syscall_trace_lock);
	अगर (!tr->sys_refcount_निकास)
		ret = रेजिस्टर_trace_sys_निकास(ftrace_syscall_निकास, tr);
	अगर (!ret) अणु
		rcu_assign_poपूर्णांकer(tr->निकास_syscall_files[num], file);
		tr->sys_refcount_निकास++;
	पूर्ण
	mutex_unlock(&syscall_trace_lock);
	वापस ret;
पूर्ण

अटल व्योम unreg_event_syscall_निकास(काष्ठा trace_event_file *file,
				     काष्ठा trace_event_call *call)
अणु
	काष्ठा trace_array *tr = file->tr;
	पूर्णांक num;

	num = ((काष्ठा syscall_metadata *)call->data)->syscall_nr;
	अगर (WARN_ON_ONCE(num < 0 || num >= NR_syscalls))
		वापस;
	mutex_lock(&syscall_trace_lock);
	tr->sys_refcount_निकास--;
	RCU_INIT_POINTER(tr->निकास_syscall_files[num], शून्य);
	अगर (!tr->sys_refcount_निकास)
		unरेजिस्टर_trace_sys_निकास(ftrace_syscall_निकास, tr);
	mutex_unlock(&syscall_trace_lock);
पूर्ण

अटल पूर्णांक __init init_syscall_trace(काष्ठा trace_event_call *call)
अणु
	पूर्णांक id;
	पूर्णांक num;

	num = ((काष्ठा syscall_metadata *)call->data)->syscall_nr;
	अगर (num < 0 || num >= NR_syscalls) अणु
		pr_debug("syscall %s metadata not mapped, disabling ftrace event\n",
				((काष्ठा syscall_metadata *)call->data)->name);
		वापस -ENOSYS;
	पूर्ण

	अगर (set_syscall_prपूर्णांक_fmt(call) < 0)
		वापस -ENOMEM;

	id = trace_event_raw_init(call);

	अगर (id < 0) अणु
		मुक्त_syscall_prपूर्णांक_fmt(call);
		वापस id;
	पूर्ण

	वापस id;
पूर्ण

अटल काष्ठा trace_event_fields __refdata syscall_enter_fields_array[] = अणु
	SYSCALL_FIELD(पूर्णांक, __syscall_nr),
	अणु .type = TRACE_FUNCTION_TYPE,
	  .define_fields = syscall_enter_define_fields पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा trace_event_functions enter_syscall_prपूर्णांक_funcs = अणु
	.trace		= prपूर्णांक_syscall_enter,
पूर्ण;

काष्ठा trace_event_functions निकास_syscall_prपूर्णांक_funcs = अणु
	.trace		= prपूर्णांक_syscall_निकास,
पूर्ण;

काष्ठा trace_event_class __refdata event_class_syscall_enter = अणु
	.प्रणाली		= "syscalls",
	.reg		= syscall_enter_रेजिस्टर,
	.fields_array	= syscall_enter_fields_array,
	.get_fields	= syscall_get_enter_fields,
	.raw_init	= init_syscall_trace,
पूर्ण;

काष्ठा trace_event_class __refdata event_class_syscall_निकास = अणु
	.प्रणाली		= "syscalls",
	.reg		= syscall_निकास_रेजिस्टर,
	.fields_array	= (काष्ठा trace_event_fields[])अणु
		SYSCALL_FIELD(पूर्णांक, __syscall_nr),
		SYSCALL_FIELD(दीर्घ, ret),
		अणुपूर्ण
	पूर्ण,
	.fields		= LIST_HEAD_INIT(event_class_syscall_निकास.fields),
	.raw_init	= init_syscall_trace,
पूर्ण;

अचिन्हित दीर्घ __init __weak arch_syscall_addr(पूर्णांक nr)
अणु
	वापस (अचिन्हित दीर्घ)sys_call_table[nr];
पूर्ण

व्योम __init init_ftrace_syscalls(व्योम)
अणु
	काष्ठा syscall_metadata *meta;
	अचिन्हित दीर्घ addr;
	पूर्णांक i;
	व्योम *ret;

	अगर (!IS_ENABLED(CONFIG_HAVE_SPARSE_SYSCALL_NR)) अणु
		syscalls_metadata = kसुस्मृति(NR_syscalls,
					माप(*syscalls_metadata),
					GFP_KERNEL);
		अगर (!syscalls_metadata) अणु
			WARN_ON(1);
			वापस;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < NR_syscalls; i++) अणु
		addr = arch_syscall_addr(i);
		meta = find_syscall_meta(addr);
		अगर (!meta)
			जारी;

		meta->syscall_nr = i;

		अगर (!IS_ENABLED(CONFIG_HAVE_SPARSE_SYSCALL_NR)) अणु
			syscalls_metadata[i] = meta;
		पूर्ण अन्यथा अणु
			ret = xa_store(&syscalls_metadata_sparse, i, meta,
					GFP_KERNEL);
			WARN(xa_is_err(ret),
				"Syscall memory allocation failed\n");
		पूर्ण

	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PERF_EVENTS

अटल DECLARE_BITMAP(enabled_perf_enter_syscalls, NR_syscalls);
अटल DECLARE_BITMAP(enabled_perf_निकास_syscalls, NR_syscalls);
अटल पूर्णांक sys_perf_refcount_enter;
अटल पूर्णांक sys_perf_refcount_निकास;

अटल पूर्णांक perf_call_bpf_enter(काष्ठा trace_event_call *call, काष्ठा pt_regs *regs,
			       काष्ठा syscall_metadata *sys_data,
			       काष्ठा syscall_trace_enter *rec)
अणु
	काष्ठा syscall_tp_t अणु
		अचिन्हित दीर्घ दीर्घ regs;
		अचिन्हित दीर्घ syscall_nr;
		अचिन्हित दीर्घ args[SYSCALL_DEFINE_MAXARGS];
	पूर्ण param;
	पूर्णांक i;

	*(काष्ठा pt_regs **)&param = regs;
	param.syscall_nr = rec->nr;
	क्रम (i = 0; i < sys_data->nb_args; i++)
		param.args[i] = rec->args[i];
	वापस trace_call_bpf(call, &param);
पूर्ण

अटल व्योम perf_syscall_enter(व्योम *ignore, काष्ठा pt_regs *regs, दीर्घ id)
अणु
	काष्ठा syscall_metadata *sys_data;
	काष्ठा syscall_trace_enter *rec;
	काष्ठा hlist_head *head;
	अचिन्हित दीर्घ args[6];
	bool valid_prog_array;
	पूर्णांक syscall_nr;
	पूर्णांक rctx;
	पूर्णांक size;

	syscall_nr = trace_get_syscall_nr(current, regs);
	अगर (syscall_nr < 0 || syscall_nr >= NR_syscalls)
		वापस;
	अगर (!test_bit(syscall_nr, enabled_perf_enter_syscalls))
		वापस;

	sys_data = syscall_nr_to_meta(syscall_nr);
	अगर (!sys_data)
		वापस;

	head = this_cpu_ptr(sys_data->enter_event->perf_events);
	valid_prog_array = bpf_prog_array_valid(sys_data->enter_event);
	अगर (!valid_prog_array && hlist_empty(head))
		वापस;

	/* get the size after alignment with the u32 buffer size field */
	size = माप(अचिन्हित दीर्घ) * sys_data->nb_args + माप(*rec);
	size = ALIGN(size + माप(u32), माप(u64));
	size -= माप(u32);

	rec = perf_trace_buf_alloc(size, शून्य, &rctx);
	अगर (!rec)
		वापस;

	rec->nr = syscall_nr;
	syscall_get_arguments(current, regs, args);
	स_नकल(&rec->args, args, माप(अचिन्हित दीर्घ) * sys_data->nb_args);

	अगर ((valid_prog_array &&
	     !perf_call_bpf_enter(sys_data->enter_event, regs, sys_data, rec)) ||
	    hlist_empty(head)) अणु
		perf_swevent_put_recursion_context(rctx);
		वापस;
	पूर्ण

	perf_trace_buf_submit(rec, size, rctx,
			      sys_data->enter_event->event.type, 1, regs,
			      head, शून्य);
पूर्ण

अटल पूर्णांक perf_sysenter_enable(काष्ठा trace_event_call *call)
अणु
	पूर्णांक ret = 0;
	पूर्णांक num;

	num = ((काष्ठा syscall_metadata *)call->data)->syscall_nr;

	mutex_lock(&syscall_trace_lock);
	अगर (!sys_perf_refcount_enter)
		ret = रेजिस्टर_trace_sys_enter(perf_syscall_enter, शून्य);
	अगर (ret) अणु
		pr_info("event trace: Could not activate syscall entry trace point");
	पूर्ण अन्यथा अणु
		set_bit(num, enabled_perf_enter_syscalls);
		sys_perf_refcount_enter++;
	पूर्ण
	mutex_unlock(&syscall_trace_lock);
	वापस ret;
पूर्ण

अटल व्योम perf_sysenter_disable(काष्ठा trace_event_call *call)
अणु
	पूर्णांक num;

	num = ((काष्ठा syscall_metadata *)call->data)->syscall_nr;

	mutex_lock(&syscall_trace_lock);
	sys_perf_refcount_enter--;
	clear_bit(num, enabled_perf_enter_syscalls);
	अगर (!sys_perf_refcount_enter)
		unरेजिस्टर_trace_sys_enter(perf_syscall_enter, शून्य);
	mutex_unlock(&syscall_trace_lock);
पूर्ण

अटल पूर्णांक perf_call_bpf_निकास(काष्ठा trace_event_call *call, काष्ठा pt_regs *regs,
			      काष्ठा syscall_trace_निकास *rec)
अणु
	काष्ठा syscall_tp_t अणु
		अचिन्हित दीर्घ दीर्घ regs;
		अचिन्हित दीर्घ syscall_nr;
		अचिन्हित दीर्घ ret;
	पूर्ण param;

	*(काष्ठा pt_regs **)&param = regs;
	param.syscall_nr = rec->nr;
	param.ret = rec->ret;
	वापस trace_call_bpf(call, &param);
पूर्ण

अटल व्योम perf_syscall_निकास(व्योम *ignore, काष्ठा pt_regs *regs, दीर्घ ret)
अणु
	काष्ठा syscall_metadata *sys_data;
	काष्ठा syscall_trace_निकास *rec;
	काष्ठा hlist_head *head;
	bool valid_prog_array;
	पूर्णांक syscall_nr;
	पूर्णांक rctx;
	पूर्णांक size;

	syscall_nr = trace_get_syscall_nr(current, regs);
	अगर (syscall_nr < 0 || syscall_nr >= NR_syscalls)
		वापस;
	अगर (!test_bit(syscall_nr, enabled_perf_निकास_syscalls))
		वापस;

	sys_data = syscall_nr_to_meta(syscall_nr);
	अगर (!sys_data)
		वापस;

	head = this_cpu_ptr(sys_data->निकास_event->perf_events);
	valid_prog_array = bpf_prog_array_valid(sys_data->निकास_event);
	अगर (!valid_prog_array && hlist_empty(head))
		वापस;

	/* We can probably करो that at build समय */
	size = ALIGN(माप(*rec) + माप(u32), माप(u64));
	size -= माप(u32);

	rec = perf_trace_buf_alloc(size, शून्य, &rctx);
	अगर (!rec)
		वापस;

	rec->nr = syscall_nr;
	rec->ret = syscall_get_वापस_value(current, regs);

	अगर ((valid_prog_array &&
	     !perf_call_bpf_निकास(sys_data->निकास_event, regs, rec)) ||
	    hlist_empty(head)) अणु
		perf_swevent_put_recursion_context(rctx);
		वापस;
	पूर्ण

	perf_trace_buf_submit(rec, size, rctx, sys_data->निकास_event->event.type,
			      1, regs, head, शून्य);
पूर्ण

अटल पूर्णांक perf_sysनिकास_enable(काष्ठा trace_event_call *call)
अणु
	पूर्णांक ret = 0;
	पूर्णांक num;

	num = ((काष्ठा syscall_metadata *)call->data)->syscall_nr;

	mutex_lock(&syscall_trace_lock);
	अगर (!sys_perf_refcount_निकास)
		ret = रेजिस्टर_trace_sys_निकास(perf_syscall_निकास, शून्य);
	अगर (ret) अणु
		pr_info("event trace: Could not activate syscall exit trace point");
	पूर्ण अन्यथा अणु
		set_bit(num, enabled_perf_निकास_syscalls);
		sys_perf_refcount_निकास++;
	पूर्ण
	mutex_unlock(&syscall_trace_lock);
	वापस ret;
पूर्ण

अटल व्योम perf_sysनिकास_disable(काष्ठा trace_event_call *call)
अणु
	पूर्णांक num;

	num = ((काष्ठा syscall_metadata *)call->data)->syscall_nr;

	mutex_lock(&syscall_trace_lock);
	sys_perf_refcount_निकास--;
	clear_bit(num, enabled_perf_निकास_syscalls);
	अगर (!sys_perf_refcount_निकास)
		unरेजिस्टर_trace_sys_निकास(perf_syscall_निकास, शून्य);
	mutex_unlock(&syscall_trace_lock);
पूर्ण

#पूर्ण_अगर /* CONFIG_PERF_EVENTS */

अटल पूर्णांक syscall_enter_रेजिस्टर(काष्ठा trace_event_call *event,
				 क्रमागत trace_reg type, व्योम *data)
अणु
	काष्ठा trace_event_file *file = data;

	चयन (type) अणु
	हाल TRACE_REG_REGISTER:
		वापस reg_event_syscall_enter(file, event);
	हाल TRACE_REG_UNREGISTER:
		unreg_event_syscall_enter(file, event);
		वापस 0;

#अगर_घोषित CONFIG_PERF_EVENTS
	हाल TRACE_REG_PERF_REGISTER:
		वापस perf_sysenter_enable(event);
	हाल TRACE_REG_PERF_UNREGISTER:
		perf_sysenter_disable(event);
		वापस 0;
	हाल TRACE_REG_PERF_OPEN:
	हाल TRACE_REG_PERF_CLOSE:
	हाल TRACE_REG_PERF_ADD:
	हाल TRACE_REG_PERF_DEL:
		वापस 0;
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक syscall_निकास_रेजिस्टर(काष्ठा trace_event_call *event,
				 क्रमागत trace_reg type, व्योम *data)
अणु
	काष्ठा trace_event_file *file = data;

	चयन (type) अणु
	हाल TRACE_REG_REGISTER:
		वापस reg_event_syscall_निकास(file, event);
	हाल TRACE_REG_UNREGISTER:
		unreg_event_syscall_निकास(file, event);
		वापस 0;

#अगर_घोषित CONFIG_PERF_EVENTS
	हाल TRACE_REG_PERF_REGISTER:
		वापस perf_sysनिकास_enable(event);
	हाल TRACE_REG_PERF_UNREGISTER:
		perf_sysनिकास_disable(event);
		वापस 0;
	हाल TRACE_REG_PERF_OPEN:
	हाल TRACE_REG_PERF_CLOSE:
	हाल TRACE_REG_PERF_ADD:
	हाल TRACE_REG_PERF_DEL:
		वापस 0;
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण
