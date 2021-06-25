<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * trace irqs off critical timings
 *
 * Copyright (C) 2007-2008 Steven Rostedt <srostedt@redhat.com>
 * Copyright (C) 2008 Ingo Molnar <mingo@redhat.com>
 *
 * From code in the latency_tracer, that is:
 *
 *  Copyright (C) 2004-2006 Ingo Molnar
 *  Copyright (C) 2004 Nadia Yvette Chambers
 */
#समावेश <linux/kallsyms.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/kprobes.h>

#समावेश "trace.h"

#समावेश <trace/events/preemptirq.h>

#अगर defined(CONFIG_IRQSOFF_TRACER) || defined(CONFIG_PREEMPT_TRACER)
अटल काष्ठा trace_array		*irqsoff_trace __पढ़ो_mostly;
अटल पूर्णांक				tracer_enabled __पढ़ो_mostly;

अटल DEFINE_PER_CPU(पूर्णांक, tracing_cpu);

अटल DEFINE_RAW_SPINLOCK(max_trace_lock);

क्रमागत अणु
	TRACER_IRQS_OFF		= (1 << 1),
	TRACER_PREEMPT_OFF	= (1 << 2),
पूर्ण;

अटल पूर्णांक trace_type __पढ़ो_mostly;

अटल पूर्णांक save_flags;

अटल व्योम stop_irqsoff_tracer(काष्ठा trace_array *tr, पूर्णांक graph);
अटल पूर्णांक start_irqsoff_tracer(काष्ठा trace_array *tr, पूर्णांक graph);

#अगर_घोषित CONFIG_PREEMPT_TRACER
अटल अंतरभूत पूर्णांक
preempt_trace(पूर्णांक pc)
अणु
	वापस ((trace_type & TRACER_PREEMPT_OFF) && pc);
पूर्ण
#अन्यथा
# define preempt_trace(pc) (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_IRQSOFF_TRACER
अटल अंतरभूत पूर्णांक
irq_trace(व्योम)
अणु
	वापस ((trace_type & TRACER_IRQS_OFF) &&
		irqs_disabled());
पूर्ण
#अन्यथा
# define irq_trace() (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
अटल पूर्णांक irqsoff_display_graph(काष्ठा trace_array *tr, पूर्णांक set);
# define is_graph(tr) ((tr)->trace_flags & TRACE_ITER_DISPLAY_GRAPH)
#अन्यथा
अटल अंतरभूत पूर्णांक irqsoff_display_graph(काष्ठा trace_array *tr, पूर्णांक set)
अणु
	वापस -EINVAL;
पूर्ण
# define is_graph(tr) false
#पूर्ण_अगर

/*
 * Sequence count - we record it when starting a measurement and
 * skip the latency अगर the sequence has changed - some other section
 * did a maximum and could disturb our measurement with serial console
 * prपूर्णांकouts, etc. Truly coinciding maximum latencies should be rare
 * and what happens together happens separately as well, so this करोesn't
 * decrease the validity of the maximum found:
 */
अटल __cacheline_aligned_in_smp	अचिन्हित दीर्घ max_sequence;

#अगर_घोषित CONFIG_FUNCTION_TRACER
/*
 * Prologue क्रम the preempt and irqs off function tracers.
 *
 * Returns 1 अगर it is OK to जारी, and data->disabled is
 *            incremented.
 *         0 अगर the trace is to be ignored, and data->disabled
 *            is kept the same.
 *
 * Note, this function is also used outside this अगरdef but
 *  inside the #अगर_घोषित of the function graph tracer below.
 *  This is OK, since the function graph tracer is
 *  dependent on the function tracer.
 */
अटल पूर्णांक func_prolog_dec(काष्ठा trace_array *tr,
			   काष्ठा trace_array_cpu **data,
			   अचिन्हित दीर्घ *flags)
