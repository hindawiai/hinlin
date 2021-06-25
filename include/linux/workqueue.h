<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * workqueue.h --- work queue handling क्रम Linux.
 */

#अगर_अघोषित _LINUX_WORKQUEUE_H
#घोषणा _LINUX_WORKQUEUE_H

#समावेश <linux/समयr.h>
#समावेश <linux/linkage.h>
#समावेश <linux/bitops.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/atomic.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/rcupdate.h>

काष्ठा workqueue_काष्ठा;

काष्ठा work_काष्ठा;
प्रकार व्योम (*work_func_t)(काष्ठा work_काष्ठा *work);
व्योम delayed_work_समयr_fn(काष्ठा समयr_list *t);

/*
 * The first word is the work queue poपूर्णांकer and the flags rolled पूर्णांकo
 * one
 */
#घोषणा work_data_bits(work) ((अचिन्हित दीर्घ *)(&(work)->data))

क्रमागत अणु
	WORK_STRUCT_PENDING_BIT	= 0,	/* work item is pending execution */
	WORK_STRUCT_DELAYED_BIT	= 1,	/* work item is delayed */
	WORK_STRUCT_PWQ_BIT	= 2,	/* data poपूर्णांकs to pwq */
	WORK_STRUCT_LINKED_BIT	= 3,	/* next work is linked to this one */
#अगर_घोषित CONFIG_DEBUG_OBJECTS_WORK
	WORK_STRUCT_STATIC_BIT	= 4,	/* अटल initializer (debugobjects) */
	WORK_STRUCT_COLOR_SHIFT	= 5,	/* color क्रम workqueue flushing */
#अन्यथा
	WORK_STRUCT_COLOR_SHIFT	= 4,	/* color क्रम workqueue flushing */
#पूर्ण_अगर

	WORK_STRUCT_COLOR_BITS	= 4,

	WORK_STRUCT_PENDING	= 1 << WORK_STRUCT_PENDING_BIT,
	WORK_STRUCT_DELAYED	= 1 << WORK_STRUCT_DELAYED_BIT,
	WORK_STRUCT_PWQ		= 1 << WORK_STRUCT_PWQ_BIT,
	WORK_STRUCT_LINKED	= 1 << WORK_STRUCT_LINKED_BIT,
#अगर_घोषित CONFIG_DEBUG_OBJECTS_WORK
	WORK_STRUCT_STATIC	= 1 << WORK_STRUCT_STATIC_BIT,
#अन्यथा
	WORK_STRUCT_STATIC	= 0,
#पूर्ण_अगर

	/*
	 * The last color is no color used क्रम works which करोn't
	 * participate in workqueue flushing.
	 */
	WORK_NR_COLORS		= (1 << WORK_STRUCT_COLOR_BITS) - 1,
	WORK_NO_COLOR		= WORK_NR_COLORS,

	/* not bound to any CPU, prefer the local CPU */
	WORK_CPU_UNBOUND	= NR_CPUS,

	/*
	 * Reserve 8 bits off of pwq poपूर्णांकer w/ debugobjects turned off.
	 * This makes pwqs aligned to 256 bytes and allows 15 workqueue
	 * flush colors.
	 */
	WORK_STRUCT_FLAG_BITS	= WORK_STRUCT_COLOR_SHIFT +
				  WORK_STRUCT_COLOR_BITS,

	/* data contains off-queue inक्रमmation when !WORK_STRUCT_PWQ */
	WORK_OFFQ_FLAG_BASE	= WORK_STRUCT_COLOR_SHIFT,

	__WORK_OFFQ_CANCELING	= WORK_OFFQ_FLAG_BASE,
	WORK_OFFQ_CANCELING	= (1 << __WORK_OFFQ_CANCELING),

	/*
	 * When a work item is off queue, its high bits poपूर्णांक to the last
	 * pool it was on.  Cap at 31 bits and use the highest number to
	 * indicate that no pool is associated.
	 */
	WORK_OFFQ_FLAG_BITS	= 1,
	WORK_OFFQ_POOL_SHIFT	= WORK_OFFQ_FLAG_BASE + WORK_OFFQ_FLAG_BITS,
	WORK_OFFQ_LEFT		= BITS_PER_LONG - WORK_OFFQ_POOL_SHIFT,
	WORK_OFFQ_POOL_BITS	= WORK_OFFQ_LEFT <= 31 ? WORK_OFFQ_LEFT : 31,
	WORK_OFFQ_POOL_NONE	= (1LU << WORK_OFFQ_POOL_BITS) - 1,

	/* convenience स्थिरants */
	WORK_STRUCT_FLAG_MASK	= (1UL << WORK_STRUCT_FLAG_BITS) - 1,
	WORK_STRUCT_WQ_DATA_MASK = ~WORK_STRUCT_FLAG_MASK,
	WORK_STRUCT_NO_POOL	= (अचिन्हित दीर्घ)WORK_OFFQ_POOL_NONE << WORK_OFFQ_POOL_SHIFT,

	/* bit mask क्रम work_busy() वापस values */
	WORK_BUSY_PENDING	= 1 << 0,
	WORK_BUSY_RUNNING	= 1 << 1,

	/* maximum string length क्रम set_worker_desc() */
	WORKER_DESC_LEN		= 24,
