<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * trace task wakeup timings
 *
 * Copyright (C) 2007-2008 Steven Rostedt <srostedt@redhat.com>
 * Copyright (C) 2008 Ingo Molnar <mingo@redhat.com>
 *
 * Based on code from the latency_tracer, that is:
 *
 *  Copyright (C) 2004-2006 Ingo Molnar
 *  Copyright (C) 2004 Nadia Yvette Chambers
 */
#समावेश <linux/module.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/sched/rt.h>
#समावेश <linux/sched/deadline.h>
#समावेश <trace/events/sched.h>
#समावेश "trace.h"

अटल काष्ठा trace_array	*wakeup_trace;
अटल पूर्णांक __पढ़ो_mostly	tracer_enabled;

अटल काष्ठा task_काष्ठा	*wakeup_task;
अटल पूर्णांक			wakeup_cpu;
अटल पूर्णांक			wakeup_current_cpu;
अटल अचिन्हित			wakeup_prio = -1;
अटल पूर्णांक			wakeup_rt;
अटल पूर्णांक			wakeup_dl;
अटल पूर्णांक			tracing_dl = 0;

अटल arch_spinlock_t wakeup_lock =
	(arch_spinlock_t)__ARCH_SPIN_LOCK_UNLOCKED;

अटल व्योम wakeup_reset(काष्ठा trace_array *tr);
अटल व्योम __wakeup_reset(काष्ठा trace_array *tr);
अटल पूर्णांक start_func_tracer(काष्ठा trace_array *tr, पूर्णांक graph);
अटल व्योम stop_func_tracer(काष्ठा trace_array *tr, पूर्णांक graph);

अटल पूर्णांक save_flags;

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
# define is_graph(tr) ((tr)->trace_flags & TRACE_ITER_DISPLAY_GRAPH)
#अन्यथा
# define is_graph(tr) false
#पूर्ण_अगर

#अगर_घोषित CONFIG_FUNCTION_TRACER

अटल bool function_enabled;

/*
 * Prologue क्रम the wakeup function tracers.
 *
 * Returns 1 अगर it is OK to जारी, and preemption
 *            is disabled and data->disabled is incremented.
 *         0 अगर the trace is to be ignored, and preemption
 *            is not disabled and data->disabled is
 *            kept the same.
 *
 * Note, this function is also used outside this अगरdef but
 *  inside the #अगर_घोषित of the function graph tracer below.
 *  This is OK, since the function graph tracer is
 *  dependent on the function tracer.
 */
अटल पूर्णांक
func_prolog_preempt_disable(काष्ठा trace_array *tr,
			    काष्ठा trace_array_cpu **data,
			    अचिन्हित पूर्णांक *trace_ctx)
अणु
	दीर्घ disabled;
	पूर्णांक cpu;

	अगर (likely(!wakeup_task))
		वापस 0;

	*trace_ctx = tracing_gen_ctx();
	preempt_disable_notrace();

	cpu = raw_smp_processor_id();
	अगर (cpu != wakeup_current_cpu)
		जाओ out_enable;

	*data = per_cpu_ptr(tr->array_buffer.data, cpu);
	disabled = atomic_inc_वापस(&(*data)->disabled);
	अगर (unlikely(disabled != 1))
		जाओ out;

	वापस 1;

out:
	atomic_dec(&(*data)->disabled);

out_enable:
	preempt_enable_notrace();
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER

अटल पूर्णांक wakeup_display_graph(काष्ठा trace_array *tr, पूर्णांक set)
अणु
	अगर (!(is_graph(tr) ^ set))
		वापस 0;

	stop_func_tracer(tr, !set);

	wakeup_reset(wakeup_trace);
	tr->max_latency = 0;

	वापस start_func_tracer(tr, set);
पूर्ण

अटल पूर्णांक wakeup_graph_entry(काष्ठा ftrace_graph_ent *trace)
अणु
	काष्ठा trace_array *tr = wakeup_trace;
	काष्ठा trace_array_cpu *data;
	अचिन्हित पूर्णांक trace_ctx;
	पूर्णांक ret = 0;

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

	अगर (!func_prolog_preempt_disable(tr, &data, &trace_ctx))
		वापस 0;

	ret = __trace_graph_entry(tr, trace, trace_ctx);
	atomic_dec(&data->disabled);
	preempt_enable_notrace();

	वापस ret;
