<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Read-Copy Update mechanism क्रम mutual exclusion
 *
 * Copyright IBM Corporation, 2001
 *
 * Author: Dipankar Sarma <dipankar@in.ibm.com>
 *
 * Based on the original work by Paul McKenney <paulmck@vnet.ibm.com>
 * and inमाला_दो from Rusty Russell, Andrea Arcangeli and Andi Kleen.
 * Papers:
 * http://www.rdrop.com/users/paulmck/paper/rघड़ीpdcsproof.pdf
 * http://lse.sourceक्रमge.net/locking/rघड़ी_OLS.2001.05.01c.sc.pdf (OLS2001)
 *
 * For detailed explanation of Read-Copy Update mechanism see -
 *		http://lse.sourceक्रमge.net/locking/rcupdate.hपंचांगl
 *
 */

#अगर_अघोषित __LINUX_RCUPDATE_H
#घोषणा __LINUX_RCUPDATE_H

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/atomic.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/preempt.h>
#समावेश <linux/bottom_half.h>
#समावेश <linux/lockdep.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/cpumask.h>

#घोषणा ULONG_CMP_GE(a, b)	(अच_दीर्घ_उच्च / 2 >= (a) - (b))
#घोषणा ULONG_CMP_LT(a, b)	(अच_दीर्घ_उच्च / 2 < (a) - (b))
#घोषणा uदीर्घ2दीर्घ(a)		(*(दीर्घ *)(&(a)))
#घोषणा USHORT_CMP_GE(a, b)	(अच_लघु_उच्च / 2 >= (अचिन्हित लघु)((a) - (b)))
#घोषणा USHORT_CMP_LT(a, b)	(अच_लघु_उच्च / 2 < (अचिन्हित लघु)((a) - (b)))

/* Exported common पूर्णांकerfaces */
व्योम call_rcu(काष्ठा rcu_head *head, rcu_callback_t func);
व्योम rcu_barrier_tasks(व्योम);
व्योम rcu_barrier_tasks_rude(व्योम);
व्योम synchronize_rcu(व्योम);

#अगर_घोषित CONFIG_PREEMPT_RCU

व्योम __rcu_पढ़ो_lock(व्योम);
व्योम __rcu_पढ़ो_unlock(व्योम);

/*
 * Defined as a macro as it is a very low level header included from
 * areas that करोn't even know about current.  This gives the rcu_पढ़ो_lock()
 * nesting depth, but makes sense only अगर CONFIG_PREEMPT_RCU -- in other
 * types of kernel builds, the rcu_पढ़ो_lock() nesting depth is unknowable.
 */
#घोषणा rcu_preempt_depth() (current->rcu_पढ़ो_lock_nesting)

#अन्यथा /* #अगर_घोषित CONFIG_PREEMPT_RCU */

#अगर_घोषित CONFIG_TINY_RCU
#घोषणा rcu_पढ़ो_unlock_strict() करो अणु पूर्ण जबतक (0)
#अन्यथा
व्योम rcu_पढ़ो_unlock_strict(व्योम);
#पूर्ण_अगर

अटल अंतरभूत व्योम __rcu_पढ़ो_lock(व्योम)
अणु
	preempt_disable();
पूर्ण

अटल अंतरभूत व्योम __rcu_पढ़ो_unlock(व्योम)
अणु
	preempt_enable();
	rcu_पढ़ो_unlock_strict();
पूर्ण

अटल अंतरभूत पूर्णांक rcu_preempt_depth(व्योम)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_PREEMPT_RCU */

/* Internal to kernel */
व्योम rcu_init(व्योम);
बाह्य पूर्णांक rcu_scheduler_active __पढ़ो_mostly;
व्योम rcu_sched_घड़ी_irq(पूर्णांक user);
व्योम rcu_report_dead(अचिन्हित पूर्णांक cpu);
व्योम rcutree_migrate_callbacks(पूर्णांक cpu);