पूर्ण;

काष्ठा work_काष्ठा अणु
	atomic_दीर्घ_t data;
	काष्ठा list_head entry;
	work_func_t func;
#अगर_घोषित CONFIG_LOCKDEP
	काष्ठा lockdep_map lockdep_map;
#पूर्ण_अगर
पूर्ण;

#घोषणा WORK_DATA_INIT()	ATOMIC_LONG_INIT((अचिन्हित दीर्घ)WORK_STRUCT_NO_POOL)
#घोषणा WORK_DATA_STATIC_INIT()	\
	ATOMIC_LONG_INIT((अचिन्हित दीर्घ)(WORK_STRUCT_NO_POOL | WORK_STRUCT_STATIC))

काष्ठा delayed_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा समयr_list समयr;

	/* target workqueue and CPU ->समयr uses to queue ->work */
	काष्ठा workqueue_काष्ठा *wq;
	पूर्णांक cpu;
पूर्ण;

काष्ठा rcu_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा rcu_head rcu;

	/* target workqueue ->rcu uses to queue ->work */
	काष्ठा workqueue_काष्ठा *wq;
पूर्ण;

/**
 * काष्ठा workqueue_attrs - A काष्ठा क्रम workqueue attributes.
 *
 * This can be used to change attributes of an unbound workqueue.
 */
काष्ठा workqueue_attrs अणु
	/**
	 * @nice: nice level
	 */
	पूर्णांक nice;

	/**
	 * @cpumask: allowed CPUs
	 */
	cpumask_var_t cpumask;

	/**
	 * @no_numa: disable NUMA affinity
	 *
	 * Unlike other fields, ``no_numa`` isn't a property of a worker_pool. It
	 * only modअगरies how :c:func:`apply_workqueue_attrs` select pools and thus
	 * करोesn't participate in pool hash calculations or equality comparisons.
	 */
	bool no_numa;
पूर्ण;

अटल अंतरभूत काष्ठा delayed_work *to_delayed_work(काष्ठा work_काष्ठा *work)
अणु
	वापस container_of(work, काष्ठा delayed_work, work);
पूर्ण

अटल अंतरभूत काष्ठा rcu_work *to_rcu_work(काष्ठा work_काष्ठा *work)
अणु
	वापस container_of(work, काष्ठा rcu_work, work);
पूर्ण

काष्ठा execute_work अणु
	काष्ठा work_काष्ठा work;
पूर्ण;

#अगर_घोषित CONFIG_LOCKDEP
/*
 * NB: because we have to copy the lockdep_map, setting _key
 * here is required, otherwise it could get initialised to the
 * copy of the lockdep_map!
 */
#घोषणा __WORK_INIT_LOCKDEP_MAP(n, k) \
	.lockdep_map = STATIC_LOCKDEP_MAP_INIT(n, k),
#अन्यथा
#घोषणा __WORK_INIT_LOCKDEP_MAP(n, k)
#पूर्ण_अगर