पूर्ण

अटल व्योम wakeup_graph_वापस(काष्ठा ftrace_graph_ret *trace)
अणु
	काष्ठा trace_array *tr = wakeup_trace;
	काष्ठा trace_array_cpu *data;
	अचिन्हित पूर्णांक trace_ctx;

	ftrace_graph_addr_finish(trace);

	अगर (!func_prolog_preempt_disable(tr, &data, &trace_ctx))
		वापस;

	__trace_graph_वापस(tr, trace, trace_ctx);
	atomic_dec(&data->disabled);

	preempt_enable_notrace();
	वापस;
पूर्ण

अटल काष्ठा fgraph_ops fgraph_wakeup_ops = अणु
	.entryfunc = &wakeup_graph_entry,
	.retfunc = &wakeup_graph_वापस,
पूर्ण;

अटल व्योम wakeup_trace_खोलो(काष्ठा trace_iterator *iter)
अणु
	अगर (is_graph(iter->tr))
		graph_trace_खोलो(iter);
पूर्ण

अटल व्योम wakeup_trace_बंद(काष्ठा trace_iterator *iter)
अणु
	अगर (iter->निजी)
		graph_trace_बंद(iter);
पूर्ण

#घोषणा GRAPH_TRACER_FLAGS (TRACE_GRAPH_PRINT_PROC | \
			    TRACE_GRAPH_PRINT_CPU |  \
			    TRACE_GRAPH_PRINT_REL_TIME | \
			    TRACE_GRAPH_PRINT_DURATION | \
			    TRACE_GRAPH_PRINT_OVERHEAD | \
			    TRACE_GRAPH_PRINT_IRQS)

अटल क्रमागत prपूर्णांक_line_t wakeup_prपूर्णांक_line(काष्ठा trace_iterator *iter)
अणु
	/*
	 * In graph mode call the graph tracer output function,
	 * otherwise go with the TRACE_FN event handler
	 */
	अगर (is_graph(iter->tr))
		वापस prपूर्णांक_graph_function_flags(iter, GRAPH_TRACER_FLAGS);

	वापस TRACE_TYPE_UNHANDLED;
पूर्ण

अटल व्योम wakeup_prपूर्णांक_header(काष्ठा seq_file *s)
अणु
	अगर (is_graph(wakeup_trace))
		prपूर्णांक_graph_headers_flags(s, GRAPH_TRACER_FLAGS);
	अन्यथा
		trace_शेष_header(s);
पूर्ण
#पूर्ण_अगर /* अन्यथा CONFIG_FUNCTION_GRAPH_TRACER */

/*
 * wakeup uses its own tracer function to keep the overhead करोwn:
 */
