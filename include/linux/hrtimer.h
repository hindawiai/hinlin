<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  hrसमयrs - High-resolution kernel समयrs
 *
 *   Copyright(C) 2005, Thomas Gleixner <tglx@linutronix.de>
 *   Copyright(C) 2005, Red Hat, Inc., Ingo Molnar
 *
 *  data type definitions, declarations, prototypes
 *
 *  Started by: Thomas Gleixner and Ingo Molnar
 */
#अगर_अघोषित _LINUX_HRTIMER_H
#घोषणा _LINUX_HRTIMER_H

#समावेश <linux/hrसमयr_defs.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/percpu.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/समयrqueue.h>

काष्ठा hrसमयr_घड़ी_base;
काष्ठा hrसमयr_cpu_base;

/*
 * Mode arguments of xxx_hrसमयr functions:
 *
 * HRTIMER_MODE_ABS		- Time value is असलolute
 * HRTIMER_MODE_REL		- Time value is relative to now
 * HRTIMER_MODE_PINNED		- Timer is bound to CPU (is only considered
 *				  when starting the समयr)
 * HRTIMER_MODE_SOFT		- Timer callback function will be executed in
 *				  soft irq context
 * HRTIMER_MODE_HARD		- Timer callback function will be executed in
 *				  hard irq context even on PREEMPT_RT.
 */
क्रमागत hrसमयr_mode अणु
	HRTIMER_MODE_ABS	= 0x00,
	HRTIMER_MODE_REL	= 0x01,
	HRTIMER_MODE_PINNED	= 0x02,
	HRTIMER_MODE_SOFT	= 0x04,
	HRTIMER_MODE_HARD	= 0x08,

	HRTIMER_MODE_ABS_PINNED = HRTIMER_MODE_ABS | HRTIMER_MODE_PINNED,
	HRTIMER_MODE_REL_PINNED = HRTIMER_MODE_REL | HRTIMER_MODE_PINNED,

	HRTIMER_MODE_ABS_SOFT	= HRTIMER_MODE_ABS | HRTIMER_MODE_SOFT,
	HRTIMER_MODE_REL_SOFT	= HRTIMER_MODE_REL | HRTIMER_MODE_SOFT,

	HRTIMER_MODE_ABS_PINNED_SOFT = HRTIMER_MODE_ABS_PINNED | HRTIMER_MODE_SOFT,
	HRTIMER_MODE_REL_PINNED_SOFT = HRTIMER_MODE_REL_PINNED | HRTIMER_MODE_SOFT,

	HRTIMER_MODE_ABS_HARD	= HRTIMER_MODE_ABS | HRTIMER_MODE_HARD,
	HRTIMER_MODE_REL_HARD	= HRTIMER_MODE_REL | HRTIMER_MODE_HARD,

	HRTIMER_MODE_ABS_PINNED_HARD = HRTIMER_MODE_ABS_PINNED | HRTIMER_MODE_HARD,
	HRTIMER_MODE_REL_PINNED_HARD = HRTIMER_MODE_REL_PINNED | HRTIMER_MODE_HARD,
पूर्ण;

/*
 * Return values क्रम the callback function
 */
क्रमागत hrसमयr_restart अणु
	HRTIMER_NORESTART,	/* Timer is not restarted */
	HRTIMER_RESTART,	/* Timer must be restarted */
पूर्ण;

/*
 * Values to track state of the समयr
 *
 * Possible states:
 *
 * 0x00		inactive
 * 0x01		enqueued पूर्णांकo rbtree
 *
 * The callback state is not part of the समयr->state because clearing it would
 * mean touching the समयr after the callback, this makes it impossible to मुक्त
 * the समयr from the callback function.
 *
 * Thereक्रमe we track the callback state in:
 *
 *	समयr->base->cpu_base->running == समयr
 *
 * On SMP it is possible to have a "callback function running and enqueued"
 * status. It happens क्रम example when a posix समयr expired and the callback
 * queued a संकेत. Between dropping the lock which protects the posix समयr
 * and reacquiring the base lock of the hrसमयr, another CPU can deliver the
 * संकेत and rearm the समयr.
 *
 * All state transitions are रक्षित by cpu_base->lock.
 */
#घोषणा HRTIMER_STATE_INACTIVE	0x00
#घोषणा HRTIMER_STATE_ENQUEUED	0x01

