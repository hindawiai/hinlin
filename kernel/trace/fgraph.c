<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Infraकाष्ठाure to took पूर्णांकo function calls and वापसs.
 * Copyright (c) 2008-2009 Frederic Weisbecker <fweisbec@gmail.com>
 * Mostly borrowed from function tracer which
 * is Copyright (c) Steven Rostedt <srostedt@redhat.com>
 *
 * Highly modअगरied by Steven Rostedt (VMware).
 */
#समावेश <linux/suspend.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/slab.h>

#समावेश <trace/events/sched.h>

#समावेश "ftrace_internal.h"

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
#घोषणा ASSIGN_OPS_HASH(opsname, val) \
	.func_hash		= val, \
	.local_hash.regex_lock	= __MUTEX_INITIALIZER(opsname.local_hash.regex_lock),
#अन्यथा
#घोषणा ASSIGN_OPS_HASH(opsname, val)
#पूर्ण_अगर

अटल bool समाप्त_ftrace_graph;
पूर्णांक ftrace_graph_active;

/* Both enabled by शेष (can be cleared by function_graph tracer flags */
अटल bool fgraph_sleep_समय = true;

/**
 * ftrace_graph_is_dead - वापसs true अगर ftrace_graph_stop() was called
 *
 * ftrace_graph_stop() is called when a severe error is detected in
 * the function graph tracing. This function is called by the critical
 * paths of function graph to keep those paths from करोing any more harm.
 */
bool ftrace_graph_is_dead(व्योम)
अणु
	वापस समाप्त_ftrace_graph;
पूर्ण

/**
 * ftrace_graph_stop - set to permanently disable function graph tracing
 *
 * In हाल of an error पूर्णांक function graph tracing, this is called
 * to try to keep function graph tracing from causing any more harm.
 * Usually this is pretty severe and this is called to try to at least
 * get a warning out to the user.
 */
व्योम ftrace_graph_stop(व्योम)
अणु
	समाप्त_ftrace_graph = true;
पूर्ण

/* Add a function वापस address to the trace stack on thपढ़ो info.*/
अटल पूर्णांक
ftrace_push_वापस_trace(अचिन्हित दीर्घ ret, अचिन्हित दीर्घ func,
			 अचिन्हित दीर्घ frame_poपूर्णांकer, अचिन्हित दीर्घ *retp)
अणु
	अचिन्हित दीर्घ दीर्घ callसमय;
	पूर्णांक index;

	अगर (unlikely(ftrace_graph_is_dead()))
		वापस -EBUSY;

	अगर (!current->ret_stack)
		वापस -EBUSY;

	/*
	 * We must make sure the ret_stack is tested beक्रमe we पढ़ो
	 * anything अन्यथा.
	 */
	smp_rmb();

	/* The वापस trace stack is full */
	अगर (current->curr_ret_stack == FTRACE_RETFUNC_DEPTH - 1) अणु
		atomic_inc(&current->trace_overrun);
		वापस -EBUSY;
	पूर्ण

	callसमय = trace_घड़ी_local();

	index = ++current->curr_ret_stack;
	barrier();
	current->ret_stack[index].ret = ret;
	current->ret_stack[index].func = func;
	current->ret_stack[index].callसमय = callसमय;
#अगर_घोषित HAVE_FUNCTION_GRAPH_FP_TEST
	current->ret_stack[index].fp = frame_poपूर्णांकer;
#पूर्ण_अगर
#अगर_घोषित HAVE_FUNCTION_GRAPH_RET_ADDR_PTR
	current->ret_stack[index].retp = retp;
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * Not all archs define MCOUNT_INSN_SIZE which is used to look क्रम direct
 * functions. But those archs currently करोn't support direct functions
 * anyway, and ftrace_find_rec_direct() is just a stub क्रम them.
 * Define MCOUNT_INSN_SIZE to keep those archs compiling.
 */
#अगर_अघोषित MCOUNT_INSN_SIZE
/* Make sure this only works without direct calls */
# अगरdef CONFIG_DYNAMIC_FTRACE_WITH_सूचीECT_CALLS
#  error MCOUNT_INSN_SIZE not defined with direct calls enabled
# endअगर
# define MCOUNT_INSN_SIZE 0
#पूर्ण_अगर

