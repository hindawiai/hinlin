<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _LINUX_TRACE_EVENT_H
#घोषणा _LINUX_TRACE_EVENT_H

#समावेश <linux/ring_buffer.h>
#समावेश <linux/trace_seq.h>
#समावेश <linux/percpu.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा trace_array;
काष्ठा array_buffer;
काष्ठा tracer;
काष्ठा dentry;
काष्ठा bpf_prog;

स्थिर अक्षर *trace_prपूर्णांक_flags_seq(काष्ठा trace_seq *p, स्थिर अक्षर *delim,
				  अचिन्हित दीर्घ flags,
				  स्थिर काष्ठा trace_prपूर्णांक_flags *flag_array);

स्थिर अक्षर *trace_prपूर्णांक_symbols_seq(काष्ठा trace_seq *p, अचिन्हित दीर्घ val,
				    स्थिर काष्ठा trace_prपूर्णांक_flags *symbol_array);

#अगर BITS_PER_LONG == 32
स्थिर अक्षर *trace_prपूर्णांक_flags_seq_u64(काष्ठा trace_seq *p, स्थिर अक्षर *delim,
		      अचिन्हित दीर्घ दीर्घ flags,
		      स्थिर काष्ठा trace_prपूर्णांक_flags_u64 *flag_array);

स्थिर अक्षर *trace_prपूर्णांक_symbols_seq_u64(काष्ठा trace_seq *p,
					अचिन्हित दीर्घ दीर्घ val,
					स्थिर काष्ठा trace_prपूर्णांक_flags_u64
								 *symbol_array);
#पूर्ण_अगर

स्थिर अक्षर *trace_prपूर्णांक_biपंचांगask_seq(काष्ठा trace_seq *p, व्योम *biपंचांगask_ptr,
				    अचिन्हित पूर्णांक biपंचांगask_size);

स्थिर अक्षर *trace_prपूर्णांक_hex_seq(काष्ठा trace_seq *p,
				स्थिर अचिन्हित अक्षर *buf, पूर्णांक len,
				bool concatenate);

स्थिर अक्षर *trace_prपूर्णांक_array_seq(काष्ठा trace_seq *p,
				   स्थिर व्योम *buf, पूर्णांक count,
				   माप_प्रकार el_size);

स्थिर अक्षर *
trace_prपूर्णांक_hex_dump_seq(काष्ठा trace_seq *p, स्थिर अक्षर *prefix_str,
			 पूर्णांक prefix_type, पूर्णांक rowsize, पूर्णांक groupsize,
			 स्थिर व्योम *buf, माप_प्रकार len, bool ascii);

काष्ठा trace_iterator;
काष्ठा trace_event;

पूर्णांक trace_raw_output_prep(काष्ठा trace_iterator *iter,
			  काष्ठा trace_event *event);
बाह्य __म_लिखो(2, 3)
व्योम trace_event_म_लिखो(काष्ठा trace_iterator *iter, स्थिर अक्षर *fmt, ...);

/*
 * The trace entry - the most basic unit of tracing. This is what
 * is prपूर्णांकed in the end as a single line in the trace output, such as:
 *
 *     bash-15816 [01]   235.197585: idle_cpu <- irq_enter
 */
काष्ठा trace_entry अणु
	अचिन्हित लघु		type;
	अचिन्हित अक्षर		flags;
	अचिन्हित अक्षर		preempt_count;
	पूर्णांक			pid;
पूर्ण;

#घोषणा TRACE_EVENT_TYPE_MAX						\
	((1 << (माप(((काष्ठा trace_entry *)0)->type) * 8)) - 1)

/*
 * Trace iterator - used by prपूर्णांकout routines who present trace
 * results to users and which routines might sleep, etc:
 */
काष्ठा trace_iterator अणु
	काष्ठा trace_array	*tr;
	काष्ठा tracer		*trace;
	काष्ठा array_buffer	*array_buffer;
	व्योम			*निजी;
	पूर्णांक			cpu_file;
	काष्ठा mutex		mutex;
	काष्ठा ring_buffer_iter	**buffer_iter;
	अचिन्हित दीर्घ		iter_flags;
	व्योम			*temp;	/* temp holder */
	अचिन्हित पूर्णांक		temp_size;
	अक्षर			*fmt;	/* modअगरied क्रमmat holder */
	अचिन्हित पूर्णांक		fmt_size;

	/* trace_seq क्रम __prपूर्णांक_flags() and __prपूर्णांक_symbolic() etc. */
	काष्ठा trace_seq	पंचांगp_seq;

	cpumask_var_t		started;

	/* it's true when current खोलो file is snapshot */
	bool			snapshot;

	/* The below is zeroed out in pipe_पढ़ो */
	काष्ठा trace_seq	seq;
	काष्ठा trace_entry	*ent;
	अचिन्हित दीर्घ		lost_events;
	पूर्णांक			leftover;
	पूर्णांक			ent_size;
	पूर्णांक			cpu;
	u64			ts;

	loff_t			pos;
	दीर्घ			idx;

	/* All new field here will be zeroed out in pipe_पढ़ो */
पूर्ण;

क्रमागत trace_iter_flags अणु
	TRACE_खाता_LAT_FMT	= 1,
	TRACE_खाता_ANNOTATE	= 2,
	TRACE_खाता_TIME_IN_NS	= 4,
