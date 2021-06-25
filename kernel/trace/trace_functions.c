<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ring buffer based function tracer
 *
 * Copyright (C) 2007-2008 Steven Rostedt <srostedt@redhat.com>
 * Copyright (C) 2008 Ingo Molnar <mingo@redhat.com>
 *
 * Based on code from the latency_tracer, that is:
 *
 *  Copyright (C) 2004-2006 Ingo Molnar
 *  Copyright (C) 2004 Nadia Yvette Chambers
 */
#समावेश <linux/ring_buffer.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>

#समावेश "trace.h"

अटल व्योम tracing_start_function_trace(काष्ठा trace_array *tr);
अटल व्योम tracing_stop_function_trace(काष्ठा trace_array *tr);
अटल व्योम
function_trace_call(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		    काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *fregs);
अटल व्योम
function_stack_trace_call(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
			  काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *fregs);
अटल व्योम
function_no_repeats_trace_call(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
			       काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *fregs);
अटल व्योम
function_stack_no_repeats_trace_call(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
				     काष्ठा ftrace_ops *op,
				     काष्ठा ftrace_regs *fregs);
अटल काष्ठा tracer_flags func_flags;

/* Our option */
क्रमागत अणु

	TRACE_FUNC_NO_OPTS		= 0x0, /* No flags set. */
	TRACE_FUNC_OPT_STACK		= 0x1,
	TRACE_FUNC_OPT_NO_REPEATS	= 0x2,

	/* Update this to next highest bit. */
	TRACE_FUNC_OPT_HIGHEST_BIT	= 0x4
पूर्ण;

#घोषणा TRACE_FUNC_OPT_MASK	(TRACE_FUNC_OPT_HIGHEST_BIT - 1)

पूर्णांक ftrace_allocate_ftrace_ops(काष्ठा trace_array *tr)
अणु
	काष्ठा ftrace_ops *ops;

	/* The top level array uses the "global_ops" */
	अगर (tr->flags & TRACE_ARRAY_FL_GLOBAL)
		वापस 0;

	ops = kzalloc(माप(*ops), GFP_KERNEL);
	अगर (!ops)
		वापस -ENOMEM;

	/* Currently only the non stack version is supported */
	ops->func = function_trace_call;
	ops->flags = FTRACE_OPS_FL_PID;

	tr->ops = ops;
	ops->निजी = tr;

	वापस 0;
पूर्ण

व्योम ftrace_मुक्त_ftrace_ops(काष्ठा trace_array *tr)
अणु
	kमुक्त(tr->ops);
	tr->ops = शून्य;
पूर्ण

पूर्णांक ftrace_create_function_files(काष्ठा trace_array *tr,
				 काष्ठा dentry *parent)
अणु
	/*
	 * The top level array uses the "global_ops", and the files are
	 * created on boot up.
	 */
	अगर (tr->flags & TRACE_ARRAY_FL_GLOBAL)
		वापस 0;

	अगर (!tr->ops)
		वापस -EINVAL;

	ftrace_create_filter_files(tr->ops, parent);

	वापस 0;
पूर्ण

व्योम ftrace_destroy_function_files(काष्ठा trace_array *tr)
अणु
	ftrace_destroy_filter_files(tr->ops);
	ftrace_मुक्त_ftrace_ops(tr);
पूर्ण

अटल ftrace_func_t select_trace_function(u32 flags_val)
अणु
	चयन (flags_val & TRACE_FUNC_OPT_MASK) अणु
	हाल TRACE_FUNC_NO_OPTS:
		वापस function_trace_call;
	हाल TRACE_FUNC_OPT_STACK:
		वापस function_stack_trace_call;
	हाल TRACE_FUNC_OPT_NO_REPEATS:
		वापस function_no_repeats_trace_call;
	हाल TRACE_FUNC_OPT_STACK | TRACE_FUNC_OPT_NO_REPEATS:
		वापस function_stack_no_repeats_trace_call;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल bool handle_func_repeats(काष्ठा trace_array *tr, u32 flags_val)
