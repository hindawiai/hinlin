<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *
 * Function graph tracer.
 * Copyright (c) 2008-2009 Frederic Weisbecker <fweisbec@gmail.com>
 * Mostly borrowed from function tracer which
 * is Copyright (c) Steven Rostedt <srostedt@redhat.com>
 *
 */
#समावेश <linux/uaccess.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>

#समावेश "trace.h"
#समावेश "trace_output.h"

/* When set, irq functions will be ignored */
अटल पूर्णांक ftrace_graph_skip_irqs;

काष्ठा fgraph_cpu_data अणु
	pid_t		last_pid;
	पूर्णांक		depth;
	पूर्णांक		depth_irq;
	पूर्णांक		ignore;
	अचिन्हित दीर्घ	enter_funcs[FTRACE_RETFUNC_DEPTH];
पूर्ण;

काष्ठा fgraph_data अणु
	काष्ठा fgraph_cpu_data __percpu *cpu_data;

	/* Place to preserve last processed entry. */
	काष्ठा ftrace_graph_ent_entry	ent;
	काष्ठा ftrace_graph_ret_entry	ret;
	पूर्णांक				failed;
	पूर्णांक				cpu;
पूर्ण;

#घोषणा TRACE_GRAPH_INDENT	2

अचिन्हित पूर्णांक fgraph_max_depth;

अटल काष्ठा tracer_opt trace_opts[] = अणु
	/* Display overruns? (क्रम self-debug purpose) */
	अणु TRACER_OPT(funcgraph-overrun, TRACE_GRAPH_PRINT_OVERRUN) पूर्ण,
	/* Display CPU ? */
	अणु TRACER_OPT(funcgraph-cpu, TRACE_GRAPH_PRINT_CPU) पूर्ण,
	/* Display Overhead ? */
	अणु TRACER_OPT(funcgraph-overhead, TRACE_GRAPH_PRINT_OVERHEAD) पूर्ण,
	/* Display proc name/pid */
	अणु TRACER_OPT(funcgraph-proc, TRACE_GRAPH_PRINT_PROC) पूर्ण,
	/* Display duration of execution */
	अणु TRACER_OPT(funcgraph-duration, TRACE_GRAPH_PRINT_DURATION) पूर्ण,
	/* Display असलolute समय of an entry */
	अणु TRACER_OPT(funcgraph-असलसमय, TRACE_GRAPH_PRINT_ABS_TIME) पूर्ण,
	/* Display पूर्णांकerrupts */
	अणु TRACER_OPT(funcgraph-irqs, TRACE_GRAPH_PRINT_IRQS) पूर्ण,
	/* Display function name after trailing पूर्ण */
	अणु TRACER_OPT(funcgraph-tail, TRACE_GRAPH_PRINT_TAIL) पूर्ण,
	/* Include sleep समय (scheduled out) between entry and वापस */
	अणु TRACER_OPT(sleep-समय, TRACE_GRAPH_SLEEP_TIME) पूर्ण,

#अगर_घोषित CONFIG_FUNCTION_PROखाताR
	/* Include समय within nested functions */
	अणु TRACER_OPT(graph-समय, TRACE_GRAPH_GRAPH_TIME) पूर्ण,
#पूर्ण_अगर

	अणु पूर्ण /* Empty entry */
पूर्ण;

अटल काष्ठा tracer_flags tracer_flags = अणु
	/* Don't display overruns, proc, or tail by शेष */
	.val = TRACE_GRAPH_PRINT_CPU | TRACE_GRAPH_PRINT_OVERHEAD |
	       TRACE_GRAPH_PRINT_DURATION | TRACE_GRAPH_PRINT_IRQS |
	       TRACE_GRAPH_SLEEP_TIME | TRACE_GRAPH_GRAPH_TIME,
	.opts = trace_opts
पूर्ण;

अटल काष्ठा trace_array *graph_array;

/*
 * DURATION column is being also used to display IRQ signs,
 * following values are used by prपूर्णांक_graph_irq and others
 * to fill in space पूर्णांकo DURATION column.
 */
क्रमागत अणु
	FLAGS_FILL_FULL  = 1 << TRACE_GRAPH_PRINT_FILL_SHIFT,
	FLAGS_FILL_START = 2 << TRACE_GRAPH_PRINT_FILL_SHIFT,
	FLAGS_FILL_END   = 3 << TRACE_GRAPH_PRINT_FILL_SHIFT,
पूर्ण;

अटल व्योम
prपूर्णांक_graph_duration(काष्ठा trace_array *tr, अचिन्हित दीर्घ दीर्घ duration,
		     काष्ठा trace_seq *s, u32 flags);

पूर्णांक __trace_graph_entry(काष्ठा trace_array *tr,
				काष्ठा ftrace_graph_ent *trace,
				अचिन्हित पूर्णांक trace_ctx)
अणु
	काष्ठा trace_event_call *call = &event_funcgraph_entry;
	काष्ठा ring_buffer_event *event;
	काष्ठा trace_buffer *buffer = tr->array_buffer.buffer;
	काष्ठा ftrace_graph_ent_entry *entry;

	event = trace_buffer_lock_reserve(buffer, TRACE_GRAPH_ENT,
					  माप(*entry), trace_ctx);
	अगर (!event)
		वापस 0;
	entry	= ring_buffer_event_data(event);
	entry->graph_ent			= *trace;
	अगर (!call_filter_check_discard(call, entry, buffer, event))
		trace_buffer_unlock_commit_nostack(buffer, event);

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक ftrace_graph_ignore_irqs(व्योम)
अणु
	अगर (!ftrace_graph_skip_irqs || trace_recursion_test(TRACE_IRQ_BIT))
		वापस 0;

	वापस in_irq();
पूर्ण