पूर्णांक function_graph_enter(अचिन्हित दीर्घ ret, अचिन्हित दीर्घ func,
			 अचिन्हित दीर्घ frame_poपूर्णांकer, अचिन्हित दीर्घ *retp)
अणु
	काष्ठा ftrace_graph_ent trace;

	/*
	 * Skip graph tracing अगर the वापस location is served by direct trampoline,
	 * since call sequence and वापस addresses are unpredictable anyway.
	 * Ex: BPF trampoline may call original function and may skip frame
	 * depending on type of BPF programs attached.
	 */
	अगर (ftrace_direct_func_count &&
	    ftrace_find_rec_direct(ret - MCOUNT_INSN_SIZE))
		वापस -EBUSY;
	trace.func = func;
	trace.depth = ++current->curr_ret_depth;

	अगर (ftrace_push_वापस_trace(ret, func, frame_poपूर्णांकer, retp))
		जाओ out;

	/* Only trace अगर the calling function expects to */
	अगर (!ftrace_graph_entry(&trace))
		जाओ out_ret;

	वापस 0;
 out_ret:
	current->curr_ret_stack--;
 out:
	current->curr_ret_depth--;
	वापस -EBUSY;
पूर्ण

/* Retrieve a function वापस address to the trace stack on thपढ़ो info.*/
अटल व्योम
ftrace_pop_वापस_trace(काष्ठा ftrace_graph_ret *trace, अचिन्हित दीर्घ *ret,
			अचिन्हित दीर्घ frame_poपूर्णांकer)
अणु
	पूर्णांक index;

	index = current->curr_ret_stack;

	अगर (unlikely(index < 0 || index >= FTRACE_RETFUNC_DEPTH)) अणु
		ftrace_graph_stop();
		WARN_ON(1);
		/* Might as well panic, otherwise we have no where to go */
		*ret = (अचिन्हित दीर्घ)panic;
		वापस;
	पूर्ण

#अगर_घोषित HAVE_FUNCTION_GRAPH_FP_TEST
	/*
	 * The arch may choose to record the frame poपूर्णांकer used
	 * and check it here to make sure that it is what we expect it
	 * to be. If gcc करोes not set the place holder of the वापस
	 * address in the frame poपूर्णांकer, and करोes a copy instead, then
	 * the function graph trace will fail. This test detects this
	 * हाल.
	 *
	 * Currently, x86_32 with optimize क्रम size (-Os) makes the latest
	 * gcc करो the above.
	 *
	 * Note, -mfentry करोes not use frame poपूर्णांकers, and this test
	 *  is not needed अगर CC_USING_FENTRY is set.
	 */
	अगर (unlikely(current->ret_stack[index].fp != frame_poपूर्णांकer)) अणु
		ftrace_graph_stop();
		WARN(1, "Bad frame pointer: expected %lx, received %lx\n"
		     "  from func %ps return to %lx\n",
		     current->ret_stack[index].fp,
		     frame_poपूर्णांकer,
		     (व्योम *)current->ret_stack[index].func,
		     current->ret_stack[index].ret);
		*ret = (अचिन्हित दीर्घ)panic;
		वापस;
	पूर्ण
#पूर्ण_अगर

	*ret = current->ret_stack[index].ret;
	trace->func = current->ret_stack[index].func;
	trace->callसमय = current->ret_stack[index].callसमय;
	trace->overrun = atomic_पढ़ो(&current->trace_overrun);
	trace->depth = current->curr_ret_depth--;
	/*
	 * We still want to trace पूर्णांकerrupts coming in अगर
	 * max_depth is set to 1. Make sure the decrement is
	 * seen beक्रमe ftrace_graph_वापस.
	 */
	barrier();
पूर्ण

/*
 * Hibernation protection.
 * The state of the current task is too much unstable during
 * suspend/restore to disk. We want to protect against that.
 */
अटल पूर्णांक
ftrace_suspend_notअगरier_call(काष्ठा notअगरier_block *bl, अचिन्हित दीर्घ state,
							व्योम *unused)