अणु
	अगर (!tr->last_func_repeats &&
	    (flags_val & TRACE_FUNC_OPT_NO_REPEATS)) अणु
		tr->last_func_repeats = alloc_percpu(काष्ठा trace_func_repeats);
		अगर (!tr->last_func_repeats)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक function_trace_init(काष्ठा trace_array *tr)
अणु
	ftrace_func_t func;
	/*
	 * Instance trace_arrays get their ops allocated
	 * at instance creation. Unless it failed
	 * the allocation.
	 */
	अगर (!tr->ops)
		वापस -ENOMEM;

	func = select_trace_function(func_flags.val);
	अगर (!func)
		वापस -EINVAL;

	अगर (!handle_func_repeats(tr, func_flags.val))
		वापस -ENOMEM;

	ftrace_init_array_ops(tr, func);

	tr->array_buffer.cpu = raw_smp_processor_id();

	tracing_start_cmdline_record();
	tracing_start_function_trace(tr);
	वापस 0;
पूर्ण

अटल व्योम function_trace_reset(काष्ठा trace_array *tr)
अणु
	tracing_stop_function_trace(tr);
	tracing_stop_cmdline_record();
	ftrace_reset_array_ops(tr);
पूर्ण

अटल व्योम function_trace_start(काष्ठा trace_array *tr)
अणु
	tracing_reset_online_cpus(&tr->array_buffer);
पूर्ण

