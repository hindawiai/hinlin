<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Read-Copy Update mechanism क्रम mutual exclusion
 *
 * Copyright IBM Corporation, 2001
 *
 * Authors: Dipankar Sarma <dipankar@in.ibm.com>
 *	    Manfred Spraul <manfred@colorfullअगरe.com>
 *
 * Based on the original work by Paul McKenney <paulmck@linux.ibm.com>
 * and inमाला_दो from Rusty Russell, Andrea Arcangeli and Andi Kleen.
 * Papers:
 * http://www.rdrop.com/users/paulmck/paper/rघड़ीpdcsproof.pdf
 * http://lse.sourceक्रमge.net/locking/rघड़ी_OLS.2001.05.01c.sc.pdf (OLS2001)
 *
 * For detailed explanation of Read-Copy Update mechanism see -
 *		http://lse.sourceक्रमge.net/locking/rcupdate.hपंचांगl
 *
 */
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/debug.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/percpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/cpu.h>
#समावेश <linux/mutex.h>
#समावेश <linux/export.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/delay.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/tick.h>
#समावेश <linux/rcupdate_रुको.h>
#समावेश <linux/sched/isolation.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/rcupdate_trace.h>

#घोषणा CREATE_TRACE_POINTS

#समावेश "rcu.h"

#अगर_घोषित MODULE_PARAM_PREFIX
#अघोषित MODULE_PARAM_PREFIX
#पूर्ण_अगर
#घोषणा MODULE_PARAM_PREFIX "rcupdate."

#अगर_अघोषित CONFIG_TINY_RCU
module_param(rcu_expedited, पूर्णांक, 0);
module_param(rcu_normal, पूर्णांक, 0);
अटल पूर्णांक rcu_normal_after_boot = IS_ENABLED(CONFIG_PREEMPT_RT);
#अगर_अघोषित CONFIG_PREEMPT_RT
module_param(rcu_normal_after_boot, पूर्णांक, 0);
#पूर्ण_अगर
#पूर्ण_अगर /* #अगर_अघोषित CONFIG_TINY_RCU */

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
/**
 * rcu_पढ़ो_lock_held_common() - might we be in RCU-sched पढ़ो-side critical section?
 * @ret:	Best guess answer अगर lockdep cannot be relied on
 *
 * Returns true अगर lockdep must be ignored, in which हाल ``*ret`` contains
 * the best guess described below.  Otherwise वापसs false, in which
 * हाल ``*ret`` tells the caller nothing and the caller should instead
 * consult lockdep.
 *
 * If CONFIG_DEBUG_LOCK_ALLOC is selected, set ``*ret`` to nonzero अगरf in an
 * RCU-sched पढ़ो-side critical section.  In असलence of
 * CONFIG_DEBUG_LOCK_ALLOC, this assumes we are in an RCU-sched पढ़ो-side
 * critical section unless it can prove otherwise.  Note that disabling
 * of preemption (including disabling irqs) counts as an RCU-sched
 * पढ़ो-side critical section.  This is useful क्रम debug checks in functions
 * that required that they be called within an RCU-sched पढ़ो-side
 * critical section.
 *
 * Check debug_lockdep_rcu_enabled() to prevent false positives during boot
 * and जबतक lockdep is disabled.
 *
 * Note that अगर the CPU is in the idle loop from an RCU poपूर्णांक of view (ie:
 * that we are in the section between rcu_idle_enter() and rcu_idle_निकास())
 * then rcu_पढ़ो_lock_held() sets ``*ret`` to false even अगर the CPU did an
 * rcu_पढ़ो_lock().  The reason क्रम this is that RCU ignores CPUs that are
 * in such a section, considering these as in extended quiescent state,
 * so such a CPU is effectively never in an RCU पढ़ो-side critical section
 * regardless of what RCU primitives it invokes.  This state of affairs is
 * required --- we need to keep an RCU-मुक्त winकरोw in idle where the CPU may
 * possibly enter पूर्णांकo low घातer mode. This way we can notice an extended
 * quiescent state to other CPUs that started a grace period. Otherwise
 * we would delay any grace period as दीर्घ as we run in the idle task.
 *
 * Similarly, we aव्योम claiming an RCU पढ़ो lock held अगर the current
 * CPU is offline.
 */
