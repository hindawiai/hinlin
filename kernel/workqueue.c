<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kernel/workqueue.c - generic async execution with shared worker pool
 *
 * Copyright (C) 2002		Ingo Molnar
 *
 *   Derived from the taskqueue/keventd code by:
 *     David Woodhouse <dwmw2@infradead.org>
 *     Andrew Morton
 *     Kai Petzke <wpp@marie.physik.tu-berlin.de>
 *     Theoकरोre Ts'o <tytso@mit.edu>
 *
 * Made to use alloc_percpu by Christoph Lameter.
 *
 * Copyright (C) 2010		SUSE Linux Products GmbH
 * Copyright (C) 2010		Tejun Heo <tj@kernel.org>
 *
 * This is the generic async execution mechanism.  Work items as are
 * executed in process context.  The worker pool is shared and
 * स्वतःmatically managed.  There are two worker pools क्रम each CPU (one क्रम
 * normal work items and the other क्रम high priority ones) and some extra
 * pools क्रम workqueues which are not bound to any specअगरic CPU - the
 * number of these backing pools is dynamic.
 *
 * Please पढ़ो Documentation/core-api/workqueue.rst क्रम details.
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/completion.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/debug_locks.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/idr.h>
#समावेश <linux/jhash.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/rculist.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched/isolation.h>
#समावेश <linux/nmi.h>
#समावेश <linux/kvm_para.h>

#समावेश "workqueue_internal.h"

क्रमागत अणु
	/*
	 * worker_pool flags
	 *
	 * A bound pool is either associated or disassociated with its CPU.
	 * While associated (!DISASSOCIATED), all workers are bound to the
	 * CPU and none has %WORKER_UNBOUND set and concurrency management
	 * is in effect.
	 *
	 * While DISASSOCIATED, the cpu may be offline and all workers have
	 * %WORKER_UNBOUND set and concurrency management disabled, and may
	 * be executing on any CPU.  The pool behaves as an unbound one.
	 *
	 * Note that DISASSOCIATED should be flipped only जबतक holding
	 * wq_pool_attach_mutex to aव्योम changing binding state जबतक
	 * worker_attach_to_pool() is in progress.
	 */
	POOL_MANAGER_ACTIVE	= 1 << 0,	/* being managed */
	POOL_DISASSOCIATED	= 1 << 2,	/* cpu can't serve workers */

	/* worker flags */
	WORKER_DIE		= 1 << 1,	/* die die die */
	WORKER_IDLE		= 1 << 2,	/* is idle */
	WORKER_PREP		= 1 << 3,	/* preparing to run works */
	WORKER_CPU_INTENSIVE	= 1 << 6,	/* cpu पूर्णांकensive */
	WORKER_UNBOUND		= 1 << 7,	/* worker is unbound */
	WORKER_REBOUND		= 1 << 8,	/* worker was rebound */

	WORKER_NOT_RUNNING	= WORKER_PREP | WORKER_CPU_INTENSIVE |
				  WORKER_UNBOUND | WORKER_REBOUND,

	NR_STD_WORKER_POOLS	= 2,		/* # standard pools per cpu */

	UNBOUND_POOL_HASH_ORDER	= 6,		/* hashed by pool->attrs */
	BUSY_WORKER_HASH_ORDER	= 6,		/* 64 poपूर्णांकers */

	MAX_IDLE_WORKERS_RATIO	= 4,		/* 1/4 of busy can be idle */
	IDLE_WORKER_TIMEOUT	= 300 * HZ,	/* keep idle ones क्रम 5 mins */

	MAYDAY_INITIAL_TIMEOUT  = HZ / 100 >= 2 ? HZ / 100 : 2,
						/* call क्रम help after 10ms
						   (min two ticks) */
	MAYDAY_INTERVAL		= HZ / 10,	/* and then every 100ms */
	CREATE_COOLDOWN		= HZ,		/* समय to breath after fail */

	/*
	 * Rescue workers are used only on emergencies and shared by
	 * all cpus.  Give MIN_NICE.
	 */
	RESCUER_NICE_LEVEL	= MIN_NICE,
	HIGHPRI_NICE_LEVEL	= MIN_NICE,

	WQ_NAME_LEN		= 24,
पूर्ण;

/*
 * Structure fields follow one of the following exclusion rules.
 *
 * I: Modअगरiable by initialization/deकाष्ठाion paths and पढ़ो-only क्रम
 *    everyone अन्यथा.
 *
 * P: Preemption रक्षित.  Disabling preemption is enough and should
 *    only be modअगरied and accessed from the local cpu.
 *
 * L: pool->lock रक्षित.  Access with pool->lock held.
 *
 * X: During normal operation, modअगरication requires pool->lock and should
 *    be करोne only from local cpu.  Either disabling preemption on local
 *    cpu or grabbing pool->lock is enough क्रम पढ़ो access.  If
 *    POOL_DISASSOCIATED is set, it's identical to L.
 *
 * A: wq_pool_attach_mutex रक्षित.
 *
 * PL: wq_pool_mutex रक्षित.
 *
 * PR: wq_pool_mutex रक्षित क्रम ग_लिखोs.  RCU रक्षित क्रम पढ़ोs.
 *
 * PW: wq_pool_mutex and wq->mutex रक्षित क्रम ग_लिखोs.  Either क्रम पढ़ोs.
 *
 * PWR: wq_pool_mutex and wq->mutex रक्षित क्रम ग_लिखोs.  Either or
 *      RCU क्रम पढ़ोs.
 *
 * WQ: wq->mutex रक्षित.
 *
 * WR: wq->mutex रक्षित क्रम ग_लिखोs.  RCU रक्षित क्रम पढ़ोs.
 *
 * MD: wq_mayday_lock रक्षित.
 */

/* काष्ठा worker is defined in workqueue_पूर्णांकernal.h */

काष्ठा worker_pool अणु
	raw_spinlock_t		lock;		/* the pool lock */
	पूर्णांक			cpu;		/* I: the associated cpu */
	पूर्णांक			node;		/* I: the associated node ID */
	पूर्णांक			id;		/* I: pool ID */
	अचिन्हित पूर्णांक		flags;		/* X: flags */

	अचिन्हित दीर्घ		watchकरोg_ts;	/* L: watchकरोg बारtamp */

	काष्ठा list_head	worklist;	/* L: list of pending works */

	पूर्णांक			nr_workers;	/* L: total number of workers */
	पूर्णांक			nr_idle;	/* L: currently idle workers */

	काष्ठा list_head	idle_list;	/* X: list of idle workers */
	काष्ठा समयr_list	idle_समयr;	/* L: worker idle समयout */
	काष्ठा समयr_list	mayday_समयr;	/* L: SOS समयr क्रम workers */

	/* a workers is either on busy_hash or idle_list, or the manager */
	DECLARE_HASHTABLE(busy_hash, BUSY_WORKER_HASH_ORDER);
						/* L: hash of busy workers */

	काष्ठा worker		*manager;	/* L: purely inक्रमmational */
	काष्ठा list_head	workers;	/* A: attached workers */
	काष्ठा completion	*detach_completion; /* all workers detached */

	काष्ठा ida		worker_ida;	/* worker IDs क्रम task name */

	काष्ठा workqueue_attrs	*attrs;		/* I: worker attributes */
	काष्ठा hlist_node	hash_node;	/* PL: unbound_pool_hash node */
	पूर्णांक			refcnt;		/* PL: refcnt क्रम unbound pools */

	/*
	 * The current concurrency level.  As it's likely to be accessed
	 * from other CPUs during try_to_wake_up(), put it in a separate
	 * cacheline.
	 */
	atomic_t		nr_running ____cacheline_aligned_in_smp;

	/*
	 * Deकाष्ठाion of pool is RCU रक्षित to allow dereferences
	 * from get_work_pool().
	 */
	काष्ठा rcu_head		rcu;
पूर्ण ____cacheline_aligned_in_smp;

/*
 * The per-pool workqueue.  While queued, the lower WORK_STRUCT_FLAG_BITS
 * of work_काष्ठा->data are used क्रम flags and the reमुख्यing high bits
 * poपूर्णांक to the pwq; thus, pwqs need to be aligned at two's घातer of the
 * number of flag bits.
 */
काष्ठा pool_workqueue अणु
	काष्ठा worker_pool	*pool;		/* I: the associated pool */
	काष्ठा workqueue_काष्ठा *wq;		/* I: the owning workqueue */
	पूर्णांक			work_color;	/* L: current color */
	पूर्णांक			flush_color;	/* L: flushing color */
	पूर्णांक			refcnt;		/* L: reference count */
	पूर्णांक			nr_in_flight[WORK_NR_COLORS];
						/* L: nr of in_flight works */
	पूर्णांक			nr_active;	/* L: nr of active works */
	पूर्णांक			max_active;	/* L: max active works */
	काष्ठा list_head	delayed_works;	/* L: delayed works */
	काष्ठा list_head	pwqs_node;	/* WR: node on wq->pwqs */
	काष्ठा list_head	mayday_node;	/* MD: node on wq->maydays */

	/*
	 * Release of unbound pwq is punted to प्रणाली_wq.  See put_pwq()
	 * and pwq_unbound_release_workfn() क्रम details.  pool_workqueue
	 * itself is also RCU रक्षित so that the first pwq can be
	 * determined without grabbing wq->mutex.
	 */
	काष्ठा work_काष्ठा	unbound_release_work;
	काष्ठा rcu_head		rcu;
पूर्ण __aligned(1 << WORK_STRUCT_FLAG_BITS);

/*
 * Structure used to रुको क्रम workqueue flush.
 */
काष्ठा wq_flusher अणु
	काष्ठा list_head	list;		/* WQ: list of flushers */
	पूर्णांक			flush_color;	/* WQ: flush color रुकोing क्रम */
	काष्ठा completion	करोne;		/* flush completion */
पूर्ण;

काष्ठा wq_device;

/*
 * The बाह्यally visible workqueue.  It relays the issued work items to
 * the appropriate worker_pool through its pool_workqueues.
 */
काष्ठा workqueue_काष्ठा अणु
	काष्ठा list_head	pwqs;		/* WR: all pwqs of this wq */
	काष्ठा list_head	list;		/* PR: list of all workqueues */

	काष्ठा mutex		mutex;		/* protects this wq */
	पूर्णांक			work_color;	/* WQ: current work color */
	पूर्णांक			flush_color;	/* WQ: current flush color */
	atomic_t		nr_pwqs_to_flush; /* flush in progress */
	काष्ठा wq_flusher	*first_flusher;	/* WQ: first flusher */
	काष्ठा list_head	flusher_queue;	/* WQ: flush रुकोers */
	काष्ठा list_head	flusher_overflow; /* WQ: flush overflow list */

	काष्ठा list_head	maydays;	/* MD: pwqs requesting rescue */
	काष्ठा worker		*rescuer;	/* MD: rescue worker */

	पूर्णांक			nr_drainers;	/* WQ: drain in progress */
	पूर्णांक			saved_max_active; /* WQ: saved pwq max_active */

	काष्ठा workqueue_attrs	*unbound_attrs;	/* PW: only क्रम unbound wqs */
	काष्ठा pool_workqueue	*dfl_pwq;	/* PW: only क्रम unbound wqs */

#अगर_घोषित CONFIG_SYSFS
	काष्ठा wq_device	*wq_dev;	/* I: क्रम sysfs पूर्णांकerface */
#पूर्ण_अगर
#अगर_घोषित CONFIG_LOCKDEP
	अक्षर			*lock_name;
	काष्ठा lock_class_key	key;
	काष्ठा lockdep_map	lockdep_map;
#पूर्ण_अगर
	अक्षर			name[WQ_NAME_LEN]; /* I: workqueue name */

	/*
	 * Deकाष्ठाion of workqueue_काष्ठा is RCU रक्षित to allow walking
	 * the workqueues list without grabbing wq_pool_mutex.
	 * This is used to dump all workqueues from sysrq.
	 */
	काष्ठा rcu_head		rcu;

	/* hot fields used during command issue, aligned to cacheline */
	अचिन्हित पूर्णांक		flags ____cacheline_aligned; /* WQ: WQ_* flags */
	काष्ठा pool_workqueue __percpu *cpu_pwqs; /* I: per-cpu pwqs */
	काष्ठा pool_workqueue __rcu *numa_pwq_tbl[]; /* PWR: unbound pwqs indexed by node */
पूर्ण;

अटल काष्ठा kmem_cache *pwq_cache;

अटल cpumask_var_t *wq_numa_possible_cpumask;
					/* possible CPUs of each node */

अटल bool wq_disable_numa;
module_param_named(disable_numa, wq_disable_numa, bool, 0444);

/* see the comment above the definition of WQ_POWER_EFFICIENT */
अटल bool wq_घातer_efficient = IS_ENABLED(CONFIG_WQ_POWER_EFFICIENT_DEFAULT);
module_param_named(घातer_efficient, wq_घातer_efficient, bool, 0444);

अटल bool wq_online;			/* can kworkers be created yet? */

अटल bool wq_numa_enabled;		/* unbound NUMA affinity enabled */

/* buf क्रम wq_update_unbound_numa_attrs(), रक्षित by CPU hotplug exclusion */
अटल काष्ठा workqueue_attrs *wq_update_unbound_numa_attrs_buf;

अटल DEFINE_MUTEX(wq_pool_mutex);	/* protects pools and workqueues list */
अटल DEFINE_MUTEX(wq_pool_attach_mutex); /* protects worker attach/detach */
अटल DEFINE_RAW_SPINLOCK(wq_mayday_lock);	/* protects wq->maydays list */
/* रुको क्रम manager to go away */
अटल काष्ठा rcuरुको manager_रुको = __RCUWAIT_INITIALIZER(manager_रुको);

अटल LIST_HEAD(workqueues);		/* PR: list of all workqueues */
अटल bool workqueue_मुक्तzing;		/* PL: have wqs started मुक्तzing? */

/* PL: allowable cpus क्रम unbound wqs and work items */
अटल cpumask_var_t wq_unbound_cpumask;

/* CPU where unbound work was last round robin scheduled from this CPU */
अटल DEFINE_PER_CPU(पूर्णांक, wq_rr_cpu_last);

/*
 * Local execution of unbound work items is no दीर्घer guaranteed.  The
 * following always क्रमces round-robin CPU selection on unbound work items
 * to uncover usages which depend on it.
 */
#अगर_घोषित CONFIG_DEBUG_WQ_FORCE_RR_CPU
अटल bool wq_debug_क्रमce_rr_cpu = true;
#अन्यथा
अटल bool wq_debug_क्रमce_rr_cpu = false;
#पूर्ण_अगर
module_param_named(debug_क्रमce_rr_cpu, wq_debug_क्रमce_rr_cpu, bool, 0644);

/* the per-cpu worker pools */
अटल DEFINE_PER_CPU_SHARED_ALIGNED(काष्ठा worker_pool [NR_STD_WORKER_POOLS], cpu_worker_pools);

अटल DEFINE_IDR(worker_pool_idr);	/* PR: idr of all pools */

/* PL: hash of all unbound pools keyed by pool->attrs */
अटल DEFINE_HASHTABLE(unbound_pool_hash, UNBOUND_POOL_HASH_ORDER);

/* I: attributes used when instantiating standard unbound pools on demand */
अटल काष्ठा workqueue_attrs *unbound_std_wq_attrs[NR_STD_WORKER_POOLS];

/* I: attributes used when instantiating ordered pools on demand */
अटल काष्ठा workqueue_attrs *ordered_wq_attrs[NR_STD_WORKER_POOLS];

काष्ठा workqueue_काष्ठा *प्रणाली_wq __पढ़ो_mostly;
EXPORT_SYMBOL(प्रणाली_wq);
काष्ठा workqueue_काष्ठा *प्रणाली_highpri_wq __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(प्रणाली_highpri_wq);
काष्ठा workqueue_काष्ठा *प्रणाली_दीर्घ_wq __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(प्रणाली_दीर्घ_wq);
काष्ठा workqueue_काष्ठा *प्रणाली_unbound_wq __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(प्रणाली_unbound_wq);
काष्ठा workqueue_काष्ठा *प्रणाली_मुक्तzable_wq __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(प्रणाली_मुक्तzable_wq);
काष्ठा workqueue_काष्ठा *प्रणाली_घातer_efficient_wq __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(प्रणाली_घातer_efficient_wq);
काष्ठा workqueue_काष्ठा *प्रणाली_मुक्तzable_घातer_efficient_wq __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(प्रणाली_मुक्तzable_घातer_efficient_wq);

अटल पूर्णांक worker_thपढ़ो(व्योम *__worker);
अटल व्योम workqueue_sysfs_unरेजिस्टर(काष्ठा workqueue_काष्ठा *wq);
अटल व्योम show_pwq(काष्ठा pool_workqueue *pwq);

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/workqueue.h>

#घोषणा निश्चित_rcu_or_pool_mutex()					\
	RCU_LOCKDEP_WARN(!rcu_पढ़ो_lock_held() &&			\
			 !lockdep_is_held(&wq_pool_mutex),		\
			 "RCU or wq_pool_mutex should be held")

#घोषणा निश्चित_rcu_or_wq_mutex_or_pool_mutex(wq)			\
	RCU_LOCKDEP_WARN(!rcu_पढ़ो_lock_held() &&			\
			 !lockdep_is_held(&wq->mutex) &&		\
			 !lockdep_is_held(&wq_pool_mutex),		\
			 "RCU, wq->mutex or wq_pool_mutex should be held")

#घोषणा क्रम_each_cpu_worker_pool(pool, cpu)				\
	क्रम ((pool) = &per_cpu(cpu_worker_pools, cpu)[0];		\
	     (pool) < &per_cpu(cpu_worker_pools, cpu)[NR_STD_WORKER_POOLS]; \
	     (pool)++)

/**
 * क्रम_each_pool - iterate through all worker_pools in the प्रणाली
 * @pool: iteration cursor
 * @pi: पूर्णांकeger used क्रम iteration
 *
 * This must be called either with wq_pool_mutex held or RCU पढ़ो
 * locked.  If the pool needs to be used beyond the locking in effect, the
 * caller is responsible क्रम guaranteeing that the pool stays online.
 *
 * The अगर/अन्यथा clause exists only क्रम the lockdep निश्चितion and can be
 * ignored.
 */
#घोषणा क्रम_each_pool(pool, pi)						\
	idr_क्रम_each_entry(&worker_pool_idr, pool, pi)			\
		अगर ((अणु निश्चित_rcu_or_pool_mutex(); false; पूर्ण)) अणु पूर्ण	\
		अन्यथा

/**
 * क्रम_each_pool_worker - iterate through all workers of a worker_pool
 * @worker: iteration cursor
 * @pool: worker_pool to iterate workers of
 *
 * This must be called with wq_pool_attach_mutex.
 *
 * The अगर/अन्यथा clause exists only क्रम the lockdep निश्चितion and can be
 * ignored.
 */
#घोषणा क्रम_each_pool_worker(worker, pool)				\
	list_क्रम_each_entry((worker), &(pool)->workers, node)		\
		अगर ((अणु lockdep_निश्चित_held(&wq_pool_attach_mutex); false; पूर्ण)) अणु पूर्ण \
		अन्यथा

/**
 * क्रम_each_pwq - iterate through all pool_workqueues of the specअगरied workqueue
 * @pwq: iteration cursor
 * @wq: the target workqueue
 *
 * This must be called either with wq->mutex held or RCU पढ़ो locked.
 * If the pwq needs to be used beyond the locking in effect, the caller is
 * responsible क्रम guaranteeing that the pwq stays online.
 *
 * The अगर/अन्यथा clause exists only क्रम the lockdep निश्चितion and can be
 * ignored.
 */
#घोषणा क्रम_each_pwq(pwq, wq)						\
	list_क्रम_each_entry_rcu((pwq), &(wq)->pwqs, pwqs_node,		\
				 lockdep_is_held(&(wq->mutex)))

#अगर_घोषित CONFIG_DEBUG_OBJECTS_WORK

अटल स्थिर काष्ठा debug_obj_descr work_debug_descr;

अटल व्योम *work_debug_hपूर्णांक(व्योम *addr)
अणु
	वापस ((काष्ठा work_काष्ठा *) addr)->func;
पूर्ण

अटल bool work_is_अटल_object(व्योम *addr)
अणु
	काष्ठा work_काष्ठा *work = addr;

	वापस test_bit(WORK_STRUCT_STATIC_BIT, work_data_bits(work));
पूर्ण

/*
 * fixup_init is called when:
 * - an active object is initialized
 */
अटल bool work_fixup_init(व्योम *addr, क्रमागत debug_obj_state state)
अणु
	काष्ठा work_काष्ठा *work = addr;

	चयन (state) अणु
	हाल ODEBUG_STATE_ACTIVE:
		cancel_work_sync(work);
		debug_object_init(work, &work_debug_descr);
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * fixup_मुक्त is called when:
 * - an active object is मुक्तd
 */
अटल bool work_fixup_मुक्त(व्योम *addr, क्रमागत debug_obj_state state)
अणु
	काष्ठा work_काष्ठा *work = addr;

	चयन (state) अणु
	हाल ODEBUG_STATE_ACTIVE:
		cancel_work_sync(work);
		debug_object_मुक्त(work, &work_debug_descr);
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा debug_obj_descr work_debug_descr = अणु
	.name		= "work_struct",
	.debug_hपूर्णांक	= work_debug_hपूर्णांक,
	.is_अटल_object = work_is_अटल_object,
	.fixup_init	= work_fixup_init,
	.fixup_मुक्त	= work_fixup_मुक्त,
पूर्ण;

अटल अंतरभूत व्योम debug_work_activate(काष्ठा work_काष्ठा *work)
अणु
	debug_object_activate(work, &work_debug_descr);
पूर्ण

अटल अंतरभूत व्योम debug_work_deactivate(काष्ठा work_काष्ठा *work)
अणु
	debug_object_deactivate(work, &work_debug_descr);
पूर्ण

व्योम __init_work(काष्ठा work_काष्ठा *work, पूर्णांक onstack)
अणु
	अगर (onstack)
		debug_object_init_on_stack(work, &work_debug_descr);
	अन्यथा
		debug_object_init(work, &work_debug_descr);
पूर्ण
EXPORT_SYMBOL_GPL(__init_work);

व्योम destroy_work_on_stack(काष्ठा work_काष्ठा *work)
अणु
	debug_object_मुक्त(work, &work_debug_descr);
पूर्ण
EXPORT_SYMBOL_GPL(destroy_work_on_stack);

व्योम destroy_delayed_work_on_stack(काष्ठा delayed_work *work)
अणु
	destroy_समयr_on_stack(&work->समयr);
	debug_object_मुक्त(&work->work, &work_debug_descr);
पूर्ण
EXPORT_SYMBOL_GPL(destroy_delayed_work_on_stack);

#अन्यथा
अटल अंतरभूत व्योम debug_work_activate(काष्ठा work_काष्ठा *work) अणु पूर्ण
अटल अंतरभूत व्योम debug_work_deactivate(काष्ठा work_काष्ठा *work) अणु पूर्ण
#पूर्ण_अगर

/**
 * worker_pool_assign_id - allocate ID and assing it to @pool
 * @pool: the pool poपूर्णांकer of पूर्णांकerest
 *
 * Returns 0 अगर ID in [0, WORK_OFFQ_POOL_NONE) is allocated and asचिन्हित
 * successfully, -त्रुटि_सं on failure.
 */
अटल पूर्णांक worker_pool_assign_id(काष्ठा worker_pool *pool)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&wq_pool_mutex);

	ret = idr_alloc(&worker_pool_idr, pool, 0, WORK_OFFQ_POOL_NONE,
			GFP_KERNEL);
	अगर (ret >= 0) अणु
		pool->id = ret;
		वापस 0;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * unbound_pwq_by_node - वापस the unbound pool_workqueue क्रम the given node
 * @wq: the target workqueue
 * @node: the node ID
 *
 * This must be called with any of wq_pool_mutex, wq->mutex or RCU
 * पढ़ो locked.
 * If the pwq needs to be used beyond the locking in effect, the caller is
 * responsible क्रम guaranteeing that the pwq stays online.
 *
 * Return: The unbound pool_workqueue क्रम @node.
 */
अटल काष्ठा pool_workqueue *unbound_pwq_by_node(काष्ठा workqueue_काष्ठा *wq,
						  पूर्णांक node)
अणु
	निश्चित_rcu_or_wq_mutex_or_pool_mutex(wq);

	/*
	 * XXX: @node can be NUMA_NO_NODE अगर CPU goes offline जबतक a
	 * delayed item is pending.  The plan is to keep CPU -> NODE
	 * mapping valid and stable across CPU on/offlines.  Once that
	 * happens, this workaround can be हटाओd.
	 */
	अगर (unlikely(node == NUMA_NO_NODE))
		वापस wq->dfl_pwq;

	वापस rcu_dereference_raw(wq->numa_pwq_tbl[node]);
पूर्ण

अटल अचिन्हित पूर्णांक work_color_to_flags(पूर्णांक color)
अणु
	वापस color << WORK_STRUCT_COLOR_SHIFT;
पूर्ण

अटल पूर्णांक get_work_color(काष्ठा work_काष्ठा *work)
अणु
	वापस (*work_data_bits(work) >> WORK_STRUCT_COLOR_SHIFT) &
		((1 << WORK_STRUCT_COLOR_BITS) - 1);
पूर्ण

अटल पूर्णांक work_next_color(पूर्णांक color)
अणु
	वापस (color + 1) % WORK_NR_COLORS;
पूर्ण

/*
 * While queued, %WORK_STRUCT_PWQ is set and non flag bits of a work's data
 * contain the poपूर्णांकer to the queued pwq.  Once execution starts, the flag
 * is cleared and the high bits contain OFFQ flags and pool ID.
 *
 * set_work_pwq(), set_work_pool_and_clear_pending(), mark_work_canceling()
 * and clear_work_data() can be used to set the pwq, pool or clear
 * work->data.  These functions should only be called जबतक the work is
 * owned - ie. जबतक the PENDING bit is set.
 *
 * get_work_pool() and get_work_pwq() can be used to obtain the pool or pwq
 * corresponding to a work.  Pool is available once the work has been
 * queued anywhere after initialization until it is sync canceled.  pwq is
 * available only जबतक the work item is queued.
 *
 * %WORK_OFFQ_CANCELING is used to mark a work item which is being
 * canceled.  While being canceled, a work item may have its PENDING set
 * but stay off समयr and worklist क्रम arbitrarily दीर्घ and nobody should
 * try to steal the PENDING bit.
 */
अटल अंतरभूत व्योम set_work_data(काष्ठा work_काष्ठा *work, अचिन्हित दीर्घ data,
				 अचिन्हित दीर्घ flags)
अणु
	WARN_ON_ONCE(!work_pending(work));
	atomic_दीर्घ_set(&work->data, data | flags | work_अटल(work));
पूर्ण

अटल व्योम set_work_pwq(काष्ठा work_काष्ठा *work, काष्ठा pool_workqueue *pwq,
			 अचिन्हित दीर्घ extra_flags)
अणु
	set_work_data(work, (अचिन्हित दीर्घ)pwq,
		      WORK_STRUCT_PENDING | WORK_STRUCT_PWQ | extra_flags);
पूर्ण

अटल व्योम set_work_pool_and_keep_pending(काष्ठा work_काष्ठा *work,
					   पूर्णांक pool_id)
अणु
	set_work_data(work, (अचिन्हित दीर्घ)pool_id << WORK_OFFQ_POOL_SHIFT,
		      WORK_STRUCT_PENDING);
पूर्ण

अटल व्योम set_work_pool_and_clear_pending(काष्ठा work_काष्ठा *work,
					    पूर्णांक pool_id)
