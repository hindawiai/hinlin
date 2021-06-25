<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#अगर_अघोषित _LINUX_KERNEL_TRACE_H
#घोषणा _LINUX_KERNEL_TRACE_H

#समावेश <linux/fs.h>
#समावेश <linux/atomic.h>
#समावेश <linux/sched.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/ring_buffer.h>
#समावेश <linux/mmiotrace.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/trace.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/trace_seq.h>
#समावेश <linux/trace_events.h>
#समावेश <linux/compiler.h>
#समावेश <linux/glob.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/प्रकार.स>

#अगर_घोषित CONFIG_FTRACE_SYSCALLS
#समावेश <यंत्र/unistd.h>		/* For NR_SYSCALLS	     */
#समावेश <यंत्र/syscall.h>	/* some archs define it here */
#पूर्ण_अगर

क्रमागत trace_type अणु
	__TRACE_FIRST_TYPE = 0,

	TRACE_FN,
	TRACE_CTX,
	TRACE_WAKE,
	TRACE_STACK,
	TRACE_PRINT,
	TRACE_BPRINT,
	TRACE_MMIO_RW,
	TRACE_MMIO_MAP,
	TRACE_BRANCH,
	TRACE_GRAPH_RET,
	TRACE_GRAPH_ENT,
	TRACE_USER_STACK,
	TRACE_BLK,
	TRACE_BPUTS,
	TRACE_HWLAT,
	TRACE_RAW_DATA,
	TRACE_FUNC_REPEATS,

	__TRACE_LAST_TYPE,
पूर्ण;


#अघोषित __field
#घोषणा __field(type, item)		type	item;

#अघोषित __field_fn
#घोषणा __field_fn(type, item)		type	item;

#अघोषित __field_काष्ठा
#घोषणा __field_काष्ठा(type, item)	__field(type, item)

#अघोषित __field_desc
#घोषणा __field_desc(type, container, item)

#अघोषित __field_packed
#घोषणा __field_packed(type, container, item)

#अघोषित __array
#घोषणा __array(type, item, size)	type	item[size];

#अघोषित __array_desc
#घोषणा __array_desc(type, container, item, size)

#अघोषित __dynamic_array
#घोषणा __dynamic_array(type, item)	type	item[];

#अघोषित F_STRUCT
#घोषणा F_STRUCT(args...)		args

#अघोषित FTRACE_ENTRY
#घोषणा FTRACE_ENTRY(name, काष्ठा_name, id, tकाष्ठा, prपूर्णांक)		\
	काष्ठा काष्ठा_name अणु						\
		काष्ठा trace_entry	ent;				\
		tकाष्ठा							\
	पूर्ण

#अघोषित FTRACE_ENTRY_DUP
#घोषणा FTRACE_ENTRY_DUP(name, name_काष्ठा, id, tकाष्ठा, prपूर्णांकk)

#अघोषित FTRACE_ENTRY_REG
#घोषणा FTRACE_ENTRY_REG(name, काष्ठा_name, id, tकाष्ठा, prपूर्णांक,	regfn)	\
	FTRACE_ENTRY(name, काष्ठा_name, id, PARAMS(tकाष्ठा), PARAMS(prपूर्णांक))

#अघोषित FTRACE_ENTRY_PACKED
#घोषणा FTRACE_ENTRY_PACKED(name, काष्ठा_name, id, tकाष्ठा, prपूर्णांक)	\
	FTRACE_ENTRY(name, काष्ठा_name, id, PARAMS(tकाष्ठा), PARAMS(prपूर्णांक)) __packed

#समावेश "trace_entries.h"

/* Use this क्रम memory failure errors */
#घोषणा MEM_FAIL(condition, fmt, ...) (अणु			\
	अटल bool __section(".data.once") __warned;		\
	पूर्णांक __ret_warn_once = !!(condition);			\
								\
	अगर (unlikely(__ret_warn_once && !__warned)) अणु		\
		__warned = true;				\
		pr_err("ERROR: " fmt, ##__VA_ARGS__);		\
	पूर्ण							\
	unlikely(__ret_warn_once);				\
पूर्ण)

/*
 * syscalls are special, and need special handling, this is why
 * they are not included in trace_entries.h
 */
काष्ठा syscall_trace_enter अणु
	काष्ठा trace_entry	ent;
	पूर्णांक			nr;
	अचिन्हित दीर्घ		args[];
पूर्ण;

काष्ठा syscall_trace_निकास अणु
	काष्ठा trace_entry	ent;
	पूर्णांक			nr;
	दीर्घ			ret;
पूर्ण;

काष्ठा kprobe_trace_entry_head अणु
	काष्ठा trace_entry	ent;
	अचिन्हित दीर्घ		ip;
पूर्ण;

काष्ठा kretprobe_trace_entry_head अणु
	काष्ठा trace_entry	ent;
	अचिन्हित दीर्घ		func;
	अचिन्हित दीर्घ		ret_ip;
पूर्ण;

#घोषणा TRACE_BUF_SIZE		1024

काष्ठा trace_array;

/*
 * The CPU trace array - it consists of thousands of trace entries
 * plus some other descriptor data: (क्रम example which task started
 * the trace, etc.)
 */
काष्ठा trace_array_cpu अणु
	atomic_t		disabled;
	व्योम			*buffer_page;	/* ring buffer spare */

	अचिन्हित दीर्घ		entries;
	अचिन्हित दीर्घ		saved_latency;
	अचिन्हित दीर्घ		critical_start;
	अचिन्हित दीर्घ		critical_end;
	अचिन्हित दीर्घ		critical_sequence;
	अचिन्हित दीर्घ		nice;
	अचिन्हित दीर्घ		policy;
	अचिन्हित दीर्घ		rt_priority;
	अचिन्हित दीर्घ		skipped_entries;
	u64			preempt_बारtamp;
	pid_t			pid;
	kuid_t			uid;
	अक्षर			comm[TASK_COMM_LEN];

#अगर_घोषित CONFIG_FUNCTION_TRACER
	पूर्णांक			ftrace_ignore_pid;
#पूर्ण_अगर
	bool			ignore_pid;
पूर्ण;

काष्ठा tracer;
काष्ठा trace_option_dentry;

काष्ठा array_buffer अणु
	काष्ठा trace_array		*tr;
	काष्ठा trace_buffer		*buffer;
	काष्ठा trace_array_cpu __percpu	*data;
	u64				समय_start;
	पूर्णांक				cpu;
पूर्ण;

#घोषणा TRACE_FLAGS_MAX_SIZE		32

काष्ठा trace_options अणु
	काष्ठा tracer			*tracer;
	काष्ठा trace_option_dentry	*topts;
पूर्ण;

काष्ठा trace_pid_list अणु
	पूर्णांक				pid_max;
	अचिन्हित दीर्घ			*pids;
पूर्ण;

क्रमागत अणु
	TRACE_PIDS		= BIT(0),
	TRACE_NO_PIDS		= BIT(1),
पूर्ण;

अटल अंतरभूत bool pid_type_enabled(पूर्णांक type, काष्ठा trace_pid_list *pid_list,
				    काष्ठा trace_pid_list *no_pid_list)
अणु
	/* Return true अगर the pid list in type has pids */
	वापस ((type & TRACE_PIDS) && pid_list) ||
		((type & TRACE_NO_PIDS) && no_pid_list);
पूर्ण

अटल अंतरभूत bool still_need_pid_events(पूर्णांक type, काष्ठा trace_pid_list *pid_list,
					 काष्ठा trace_pid_list *no_pid_list)
अणु
	/*
	 * Turning off what is in @type, वापस true अगर the "other"
	 * pid list, still has pids in it.
	 */
	वापस (!(type & TRACE_PIDS) && pid_list) ||
		(!(type & TRACE_NO_PIDS) && no_pid_list);
पूर्ण

प्रकार bool (*cond_update_fn_t)(काष्ठा trace_array *tr, व्योम *cond_data);

/**
 * काष्ठा cond_snapshot - conditional snapshot data and callback
 *
 * The cond_snapshot काष्ठाure encapsulates a callback function and
 * data associated with the snapshot क्रम a given tracing instance.
 *
 * When a snapshot is taken conditionally, by invoking
 * tracing_snapshot_cond(tr, cond_data), the cond_data passed in is
 * passed in turn to the cond_snapshot.update() function.  That data
 * can be compared by the update() implementation with the cond_data
 * contained within the काष्ठा cond_snapshot instance associated with
 * the trace_array.  Because the tr->max_lock is held throughout the
 * update() call, the update() function can directly retrieve the
 * cond_snapshot and cond_data associated with the per-instance
 * snapshot associated with the trace_array.
 *
 * The cond_snapshot.update() implementation can save data to be
 * associated with the snapshot अगर it decides to, and वापसs 'true'
 * in that हाल, or it वापसs 'false' अगर the conditional snapshot
 * shouldn't be taken.
 *
 * The cond_snapshot instance is created and associated with the
 * user-defined cond_data by tracing_cond_snapshot_enable().
 * Likewise, the cond_snapshot instance is destroyed and is no दीर्घer
 * associated with the trace instance by
 * tracing_cond_snapshot_disable().
 *
 * The method below is required.
 *
 * @update: When a conditional snapshot is invoked, the update()
 *	callback function is invoked with the tr->max_lock held.  The
 *	update() implementation संकेतs whether or not to actually
 *	take the snapshot, by वापसing 'true' if so, 'false' अगर no
 *	snapshot should be taken.  Because the max_lock is held क्रम
 *	the duration of update(), the implementation is safe to
 *	directly retrieved and save any implementation data it needs
 *	to in association with the snapshot.
 */
काष्ठा cond_snapshot अणु
	व्योम				*cond_data;
	cond_update_fn_t		update;
पूर्ण;

/*
 * काष्ठा trace_func_repeats - used to keep track of the consecutive
 * (on the same CPU) calls of a single function.
 */
काष्ठा trace_func_repeats अणु
	अचिन्हित दीर्घ	ip;
	अचिन्हित दीर्घ	parent_ip;
	अचिन्हित दीर्घ	count;
	u64		ts_last_call;
पूर्ण;

/*
 * The trace array - an array of per-CPU trace arrays. This is the
 * highest level data काष्ठाure that inभागidual tracers deal with.
 * They have on/off state as well:
 */
काष्ठा trace_array अणु
	काष्ठा list_head	list;
	अक्षर			*name;
	काष्ठा array_buffer	array_buffer;
#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	/*
	 * The max_buffer is used to snapshot the trace when a maximum
	 * latency is reached, or when the user initiates a snapshot.
	 * Some tracers will use this to store a maximum trace जबतक
	 * it जारीs examining live traces.
	 *
	 * The buffers क्रम the max_buffer are set up the same as the array_buffer
	 * When a snapshot is taken, the buffer of the max_buffer is swapped
	 * with the buffer of the array_buffer and the buffers are reset क्रम
	 * the array_buffer so the tracing can जारी.
	 */
	काष्ठा array_buffer	max_buffer;
	bool			allocated_snapshot;
#पूर्ण_अगर
#अगर defined(CONFIG_TRACER_MAX_TRACE) || defined(CONFIG_HWLAT_TRACER)
	अचिन्हित दीर्घ		max_latency;