अटल व्योम
wakeup_tracer_call(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		   काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा trace_array *tr = wakeup_trace;
	काष्ठा trace_array_cpu *data;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक trace_ctx;

	अगर (!func_prolog_preempt_disable(tr, &data, &trace_ctx))
		वापस;

	local_irq_save(flags);
	trace_function(tr, ip, parent_ip, trace_ctx);
	local_irq_restore(flags);

	atomic_dec(&data->disabled);
	preempt_enable_notrace();
पूर्ण

अटल पूर्णांक रेजिस्टर_wakeup_function(काष्ठा trace_array *tr, पूर्णांक graph, पूर्णांक set)
अणु
	पूर्णांक ret;

	/* 'set' is set अगर TRACE_ITER_FUNCTION is about to be set */
	अगर (function_enabled || (!set && !(tr->trace_flags & TRACE_ITER_FUNCTION)))
		वापस 0;

	अगर (graph)
		ret = रेजिस्टर_ftrace_graph(&fgraph_wakeup_ops);
	अन्यथा
		ret = रेजिस्टर_ftrace_function(tr->ops);

	अगर (!ret)
		function_enabled = true;

	वापस ret;
पूर्ण

अटल व्योम unरेजिस्टर_wakeup_function(काष्ठा trace_array *tr, पूर्णांक graph)
अणु
	अगर (!function_enabled)
		वापस;

	अगर (graph)
		unरेजिस्टर_ftrace_graph(&fgraph_wakeup_ops);
	अन्यथा
		unरेजिस्टर_ftrace_function(tr->ops);

	function_enabled = false;
पूर्ण

अटल पूर्णांक wakeup_function_set(काष्ठा trace_array *tr, u32 mask, पूर्णांक set)
अणु
	अगर (!(mask & TRACE_ITER_FUNCTION))
		वापस 0;

	अगर (set)
		रेजिस्टर_wakeup_function(tr, is_graph(tr), 1);
	अन्यथा
		unरेजिस्टर_wakeup_function(tr, is_graph(tr));
	वापस 1;
पूर्ण
#अन्यथा /* CONFIG_FUNCTION_TRACER */
अटल पूर्णांक रेजिस्टर_wakeup_function(काष्ठा trace_array *tr, पूर्णांक graph, पूर्णांक set)
अणु
	वापस 0;
पूर्ण
अटल व्योम unरेजिस्टर_wakeup_function(काष्ठा trace_array *tr, पूर्णांक graph) अणु पूर्ण
अटल पूर्णांक wakeup_function_set(काष्ठा trace_array *tr, u32 mask, पूर्णांक set)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* अन्यथा CONFIG_FUNCTION_TRACER */

#अगर_अघोषित CONFIG_FUNCTION_GRAPH_TRACER
अटल क्रमागत prपूर्णांक_line_t wakeup_prपूर्णांक_line(काष्ठा trace_iterator *iter)
अणु
	वापस TRACE_TYPE_UNHANDLED;
पूर्ण

अटल व्योम wakeup_trace_खोलो(काष्ठा trace_iterator *iter) अणु पूर्ण
अटल व्योम wakeup_trace_बंद(काष्ठा trace_iterator *iter) अणु पूर्ण

अटल व्योम wakeup_prपूर्णांक_header(काष्ठा seq_file *s)
अणु
	trace_शेष_header(s);
पूर्ण
#पूर्ण_अगर /* !CONFIG_FUNCTION_GRAPH_TRACER */

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

अटल पूर्णांक wakeup_flag_changed(काष्ठा trace_array *tr, u32 mask, पूर्णांक set)
अणु
	काष्ठा tracer *tracer = tr->current_trace;

	अगर (wakeup_function_set(tr, mask, set))
		वापस 0;

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	अगर (mask & TRACE_ITER_DISPLAY_GRAPH)
		वापस wakeup_display_graph(tr, set);
#पूर्ण_अगर

	वापस trace_keep_overग_लिखो(tracer, mask, set);
पूर्ण

अटल पूर्णांक start_func_tracer(काष्ठा trace_array *tr, पूर्णांक graph)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_wakeup_function(tr, graph, 0);

	अगर (!ret && tracing_is_enabled())
		tracer_enabled = 1;
	अन्यथा
		tracer_enabled = 0;

	वापस ret;
पूर्ण

अटल व्योम stop_func_tracer(काष्ठा trace_array *tr, पूर्णांक graph)
अणु
	tracer_enabled = 0;

	unरेजिस्टर_wakeup_function(tr, graph);
पूर्ण

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
probe_wakeup_migrate_task(व्योम *ignore, काष्ठा task_काष्ठा *task, पूर्णांक cpu)
अणु
	अगर (task != wakeup_task)
		वापस;

	wakeup_current_cpu = cpu;
पूर्ण

अटल व्योम
tracing_sched_चयन_trace(काष्ठा trace_array *tr,
			   काष्ठा task_काष्ठा *prev,
			   काष्ठा task_काष्ठा *next,
			   अचिन्हित पूर्णांक trace_ctx)
अणु
	काष्ठा trace_event_call *call = &event_context_चयन;
	काष्ठा trace_buffer *buffer = tr->array_buffer.buffer;
	काष्ठा ring_buffer_event *event;
	काष्ठा ctx_चयन_entry *entry;

	event = trace_buffer_lock_reserve(buffer, TRACE_CTX,
					  माप(*entry), trace_ctx);
	अगर (!event)
		वापस;
	entry	= ring_buffer_event_data(event);
	entry->prev_pid			= prev->pid;
	entry->prev_prio		= prev->prio;
	entry->prev_state		= task_state_index(prev);
	entry->next_pid			= next->pid;
	entry->next_prio		= next->prio;
	entry->next_state		= task_state_index(next);
	entry->next_cpu	= task_cpu(next);

	अगर (!call_filter_check_discard(call, entry, buffer, event))
		trace_buffer_unlock_commit(tr, buffer, event, trace_ctx);
पूर्ण

अटल व्योम
tracing_sched_wakeup_trace(काष्ठा trace_array *tr,
			   काष्ठा task_काष्ठा *wakee,
			   काष्ठा task_काष्ठा *curr,
			   अचिन्हित पूर्णांक trace_ctx)
अणु
	काष्ठा trace_event_call *call = &event_wakeup;
	काष्ठा ring_buffer_event *event;
	काष्ठा ctx_चयन_entry *entry;
	काष्ठा trace_buffer *buffer = tr->array_buffer.buffer;

	event = trace_buffer_lock_reserve(buffer, TRACE_WAKE,
					  माप(*entry), trace_ctx);
	अगर (!event)
		वापस;
	entry	= ring_buffer_event_data(event);
	entry->prev_pid			= curr->pid;
	entry->prev_prio		= curr->prio;
	entry->prev_state		= task_state_index(curr);
	entry->next_pid			= wakee->pid;
	entry->next_prio		= wakee->prio;
	entry->next_state		= task_state_index(wakee);
	entry->next_cpu			= task_cpu(wakee);

	अगर (!call_filter_check_discard(call, entry, buffer, event))
		trace_buffer_unlock_commit(tr, buffer, event, trace_ctx);
पूर्ण

अटल व्योम notrace
probe_wakeup_sched_चयन(व्योम *ignore, bool preempt,
			  काष्ठा task_काष्ठा *prev, काष्ठा task_काष्ठा *next)
अणु
	काष्ठा trace_array_cpu *data;
	u64 T0, T1, delta;
	अचिन्हित दीर्घ flags;
	दीर्घ disabled;
	पूर्णांक cpu;
	अचिन्हित पूर्णांक trace_ctx;

	tracing_record_cmdline(prev);

	अगर (unlikely(!tracer_enabled))
		वापस;

	/*
	 * When we start a new trace, we set wakeup_task to शून्य
	 * and then set tracer_enabled = 1. We want to make sure
	 * that another CPU करोes not see the tracer_enabled = 1
	 * and the wakeup_task with an older task, that might
	 * actually be the same as next.
	 */
	smp_rmb();

	अगर (next != wakeup_task)
		वापस;

	/* disable local data, not wakeup_cpu data */
	cpu = raw_smp_processor_id();
	disabled = atomic_inc_वापस(&per_cpu_ptr(wakeup_trace->array_buffer.data, cpu)->disabled);
	अगर (likely(disabled != 1))
		जाओ out;

	local_irq_save(flags);
	trace_ctx = tracing_gen_ctx_flags(flags);

	arch_spin_lock(&wakeup_lock);

	/* We could race with grabbing wakeup_lock */
	अगर (unlikely(!tracer_enabled || next != wakeup_task))
		जाओ out_unlock;

	/* The task we are रुकोing क्रम is waking up */
	data = per_cpu_ptr(wakeup_trace->array_buffer.data, wakeup_cpu);

	__trace_function(wakeup_trace, CALLER_ADDR0, CALLER_ADDR1, trace_ctx);
	tracing_sched_चयन_trace(wakeup_trace, prev, next, trace_ctx);
	__trace_stack(wakeup_trace, trace_ctx, 0);

	T0 = data->preempt_बारtamp;
	T1 = ftrace_now(cpu);
	delta = T1-T0;

	अगर (!report_latency(wakeup_trace, delta))
		जाओ out_unlock;

	अगर (likely(!is_tracing_stopped())) अणु
		wakeup_trace->max_latency = delta;
		update_max_tr(wakeup_trace, wakeup_task, wakeup_cpu, शून्य);
	पूर्ण

out_unlock:
	__wakeup_reset(wakeup_trace);
	arch_spin_unlock(&wakeup_lock);
	local_irq_restore(flags);
out:
	atomic_dec(&per_cpu_ptr(wakeup_trace->array_buffer.data, cpu)->disabled);
पूर्ण

अटल व्योम __wakeup_reset(काष्ठा trace_array *tr)
अणु
	wakeup_cpu = -1;
	wakeup_prio = -1;
	tracing_dl = 0;

	अगर (wakeup_task)
		put_task_काष्ठा(wakeup_task);

	wakeup_task = शून्य;
पूर्ण

अटल व्योम wakeup_reset(काष्ठा trace_array *tr)
अणु
	अचिन्हित दीर्घ flags;

	tracing_reset_online_cpus(&tr->array_buffer);

	local_irq_save(flags);
	arch_spin_lock(&wakeup_lock);
	__wakeup_reset(tr);
	arch_spin_unlock(&wakeup_lock);
	local_irq_restore(flags);
पूर्ण

अटल व्योम
probe_wakeup(व्योम *ignore, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा trace_array_cpu *data;
	पूर्णांक cpu = smp_processor_id();
	दीर्घ disabled;
	अचिन्हित पूर्णांक trace_ctx;

	अगर (likely(!tracer_enabled))
		वापस;

	tracing_record_cmdline(p);
	tracing_record_cmdline(current);

	/*
	 * Semantic is like this:
	 *  - wakeup tracer handles all tasks in the प्रणाली, independently
	 *    from their scheduling class;
	 *  - wakeup_rt tracer handles tasks beदीर्घing to sched_dl and
	 *    sched_rt class;
	 *  - wakeup_dl handles tasks beदीर्घing to sched_dl class only.
	 */
	अगर (tracing_dl || (wakeup_dl && !dl_task(p)) ||
	    (wakeup_rt && !dl_task(p) && !rt_task(p)) ||
	    (!dl_task(p) && (p->prio >= wakeup_prio || p->prio >= current->prio)))
		वापस;

	disabled = atomic_inc_वापस(&per_cpu_ptr(wakeup_trace->array_buffer.data, cpu)->disabled);
	अगर (unlikely(disabled != 1))
		जाओ out;

	trace_ctx = tracing_gen_ctx();

	/* पूर्णांकerrupts should be off from try_to_wake_up */
	arch_spin_lock(&wakeup_lock);

	/* check क्रम races. */
	अगर (!tracer_enabled || tracing_dl ||
	    (!dl_task(p) && p->prio >= wakeup_prio))
		जाओ out_locked;

	/* reset the trace */
	__wakeup_reset(wakeup_trace);

	wakeup_cpu = task_cpu(p);
	wakeup_current_cpu = wakeup_cpu;
	wakeup_prio = p->prio;

	/*
	 * Once you start tracing a -deadline task, करोn't bother tracing
	 * another task until the first one wakes up.
	 */
	अगर (dl_task(p))
		tracing_dl = 1;
	अन्यथा
		tracing_dl = 0;

	wakeup_task = get_task_काष्ठा(p);

	data = per_cpu_ptr(wakeup_trace->array_buffer.data, wakeup_cpu);
	data->preempt_बारtamp = ftrace_now(cpu);
	tracing_sched_wakeup_trace(wakeup_trace, p, current, trace_ctx);
	__trace_stack(wakeup_trace, trace_ctx, 0);

	/*
	 * We must be careful in using CALLER_ADDR2. But since wake_up
	 * is not called by an assembly function  (where as schedule is)
	 * it should be safe to use it here.
	 */
	__trace_function(wakeup_trace, CALLER_ADDR1, CALLER_ADDR2, trace_ctx);

out_locked:
	arch_spin_unlock(&wakeup_lock);
out:
	atomic_dec(&per_cpu_ptr(wakeup_trace->array_buffer.data, cpu)->disabled);
पूर्ण

अटल व्योम start_wakeup_tracer(काष्ठा trace_array *tr)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_trace_sched_wakeup(probe_wakeup, शून्य);
	अगर (ret) अणु
		pr_info("wakeup trace: Couldn't activate tracepoint"
			" probe to kernel_sched_wakeup\n");
		वापस;
	पूर्ण

	ret = रेजिस्टर_trace_sched_wakeup_new(probe_wakeup, शून्य);
	अगर (ret) अणु
		pr_info("wakeup trace: Couldn't activate tracepoint"
			" probe to kernel_sched_wakeup_new\n");
		जाओ fail_deprobe;
	पूर्ण

	ret = रेजिस्टर_trace_sched_चयन(probe_wakeup_sched_चयन, शून्य);
	अगर (ret) अणु
		pr_info("sched trace: Couldn't activate tracepoint"
			" probe to kernel_sched_switch\n");
		जाओ fail_deprobe_wake_new;
	पूर्ण

	ret = रेजिस्टर_trace_sched_migrate_task(probe_wakeup_migrate_task, शून्य);
	अगर (ret) अणु
		pr_info("wakeup trace: Couldn't activate tracepoint"
			" probe to kernel_sched_migrate_task\n");
		जाओ fail_deprobe_sched_चयन;
	पूर्ण

	wakeup_reset(tr);

	/*
	 * Don't let the tracer_enabled = 1 show up beक्रमe
	 * the wakeup_task is reset. This may be overसमाप्त since
	 * wakeup_reset करोes a spin_unlock after setting the
	 * wakeup_task to शून्य, but I want to be safe.
	 * This is a slow path anyway.
	 */
	smp_wmb();

	अगर (start_func_tracer(tr, is_graph(tr)))
		prपूर्णांकk(KERN_ERR "failed to start wakeup tracer\n");

	वापस;
fail_deprobe_sched_चयन:
	unरेजिस्टर_trace_sched_चयन(probe_wakeup_sched_चयन, शून्य);
fail_deprobe_wake_new:
	unरेजिस्टर_trace_sched_wakeup_new(probe_wakeup, शून्य);
fail_deprobe:
	unरेजिस्टर_trace_sched_wakeup(probe_wakeup, शून्य);
पूर्ण

अटल व्योम stop_wakeup_tracer(काष्ठा trace_array *tr)
अणु
	tracer_enabled = 0;
	stop_func_tracer(tr, is_graph(tr));
	unरेजिस्टर_trace_sched_चयन(probe_wakeup_sched_चयन, शून्य);
	unरेजिस्टर_trace_sched_wakeup_new(probe_wakeup, शून्य);
	unरेजिस्टर_trace_sched_wakeup(probe_wakeup, शून्य);
	unरेजिस्टर_trace_sched_migrate_task(probe_wakeup_migrate_task, शून्य);
पूर्ण

अटल bool wakeup_busy;

अटल पूर्णांक __wakeup_tracer_init(काष्ठा trace_array *tr)
अणु
	save_flags = tr->trace_flags;

	/* non overग_लिखो screws up the latency tracers */
	set_tracer_flag(tr, TRACE_ITER_OVERWRITE, 1);
	set_tracer_flag(tr, TRACE_ITER_LATENCY_FMT, 1);

	tr->max_latency = 0;
	wakeup_trace = tr;
	ftrace_init_array_ops(tr, wakeup_tracer_call);
	start_wakeup_tracer(tr);

	wakeup_busy = true;
	वापस 0;
पूर्ण

अटल पूर्णांक wakeup_tracer_init(काष्ठा trace_array *tr)
अणु
	अगर (wakeup_busy)
		वापस -EBUSY;

	wakeup_dl = 0;
	wakeup_rt = 0;
	वापस __wakeup_tracer_init(tr);
पूर्ण

अटल पूर्णांक wakeup_rt_tracer_init(काष्ठा trace_array *tr)
अणु
	अगर (wakeup_busy)
		वापस -EBUSY;

	wakeup_dl = 0;
	wakeup_rt = 1;
	वापस __wakeup_tracer_init(tr);
पूर्ण

अटल पूर्णांक wakeup_dl_tracer_init(काष्ठा trace_array *tr)
अणु
	अगर (wakeup_busy)
		वापस -EBUSY;

	wakeup_dl = 1;
	wakeup_rt = 0;
	वापस __wakeup_tracer_init(tr);
पूर्ण

अटल व्योम wakeup_tracer_reset(काष्ठा trace_array *tr)
अणु
	पूर्णांक lat_flag = save_flags & TRACE_ITER_LATENCY_FMT;
	पूर्णांक overग_लिखो_flag = save_flags & TRACE_ITER_OVERWRITE;

	stop_wakeup_tracer(tr);
	/* make sure we put back any tasks we are tracing */
	wakeup_reset(tr);

	set_tracer_flag(tr, TRACE_ITER_LATENCY_FMT, lat_flag);
	set_tracer_flag(tr, TRACE_ITER_OVERWRITE, overग_लिखो_flag);
	ftrace_reset_array_ops(tr);
	wakeup_busy = false;
पूर्ण

अटल व्योम wakeup_tracer_start(काष्ठा trace_array *tr)
अणु
	wakeup_reset(tr);
	tracer_enabled = 1;
पूर्ण

अटल व्योम wakeup_tracer_stop(काष्ठा trace_array *tr)
अणु
	tracer_enabled = 0;
पूर्ण

अटल काष्ठा tracer wakeup_tracer __पढ़ो_mostly =
अणु
	.name		= "wakeup",
	.init		= wakeup_tracer_init,
	.reset		= wakeup_tracer_reset,
	.start		= wakeup_tracer_start,
	.stop		= wakeup_tracer_stop,
	.prपूर्णांक_max	= true,
	.prपूर्णांक_header	= wakeup_prपूर्णांक_header,
	.prपूर्णांक_line	= wakeup_prपूर्णांक_line,
	.flag_changed	= wakeup_flag_changed,
#अगर_घोषित CONFIG_FTRACE_SELFTEST
	.selftest    = trace_selftest_startup_wakeup,
#पूर्ण_अगर
	.खोलो		= wakeup_trace_खोलो,
	.बंद		= wakeup_trace_बंद,
	.allow_instances = true,
	.use_max_tr	= true,
पूर्ण;

अटल काष्ठा tracer wakeup_rt_tracer __पढ़ो_mostly =
अणु
	.name		= "wakeup_rt",
	.init		= wakeup_rt_tracer_init,
	.reset		= wakeup_tracer_reset,
	.start		= wakeup_tracer_start,
	.stop		= wakeup_tracer_stop,
	.prपूर्णांक_max	= true,
	.prपूर्णांक_header	= wakeup_prपूर्णांक_header,
	.prपूर्णांक_line	= wakeup_prपूर्णांक_line,
	.flag_changed	= wakeup_flag_changed,
#अगर_घोषित CONFIG_FTRACE_SELFTEST
	.selftest    = trace_selftest_startup_wakeup,
#पूर्ण_अगर
	.खोलो		= wakeup_trace_खोलो,
	.बंद		= wakeup_trace_बंद,
	.allow_instances = true,
	.use_max_tr	= true,
पूर्ण;

अटल काष्ठा tracer wakeup_dl_tracer __पढ़ो_mostly =
अणु
	.name		= "wakeup_dl",
	.init		= wakeup_dl_tracer_init,
	.reset		= wakeup_tracer_reset,
	.start		= wakeup_tracer_start,
	.stop		= wakeup_tracer_stop,
	.prपूर्णांक_max	= true,
	.prपूर्णांक_header	= wakeup_prपूर्णांक_header,
	.prपूर्णांक_line	= wakeup_prपूर्णांक_line,
	.flag_changed	= wakeup_flag_changed,
#अगर_घोषित CONFIG_FTRACE_SELFTEST
	.selftest    = trace_selftest_startup_wakeup,
#पूर्ण_अगर
	.खोलो		= wakeup_trace_खोलो,
	.बंद		= wakeup_trace_बंद,
	.allow_instances = true,
	.use_max_tr	= true,
पूर्ण;

__init अटल पूर्णांक init_wakeup_tracer(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_tracer(&wakeup_tracer);
	अगर (ret)
		वापस ret;

	ret = रेजिस्टर_tracer(&wakeup_rt_tracer);
	अगर (ret)
		वापस ret;

	ret = रेजिस्टर_tracer(&wakeup_dl_tracer);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
core_initcall(init_wakeup_tracer);