/**
 * काष्ठा hrसमयr - the basic hrसमयr काष्ठाure
 * @node:	समयrqueue node, which also manages node.expires,
 *		the असलolute expiry समय in the hrसमयrs पूर्णांकernal
 *		representation. The समय is related to the घड़ी on
 *		which the समयr is based. Is setup by adding
 *		slack to the _softexpires value. For non range समयrs
 *		identical to _softexpires.
 * @_softexpires: the असलolute earliest expiry समय of the hrसमयr.
 *		The समय which was given as expiry समय when the समयr
 *		was armed.
 * @function:	समयr expiry callback function
 * @base:	poपूर्णांकer to the समयr base (per cpu and per घड़ी)
 * @state:	state inक्रमmation (See bit values above)
 * @is_rel:	Set अगर the समयr was armed relative
 * @is_soft:	Set अगर hrसमयr will be expired in soft पूर्णांकerrupt context.
 * @is_hard:	Set अगर hrसमयr will be expired in hard पूर्णांकerrupt context
 *		even on RT.
 *
 * The hrसमयr काष्ठाure must be initialized by hrसमयr_init()
 */
काष्ठा hrसमयr अणु
	काष्ठा समयrqueue_node		node;
	kसमय_प्रकार				_softexpires;
	क्रमागत hrसमयr_restart		(*function)(काष्ठा hrसमयr *);
	काष्ठा hrसमयr_घड़ी_base	*base;
	u8				state;
	u8				is_rel;
	u8				is_soft;
	u8				is_hard;
पूर्ण;

/**
 * काष्ठा hrसमयr_sleeper - simple sleeper काष्ठाure
 * @समयr:	embedded समयr काष्ठाure
 * @task:	task to wake up
 *
 * task is set to शून्य, when the समयr expires.
 */
काष्ठा hrसमयr_sleeper अणु
	काष्ठा hrसमयr समयr;
	काष्ठा task_काष्ठा *task;
पूर्ण;

#अगर_घोषित CONFIG_64BIT
# define __hrसमयr_घड़ी_base_align	____cacheline_aligned
#अन्यथा
# define __hrसमयr_घड़ी_base_align
#पूर्ण_अगर

/**
 * काष्ठा hrसमयr_घड़ी_base - the समयr base क्रम a specअगरic घड़ी
 * @cpu_base:		per cpu घड़ी base
 * @index:		घड़ी type index क्रम per_cpu support when moving a
 *			समयr to a base on another cpu.
 * @घड़ीid:		घड़ी id क्रम per_cpu support
 * @seq:		seqcount around __run_hrसमयr
 * @running:		poपूर्णांकer to the currently running hrसमयr
 * @active:		red black tree root node क्रम the active समयrs
 * @get_समय:		function to retrieve the current समय of the घड़ी
 * @offset:		offset of this घड़ी to the monotonic base
 */
काष्ठा hrसमयr_घड़ी_base अणु
	काष्ठा hrसमयr_cpu_base	*cpu_base;
	अचिन्हित पूर्णांक		index;
	घड़ीid_t		घड़ीid;
	seqcount_raw_spinlock_t	seq;
	काष्ठा hrसमयr		*running;
	काष्ठा समयrqueue_head	active;
	kसमय_प्रकार			(*get_समय)(व्योम);
	kसमय_प्रकार			offset;
पूर्ण __hrसमयr_घड़ी_base_align;

क्रमागत  hrसमयr_base_type अणु
	HRTIMER_BASE_MONOTONIC,
	HRTIMER_BASE_REALTIME,
	HRTIMER_BASE_BOOTTIME,
	HRTIMER_BASE_TAI,
	HRTIMER_BASE_MONOTONIC_SOFT,
	HRTIMER_BASE_REALTIME_SOFT,
	HRTIMER_BASE_BOOTTIME_SOFT,
	HRTIMER_BASE_TAI_SOFT,
	HRTIMER_MAX_CLOCK_BASES,
पूर्ण;