अणु
	/*
	 * The following wmb is paired with the implied mb in
	 * test_and_set_bit(PENDING) and ensures all updates to @work made
	 * here are visible to and precede any updates by the next PENDING
	 * owner.
	 */
	smp_wmb();
	set_work_data(work, (अचिन्हित दीर्घ)pool_id << WORK_OFFQ_POOL_SHIFT, 0);
	/*
	 * The following mb guarantees that previous clear of a PENDING bit
	 * will not be reordered with any speculative LOADS or STORES from
	 * work->current_func, which is executed afterwards.  This possible
	 * reordering can lead to a missed execution on attempt to queue
	 * the same @work.  E.g. consider this हाल:
	 *
	 *   CPU#0                         CPU#1
	 *   ----------------------------  --------------------------------
	 *
	 * 1  STORE event_indicated
	 * 2  queue_work_on() अणु
	 * 3    test_and_set_bit(PENDING)
	 * 4 पूर्ण                             set_..._and_clear_pending() अणु
	 * 5                                 set_work_data() # clear bit
	 * 6                                 smp_mb()
	 * 7                               work->current_func() अणु
	 * 8				      LOAD event_indicated
	 *				   पूर्ण
	 *
	 * Without an explicit full barrier speculative LOAD on line 8 can
	 * be executed beक्रमe CPU#0 करोes STORE on line 1.  If that happens,
	 * CPU#0 observes the PENDING bit is still set and new execution of
	 * a @work is not queued in a hope, that CPU#1 will eventually
	 * finish the queued @work.  Meanजबतक CPU#1 करोes not see
	 * event_indicated is set, because speculative LOAD was executed
	 * beक्रमe actual STORE.
	 */
	smp_mb();
पूर्ण

अटल व्योम clear_work_data(काष्ठा work_काष्ठा *work)
अणु
	smp_wmb();	/* see set_work_pool_and_clear_pending() */
	set_work_data(work, WORK_STRUCT_NO_POOL, 0);
पूर्ण