पूर्णांक trace_graph_entry(काष्ठा ftrace_graph_ent *trace)
अणु
	काष्ठा trace_array *tr = graph_array;
	काष्ठा trace_array_cpu *data;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक trace_ctx;
	दीर्घ disabled;
	पूर्णांक ret;
	पूर्णांक cpu;

	अगर (trace_recursion_test(TRACE_GRAPH_NOTRACE_BIT))
		वापस 0;

	/*
	 * Do not trace a function अगर it's filtered by set_graph_notrace.
	 * Make the index of ret stack negative to indicate that it should
	 * ignore further functions.  But it needs its own ret stack entry
	 * to recover the original index in order to जारी tracing after
	 * वापसing from the function.
	 */
	अगर (ftrace_graph_notrace_addr(trace->func)) अणु
		trace_recursion_set(TRACE_GRAPH_NOTRACE_BIT);
		/*
		 * Need to वापस 1 to have the वापस called
		 * that will clear the NOTRACE bit.
		 */
		वापस 1;
	पूर्ण

	अगर (!ftrace_trace_task(tr))
		वापस 0;

	अगर (ftrace_graph_ignore_func(trace))
		वापस 0;

	अगर (ftrace_graph_ignore_irqs())
		वापस 0;

	/*
	 * Stop here अगर tracing_threshold is set. We only ग_लिखो function वापस
	 * events to the ring buffer.
	 */
	अगर (tracing_thresh)
		वापस 1;

	local_irq_save(flags);
	cpu = raw_smp_processor_id();
	data = per_cpu_ptr(tr->array_buffer.data, cpu);
	disabled = atomic_inc_वापस(&data->disabled);
	अगर (likely(disabled == 1)) अणु
		trace_ctx = tracing_gen_ctx_flags(flags);
		ret = __trace_graph_entry(tr, trace, trace_ctx);
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	atomic_dec(&data->disabled);
	local_irq_restore(flags);

	वापस ret;
पूर्ण

अटल व्योम
__trace_graph_function(काष्ठा trace_array *tr,
		अचिन्हित दीर्घ ip, अचिन्हित पूर्णांक trace_ctx)
अणु
	u64 समय = trace_घड़ी_local();
	काष्ठा ftrace_graph_ent ent = अणु
		.func  = ip,
		.depth = 0,
	पूर्ण;
	काष्ठा ftrace_graph_ret ret = अणु
		.func     = ip,
		.depth    = 0,
		.callसमय = समय,
		.retसमय  = समय,
	पूर्ण;

	__trace_graph_entry(tr, &ent, trace_ctx);
	__trace_graph_वापस(tr, &ret, trace_ctx);
पूर्ण

व्योम
trace_graph_function(काष्ठा trace_array *tr,
		अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		अचिन्हित पूर्णांक trace_ctx)
अणु
	__trace_graph_function(tr, ip, trace_ctx);
पूर्ण

व्योम __trace_graph_वापस(काष्ठा trace_array *tr,
				काष्ठा ftrace_graph_ret *trace,
				अचिन्हित पूर्णांक trace_ctx)
अणु
	काष्ठा trace_event_call *call = &event_funcgraph_निकास;
	काष्ठा ring_buffer_event *event;
	काष्ठा trace_buffer *buffer = tr->array_buffer.buffer;
	काष्ठा ftrace_graph_ret_entry *entry;

	event = trace_buffer_lock_reserve(buffer, TRACE_GRAPH_RET,
					  माप(*entry), trace_ctx);
	अगर (!event)
		वापस;
	entry	= ring_buffer_event_data(event);
	entry->ret				= *trace;
	अगर (!call_filter_check_discard(call, entry, buffer, event))
		trace_buffer_unlock_commit_nostack(buffer, event);
पूर्ण

व्योम trace_graph_वापस(काष्ठा ftrace_graph_ret *trace)
अणु
	काष्ठा trace_array *tr = graph_array;
	काष्ठा trace_array_cpu *data;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक trace_ctx;
	दीर्घ disabled;
	पूर्णांक cpu;

	ftrace_graph_addr_finish(trace);

	अगर (trace_recursion_test(TRACE_GRAPH_NOTRACE_BIT)) अणु
		trace_recursion_clear(TRACE_GRAPH_NOTRACE_BIT);
		वापस;
	पूर्ण

	local_irq_save(flags);
	cpu = raw_smp_processor_id();
	data = per_cpu_ptr(tr->array_buffer.data, cpu);
	disabled = atomic_inc_वापस(&data->disabled);
	अगर (likely(disabled == 1)) अणु
		trace_ctx = tracing_gen_ctx_flags(flags);
		__trace_graph_वापस(tr, trace, trace_ctx);
	पूर्ण
	atomic_dec(&data->disabled);
	local_irq_restore(flags);
पूर्ण

व्योम set_graph_array(काष्ठा trace_array *tr)
अणु
	graph_array = tr;

	/* Make graph_array visible beक्रमe we start tracing */

	smp_mb();
पूर्ण

अटल व्योम trace_graph_thresh_वापस(काष्ठा ftrace_graph_ret *trace)
अणु
	ftrace_graph_addr_finish(trace);

	अगर (trace_recursion_test(TRACE_GRAPH_NOTRACE_BIT)) अणु
		trace_recursion_clear(TRACE_GRAPH_NOTRACE_BIT);
		वापस;
	पूर्ण

	अगर (tracing_thresh &&
	    (trace->retसमय - trace->callसमय < tracing_thresh))
		वापस;
	अन्यथा
		trace_graph_वापस(trace);
पूर्ण

अटल काष्ठा fgraph_ops funcgraph_thresh_ops = अणु
	.entryfunc = &trace_graph_entry,
	.retfunc = &trace_graph_thresh_वापस,
पूर्ण;

अटल काष्ठा fgraph_ops funcgraph_ops = अणु
	.entryfunc = &trace_graph_entry,
	.retfunc = &trace_graph_वापस,
पूर्ण;

अटल पूर्णांक graph_trace_init(काष्ठा trace_array *tr)
अणु
	पूर्णांक ret;

	set_graph_array(tr);
	अगर (tracing_thresh)
		ret = रेजिस्टर_ftrace_graph(&funcgraph_thresh_ops);
	अन्यथा
		ret = रेजिस्टर_ftrace_graph(&funcgraph_ops);
	अगर (ret)
		वापस ret;
	tracing_start_cmdline_record();

	वापस 0;
पूर्ण

अटल व्योम graph_trace_reset(काष्ठा trace_array *tr)
अणु
	tracing_stop_cmdline_record();
	अगर (tracing_thresh)
		unरेजिस्टर_ftrace_graph(&funcgraph_thresh_ops);
	अन्यथा
		unरेजिस्टर_ftrace_graph(&funcgraph_ops);
पूर्ण

अटल पूर्णांक graph_trace_update_thresh(काष्ठा trace_array *tr)
अणु
	graph_trace_reset(tr);
	वापस graph_trace_init(tr);
पूर्ण

अटल पूर्णांक max_bytes_क्रम_cpu;

अटल व्योम prपूर्णांक_graph_cpu(काष्ठा trace_seq *s, पूर्णांक cpu)
अणु
	/*
	 * Start with a space अक्षरacter - to make it stand out
	 * to the right a bit when trace output is pasted पूर्णांकo
	 * email:
	 */
	trace_seq_म_लिखो(s, " %*d) ", max_bytes_क्रम_cpu, cpu);