/**
 * काष्ठा hrसमयr_cpu_base - the per cpu घड़ी bases
 * @lock:		lock protecting the base and associated घड़ी bases
 *			and समयrs
 * @cpu:		cpu number
 * @active_bases:	Bitfield to mark bases with active समयrs
 * @घड़ी_was_set_seq:	Sequence counter of घड़ी was set events
 * @hres_active:	State of high resolution mode
 * @in_hrtirq:		hrसमयr_पूर्णांकerrupt() is currently executing
 * @hang_detected:	The last hrसमयr पूर्णांकerrupt detected a hang
 * @softirq_activated:	displays, अगर the softirq is उठाओd - update of softirq
 *			related settings is not required then.
 * @nr_events:		Total number of hrसमयr पूर्णांकerrupt events
 * @nr_retries:		Total number of hrसमयr पूर्णांकerrupt retries
 * @nr_hangs:		Total number of hrसमयr पूर्णांकerrupt hangs
 * @max_hang_समय:	Maximum समय spent in hrसमयr_पूर्णांकerrupt
 * @softirq_expiry_lock: Lock which is taken जबतक softirq based hrसमयr are
 *			 expired
 * @समयr_रुकोers:	A hrसमयr_cancel() invocation रुकोs क्रम the समयr
 *			callback to finish.
 * @expires_next:	असलolute समय of the next event, is required क्रम remote
 *			hrसमयr enqueue; it is the total first expiry समय (hard
 *			and soft hrसमयr are taken पूर्णांकo account)
 * @next_समयr:		Poपूर्णांकer to the first expiring समयr
 * @softirq_expires_next: Time to check, अगर soft queues needs also to be expired
 * @softirq_next_समयr: Poपूर्णांकer to the first expiring softirq based समयr
 * @घड़ी_base:		array of घड़ी bases क्रम this cpu
 *
 * Note: next_समयr is just an optimization क्रम __हटाओ_hrसमयr().
 *	 Do not dereference the poपूर्णांकer because it is not reliable on
 *	 cross cpu removals.
 */
काष्ठा hrसमयr_cpu_base अणु
	raw_spinlock_t			lock;
	अचिन्हित पूर्णांक			cpu;
	अचिन्हित पूर्णांक			active_bases;
	अचिन्हित पूर्णांक			घड़ी_was_set_seq;
	अचिन्हित पूर्णांक			hres_active		: 1,
					in_hrtirq		: 1,
					hang_detected		: 1,
					softirq_activated       : 1;
#अगर_घोषित CONFIG_HIGH_RES_TIMERS
	अचिन्हित पूर्णांक			nr_events;
	अचिन्हित लघु			nr_retries;
	अचिन्हित लघु			nr_hangs;
	अचिन्हित पूर्णांक			max_hang_समय;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PREEMPT_RT
	spinlock_t			softirq_expiry_lock;
	atomic_t			समयr_रुकोers;
#पूर्ण_अगर
	kसमय_प्रकार				expires_next;
	काष्ठा hrसमयr			*next_समयr;
	kसमय_प्रकार				softirq_expires_next;
	काष्ठा hrसमयr			*softirq_next_समयr;
	काष्ठा hrसमयr_घड़ी_base	घड़ी_base[HRTIMER_MAX_CLOCK_BASES];
पूर्ण ____cacheline_aligned;

अटल अंतरभूत व्योम hrसमयr_set_expires(काष्ठा hrसमयr *समयr, kसमय_प्रकार समय)
अणु
	समयr->node.expires = समय;
	समयr->_softexpires = समय;
पूर्ण

अटल अंतरभूत व्योम hrसमयr_set_expires_range(काष्ठा hrसमयr *समयr, kसमय_प्रकार समय, kसमय_प्रकार delta)
अणु
	समयr->_softexpires = समय;
	समयr->node.expires = kसमय_add_safe(समय, delta);
पूर्ण

अटल अंतरभूत व्योम hrसमयr_set_expires_range_ns(काष्ठा hrसमयr *समयr, kसमय_प्रकार समय, u64 delta)
अणु
	समयr->_softexpires = समय;
	समयr->node.expires = kसमय_add_safe(समय, ns_to_kसमय(delta));
पूर्ण

अटल अंतरभूत व्योम hrसमयr_set_expires_tv64(काष्ठा hrसमयr *समयr, s64 tv64)
अणु
	समयr->node.expires = tv64;
	समयr->_softexpires = tv64;
पूर्ण

अटल अंतरभूत व्योम hrसमयr_add_expires(काष्ठा hrसमयr *समयr, kसमय_प्रकार समय)
अणु
	समयr->node.expires = kसमय_add_safe(समयr->node.expires, समय);
	समयr->_softexpires = kसमय_add_safe(समयr->_softexpires, समय);
पूर्ण