अणु
	चयन (state) अणु
	हाल PM_HIBERNATION_PREPARE:
		छोड़ो_graph_tracing();
		अवरोध;

	हाल PM_POST_HIBERNATION:
		unछोड़ो_graph_tracing();
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block ftrace_suspend_notअगरier = अणु
	.notअगरier_call = ftrace_suspend_notअगरier_call,
पूर्ण;

/*
 * Send the trace to the ring-buffer.
 * @वापस the original वापस address.
 */
अचिन्हित दीर्घ ftrace_वापस_to_handler(अचिन्हित दीर्घ frame_poपूर्णांकer)
अणु
	काष्ठा ftrace_graph_ret trace;
	अचिन्हित दीर्घ ret;

	ftrace_pop_वापस_trace(&trace, &ret, frame_poपूर्णांकer);
	trace.retसमय = trace_घड़ी_local();
	ftrace_graph_वापस(&trace);
	/*
	 * The ftrace_graph_वापस() may still access the current
	 * ret_stack काष्ठाure, we need to make sure the update of
	 * curr_ret_stack is after that.
	 */
	barrier();
	current->curr_ret_stack--;

	अगर (unlikely(!ret)) अणु
		ftrace_graph_stop();
		WARN_ON(1);
		/* Might as well panic. What अन्यथा to करो? */
		ret = (अचिन्हित दीर्घ)panic;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ftrace_graph_get_ret_stack - वापस the entry of the shaकरोw stack
 * @task: The task to पढ़ो the shaकरोw stack from
 * @idx: Index करोwn the shaकरोw stack
 *
 * Return the ret_काष्ठा on the shaकरोw stack of the @task at the
 * call graph at @idx starting with zero. If @idx is zero, it
 * will वापस the last saved ret_stack entry. If it is greater than
 * zero, it will वापस the corresponding ret_stack क्रम the depth
 * of saved वापस addresses.
 */
काष्ठा ftrace_ret_stack *
ftrace_graph_get_ret_stack(काष्ठा task_काष्ठा *task, पूर्णांक idx)
अणु
	idx = task->curr_ret_stack - idx;

	अगर (idx >= 0 && idx <= task->curr_ret_stack)
		वापस &task->ret_stack[idx];

	वापस शून्य;
पूर्ण

/**
 * ftrace_graph_ret_addr - convert a potentially modअगरied stack वापस address
 *			   to its original value
 *
 * This function can be called by stack unwinding code to convert a found stack
 * वापस address ('ret') to its original value, in हाल the function graph
 * tracer has modअगरied it to be 'return_to_handler'.  If the address hasn't
 * been modअगरied, the unchanged value of 'ret' is वापसed.
 *
 * 'idx' is a state variable which should be initialized by the caller to zero
 * beक्रमe the first call.
 *
 * 'retp' is a pointer to the return address on the stack.  It's ignored अगर
 * the arch करोesn't have HAVE_FUNCTION_GRAPH_RET_ADDR_PTR defined.
 */
#अगर_घोषित HAVE_FUNCTION_GRAPH_RET_ADDR_PTR
अचिन्हित दीर्घ ftrace_graph_ret_addr(काष्ठा task_काष्ठा *task, पूर्णांक *idx,
				    अचिन्हित दीर्घ ret, अचिन्हित दीर्घ *retp)
अणु
	पूर्णांक index = task->curr_ret_stack;
	पूर्णांक i;

	अगर (ret != (अचिन्हित दीर्घ)dereference_kernel_function_descriptor(वापस_to_handler))
		वापस ret;

	अगर (index < 0)
		वापस ret;

	क्रम (i = 0; i <= index; i++)
		अगर (task->ret_stack[i].retp == retp)
			वापस task->ret_stack[i].ret;

	वापस ret;
पूर्ण
#अन्यथा /* !HAVE_FUNCTION_GRAPH_RET_ADDR_PTR */
अचिन्हित दीर्घ ftrace_graph_ret_addr(काष्ठा task_काष्ठा *task, पूर्णांक *idx,
				    अचिन्हित दीर्घ ret, अचिन्हित दीर्घ *retp)