#अगर_घोषित CONFIG_FSNOTIFY
	काष्ठा dentry		*d_max_latency;
	काष्ठा work_काष्ठा	fsnotअगरy_work;
	काष्ठा irq_work		fsnotअगरy_irqwork;
#पूर्ण_अगर
#पूर्ण_अगर
	काष्ठा trace_pid_list	__rcu *filtered_pids;
	काष्ठा trace_pid_list	__rcu *filtered_no_pids;
	/*
	 * max_lock is used to protect the swapping of buffers
	 * when taking a max snapshot. The buffers themselves are
	 * रक्षित by per_cpu spinlocks. But the action of the swap
	 * needs its own lock.
	 *
	 * This is defined as a arch_spinlock_t in order to help
	 * with perक्रमmance when lockdep debugging is enabled.
	 *
	 * It is also used in other places outside the update_max_tr
	 * so it needs to be defined outside of the
	 * CONFIG_TRACER_MAX_TRACE.
	 */
	arch_spinlock_t		max_lock;
	पूर्णांक			buffer_disabled;
#अगर_घोषित CONFIG_FTRACE_SYSCALLS
	पूर्णांक			sys_refcount_enter;
	पूर्णांक			sys_refcount_निकास;
	काष्ठा trace_event_file __rcu *enter_syscall_files[NR_syscalls];
	काष्ठा trace_event_file __rcu *निकास_syscall_files[NR_syscalls];
#पूर्ण_अगर
	पूर्णांक			stop_count;
	पूर्णांक			घड़ी_id;
	पूर्णांक			nr_topts;
	bool			clear_trace;
	पूर्णांक			buffer_percent;
	अचिन्हित पूर्णांक		n_err_log_entries;
	काष्ठा tracer		*current_trace;
	अचिन्हित पूर्णांक		trace_flags;
	अचिन्हित अक्षर		trace_flags_index[TRACE_FLAGS_MAX_SIZE];
	अचिन्हित पूर्णांक		flags;
	raw_spinlock_t		start_lock;
	काष्ठा list_head	err_log;
	काष्ठा dentry		*dir;
	काष्ठा dentry		*options;
	काष्ठा dentry		*percpu_dir;
	काष्ठा dentry		*event_dir;
	काष्ठा trace_options	*topts;
	काष्ठा list_head	प्रणालीs;
	काष्ठा list_head	events;
	काष्ठा trace_event_file *trace_marker_file;
	cpumask_var_t		tracing_cpumask; /* only trace on set CPUs */
	पूर्णांक			ref;
	पूर्णांक			trace_ref;
#अगर_घोषित CONFIG_FUNCTION_TRACER
	काष्ठा ftrace_ops	*ops;
	काष्ठा trace_pid_list	__rcu *function_pids;
	काष्ठा trace_pid_list	__rcu *function_no_pids;
#अगर_घोषित CONFIG_DYNAMIC_FTRACE
	/* All of these are रक्षित by the ftrace_lock */
	काष्ठा list_head	func_probes;
	काष्ठा list_head	mod_trace;
	काष्ठा list_head	mod_notrace;
#पूर्ण_अगर
	/* function tracing enabled */
	पूर्णांक			function_enabled;
#पूर्ण_अगर
	पूर्णांक			no_filter_buffering_ref;
	काष्ठा list_head	hist_vars;
#अगर_घोषित CONFIG_TRACER_SNAPSHOT
	काष्ठा cond_snapshot	*cond_snapshot;
#पूर्ण_अगर
	काष्ठा trace_func_repeats	__percpu *last_func_repeats;
पूर्ण;

क्रमागत अणु
	TRACE_ARRAY_FL_GLOBAL	= (1 << 0)
पूर्ण;

बाह्य काष्ठा list_head ftrace_trace_arrays;

बाह्य काष्ठा mutex trace_types_lock;

बाह्य पूर्णांक trace_array_get(काष्ठा trace_array *tr);
बाह्य पूर्णांक tracing_check_खोलो_get_tr(काष्ठा trace_array *tr);
बाह्य काष्ठा trace_array *trace_array_find(स्थिर अक्षर *instance);
बाह्य काष्ठा trace_array *trace_array_find_get(स्थिर अक्षर *instance);

बाह्य u64 tracing_event_समय_stamp(काष्ठा trace_buffer *buffer, काष्ठा ring_buffer_event *rbe);
बाह्य पूर्णांक tracing_set_filter_buffering(काष्ठा trace_array *tr, bool set);
बाह्य पूर्णांक tracing_set_घड़ी(काष्ठा trace_array *tr, स्थिर अक्षर *घड़ीstr);

बाह्य bool trace_घड़ी_in_ns(काष्ठा trace_array *tr);

/*
 * The global tracer (top) should be the first trace array added,
 * but we check the flag anyway.
 */
अटल अंतरभूत काष्ठा trace_array *top_trace_array(व्योम)
अणु
	काष्ठा trace_array *tr;

	अगर (list_empty(&ftrace_trace_arrays))
		वापस शून्य;

	tr = list_entry(ftrace_trace_arrays.prev,
			typeof(*tr), list);
	WARN_ON(!(tr->flags & TRACE_ARRAY_FL_GLOBAL));
	वापस tr;
पूर्ण

#घोषणा FTRACE_CMP_TYPE(var, type) \
	__builtin_types_compatible_p(typeof(var), type *)

#अघोषित IF_ASSIGN
#घोषणा IF_ASSIGN(var, entry, etype, id)			\
	अगर (FTRACE_CMP_TYPE(var, etype)) अणु			\
		var = (typeof(var))(entry);			\
		WARN_ON(id != 0 && (entry)->type != id);	\
		अवरोध;						\
	पूर्ण

/* Will cause compile errors अगर type is not found. */
बाह्य व्योम __ftrace_bad_type(व्योम);

/*
 * The trace_assign_type is a verअगरier that the entry type is
 * the same as the type being asचिन्हित. To add new types simply
 * add a line with the following क्रमmat:
 *
 * IF_ASSIGN(var, ent, type, id);
 *
 *  Where "type" is the trace type that includes the trace_entry
 *  as the "ent" item. And "id" is the trace identअगरier that is
 *  used in the trace_type क्रमागत.
 *
 *  If the type can have more than one id, then use zero.
 */
#घोषणा trace_assign_type(var, ent)					\
	करो अणु								\
		IF_ASSIGN(var, ent, काष्ठा ftrace_entry, TRACE_FN);	\
		IF_ASSIGN(var, ent, काष्ठा ctx_चयन_entry, 0);	\
		IF_ASSIGN(var, ent, काष्ठा stack_entry, TRACE_STACK);	\
		IF_ASSIGN(var, ent, काष्ठा userstack_entry, TRACE_USER_STACK);\
		IF_ASSIGN(var, ent, काष्ठा prपूर्णांक_entry, TRACE_PRINT);	\
		IF_ASSIGN(var, ent, काष्ठा bprपूर्णांक_entry, TRACE_BPRINT);	\
		IF_ASSIGN(var, ent, काष्ठा bमाला_दो_entry, TRACE_BPUTS);	\
		IF_ASSIGN(var, ent, काष्ठा hwlat_entry, TRACE_HWLAT);	\
		IF_ASSIGN(var, ent, काष्ठा raw_data_entry, TRACE_RAW_DATA);\
		IF_ASSIGN(var, ent, काष्ठा trace_mmiotrace_rw,		\
			  TRACE_MMIO_RW);				\
		IF_ASSIGN(var, ent, काष्ठा trace_mmiotrace_map,		\
			  TRACE_MMIO_MAP);				\
		IF_ASSIGN(var, ent, काष्ठा trace_branch, TRACE_BRANCH); \
		IF_ASSIGN(var, ent, काष्ठा ftrace_graph_ent_entry,	\
			  TRACE_GRAPH_ENT);		\
		IF_ASSIGN(var, ent, काष्ठा ftrace_graph_ret_entry,	\
			  TRACE_GRAPH_RET);		\
		IF_ASSIGN(var, ent, काष्ठा func_repeats_entry,		\
			  TRACE_FUNC_REPEATS);				\
		__ftrace_bad_type();					\
	पूर्ण जबतक (0)

/*
 * An option specअगरic to a tracer. This is a boolean value.
 * The bit is the bit index that sets its value on the
 * flags value in काष्ठा tracer_flags.
 */
काष्ठा tracer_opt अणु
	स्थिर अक्षर	*name; /* Will appear on the trace_options file */
	u32		bit; /* Mask asचिन्हित in val field in tracer_flags */
पूर्ण;

/*
 * The set of specअगरic options क्रम a tracer. Your tracer
 * have to set the initial value of the flags val.
 */
काष्ठा tracer_flags अणु
	u32			val;
	काष्ठा tracer_opt	*opts;
	काष्ठा tracer		*trace;
पूर्ण;

/* Makes more easy to define a tracer opt */
#घोषणा TRACER_OPT(s, b)	.name = #s, .bit = b


काष्ठा trace_option_dentry अणु
	काष्ठा tracer_opt		*opt;
	काष्ठा tracer_flags		*flags;
	काष्ठा trace_array		*tr;
	काष्ठा dentry			*entry;
पूर्ण;

/**
 * काष्ठा tracer - a specअगरic tracer and its callbacks to पूर्णांकeract with tracefs
 * @name: the name chosen to select it on the available_tracers file
 * @init: called when one चयनes to this tracer (echo name > current_tracer)
 * @reset: called when one चयनes to another tracer
 * @start: called when tracing is unछोड़ोd (echo 1 > tracing_on)
 * @stop: called when tracing is छोड़ोd (echo 0 > tracing_on)
 * @update_thresh: called when tracing_thresh is updated
 * @खोलो: called when the trace file is खोलोed
 * @pipe_खोलो: called when the trace_pipe file is खोलोed
 * @बंद: called when the trace file is released
 * @pipe_बंद: called when the trace_pipe file is released
 * @पढ़ो: override the शेष पढ़ो callback on trace_pipe
 * @splice_पढ़ो: override the शेष splice_पढ़ो callback on trace_pipe
 * @selftest: selftest to run on boot (see trace_selftest.c)
 * @prपूर्णांक_headers: override the first lines that describe your columns
 * @prपूर्णांक_line: callback that prपूर्णांकs a trace
 * @set_flag: संकेतs one of your निजी flags changed (trace_options file)
 * @flags: your निजी flags
 */
काष्ठा tracer अणु
	स्थिर अक्षर		*name;
	पूर्णांक			(*init)(काष्ठा trace_array *tr);
	व्योम			(*reset)(काष्ठा trace_array *tr);
	व्योम			(*start)(काष्ठा trace_array *tr);
	व्योम			(*stop)(काष्ठा trace_array *tr);
	पूर्णांक			(*update_thresh)(काष्ठा trace_array *tr);
	व्योम			(*खोलो)(काष्ठा trace_iterator *iter);
	व्योम			(*pipe_खोलो)(काष्ठा trace_iterator *iter);
	व्योम			(*बंद)(काष्ठा trace_iterator *iter);
	व्योम			(*pipe_बंद)(काष्ठा trace_iterator *iter);
	sमाप_प्रकार			(*पढ़ो)(काष्ठा trace_iterator *iter,
					काष्ठा file *filp, अक्षर __user *ubuf,
					माप_प्रकार cnt, loff_t *ppos);
	sमाप_प्रकार			(*splice_पढ़ो)(काष्ठा trace_iterator *iter,
					       काष्ठा file *filp,
					       loff_t *ppos,
					       काष्ठा pipe_inode_info *pipe,
					       माप_प्रकार len,
					       अचिन्हित पूर्णांक flags);