अटल अंतरभूत व्योम hrसमयr_add_expires_ns(काष्ठा hrसमयr *समयr, u64 ns)
अणु
	समयr->node.expires = kसमय_add_ns(समयr->node.expires, ns);
	समयr->_softexpires = kसमय_add_ns(समयr->_softexpires, ns);
पूर्ण

अटल अंतरभूत kसमय_प्रकार hrसमयr_get_expires(स्थिर काष्ठा hrसमयr *समयr)
अणु
	वापस समयr->node.expires;
पूर्ण

अटल अंतरभूत kसमय_प्रकार hrसमयr_get_softexpires(स्थिर काष्ठा hrसमयr *समयr)
अणु
	वापस समयr->_softexpires;
पूर्ण

अटल अंतरभूत s64 hrसमयr_get_expires_tv64(स्थिर काष्ठा hrसमयr *समयr)
अणु
	वापस समयr->node.expires;
पूर्ण
अटल अंतरभूत s64 hrसमयr_get_softexpires_tv64(स्थिर काष्ठा hrसमयr *समयr)
अणु
	वापस समयr->_softexpires;
पूर्ण

अटल अंतरभूत s64 hrसमयr_get_expires_ns(स्थिर काष्ठा hrसमयr *समयr)
अणु
	वापस kसमय_प्रकारo_ns(समयr->node.expires);
पूर्ण

अटल अंतरभूत kसमय_प्रकार hrसमयr_expires_reमुख्यing(स्थिर काष्ठा hrसमयr *समयr)
अणु
	वापस kसमय_sub(समयr->node.expires, समयr->base->get_समय());
पूर्ण

अटल अंतरभूत kसमय_प्रकार hrसमयr_cb_get_समय(काष्ठा hrसमयr *समयr)
अणु
	वापस समयr->base->get_समय();
पूर्ण

अटल अंतरभूत पूर्णांक hrसमयr_is_hres_active(काष्ठा hrसमयr *समयr)
अणु
	वापस IS_ENABLED(CONFIG_HIGH_RES_TIMERS) ?
		समयr->base->cpu_base->hres_active : 0;
पूर्ण

#अगर_घोषित CONFIG_HIGH_RES_TIMERS
काष्ठा घड़ी_event_device;

बाह्य व्योम hrसमयr_पूर्णांकerrupt(काष्ठा घड़ी_event_device *dev);

बाह्य व्योम घड़ी_was_set_delayed(व्योम);

बाह्य अचिन्हित पूर्णांक hrसमयr_resolution;

#अन्यथा

#घोषणा hrसमयr_resolution	(अचिन्हित पूर्णांक)LOW_RES_NSEC

अटल अंतरभूत व्योम घड़ी_was_set_delayed(व्योम) अणु पूर्ण

#पूर्ण_अगर

अटल अंतरभूत kसमय_प्रकार
__hrसमयr_expires_reमुख्यing_adjusted(स्थिर काष्ठा hrसमयr *समयr, kसमय_प्रकार now)
अणु
	kसमय_प्रकार rem = kसमय_sub(समयr->node.expires, now);

	/*
	 * Adjust relative समयrs क्रम the extra we added in
	 * hrसमयr_start_range_ns() to prevent लघु समयouts.
	 */
	अगर (IS_ENABLED(CONFIG_TIME_LOW_RES) && समयr->is_rel)
		rem -= hrसमयr_resolution;
	वापस rem;
पूर्ण

अटल अंतरभूत kसमय_प्रकार
hrसमयr_expires_reमुख्यing_adjusted(स्थिर काष्ठा hrसमयr *समयr)
अणु
	वापस __hrसमयr_expires_reमुख्यing_adjusted(समयr,
						    समयr->base->get_समय());
पूर्ण

बाह्य व्योम घड़ी_was_set(व्योम);
#अगर_घोषित CONFIG_TIMERFD
बाह्य व्योम समयrfd_घड़ी_was_set(व्योम);
#अन्यथा
अटल अंतरभूत व्योम समयrfd_घड़ी_was_set(व्योम) अणु पूर्ण
#पूर्ण_अगर
बाह्य व्योम hrसमयrs_resume(व्योम);

DECLARE_PER_CPU(काष्ठा tick_device, tick_cpu_device);

#अगर_घोषित CONFIG_PREEMPT_RT
व्योम hrसमयr_cancel_रुको_running(स्थिर काष्ठा hrसमयr *समयr);
#अन्यथा
अटल अंतरभूत व्योम hrसमयr_cancel_रुको_running(काष्ठा hrसमयr *समयr)
अणु
	cpu_relax();