अटल bool rcu_पढ़ो_lock_held_common(bool *ret)
अणु
	अगर (!debug_lockdep_rcu_enabled()) अणु
		*ret = true;
		वापस true;
	पूर्ण
	अगर (!rcu_is_watching()) अणु
		*ret = false;
		वापस true;
	पूर्ण
	अगर (!rcu_lockdep_current_cpu_online()) अणु
		*ret = false;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक rcu_पढ़ो_lock_sched_held(व्योम)
अणु
	bool ret;

	अगर (rcu_पढ़ो_lock_held_common(&ret))
		वापस ret;
	वापस lock_is_held(&rcu_sched_lock_map) || !preemptible();
पूर्ण
EXPORT_SYMBOL(rcu_पढ़ो_lock_sched_held);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_TINY_RCU

/*
 * Should expedited grace-period primitives always fall back to their
 * non-expedited counterparts?  Intended क्रम use within RCU.  Note
 * that अगर the user specअगरies both rcu_expedited and rcu_normal, then
 * rcu_normal wins.  (Except during the समय period during boot from
 * when the first task is spawned until the rcu_set_runसमय_mode()
 * core_initcall() is invoked, at which poपूर्णांक everything is expedited.)
 */
bool rcu_gp_is_normal(व्योम)
अणु
	वापस READ_ONCE(rcu_normal) &&
	       rcu_scheduler_active != RCU_SCHEDULER_INIT;
पूर्ण
EXPORT_SYMBOL_GPL(rcu_gp_is_normal);

अटल atomic_t rcu_expedited_nesting = ATOMIC_INIT(1);

/*
 * Should normal grace-period primitives be expedited?  Intended क्रम
 * use within RCU.  Note that this function takes the rcu_expedited
 * sysfs/boot variable and rcu_scheduler_active पूर्णांकo account as well
 * as the rcu_expedite_gp() nesting.  So looping on rcu_unexpedite_gp()
 * until rcu_gp_is_expedited() वापसs false is a -really- bad idea.
 */
bool rcu_gp_is_expedited(व्योम)
अणु
	वापस rcu_expedited || atomic_पढ़ो(&rcu_expedited_nesting);
पूर्ण
EXPORT_SYMBOL_GPL(rcu_gp_is_expedited);

/**
 * rcu_expedite_gp - Expedite future RCU grace periods
 *
 * After a call to this function, future calls to synchronize_rcu() and
 * मित्रs act as the corresponding synchronize_rcu_expedited() function
 * had instead been called.
 */
व्योम rcu_expedite_gp(व्योम)
अणु
	atomic_inc(&rcu_expedited_nesting);
पूर्ण
EXPORT_SYMBOL_GPL(rcu_expedite_gp);

/**
 * rcu_unexpedite_gp - Cancel prior rcu_expedite_gp() invocation
 *
 * Unकरो a prior call to rcu_expedite_gp().  If all prior calls to
 * rcu_expedite_gp() are unकरोne by a subsequent call to rcu_unexpedite_gp(),
 * and अगर the rcu_expedited sysfs/boot parameter is not set, then all
 * subsequent calls to synchronize_rcu() and मित्रs will वापस to
 * their normal non-expedited behavior.
 */
व्योम rcu_unexpedite_gp(व्योम)
अणु
	atomic_dec(&rcu_expedited_nesting);
पूर्ण
EXPORT_SYMBOL_GPL(rcu_unexpedite_gp);

अटल bool rcu_boot_ended __पढ़ो_mostly;

/*
 * Inक्रमm RCU of the end of the in-kernel boot sequence.
 */
व्योम rcu_end_inkernel_boot(व्योम)
अणु
	rcu_unexpedite_gp();
	अगर (rcu_normal_after_boot)
		WRITE_ONCE(rcu_normal, 1);
	rcu_boot_ended = true;
पूर्ण

/*
 * Let rcutorture know when it is OK to turn it up to eleven.
 */
bool rcu_inkernel_boot_has_ended(व्योम)
अणु
	वापस rcu_boot_ended;
पूर्ण
EXPORT_SYMBOL_GPL(rcu_inkernel_boot_has_ended);

#पूर्ण_अगर /* #अगर_अघोषित CONFIG_TINY_RCU */

/*
 * Test each non-SRCU synchronous grace-period रुको API.  This is
 * useful just after a change in mode क्रम these primitives, and
 * during early boot.
 */