पूर्ण

#घोषणा TRACE_GRAPH_PROCINFO_LENGTH	14

अटल व्योम prपूर्णांक_graph_proc(काष्ठा trace_seq *s, pid_t pid)
अणु
	अक्षर comm[TASK_COMM_LEN];
	/* sign + log10(MAX_INT) + '\0' */
	अक्षर pid_str[11];
	पूर्णांक spaces = 0;
	पूर्णांक len;
	पूर्णांक i;

	trace_find_cmdline(pid, comm);
	comm[7] = '\0';
	प्र_लिखो(pid_str, "%d", pid);

	/* 1 stands क्रम the "-" अक्षरacter */
	len = म_माप(comm) + म_माप(pid_str) + 1;

	अगर (len < TRACE_GRAPH_PROCINFO_LENGTH)
		spaces = TRACE_GRAPH_PROCINFO_LENGTH - len;

	/* First spaces to align center */
	क्रम (i = 0; i < spaces / 2; i++)
		trace_seq_अ_दो(s, ' ');

	trace_seq_म_लिखो(s, "%s-%s", comm, pid_str);

	/* Last spaces to align center */
	क्रम (i = 0; i < spaces - (spaces / 2); i++)
		trace_seq_अ_दो(s, ' ');
पूर्ण


अटल व्योम prपूर्णांक_graph_lat_fmt(काष्ठा trace_seq *s, काष्ठा trace_entry *entry)
अणु
	trace_seq_अ_दो(s, ' ');
	trace_prपूर्णांक_lat_fmt(s, entry);
	trace_seq_माला_दो(s, " | ");
पूर्ण

/* If the pid changed since the last trace, output this event */
अटल व्योम
verअगर_pid(काष्ठा trace_seq *s, pid_t pid, पूर्णांक cpu, काष्ठा fgraph_data *data)
अणु
	pid_t prev_pid;
	pid_t *last_pid;

	अगर (!data)
		वापस;

	last_pid = &(per_cpu_ptr(data->cpu_data, cpu)->last_pid);

	अगर (*last_pid == pid)
		वापस;

	prev_pid = *last_pid;
	*last_pid = pid;

	अगर (prev_pid == -1)
		वापस;
/*
 * Context-चयन trace line:

 ------------------------------------------
 | 1)  migration/0--1  =>  sshd-1755
 ------------------------------------------

 */
	trace_seq_माला_दो(s, " ------------------------------------------\n");
	prपूर्णांक_graph_cpu(s, cpu);
	prपूर्णांक_graph_proc(s, prev_pid);
	trace_seq_माला_दो(s, " => ");
	prपूर्णांक_graph_proc(s, pid);
	trace_seq_माला_दो(s, "\n ------------------------------------------\n\n");
पूर्ण

अटल काष्ठा ftrace_graph_ret_entry *
get_वापस_क्रम_leaf(काष्ठा trace_iterator *iter,
		काष्ठा ftrace_graph_ent_entry *curr)
अणु
	काष्ठा fgraph_data *data = iter->निजी;
	काष्ठा ring_buffer_iter *ring_iter = शून्य;
	काष्ठा ring_buffer_event *event;
	काष्ठा ftrace_graph_ret_entry *next;

	/*
	 * If the previous output failed to ग_लिखो to the seq buffer,
	 * then we just reuse the data from beक्रमe.
	 */
	अगर (data && data->failed) अणु
		curr = &data->ent;
		next = &data->ret;
	पूर्ण अन्यथा अणु

		ring_iter = trace_buffer_iter(iter, iter->cpu);

		/* First peek to compare current entry and the next one */
		अगर (ring_iter)
			event = ring_buffer_iter_peek(ring_iter, शून्य);
		अन्यथा अणु
			/*
			 * We need to consume the current entry to see
			 * the next one.
			 */
			ring_buffer_consume(iter->array_buffer->buffer, iter->cpu,
					    शून्य, शून्य);
			event = ring_buffer_peek(iter->array_buffer->buffer, iter->cpu,
						 शून्य, शून्य);
		पूर्ण

		अगर (!event)
			वापस शून्य;

		next = ring_buffer_event_data(event);

		अगर (data) अणु
			/*
			 * Save current and next entries क्रम later reference
			 * अगर the output fails.
			 */
			data->ent = *curr;
			/*
			 * If the next event is not a वापस type, then
			 * we only care about what type it is. Otherwise we can
			 * safely copy the entire event.
			 */
			अगर (next->ent.type == TRACE_GRAPH_RET)
				data->ret = *next;
			अन्यथा
				data->ret.ent.type = next->ent.type;
		पूर्ण
	पूर्ण

	अगर (next->ent.type != TRACE_GRAPH_RET)
		वापस शून्य;

	अगर (curr->ent.pid != next->ent.pid ||
			curr->graph_ent.func != next->ret.func)
		वापस शून्य;

	/* this is a leaf, now advance the iterator */
	अगर (ring_iter)
		ring_buffer_iter_advance(ring_iter);

	वापस next;
पूर्ण

अटल व्योम prपूर्णांक_graph_असल_समय(u64 t, काष्ठा trace_seq *s)
अणु
	अचिन्हित दीर्घ usecs_rem;

	usecs_rem = करो_भाग(t, NSEC_PER_SEC);
	usecs_rem /= 1000;

	trace_seq_म_लिखो(s, "%5lu.%06lu |  ",
			 (अचिन्हित दीर्घ)t, usecs_rem);
पूर्ण

अटल व्योम
prपूर्णांक_graph_rel_समय(काष्ठा trace_iterator *iter, काष्ठा trace_seq *s)
अणु
	अचिन्हित दीर्घ दीर्घ usecs;

	usecs = iter->ts - iter->array_buffer->समय_start;
	करो_भाग(usecs, NSEC_PER_USEC);

	trace_seq_म_लिखो(s, "%9llu us |  ", usecs);
पूर्ण

अटल व्योम
prपूर्णांक_graph_irq(काष्ठा trace_iterator *iter, अचिन्हित दीर्घ addr,
		क्रमागत trace_type type, पूर्णांक cpu, pid_t pid, u32 flags)