पूर्ण
#पूर्ण_अगर

/* Exported समयr functions: */

/* Initialize समयrs: */
बाह्य व्योम hrसमयr_init(काष्ठा hrसमयr *समयr, घड़ीid_t which_घड़ी,
			 क्रमागत hrसमयr_mode mode);
बाह्य व्योम hrसमयr_init_sleeper(काष्ठा hrसमयr_sleeper *sl, घड़ीid_t घड़ी_id,
				 क्रमागत hrसमयr_mode mode);

#अगर_घोषित CONFIG_DEBUG_OBJECTS_TIMERS
बाह्य व्योम hrसमयr_init_on_stack(काष्ठा hrसमयr *समयr, घड़ीid_t which_घड़ी,
				  क्रमागत hrसमयr_mode mode);
बाह्य व्योम hrसमयr_init_sleeper_on_stack(काष्ठा hrसमयr_sleeper *sl,
					  घड़ीid_t घड़ी_id,
					  क्रमागत hrसमयr_mode mode);

बाह्य व्योम destroy_hrसमयr_on_stack(काष्ठा hrसमयr *समयr);
#अन्यथा
अटल अंतरभूत व्योम hrसमयr_init_on_stack(काष्ठा hrसमयr *समयr,
					 घड़ीid_t which_घड़ी,
					 क्रमागत hrसमयr_mode mode)
अणु
	hrसमयr_init(समयr, which_घड़ी, mode);
पूर्ण

अटल अंतरभूत व्योम hrसमयr_init_sleeper_on_stack(काष्ठा hrसमयr_sleeper *sl,
						 घड़ीid_t घड़ी_id,
						 क्रमागत hrसमयr_mode mode)
अणु
	hrसमयr_init_sleeper(sl, घड़ी_id, mode);
पूर्ण

अटल अंतरभूत व्योम destroy_hrसमयr_on_stack(काष्ठा hrसमयr *समयr) अणु पूर्ण
#पूर्ण_अगर

/* Basic समयr operations: */
बाह्य व्योम hrसमयr_start_range_ns(काष्ठा hrसमयr *समयr, kसमय_प्रकार tim,
				   u64 range_ns, स्थिर क्रमागत hrसमयr_mode mode);

/**
 * hrसमयr_start - (re)start an hrसमयr
 * @समयr:	the समयr to be added
 * @tim:	expiry समय
 * @mode:	समयr mode: असलolute (HRTIMER_MODE_ABS) or
 *		relative (HRTIMER_MODE_REL), and pinned (HRTIMER_MODE_PINNED);
 *		softirq based mode is considered क्रम debug purpose only!
 */
अटल अंतरभूत व्योम hrसमयr_start(काष्ठा hrसमयr *समयr, kसमय_प्रकार tim,
				 स्थिर क्रमागत hrसमयr_mode mode)
अणु
	hrसमयr_start_range_ns(समयr, tim, 0, mode);
पूर्ण

बाह्य पूर्णांक hrसमयr_cancel(काष्ठा hrसमयr *समयr);
बाह्य पूर्णांक hrसमयr_try_to_cancel(काष्ठा hrसमयr *समयr);

अटल अंतरभूत व्योम hrसमयr_start_expires(काष्ठा hrसमयr *समयr,
					 क्रमागत hrसमयr_mode mode)
अणु
	u64 delta;
	kसमय_प्रकार soft, hard;
	soft = hrसमयr_get_softexpires(समयr);
	hard = hrसमयr_get_expires(समयr);
	delta = kसमय_प्रकारo_ns(kसमय_sub(hard, soft));
	hrसमयr_start_range_ns(समयr, soft, delta, mode);
पूर्ण

व्योम hrसमयr_sleeper_start_expires(काष्ठा hrसमयr_sleeper *sl,
				   क्रमागत hrसमयr_mode mode);

अटल अंतरभूत व्योम hrसमयr_restart(काष्ठा hrसमयr *समयr)
अणु
	hrसमयr_start_expires(समयr, HRTIMER_MODE_ABS);
पूर्ण

/* Query समयrs: */
बाह्य kसमय_प्रकार __hrसमयr_get_reमुख्यing(स्थिर काष्ठा hrसमयr *समयr, bool adjust);