#अगर_घोषित CONFIG_FTRACE_STARTUP_TEST
	पूर्णांक			(*selftest)(काष्ठा tracer *trace,
					    काष्ठा trace_array *tr);
#पूर्ण_अगर
	व्योम			(*prपूर्णांक_header)(काष्ठा seq_file *m);
	क्रमागत prपूर्णांक_line_t	(*prपूर्णांक_line)(काष्ठा trace_iterator *iter);
	/* If you handled the flag setting, वापस 0 */
	पूर्णांक			(*set_flag)(काष्ठा trace_array *tr,
					    u32 old_flags, u32 bit, पूर्णांक set);
	/* Return 0 अगर OK with change, अन्यथा वापस non-zero */
	पूर्णांक			(*flag_changed)(काष्ठा trace_array *tr,
						u32 mask, पूर्णांक set);
	काष्ठा tracer		*next;
	काष्ठा tracer_flags	*flags;
	पूर्णांक			enabled;
	bool			prपूर्णांक_max;
	bool			allow_instances;
#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	bool			use_max_tr;
#पूर्ण_अगर
	/* True अगर tracer cannot be enabled in kernel param */
	bool			noboot;
पूर्ण;

अटल अंतरभूत काष्ठा ring_buffer_iter *
trace_buffer_iter(काष्ठा trace_iterator *iter, पूर्णांक cpu)
अणु
	वापस iter->buffer_iter ? iter->buffer_iter[cpu] : शून्य;
पूर्ण

पूर्णांक tracer_init(काष्ठा tracer *t, काष्ठा trace_array *tr);
पूर्णांक tracing_is_enabled(व्योम);
व्योम tracing_reset_online_cpus(काष्ठा array_buffer *buf);
व्योम tracing_reset_current(पूर्णांक cpu);
व्योम tracing_reset_all_online_cpus(व्योम);
पूर्णांक tracing_खोलो_generic(काष्ठा inode *inode, काष्ठा file *filp);
पूर्णांक tracing_खोलो_generic_tr(काष्ठा inode *inode, काष्ठा file *filp);
bool tracing_is_disabled(व्योम);
bool tracer_tracing_is_on(काष्ठा trace_array *tr);
व्योम tracer_tracing_on(काष्ठा trace_array *tr);
व्योम tracer_tracing_off(काष्ठा trace_array *tr);
काष्ठा dentry *trace_create_file(स्थिर अक्षर *name,
				 umode_t mode,
				 काष्ठा dentry *parent,
				 व्योम *data,
				 स्थिर काष्ठा file_operations *fops);

पूर्णांक tracing_init_dentry(व्योम);

काष्ठा ring_buffer_event;

काष्ठा ring_buffer_event *
trace_buffer_lock_reserve(काष्ठा trace_buffer *buffer,
			  पूर्णांक type,
			  अचिन्हित दीर्घ len,
			  अचिन्हित पूर्णांक trace_ctx);

काष्ठा trace_entry *tracing_get_trace_entry(काष्ठा trace_array *tr,
						काष्ठा trace_array_cpu *data);

काष्ठा trace_entry *trace_find_next_entry(काष्ठा trace_iterator *iter,
					  पूर्णांक *ent_cpu, u64 *ent_ts);

व्योम trace_buffer_unlock_commit_nostack(काष्ठा trace_buffer *buffer,
					काष्ठा ring_buffer_event *event);

bool trace_is_tracepoपूर्णांक_string(स्थिर अक्षर *str);
स्थिर अक्षर *trace_event_क्रमmat(काष्ठा trace_iterator *iter, स्थिर अक्षर *fmt);
व्योम trace_check_भ_लिखो(काष्ठा trace_iterator *iter, स्थिर अक्षर *fmt,
			 बहु_सूची ap);

पूर्णांक trace_empty(काष्ठा trace_iterator *iter);

व्योम *trace_find_next_entry_inc(काष्ठा trace_iterator *iter);

व्योम trace_init_global_iter(काष्ठा trace_iterator *iter);

व्योम tracing_iter_reset(काष्ठा trace_iterator *iter, पूर्णांक cpu);

अचिन्हित दीर्घ trace_total_entries_cpu(काष्ठा trace_array *tr, पूर्णांक cpu);
अचिन्हित दीर्घ trace_total_entries(काष्ठा trace_array *tr);

व्योम trace_function(काष्ठा trace_array *tr,
		    अचिन्हित दीर्घ ip,
		    अचिन्हित दीर्घ parent_ip,
		    अचिन्हित पूर्णांक trace_ctx);
व्योम trace_graph_function(काष्ठा trace_array *tr,
		    अचिन्हित दीर्घ ip,
		    अचिन्हित दीर्घ parent_ip,
		    अचिन्हित पूर्णांक trace_ctx);
व्योम trace_latency_header(काष्ठा seq_file *m);
व्योम trace_शेष_header(काष्ठा seq_file *m);
व्योम prपूर्णांक_trace_header(काष्ठा seq_file *m, काष्ठा trace_iterator *iter);

व्योम trace_graph_वापस(काष्ठा ftrace_graph_ret *trace);
पूर्णांक trace_graph_entry(काष्ठा ftrace_graph_ent *trace);
व्योम set_graph_array(काष्ठा trace_array *tr);

व्योम tracing_start_cmdline_record(व्योम);
व्योम tracing_stop_cmdline_record(व्योम);
व्योम tracing_start_tgid_record(व्योम);
व्योम tracing_stop_tgid_record(व्योम);

पूर्णांक रेजिस्टर_tracer(काष्ठा tracer *type);
पूर्णांक is_tracing_stopped(व्योम);

loff_t tracing_lseek(काष्ठा file *file, loff_t offset, पूर्णांक whence);

बाह्य cpumask_var_t __पढ़ो_mostly tracing_buffer_mask;

#घोषणा क्रम_each_tracing_cpu(cpu)	\
	क्रम_each_cpu(cpu, tracing_buffer_mask)

बाह्य अचिन्हित दीर्घ nsecs_to_usecs(अचिन्हित दीर्घ nsecs);

बाह्य अचिन्हित दीर्घ tracing_thresh;

/* PID filtering */

बाह्य पूर्णांक pid_max;

bool trace_find_filtered_pid(काष्ठा trace_pid_list *filtered_pids,
			     pid_t search_pid);
bool trace_ignore_this_task(काष्ठा trace_pid_list *filtered_pids,
			    काष्ठा trace_pid_list *filtered_no_pids,
			    काष्ठा task_काष्ठा *task);
व्योम trace_filter_add_हटाओ_task(काष्ठा trace_pid_list *pid_list,
				  काष्ठा task_काष्ठा *self,
				  काष्ठा task_काष्ठा *task);
व्योम *trace_pid_next(काष्ठा trace_pid_list *pid_list, व्योम *v, loff_t *pos);
व्योम *trace_pid_start(काष्ठा trace_pid_list *pid_list, loff_t *pos);
पूर्णांक trace_pid_show(काष्ठा seq_file *m, व्योम *v);
व्योम trace_मुक्त_pid_list(काष्ठा trace_pid_list *pid_list);
पूर्णांक trace_pid_ग_लिखो(काष्ठा trace_pid_list *filtered_pids,
		    काष्ठा trace_pid_list **new_pid_list,
		    स्थिर अक्षर __user *ubuf, माप_प्रकार cnt);

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
व्योम update_max_tr(काष्ठा trace_array *tr, काष्ठा task_काष्ठा *tsk, पूर्णांक cpu,
		   व्योम *cond_data);
व्योम update_max_tr_single(काष्ठा trace_array *tr,
			  काष्ठा task_काष्ठा *tsk, पूर्णांक cpu);
#पूर्ण_अगर /* CONFIG_TRACER_MAX_TRACE */

#अगर (defined(CONFIG_TRACER_MAX_TRACE) || defined(CONFIG_HWLAT_TRACER)) && \
	defined(CONFIG_FSNOTIFY)

व्योम latency_fsnotअगरy(काष्ठा trace_array *tr);

#अन्यथा

अटल अंतरभूत व्योम latency_fsnotअगरy(काष्ठा trace_array *tr) अणु पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_STACKTRACE
व्योम __trace_stack(काष्ठा trace_array *tr, अचिन्हित पूर्णांक trace_ctx, पूर्णांक skip);
#अन्यथा
अटल अंतरभूत व्योम __trace_stack(काष्ठा trace_array *tr, अचिन्हित पूर्णांक trace_ctx,
				 पूर्णांक skip)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_STACKTRACE */

व्योम trace_last_func_repeats(काष्ठा trace_array *tr,
			     काष्ठा trace_func_repeats *last_info,
			     अचिन्हित पूर्णांक trace_ctx);

बाह्य u64 ftrace_now(पूर्णांक cpu);

बाह्य व्योम trace_find_cmdline(पूर्णांक pid, अक्षर comm[]);
बाह्य पूर्णांक trace_find_tgid(पूर्णांक pid);
बाह्य व्योम trace_event_follow_विभाजन(काष्ठा trace_array *tr, bool enable);

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
बाह्य अचिन्हित दीर्घ ftrace_update_tot_cnt;
बाह्य अचिन्हित दीर्घ ftrace_number_of_pages;
बाह्य अचिन्हित दीर्घ ftrace_number_of_groups;
व्योम ftrace_init_trace_array(काष्ठा trace_array *tr);
#अन्यथा
अटल अंतरभूत व्योम ftrace_init_trace_array(काष्ठा trace_array *tr) अणु पूर्ण
#पूर्ण_अगर
#घोषणा DYN_FTRACE_TEST_NAME trace_selftest_dynamic_test_func
बाह्य पूर्णांक DYN_FTRACE_TEST_NAME(व्योम);
#घोषणा DYN_FTRACE_TEST_NAME2 trace_selftest_dynamic_test_func2
बाह्य पूर्णांक DYN_FTRACE_TEST_NAME2(व्योम);

बाह्य bool ring_buffer_expanded;
बाह्य bool tracing_selftest_disabled;

#अगर_घोषित CONFIG_FTRACE_STARTUP_TEST
बाह्य व्योम __init disable_tracing_selftest(स्थिर अक्षर *reason);

बाह्य पूर्णांक trace_selftest_startup_function(काष्ठा tracer *trace,
					   काष्ठा trace_array *tr);
बाह्य पूर्णांक trace_selftest_startup_function_graph(काष्ठा tracer *trace,
						 काष्ठा trace_array *tr);
बाह्य पूर्णांक trace_selftest_startup_irqsoff(काष्ठा tracer *trace,
					  काष्ठा trace_array *tr);
बाह्य पूर्णांक trace_selftest_startup_preemptoff(काष्ठा tracer *trace,
					     काष्ठा trace_array *tr);
बाह्य पूर्णांक trace_selftest_startup_preemptirqsoff(काष्ठा tracer *trace,
						 काष्ठा trace_array *tr);
