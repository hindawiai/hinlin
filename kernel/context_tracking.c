<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Context tracking: Probe on high level context boundaries such as kernel
 * and userspace. This includes syscalls and exceptions entry/निकास.
 *
 * This is used by RCU to हटाओ its dependency on the समयr tick जबतक a CPU
 * runs in userspace.
 *
 *  Started by Frederic Weisbecker:
 *
 * Copyright (C) 2012 Red Hat, Inc., Frederic Weisbecker <fweisbec@redhat.com>
 *
 * Many thanks to Gilad Ben-Yossef, Paul McKenney, Ingo Molnar, Andrew Morton,
 * Steven Rostedt, Peter Zijlstra क्रम suggestions and improvements.
 *
 */

#समावेश <linux/context_tracking.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/sched.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/export.h>
#समावेश <linux/kprobes.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/context_tracking.h>

DEFINE_STATIC_KEY_FALSE(context_tracking_key);
EXPORT_SYMBOL_GPL(context_tracking_key);

DEFINE_PER_CPU(काष्ठा context_tracking, context_tracking);
EXPORT_SYMBOL_GPL(context_tracking);

अटल noinstr bool context_tracking_recursion_enter(व्योम)
अणु
	पूर्णांक recursion;

	recursion = __this_cpu_inc_वापस(context_tracking.recursion);
	अगर (recursion == 1)
		वापस true;

	WARN_ONCE((recursion < 1), "Invalid context tracking recursion value %d\n", recursion);
	__this_cpu_dec(context_tracking.recursion);

	वापस false;
पूर्ण

अटल __always_अंतरभूत व्योम context_tracking_recursion_निकास(व्योम)
अणु
	__this_cpu_dec(context_tracking.recursion);
पूर्ण

/**
 * context_tracking_enter - Inक्रमm the context tracking that the CPU is going
 *                          enter user or guest space mode.
 *
 * This function must be called right beक्रमe we चयन from the kernel
 * to user or guest space, when it's guaranteed the reमुख्यing kernel
 * inकाष्ठाions to execute won't use any RCU पढ़ो side critical section
 * because this function sets RCU in extended quiescent state.
 */
व्योम noinstr __context_tracking_enter(क्रमागत ctx_state state)
अणु
	/* Kernel thपढ़ोs aren't supposed to go to userspace */
	WARN_ON_ONCE(!current->mm);

	अगर (!context_tracking_recursion_enter())
		वापस;

	अगर ( __this_cpu_पढ़ो(context_tracking.state) != state) अणु
		अगर (__this_cpu_पढ़ो(context_tracking.active)) अणु
			/*
			 * At this stage, only low level arch entry code reमुख्यs and
			 * then we'll run in userspace. We can assume there won't be
			 * any RCU पढ़ो-side critical section until the next call to
			 * user_निकास() or rcu_irq_enter(). Let's remove RCU's dependency
			 * on the tick.
			 */
			अगर (state == CONTEXT_USER) अणु
				instrumentation_begin();
				trace_user_enter(0);
				vसमय_user_enter(current);
				instrumentation_end();
			पूर्ण
			rcu_user_enter();
		पूर्ण
		/*
		 * Even अगर context tracking is disabled on this CPU, because it's outside
		 * the full dynticks mask क्रम example, we still have to keep track of the
		 * context transitions and states to prevent inconsistency on those of
		 * other CPUs.
		 * If a task triggers an exception in userspace, sleep on the exception
		 * handler and then migrate to another CPU, that new CPU must know where
		 * the exception वापसs by the समय we call exception_निकास().
		 * This inक्रमmation can only be provided by the previous CPU when it called
		 * exception_enter().
		 * OTOH we can spare the calls to vसमय and RCU when context_tracking.active
		 * is false because we know that CPU is not tickless.
		 */
		__this_cpu_ग_लिखो(context_tracking.state, state);
	पूर्ण
	context_tracking_recursion_निकास();
पूर्ण
EXPORT_SYMBOL_GPL(__context_tracking_enter);