अणु
	पूर्णांक task_idx;

	अगर (ret != (अचिन्हित दीर्घ)dereference_kernel_function_descriptor(वापस_to_handler))
		वापस ret;

	task_idx = task->curr_ret_stack;

	अगर (!task->ret_stack || task_idx < *idx)
		वापस ret;

	task_idx -= *idx;
	(*idx)++;

	वापस task->ret_stack[task_idx].ret;
पूर्ण
#पूर्ण_अगर /* HAVE_FUNCTION_GRAPH_RET_ADDR_PTR */

अटल काष्ठा ftrace_ops graph_ops = अणु
	.func			= ftrace_stub,
	.flags			= FTRACE_OPS_FL_INITIALIZED |
				   FTRACE_OPS_FL_PID |
				   FTRACE_OPS_FL_STUB,
#अगर_घोषित FTRACE_GRAPH_TRAMP_ADDR
	.trampoline		= FTRACE_GRAPH_TRAMP_ADDR,
	/* trampoline_size is only needed क्रम dynamically allocated tramps */
#पूर्ण_अगर
	ASSIGN_OPS_HASH(graph_ops, &global_ops.local_hash)
पूर्ण;

व्योम ftrace_graph_sleep_समय_control(bool enable)
अणु
	fgraph_sleep_समय = enable;
पूर्ण

पूर्णांक ftrace_graph_entry_stub(काष्ठा ftrace_graph_ent *trace)
अणु
	वापस 0;
पूर्ण

/*
 * Simply poपूर्णांकs to ftrace_stub, but with the proper protocol.
 * Defined by the linker script in linux/vmlinux.lds.h
 */
बाह्य व्योम ftrace_stub_graph(काष्ठा ftrace_graph_ret *);

/* The callbacks that hook a function */
trace_func_graph_ret_t ftrace_graph_वापस = ftrace_stub_graph;
trace_func_graph_ent_t ftrace_graph_entry = ftrace_graph_entry_stub;
अटल trace_func_graph_ent_t __ftrace_graph_entry = ftrace_graph_entry_stub;

/* Try to assign a वापस stack array on FTRACE_RETSTACK_ALLOC_SIZE tasks. */
अटल पूर्णांक alloc_retstack_tasklist(काष्ठा ftrace_ret_stack **ret_stack_list)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	पूर्णांक start = 0, end = FTRACE_RETSTACK_ALLOC_SIZE;
	काष्ठा task_काष्ठा *g, *t;

	क्रम (i = 0; i < FTRACE_RETSTACK_ALLOC_SIZE; i++) अणु
		ret_stack_list[i] =
			kदो_स्मृति_array(FTRACE_RETFUNC_DEPTH,
				      माप(काष्ठा ftrace_ret_stack),
				      GFP_KERNEL);
		अगर (!ret_stack_list[i]) अणु
			start = 0;
			end = i;
			ret = -ENOMEM;
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_lock();
	क्रम_each_process_thपढ़ो(g, t) अणु
		अगर (start == end) अणु
			ret = -EAGAIN;
			जाओ unlock;
		पूर्ण

		अगर (t->ret_stack == शून्य) अणु
			atomic_set(&t->trace_overrun, 0);
			t->curr_ret_stack = -1;
			t->curr_ret_depth = -1;
			/* Make sure the tasks see the -1 first: */
			smp_wmb();
			t->ret_stack = ret_stack_list[start++];
		पूर्ण
	पूर्ण

unlock:
	rcu_पढ़ो_unlock();
मुक्त:
	क्रम (i = start; i < end; i++)
		kमुक्त(ret_stack_list[i]);
	वापस ret;
पूर्ण

अटल व्योम
ftrace_graph_probe_sched_चयन(व्योम *ignore, bool preempt,
			काष्ठा task_काष्ठा *prev, काष्ठा task_काष्ठा *next)