अणु
	काष्ठा trace_array *tr = iter->tr;
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा trace_entry *ent = iter->ent;

	अगर (addr < (अचिन्हित दीर्घ)__irqentry_text_start ||
		addr >= (अचिन्हित दीर्घ)__irqentry_text_end)
		वापस;

	अगर (tr->trace_flags & TRACE_ITER_CONTEXT_INFO) अणु
		/* Absolute समय */
		अगर (flags & TRACE_GRAPH_PRINT_ABS_TIME)
			prपूर्णांक_graph_असल_समय(iter->ts, s);

		/* Relative समय */
		अगर (flags & TRACE_GRAPH_PRINT_REL_TIME)
			prपूर्णांक_graph_rel_समय(iter, s);

		/* Cpu */
		अगर (flags & TRACE_GRAPH_PRINT_CPU)
			prपूर्णांक_graph_cpu(s, cpu);

		/* Proc */
		अगर (flags & TRACE_GRAPH_PRINT_PROC) अणु
			prपूर्णांक_graph_proc(s, pid);
			trace_seq_माला_दो(s, " | ");
		पूर्ण

		/* Latency क्रमmat */
		अगर (tr->trace_flags & TRACE_ITER_LATENCY_FMT)
			prपूर्णांक_graph_lat_fmt(s, ent);
	पूर्ण

	/* No overhead */
	prपूर्णांक_graph_duration(tr, 0, s, flags | FLAGS_FILL_START);

	अगर (type == TRACE_GRAPH_ENT)
		trace_seq_माला_दो(s, "==========>");
	अन्यथा
		trace_seq_माला_दो(s, "<==========");

	prपूर्णांक_graph_duration(tr, 0, s, flags | FLAGS_FILL_END);
	trace_seq_अ_दो(s, '\n');
पूर्ण

व्योम
trace_prपूर्णांक_graph_duration(अचिन्हित दीर्घ दीर्घ duration, काष्ठा trace_seq *s)
अणु
	अचिन्हित दीर्घ nsecs_rem = करो_भाग(duration, 1000);
	/* log10(अच_दीर्घ_उच्च) + '\0' */
	अक्षर usecs_str[21];
	अक्षर nsecs_str[5];
	पूर्णांक len;
	पूर्णांक i;

	प्र_लिखो(usecs_str, "%lu", (अचिन्हित दीर्घ) duration);

	/* Prपूर्णांक msecs */
	trace_seq_म_लिखो(s, "%s", usecs_str);

	len = म_माप(usecs_str);

	/* Prपूर्णांक nsecs (we करोn't want to exceed 7 numbers) */
	अगर (len < 7) अणु
		माप_प्रकार slen = min_t(माप_प्रकार, माप(nsecs_str), 8UL - len);

		snम_लिखो(nsecs_str, slen, "%03lu", nsecs_rem);
		trace_seq_म_लिखो(s, ".%s", nsecs_str);
		len += म_माप(nsecs_str) + 1;
	पूर्ण

	trace_seq_माला_दो(s, " us ");

	/* Prपूर्णांक reमुख्यing spaces to fit the row's width */
	क्रम (i = len; i < 8; i++)
		trace_seq_अ_दो(s, ' ');
पूर्ण

अटल व्योम
prपूर्णांक_graph_duration(काष्ठा trace_array *tr, अचिन्हित दीर्घ दीर्घ duration,
		     काष्ठा trace_seq *s, u32 flags)
अणु
	अगर (!(flags & TRACE_GRAPH_PRINT_DURATION) ||
	    !(tr->trace_flags & TRACE_ITER_CONTEXT_INFO))
		वापस;

	/* No real adata, just filling the column with spaces */
	चयन (flags & TRACE_GRAPH_PRINT_FILL_MASK) अणु
	हाल FLAGS_FILL_FULL:
		trace_seq_माला_दो(s, "              |  ");
		वापस;
	हाल FLAGS_FILL_START:
		trace_seq_माला_दो(s, "  ");
		वापस;
	हाल FLAGS_FILL_END:
		trace_seq_माला_दो(s, " |");
		वापस;
	पूर्ण

	/* Signal a overhead of समय execution to the output */
	अगर (flags & TRACE_GRAPH_PRINT_OVERHEAD)
		trace_seq_म_लिखो(s, "%c ", trace_find_mark(duration));
	अन्यथा
		trace_seq_माला_दो(s, "  ");

	trace_prपूर्णांक_graph_duration(duration, s);
	trace_seq_माला_दो(s, "|  ");
पूर्ण

/* Case of a leaf function on its call entry */
अटल क्रमागत prपूर्णांक_line_t
prपूर्णांक_graph_entry_leaf(काष्ठा trace_iterator *iter,
		काष्ठा ftrace_graph_ent_entry *entry,
		काष्ठा ftrace_graph_ret_entry *ret_entry,
		काष्ठा trace_seq *s, u32 flags)
अणु
	काष्ठा fgraph_data *data = iter->निजी;
	काष्ठा trace_array *tr = iter->tr;
	काष्ठा ftrace_graph_ret *graph_ret;
	काष्ठा ftrace_graph_ent *call;
	अचिन्हित दीर्घ दीर्घ duration;
	पूर्णांक cpu = iter->cpu;
	पूर्णांक i;

	graph_ret = &ret_entry->ret;
	call = &entry->graph_ent;
	duration = graph_ret->retसमय - graph_ret->callसमय;

	अगर (data) अणु
		काष्ठा fgraph_cpu_data *cpu_data;

		cpu_data = per_cpu_ptr(data->cpu_data, cpu);

		/*
		 * Comments display at + 1 to depth. Since
		 * this is a leaf function, keep the comments
		 * equal to this depth.
		 */
		cpu_data->depth = call->depth - 1;

		/* No need to keep this function around क्रम this depth */
		अगर (call->depth < FTRACE_RETFUNC_DEPTH &&
		    !WARN_ON_ONCE(call->depth < 0))
			cpu_data->enter_funcs[call->depth] = 0;
	पूर्ण

	/* Overhead and duration */
	prपूर्णांक_graph_duration(tr, duration, s, flags);

	/* Function */
	क्रम (i = 0; i < call->depth * TRACE_GRAPH_INDENT; i++)
		trace_seq_अ_दो(s, ' ');

	trace_seq_म_लिखो(s, "%ps();\n", (व्योम *)call->func);

	prपूर्णांक_graph_irq(iter, graph_ret->func, TRACE_GRAPH_RET,
			cpu, iter->ent->pid, flags);

	वापस trace_handle_वापस(s);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t
prपूर्णांक_graph_entry_nested(काष्ठा trace_iterator *iter,
			 काष्ठा ftrace_graph_ent_entry *entry,
			 काष्ठा trace_seq *s, पूर्णांक cpu, u32 flags)