अणु
	दीर्घ disabled;
	पूर्णांक cpu;

	/*
	 * Does not matter अगर we preempt. We test the flags
	 * afterward, to see अगर irqs are disabled or not.
	 * If we preempt and get a false positive, the flags
	 * test will fail.
	 */
	cpu = raw_smp_processor_id();
	अगर (likely(!per_cpu(tracing_cpu, cpu)))
		वापस 0;

	local_save_flags(*flags);
	/*
	 * Slight chance to get a false positive on tracing_cpu,
	 * although I'm starting to think there isn't a chance.
	 * Leave this क्रम now just to be paranoid.
	 */
	अगर (!irqs_disabled_flags(*flags) && !preempt_count())
		वापस 0;

	*data = per_cpu_ptr(tr->array_buffer.data, cpu);
	disabled = atomic_inc_वापस(&(*data)->disabled);

	अगर (likely(disabled == 1))
		वापस 1;

	atomic_dec(&(*data)->disabled);

	वापस 0;
पूर्ण

/*
 * irqsoff uses its own tracer function to keep the overhead करोwn:
 */
अटल व्योम
irqsoff_tracer_call(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		    काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा trace_array *tr = irqsoff_trace;
	काष्ठा trace_array_cpu *data;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक trace_ctx;

	अगर (!func_prolog_dec(tr, &data, &flags))
		वापस;

	trace_ctx = tracing_gen_ctx_flags(flags);

	trace_function(tr, ip, parent_ip, trace_ctx);

	atomic_dec(&data->disabled);
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER */

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
अटल पूर्णांक irqsoff_display_graph(काष्ठा trace_array *tr, पूर्णांक set)
अणु
	पूर्णांक cpu;

	अगर (!(is_graph(tr) ^ set))
		वापस 0;

	stop_irqsoff_tracer(irqsoff_trace, !set);

	क्रम_each_possible_cpu(cpu)
		per_cpu(tracing_cpu, cpu) = 0;

	tr->max_latency = 0;
	tracing_reset_online_cpus(&irqsoff_trace->array_buffer);

	वापस start_irqsoff_tracer(irqsoff_trace, set);
पूर्ण

अटल पूर्णांक irqsoff_graph_entry(काष्ठा ftrace_graph_ent *trace)
अणु
	काष्ठा trace_array *tr = irqsoff_trace;
	काष्ठा trace_array_cpu *data;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक trace_ctx;
	पूर्णांक ret;

	अगर (ftrace_graph_ignore_func(trace))
		वापस 0;
	/*
	 * Do not trace a function अगर it's filtered by set_graph_notrace.
	 * Make the index of ret stack negative to indicate that it should
	 * ignore further functions.  But it needs its own ret stack entry
	 * to recover the original index in order to जारी tracing after
	 * वापसing from the function.
	 */
	अगर (ftrace_graph_notrace_addr(trace->func))
		वापस 1;

	अगर (!func_prolog_dec(tr, &data, &flags))
		वापस 0;

	trace_ctx = tracing_gen_ctx_flags(flags);
	ret = __trace_graph_entry(tr, trace, trace_ctx);
	atomic_dec(&data->disabled);

	वापस ret;
पूर्ण

अटल व्योम irqsoff_graph_वापस(काष्ठा ftrace_graph_ret *trace)
अणु
	काष्ठा trace_array *tr = irqsoff_trace;
	काष्ठा trace_array_cpu *data;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक trace_ctx;

	ftrace_graph_addr_finish(trace);

	अगर (!func_prolog_dec(tr, &data, &flags))
		वापस;

	trace_ctx = tracing_gen_ctx_flags(flags);
	__trace_graph_वापस(tr, trace, trace_ctx);
	atomic_dec(&data->disabled);
पूर्ण

अटल काष्ठा fgraph_ops fgraph_ops = अणु
	.entryfunc		= &irqsoff_graph_entry,
	.retfunc		= &irqsoff_graph_वापस,
पूर्ण;

अटल व्योम irqsoff_trace_खोलो(काष्ठा trace_iterator *iter)
अणु
	अगर (is_graph(iter->tr))
		graph_trace_खोलो(iter);

पूर्ण

अटल व्योम irqsoff_trace_बंद(काष्ठा trace_iterator *iter)
अणु
	अगर (iter->निजी)
		graph_trace_बंद(iter);
पूर्ण

#घोषणा GRAPH_TRACER_FLAGS (TRACE_GRAPH_PRINT_CPU | \
			    TRACE_GRAPH_PRINT_PROC | \
			    TRACE_GRAPH_PRINT_REL_TIME | \
			    TRACE_GRAPH_PRINT_DURATION)