अणु
	अचिन्हित दीर्घ दीर्घ बारtamp;
	पूर्णांक index;

	/*
	 * Does the user want to count the समय a function was asleep.
	 * If so, करो not update the समय stamps.
	 */
	अगर (fgraph_sleep_समय)
		वापस;

	बारtamp = trace_घड़ी_local();

	prev->ftrace_बारtamp = बारtamp;

	/* only process tasks that we बारtamped */
	अगर (!next->ftrace_बारtamp)
		वापस;

	/*
	 * Update all the counters in next to make up क्रम the
	 * समय next was sleeping.
	 */
	बारtamp -= next->ftrace_बारtamp;

	क्रम (index = next->curr_ret_stack; index >= 0; index--)
		next->ret_stack[index].callसमय += बारtamp;
पूर्ण

अटल पूर्णांक ftrace_graph_entry_test(काष्ठा ftrace_graph_ent *trace)
अणु
	अगर (!ftrace_ops_test(&global_ops, trace->func, शून्य))
		वापस 0;
	वापस __ftrace_graph_entry(trace);
पूर्ण

/*
 * The function graph tracer should only trace the functions defined
 * by set_ftrace_filter and set_ftrace_notrace. If another function
 * tracer ops is रेजिस्टरed, the graph tracer requires testing the
 * function against the global ops, and not just trace any function
 * that any ftrace_ops रेजिस्टरed.
 */
व्योम update_function_graph_func(व्योम)
अणु
	काष्ठा ftrace_ops *op;
	bool करो_test = false;

	/*
	 * The graph and global ops share the same set of functions
	 * to test. If any other ops is on the list, then
	 * the graph tracing needs to test अगर its the function
	 * it should call.
	 */
	करो_क्रम_each_ftrace_op(op, ftrace_ops_list) अणु
		अगर (op != &global_ops && op != &graph_ops &&
		    op != &ftrace_list_end) अणु
			करो_test = true;
			/* in द्विगुन loop, अवरोध out with जाओ */
			जाओ out;
		पूर्ण
	पूर्ण जबतक_क्रम_each_ftrace_op(op);
 out:
	अगर (करो_test)
		ftrace_graph_entry = ftrace_graph_entry_test;
	अन्यथा
		ftrace_graph_entry = __ftrace_graph_entry;
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा ftrace_ret_stack *, idle_ret_stack);

अटल व्योम
graph_init_task(काष्ठा task_काष्ठा *t, काष्ठा ftrace_ret_stack *ret_stack)
अणु
	atomic_set(&t->trace_overrun, 0);
	t->ftrace_बारtamp = 0;
	/* make curr_ret_stack visible beक्रमe we add the ret_stack */
	smp_wmb();
	t->ret_stack = ret_stack;
पूर्ण

/*
 * Allocate a वापस stack क्रम the idle task. May be the first
 * समय through, or it may be करोne by CPU hotplug online.
 */
व्योम ftrace_graph_init_idle_task(काष्ठा task_काष्ठा *t, पूर्णांक cpu)
अणु
	t->curr_ret_stack = -1;
	t->curr_ret_depth = -1;
	/*
	 * The idle task has no parent, it either has its own
	 * stack or no stack at all.
	 */
	अगर (t->ret_stack)
		WARN_ON(t->ret_stack != per_cpu(idle_ret_stack, cpu));

	अगर (ftrace_graph_active) अणु
		काष्ठा ftrace_ret_stack *ret_stack;

		ret_stack = per_cpu(idle_ret_stack, cpu);
		अगर (!ret_stack) अणु
			ret_stack =
				kदो_स्मृति_array(FTRACE_RETFUNC_DEPTH,
					      माप(काष्ठा ftrace_ret_stack),
					      GFP_KERNEL);
			अगर (!ret_stack)
				वापस;
			per_cpu(idle_ret_stack, cpu) = ret_stack;
		पूर्ण
		graph_init_task(t, ret_stack);
	पूर्ण
पूर्ण