व्योम rcu_test_sync_prims(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_PROVE_RCU))
		वापस;
	synchronize_rcu();
	synchronize_rcu_expedited();
पूर्ण

#अगर !defined(CONFIG_TINY_RCU) || defined(CONFIG_SRCU)

/*
 * Switch to run-समय mode once RCU has fully initialized.
 */
अटल पूर्णांक __init rcu_set_runसमय_mode(व्योम)
अणु
	rcu_test_sync_prims();
	rcu_scheduler_active = RCU_SCHEDULER_RUNNING;
	kमुक्त_rcu_scheduler_running();
	rcu_test_sync_prims();
	वापस 0;
पूर्ण
core_initcall(rcu_set_runसमय_mode);

#पूर्ण_अगर /* #अगर !defined(CONFIG_TINY_RCU) || defined(CONFIG_SRCU) */

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
अटल काष्ठा lock_class_key rcu_lock_key;
काष्ठा lockdep_map rcu_lock_map = अणु
	.name = "rcu_read_lock",
	.key = &rcu_lock_key,
	.रुको_type_outer = LD_WAIT_FREE,
	.रुको_type_inner = LD_WAIT_CONFIG, /* XXX PREEMPT_RCU ? */
पूर्ण;
EXPORT_SYMBOL_GPL(rcu_lock_map);

अटल काष्ठा lock_class_key rcu_bh_lock_key;
काष्ठा lockdep_map rcu_bh_lock_map = अणु
	.name = "rcu_read_lock_bh",
	.key = &rcu_bh_lock_key,
	.रुको_type_outer = LD_WAIT_FREE,
	.रुको_type_inner = LD_WAIT_CONFIG, /* PREEMPT_LOCK also makes BH preemptible */
पूर्ण;
EXPORT_SYMBOL_GPL(rcu_bh_lock_map);

अटल काष्ठा lock_class_key rcu_sched_lock_key;
काष्ठा lockdep_map rcu_sched_lock_map = अणु
	.name = "rcu_read_lock_sched",
	.key = &rcu_sched_lock_key,
	.रुको_type_outer = LD_WAIT_FREE,
	.रुको_type_inner = LD_WAIT_SPIN,
पूर्ण;
EXPORT_SYMBOL_GPL(rcu_sched_lock_map);

// Tell lockdep when RCU callbacks are being invoked.
अटल काष्ठा lock_class_key rcu_callback_key;
काष्ठा lockdep_map rcu_callback_map =
	STATIC_LOCKDEP_MAP_INIT("rcu_callback", &rcu_callback_key);
EXPORT_SYMBOL_GPL(rcu_callback_map);

noinstr पूर्णांक notrace debug_lockdep_rcu_enabled(व्योम)
अणु
	वापस rcu_scheduler_active != RCU_SCHEDULER_INACTIVE && debug_locks &&
	       current->lockdep_recursion == 0;
पूर्ण
EXPORT_SYMBOL_GPL(debug_lockdep_rcu_enabled);

/**
 * rcu_पढ़ो_lock_held() - might we be in RCU पढ़ो-side critical section?
 *
 * If CONFIG_DEBUG_LOCK_ALLOC is selected, वापसs nonzero अगरf in an RCU
 * पढ़ो-side critical section.  In असलence of CONFIG_DEBUG_LOCK_ALLOC,
 * this assumes we are in an RCU पढ़ो-side critical section unless it can
 * prove otherwise.  This is useful क्रम debug checks in functions that
 * require that they be called within an RCU पढ़ो-side critical section.
 *
 * Checks debug_lockdep_rcu_enabled() to prevent false positives during boot
 * and जबतक lockdep is disabled.
 *
 * Note that rcu_पढ़ो_lock() and the matching rcu_पढ़ो_unlock() must
 * occur in the same context, क्रम example, it is illegal to invoke
 * rcu_पढ़ो_unlock() in process context अगर the matching rcu_पढ़ो_lock()
 * was invoked from within an irq handler.
 *
 * Note that rcu_पढ़ो_lock() is disallowed अगर the CPU is either idle or
 * offline from an RCU perspective, so check क्रम those as well.
 */
पूर्णांक rcu_पढ़ो_lock_held(व्योम)
अणु
	bool ret;

	अगर (rcu_पढ़ो_lock_held_common(&ret))
		वापस ret;
	वापस lock_is_held(&rcu_lock_map);