#अगर_घोषित CONFIG_TASKS_RCU_GENERIC
व्योम rcu_init_tasks_generic(व्योम);
#अन्यथा
अटल अंतरभूत व्योम rcu_init_tasks_generic(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_RCU_STALL_COMMON
व्योम rcu_sysrq_start(व्योम);
व्योम rcu_sysrq_end(व्योम);
#अन्यथा /* #अगर_घोषित CONFIG_RCU_STALL_COMMON */
अटल अंतरभूत व्योम rcu_sysrq_start(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम rcu_sysrq_end(व्योम) अणु पूर्ण
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_RCU_STALL_COMMON */

#अगर_घोषित CONFIG_NO_HZ_FULL
व्योम rcu_user_enter(व्योम);
व्योम rcu_user_निकास(व्योम);
#अन्यथा
अटल अंतरभूत व्योम rcu_user_enter(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम rcu_user_निकास(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_NO_HZ_FULL */

#अगर_घोषित CONFIG_RCU_NOCB_CPU
व्योम rcu_init_nohz(व्योम);
पूर्णांक rcu_nocb_cpu_offload(पूर्णांक cpu);
पूर्णांक rcu_nocb_cpu_deoffload(पूर्णांक cpu);
व्योम rcu_nocb_flush_deferred_wakeup(व्योम);
#अन्यथा /* #अगर_घोषित CONFIG_RCU_NOCB_CPU */
अटल अंतरभूत व्योम rcu_init_nohz(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक rcu_nocb_cpu_offload(पूर्णांक cpu) अणु वापस -EINVAL; पूर्ण
अटल अंतरभूत पूर्णांक rcu_nocb_cpu_deoffload(पूर्णांक cpu) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम rcu_nocb_flush_deferred_wakeup(व्योम) अणु पूर्ण
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_RCU_NOCB_CPU */

/**
 * RCU_NONIDLE - Indicate idle-loop code that needs RCU पढ़ोers
 * @a: Code that RCU needs to pay attention to.
 *
 * RCU पढ़ो-side critical sections are क्रमbidden in the inner idle loop,
 * that is, between the rcu_idle_enter() and the rcu_idle_निकास() -- RCU
 * will happily ignore any such पढ़ो-side critical sections.  However,
 * things like घातertop need tracepoपूर्णांकs in the inner idle loop.
 *
 * This macro provides the way out:  RCU_NONIDLE(करो_something_with_RCU())
 * will tell RCU that it needs to pay attention, invoke its argument
 * (in this example, calling the करो_something_with_RCU() function),
 * and then tell RCU to go back to ignoring this CPU.  It is permissible
 * to nest RCU_NONIDLE() wrappers, but not indefinitely (but the limit is
 * on the order of a million or so, even on 32-bit प्रणालीs).  It is
 * not legal to block within RCU_NONIDLE(), nor is it permissible to
 * transfer control either पूर्णांकo or out of RCU_NONIDLE()'s statement.
 */
#घोषणा RCU_NONIDLE(a) \
	करो अणु \
		rcu_irq_enter_irqson(); \
		करो अणु a; पूर्ण जबतक (0); \
		rcu_irq_निकास_irqson(); \
	पूर्ण जबतक (0)

/*
 * Note a quasi-voluntary context चयन क्रम RCU-tasks's benefit.
 * This is a macro rather than an अंतरभूत function to aव्योम #समावेश hell.
 */
#अगर_घोषित CONFIG_TASKS_RCU_GENERIC

# अगरdef CONFIG_TASKS_RCU
# define rcu_tasks_classic_qs(t, preempt)				\
	करो अणु								\
		अगर (!(preempt) && READ_ONCE((t)->rcu_tasks_holकरोut))	\
			WRITE_ONCE((t)->rcu_tasks_holकरोut, false);	\
	पूर्ण जबतक (0)
व्योम call_rcu_tasks(काष्ठा rcu_head *head, rcu_callback_t func);
व्योम synchronize_rcu_tasks(व्योम);
# अन्यथा
# define rcu_tasks_classic_qs(t, preempt) करो अणु पूर्ण जबतक (0)
# define call_rcu_tasks call_rcu
# define synchronize_rcu_tasks synchronize_rcu
# endअगर

# अगरdef CONFIG_TASKS_RCU_TRACE
# define rcu_tasks_trace_qs(t)						\
	करो अणु								\
		अगर (!likely(READ_ONCE((t)->trc_पढ़ोer_checked)) &&	\
		    !unlikely(READ_ONCE((t)->trc_पढ़ोer_nesting))) अणु	\
			smp_store_release(&(t)->trc_पढ़ोer_checked, true); \
			smp_mb(); /* Readers partitioned by store. */	\
		पूर्ण							\
	पूर्ण जबतक (0)
# अन्यथा
# define rcu_tasks_trace_qs(t) करो अणु पूर्ण जबतक (0)
# endअगर

#घोषणा rcu_tasks_qs(t, preempt)					\
करो अणु									\
	rcu_tasks_classic_qs((t), (preempt));				\
	rcu_tasks_trace_qs((t));					\
पूर्ण जबतक (0)

# अगरdef CONFIG_TASKS_RUDE_RCU
व्योम call_rcu_tasks_rude(काष्ठा rcu_head *head, rcu_callback_t func);
व्योम synchronize_rcu_tasks_rude(व्योम);
# endअगर

#घोषणा rcu_note_voluntary_context_चयन(t) rcu_tasks_qs(t, false)
व्योम निकास_tasks_rcu_start(व्योम);
व्योम निकास_tasks_rcu_finish(व्योम);
#अन्यथा /* #अगर_घोषित CONFIG_TASKS_RCU_GENERIC */
#घोषणा rcu_tasks_qs(t, preempt) करो अणु पूर्ण जबतक (0)
#घोषणा rcu_note_voluntary_context_चयन(t) करो अणु पूर्ण जबतक (0)
#घोषणा call_rcu_tasks call_rcu
#घोषणा synchronize_rcu_tasks synchronize_rcu
अटल अंतरभूत व्योम निकास_tasks_rcu_start(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम निकास_tasks_rcu_finish(व्योम) अणु पूर्ण
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_TASKS_RCU_GENERIC */

/**
 * cond_resched_tasks_rcu_qs - Report potential quiescent states to RCU
 *
 * This macro resembles cond_resched(), except that it is defined to
 * report potential quiescent states to RCU-tasks even अगर the cond_resched()
 * machinery were to be shut off, as some advocate क्रम PREEMPTION kernels.
 */
#घोषणा cond_resched_tasks_rcu_qs() \
करो अणु \
	rcu_tasks_qs(current, false); \
	cond_resched(); \
पूर्ण जबतक (0)

/*
 * Infraकाष्ठाure to implement the synchronize_() primitives in
 * TREE_RCU and rcu_barrier_() primitives in TINY_RCU.
 */

#अगर defined(CONFIG_TREE_RCU)
#समावेश <linux/rcutree.h>
#या_अगर defined(CONFIG_TINY_RCU)
#समावेश <linux/rcutiny.h>
#अन्यथा
#त्रुटि "Unknown RCU implementation specified to kernel configuration"
#पूर्ण_अगर

/*
 * The init_rcu_head_on_stack() and destroy_rcu_head_on_stack() calls
 * are needed क्रम dynamic initialization and deकाष्ठाion of rcu_head
 * on the stack, and init_rcu_head()/destroy_rcu_head() are needed क्रम
 * dynamic initialization and deकाष्ठाion of अटलally allocated rcu_head
 * काष्ठाures.  However, rcu_head काष्ठाures allocated dynamically in the
 * heap करोn't need any initialization.
 */
#अगर_घोषित CONFIG_DEBUG_OBJECTS_RCU_HEAD
व्योम init_rcu_head(काष्ठा rcu_head *head);
व्योम destroy_rcu_head(काष्ठा rcu_head *head);
व्योम init_rcu_head_on_stack(काष्ठा rcu_head *head);
व्योम destroy_rcu_head_on_stack(काष्ठा rcu_head *head);
#अन्यथा /* !CONFIG_DEBUG_OBJECTS_RCU_HEAD */
अटल अंतरभूत व्योम init_rcu_head(काष्ठा rcu_head *head) अणु पूर्ण
अटल अंतरभूत व्योम destroy_rcu_head(काष्ठा rcu_head *head) अणु पूर्ण
अटल अंतरभूत व्योम init_rcu_head_on_stack(काष्ठा rcu_head *head) अणु पूर्ण
अटल अंतरभूत व्योम destroy_rcu_head_on_stack(काष्ठा rcu_head *head) अणु पूर्ण
#पूर्ण_अगर	/* #अन्यथा !CONFIG_DEBUG_OBJECTS_RCU_HEAD */

#अगर defined(CONFIG_HOTPLUG_CPU) && defined(CONFIG_PROVE_RCU)
bool rcu_lockdep_current_cpu_online(व्योम);
#अन्यथा /* #अगर defined(CONFIG_HOTPLUG_CPU) && defined(CONFIG_PROVE_RCU) */
अटल अंतरभूत bool rcu_lockdep_current_cpu_online(व्योम) अणु वापस true; पूर्ण
#पूर्ण_अगर /* #अन्यथा #अगर defined(CONFIG_HOTPLUG_CPU) && defined(CONFIG_PROVE_RCU) */

बाह्य काष्ठा lockdep_map rcu_lock_map;
बाह्य काष्ठा lockdep_map rcu_bh_lock_map;
बाह्य काष्ठा lockdep_map rcu_sched_lock_map;
बाह्य काष्ठा lockdep_map rcu_callback_map;

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC

अटल अंतरभूत व्योम rcu_lock_acquire(काष्ठा lockdep_map *map)
अणु
	lock_acquire(map, 0, 0, 2, 0, शून्य, _THIS_IP_);
पूर्ण

अटल अंतरभूत व्योम rcu_lock_release(काष्ठा lockdep_map *map)
अणु
	lock_release(map, _THIS_IP_);
पूर्ण

पूर्णांक debug_lockdep_rcu_enabled(व्योम);
पूर्णांक rcu_पढ़ो_lock_held(व्योम);
पूर्णांक rcu_पढ़ो_lock_bh_held(व्योम);
पूर्णांक rcu_पढ़ो_lock_sched_held(व्योम);
पूर्णांक rcu_पढ़ो_lock_any_held(व्योम);

#अन्यथा /* #अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC */

# define rcu_lock_acquire(a)		करो अणु पूर्ण जबतक (0)
# define rcu_lock_release(a)		करो अणु पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक rcu_पढ़ो_lock_held(व्योम)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक rcu_पढ़ो_lock_bh_held(व्योम)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक rcu_पढ़ो_lock_sched_held(व्योम)
अणु
	वापस !preemptible();
पूर्ण

अटल अंतरभूत पूर्णांक rcu_पढ़ो_lock_any_held(व्योम)
अणु
	वापस !preemptible();
पूर्ण

#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC */

#अगर_घोषित CONFIG_PROVE_RCU

/**
 * RCU_LOCKDEP_WARN - emit lockdep splat अगर specअगरied condition is met
 * @c: condition to check
 * @s: inक्रमmative message
 */
#घोषणा RCU_LOCKDEP_WARN(c, s)						\
	करो अणु								\
		अटल bool __section(".data.unlikely") __warned;	\
		अगर (debug_lockdep_rcu_enabled() && !__warned && (c)) अणु	\
			__warned = true;				\
			lockdep_rcu_suspicious(__खाता__, __LINE__, s);	\
		पूर्ण							\
	पूर्ण जबतक (0)

#अगर defined(CONFIG_PROVE_RCU) && !defined(CONFIG_PREEMPT_RCU)
अटल अंतरभूत व्योम rcu_preempt_sleep_check(व्योम)
अणु
	RCU_LOCKDEP_WARN(lock_is_held(&rcu_lock_map),
			 "Illegal context switch in RCU read-side critical section");
पूर्ण
#अन्यथा /* #अगर_घोषित CONFIG_PROVE_RCU */
अटल अंतरभूत व्योम rcu_preempt_sleep_check(व्योम) अणु पूर्ण
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_PROVE_RCU */

#घोषणा rcu_sleep_check()						\
	करो अणु								\
		rcu_preempt_sleep_check();				\
		अगर (!IS_ENABLED(CONFIG_PREEMPT_RT))			\
		    RCU_LOCKDEP_WARN(lock_is_held(&rcu_bh_lock_map),	\
				 "Illegal context switch in RCU-bh read-side critical section"); \
		RCU_LOCKDEP_WARN(lock_is_held(&rcu_sched_lock_map),	\
				 "Illegal context switch in RCU-sched read-side critical section"); \
	पूर्ण जबतक (0)

#अन्यथा /* #अगर_घोषित CONFIG_PROVE_RCU */

#घोषणा RCU_LOCKDEP_WARN(c, s) करो अणु पूर्ण जबतक (0 && (c))
#घोषणा rcu_sleep_check() करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_PROVE_RCU */

/*
 * Helper functions क्रम rcu_dereference_check(), rcu_dereference_रक्षित()
 * and rcu_assign_poपूर्णांकer().  Some of these could be folded पूर्णांकo their
 * callers, but they are left separate in order to ease पूर्णांकroduction of
 * multiple poपूर्णांकers markings to match dअगरferent RCU implementations
 * (e.g., __srcu), should this make sense in the future.
 */

#अगर_घोषित __CHECKER__
#घोषणा rcu_check_sparse(p, space) \
	((व्योम)(((typeof(*p) space *)p) == p))
#अन्यथा /* #अगर_घोषित __CHECKER__ */
#घोषणा rcu_check_sparse(p, space)
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित __CHECKER__ */

#घोषणा __rcu_access_poपूर्णांकer(p, space) \
(अणु \
	typeof(*p) *_________p1 = (typeof(*p) *__क्रमce)READ_ONCE(p); \
	rcu_check_sparse(p, space); \
	((typeof(*p) __क्रमce __kernel *)(_________p1)); \
पूर्ण)
#घोषणा __rcu_dereference_check(p, c, space) \
(अणु \
	/* Dependency order vs. p above. */ \
	typeof(*p) *________p1 = (typeof(*p) *__क्रमce)READ_ONCE(p); \
	RCU_LOCKDEP_WARN(!(c), "suspicious rcu_dereference_check() usage"); \
	rcu_check_sparse(p, space); \
	((typeof(*p) __क्रमce __kernel *)(________p1)); \
पूर्ण)
#घोषणा __rcu_dereference_रक्षित(p, c, space) \
(अणु \
	RCU_LOCKDEP_WARN(!(c), "suspicious rcu_dereference_protected() usage"); \
	rcu_check_sparse(p, space); \
	((typeof(*p) __क्रमce __kernel *)(p)); \
पूर्ण)
#घोषणा rcu_dereference_raw(p) \
(अणु \
	/* Dependency order vs. p above. */ \
	typeof(p) ________p1 = READ_ONCE(p); \
	((typeof(*p) __क्रमce __kernel *)(________p1)); \
पूर्ण)

/**
 * RCU_INITIALIZER() - अटलally initialize an RCU-रक्षित global variable
 * @v: The value to अटलally initialize with.
 */
#घोषणा RCU_INITIALIZER(v) (typeof(*(v)) __क्रमce __rcu *)(v)

/**
 * rcu_assign_poपूर्णांकer() - assign to RCU-रक्षित poपूर्णांकer
 * @p: poपूर्णांकer to assign to
 * @v: value to assign (publish)
 *
 * Assigns the specअगरied value to the specअगरied RCU-रक्षित
 * poपूर्णांकer, ensuring that any concurrent RCU पढ़ोers will see
 * any prior initialization.
 *
 * Inserts memory barriers on architectures that require them
 * (which is most of them), and also prevents the compiler from
 * reordering the code that initializes the काष्ठाure after the poपूर्णांकer
 * assignment.  More importantly, this call करोcuments which poपूर्णांकers
 * will be dereferenced by RCU पढ़ो-side code.
 *
 * In some special हालs, you may use RCU_INIT_POINTER() instead
 * of rcu_assign_poपूर्णांकer().  RCU_INIT_POINTER() is a bit faster due
 * to the fact that it करोes not स्थिरrain either the CPU or the compiler.
 * That said, using RCU_INIT_POINTER() when you should have used
 * rcu_assign_poपूर्णांकer() is a very bad thing that results in
 * impossible-to-diagnose memory corruption.  So please be careful.
 * See the RCU_INIT_POINTER() comment header क्रम details.
 *
 * Note that rcu_assign_poपूर्णांकer() evaluates each of its arguments only
 * once, appearances notwithstanding.  One of the "extra" evaluations
 * is in typeof() and the other visible only to sparse (__CHECKER__),
 * neither of which actually execute the argument.  As with most cpp
 * macros, this execute-arguments-only-once property is important, so
 * please be careful when making changes to rcu_assign_poपूर्णांकer() and the
 * other macros that it invokes.
 */
#घोषणा rcu_assign_poपूर्णांकer(p, v)					      \
करो अणु									      \
	uपूर्णांकptr_t _r_a_p__v = (uपूर्णांकptr_t)(v);				      \
	rcu_check_sparse(p, __rcu);					      \
									      \
	अगर (__builtin_स्थिरant_p(v) && (_r_a_p__v) == (uपूर्णांकptr_t)शून्य)	      \
		WRITE_ONCE((p), (typeof(p))(_r_a_p__v));		      \
	अन्यथा								      \
		smp_store_release(&p, RCU_INITIALIZER((typeof(p))_r_a_p__v)); \
पूर्ण जबतक (0)

/**
 * rcu_replace_poपूर्णांकer() - replace an RCU poपूर्णांकer, वापसing its old value
 * @rcu_ptr: RCU poपूर्णांकer, whose old value is वापसed
 * @ptr: regular poपूर्णांकer
 * @c: the lockdep conditions under which the dereference will take place
 *
 * Perक्रमm a replacement, where @rcu_ptr is an RCU-annotated
 * poपूर्णांकer and @c is the lockdep argument that is passed to the
 * rcu_dereference_रक्षित() call used to पढ़ो that poपूर्णांकer.  The old
 * value of @rcu_ptr is वापसed, and @rcu_ptr is set to @ptr.
 */
#घोषणा rcu_replace_poपूर्णांकer(rcu_ptr, ptr, c)				\
(अणु									\
	typeof(ptr) __पंचांगp = rcu_dereference_रक्षित((rcu_ptr), (c));	\
	rcu_assign_poपूर्णांकer((rcu_ptr), (ptr));				\
	__पंचांगp;								\
पूर्ण)

/**
 * rcu_access_poपूर्णांकer() - fetch RCU poपूर्णांकer with no dereferencing
 * @p: The poपूर्णांकer to पढ़ो
 *
 * Return the value of the specअगरied RCU-रक्षित poपूर्णांकer, but omit the
 * lockdep checks क्रम being in an RCU पढ़ो-side critical section.  This is
 * useful when the value of this poपूर्णांकer is accessed, but the poपूर्णांकer is
 * not dereferenced, क्रम example, when testing an RCU-रक्षित poपूर्णांकer
 * against शून्य.  Although rcu_access_poपूर्णांकer() may also be used in हालs
 * where update-side locks prevent the value of the poपूर्णांकer from changing,
 * you should instead use rcu_dereference_रक्षित() क्रम this use हाल.
 *
 * It is also permissible to use rcu_access_poपूर्णांकer() when पढ़ो-side
 * access to the poपूर्णांकer was हटाओd at least one grace period ago, as
 * is the हाल in the context of the RCU callback that is मुक्तing up
 * the data, or after a synchronize_rcu() वापसs.  This can be useful
 * when tearing करोwn multi-linked काष्ठाures after a grace period
 * has elapsed.
 */
#घोषणा rcu_access_poपूर्णांकer(p) __rcu_access_poपूर्णांकer((p), __rcu)

/**
 * rcu_dereference_check() - rcu_dereference with debug checking
 * @p: The poपूर्णांकer to पढ़ो, prior to dereferencing
 * @c: The conditions under which the dereference will take place
 *
 * Do an rcu_dereference(), but check that the conditions under which the
 * dereference will take place are correct.  Typically the conditions
 * indicate the various locking conditions that should be held at that
 * poपूर्णांक.  The check should वापस true अगर the conditions are satisfied.
 * An implicit check क्रम being in an RCU पढ़ो-side critical section
 * (rcu_पढ़ो_lock()) is included.
 *
 * For example:
 *
 *	bar = rcu_dereference_check(foo->bar, lockdep_is_held(&foo->lock));
 *
 * could be used to indicate to lockdep that foo->bar may only be dereferenced
 * अगर either rcu_पढ़ो_lock() is held, or that the lock required to replace
 * the bar काष्ठा at foo->bar is held.
 *
 * Note that the list of conditions may also include indications of when a lock
 * need not be held, क्रम example during initialisation or deकाष्ठाion of the
 * target काष्ठा:
 *
 *	bar = rcu_dereference_check(foo->bar, lockdep_is_held(&foo->lock) ||
 *					      atomic_पढ़ो(&foo->usage) == 0);
 *
 * Inserts memory barriers on architectures that require them
 * (currently only the Alpha), prevents the compiler from refetching
 * (and from merging fetches), and, more importantly, करोcuments exactly
 * which poपूर्णांकers are रक्षित by RCU and checks that the poपूर्णांकer is
 * annotated as __rcu.
 */
#घोषणा rcu_dereference_check(p, c) \
	__rcu_dereference_check((p), (c) || rcu_पढ़ो_lock_held(), __rcu)

/**
 * rcu_dereference_bh_check() - rcu_dereference_bh with debug checking
 * @p: The poपूर्णांकer to पढ़ो, prior to dereferencing
 * @c: The conditions under which the dereference will take place
 *
 * This is the RCU-bh counterpart to rcu_dereference_check().
 */
#घोषणा rcu_dereference_bh_check(p, c) \
	__rcu_dereference_check((p), (c) || rcu_पढ़ो_lock_bh_held(), __rcu)

/**
 * rcu_dereference_sched_check() - rcu_dereference_sched with debug checking
 * @p: The poपूर्णांकer to पढ़ो, prior to dereferencing
 * @c: The conditions under which the dereference will take place
 *
 * This is the RCU-sched counterpart to rcu_dereference_check().
 */
#घोषणा rcu_dereference_sched_check(p, c) \
	__rcu_dereference_check((p), (c) || rcu_पढ़ो_lock_sched_held(), \
				__rcu)

/*
 * The tracing infraकाष्ठाure traces RCU (we want that), but unक्रमtunately
 * some of the RCU checks causes tracing to lock up the प्रणाली.
 *
 * The no-tracing version of rcu_dereference_raw() must not call
 * rcu_पढ़ो_lock_held().
 */
#घोषणा rcu_dereference_raw_check(p) __rcu_dereference_check((p), 1, __rcu)

/**
 * rcu_dereference_रक्षित() - fetch RCU poपूर्णांकer when updates prevented
 * @p: The poपूर्णांकer to पढ़ो, prior to dereferencing
 * @c: The conditions under which the dereference will take place
 *
 * Return the value of the specअगरied RCU-रक्षित poपूर्णांकer, but omit
 * the READ_ONCE().  This is useful in हालs where update-side locks
 * prevent the value of the poपूर्णांकer from changing.  Please note that this
 * primitive करोes *not* prevent the compiler from repeating this reference
 * or combining it with other references, so it should not be used without
 * protection of appropriate locks.
 *
 * This function is only क्रम update-side use.  Using this function
 * when रक्षित only by rcu_पढ़ो_lock() will result in infrequent
 * but very ugly failures.
 */
#घोषणा rcu_dereference_रक्षित(p, c) \
	__rcu_dereference_रक्षित((p), (c), __rcu)


/**
 * rcu_dereference() - fetch RCU-रक्षित poपूर्णांकer क्रम dereferencing
 * @p: The poपूर्णांकer to पढ़ो, prior to dereferencing
 *
 * This is a simple wrapper around rcu_dereference_check().
 */
#घोषणा rcu_dereference(p) rcu_dereference_check(p, 0)

/**
 * rcu_dereference_bh() - fetch an RCU-bh-रक्षित poपूर्णांकer क्रम dereferencing
 * @p: The poपूर्णांकer to पढ़ो, prior to dereferencing
 *
 * Makes rcu_dereference_check() करो the dirty work.
 */
#घोषणा rcu_dereference_bh(p) rcu_dereference_bh_check(p, 0)

/**
 * rcu_dereference_sched() - fetch RCU-sched-रक्षित poपूर्णांकer क्रम dereferencing
 * @p: The poपूर्णांकer to पढ़ो, prior to dereferencing
 *
 * Makes rcu_dereference_check() करो the dirty work.
 */
#घोषणा rcu_dereference_sched(p) rcu_dereference_sched_check(p, 0)

/**
 * rcu_poपूर्णांकer_hanकरोff() - Hand off a poपूर्णांकer from RCU to other mechanism
 * @p: The poपूर्णांकer to hand off
 *
 * This is simply an identity function, but it करोcuments where a poपूर्णांकer
 * is handed off from RCU to some other synchronization mechanism, क्रम
 * example, reference counting or locking.  In C11, it would map to
 * समाप्त_dependency().  It could be used as follows::
 *
 *	rcu_पढ़ो_lock();
 *	p = rcu_dereference(gp);
 *	दीर्घ_lived = is_दीर्घ_lived(p);
 *	अगर (दीर्घ_lived) अणु
 *		अगर (!atomic_inc_not_zero(p->refcnt))
 *			दीर्घ_lived = false;
 *		अन्यथा
 *			p = rcu_poपूर्णांकer_hanकरोff(p);
 *	पूर्ण
 *	rcu_पढ़ो_unlock();
 */
#घोषणा rcu_poपूर्णांकer_hanकरोff(p) (p)

/**
 * rcu_पढ़ो_lock() - mark the beginning of an RCU पढ़ो-side critical section
 *
 * When synchronize_rcu() is invoked on one CPU जबतक other CPUs
 * are within RCU पढ़ो-side critical sections, then the
 * synchronize_rcu() is guaranteed to block until after all the other
 * CPUs निकास their critical sections.  Similarly, अगर call_rcu() is invoked
 * on one CPU जबतक other CPUs are within RCU पढ़ो-side critical
 * sections, invocation of the corresponding RCU callback is deferred
 * until after the all the other CPUs निकास their critical sections.
 *
 * Note, however, that RCU callbacks are permitted to run concurrently
 * with new RCU पढ़ो-side critical sections.  One way that this can happen
 * is via the following sequence of events: (1) CPU 0 enters an RCU
 * पढ़ो-side critical section, (2) CPU 1 invokes call_rcu() to रेजिस्टर
 * an RCU callback, (3) CPU 0 निकासs the RCU पढ़ो-side critical section,
 * (4) CPU 2 enters a RCU पढ़ो-side critical section, (5) the RCU
 * callback is invoked.  This is legal, because the RCU पढ़ो-side critical
 * section that was running concurrently with the call_rcu() (and which
 * thereक्रमe might be referencing something that the corresponding RCU
 * callback would मुक्त up) has completed beक्रमe the corresponding
 * RCU callback is invoked.
 *
 * RCU पढ़ो-side critical sections may be nested.  Any deferred actions
 * will be deferred until the outermost RCU पढ़ो-side critical section
 * completes.
 *
 * You can aव्योम पढ़ोing and understanding the next paragraph by
 * following this rule: करोn't put anything in an rcu_पढ़ो_lock() RCU
 * पढ़ो-side critical section that would block in a !PREEMPTION kernel.
 * But अगर you want the full story, पढ़ो on!
 *
 * In non-preemptible RCU implementations (pure TREE_RCU and TINY_RCU),
 * it is illegal to block जबतक in an RCU पढ़ो-side critical section.
 * In preemptible RCU implementations (PREEMPT_RCU) in CONFIG_PREEMPTION
 * kernel builds, RCU पढ़ो-side critical sections may be preempted,
 * but explicit blocking is illegal.  Finally, in preemptible RCU
 * implementations in real-समय (with -rt patchset) kernel builds, RCU
 * पढ़ो-side critical sections may be preempted and they may also block, but
 * only when acquiring spinlocks that are subject to priority inheritance.
 */
अटल __always_अंतरभूत व्योम rcu_पढ़ो_lock(व्योम)
अणु
	__rcu_पढ़ो_lock();
	__acquire(RCU);
	rcu_lock_acquire(&rcu_lock_map);
	RCU_LOCKDEP_WARN(!rcu_is_watching(),
			 "rcu_read_lock() used illegally while idle");
पूर्ण

/*
 * So where is rcu_ग_लिखो_lock()?  It करोes not exist, as there is no
 * way क्रम ग_लिखोrs to lock out RCU पढ़ोers.  This is a feature, not
 * a bug -- this property is what provides RCU's perक्रमmance benefits.
 * Of course, ग_लिखोrs must coordinate with each other.  The normal
 * spinlock primitives work well क्रम this, but any other technique may be
 * used as well.  RCU करोes not care how the ग_लिखोrs keep out of each
 * others' way, as दीर्घ as they करो so.
 */

/**
 * rcu_पढ़ो_unlock() - marks the end of an RCU पढ़ो-side critical section.
 *
 * In most situations, rcu_पढ़ो_unlock() is immune from deadlock.
 * However, in kernels built with CONFIG_RCU_BOOST, rcu_पढ़ो_unlock()
 * is responsible क्रम deboosting, which it करोes via rt_mutex_unlock().
 * Unक्रमtunately, this function acquires the scheduler's runqueue and
 * priority-inheritance spinlocks.  This means that deadlock could result
 * अगर the caller of rcu_पढ़ो_unlock() alपढ़ोy holds one of these locks or
 * any lock that is ever acquired जबतक holding them.
 *
 * That said, RCU पढ़ोers are never priority boosted unless they were
 * preempted.  Thereक्रमe, one way to aव्योम deadlock is to make sure
 * that preemption never happens within any RCU पढ़ो-side critical
 * section whose outermost rcu_पढ़ो_unlock() is called with one of
 * rt_mutex_unlock()'s locks held.  Such preemption can be aव्योमed in
 * a number of ways, क्रम example, by invoking preempt_disable() beक्रमe
 * critical section's outermost rcu_पढ़ो_lock().
 *
 * Given that the set of locks acquired by rt_mutex_unlock() might change
 * at any समय, a somewhat more future-proofed approach is to make sure
 * that that preemption never happens within any RCU पढ़ो-side critical
 * section whose outermost rcu_पढ़ो_unlock() is called with irqs disabled.
 * This approach relies on the fact that rt_mutex_unlock() currently only
 * acquires irq-disabled locks.
 *
 * The second of these two approaches is best in most situations,
 * however, the first approach can also be useful, at least to those
 * developers willing to keep abreast of the set of locks acquired by
 * rt_mutex_unlock().
 *
 * See rcu_पढ़ो_lock() क्रम more inक्रमmation.
 */
अटल अंतरभूत व्योम rcu_पढ़ो_unlock(व्योम)
अणु
	RCU_LOCKDEP_WARN(!rcu_is_watching(),
			 "rcu_read_unlock() used illegally while idle");
	__release(RCU);
	__rcu_पढ़ो_unlock();
	rcu_lock_release(&rcu_lock_map); /* Keep acq info क्रम rls diags. */
पूर्ण

/**
 * rcu_पढ़ो_lock_bh() - mark the beginning of an RCU-bh critical section
 *
 * This is equivalent of rcu_पढ़ो_lock(), but also disables softirqs.
 * Note that anything अन्यथा that disables softirqs can also serve as
 * an RCU पढ़ो-side critical section.
 *
 * Note that rcu_पढ़ो_lock_bh() and the matching rcu_पढ़ो_unlock_bh()
 * must occur in the same context, क्रम example, it is illegal to invoke
 * rcu_पढ़ो_unlock_bh() from one task अगर the matching rcu_पढ़ो_lock_bh()
 * was invoked from some other task.
 */
अटल अंतरभूत व्योम rcu_पढ़ो_lock_bh(व्योम)
अणु
	local_bh_disable();
	__acquire(RCU_BH);
	rcu_lock_acquire(&rcu_bh_lock_map);
	RCU_LOCKDEP_WARN(!rcu_is_watching(),
			 "rcu_read_lock_bh() used illegally while idle");
पूर्ण

/**
 * rcu_पढ़ो_unlock_bh() - marks the end of a softirq-only RCU critical section
 *
 * See rcu_पढ़ो_lock_bh() क्रम more inक्रमmation.
 */
अटल अंतरभूत व्योम rcu_पढ़ो_unlock_bh(व्योम)
अणु
	RCU_LOCKDEP_WARN(!rcu_is_watching(),
			 "rcu_read_unlock_bh() used illegally while idle");
	rcu_lock_release(&rcu_bh_lock_map);
	__release(RCU_BH);
	local_bh_enable();
पूर्ण

/**
 * rcu_पढ़ो_lock_sched() - mark the beginning of a RCU-sched critical section
 *
 * This is equivalent of rcu_पढ़ो_lock(), but disables preemption.
 * Read-side critical sections can also be पूर्णांकroduced by anything अन्यथा
 * that disables preemption, including local_irq_disable() and मित्रs.
 *
 * Note that rcu_पढ़ो_lock_sched() and the matching rcu_पढ़ो_unlock_sched()
 * must occur in the same context, क्रम example, it is illegal to invoke
 * rcu_पढ़ो_unlock_sched() from process context अगर the matching
 * rcu_पढ़ो_lock_sched() was invoked from an NMI handler.
 */
अटल अंतरभूत व्योम rcu_पढ़ो_lock_sched(व्योम)
अणु
	preempt_disable();
	__acquire(RCU_SCHED);
	rcu_lock_acquire(&rcu_sched_lock_map);
	RCU_LOCKDEP_WARN(!rcu_is_watching(),
			 "rcu_read_lock_sched() used illegally while idle");
पूर्ण

/* Used by lockdep and tracing: cannot be traced, cannot call lockdep. */
अटल अंतरभूत notrace व्योम rcu_पढ़ो_lock_sched_notrace(व्योम)
अणु
	preempt_disable_notrace();
	__acquire(RCU_SCHED);
पूर्ण

/**
 * rcu_पढ़ो_unlock_sched() - marks the end of a RCU-classic critical section
 *
 * See rcu_पढ़ो_lock_sched() क्रम more inक्रमmation.
 */
अटल अंतरभूत व्योम rcu_पढ़ो_unlock_sched(व्योम)
अणु
	RCU_LOCKDEP_WARN(!rcu_is_watching(),
			 "rcu_read_unlock_sched() used illegally while idle");
	rcu_lock_release(&rcu_sched_lock_map);
	__release(RCU_SCHED);
	preempt_enable();
पूर्ण

/* Used by lockdep and tracing: cannot be traced, cannot call lockdep. */
अटल अंतरभूत notrace व्योम rcu_पढ़ो_unlock_sched_notrace(व्योम)
अणु
	__release(RCU_SCHED);
	preempt_enable_notrace();
पूर्ण

/**
 * RCU_INIT_POINTER() - initialize an RCU रक्षित poपूर्णांकer
 * @p: The poपूर्णांकer to be initialized.
 * @v: The value to initialized the poपूर्णांकer to.
 *
 * Initialize an RCU-रक्षित poपूर्णांकer in special हालs where पढ़ोers
 * करो not need ordering स्थिरraपूर्णांकs on the CPU or the compiler.  These
 * special हालs are:
 *
 * 1.	This use of RCU_INIT_POINTER() is शून्यing out the poपूर्णांकer *or*
 * 2.	The caller has taken whatever steps are required to prevent
 *	RCU पढ़ोers from concurrently accessing this poपूर्णांकer *or*
 * 3.	The referenced data काष्ठाure has alपढ़ोy been exposed to
 *	पढ़ोers either at compile समय or via rcu_assign_poपूर्णांकer() *and*
 *
 *	a.	You have not made *any* पढ़ोer-visible changes to
 *		this काष्ठाure since then *or*
 *	b.	It is OK क्रम पढ़ोers accessing this काष्ठाure from its
 *		new location to see the old state of the काष्ठाure.  (For
 *		example, the changes were to statistical counters or to
 *		other state where exact synchronization is not required.)
 *
 * Failure to follow these rules governing use of RCU_INIT_POINTER() will
 * result in impossible-to-diagnose memory corruption.  As in the काष्ठाures
 * will look OK in crash dumps, but any concurrent RCU पढ़ोers might
 * see pre-initialized values of the referenced data काष्ठाure.  So
 * please be very careful how you use RCU_INIT_POINTER()!!!
 *
 * If you are creating an RCU-रक्षित linked काष्ठाure that is accessed
 * by a single बाह्यal-to-काष्ठाure RCU-रक्षित poपूर्णांकer, then you may
 * use RCU_INIT_POINTER() to initialize the पूर्णांकernal RCU-रक्षित
 * poपूर्णांकers, but you must use rcu_assign_poपूर्णांकer() to initialize the
 * बाह्यal-to-काष्ठाure poपूर्णांकer *after* you have completely initialized
 * the पढ़ोer-accessible portions of the linked काष्ठाure.
 *
 * Note that unlike rcu_assign_poपूर्णांकer(), RCU_INIT_POINTER() provides no
 * ordering guarantees क्रम either the CPU or the compiler.
 */
#घोषणा RCU_INIT_POINTER(p, v) \
	करो अणु \
		rcu_check_sparse(p, __rcu); \
		WRITE_ONCE(p, RCU_INITIALIZER(v)); \
	पूर्ण जबतक (0)

/**
 * RCU_POINTER_INITIALIZER() - अटलally initialize an RCU रक्षित poपूर्णांकer
 * @p: The poपूर्णांकer to be initialized.
 * @v: The value to initialized the poपूर्णांकer to.
 *
 * GCC-style initialization क्रम an RCU-रक्षित poपूर्णांकer in a काष्ठाure field.
 */
#घोषणा RCU_POINTER_INITIALIZER(p, v) \
		.p = RCU_INITIALIZER(v)

/*
 * Does the specअगरied offset indicate that the corresponding rcu_head
 * काष्ठाure can be handled by kvमुक्त_rcu()?
 */
#घोषणा __is_kvमुक्त_rcu_offset(offset) ((offset) < 4096)

/**
 * kमुक्त_rcu() - kमुक्त an object after a grace period.
 * @ptr: poपूर्णांकer to kमुक्त क्रम both single- and द्विगुन-argument invocations.
 * @rhf: the name of the काष्ठा rcu_head within the type of @ptr,
 *       but only क्रम द्विगुन-argument invocations.
 *
 * Many rcu callbacks functions just call kमुक्त() on the base काष्ठाure.
 * These functions are trivial, but their size adds up, and furthermore
 * when they are used in a kernel module, that module must invoke the
 * high-latency rcu_barrier() function at module-unload समय.
 *
 * The kमुक्त_rcu() function handles this issue.  Rather than encoding a
 * function address in the embedded rcu_head काष्ठाure, kमुक्त_rcu() instead
 * encodes the offset of the rcu_head काष्ठाure within the base काष्ठाure.
 * Because the functions are not allowed in the low-order 4096 bytes of
 * kernel भव memory, offsets up to 4095 bytes can be accommodated.
 * If the offset is larger than 4095 bytes, a compile-समय error will
 * be generated in kvमुक्त_rcu_arg_2(). If this error is triggered, you can
 * either fall back to use of call_rcu() or rearrange the काष्ठाure to
 * position the rcu_head काष्ठाure पूर्णांकo the first 4096 bytes.
 *
 * Note that the allowable offset might decrease in the future, क्रम example,
 * to allow something like kmem_cache_मुक्त_rcu().
 *
 * The BUILD_BUG_ON check must not involve any function calls, hence the
 * checks are करोne in macros here.
 */
#घोषणा kमुक्त_rcu(ptr, rhf...) kvमुक्त_rcu(ptr, ## rhf)

/**
 * kvमुक्त_rcu() - kvमुक्त an object after a grace period.
 *
 * This macro consists of one or two arguments and it is
 * based on whether an object is head-less or not. If it
 * has a head then a semantic stays the same as it used
 * to be beक्रमe:
 *
 *     kvमुक्त_rcu(ptr, rhf);
 *
 * where @ptr is a poपूर्णांकer to kvमुक्त(), @rhf is the name
 * of the rcu_head काष्ठाure within the type of @ptr.
 *
 * When it comes to head-less variant, only one argument
 * is passed and that is just a poपूर्णांकer which has to be
 * मुक्तd after a grace period. Thereक्रमe the semantic is
 *
 *     kvमुक्त_rcu(ptr);
 *
 * where @ptr is a poपूर्णांकer to kvमुक्त().
 *
 * Please note, head-less way of मुक्तing is permitted to
 * use from a context that has to follow might_sleep()
 * annotation. Otherwise, please चयन and embed the
 * rcu_head काष्ठाure within the type of @ptr.
 */
#घोषणा kvमुक्त_rcu(...) KVFREE_GET_MACRO(__VA_ARGS__,		\
	kvमुक्त_rcu_arg_2, kvमुक्त_rcu_arg_1)(__VA_ARGS__)

#घोषणा KVFREE_GET_MACRO(_1, _2, NAME, ...) NAME
#घोषणा kvमुक्त_rcu_arg_2(ptr, rhf)					\
करो अणु									\
	typeof (ptr) ___p = (ptr);					\
									\
	अगर (___p) अणु									\
		BUILD_BUG_ON(!__is_kvमुक्त_rcu_offset(दुरत्व(typeof(*(ptr)), rhf)));	\
		kvमुक्त_call_rcu(&((___p)->rhf), (rcu_callback_t)(अचिन्हित दीर्घ)		\
			(दुरत्व(typeof(*(ptr)), rhf)));				\
	पूर्ण										\
पूर्ण जबतक (0)

#घोषणा kvमुक्त_rcu_arg_1(ptr)					\
करो अणु								\
	typeof(ptr) ___p = (ptr);				\
								\
	अगर (___p)						\
		kvमुक्त_call_rcu(शून्य, (rcu_callback_t) (___p));	\
पूर्ण जबतक (0)

/*
 * Place this after a lock-acquisition primitive to guarantee that
 * an UNLOCK+LOCK pair acts as a full barrier.  This guarantee applies
 * अगर the UNLOCK and LOCK are executed by the same CPU or अगर the
 * UNLOCK and LOCK operate on the same lock variable.
 */
#अगर_घोषित CONFIG_ARCH_WEAK_RELEASE_ACQUIRE
#घोषणा smp_mb__after_unlock_lock()	smp_mb()  /* Full ordering क्रम lock. */
#अन्यथा /* #अगर_घोषित CONFIG_ARCH_WEAK_RELEASE_ACQUIRE */
#घोषणा smp_mb__after_unlock_lock()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_ARCH_WEAK_RELEASE_ACQUIRE */


/* Has the specअगरied rcu_head काष्ठाure been handed to call_rcu()? */

/**
 * rcu_head_init - Initialize rcu_head क्रम rcu_head_after_call_rcu()
 * @rhp: The rcu_head काष्ठाure to initialize.
 *
 * If you पूर्णांकend to invoke rcu_head_after_call_rcu() to test whether a
 * given rcu_head काष्ठाure has alपढ़ोy been passed to call_rcu(), then
 * you must also invoke this rcu_head_init() function on it just after
 * allocating that काष्ठाure.  Calls to this function must not race with
 * calls to call_rcu(), rcu_head_after_call_rcu(), or callback invocation.
 */
अटल अंतरभूत व्योम rcu_head_init(काष्ठा rcu_head *rhp)
अणु
	rhp->func = (rcu_callback_t)~0L;
पूर्ण

/**
 * rcu_head_after_call_rcu() - Has this rcu_head been passed to call_rcu()?
 * @rhp: The rcu_head काष्ठाure to test.
 * @f: The function passed to call_rcu() aदीर्घ with @rhp.
 *
 * Returns @true अगर the @rhp has been passed to call_rcu() with @func,
 * and @false otherwise.  Emits a warning in any other हाल, including
 * the हाल where @rhp has alपढ़ोy been invoked after a grace period.
 * Calls to this function must not race with callback invocation.  One way
 * to aव्योम such races is to enबंद the call to rcu_head_after_call_rcu()
 * in an RCU पढ़ो-side critical section that includes a पढ़ो-side fetch
 * of the poपूर्णांकer to the काष्ठाure containing @rhp.
 */
अटल अंतरभूत bool
rcu_head_after_call_rcu(काष्ठा rcu_head *rhp, rcu_callback_t f)
अणु
	rcu_callback_t func = READ_ONCE(rhp->func);

	अगर (func == f)
		वापस true;
	WARN_ON_ONCE(func != (rcu_callback_t)~0L);
	वापस false;
पूर्ण

/* kernel/ksysfs.c definitions */
बाह्य पूर्णांक rcu_expedited;
बाह्य पूर्णांक rcu_normal;

#पूर्ण_अगर /* __LINUX_RCUPDATE_H */