पूर्ण;


प्रकार क्रमागत prपूर्णांक_line_t (*trace_prपूर्णांक_func)(काष्ठा trace_iterator *iter,
				      पूर्णांक flags, काष्ठा trace_event *event);

काष्ठा trace_event_functions अणु
	trace_prपूर्णांक_func	trace;
	trace_prपूर्णांक_func	raw;
	trace_prपूर्णांक_func	hex;
	trace_prपूर्णांक_func	binary;
पूर्ण;

काष्ठा trace_event अणु
	काष्ठा hlist_node		node;
	काष्ठा list_head		list;
	पूर्णांक				type;
	काष्ठा trace_event_functions	*funcs;
पूर्ण;

बाह्य पूर्णांक रेजिस्टर_trace_event(काष्ठा trace_event *event);
बाह्य पूर्णांक unरेजिस्टर_trace_event(काष्ठा trace_event *event);

/* Return values क्रम prपूर्णांक_line callback */
क्रमागत prपूर्णांक_line_t अणु
	TRACE_TYPE_PARTIAL_LINE	= 0,	/* Retry after flushing the seq */
	TRACE_TYPE_HANDLED	= 1,
	TRACE_TYPE_UNHANDLED	= 2,	/* Relay to other output functions */
	TRACE_TYPE_NO_CONSUME	= 3	/* Handled but ask to not consume */
पूर्ण;

क्रमागत prपूर्णांक_line_t trace_handle_वापस(काष्ठा trace_seq *s);

अटल अंतरभूत व्योम tracing_generic_entry_update(काष्ठा trace_entry *entry,
						अचिन्हित लघु type,
						अचिन्हित पूर्णांक trace_ctx)
अणु
	entry->preempt_count		= trace_ctx & 0xff;
	entry->pid			= current->pid;
	entry->type			= type;
	entry->flags =			trace_ctx >> 16;
पूर्ण

अचिन्हित पूर्णांक tracing_gen_ctx_irq_test(अचिन्हित पूर्णांक irqs_status);

क्रमागत trace_flag_type अणु
	TRACE_FLAG_IRQS_OFF		= 0x01,
	TRACE_FLAG_IRQS_NOSUPPORT	= 0x02,
	TRACE_FLAG_NEED_RESCHED		= 0x04,
	TRACE_FLAG_HARसूचीQ		= 0x08,
	TRACE_FLAG_SOFTIRQ		= 0x10,
	TRACE_FLAG_PREEMPT_RESCHED	= 0x20,
	TRACE_FLAG_NMI			= 0x40,
पूर्ण;

#अगर_घोषित CONFIG_TRACE_IRQFLAGS_SUPPORT
अटल अंतरभूत अचिन्हित पूर्णांक tracing_gen_ctx_flags(अचिन्हित दीर्घ irqflags)
अणु
	अचिन्हित पूर्णांक irq_status = irqs_disabled_flags(irqflags) ?
		TRACE_FLAG_IRQS_OFF : 0;
	वापस tracing_gen_ctx_irq_test(irq_status);
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक tracing_gen_ctx(व्योम)
अणु
	अचिन्हित दीर्घ irqflags;

	local_save_flags(irqflags);
	वापस tracing_gen_ctx_flags(irqflags);
पूर्ण
#अन्यथा

अटल अंतरभूत अचिन्हित पूर्णांक tracing_gen_ctx_flags(अचिन्हित दीर्घ irqflags)
अणु
	वापस tracing_gen_ctx_irq_test(TRACE_FLAG_IRQS_NOSUPPORT);
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक tracing_gen_ctx(व्योम)
अणु
	वापस tracing_gen_ctx_irq_test(TRACE_FLAG_IRQS_NOSUPPORT);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित पूर्णांक tracing_gen_ctx_dec(व्योम)
अणु
	अचिन्हित पूर्णांक trace_ctx;

	trace_ctx = tracing_gen_ctx();
	/*
	 * Subtract one from the preemption counter अगर preemption is enabled,
	 * see trace_event_buffer_reserve()क्रम details.
	 */
	अगर (IS_ENABLED(CONFIG_PREEMPTION))
		trace_ctx--;
	वापस trace_ctx;
पूर्ण

काष्ठा trace_event_file;

काष्ठा ring_buffer_event *
trace_event_buffer_lock_reserve(काष्ठा trace_buffer **current_buffer,
				काष्ठा trace_event_file *trace_file,
				पूर्णांक type, अचिन्हित दीर्घ len,
				अचिन्हित पूर्णांक trace_ctx);

#घोषणा TRACE_RECORD_CMDLINE	BIT(0)
#घोषणा TRACE_RECORD_TGID	BIT(1)

व्योम tracing_record_taskinfo(काष्ठा task_काष्ठा *task, पूर्णांक flags);
व्योम tracing_record_taskinfo_sched_चयन(काष्ठा task_काष्ठा *prev,
					  काष्ठा task_काष्ठा *next, पूर्णांक flags);

व्योम tracing_record_cmdline(काष्ठा task_काष्ठा *task);
व्योम tracing_record_tgid(काष्ठा task_काष्ठा *task);

पूर्णांक trace_output_call(काष्ठा trace_iterator *iter, अक्षर *name, अक्षर *fmt, ...);