अटल क्रमागत prपूर्णांक_line_t irqsoff_prपूर्णांक_line(काष्ठा trace_iterator *iter)
अणु
	/*
	 * In graph mode call the graph tracer output function,
	 * otherwise go with the TRACE_FN event handler
	 */
	अगर (is_graph(iter->tr))
		वापस prपूर्णांक_graph_function_flags(iter, GRAPH_TRACER_FLAGS);

	वापस TRACE_TYPE_UNHANDLED;
पूर्ण

अटल व्योम irqsoff_prपूर्णांक_header(काष्ठा seq_file *s)
अणु
	काष्ठा trace_array *tr = irqsoff_trace;

	अगर (is_graph(tr))
		prपूर्णांक_graph_headers_flags(s, GRAPH_TRACER_FLAGS);
	अन्यथा
		trace_शेष_header(s);
पूर्ण

अटल व्योम
__trace_function(काष्ठा trace_array *tr,
		 अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		 अचिन्हित पूर्णांक trace_ctx)
अणु
	अगर (is_graph(tr))
		trace_graph_function(tr, ip, parent_ip, trace_ctx);
	अन्यथा
		trace_function(tr, ip, parent_ip, trace_ctx);
पूर्ण

#अन्यथा
#घोषणा __trace_function trace_function

अटल क्रमागत prपूर्णांक_line_t irqsoff_prपूर्णांक_line(काष्ठा trace_iterator *iter)
अणु
	वापस TRACE_TYPE_UNHANDLED;
पूर्ण

अटल व्योम irqsoff_trace_खोलो(काष्ठा trace_iterator *iter) अणु पूर्ण
अटल व्योम irqsoff_trace_बंद(काष्ठा trace_iterator *iter) अणु पूर्ण

#अगर_घोषित CONFIG_FUNCTION_TRACER
अटल व्योम irqsoff_prपूर्णांक_header(काष्ठा seq_file *s)
अणु
	trace_शेष_header(s);
पूर्ण
#अन्यथा
अटल व्योम irqsoff_prपूर्णांक_header(काष्ठा seq_file *s)
अणु
	trace_latency_header(s);
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER */
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */

/*
 * Should this new latency be reported/recorded?
 */
अटल bool report_latency(काष्ठा trace_array *tr, u64 delta)
अणु
	अगर (tracing_thresh) अणु
		अगर (delta < tracing_thresh)
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (delta <= tr->max_latency)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम
check_critical_timing(काष्ठा trace_array *tr,
		      काष्ठा trace_array_cpu *data,
		      अचिन्हित दीर्घ parent_ip,
		      पूर्णांक cpu)
अणु
	u64 T0, T1, delta;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक trace_ctx;

	T0 = data->preempt_बारtamp;
	T1 = ftrace_now(cpu);
	delta = T1-T0;

	trace_ctx = tracing_gen_ctx();

	अगर (!report_latency(tr, delta))
		जाओ out;

	raw_spin_lock_irqsave(&max_trace_lock, flags);

	/* check अगर we are still the max latency */
	अगर (!report_latency(tr, delta))
		जाओ out_unlock;

	__trace_function(tr, CALLER_ADDR0, parent_ip, trace_ctx);
	/* Skip 5 functions to get to the irq/preempt enable function */
	__trace_stack(tr, trace_ctx, 5);

	अगर (data->critical_sequence != max_sequence)
		जाओ out_unlock;

	data->critical_end = parent_ip;

	अगर (likely(!is_tracing_stopped())) अणु
		tr->max_latency = delta;
		update_max_tr_single(tr, current, cpu);
	पूर्ण

	max_sequence++;