/* Allocate a वापस stack क्रम newly created task */
व्योम ftrace_graph_init_task(काष्ठा task_काष्ठा *t)
अणु
	/* Make sure we करो not use the parent ret_stack */
	t->ret_stack = शून्य;
	t->curr_ret_stack = -1;
	t->curr_ret_depth = -1;

	अगर (ftrace_graph_active) अणु
		काष्ठा ftrace_ret_stack *ret_stack;

		ret_stack = kदो_स्मृति_array(FTRACE_RETFUNC_DEPTH,
					  माप(काष्ठा ftrace_ret_stack),
					  GFP_KERNEL);
		अगर (!ret_stack)
			वापस;
		graph_init_task(t, ret_stack);
	पूर्ण
पूर्ण

व्योम ftrace_graph_निकास_task(काष्ठा task_काष्ठा *t)
अणु
	काष्ठा ftrace_ret_stack	*ret_stack = t->ret_stack;

	t->ret_stack = शून्य;
	/* शून्य must become visible to IRQs beक्रमe we मुक्त it: */
	barrier();

	kमुक्त(ret_stack);
पूर्ण

/* Allocate a वापस stack क्रम each task */
अटल पूर्णांक start_graph_tracing(व्योम)
अणु
	काष्ठा ftrace_ret_stack **ret_stack_list;
	पूर्णांक ret, cpu;

	ret_stack_list = kदो_स्मृति_array(FTRACE_RETSTACK_ALLOC_SIZE,
				       माप(काष्ठा ftrace_ret_stack *),
				       GFP_KERNEL);

	अगर (!ret_stack_list)
		वापस -ENOMEM;

	/* The cpu_boot init_task->ret_stack will never be मुक्तd */
	क्रम_each_online_cpu(cpu) अणु
		अगर (!idle_task(cpu)->ret_stack)
			ftrace_graph_init_idle_task(idle_task(cpu), cpu);
	पूर्ण

	करो अणु
		ret = alloc_retstack_tasklist(ret_stack_list);
	पूर्ण जबतक (ret == -EAGAIN);

	अगर (!ret) अणु
		ret = रेजिस्टर_trace_sched_चयन(ftrace_graph_probe_sched_चयन, शून्य);
		अगर (ret)
			pr_info("ftrace_graph: Couldn't activate tracepoint"
				" probe to kernel_sched_switch\n");
	पूर्ण

	kमुक्त(ret_stack_list);
	वापस ret;
पूर्ण

पूर्णांक रेजिस्टर_ftrace_graph(काष्ठा fgraph_ops *gops)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&ftrace_lock);

	/* we currently allow only one tracer रेजिस्टरed at a समय */
	अगर (ftrace_graph_active) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	रेजिस्टर_pm_notअगरier(&ftrace_suspend_notअगरier);

	ftrace_graph_active++;
	ret = start_graph_tracing();
	अगर (ret) अणु
		ftrace_graph_active--;
		जाओ out;
	पूर्ण

	ftrace_graph_वापस = gops->retfunc;

	/*
	 * Update the indirect function to the entryfunc, and the
	 * function that माला_लो called to the entry_test first. Then
	 * call the update fgraph entry function to determine अगर
	 * the entryfunc should be called directly or not.
	 */
	__ftrace_graph_entry = gops->entryfunc;
	ftrace_graph_entry = ftrace_graph_entry_test;
	update_function_graph_func();

	ret = ftrace_startup(&graph_ops, FTRACE_START_FUNC_RET);
out:
	mutex_unlock(&ftrace_lock);
	वापस ret;
पूर्ण

व्योम unरेजिस्टर_ftrace_graph(काष्ठा fgraph_ops *gops)
अणु
	mutex_lock(&ftrace_lock);

	अगर (unlikely(!ftrace_graph_active))
		जाओ out;

	ftrace_graph_active--;
	ftrace_graph_वापस = ftrace_stub_graph;
	ftrace_graph_entry = ftrace_graph_entry_stub;
	__ftrace_graph_entry = ftrace_graph_entry_stub;
	ftrace_shutकरोwn(&graph_ops, FTRACE_STOP_FUNC_RET);
	unरेजिस्टर_pm_notअगरier(&ftrace_suspend_notअगरier);
	unरेजिस्टर_trace_sched_चयन(ftrace_graph_probe_sched_चयन, शून्य);

 out:
	mutex_unlock(&ftrace_lock);
पूर्ण