अटल व्योम
function_trace_call(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		    काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा trace_array *tr = op->निजी;
	काष्ठा trace_array_cpu *data;
	अचिन्हित पूर्णांक trace_ctx;
	पूर्णांक bit;
	पूर्णांक cpu;

	अगर (unlikely(!tr->function_enabled))
		वापस;

	bit = ftrace_test_recursion_trylock(ip, parent_ip);
	अगर (bit < 0)
		वापस;

	trace_ctx = tracing_gen_ctx();
	preempt_disable_notrace();

	cpu = smp_processor_id();
	data = per_cpu_ptr(tr->array_buffer.data, cpu);
	अगर (!atomic_पढ़ो(&data->disabled))
		trace_function(tr, ip, parent_ip, trace_ctx);

	ftrace_test_recursion_unlock(bit);
	preempt_enable_notrace();
पूर्ण

#अगर_घोषित CONFIG_UNWINDER_ORC
/*
 * Skip 2:
 *
 *   function_stack_trace_call()
 *   ftrace_call()
 */
#घोषणा STACK_SKIP 2
#अन्यथा
/*
 * Skip 3:
 *   __trace_stack()
 *   function_stack_trace_call()
 *   ftrace_call()
 */
#घोषणा STACK_SKIP 3
#पूर्ण_अगर

अटल व्योम
function_stack_trace_call(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
			  काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा trace_array *tr = op->निजी;
	काष्ठा trace_array_cpu *data;
	अचिन्हित दीर्घ flags;
	दीर्घ disabled;
	पूर्णांक cpu;
	अचिन्हित पूर्णांक trace_ctx;

	अगर (unlikely(!tr->function_enabled))
		वापस;

	/*
	 * Need to use raw, since this must be called beक्रमe the
	 * recursive protection is perक्रमmed.
	 */
	local_irq_save(flags);
	cpu = raw_smp_processor_id();
	data = per_cpu_ptr(tr->array_buffer.data, cpu);
	disabled = atomic_inc_वापस(&data->disabled);

	अगर (likely(disabled == 1)) अणु
		trace_ctx = tracing_gen_ctx_flags(flags);
		trace_function(tr, ip, parent_ip, trace_ctx);
		__trace_stack(tr, trace_ctx, STACK_SKIP);
	पूर्ण

	atomic_dec(&data->disabled);
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत bool is_repeat_check(काष्ठा trace_array *tr,
				   काष्ठा trace_func_repeats *last_info,
				   अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip)
अणु
	अगर (last_info->ip == ip &&
	    last_info->parent_ip == parent_ip &&
	    last_info->count < U16_MAX) अणु
		last_info->ts_last_call =
			ring_buffer_समय_stamp(tr->array_buffer.buffer);
		last_info->count++;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत व्योम process_repeats(काष्ठा trace_array *tr,
				   अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
				   काष्ठा trace_func_repeats *last_info,
				   अचिन्हित पूर्णांक trace_ctx)
अणु
	अगर (last_info->count) अणु
		trace_last_func_repeats(tr, last_info, trace_ctx);
		last_info->count = 0;
	पूर्ण

	last_info->ip = ip;
	last_info->parent_ip = parent_ip;
पूर्ण

अटल व्योम
function_no_repeats_trace_call(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
			       काष्ठा ftrace_ops *op,
			       काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा trace_func_repeats *last_info;
	काष्ठा trace_array *tr = op->निजी;
	काष्ठा trace_array_cpu *data;
	अचिन्हित पूर्णांक trace_ctx;
	अचिन्हित दीर्घ flags;
	पूर्णांक bit;
	पूर्णांक cpu;

	अगर (unlikely(!tr->function_enabled))
		वापस;

	bit = ftrace_test_recursion_trylock(ip, parent_ip);
	अगर (bit < 0)
		वापस;

	preempt_disable_notrace();

	cpu = smp_processor_id();
	data = per_cpu_ptr(tr->array_buffer.data, cpu);
	अगर (atomic_पढ़ो(&data->disabled))
		जाओ out;

	/*
	 * An पूर्णांकerrupt may happen at any place here. But as far as I can see,
	 * the only damage that this can cause is to mess up the repetition
	 * counter without valuable data being lost.
	 * TODO: think about a solution that is better than just hoping to be
	 * lucky.
	 */
	last_info = per_cpu_ptr(tr->last_func_repeats, cpu);
	अगर (is_repeat_check(tr, last_info, ip, parent_ip))
		जाओ out;

	local_save_flags(flags);
	trace_ctx = tracing_gen_ctx_flags(flags);
	process_repeats(tr, ip, parent_ip, last_info, trace_ctx);

	trace_function(tr, ip, parent_ip, trace_ctx);

out:
	ftrace_test_recursion_unlock(bit);
	preempt_enable_notrace();
पूर्ण

अटल व्योम
function_stack_no_repeats_trace_call(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
				     काष्ठा ftrace_ops *op,
				     काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा trace_func_repeats *last_info;
	काष्ठा trace_array *tr = op->निजी;
	काष्ठा trace_array_cpu *data;
	अचिन्हित दीर्घ flags;
	दीर्घ disabled;
	पूर्णांक cpu;
	अचिन्हित पूर्णांक trace_ctx;

	अगर (unlikely(!tr->function_enabled))
		वापस;

	/*
	 * Need to use raw, since this must be called beक्रमe the
	 * recursive protection is perक्रमmed.
	 */
	local_irq_save(flags);
	cpu = raw_smp_processor_id();
	data = per_cpu_ptr(tr->array_buffer.data, cpu);
	disabled = atomic_inc_वापस(&data->disabled);

	अगर (likely(disabled == 1)) अणु
		last_info = per_cpu_ptr(tr->last_func_repeats, cpu);
		अगर (is_repeat_check(tr, last_info, ip, parent_ip))
			जाओ out;

		trace_ctx = tracing_gen_ctx_flags(flags);
		process_repeats(tr, ip, parent_ip, last_info, trace_ctx);

		trace_function(tr, ip, parent_ip, trace_ctx);
		__trace_stack(tr, trace_ctx, STACK_SKIP);
	पूर्ण

 out:
	atomic_dec(&data->disabled);
	local_irq_restore(flags);
पूर्ण

अटल काष्ठा tracer_opt func_opts[] = अणु
#अगर_घोषित CONFIG_STACKTRACE
	अणु TRACER_OPT(func_stack_trace, TRACE_FUNC_OPT_STACK) पूर्ण,
#पूर्ण_अगर
	अणु TRACER_OPT(func-no-repeats, TRACE_FUNC_OPT_NO_REPEATS) पूर्ण,
	अणु पूर्ण /* Always set a last empty entry */
पूर्ण;

अटल काष्ठा tracer_flags func_flags = अणु
	.val = TRACE_FUNC_NO_OPTS, /* By शेष: all flags disabled */
	.opts = func_opts
पूर्ण;

अटल व्योम tracing_start_function_trace(काष्ठा trace_array *tr)
अणु
	tr->function_enabled = 0;
	रेजिस्टर_ftrace_function(tr->ops);
	tr->function_enabled = 1;
पूर्ण

अटल व्योम tracing_stop_function_trace(काष्ठा trace_array *tr)
अणु
	tr->function_enabled = 0;
	unरेजिस्टर_ftrace_function(tr->ops);
पूर्ण

अटल काष्ठा tracer function_trace;

अटल पूर्णांक
func_set_flag(काष्ठा trace_array *tr, u32 old_flags, u32 bit, पूर्णांक set)
अणु
	ftrace_func_t func;
	u32 new_flags;

	/* Do nothing अगर alपढ़ोy set. */
	अगर (!!set == !!(func_flags.val & bit))
		वापस 0;

	/* We can change this flag only when not running. */
	अगर (tr->current_trace != &function_trace)
		वापस 0;

	new_flags = (func_flags.val & ~bit) | (set ? bit : 0);
	func = select_trace_function(new_flags);
	अगर (!func)
		वापस -EINVAL;

	/* Check अगर there's anything to change. */
	अगर (tr->ops->func == func)
		वापस 0;

	अगर (!handle_func_repeats(tr, new_flags))
		वापस -ENOMEM;

	unरेजिस्टर_ftrace_function(tr->ops);
	tr->ops->func = func;
	रेजिस्टर_ftrace_function(tr->ops);

	वापस 0;
पूर्ण

अटल काष्ठा tracer function_trace __tracer_data =
अणु
	.name		= "function",
	.init		= function_trace_init,
	.reset		= function_trace_reset,
	.start		= function_trace_start,
	.flags		= &func_flags,
	.set_flag	= func_set_flag,
	.allow_instances = true,
#अगर_घोषित CONFIG_FTRACE_SELFTEST
	.selftest	= trace_selftest_startup_function,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
अटल व्योम update_traceon_count(काष्ठा ftrace_probe_ops *ops,
				 अचिन्हित दीर्घ ip,
				 काष्ठा trace_array *tr, bool on,
				 व्योम *data)
अणु
	काष्ठा ftrace_func_mapper *mapper = data;
	दीर्घ *count;
	दीर्घ old_count;

	/*
	 * Tracing माला_लो disabled (or enabled) once per count.
	 * This function can be called at the same समय on multiple CPUs.
	 * It is fine अगर both disable (or enable) tracing, as disabling
	 * (or enabling) the second समय करोesn't करो anything as the
	 * state of the tracer is alपढ़ोy disabled (or enabled).
	 * What needs to be synchronized in this हाल is that the count
	 * only माला_लो decremented once, even अगर the tracer is disabled
	 * (or enabled) twice, as the second one is really a nop.
	 *
	 * The memory barriers guarantee that we only decrement the
	 * counter once. First the count is पढ़ो to a local variable
	 * and a पढ़ो barrier is used to make sure that it is loaded
	 * beक्रमe checking अगर the tracer is in the state we want.
	 * If the tracer is not in the state we want, then the count
	 * is guaranteed to be the old count.
	 *
	 * Next the tracer is set to the state we want (disabled or enabled)
	 * then a ग_लिखो memory barrier is used to make sure that
	 * the new state is visible beक्रमe changing the counter by
	 * one minus the old counter. This guarantees that another CPU
	 * executing this code will see the new state beक्रमe seeing
	 * the new counter value, and would not करो anything अगर the new
	 * counter is seen.
	 *
	 * Note, there is no synchronization between this and a user
	 * setting the tracing_on file. But we currently करोn't care
	 * about that.
	 */
	count = (दीर्घ *)ftrace_func_mapper_find_ip(mapper, ip);
	old_count = *count;

	अगर (old_count <= 0)
		वापस;

	/* Make sure we see count beक्रमe checking tracing state */
	smp_rmb();

	अगर (on == !!tracer_tracing_is_on(tr))
		वापस;

	अगर (on)
		tracer_tracing_on(tr);
	अन्यथा
		tracer_tracing_off(tr);

	/* Make sure tracing state is visible beक्रमe updating count */
	smp_wmb();

	*count = old_count - 1;
पूर्ण

अटल व्योम
ftrace_traceon_count(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		     काष्ठा trace_array *tr, काष्ठा ftrace_probe_ops *ops,
		     व्योम *data)
अणु
	update_traceon_count(ops, ip, tr, 1, data);
पूर्ण

अटल व्योम
ftrace_traceoff_count(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		      काष्ठा trace_array *tr, काष्ठा ftrace_probe_ops *ops,
		      व्योम *data)
अणु
	update_traceon_count(ops, ip, tr, 0, data);
पूर्ण

अटल व्योम
ftrace_traceon(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
	       काष्ठा trace_array *tr, काष्ठा ftrace_probe_ops *ops,
	       व्योम *data)
अणु
	अगर (tracer_tracing_is_on(tr))
		वापस;

	tracer_tracing_on(tr);
पूर्ण

अटल व्योम
ftrace_traceoff(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		काष्ठा trace_array *tr, काष्ठा ftrace_probe_ops *ops,
		व्योम *data)
अणु
	अगर (!tracer_tracing_is_on(tr))
		वापस;

	tracer_tracing_off(tr);
पूर्ण

#अगर_घोषित CONFIG_UNWINDER_ORC
/*
 * Skip 3:
 *
 *   function_trace_probe_call()
 *   ftrace_ops_assist_func()
 *   ftrace_call()
 */
#घोषणा FTRACE_STACK_SKIP 3
#अन्यथा
/*
 * Skip 5:
 *
 *   __trace_stack()
 *   ftrace_stacktrace()
 *   function_trace_probe_call()
 *   ftrace_ops_assist_func()
 *   ftrace_call()
 */
#घोषणा FTRACE_STACK_SKIP 5
#पूर्ण_अगर

अटल __always_अंतरभूत व्योम trace_stack(काष्ठा trace_array *tr)
अणु
	अचिन्हित पूर्णांक trace_ctx;

	trace_ctx = tracing_gen_ctx();

	__trace_stack(tr, trace_ctx, FTRACE_STACK_SKIP);
पूर्ण

अटल व्योम
ftrace_stacktrace(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		  काष्ठा trace_array *tr, काष्ठा ftrace_probe_ops *ops,
		  व्योम *data)
अणु
	trace_stack(tr);
पूर्ण

अटल व्योम
ftrace_stacktrace_count(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
			काष्ठा trace_array *tr, काष्ठा ftrace_probe_ops *ops,
			व्योम *data)
अणु
	काष्ठा ftrace_func_mapper *mapper = data;
	दीर्घ *count;
	दीर्घ old_count;
	दीर्घ new_count;

	अगर (!tracing_is_on())
		वापस;

	/* unlimited? */
	अगर (!mapper) अणु
		trace_stack(tr);
		वापस;
	पूर्ण

	count = (दीर्घ *)ftrace_func_mapper_find_ip(mapper, ip);

	/*
	 * Stack traces should only execute the number of बार the
	 * user specअगरied in the counter.
	 */
	करो अणु
		old_count = *count;

		अगर (!old_count)
			वापस;

		new_count = old_count - 1;
		new_count = cmpxchg(count, old_count, new_count);
		अगर (new_count == old_count)
			trace_stack(tr);

		अगर (!tracing_is_on())
			वापस;

	पूर्ण जबतक (new_count != old_count);
पूर्ण

अटल पूर्णांक update_count(काष्ठा ftrace_probe_ops *ops, अचिन्हित दीर्घ ip,
			व्योम *data)
अणु
	काष्ठा ftrace_func_mapper *mapper = data;
	दीर्घ *count = शून्य;

	अगर (mapper)
		count = (दीर्घ *)ftrace_func_mapper_find_ip(mapper, ip);

	अगर (count) अणु
		अगर (*count <= 0)
			वापस 0;
		(*count)--;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम
ftrace_dump_probe(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		  काष्ठा trace_array *tr, काष्ठा ftrace_probe_ops *ops,
		  व्योम *data)
अणु
	अगर (update_count(ops, ip, data))
		ftrace_dump(DUMP_ALL);
पूर्ण

/* Only dump the current CPU buffer. */
अटल व्योम
ftrace_cpudump_probe(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		     काष्ठा trace_array *tr, काष्ठा ftrace_probe_ops *ops,
		     व्योम *data)
अणु
	अगर (update_count(ops, ip, data))
		ftrace_dump(DUMP_ORIG);
पूर्ण

अटल पूर्णांक
ftrace_probe_prपूर्णांक(स्थिर अक्षर *name, काष्ठा seq_file *m,
		   अचिन्हित दीर्घ ip, काष्ठा ftrace_probe_ops *ops,
		   व्योम *data)
अणु
	काष्ठा ftrace_func_mapper *mapper = data;
	दीर्घ *count = शून्य;

	seq_म_लिखो(m, "%ps:%s", (व्योम *)ip, name);

	अगर (mapper)
		count = (दीर्घ *)ftrace_func_mapper_find_ip(mapper, ip);

	अगर (count)
		seq_म_लिखो(m, ":count=%ld\n", *count);
	अन्यथा
		seq_माला_दो(m, ":unlimited\n");

	वापस 0;
पूर्ण

अटल पूर्णांक
ftrace_traceon_prपूर्णांक(काष्ठा seq_file *m, अचिन्हित दीर्घ ip,
		     काष्ठा ftrace_probe_ops *ops,
		     व्योम *data)
अणु
	वापस ftrace_probe_prपूर्णांक("traceon", m, ip, ops, data);
पूर्ण

अटल पूर्णांक
ftrace_traceoff_prपूर्णांक(काष्ठा seq_file *m, अचिन्हित दीर्घ ip,
			 काष्ठा ftrace_probe_ops *ops, व्योम *data)
अणु
	वापस ftrace_probe_prपूर्णांक("traceoff", m, ip, ops, data);
पूर्ण

अटल पूर्णांक
ftrace_stacktrace_prपूर्णांक(काष्ठा seq_file *m, अचिन्हित दीर्घ ip,
			काष्ठा ftrace_probe_ops *ops, व्योम *data)
अणु
	वापस ftrace_probe_prपूर्णांक("stacktrace", m, ip, ops, data);
पूर्ण

अटल पूर्णांक
ftrace_dump_prपूर्णांक(काष्ठा seq_file *m, अचिन्हित दीर्घ ip,
			काष्ठा ftrace_probe_ops *ops, व्योम *data)
अणु
	वापस ftrace_probe_prपूर्णांक("dump", m, ip, ops, data);
पूर्ण

अटल पूर्णांक
ftrace_cpudump_prपूर्णांक(काष्ठा seq_file *m, अचिन्हित दीर्घ ip,
			काष्ठा ftrace_probe_ops *ops, व्योम *data)
अणु
	वापस ftrace_probe_prपूर्णांक("cpudump", m, ip, ops, data);
पूर्ण


अटल पूर्णांक
ftrace_count_init(काष्ठा ftrace_probe_ops *ops, काष्ठा trace_array *tr,
		  अचिन्हित दीर्घ ip, व्योम *init_data, व्योम **data)
अणु
	काष्ठा ftrace_func_mapper *mapper = *data;

	अगर (!mapper) अणु
		mapper = allocate_ftrace_func_mapper();
		अगर (!mapper)
			वापस -ENOMEM;
		*data = mapper;
	पूर्ण

	वापस ftrace_func_mapper_add_ip(mapper, ip, init_data);
पूर्ण

अटल व्योम
ftrace_count_मुक्त(काष्ठा ftrace_probe_ops *ops, काष्ठा trace_array *tr,
		  अचिन्हित दीर्घ ip, व्योम *data)
अणु
	काष्ठा ftrace_func_mapper *mapper = data;

	अगर (!ip) अणु
		मुक्त_ftrace_func_mapper(mapper, शून्य);
		वापस;
	पूर्ण

	ftrace_func_mapper_हटाओ_ip(mapper, ip);
पूर्ण

अटल काष्ठा ftrace_probe_ops traceon_count_probe_ops = अणु
	.func			= ftrace_traceon_count,
	.prपूर्णांक			= ftrace_traceon_prपूर्णांक,
	.init			= ftrace_count_init,
	.मुक्त			= ftrace_count_मुक्त,
पूर्ण;

अटल काष्ठा ftrace_probe_ops traceoff_count_probe_ops = अणु
	.func			= ftrace_traceoff_count,
	.prपूर्णांक			= ftrace_traceoff_prपूर्णांक,
	.init			= ftrace_count_init,
	.मुक्त			= ftrace_count_मुक्त,
पूर्ण;

अटल काष्ठा ftrace_probe_ops stacktrace_count_probe_ops = अणु
	.func			= ftrace_stacktrace_count,
	.prपूर्णांक			= ftrace_stacktrace_prपूर्णांक,
	.init			= ftrace_count_init,
	.मुक्त			= ftrace_count_मुक्त,
पूर्ण;

अटल काष्ठा ftrace_probe_ops dump_probe_ops = अणु
	.func			= ftrace_dump_probe,
	.prपूर्णांक			= ftrace_dump_prपूर्णांक,
	.init			= ftrace_count_init,
	.मुक्त			= ftrace_count_मुक्त,
पूर्ण;

अटल काष्ठा ftrace_probe_ops cpudump_probe_ops = अणु
	.func			= ftrace_cpudump_probe,
	.prपूर्णांक			= ftrace_cpudump_prपूर्णांक,
पूर्ण;

अटल काष्ठा ftrace_probe_ops traceon_probe_ops = अणु
	.func			= ftrace_traceon,
	.prपूर्णांक			= ftrace_traceon_prपूर्णांक,
पूर्ण;

अटल काष्ठा ftrace_probe_ops traceoff_probe_ops = अणु
	.func			= ftrace_traceoff,
	.prपूर्णांक			= ftrace_traceoff_prपूर्णांक,
पूर्ण;

अटल काष्ठा ftrace_probe_ops stacktrace_probe_ops = अणु
	.func			= ftrace_stacktrace,
	.prपूर्णांक			= ftrace_stacktrace_prपूर्णांक,
पूर्ण;

अटल पूर्णांक
ftrace_trace_probe_callback(काष्ठा trace_array *tr,
			    काष्ठा ftrace_probe_ops *ops,
			    काष्ठा ftrace_hash *hash, अक्षर *glob,
			    अक्षर *cmd, अक्षर *param, पूर्णांक enable)
अणु
	व्योम *count = (व्योम *)-1;
	अक्षर *number;
	पूर्णांक ret;

	/* hash funcs only work with set_ftrace_filter */
	अगर (!enable)
		वापस -EINVAL;

	अगर (glob[0] == '!')
		वापस unरेजिस्टर_ftrace_function_probe_func(glob+1, tr, ops);

	अगर (!param)
		जाओ out_reg;

	number = strsep(&param, ":");

	अगर (!म_माप(number))
		जाओ out_reg;

	/*
	 * We use the callback data field (which is a poपूर्णांकer)
	 * as our counter.
	 */
	ret = kम_से_अदीर्घ(number, 0, (अचिन्हित दीर्घ *)&count);
	अगर (ret)
		वापस ret;

 out_reg:
	ret = रेजिस्टर_ftrace_function_probe(glob, tr, ops, count);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक
ftrace_trace_onoff_callback(काष्ठा trace_array *tr, काष्ठा ftrace_hash *hash,
			    अक्षर *glob, अक्षर *cmd, अक्षर *param, पूर्णांक enable)
अणु
	काष्ठा ftrace_probe_ops *ops;

	अगर (!tr)
		वापस -ENODEV;

	/* we रेजिस्टर both traceon and traceoff to this callback */
	अगर (म_भेद(cmd, "traceon") == 0)
		ops = param ? &traceon_count_probe_ops : &traceon_probe_ops;
	अन्यथा
		ops = param ? &traceoff_count_probe_ops : &traceoff_probe_ops;

	वापस ftrace_trace_probe_callback(tr, ops, hash, glob, cmd,
					   param, enable);
पूर्ण

अटल पूर्णांक
ftrace_stacktrace_callback(काष्ठा trace_array *tr, काष्ठा ftrace_hash *hash,
			   अक्षर *glob, अक्षर *cmd, अक्षर *param, पूर्णांक enable)
अणु
	काष्ठा ftrace_probe_ops *ops;

	अगर (!tr)
		वापस -ENODEV;

	ops = param ? &stacktrace_count_probe_ops : &stacktrace_probe_ops;

	वापस ftrace_trace_probe_callback(tr, ops, hash, glob, cmd,
					   param, enable);
पूर्ण

अटल पूर्णांक
ftrace_dump_callback(काष्ठा trace_array *tr, काष्ठा ftrace_hash *hash,
			   अक्षर *glob, अक्षर *cmd, अक्षर *param, पूर्णांक enable)
अणु
	काष्ठा ftrace_probe_ops *ops;

	अगर (!tr)
		वापस -ENODEV;

	ops = &dump_probe_ops;

	/* Only dump once. */
	वापस ftrace_trace_probe_callback(tr, ops, hash, glob, cmd,
					   "1", enable);
पूर्ण

अटल पूर्णांक
ftrace_cpudump_callback(काष्ठा trace_array *tr, काष्ठा ftrace_hash *hash,
			   अक्षर *glob, अक्षर *cmd, अक्षर *param, पूर्णांक enable)
अणु
	काष्ठा ftrace_probe_ops *ops;

	अगर (!tr)
		वापस -ENODEV;

	ops = &cpudump_probe_ops;

	/* Only dump once. */
	वापस ftrace_trace_probe_callback(tr, ops, hash, glob, cmd,
					   "1", enable);
पूर्ण

अटल काष्ठा ftrace_func_command ftrace_traceon_cmd = अणु
	.name			= "traceon",
	.func			= ftrace_trace_onoff_callback,
पूर्ण;

अटल काष्ठा ftrace_func_command ftrace_traceoff_cmd = अणु
	.name			= "traceoff",
	.func			= ftrace_trace_onoff_callback,
पूर्ण;

अटल काष्ठा ftrace_func_command ftrace_stacktrace_cmd = अणु
	.name			= "stacktrace",
	.func			= ftrace_stacktrace_callback,
पूर्ण;

अटल काष्ठा ftrace_func_command ftrace_dump_cmd = अणु
	.name			= "dump",
	.func			= ftrace_dump_callback,
पूर्ण;

अटल काष्ठा ftrace_func_command ftrace_cpudump_cmd = अणु
	.name			= "cpudump",
	.func			= ftrace_cpudump_callback,
पूर्ण;

अटल पूर्णांक __init init_func_cmd_traceon(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_ftrace_command(&ftrace_traceoff_cmd);
	अगर (ret)
		वापस ret;

	ret = रेजिस्टर_ftrace_command(&ftrace_traceon_cmd);
	अगर (ret)
		जाओ out_मुक्त_traceoff;

	ret = रेजिस्टर_ftrace_command(&ftrace_stacktrace_cmd);
	अगर (ret)
		जाओ out_मुक्त_traceon;

	ret = रेजिस्टर_ftrace_command(&ftrace_dump_cmd);
	अगर (ret)
		जाओ out_मुक्त_stacktrace;

	ret = रेजिस्टर_ftrace_command(&ftrace_cpudump_cmd);
	अगर (ret)
		जाओ out_मुक्त_dump;

	वापस 0;

 out_मुक्त_dump:
	unरेजिस्टर_ftrace_command(&ftrace_dump_cmd);
 out_मुक्त_stacktrace:
	unरेजिस्टर_ftrace_command(&ftrace_stacktrace_cmd);
 out_मुक्त_traceon:
	unरेजिस्टर_ftrace_command(&ftrace_traceon_cmd);
 out_मुक्त_traceoff:
	unरेजिस्टर_ftrace_command(&ftrace_traceoff_cmd);

	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक init_func_cmd_traceon(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

__init पूर्णांक init_function_trace(व्योम)
अणु
	init_func_cmd_traceon();
	वापस रेजिस्टर_tracer(&function_trace);
पूर्ण