out_unlock:
	raw_spin_unlock_irqrestore(&max_trace_lock, flags);

out:
	data->critical_sequence = max_sequence;
	data->preempt_बारtamp = ftrace_now(cpu);
	__trace_function(tr, CALLER_ADDR0, parent_ip, trace_ctx);
पूर्ण

अटल nokprobe_अंतरभूत व्योम
start_critical_timing(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip)
अणु
	पूर्णांक cpu;
	काष्ठा trace_array *tr = irqsoff_trace;
	काष्ठा trace_array_cpu *data;

	अगर (!tracer_enabled || !tracing_is_enabled())
		वापस;

	cpu = raw_smp_processor_id();

	अगर (per_cpu(tracing_cpu, cpu))
		वापस;

	data = per_cpu_ptr(tr->array_buffer.data, cpu);

	अगर (unlikely(!data) || atomic_पढ़ो(&data->disabled))
		वापस;

	atomic_inc(&data->disabled);

	data->critical_sequence = max_sequence;
	data->preempt_बारtamp = ftrace_now(cpu);
	data->critical_start = parent_ip ? : ip;

	__trace_function(tr, ip, parent_ip, tracing_gen_ctx());

	per_cpu(tracing_cpu, cpu) = 1;

	atomic_dec(&data->disabled);
पूर्ण

अटल nokprobe_अंतरभूत व्योम
stop_critical_timing(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip)
अणु
	पूर्णांक cpu;
	काष्ठा trace_array *tr = irqsoff_trace;
	काष्ठा trace_array_cpu *data;
	अचिन्हित पूर्णांक trace_ctx;

	cpu = raw_smp_processor_id();
	/* Always clear the tracing cpu on stopping the trace */
	अगर (unlikely(per_cpu(tracing_cpu, cpu)))
		per_cpu(tracing_cpu, cpu) = 0;
	अन्यथा
		वापस;

	अगर (!tracer_enabled || !tracing_is_enabled())
		वापस;

	data = per_cpu_ptr(tr->array_buffer.data, cpu);

	अगर (unlikely(!data) ||
	    !data->critical_start || atomic_पढ़ो(&data->disabled))
		वापस;

	atomic_inc(&data->disabled);

	trace_ctx = tracing_gen_ctx();
	__trace_function(tr, ip, parent_ip, trace_ctx);
	check_critical_timing(tr, data, parent_ip ? : ip, cpu);
	data->critical_start = 0;
	atomic_dec(&data->disabled);
पूर्ण

/* start and stop critical timings used to क्रम stoppage (in idle) */
व्योम start_critical_timings(व्योम)
अणु
	अगर (preempt_trace(preempt_count()) || irq_trace())
		start_critical_timing(CALLER_ADDR0, CALLER_ADDR1);
पूर्ण
EXPORT_SYMBOL_GPL(start_critical_timings);
NOKPROBE_SYMBOL(start_critical_timings);

व्योम stop_critical_timings(व्योम)
अणु
	अगर (preempt_trace(preempt_count()) || irq_trace())
		stop_critical_timing(CALLER_ADDR0, CALLER_ADDR1);
पूर्ण
EXPORT_SYMBOL_GPL(stop_critical_timings);
NOKPROBE_SYMBOL(stop_critical_timings);

#अगर_घोषित CONFIG_FUNCTION_TRACER
अटल bool function_enabled;