काष्ठा event_filter;

क्रमागत trace_reg अणु
	TRACE_REG_REGISTER,
	TRACE_REG_UNREGISTER,
#अगर_घोषित CONFIG_PERF_EVENTS
	TRACE_REG_PERF_REGISTER,
	TRACE_REG_PERF_UNREGISTER,
	TRACE_REG_PERF_OPEN,
	TRACE_REG_PERF_CLOSE,
	/*
	 * These (ADD/DEL) use a 'boolean' वापस value, where 1 (true) means a
	 * custom action was taken and the शेष action is not to be
	 * perक्रमmed.
	 */
	TRACE_REG_PERF_ADD,
	TRACE_REG_PERF_DEL,
#पूर्ण_अगर
पूर्ण;

काष्ठा trace_event_call;

#घोषणा TRACE_FUNCTION_TYPE ((स्थिर अक्षर *)~0UL)

काष्ठा trace_event_fields अणु
	स्थिर अक्षर *type;
	जोड़ अणु
		काष्ठा अणु
			स्थिर अक्षर *name;
			स्थिर पूर्णांक  size;
			स्थिर पूर्णांक  align;
			स्थिर पूर्णांक  is_चिन्हित;
			स्थिर पूर्णांक  filter_type;
		पूर्ण;
		पूर्णांक (*define_fields)(काष्ठा trace_event_call *);
	पूर्ण;
पूर्ण;

काष्ठा trace_event_class अणु
	स्थिर अक्षर		*प्रणाली;
	व्योम			*probe;
#अगर_घोषित CONFIG_PERF_EVENTS
	व्योम			*perf_probe;
#पूर्ण_अगर
	पूर्णांक			(*reg)(काष्ठा trace_event_call *event,
				       क्रमागत trace_reg type, व्योम *data);
	काष्ठा trace_event_fields *fields_array;
	काष्ठा list_head	*(*get_fields)(काष्ठा trace_event_call *);
	काष्ठा list_head	fields;
	पूर्णांक			(*raw_init)(काष्ठा trace_event_call *);
पूर्ण;

बाह्य पूर्णांक trace_event_reg(काष्ठा trace_event_call *event,
			    क्रमागत trace_reg type, व्योम *data);

काष्ठा trace_event_buffer अणु
	काष्ठा trace_buffer		*buffer;
	काष्ठा ring_buffer_event	*event;
	काष्ठा trace_event_file		*trace_file;
	व्योम				*entry;
	अचिन्हित पूर्णांक			trace_ctx;
	काष्ठा pt_regs			*regs;
पूर्ण;

व्योम *trace_event_buffer_reserve(काष्ठा trace_event_buffer *fbuffer,
				  काष्ठा trace_event_file *trace_file,
				  अचिन्हित दीर्घ len);

व्योम trace_event_buffer_commit(काष्ठा trace_event_buffer *fbuffer);

क्रमागत अणु
	TRACE_EVENT_FL_FILTERED_BIT,
	TRACE_EVENT_FL_CAP_ANY_BIT,
	TRACE_EVENT_FL_NO_SET_FILTER_BIT,
	TRACE_EVENT_FL_IGNORE_ENABLE_BIT,
	TRACE_EVENT_FL_TRACEPOINT_BIT,
	TRACE_EVENT_FL_KPROBE_BIT,
	TRACE_EVENT_FL_UPROBE_BIT,
पूर्ण;

/*
 * Event flags:
 *  FILTERED	  - The event has a filter attached
 *  CAP_ANY	  - Any user can enable क्रम perf
 *  NO_SET_FILTER - Set when filter has error and is to be ignored
 *  IGNORE_ENABLE - For trace पूर्णांकernal events, करो not enable with debugfs file
 *  TRACEPOINT    - Event is a tracepoपूर्णांक
 *  KPROBE        - Event is a kprobe
 *  UPROBE        - Event is a uprobe
 */
क्रमागत अणु
	TRACE_EVENT_FL_FILTERED		= (1 << TRACE_EVENT_FL_FILTERED_BIT),
	TRACE_EVENT_FL_CAP_ANY		= (1 << TRACE_EVENT_FL_CAP_ANY_BIT),
	TRACE_EVENT_FL_NO_SET_FILTER	= (1 << TRACE_EVENT_FL_NO_SET_FILTER_BIT),
	TRACE_EVENT_FL_IGNORE_ENABLE	= (1 << TRACE_EVENT_FL_IGNORE_ENABLE_BIT),
	TRACE_EVENT_FL_TRACEPOINT	= (1 << TRACE_EVENT_FL_TRACEPOINT_BIT),
	TRACE_EVENT_FL_KPROBE		= (1 << TRACE_EVENT_FL_KPROBE_BIT),
	TRACE_EVENT_FL_UPROBE		= (1 << TRACE_EVENT_FL_UPROBE_BIT),
पूर्ण;

#घोषणा TRACE_EVENT_FL_UKPROBE (TRACE_EVENT_FL_KPROBE | TRACE_EVENT_FL_UPROBE)