अटल काष्ठा pool_workqueue *get_work_pwq(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ data = atomic_दीर्घ_पढ़ो(&work->data);

	अगर (data & WORK_STRUCT_PWQ)
		वापस (व्योम *)(data & WORK_STRUCT_WQ_DATA_MASK);
	अन्यथा
		वापस शून्य;
पूर्ण

/**
 * get_work_pool - वापस the worker_pool a given work was associated with
 * @work: the work item of पूर्णांकerest
 *
 * Pools are created and destroyed under wq_pool_mutex, and allows पढ़ो
 * access under RCU पढ़ो lock.  As such, this function should be
 * called under wq_pool_mutex or inside of a rcu_पढ़ो_lock() region.
 *
 * All fields of the वापसed pool are accessible as दीर्घ as the above
 * mentioned locking is in effect.  If the वापसed pool needs to be used
 * beyond the critical section, the caller is responsible क्रम ensuring the
 * वापसed pool is and stays online.
 *
 * Return: The worker_pool @work was last associated with.  %शून्य अगर none.
 */
अटल काष्ठा worker_pool *get_work_pool(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ data = atomic_दीर्घ_पढ़ो(&work->data);
	पूर्णांक pool_id;

	निश्चित_rcu_or_pool_mutex();

	अगर (data & WORK_STRUCT_PWQ)
		वापस ((काष्ठा pool_workqueue *)
			(data & WORK_STRUCT_WQ_DATA_MASK))->pool;

	pool_id = data >> WORK_OFFQ_POOL_SHIFT;
	अगर (pool_id == WORK_OFFQ_POOL_NONE)
		वापस शून्य;

	वापस idr_find(&worker_pool_idr, pool_id);
पूर्ण

/**
 * get_work_pool_id - वापस the worker pool ID a given work is associated with
 * @work: the work item of पूर्णांकerest
 *
 * Return: The worker_pool ID @work was last associated with.
 * %WORK_OFFQ_POOL_NONE अगर none.
 */
अटल पूर्णांक get_work_pool_id(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ data = atomic_दीर्घ_पढ़ो(&work->data);

	अगर (data & WORK_STRUCT_PWQ)
		वापस ((काष्ठा pool_workqueue *)
			(data & WORK_STRUCT_WQ_DATA_MASK))->pool->id;

	वापस data >> WORK_OFFQ_POOL_SHIFT;
पूर्ण

अटल व्योम mark_work_canceling(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ pool_id = get_work_pool_id(work);

	pool_id <<= WORK_OFFQ_POOL_SHIFT;
	set_work_data(work, pool_id | WORK_OFFQ_CANCELING, WORK_STRUCT_PENDING);
पूर्ण

अटल bool work_is_canceling(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ data = atomic_दीर्घ_पढ़ो(&work->data);

	वापस !(data & WORK_STRUCT_PWQ) && (data & WORK_OFFQ_CANCELING);
पूर्ण

/*
 * Policy functions.  These define the policies on how the global worker
 * pools are managed.  Unless noted otherwise, these functions assume that
 * they're being called with pool->lock held.
 */

अटल bool __need_more_worker(काष्ठा worker_pool *pool)
अणु
	वापस !atomic_पढ़ो(&pool->nr_running);
पूर्ण

/*
 * Need to wake up a worker?  Called from anything but currently
 * running workers.
 *
 * Note that, because unbound workers never contribute to nr_running, this
 * function will always वापस %true क्रम unbound pools as दीर्घ as the
 * worklist isn't empty.
 */
अटल bool need_more_worker(काष्ठा worker_pool *pool)
अणु
	वापस !list_empty(&pool->worklist) && __need_more_worker(pool);
पूर्ण

/* Can I start working?  Called from busy but !running workers. */
अटल bool may_start_working(काष्ठा worker_pool *pool)
अणु
	वापस pool->nr_idle;
पूर्ण

/* Do I need to keep working?  Called from currently running workers. */
अटल bool keep_working(काष्ठा worker_pool *pool)
अणु
	वापस !list_empty(&pool->worklist) &&
		atomic_पढ़ो(&pool->nr_running) <= 1;
पूर्ण

/* Do we need a new worker?  Called from manager. */
अटल bool need_to_create_worker(काष्ठा worker_pool *pool)
अणु
	वापस need_more_worker(pool) && !may_start_working(pool);
पूर्ण

/* Do we have too many workers and should some go away? */
अटल bool too_many_workers(काष्ठा worker_pool *pool)
अणु
	bool managing = pool->flags & POOL_MANAGER_ACTIVE;
	पूर्णांक nr_idle = pool->nr_idle + managing; /* manager is considered idle */
	पूर्णांक nr_busy = pool->nr_workers - nr_idle;

	वापस nr_idle > 2 && (nr_idle - 2) * MAX_IDLE_WORKERS_RATIO >= nr_busy;
पूर्ण

/*
 * Wake up functions.
 */

/* Return the first idle worker.  Safe with preemption disabled */
अटल काष्ठा worker *first_idle_worker(काष्ठा worker_pool *pool)
अणु
	अगर (unlikely(list_empty(&pool->idle_list)))
		वापस शून्य;

	वापस list_first_entry(&pool->idle_list, काष्ठा worker, entry);
पूर्ण

/**
 * wake_up_worker - wake up an idle worker
 * @pool: worker pool to wake worker from
 *
 * Wake up the first idle worker of @pool.
 *
 * CONTEXT:
 * raw_spin_lock_irq(pool->lock).
 */
अटल व्योम wake_up_worker(काष्ठा worker_pool *pool)
अणु
	काष्ठा worker *worker = first_idle_worker(pool);

	अगर (likely(worker))
		wake_up_process(worker->task);
पूर्ण

/**
 * wq_worker_running - a worker is running again
 * @task: task waking up
 *
 * This function is called when a worker वापसs from schedule()
 */
व्योम wq_worker_running(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा worker *worker = kthपढ़ो_data(task);

	अगर (!worker->sleeping)
		वापस;
	अगर (!(worker->flags & WORKER_NOT_RUNNING))
		atomic_inc(&worker->pool->nr_running);
	worker->sleeping = 0;
पूर्ण

/**
 * wq_worker_sleeping - a worker is going to sleep
 * @task: task going to sleep
 *
 * This function is called from schedule() when a busy worker is
 * going to sleep. Preemption needs to be disabled to protect ->sleeping
 * assignment.
 */
व्योम wq_worker_sleeping(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा worker *next, *worker = kthपढ़ो_data(task);
	काष्ठा worker_pool *pool;

	/*
	 * Rescuers, which may not have all the fields set up like normal
	 * workers, also reach here, let's not access anything beक्रमe
	 * checking NOT_RUNNING.
	 */
	अगर (worker->flags & WORKER_NOT_RUNNING)
		वापस;

	pool = worker->pool;

	/* Return अगर preempted beक्रमe wq_worker_running() was reached */
	अगर (worker->sleeping)
		वापस;

	worker->sleeping = 1;
	raw_spin_lock_irq(&pool->lock);

	/*
	 * The counterpart of the following dec_and_test, implied mb,
	 * worklist not empty test sequence is in insert_work().
	 * Please पढ़ो comment there.
	 *
	 * NOT_RUNNING is clear.  This means that we're bound to and
	 * running on the local cpu w/ rq lock held and preemption
	 * disabled, which in turn means that none अन्यथा could be
	 * manipulating idle_list, so dereferencing idle_list without pool
	 * lock is safe.
	 */
	अगर (atomic_dec_and_test(&pool->nr_running) &&
	    !list_empty(&pool->worklist)) अणु
		next = first_idle_worker(pool);
		अगर (next)
			wake_up_process(next->task);
	पूर्ण
	raw_spin_unlock_irq(&pool->lock);
पूर्ण

/**
 * wq_worker_last_func - retrieve worker's last work function
 * @task: Task to retrieve last work function of.
 *
 * Determine the last function a worker executed. This is called from
 * the scheduler to get a worker's last known identity.
 *
 * CONTEXT:
 * raw_spin_lock_irq(rq->lock)
 *
 * This function is called during schedule() when a kworker is going
 * to sleep. It's used by psi to identअगरy aggregation workers during
 * dequeuing, to allow periodic aggregation to shut-off when that
 * worker is the last task in the प्रणाली or cgroup to go to sleep.
 *
 * As this function करोesn't involve any workqueue-related locking, it
 * only वापसs stable values when called from inside the scheduler's
 * queuing and dequeuing paths, when @task, which must be a kworker,
 * is guaranteed to not be processing any works.
 *
 * Return:
 * The last work function %current executed as a worker, शून्य अगर it
 * hasn't executed any work yet.
 */
work_func_t wq_worker_last_func(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा worker *worker = kthपढ़ो_data(task);

	वापस worker->last_func;
पूर्ण

/**
 * worker_set_flags - set worker flags and adjust nr_running accordingly
 * @worker: self
 * @flags: flags to set
 *
 * Set @flags in @worker->flags and adjust nr_running accordingly.
 *
 * CONTEXT:
 * raw_spin_lock_irq(pool->lock)
 */
अटल अंतरभूत व्योम worker_set_flags(काष्ठा worker *worker, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा worker_pool *pool = worker->pool;

	WARN_ON_ONCE(worker->task != current);

	/* If transitioning पूर्णांकo NOT_RUNNING, adjust nr_running. */
	अगर ((flags & WORKER_NOT_RUNNING) &&
	    !(worker->flags & WORKER_NOT_RUNNING)) अणु
		atomic_dec(&pool->nr_running);
	पूर्ण

	worker->flags |= flags;
पूर्ण

/**
 * worker_clr_flags - clear worker flags and adjust nr_running accordingly
 * @worker: self
 * @flags: flags to clear
 *
 * Clear @flags in @worker->flags and adjust nr_running accordingly.
 *
 * CONTEXT:
 * raw_spin_lock_irq(pool->lock)
 */
अटल अंतरभूत व्योम worker_clr_flags(काष्ठा worker *worker, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा worker_pool *pool = worker->pool;
	अचिन्हित पूर्णांक oflags = worker->flags;

	WARN_ON_ONCE(worker->task != current);

	worker->flags &= ~flags;

	/*
	 * If transitioning out of NOT_RUNNING, increment nr_running.  Note
	 * that the nested NOT_RUNNING is not a noop.  NOT_RUNNING is mask
	 * of multiple flags, not a single flag.
	 */
	अगर ((flags & WORKER_NOT_RUNNING) && (oflags & WORKER_NOT_RUNNING))
		अगर (!(worker->flags & WORKER_NOT_RUNNING))
			atomic_inc(&pool->nr_running);
पूर्ण

/**
 * find_worker_executing_work - find worker which is executing a work
 * @pool: pool of पूर्णांकerest
 * @work: work to find worker क्रम
 *
 * Find a worker which is executing @work on @pool by searching
 * @pool->busy_hash which is keyed by the address of @work.  For a worker
 * to match, its current execution should match the address of @work and
 * its work function.  This is to aव्योम unwanted dependency between
 * unrelated work executions through a work item being recycled जबतक still
 * being executed.
 *
 * This is a bit tricky.  A work item may be मुक्तd once its execution
 * starts and nothing prevents the मुक्तd area from being recycled क्रम
 * another work item.  If the same work item address ends up being reused
 * beक्रमe the original execution finishes, workqueue will identअगरy the
 * recycled work item as currently executing and make it रुको until the
 * current execution finishes, पूर्णांकroducing an unwanted dependency.
 *
 * This function checks the work item address and work function to aव्योम
 * false positives.  Note that this isn't complete as one may स्थिरruct a
 * work function which can पूर्णांकroduce dependency onto itself through a
 * recycled work item.  Well, अगर somebody wants to shoot oneself in the
 * foot that badly, there's only so much we can करो, and अगर such deadlock
 * actually occurs, it should be easy to locate the culprit work function.
 *
 * CONTEXT:
 * raw_spin_lock_irq(pool->lock).
 *
 * Return:
 * Poपूर्णांकer to worker which is executing @work अगर found, %शून्य
 * otherwise.
 */
अटल काष्ठा worker *find_worker_executing_work(काष्ठा worker_pool *pool,
						 काष्ठा work_काष्ठा *work)
अणु
	काष्ठा worker *worker;

	hash_क्रम_each_possible(pool->busy_hash, worker, hentry,
			       (अचिन्हित दीर्घ)work)
		अगर (worker->current_work == work &&
		    worker->current_func == work->func)
			वापस worker;

	वापस शून्य;
पूर्ण

/**
 * move_linked_works - move linked works to a list
 * @work: start of series of works to be scheduled
 * @head: target list to append @work to
 * @nextp: out parameter क्रम nested worklist walking
 *
 * Schedule linked works starting from @work to @head.  Work series to
 * be scheduled starts at @work and includes any consecutive work with
 * WORK_STRUCT_LINKED set in its predecessor.
 *
 * If @nextp is not शून्य, it's updated to poपूर्णांक to the next work of
 * the last scheduled work.  This allows move_linked_works() to be
 * nested inside outer list_क्रम_each_entry_safe().
 *
 * CONTEXT:
 * raw_spin_lock_irq(pool->lock).
 */
अटल व्योम move_linked_works(काष्ठा work_काष्ठा *work, काष्ठा list_head *head,
			      काष्ठा work_काष्ठा **nextp)
अणु
	काष्ठा work_काष्ठा *n;

	/*
	 * Linked worklist will always end beक्रमe the end of the list,
	 * use शून्य क्रम list head.
	 */
	list_क्रम_each_entry_safe_from(work, n, शून्य, entry) अणु
		list_move_tail(&work->entry, head);
		अगर (!(*work_data_bits(work) & WORK_STRUCT_LINKED))
			अवरोध;
	पूर्ण

	/*
	 * If we're alपढ़ोy inside safe list traversal and have moved
	 * multiple works to the scheduled queue, the next position
	 * needs to be updated.
	 */
	अगर (nextp)
		*nextp = n;
पूर्ण

/**
 * get_pwq - get an extra reference on the specअगरied pool_workqueue
 * @pwq: pool_workqueue to get
 *
 * Obtain an extra reference on @pwq.  The caller should guarantee that
 * @pwq has positive refcnt and be holding the matching pool->lock.
 */
अटल व्योम get_pwq(काष्ठा pool_workqueue *pwq)
अणु
	lockdep_निश्चित_held(&pwq->pool->lock);
	WARN_ON_ONCE(pwq->refcnt <= 0);
	pwq->refcnt++;
पूर्ण

/**
 * put_pwq - put a pool_workqueue reference
 * @pwq: pool_workqueue to put
 *
 * Drop a reference of @pwq.  If its refcnt reaches zero, schedule its
 * deकाष्ठाion.  The caller should be holding the matching pool->lock.
 */
अटल व्योम put_pwq(काष्ठा pool_workqueue *pwq)
अणु
	lockdep_निश्चित_held(&pwq->pool->lock);
	अगर (likely(--pwq->refcnt))
		वापस;
	अगर (WARN_ON_ONCE(!(pwq->wq->flags & WQ_UNBOUND)))
		वापस;
	/*
	 * @pwq can't be released under pool->lock, bounce to
	 * pwq_unbound_release_workfn().  This never recurses on the same
	 * pool->lock as this path is taken only क्रम unbound workqueues and
	 * the release work item is scheduled on a per-cpu workqueue.  To
	 * aव्योम lockdep warning, unbound pool->locks are given lockdep
	 * subclass of 1 in get_unbound_pool().
	 */
	schedule_work(&pwq->unbound_release_work);
पूर्ण

/**
 * put_pwq_unlocked - put_pwq() with surrounding pool lock/unlock
 * @pwq: pool_workqueue to put (can be %शून्य)
 *
 * put_pwq() with locking.  This function also allows %शून्य @pwq.
 */
अटल व्योम put_pwq_unlocked(काष्ठा pool_workqueue *pwq)
अणु
	अगर (pwq) अणु
		/*
		 * As both pwqs and pools are RCU रक्षित, the
		 * following lock operations are safe.
		 */
		raw_spin_lock_irq(&pwq->pool->lock);
		put_pwq(pwq);
		raw_spin_unlock_irq(&pwq->pool->lock);
	पूर्ण
पूर्ण

अटल व्योम pwq_activate_delayed_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pool_workqueue *pwq = get_work_pwq(work);

	trace_workqueue_activate_work(work);
	अगर (list_empty(&pwq->pool->worklist))
		pwq->pool->watchकरोg_ts = jअगरfies;
	move_linked_works(work, &pwq->pool->worklist, शून्य);
	__clear_bit(WORK_STRUCT_DELAYED_BIT, work_data_bits(work));
	pwq->nr_active++;
पूर्ण

अटल व्योम pwq_activate_first_delayed(काष्ठा pool_workqueue *pwq)
अणु
	काष्ठा work_काष्ठा *work = list_first_entry(&pwq->delayed_works,
						    काष्ठा work_काष्ठा, entry);

	pwq_activate_delayed_work(work);
पूर्ण

/**
 * pwq_dec_nr_in_flight - decrement pwq's nr_in_flight
 * @pwq: pwq of पूर्णांकerest
 * @color: color of work which left the queue
 *
 * A work either has completed or is हटाओd from pending queue,
 * decrement nr_in_flight of its pwq and handle workqueue flushing.
 *
 * CONTEXT:
 * raw_spin_lock_irq(pool->lock).
 */
अटल व्योम pwq_dec_nr_in_flight(काष्ठा pool_workqueue *pwq, पूर्णांक color)
अणु
	/* uncolored work items करोn't participate in flushing or nr_active */
	अगर (color == WORK_NO_COLOR)
		जाओ out_put;

	pwq->nr_in_flight[color]--;

	pwq->nr_active--;
	अगर (!list_empty(&pwq->delayed_works)) अणु
		/* one करोwn, submit a delayed one */
		अगर (pwq->nr_active < pwq->max_active)
			pwq_activate_first_delayed(pwq);
	पूर्ण

	/* is flush in progress and are we at the flushing tip? */
	अगर (likely(pwq->flush_color != color))
		जाओ out_put;

	/* are there still in-flight works? */
	अगर (pwq->nr_in_flight[color])
		जाओ out_put;

	/* this pwq is करोne, clear flush_color */
	pwq->flush_color = -1;

	/*
	 * If this was the last pwq, wake up the first flusher.  It
	 * will handle the rest.
	 */
	अगर (atomic_dec_and_test(&pwq->wq->nr_pwqs_to_flush))
		complete(&pwq->wq->first_flusher->करोne);
out_put:
	put_pwq(pwq);
पूर्ण

/**
 * try_to_grab_pending - steal work item from worklist and disable irq
 * @work: work item to steal
 * @is_dwork: @work is a delayed_work
 * @flags: place to store irq state
 *
 * Try to grab PENDING bit of @work.  This function can handle @work in any
 * stable state - idle, on समयr or on worklist.
 *
 * Return:
 *
 *  ========	================================================================
 *  1		अगर @work was pending and we successfully stole PENDING
 *  0		अगर @work was idle and we claimed PENDING
 *  -EAGAIN	अगर PENDING couldn't be grabbed at the moment, safe to busy-retry
 *  -ENOENT	अगर someone अन्यथा is canceling @work, this state may persist
 *		क्रम arbitrarily दीर्घ
 *  ========	================================================================
 *
 * Note:
 * On >= 0 वापस, the caller owns @work's PENDING bit.  To aव्योम getting
 * पूर्णांकerrupted जबतक holding PENDING and @work off queue, irq must be
 * disabled on entry.  This, combined with delayed_work->समयr being
 * irqsafe, ensures that we वापस -EAGAIN क्रम finite लघु period of समय.
 *
 * On successful वापस, >= 0, irq is disabled and the caller is
 * responsible क्रम releasing it using local_irq_restore(*@flags).
 *
 * This function is safe to call from any context including IRQ handler.
 */
अटल पूर्णांक try_to_grab_pending(काष्ठा work_काष्ठा *work, bool is_dwork,
			       अचिन्हित दीर्घ *flags)
अणु
	काष्ठा worker_pool *pool;
	काष्ठा pool_workqueue *pwq;

	local_irq_save(*flags);

	/* try to steal the समयr अगर it exists */
	अगर (is_dwork) अणु
		काष्ठा delayed_work *dwork = to_delayed_work(work);

		/*
		 * dwork->समयr is irqsafe.  If del_समयr() fails, it's
		 * guaranteed that the समयr is not queued anywhere and not
		 * running on the local CPU.
		 */
		अगर (likely(del_समयr(&dwork->समयr)))
			वापस 1;
	पूर्ण

	/* try to claim PENDING the normal way */
	अगर (!test_and_set_bit(WORK_STRUCT_PENDING_BIT, work_data_bits(work)))
		वापस 0;

	rcu_पढ़ो_lock();
	/*
	 * The queueing is in progress, or it is alपढ़ोy queued. Try to
	 * steal it from ->worklist without clearing WORK_STRUCT_PENDING.
	 */
	pool = get_work_pool(work);
	अगर (!pool)
		जाओ fail;

	raw_spin_lock(&pool->lock);
	/*
	 * work->data is guaranteed to poपूर्णांक to pwq only जबतक the work
	 * item is queued on pwq->wq, and both updating work->data to poपूर्णांक
	 * to pwq on queueing and to pool on dequeueing are करोne under
	 * pwq->pool->lock.  This in turn guarantees that, अगर work->data
	 * poपूर्णांकs to pwq which is associated with a locked pool, the work
	 * item is currently queued on that pool.
	 */
	pwq = get_work_pwq(work);
	अगर (pwq && pwq->pool == pool) अणु
		debug_work_deactivate(work);

		/*
		 * A delayed work item cannot be grabbed directly because
		 * it might have linked NO_COLOR work items which, अगर left
		 * on the delayed_list, will confuse pwq->nr_active
		 * management later on and cause stall.  Make sure the work
		 * item is activated beक्रमe grabbing.
		 */
		अगर (*work_data_bits(work) & WORK_STRUCT_DELAYED)
			pwq_activate_delayed_work(work);

		list_del_init(&work->entry);
		pwq_dec_nr_in_flight(pwq, get_work_color(work));

		/* work->data poपूर्णांकs to pwq अगरf queued, poपूर्णांक to pool */
		set_work_pool_and_keep_pending(work, pool->id);

		raw_spin_unlock(&pool->lock);
		rcu_पढ़ो_unlock();
		वापस 1;
	पूर्ण
	raw_spin_unlock(&pool->lock);
fail:
	rcu_पढ़ो_unlock();
	local_irq_restore(*flags);
	अगर (work_is_canceling(work))
		वापस -ENOENT;
	cpu_relax();
	वापस -EAGAIN;
पूर्ण

/**
 * insert_work - insert a work पूर्णांकo a pool
 * @pwq: pwq @work beदीर्घs to
 * @work: work to insert
 * @head: insertion poपूर्णांक
 * @extra_flags: extra WORK_STRUCT_* flags to set
 *
 * Insert @work which beदीर्घs to @pwq after @head.  @extra_flags is or'd to
 * work_काष्ठा flags.
 *
 * CONTEXT:
 * raw_spin_lock_irq(pool->lock).
 */
अटल व्योम insert_work(काष्ठा pool_workqueue *pwq, काष्ठा work_काष्ठा *work,
			काष्ठा list_head *head, अचिन्हित पूर्णांक extra_flags)
अणु
	काष्ठा worker_pool *pool = pwq->pool;

	/* record the work call stack in order to prपूर्णांक it in KASAN reports */
	kasan_record_aux_stack(work);

	/* we own @work, set data and link */
	set_work_pwq(work, pwq, extra_flags);
	list_add_tail(&work->entry, head);
	get_pwq(pwq);

	/*
	 * Ensure either wq_worker_sleeping() sees the above
	 * list_add_tail() or we see zero nr_running to aव्योम workers lying
	 * around lazily जबतक there are works to be processed.
	 */
	smp_mb();

	अगर (__need_more_worker(pool))
		wake_up_worker(pool);
पूर्ण

/*
 * Test whether @work is being queued from another work executing on the
 * same workqueue.
 */
अटल bool is_chained_work(काष्ठा workqueue_काष्ठा *wq)
अणु
	काष्ठा worker *worker;

	worker = current_wq_worker();
	/*
	 * Return %true अगरf I'm a worker executing a work item on @wq.  If
	 * I'm @worker, it's safe to dereference it without locking.
	 */
	वापस worker && worker->current_pwq->wq == wq;
पूर्ण

/*
 * When queueing an unbound work item to a wq, prefer local CPU अगर allowed
 * by wq_unbound_cpumask.  Otherwise, round robin among the allowed ones to
 * aव्योम perturbing sensitive tasks.
 */
अटल पूर्णांक wq_select_unbound_cpu(पूर्णांक cpu)
अणु
	अटल bool prपूर्णांकed_dbg_warning;
	पूर्णांक new_cpu;

	अगर (likely(!wq_debug_क्रमce_rr_cpu)) अणु
		अगर (cpumask_test_cpu(cpu, wq_unbound_cpumask))
			वापस cpu;
	पूर्ण अन्यथा अगर (!prपूर्णांकed_dbg_warning) अणु
		pr_warn("workqueue: round-robin CPU selection forced, expect performance impact\n");
		prपूर्णांकed_dbg_warning = true;
	पूर्ण

	अगर (cpumask_empty(wq_unbound_cpumask))
		वापस cpu;

	new_cpu = __this_cpu_पढ़ो(wq_rr_cpu_last);
	new_cpu = cpumask_next_and(new_cpu, wq_unbound_cpumask, cpu_online_mask);
	अगर (unlikely(new_cpu >= nr_cpu_ids)) अणु
		new_cpu = cpumask_first_and(wq_unbound_cpumask, cpu_online_mask);
		अगर (unlikely(new_cpu >= nr_cpu_ids))
			वापस cpu;
	पूर्ण
	__this_cpu_ग_लिखो(wq_rr_cpu_last, new_cpu);

	वापस new_cpu;
पूर्ण

अटल व्योम __queue_work(पूर्णांक cpu, काष्ठा workqueue_काष्ठा *wq,
			 काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pool_workqueue *pwq;
	काष्ठा worker_pool *last_pool;
	काष्ठा list_head *worklist;
	अचिन्हित पूर्णांक work_flags;
	अचिन्हित पूर्णांक req_cpu = cpu;

	/*
	 * While a work item is PENDING && off queue, a task trying to
	 * steal the PENDING will busy-loop रुकोing क्रम it to either get
	 * queued or lose PENDING.  Grabbing PENDING and queueing should
	 * happen with IRQ disabled.
	 */
	lockdep_निश्चित_irqs_disabled();


	/* अगर draining, only works from the same workqueue are allowed */
	अगर (unlikely(wq->flags & __WQ_DRAINING) &&
	    WARN_ON_ONCE(!is_chained_work(wq)))
		वापस;
	rcu_पढ़ो_lock();
retry:
	/* pwq which will be used unless @work is executing अन्यथाwhere */
	अगर (wq->flags & WQ_UNBOUND) अणु
		अगर (req_cpu == WORK_CPU_UNBOUND)
			cpu = wq_select_unbound_cpu(raw_smp_processor_id());
		pwq = unbound_pwq_by_node(wq, cpu_to_node(cpu));
	पूर्ण अन्यथा अणु
		अगर (req_cpu == WORK_CPU_UNBOUND)
			cpu = raw_smp_processor_id();
		pwq = per_cpu_ptr(wq->cpu_pwqs, cpu);
	पूर्ण

	/*
	 * If @work was previously on a dअगरferent pool, it might still be
	 * running there, in which हाल the work needs to be queued on that
	 * pool to guarantee non-reentrancy.
	 */
	last_pool = get_work_pool(work);
	अगर (last_pool && last_pool != pwq->pool) अणु
		काष्ठा worker *worker;

		raw_spin_lock(&last_pool->lock);

		worker = find_worker_executing_work(last_pool, work);

		अगर (worker && worker->current_pwq->wq == wq) अणु
			pwq = worker->current_pwq;
		पूर्ण अन्यथा अणु
			/* meh... not running there, queue here */
			raw_spin_unlock(&last_pool->lock);
			raw_spin_lock(&pwq->pool->lock);
		पूर्ण
	पूर्ण अन्यथा अणु
		raw_spin_lock(&pwq->pool->lock);
	पूर्ण

	/*
	 * pwq is determined and locked.  For unbound pools, we could have
	 * raced with pwq release and it could alपढ़ोy be dead.  If its
	 * refcnt is zero, repeat pwq selection.  Note that pwqs never die
	 * without another pwq replacing it in the numa_pwq_tbl or जबतक
	 * work items are executing on it, so the retrying is guaranteed to
	 * make क्रमward-progress.
	 */
	अगर (unlikely(!pwq->refcnt)) अणु
		अगर (wq->flags & WQ_UNBOUND) अणु
			raw_spin_unlock(&pwq->pool->lock);
			cpu_relax();
			जाओ retry;
		पूर्ण
		/* oops */
		WARN_ONCE(true, "workqueue: per-cpu pwq for %s on cpu%d has 0 refcnt",
			  wq->name, cpu);
	पूर्ण

	/* pwq determined, queue */
	trace_workqueue_queue_work(req_cpu, pwq, work);

	अगर (WARN_ON(!list_empty(&work->entry)))
		जाओ out;

	pwq->nr_in_flight[pwq->work_color]++;
	work_flags = work_color_to_flags(pwq->work_color);

	अगर (likely(pwq->nr_active < pwq->max_active)) अणु
		trace_workqueue_activate_work(work);
		pwq->nr_active++;
		worklist = &pwq->pool->worklist;
		अगर (list_empty(worklist))
			pwq->pool->watchकरोg_ts = jअगरfies;
	पूर्ण अन्यथा अणु
		work_flags |= WORK_STRUCT_DELAYED;
		worklist = &pwq->delayed_works;
	पूर्ण

	debug_work_activate(work);
	insert_work(pwq, work, worklist, work_flags);

out:
	raw_spin_unlock(&pwq->pool->lock);
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * queue_work_on - queue work on specअगरic cpu
 * @cpu: CPU number to execute work on
 * @wq: workqueue to use
 * @work: work to queue
 *
 * We queue the work to a specअगरic CPU, the caller must ensure it
 * can't go away.
 *
 * Return: %false अगर @work was alपढ़ोy on a queue, %true otherwise.
 */
bool queue_work_on(पूर्णांक cpu, काष्ठा workqueue_काष्ठा *wq,
		   काष्ठा work_काष्ठा *work)
अणु
	bool ret = false;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	अगर (!test_and_set_bit(WORK_STRUCT_PENDING_BIT, work_data_bits(work))) अणु
		__queue_work(cpu, wq, work);
		ret = true;
	पूर्ण

	local_irq_restore(flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(queue_work_on);

/**
 * workqueue_select_cpu_near - Select a CPU based on NUMA node
 * @node: NUMA node ID that we want to select a CPU from
 *
 * This function will attempt to find a "random" cpu available on a given
 * node. If there are no CPUs available on the given node it will वापस
 * WORK_CPU_UNBOUND indicating that we should just schedule to any
 * available CPU अगर we need to schedule this work.
 */
अटल पूर्णांक workqueue_select_cpu_near(पूर्णांक node)
अणु
	पूर्णांक cpu;

	/* No poपूर्णांक in करोing this अगर NUMA isn't enabled क्रम workqueues */
	अगर (!wq_numa_enabled)
		वापस WORK_CPU_UNBOUND;

	/* Delay binding to CPU अगर node is not valid or online */
	अगर (node < 0 || node >= MAX_NUMNODES || !node_online(node))
		वापस WORK_CPU_UNBOUND;

	/* Use local node/cpu अगर we are alपढ़ोy there */
	cpu = raw_smp_processor_id();
	अगर (node == cpu_to_node(cpu))
		वापस cpu;

	/* Use "random" otherwise know as "first" online CPU of node */
	cpu = cpumask_any_and(cpumask_of_node(node), cpu_online_mask);

	/* If CPU is valid वापस that, otherwise just defer */
	वापस cpu < nr_cpu_ids ? cpu : WORK_CPU_UNBOUND;
पूर्ण

/**
 * queue_work_node - queue work on a "random" cpu क्रम a given NUMA node
 * @node: NUMA node that we are targeting the work क्रम
 * @wq: workqueue to use
 * @work: work to queue
 *
 * We queue the work to a "random" CPU within a given NUMA node. The basic
 * idea here is to provide a way to somehow associate work with a given
 * NUMA node.
 *
 * This function will only make a best efक्रमt attempt at getting this onto
 * the right NUMA node. If no node is requested or the requested node is
 * offline then we just fall back to standard queue_work behavior.
 *
 * Currently the "random" CPU ends up being the first available CPU in the
 * पूर्णांकersection of cpu_online_mask and the cpumask of the node, unless we
 * are running on the node. In that हाल we just use the current CPU.
 *
 * Return: %false अगर @work was alपढ़ोy on a queue, %true otherwise.
 */
bool queue_work_node(पूर्णांक node, काष्ठा workqueue_काष्ठा *wq,
		     काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ flags;
	bool ret = false;

	/*
	 * This current implementation is specअगरic to unbound workqueues.
	 * Specअगरically we only वापस the first available CPU क्रम a given
	 * node instead of cycling through inभागidual CPUs within the node.
	 *
	 * If this is used with a per-cpu workqueue then the logic in
	 * workqueue_select_cpu_near would need to be updated to allow क्रम
	 * some round robin type logic.
	 */
	WARN_ON_ONCE(!(wq->flags & WQ_UNBOUND));

	local_irq_save(flags);

	अगर (!test_and_set_bit(WORK_STRUCT_PENDING_BIT, work_data_bits(work))) अणु
		पूर्णांक cpu = workqueue_select_cpu_near(node);

		__queue_work(cpu, wq, work);
		ret = true;
	पूर्ण

	local_irq_restore(flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(queue_work_node);

व्योम delayed_work_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा delayed_work *dwork = from_समयr(dwork, t, समयr);

	/* should have been called from irqsafe समयr with irq alपढ़ोy off */
	__queue_work(dwork->cpu, dwork->wq, &dwork->work);
पूर्ण
EXPORT_SYMBOL(delayed_work_समयr_fn);

अटल व्योम __queue_delayed_work(पूर्णांक cpu, काष्ठा workqueue_काष्ठा *wq,
				काष्ठा delayed_work *dwork, अचिन्हित दीर्घ delay)
अणु
	काष्ठा समयr_list *समयr = &dwork->समयr;
	काष्ठा work_काष्ठा *work = &dwork->work;

	WARN_ON_ONCE(!wq);
	WARN_ON_FUNCTION_MISMATCH(समयr->function, delayed_work_समयr_fn);
	WARN_ON_ONCE(समयr_pending(समयr));
	WARN_ON_ONCE(!list_empty(&work->entry));

	/*
	 * If @delay is 0, queue @dwork->work immediately.  This is क्रम
	 * both optimization and correctness.  The earliest @समयr can
	 * expire is on the बंदst next tick and delayed_work users depend
	 * on that there's no such delay when @delay is 0.
	 */
	अगर (!delay) अणु
		__queue_work(cpu, wq, &dwork->work);
		वापस;
	पूर्ण

	dwork->wq = wq;
	dwork->cpu = cpu;
	समयr->expires = jअगरfies + delay;

	अगर (unlikely(cpu != WORK_CPU_UNBOUND))
		add_समयr_on(समयr, cpu);
	अन्यथा
		add_समयr(समयr);
पूर्ण

/**
 * queue_delayed_work_on - queue work on specअगरic CPU after delay
 * @cpu: CPU number to execute work on
 * @wq: workqueue to use
 * @dwork: work to queue
 * @delay: number of jअगरfies to रुको beक्रमe queueing
 *
 * Return: %false अगर @work was alपढ़ोy on a queue, %true otherwise.  If
 * @delay is zero and @dwork is idle, it will be scheduled क्रम immediate
 * execution.
 */
bool queue_delayed_work_on(पूर्णांक cpu, काष्ठा workqueue_काष्ठा *wq,
			   काष्ठा delayed_work *dwork, अचिन्हित दीर्घ delay)
अणु
	काष्ठा work_काष्ठा *work = &dwork->work;
	bool ret = false;
	अचिन्हित दीर्घ flags;

	/* पढ़ो the comment in __queue_work() */
	local_irq_save(flags);

	अगर (!test_and_set_bit(WORK_STRUCT_PENDING_BIT, work_data_bits(work))) अणु
		__queue_delayed_work(cpu, wq, dwork, delay);
		ret = true;
	पूर्ण

	local_irq_restore(flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(queue_delayed_work_on);

/**
 * mod_delayed_work_on - modअगरy delay of or queue a delayed work on specअगरic CPU
 * @cpu: CPU number to execute work on
 * @wq: workqueue to use
 * @dwork: work to queue
 * @delay: number of jअगरfies to रुको beक्रमe queueing
 *
 * If @dwork is idle, equivalent to queue_delayed_work_on(); otherwise,
 * modअगरy @dwork's समयr so that it expires after @delay.  If @delay is
 * zero, @work is guaranteed to be scheduled immediately regardless of its
 * current state.
 *
 * Return: %false अगर @dwork was idle and queued, %true अगर @dwork was
 * pending and its समयr was modअगरied.
 *
 * This function is safe to call from any context including IRQ handler.
 * See try_to_grab_pending() क्रम details.
 */
bool mod_delayed_work_on(पूर्णांक cpu, काष्ठा workqueue_काष्ठा *wq,
			 काष्ठा delayed_work *dwork, अचिन्हित दीर्घ delay)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	करो अणु
		ret = try_to_grab_pending(&dwork->work, true, &flags);
	पूर्ण जबतक (unlikely(ret == -EAGAIN));

	अगर (likely(ret >= 0)) अणु
		__queue_delayed_work(cpu, wq, dwork, delay);
		local_irq_restore(flags);
	पूर्ण

	/* -ENOENT from try_to_grab_pending() becomes %true */
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mod_delayed_work_on);

अटल व्योम rcu_work_rcufn(काष्ठा rcu_head *rcu)
अणु
	काष्ठा rcu_work *rwork = container_of(rcu, काष्ठा rcu_work, rcu);

	/* पढ़ो the comment in __queue_work() */
	local_irq_disable();
	__queue_work(WORK_CPU_UNBOUND, rwork->wq, &rwork->work);
	local_irq_enable();
पूर्ण

/**
 * queue_rcu_work - queue work after a RCU grace period
 * @wq: workqueue to use
 * @rwork: work to queue
 *
 * Return: %false अगर @rwork was alपढ़ोy pending, %true otherwise.  Note
 * that a full RCU grace period is guaranteed only after a %true वापस.
 * While @rwork is guaranteed to be executed after a %false वापस, the
 * execution may happen beक्रमe a full RCU grace period has passed.
 */
bool queue_rcu_work(काष्ठा workqueue_काष्ठा *wq, काष्ठा rcu_work *rwork)
अणु
	काष्ठा work_काष्ठा *work = &rwork->work;

	अगर (!test_and_set_bit(WORK_STRUCT_PENDING_BIT, work_data_bits(work))) अणु
		rwork->wq = wq;
		call_rcu(&rwork->rcu, rcu_work_rcufn);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL(queue_rcu_work);

/**
 * worker_enter_idle - enter idle state
 * @worker: worker which is entering idle state
 *
 * @worker is entering idle state.  Update stats and idle समयr अगर
 * necessary.
 *
 * LOCKING:
 * raw_spin_lock_irq(pool->lock).
 */
अटल व्योम worker_enter_idle(काष्ठा worker *worker)
अणु
	काष्ठा worker_pool *pool = worker->pool;

	अगर (WARN_ON_ONCE(worker->flags & WORKER_IDLE) ||
	    WARN_ON_ONCE(!list_empty(&worker->entry) &&
			 (worker->hentry.next || worker->hentry.pprev)))
		वापस;

	/* can't use worker_set_flags(), also called from create_worker() */
	worker->flags |= WORKER_IDLE;
	pool->nr_idle++;
	worker->last_active = jअगरfies;

	/* idle_list is LIFO */
	list_add(&worker->entry, &pool->idle_list);

	अगर (too_many_workers(pool) && !समयr_pending(&pool->idle_समयr))
		mod_समयr(&pool->idle_समयr, jअगरfies + IDLE_WORKER_TIMEOUT);

	/*
	 * Sanity check nr_running.  Because unbind_workers() releases
	 * pool->lock between setting %WORKER_UNBOUND and zapping
	 * nr_running, the warning may trigger spuriously.  Check अगरf
	 * unbind is not in progress.
	 */
	WARN_ON_ONCE(!(pool->flags & POOL_DISASSOCIATED) &&
		     pool->nr_workers == pool->nr_idle &&
		     atomic_पढ़ो(&pool->nr_running));
पूर्ण

/**
 * worker_leave_idle - leave idle state
 * @worker: worker which is leaving idle state
 *
 * @worker is leaving idle state.  Update stats.
 *
 * LOCKING:
 * raw_spin_lock_irq(pool->lock).
 */
अटल व्योम worker_leave_idle(काष्ठा worker *worker)
अणु
	काष्ठा worker_pool *pool = worker->pool;

	अगर (WARN_ON_ONCE(!(worker->flags & WORKER_IDLE)))
		वापस;
	worker_clr_flags(worker, WORKER_IDLE);
	pool->nr_idle--;
	list_del_init(&worker->entry);
पूर्ण

अटल काष्ठा worker *alloc_worker(पूर्णांक node)
अणु
	काष्ठा worker *worker;

	worker = kzalloc_node(माप(*worker), GFP_KERNEL, node);
	अगर (worker) अणु
		INIT_LIST_HEAD(&worker->entry);
		INIT_LIST_HEAD(&worker->scheduled);
		INIT_LIST_HEAD(&worker->node);
		/* on creation a worker is in !idle && prep state */
		worker->flags = WORKER_PREP;
	पूर्ण
	वापस worker;
पूर्ण

/**
 * worker_attach_to_pool() - attach a worker to a pool
 * @worker: worker to be attached
 * @pool: the target pool
 *
 * Attach @worker to @pool.  Once attached, the %WORKER_UNBOUND flag and
 * cpu-binding of @worker are kept coordinated with the pool across
 * cpu-[un]hotplugs.
 */
अटल व्योम worker_attach_to_pool(काष्ठा worker *worker,
				   काष्ठा worker_pool *pool)
अणु
	mutex_lock(&wq_pool_attach_mutex);

	/*
	 * The wq_pool_attach_mutex ensures %POOL_DISASSOCIATED reमुख्यs
	 * stable across this function.  See the comments above the flag
	 * definition क्रम details.
	 */
	अगर (pool->flags & POOL_DISASSOCIATED)
		worker->flags |= WORKER_UNBOUND;
	अन्यथा
		kthपढ़ो_set_per_cpu(worker->task, pool->cpu);

	अगर (worker->rescue_wq)
		set_cpus_allowed_ptr(worker->task, pool->attrs->cpumask);

	list_add_tail(&worker->node, &pool->workers);
	worker->pool = pool;

	mutex_unlock(&wq_pool_attach_mutex);
पूर्ण

/**
 * worker_detach_from_pool() - detach a worker from its pool
 * @worker: worker which is attached to its pool
 *
 * Unकरो the attaching which had been करोne in worker_attach_to_pool().  The
 * caller worker shouldn't access to the pool after detached except it has
 * other reference to the pool.
 */
अटल व्योम worker_detach_from_pool(काष्ठा worker *worker)
अणु
	काष्ठा worker_pool *pool = worker->pool;
	काष्ठा completion *detach_completion = शून्य;

	mutex_lock(&wq_pool_attach_mutex);

	kthपढ़ो_set_per_cpu(worker->task, -1);
	list_del(&worker->node);
	worker->pool = शून्य;

	अगर (list_empty(&pool->workers))
		detach_completion = pool->detach_completion;
	mutex_unlock(&wq_pool_attach_mutex);

	/* clear leftover flags without pool->lock after it is detached */
	worker->flags &= ~(WORKER_UNBOUND | WORKER_REBOUND);

	अगर (detach_completion)
		complete(detach_completion);
पूर्ण

/**
 * create_worker - create a new workqueue worker
 * @pool: pool the new worker will beदीर्घ to
 *
 * Create and start a new worker which is attached to @pool.
 *
 * CONTEXT:
 * Might sleep.  Does GFP_KERNEL allocations.
 *
 * Return:
 * Poपूर्णांकer to the newly created worker.
 */
अटल काष्ठा worker *create_worker(काष्ठा worker_pool *pool)
अणु
	काष्ठा worker *worker = शून्य;
	पूर्णांक id = -1;
	अक्षर id_buf[16];

	/* ID is needed to determine kthपढ़ो name */
	id = ida_simple_get(&pool->worker_ida, 0, 0, GFP_KERNEL);
	अगर (id < 0)
		जाओ fail;

	worker = alloc_worker(pool->node);
	अगर (!worker)
		जाओ fail;

	worker->id = id;

	अगर (pool->cpu >= 0)
		snम_लिखो(id_buf, माप(id_buf), "%d:%d%s", pool->cpu, id,
			 pool->attrs->nice < 0  ? "H" : "");
	अन्यथा
		snम_लिखो(id_buf, माप(id_buf), "u%d:%d", pool->id, id);

	worker->task = kthपढ़ो_create_on_node(worker_thपढ़ो, worker, pool->node,
					      "kworker/%s", id_buf);
	अगर (IS_ERR(worker->task))
		जाओ fail;

	set_user_nice(worker->task, pool->attrs->nice);
	kthपढ़ो_bind_mask(worker->task, pool->attrs->cpumask);

	/* successful, attach the worker to the pool */
	worker_attach_to_pool(worker, pool);

	/* start the newly created worker */
	raw_spin_lock_irq(&pool->lock);
	worker->pool->nr_workers++;
	worker_enter_idle(worker);
	wake_up_process(worker->task);
	raw_spin_unlock_irq(&pool->lock);

	वापस worker;

fail:
	अगर (id >= 0)
		ida_simple_हटाओ(&pool->worker_ida, id);
	kमुक्त(worker);
	वापस शून्य;
पूर्ण

/**
 * destroy_worker - destroy a workqueue worker
 * @worker: worker to be destroyed
 *
 * Destroy @worker and adjust @pool stats accordingly.  The worker should
 * be idle.
 *
 * CONTEXT:
 * raw_spin_lock_irq(pool->lock).
 */
अटल व्योम destroy_worker(काष्ठा worker *worker)
अणु
	काष्ठा worker_pool *pool = worker->pool;

	lockdep_निश्चित_held(&pool->lock);

	/* sanity check frenzy */
	अगर (WARN_ON(worker->current_work) ||
	    WARN_ON(!list_empty(&worker->scheduled)) ||
	    WARN_ON(!(worker->flags & WORKER_IDLE)))
		वापस;

	pool->nr_workers--;
	pool->nr_idle--;

	list_del_init(&worker->entry);
	worker->flags |= WORKER_DIE;
	wake_up_process(worker->task);
पूर्ण

अटल व्योम idle_worker_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा worker_pool *pool = from_समयr(pool, t, idle_समयr);

	raw_spin_lock_irq(&pool->lock);

	जबतक (too_many_workers(pool)) अणु
		काष्ठा worker *worker;
		अचिन्हित दीर्घ expires;

		/* idle_list is kept in LIFO order, check the last one */
		worker = list_entry(pool->idle_list.prev, काष्ठा worker, entry);
		expires = worker->last_active + IDLE_WORKER_TIMEOUT;

		अगर (समय_beक्रमe(jअगरfies, expires)) अणु
			mod_समयr(&pool->idle_समयr, expires);
			अवरोध;
		पूर्ण

		destroy_worker(worker);
	पूर्ण

	raw_spin_unlock_irq(&pool->lock);
पूर्ण

अटल व्योम send_mayday(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pool_workqueue *pwq = get_work_pwq(work);
	काष्ठा workqueue_काष्ठा *wq = pwq->wq;

	lockdep_निश्चित_held(&wq_mayday_lock);

	अगर (!wq->rescuer)
		वापस;

	/* mayday mayday mayday */
	अगर (list_empty(&pwq->mayday_node)) अणु
		/*
		 * If @pwq is क्रम an unbound wq, its base ref may be put at
		 * any समय due to an attribute change.  Pin @pwq until the
		 * rescuer is करोne with it.
		 */
		get_pwq(pwq);
		list_add_tail(&pwq->mayday_node, &wq->maydays);
		wake_up_process(wq->rescuer->task);
	पूर्ण
पूर्ण

अटल व्योम pool_mayday_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा worker_pool *pool = from_समयr(pool, t, mayday_समयr);
	काष्ठा work_काष्ठा *work;

	raw_spin_lock_irq(&pool->lock);
	raw_spin_lock(&wq_mayday_lock);		/* क्रम wq->maydays */

	अगर (need_to_create_worker(pool)) अणु
		/*
		 * We've been trying to create a new worker but
		 * haven't been successful.  We might be hitting an
		 * allocation deadlock.  Send distress संकेतs to
		 * rescuers.
		 */
		list_क्रम_each_entry(work, &pool->worklist, entry)
			send_mayday(work);
	पूर्ण

	raw_spin_unlock(&wq_mayday_lock);
	raw_spin_unlock_irq(&pool->lock);

	mod_समयr(&pool->mayday_समयr, jअगरfies + MAYDAY_INTERVAL);
पूर्ण

/**
 * maybe_create_worker - create a new worker अगर necessary
 * @pool: pool to create a new worker क्रम
 *
 * Create a new worker क्रम @pool अगर necessary.  @pool is guaranteed to
 * have at least one idle worker on वापस from this function.  If
 * creating a new worker takes दीर्घer than MAYDAY_INTERVAL, mayday is
 * sent to all rescuers with works scheduled on @pool to resolve
 * possible allocation deadlock.
 *
 * On वापस, need_to_create_worker() is guaranteed to be %false and
 * may_start_working() %true.
 *
 * LOCKING:
 * raw_spin_lock_irq(pool->lock) which may be released and regrabbed
 * multiple बार.  Does GFP_KERNEL allocations.  Called only from
 * manager.
 */
अटल व्योम maybe_create_worker(काष्ठा worker_pool *pool)
__releases(&pool->lock)
__acquires(&pool->lock)
अणु
restart:
	raw_spin_unlock_irq(&pool->lock);

	/* अगर we करोn't make progress in MAYDAY_INITIAL_TIMEOUT, call क्रम help */
	mod_समयr(&pool->mayday_समयr, jअगरfies + MAYDAY_INITIAL_TIMEOUT);

	जबतक (true) अणु
		अगर (create_worker(pool) || !need_to_create_worker(pool))
			अवरोध;

		schedule_समयout_पूर्णांकerruptible(CREATE_COOLDOWN);

		अगर (!need_to_create_worker(pool))
			अवरोध;
	पूर्ण

	del_समयr_sync(&pool->mayday_समयr);
	raw_spin_lock_irq(&pool->lock);
	/*
	 * This is necessary even after a new worker was just successfully
	 * created as @pool->lock was dropped and the new worker might have
	 * alपढ़ोy become busy.
	 */
	अगर (need_to_create_worker(pool))
		जाओ restart;
पूर्ण

/**
 * manage_workers - manage worker pool
 * @worker: self
 *
 * Assume the manager role and manage the worker pool @worker beदीर्घs
 * to.  At any given समय, there can be only zero or one manager per
 * pool.  The exclusion is handled स्वतःmatically by this function.
 *
 * The caller can safely start processing works on false वापस.  On
 * true वापस, it's guaranteed that need_to_create_worker() is false
 * and may_start_working() is true.
 *
 * CONTEXT:
 * raw_spin_lock_irq(pool->lock) which may be released and regrabbed
 * multiple बार.  Does GFP_KERNEL allocations.
 *
 * Return:
 * %false अगर the pool करोesn't need management and the caller can safely
 * start processing works, %true अगर management function was perक्रमmed and
 * the conditions that the caller verअगरied beक्रमe calling the function may
 * no दीर्घer be true.
 */
अटल bool manage_workers(काष्ठा worker *worker)
अणु
	काष्ठा worker_pool *pool = worker->pool;

	अगर (pool->flags & POOL_MANAGER_ACTIVE)
		वापस false;

	pool->flags |= POOL_MANAGER_ACTIVE;
	pool->manager = worker;

	maybe_create_worker(pool);

	pool->manager = शून्य;
	pool->flags &= ~POOL_MANAGER_ACTIVE;
	rcuरुको_wake_up(&manager_रुको);
	वापस true;
पूर्ण

/**
 * process_one_work - process single work
 * @worker: self
 * @work: work to process
 *
 * Process @work.  This function contains all the logics necessary to
 * process a single work including synchronization against and
 * पूर्णांकeraction with other workers on the same cpu, queueing and
 * flushing.  As दीर्घ as context requirement is met, any worker can
 * call this function to process a work.
 *
 * CONTEXT:
 * raw_spin_lock_irq(pool->lock) which is released and regrabbed.
 */
अटल व्योम process_one_work(काष्ठा worker *worker, काष्ठा work_काष्ठा *work)
__releases(&pool->lock)
__acquires(&pool->lock)
अणु
	काष्ठा pool_workqueue *pwq = get_work_pwq(work);
	काष्ठा worker_pool *pool = worker->pool;
	bool cpu_पूर्णांकensive = pwq->wq->flags & WQ_CPU_INTENSIVE;
	पूर्णांक work_color;
	काष्ठा worker *collision;
#अगर_घोषित CONFIG_LOCKDEP
	/*
	 * It is permissible to मुक्त the काष्ठा work_काष्ठा from
	 * inside the function that is called from it, this we need to
	 * take पूर्णांकo account क्रम lockdep too.  To aव्योम bogus "held
	 * lock मुक्तd" warnings as well as problems when looking पूर्णांकo
	 * work->lockdep_map, make a copy and use that here.
	 */
	काष्ठा lockdep_map lockdep_map;

	lockdep_copy_map(&lockdep_map, &work->lockdep_map);
#पूर्ण_अगर
	/* ensure we're on the correct CPU */
	WARN_ON_ONCE(!(pool->flags & POOL_DISASSOCIATED) &&
		     raw_smp_processor_id() != pool->cpu);

	/*
	 * A single work shouldn't be executed concurrently by
	 * multiple workers on a single cpu.  Check whether anyone is
	 * alपढ़ोy processing the work.  If so, defer the work to the
	 * currently executing one.
	 */
	collision = find_worker_executing_work(pool, work);
	अगर (unlikely(collision)) अणु
		move_linked_works(work, &collision->scheduled, शून्य);
		वापस;
	पूर्ण

	/* claim and dequeue */
	debug_work_deactivate(work);
	hash_add(pool->busy_hash, &worker->hentry, (अचिन्हित दीर्घ)work);
	worker->current_work = work;
	worker->current_func = work->func;
	worker->current_pwq = pwq;
	work_color = get_work_color(work);

	/*
	 * Record wq name क्रम cmdline and debug reporting, may get
	 * overridden through set_worker_desc().
	 */
	strscpy(worker->desc, pwq->wq->name, WORKER_DESC_LEN);

	list_del_init(&work->entry);

	/*
	 * CPU पूर्णांकensive works करोn't participate in concurrency management.
	 * They're the scheduler's responsibility.  This takes @worker out
	 * of concurrency management and the next code block will chain
	 * execution of the pending work items.
	 */
	अगर (unlikely(cpu_पूर्णांकensive))
		worker_set_flags(worker, WORKER_CPU_INTENSIVE);

	/*
	 * Wake up another worker अगर necessary.  The condition is always
	 * false क्रम normal per-cpu workers since nr_running would always
	 * be >= 1 at this poपूर्णांक.  This is used to chain execution of the
	 * pending work items क्रम WORKER_NOT_RUNNING workers such as the
	 * UNBOUND and CPU_INTENSIVE ones.
	 */
	अगर (need_more_worker(pool))
		wake_up_worker(pool);

	/*
	 * Record the last pool and clear PENDING which should be the last
	 * update to @work.  Also, करो this inside @pool->lock so that
	 * PENDING and queued state changes happen together जबतक IRQ is
	 * disabled.
	 */
	set_work_pool_and_clear_pending(work, pool->id);

	raw_spin_unlock_irq(&pool->lock);

	lock_map_acquire(&pwq->wq->lockdep_map);
	lock_map_acquire(&lockdep_map);
	/*
	 * Strictly speaking we should mark the invariant state without holding
	 * any locks, that is, beक्रमe these two lock_map_acquire()'s.
	 *
	 * However, that would result in:
	 *
	 *   A(W1)
	 *   WFC(C)
	 *		A(W1)
	 *		C(C)
	 *
	 * Which would create W1->C->W1 dependencies, even though there is no
	 * actual deadlock possible. There are two solutions, using a
	 * पढ़ो-recursive acquire on the work(queue) 'locks', but this will then
	 * hit the lockdep limitation on recursive locks, or simply discard
	 * these locks.
	 *
	 * AFAICT there is no possible deadlock scenario between the
	 * flush_work() and complete() primitives (except क्रम single-thपढ़ोed
	 * workqueues), so hiding them isn't a problem.
	 */
	lockdep_invariant_state(true);
	trace_workqueue_execute_start(work);
	worker->current_func(work);
	/*
	 * While we must be careful to not use "work" after this, the trace
	 * poपूर्णांक will only record its address.
	 */
	trace_workqueue_execute_end(work, worker->current_func);
	lock_map_release(&lockdep_map);
	lock_map_release(&pwq->wq->lockdep_map);

	अगर (unlikely(in_atomic() || lockdep_depth(current) > 0)) अणु
		pr_err("BUG: workqueue leaked lock or atomic: %s/0x%08x/%d\n"
		       "     last function: %ps\n",
		       current->comm, preempt_count(), task_pid_nr(current),
		       worker->current_func);
		debug_show_held_locks(current);
		dump_stack();
	पूर्ण

	/*
	 * The following prevents a kworker from hogging CPU on !PREEMPTION
	 * kernels, where a requeueing work item रुकोing क्रम something to
	 * happen could deadlock with stop_machine as such work item could
	 * indefinitely requeue itself जबतक all other CPUs are trapped in
	 * stop_machine. At the same समय, report a quiescent RCU state so
	 * the same condition करोesn't मुक्तze RCU.
	 */
	cond_resched();

	raw_spin_lock_irq(&pool->lock);

	/* clear cpu पूर्णांकensive status */
	अगर (unlikely(cpu_पूर्णांकensive))
		worker_clr_flags(worker, WORKER_CPU_INTENSIVE);

	/* tag the worker क्रम identअगरication in schedule() */
	worker->last_func = worker->current_func;

	/* we're करोne with it, release */
	hash_del(&worker->hentry);
	worker->current_work = शून्य;
	worker->current_func = शून्य;
	worker->current_pwq = शून्य;
	pwq_dec_nr_in_flight(pwq, work_color);
पूर्ण

/**
 * process_scheduled_works - process scheduled works
 * @worker: self
 *
 * Process all scheduled works.  Please note that the scheduled list
 * may change जबतक processing a work, so this function repeatedly
 * fetches a work from the top and executes it.
 *
 * CONTEXT:
 * raw_spin_lock_irq(pool->lock) which may be released and regrabbed
 * multiple बार.
 */
अटल व्योम process_scheduled_works(काष्ठा worker *worker)
अणु
	जबतक (!list_empty(&worker->scheduled)) अणु
		काष्ठा work_काष्ठा *work = list_first_entry(&worker->scheduled,
						काष्ठा work_काष्ठा, entry);
		process_one_work(worker, work);
	पूर्ण
पूर्ण

अटल व्योम set_pf_worker(bool val)
अणु
	mutex_lock(&wq_pool_attach_mutex);
	अगर (val)
		current->flags |= PF_WQ_WORKER;
	अन्यथा
		current->flags &= ~PF_WQ_WORKER;
	mutex_unlock(&wq_pool_attach_mutex);
पूर्ण

/**
 * worker_thपढ़ो - the worker thपढ़ो function
 * @__worker: self
 *
 * The worker thपढ़ो function.  All workers beदीर्घ to a worker_pool -
 * either a per-cpu one or dynamic unbound one.  These workers process all
 * work items regardless of their specअगरic target workqueue.  The only
 * exception is work items which beदीर्घ to workqueues with a rescuer which
 * will be explained in rescuer_thपढ़ो().
 *
 * Return: 0
 */
अटल पूर्णांक worker_thपढ़ो(व्योम *__worker)
अणु
	काष्ठा worker *worker = __worker;
	काष्ठा worker_pool *pool = worker->pool;

	/* tell the scheduler that this is a workqueue worker */
	set_pf_worker(true);
woke_up:
	raw_spin_lock_irq(&pool->lock);

	/* am I supposed to die? */
	अगर (unlikely(worker->flags & WORKER_DIE)) अणु
		raw_spin_unlock_irq(&pool->lock);
		WARN_ON_ONCE(!list_empty(&worker->entry));
		set_pf_worker(false);

		set_task_comm(worker->task, "kworker/dying");
		ida_simple_हटाओ(&pool->worker_ida, worker->id);
		worker_detach_from_pool(worker);
		kमुक्त(worker);
		वापस 0;
	पूर्ण

	worker_leave_idle(worker);
recheck:
	/* no more worker necessary? */
	अगर (!need_more_worker(pool))
		जाओ sleep;

	/* करो we need to manage? */
	अगर (unlikely(!may_start_working(pool)) && manage_workers(worker))
		जाओ recheck;

	/*
	 * ->scheduled list can only be filled जबतक a worker is
	 * preparing to process a work or actually processing it.
	 * Make sure nobody diddled with it जबतक I was sleeping.
	 */
	WARN_ON_ONCE(!list_empty(&worker->scheduled));

	/*
	 * Finish PREP stage.  We're guaranteed to have at least one idle
	 * worker or that someone अन्यथा has alपढ़ोy assumed the manager
	 * role.  This is where @worker starts participating in concurrency
	 * management अगर applicable and concurrency management is restored
	 * after being rebound.  See rebind_workers() क्रम details.
	 */
	worker_clr_flags(worker, WORKER_PREP | WORKER_REBOUND);

	करो अणु
		काष्ठा work_काष्ठा *work =
			list_first_entry(&pool->worklist,
					 काष्ठा work_काष्ठा, entry);

		pool->watchकरोg_ts = jअगरfies;

		अगर (likely(!(*work_data_bits(work) & WORK_STRUCT_LINKED))) अणु
			/* optimization path, not strictly necessary */
			process_one_work(worker, work);
			अगर (unlikely(!list_empty(&worker->scheduled)))
				process_scheduled_works(worker);
		पूर्ण अन्यथा अणु
			move_linked_works(work, &worker->scheduled, शून्य);
			process_scheduled_works(worker);
		पूर्ण
	पूर्ण जबतक (keep_working(pool));

	worker_set_flags(worker, WORKER_PREP);
sleep:
	/*
	 * pool->lock is held and there's no work to process and no need to
	 * manage, sleep.  Workers are woken up only जबतक holding
	 * pool->lock or from local cpu, so setting the current state
	 * beक्रमe releasing pool->lock is enough to prevent losing any
	 * event.
	 */
	worker_enter_idle(worker);
	__set_current_state(TASK_IDLE);
	raw_spin_unlock_irq(&pool->lock);
	schedule();
	जाओ woke_up;
पूर्ण

/**
 * rescuer_thपढ़ो - the rescuer thपढ़ो function
 * @__rescuer: self
 *
 * Workqueue rescuer thपढ़ो function.  There's one rescuer क्रम each
 * workqueue which has WQ_MEM_RECLAIM set.
 *
 * Regular work processing on a pool may block trying to create a new
 * worker which uses GFP_KERNEL allocation which has slight chance of
 * developing पूर्णांकo deadlock अगर some works currently on the same queue
 * need to be processed to satisfy the GFP_KERNEL allocation.  This is
 * the problem rescuer solves.
 *
 * When such condition is possible, the pool summons rescuers of all
 * workqueues which have works queued on the pool and let them process
 * those works so that क्रमward progress can be guaranteed.
 *
 * This should happen rarely.
 *
 * Return: 0
 */
अटल पूर्णांक rescuer_thपढ़ो(व्योम *__rescuer)
अणु
	काष्ठा worker *rescuer = __rescuer;
	काष्ठा workqueue_काष्ठा *wq = rescuer->rescue_wq;
	काष्ठा list_head *scheduled = &rescuer->scheduled;
	bool should_stop;

	set_user_nice(current, RESCUER_NICE_LEVEL);

	/*
	 * Mark rescuer as worker too.  As WORKER_PREP is never cleared, it
	 * करोesn't participate in concurrency management.
	 */
	set_pf_worker(true);
repeat:
	set_current_state(TASK_IDLE);

	/*
	 * By the समय the rescuer is requested to stop, the workqueue
	 * shouldn't have any work pending, but @wq->maydays may still have
	 * pwq(s) queued.  This can happen by non-rescuer workers consuming
	 * all the work items beक्रमe the rescuer got to them.  Go through
	 * @wq->maydays processing beक्रमe acting on should_stop so that the
	 * list is always empty on निकास.
	 */
	should_stop = kthपढ़ो_should_stop();

	/* see whether any pwq is asking क्रम help */
	raw_spin_lock_irq(&wq_mayday_lock);

	जबतक (!list_empty(&wq->maydays)) अणु
		काष्ठा pool_workqueue *pwq = list_first_entry(&wq->maydays,
					काष्ठा pool_workqueue, mayday_node);
		काष्ठा worker_pool *pool = pwq->pool;
		काष्ठा work_काष्ठा *work, *n;
		bool first = true;

		__set_current_state(TASK_RUNNING);
		list_del_init(&pwq->mayday_node);

		raw_spin_unlock_irq(&wq_mayday_lock);

		worker_attach_to_pool(rescuer, pool);

		raw_spin_lock_irq(&pool->lock);

		/*
		 * Slurp in all works issued via this workqueue and
		 * process'em.
		 */
		WARN_ON_ONCE(!list_empty(scheduled));
		list_क्रम_each_entry_safe(work, n, &pool->worklist, entry) अणु
			अगर (get_work_pwq(work) == pwq) अणु
				अगर (first)
					pool->watchकरोg_ts = jअगरfies;
				move_linked_works(work, scheduled, &n);
			पूर्ण
			first = false;
		पूर्ण

		अगर (!list_empty(scheduled)) अणु
			process_scheduled_works(rescuer);

			/*
			 * The above execution of rescued work items could
			 * have created more to rescue through
			 * pwq_activate_first_delayed() or chained
			 * queueing.  Let's put @pwq back on mayday list so
			 * that such back-to-back work items, which may be
			 * being used to relieve memory pressure, करोn't
			 * incur MAYDAY_INTERVAL delay inbetween.
			 */
			अगर (pwq->nr_active && need_to_create_worker(pool)) अणु
				raw_spin_lock(&wq_mayday_lock);
				/*
				 * Queue अगरf we aren't racing deकाष्ठाion
				 * and somebody अन्यथा hasn't queued it alपढ़ोy.
				 */
				अगर (wq->rescuer && list_empty(&pwq->mayday_node)) अणु
					get_pwq(pwq);
					list_add_tail(&pwq->mayday_node, &wq->maydays);
				पूर्ण
				raw_spin_unlock(&wq_mayday_lock);
			पूर्ण
		पूर्ण

		/*
		 * Put the reference grabbed by send_mayday().  @pool won't
		 * go away जबतक we're still attached to it.
		 */
		put_pwq(pwq);

		/*
		 * Leave this pool.  If need_more_worker() is %true, notअगरy a
		 * regular worker; otherwise, we end up with 0 concurrency
		 * and stalling the execution.
		 */
		अगर (need_more_worker(pool))
			wake_up_worker(pool);

		raw_spin_unlock_irq(&pool->lock);

		worker_detach_from_pool(rescuer);

		raw_spin_lock_irq(&wq_mayday_lock);
	पूर्ण

	raw_spin_unlock_irq(&wq_mayday_lock);

	अगर (should_stop) अणु
		__set_current_state(TASK_RUNNING);
		set_pf_worker(false);
		वापस 0;
	पूर्ण

	/* rescuers should never participate in concurrency management */
	WARN_ON_ONCE(!(rescuer->flags & WORKER_NOT_RUNNING));
	schedule();
	जाओ repeat;
पूर्ण

/**
 * check_flush_dependency - check क्रम flush dependency sanity
 * @target_wq: workqueue being flushed
 * @target_work: work item being flushed (शून्य क्रम workqueue flushes)
 *
 * %current is trying to flush the whole @target_wq or @target_work on it.
 * If @target_wq करोesn't have %WQ_MEM_RECLAIM, verअगरy that %current is not
 * reclaiming memory or running on a workqueue which करोesn't have
 * %WQ_MEM_RECLAIM as that can अवरोध क्रमward-progress guarantee leading to
 * a deadlock.
 */
अटल व्योम check_flush_dependency(काष्ठा workqueue_काष्ठा *target_wq,
				   काष्ठा work_काष्ठा *target_work)
अणु
	work_func_t target_func = target_work ? target_work->func : शून्य;
	काष्ठा worker *worker;

	अगर (target_wq->flags & WQ_MEM_RECLAIM)
		वापस;

	worker = current_wq_worker();

	WARN_ONCE(current->flags & PF_MEMALLOC,
		  "workqueue: PF_MEMALLOC task %d(%s) is flushing !WQ_MEM_RECLAIM %s:%ps",
		  current->pid, current->comm, target_wq->name, target_func);
	WARN_ONCE(worker && ((worker->current_pwq->wq->flags &
			      (WQ_MEM_RECLAIM | __WQ_LEGACY)) == WQ_MEM_RECLAIM),
		  "workqueue: WQ_MEM_RECLAIM %s:%ps is flushing !WQ_MEM_RECLAIM %s:%ps",
		  worker->current_pwq->wq->name, worker->current_func,
		  target_wq->name, target_func);
पूर्ण

काष्ठा wq_barrier अणु
	काष्ठा work_काष्ठा	work;
	काष्ठा completion	करोne;
	काष्ठा task_काष्ठा	*task;	/* purely inक्रमmational */
पूर्ण;

अटल व्योम wq_barrier_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wq_barrier *barr = container_of(work, काष्ठा wq_barrier, work);
	complete(&barr->करोne);
पूर्ण

/**
 * insert_wq_barrier - insert a barrier work
 * @pwq: pwq to insert barrier पूर्णांकo
 * @barr: wq_barrier to insert
 * @target: target work to attach @barr to
 * @worker: worker currently executing @target, शून्य अगर @target is not executing
 *
 * @barr is linked to @target such that @barr is completed only after
 * @target finishes execution.  Please note that the ordering
 * guarantee is observed only with respect to @target and on the local
 * cpu.
 *
 * Currently, a queued barrier can't be canceled.  This is because
 * try_to_grab_pending() can't determine whether the work to be
 * grabbed is at the head of the queue and thus can't clear LINKED
 * flag of the previous work जबतक there must be a valid next work
 * after a work with LINKED flag set.
 *
 * Note that when @worker is non-शून्य, @target may be modअगरied
 * underneath us, so we can't reliably determine pwq from @target.
 *
 * CONTEXT:
 * raw_spin_lock_irq(pool->lock).
 */
अटल व्योम insert_wq_barrier(काष्ठा pool_workqueue *pwq,
			      काष्ठा wq_barrier *barr,
			      काष्ठा work_काष्ठा *target, काष्ठा worker *worker)
अणु
	काष्ठा list_head *head;
	अचिन्हित पूर्णांक linked = 0;

	/*
	 * debugobject calls are safe here even with pool->lock locked
	 * as we know क्रम sure that this will not trigger any of the
	 * checks and call back पूर्णांकo the fixup functions where we
	 * might deadlock.
	 */
	INIT_WORK_ONSTACK(&barr->work, wq_barrier_func);
	__set_bit(WORK_STRUCT_PENDING_BIT, work_data_bits(&barr->work));

	init_completion_map(&barr->करोne, &target->lockdep_map);

	barr->task = current;

	/*
	 * If @target is currently being executed, schedule the
	 * barrier to the worker; otherwise, put it after @target.
	 */
	अगर (worker)
		head = worker->scheduled.next;
	अन्यथा अणु
		अचिन्हित दीर्घ *bits = work_data_bits(target);

		head = target->entry.next;
		/* there can alपढ़ोy be other linked works, inherit and set */
		linked = *bits & WORK_STRUCT_LINKED;
		__set_bit(WORK_STRUCT_LINKED_BIT, bits);
	पूर्ण

	debug_work_activate(&barr->work);
	insert_work(pwq, &barr->work, head,
		    work_color_to_flags(WORK_NO_COLOR) | linked);
पूर्ण

/**
 * flush_workqueue_prep_pwqs - prepare pwqs क्रम workqueue flushing
 * @wq: workqueue being flushed
 * @flush_color: new flush color, < 0 क्रम no-op
 * @work_color: new work color, < 0 क्रम no-op
 *
 * Prepare pwqs क्रम workqueue flushing.
 *
 * If @flush_color is non-negative, flush_color on all pwqs should be
 * -1.  If no pwq has in-flight commands at the specअगरied color, all
 * pwq->flush_color's stay at -1 and %false is वापसed.  If any pwq
 * has in flight commands, its pwq->flush_color is set to
 * @flush_color, @wq->nr_pwqs_to_flush is updated accordingly, pwq
 * wakeup logic is armed and %true is वापसed.
 *
 * The caller should have initialized @wq->first_flusher prior to
 * calling this function with non-negative @flush_color.  If
 * @flush_color is negative, no flush color update is करोne and %false
 * is वापसed.
 *
 * If @work_color is non-negative, all pwqs should have the same
 * work_color which is previous to @work_color and all will be
 * advanced to @work_color.
 *
 * CONTEXT:
 * mutex_lock(wq->mutex).
 *
 * Return:
 * %true अगर @flush_color >= 0 and there's something to flush.  %false
 * otherwise.
 */
अटल bool flush_workqueue_prep_pwqs(काष्ठा workqueue_काष्ठा *wq,
				      पूर्णांक flush_color, पूर्णांक work_color)
अणु
	bool रुको = false;
	काष्ठा pool_workqueue *pwq;

	अगर (flush_color >= 0) अणु
		WARN_ON_ONCE(atomic_पढ़ो(&wq->nr_pwqs_to_flush));
		atomic_set(&wq->nr_pwqs_to_flush, 1);
	पूर्ण

	क्रम_each_pwq(pwq, wq) अणु
		काष्ठा worker_pool *pool = pwq->pool;

		raw_spin_lock_irq(&pool->lock);

		अगर (flush_color >= 0) अणु
			WARN_ON_ONCE(pwq->flush_color != -1);

			अगर (pwq->nr_in_flight[flush_color]) अणु
				pwq->flush_color = flush_color;
				atomic_inc(&wq->nr_pwqs_to_flush);
				रुको = true;
			पूर्ण
		पूर्ण

		अगर (work_color >= 0) अणु
			WARN_ON_ONCE(work_color != work_next_color(pwq->work_color));
			pwq->work_color = work_color;
		पूर्ण

		raw_spin_unlock_irq(&pool->lock);
	पूर्ण

	अगर (flush_color >= 0 && atomic_dec_and_test(&wq->nr_pwqs_to_flush))
		complete(&wq->first_flusher->करोne);

	वापस रुको;
पूर्ण

/**
 * flush_workqueue - ensure that any scheduled work has run to completion.
 * @wq: workqueue to flush
 *
 * This function sleeps until all work items which were queued on entry
 * have finished execution, but it is not livelocked by new incoming ones.
 */
व्योम flush_workqueue(काष्ठा workqueue_काष्ठा *wq)
अणु
	काष्ठा wq_flusher this_flusher = अणु
		.list = LIST_HEAD_INIT(this_flusher.list),
		.flush_color = -1,
		.करोne = COMPLETION_INITIALIZER_ONSTACK_MAP(this_flusher.करोne, wq->lockdep_map),
	पूर्ण;
	पूर्णांक next_color;

	अगर (WARN_ON(!wq_online))
		वापस;

	lock_map_acquire(&wq->lockdep_map);
	lock_map_release(&wq->lockdep_map);

	mutex_lock(&wq->mutex);

	/*
	 * Start-to-रुको phase
	 */
	next_color = work_next_color(wq->work_color);

	अगर (next_color != wq->flush_color) अणु
		/*
		 * Color space is not full.  The current work_color
		 * becomes our flush_color and work_color is advanced
		 * by one.
		 */
		WARN_ON_ONCE(!list_empty(&wq->flusher_overflow));
		this_flusher.flush_color = wq->work_color;
		wq->work_color = next_color;

		अगर (!wq->first_flusher) अणु
			/* no flush in progress, become the first flusher */
			WARN_ON_ONCE(wq->flush_color != this_flusher.flush_color);

			wq->first_flusher = &this_flusher;

			अगर (!flush_workqueue_prep_pwqs(wq, wq->flush_color,
						       wq->work_color)) अणु
				/* nothing to flush, करोne */
				wq->flush_color = next_color;
				wq->first_flusher = शून्य;
				जाओ out_unlock;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* रुको in queue */
			WARN_ON_ONCE(wq->flush_color == this_flusher.flush_color);
			list_add_tail(&this_flusher.list, &wq->flusher_queue);
			flush_workqueue_prep_pwqs(wq, -1, wq->work_color);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Oops, color space is full, रुको on overflow queue.
		 * The next flush completion will assign us
		 * flush_color and transfer to flusher_queue.
		 */
		list_add_tail(&this_flusher.list, &wq->flusher_overflow);
	पूर्ण

	check_flush_dependency(wq, शून्य);

	mutex_unlock(&wq->mutex);

	रुको_क्रम_completion(&this_flusher.करोne);

	/*
	 * Wake-up-and-cascade phase
	 *
	 * First flushers are responsible क्रम cascading flushes and
	 * handling overflow.  Non-first flushers can simply वापस.
	 */
	अगर (READ_ONCE(wq->first_flusher) != &this_flusher)
		वापस;

	mutex_lock(&wq->mutex);

	/* we might have raced, check again with mutex held */
	अगर (wq->first_flusher != &this_flusher)
		जाओ out_unlock;

	WRITE_ONCE(wq->first_flusher, शून्य);

	WARN_ON_ONCE(!list_empty(&this_flusher.list));
	WARN_ON_ONCE(wq->flush_color != this_flusher.flush_color);

	जबतक (true) अणु
		काष्ठा wq_flusher *next, *पंचांगp;

		/* complete all the flushers sharing the current flush color */
		list_क्रम_each_entry_safe(next, पंचांगp, &wq->flusher_queue, list) अणु
			अगर (next->flush_color != wq->flush_color)
				अवरोध;
			list_del_init(&next->list);
			complete(&next->करोne);
		पूर्ण

		WARN_ON_ONCE(!list_empty(&wq->flusher_overflow) &&
			     wq->flush_color != work_next_color(wq->work_color));

		/* this flush_color is finished, advance by one */
		wq->flush_color = work_next_color(wq->flush_color);

		/* one color has been मुक्तd, handle overflow queue */
		अगर (!list_empty(&wq->flusher_overflow)) अणु
			/*
			 * Assign the same color to all overflowed
			 * flushers, advance work_color and append to
			 * flusher_queue.  This is the start-to-रुको
			 * phase क्रम these overflowed flushers.
			 */
			list_क्रम_each_entry(पंचांगp, &wq->flusher_overflow, list)
				पंचांगp->flush_color = wq->work_color;

			wq->work_color = work_next_color(wq->work_color);

			list_splice_tail_init(&wq->flusher_overflow,
					      &wq->flusher_queue);
			flush_workqueue_prep_pwqs(wq, -1, wq->work_color);
		पूर्ण

		अगर (list_empty(&wq->flusher_queue)) अणु
			WARN_ON_ONCE(wq->flush_color != wq->work_color);
			अवरोध;
		पूर्ण

		/*
		 * Need to flush more colors.  Make the next flusher
		 * the new first flusher and arm pwqs.
		 */
		WARN_ON_ONCE(wq->flush_color == wq->work_color);
		WARN_ON_ONCE(wq->flush_color != next->flush_color);

		list_del_init(&next->list);
		wq->first_flusher = next;

		अगर (flush_workqueue_prep_pwqs(wq, wq->flush_color, -1))
			अवरोध;

		/*
		 * Meh... this color is alपढ़ोy करोne, clear first
		 * flusher and repeat cascading.
		 */
		wq->first_flusher = शून्य;
	पूर्ण

out_unlock:
	mutex_unlock(&wq->mutex);
पूर्ण
EXPORT_SYMBOL(flush_workqueue);

/**
 * drain_workqueue - drain a workqueue
 * @wq: workqueue to drain
 *
 * Wait until the workqueue becomes empty.  While draining is in progress,
 * only chain queueing is allowed.  IOW, only currently pending or running
 * work items on @wq can queue further work items on it.  @wq is flushed
 * repeatedly until it becomes empty.  The number of flushing is determined
 * by the depth of chaining and should be relatively लघु.  Whine अगर it
 * takes too दीर्घ.
 */
व्योम drain_workqueue(काष्ठा workqueue_काष्ठा *wq)
अणु
	अचिन्हित पूर्णांक flush_cnt = 0;
	काष्ठा pool_workqueue *pwq;

	/*
	 * __queue_work() needs to test whether there are drainers, is much
	 * hotter than drain_workqueue() and alपढ़ोy looks at @wq->flags.
	 * Use __WQ_DRAINING so that queue करोesn't have to check nr_drainers.
	 */
	mutex_lock(&wq->mutex);
	अगर (!wq->nr_drainers++)
		wq->flags |= __WQ_DRAINING;
	mutex_unlock(&wq->mutex);
reflush:
	flush_workqueue(wq);

	mutex_lock(&wq->mutex);

	क्रम_each_pwq(pwq, wq) अणु
		bool drained;

		raw_spin_lock_irq(&pwq->pool->lock);
		drained = !pwq->nr_active && list_empty(&pwq->delayed_works);
		raw_spin_unlock_irq(&pwq->pool->lock);

		अगर (drained)
			जारी;

		अगर (++flush_cnt == 10 ||
		    (flush_cnt % 100 == 0 && flush_cnt <= 1000))
			pr_warn("workqueue %s: %s() isn't complete after %u tries\n",
				wq->name, __func__, flush_cnt);

		mutex_unlock(&wq->mutex);
		जाओ reflush;
	पूर्ण

	अगर (!--wq->nr_drainers)
		wq->flags &= ~__WQ_DRAINING;
	mutex_unlock(&wq->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(drain_workqueue);

अटल bool start_flush_work(काष्ठा work_काष्ठा *work, काष्ठा wq_barrier *barr,
			     bool from_cancel)
अणु
	काष्ठा worker *worker = शून्य;
	काष्ठा worker_pool *pool;
	काष्ठा pool_workqueue *pwq;

	might_sleep();

	rcu_पढ़ो_lock();
	pool = get_work_pool(work);
	अगर (!pool) अणु
		rcu_पढ़ो_unlock();
		वापस false;
	पूर्ण

	raw_spin_lock_irq(&pool->lock);
	/* see the comment in try_to_grab_pending() with the same code */
	pwq = get_work_pwq(work);
	अगर (pwq) अणु
		अगर (unlikely(pwq->pool != pool))
			जाओ alपढ़ोy_gone;
	पूर्ण अन्यथा अणु
		worker = find_worker_executing_work(pool, work);
		अगर (!worker)
			जाओ alपढ़ोy_gone;
		pwq = worker->current_pwq;
	पूर्ण

	check_flush_dependency(pwq->wq, work);

	insert_wq_barrier(pwq, barr, work, worker);
	raw_spin_unlock_irq(&pool->lock);

	/*
	 * Force a lock recursion deadlock when using flush_work() inside a
	 * single-thपढ़ोed or rescuer equipped workqueue.
	 *
	 * For single thपढ़ोed workqueues the deadlock happens when the work
	 * is after the work issuing the flush_work(). For rescuer equipped
	 * workqueues the deadlock happens when the rescuer stalls, blocking
	 * क्रमward progress.
	 */
	अगर (!from_cancel &&
	    (pwq->wq->saved_max_active == 1 || pwq->wq->rescuer)) अणु
		lock_map_acquire(&pwq->wq->lockdep_map);
		lock_map_release(&pwq->wq->lockdep_map);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस true;
alपढ़ोy_gone:
	raw_spin_unlock_irq(&pool->lock);
	rcu_पढ़ो_unlock();
	वापस false;
पूर्ण

अटल bool __flush_work(काष्ठा work_काष्ठा *work, bool from_cancel)
अणु
	काष्ठा wq_barrier barr;

	अगर (WARN_ON(!wq_online))
		वापस false;

	अगर (WARN_ON(!work->func))
		वापस false;

	अगर (!from_cancel) अणु
		lock_map_acquire(&work->lockdep_map);
		lock_map_release(&work->lockdep_map);
	पूर्ण

	अगर (start_flush_work(work, &barr, from_cancel)) अणु
		रुको_क्रम_completion(&barr.करोne);
		destroy_work_on_stack(&barr.work);
		वापस true;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
पूर्ण

/**
 * flush_work - रुको क्रम a work to finish executing the last queueing instance
 * @work: the work to flush
 *
 * Wait until @work has finished execution.  @work is guaranteed to be idle
 * on वापस अगर it hasn't been requeued since flush started.
 *
 * Return:
 * %true अगर flush_work() रुकोed क्रम the work to finish execution,
 * %false अगर it was alपढ़ोy idle.
 */
bool flush_work(काष्ठा work_काष्ठा *work)
अणु
	वापस __flush_work(work, false);
पूर्ण
EXPORT_SYMBOL_GPL(flush_work);

काष्ठा cwt_रुको अणु
	रुको_queue_entry_t		रुको;
	काष्ठा work_काष्ठा	*work;
पूर्ण;

अटल पूर्णांक cwt_wakefn(रुको_queue_entry_t *रुको, अचिन्हित mode, पूर्णांक sync, व्योम *key)
अणु
	काष्ठा cwt_रुको *cरुको = container_of(रुको, काष्ठा cwt_रुको, रुको);

	अगर (cरुको->work != key)
		वापस 0;
	वापस स्वतःहटाओ_wake_function(रुको, mode, sync, key);
पूर्ण

अटल bool __cancel_work_समयr(काष्ठा work_काष्ठा *work, bool is_dwork)
अणु
	अटल DECLARE_WAIT_QUEUE_HEAD(cancel_रुकोq);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	करो अणु
		ret = try_to_grab_pending(work, is_dwork, &flags);
		/*
		 * If someone अन्यथा is alपढ़ोy canceling, रुको क्रम it to
		 * finish.  flush_work() करोesn't work क्रम PREEMPT_NONE
		 * because we may get scheduled between @work's completion
		 * and the other canceling task resuming and clearing
		 * CANCELING - flush_work() will वापस false immediately
		 * as @work is no दीर्घer busy, try_to_grab_pending() will
		 * वापस -ENOENT as @work is still being canceled and the
		 * other canceling task won't be able to clear CANCELING as
		 * we're hogging the CPU.
		 *
		 * Let's रुको क्रम completion using a रुकोqueue.  As this
		 * may lead to the thundering herd problem, use a custom
		 * wake function which matches @work aदीर्घ with exclusive
		 * रुको and wakeup.
		 */
		अगर (unlikely(ret == -ENOENT)) अणु
			काष्ठा cwt_रुको cरुको;

			init_रुको(&cरुको.रुको);
			cरुको.रुको.func = cwt_wakefn;
			cरुको.work = work;

			prepare_to_रुको_exclusive(&cancel_रुकोq, &cरुको.रुको,
						  TASK_UNINTERRUPTIBLE);
			अगर (work_is_canceling(work))
				schedule();
			finish_रुको(&cancel_रुकोq, &cरुको.रुको);
		पूर्ण
	पूर्ण जबतक (unlikely(ret < 0));

	/* tell other tasks trying to grab @work to back off */
	mark_work_canceling(work);
	local_irq_restore(flags);

	/*
	 * This allows canceling during early boot.  We know that @work
	 * isn't executing.
	 */
	अगर (wq_online)
		__flush_work(work, true);

	clear_work_data(work);

	/*
	 * Paired with prepare_to_रुको() above so that either
	 * रुकोqueue_active() is visible here or !work_is_canceling() is
	 * visible there.
	 */
	smp_mb();
	अगर (रुकोqueue_active(&cancel_रुकोq))
		__wake_up(&cancel_रुकोq, TASK_NORMAL, 1, work);

	वापस ret;
पूर्ण

/**
 * cancel_work_sync - cancel a work and रुको क्रम it to finish
 * @work: the work to cancel
 *
 * Cancel @work and रुको क्रम its execution to finish.  This function
 * can be used even अगर the work re-queues itself or migrates to
 * another workqueue.  On वापस from this function, @work is
 * guaranteed to be not pending or executing on any CPU.
 *
 * cancel_work_sync(&delayed_work->work) must not be used क्रम
 * delayed_work's.  Use cancel_delayed_work_sync() instead.
 *
 * The caller must ensure that the workqueue on which @work was last
 * queued can't be destroyed beक्रमe this function वापसs.
 *
 * Return:
 * %true अगर @work was pending, %false otherwise.
 */
bool cancel_work_sync(काष्ठा work_काष्ठा *work)
अणु
	वापस __cancel_work_समयr(work, false);
पूर्ण
EXPORT_SYMBOL_GPL(cancel_work_sync);

/**
 * flush_delayed_work - रुको क्रम a dwork to finish executing the last queueing
 * @dwork: the delayed work to flush
 *
 * Delayed समयr is cancelled and the pending work is queued क्रम
 * immediate execution.  Like flush_work(), this function only
 * considers the last queueing instance of @dwork.
 *
 * Return:
 * %true अगर flush_work() रुकोed क्रम the work to finish execution,
 * %false अगर it was alपढ़ोy idle.
 */
bool flush_delayed_work(काष्ठा delayed_work *dwork)
अणु
	local_irq_disable();
	अगर (del_समयr_sync(&dwork->समयr))
		__queue_work(dwork->cpu, dwork->wq, &dwork->work);
	local_irq_enable();
	वापस flush_work(&dwork->work);
पूर्ण
EXPORT_SYMBOL(flush_delayed_work);

/**
 * flush_rcu_work - रुको क्रम a rwork to finish executing the last queueing
 * @rwork: the rcu work to flush
 *
 * Return:
 * %true अगर flush_rcu_work() रुकोed क्रम the work to finish execution,
 * %false अगर it was alपढ़ोy idle.
 */
bool flush_rcu_work(काष्ठा rcu_work *rwork)
अणु
	अगर (test_bit(WORK_STRUCT_PENDING_BIT, work_data_bits(&rwork->work))) अणु
		rcu_barrier();
		flush_work(&rwork->work);
		वापस true;
	पूर्ण अन्यथा अणु
		वापस flush_work(&rwork->work);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(flush_rcu_work);

अटल bool __cancel_work(काष्ठा work_काष्ठा *work, bool is_dwork)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	करो अणु
		ret = try_to_grab_pending(work, is_dwork, &flags);
	पूर्ण जबतक (unlikely(ret == -EAGAIN));

	अगर (unlikely(ret < 0))
		वापस false;

	set_work_pool_and_clear_pending(work, get_work_pool_id(work));
	local_irq_restore(flags);
	वापस ret;
पूर्ण

/**
 * cancel_delayed_work - cancel a delayed work
 * @dwork: delayed_work to cancel
 *
 * Kill off a pending delayed_work.
 *
 * Return: %true अगर @dwork was pending and canceled; %false अगर it wasn't
 * pending.
 *
 * Note:
 * The work callback function may still be running on वापस, unless
 * it वापसs %true and the work करोesn't re-arm itself.  Explicitly flush or
 * use cancel_delayed_work_sync() to रुको on it.
 *
 * This function is safe to call from any context including IRQ handler.
 */
bool cancel_delayed_work(काष्ठा delayed_work *dwork)
अणु
	वापस __cancel_work(&dwork->work, true);
पूर्ण
EXPORT_SYMBOL(cancel_delayed_work);

/**
 * cancel_delayed_work_sync - cancel a delayed work and रुको क्रम it to finish
 * @dwork: the delayed work cancel
 *
 * This is cancel_work_sync() क्रम delayed works.
 *
 * Return:
 * %true अगर @dwork was pending, %false otherwise.
 */
bool cancel_delayed_work_sync(काष्ठा delayed_work *dwork)
अणु
	वापस __cancel_work_समयr(&dwork->work, true);
पूर्ण
EXPORT_SYMBOL(cancel_delayed_work_sync);

/**
 * schedule_on_each_cpu - execute a function synchronously on each online CPU
 * @func: the function to call
 *
 * schedule_on_each_cpu() executes @func on each online CPU using the
 * प्रणाली workqueue and blocks until all CPUs have completed.
 * schedule_on_each_cpu() is very slow.
 *
 * Return:
 * 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक schedule_on_each_cpu(work_func_t func)
अणु
	पूर्णांक cpu;
	काष्ठा work_काष्ठा __percpu *works;

	works = alloc_percpu(काष्ठा work_काष्ठा);
	अगर (!works)
		वापस -ENOMEM;

	get_online_cpus();

	क्रम_each_online_cpu(cpu) अणु
		काष्ठा work_काष्ठा *work = per_cpu_ptr(works, cpu);

		INIT_WORK(work, func);
		schedule_work_on(cpu, work);
	पूर्ण

	क्रम_each_online_cpu(cpu)
		flush_work(per_cpu_ptr(works, cpu));

	put_online_cpus();
	मुक्त_percpu(works);
	वापस 0;
पूर्ण

/**
 * execute_in_process_context - reliably execute the routine with user context
 * @fn:		the function to execute
 * @ew:		guaranteed storage क्रम the execute work काष्ठाure (must
 *		be available when the work executes)
 *
 * Executes the function immediately अगर process context is available,
 * otherwise schedules the function क्रम delayed execution.
 *
 * Return:	0 - function was executed
 *		1 - function was scheduled क्रम execution
 */
पूर्णांक execute_in_process_context(work_func_t fn, काष्ठा execute_work *ew)
अणु
	अगर (!in_पूर्णांकerrupt()) अणु
		fn(&ew->work);
		वापस 0;
	पूर्ण

	INIT_WORK(&ew->work, fn);
	schedule_work(&ew->work);

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(execute_in_process_context);

/**
 * मुक्त_workqueue_attrs - मुक्त a workqueue_attrs
 * @attrs: workqueue_attrs to मुक्त
 *
 * Unकरो alloc_workqueue_attrs().
 */
व्योम मुक्त_workqueue_attrs(काष्ठा workqueue_attrs *attrs)
अणु
	अगर (attrs) अणु
		मुक्त_cpumask_var(attrs->cpumask);
		kमुक्त(attrs);
	पूर्ण
पूर्ण

/**
 * alloc_workqueue_attrs - allocate a workqueue_attrs
 *
 * Allocate a new workqueue_attrs, initialize with शेष settings and
 * वापस it.
 *
 * Return: The allocated new workqueue_attr on success. %शून्य on failure.
 */
काष्ठा workqueue_attrs *alloc_workqueue_attrs(व्योम)
अणु
	काष्ठा workqueue_attrs *attrs;

	attrs = kzalloc(माप(*attrs), GFP_KERNEL);
	अगर (!attrs)
		जाओ fail;
	अगर (!alloc_cpumask_var(&attrs->cpumask, GFP_KERNEL))
		जाओ fail;

	cpumask_copy(attrs->cpumask, cpu_possible_mask);
	वापस attrs;
fail:
	मुक्त_workqueue_attrs(attrs);
	वापस शून्य;
पूर्ण

अटल व्योम copy_workqueue_attrs(काष्ठा workqueue_attrs *to,
				 स्थिर काष्ठा workqueue_attrs *from)
अणु
	to->nice = from->nice;
	cpumask_copy(to->cpumask, from->cpumask);
	/*
	 * Unlike hash and equality test, this function करोesn't ignore
	 * ->no_numa as it is used क्रम both pool and wq attrs.  Instead,
	 * get_unbound_pool() explicitly clears ->no_numa after copying.
	 */
	to->no_numa = from->no_numa;
पूर्ण

/* hash value of the content of @attr */
अटल u32 wqattrs_hash(स्थिर काष्ठा workqueue_attrs *attrs)
अणु
	u32 hash = 0;

	hash = jhash_1word(attrs->nice, hash);
	hash = jhash(cpumask_bits(attrs->cpumask),
		     BITS_TO_LONGS(nr_cpumask_bits) * माप(दीर्घ), hash);
	वापस hash;
पूर्ण

/* content equality test */
अटल bool wqattrs_equal(स्थिर काष्ठा workqueue_attrs *a,
			  स्थिर काष्ठा workqueue_attrs *b)
अणु
	अगर (a->nice != b->nice)
		वापस false;
	अगर (!cpumask_equal(a->cpumask, b->cpumask))
		वापस false;
	वापस true;
पूर्ण

/**
 * init_worker_pool - initialize a newly zalloc'd worker_pool
 * @pool: worker_pool to initialize
 *
 * Initialize a newly zalloc'd @pool.  It also allocates @pool->attrs.
 *
 * Return: 0 on success, -त्रुटि_सं on failure.  Even on failure, all fields
 * inside @pool proper are initialized and put_unbound_pool() can be called
 * on @pool safely to release it.
 */
अटल पूर्णांक init_worker_pool(काष्ठा worker_pool *pool)
अणु
	raw_spin_lock_init(&pool->lock);
	pool->id = -1;
	pool->cpu = -1;
	pool->node = NUMA_NO_NODE;
	pool->flags |= POOL_DISASSOCIATED;
	pool->watchकरोg_ts = jअगरfies;
	INIT_LIST_HEAD(&pool->worklist);
	INIT_LIST_HEAD(&pool->idle_list);
	hash_init(pool->busy_hash);

	समयr_setup(&pool->idle_समयr, idle_worker_समयout, TIMER_DEFERRABLE);

	समयr_setup(&pool->mayday_समयr, pool_mayday_समयout, 0);

	INIT_LIST_HEAD(&pool->workers);

	ida_init(&pool->worker_ida);
	INIT_HLIST_NODE(&pool->hash_node);
	pool->refcnt = 1;

	/* shouldn't fail above this poपूर्णांक */
	pool->attrs = alloc_workqueue_attrs();
	अगर (!pool->attrs)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_LOCKDEP
अटल व्योम wq_init_lockdep(काष्ठा workqueue_काष्ठा *wq)
अणु
	अक्षर *lock_name;

	lockdep_रेजिस्टर_key(&wq->key);
	lock_name = kaप्र_लिखो(GFP_KERNEL, "%s%s", "(wq_completion)", wq->name);
	अगर (!lock_name)
		lock_name = wq->name;

	wq->lock_name = lock_name;
	lockdep_init_map(&wq->lockdep_map, lock_name, &wq->key, 0);
पूर्ण

अटल व्योम wq_unरेजिस्टर_lockdep(काष्ठा workqueue_काष्ठा *wq)
अणु
	lockdep_unरेजिस्टर_key(&wq->key);
पूर्ण

अटल व्योम wq_मुक्त_lockdep(काष्ठा workqueue_काष्ठा *wq)
अणु
	अगर (wq->lock_name != wq->name)
		kमुक्त(wq->lock_name);
पूर्ण
#अन्यथा
अटल व्योम wq_init_lockdep(काष्ठा workqueue_काष्ठा *wq)
अणु
पूर्ण

अटल व्योम wq_unरेजिस्टर_lockdep(काष्ठा workqueue_काष्ठा *wq)
अणु
पूर्ण

अटल व्योम wq_मुक्त_lockdep(काष्ठा workqueue_काष्ठा *wq)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम rcu_मुक्त_wq(काष्ठा rcu_head *rcu)
अणु
	काष्ठा workqueue_काष्ठा *wq =
		container_of(rcu, काष्ठा workqueue_काष्ठा, rcu);

	wq_मुक्त_lockdep(wq);

	अगर (!(wq->flags & WQ_UNBOUND))
		मुक्त_percpu(wq->cpu_pwqs);
	अन्यथा
		मुक्त_workqueue_attrs(wq->unbound_attrs);

	kमुक्त(wq);
पूर्ण

अटल व्योम rcu_मुक्त_pool(काष्ठा rcu_head *rcu)
अणु
	काष्ठा worker_pool *pool = container_of(rcu, काष्ठा worker_pool, rcu);

	ida_destroy(&pool->worker_ida);
	मुक्त_workqueue_attrs(pool->attrs);
	kमुक्त(pool);
पूर्ण

/* This वापसs with the lock held on success (pool manager is inactive). */
अटल bool wq_manager_inactive(काष्ठा worker_pool *pool)
अणु
	raw_spin_lock_irq(&pool->lock);

	अगर (pool->flags & POOL_MANAGER_ACTIVE) अणु
		raw_spin_unlock_irq(&pool->lock);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 * put_unbound_pool - put a worker_pool
 * @pool: worker_pool to put
 *
 * Put @pool.  If its refcnt reaches zero, it माला_लो destroyed in RCU
 * safe manner.  get_unbound_pool() calls this function on its failure path
 * and this function should be able to release pools which went through,
 * successfully or not, init_worker_pool().
 *
 * Should be called with wq_pool_mutex held.
 */
अटल व्योम put_unbound_pool(काष्ठा worker_pool *pool)
अणु
	DECLARE_COMPLETION_ONSTACK(detach_completion);
	काष्ठा worker *worker;

	lockdep_निश्चित_held(&wq_pool_mutex);

	अगर (--pool->refcnt)
		वापस;

	/* sanity checks */
	अगर (WARN_ON(!(pool->cpu < 0)) ||
	    WARN_ON(!list_empty(&pool->worklist)))
		वापस;

	/* release id and unhash */
	अगर (pool->id >= 0)
		idr_हटाओ(&worker_pool_idr, pool->id);
	hash_del(&pool->hash_node);

	/*
	 * Become the manager and destroy all workers.  This prevents
	 * @pool's workers from blocking on attach_mutex.  We're the last
	 * manager and @pool माला_लो मुक्तd with the flag set.
	 * Because of how wq_manager_inactive() works, we will hold the
	 * spinlock after a successful रुको.
	 */
	rcuरुको_रुको_event(&manager_रुको, wq_manager_inactive(pool),
			   TASK_UNINTERRUPTIBLE);
	pool->flags |= POOL_MANAGER_ACTIVE;

	जबतक ((worker = first_idle_worker(pool)))
		destroy_worker(worker);
	WARN_ON(pool->nr_workers || pool->nr_idle);
	raw_spin_unlock_irq(&pool->lock);

	mutex_lock(&wq_pool_attach_mutex);
	अगर (!list_empty(&pool->workers))
		pool->detach_completion = &detach_completion;
	mutex_unlock(&wq_pool_attach_mutex);

	अगर (pool->detach_completion)
		रुको_क्रम_completion(pool->detach_completion);

	/* shut करोwn the समयrs */
	del_समयr_sync(&pool->idle_समयr);
	del_समयr_sync(&pool->mayday_समयr);

	/* RCU रक्षित to allow dereferences from get_work_pool() */
	call_rcu(&pool->rcu, rcu_मुक्त_pool);
पूर्ण

/**
 * get_unbound_pool - get a worker_pool with the specअगरied attributes
 * @attrs: the attributes of the worker_pool to get
 *
 * Obtain a worker_pool which has the same attributes as @attrs, bump the
 * reference count and वापस it.  If there alपढ़ोy is a matching
 * worker_pool, it will be used; otherwise, this function attempts to
 * create a new one.
 *
 * Should be called with wq_pool_mutex held.
 *
 * Return: On success, a worker_pool with the same attributes as @attrs.
 * On failure, %शून्य.
 */
अटल काष्ठा worker_pool *get_unbound_pool(स्थिर काष्ठा workqueue_attrs *attrs)
अणु
	u32 hash = wqattrs_hash(attrs);
	काष्ठा worker_pool *pool;
	पूर्णांक node;
	पूर्णांक target_node = NUMA_NO_NODE;

	lockdep_निश्चित_held(&wq_pool_mutex);

	/* करो we alपढ़ोy have a matching pool? */
	hash_क्रम_each_possible(unbound_pool_hash, pool, hash_node, hash) अणु
		अगर (wqattrs_equal(pool->attrs, attrs)) अणु
			pool->refcnt++;
			वापस pool;
		पूर्ण
	पूर्ण

	/* अगर cpumask is contained inside a NUMA node, we beदीर्घ to that node */
	अगर (wq_numa_enabled) अणु
		क्रम_each_node(node) अणु
			अगर (cpumask_subset(attrs->cpumask,
					   wq_numa_possible_cpumask[node])) अणु
				target_node = node;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* nope, create a new one */
	pool = kzalloc_node(माप(*pool), GFP_KERNEL, target_node);
	अगर (!pool || init_worker_pool(pool) < 0)
		जाओ fail;

	lockdep_set_subclass(&pool->lock, 1);	/* see put_pwq() */
	copy_workqueue_attrs(pool->attrs, attrs);
	pool->node = target_node;

	/*
	 * no_numa isn't a worker_pool attribute, always clear it.  See
	 * 'struct workqueue_attrs' comments क्रम detail.
	 */
	pool->attrs->no_numa = false;

	अगर (worker_pool_assign_id(pool) < 0)
		जाओ fail;

	/* create and start the initial worker */
	अगर (wq_online && !create_worker(pool))
		जाओ fail;

	/* install */
	hash_add(unbound_pool_hash, &pool->hash_node, hash);

	वापस pool;
fail:
	अगर (pool)
		put_unbound_pool(pool);
	वापस शून्य;
पूर्ण

अटल व्योम rcu_मुक्त_pwq(काष्ठा rcu_head *rcu)
अणु
	kmem_cache_मुक्त(pwq_cache,
			container_of(rcu, काष्ठा pool_workqueue, rcu));
पूर्ण

/*
 * Scheduled on प्रणाली_wq by put_pwq() when an unbound pwq hits zero refcnt
 * and needs to be destroyed.
 */
अटल व्योम pwq_unbound_release_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pool_workqueue *pwq = container_of(work, काष्ठा pool_workqueue,
						  unbound_release_work);
	काष्ठा workqueue_काष्ठा *wq = pwq->wq;
	काष्ठा worker_pool *pool = pwq->pool;
	bool is_last;

	अगर (WARN_ON_ONCE(!(wq->flags & WQ_UNBOUND)))
		वापस;

	mutex_lock(&wq->mutex);
	list_del_rcu(&pwq->pwqs_node);
	is_last = list_empty(&wq->pwqs);
	mutex_unlock(&wq->mutex);

	mutex_lock(&wq_pool_mutex);
	put_unbound_pool(pool);
	mutex_unlock(&wq_pool_mutex);

	call_rcu(&pwq->rcu, rcu_मुक्त_pwq);

	/*
	 * If we're the last pwq going away, @wq is alपढ़ोy dead and no one
	 * is gonna access it anymore.  Schedule RCU मुक्त.
	 */
	अगर (is_last) अणु
		wq_unरेजिस्टर_lockdep(wq);
		call_rcu(&wq->rcu, rcu_मुक्त_wq);
	पूर्ण
पूर्ण

/**
 * pwq_adjust_max_active - update a pwq's max_active to the current setting
 * @pwq: target pool_workqueue
 *
 * If @pwq isn't मुक्तzing, set @pwq->max_active to the associated
 * workqueue's saved_max_active and activate delayed work items
 * accordingly.  If @pwq is मुक्तzing, clear @pwq->max_active to zero.
 */
अटल व्योम pwq_adjust_max_active(काष्ठा pool_workqueue *pwq)
अणु
	काष्ठा workqueue_काष्ठा *wq = pwq->wq;
	bool मुक्तzable = wq->flags & WQ_FREEZABLE;
	अचिन्हित दीर्घ flags;

	/* क्रम @wq->saved_max_active */
	lockdep_निश्चित_held(&wq->mutex);

	/* fast निकास क्रम non-मुक्तzable wqs */
	अगर (!मुक्तzable && pwq->max_active == wq->saved_max_active)
		वापस;

	/* this function can be called during early boot w/ irq disabled */
	raw_spin_lock_irqsave(&pwq->pool->lock, flags);

	/*
	 * During [un]मुक्तzing, the caller is responsible क्रम ensuring that
	 * this function is called at least once after @workqueue_मुक्तzing
	 * is updated and visible.
	 */
	अगर (!मुक्तzable || !workqueue_मुक्तzing) अणु
		bool kick = false;

		pwq->max_active = wq->saved_max_active;

		जबतक (!list_empty(&pwq->delayed_works) &&
		       pwq->nr_active < pwq->max_active) अणु
			pwq_activate_first_delayed(pwq);
			kick = true;
		पूर्ण

		/*
		 * Need to kick a worker after thawed or an unbound wq's
		 * max_active is bumped. In realसमय scenarios, always kicking a
		 * worker will cause पूर्णांकerference on the isolated cpu cores, so
		 * let's kick अगरf work items were activated.
		 */
		अगर (kick)
			wake_up_worker(pwq->pool);
	पूर्ण अन्यथा अणु
		pwq->max_active = 0;
	पूर्ण

	raw_spin_unlock_irqrestore(&pwq->pool->lock, flags);
पूर्ण

/* initialize newly alloced @pwq which is associated with @wq and @pool */
अटल व्योम init_pwq(काष्ठा pool_workqueue *pwq, काष्ठा workqueue_काष्ठा *wq,
		     काष्ठा worker_pool *pool)
अणु
	BUG_ON((अचिन्हित दीर्घ)pwq & WORK_STRUCT_FLAG_MASK);

	स_रखो(pwq, 0, माप(*pwq));

	pwq->pool = pool;
	pwq->wq = wq;
	pwq->flush_color = -1;
	pwq->refcnt = 1;
	INIT_LIST_HEAD(&pwq->delayed_works);
	INIT_LIST_HEAD(&pwq->pwqs_node);
	INIT_LIST_HEAD(&pwq->mayday_node);
	INIT_WORK(&pwq->unbound_release_work, pwq_unbound_release_workfn);
पूर्ण

/* sync @pwq with the current state of its associated wq and link it */
अटल व्योम link_pwq(काष्ठा pool_workqueue *pwq)
अणु
	काष्ठा workqueue_काष्ठा *wq = pwq->wq;

	lockdep_निश्चित_held(&wq->mutex);

	/* may be called multiple बार, ignore अगर alपढ़ोy linked */
	अगर (!list_empty(&pwq->pwqs_node))
		वापस;

	/* set the matching work_color */
	pwq->work_color = wq->work_color;

	/* sync max_active to the current setting */
	pwq_adjust_max_active(pwq);

	/* link in @pwq */
	list_add_rcu(&pwq->pwqs_node, &wq->pwqs);
पूर्ण

/* obtain a pool matching @attr and create a pwq associating the pool and @wq */
अटल काष्ठा pool_workqueue *alloc_unbound_pwq(काष्ठा workqueue_काष्ठा *wq,
					स्थिर काष्ठा workqueue_attrs *attrs)
अणु
	काष्ठा worker_pool *pool;
	काष्ठा pool_workqueue *pwq;

	lockdep_निश्चित_held(&wq_pool_mutex);

	pool = get_unbound_pool(attrs);
	अगर (!pool)
		वापस शून्य;

	pwq = kmem_cache_alloc_node(pwq_cache, GFP_KERNEL, pool->node);
	अगर (!pwq) अणु
		put_unbound_pool(pool);
		वापस शून्य;
	पूर्ण

	init_pwq(pwq, wq, pool);
	वापस pwq;
पूर्ण

/**
 * wq_calc_node_cpumask - calculate a wq_attrs' cpumask क्रम the specअगरied node
 * @attrs: the wq_attrs of the शेष pwq of the target workqueue
 * @node: the target NUMA node
 * @cpu_going_करोwn: अगर >= 0, the CPU to consider as offline
 * @cpumask: outarg, the resulting cpumask
 *
 * Calculate the cpumask a workqueue with @attrs should use on @node.  If
 * @cpu_going_करोwn is >= 0, that cpu is considered offline during
 * calculation.  The result is stored in @cpumask.
 *
 * If NUMA affinity is not enabled, @attrs->cpumask is always used.  If
 * enabled and @node has online CPUs requested by @attrs, the वापसed
 * cpumask is the पूर्णांकersection of the possible CPUs of @node and
 * @attrs->cpumask.
 *
 * The caller is responsible क्रम ensuring that the cpumask of @node stays
 * stable.
 *
 * Return: %true अगर the resulting @cpumask is dअगरferent from @attrs->cpumask,
 * %false अगर equal.
 */
अटल bool wq_calc_node_cpumask(स्थिर काष्ठा workqueue_attrs *attrs, पूर्णांक node,
				 पूर्णांक cpu_going_करोwn, cpumask_t *cpumask)
अणु
	अगर (!wq_numa_enabled || attrs->no_numa)
		जाओ use_dfl;

	/* करोes @node have any online CPUs @attrs wants? */
	cpumask_and(cpumask, cpumask_of_node(node), attrs->cpumask);
	अगर (cpu_going_करोwn >= 0)
		cpumask_clear_cpu(cpu_going_करोwn, cpumask);

	अगर (cpumask_empty(cpumask))
		जाओ use_dfl;

	/* yeap, वापस possible CPUs in @node that @attrs wants */
	cpumask_and(cpumask, attrs->cpumask, wq_numa_possible_cpumask[node]);

	अगर (cpumask_empty(cpumask)) अणु
		pr_warn_once("WARNING: workqueue cpumask: online intersect > "
				"possible intersect\n");
		वापस false;
	पूर्ण

	वापस !cpumask_equal(cpumask, attrs->cpumask);

use_dfl:
	cpumask_copy(cpumask, attrs->cpumask);
	वापस false;
पूर्ण

/* install @pwq पूर्णांकo @wq's numa_pwq_tbl[] क्रम @node and वापस the old pwq */
अटल काष्ठा pool_workqueue *numa_pwq_tbl_install(काष्ठा workqueue_काष्ठा *wq,
						   पूर्णांक node,
						   काष्ठा pool_workqueue *pwq)
अणु
	काष्ठा pool_workqueue *old_pwq;

	lockdep_निश्चित_held(&wq_pool_mutex);
	lockdep_निश्चित_held(&wq->mutex);

	/* link_pwq() can handle duplicate calls */
	link_pwq(pwq);

	old_pwq = rcu_access_poपूर्णांकer(wq->numa_pwq_tbl[node]);
	rcu_assign_poपूर्णांकer(wq->numa_pwq_tbl[node], pwq);
	वापस old_pwq;
पूर्ण

/* context to store the prepared attrs & pwqs beक्रमe applying */
काष्ठा apply_wqattrs_ctx अणु
	काष्ठा workqueue_काष्ठा	*wq;		/* target workqueue */
	काष्ठा workqueue_attrs	*attrs;		/* attrs to apply */
	काष्ठा list_head	list;		/* queued क्रम batching commit */
	काष्ठा pool_workqueue	*dfl_pwq;
	काष्ठा pool_workqueue	*pwq_tbl[];
पूर्ण;

/* मुक्त the resources after success or पात */
अटल व्योम apply_wqattrs_cleanup(काष्ठा apply_wqattrs_ctx *ctx)
अणु
	अगर (ctx) अणु
		पूर्णांक node;

		क्रम_each_node(node)
			put_pwq_unlocked(ctx->pwq_tbl[node]);
		put_pwq_unlocked(ctx->dfl_pwq);

		मुक्त_workqueue_attrs(ctx->attrs);

		kमुक्त(ctx);
	पूर्ण
पूर्ण

/* allocate the attrs and pwqs क्रम later installation */
अटल काष्ठा apply_wqattrs_ctx *
apply_wqattrs_prepare(काष्ठा workqueue_काष्ठा *wq,
		      स्थिर काष्ठा workqueue_attrs *attrs)
अणु
	काष्ठा apply_wqattrs_ctx *ctx;
	काष्ठा workqueue_attrs *new_attrs, *पंचांगp_attrs;
	पूर्णांक node;

	lockdep_निश्चित_held(&wq_pool_mutex);

	ctx = kzalloc(काष्ठा_size(ctx, pwq_tbl, nr_node_ids), GFP_KERNEL);

	new_attrs = alloc_workqueue_attrs();
	पंचांगp_attrs = alloc_workqueue_attrs();
	अगर (!ctx || !new_attrs || !पंचांगp_attrs)
		जाओ out_मुक्त;

	/*
	 * Calculate the attrs of the शेष pwq.
	 * If the user configured cpumask करोesn't overlap with the
	 * wq_unbound_cpumask, we fallback to the wq_unbound_cpumask.
	 */
	copy_workqueue_attrs(new_attrs, attrs);
	cpumask_and(new_attrs->cpumask, new_attrs->cpumask, wq_unbound_cpumask);
	अगर (unlikely(cpumask_empty(new_attrs->cpumask)))
		cpumask_copy(new_attrs->cpumask, wq_unbound_cpumask);

	/*
	 * We may create multiple pwqs with dअगरfering cpumasks.  Make a
	 * copy of @new_attrs which will be modअगरied and used to obtain
	 * pools.
	 */
	copy_workqueue_attrs(पंचांगp_attrs, new_attrs);

	/*
	 * If something goes wrong during CPU up/करोwn, we'll fall back to
	 * the शेष pwq covering whole @attrs->cpumask.  Always create
	 * it even अगर we करोn't use it immediately.
	 */
	ctx->dfl_pwq = alloc_unbound_pwq(wq, new_attrs);
	अगर (!ctx->dfl_pwq)
		जाओ out_मुक्त;

	क्रम_each_node(node) अणु
		अगर (wq_calc_node_cpumask(new_attrs, node, -1, पंचांगp_attrs->cpumask)) अणु
			ctx->pwq_tbl[node] = alloc_unbound_pwq(wq, पंचांगp_attrs);
			अगर (!ctx->pwq_tbl[node])
				जाओ out_मुक्त;
		पूर्ण अन्यथा अणु
			ctx->dfl_pwq->refcnt++;
			ctx->pwq_tbl[node] = ctx->dfl_pwq;
		पूर्ण
	पूर्ण

	/* save the user configured attrs and sanitize it. */
	copy_workqueue_attrs(new_attrs, attrs);
	cpumask_and(new_attrs->cpumask, new_attrs->cpumask, cpu_possible_mask);
	ctx->attrs = new_attrs;

	ctx->wq = wq;
	मुक्त_workqueue_attrs(पंचांगp_attrs);
	वापस ctx;

out_मुक्त:
	मुक्त_workqueue_attrs(पंचांगp_attrs);
	मुक्त_workqueue_attrs(new_attrs);
	apply_wqattrs_cleanup(ctx);
	वापस शून्य;
पूर्ण

/* set attrs and install prepared pwqs, @ctx poपूर्णांकs to old pwqs on वापस */
अटल व्योम apply_wqattrs_commit(काष्ठा apply_wqattrs_ctx *ctx)
अणु
	पूर्णांक node;

	/* all pwqs have been created successfully, let's install'em */
	mutex_lock(&ctx->wq->mutex);

	copy_workqueue_attrs(ctx->wq->unbound_attrs, ctx->attrs);

	/* save the previous pwq and install the new one */
	क्रम_each_node(node)
		ctx->pwq_tbl[node] = numa_pwq_tbl_install(ctx->wq, node,
							  ctx->pwq_tbl[node]);

	/* @dfl_pwq might not have been used, ensure it's linked */
	link_pwq(ctx->dfl_pwq);
	swap(ctx->wq->dfl_pwq, ctx->dfl_pwq);

	mutex_unlock(&ctx->wq->mutex);
पूर्ण

अटल व्योम apply_wqattrs_lock(व्योम)
अणु
	/* CPUs should stay stable across pwq creations and installations */
	get_online_cpus();
	mutex_lock(&wq_pool_mutex);
पूर्ण

अटल व्योम apply_wqattrs_unlock(व्योम)
अणु
	mutex_unlock(&wq_pool_mutex);
	put_online_cpus();
पूर्ण

अटल पूर्णांक apply_workqueue_attrs_locked(काष्ठा workqueue_काष्ठा *wq,
					स्थिर काष्ठा workqueue_attrs *attrs)
अणु
	काष्ठा apply_wqattrs_ctx *ctx;

	/* only unbound workqueues can change attributes */
	अगर (WARN_ON(!(wq->flags & WQ_UNBOUND)))
		वापस -EINVAL;

	/* creating multiple pwqs अवरोधs ordering guarantee */
	अगर (!list_empty(&wq->pwqs)) अणु
		अगर (WARN_ON(wq->flags & __WQ_ORDERED_EXPLICIT))
			वापस -EINVAL;

		wq->flags &= ~__WQ_ORDERED;
	पूर्ण

	ctx = apply_wqattrs_prepare(wq, attrs);
	अगर (!ctx)
		वापस -ENOMEM;

	/* the ctx has been prepared successfully, let's commit it */
	apply_wqattrs_commit(ctx);
	apply_wqattrs_cleanup(ctx);

	वापस 0;
पूर्ण

/**
 * apply_workqueue_attrs - apply new workqueue_attrs to an unbound workqueue
 * @wq: the target workqueue
 * @attrs: the workqueue_attrs to apply, allocated with alloc_workqueue_attrs()
 *
 * Apply @attrs to an unbound workqueue @wq.  Unless disabled, on NUMA
 * machines, this function maps a separate pwq to each NUMA node with
 * possibles CPUs in @attrs->cpumask so that work items are affine to the
 * NUMA node it was issued on.  Older pwqs are released as in-flight work
 * items finish.  Note that a work item which repeatedly requeues itself
 * back-to-back will stay on its current pwq.
 *
 * Perक्रमms GFP_KERNEL allocations.
 *
 * Assumes caller has CPU hotplug पढ़ो exclusion, i.e. get_online_cpus().
 *
 * Return: 0 on success and -त्रुटि_सं on failure.
 */
पूर्णांक apply_workqueue_attrs(काष्ठा workqueue_काष्ठा *wq,
			  स्थिर काष्ठा workqueue_attrs *attrs)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_cpus_held();

	mutex_lock(&wq_pool_mutex);
	ret = apply_workqueue_attrs_locked(wq, attrs);
	mutex_unlock(&wq_pool_mutex);

	वापस ret;
पूर्ण

/**
 * wq_update_unbound_numa - update NUMA affinity of a wq क्रम CPU hot[un]plug
 * @wq: the target workqueue
 * @cpu: the CPU coming up or going करोwn
 * @online: whether @cpu is coming up or going करोwn
 *
 * This function is to be called from %CPU_DOWN_PREPARE, %CPU_ONLINE and
 * %CPU_DOWN_FAILED.  @cpu is being hot[un]plugged, update NUMA affinity of
 * @wq accordingly.
 *
 * If NUMA affinity can't be adjusted due to memory allocation failure, it
 * falls back to @wq->dfl_pwq which may not be optimal but is always
 * correct.
 *
 * Note that when the last allowed CPU of a NUMA node goes offline क्रम a
 * workqueue with a cpumask spanning multiple nodes, the workers which were
 * alपढ़ोy executing the work items क्रम the workqueue will lose their CPU
 * affinity and may execute on any CPU.  This is similar to how per-cpu
 * workqueues behave on CPU_DOWN.  If a workqueue user wants strict
 * affinity, it's the user's responsibility to flush the work item from
 * CPU_DOWN_PREPARE.
 */
अटल व्योम wq_update_unbound_numa(काष्ठा workqueue_काष्ठा *wq, पूर्णांक cpu,
				   bool online)
अणु
	पूर्णांक node = cpu_to_node(cpu);
	पूर्णांक cpu_off = online ? -1 : cpu;
	काष्ठा pool_workqueue *old_pwq = शून्य, *pwq;
	काष्ठा workqueue_attrs *target_attrs;
	cpumask_t *cpumask;

	lockdep_निश्चित_held(&wq_pool_mutex);

	अगर (!wq_numa_enabled || !(wq->flags & WQ_UNBOUND) ||
	    wq->unbound_attrs->no_numa)
		वापस;

	/*
	 * We करोn't wanna alloc/मुक्त wq_attrs क्रम each wq क्रम each CPU.
	 * Let's use a pपुनः_स्मृतिated one.  The following buf is रक्षित by
	 * CPU hotplug exclusion.
	 */
	target_attrs = wq_update_unbound_numa_attrs_buf;
	cpumask = target_attrs->cpumask;

	copy_workqueue_attrs(target_attrs, wq->unbound_attrs);
	pwq = unbound_pwq_by_node(wq, node);

	/*
	 * Let's determine what needs to be करोne.  If the target cpumask is
	 * dअगरferent from the शेष pwq's, we need to compare it to @pwq's
	 * and create a new one अगर they करोn't match.  If the target cpumask
	 * equals the शेष pwq's, the शेष pwq should be used.
	 */
	अगर (wq_calc_node_cpumask(wq->dfl_pwq->pool->attrs, node, cpu_off, cpumask)) अणु
		अगर (cpumask_equal(cpumask, pwq->pool->attrs->cpumask))
			वापस;
	पूर्ण अन्यथा अणु
		जाओ use_dfl_pwq;
	पूर्ण

	/* create a new pwq */
	pwq = alloc_unbound_pwq(wq, target_attrs);
	अगर (!pwq) अणु
		pr_warn("workqueue: allocation failed while updating NUMA affinity of \"%s\"\n",
			wq->name);
		जाओ use_dfl_pwq;
	पूर्ण

	/* Install the new pwq. */
	mutex_lock(&wq->mutex);
	old_pwq = numa_pwq_tbl_install(wq, node, pwq);
	जाओ out_unlock;

use_dfl_pwq:
	mutex_lock(&wq->mutex);
	raw_spin_lock_irq(&wq->dfl_pwq->pool->lock);
	get_pwq(wq->dfl_pwq);
	raw_spin_unlock_irq(&wq->dfl_pwq->pool->lock);
	old_pwq = numa_pwq_tbl_install(wq, node, wq->dfl_pwq);
out_unlock:
	mutex_unlock(&wq->mutex);
	put_pwq_unlocked(old_pwq);
पूर्ण

अटल पूर्णांक alloc_and_link_pwqs(काष्ठा workqueue_काष्ठा *wq)
अणु
	bool highpri = wq->flags & WQ_HIGHPRI;
	पूर्णांक cpu, ret;

	अगर (!(wq->flags & WQ_UNBOUND)) अणु
		wq->cpu_pwqs = alloc_percpu(काष्ठा pool_workqueue);
		अगर (!wq->cpu_pwqs)
			वापस -ENOMEM;

		क्रम_each_possible_cpu(cpu) अणु
			काष्ठा pool_workqueue *pwq =
				per_cpu_ptr(wq->cpu_pwqs, cpu);
			काष्ठा worker_pool *cpu_pools =
				per_cpu(cpu_worker_pools, cpu);

			init_pwq(pwq, wq, &cpu_pools[highpri]);

			mutex_lock(&wq->mutex);
			link_pwq(pwq);
			mutex_unlock(&wq->mutex);
		पूर्ण
		वापस 0;
	पूर्ण

	get_online_cpus();
	अगर (wq->flags & __WQ_ORDERED) अणु
		ret = apply_workqueue_attrs(wq, ordered_wq_attrs[highpri]);
		/* there should only be single pwq क्रम ordering guarantee */
		WARN(!ret && (wq->pwqs.next != &wq->dfl_pwq->pwqs_node ||
			      wq->pwqs.prev != &wq->dfl_pwq->pwqs_node),
		     "ordering guarantee broken for workqueue %s\n", wq->name);
	पूर्ण अन्यथा अणु
		ret = apply_workqueue_attrs(wq, unbound_std_wq_attrs[highpri]);
	पूर्ण
	put_online_cpus();

	वापस ret;
पूर्ण

अटल पूर्णांक wq_clamp_max_active(पूर्णांक max_active, अचिन्हित पूर्णांक flags,
			       स्थिर अक्षर *name)
अणु
	पूर्णांक lim = flags & WQ_UNBOUND ? WQ_UNBOUND_MAX_ACTIVE : WQ_MAX_ACTIVE;

	अगर (max_active < 1 || max_active > lim)
		pr_warn("workqueue: max_active %d requested for %s is out of range, clamping between %d and %d\n",
			max_active, name, 1, lim);

	वापस clamp_val(max_active, 1, lim);
पूर्ण

/*
 * Workqueues which may be used during memory reclaim should have a rescuer
 * to guarantee क्रमward progress.
 */
अटल पूर्णांक init_rescuer(काष्ठा workqueue_काष्ठा *wq)
अणु
	काष्ठा worker *rescuer;
	पूर्णांक ret;

	अगर (!(wq->flags & WQ_MEM_RECLAIM))
		वापस 0;

	rescuer = alloc_worker(NUMA_NO_NODE);
	अगर (!rescuer)
		वापस -ENOMEM;

	rescuer->rescue_wq = wq;
	rescuer->task = kthपढ़ो_create(rescuer_thपढ़ो, rescuer, "%s", wq->name);
	अगर (IS_ERR(rescuer->task)) अणु
		ret = PTR_ERR(rescuer->task);
		kमुक्त(rescuer);
		वापस ret;
	पूर्ण

	wq->rescuer = rescuer;
	kthपढ़ो_bind_mask(rescuer->task, cpu_possible_mask);
	wake_up_process(rescuer->task);

	वापस 0;
पूर्ण

__म_लिखो(1, 4)
काष्ठा workqueue_काष्ठा *alloc_workqueue(स्थिर अक्षर *fmt,
					 अचिन्हित पूर्णांक flags,
					 पूर्णांक max_active, ...)
अणु
	माप_प्रकार tbl_size = 0;
	बहु_सूची args;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा pool_workqueue *pwq;

	/*
	 * Unbound && max_active == 1 used to imply ordered, which is no
	 * दीर्घer the हाल on NUMA machines due to per-node pools.  While
	 * alloc_ordered_workqueue() is the right way to create an ordered
	 * workqueue, keep the previous behavior to aव्योम subtle अवरोधages
	 * on NUMA.
	 */
	अगर ((flags & WQ_UNBOUND) && max_active == 1)
		flags |= __WQ_ORDERED;

	/* see the comment above the definition of WQ_POWER_EFFICIENT */
	अगर ((flags & WQ_POWER_EFFICIENT) && wq_घातer_efficient)
		flags |= WQ_UNBOUND;

	/* allocate wq and क्रमmat name */
	अगर (flags & WQ_UNBOUND)
		tbl_size = nr_node_ids * माप(wq->numa_pwq_tbl[0]);

	wq = kzalloc(माप(*wq) + tbl_size, GFP_KERNEL);
	अगर (!wq)
		वापस शून्य;

	अगर (flags & WQ_UNBOUND) अणु
		wq->unbound_attrs = alloc_workqueue_attrs();
		अगर (!wq->unbound_attrs)
			जाओ err_मुक्त_wq;
	पूर्ण

	बहु_शुरू(args, max_active);
	vsnम_लिखो(wq->name, माप(wq->name), fmt, args);
	बहु_पूर्ण(args);

	max_active = max_active ?: WQ_DFL_ACTIVE;
	max_active = wq_clamp_max_active(max_active, flags, wq->name);

	/* init wq */
	wq->flags = flags;
	wq->saved_max_active = max_active;
	mutex_init(&wq->mutex);
	atomic_set(&wq->nr_pwqs_to_flush, 0);
	INIT_LIST_HEAD(&wq->pwqs);
	INIT_LIST_HEAD(&wq->flusher_queue);
	INIT_LIST_HEAD(&wq->flusher_overflow);
	INIT_LIST_HEAD(&wq->maydays);

	wq_init_lockdep(wq);
	INIT_LIST_HEAD(&wq->list);

	अगर (alloc_and_link_pwqs(wq) < 0)
		जाओ err_unreg_lockdep;

	अगर (wq_online && init_rescuer(wq) < 0)
		जाओ err_destroy;

	अगर ((wq->flags & WQ_SYSFS) && workqueue_sysfs_रेजिस्टर(wq))
		जाओ err_destroy;

	/*
	 * wq_pool_mutex protects global मुक्तze state and workqueues list.
	 * Grab it, adjust max_active and add the new @wq to workqueues
	 * list.
	 */
	mutex_lock(&wq_pool_mutex);

	mutex_lock(&wq->mutex);
	क्रम_each_pwq(pwq, wq)
		pwq_adjust_max_active(pwq);
	mutex_unlock(&wq->mutex);

	list_add_tail_rcu(&wq->list, &workqueues);

	mutex_unlock(&wq_pool_mutex);

	वापस wq;

err_unreg_lockdep:
	wq_unरेजिस्टर_lockdep(wq);
	wq_मुक्त_lockdep(wq);
err_मुक्त_wq:
	मुक्त_workqueue_attrs(wq->unbound_attrs);
	kमुक्त(wq);
	वापस शून्य;
err_destroy:
	destroy_workqueue(wq);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(alloc_workqueue);

अटल bool pwq_busy(काष्ठा pool_workqueue *pwq)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < WORK_NR_COLORS; i++)
		अगर (pwq->nr_in_flight[i])
			वापस true;

	अगर ((pwq != pwq->wq->dfl_pwq) && (pwq->refcnt > 1))
		वापस true;
	अगर (pwq->nr_active || !list_empty(&pwq->delayed_works))
		वापस true;

	वापस false;
पूर्ण

/**
 * destroy_workqueue - safely terminate a workqueue
 * @wq: target workqueue
 *
 * Safely destroy a workqueue. All work currently pending will be करोne first.
 */
व्योम destroy_workqueue(काष्ठा workqueue_काष्ठा *wq)
अणु
	काष्ठा pool_workqueue *pwq;
	पूर्णांक node;

	/*
	 * Remove it from sysfs first so that sanity check failure करोesn't
	 * lead to sysfs name conflicts.
	 */
	workqueue_sysfs_unरेजिस्टर(wq);

	/* drain it beक्रमe proceeding with deकाष्ठाion */
	drain_workqueue(wq);

	/* समाप्त rescuer, अगर sanity checks fail, leave it w/o rescuer */
	अगर (wq->rescuer) अणु
		काष्ठा worker *rescuer = wq->rescuer;

		/* this prevents new queueing */
		raw_spin_lock_irq(&wq_mayday_lock);
		wq->rescuer = शून्य;
		raw_spin_unlock_irq(&wq_mayday_lock);

		/* rescuer will empty maydays list beक्रमe निकासing */
		kthपढ़ो_stop(rescuer->task);
		kमुक्त(rescuer);
	पूर्ण

	/*
	 * Sanity checks - grab all the locks so that we रुको क्रम all
	 * in-flight operations which may करो put_pwq().
	 */
	mutex_lock(&wq_pool_mutex);
	mutex_lock(&wq->mutex);
	क्रम_each_pwq(pwq, wq) अणु
		raw_spin_lock_irq(&pwq->pool->lock);
		अगर (WARN_ON(pwq_busy(pwq))) अणु
			pr_warn("%s: %s has the following busy pwq\n",
				__func__, wq->name);
			show_pwq(pwq);
			raw_spin_unlock_irq(&pwq->pool->lock);
			mutex_unlock(&wq->mutex);
			mutex_unlock(&wq_pool_mutex);
			show_workqueue_state();
			वापस;
		पूर्ण
		raw_spin_unlock_irq(&pwq->pool->lock);
	पूर्ण
	mutex_unlock(&wq->mutex);

	/*
	 * wq list is used to मुक्तze wq, हटाओ from list after
	 * flushing is complete in हाल मुक्तze races us.
	 */
	list_del_rcu(&wq->list);
	mutex_unlock(&wq_pool_mutex);

	अगर (!(wq->flags & WQ_UNBOUND)) अणु
		wq_unरेजिस्टर_lockdep(wq);
		/*
		 * The base ref is never dropped on per-cpu pwqs.  Directly
		 * schedule RCU मुक्त.
		 */
		call_rcu(&wq->rcu, rcu_मुक्त_wq);
	पूर्ण अन्यथा अणु
		/*
		 * We're the sole accessor of @wq at this poपूर्णांक.  Directly
		 * access numa_pwq_tbl[] and dfl_pwq to put the base refs.
		 * @wq will be मुक्तd when the last pwq is released.
		 */
		क्रम_each_node(node) अणु
			pwq = rcu_access_poपूर्णांकer(wq->numa_pwq_tbl[node]);
			RCU_INIT_POINTER(wq->numa_pwq_tbl[node], शून्य);
			put_pwq_unlocked(pwq);
		पूर्ण

		/*
		 * Put dfl_pwq.  @wq may be मुक्तd any समय after dfl_pwq is
		 * put.  Don't access it afterwards.
		 */
		pwq = wq->dfl_pwq;
		wq->dfl_pwq = शून्य;
		put_pwq_unlocked(pwq);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(destroy_workqueue);

/**
 * workqueue_set_max_active - adjust max_active of a workqueue
 * @wq: target workqueue
 * @max_active: new max_active value.
 *
 * Set max_active of @wq to @max_active.
 *
 * CONTEXT:
 * Don't call from IRQ context.
 */
व्योम workqueue_set_max_active(काष्ठा workqueue_काष्ठा *wq, पूर्णांक max_active)
अणु
	काष्ठा pool_workqueue *pwq;

	/* disallow meddling with max_active क्रम ordered workqueues */
	अगर (WARN_ON(wq->flags & __WQ_ORDERED_EXPLICIT))
		वापस;

	max_active = wq_clamp_max_active(max_active, wq->flags, wq->name);

	mutex_lock(&wq->mutex);

	wq->flags &= ~__WQ_ORDERED;
	wq->saved_max_active = max_active;

	क्रम_each_pwq(pwq, wq)
		pwq_adjust_max_active(pwq);

	mutex_unlock(&wq->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(workqueue_set_max_active);

/**
 * current_work - retrieve %current task's work काष्ठा
 *
 * Determine अगर %current task is a workqueue worker and what it's working on.
 * Useful to find out the context that the %current task is running in.
 *
 * Return: work काष्ठा अगर %current task is a workqueue worker, %शून्य otherwise.
 */
काष्ठा work_काष्ठा *current_work(व्योम)
अणु
	काष्ठा worker *worker = current_wq_worker();

	वापस worker ? worker->current_work : शून्य;
पूर्ण
EXPORT_SYMBOL(current_work);

/**
 * current_is_workqueue_rescuer - is %current workqueue rescuer?
 *
 * Determine whether %current is a workqueue rescuer.  Can be used from
 * work functions to determine whether it's being run off the rescuer task.
 *
 * Return: %true अगर %current is a workqueue rescuer. %false otherwise.
 */
bool current_is_workqueue_rescuer(व्योम)
अणु
	काष्ठा worker *worker = current_wq_worker();

	वापस worker && worker->rescue_wq;
पूर्ण

/**
 * workqueue_congested - test whether a workqueue is congested
 * @cpu: CPU in question
 * @wq: target workqueue
 *
 * Test whether @wq's cpu workqueue क्रम @cpu is congested.  There is
 * no synchronization around this function and the test result is
 * unreliable and only useful as advisory hपूर्णांकs or क्रम debugging.
 *
 * If @cpu is WORK_CPU_UNBOUND, the test is perक्रमmed on the local CPU.
 * Note that both per-cpu and unbound workqueues may be associated with
 * multiple pool_workqueues which have separate congested states.  A
 * workqueue being congested on one CPU करोesn't mean the workqueue is also
 * contested on other CPUs / NUMA nodes.
 *
 * Return:
 * %true अगर congested, %false otherwise.
 */
bool workqueue_congested(पूर्णांक cpu, काष्ठा workqueue_काष्ठा *wq)
अणु
	काष्ठा pool_workqueue *pwq;
	bool ret;

	rcu_पढ़ो_lock();
	preempt_disable();

	अगर (cpu == WORK_CPU_UNBOUND)
		cpu = smp_processor_id();

	अगर (!(wq->flags & WQ_UNBOUND))
		pwq = per_cpu_ptr(wq->cpu_pwqs, cpu);
	अन्यथा
		pwq = unbound_pwq_by_node(wq, cpu_to_node(cpu));

	ret = !list_empty(&pwq->delayed_works);
	preempt_enable();
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(workqueue_congested);

/**
 * work_busy - test whether a work is currently pending or running
 * @work: the work to be tested
 *
 * Test whether @work is currently pending or running.  There is no
 * synchronization around this function and the test result is
 * unreliable and only useful as advisory hपूर्णांकs or क्रम debugging.
 *
 * Return:
 * OR'd biपंचांगask of WORK_BUSY_* bits.
 */
अचिन्हित पूर्णांक work_busy(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा worker_pool *pool;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ret = 0;

	अगर (work_pending(work))
		ret |= WORK_BUSY_PENDING;

	rcu_पढ़ो_lock();
	pool = get_work_pool(work);
	अगर (pool) अणु
		raw_spin_lock_irqsave(&pool->lock, flags);
		अगर (find_worker_executing_work(pool, work))
			ret |= WORK_BUSY_RUNNING;
		raw_spin_unlock_irqrestore(&pool->lock, flags);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(work_busy);

/**
 * set_worker_desc - set description क्रम the current work item
 * @fmt: म_लिखो-style क्रमmat string
 * @...: arguments क्रम the क्रमmat string
 *
 * This function can be called by a running work function to describe what
 * the work item is about.  If the worker task माला_लो dumped, this
 * inक्रमmation will be prपूर्णांकed out together to help debugging.  The
 * description can be at most WORKER_DESC_LEN including the trailing '\0'.
 */
व्योम set_worker_desc(स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा worker *worker = current_wq_worker();
	बहु_सूची args;

	अगर (worker) अणु
		बहु_शुरू(args, fmt);
		vsnम_लिखो(worker->desc, माप(worker->desc), fmt, args);
		बहु_पूर्ण(args);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(set_worker_desc);

/**
 * prपूर्णांक_worker_info - prपूर्णांक out worker inक्रमmation and description
 * @log_lvl: the log level to use when prपूर्णांकing
 * @task: target task
 *
 * If @task is a worker and currently executing a work item, prपूर्णांक out the
 * name of the workqueue being serviced and worker description set with
 * set_worker_desc() by the currently executing work item.
 *
 * This function can be safely called on any task as दीर्घ as the
 * task_काष्ठा itself is accessible.  While safe, this function isn't
 * synchronized and may prपूर्णांक out mixups or garbages of limited length.
 */
व्योम prपूर्णांक_worker_info(स्थिर अक्षर *log_lvl, काष्ठा task_काष्ठा *task)
अणु
	work_func_t *fn = शून्य;
	अक्षर name[WQ_NAME_LEN] = अणु पूर्ण;
	अक्षर desc[WORKER_DESC_LEN] = अणु पूर्ण;
	काष्ठा pool_workqueue *pwq = शून्य;
	काष्ठा workqueue_काष्ठा *wq = शून्य;
	काष्ठा worker *worker;

	अगर (!(task->flags & PF_WQ_WORKER))
		वापस;

	/*
	 * This function is called without any synchronization and @task
	 * could be in any state.  Be careful with dereferences.
	 */
	worker = kthपढ़ो_probe_data(task);

	/*
	 * Carefully copy the associated workqueue's workfn, name and desc.
	 * Keep the original last '\0' in हाल the original is garbage.
	 */
	copy_from_kernel_nofault(&fn, &worker->current_func, माप(fn));
	copy_from_kernel_nofault(&pwq, &worker->current_pwq, माप(pwq));
	copy_from_kernel_nofault(&wq, &pwq->wq, माप(wq));
	copy_from_kernel_nofault(name, wq->name, माप(name) - 1);
	copy_from_kernel_nofault(desc, worker->desc, माप(desc) - 1);

	अगर (fn || name[0] || desc[0]) अणु
		prपूर्णांकk("%sWorkqueue: %s %ps", log_lvl, name, fn);
		अगर (म_भेद(name, desc))
			pr_cont(" (%s)", desc);
		pr_cont("\n");
	पूर्ण
पूर्ण

अटल व्योम pr_cont_pool_info(काष्ठा worker_pool *pool)
अणु
	pr_cont(" cpus=%*pbl", nr_cpumask_bits, pool->attrs->cpumask);
	अगर (pool->node != NUMA_NO_NODE)
		pr_cont(" node=%d", pool->node);
	pr_cont(" flags=0x%x nice=%d", pool->flags, pool->attrs->nice);
पूर्ण

अटल व्योम pr_cont_work(bool comma, काष्ठा work_काष्ठा *work)
अणु
	अगर (work->func == wq_barrier_func) अणु
		काष्ठा wq_barrier *barr;

		barr = container_of(work, काष्ठा wq_barrier, work);

		pr_cont("%s BAR(%d)", comma ? "," : "",
			task_pid_nr(barr->task));
	पूर्ण अन्यथा अणु
		pr_cont("%s %ps", comma ? "," : "", work->func);
	पूर्ण
पूर्ण

अटल व्योम show_pwq(काष्ठा pool_workqueue *pwq)
अणु
	काष्ठा worker_pool *pool = pwq->pool;
	काष्ठा work_काष्ठा *work;
	काष्ठा worker *worker;
	bool has_in_flight = false, has_pending = false;
	पूर्णांक bkt;

	pr_info("  pwq %d:", pool->id);
	pr_cont_pool_info(pool);

	pr_cont(" active=%d/%d refcnt=%d%s\n",
		pwq->nr_active, pwq->max_active, pwq->refcnt,
		!list_empty(&pwq->mayday_node) ? " MAYDAY" : "");

	hash_क्रम_each(pool->busy_hash, bkt, worker, hentry) अणु
		अगर (worker->current_pwq == pwq) अणु
			has_in_flight = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (has_in_flight) अणु
		bool comma = false;

		pr_info("    in-flight:");
		hash_क्रम_each(pool->busy_hash, bkt, worker, hentry) अणु
			अगर (worker->current_pwq != pwq)
				जारी;

			pr_cont("%s %d%s:%ps", comma ? "," : "",
				task_pid_nr(worker->task),
				worker->rescue_wq ? "(RESCUER)" : "",
				worker->current_func);
			list_क्रम_each_entry(work, &worker->scheduled, entry)
				pr_cont_work(false, work);
			comma = true;
		पूर्ण
		pr_cont("\n");
	पूर्ण

	list_क्रम_each_entry(work, &pool->worklist, entry) अणु
		अगर (get_work_pwq(work) == pwq) अणु
			has_pending = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (has_pending) अणु
		bool comma = false;

		pr_info("    pending:");
		list_क्रम_each_entry(work, &pool->worklist, entry) अणु
			अगर (get_work_pwq(work) != pwq)
				जारी;

			pr_cont_work(comma, work);
			comma = !(*work_data_bits(work) & WORK_STRUCT_LINKED);
		पूर्ण
		pr_cont("\n");
	पूर्ण

	अगर (!list_empty(&pwq->delayed_works)) अणु
		bool comma = false;

		pr_info("    delayed:");
		list_क्रम_each_entry(work, &pwq->delayed_works, entry) अणु
			pr_cont_work(comma, work);
			comma = !(*work_data_bits(work) & WORK_STRUCT_LINKED);
		पूर्ण
		pr_cont("\n");
	पूर्ण
पूर्ण

/**
 * show_workqueue_state - dump workqueue state
 *
 * Called from a sysrq handler or try_to_मुक्तze_tasks() and prपूर्णांकs out
 * all busy workqueues and pools.
 */
व्योम show_workqueue_state(व्योम)
अणु
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा worker_pool *pool;
	अचिन्हित दीर्घ flags;
	पूर्णांक pi;

	rcu_पढ़ो_lock();

	pr_info("Showing busy workqueues and worker pools:\n");

	list_क्रम_each_entry_rcu(wq, &workqueues, list) अणु
		काष्ठा pool_workqueue *pwq;
		bool idle = true;

		क्रम_each_pwq(pwq, wq) अणु
			अगर (pwq->nr_active || !list_empty(&pwq->delayed_works)) अणु
				idle = false;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (idle)
			जारी;

		pr_info("workqueue %s: flags=0x%x\n", wq->name, wq->flags);

		क्रम_each_pwq(pwq, wq) अणु
			raw_spin_lock_irqsave(&pwq->pool->lock, flags);
			अगर (pwq->nr_active || !list_empty(&pwq->delayed_works))
				show_pwq(pwq);
			raw_spin_unlock_irqrestore(&pwq->pool->lock, flags);
			/*
			 * We could be prपूर्णांकing a lot from atomic context, e.g.
			 * sysrq-t -> show_workqueue_state(). Aव्योम triggering
			 * hard lockup.
			 */
			touch_nmi_watchकरोg();
		पूर्ण
	पूर्ण

	क्रम_each_pool(pool, pi) अणु
		काष्ठा worker *worker;
		bool first = true;

		raw_spin_lock_irqsave(&pool->lock, flags);
		अगर (pool->nr_workers == pool->nr_idle)
			जाओ next_pool;

		pr_info("pool %d:", pool->id);
		pr_cont_pool_info(pool);
		pr_cont(" hung=%us workers=%d",
			jअगरfies_to_msecs(jअगरfies - pool->watchकरोg_ts) / 1000,
			pool->nr_workers);
		अगर (pool->manager)
			pr_cont(" manager: %d",
				task_pid_nr(pool->manager->task));
		list_क्रम_each_entry(worker, &pool->idle_list, entry) अणु
			pr_cont(" %s%d", first ? "idle: " : "",
				task_pid_nr(worker->task));
			first = false;
		पूर्ण
		pr_cont("\n");
	next_pool:
		raw_spin_unlock_irqrestore(&pool->lock, flags);
		/*
		 * We could be prपूर्णांकing a lot from atomic context, e.g.
		 * sysrq-t -> show_workqueue_state(). Aव्योम triggering
		 * hard lockup.
		 */
		touch_nmi_watchकरोg();
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

/* used to show worker inक्रमmation through /proc/PID/अणुcomm,stat,statusपूर्ण */
व्योम wq_worker_comm(अक्षर *buf, माप_प्रकार size, काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक off;

	/* always show the actual comm */
	off = strscpy(buf, task->comm, size);
	अगर (off < 0)
		वापस;

	/* stabilize PF_WQ_WORKER and worker pool association */
	mutex_lock(&wq_pool_attach_mutex);

	अगर (task->flags & PF_WQ_WORKER) अणु
		काष्ठा worker *worker = kthपढ़ो_data(task);
		काष्ठा worker_pool *pool = worker->pool;

		अगर (pool) अणु
			raw_spin_lock_irq(&pool->lock);
			/*
			 * ->desc tracks inक्रमmation (wq name or
			 * set_worker_desc()) क्रम the latest execution.  If
			 * current, prepend '+', otherwise '-'.
			 */
			अगर (worker->desc[0] != '\0') अणु
				अगर (worker->current_work)
					scnम_लिखो(buf + off, size - off, "+%s",
						  worker->desc);
				अन्यथा
					scnम_लिखो(buf + off, size - off, "-%s",
						  worker->desc);
			पूर्ण
			raw_spin_unlock_irq(&pool->lock);
		पूर्ण
	पूर्ण

	mutex_unlock(&wq_pool_attach_mutex);
पूर्ण

#अगर_घोषित CONFIG_SMP

/*
 * CPU hotplug.
 *
 * There are two challenges in supporting CPU hotplug.  Firstly, there
 * are a lot of assumptions on strong associations among work, pwq and
 * pool which make migrating pending and scheduled works very
 * dअगरficult to implement without impacting hot paths.  Secondly,
 * worker pools serve mix of लघु, दीर्घ and very दीर्घ running works making
 * blocked draining impractical.
 *
 * This is solved by allowing the pools to be disassociated from the CPU
 * running as an unbound one and allowing it to be reattached later अगर the
 * cpu comes back online.
 */

अटल व्योम unbind_workers(पूर्णांक cpu)
अणु
	काष्ठा worker_pool *pool;
	काष्ठा worker *worker;

	क्रम_each_cpu_worker_pool(pool, cpu) अणु
		mutex_lock(&wq_pool_attach_mutex);
		raw_spin_lock_irq(&pool->lock);

		/*
		 * We've blocked all attach/detach operations. Make all workers
		 * unbound and set DISASSOCIATED.  Beक्रमe this, all workers
		 * except क्रम the ones which are still executing works from
		 * beक्रमe the last CPU करोwn must be on the cpu.  After
		 * this, they may become diasporas.
		 */
		क्रम_each_pool_worker(worker, pool)
			worker->flags |= WORKER_UNBOUND;

		pool->flags |= POOL_DISASSOCIATED;

		raw_spin_unlock_irq(&pool->lock);

		क्रम_each_pool_worker(worker, pool) अणु
			kthपढ़ो_set_per_cpu(worker->task, -1);
			WARN_ON_ONCE(set_cpus_allowed_ptr(worker->task, cpu_possible_mask) < 0);
		पूर्ण

		mutex_unlock(&wq_pool_attach_mutex);

		/*
		 * Call schedule() so that we cross rq->lock and thus can
		 * guarantee sched callbacks see the %WORKER_UNBOUND flag.
		 * This is necessary as scheduler callbacks may be invoked
		 * from other cpus.
		 */
		schedule();

		/*
		 * Sched callbacks are disabled now.  Zap nr_running.
		 * After this, nr_running stays zero and need_more_worker()
		 * and keep_working() are always true as दीर्घ as the
		 * worklist is not empty.  This pool now behaves as an
		 * unbound (in terms of concurrency management) pool which
		 * are served by workers tied to the pool.
		 */
		atomic_set(&pool->nr_running, 0);

		/*
		 * With concurrency management just turned off, a busy
		 * worker blocking could lead to lengthy stalls.  Kick off
		 * unbound chain execution of currently pending work items.
		 */
		raw_spin_lock_irq(&pool->lock);
		wake_up_worker(pool);
		raw_spin_unlock_irq(&pool->lock);
	पूर्ण
पूर्ण

/**
 * rebind_workers - rebind all workers of a pool to the associated CPU
 * @pool: pool of पूर्णांकerest
 *
 * @pool->cpu is coming online.  Rebind all workers to the CPU.
 */
अटल व्योम rebind_workers(काष्ठा worker_pool *pool)
अणु
	काष्ठा worker *worker;

	lockdep_निश्चित_held(&wq_pool_attach_mutex);

	/*
	 * Restore CPU affinity of all workers.  As all idle workers should
	 * be on the run-queue of the associated CPU beक्रमe any local
	 * wake-ups क्रम concurrency management happen, restore CPU affinity
	 * of all workers first and then clear UNBOUND.  As we're called
	 * from CPU_ONLINE, the following shouldn't fail.
	 */
	क्रम_each_pool_worker(worker, pool) अणु
		kthपढ़ो_set_per_cpu(worker->task, pool->cpu);
		WARN_ON_ONCE(set_cpus_allowed_ptr(worker->task,
						  pool->attrs->cpumask) < 0);
	पूर्ण

	raw_spin_lock_irq(&pool->lock);

	pool->flags &= ~POOL_DISASSOCIATED;

	क्रम_each_pool_worker(worker, pool) अणु
		अचिन्हित पूर्णांक worker_flags = worker->flags;

		/*
		 * A bound idle worker should actually be on the runqueue
		 * of the associated CPU क्रम local wake-ups targeting it to
		 * work.  Kick all idle workers so that they migrate to the
		 * associated CPU.  Doing this in the same loop as
		 * replacing UNBOUND with REBOUND is safe as no worker will
		 * be bound beक्रमe @pool->lock is released.
		 */
		अगर (worker_flags & WORKER_IDLE)
			wake_up_process(worker->task);

		/*
		 * We want to clear UNBOUND but can't directly call
		 * worker_clr_flags() or adjust nr_running.  Atomically
		 * replace UNBOUND with another NOT_RUNNING flag REBOUND.
		 * @worker will clear REBOUND using worker_clr_flags() when
		 * it initiates the next execution cycle thus restoring
		 * concurrency management.  Note that when or whether
		 * @worker clears REBOUND करोesn't affect correctness.
		 *
		 * WRITE_ONCE() is necessary because @worker->flags may be
		 * tested without holding any lock in
		 * wq_worker_running().  Without it, NOT_RUNNING test may
		 * fail incorrectly leading to premature concurrency
		 * management operations.
		 */
		WARN_ON_ONCE(!(worker_flags & WORKER_UNBOUND));
		worker_flags |= WORKER_REBOUND;
		worker_flags &= ~WORKER_UNBOUND;
		WRITE_ONCE(worker->flags, worker_flags);
	पूर्ण

	raw_spin_unlock_irq(&pool->lock);
पूर्ण

/**
 * restore_unbound_workers_cpumask - restore cpumask of unbound workers
 * @pool: unbound pool of पूर्णांकerest
 * @cpu: the CPU which is coming up
 *
 * An unbound pool may end up with a cpumask which करोesn't have any online
 * CPUs.  When a worker of such pool get scheduled, the scheduler resets
 * its cpus_allowed.  If @cpu is in @pool's cpumask which didn't have any
 * online CPU beक्रमe, cpus_allowed of all its workers should be restored.
 */
अटल व्योम restore_unbound_workers_cpumask(काष्ठा worker_pool *pool, पूर्णांक cpu)
अणु
	अटल cpumask_t cpumask;
	काष्ठा worker *worker;

	lockdep_निश्चित_held(&wq_pool_attach_mutex);

	/* is @cpu allowed क्रम @pool? */
	अगर (!cpumask_test_cpu(cpu, pool->attrs->cpumask))
		वापस;

	cpumask_and(&cpumask, pool->attrs->cpumask, cpu_online_mask);

	/* as we're called from CPU_ONLINE, the following shouldn't fail */
	क्रम_each_pool_worker(worker, pool)
		WARN_ON_ONCE(set_cpus_allowed_ptr(worker->task, &cpumask) < 0);
पूर्ण

पूर्णांक workqueue_prepare_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा worker_pool *pool;

	क्रम_each_cpu_worker_pool(pool, cpu) अणु
		अगर (pool->nr_workers)
			जारी;
		अगर (!create_worker(pool))
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक workqueue_online_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा worker_pool *pool;
	काष्ठा workqueue_काष्ठा *wq;
	पूर्णांक pi;

	mutex_lock(&wq_pool_mutex);

	क्रम_each_pool(pool, pi) अणु
		mutex_lock(&wq_pool_attach_mutex);

		अगर (pool->cpu == cpu)
			rebind_workers(pool);
		अन्यथा अगर (pool->cpu < 0)
			restore_unbound_workers_cpumask(pool, cpu);

		mutex_unlock(&wq_pool_attach_mutex);
	पूर्ण

	/* update NUMA affinity of unbound workqueues */
	list_क्रम_each_entry(wq, &workqueues, list)
		wq_update_unbound_numa(wq, cpu, true);

	mutex_unlock(&wq_pool_mutex);
	वापस 0;
पूर्ण

पूर्णांक workqueue_offline_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा workqueue_काष्ठा *wq;

	/* unbinding per-cpu workers should happen on the local CPU */
	अगर (WARN_ON(cpu != smp_processor_id()))
		वापस -1;

	unbind_workers(cpu);

	/* update NUMA affinity of unbound workqueues */
	mutex_lock(&wq_pool_mutex);
	list_क्रम_each_entry(wq, &workqueues, list)
		wq_update_unbound_numa(wq, cpu, false);
	mutex_unlock(&wq_pool_mutex);

	वापस 0;
पूर्ण

काष्ठा work_क्रम_cpu अणु
	काष्ठा work_काष्ठा work;
	दीर्घ (*fn)(व्योम *);
	व्योम *arg;
	दीर्घ ret;
पूर्ण;

अटल व्योम work_क्रम_cpu_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा work_क्रम_cpu *wfc = container_of(work, काष्ठा work_क्रम_cpu, work);

	wfc->ret = wfc->fn(wfc->arg);
पूर्ण

/**
 * work_on_cpu - run a function in thपढ़ो context on a particular cpu
 * @cpu: the cpu to run on
 * @fn: the function to run
 * @arg: the function arg
 *
 * It is up to the caller to ensure that the cpu करोesn't go offline.
 * The caller must not hold any locks which would prevent @fn from completing.
 *
 * Return: The value @fn वापसs.
 */
दीर्घ work_on_cpu(पूर्णांक cpu, दीर्घ (*fn)(व्योम *), व्योम *arg)
अणु
	काष्ठा work_क्रम_cpu wfc = अणु .fn = fn, .arg = arg पूर्ण;

	INIT_WORK_ONSTACK(&wfc.work, work_क्रम_cpu_fn);
	schedule_work_on(cpu, &wfc.work);
	flush_work(&wfc.work);
	destroy_work_on_stack(&wfc.work);
	वापस wfc.ret;
पूर्ण
EXPORT_SYMBOL_GPL(work_on_cpu);

/**
 * work_on_cpu_safe - run a function in thपढ़ो context on a particular cpu
 * @cpu: the cpu to run on
 * @fn:  the function to run
 * @arg: the function argument
 *
 * Disables CPU hotplug and calls work_on_cpu(). The caller must not hold
 * any locks which would prevent @fn from completing.
 *
 * Return: The value @fn वापसs.
 */
दीर्घ work_on_cpu_safe(पूर्णांक cpu, दीर्घ (*fn)(व्योम *), व्योम *arg)
अणु
	दीर्घ ret = -ENODEV;

	get_online_cpus();
	अगर (cpu_online(cpu))
		ret = work_on_cpu(cpu, fn, arg);
	put_online_cpus();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(work_on_cpu_safe);
#पूर्ण_अगर /* CONFIG_SMP */

#अगर_घोषित CONFIG_FREEZER

/**
 * मुक्तze_workqueues_begin - begin मुक्तzing workqueues
 *
 * Start मुक्तzing workqueues.  After this function वापसs, all मुक्तzable
 * workqueues will queue new works to their delayed_works list instead of
 * pool->worklist.
 *
 * CONTEXT:
 * Grअसल and releases wq_pool_mutex, wq->mutex and pool->lock's.
 */
व्योम मुक्तze_workqueues_begin(व्योम)
अणु
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा pool_workqueue *pwq;

	mutex_lock(&wq_pool_mutex);

	WARN_ON_ONCE(workqueue_मुक्तzing);
	workqueue_मुक्तzing = true;

	list_क्रम_each_entry(wq, &workqueues, list) अणु
		mutex_lock(&wq->mutex);
		क्रम_each_pwq(pwq, wq)
			pwq_adjust_max_active(pwq);
		mutex_unlock(&wq->mutex);
	पूर्ण

	mutex_unlock(&wq_pool_mutex);
पूर्ण

/**
 * मुक्तze_workqueues_busy - are मुक्तzable workqueues still busy?
 *
 * Check whether मुक्तzing is complete.  This function must be called
 * between मुक्तze_workqueues_begin() and thaw_workqueues().
 *
 * CONTEXT:
 * Grअसल and releases wq_pool_mutex.
 *
 * Return:
 * %true अगर some मुक्तzable workqueues are still busy.  %false अगर मुक्तzing
 * is complete.
 */
bool मुक्तze_workqueues_busy(व्योम)
अणु
	bool busy = false;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा pool_workqueue *pwq;

	mutex_lock(&wq_pool_mutex);

	WARN_ON_ONCE(!workqueue_मुक्तzing);

	list_क्रम_each_entry(wq, &workqueues, list) अणु
		अगर (!(wq->flags & WQ_FREEZABLE))
			जारी;
		/*
		 * nr_active is monotonically decreasing.  It's safe
		 * to peek without lock.
		 */
		rcu_पढ़ो_lock();
		क्रम_each_pwq(pwq, wq) अणु
			WARN_ON_ONCE(pwq->nr_active < 0);
			अगर (pwq->nr_active) अणु
				busy = true;
				rcu_पढ़ो_unlock();
				जाओ out_unlock;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
out_unlock:
	mutex_unlock(&wq_pool_mutex);
	वापस busy;
पूर्ण

/**
 * thaw_workqueues - thaw workqueues
 *
 * Thaw workqueues.  Normal queueing is restored and all collected
 * frozen works are transferred to their respective pool worklists.
 *
 * CONTEXT:
 * Grअसल and releases wq_pool_mutex, wq->mutex and pool->lock's.
 */
व्योम thaw_workqueues(व्योम)
अणु
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा pool_workqueue *pwq;

	mutex_lock(&wq_pool_mutex);

	अगर (!workqueue_मुक्तzing)
		जाओ out_unlock;

	workqueue_मुक्तzing = false;

	/* restore max_active and repopulate worklist */
	list_क्रम_each_entry(wq, &workqueues, list) अणु
		mutex_lock(&wq->mutex);
		क्रम_each_pwq(pwq, wq)
			pwq_adjust_max_active(pwq);
		mutex_unlock(&wq->mutex);
	पूर्ण

out_unlock:
	mutex_unlock(&wq_pool_mutex);
पूर्ण
#पूर्ण_अगर /* CONFIG_FREEZER */

अटल पूर्णांक workqueue_apply_unbound_cpumask(व्योम)
अणु
	LIST_HEAD(ctxs);
	पूर्णांक ret = 0;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा apply_wqattrs_ctx *ctx, *n;

	lockdep_निश्चित_held(&wq_pool_mutex);

	list_क्रम_each_entry(wq, &workqueues, list) अणु
		अगर (!(wq->flags & WQ_UNBOUND))
			जारी;
		/* creating multiple pwqs अवरोधs ordering guarantee */
		अगर (wq->flags & __WQ_ORDERED)
			जारी;

		ctx = apply_wqattrs_prepare(wq, wq->unbound_attrs);
		अगर (!ctx) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		list_add_tail(&ctx->list, &ctxs);
	पूर्ण

	list_क्रम_each_entry_safe(ctx, n, &ctxs, list) अणु
		अगर (!ret)
			apply_wqattrs_commit(ctx);
		apply_wqattrs_cleanup(ctx);
	पूर्ण

	वापस ret;
पूर्ण

/**
 *  workqueue_set_unbound_cpumask - Set the low-level unbound cpumask
 *  @cpumask: the cpumask to set
 *
 *  The low-level workqueues cpumask is a global cpumask that limits
 *  the affinity of all unbound workqueues.  This function check the @cpumask
 *  and apply it to all unbound workqueues and updates all pwqs of them.
 *
 *  Retun:	0	- Success
 *  		-EINVAL	- Invalid @cpumask
 *  		-ENOMEM	- Failed to allocate memory क्रम attrs or pwqs.
 */
पूर्णांक workqueue_set_unbound_cpumask(cpumask_var_t cpumask)
अणु
	पूर्णांक ret = -EINVAL;
	cpumask_var_t saved_cpumask;

	अगर (!zalloc_cpumask_var(&saved_cpumask, GFP_KERNEL))
		वापस -ENOMEM;

	/*
	 * Not excluding isolated cpus on purpose.
	 * If the user wishes to include them, we allow that.
	 */
	cpumask_and(cpumask, cpumask, cpu_possible_mask);
	अगर (!cpumask_empty(cpumask)) अणु
		apply_wqattrs_lock();

		/* save the old wq_unbound_cpumask. */
		cpumask_copy(saved_cpumask, wq_unbound_cpumask);

		/* update wq_unbound_cpumask at first and apply it to wqs. */
		cpumask_copy(wq_unbound_cpumask, cpumask);
		ret = workqueue_apply_unbound_cpumask();

		/* restore the wq_unbound_cpumask when failed. */
		अगर (ret < 0)
			cpumask_copy(wq_unbound_cpumask, saved_cpumask);

		apply_wqattrs_unlock();
	पूर्ण

	मुक्त_cpumask_var(saved_cpumask);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SYSFS
/*
 * Workqueues with WQ_SYSFS flag set is visible to userland via
 * /sys/bus/workqueue/devices/WQ_NAME.  All visible workqueues have the
 * following attributes.
 *
 *  per_cpu	RO bool	: whether the workqueue is per-cpu or unbound
 *  max_active	RW पूर्णांक	: maximum number of in-flight work items
 *
 * Unbound workqueues have the following extra attributes.
 *
 *  pool_ids	RO पूर्णांक	: the associated pool IDs क्रम each node
 *  nice	RW पूर्णांक	: nice value of the workers
 *  cpumask	RW mask	: biपंचांगask of allowed CPUs क्रम the workers
 *  numa	RW bool	: whether enable NUMA affinity
 */
काष्ठा wq_device अणु
	काष्ठा workqueue_काष्ठा		*wq;
	काष्ठा device			dev;
पूर्ण;

अटल काष्ठा workqueue_काष्ठा *dev_to_wq(काष्ठा device *dev)
अणु
	काष्ठा wq_device *wq_dev = container_of(dev, काष्ठा wq_device, dev);

	वापस wq_dev->wq;
पूर्ण

अटल sमाप_प्रकार per_cpu_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा workqueue_काष्ठा *wq = dev_to_wq(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", (bool)!(wq->flags & WQ_UNBOUND));
पूर्ण
अटल DEVICE_ATTR_RO(per_cpu);

अटल sमाप_प्रकार max_active_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा workqueue_काष्ठा *wq = dev_to_wq(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", wq->saved_max_active);
पूर्ण

अटल sमाप_प्रकार max_active_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा workqueue_काष्ठा *wq = dev_to_wq(dev);
	पूर्णांक val;

	अगर (माला_पूछो(buf, "%d", &val) != 1 || val <= 0)
		वापस -EINVAL;

	workqueue_set_max_active(wq, val);
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(max_active);

अटल काष्ठा attribute *wq_sysfs_attrs[] = अणु
	&dev_attr_per_cpu.attr,
	&dev_attr_max_active.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(wq_sysfs);

अटल sमाप_प्रकार wq_pool_ids_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा workqueue_काष्ठा *wq = dev_to_wq(dev);
	स्थिर अक्षर *delim = "";
	पूर्णांक node, written = 0;

	get_online_cpus();
	rcu_पढ़ो_lock();
	क्रम_each_node(node) अणु
		written += scnम_लिखो(buf + written, PAGE_SIZE - written,
				     "%s%d:%d", delim, node,
				     unbound_pwq_by_node(wq, node)->pool->id);
		delim = " ";
	पूर्ण
	written += scnम_लिखो(buf + written, PAGE_SIZE - written, "\n");
	rcu_पढ़ो_unlock();
	put_online_cpus();

	वापस written;
पूर्ण

अटल sमाप_प्रकार wq_nice_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा workqueue_काष्ठा *wq = dev_to_wq(dev);
	पूर्णांक written;

	mutex_lock(&wq->mutex);
	written = scnम_लिखो(buf, PAGE_SIZE, "%d\n", wq->unbound_attrs->nice);
	mutex_unlock(&wq->mutex);

	वापस written;
पूर्ण

/* prepare workqueue_attrs क्रम sysfs store operations */
अटल काष्ठा workqueue_attrs *wq_sysfs_prep_attrs(काष्ठा workqueue_काष्ठा *wq)
अणु
	काष्ठा workqueue_attrs *attrs;

	lockdep_निश्चित_held(&wq_pool_mutex);

	attrs = alloc_workqueue_attrs();
	अगर (!attrs)
		वापस शून्य;

	copy_workqueue_attrs(attrs, wq->unbound_attrs);
	वापस attrs;
पूर्ण

अटल sमाप_प्रकार wq_nice_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा workqueue_काष्ठा *wq = dev_to_wq(dev);
	काष्ठा workqueue_attrs *attrs;
	पूर्णांक ret = -ENOMEM;

	apply_wqattrs_lock();

	attrs = wq_sysfs_prep_attrs(wq);
	अगर (!attrs)
		जाओ out_unlock;

	अगर (माला_पूछो(buf, "%d", &attrs->nice) == 1 &&
	    attrs->nice >= MIN_NICE && attrs->nice <= MAX_NICE)
		ret = apply_workqueue_attrs_locked(wq, attrs);
	अन्यथा
		ret = -EINVAL;

out_unlock:
	apply_wqattrs_unlock();
	मुक्त_workqueue_attrs(attrs);
	वापस ret ?: count;
पूर्ण

अटल sमाप_प्रकार wq_cpumask_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा workqueue_काष्ठा *wq = dev_to_wq(dev);
	पूर्णांक written;

	mutex_lock(&wq->mutex);
	written = scnम_लिखो(buf, PAGE_SIZE, "%*pb\n",
			    cpumask_pr_args(wq->unbound_attrs->cpumask));
	mutex_unlock(&wq->mutex);
	वापस written;
पूर्ण

अटल sमाप_प्रकार wq_cpumask_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा workqueue_काष्ठा *wq = dev_to_wq(dev);
	काष्ठा workqueue_attrs *attrs;
	पूर्णांक ret = -ENOMEM;

	apply_wqattrs_lock();

	attrs = wq_sysfs_prep_attrs(wq);
	अगर (!attrs)
		जाओ out_unlock;

	ret = cpumask_parse(buf, attrs->cpumask);
	अगर (!ret)
		ret = apply_workqueue_attrs_locked(wq, attrs);

out_unlock:
	apply_wqattrs_unlock();
	मुक्त_workqueue_attrs(attrs);
	वापस ret ?: count;
पूर्ण

अटल sमाप_प्रकार wq_numa_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा workqueue_काष्ठा *wq = dev_to_wq(dev);
	पूर्णांक written;

	mutex_lock(&wq->mutex);
	written = scnम_लिखो(buf, PAGE_SIZE, "%d\n",
			    !wq->unbound_attrs->no_numa);
	mutex_unlock(&wq->mutex);

	वापस written;
पूर्ण

अटल sमाप_प्रकार wq_numa_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा workqueue_काष्ठा *wq = dev_to_wq(dev);
	काष्ठा workqueue_attrs *attrs;
	पूर्णांक v, ret = -ENOMEM;

	apply_wqattrs_lock();

	attrs = wq_sysfs_prep_attrs(wq);
	अगर (!attrs)
		जाओ out_unlock;

	ret = -EINVAL;
	अगर (माला_पूछो(buf, "%d", &v) == 1) अणु
		attrs->no_numa = !v;
		ret = apply_workqueue_attrs_locked(wq, attrs);
	पूर्ण

out_unlock:
	apply_wqattrs_unlock();
	मुक्त_workqueue_attrs(attrs);
	वापस ret ?: count;
पूर्ण

अटल काष्ठा device_attribute wq_sysfs_unbound_attrs[] = अणु
	__ATTR(pool_ids, 0444, wq_pool_ids_show, शून्य),
	__ATTR(nice, 0644, wq_nice_show, wq_nice_store),
	__ATTR(cpumask, 0644, wq_cpumask_show, wq_cpumask_store),
	__ATTR(numa, 0644, wq_numa_show, wq_numa_store),
	__ATTR_शून्य,
पूर्ण;

अटल काष्ठा bus_type wq_subsys = अणु
	.name				= "workqueue",
	.dev_groups			= wq_sysfs_groups,
पूर्ण;

अटल sमाप_प्रकार wq_unbound_cpumask_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक written;

	mutex_lock(&wq_pool_mutex);
	written = scnम_लिखो(buf, PAGE_SIZE, "%*pb\n",
			    cpumask_pr_args(wq_unbound_cpumask));
	mutex_unlock(&wq_pool_mutex);

	वापस written;
पूर्ण

अटल sमाप_प्रकार wq_unbound_cpumask_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	cpumask_var_t cpumask;
	पूर्णांक ret;

	अगर (!zalloc_cpumask_var(&cpumask, GFP_KERNEL))
		वापस -ENOMEM;

	ret = cpumask_parse(buf, cpumask);
	अगर (!ret)
		ret = workqueue_set_unbound_cpumask(cpumask);

	मुक्त_cpumask_var(cpumask);
	वापस ret ? ret : count;
पूर्ण

अटल काष्ठा device_attribute wq_sysfs_cpumask_attr =
	__ATTR(cpumask, 0644, wq_unbound_cpumask_show,
	       wq_unbound_cpumask_store);

अटल पूर्णांक __init wq_sysfs_init(व्योम)
अणु
	पूर्णांक err;

	err = subsys_भव_रेजिस्टर(&wq_subsys, शून्य);
	अगर (err)
		वापस err;

	वापस device_create_file(wq_subsys.dev_root, &wq_sysfs_cpumask_attr);
पूर्ण
core_initcall(wq_sysfs_init);

अटल व्योम wq_device_release(काष्ठा device *dev)
अणु
	काष्ठा wq_device *wq_dev = container_of(dev, काष्ठा wq_device, dev);

	kमुक्त(wq_dev);
पूर्ण

/**
 * workqueue_sysfs_रेजिस्टर - make a workqueue visible in sysfs
 * @wq: the workqueue to रेजिस्टर
 *
 * Expose @wq in sysfs under /sys/bus/workqueue/devices.
 * alloc_workqueue*() स्वतःmatically calls this function अगर WQ_SYSFS is set
 * which is the preferred method.
 *
 * Workqueue user should use this function directly अगरf it wants to apply
 * workqueue_attrs beक्रमe making the workqueue visible in sysfs; otherwise,
 * apply_workqueue_attrs() may race against userland updating the
 * attributes.
 *
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक workqueue_sysfs_रेजिस्टर(काष्ठा workqueue_काष्ठा *wq)
अणु
	काष्ठा wq_device *wq_dev;
	पूर्णांक ret;

	/*
	 * Adjusting max_active or creating new pwqs by applying
	 * attributes अवरोधs ordering guarantee.  Disallow exposing ordered
	 * workqueues.
	 */
	अगर (WARN_ON(wq->flags & __WQ_ORDERED_EXPLICIT))
		वापस -EINVAL;

	wq->wq_dev = wq_dev = kzalloc(माप(*wq_dev), GFP_KERNEL);
	अगर (!wq_dev)
		वापस -ENOMEM;

	wq_dev->wq = wq;
	wq_dev->dev.bus = &wq_subsys;
	wq_dev->dev.release = wq_device_release;
	dev_set_name(&wq_dev->dev, "%s", wq->name);

	/*
	 * unbound_attrs are created separately.  Suppress uevent until
	 * everything is पढ़ोy.
	 */
	dev_set_uevent_suppress(&wq_dev->dev, true);

	ret = device_रेजिस्टर(&wq_dev->dev);
	अगर (ret) अणु
		put_device(&wq_dev->dev);
		wq->wq_dev = शून्य;
		वापस ret;
	पूर्ण

	अगर (wq->flags & WQ_UNBOUND) अणु
		काष्ठा device_attribute *attr;

		क्रम (attr = wq_sysfs_unbound_attrs; attr->attr.name; attr++) अणु
			ret = device_create_file(&wq_dev->dev, attr);
			अगर (ret) अणु
				device_unरेजिस्टर(&wq_dev->dev);
				wq->wq_dev = शून्य;
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	dev_set_uevent_suppress(&wq_dev->dev, false);
	kobject_uevent(&wq_dev->dev.kobj, KOBJ_ADD);
	वापस 0;
पूर्ण

/**
 * workqueue_sysfs_unरेजिस्टर - unकरो workqueue_sysfs_रेजिस्टर()
 * @wq: the workqueue to unरेजिस्टर
 *
 * If @wq is रेजिस्टरed to sysfs by workqueue_sysfs_रेजिस्टर(), unरेजिस्टर.
 */
अटल व्योम workqueue_sysfs_unरेजिस्टर(काष्ठा workqueue_काष्ठा *wq)
अणु
	काष्ठा wq_device *wq_dev = wq->wq_dev;

	अगर (!wq->wq_dev)
		वापस;

	wq->wq_dev = शून्य;
	device_unरेजिस्टर(&wq_dev->dev);
पूर्ण
#अन्यथा	/* CONFIG_SYSFS */
अटल व्योम workqueue_sysfs_unरेजिस्टर(काष्ठा workqueue_काष्ठा *wq)	अणु पूर्ण
#पूर्ण_अगर	/* CONFIG_SYSFS */

/*
 * Workqueue watchकरोg.
 *
 * Stall may be caused by various bugs - missing WQ_MEM_RECLAIM, illegal
 * flush dependency, a concurrency managed work item which stays RUNNING
 * indefinitely.  Workqueue stalls can be very dअगरficult to debug as the
 * usual warning mechanisms करोn't trigger and पूर्णांकernal workqueue state is
 * largely opaque.
 *
 * Workqueue watchकरोg monitors all worker pools periodically and dumps
 * state अगर some pools failed to make क्रमward progress क्रम a जबतक where
 * क्रमward progress is defined as the first item on ->worklist changing.
 *
 * This mechanism is controlled through the kernel parameter
 * "workqueue.watchdog_thresh" which can be updated at runसमय through the
 * corresponding sysfs parameter file.
 */
#अगर_घोषित CONFIG_WQ_WATCHDOG

अटल अचिन्हित दीर्घ wq_watchकरोg_thresh = 30;
अटल काष्ठा समयr_list wq_watchकरोg_समयr;

अटल अचिन्हित दीर्घ wq_watchकरोg_touched = INITIAL_JIFFIES;
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, wq_watchकरोg_touched_cpu) = INITIAL_JIFFIES;

अटल व्योम wq_watchकरोg_reset_touched(व्योम)
अणु
	पूर्णांक cpu;

	wq_watchकरोg_touched = jअगरfies;
	क्रम_each_possible_cpu(cpu)
		per_cpu(wq_watchकरोg_touched_cpu, cpu) = jअगरfies;
पूर्ण

अटल व्योम wq_watchकरोg_समयr_fn(काष्ठा समयr_list *unused)
अणु
	अचिन्हित दीर्घ thresh = READ_ONCE(wq_watchकरोg_thresh) * HZ;
	bool lockup_detected = false;
	अचिन्हित दीर्घ now = jअगरfies;
	काष्ठा worker_pool *pool;
	पूर्णांक pi;

	अगर (!thresh)
		वापस;

	rcu_पढ़ो_lock();

	क्रम_each_pool(pool, pi) अणु
		अचिन्हित दीर्घ pool_ts, touched, ts;

		अगर (list_empty(&pool->worklist))
			जारी;

		/*
		 * If a भव machine is stopped by the host it can look to
		 * the watchकरोg like a stall.
		 */
		kvm_check_and_clear_guest_छोड़ोd();

		/* get the latest of pool and touched बारtamps */
		अगर (pool->cpu >= 0)
			touched = READ_ONCE(per_cpu(wq_watchकरोg_touched_cpu, pool->cpu));
		अन्यथा
			touched = READ_ONCE(wq_watchकरोg_touched);
		pool_ts = READ_ONCE(pool->watchकरोg_ts);

		अगर (समय_after(pool_ts, touched))
			ts = pool_ts;
		अन्यथा
			ts = touched;

		/* did we stall? */
		अगर (समय_after(now, ts + thresh)) अणु
			lockup_detected = true;
			pr_emerg("BUG: workqueue lockup - pool");
			pr_cont_pool_info(pool);
			pr_cont(" stuck for %us!\n",
				jअगरfies_to_msecs(now - pool_ts) / 1000);
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (lockup_detected)
		show_workqueue_state();

	wq_watchकरोg_reset_touched();
	mod_समयr(&wq_watchकरोg_समयr, jअगरfies + thresh);
पूर्ण

notrace व्योम wq_watchकरोg_touch(पूर्णांक cpu)
अणु
	अगर (cpu >= 0)
		per_cpu(wq_watchकरोg_touched_cpu, cpu) = jअगरfies;

	wq_watchकरोg_touched = jअगरfies;
पूर्ण

अटल व्योम wq_watchकरोg_set_thresh(अचिन्हित दीर्घ thresh)
अणु
	wq_watchकरोg_thresh = 0;
	del_समयr_sync(&wq_watchकरोg_समयr);

	अगर (thresh) अणु
		wq_watchकरोg_thresh = thresh;
		wq_watchकरोg_reset_touched();
		mod_समयr(&wq_watchकरोg_समयr, jअगरfies + thresh * HZ);
	पूर्ण
पूर्ण

अटल पूर्णांक wq_watchकरोg_param_set_thresh(स्थिर अक्षर *val,
					स्थिर काष्ठा kernel_param *kp)
अणु
	अचिन्हित दीर्घ thresh;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(val, 0, &thresh);
	अगर (ret)
		वापस ret;

	अगर (प्रणाली_wq)
		wq_watchकरोg_set_thresh(thresh);
	अन्यथा
		wq_watchकरोg_thresh = thresh;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops wq_watchकरोg_thresh_ops = अणु
	.set	= wq_watchकरोg_param_set_thresh,
	.get	= param_get_uदीर्घ,
पूर्ण;

module_param_cb(watchकरोg_thresh, &wq_watchकरोg_thresh_ops, &wq_watchकरोg_thresh,
		0644);

अटल व्योम wq_watchकरोg_init(व्योम)
अणु
	समयr_setup(&wq_watchकरोg_समयr, wq_watchकरोg_समयr_fn, TIMER_DEFERRABLE);
	wq_watchकरोg_set_thresh(wq_watchकरोg_thresh);
पूर्ण

#अन्यथा	/* CONFIG_WQ_WATCHDOG */

अटल अंतरभूत व्योम wq_watchकरोg_init(व्योम) अणु पूर्ण

#पूर्ण_अगर	/* CONFIG_WQ_WATCHDOG */

अटल व्योम __init wq_numa_init(व्योम)
अणु
	cpumask_var_t *tbl;
	पूर्णांक node, cpu;

	अगर (num_possible_nodes() <= 1)
		वापस;

	अगर (wq_disable_numa) अणु
		pr_info("workqueue: NUMA affinity support disabled\n");
		वापस;
	पूर्ण

	wq_update_unbound_numa_attrs_buf = alloc_workqueue_attrs();
	BUG_ON(!wq_update_unbound_numa_attrs_buf);

	/*
	 * We want masks of possible CPUs of each node which isn't पढ़ोily
	 * available.  Build one from cpu_to_node() which should have been
	 * fully initialized by now.
	 */
	tbl = kसुस्मृति(nr_node_ids, माप(tbl[0]), GFP_KERNEL);
	BUG_ON(!tbl);

	क्रम_each_node(node)
		BUG_ON(!zalloc_cpumask_var_node(&tbl[node], GFP_KERNEL,
				node_online(node) ? node : NUMA_NO_NODE));

	क्रम_each_possible_cpu(cpu) अणु
		node = cpu_to_node(cpu);
		अगर (WARN_ON(node == NUMA_NO_NODE)) अणु
			pr_warn("workqueue: NUMA node mapping not available for cpu%d, disabling NUMA support\n", cpu);
			/* happens अगरf arch is bonkers, let's just proceed */
			वापस;
		पूर्ण
		cpumask_set_cpu(cpu, tbl[node]);
	पूर्ण

	wq_numa_possible_cpumask = tbl;
	wq_numa_enabled = true;
पूर्ण

/**
 * workqueue_init_early - early init क्रम workqueue subप्रणाली
 *
 * This is the first half of two-staged workqueue subप्रणाली initialization
 * and invoked as soon as the bare basics - memory allocation, cpumasks and
 * idr are up.  It sets up all the data काष्ठाures and प्रणाली workqueues
 * and allows early boot code to create workqueues and queue/cancel work
 * items.  Actual work item execution starts only after kthपढ़ोs can be
 * created and scheduled right beक्रमe early initcalls.
 */
व्योम __init workqueue_init_early(व्योम)
अणु
	पूर्णांक std_nice[NR_STD_WORKER_POOLS] = अणु 0, HIGHPRI_NICE_LEVEL पूर्ण;
	पूर्णांक hk_flags = HK_FLAG_DOMAIN | HK_FLAG_WQ;
	पूर्णांक i, cpu;

	BUILD_BUG_ON(__alignof__(काष्ठा pool_workqueue) < __alignof__(दीर्घ दीर्घ));

	BUG_ON(!alloc_cpumask_var(&wq_unbound_cpumask, GFP_KERNEL));
	cpumask_copy(wq_unbound_cpumask, housekeeping_cpumask(hk_flags));

	pwq_cache = KMEM_CACHE(pool_workqueue, SLAB_PANIC);

	/* initialize CPU pools */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा worker_pool *pool;

		i = 0;
		क्रम_each_cpu_worker_pool(pool, cpu) अणु
			BUG_ON(init_worker_pool(pool));
			pool->cpu = cpu;
			cpumask_copy(pool->attrs->cpumask, cpumask_of(cpu));
			pool->attrs->nice = std_nice[i++];
			pool->node = cpu_to_node(cpu);

			/* alloc pool ID */
			mutex_lock(&wq_pool_mutex);
			BUG_ON(worker_pool_assign_id(pool));
			mutex_unlock(&wq_pool_mutex);
		पूर्ण
	पूर्ण

	/* create शेष unbound and ordered wq attrs */
	क्रम (i = 0; i < NR_STD_WORKER_POOLS; i++) अणु
		काष्ठा workqueue_attrs *attrs;

		BUG_ON(!(attrs = alloc_workqueue_attrs()));
		attrs->nice = std_nice[i];
		unbound_std_wq_attrs[i] = attrs;

		/*
		 * An ordered wq should have only one pwq as ordering is
		 * guaranteed by max_active which is enक्रमced by pwqs.
		 * Turn off NUMA so that dfl_pwq is used क्रम all nodes.
		 */
		BUG_ON(!(attrs = alloc_workqueue_attrs()));
		attrs->nice = std_nice[i];
		attrs->no_numa = true;
		ordered_wq_attrs[i] = attrs;
	पूर्ण

	प्रणाली_wq = alloc_workqueue("events", 0, 0);
	प्रणाली_highpri_wq = alloc_workqueue("events_highpri", WQ_HIGHPRI, 0);
	प्रणाली_दीर्घ_wq = alloc_workqueue("events_long", 0, 0);
	प्रणाली_unbound_wq = alloc_workqueue("events_unbound", WQ_UNBOUND,
					    WQ_UNBOUND_MAX_ACTIVE);
	प्रणाली_मुक्तzable_wq = alloc_workqueue("events_freezable",
					      WQ_FREEZABLE, 0);
	प्रणाली_घातer_efficient_wq = alloc_workqueue("events_power_efficient",
					      WQ_POWER_EFFICIENT, 0);
	प्रणाली_मुक्तzable_घातer_efficient_wq = alloc_workqueue("events_freezable_power_efficient",
					      WQ_FREEZABLE | WQ_POWER_EFFICIENT,
					      0);
	BUG_ON(!प्रणाली_wq || !प्रणाली_highpri_wq || !प्रणाली_दीर्घ_wq ||
	       !प्रणाली_unbound_wq || !प्रणाली_मुक्तzable_wq ||
	       !प्रणाली_घातer_efficient_wq ||
	       !प्रणाली_मुक्तzable_घातer_efficient_wq);
पूर्ण

/**
 * workqueue_init - bring workqueue subप्रणाली fully online
 *
 * This is the latter half of two-staged workqueue subप्रणाली initialization
 * and invoked as soon as kthपढ़ोs can be created and scheduled.
 * Workqueues have been created and work items queued on them, but there
 * are no kworkers executing the work items yet.  Populate the worker pools
 * with the initial workers and enable future kworker creations.
 */
व्योम __init workqueue_init(व्योम)
अणु
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा worker_pool *pool;
	पूर्णांक cpu, bkt;

	/*
	 * It'd be simpler to initialize NUMA in workqueue_init_early() but
	 * CPU to node mapping may not be available that early on some
	 * archs such as घातer and arm64.  As per-cpu pools created
	 * previously could be missing node hपूर्णांक and unbound pools NUMA
	 * affinity, fix them up.
	 *
	 * Also, जबतक iterating workqueues, create rescuers अगर requested.
	 */
	wq_numa_init();

	mutex_lock(&wq_pool_mutex);

	क्रम_each_possible_cpu(cpu) अणु
		क्रम_each_cpu_worker_pool(pool, cpu) अणु
			pool->node = cpu_to_node(cpu);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(wq, &workqueues, list) अणु
		wq_update_unbound_numa(wq, smp_processor_id(), true);
		WARN(init_rescuer(wq),
		     "workqueue: failed to create early rescuer for %s",
		     wq->name);
	पूर्ण

	mutex_unlock(&wq_pool_mutex);

	/* create the initial workers */
	क्रम_each_online_cpu(cpu) अणु
		क्रम_each_cpu_worker_pool(pool, cpu) अणु
			pool->flags &= ~POOL_DISASSOCIATED;
			BUG_ON(!create_worker(pool));
		पूर्ण
	पूर्ण

	hash_क्रम_each(unbound_pool_hash, bkt, pool, hash_node)
		BUG_ON(!create_worker(pool));

	wq_online = true;
	wq_watchकरोg_init();
पूर्ण