/**
 * hrसमयr_get_reमुख्यing - get reमुख्यing समय क्रम the समयr
 * @समयr:	the समयr to पढ़ो
 */
अटल अंतरभूत kसमय_प्रकार hrसमयr_get_reमुख्यing(स्थिर काष्ठा hrसमयr *समयr)
अणु
	वापस __hrसमयr_get_reमुख्यing(समयr, false);
पूर्ण

बाह्य u64 hrसमयr_get_next_event(व्योम);
बाह्य u64 hrसमयr_next_event_without(स्थिर काष्ठा hrसमयr *exclude);

बाह्य bool hrसमयr_active(स्थिर काष्ठा hrसमयr *समयr);

/**
 * hrसमयr_is_queued - check, whether the समयr is on one of the queues
 * @समयr:	Timer to check
 *
 * Returns: True अगर the समयr is queued, false otherwise
 *
 * The function can be used lockless, but it gives only a current snapshot.
 */
अटल अंतरभूत bool hrसमयr_is_queued(काष्ठा hrसमयr *समयr)
अणु
	/* The READ_ONCE pairs with the update functions of समयr->state */
	वापस !!(READ_ONCE(समयr->state) & HRTIMER_STATE_ENQUEUED);
पूर्ण

/*
 * Helper function to check, whether the समयr is running the callback
 * function
 */
अटल अंतरभूत पूर्णांक hrसमयr_callback_running(काष्ठा hrसमयr *समयr)
अणु
	वापस समयr->base->running == समयr;
पूर्ण

/* Forward a hrसमयr so it expires after now: */
बाह्य u64
hrसमयr_क्रमward(काष्ठा hrसमयr *समयr, kसमय_प्रकार now, kसमय_प्रकार पूर्णांकerval);

/**
 * hrसमयr_क्रमward_now - क्रमward the समयr expiry so it expires after now
 * @समयr:	hrसमयr to क्रमward
 * @पूर्णांकerval:	the पूर्णांकerval to क्रमward
 *
 * Forward the समयr expiry so it will expire after the current समय
 * of the hrसमयr घड़ी base. Returns the number of overruns.
 *
 * Can be safely called from the callback function of @समयr. If
 * called from other contexts @समयr must neither be enqueued nor
 * running the callback and the caller needs to take care of
 * serialization.
 *
 * Note: This only updates the समयr expiry value and करोes not requeue
 * the समयr.
 */
अटल अंतरभूत u64 hrसमयr_क्रमward_now(काष्ठा hrसमयr *समयr,
				      kसमय_प्रकार पूर्णांकerval)
अणु
	वापस hrसमयr_क्रमward(समयr, समयr->base->get_समय(), पूर्णांकerval);
पूर्ण

/* Precise sleep: */

बाह्य पूर्णांक nanosleep_copyout(काष्ठा restart_block *, काष्ठा बारpec64 *);
बाह्य दीर्घ hrसमयr_nanosleep(kसमय_प्रकार rqtp, स्थिर क्रमागत hrसमयr_mode mode,
			      स्थिर घड़ीid_t घड़ीid);

बाह्य पूर्णांक schedule_hrसमयout_range(kसमय_प्रकार *expires, u64 delta,
				    स्थिर क्रमागत hrसमयr_mode mode);
बाह्य पूर्णांक schedule_hrसमयout_range_घड़ी(kसमय_प्रकार *expires,
					  u64 delta,
					  स्थिर क्रमागत hrसमयr_mode mode,
					  घड़ीid_t घड़ी_id);
बाह्य पूर्णांक schedule_hrसमयout(kसमय_प्रकार *expires, स्थिर क्रमागत hrसमयr_mode mode);

/* Soft पूर्णांकerrupt function to run the hrसमयr queues: */
बाह्य व्योम hrसमयr_run_queues(व्योम);

/* Bootup initialization: */
बाह्य व्योम __init hrसमयrs_init(व्योम);

/* Show pending समयrs: */
बाह्य व्योम sysrq_समयr_list_show(व्योम);

पूर्णांक hrसमयrs_prepare_cpu(अचिन्हित पूर्णांक cpu);
#अगर_घोषित CONFIG_HOTPLUG_CPU
पूर्णांक hrसमयrs_dead_cpu(अचिन्हित पूर्णांक cpu);
#अन्यथा
#घोषणा hrसमयrs_dead_cpu	शून्य
#पूर्ण_अगर

#पूर्ण_अगर