अटल पूर्णांक रेजिस्टर_irqsoff_function(काष्ठा trace_array *tr, पूर्णांक graph, पूर्णांक set)
अणु
	पूर्णांक ret;

	/* 'set' is set अगर TRACE_ITER_FUNCTION is about to be set */
	अगर (function_enabled || (!set && !(tr->trace_flags & TRACE_ITER_FUNCTION)))
		वापस 0;

	अगर (graph)
		ret = रेजिस्टर_ftrace_graph(&fgraph_ops);
	अन्यथा
		ret = रेजिस्टर_ftrace_function(tr->ops);

	अगर (!ret)
		function_enabled = true;

	वापस ret;
पूर्ण

अटल व्योम unरेजिस्टर_irqsoff_function(काष्ठा trace_array *tr, पूर्णांक graph)
अणु
	अगर (!function_enabled)
		वापस;

	अगर (graph)
		unरेजिस्टर_ftrace_graph(&fgraph_ops);
	अन्यथा
		unरेजिस्टर_ftrace_function(tr->ops);

	function_enabled = false;
पूर्ण

अटल पूर्णांक irqsoff_function_set(काष्ठा trace_array *tr, u32 mask, पूर्णांक set)
अणु
	अगर (!(mask & TRACE_ITER_FUNCTION))
		वापस 0;

	अगर (set)
		रेजिस्टर_irqsoff_function(tr, is_graph(tr), 1);
	अन्यथा
		unरेजिस्टर_irqsoff_function(tr, is_graph(tr));
	वापस 1;
पूर्ण
#अन्यथा
अटल पूर्णांक रेजिस्टर_irqsoff_function(काष्ठा trace_array *tr, पूर्णांक graph, पूर्णांक set)
अणु
	वापस 0;
पूर्ण
अटल व्योम unरेजिस्टर_irqsoff_function(काष्ठा trace_array *tr, पूर्णांक graph) अणु पूर्ण
अटल अंतरभूत पूर्णांक irqsoff_function_set(काष्ठा trace_array *tr, u32 mask, पूर्णांक set)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER */

अटल पूर्णांक irqsoff_flag_changed(काष्ठा trace_array *tr, u32 mask, पूर्णांक set)
अणु
	काष्ठा tracer *tracer = tr->current_trace;

	अगर (irqsoff_function_set(tr, mask, set))
		वापस 0;

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	अगर (mask & TRACE_ITER_DISPLAY_GRAPH)
		वापस irqsoff_display_graph(tr, set);
#पूर्ण_अगर

	वापस trace_keep_overग_लिखो(tracer, mask, set);
पूर्ण

अटल पूर्णांक start_irqsoff_tracer(काष्ठा trace_array *tr, पूर्णांक graph)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_irqsoff_function(tr, graph, 0);

	अगर (!ret && tracing_is_enabled())
		tracer_enabled = 1;
	अन्यथा
		tracer_enabled = 0;

	वापस ret;
पूर्ण

अटल व्योम stop_irqsoff_tracer(काष्ठा trace_array *tr, पूर्णांक graph)
अणु
	tracer_enabled = 0;

	unरेजिस्टर_irqsoff_function(tr, graph);
पूर्ण

अटल bool irqsoff_busy;

अटल पूर्णांक __irqsoff_tracer_init(काष्ठा trace_array *tr)
अणु
	अगर (irqsoff_busy)
		वापस -EBUSY;

	save_flags = tr->trace_flags;

	/* non overग_लिखो screws up the latency tracers */
	set_tracer_flag(tr, TRACE_ITER_OVERWRITE, 1);
	set_tracer_flag(tr, TRACE_ITER_LATENCY_FMT, 1);
	/* without छोड़ो, we will produce garbage अगर another latency occurs */
	set_tracer_flag(tr, TRACE_ITER_PAUSE_ON_TRACE, 1);

	tr->max_latency = 0;
	irqsoff_trace = tr;
	/* make sure that the tracer is visible */
	smp_wmb();

	ftrace_init_array_ops(tr, irqsoff_tracer_call);

	/* Only toplevel instance supports graph tracing */
	अगर (start_irqsoff_tracer(tr, (tr->flags & TRACE_ARRAY_FL_GLOBAL &&
				      is_graph(tr))))
		prपूर्णांकk(KERN_ERR "failed to start irqsoff tracer\n");

	irqsoff_busy = true;
	वापस 0;