अणु
	काष्ठा ftrace_graph_ent *call = &entry->graph_ent;
	काष्ठा fgraph_data *data = iter->निजी;
	काष्ठा trace_array *tr = iter->tr;
	पूर्णांक i;

	अगर (data) अणु
		काष्ठा fgraph_cpu_data *cpu_data;
		पूर्णांक cpu = iter->cpu;

		cpu_data = per_cpu_ptr(data->cpu_data, cpu);
		cpu_data->depth = call->depth;

		/* Save this function poपूर्णांकer to see अगर the निकास matches */
		अगर (call->depth < FTRACE_RETFUNC_DEPTH &&
		    !WARN_ON_ONCE(call->depth < 0))
			cpu_data->enter_funcs[call->depth] = call->func;
	पूर्ण

	/* No समय */
	prपूर्णांक_graph_duration(tr, 0, s, flags | FLAGS_FILL_FULL);

	/* Function */
	क्रम (i = 0; i < call->depth * TRACE_GRAPH_INDENT; i++)
		trace_seq_अ_दो(s, ' ');

	trace_seq_म_लिखो(s, "%ps() {\n", (व्योम *)call->func);

	अगर (trace_seq_has_overflowed(s))
		वापस TRACE_TYPE_PARTIAL_LINE;

	/*
	 * we alपढ़ोy consumed the current entry to check the next one
	 * and see अगर this is a leaf.
	 */
	वापस TRACE_TYPE_NO_CONSUME;
पूर्ण

अटल व्योम
prपूर्णांक_graph_prologue(काष्ठा trace_iterator *iter, काष्ठा trace_seq *s,
		     पूर्णांक type, अचिन्हित दीर्घ addr, u32 flags)
अणु
	काष्ठा fgraph_data *data = iter->निजी;
	काष्ठा trace_entry *ent = iter->ent;
	काष्ठा trace_array *tr = iter->tr;
	पूर्णांक cpu = iter->cpu;

	/* Pid */
	verअगर_pid(s, ent->pid, cpu, data);

	अगर (type)
		/* Interrupt */
		prपूर्णांक_graph_irq(iter, addr, type, cpu, ent->pid, flags);

	अगर (!(tr->trace_flags & TRACE_ITER_CONTEXT_INFO))
		वापस;

	/* Absolute समय */
	अगर (flags & TRACE_GRAPH_PRINT_ABS_TIME)
		prपूर्णांक_graph_असल_समय(iter->ts, s);

	/* Relative समय */
	अगर (flags & TRACE_GRAPH_PRINT_REL_TIME)
		prपूर्णांक_graph_rel_समय(iter, s);

	/* Cpu */
	अगर (flags & TRACE_GRAPH_PRINT_CPU)
		prपूर्णांक_graph_cpu(s, cpu);

	/* Proc */
	अगर (flags & TRACE_GRAPH_PRINT_PROC) अणु
		prपूर्णांक_graph_proc(s, ent->pid);
		trace_seq_माला_दो(s, " | ");
	पूर्ण

	/* Latency क्रमmat */
	अगर (tr->trace_flags & TRACE_ITER_LATENCY_FMT)
		prपूर्णांक_graph_lat_fmt(s, ent);

	वापस;
पूर्ण

/*
 * Entry check क्रम irq code
 *
 * वापसs 1 अगर
 *  - we are inside irq code
 *  - we just entered irq code
 *
 * वापसs 0 अगर
 *  - funcgraph-पूर्णांकerrupts option is set
 *  - we are not inside irq code
 */
अटल पूर्णांक
check_irq_entry(काष्ठा trace_iterator *iter, u32 flags,
		अचिन्हित दीर्घ addr, पूर्णांक depth)
अणु
	पूर्णांक cpu = iter->cpu;
	पूर्णांक *depth_irq;
	काष्ठा fgraph_data *data = iter->निजी;

	/*
	 * If we are either displaying irqs, or we got called as
	 * a graph event and निजी data करोes not exist,
	 * then we bypass the irq check.
	 */
	अगर ((flags & TRACE_GRAPH_PRINT_IRQS) ||
	    (!data))
		वापस 0;

	depth_irq = &(per_cpu_ptr(data->cpu_data, cpu)->depth_irq);

	/*
	 * We are inside the irq code
	 */
	अगर (*depth_irq >= 0)
		वापस 1;

	अगर ((addr < (अचिन्हित दीर्घ)__irqentry_text_start) ||
	    (addr >= (अचिन्हित दीर्घ)__irqentry_text_end))
		वापस 0;

	/*
	 * We are entering irq code.
	 */
	*depth_irq = depth;
	वापस 1;
पूर्ण

/*
 * Return check क्रम irq code
 *
 * वापसs 1 अगर
 *  - we are inside irq code
 *  - we just left irq code
 *
 * वापसs 0 अगर
 *  - funcgraph-पूर्णांकerrupts option is set
 *  - we are not inside irq code
 */
अटल पूर्णांक
check_irq_वापस(काष्ठा trace_iterator *iter, u32 flags, पूर्णांक depth)
अणु
	पूर्णांक cpu = iter->cpu;
	पूर्णांक *depth_irq;
	काष्ठा fgraph_data *data = iter->निजी;

	/*
	 * If we are either displaying irqs, or we got called as
	 * a graph event and निजी data करोes not exist,
	 * then we bypass the irq check.
	 */
	अगर ((flags & TRACE_GRAPH_PRINT_IRQS) ||
	    (!data))
		वापस 0;

	depth_irq = &(per_cpu_ptr(data->cpu_data, cpu)->depth_irq);

	/*
	 * We are not inside the irq code.
	 */
	अगर (*depth_irq == -1)
		वापस 0;

	/*
	 * We are inside the irq code, and this is वापसing entry.
	 * Let's not trace it and clear the entry depth, since
	 * we are out of irq code.
	 *
	 * This condition ensures that we 'leave the irq code' once
	 * we are out of the entry depth. Thus protecting us from
	 * the RETURN entry loss.
	 */
	अगर (*depth_irq >= depth) अणु
		*depth_irq = -1;
		वापस 1;
	पूर्ण

	/*
	 * We are inside the irq code, and this is not the entry.
	 */
	वापस 1;
पूर्ण

अटल क्रमागत prपूर्णांक_line_t
prपूर्णांक_graph_entry(काष्ठा ftrace_graph_ent_entry *field, काष्ठा trace_seq *s,
			काष्ठा trace_iterator *iter, u32 flags)