काष्ठा trace_event_call अणु
	काष्ठा list_head	list;
	काष्ठा trace_event_class *class;
	जोड़ अणु
		अक्षर			*name;
		/* Set TRACE_EVENT_FL_TRACEPOINT flag when using "tp" */
		काष्ठा tracepoपूर्णांक	*tp;
	पूर्ण;
	काष्ठा trace_event	event;
	अक्षर			*prपूर्णांक_fmt;
	काष्ठा event_filter	*filter;
	व्योम			*mod;
	व्योम			*data;

	/* See the TRACE_EVENT_FL_* flags above */
	पूर्णांक			flags; /* अटल flags of dअगरferent events */

#अगर_घोषित CONFIG_PERF_EVENTS
	पूर्णांक				perf_refcount;
	काष्ठा hlist_head __percpu	*perf_events;
	काष्ठा bpf_prog_array __rcu	*prog_array;

	पूर्णांक	(*perf_perm)(काष्ठा trace_event_call *,
			     काष्ठा perf_event *);
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_PERF_EVENTS
अटल अंतरभूत bool bpf_prog_array_valid(काष्ठा trace_event_call *call)
अणु
	/*
	 * This अंतरभूत function checks whether call->prog_array
	 * is valid or not. The function is called in various places,
	 * outside rcu_पढ़ो_lock/unlock, as a heuristic to speed up execution.
	 *
	 * If this function वापसs true, and later call->prog_array
	 * becomes false inside rcu_पढ़ो_lock/unlock region,
	 * we bail out then. If this function वापस false,
	 * there is a risk that we might miss a few events अगर the checking
	 * were delayed until inside rcu_पढ़ो_lock/unlock region and
	 * call->prog_array happened to become non-शून्य then.
	 *
	 * Here, READ_ONCE() is used instead of rcu_access_poपूर्णांकer().
	 * rcu_access_poपूर्णांकer() requires the actual definition of
	 * "struct bpf_prog_array" जबतक READ_ONCE() only needs
	 * a declaration of the same type.
	 */
	वापस !!READ_ONCE(call->prog_array);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत स्थिर अक्षर *
trace_event_name(काष्ठा trace_event_call *call)
अणु
	अगर (call->flags & TRACE_EVENT_FL_TRACEPOINT)
		वापस call->tp ? call->tp->name : शून्य;
	अन्यथा
		वापस call->name;
पूर्ण

अटल अंतरभूत काष्ठा list_head *
trace_get_fields(काष्ठा trace_event_call *event_call)
अणु
	अगर (!event_call->class->get_fields)
		वापस &event_call->class->fields;
	वापस event_call->class->get_fields(event_call);
पूर्ण

काष्ठा trace_subप्रणाली_dir;

क्रमागत अणु
	EVENT_खाता_FL_ENABLED_BIT,
	EVENT_खाता_FL_RECORDED_CMD_BIT,
	EVENT_खाता_FL_RECORDED_TGID_BIT,
	EVENT_खाता_FL_FILTERED_BIT,
	EVENT_खाता_FL_NO_SET_FILTER_BIT,
	EVENT_खाता_FL_SOFT_MODE_BIT,
	EVENT_खाता_FL_SOFT_DISABLED_BIT,
	EVENT_खाता_FL_TRIGGER_MODE_BIT,
	EVENT_खाता_FL_TRIGGER_COND_BIT,
	EVENT_खाता_FL_PID_FILTER_BIT,
	EVENT_खाता_FL_WAS_ENABLED_BIT,
पूर्ण;

बाह्य काष्ठा trace_event_file *trace_get_event_file(स्थिर अक्षर *instance,
						     स्थिर अक्षर *प्रणाली,
						     स्थिर अक्षर *event);
बाह्य व्योम trace_put_event_file(काष्ठा trace_event_file *file);

#घोषणा MAX_DYNEVENT_CMD_LEN	(2048)

क्रमागत dynevent_type अणु
	DYNEVENT_TYPE_SYNTH = 1,
	DYNEVENT_TYPE_KPROBE,
	DYNEVENT_TYPE_NONE,
पूर्ण;

काष्ठा dynevent_cmd;

प्रकार पूर्णांक (*dynevent_create_fn_t)(काष्ठा dynevent_cmd *cmd);

काष्ठा dynevent_cmd अणु
	काष्ठा seq_buf		seq;
	स्थिर अक्षर		*event_name;
	अचिन्हित पूर्णांक		n_fields;
	क्रमागत dynevent_type	type;
	dynevent_create_fn_t	run_command;
	व्योम			*निजी_data;
पूर्ण;

बाह्य पूर्णांक dynevent_create(काष्ठा dynevent_cmd *cmd);

बाह्य पूर्णांक synth_event_delete(स्थिर अक्षर *name);

बाह्य व्योम synth_event_cmd_init(काष्ठा dynevent_cmd *cmd,
				 अक्षर *buf, पूर्णांक maxlen);

बाह्य पूर्णांक __synth_event_gen_cmd_start(काष्ठा dynevent_cmd *cmd,
				       स्थिर अक्षर *name,
				       काष्ठा module *mod, ...);