बाह्य पूर्णांक trace_selftest_startup_wakeup(काष्ठा tracer *trace,
					 काष्ठा trace_array *tr);
बाह्य पूर्णांक trace_selftest_startup_nop(काष्ठा tracer *trace,
					 काष्ठा trace_array *tr);
बाह्य पूर्णांक trace_selftest_startup_branch(काष्ठा tracer *trace,
					 काष्ठा trace_array *tr);
/*
 * Tracer data references selftest functions that only occur
 * on boot up. These can be __init functions. Thus, when selftests
 * are enabled, then the tracers need to reference __init functions.
 */
#घोषणा __tracer_data		__refdata
#अन्यथा
अटल अंतरभूत व्योम __init disable_tracing_selftest(स्थिर अक्षर *reason)
अणु
पूर्ण
/* Tracers are selकरोm changed. Optimize when selftests are disabled. */
#घोषणा __tracer_data		__पढ़ो_mostly
#पूर्ण_अगर /* CONFIG_FTRACE_STARTUP_TEST */

बाह्य व्योम *head_page(काष्ठा trace_array_cpu *data);
बाह्य अचिन्हित दीर्घ दीर्घ ns2usecs(u64 nsec);
बाह्य पूर्णांक
trace_vbprपूर्णांकk(अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, बहु_सूची args);
बाह्य पूर्णांक
trace_vprपूर्णांकk(अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, बहु_सूची args);
बाह्य पूर्णांक
trace_array_vprपूर्णांकk(काष्ठा trace_array *tr,
		    अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, बहु_सूची args);
पूर्णांक trace_array_prपूर्णांकk_buf(काष्ठा trace_buffer *buffer,
			   अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, ...);
व्योम trace_prपूर्णांकk_seq(काष्ठा trace_seq *s);
क्रमागत prपूर्णांक_line_t prपूर्णांक_trace_line(काष्ठा trace_iterator *iter);

बाह्य अक्षर trace_find_mark(अचिन्हित दीर्घ दीर्घ duration);

काष्ठा ftrace_hash;

काष्ठा ftrace_mod_load अणु
	काष्ठा list_head	list;
	अक्षर			*func;
	अक्षर			*module;
	पूर्णांक			 enable;
पूर्ण;

क्रमागत अणु
	FTRACE_HASH_FL_MOD	= (1 << 0),
पूर्ण;

काष्ठा ftrace_hash अणु
	अचिन्हित दीर्घ		size_bits;
	काष्ठा hlist_head	*buckets;
	अचिन्हित दीर्घ		count;
	अचिन्हित दीर्घ		flags;
	काष्ठा rcu_head		rcu;
पूर्ण;

काष्ठा ftrace_func_entry *
ftrace_lookup_ip(काष्ठा ftrace_hash *hash, अचिन्हित दीर्घ ip);

अटल __always_अंतरभूत bool ftrace_hash_empty(काष्ठा ftrace_hash *hash)
अणु
	वापस !hash || !(hash->count || (hash->flags & FTRACE_HASH_FL_MOD));
पूर्ण

/* Standard output क्रमmatting function used क्रम function वापस traces */
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER

/* Flag options */
#घोषणा TRACE_GRAPH_PRINT_OVERRUN       0x1
#घोषणा TRACE_GRAPH_PRINT_CPU           0x2
#घोषणा TRACE_GRAPH_PRINT_OVERHEAD      0x4
#घोषणा TRACE_GRAPH_PRINT_PROC          0x8
#घोषणा TRACE_GRAPH_PRINT_DURATION      0x10
#घोषणा TRACE_GRAPH_PRINT_ABS_TIME      0x20
#घोषणा TRACE_GRAPH_PRINT_REL_TIME      0x40
#घोषणा TRACE_GRAPH_PRINT_IRQS          0x80
#घोषणा TRACE_GRAPH_PRINT_TAIL          0x100
#घोषणा TRACE_GRAPH_SLEEP_TIME          0x200
#घोषणा TRACE_GRAPH_GRAPH_TIME          0x400
#घोषणा TRACE_GRAPH_PRINT_FILL_SHIFT	28
#घोषणा TRACE_GRAPH_PRINT_FILL_MASK	(0x3 << TRACE_GRAPH_PRINT_FILL_SHIFT)

बाह्य व्योम ftrace_graph_sleep_समय_control(bool enable);

#अगर_घोषित CONFIG_FUNCTION_PROखाताR
बाह्य व्योम ftrace_graph_graph_समय_control(bool enable);
#अन्यथा
अटल अंतरभूत व्योम ftrace_graph_graph_समय_control(bool enable) अणु पूर्ण
#पूर्ण_अगर

बाह्य क्रमागत prपूर्णांक_line_t
prपूर्णांक_graph_function_flags(काष्ठा trace_iterator *iter, u32 flags);
बाह्य व्योम prपूर्णांक_graph_headers_flags(काष्ठा seq_file *s, u32 flags);
बाह्य व्योम
trace_prपूर्णांक_graph_duration(अचिन्हित दीर्घ दीर्घ duration, काष्ठा trace_seq *s);
बाह्य व्योम graph_trace_खोलो(काष्ठा trace_iterator *iter);
बाह्य व्योम graph_trace_बंद(काष्ठा trace_iterator *iter);
बाह्य पूर्णांक __trace_graph_entry(काष्ठा trace_array *tr,
			       काष्ठा ftrace_graph_ent *trace,
			       अचिन्हित पूर्णांक trace_ctx);
बाह्य व्योम __trace_graph_वापस(काष्ठा trace_array *tr,
				 काष्ठा ftrace_graph_ret *trace,
				 अचिन्हित पूर्णांक trace_ctx);

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
बाह्य काष्ठा ftrace_hash __rcu *ftrace_graph_hash;
बाह्य काष्ठा ftrace_hash __rcu *ftrace_graph_notrace_hash;

अटल अंतरभूत पूर्णांक ftrace_graph_addr(काष्ठा ftrace_graph_ent *trace)
अणु
	अचिन्हित दीर्घ addr = trace->func;
	पूर्णांक ret = 0;
	काष्ठा ftrace_hash *hash;

	preempt_disable_notrace();

	/*
	 * Have to खोलो code "rcu_dereference_sched()" because the
	 * function graph tracer can be called when RCU is not
	 * "watching".
	 * Protected with schedule_on_each_cpu(ftrace_sync)
	 */
	hash = rcu_dereference_रक्षित(ftrace_graph_hash, !preemptible());

	अगर (ftrace_hash_empty(hash)) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	अगर (ftrace_lookup_ip(hash, addr)) अणु

		/*
		 * This needs to be cleared on the वापस functions
		 * when the depth is zero.
		 */
		trace_recursion_set(TRACE_GRAPH_BIT);
		trace_recursion_set_depth(trace->depth);

		/*
		 * If no irqs are to be traced, but a set_graph_function
		 * is set, and called by an पूर्णांकerrupt handler, we still
		 * want to trace it.
		 */
		अगर (in_irq())
			trace_recursion_set(TRACE_IRQ_BIT);
		अन्यथा
			trace_recursion_clear(TRACE_IRQ_BIT);
		ret = 1;
	पूर्ण

out:
	preempt_enable_notrace();
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम ftrace_graph_addr_finish(काष्ठा ftrace_graph_ret *trace)
अणु
	अगर (trace_recursion_test(TRACE_GRAPH_BIT) &&
	    trace->depth == trace_recursion_depth())
		trace_recursion_clear(TRACE_GRAPH_BIT);
पूर्ण

अटल अंतरभूत पूर्णांक ftrace_graph_notrace_addr(अचिन्हित दीर्घ addr)
अणु
	पूर्णांक ret = 0;
	काष्ठा ftrace_hash *notrace_hash;

	preempt_disable_notrace();

	/*
	 * Have to खोलो code "rcu_dereference_sched()" because the
	 * function graph tracer can be called when RCU is not
	 * "watching".
	 * Protected with schedule_on_each_cpu(ftrace_sync)
	 */
	notrace_hash = rcu_dereference_रक्षित(ftrace_graph_notrace_hash,
						 !preemptible());

	अगर (ftrace_lookup_ip(notrace_hash, addr))
		ret = 1;

	preempt_enable_notrace();
	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक ftrace_graph_addr(काष्ठा ftrace_graph_ent *trace)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक ftrace_graph_notrace_addr(अचिन्हित दीर्घ addr)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ftrace_graph_addr_finish(काष्ठा ftrace_graph_ret *trace)
अणु पूर्ण
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

बाह्य अचिन्हित पूर्णांक fgraph_max_depth;

अटल अंतरभूत bool ftrace_graph_ignore_func(काष्ठा ftrace_graph_ent *trace)
अणु
	/* trace it when it is-nested-in or is a function enabled. */
	वापस !(trace_recursion_test(TRACE_GRAPH_BIT) ||
		 ftrace_graph_addr(trace)) ||
		(trace->depth < 0) ||
		(fgraph_max_depth && trace->depth >= fgraph_max_depth);
पूर्ण

#अन्यथा /* CONFIG_FUNCTION_GRAPH_TRACER */
अटल अंतरभूत क्रमागत prपूर्णांक_line_t
prपूर्णांक_graph_function_flags(काष्ठा trace_iterator *iter, u32 flags)
अणु
	वापस TRACE_TYPE_UNHANDLED;
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */

बाह्य काष्ठा list_head ftrace_pids;

#अगर_घोषित CONFIG_FUNCTION_TRACER

#घोषणा FTRACE_PID_IGNORE	-1
#घोषणा FTRACE_PID_TRACE	-2

काष्ठा ftrace_func_command अणु
	काष्ठा list_head	list;
	अक्षर			*name;
	पूर्णांक			(*func)(काष्ठा trace_array *tr,
					काष्ठा ftrace_hash *hash,
					अक्षर *func, अक्षर *cmd,
					अक्षर *params, पूर्णांक enable);
पूर्ण;
बाह्य bool ftrace_filter_param __initdata;
अटल अंतरभूत पूर्णांक ftrace_trace_task(काष्ठा trace_array *tr)
अणु
	वापस this_cpu_पढ़ो(tr->array_buffer.data->ftrace_ignore_pid) !=
		FTRACE_PID_IGNORE;
पूर्ण
बाह्य पूर्णांक ftrace_is_dead(व्योम);
पूर्णांक ftrace_create_function_files(काष्ठा trace_array *tr,
				 काष्ठा dentry *parent);
व्योम ftrace_destroy_function_files(काष्ठा trace_array *tr);
पूर्णांक ftrace_allocate_ftrace_ops(काष्ठा trace_array *tr);
व्योम ftrace_मुक्त_ftrace_ops(काष्ठा trace_array *tr);
व्योम ftrace_init_global_array_ops(काष्ठा trace_array *tr);
व्योम ftrace_init_array_ops(काष्ठा trace_array *tr, ftrace_func_t func);
व्योम ftrace_reset_array_ops(काष्ठा trace_array *tr);
व्योम ftrace_init_tracefs(काष्ठा trace_array *tr, काष्ठा dentry *d_tracer);
व्योम ftrace_init_tracefs_toplevel(काष्ठा trace_array *tr,
				  काष्ठा dentry *d_tracer);