अणु
	काष्ठा fgraph_data *data = iter->निजी;
	काष्ठा ftrace_graph_ent *call = &field->graph_ent;
	काष्ठा ftrace_graph_ret_entry *leaf_ret;
	अटल क्रमागत prपूर्णांक_line_t ret;
	पूर्णांक cpu = iter->cpu;

	अगर (check_irq_entry(iter, flags, call->func, call->depth))
		वापस TRACE_TYPE_HANDLED;

	prपूर्णांक_graph_prologue(iter, s, TRACE_GRAPH_ENT, call->func, flags);

	leaf_ret = get_वापस_क्रम_leaf(iter, field);
	अगर (leaf_ret)
		ret = prपूर्णांक_graph_entry_leaf(iter, field, leaf_ret, s, flags);
	अन्यथा
		ret = prपूर्णांक_graph_entry_nested(iter, field, s, cpu, flags);

	अगर (data) अणु
		/*
		 * If we failed to ग_लिखो our output, then we need to make
		 * note of it. Because we alपढ़ोy consumed our entry.
		 */
		अगर (s->full) अणु
			data->failed = 1;
			data->cpu = cpu;
		पूर्ण अन्यथा
			data->failed = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत prपूर्णांक_line_t
prपूर्णांक_graph_वापस(काष्ठा ftrace_graph_ret *trace, काष्ठा trace_seq *s,
		   काष्ठा trace_entry *ent, काष्ठा trace_iterator *iter,
		   u32 flags)
अणु
	अचिन्हित दीर्घ दीर्घ duration = trace->retसमय - trace->callसमय;
	काष्ठा fgraph_data *data = iter->निजी;
	काष्ठा trace_array *tr = iter->tr;
	pid_t pid = ent->pid;
	पूर्णांक cpu = iter->cpu;
	पूर्णांक func_match = 1;
	पूर्णांक i;

	अगर (check_irq_वापस(iter, flags, trace->depth))
		वापस TRACE_TYPE_HANDLED;

	अगर (data) अणु
		काष्ठा fgraph_cpu_data *cpu_data;
		पूर्णांक cpu = iter->cpu;

		cpu_data = per_cpu_ptr(data->cpu_data, cpu);

		/*
		 * Comments display at + 1 to depth. This is the
		 * वापस from a function, we now want the comments
		 * to display at the same level of the bracket.
		 */
		cpu_data->depth = trace->depth - 1;

		अगर (trace->depth < FTRACE_RETFUNC_DEPTH &&
		    !WARN_ON_ONCE(trace->depth < 0)) अणु
			अगर (cpu_data->enter_funcs[trace->depth] != trace->func)
				func_match = 0;
			cpu_data->enter_funcs[trace->depth] = 0;
		पूर्ण
	पूर्ण

	prपूर्णांक_graph_prologue(iter, s, 0, 0, flags);

	/* Overhead and duration */
	prपूर्णांक_graph_duration(tr, duration, s, flags);

	/* Closing brace */
	क्रम (i = 0; i < trace->depth * TRACE_GRAPH_INDENT; i++)
		trace_seq_अ_दो(s, ' ');

	/*
	 * If the वापस function करोes not have a matching entry,
	 * then the entry was lost. Instead of just prपूर्णांकing
	 * the '}' and letting the user guess what function this
	 * beदीर्घs to, ग_लिखो out the function name. Always करो
	 * that अगर the funcgraph-tail option is enabled.
	 */
	अगर (func_match && !(flags & TRACE_GRAPH_PRINT_TAIL))
		trace_seq_माला_दो(s, "}\n");
	अन्यथा
		trace_seq_म_लिखो(s, "} /* %ps */\n", (व्योम *)trace->func);

	/* Overrun */
	अगर (flags & TRACE_GRAPH_PRINT_OVERRUN)
		trace_seq_म_लिखो(s, " (Overruns: %u)\n",
				 trace->overrun);

	prपूर्णांक_graph_irq(iter, trace->func, TRACE_GRAPH_RET,
			cpu, pid, flags);

	वापस trace_handle_वापस(s);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t
prपूर्णांक_graph_comment(काष्ठा trace_seq *s, काष्ठा trace_entry *ent,
		    काष्ठा trace_iterator *iter, u32 flags)
अणु
	काष्ठा trace_array *tr = iter->tr;
	अचिन्हित दीर्घ sym_flags = (tr->trace_flags & TRACE_ITER_SYM_MASK);
	काष्ठा fgraph_data *data = iter->निजी;
	काष्ठा trace_event *event;
	पूर्णांक depth = 0;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (data)
		depth = per_cpu_ptr(data->cpu_data, iter->cpu)->depth;

	prपूर्णांक_graph_prologue(iter, s, 0, 0, flags);

	/* No समय */
	prपूर्णांक_graph_duration(tr, 0, s, flags | FLAGS_FILL_FULL);

	/* Indentation */
	अगर (depth > 0)
		क्रम (i = 0; i < (depth + 1) * TRACE_GRAPH_INDENT; i++)
			trace_seq_अ_दो(s, ' ');

	/* The comment */
	trace_seq_माला_दो(s, "/* ");

	चयन (iter->ent->type) अणु
	हाल TRACE_BPUTS:
		ret = trace_prपूर्णांक_bमाला_दो_msg_only(iter);
		अगर (ret != TRACE_TYPE_HANDLED)
			वापस ret;
		अवरोध;
	हाल TRACE_BPRINT:
		ret = trace_prपूर्णांक_bprपूर्णांकk_msg_only(iter);
		अगर (ret != TRACE_TYPE_HANDLED)
			वापस ret;
		अवरोध;
	हाल TRACE_PRINT:
		ret = trace_prपूर्णांक_prपूर्णांकk_msg_only(iter);
		अगर (ret != TRACE_TYPE_HANDLED)
			वापस ret;
		अवरोध;
	शेष:
		event = ftrace_find_event(ent->type);
		अगर (!event)
			वापस TRACE_TYPE_UNHANDLED;

		ret = event->funcs->trace(iter, sym_flags, event);
		अगर (ret != TRACE_TYPE_HANDLED)
			वापस ret;
	पूर्ण

	अगर (trace_seq_has_overflowed(s))
		जाओ out;

	/* Strip ending newline */
	अगर (s->buffer[s->seq.len - 1] == '\n') अणु
		s->buffer[s->seq.len - 1] = '\0';
		s->seq.len--;
	पूर्ण

	trace_seq_माला_दो(s, " */\n");
 out:
	वापस trace_handle_वापस(s);