पूर्ण
EXPORT_SYMBOL_GPL(rcu_पढ़ो_lock_held);

/**
 * rcu_पढ़ो_lock_bh_held() - might we be in RCU-bh पढ़ो-side critical section?
 *
 * Check क्रम bottom half being disabled, which covers both the
 * CONFIG_PROVE_RCU and not हालs.  Note that अगर someone uses
 * rcu_पढ़ो_lock_bh(), but then later enables BH, lockdep (अगर enabled)
 * will show the situation.  This is useful क्रम debug checks in functions
 * that require that they be called within an RCU पढ़ो-side critical
 * section.
 *
 * Check debug_lockdep_rcu_enabled() to prevent false positives during boot.
 *
 * Note that rcu_पढ़ो_lock_bh() is disallowed अगर the CPU is either idle or
 * offline from an RCU perspective, so check क्रम those as well.
 */
पूर्णांक rcu_पढ़ो_lock_bh_held(व्योम)
अणु
	bool ret;

	अगर (rcu_पढ़ो_lock_held_common(&ret))
		वापस ret;
	वापस in_softirq() || irqs_disabled();
पूर्ण
EXPORT_SYMBOL_GPL(rcu_पढ़ो_lock_bh_held);

पूर्णांक rcu_पढ़ो_lock_any_held(व्योम)
अणु
	bool ret;

	अगर (rcu_पढ़ो_lock_held_common(&ret))
		वापस ret;
	अगर (lock_is_held(&rcu_lock_map) ||
	    lock_is_held(&rcu_bh_lock_map) ||
	    lock_is_held(&rcu_sched_lock_map))
		वापस 1;
	वापस !preemptible();
पूर्ण
EXPORT_SYMBOL_GPL(rcu_पढ़ो_lock_any_held);

#पूर्ण_अगर /* #अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC */

/**
 * wakeme_after_rcu() - Callback function to awaken a task after grace period
 * @head: Poपूर्णांकer to rcu_head member within rcu_synchronize काष्ठाure
 *
 * Awaken the corresponding task now that a grace period has elapsed.
 */
व्योम wakeme_after_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा rcu_synchronize *rcu;

	rcu = container_of(head, काष्ठा rcu_synchronize, head);
	complete(&rcu->completion);
पूर्ण
EXPORT_SYMBOL_GPL(wakeme_after_rcu);

व्योम __रुको_rcu_gp(bool checktiny, पूर्णांक n, call_rcu_func_t *crcu_array,
		   काष्ठा rcu_synchronize *rs_array)
अणु
	पूर्णांक i;
	पूर्णांक j;

	/* Initialize and रेजिस्टर callbacks क्रम each crcu_array element. */
	क्रम (i = 0; i < n; i++) अणु
		अगर (checktiny &&
		    (crcu_array[i] == call_rcu)) अणु
			might_sleep();
			जारी;
		पूर्ण
		क्रम (j = 0; j < i; j++)
			अगर (crcu_array[j] == crcu_array[i])
				अवरोध;
		अगर (j == i) अणु
			init_rcu_head_on_stack(&rs_array[i].head);
			init_completion(&rs_array[i].completion);
			(crcu_array[i])(&rs_array[i].head, wakeme_after_rcu);
		पूर्ण
	पूर्ण

	/* Wait क्रम all callbacks to be invoked. */
	क्रम (i = 0; i < n; i++) अणु
		अगर (checktiny &&
		    (crcu_array[i] == call_rcu))
			जारी;
		क्रम (j = 0; j < i; j++)
			अगर (crcu_array[j] == crcu_array[i])
				अवरोध;
		अगर (j == i) अणु
			रुको_क्रम_completion(&rs_array[i].completion);
			destroy_rcu_head_on_stack(&rs_array[i].head);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__रुको_rcu_gp);

#अगर_घोषित CONFIG_DEBUG_OBJECTS_RCU_HEAD
व्योम init_rcu_head(काष्ठा rcu_head *head)
अणु
	debug_object_init(head, &rcuhead_debug_descr);
पूर्ण
EXPORT_SYMBOL_GPL(init_rcu_head);

व्योम destroy_rcu_head(काष्ठा rcu_head *head)
अणु
	debug_object_मुक्त(head, &rcuhead_debug_descr);