व्योम ftrace_clear_pids(काष्ठा trace_array *tr);
पूर्णांक init_function_trace(व्योम);
व्योम ftrace_pid_follow_विभाजन(काष्ठा trace_array *tr, bool enable);
#अन्यथा
अटल अंतरभूत पूर्णांक ftrace_trace_task(काष्ठा trace_array *tr)
अणु
	वापस 1;
पूर्ण
अटल अंतरभूत पूर्णांक ftrace_is_dead(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक
ftrace_create_function_files(काष्ठा trace_array *tr,
			     काष्ठा dentry *parent)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक ftrace_allocate_ftrace_ops(काष्ठा trace_array *tr)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ftrace_मुक्त_ftrace_ops(काष्ठा trace_array *tr) अणु पूर्ण
अटल अंतरभूत व्योम ftrace_destroy_function_files(काष्ठा trace_array *tr) अणु पूर्ण
अटल अंतरभूत __init व्योम
ftrace_init_global_array_ops(काष्ठा trace_array *tr) अणु पूर्ण
अटल अंतरभूत व्योम ftrace_reset_array_ops(काष्ठा trace_array *tr) अणु पूर्ण
अटल अंतरभूत व्योम ftrace_init_tracefs(काष्ठा trace_array *tr, काष्ठा dentry *d) अणु पूर्ण
अटल अंतरभूत व्योम ftrace_init_tracefs_toplevel(काष्ठा trace_array *tr, काष्ठा dentry *d) अणु पूर्ण
अटल अंतरभूत व्योम ftrace_clear_pids(काष्ठा trace_array *tr) अणु पूर्ण
अटल अंतरभूत पूर्णांक init_function_trace(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ftrace_pid_follow_विभाजन(काष्ठा trace_array *tr, bool enable) अणु पूर्ण
/* ftace_func_t type is not defined, use macro instead of अटल अंतरभूत */
#घोषणा ftrace_init_array_ops(tr, func) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER */

#अगर defined(CONFIG_FUNCTION_TRACER) && defined(CONFIG_DYNAMIC_FTRACE)

काष्ठा ftrace_probe_ops अणु
	व्योम			(*func)(अचिन्हित दीर्घ ip,
					अचिन्हित दीर्घ parent_ip,
					काष्ठा trace_array *tr,
					काष्ठा ftrace_probe_ops *ops,
					व्योम *data);
	पूर्णांक			(*init)(काष्ठा ftrace_probe_ops *ops,
					काष्ठा trace_array *tr,
					अचिन्हित दीर्घ ip, व्योम *init_data,
					व्योम **data);
	व्योम			(*मुक्त)(काष्ठा ftrace_probe_ops *ops,
					काष्ठा trace_array *tr,
					अचिन्हित दीर्घ ip, व्योम *data);
	पूर्णांक			(*prपूर्णांक)(काष्ठा seq_file *m,
					 अचिन्हित दीर्घ ip,
					 काष्ठा ftrace_probe_ops *ops,
					 व्योम *data);
पूर्ण;

काष्ठा ftrace_func_mapper;
प्रकार पूर्णांक (*ftrace_mapper_func)(व्योम *data);

काष्ठा ftrace_func_mapper *allocate_ftrace_func_mapper(व्योम);
व्योम **ftrace_func_mapper_find_ip(काष्ठा ftrace_func_mapper *mapper,
					   अचिन्हित दीर्घ ip);
पूर्णांक ftrace_func_mapper_add_ip(काष्ठा ftrace_func_mapper *mapper,
			       अचिन्हित दीर्घ ip, व्योम *data);
व्योम *ftrace_func_mapper_हटाओ_ip(काष्ठा ftrace_func_mapper *mapper,
				   अचिन्हित दीर्घ ip);
व्योम मुक्त_ftrace_func_mapper(काष्ठा ftrace_func_mapper *mapper,
			     ftrace_mapper_func मुक्त_func);

बाह्य पूर्णांक
रेजिस्टर_ftrace_function_probe(अक्षर *glob, काष्ठा trace_array *tr,
			       काष्ठा ftrace_probe_ops *ops, व्योम *data);
बाह्य पूर्णांक
unरेजिस्टर_ftrace_function_probe_func(अक्षर *glob, काष्ठा trace_array *tr,
				      काष्ठा ftrace_probe_ops *ops);
बाह्य व्योम clear_ftrace_function_probes(काष्ठा trace_array *tr);

पूर्णांक रेजिस्टर_ftrace_command(काष्ठा ftrace_func_command *cmd);
पूर्णांक unरेजिस्टर_ftrace_command(काष्ठा ftrace_func_command *cmd);

व्योम ftrace_create_filter_files(काष्ठा ftrace_ops *ops,
				काष्ठा dentry *parent);
व्योम ftrace_destroy_filter_files(काष्ठा ftrace_ops *ops);

बाह्य पूर्णांक ftrace_set_filter(काष्ठा ftrace_ops *ops, अचिन्हित अक्षर *buf,
			     पूर्णांक len, पूर्णांक reset);
बाह्य पूर्णांक ftrace_set_notrace(काष्ठा ftrace_ops *ops, अचिन्हित अक्षर *buf,
			      पूर्णांक len, पूर्णांक reset);
#अन्यथा
काष्ठा ftrace_func_command;

अटल अंतरभूत __init पूर्णांक रेजिस्टर_ftrace_command(काष्ठा ftrace_func_command *cmd)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत __init पूर्णांक unरेजिस्टर_ftrace_command(अक्षर *cmd_name)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत व्योम clear_ftrace_function_probes(काष्ठा trace_array *tr)
अणु
पूर्ण

/*
 * The ops parameter passed in is usually undefined.
 * This must be a macro.
 */
#घोषणा ftrace_create_filter_files(ops, parent) करो अणु पूर्ण जबतक (0)
#घोषणा ftrace_destroy_filter_files(ops) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER && CONFIG_DYNAMIC_FTRACE */

bool ftrace_event_is_function(काष्ठा trace_event_call *call);

/*
 * काष्ठा trace_parser - servers क्रम पढ़ोing the user input separated by spaces
 * @cont: set अगर the input is not complete - no final space अक्षर was found
 * @buffer: holds the parsed user input
 * @idx: user input length
 * @size: buffer size
 */
काष्ठा trace_parser अणु
	bool		cont;
	अक्षर		*buffer;
	अचिन्हित	idx;
	अचिन्हित	size;
पूर्ण;

अटल अंतरभूत bool trace_parser_loaded(काष्ठा trace_parser *parser)
अणु
	वापस (parser->idx != 0);
पूर्ण

अटल अंतरभूत bool trace_parser_cont(काष्ठा trace_parser *parser)
अणु
	वापस parser->cont;
पूर्ण

अटल अंतरभूत व्योम trace_parser_clear(काष्ठा trace_parser *parser)
अणु
	parser->cont = false;
	parser->idx = 0;
पूर्ण

बाह्य पूर्णांक trace_parser_get_init(काष्ठा trace_parser *parser, पूर्णांक size);
बाह्य व्योम trace_parser_put(काष्ठा trace_parser *parser);
बाह्य पूर्णांक trace_get_user(काष्ठा trace_parser *parser, स्थिर अक्षर __user *ubuf,
	माप_प्रकार cnt, loff_t *ppos);

/*
 * Only create function graph options अगर function graph is configured.
 */
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
# define FGRAPH_FLAGS						\
		C(DISPLAY_GRAPH,	"display-graph"),
#अन्यथा
# define FGRAPH_FLAGS
#पूर्ण_अगर

#अगर_घोषित CONFIG_BRANCH_TRACER
# define BRANCH_FLAGS					\
		C(BRANCH,		"branch"),
#अन्यथा
# define BRANCH_FLAGS
#पूर्ण_अगर

#अगर_घोषित CONFIG_FUNCTION_TRACER
# define FUNCTION_FLAGS						\
		C(FUNCTION,		"function-trace"),	\
		C(FUNC_FORK,		"function-fork"),
# define FUNCTION_DEFAULT_FLAGS		TRACE_ITER_FUNCTION
#अन्यथा
# define FUNCTION_FLAGS
# define FUNCTION_DEFAULT_FLAGS		0UL
# define TRACE_ITER_FUNC_FORK		0UL
#पूर्ण_अगर

#अगर_घोषित CONFIG_STACKTRACE
# define STACK_FLAGS				\
		C(STACKTRACE,		"stacktrace"),
#अन्यथा
# define STACK_FLAGS
#पूर्ण_अगर

/*
 * trace_iterator_flags is an क्रमागतeration that defines bit
 * positions पूर्णांकo trace_flags that controls the output.
 *
 * NOTE: These bits must match the trace_options array in
 *       trace.c (this macro guarantees it).
 */
#घोषणा TRACE_FLAGS						\
		C(PRINT_PARENT,		"print-parent"),	\
		C(SYM_OFFSET,		"sym-offset"),		\
		C(SYM_ADDR,		"sym-addr"),		\
		C(VERBOSE,		"verbose"),		\
		C(RAW,			"raw"),			\
		C(HEX,			"hex"),			\
		C(BIN,			"bin"),			\
		C(BLOCK,		"block"),		\
		C(PRINTK,		"trace_printk"),	\
		C(ANNOTATE,		"annotate"),		\
		C(USERSTACKTRACE,	"userstacktrace"),	\
		C(SYM_USEROBJ,		"sym-userobj"),		\
		C(PRINTK_MSGONLY,	"printk-msg-only"),	\
		C(CONTEXT_INFO,		"context-info"),   /* Prपूर्णांक pid/cpu/समय */ \
		C(LATENCY_FMT,		"latency-format"),	\
		C(RECORD_CMD,		"record-cmd"),		\
		C(RECORD_TGID,		"record-tgid"),		\
		C(OVERWRITE,		"overwrite"),		\
		C(STOP_ON_FREE,		"disable_on_free"),	\
		C(IRQ_INFO,		"irq-info"),		\
		C(MARKERS,		"markers"),		\
		C(EVENT_FORK,		"event-fork"),		\
		C(PAUSE_ON_TRACE,	"pause-on-trace"),	\
		C(HASH_PTR,		"hash-ptr"),	/* Prपूर्णांक hashed poपूर्णांकer */ \
		FUNCTION_FLAGS					\
		FGRAPH_FLAGS					\
		STACK_FLAGS					\
		BRANCH_FLAGS

/*
 * By defining C, we can make TRACE_FLAGS a list of bit names
 * that will define the bits क्रम the flag masks.
 */
#अघोषित C
#घोषणा C(a, b) TRACE_ITER_##a##_BIT

क्रमागत trace_iterator_bits अणु
	TRACE_FLAGS
	/* Make sure we करोn't go more than we have bits क्रम */
	TRACE_ITER_LAST_BIT
पूर्ण;

/*
 * By redefining C, we can make TRACE_FLAGS a list of masks that
 * use the bits as defined above.
 */
#अघोषित C
#घोषणा C(a, b) TRACE_ITER_##a = (1 << TRACE_ITER_##a##_BIT)

क्रमागत trace_iterator_flags अणु TRACE_FLAGS पूर्ण;

/*
 * TRACE_ITER_SYM_MASK masks the options in trace_flags that
 * control the output of kernel symbols.
 */
#घोषणा TRACE_ITER_SYM_MASK \
	(TRACE_ITER_PRINT_PARENT|TRACE_ITER_SYM_OFFSET|TRACE_ITER_SYM_ADDR)

बाह्य काष्ठा tracer nop_trace;

#अगर_घोषित CONFIG_BRANCH_TRACER
बाह्य पूर्णांक enable_branch_tracing(काष्ठा trace_array *tr);
बाह्य व्योम disable_branch_tracing(व्योम);
अटल अंतरभूत पूर्णांक trace_branch_enable(काष्ठा trace_array *tr)
अणु
	अगर (tr->trace_flags & TRACE_ITER_BRANCH)
		वापस enable_branch_tracing(tr);
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम trace_branch_disable(व्योम)
अणु
	/* due to races, always disable */
	disable_branch_tracing();
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक trace_branch_enable(काष्ठा trace_array *tr)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम trace_branch_disable(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_BRANCH_TRACER */

/* set ring buffers to शेष size अगर not alपढ़ोy करोne so */
पूर्णांक tracing_update_buffers(व्योम);

काष्ठा ftrace_event_field अणु
	काष्ठा list_head	link;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*type;
	पूर्णांक			filter_type;
	पूर्णांक			offset;
	पूर्णांक			size;
	पूर्णांक			is_चिन्हित;
पूर्ण;

काष्ठा prog_entry;

काष्ठा event_filter अणु
	काष्ठा prog_entry __rcu	*prog;
	अक्षर			*filter_string;
पूर्ण;

काष्ठा event_subप्रणाली अणु
	काष्ठा list_head	list;
	स्थिर अक्षर		*name;
	काष्ठा event_filter	*filter;
	पूर्णांक			ref_count;
पूर्ण;

काष्ठा trace_subप्रणाली_dir अणु
	काष्ठा list_head		list;
	काष्ठा event_subप्रणाली		*subप्रणाली;
	काष्ठा trace_array		*tr;
	काष्ठा dentry			*entry;
	पूर्णांक				ref_count;
	पूर्णांक				nr_events;
पूर्ण;

बाह्य पूर्णांक call_filter_check_discard(काष्ठा trace_event_call *call, व्योम *rec,
				     काष्ठा trace_buffer *buffer,
				     काष्ठा ring_buffer_event *event);

व्योम trace_buffer_unlock_commit_regs(काष्ठा trace_array *tr,
				     काष्ठा trace_buffer *buffer,
				     काष्ठा ring_buffer_event *event,
				     अचिन्हित पूर्णांक trcace_ctx,
				     काष्ठा pt_regs *regs);

अटल अंतरभूत व्योम trace_buffer_unlock_commit(काष्ठा trace_array *tr,
					      काष्ठा trace_buffer *buffer,
					      काष्ठा ring_buffer_event *event,
					      अचिन्हित पूर्णांक trace_ctx)
अणु
	trace_buffer_unlock_commit_regs(tr, buffer, event, trace_ctx, शून्य);
पूर्ण

DECLARE_PER_CPU(काष्ठा ring_buffer_event *, trace_buffered_event);
DECLARE_PER_CPU(पूर्णांक, trace_buffered_event_cnt);
व्योम trace_buffered_event_disable(व्योम);
व्योम trace_buffered_event_enable(व्योम);

अटल अंतरभूत व्योम
__trace_event_discard_commit(काष्ठा trace_buffer *buffer,
			     काष्ठा ring_buffer_event *event)
अणु
	अगर (this_cpu_पढ़ो(trace_buffered_event) == event) अणु
		/* Simply release the temp buffer */
		this_cpu_dec(trace_buffered_event_cnt);
		वापस;
	पूर्ण
	ring_buffer_discard_commit(buffer, event);
पूर्ण

/*
 * Helper function क्रम event_trigger_unlock_commitअणु_regsपूर्ण().
 * If there are event triggers attached to this event that requires
 * filtering against its fields, then they will be called as the
 * entry alपढ़ोy holds the field inक्रमmation of the current event.
 *
 * It also checks अगर the event should be discarded or not.
 * It is to be discarded अगर the event is soft disabled and the
 * event was only recorded to process triggers, or अगर the event
 * filter is active and this event did not match the filters.
 *
 * Returns true अगर the event is discarded, false otherwise.
 */
अटल अंतरभूत bool
__event_trigger_test_discard(काष्ठा trace_event_file *file,
			     काष्ठा trace_buffer *buffer,
			     काष्ठा ring_buffer_event *event,
			     व्योम *entry,
			     क्रमागत event_trigger_type *tt)
अणु
	अचिन्हित दीर्घ eflags = file->flags;

	अगर (eflags & EVENT_खाता_FL_TRIGGER_COND)
		*tt = event_triggers_call(file, buffer, entry, event);

	अगर (test_bit(EVENT_खाता_FL_SOFT_DISABLED_BIT, &file->flags) ||
	    (unlikely(file->flags & EVENT_खाता_FL_FILTERED) &&
	     !filter_match_preds(file->filter, entry))) अणु
		__trace_event_discard_commit(buffer, event);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * event_trigger_unlock_commit - handle triggers and finish event commit
 * @file: The file poपूर्णांकer associated with the event
 * @buffer: The ring buffer that the event is being written to
 * @event: The event meta data in the ring buffer
 * @entry: The event itself
 * @trace_ctx: The tracing context flags.
 *
 * This is a helper function to handle triggers that require data
 * from the event itself. It also tests the event against filters and
 * अगर the event is soft disabled and should be discarded.
 */
अटल अंतरभूत व्योम
event_trigger_unlock_commit(काष्ठा trace_event_file *file,
			    काष्ठा trace_buffer *buffer,
			    काष्ठा ring_buffer_event *event,
			    व्योम *entry, अचिन्हित पूर्णांक trace_ctx)
अणु
	क्रमागत event_trigger_type tt = ETT_NONE;

	अगर (!__event_trigger_test_discard(file, buffer, event, entry, &tt))
		trace_buffer_unlock_commit(file->tr, buffer, event, trace_ctx);

	अगर (tt)
		event_triggers_post_call(file, tt);
पूर्ण

/**
 * event_trigger_unlock_commit_regs - handle triggers and finish event commit
 * @file: The file poपूर्णांकer associated with the event
 * @buffer: The ring buffer that the event is being written to
 * @event: The event meta data in the ring buffer
 * @entry: The event itself
 * @trace_ctx: The tracing context flags.
 *
 * This is a helper function to handle triggers that require data
 * from the event itself. It also tests the event against filters and
 * अगर the event is soft disabled and should be discarded.
 *
 * Same as event_trigger_unlock_commit() but calls
 * trace_buffer_unlock_commit_regs() instead of trace_buffer_unlock_commit().
 */
अटल अंतरभूत व्योम
event_trigger_unlock_commit_regs(काष्ठा trace_event_file *file,
				 काष्ठा trace_buffer *buffer,
				 काष्ठा ring_buffer_event *event,
				 व्योम *entry, अचिन्हित पूर्णांक trace_ctx,
				 काष्ठा pt_regs *regs)
अणु
	क्रमागत event_trigger_type tt = ETT_NONE;

	अगर (!__event_trigger_test_discard(file, buffer, event, entry, &tt))
		trace_buffer_unlock_commit_regs(file->tr, buffer, event,
						trace_ctx, regs);

	अगर (tt)
		event_triggers_post_call(file, tt);
पूर्ण

#घोषणा FILTER_PRED_INVALID	((अचिन्हित लघु)-1)
#घोषणा FILTER_PRED_IS_RIGHT	(1 << 15)
#घोषणा FILTER_PRED_FOLD	(1 << 15)

/*
 * The max preds is the size of अचिन्हित लघु with
 * two flags at the MSBs. One bit is used क्रम both the IS_RIGHT
 * and FOLD flags. The other is reserved.
 *
 * 2^14 preds is way more than enough.
 */
#घोषणा MAX_FILTER_PRED		16384

काष्ठा filter_pred;
काष्ठा regex;

प्रकार पूर्णांक (*filter_pred_fn_t) (काष्ठा filter_pred *pred, व्योम *event);

प्रकार पूर्णांक (*regex_match_func)(अक्षर *str, काष्ठा regex *r, पूर्णांक len);

क्रमागत regex_type अणु
	MATCH_FULL = 0,
	MATCH_FRONT_ONLY,
	MATCH_MIDDLE_ONLY,
	MATCH_END_ONLY,
	MATCH_GLOB,
	MATCH_INDEX,
पूर्ण;

काष्ठा regex अणु
	अक्षर			pattern[MAX_FILTER_STR_VAL];
	पूर्णांक			len;
	पूर्णांक			field_len;
	regex_match_func	match;
पूर्ण;

काष्ठा filter_pred अणु
	filter_pred_fn_t 	fn;
	u64 			val;
	काष्ठा regex		regex;
	अचिन्हित लघु		*ops;
	काष्ठा ftrace_event_field *field;
	पूर्णांक 			offset;
	पूर्णांक			not;
	पूर्णांक 			op;
पूर्ण;

अटल अंतरभूत bool is_string_field(काष्ठा ftrace_event_field *field)
अणु
	वापस field->filter_type == FILTER_DYN_STRING ||
	       field->filter_type == FILTER_STATIC_STRING ||
	       field->filter_type == FILTER_PTR_STRING ||
	       field->filter_type == FILTER_COMM;
पूर्ण

अटल अंतरभूत bool is_function_field(काष्ठा ftrace_event_field *field)
अणु
	वापस field->filter_type == FILTER_TRACE_FN;
पूर्ण

बाह्य क्रमागत regex_type
filter_parse_regex(अक्षर *buff, पूर्णांक len, अक्षर **search, पूर्णांक *not);
बाह्य व्योम prपूर्णांक_event_filter(काष्ठा trace_event_file *file,
			       काष्ठा trace_seq *s);
बाह्य पूर्णांक apply_event_filter(काष्ठा trace_event_file *file,
			      अक्षर *filter_string);
बाह्य पूर्णांक apply_subप्रणाली_event_filter(काष्ठा trace_subप्रणाली_dir *dir,
					अक्षर *filter_string);
बाह्य व्योम prपूर्णांक_subप्रणाली_event_filter(काष्ठा event_subप्रणाली *प्रणाली,
					 काष्ठा trace_seq *s);
बाह्य पूर्णांक filter_assign_type(स्थिर अक्षर *type);
बाह्य पूर्णांक create_event_filter(काष्ठा trace_array *tr,
			       काष्ठा trace_event_call *call,
			       अक्षर *filter_str, bool set_str,
			       काष्ठा event_filter **filterp);
बाह्य व्योम मुक्त_event_filter(काष्ठा event_filter *filter);

काष्ठा ftrace_event_field *
trace_find_event_field(काष्ठा trace_event_call *call, अक्षर *name);

बाह्य व्योम trace_event_enable_cmd_record(bool enable);
बाह्य व्योम trace_event_enable_tgid_record(bool enable);

बाह्य पूर्णांक event_trace_init(व्योम);
बाह्य पूर्णांक event_trace_add_tracer(काष्ठा dentry *parent, काष्ठा trace_array *tr);
बाह्य पूर्णांक event_trace_del_tracer(काष्ठा trace_array *tr);
बाह्य व्योम __trace_early_add_events(काष्ठा trace_array *tr);

बाह्य काष्ठा trace_event_file *__find_event_file(काष्ठा trace_array *tr,
						  स्थिर अक्षर *प्रणाली,
						  स्थिर अक्षर *event);
बाह्य काष्ठा trace_event_file *find_event_file(काष्ठा trace_array *tr,
						स्थिर अक्षर *प्रणाली,
						स्थिर अक्षर *event);

अटल अंतरभूत व्योम *event_file_data(काष्ठा file *filp)
अणु
	वापस READ_ONCE(file_inode(filp)->i_निजी);
पूर्ण

बाह्य काष्ठा mutex event_mutex;
बाह्य काष्ठा list_head ftrace_events;

बाह्य स्थिर काष्ठा file_operations event_trigger_fops;
बाह्य स्थिर काष्ठा file_operations event_hist_fops;
बाह्य स्थिर काष्ठा file_operations event_hist_debug_fops;
बाह्य स्थिर काष्ठा file_operations event_inject_fops;

#अगर_घोषित CONFIG_HIST_TRIGGERS
बाह्य पूर्णांक रेजिस्टर_trigger_hist_cmd(व्योम);
बाह्य पूर्णांक रेजिस्टर_trigger_hist_enable_disable_cmds(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक रेजिस्टर_trigger_hist_cmd(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक रेजिस्टर_trigger_hist_enable_disable_cmds(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक रेजिस्टर_trigger_cmds(व्योम);
बाह्य व्योम clear_event_triggers(काष्ठा trace_array *tr);

काष्ठा event_trigger_data अणु
	अचिन्हित दीर्घ			count;
	पूर्णांक				ref;
	काष्ठा event_trigger_ops	*ops;
	काष्ठा event_command		*cmd_ops;
	काष्ठा event_filter __rcu	*filter;
	अक्षर				*filter_str;
	व्योम				*निजी_data;
	bool				छोड़ोd;
	bool				छोड़ोd_पंचांगp;
	काष्ठा list_head		list;
	अक्षर				*name;
	काष्ठा list_head		named_list;
	काष्ठा event_trigger_data	*named_data;
पूर्ण;

/* Aव्योम typos */
#घोषणा ENABLE_EVENT_STR	"enable_event"
#घोषणा DISABLE_EVENT_STR	"disable_event"
#घोषणा ENABLE_HIST_STR		"enable_hist"
#घोषणा DISABLE_HIST_STR	"disable_hist"

काष्ठा enable_trigger_data अणु
	काष्ठा trace_event_file		*file;
	bool				enable;
	bool				hist;
पूर्ण;

बाह्य पूर्णांक event_enable_trigger_prपूर्णांक(काष्ठा seq_file *m,
				      काष्ठा event_trigger_ops *ops,
				      काष्ठा event_trigger_data *data);
बाह्य व्योम event_enable_trigger_मुक्त(काष्ठा event_trigger_ops *ops,
				      काष्ठा event_trigger_data *data);
बाह्य पूर्णांक event_enable_trigger_func(काष्ठा event_command *cmd_ops,
				     काष्ठा trace_event_file *file,
				     अक्षर *glob, अक्षर *cmd, अक्षर *param);
बाह्य पूर्णांक event_enable_रेजिस्टर_trigger(अक्षर *glob,
					 काष्ठा event_trigger_ops *ops,
					 काष्ठा event_trigger_data *data,
					 काष्ठा trace_event_file *file);
बाह्य व्योम event_enable_unरेजिस्टर_trigger(अक्षर *glob,
					    काष्ठा event_trigger_ops *ops,
					    काष्ठा event_trigger_data *test,
					    काष्ठा trace_event_file *file);
बाह्य व्योम trigger_data_मुक्त(काष्ठा event_trigger_data *data);
बाह्य पूर्णांक event_trigger_init(काष्ठा event_trigger_ops *ops,
			      काष्ठा event_trigger_data *data);
बाह्य पूर्णांक trace_event_trigger_enable_disable(काष्ठा trace_event_file *file,
					      पूर्णांक trigger_enable);
बाह्य व्योम update_cond_flag(काष्ठा trace_event_file *file);
बाह्य पूर्णांक set_trigger_filter(अक्षर *filter_str,
			      काष्ठा event_trigger_data *trigger_data,
			      काष्ठा trace_event_file *file);
बाह्य काष्ठा event_trigger_data *find_named_trigger(स्थिर अक्षर *name);
बाह्य bool is_named_trigger(काष्ठा event_trigger_data *test);
बाह्य पूर्णांक save_named_trigger(स्थिर अक्षर *name,
			      काष्ठा event_trigger_data *data);
बाह्य व्योम del_named_trigger(काष्ठा event_trigger_data *data);
बाह्य व्योम छोड़ो_named_trigger(काष्ठा event_trigger_data *data);
बाह्य व्योम unछोड़ो_named_trigger(काष्ठा event_trigger_data *data);
बाह्य व्योम set_named_trigger_data(काष्ठा event_trigger_data *data,
				   काष्ठा event_trigger_data *named_data);
बाह्य काष्ठा event_trigger_data *
get_named_trigger_data(काष्ठा event_trigger_data *data);
बाह्य पूर्णांक रेजिस्टर_event_command(काष्ठा event_command *cmd);
बाह्य पूर्णांक unरेजिस्टर_event_command(काष्ठा event_command *cmd);
बाह्य पूर्णांक रेजिस्टर_trigger_hist_enable_disable_cmds(व्योम);

/**
 * काष्ठा event_trigger_ops - callbacks क्रम trace event triggers
 *
 * The methods in this काष्ठाure provide per-event trigger hooks क्रम
 * various trigger operations.
 *
 * All the methods below, except क्रम @init() and @मुक्त(), must be
 * implemented.
 *
 * @func: The trigger 'probe' function called when the triggering
 *	event occurs.  The data passed पूर्णांकo this callback is the data
 *	that was supplied to the event_command @reg() function that
 *	रेजिस्टरed the trigger (see काष्ठा event_command) aदीर्घ with
 *	the trace record, rec.
 *
 * @init: An optional initialization function called क्रम the trigger
 *	when the trigger is रेजिस्टरed (via the event_command reg()
 *	function).  This can be used to perक्रमm per-trigger
 *	initialization such as incrementing a per-trigger reference
 *	count, क्रम instance.  This is usually implemented by the
 *	generic utility function @event_trigger_init() (see
 *	trace_event_triggers.c).
 *
 * @मुक्त: An optional de-initialization function called क्रम the
 *	trigger when the trigger is unरेजिस्टरed (via the
 *	event_command @reg() function).  This can be used to perक्रमm
 *	per-trigger de-initialization such as decrementing a
 *	per-trigger reference count and मुक्तing corresponding trigger
 *	data, क्रम instance.  This is usually implemented by the
 *	generic utility function @event_trigger_मुक्त() (see
 *	trace_event_triggers.c).
 *
 * @prपूर्णांक: The callback function invoked to have the trigger prपूर्णांक
 *	itself.  This is usually implemented by a wrapper function
 *	that calls the generic utility function @event_trigger_prपूर्णांक()
 *	(see trace_event_triggers.c).
 */
काष्ठा event_trigger_ops अणु
	व्योम			(*func)(काष्ठा event_trigger_data *data,
					काष्ठा trace_buffer *buffer, व्योम *rec,
					काष्ठा ring_buffer_event *rbe);
	पूर्णांक			(*init)(काष्ठा event_trigger_ops *ops,
					काष्ठा event_trigger_data *data);
	व्योम			(*मुक्त)(काष्ठा event_trigger_ops *ops,
					काष्ठा event_trigger_data *data);
	पूर्णांक			(*prपूर्णांक)(काष्ठा seq_file *m,
					 काष्ठा event_trigger_ops *ops,
					 काष्ठा event_trigger_data *data);
पूर्ण;

/**
 * काष्ठा event_command - callbacks and data members क्रम event commands
 *
 * Event commands are invoked by users by writing the command name
 * पूर्णांकo the 'trigger' file associated with a trace event.  The
 * parameters associated with a specअगरic invocation of an event
 * command are used to create an event trigger instance, which is
 * added to the list of trigger instances associated with that trace
 * event.  When the event is hit, the set of triggers associated with
 * that event is invoked.
 *
 * The data members in this काष्ठाure provide per-event command data
 * क्रम various event commands.
 *
 * All the data members below, except क्रम @post_trigger, must be set
 * क्रम each event command.
 *
 * @name: The unique name that identअगरies the event command.  This is
 *	the name used when setting triggers via trigger files.
 *
 * @trigger_type: A unique id that identअगरies the event command
 *	'type'.  This value has two purposes, the first to ensure that
 *	only one trigger of the same type can be set at a given समय
 *	क्रम a particular event e.g. it करोesn't make sense to have both
 *	a traceon and traceoff trigger attached to a single event at
 *	the same समय, so traceon and traceoff have the same type
 *	though they have dअगरferent names.  The @trigger_type value is
 *	also used as a bit value क्रम deferring the actual trigger
 *	action until after the current event is finished.  Some
 *	commands need to करो this अगर they themselves log to the trace
 *	buffer (see the @post_trigger() member below).  @trigger_type
 *	values are defined by adding new values to the trigger_type
 *	क्रमागत in include/linux/trace_events.h.
 *
 * @flags: See the क्रमागत event_command_flags below.
 *
 * All the methods below, except क्रम @set_filter() and @unreg_all(),
 * must be implemented.
 *
 * @func: The callback function responsible क्रम parsing and
 *	रेजिस्टरing the trigger written to the 'trigger' file by the
 *	user.  It allocates the trigger instance and रेजिस्टरs it with
 *	the appropriate trace event.  It makes use of the other
 *	event_command callback functions to orchestrate this, and is
 *	usually implemented by the generic utility function
 *	@event_trigger_callback() (see trace_event_triggers.c).
 *
 * @reg: Adds the trigger to the list of triggers associated with the
 *	event, and enables the event trigger itself, after
 *	initializing it (via the event_trigger_ops @init() function).
 *	This is also where commands can use the @trigger_type value to
 *	make the decision as to whether or not multiple instances of
 *	the trigger should be allowed.  This is usually implemented by
 *	the generic utility function @रेजिस्टर_trigger() (see
 *	trace_event_triggers.c).
 *
 * @unreg: Removes the trigger from the list of triggers associated
 *	with the event, and disables the event trigger itself, after
 *	initializing it (via the event_trigger_ops @मुक्त() function).
 *	This is usually implemented by the generic utility function
 *	@unरेजिस्टर_trigger() (see trace_event_triggers.c).
 *
 * @unreg_all: An optional function called to हटाओ all the triggers
 *	from the list of triggers associated with the event.  Called
 *	when a trigger file is खोलोed in truncate mode.
 *
 * @set_filter: An optional function called to parse and set a filter
 *	क्रम the trigger.  If no @set_filter() method is set क्रम the
 *	event command, filters set by the user क्रम the command will be
 *	ignored.  This is usually implemented by the generic utility
 *	function @set_trigger_filter() (see trace_event_triggers.c).
 *
 * @get_trigger_ops: The callback function invoked to retrieve the
 *	event_trigger_ops implementation associated with the command.
 */
काष्ठा event_command अणु
	काष्ठा list_head	list;
	अक्षर			*name;
	क्रमागत event_trigger_type	trigger_type;
	पूर्णांक			flags;
	पूर्णांक			(*func)(काष्ठा event_command *cmd_ops,
					काष्ठा trace_event_file *file,
					अक्षर *glob, अक्षर *cmd, अक्षर *params);
	पूर्णांक			(*reg)(अक्षर *glob,
				       काष्ठा event_trigger_ops *ops,
				       काष्ठा event_trigger_data *data,
				       काष्ठा trace_event_file *file);
	व्योम			(*unreg)(अक्षर *glob,
					 काष्ठा event_trigger_ops *ops,
					 काष्ठा event_trigger_data *data,
					 काष्ठा trace_event_file *file);
	व्योम			(*unreg_all)(काष्ठा trace_event_file *file);
	पूर्णांक			(*set_filter)(अक्षर *filter_str,
					      काष्ठा event_trigger_data *data,
					      काष्ठा trace_event_file *file);
	काष्ठा event_trigger_ops *(*get_trigger_ops)(अक्षर *cmd, अक्षर *param);
पूर्ण;

/**
 * क्रमागत event_command_flags - flags क्रम काष्ठा event_command
 *
 * @POST_TRIGGER: A flag that says whether or not this command needs
 *	to have its action delayed until after the current event has
 *	been बंदd.  Some triggers need to aव्योम being invoked जबतक
 *	an event is currently in the process of being logged, since
 *	the trigger may itself log data पूर्णांकo the trace buffer.  Thus
 *	we make sure the current event is committed beक्रमe invoking
 *	those triggers.  To करो that, the trigger invocation is split
 *	in two - the first part checks the filter using the current
 *	trace record; अगर a command has the @post_trigger flag set, it
 *	sets a bit क्रम itself in the वापस value, otherwise it
 *	directly invokes the trigger.  Once all commands have been
 *	either invoked or set their वापस flag, the current record is
 *	either committed or discarded.  At that poपूर्णांक, अगर any commands
 *	have deferred their triggers, those commands are finally
 *	invoked following the बंद of the current event.  In other
 *	words, अगर the event_trigger_ops @func() probe implementation
 *	itself logs to the trace buffer, this flag should be set,
 *	otherwise it can be left unspecअगरied.
 *
 * @NEEDS_REC: A flag that says whether or not this command needs
 *	access to the trace record in order to perक्रमm its function,
 *	regardless of whether or not it has a filter associated with
 *	it (filters make a trigger require access to the trace record
 *	but are not always present).
 */
क्रमागत event_command_flags अणु
	EVENT_CMD_FL_POST_TRIGGER	= 1,
	EVENT_CMD_FL_NEEDS_REC		= 2,
पूर्ण;

अटल अंतरभूत bool event_command_post_trigger(काष्ठा event_command *cmd_ops)
अणु
	वापस cmd_ops->flags & EVENT_CMD_FL_POST_TRIGGER;
पूर्ण

अटल अंतरभूत bool event_command_needs_rec(काष्ठा event_command *cmd_ops)
अणु
	वापस cmd_ops->flags & EVENT_CMD_FL_NEEDS_REC;
पूर्ण

बाह्य पूर्णांक trace_event_enable_disable(काष्ठा trace_event_file *file,
				      पूर्णांक enable, पूर्णांक soft_disable);
बाह्य पूर्णांक tracing_alloc_snapshot(व्योम);
बाह्य व्योम tracing_snapshot_cond(काष्ठा trace_array *tr, व्योम *cond_data);
बाह्य पूर्णांक tracing_snapshot_cond_enable(काष्ठा trace_array *tr, व्योम *cond_data, cond_update_fn_t update);

बाह्य पूर्णांक tracing_snapshot_cond_disable(काष्ठा trace_array *tr);
बाह्य व्योम *tracing_cond_snapshot_data(काष्ठा trace_array *tr);

बाह्य स्थिर अक्षर *__start___trace_bprपूर्णांकk_fmt[];
बाह्य स्थिर अक्षर *__stop___trace_bprपूर्णांकk_fmt[];

बाह्य स्थिर अक्षर *__start___tracepoपूर्णांक_str[];
बाह्य स्थिर अक्षर *__stop___tracepoपूर्णांक_str[];

व्योम trace_prपूर्णांकk_control(bool enabled);
व्योम trace_prपूर्णांकk_start_comm(व्योम);
पूर्णांक trace_keep_overग_लिखो(काष्ठा tracer *tracer, u32 mask, पूर्णांक set);
पूर्णांक set_tracer_flag(काष्ठा trace_array *tr, अचिन्हित पूर्णांक mask, पूर्णांक enabled);

/* Used from boot समय tracer */
बाह्य पूर्णांक trace_set_options(काष्ठा trace_array *tr, अक्षर *option);
बाह्य पूर्णांक tracing_set_tracer(काष्ठा trace_array *tr, स्थिर अक्षर *buf);
बाह्य sमाप_प्रकार tracing_resize_ring_buffer(काष्ठा trace_array *tr,
					  अचिन्हित दीर्घ size, पूर्णांक cpu_id);
बाह्य पूर्णांक tracing_set_cpumask(काष्ठा trace_array *tr,
				cpumask_var_t tracing_cpumask_new);


#घोषणा MAX_EVENT_NAME_LEN	64

बाह्य sमाप_प्रकार trace_parse_run_command(काष्ठा file *file,
		स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos,
		पूर्णांक (*createfn)(स्थिर अक्षर *));

बाह्य अचिन्हित पूर्णांक err_pos(अक्षर *cmd, स्थिर अक्षर *str);
बाह्य व्योम tracing_log_err(काष्ठा trace_array *tr,
			    स्थिर अक्षर *loc, स्थिर अक्षर *cmd,
			    स्थिर अक्षर **errs, u8 type, u8 pos);

/*
 * Normal trace_prपूर्णांकk() and मित्रs allocates special buffers
 * to करो the manipulation, as well as saves the prपूर्णांक क्रमmats
 * पूर्णांकo sections to display. But the trace infraकाष्ठाure wants
 * to use these without the added overhead at the price of being
 * a bit slower (used मुख्यly क्रम warnings, where we करोn't care
 * about perक्रमmance). The पूर्णांकernal_trace_माला_दो() is क्रम such
 * a purpose.
 */
#घोषणा पूर्णांकernal_trace_माला_दो(str) __trace_माला_दो(_THIS_IP_, str, म_माप(str))

#अघोषित FTRACE_ENTRY
#घोषणा FTRACE_ENTRY(call, काष्ठा_name, id, tकाष्ठा, prपूर्णांक)	\
	बाह्य काष्ठा trace_event_call					\
	__aligned(4) event_##call;
#अघोषित FTRACE_ENTRY_DUP
#घोषणा FTRACE_ENTRY_DUP(call, काष्ठा_name, id, tकाष्ठा, prपूर्णांक)	\
	FTRACE_ENTRY(call, काष्ठा_name, id, PARAMS(tकाष्ठा), PARAMS(prपूर्णांक))
#अघोषित FTRACE_ENTRY_PACKED
#घोषणा FTRACE_ENTRY_PACKED(call, काष्ठा_name, id, tकाष्ठा, prपूर्णांक) \
	FTRACE_ENTRY(call, काष्ठा_name, id, PARAMS(tकाष्ठा), PARAMS(prपूर्णांक))

#समावेश "trace_entries.h"

#अगर defined(CONFIG_PERF_EVENTS) && defined(CONFIG_FUNCTION_TRACER)
पूर्णांक perf_ftrace_event_रेजिस्टर(काष्ठा trace_event_call *call,
			       क्रमागत trace_reg type, व्योम *data);
#अन्यथा
#घोषणा perf_ftrace_event_रेजिस्टर शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_FTRACE_SYSCALLS
व्योम init_ftrace_syscalls(व्योम);
स्थिर अक्षर *get_syscall_name(पूर्णांक syscall);
#अन्यथा
अटल अंतरभूत व्योम init_ftrace_syscalls(व्योम) अणु पूर्ण
अटल अंतरभूत स्थिर अक्षर *get_syscall_name(पूर्णांक syscall)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_EVENT_TRACING
व्योम trace_event_init(व्योम);
व्योम trace_event_eval_update(काष्ठा trace_eval_map **map, पूर्णांक len);
/* Used from boot समय tracer */
बाह्य पूर्णांक ftrace_set_clr_event(काष्ठा trace_array *tr, अक्षर *buf, पूर्णांक set);
बाह्य पूर्णांक trigger_process_regex(काष्ठा trace_event_file *file, अक्षर *buff);
#अन्यथा
अटल अंतरभूत व्योम __init trace_event_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम trace_event_eval_update(काष्ठा trace_eval_map **map, पूर्णांक len) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRACER_SNAPSHOT
व्योम tracing_snapshot_instance(काष्ठा trace_array *tr);
पूर्णांक tracing_alloc_snapshot_instance(काष्ठा trace_array *tr);
#अन्यथा
अटल अंतरभूत व्योम tracing_snapshot_instance(काष्ठा trace_array *tr) अणु पूर्ण
अटल अंतरभूत पूर्णांक tracing_alloc_snapshot_instance(काष्ठा trace_array *tr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PREEMPT_TRACER
व्योम tracer_preempt_on(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1);
व्योम tracer_preempt_off(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1);
#अन्यथा
अटल अंतरभूत व्योम tracer_preempt_on(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1) अणु पूर्ण
अटल अंतरभूत व्योम tracer_preempt_off(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1) अणु पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_IRQSOFF_TRACER
व्योम tracer_hardirqs_on(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1);
व्योम tracer_hardirqs_off(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1);
#अन्यथा
अटल अंतरभूत व्योम tracer_hardirqs_on(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1) अणु पूर्ण
अटल अंतरभूत व्योम tracer_hardirqs_off(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1) अणु पूर्ण
#पूर्ण_अगर

बाह्य काष्ठा trace_iterator *tracepoपूर्णांक_prपूर्णांक_iter;

/*
 * Reset the state of the trace_iterator so that it can पढ़ो consumed data.
 * Normally, the trace_iterator is used क्रम पढ़ोing the data when it is not
 * consumed, and must retain state.
 */
अटल __always_अंतरभूत व्योम trace_iterator_reset(काष्ठा trace_iterator *iter)
अणु
	स्थिर माप_प्रकार offset = दुरत्व(काष्ठा trace_iterator, seq);

	/*
	 * Keep gcc from complaining about overwriting more than just one
	 * member in the काष्ठाure.
	 */
	स_रखो((अक्षर *)iter + offset, 0, माप(काष्ठा trace_iterator) - offset);

	iter->pos = -1;
पूर्ण

/* Check the name is good क्रम event/group/fields */
अटल अंतरभूत bool is_good_name(स्थिर अक्षर *name)
अणु
	अगर (!है_अक्षर(*name) && *name != '_')
		वापस false;
	जबतक (*++name != '\0') अणु
		अगर (!है_अक्षर(*name) && !है_अंक(*name) && *name != '_')
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

#पूर्ण_अगर /* _LINUX_KERNEL_TRACE_H */