पूर्ण


क्रमागत prपूर्णांक_line_t
prपूर्णांक_graph_function_flags(काष्ठा trace_iterator *iter, u32 flags)
अणु
	काष्ठा ftrace_graph_ent_entry *field;
	काष्ठा fgraph_data *data = iter->निजी;
	काष्ठा trace_entry *entry = iter->ent;
	काष्ठा trace_seq *s = &iter->seq;
	पूर्णांक cpu = iter->cpu;
	पूर्णांक ret;

	अगर (data && per_cpu_ptr(data->cpu_data, cpu)->ignore) अणु
		per_cpu_ptr(data->cpu_data, cpu)->ignore = 0;
		वापस TRACE_TYPE_HANDLED;
	पूर्ण

	/*
	 * If the last output failed, there's a possibility we need
	 * to prपूर्णांक out the missing entry which would never go out.
	 */
	अगर (data && data->failed) अणु
		field = &data->ent;
		iter->cpu = data->cpu;
		ret = prपूर्णांक_graph_entry(field, s, iter, flags);
		अगर (ret == TRACE_TYPE_HANDLED && iter->cpu != cpu) अणु
			per_cpu_ptr(data->cpu_data, iter->cpu)->ignore = 1;
			ret = TRACE_TYPE_NO_CONSUME;
		पूर्ण
		iter->cpu = cpu;
		वापस ret;
	पूर्ण

	चयन (entry->type) अणु
	हाल TRACE_GRAPH_ENT: अणु
		/*
		 * prपूर्णांक_graph_entry() may consume the current event,
		 * thus @field may become invalid, so we need to save it.
		 * माप(काष्ठा ftrace_graph_ent_entry) is very small,
		 * it can be safely saved at the stack.
		 */
		काष्ठा ftrace_graph_ent_entry saved;
		trace_assign_type(field, entry);
		saved = *field;
		वापस prपूर्णांक_graph_entry(&saved, s, iter, flags);
	पूर्ण
	हाल TRACE_GRAPH_RET: अणु
		काष्ठा ftrace_graph_ret_entry *field;
		trace_assign_type(field, entry);
		वापस prपूर्णांक_graph_वापस(&field->ret, s, entry, iter, flags);
	पूर्ण
	हाल TRACE_STACK:
	हाल TRACE_FN:
		/* करोnt trace stack and functions as comments */
		वापस TRACE_TYPE_UNHANDLED;

	शेष:
		वापस prपूर्णांक_graph_comment(s, entry, iter, flags);
	पूर्ण

	वापस TRACE_TYPE_HANDLED;
पूर्ण

अटल क्रमागत prपूर्णांक_line_t
prपूर्णांक_graph_function(काष्ठा trace_iterator *iter)
अणु
	वापस prपूर्णांक_graph_function_flags(iter, tracer_flags.val);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t
prपूर्णांक_graph_function_event(काष्ठा trace_iterator *iter, पूर्णांक flags,
			   काष्ठा trace_event *event)
अणु
	वापस prपूर्णांक_graph_function(iter);
पूर्ण

अटल व्योम prपूर्णांक_lat_header(काष्ठा seq_file *s, u32 flags)
अणु
	अटल स्थिर अक्षर spaces[] = "                "	/* 16 spaces */
		"    "					/* 4 spaces */
		"                 ";			/* 17 spaces */
	पूर्णांक size = 0;

	अगर (flags & TRACE_GRAPH_PRINT_ABS_TIME)
		size += 16;
	अगर (flags & TRACE_GRAPH_PRINT_REL_TIME)
		size += 16;
	अगर (flags & TRACE_GRAPH_PRINT_CPU)
		size += 4;
	अगर (flags & TRACE_GRAPH_PRINT_PROC)
		size += 17;

	seq_म_लिखो(s, "#%.*s  _-----=> irqs-off        \n", size, spaces);
	seq_म_लिखो(s, "#%.*s / _----=> need-resched    \n", size, spaces);
	seq_म_लिखो(s, "#%.*s| / _---=> hardirq/softirq \n", size, spaces);
	seq_म_लिखो(s, "#%.*s|| / _--=> preempt-depth   \n", size, spaces);
	seq_म_लिखो(s, "#%.*s||| /                      \n", size, spaces);
पूर्ण

अटल व्योम __prपूर्णांक_graph_headers_flags(काष्ठा trace_array *tr,
					काष्ठा seq_file *s, u32 flags)
अणु
	पूर्णांक lat = tr->trace_flags & TRACE_ITER_LATENCY_FMT;

	अगर (lat)
		prपूर्णांक_lat_header(s, flags);

	/* 1st line */
	seq_अ_दो(s, '#');
	अगर (flags & TRACE_GRAPH_PRINT_ABS_TIME)
		seq_माला_दो(s, "     TIME       ");
	अगर (flags & TRACE_GRAPH_PRINT_REL_TIME)
		seq_माला_दो(s, "   REL TIME     ");
	अगर (flags & TRACE_GRAPH_PRINT_CPU)
		seq_माला_दो(s, " CPU");
	अगर (flags & TRACE_GRAPH_PRINT_PROC)
		seq_माला_दो(s, "  TASK/PID       ");
	अगर (lat)
		seq_माला_दो(s, "||||   ");
	अगर (flags & TRACE_GRAPH_PRINT_DURATION)
		seq_माला_दो(s, "  DURATION   ");
	seq_माला_दो(s, "               FUNCTION CALLS\n");

	/* 2nd line */
	seq_अ_दो(s, '#');
	अगर (flags & TRACE_GRAPH_PRINT_ABS_TIME)
		seq_माला_दो(s, "      |         ");
	अगर (flags & TRACE_GRAPH_PRINT_REL_TIME)
		seq_माला_दो(s, "      |         ");
	अगर (flags & TRACE_GRAPH_PRINT_CPU)
		seq_माला_दो(s, " |  ");
	अगर (flags & TRACE_GRAPH_PRINT_PROC)
		seq_माला_दो(s, "   |    |        ");
	अगर (lat)
		seq_माला_दो(s, "||||   ");
	अगर (flags & TRACE_GRAPH_PRINT_DURATION)
		seq_माला_दो(s, "   |   |      ");
	seq_माला_दो(s, "               |   |   |   |\n");
पूर्ण

अटल व्योम prपूर्णांक_graph_headers(काष्ठा seq_file *s)
अणु
	prपूर्णांक_graph_headers_flags(s, tracer_flags.val);