पूर्ण
EXPORT_SYMBOL_GPL(destroy_rcu_head);

अटल bool rcuhead_is_अटल_object(व्योम *addr)
अणु
	वापस true;
पूर्ण

/**
 * init_rcu_head_on_stack() - initialize on-stack rcu_head क्रम debugobjects
 * @head: poपूर्णांकer to rcu_head काष्ठाure to be initialized
 *
 * This function inक्रमms debugobjects of a new rcu_head काष्ठाure that
 * has been allocated as an स्वतः variable on the stack.  This function
 * is not required क्रम rcu_head काष्ठाures that are अटलally defined or
 * that are dynamically allocated on the heap.  This function has no
 * effect क्रम !CONFIG_DEBUG_OBJECTS_RCU_HEAD kernel builds.
 */
व्योम init_rcu_head_on_stack(काष्ठा rcu_head *head)
अणु
	debug_object_init_on_stack(head, &rcuhead_debug_descr);
पूर्ण
EXPORT_SYMBOL_GPL(init_rcu_head_on_stack);

/**
 * destroy_rcu_head_on_stack() - destroy on-stack rcu_head क्रम debugobjects
 * @head: poपूर्णांकer to rcu_head काष्ठाure to be initialized
 *
 * This function inक्रमms debugobjects that an on-stack rcu_head काष्ठाure
 * is about to go out of scope.  As with init_rcu_head_on_stack(), this
 * function is not required क्रम rcu_head काष्ठाures that are अटलally
 * defined or that are dynamically allocated on the heap.  Also as with
 * init_rcu_head_on_stack(), this function has no effect क्रम
 * !CONFIG_DEBUG_OBJECTS_RCU_HEAD kernel builds.
 */
व्योम destroy_rcu_head_on_stack(काष्ठा rcu_head *head)
अणु
	debug_object_मुक्त(head, &rcuhead_debug_descr);
पूर्ण
EXPORT_SYMBOL_GPL(destroy_rcu_head_on_stack);

स्थिर काष्ठा debug_obj_descr rcuhead_debug_descr = अणु
	.name = "rcu_head",
	.is_अटल_object = rcuhead_is_अटल_object,
पूर्ण;
EXPORT_SYMBOL_GPL(rcuhead_debug_descr);
#पूर्ण_अगर /* #अगर_घोषित CONFIG_DEBUG_OBJECTS_RCU_HEAD */

#अगर defined(CONFIG_TREE_RCU) || defined(CONFIG_RCU_TRACE)
व्योम करो_trace_rcu_torture_पढ़ो(स्थिर अक्षर *rcutortuनाम, काष्ठा rcu_head *rhp,
			       अचिन्हित दीर्घ secs,
			       अचिन्हित दीर्घ c_old, अचिन्हित दीर्घ c)
अणु
	trace_rcu_torture_पढ़ो(rcutortuनाम, rhp, secs, c_old, c);
पूर्ण
EXPORT_SYMBOL_GPL(करो_trace_rcu_torture_पढ़ो);
#अन्यथा
#घोषणा करो_trace_rcu_torture_पढ़ो(rcutortuनाम, rhp, secs, c_old, c) \
	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_RCU_TORTURE_TEST) || IS_MODULE(CONFIG_RCU_TORTURE_TEST)
/* Get rcutorture access to sched_setaffinity(). */
दीर्घ rcutorture_sched_setaffinity(pid_t pid, स्थिर काष्ठा cpumask *in_mask)
अणु
	पूर्णांक ret;

	ret = sched_setaffinity(pid, in_mask);
	WARN_ONCE(ret, "%s: sched_setaffinity() returned %d\n", __func__, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rcutorture_sched_setaffinity);
#पूर्ण_अगर

#अगर_घोषित CONFIG_RCU_STALL_COMMON
पूर्णांक rcu_cpu_stall_ftrace_dump __पढ़ो_mostly;
module_param(rcu_cpu_stall_ftrace_dump, पूर्णांक, 0644);
पूर्णांक rcu_cpu_stall_suppress __पढ़ो_mostly; // !0 = suppress stall warnings.
EXPORT_SYMBOL_GPL(rcu_cpu_stall_suppress);
module_param(rcu_cpu_stall_suppress, पूर्णांक, 0644);
पूर्णांक rcu_cpu_stall_समयout __पढ़ो_mostly = CONFIG_RCU_CPU_STALL_TIMEOUT;
module_param(rcu_cpu_stall_समयout, पूर्णांक, 0644);
#पूर्ण_अगर /* #अगर_घोषित CONFIG_RCU_STALL_COMMON */