#घोषणा synth_event_gen_cmd_start(cmd, name, mod, ...)	\
	__synth_event_gen_cmd_start(cmd, name, mod, ## __VA_ARGS__, शून्य)

काष्ठा synth_field_desc अणु
	स्थिर अक्षर *type;
	स्थिर अक्षर *name;
पूर्ण;

बाह्य पूर्णांक synth_event_gen_cmd_array_start(काष्ठा dynevent_cmd *cmd,
					   स्थिर अक्षर *name,
					   काष्ठा module *mod,
					   काष्ठा synth_field_desc *fields,
					   अचिन्हित पूर्णांक n_fields);
बाह्य पूर्णांक synth_event_create(स्थिर अक्षर *name,
			      काष्ठा synth_field_desc *fields,
			      अचिन्हित पूर्णांक n_fields, काष्ठा module *mod);

बाह्य पूर्णांक synth_event_add_field(काष्ठा dynevent_cmd *cmd,
				 स्थिर अक्षर *type,
				 स्थिर अक्षर *name);
बाह्य पूर्णांक synth_event_add_field_str(काष्ठा dynevent_cmd *cmd,
				     स्थिर अक्षर *type_name);
बाह्य पूर्णांक synth_event_add_fields(काष्ठा dynevent_cmd *cmd,
				  काष्ठा synth_field_desc *fields,
				  अचिन्हित पूर्णांक n_fields);

#घोषणा synth_event_gen_cmd_end(cmd)	\
	dynevent_create(cmd)

काष्ठा synth_event;

काष्ठा synth_event_trace_state अणु
	काष्ठा trace_event_buffer fbuffer;
	काष्ठा synth_trace_event *entry;
	काष्ठा trace_buffer *buffer;
	काष्ठा synth_event *event;
	अचिन्हित पूर्णांक cur_field;
	अचिन्हित पूर्णांक n_u64;
	bool disabled;
	bool add_next;
	bool add_name;
पूर्ण;

बाह्य पूर्णांक synth_event_trace(काष्ठा trace_event_file *file,
			     अचिन्हित पूर्णांक n_vals, ...);
बाह्य पूर्णांक synth_event_trace_array(काष्ठा trace_event_file *file, u64 *vals,
				   अचिन्हित पूर्णांक n_vals);
बाह्य पूर्णांक synth_event_trace_start(काष्ठा trace_event_file *file,
				   काष्ठा synth_event_trace_state *trace_state);
बाह्य पूर्णांक synth_event_add_next_val(u64 val,
				    काष्ठा synth_event_trace_state *trace_state);
बाह्य पूर्णांक synth_event_add_val(स्थिर अक्षर *field_name, u64 val,
			       काष्ठा synth_event_trace_state *trace_state);
बाह्य पूर्णांक synth_event_trace_end(काष्ठा synth_event_trace_state *trace_state);

बाह्य पूर्णांक kprobe_event_delete(स्थिर अक्षर *name);

बाह्य व्योम kprobe_event_cmd_init(काष्ठा dynevent_cmd *cmd,
				  अक्षर *buf, पूर्णांक maxlen);

#घोषणा kprobe_event_gen_cmd_start(cmd, name, loc, ...)			\
	__kprobe_event_gen_cmd_start(cmd, false, name, loc, ## __VA_ARGS__, शून्य)

#घोषणा kretprobe_event_gen_cmd_start(cmd, name, loc, ...)		\
	__kprobe_event_gen_cmd_start(cmd, true, name, loc, ## __VA_ARGS__, शून्य)

बाह्य पूर्णांक __kprobe_event_gen_cmd_start(काष्ठा dynevent_cmd *cmd,
					bool kretprobe,
					स्थिर अक्षर *name,
					स्थिर अक्षर *loc, ...);

#घोषणा kprobe_event_add_fields(cmd, ...)	\
	__kprobe_event_add_fields(cmd, ## __VA_ARGS__, शून्य)

#घोषणा kprobe_event_add_field(cmd, field)	\
	__kprobe_event_add_fields(cmd, field, शून्य)

बाह्य पूर्णांक __kprobe_event_add_fields(काष्ठा dynevent_cmd *cmd, ...);

#घोषणा kprobe_event_gen_cmd_end(cmd)		\
	dynevent_create(cmd)

#घोषणा kretprobe_event_gen_cmd_end(cmd)	\
	dynevent_create(cmd)

/*
 * Event file flags:
 *  ENABLED	  - The event is enabled
 *  RECORDED_CMD  - The comms should be recorded at sched_चयन
 *  RECORDED_TGID - The tgids should be recorded at sched_चयन
 *  FILTERED	  - The event has a filter attached
 *  NO_SET_FILTER - Set when filter has error and is to be ignored
 *  SOFT_MODE     - The event is enabled/disabled by SOFT_DISABLED
 *  SOFT_DISABLED - When set, करो not trace the event (even though its
 *                   tracepoपूर्णांक may be enabled)
 *  TRIGGER_MODE  - When set, invoke the triggers associated with the event
 *  TRIGGER_COND  - When set, one or more triggers has an associated filter
 *  PID_FILTER    - When set, the event is filtered based on pid
 *  WAS_ENABLED   - Set when enabled to know to clear trace on module removal
 */
क्रमागत अणु
	EVENT_खाता_FL_ENABLED		= (1 << EVENT_खाता_FL_ENABLED_BIT),
	EVENT_खाता_FL_RECORDED_CMD	= (1 << EVENT_खाता_FL_RECORDED_CMD_BIT),
	EVENT_खाता_FL_RECORDED_TGID	= (1 << EVENT_खाता_FL_RECORDED_TGID_BIT),
	EVENT_खाता_FL_FILTERED		= (1 << EVENT_खाता_FL_FILTERED_BIT),
	EVENT_खाता_FL_NO_SET_FILTER	= (1 << EVENT_खाता_FL_NO_SET_FILTER_BIT),
	EVENT_खाता_FL_SOFT_MODE		= (1 << EVENT_खाता_FL_SOFT_MODE_BIT),
	EVENT_खाता_FL_SOFT_DISABLED	= (1 << EVENT_खाता_FL_SOFT_DISABLED_BIT),
	EVENT_खाता_FL_TRIGGER_MODE	= (1 << EVENT_खाता_FL_TRIGGER_MODE_BIT),
	EVENT_खाता_FL_TRIGGER_COND	= (1 << EVENT_खाता_FL_TRIGGER_COND_BIT),
	EVENT_खाता_FL_PID_FILTER	= (1 << EVENT_खाता_FL_PID_FILTER_BIT),
	EVENT_खाता_FL_WAS_ENABLED	= (1 << EVENT_खाता_FL_WAS_ENABLED_BIT),
पूर्ण;

काष्ठा trace_event_file अणु
	काष्ठा list_head		list;
	काष्ठा trace_event_call		*event_call;
	काष्ठा event_filter __rcu	*filter;
	काष्ठा dentry			*dir;
	काष्ठा trace_array		*tr;
	काष्ठा trace_subप्रणाली_dir	*प्रणाली;
	काष्ठा list_head		triggers;

	/*
	 * 32 bit flags:
	 *   bit 0:		enabled
	 *   bit 1:		enabled cmd record
	 *   bit 2:		enable/disable with the soft disable bit
	 *   bit 3:		soft disabled
	 *   bit 4:		trigger enabled
	 *
	 * Note: The bits must be set atomically to prevent races
	 * from other ग_लिखोrs. Reads of flags करो not need to be in
	 * sync as they occur in critical sections. But the way flags
	 * is currently used, these changes करो not affect the code
	 * except that when a change is made, it may have a slight
	 * delay in propagating the changes to other CPUs due to
	 * caching and such. Which is mostly OK ;-)
	 */
	अचिन्हित दीर्घ		flags;
	atomic_t		sm_ref;	/* soft-mode reference counter */
	atomic_t		पंचांग_ref;	/* trigger-mode reference counter */
पूर्ण;

#घोषणा __TRACE_EVENT_FLAGS(name, value)				\
	अटल पूर्णांक __init trace_init_flags_##name(व्योम)			\
	अणु								\
		event_##name.flags |= value;				\
		वापस 0;						\
	पूर्ण								\
	early_initcall(trace_init_flags_##name);

#घोषणा __TRACE_EVENT_PERF_PERM(name, expr...)				\
	अटल पूर्णांक perf_perm_##name(काष्ठा trace_event_call *tp_event, \
				    काष्ठा perf_event *p_event)		\
	अणु								\
		वापस (अणु expr; पूर्ण);					\
	पूर्ण								\
	अटल पूर्णांक __init trace_init_perf_perm_##name(व्योम)		\
	अणु								\
		event_##name.perf_perm = &perf_perm_##name;		\
		वापस 0;						\
	पूर्ण								\
	early_initcall(trace_init_perf_perm_##name);

#घोषणा PERF_MAX_TRACE_SIZE	2048

#घोषणा MAX_FILTER_STR_VAL	256	/* Should handle KSYM_SYMBOL_LEN */

क्रमागत event_trigger_type अणु
	ETT_NONE		= (0),
	ETT_TRACE_ONOFF		= (1 << 0),
	ETT_SNAPSHOT		= (1 << 1),
	ETT_STACKTRACE		= (1 << 2),
	ETT_EVENT_ENABLE	= (1 << 3),
	ETT_EVENT_HIST		= (1 << 4),
	ETT_HIST_ENABLE		= (1 << 5),
पूर्ण;

बाह्य पूर्णांक filter_match_preds(काष्ठा event_filter *filter, व्योम *rec);

बाह्य क्रमागत event_trigger_type
event_triggers_call(काष्ठा trace_event_file *file,
		    काष्ठा trace_buffer *buffer, व्योम *rec,
		    काष्ठा ring_buffer_event *event);
बाह्य व्योम
event_triggers_post_call(काष्ठा trace_event_file *file,
			 क्रमागत event_trigger_type tt);

bool trace_event_ignore_this_pid(काष्ठा trace_event_file *trace_file);

/**
 * trace_trigger_soft_disabled - करो triggers and test अगर soft disabled
 * @file: The file poपूर्णांकer of the event to test
 *
 * If any triggers without filters are attached to this event, they
 * will be called here. If the event is soft disabled and has no
 * triggers that require testing the fields, it will वापस true,
 * otherwise false.
 */
अटल अंतरभूत bool
trace_trigger_soft_disabled(काष्ठा trace_event_file *file)
अणु
	अचिन्हित दीर्घ eflags = file->flags;

	अगर (!(eflags & EVENT_खाता_FL_TRIGGER_COND)) अणु
		अगर (eflags & EVENT_खाता_FL_TRIGGER_MODE)
			event_triggers_call(file, शून्य, शून्य, शून्य);
		अगर (eflags & EVENT_खाता_FL_SOFT_DISABLED)
			वापस true;
		अगर (eflags & EVENT_खाता_FL_PID_FILTER)
			वापस trace_event_ignore_this_pid(file);
	पूर्ण
	वापस false;
पूर्ण

#अगर_घोषित CONFIG_BPF_EVENTS
अचिन्हित पूर्णांक trace_call_bpf(काष्ठा trace_event_call *call, व्योम *ctx);
पूर्णांक perf_event_attach_bpf_prog(काष्ठा perf_event *event, काष्ठा bpf_prog *prog);
व्योम perf_event_detach_bpf_prog(काष्ठा perf_event *event);
पूर्णांक perf_event_query_prog_array(काष्ठा perf_event *event, व्योम __user *info);
पूर्णांक bpf_probe_रेजिस्टर(काष्ठा bpf_raw_event_map *btp, काष्ठा bpf_prog *prog);
पूर्णांक bpf_probe_unरेजिस्टर(काष्ठा bpf_raw_event_map *btp, काष्ठा bpf_prog *prog);
काष्ठा bpf_raw_event_map *bpf_get_raw_tracepoपूर्णांक(स्थिर अक्षर *name);
व्योम bpf_put_raw_tracepoपूर्णांक(काष्ठा bpf_raw_event_map *btp);
पूर्णांक bpf_get_perf_event_info(स्थिर काष्ठा perf_event *event, u32 *prog_id,
			    u32 *fd_type, स्थिर अक्षर **buf,
			    u64 *probe_offset, u64 *probe_addr);
#अन्यथा
अटल अंतरभूत अचिन्हित पूर्णांक trace_call_bpf(काष्ठा trace_event_call *call, व्योम *ctx)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक
perf_event_attach_bpf_prog(काष्ठा perf_event *event, काष्ठा bpf_prog *prog)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम perf_event_detach_bpf_prog(काष्ठा perf_event *event) अणु पूर्ण

अटल अंतरभूत पूर्णांक
perf_event_query_prog_array(काष्ठा perf_event *event, व्योम __user *info)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक bpf_probe_रेजिस्टर(काष्ठा bpf_raw_event_map *btp, काष्ठा bpf_prog *p)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक bpf_probe_unरेजिस्टर(काष्ठा bpf_raw_event_map *btp, काष्ठा bpf_prog *p)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत काष्ठा bpf_raw_event_map *bpf_get_raw_tracepoपूर्णांक(स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम bpf_put_raw_tracepoपूर्णांक(काष्ठा bpf_raw_event_map *btp)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक bpf_get_perf_event_info(स्थिर काष्ठा perf_event *event,
					  u32 *prog_id, u32 *fd_type,
					  स्थिर अक्षर **buf, u64 *probe_offset,
					  u64 *probe_addr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

क्रमागत अणु
	FILTER_OTHER = 0,
	FILTER_STATIC_STRING,
	FILTER_DYN_STRING,
	FILTER_PTR_STRING,
	FILTER_TRACE_FN,
	FILTER_COMM,
	FILTER_CPU,
पूर्ण;

बाह्य पूर्णांक trace_event_raw_init(काष्ठा trace_event_call *call);
बाह्य पूर्णांक trace_define_field(काष्ठा trace_event_call *call, स्थिर अक्षर *type,
			      स्थिर अक्षर *name, पूर्णांक offset, पूर्णांक size,
			      पूर्णांक is_चिन्हित, पूर्णांक filter_type);
बाह्य पूर्णांक trace_add_event_call(काष्ठा trace_event_call *call);
बाह्य पूर्णांक trace_हटाओ_event_call(काष्ठा trace_event_call *call);
बाह्य पूर्णांक trace_event_get_offsets(काष्ठा trace_event_call *call);

#घोषणा is_चिन्हित_type(type)	(((type)(-1)) < (type)1)

पूर्णांक ftrace_set_clr_event(काष्ठा trace_array *tr, अक्षर *buf, पूर्णांक set);
पूर्णांक trace_set_clr_event(स्थिर अक्षर *प्रणाली, स्थिर अक्षर *event, पूर्णांक set);
पूर्णांक trace_array_set_clr_event(काष्ठा trace_array *tr, स्थिर अक्षर *प्रणाली,
		स्थिर अक्षर *event, bool enable);
/*
 * The द्विगुन __builtin_स्थिरant_p is because gcc will give us an error
 * अगर we try to allocate the अटल variable to fmt अगर it is not a
 * स्थिरant. Even with the outer अगर statement optimizing out.
 */
#घोषणा event_trace_prपूर्णांकk(ip, fmt, args...)				\
करो अणु									\
	__trace_prपूर्णांकk_check_क्रमmat(fmt, ##args);			\
	tracing_record_cmdline(current);				\
	अगर (__builtin_स्थिरant_p(fmt)) अणु				\
		अटल स्थिर अक्षर *trace_prपूर्णांकk_fmt			\
		  __section("__trace_printk_fmt") =			\
			__builtin_स्थिरant_p(fmt) ? fmt : शून्य;		\
									\
		__trace_bprपूर्णांकk(ip, trace_prपूर्णांकk_fmt, ##args);		\
	पूर्ण अन्यथा								\
		__trace_prपूर्णांकk(ip, fmt, ##args);			\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_PERF_EVENTS
काष्ठा perf_event;

DECLARE_PER_CPU(काष्ठा pt_regs, perf_trace_regs);
DECLARE_PER_CPU(पूर्णांक, bpf_kprobe_override);

बाह्य पूर्णांक  perf_trace_init(काष्ठा perf_event *event);
बाह्य व्योम perf_trace_destroy(काष्ठा perf_event *event);
बाह्य पूर्णांक  perf_trace_add(काष्ठा perf_event *event, पूर्णांक flags);
बाह्य व्योम perf_trace_del(काष्ठा perf_event *event, पूर्णांक flags);
#अगर_घोषित CONFIG_KPROBE_EVENTS
बाह्य पूर्णांक  perf_kprobe_init(काष्ठा perf_event *event, bool is_retprobe);
बाह्य व्योम perf_kprobe_destroy(काष्ठा perf_event *event);
बाह्य पूर्णांक bpf_get_kprobe_info(स्थिर काष्ठा perf_event *event,
			       u32 *fd_type, स्थिर अक्षर **symbol,
			       u64 *probe_offset, u64 *probe_addr,
			       bool perf_type_tracepoपूर्णांक);
#पूर्ण_अगर
#अगर_घोषित CONFIG_UPROBE_EVENTS
बाह्य पूर्णांक  perf_uprobe_init(काष्ठा perf_event *event,
			     अचिन्हित दीर्घ ref_ctr_offset, bool is_retprobe);
बाह्य व्योम perf_uprobe_destroy(काष्ठा perf_event *event);
बाह्य पूर्णांक bpf_get_uprobe_info(स्थिर काष्ठा perf_event *event,
			       u32 *fd_type, स्थिर अक्षर **filename,
			       u64 *probe_offset, bool perf_type_tracepoपूर्णांक);
#पूर्ण_अगर
बाह्य पूर्णांक  ftrace_profile_set_filter(काष्ठा perf_event *event, पूर्णांक event_id,
				     अक्षर *filter_str);
बाह्य व्योम ftrace_profile_मुक्त_filter(काष्ठा perf_event *event);
व्योम perf_trace_buf_update(व्योम *record, u16 type);
व्योम *perf_trace_buf_alloc(पूर्णांक size, काष्ठा pt_regs **regs, पूर्णांक *rctxp);

व्योम bpf_trace_run1(काष्ठा bpf_prog *prog, u64 arg1);
व्योम bpf_trace_run2(काष्ठा bpf_prog *prog, u64 arg1, u64 arg2);
व्योम bpf_trace_run3(काष्ठा bpf_prog *prog, u64 arg1, u64 arg2,
		    u64 arg3);
व्योम bpf_trace_run4(काष्ठा bpf_prog *prog, u64 arg1, u64 arg2,
		    u64 arg3, u64 arg4);
व्योम bpf_trace_run5(काष्ठा bpf_prog *prog, u64 arg1, u64 arg2,
		    u64 arg3, u64 arg4, u64 arg5);
व्योम bpf_trace_run6(काष्ठा bpf_prog *prog, u64 arg1, u64 arg2,
		    u64 arg3, u64 arg4, u64 arg5, u64 arg6);
व्योम bpf_trace_run7(काष्ठा bpf_prog *prog, u64 arg1, u64 arg2,
		    u64 arg3, u64 arg4, u64 arg5, u64 arg6, u64 arg7);
व्योम bpf_trace_run8(काष्ठा bpf_prog *prog, u64 arg1, u64 arg2,
		    u64 arg3, u64 arg4, u64 arg5, u64 arg6, u64 arg7,
		    u64 arg8);
व्योम bpf_trace_run9(काष्ठा bpf_prog *prog, u64 arg1, u64 arg2,
		    u64 arg3, u64 arg4, u64 arg5, u64 arg6, u64 arg7,
		    u64 arg8, u64 arg9);
व्योम bpf_trace_run10(काष्ठा bpf_prog *prog, u64 arg1, u64 arg2,
		     u64 arg3, u64 arg4, u64 arg5, u64 arg6, u64 arg7,
		     u64 arg8, u64 arg9, u64 arg10);
व्योम bpf_trace_run11(काष्ठा bpf_prog *prog, u64 arg1, u64 arg2,
		     u64 arg3, u64 arg4, u64 arg5, u64 arg6, u64 arg7,
		     u64 arg8, u64 arg9, u64 arg10, u64 arg11);
व्योम bpf_trace_run12(काष्ठा bpf_prog *prog, u64 arg1, u64 arg2,
		     u64 arg3, u64 arg4, u64 arg5, u64 arg6, u64 arg7,
		     u64 arg8, u64 arg9, u64 arg10, u64 arg11, u64 arg12);
व्योम perf_trace_run_bpf_submit(व्योम *raw_data, पूर्णांक size, पूर्णांक rctx,
			       काष्ठा trace_event_call *call, u64 count,
			       काष्ठा pt_regs *regs, काष्ठा hlist_head *head,
			       काष्ठा task_काष्ठा *task);

अटल अंतरभूत व्योम
perf_trace_buf_submit(व्योम *raw_data, पूर्णांक size, पूर्णांक rctx, u16 type,
		       u64 count, काष्ठा pt_regs *regs, व्योम *head,
		       काष्ठा task_काष्ठा *task)
अणु
	perf_tp_event(type, count, raw_data, size, regs, head, rctx, task);
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_TRACE_EVENT_H */