पूर्ण

अटल व्योम __irqsoff_tracer_reset(काष्ठा trace_array *tr)
अणु
	पूर्णांक lat_flag = save_flags & TRACE_ITER_LATENCY_FMT;
	पूर्णांक overग_लिखो_flag = save_flags & TRACE_ITER_OVERWRITE;
	पूर्णांक छोड़ो_flag = save_flags & TRACE_ITER_PAUSE_ON_TRACE;

	stop_irqsoff_tracer(tr, is_graph(tr));

	set_tracer_flag(tr, TRACE_ITER_LATENCY_FMT, lat_flag);
	set_tracer_flag(tr, TRACE_ITER_OVERWRITE, overग_लिखो_flag);
	set_tracer_flag(tr, TRACE_ITER_PAUSE_ON_TRACE, छोड़ो_flag);
	ftrace_reset_array_ops(tr);

	irqsoff_busy = false;
पूर्ण

अटल व्योम irqsoff_tracer_start(काष्ठा trace_array *tr)
अणु
	tracer_enabled = 1;
पूर्ण

अटल व्योम irqsoff_tracer_stop(काष्ठा trace_array *tr)
अणु
	tracer_enabled = 0;
पूर्ण

#अगर_घोषित CONFIG_IRQSOFF_TRACER
/*
 * We are only पूर्णांकerested in hardirq on/off events:
 */
व्योम tracer_hardirqs_on(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1)
अणु
	अगर (!preempt_trace(preempt_count()) && irq_trace())
		stop_critical_timing(a0, a1);
पूर्ण
NOKPROBE_SYMBOL(tracer_hardirqs_on);

व्योम tracer_hardirqs_off(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1)
अणु
	अगर (!preempt_trace(preempt_count()) && irq_trace())
		start_critical_timing(a0, a1);
पूर्ण
NOKPROBE_SYMBOL(tracer_hardirqs_off);

अटल पूर्णांक irqsoff_tracer_init(काष्ठा trace_array *tr)
अणु
	trace_type = TRACER_IRQS_OFF;

	वापस __irqsoff_tracer_init(tr);
पूर्ण

अटल व्योम irqsoff_tracer_reset(काष्ठा trace_array *tr)
अणु
	__irqsoff_tracer_reset(tr);
पूर्ण

अटल काष्ठा tracer irqsoff_tracer __पढ़ो_mostly =
अणु
	.name		= "irqsoff",
	.init		= irqsoff_tracer_init,
	.reset		= irqsoff_tracer_reset,
	.start		= irqsoff_tracer_start,
	.stop		= irqsoff_tracer_stop,
	.prपूर्णांक_max	= true,
	.prपूर्णांक_header   = irqsoff_prपूर्णांक_header,
	.prपूर्णांक_line     = irqsoff_prपूर्णांक_line,
	.flag_changed	= irqsoff_flag_changed,
#अगर_घोषित CONFIG_FTRACE_SELFTEST
	.selftest    = trace_selftest_startup_irqsoff,
#पूर्ण_अगर
	.खोलो           = irqsoff_trace_खोलो,
	.बंद          = irqsoff_trace_बंद,
	.allow_instances = true,
	.use_max_tr	= true,
पूर्ण;
#पूर्ण_अगर /*  CONFIG_IRQSOFF_TRACER */

#अगर_घोषित CONFIG_PREEMPT_TRACER
व्योम tracer_preempt_on(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1)
अणु
	अगर (preempt_trace(preempt_count()) && !irq_trace())
		stop_critical_timing(a0, a1);