// Suppress boot-समय RCU CPU stall warnings and rcutorture ग_लिखोr stall
// warnings.  Also used by rcutorture even अगर stall warnings are excluded.
पूर्णांक rcu_cpu_stall_suppress_at_boot __पढ़ो_mostly; // !0 = suppress boot stalls.
EXPORT_SYMBOL_GPL(rcu_cpu_stall_suppress_at_boot);
module_param(rcu_cpu_stall_suppress_at_boot, पूर्णांक, 0444);

#अगर_घोषित CONFIG_PROVE_RCU

/*
 * Early boot self test parameters.
 */
अटल bool rcu_self_test;
module_param(rcu_self_test, bool, 0444);

अटल पूर्णांक rcu_self_test_counter;

अटल व्योम test_callback(काष्ठा rcu_head *r)
अणु
	rcu_self_test_counter++;
	pr_info("RCU test callback executed %d\n", rcu_self_test_counter);
पूर्ण

DEFINE_STATIC_SRCU(early_srcu);

काष्ठा early_boot_kमुक्त_rcu अणु
	काष्ठा rcu_head rh;
पूर्ण;

अटल व्योम early_boot_test_call_rcu(व्योम)
अणु
	अटल काष्ठा rcu_head head;
	अटल काष्ठा rcu_head shead;
	काष्ठा early_boot_kमुक्त_rcu *rhp;

	call_rcu(&head, test_callback);
	अगर (IS_ENABLED(CONFIG_SRCU))
		call_srcu(&early_srcu, &shead, test_callback);
	rhp = kदो_स्मृति(माप(*rhp), GFP_KERNEL);
	अगर (!WARN_ON_ONCE(!rhp))
		kमुक्त_rcu(rhp, rh);
पूर्ण

व्योम rcu_early_boot_tests(व्योम)
अणु
	pr_info("Running RCU self tests\n");

	अगर (rcu_self_test)
		early_boot_test_call_rcu();
	rcu_test_sync_prims();
पूर्ण

अटल पूर्णांक rcu_verअगरy_early_boot_tests(व्योम)
अणु
	पूर्णांक ret = 0;
	पूर्णांक early_boot_test_counter = 0;

	अगर (rcu_self_test) अणु
		early_boot_test_counter++;
		rcu_barrier();
		अगर (IS_ENABLED(CONFIG_SRCU)) अणु
			early_boot_test_counter++;
			srcu_barrier(&early_srcu);
		पूर्ण
	पूर्ण
	अगर (rcu_self_test_counter != early_boot_test_counter) अणु
		WARN_ON(1);
		ret = -1;
	पूर्ण

	वापस ret;
पूर्ण
late_initcall(rcu_verअगरy_early_boot_tests);
#अन्यथा
व्योम rcu_early_boot_tests(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PROVE_RCU */

#समावेश "tasks.h"

#अगर_अघोषित CONFIG_TINY_RCU

/*
 * Prपूर्णांक any signअगरicant non-शेष boot-समय settings.
 */
व्योम __init rcupdate_announce_bootup_oddness(व्योम)
अणु
	अगर (rcu_normal)
		pr_info("\tNo expedited grace period (rcu_normal).\n");
	अन्यथा अगर (rcu_normal_after_boot)
		pr_info("\tNo expedited grace period (rcu_normal_after_boot).\n");
	अन्यथा अगर (rcu_expedited)
		pr_info("\tAll grace periods are expedited (rcu_expedited).\n");
	अगर (rcu_cpu_stall_suppress)
		pr_info("\tRCU CPU stall warnings suppressed (rcu_cpu_stall_suppress).\n");
	अगर (rcu_cpu_stall_समयout != CONFIG_RCU_CPU_STALL_TIMEOUT)
		pr_info("\tRCU CPU stall warnings timeout set to %d (rcu_cpu_stall_timeout).\n", rcu_cpu_stall_समयout);
	rcu_tasks_bootup_oddness();
पूर्ण

#पूर्ण_अगर /* #अगर_अघोषित CONFIG_TINY_RCU */