#घोषणा __WORK_INITIALIZER(n, f) अणु					\
	.data = WORK_DATA_STATIC_INIT(),				\
	.entry	= अणु &(n).entry, &(n).entry पूर्ण,				\
	.func = (f),							\
	__WORK_INIT_LOCKDEP_MAP(#n, &(n))				\
	पूर्ण

#घोषणा __DELAYED_WORK_INITIALIZER(n, f, tflags) अणु			\
	.work = __WORK_INITIALIZER((n).work, (f)),			\
	.समयr = __TIMER_INITIALIZER(delayed_work_समयr_fn,\
				     (tflags) | TIMER_IRQSAFE),		\
	पूर्ण

#घोषणा DECLARE_WORK(n, f)						\
	काष्ठा work_काष्ठा n = __WORK_INITIALIZER(n, f)

#घोषणा DECLARE_DELAYED_WORK(n, f)					\
	काष्ठा delayed_work n = __DELAYED_WORK_INITIALIZER(n, f, 0)

#घोषणा DECLARE_DEFERRABLE_WORK(n, f)					\
	काष्ठा delayed_work n = __DELAYED_WORK_INITIALIZER(n, f, TIMER_DEFERRABLE)

#अगर_घोषित CONFIG_DEBUG_OBJECTS_WORK
बाह्य व्योम __init_work(काष्ठा work_काष्ठा *work, पूर्णांक onstack);
बाह्य व्योम destroy_work_on_stack(काष्ठा work_काष्ठा *work);
बाह्य व्योम destroy_delayed_work_on_stack(काष्ठा delayed_work *work);
अटल अंतरभूत अचिन्हित पूर्णांक work_अटल(काष्ठा work_काष्ठा *work)
अणु
	वापस *work_data_bits(work) & WORK_STRUCT_STATIC;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम __init_work(काष्ठा work_काष्ठा *work, पूर्णांक onstack) अणु पूर्ण
अटल अंतरभूत व्योम destroy_work_on_stack(काष्ठा work_काष्ठा *work) अणु पूर्ण
अटल अंतरभूत व्योम destroy_delayed_work_on_stack(काष्ठा delayed_work *work) अणु पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक work_अटल(काष्ठा work_काष्ठा *work) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/*
 * initialize all of a work item in one go
 *
 * NOTE! No poपूर्णांक in using "atomic_long_set()": using a direct
 * assignment of the work data initializer allows the compiler
 * to generate better code.
 */
#अगर_घोषित CONFIG_LOCKDEP
#घोषणा __INIT_WORK(_work, _func, _onstack)				\
	करो अणु								\
		अटल काष्ठा lock_class_key __key;			\
									\
		__init_work((_work), _onstack);				\
		(_work)->data = (atomic_दीर्घ_t) WORK_DATA_INIT();	\
		lockdep_init_map(&(_work)->lockdep_map, "(work_completion)"#_work, &__key, 0); \
		INIT_LIST_HEAD(&(_work)->entry);			\
		(_work)->func = (_func);				\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा __INIT_WORK(_work, _func, _onstack)				\
	करो अणु								\
		__init_work((_work), _onstack);				\
		(_work)->data = (atomic_दीर्घ_t) WORK_DATA_INIT();	\
		INIT_LIST_HEAD(&(_work)->entry);			\
		(_work)->func = (_func);				\
	पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा INIT_WORK(_work, _func)						\
	__INIT_WORK((_work), (_func), 0)

#घोषणा INIT_WORK_ONSTACK(_work, _func)					\
	__INIT_WORK((_work), (_func), 1)

#घोषणा __INIT_DELAYED_WORK(_work, _func, _tflags)			\
	करो अणु								\
		INIT_WORK(&(_work)->work, (_func));			\
		__init_समयr(&(_work)->समयr,				\
			     delayed_work_समयr_fn,			\
			     (_tflags) | TIMER_IRQSAFE);		\
	पूर्ण जबतक (0)

#घोषणा __INIT_DELAYED_WORK_ONSTACK(_work, _func, _tflags)		\
	करो अणु								\
		INIT_WORK_ONSTACK(&(_work)->work, (_func));		\
		__init_समयr_on_stack(&(_work)->समयr,			\
				      delayed_work_समयr_fn,		\
				      (_tflags) | TIMER_IRQSAFE);	\
	पूर्ण जबतक (0)

#घोषणा INIT_DELAYED_WORK(_work, _func)					\
	__INIT_DELAYED_WORK(_work, _func, 0)

#घोषणा INIT_DELAYED_WORK_ONSTACK(_work, _func)				\
	__INIT_DELAYED_WORK_ONSTACK(_work, _func, 0)

#घोषणा INIT_DEFERRABLE_WORK(_work, _func)				\
	__INIT_DELAYED_WORK(_work, _func, TIMER_DEFERRABLE)

#घोषणा INIT_DEFERRABLE_WORK_ONSTACK(_work, _func)			\
	__INIT_DELAYED_WORK_ONSTACK(_work, _func, TIMER_DEFERRABLE)

#घोषणा INIT_RCU_WORK(_work, _func)					\
	INIT_WORK(&(_work)->work, (_func))

#घोषणा INIT_RCU_WORK_ONSTACK(_work, _func)				\
	INIT_WORK_ONSTACK(&(_work)->work, (_func))

/**
 * work_pending - Find out whether a work item is currently pending
 * @work: The work item in question
 */
#घोषणा work_pending(work) \
	test_bit(WORK_STRUCT_PENDING_BIT, work_data_bits(work))

/**
 * delayed_work_pending - Find out whether a delayable work item is currently
 * pending
 * @w: The work item in question
 */
#घोषणा delayed_work_pending(w) \
	work_pending(&(w)->work)

/*
 * Workqueue flags and स्थिरants.  For details, please refer to
 * Documentation/core-api/workqueue.rst.
 */
क्रमागत अणु
	WQ_UNBOUND		= 1 << 1, /* not bound to any cpu */
	WQ_FREEZABLE		= 1 << 2, /* मुक्तze during suspend */
	WQ_MEM_RECLAIM		= 1 << 3, /* may be used क्रम memory reclaim */
	WQ_HIGHPRI		= 1 << 4, /* high priority */
	WQ_CPU_INTENSIVE	= 1 << 5, /* cpu पूर्णांकensive workqueue */
	WQ_SYSFS		= 1 << 6, /* visible in sysfs, see workqueue_sysfs_रेजिस्टर() */

	/*
	 * Per-cpu workqueues are generally preferred because they tend to
	 * show better perक्रमmance thanks to cache locality.  Per-cpu
	 * workqueues exclude the scheduler from choosing the CPU to
	 * execute the worker thपढ़ोs, which has an unक्रमtunate side effect
	 * of increasing घातer consumption.
	 *
	 * The scheduler considers a CPU idle अगर it करोesn't have any task
	 * to execute and tries to keep idle cores idle to conserve घातer;
	 * however, क्रम example, a per-cpu work item scheduled from an
	 * पूर्णांकerrupt handler on an idle CPU will क्रमce the scheduler to
	 * excute the work item on that CPU अवरोधing the idleness, which in
	 * turn may lead to more scheduling choices which are sub-optimal
	 * in terms of घातer consumption.
	 *
	 * Workqueues marked with WQ_POWER_EFFICIENT are per-cpu by शेष
	 * but become unbound अगर workqueue.घातer_efficient kernel param is
	 * specअगरied.  Per-cpu workqueues which are identअगरied to
	 * contribute signअगरicantly to घातer-consumption are identअगरied and
	 * marked with this flag and enabling the घातer_efficient mode
	 * leads to noticeable घातer saving at the cost of small
	 * perक्रमmance disadvantage.
	 *
	 * http://thपढ़ो.gmane.org/gmane.linux.kernel/1480396
	 */
	WQ_POWER_EFFICIENT	= 1 << 7,

	__WQ_DRAINING		= 1 << 16, /* पूर्णांकernal: workqueue is draining */
	__WQ_ORDERED		= 1 << 17, /* पूर्णांकernal: workqueue is ordered */
	__WQ_LEGACY		= 1 << 18, /* पूर्णांकernal: create*_workqueue() */
	__WQ_ORDERED_EXPLICIT	= 1 << 19, /* पूर्णांकernal: alloc_ordered_workqueue() */

	WQ_MAX_ACTIVE		= 512,	  /* I like 512, better ideas? */
	WQ_MAX_UNBOUND_PER_CPU	= 4,	  /* 4 * #cpus क्रम unbound wq */
	WQ_DFL_ACTIVE		= WQ_MAX_ACTIVE / 2,
पूर्ण;

/* unbound wq's aren't per-cpu, scale max_active according to #cpus */
#घोषणा WQ_UNBOUND_MAX_ACTIVE	\
	max_t(पूर्णांक, WQ_MAX_ACTIVE, num_possible_cpus() * WQ_MAX_UNBOUND_PER_CPU)

/*
 * System-wide workqueues which are always present.
 *
 * प्रणाली_wq is the one used by schedule[_delayed]_work[_on]().
 * Multi-CPU multi-thपढ़ोed.  There are users which expect relatively
 * लघु queue flush समय.  Don't queue works which can run क्रम too
 * दीर्घ.
 *
 * प्रणाली_highpri_wq is similar to प्रणाली_wq but क्रम work items which
 * require WQ_HIGHPRI.
 *
 * प्रणाली_दीर्घ_wq is similar to प्रणाली_wq but may host दीर्घ running
 * works.  Queue flushing might take relatively दीर्घ.
 *
 * प्रणाली_unbound_wq is unbound workqueue.  Workers are not bound to
 * any specअगरic CPU, not concurrency managed, and all queued works are
 * executed immediately as दीर्घ as max_active limit is not reached and
 * resources are available.
 *
 * प्रणाली_मुक्तzable_wq is equivalent to प्रणाली_wq except that it's
 * मुक्तzable.
 *
 * *_घातer_efficient_wq are inclined towards saving घातer and converted
 * पूर्णांकo WQ_UNBOUND variants अगर 'wq_power_efficient' is enabled; otherwise,
 * they are same as their non-घातer-efficient counterparts - e.g.
 * प्रणाली_घातer_efficient_wq is identical to प्रणाली_wq अगर
 * 'wq_power_efficient' is disabled.  See WQ_POWER_EFFICIENT क्रम more info.
 */
बाह्य काष्ठा workqueue_काष्ठा *प्रणाली_wq;
बाह्य काष्ठा workqueue_काष्ठा *प्रणाली_highpri_wq;
बाह्य काष्ठा workqueue_काष्ठा *प्रणाली_दीर्घ_wq;
बाह्य काष्ठा workqueue_काष्ठा *प्रणाली_unbound_wq;
बाह्य काष्ठा workqueue_काष्ठा *प्रणाली_मुक्तzable_wq;
बाह्य काष्ठा workqueue_काष्ठा *प्रणाली_घातer_efficient_wq;
बाह्य काष्ठा workqueue_काष्ठा *प्रणाली_मुक्तzable_घातer_efficient_wq;

/**
 * alloc_workqueue - allocate a workqueue
 * @fmt: म_लिखो क्रमmat क्रम the name of the workqueue
 * @flags: WQ_* flags
 * @max_active: max in-flight work items, 0 क्रम शेष
 * reमुख्यing args: args क्रम @fmt
 *
 * Allocate a workqueue with the specअगरied parameters.  For detailed
 * inक्रमmation on WQ_* flags, please refer to
 * Documentation/core-api/workqueue.rst.
 *
 * RETURNS:
 * Poपूर्णांकer to the allocated workqueue on success, %शून्य on failure.
 */
काष्ठा workqueue_काष्ठा *alloc_workqueue(स्थिर अक्षर *fmt,
					 अचिन्हित पूर्णांक flags,
					 पूर्णांक max_active, ...);

/**
 * alloc_ordered_workqueue - allocate an ordered workqueue
 * @fmt: म_लिखो क्रमmat क्रम the name of the workqueue
 * @flags: WQ_* flags (only WQ_FREEZABLE and WQ_MEM_RECLAIM are meaningful)
 * @args...: args क्रम @fmt
 *
 * Allocate an ordered workqueue.  An ordered workqueue executes at
 * most one work item at any given समय in the queued order.  They are
 * implemented as unbound workqueues with @max_active of one.
 *
 * RETURNS:
 * Poपूर्णांकer to the allocated workqueue on success, %शून्य on failure.
 */
#घोषणा alloc_ordered_workqueue(fmt, flags, args...)			\
	alloc_workqueue(fmt, WQ_UNBOUND | __WQ_ORDERED |		\
			__WQ_ORDERED_EXPLICIT | (flags), 1, ##args)

#घोषणा create_workqueue(name)						\
	alloc_workqueue("%s", __WQ_LEGACY | WQ_MEM_RECLAIM, 1, (name))
#घोषणा create_मुक्तzable_workqueue(name)				\
	alloc_workqueue("%s", __WQ_LEGACY | WQ_FREEZABLE | WQ_UNBOUND |	\
			WQ_MEM_RECLAIM, 1, (name))
#घोषणा create_singlethपढ़ो_workqueue(name)				\
	alloc_ordered_workqueue("%s", __WQ_LEGACY | WQ_MEM_RECLAIM, name)

बाह्य व्योम destroy_workqueue(काष्ठा workqueue_काष्ठा *wq);

काष्ठा workqueue_attrs *alloc_workqueue_attrs(व्योम);
व्योम मुक्त_workqueue_attrs(काष्ठा workqueue_attrs *attrs);
पूर्णांक apply_workqueue_attrs(काष्ठा workqueue_काष्ठा *wq,
			  स्थिर काष्ठा workqueue_attrs *attrs);
पूर्णांक workqueue_set_unbound_cpumask(cpumask_var_t cpumask);

बाह्य bool queue_work_on(पूर्णांक cpu, काष्ठा workqueue_काष्ठा *wq,
			काष्ठा work_काष्ठा *work);
बाह्य bool queue_work_node(पूर्णांक node, काष्ठा workqueue_काष्ठा *wq,
			    काष्ठा work_काष्ठा *work);
बाह्य bool queue_delayed_work_on(पूर्णांक cpu, काष्ठा workqueue_काष्ठा *wq,
			काष्ठा delayed_work *work, अचिन्हित दीर्घ delay);
बाह्य bool mod_delayed_work_on(पूर्णांक cpu, काष्ठा workqueue_काष्ठा *wq,
			काष्ठा delayed_work *dwork, अचिन्हित दीर्घ delay);
बाह्य bool queue_rcu_work(काष्ठा workqueue_काष्ठा *wq, काष्ठा rcu_work *rwork);

बाह्य व्योम flush_workqueue(काष्ठा workqueue_काष्ठा *wq);
बाह्य व्योम drain_workqueue(काष्ठा workqueue_काष्ठा *wq);

बाह्य पूर्णांक schedule_on_each_cpu(work_func_t func);

पूर्णांक execute_in_process_context(work_func_t fn, काष्ठा execute_work *);

बाह्य bool flush_work(काष्ठा work_काष्ठा *work);
बाह्य bool cancel_work_sync(काष्ठा work_काष्ठा *work);

बाह्य bool flush_delayed_work(काष्ठा delayed_work *dwork);
बाह्य bool cancel_delayed_work(काष्ठा delayed_work *dwork);
बाह्य bool cancel_delayed_work_sync(काष्ठा delayed_work *dwork);

बाह्य bool flush_rcu_work(काष्ठा rcu_work *rwork);

बाह्य व्योम workqueue_set_max_active(काष्ठा workqueue_काष्ठा *wq,
				     पूर्णांक max_active);
बाह्य काष्ठा work_काष्ठा *current_work(व्योम);
बाह्य bool current_is_workqueue_rescuer(व्योम);
बाह्य bool workqueue_congested(पूर्णांक cpu, काष्ठा workqueue_काष्ठा *wq);
बाह्य अचिन्हित पूर्णांक work_busy(काष्ठा work_काष्ठा *work);
बाह्य __म_लिखो(1, 2) व्योम set_worker_desc(स्थिर अक्षर *fmt, ...);
बाह्य व्योम prपूर्णांक_worker_info(स्थिर अक्षर *log_lvl, काष्ठा task_काष्ठा *task);
बाह्य व्योम show_workqueue_state(व्योम);
बाह्य व्योम wq_worker_comm(अक्षर *buf, माप_प्रकार size, काष्ठा task_काष्ठा *task);

/**
 * queue_work - queue work on a workqueue
 * @wq: workqueue to use
 * @work: work to queue
 *
 * Returns %false अगर @work was alपढ़ोy on a queue, %true otherwise.
 *
 * We queue the work to the CPU on which it was submitted, but अगर the CPU dies
 * it can be processed by another CPU.
 *
 * Memory-ordering properties:  If it वापसs %true, guarantees that all stores
 * preceding the call to queue_work() in the program order will be visible from
 * the CPU which will execute @work by the समय such work executes, e.g.,
 *
 * अणु x is initially 0 पूर्ण
 *
 *   CPU0				CPU1
 *
 *   WRITE_ONCE(x, 1);			[ @work is being executed ]
 *   r0 = queue_work(wq, work);		  r1 = READ_ONCE(x);
 *
 * Forbids: r0 == true && r1 == 0
 */
अटल अंतरभूत bool queue_work(काष्ठा workqueue_काष्ठा *wq,
			      काष्ठा work_काष्ठा *work)
अणु
	वापस queue_work_on(WORK_CPU_UNBOUND, wq, work);
पूर्ण

/**
 * queue_delayed_work - queue work on a workqueue after delay
 * @wq: workqueue to use
 * @dwork: delayable work to queue
 * @delay: number of jअगरfies to रुको beक्रमe queueing
 *
 * Equivalent to queue_delayed_work_on() but tries to use the local CPU.
 */
अटल अंतरभूत bool queue_delayed_work(काष्ठा workqueue_काष्ठा *wq,
				      काष्ठा delayed_work *dwork,
				      अचिन्हित दीर्घ delay)
अणु
	वापस queue_delayed_work_on(WORK_CPU_UNBOUND, wq, dwork, delay);
पूर्ण

/**
 * mod_delayed_work - modअगरy delay of or queue a delayed work
 * @wq: workqueue to use
 * @dwork: work to queue
 * @delay: number of jअगरfies to रुको beक्रमe queueing
 *
 * mod_delayed_work_on() on local CPU.
 */
अटल अंतरभूत bool mod_delayed_work(काष्ठा workqueue_काष्ठा *wq,
				    काष्ठा delayed_work *dwork,
				    अचिन्हित दीर्घ delay)
अणु
	वापस mod_delayed_work_on(WORK_CPU_UNBOUND, wq, dwork, delay);
पूर्ण

/**
 * schedule_work_on - put work task on a specअगरic cpu
 * @cpu: cpu to put the work task on
 * @work: job to be करोne
 *
 * This माला_दो a job on a specअगरic cpu
 */
अटल अंतरभूत bool schedule_work_on(पूर्णांक cpu, काष्ठा work_काष्ठा *work)
अणु
	वापस queue_work_on(cpu, प्रणाली_wq, work);
पूर्ण

/**
 * schedule_work - put work task in global workqueue
 * @work: job to be करोne
 *
 * Returns %false अगर @work was alपढ़ोy on the kernel-global workqueue and
 * %true otherwise.
 *
 * This माला_दो a job in the kernel-global workqueue अगर it was not alपढ़ोy
 * queued and leaves it in the same position on the kernel-global
 * workqueue otherwise.
 *
 * Shares the same memory-ordering properties of queue_work(), cf. the
 * DocBook header of queue_work().
 */
अटल अंतरभूत bool schedule_work(काष्ठा work_काष्ठा *work)
अणु
	वापस queue_work(प्रणाली_wq, work);
पूर्ण

/**
 * flush_scheduled_work - ensure that any scheduled work has run to completion.
 *
 * Forces execution of the kernel-global workqueue and blocks until its
 * completion.
 *
 * Think twice beक्रमe calling this function!  It's very easy to get पूर्णांकo
 * trouble अगर you करोn't take great care.  Either of the following situations
 * will lead to deadlock:
 *
 *	One of the work items currently on the workqueue needs to acquire
 *	a lock held by your code or its caller.
 *
 *	Your code is running in the context of a work routine.
 *
 * They will be detected by lockdep when they occur, but the first might not
 * occur very often.  It depends on what work items are on the workqueue and
 * what locks they need, which you have no control over.
 *
 * In most situations flushing the entire workqueue is overसमाप्त; you merely
 * need to know that a particular work item isn't queued and isn't running.
 * In such हालs you should use cancel_delayed_work_sync() or
 * cancel_work_sync() instead.
 */
अटल अंतरभूत व्योम flush_scheduled_work(व्योम)
अणु
	flush_workqueue(प्रणाली_wq);
पूर्ण

/**
 * schedule_delayed_work_on - queue work in global workqueue on CPU after delay
 * @cpu: cpu to use
 * @dwork: job to be करोne
 * @delay: number of jअगरfies to रुको
 *
 * After रुकोing क्रम a given समय this माला_दो a job in the kernel-global
 * workqueue on the specअगरied CPU.
 */
अटल अंतरभूत bool schedule_delayed_work_on(पूर्णांक cpu, काष्ठा delayed_work *dwork,
					    अचिन्हित दीर्घ delay)
अणु
	वापस queue_delayed_work_on(cpu, प्रणाली_wq, dwork, delay);
पूर्ण

/**
 * schedule_delayed_work - put work task in global workqueue after delay
 * @dwork: job to be करोne
 * @delay: number of jअगरfies to रुको or 0 क्रम immediate execution
 *
 * After रुकोing क्रम a given समय this माला_दो a job in the kernel-global
 * workqueue.
 */
अटल अंतरभूत bool schedule_delayed_work(काष्ठा delayed_work *dwork,
					 अचिन्हित दीर्घ delay)
अणु
	वापस queue_delayed_work(प्रणाली_wq, dwork, delay);
पूर्ण

#अगर_अघोषित CONFIG_SMP
अटल अंतरभूत दीर्घ work_on_cpu(पूर्णांक cpu, दीर्घ (*fn)(व्योम *), व्योम *arg)
अणु
	वापस fn(arg);
पूर्ण
अटल अंतरभूत दीर्घ work_on_cpu_safe(पूर्णांक cpu, दीर्घ (*fn)(व्योम *), व्योम *arg)
अणु
	वापस fn(arg);
पूर्ण
#अन्यथा
दीर्घ work_on_cpu(पूर्णांक cpu, दीर्घ (*fn)(व्योम *), व्योम *arg);
दीर्घ work_on_cpu_safe(पूर्णांक cpu, दीर्घ (*fn)(व्योम *), व्योम *arg);
#पूर्ण_अगर /* CONFIG_SMP */

#अगर_घोषित CONFIG_FREEZER
बाह्य व्योम मुक्तze_workqueues_begin(व्योम);
बाह्य bool मुक्तze_workqueues_busy(व्योम);
बाह्य व्योम thaw_workqueues(व्योम);
#पूर्ण_अगर /* CONFIG_FREEZER */

#अगर_घोषित CONFIG_SYSFS
पूर्णांक workqueue_sysfs_रेजिस्टर(काष्ठा workqueue_काष्ठा *wq);
#अन्यथा	/* CONFIG_SYSFS */
अटल अंतरभूत पूर्णांक workqueue_sysfs_रेजिस्टर(काष्ठा workqueue_काष्ठा *wq)
अणु वापस 0; पूर्ण
#पूर्ण_अगर	/* CONFIG_SYSFS */

#अगर_घोषित CONFIG_WQ_WATCHDOG
व्योम wq_watchकरोg_touch(पूर्णांक cpu);
#अन्यथा	/* CONFIG_WQ_WATCHDOG */
अटल अंतरभूत व्योम wq_watchकरोg_touch(पूर्णांक cpu) अणु पूर्ण
#पूर्ण_अगर	/* CONFIG_WQ_WATCHDOG */

#अगर_घोषित CONFIG_SMP
पूर्णांक workqueue_prepare_cpu(अचिन्हित पूर्णांक cpu);
पूर्णांक workqueue_online_cpu(अचिन्हित पूर्णांक cpu);
पूर्णांक workqueue_offline_cpu(अचिन्हित पूर्णांक cpu);
#पूर्ण_अगर

व्योम __init workqueue_init_early(व्योम);
व्योम __init workqueue_init(व्योम);

#पूर्ण_अगर