पूर्ण

व्योम prपूर्णांक_graph_headers_flags(काष्ठा seq_file *s, u32 flags)
अणु
	काष्ठा trace_iterator *iter = s->निजी;
	काष्ठा trace_array *tr = iter->tr;

	अगर (!(tr->trace_flags & TRACE_ITER_CONTEXT_INFO))
		वापस;

	अगर (tr->trace_flags & TRACE_ITER_LATENCY_FMT) अणु
		/* prपूर्णांक nothing अगर the buffers are empty */
		अगर (trace_empty(iter))
			वापस;

		prपूर्णांक_trace_header(s, iter);
	पूर्ण

	__prपूर्णांक_graph_headers_flags(tr, s, flags);
पूर्ण

व्योम graph_trace_खोलो(काष्ठा trace_iterator *iter)
अणु
	/* pid and depth on the last trace processed */
	काष्ठा fgraph_data *data;
	gfp_t gfpflags;
	पूर्णांक cpu;

	iter->निजी = शून्य;

	/* We can be called in atomic context via ftrace_dump() */
	gfpflags = (in_atomic() || irqs_disabled()) ? GFP_ATOMIC : GFP_KERNEL;

	data = kzalloc(माप(*data), gfpflags);
	अगर (!data)
		जाओ out_err;

	data->cpu_data = alloc_percpu_gfp(काष्ठा fgraph_cpu_data, gfpflags);
	अगर (!data->cpu_data)
		जाओ out_err_मुक्त;

	क्रम_each_possible_cpu(cpu) अणु
		pid_t *pid = &(per_cpu_ptr(data->cpu_data, cpu)->last_pid);
		पूर्णांक *depth = &(per_cpu_ptr(data->cpu_data, cpu)->depth);
		पूर्णांक *ignore = &(per_cpu_ptr(data->cpu_data, cpu)->ignore);
		पूर्णांक *depth_irq = &(per_cpu_ptr(data->cpu_data, cpu)->depth_irq);

		*pid = -1;
		*depth = 0;
		*ignore = 0;
		*depth_irq = -1;
	पूर्ण

	iter->निजी = data;

	वापस;

 out_err_मुक्त:
	kमुक्त(data);
 out_err:
	pr_warn("function graph tracer: not enough memory\n");
पूर्ण

व्योम graph_trace_बंद(काष्ठा trace_iterator *iter)
अणु
	काष्ठा fgraph_data *data = iter->निजी;

	अगर (data) अणु
		मुक्त_percpu(data->cpu_data);
		kमुक्त(data);
	पूर्ण
पूर्ण

अटल पूर्णांक
func_graph_set_flag(काष्ठा trace_array *tr, u32 old_flags, u32 bit, पूर्णांक set)
अणु
	अगर (bit == TRACE_GRAPH_PRINT_IRQS)
		ftrace_graph_skip_irqs = !set;

	अगर (bit == TRACE_GRAPH_SLEEP_TIME)
		ftrace_graph_sleep_समय_control(set);

	अगर (bit == TRACE_GRAPH_GRAPH_TIME)
		ftrace_graph_graph_समय_control(set);

	वापस 0;
पूर्ण

अटल काष्ठा trace_event_functions graph_functions = अणु
	.trace		= prपूर्णांक_graph_function_event,
पूर्ण;

अटल काष्ठा trace_event graph_trace_entry_event = अणु
	.type		= TRACE_GRAPH_ENT,
	.funcs		= &graph_functions,
पूर्ण;

अटल काष्ठा trace_event graph_trace_ret_event = अणु
	.type		= TRACE_GRAPH_RET,
	.funcs		= &graph_functions
पूर्ण;

अटल काष्ठा tracer graph_trace __tracer_data = अणु
	.name		= "function_graph",
	.update_thresh	= graph_trace_update_thresh,
	.खोलो		= graph_trace_खोलो,
	.pipe_खोलो	= graph_trace_खोलो,
	.बंद		= graph_trace_बंद,
	.pipe_बंद	= graph_trace_बंद,
	.init		= graph_trace_init,
	.reset		= graph_trace_reset,
	.prपूर्णांक_line	= prपूर्णांक_graph_function,
	.prपूर्णांक_header	= prपूर्णांक_graph_headers,
	.flags		= &tracer_flags,
	.set_flag	= func_graph_set_flag,
#अगर_घोषित CONFIG_FTRACE_SELFTEST
	.selftest	= trace_selftest_startup_function_graph,
#पूर्ण_अगर
पूर्ण;


अटल sमाप_प्रकार
graph_depth_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf, माप_प्रकार cnt,
		  loff_t *ppos)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(ubuf, cnt, 10, &val);
	अगर (ret)
		वापस ret;

	fgraph_max_depth = val;

	*ppos += cnt;

	वापस cnt;
पूर्ण

अटल sमाप_प्रकार
graph_depth_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf, माप_प्रकार cnt,
		 loff_t *ppos)
अणु
	अक्षर buf[15]; /* More than enough to hold अच_पूर्णांक_उच्च + "\n"*/
	पूर्णांक n;

	n = प्र_लिखो(buf, "%d\n", fgraph_max_depth);

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, n);
पूर्ण

अटल स्थिर काष्ठा file_operations graph_depth_fops = अणु
	.खोलो		= tracing_खोलो_generic,
	.ग_लिखो		= graph_depth_ग_लिखो,
	.पढ़ो		= graph_depth_पढ़ो,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल __init पूर्णांक init_graph_tracefs(व्योम)
अणु
	पूर्णांक ret;

	ret = tracing_init_dentry();
	अगर (ret)
		वापस 0;

	trace_create_file("max_graph_depth", 0644, शून्य,
			  शून्य, &graph_depth_fops);

	वापस 0;
पूर्ण
fs_initcall(init_graph_tracefs);

अटल __init पूर्णांक init_graph_trace(व्योम)
अणु
	max_bytes_क्रम_cpu = snम_लिखो(शून्य, 0, "%u", nr_cpu_ids - 1);

	अगर (!रेजिस्टर_trace_event(&graph_trace_entry_event)) अणु
		pr_warn("Warning: could not register graph trace events\n");
		वापस 1;
	पूर्ण

	अगर (!रेजिस्टर_trace_event(&graph_trace_ret_event)) अणु
		pr_warn("Warning: could not register graph trace events\n");
		वापस 1;
	पूर्ण

	वापस रेजिस्टर_tracer(&graph_trace);
पूर्ण

core_initcall(init_graph_trace);