व्योम context_tracking_enter(क्रमागत ctx_state state)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * Some contexts may involve an exception occuring in an irq,
	 * leading to that nesting:
	 * rcu_irq_enter() rcu_user_निकास() rcu_user_निकास() rcu_irq_निकास()
	 * This would mess up the dyntick_nesting count though. And rcu_irq_*()
	 * helpers are enough to protect RCU uses inside the exception. So
	 * just वापस immediately अगर we detect we are in an IRQ.
	 */
	अगर (in_पूर्णांकerrupt())
		वापस;

	local_irq_save(flags);
	__context_tracking_enter(state);
	local_irq_restore(flags);
पूर्ण
NOKPROBE_SYMBOL(context_tracking_enter);
EXPORT_SYMBOL_GPL(context_tracking_enter);

व्योम context_tracking_user_enter(व्योम)
अणु
	user_enter();
पूर्ण
NOKPROBE_SYMBOL(context_tracking_user_enter);

/**
 * context_tracking_निकास - Inक्रमm the context tracking that the CPU is
 *                         निकासing user or guest mode and entering the kernel.
 *
 * This function must be called after we entered the kernel from user or
 * guest space beक्रमe any use of RCU पढ़ो side critical section. This
 * potentially include any high level kernel code like syscalls, exceptions,
 * संकेत handling, etc...
 *
 * This call supports re-entrancy. This way it can be called from any exception
 * handler without needing to know अगर we came from userspace or not.
 */
व्योम noinstr __context_tracking_निकास(क्रमागत ctx_state state)
अणु
	अगर (!context_tracking_recursion_enter())
		वापस;

	अगर (__this_cpu_पढ़ो(context_tracking.state) == state) अणु
		अगर (__this_cpu_पढ़ो(context_tracking.active)) अणु
			/*
			 * We are going to run code that may use RCU. Inक्रमm
			 * RCU core about that (ie: we may need the tick again).
			 */
			rcu_user_निकास();
			अगर (state == CONTEXT_USER) अणु
				instrumentation_begin();
				vसमय_user_निकास(current);
				trace_user_निकास(0);
				instrumentation_end();
			पूर्ण
		पूर्ण
		__this_cpu_ग_लिखो(context_tracking.state, CONTEXT_KERNEL);
	पूर्ण
	context_tracking_recursion_निकास();
पूर्ण
EXPORT_SYMBOL_GPL(__context_tracking_निकास);

व्योम context_tracking_निकास(क्रमागत ctx_state state)
अणु
	अचिन्हित दीर्घ flags;

	अगर (in_पूर्णांकerrupt())
		वापस;

	local_irq_save(flags);
	__context_tracking_निकास(state);
	local_irq_restore(flags);
पूर्ण
NOKPROBE_SYMBOL(context_tracking_निकास);
EXPORT_SYMBOL_GPL(context_tracking_निकास);

व्योम context_tracking_user_निकास(व्योम)
अणु
	user_निकास();
पूर्ण
NOKPROBE_SYMBOL(context_tracking_user_निकास);

व्योम __init context_tracking_cpu_set(पूर्णांक cpu)
अणु
	अटल __initdata bool initialized = false;

	अगर (!per_cpu(context_tracking.active, cpu)) अणु
		per_cpu(context_tracking.active, cpu) = true;
		अटल_branch_inc(&context_tracking_key);
	पूर्ण

	अगर (initialized)
		वापस;

#अगर_घोषित CONFIG_HAVE_TIF_NOHZ
	/*
	 * Set TIF_NOHZ to init/0 and let it propagate to all tasks through विभाजन
	 * This assumes that init is the only task at this early boot stage.
	 */
	set_tsk_thपढ़ो_flag(&init_task, TIF_NOHZ);
#पूर्ण_अगर
	WARN_ON_ONCE(!tasklist_empty());

	initialized = true;
पूर्ण

#अगर_घोषित CONFIG_CONTEXT_TRACKING_FORCE
व्योम __init context_tracking_init(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		context_tracking_cpu_set(cpu);
पूर्ण
#पूर्ण_अगर