पूर्ण

व्योम tracer_preempt_off(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1)
अणु
	अगर (preempt_trace(preempt_count()) && !irq_trace())
		start_critical_timing(a0, a1);
पूर्ण

अटल पूर्णांक preemptoff_tracer_init(काष्ठा trace_array *tr)
अणु
	trace_type = TRACER_PREEMPT_OFF;

	वापस __irqsoff_tracer_init(tr);
पूर्ण

अटल व्योम preemptoff_tracer_reset(काष्ठा trace_array *tr)
अणु
	__irqsoff_tracer_reset(tr);
पूर्ण

अटल काष्ठा tracer preemptoff_tracer __पढ़ो_mostly =
अणु
	.name		= "preemptoff",
	.init		= preemptoff_tracer_init,
	.reset		= preemptoff_tracer_reset,
	.start		= irqsoff_tracer_start,
	.stop		= irqsoff_tracer_stop,
	.prपूर्णांक_max	= true,
	.prपूर्णांक_header   = irqsoff_prपूर्णांक_header,
	.prपूर्णांक_line     = irqsoff_prपूर्णांक_line,
	.flag_changed	= irqsoff_flag_changed,
#अगर_घोषित CONFIG_FTRACE_SELFTEST
	.selftest    = trace_selftest_startup_preemptoff,
#पूर्ण_अगर
	.खोलो		= irqsoff_trace_खोलो,
	.बंद		= irqsoff_trace_बंद,
	.allow_instances = true,
	.use_max_tr	= true,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PREEMPT_TRACER */

#अगर defined(CONFIG_IRQSOFF_TRACER) && defined(CONFIG_PREEMPT_TRACER)

अटल पूर्णांक preemptirqsoff_tracer_init(काष्ठा trace_array *tr)
अणु
	trace_type = TRACER_IRQS_OFF | TRACER_PREEMPT_OFF;

	वापस __irqsoff_tracer_init(tr);
पूर्ण

अटल व्योम preemptirqsoff_tracer_reset(काष्ठा trace_array *tr)
अणु
	__irqsoff_tracer_reset(tr);
पूर्ण

अटल काष्ठा tracer preemptirqsoff_tracer __पढ़ो_mostly =
अणु
	.name		= "preemptirqsoff",
	.init		= preemptirqsoff_tracer_init,
	.reset		= preemptirqsoff_tracer_reset,
	.start		= irqsoff_tracer_start,
	.stop		= irqsoff_tracer_stop,
	.prपूर्णांक_max	= true,
	.prपूर्णांक_header   = irqsoff_prपूर्णांक_header,
	.prपूर्णांक_line     = irqsoff_prपूर्णांक_line,
	.flag_changed	= irqsoff_flag_changed,
#अगर_घोषित CONFIG_FTRACE_SELFTEST
	.selftest    = trace_selftest_startup_preemptirqsoff,
#पूर्ण_अगर
	.खोलो		= irqsoff_trace_खोलो,
	.बंद		= irqsoff_trace_बंद,
	.allow_instances = true,
	.use_max_tr	= true,
पूर्ण;
#पूर्ण_अगर

__init अटल पूर्णांक init_irqsoff_tracer(व्योम)
अणु
#अगर_घोषित CONFIG_IRQSOFF_TRACER
	रेजिस्टर_tracer(&irqsoff_tracer);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PREEMPT_TRACER
	रेजिस्टर_tracer(&preemptoff_tracer);
#पूर्ण_अगर
#अगर defined(CONFIG_IRQSOFF_TRACER) && defined(CONFIG_PREEMPT_TRACER)
	रेजिस्टर_tracer(&preemptirqsoff_tracer);
#पूर्ण_अगर

	वापस 0;
पूर्ण
core_initcall(init_irqsoff_tracer);
#पूर्ण_अगर /* IRQSOFF_TRACER || PREEMPTOFF_TRACER */
