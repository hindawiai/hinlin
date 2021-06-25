<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright(C) 2005-2006, Thomas Gleixner <tglx@linutronix.de>
 *  Copyright(C) 2005-2007, Red Hat, Inc., Ingo Molnar
 *  Copyright(C) 2006-2007  Timesys Corp., Thomas Gleixner
 *
 *  High-resolution kernel समयrs
 *
 *  In contrast to the low-resolution समयout API, aka समयr wheel,
 *  hrसमयrs provide finer resolution and accuracy depending on प्रणाली
 *  configuration and capabilities.
 *
 *  Started by: Thomas Gleixner and Ingo Molnar
 *
 *  Credits:
 *	Based on the original समयr wheel code
 *
 *	Help, testing, suggestions, bugfixes, improvements were
 *	provided by:
 *
 *	George Anzinger, Andrew Morton, Steven Rostedt, Roman Zippel
 *	et. al.
 */

#समावेश <linux/cpu.h>
#समावेश <linux/export.h>
#समावेश <linux/percpu.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/tick.h>
#समावेश <linux/err.h>
#समावेश <linux/debugobjects.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/sysctl.h>
#समावेश <linux/sched/rt.h>
#समावेश <linux/sched/deadline.h>
#समावेश <linux/sched/nohz.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/समयr.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/compat.h>

#समावेश <linux/uaccess.h>

#समावेश <trace/events/समयr.h>

#समावेश "tick-internal.h"

/*
 * Masks क्रम selecting the soft and hard context समयrs from
 * cpu_base->active
 */
#घोषणा MASK_SHIFT		(HRTIMER_BASE_MONOTONIC_SOFT)
#घोषणा HRTIMER_ACTIVE_HARD	((1U << MASK_SHIFT) - 1)
#घोषणा HRTIMER_ACTIVE_SOFT	(HRTIMER_ACTIVE_HARD << MASK_SHIFT)
#घोषणा HRTIMER_ACTIVE_ALL	(HRTIMER_ACTIVE_SOFT | HRTIMER_ACTIVE_HARD)

/*
 * The समयr bases:
 *
 * There are more घड़ीids than hrसमयr bases. Thus, we index
 * पूर्णांकo the समयr bases by the hrसमयr_base_type क्रमागत. When trying
 * to reach a base using a घड़ीid, hrसमयr_घड़ीid_to_base()
 * is used to convert from घड़ीid to the proper hrसमयr_base_type.
 */
DEFINE_PER_CPU(काष्ठा hrसमयr_cpu_base, hrसमयr_bases) =
अणु
	.lock = __RAW_SPIN_LOCK_UNLOCKED(hrसमयr_bases.lock),
	.घड़ी_base =
	अणु
		अणु
			.index = HRTIMER_BASE_MONOTONIC,
			.घड़ीid = CLOCK_MONOTONIC,
			.get_समय = &kसमय_get,
		पूर्ण,
		अणु
			.index = HRTIMER_BASE_REALTIME,
			.घड़ीid = CLOCK_REALTIME,
			.get_समय = &kसमय_get_real,
		पूर्ण,
		अणु
			.index = HRTIMER_BASE_BOOTTIME,
			.घड़ीid = CLOCK_BOOTTIME,
			.get_समय = &kसमय_get_bootसमय,
		पूर्ण,
		अणु
			.index = HRTIMER_BASE_TAI,
			.घड़ीid = CLOCK_TAI,
			.get_समय = &kसमय_get_घड़ीtai,
		पूर्ण,
		अणु
			.index = HRTIMER_BASE_MONOTONIC_SOFT,
			.घड़ीid = CLOCK_MONOTONIC,
			.get_समय = &kसमय_get,
		पूर्ण,
		अणु
			.index = HRTIMER_BASE_REALTIME_SOFT,
			.घड़ीid = CLOCK_REALTIME,
			.get_समय = &kसमय_get_real,
		पूर्ण,
		अणु
			.index = HRTIMER_BASE_BOOTTIME_SOFT,
			.घड़ीid = CLOCK_BOOTTIME,
			.get_समय = &kसमय_get_bootसमय,
		पूर्ण,
		अणु
			.index = HRTIMER_BASE_TAI_SOFT,
			.घड़ीid = CLOCK_TAI,
			.get_समय = &kसमय_get_घड़ीtai,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर पूर्णांक hrसमयr_घड़ी_प्रकारo_base_table[MAX_CLOCKS] = अणु
	/* Make sure we catch unsupported घड़ीids */
	[0 ... MAX_CLOCKS - 1]	= HRTIMER_MAX_CLOCK_BASES,

	[CLOCK_REALTIME]	= HRTIMER_BASE_REALTIME,
	[CLOCK_MONOTONIC]	= HRTIMER_BASE_MONOTONIC,
	[CLOCK_BOOTTIME]	= HRTIMER_BASE_BOOTTIME,
	[CLOCK_TAI]		= HRTIMER_BASE_TAI,
पूर्ण;

/*
 * Functions and macros which are dअगरferent क्रम UP/SMP प्रणालीs are kept in a
 * single place
 */
#अगर_घोषित CONFIG_SMP

/*
 * We require the migration_base क्रम lock_hrसमयr_base()/चयन_hrसमयr_base()
 * such that hrसमयr_callback_running() can unconditionally dereference
 * समयr->base->cpu_base
 */
अटल काष्ठा hrसमयr_cpu_base migration_cpu_base = अणु
	.घड़ी_base = अणु अणु
		.cpu_base = &migration_cpu_base,
		.seq      = SEQCNT_RAW_SPINLOCK_ZERO(migration_cpu_base.seq,
						     &migration_cpu_base.lock),
	पूर्ण, पूर्ण,
पूर्ण;

#घोषणा migration_base	migration_cpu_base.घड़ी_base[0]

अटल अंतरभूत bool is_migration_base(काष्ठा hrसमयr_घड़ी_base *base)
अणु
	वापस base == &migration_base;
पूर्ण

/*
 * We are using hashed locking: holding per_cpu(hrसमयr_bases)[n].lock
 * means that all समयrs which are tied to this base via समयr->base are
 * locked, and the base itself is locked too.
 *
 * So __run_समयrs/migrate_समयrs can safely modअगरy all समयrs which could
 * be found on the lists/queues.
 *
 * When the समयr's base is locked, and the समयr हटाओd from list, it is
 * possible to set समयr->base = &migration_base and drop the lock: the समयr
 * reमुख्यs locked.
 */
अटल
काष्ठा hrसमयr_घड़ी_base *lock_hrसमयr_base(स्थिर काष्ठा hrसमयr *समयr,
					     अचिन्हित दीर्घ *flags)
अणु
	काष्ठा hrसमयr_घड़ी_base *base;

	क्रम (;;) अणु
		base = READ_ONCE(समयr->base);
		अगर (likely(base != &migration_base)) अणु
			raw_spin_lock_irqsave(&base->cpu_base->lock, *flags);
			अगर (likely(base == समयr->base))
				वापस base;
			/* The समयr has migrated to another CPU: */
			raw_spin_unlock_irqrestore(&base->cpu_base->lock, *flags);
		पूर्ण
		cpu_relax();
	पूर्ण
पूर्ण

/*
 * We करो not migrate the समयr when it is expiring beक्रमe the next
 * event on the target cpu. When high resolution is enabled, we cannot
 * reprogram the target cpu hardware and we would cause it to fire
 * late. To keep it simple, we handle the high resolution enabled and
 * disabled हाल similar.
 *
 * Called with cpu_base->lock of target cpu held.
 */
अटल पूर्णांक
hrसमयr_check_target(काष्ठा hrसमयr *समयr, काष्ठा hrसमयr_घड़ी_base *new_base)
अणु
	kसमय_प्रकार expires;

	expires = kसमय_sub(hrसमयr_get_expires(समयr), new_base->offset);
	वापस expires < new_base->cpu_base->expires_next;
पूर्ण

अटल अंतरभूत
काष्ठा hrसमयr_cpu_base *get_target_base(काष्ठा hrसमयr_cpu_base *base,
					 पूर्णांक pinned)
अणु
#अगर defined(CONFIG_SMP) && defined(CONFIG_NO_HZ_COMMON)
	अगर (अटल_branch_likely(&समयrs_migration_enabled) && !pinned)
		वापस &per_cpu(hrसमयr_bases, get_nohz_समयr_target());
#पूर्ण_अगर
	वापस base;
पूर्ण

/*
 * We चयन the समयr base to a घातer-optimized selected CPU target,
 * अगर:
 *	- NO_HZ_COMMON is enabled
 *	- समयr migration is enabled
 *	- the समयr callback is not running
 *	- the समयr is not the first expiring समयr on the new target
 *
 * If one of the above requirements is not fulfilled we move the समयr
 * to the current CPU or leave it on the previously asचिन्हित CPU अगर
 * the समयr callback is currently running.
 */
अटल अंतरभूत काष्ठा hrसमयr_घड़ी_base *
चयन_hrसमयr_base(काष्ठा hrसमयr *समयr, काष्ठा hrसमयr_घड़ी_base *base,
		    पूर्णांक pinned)
अणु
	काष्ठा hrसमयr_cpu_base *new_cpu_base, *this_cpu_base;
	काष्ठा hrसमयr_घड़ी_base *new_base;
	पूर्णांक basक्रमागत = base->index;

	this_cpu_base = this_cpu_ptr(&hrसमयr_bases);
	new_cpu_base = get_target_base(this_cpu_base, pinned);
again:
	new_base = &new_cpu_base->घड़ी_base[basक्रमागत];

	अगर (base != new_base) अणु
		/*
		 * We are trying to move समयr to new_base.
		 * However we can't change timer's base जबतक it is running,
		 * so we keep it on the same CPU. No hassle vs. reprogramming
		 * the event source in the high resolution हाल. The softirq
		 * code will take care of this when the समयr function has
		 * completed. There is no conflict as we hold the lock until
		 * the समयr is enqueued.
		 */
		अगर (unlikely(hrसमयr_callback_running(समयr)))
			वापस base;

		/* See the comment in lock_hrसमयr_base() */
		WRITE_ONCE(समयr->base, &migration_base);
		raw_spin_unlock(&base->cpu_base->lock);
		raw_spin_lock(&new_base->cpu_base->lock);

		अगर (new_cpu_base != this_cpu_base &&
		    hrसमयr_check_target(समयr, new_base)) अणु
			raw_spin_unlock(&new_base->cpu_base->lock);
			raw_spin_lock(&base->cpu_base->lock);
			new_cpu_base = this_cpu_base;
			WRITE_ONCE(समयr->base, base);
			जाओ again;
		पूर्ण
		WRITE_ONCE(समयr->base, new_base);
	पूर्ण अन्यथा अणु
		अगर (new_cpu_base != this_cpu_base &&
		    hrसमयr_check_target(समयr, new_base)) अणु
			new_cpu_base = this_cpu_base;
			जाओ again;
		पूर्ण
	पूर्ण
	वापस new_base;
पूर्ण

#अन्यथा /* CONFIG_SMP */

अटल अंतरभूत bool is_migration_base(काष्ठा hrसमयr_घड़ी_base *base)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा hrसमयr_घड़ी_base *
lock_hrसमयr_base(स्थिर काष्ठा hrसमयr *समयr, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा hrसमयr_घड़ी_base *base = समयr->base;

	raw_spin_lock_irqsave(&base->cpu_base->lock, *flags);

	वापस base;
पूर्ण

# define चयन_hrसमयr_base(t, b, p)	(b)

#पूर्ण_अगर	/* !CONFIG_SMP */

/*
 * Functions क्रम the जोड़ type storage क्रमmat of kसमय_प्रकार which are
 * too large क्रम inlining:
 */
#अगर BITS_PER_LONG < 64
/*
 * Divide a kसमय value by a nanosecond value
 */
s64 __kसमय_भागns(स्थिर kसमय_प्रकार kt, s64 भाग)
अणु
	पूर्णांक sft = 0;
	s64 dclc;
	u64 पंचांगp;

	dclc = kसमय_प्रकारo_ns(kt);
	पंचांगp = dclc < 0 ? -dclc : dclc;

	/* Make sure the भागisor is less than 2^32: */
	जबतक (भाग >> 32) अणु
		sft++;
		भाग >>= 1;
	पूर्ण
	पंचांगp >>= sft;
	करो_भाग(पंचांगp, (u32) भाग);
	वापस dclc < 0 ? -पंचांगp : पंचांगp;
पूर्ण
EXPORT_SYMBOL_GPL(__kसमय_भागns);
#पूर्ण_अगर /* BITS_PER_LONG >= 64 */

/*
 * Add two kसमय values and करो a safety check क्रम overflow:
 */
kसमय_प्रकार kसमय_add_safe(स्थिर kसमय_प्रकार lhs, स्थिर kसमय_प्रकार rhs)
अणु
	kसमय_प्रकार res = kसमय_add_unsafe(lhs, rhs);

	/*
	 * We use KTIME_SEC_MAX here, the maximum समयout which we can
	 * वापस to user space in a बारpec:
	 */
	अगर (res < 0 || res < lhs || res < rhs)
		res = kसमय_set(KTIME_SEC_MAX, 0);

	वापस res;
पूर्ण

EXPORT_SYMBOL_GPL(kसमय_add_safe);

#अगर_घोषित CONFIG_DEBUG_OBJECTS_TIMERS

अटल स्थिर काष्ठा debug_obj_descr hrसमयr_debug_descr;

अटल व्योम *hrसमयr_debug_hपूर्णांक(व्योम *addr)
अणु
	वापस ((काष्ठा hrसमयr *) addr)->function;
पूर्ण

/*
 * fixup_init is called when:
 * - an active object is initialized
 */
अटल bool hrसमयr_fixup_init(व्योम *addr, क्रमागत debug_obj_state state)
अणु
	काष्ठा hrसमयr *समयr = addr;

	चयन (state) अणु
	हाल ODEBUG_STATE_ACTIVE:
		hrसमयr_cancel(समयr);
		debug_object_init(समयr, &hrसमयr_debug_descr);
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * fixup_activate is called when:
 * - an active object is activated
 * - an unknown non-अटल object is activated
 */
अटल bool hrसमयr_fixup_activate(व्योम *addr, क्रमागत debug_obj_state state)
अणु
	चयन (state) अणु
	हाल ODEBUG_STATE_ACTIVE:
		WARN_ON(1);
		fallthrough;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * fixup_मुक्त is called when:
 * - an active object is मुक्तd
 */
अटल bool hrसमयr_fixup_मुक्त(व्योम *addr, क्रमागत debug_obj_state state)
अणु
	काष्ठा hrसमयr *समयr = addr;

	चयन (state) अणु
	हाल ODEBUG_STATE_ACTIVE:
		hrसमयr_cancel(समयr);
		debug_object_मुक्त(समयr, &hrसमयr_debug_descr);
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा debug_obj_descr hrसमयr_debug_descr = अणु
	.name		= "hrtimer",
	.debug_hपूर्णांक	= hrसमयr_debug_hपूर्णांक,
	.fixup_init	= hrसमयr_fixup_init,
	.fixup_activate	= hrसमयr_fixup_activate,
	.fixup_मुक्त	= hrसमयr_fixup_मुक्त,
पूर्ण;

अटल अंतरभूत व्योम debug_hrसमयr_init(काष्ठा hrसमयr *समयr)
अणु
	debug_object_init(समयr, &hrसमयr_debug_descr);
पूर्ण

अटल अंतरभूत व्योम debug_hrसमयr_activate(काष्ठा hrसमयr *समयr,
					  क्रमागत hrसमयr_mode mode)
अणु
	debug_object_activate(समयr, &hrसमयr_debug_descr);
पूर्ण

अटल अंतरभूत व्योम debug_hrसमयr_deactivate(काष्ठा hrसमयr *समयr)
अणु
	debug_object_deactivate(समयr, &hrसमयr_debug_descr);
पूर्ण

अटल व्योम __hrसमयr_init(काष्ठा hrसमयr *समयr, घड़ीid_t घड़ी_id,
			   क्रमागत hrसमयr_mode mode);

व्योम hrसमयr_init_on_stack(काष्ठा hrसमयr *समयr, घड़ीid_t घड़ी_id,
			   क्रमागत hrसमयr_mode mode)
अणु
	debug_object_init_on_stack(समयr, &hrसमयr_debug_descr);
	__hrसमयr_init(समयr, घड़ी_id, mode);
पूर्ण
EXPORT_SYMBOL_GPL(hrसमयr_init_on_stack);

अटल व्योम __hrसमयr_init_sleeper(काष्ठा hrसमयr_sleeper *sl,
				   घड़ीid_t घड़ी_id, क्रमागत hrसमयr_mode mode);

व्योम hrसमयr_init_sleeper_on_stack(काष्ठा hrसमयr_sleeper *sl,
				   घड़ीid_t घड़ी_id, क्रमागत hrसमयr_mode mode)
अणु
	debug_object_init_on_stack(&sl->समयr, &hrसमयr_debug_descr);
	__hrसमयr_init_sleeper(sl, घड़ी_id, mode);
पूर्ण
EXPORT_SYMBOL_GPL(hrसमयr_init_sleeper_on_stack);

व्योम destroy_hrसमयr_on_stack(काष्ठा hrसमयr *समयr)
अणु
	debug_object_मुक्त(समयr, &hrसमयr_debug_descr);
पूर्ण
EXPORT_SYMBOL_GPL(destroy_hrसमयr_on_stack);

#अन्यथा

अटल अंतरभूत व्योम debug_hrसमयr_init(काष्ठा hrसमयr *समयr) अणु पूर्ण
अटल अंतरभूत व्योम debug_hrसमयr_activate(काष्ठा hrसमयr *समयr,
					  क्रमागत hrसमयr_mode mode) अणु पूर्ण
अटल अंतरभूत व्योम debug_hrसमयr_deactivate(काष्ठा hrसमयr *समयr) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम
debug_init(काष्ठा hrसमयr *समयr, घड़ीid_t घड़ीid,
	   क्रमागत hrसमयr_mode mode)
अणु
	debug_hrसमयr_init(समयr);
	trace_hrसमयr_init(समयr, घड़ीid, mode);
पूर्ण

अटल अंतरभूत व्योम debug_activate(काष्ठा hrसमयr *समयr,
				  क्रमागत hrसमयr_mode mode)
अणु
	debug_hrसमयr_activate(समयr, mode);
	trace_hrसमयr_start(समयr, mode);
पूर्ण

अटल अंतरभूत व्योम debug_deactivate(काष्ठा hrसमयr *समयr)
अणु
	debug_hrसमयr_deactivate(समयr);
	trace_hrसमयr_cancel(समयr);
पूर्ण

अटल काष्ठा hrसमयr_घड़ी_base *
__next_base(काष्ठा hrसमयr_cpu_base *cpu_base, अचिन्हित पूर्णांक *active)
अणु
	अचिन्हित पूर्णांक idx;

	अगर (!*active)
		वापस शून्य;

	idx = __ffs(*active);
	*active &= ~(1U << idx);

	वापस &cpu_base->घड़ी_base[idx];
पूर्ण

#घोषणा क्रम_each_active_base(base, cpu_base, active)	\
	जबतक ((base = __next_base((cpu_base), &(active))))

अटल kसमय_प्रकार __hrसमयr_next_event_base(काष्ठा hrसमयr_cpu_base *cpu_base,
					 स्थिर काष्ठा hrसमयr *exclude,
					 अचिन्हित पूर्णांक active,
					 kसमय_प्रकार expires_next)
अणु
	काष्ठा hrसमयr_घड़ी_base *base;
	kसमय_प्रकार expires;

	क्रम_each_active_base(base, cpu_base, active) अणु
		काष्ठा समयrqueue_node *next;
		काष्ठा hrसमयr *समयr;

		next = समयrqueue_getnext(&base->active);
		समयr = container_of(next, काष्ठा hrसमयr, node);
		अगर (समयr == exclude) अणु
			/* Get to the next समयr in the queue. */
			next = समयrqueue_iterate_next(next);
			अगर (!next)
				जारी;

			समयr = container_of(next, काष्ठा hrसमयr, node);
		पूर्ण
		expires = kसमय_sub(hrसमयr_get_expires(समयr), base->offset);
		अगर (expires < expires_next) अणु
			expires_next = expires;

			/* Skip cpu_base update अगर a समयr is being excluded. */
			अगर (exclude)
				जारी;

			अगर (समयr->is_soft)
				cpu_base->softirq_next_समयr = समयr;
			अन्यथा
				cpu_base->next_समयr = समयr;
		पूर्ण
	पूर्ण
	/*
	 * घड़ी_was_set() might have changed base->offset of any of
	 * the घड़ी bases so the result might be negative. Fix it up
	 * to prevent a false positive in घड़ीevents_program_event().
	 */
	अगर (expires_next < 0)
		expires_next = 0;
	वापस expires_next;
पूर्ण

/*
 * Recomputes cpu_base::*next_समयr and वापसs the earliest expires_next
 * but करोes not set cpu_base::*expires_next, that is करोne by
 * hrसमयr[_क्रमce]_reprogram and hrसमयr_पूर्णांकerrupt only. When updating
 * cpu_base::*expires_next right away, reprogramming logic would no दीर्घer
 * work.
 *
 * When a softirq is pending, we can ignore the HRTIMER_ACTIVE_SOFT bases,
 * those समयrs will get run whenever the softirq माला_लो handled, at the end of
 * hrसमयr_run_softirq(), hrसमयr_update_softirq_समयr() will re-add these bases.
 *
 * Thereक्रमe softirq values are those from the HRTIMER_ACTIVE_SOFT घड़ी bases.
 * The !softirq values are the minima across HRTIMER_ACTIVE_ALL, unless an actual
 * softirq is pending, in which हाल they're the minima of HRTIMER_ACTIVE_HARD.
 *
 * @active_mask must be one of:
 *  - HRTIMER_ACTIVE_ALL,
 *  - HRTIMER_ACTIVE_SOFT, or
 *  - HRTIMER_ACTIVE_HARD.
 */
अटल kसमय_प्रकार
__hrसमयr_get_next_event(काष्ठा hrसमयr_cpu_base *cpu_base, अचिन्हित पूर्णांक active_mask)
अणु
	अचिन्हित पूर्णांक active;
	काष्ठा hrसमयr *next_समयr = शून्य;
	kसमय_प्रकार expires_next = KTIME_MAX;

	अगर (!cpu_base->softirq_activated && (active_mask & HRTIMER_ACTIVE_SOFT)) अणु
		active = cpu_base->active_bases & HRTIMER_ACTIVE_SOFT;
		cpu_base->softirq_next_समयr = शून्य;
		expires_next = __hrसमयr_next_event_base(cpu_base, शून्य,
							 active, KTIME_MAX);

		next_समयr = cpu_base->softirq_next_समयr;
	पूर्ण

	अगर (active_mask & HRTIMER_ACTIVE_HARD) अणु
		active = cpu_base->active_bases & HRTIMER_ACTIVE_HARD;
		cpu_base->next_समयr = next_समयr;
		expires_next = __hrसमयr_next_event_base(cpu_base, शून्य, active,
							 expires_next);
	पूर्ण

	वापस expires_next;
पूर्ण

अटल kसमय_प्रकार hrसमयr_update_next_event(काष्ठा hrसमयr_cpu_base *cpu_base)
अणु
	kसमय_प्रकार expires_next, soft = KTIME_MAX;

	/*
	 * If the soft पूर्णांकerrupt has alपढ़ोy been activated, ignore the
	 * soft bases. They will be handled in the alपढ़ोy उठाओd soft
	 * पूर्णांकerrupt.
	 */
	अगर (!cpu_base->softirq_activated) अणु
		soft = __hrसमयr_get_next_event(cpu_base, HRTIMER_ACTIVE_SOFT);
		/*
		 * Update the soft expiry समय. घड़ी_समय_रखो() might have
		 * affected it.
		 */
		cpu_base->softirq_expires_next = soft;
	पूर्ण

	expires_next = __hrसमयr_get_next_event(cpu_base, HRTIMER_ACTIVE_HARD);
	/*
	 * If a softirq समयr is expiring first, update cpu_base->next_समयr
	 * and program the hardware with the soft expiry समय.
	 */
	अगर (expires_next > soft) अणु
		cpu_base->next_समयr = cpu_base->softirq_next_समयr;
		expires_next = soft;
	पूर्ण

	वापस expires_next;
पूर्ण

अटल अंतरभूत kसमय_प्रकार hrसमयr_update_base(काष्ठा hrसमयr_cpu_base *base)
अणु
	kसमय_प्रकार *offs_real = &base->घड़ी_base[HRTIMER_BASE_REALTIME].offset;
	kसमय_प्रकार *offs_boot = &base->घड़ी_base[HRTIMER_BASE_BOOTTIME].offset;
	kसमय_प्रकार *offs_tai = &base->घड़ी_base[HRTIMER_BASE_TAI].offset;

	kसमय_प्रकार now = kसमय_get_update_offsets_now(&base->घड़ी_was_set_seq,
					    offs_real, offs_boot, offs_tai);

	base->घड़ी_base[HRTIMER_BASE_REALTIME_SOFT].offset = *offs_real;
	base->घड़ी_base[HRTIMER_BASE_BOOTTIME_SOFT].offset = *offs_boot;
	base->घड़ी_base[HRTIMER_BASE_TAI_SOFT].offset = *offs_tai;

	वापस now;
पूर्ण

/*
 * Is the high resolution mode active ?
 */
अटल अंतरभूत पूर्णांक __hrसमयr_hres_active(काष्ठा hrसमयr_cpu_base *cpu_base)
अणु
	वापस IS_ENABLED(CONFIG_HIGH_RES_TIMERS) ?
		cpu_base->hres_active : 0;
पूर्ण

अटल अंतरभूत पूर्णांक hrसमयr_hres_active(व्योम)
अणु
	वापस __hrसमयr_hres_active(this_cpu_ptr(&hrसमयr_bases));
पूर्ण

/*
 * Reprogram the event source with checking both queues क्रम the
 * next event
 * Called with पूर्णांकerrupts disabled and base->lock held
 */
अटल व्योम
hrसमयr_क्रमce_reprogram(काष्ठा hrसमयr_cpu_base *cpu_base, पूर्णांक skip_equal)
अणु
	kसमय_प्रकार expires_next;

	expires_next = hrसमयr_update_next_event(cpu_base);

	अगर (skip_equal && expires_next == cpu_base->expires_next)
		वापस;

	cpu_base->expires_next = expires_next;

	/*
	 * If hres is not active, hardware करोes not have to be
	 * reprogrammed yet.
	 *
	 * If a hang was detected in the last समयr पूर्णांकerrupt then we
	 * leave the hang delay active in the hardware. We want the
	 * प्रणाली to make progress. That also prevents the following
	 * scenario:
	 * T1 expires 50ms from now
	 * T2 expires 5s from now
	 *
	 * T1 is हटाओd, so this code is called and would reprogram
	 * the hardware to 5s from now. Any hrसमयr_start after that
	 * will not reprogram the hardware due to hang_detected being
	 * set. So we'd effectively block all समयrs until the T2 event
	 * fires.
	 */
	अगर (!__hrसमयr_hres_active(cpu_base) || cpu_base->hang_detected)
		वापस;

	tick_program_event(cpu_base->expires_next, 1);
पूर्ण

/* High resolution समयr related functions */
#अगर_घोषित CONFIG_HIGH_RES_TIMERS

/*
 * High resolution समयr enabled ?
 */
अटल bool hrसमयr_hres_enabled __पढ़ो_mostly  = true;
अचिन्हित पूर्णांक hrसमयr_resolution __पढ़ो_mostly = LOW_RES_NSEC;
EXPORT_SYMBOL_GPL(hrसमयr_resolution);

/*
 * Enable / Disable high resolution mode
 */
अटल पूर्णांक __init setup_hrसमयr_hres(अक्षर *str)
अणु
	वापस (kstrtobool(str, &hrसमयr_hres_enabled) == 0);
पूर्ण

__setup("highres=", setup_hrसमयr_hres);

/*
 * hrसमयr_high_res_enabled - query, अगर the highres mode is enabled
 */
अटल अंतरभूत पूर्णांक hrसमयr_is_hres_enabled(व्योम)
अणु
	वापस hrसमयr_hres_enabled;
पूर्ण

/*
 * Retrigger next event is called after घड़ी was set
 *
 * Called with पूर्णांकerrupts disabled via on_each_cpu()
 */
अटल व्योम retrigger_next_event(व्योम *arg)
अणु
	काष्ठा hrसमयr_cpu_base *base = this_cpu_ptr(&hrसमयr_bases);

	अगर (!__hrसमयr_hres_active(base))
		वापस;

	raw_spin_lock(&base->lock);
	hrसमयr_update_base(base);
	hrसमयr_क्रमce_reprogram(base, 0);
	raw_spin_unlock(&base->lock);
पूर्ण

/*
 * Switch to high resolution mode
 */
अटल व्योम hrसमयr_चयन_to_hres(व्योम)
अणु
	काष्ठा hrसमयr_cpu_base *base = this_cpu_ptr(&hrसमयr_bases);

	अगर (tick_init_highres()) अणु
		pr_warn("Could not switch to high resolution mode on CPU %u\n",
			base->cpu);
		वापस;
	पूर्ण
	base->hres_active = 1;
	hrसमयr_resolution = HIGH_RES_NSEC;

	tick_setup_sched_समयr();
	/* "Retrigger" the पूर्णांकerrupt to get things going */
	retrigger_next_event(शून्य);
पूर्ण

अटल व्योम घड़ी_was_set_work(काष्ठा work_काष्ठा *work)
अणु
	घड़ी_was_set();
पूर्ण

अटल DECLARE_WORK(hrसमयr_work, घड़ी_was_set_work);

/*
 * Called from समयkeeping and resume code to reprogram the hrसमयr
 * पूर्णांकerrupt device on all cpus.
 */
व्योम घड़ी_was_set_delayed(व्योम)
अणु
	schedule_work(&hrसमयr_work);
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक hrसमयr_is_hres_enabled(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम hrसमयr_चयन_to_hres(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम retrigger_next_event(व्योम *arg) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_HIGH_RES_TIMERS */

/*
 * When a समयr is enqueued and expires earlier than the alपढ़ोy enqueued
 * समयrs, we have to check, whether it expires earlier than the समयr क्रम
 * which the घड़ी event device was armed.
 *
 * Called with पूर्णांकerrupts disabled and base->cpu_base.lock held
 */
अटल व्योम hrसमयr_reprogram(काष्ठा hrसमयr *समयr, bool reprogram)
अणु
	काष्ठा hrसमयr_cpu_base *cpu_base = this_cpu_ptr(&hrसमयr_bases);
	काष्ठा hrसमयr_घड़ी_base *base = समयr->base;
	kसमय_प्रकार expires = kसमय_sub(hrसमयr_get_expires(समयr), base->offset);

	WARN_ON_ONCE(hrसमयr_get_expires_tv64(समयr) < 0);

	/*
	 * CLOCK_REALTIME समयr might be requested with an असलolute
	 * expiry समय which is less than base->offset. Set it to 0.
	 */
	अगर (expires < 0)
		expires = 0;

	अगर (समयr->is_soft) अणु
		/*
		 * soft hrसमयr could be started on a remote CPU. In this
		 * हाल softirq_expires_next needs to be updated on the
		 * remote CPU. The soft hrसमयr will not expire beक्रमe the
		 * first hard hrसमयr on the remote CPU -
		 * hrसमयr_check_target() prevents this हाल.
		 */
		काष्ठा hrसमयr_cpu_base *समयr_cpu_base = base->cpu_base;

		अगर (समयr_cpu_base->softirq_activated)
			वापस;

		अगर (!kसमय_beक्रमe(expires, समयr_cpu_base->softirq_expires_next))
			वापस;

		समयr_cpu_base->softirq_next_समयr = समयr;
		समयr_cpu_base->softirq_expires_next = expires;

		अगर (!kसमय_beक्रमe(expires, समयr_cpu_base->expires_next) ||
		    !reprogram)
			वापस;
	पूर्ण

	/*
	 * If the समयr is not on the current cpu, we cannot reprogram
	 * the other cpus घड़ी event device.
	 */
	अगर (base->cpu_base != cpu_base)
		वापस;

	/*
	 * If the hrसमयr पूर्णांकerrupt is running, then it will
	 * reevaluate the घड़ी bases and reprogram the घड़ी event
	 * device. The callbacks are always executed in hard पूर्णांकerrupt
	 * context so we करोn't need an extra check क्रम a running
	 * callback.
	 */
	अगर (cpu_base->in_hrtirq)
		वापस;

	अगर (expires >= cpu_base->expires_next)
		वापस;

	/* Update the poपूर्णांकer to the next expiring समयr */
	cpu_base->next_समयr = समयr;
	cpu_base->expires_next = expires;

	/*
	 * If hres is not active, hardware करोes not have to be
	 * programmed yet.
	 *
	 * If a hang was detected in the last समयr पूर्णांकerrupt then we
	 * करो not schedule a समयr which is earlier than the expiry
	 * which we enक्रमced in the hang detection. We want the प्रणाली
	 * to make progress.
	 */
	अगर (!__hrसमयr_hres_active(cpu_base) || cpu_base->hang_detected)
		वापस;

	/*
	 * Program the समयr hardware. We enक्रमce the expiry क्रम
	 * events which are alपढ़ोy in the past.
	 */
	tick_program_event(expires, 1);
पूर्ण

/*
 * Clock realसमय was set
 *
 * Change the offset of the realसमय घड़ी vs. the monotonic
 * घड़ी.
 *
 * We might have to reprogram the high resolution समयr पूर्णांकerrupt. On
 * SMP we call the architecture specअगरic code to retrigger _all_ high
 * resolution समयr पूर्णांकerrupts. On UP we just disable पूर्णांकerrupts and
 * call the high resolution पूर्णांकerrupt code.
 */
व्योम घड़ी_was_set(व्योम)
अणु
#अगर_घोषित CONFIG_HIGH_RES_TIMERS
	/* Retrigger the CPU local events everywhere */
	on_each_cpu(retrigger_next_event, शून्य, 1);
#पूर्ण_अगर
	समयrfd_घड़ी_was_set();
पूर्ण

/*
 * During resume we might have to reprogram the high resolution समयr
 * पूर्णांकerrupt on all online CPUs.  However, all other CPUs will be
 * stopped with IRQs पूर्णांकerrupts disabled so the घड़ी_was_set() call
 * must be deferred.
 */
व्योम hrसमयrs_resume(व्योम)
अणु
	lockdep_निश्चित_irqs_disabled();
	/* Retrigger on the local CPU */
	retrigger_next_event(शून्य);
	/* And schedule a retrigger क्रम all others */
	घड़ी_was_set_delayed();
पूर्ण

/*
 * Counterpart to lock_hrसमयr_base above:
 */
अटल अंतरभूत
व्योम unlock_hrसमयr_base(स्थिर काष्ठा hrसमयr *समयr, अचिन्हित दीर्घ *flags)
अणु
	raw_spin_unlock_irqrestore(&समयr->base->cpu_base->lock, *flags);
पूर्ण

/**
 * hrसमयr_क्रमward - क्रमward the समयr expiry
 * @समयr:	hrसमयr to क्रमward
 * @now:	क्रमward past this समय
 * @पूर्णांकerval:	the पूर्णांकerval to क्रमward
 *
 * Forward the समयr expiry so it will expire in the future.
 * Returns the number of overruns.
 *
 * Can be safely called from the callback function of @समयr. If
 * called from other contexts @समयr must neither be enqueued nor
 * running the callback and the caller needs to take care of
 * serialization.
 *
 * Note: This only updates the समयr expiry value and करोes not requeue
 * the समयr.
 */
u64 hrसमयr_क्रमward(काष्ठा hrसमयr *समयr, kसमय_प्रकार now, kसमय_प्रकार पूर्णांकerval)
अणु
	u64 orun = 1;
	kसमय_प्रकार delta;

	delta = kसमय_sub(now, hrसमयr_get_expires(समयr));

	अगर (delta < 0)
		वापस 0;

	अगर (WARN_ON(समयr->state & HRTIMER_STATE_ENQUEUED))
		वापस 0;

	अगर (पूर्णांकerval < hrसमयr_resolution)
		पूर्णांकerval = hrसमयr_resolution;

	अगर (unlikely(delta >= पूर्णांकerval)) अणु
		s64 incr = kसमय_प्रकारo_ns(पूर्णांकerval);

		orun = kसमय_भागns(delta, incr);
		hrसमयr_add_expires_ns(समयr, incr * orun);
		अगर (hrसमयr_get_expires_tv64(समयr) > now)
			वापस orun;
		/*
		 * This (and the kसमय_add() below) is the
		 * correction क्रम exact:
		 */
		orun++;
	पूर्ण
	hrसमयr_add_expires(समयr, पूर्णांकerval);

	वापस orun;
पूर्ण
EXPORT_SYMBOL_GPL(hrसमयr_क्रमward);

/*
 * enqueue_hrसमयr - पूर्णांकernal function to (re)start a समयr
 *
 * The समयr is inserted in expiry order. Insertion पूर्णांकo the
 * red black tree is O(log(n)). Must hold the base lock.
 *
 * Returns 1 when the new समयr is the lefपंचांगost समयr in the tree.
 */
अटल पूर्णांक enqueue_hrसमयr(काष्ठा hrसमयr *समयr,
			   काष्ठा hrसमयr_घड़ी_base *base,
			   क्रमागत hrसमयr_mode mode)
अणु
	debug_activate(समयr, mode);

	base->cpu_base->active_bases |= 1 << base->index;

	/* Pairs with the lockless पढ़ो in hrसमयr_is_queued() */
	WRITE_ONCE(समयr->state, HRTIMER_STATE_ENQUEUED);

	वापस समयrqueue_add(&base->active, &समयr->node);
पूर्ण

/*
 * __हटाओ_hrसमयr - पूर्णांकernal function to हटाओ a समयr
 *
 * Caller must hold the base lock.
 *
 * High resolution समयr mode reprograms the घड़ी event device when the
 * समयr is the one which expires next. The caller can disable this by setting
 * reprogram to zero. This is useful, when the context करोes a reprogramming
 * anyway (e.g. समयr पूर्णांकerrupt)
 */
अटल व्योम __हटाओ_hrसमयr(काष्ठा hrसमयr *समयr,
			     काष्ठा hrसमयr_घड़ी_base *base,
			     u8 newstate, पूर्णांक reprogram)
अणु
	काष्ठा hrसमयr_cpu_base *cpu_base = base->cpu_base;
	u8 state = समयr->state;

	/* Pairs with the lockless पढ़ो in hrसमयr_is_queued() */
	WRITE_ONCE(समयr->state, newstate);
	अगर (!(state & HRTIMER_STATE_ENQUEUED))
		वापस;

	अगर (!समयrqueue_del(&base->active, &समयr->node))
		cpu_base->active_bases &= ~(1 << base->index);

	/*
	 * Note: If reprogram is false we करो not update
	 * cpu_base->next_समयr. This happens when we हटाओ the first
	 * समयr on a remote cpu. No harm as we never dereference
	 * cpu_base->next_समयr. So the worst thing what can happen is
	 * an superfluous call to hrसमयr_क्रमce_reprogram() on the
	 * remote cpu later on अगर the same समयr माला_लो enqueued again.
	 */
	अगर (reprogram && समयr == cpu_base->next_समयr)
		hrसमयr_क्रमce_reprogram(cpu_base, 1);
पूर्ण

/*
 * हटाओ hrसमयr, called with base lock held
 */
अटल अंतरभूत पूर्णांक
हटाओ_hrसमयr(काष्ठा hrसमयr *समयr, काष्ठा hrसमयr_घड़ी_base *base, bool restart)
अणु
	u8 state = समयr->state;

	अगर (state & HRTIMER_STATE_ENQUEUED) अणु
		पूर्णांक reprogram;

		/*
		 * Remove the समयr and क्रमce reprogramming when high
		 * resolution mode is active and the समयr is on the current
		 * CPU. If we हटाओ a समयr on another CPU, reprogramming is
		 * skipped. The पूर्णांकerrupt event on this CPU is fired and
		 * reprogramming happens in the पूर्णांकerrupt handler. This is a
		 * rare हाल and less expensive than a smp call.
		 */
		debug_deactivate(समयr);
		reprogram = base->cpu_base == this_cpu_ptr(&hrसमयr_bases);

		अगर (!restart)
			state = HRTIMER_STATE_INACTIVE;

		__हटाओ_hrसमयr(समयr, base, state, reprogram);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत kसमय_प्रकार hrसमयr_update_lowres(काष्ठा hrसमयr *समयr, kसमय_प्रकार tim,
					    स्थिर क्रमागत hrसमयr_mode mode)
अणु
#अगर_घोषित CONFIG_TIME_LOW_RES
	/*
	 * CONFIG_TIME_LOW_RES indicates that the प्रणाली has no way to वापस
	 * granular समय values. For relative समयrs we add hrसमयr_resolution
	 * (i.e. one jअगरfie) to prevent लघु समयouts.
	 */
	समयr->is_rel = mode & HRTIMER_MODE_REL;
	अगर (समयr->is_rel)
		tim = kसमय_add_safe(tim, hrसमयr_resolution);
#पूर्ण_अगर
	वापस tim;
पूर्ण

अटल व्योम
hrसमयr_update_softirq_समयr(काष्ठा hrसमयr_cpu_base *cpu_base, bool reprogram)
अणु
	kसमय_प्रकार expires;

	/*
	 * Find the next SOFT expiration.
	 */
	expires = __hrसमयr_get_next_event(cpu_base, HRTIMER_ACTIVE_SOFT);

	/*
	 * reprogramming needs to be triggered, even अगर the next soft
	 * hrसमयr expires at the same समय than the next hard
	 * hrसमयr. cpu_base->softirq_expires_next needs to be updated!
	 */
	अगर (expires == KTIME_MAX)
		वापस;

	/*
	 * cpu_base->*next_समयr is recomputed by __hrसमयr_get_next_event()
	 * cpu_base->*expires_next is only set by hrसमयr_reprogram()
	 */
	hrसमयr_reprogram(cpu_base->softirq_next_समयr, reprogram);
पूर्ण

अटल पूर्णांक __hrसमयr_start_range_ns(काष्ठा hrसमयr *समयr, kसमय_प्रकार tim,
				    u64 delta_ns, स्थिर क्रमागत hrसमयr_mode mode,
				    काष्ठा hrसमयr_घड़ी_base *base)
अणु
	काष्ठा hrसमयr_घड़ी_base *new_base;

	/* Remove an active समयr from the queue: */
	हटाओ_hrसमयr(समयr, base, true);

	अगर (mode & HRTIMER_MODE_REL)
		tim = kसमय_add_safe(tim, base->get_समय());

	tim = hrसमयr_update_lowres(समयr, tim, mode);

	hrसमयr_set_expires_range_ns(समयr, tim, delta_ns);

	/* Switch the समयr base, अगर necessary: */
	new_base = चयन_hrसमयr_base(समयr, base, mode & HRTIMER_MODE_PINNED);

	वापस enqueue_hrसमयr(समयr, new_base, mode);
पूर्ण

/**
 * hrसमयr_start_range_ns - (re)start an hrसमयr
 * @समयr:	the समयr to be added
 * @tim:	expiry समय
 * @delta_ns:	"slack" range क्रम the समयr
 * @mode:	समयr mode: असलolute (HRTIMER_MODE_ABS) or
 *		relative (HRTIMER_MODE_REL), and pinned (HRTIMER_MODE_PINNED);
 *		softirq based mode is considered क्रम debug purpose only!
 */
व्योम hrसमयr_start_range_ns(काष्ठा hrसमयr *समयr, kसमय_प्रकार tim,
			    u64 delta_ns, स्थिर क्रमागत hrसमयr_mode mode)
अणु
	काष्ठा hrसमयr_घड़ी_base *base;
	अचिन्हित दीर्घ flags;

	/*
	 * Check whether the HRTIMER_MODE_SOFT bit and hrसमयr.is_soft
	 * match on CONFIG_PREEMPT_RT = n. With PREEMPT_RT check the hard
	 * expiry mode because unmarked समयrs are moved to softirq expiry.
	 */
	अगर (!IS_ENABLED(CONFIG_PREEMPT_RT))
		WARN_ON_ONCE(!(mode & HRTIMER_MODE_SOFT) ^ !समयr->is_soft);
	अन्यथा
		WARN_ON_ONCE(!(mode & HRTIMER_MODE_HARD) ^ !समयr->is_hard);

	base = lock_hrसमयr_base(समयr, &flags);

	अगर (__hrसमयr_start_range_ns(समयr, tim, delta_ns, mode, base))
		hrसमयr_reprogram(समयr, true);

	unlock_hrसमयr_base(समयr, &flags);
पूर्ण
EXPORT_SYMBOL_GPL(hrसमयr_start_range_ns);

/**
 * hrसमयr_try_to_cancel - try to deactivate a समयr
 * @समयr:	hrसमयr to stop
 *
 * Returns:
 *
 *  *  0 when the समयr was not active
 *  *  1 when the समयr was active
 *  * -1 when the समयr is currently executing the callback function and
 *    cannot be stopped
 */
पूर्णांक hrसमयr_try_to_cancel(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा hrसमयr_घड़ी_base *base;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -1;

	/*
	 * Check lockless first. If the समयr is not active (neither
	 * enqueued nor running the callback, nothing to करो here.  The
	 * base lock करोes not serialize against a concurrent enqueue,
	 * so we can aव्योम taking it.
	 */
	अगर (!hrसमयr_active(समयr))
		वापस 0;

	base = lock_hrसमयr_base(समयr, &flags);

	अगर (!hrसमयr_callback_running(समयr))
		ret = हटाओ_hrसमयr(समयr, base, false);

	unlock_hrसमयr_base(समयr, &flags);

	वापस ret;

पूर्ण
EXPORT_SYMBOL_GPL(hrसमयr_try_to_cancel);

#अगर_घोषित CONFIG_PREEMPT_RT
अटल व्योम hrसमयr_cpu_base_init_expiry_lock(काष्ठा hrसमयr_cpu_base *base)
अणु
	spin_lock_init(&base->softirq_expiry_lock);
पूर्ण

अटल व्योम hrसमयr_cpu_base_lock_expiry(काष्ठा hrसमयr_cpu_base *base)
अणु
	spin_lock(&base->softirq_expiry_lock);
पूर्ण

अटल व्योम hrसमयr_cpu_base_unlock_expiry(काष्ठा hrसमयr_cpu_base *base)
अणु
	spin_unlock(&base->softirq_expiry_lock);
पूर्ण

/*
 * The counterpart to hrसमयr_cancel_रुको_running().
 *
 * If there is a रुकोer क्रम cpu_base->expiry_lock, then it was रुकोing क्रम
 * the समयr callback to finish. Drop expiry_lock and reacquire it. That
 * allows the रुकोer to acquire the lock and make progress.
 */
अटल व्योम hrसमयr_sync_रुको_running(काष्ठा hrसमयr_cpu_base *cpu_base,
				      अचिन्हित दीर्घ flags)
अणु
	अगर (atomic_पढ़ो(&cpu_base->समयr_रुकोers)) अणु
		raw_spin_unlock_irqrestore(&cpu_base->lock, flags);
		spin_unlock(&cpu_base->softirq_expiry_lock);
		spin_lock(&cpu_base->softirq_expiry_lock);
		raw_spin_lock_irq(&cpu_base->lock);
	पूर्ण
पूर्ण

/*
 * This function is called on PREEMPT_RT kernels when the fast path
 * deletion of a समयr failed because the समयr callback function was
 * running.
 *
 * This prevents priority inversion: अगर the soft irq thपढ़ो is preempted
 * in the middle of a समयr callback, then calling del_समयr_sync() can
 * lead to two issues:
 *
 *  - If the caller is on a remote CPU then it has to spin रुको क्रम the समयr
 *    handler to complete. This can result in unbound priority inversion.
 *
 *  - If the caller originates from the task which preempted the समयr
 *    handler on the same CPU, then spin रुकोing क्रम the समयr handler to
 *    complete is never going to end.
 */
व्योम hrसमयr_cancel_रुको_running(स्थिर काष्ठा hrसमयr *समयr)
अणु
	/* Lockless पढ़ो. Prevent the compiler from reloading it below */
	काष्ठा hrसमयr_घड़ी_base *base = READ_ONCE(समयr->base);

	/*
	 * Just relax अगर the समयr expires in hard पूर्णांकerrupt context or अगर
	 * it is currently on the migration base.
	 */
	अगर (!समयr->is_soft || is_migration_base(base)) अणु
		cpu_relax();
		वापस;
	पूर्ण

	/*
	 * Mark the base as contended and grab the expiry lock, which is
	 * held by the softirq across the समयr callback. Drop the lock
	 * immediately so the softirq can expire the next समयr. In theory
	 * the समयr could alपढ़ोy be running again, but that's more than
	 * unlikely and just causes another रुको loop.
	 */
	atomic_inc(&base->cpu_base->समयr_रुकोers);
	spin_lock_bh(&base->cpu_base->softirq_expiry_lock);
	atomic_dec(&base->cpu_base->समयr_रुकोers);
	spin_unlock_bh(&base->cpu_base->softirq_expiry_lock);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
hrसमयr_cpu_base_init_expiry_lock(काष्ठा hrसमयr_cpu_base *base) अणु पूर्ण
अटल अंतरभूत व्योम
hrसमयr_cpu_base_lock_expiry(काष्ठा hrसमयr_cpu_base *base) अणु पूर्ण
अटल अंतरभूत व्योम
hrसमयr_cpu_base_unlock_expiry(काष्ठा hrसमयr_cpu_base *base) अणु पूर्ण
अटल अंतरभूत व्योम hrसमयr_sync_रुको_running(काष्ठा hrसमयr_cpu_base *base,
					     अचिन्हित दीर्घ flags) अणु पूर्ण
#पूर्ण_अगर

/**
 * hrसमयr_cancel - cancel a समयr and रुको क्रम the handler to finish.
 * @समयr:	the समयr to be cancelled
 *
 * Returns:
 *  0 when the समयr was not active
 *  1 when the समयr was active
 */
पूर्णांक hrसमयr_cancel(काष्ठा hrसमयr *समयr)
अणु
	पूर्णांक ret;

	करो अणु
		ret = hrसमयr_try_to_cancel(समयr);

		अगर (ret < 0)
			hrसमयr_cancel_रुको_running(समयr);
	पूर्ण जबतक (ret < 0);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hrसमयr_cancel);

/**
 * __hrसमयr_get_reमुख्यing - get reमुख्यing समय क्रम the समयr
 * @समयr:	the समयr to पढ़ो
 * @adjust:	adjust relative समयrs when CONFIG_TIME_LOW_RES=y
 */
kसमय_प्रकार __hrसमयr_get_reमुख्यing(स्थिर काष्ठा hrसमयr *समयr, bool adjust)
अणु
	अचिन्हित दीर्घ flags;
	kसमय_प्रकार rem;

	lock_hrसमयr_base(समयr, &flags);
	अगर (IS_ENABLED(CONFIG_TIME_LOW_RES) && adjust)
		rem = hrसमयr_expires_reमुख्यing_adjusted(समयr);
	अन्यथा
		rem = hrसमयr_expires_reमुख्यing(समयr);
	unlock_hrसमयr_base(समयr, &flags);

	वापस rem;
पूर्ण
EXPORT_SYMBOL_GPL(__hrसमयr_get_reमुख्यing);

#अगर_घोषित CONFIG_NO_HZ_COMMON
/**
 * hrसमयr_get_next_event - get the समय until next expiry event
 *
 * Returns the next expiry समय or KTIME_MAX अगर no समयr is pending.
 */
u64 hrसमयr_get_next_event(व्योम)
अणु
	काष्ठा hrसमयr_cpu_base *cpu_base = this_cpu_ptr(&hrसमयr_bases);
	u64 expires = KTIME_MAX;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&cpu_base->lock, flags);

	अगर (!__hrसमयr_hres_active(cpu_base))
		expires = __hrसमयr_get_next_event(cpu_base, HRTIMER_ACTIVE_ALL);

	raw_spin_unlock_irqrestore(&cpu_base->lock, flags);

	वापस expires;
पूर्ण

/**
 * hrसमयr_next_event_without - समय until next expiry event w/o one समयr
 * @exclude:	समयr to exclude
 *
 * Returns the next expiry समय over all समयrs except क्रम the @exclude one or
 * KTIME_MAX अगर none of them is pending.
 */
u64 hrसमयr_next_event_without(स्थिर काष्ठा hrसमयr *exclude)
अणु
	काष्ठा hrसमयr_cpu_base *cpu_base = this_cpu_ptr(&hrसमयr_bases);
	u64 expires = KTIME_MAX;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&cpu_base->lock, flags);

	अगर (__hrसमयr_hres_active(cpu_base)) अणु
		अचिन्हित पूर्णांक active;

		अगर (!cpu_base->softirq_activated) अणु
			active = cpu_base->active_bases & HRTIMER_ACTIVE_SOFT;
			expires = __hrसमयr_next_event_base(cpu_base, exclude,
							    active, KTIME_MAX);
		पूर्ण
		active = cpu_base->active_bases & HRTIMER_ACTIVE_HARD;
		expires = __hrसमयr_next_event_base(cpu_base, exclude, active,
						    expires);
	पूर्ण

	raw_spin_unlock_irqrestore(&cpu_base->lock, flags);

	वापस expires;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक hrसमयr_घड़ीid_to_base(घड़ीid_t घड़ी_id)
अणु
	अगर (likely(घड़ी_id < MAX_CLOCKS)) अणु
		पूर्णांक base = hrसमयr_घड़ी_प्रकारo_base_table[घड़ी_id];

		अगर (likely(base != HRTIMER_MAX_CLOCK_BASES))
			वापस base;
	पूर्ण
	WARN(1, "Invalid clockid %d. Using MONOTONIC\n", घड़ी_id);
	वापस HRTIMER_BASE_MONOTONIC;
पूर्ण

अटल व्योम __hrसमयr_init(काष्ठा hrसमयr *समयr, घड़ीid_t घड़ी_id,
			   क्रमागत hrसमयr_mode mode)
अणु
	bool softसमयr = !!(mode & HRTIMER_MODE_SOFT);
	काष्ठा hrसमयr_cpu_base *cpu_base;
	पूर्णांक base;

	/*
	 * On PREEMPT_RT enabled kernels hrसमयrs which are not explicitly
	 * marked क्रम hard पूर्णांकerrupt expiry mode are moved पूर्णांकo soft
	 * पूर्णांकerrupt context क्रम latency reasons and because the callbacks
	 * can invoke functions which might sleep on RT, e.g. spin_lock().
	 */
	अगर (IS_ENABLED(CONFIG_PREEMPT_RT) && !(mode & HRTIMER_MODE_HARD))
		softसमयr = true;

	स_रखो(समयr, 0, माप(काष्ठा hrसमयr));

	cpu_base = raw_cpu_ptr(&hrसमयr_bases);

	/*
	 * POSIX magic: Relative CLOCK_REALTIME समयrs are not affected by
	 * घड़ी modअगरications, so they needs to become CLOCK_MONOTONIC to
	 * ensure POSIX compliance.
	 */
	अगर (घड़ी_id == CLOCK_REALTIME && mode & HRTIMER_MODE_REL)
		घड़ी_id = CLOCK_MONOTONIC;

	base = softसमयr ? HRTIMER_MAX_CLOCK_BASES / 2 : 0;
	base += hrसमयr_घड़ीid_to_base(घड़ी_id);
	समयr->is_soft = softसमयr;
	समयr->is_hard = !!(mode & HRTIMER_MODE_HARD);
	समयr->base = &cpu_base->घड़ी_base[base];
	समयrqueue_init(&समयr->node);
पूर्ण

/**
 * hrसमयr_init - initialize a समयr to the given घड़ी
 * @समयr:	the समयr to be initialized
 * @घड़ी_id:	the घड़ी to be used
 * @mode:       The modes which are relevant क्रम initialization:
 *              HRTIMER_MODE_ABS, HRTIMER_MODE_REL, HRTIMER_MODE_ABS_SOFT,
 *              HRTIMER_MODE_REL_SOFT
 *
 *              The PINNED variants of the above can be handed in,
 *              but the PINNED bit is ignored as pinning happens
 *              when the hrसमयr is started
 */
व्योम hrसमयr_init(काष्ठा hrसमयr *समयr, घड़ीid_t घड़ी_id,
		  क्रमागत hrसमयr_mode mode)
अणु
	debug_init(समयr, घड़ी_id, mode);
	__hrसमयr_init(समयr, घड़ी_id, mode);
पूर्ण
EXPORT_SYMBOL_GPL(hrसमयr_init);

/*
 * A समयr is active, when it is enqueued पूर्णांकo the rbtree or the
 * callback function is running or it's in the state of being migrated
 * to another cpu.
 *
 * It is important क्रम this function to not वापस a false negative.
 */
bool hrसमयr_active(स्थिर काष्ठा hrसमयr *समयr)
अणु
	काष्ठा hrसमयr_घड़ी_base *base;
	अचिन्हित पूर्णांक seq;

	करो अणु
		base = READ_ONCE(समयr->base);
		seq = raw_पढ़ो_seqcount_begin(&base->seq);

		अगर (समयr->state != HRTIMER_STATE_INACTIVE ||
		    base->running == समयr)
			वापस true;

	पूर्ण जबतक (पढ़ो_seqcount_retry(&base->seq, seq) ||
		 base != READ_ONCE(समयr->base));

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(hrसमयr_active);

/*
 * The ग_लिखो_seqcount_barrier()s in __run_hrसमयr() split the thing पूर्णांकo 3
 * distinct sections:
 *
 *  - queued:	the समयr is queued
 *  - callback:	the समयr is being ran
 *  - post:	the समयr is inactive or (re)queued
 *
 * On the पढ़ो side we ensure we observe समयr->state and cpu_base->running
 * from the same section, अगर anything changed जबतक we looked at it, we retry.
 * This includes समयr->base changing because sequence numbers alone are
 * insufficient क्रम that.
 *
 * The sequence numbers are required because otherwise we could still observe
 * a false negative अगर the पढ़ो side got smeared over multiple consecutive
 * __run_hrसमयr() invocations.
 */

अटल व्योम __run_hrसमयr(काष्ठा hrसमयr_cpu_base *cpu_base,
			  काष्ठा hrसमयr_घड़ी_base *base,
			  काष्ठा hrसमयr *समयr, kसमय_प्रकार *now,
			  अचिन्हित दीर्घ flags) __must_hold(&cpu_base->lock)
अणु
	क्रमागत hrसमयr_restart (*fn)(काष्ठा hrसमयr *);
	bool expires_in_hardirq;
	पूर्णांक restart;

	lockdep_निश्चित_held(&cpu_base->lock);

	debug_deactivate(समयr);
	base->running = समयr;

	/*
	 * Separate the ->running assignment from the ->state assignment.
	 *
	 * As with a regular ग_लिखो barrier, this ensures the पढ़ो side in
	 * hrसमयr_active() cannot observe base->running == शून्य &&
	 * समयr->state == INACTIVE.
	 */
	raw_ग_लिखो_seqcount_barrier(&base->seq);

	__हटाओ_hrसमयr(समयr, base, HRTIMER_STATE_INACTIVE, 0);
	fn = समयr->function;

	/*
	 * Clear the 'is relative' flag क्रम the TIME_LOW_RES हाल. If the
	 * समयr is restarted with a period then it becomes an असलolute
	 * समयr. If its not restarted it करोes not matter.
	 */
	अगर (IS_ENABLED(CONFIG_TIME_LOW_RES))
		समयr->is_rel = false;

	/*
	 * The समयr is marked as running in the CPU base, so it is
	 * रक्षित against migration to a dअगरferent CPU even अगर the lock
	 * is dropped.
	 */
	raw_spin_unlock_irqrestore(&cpu_base->lock, flags);
	trace_hrसमयr_expire_entry(समयr, now);
	expires_in_hardirq = lockdep_hrसमयr_enter(समयr);

	restart = fn(समयr);

	lockdep_hrसमयr_निकास(expires_in_hardirq);
	trace_hrसमयr_expire_निकास(समयr);
	raw_spin_lock_irq(&cpu_base->lock);

	/*
	 * Note: We clear the running state after enqueue_hrसमयr and
	 * we करो not reprogram the event hardware. Happens either in
	 * hrसमयr_start_range_ns() or in hrसमयr_पूर्णांकerrupt()
	 *
	 * Note: Because we dropped the cpu_base->lock above,
	 * hrसमयr_start_range_ns() can have popped in and enqueued the समयr
	 * क्रम us alपढ़ोy.
	 */
	अगर (restart != HRTIMER_NORESTART &&
	    !(समयr->state & HRTIMER_STATE_ENQUEUED))
		enqueue_hrसमयr(समयr, base, HRTIMER_MODE_ABS);

	/*
	 * Separate the ->running assignment from the ->state assignment.
	 *
	 * As with a regular ग_लिखो barrier, this ensures the पढ़ो side in
	 * hrसमयr_active() cannot observe base->running.समयr == शून्य &&
	 * समयr->state == INACTIVE.
	 */
	raw_ग_लिखो_seqcount_barrier(&base->seq);

	WARN_ON_ONCE(base->running != समयr);
	base->running = शून्य;
पूर्ण

अटल व्योम __hrसमयr_run_queues(काष्ठा hrसमयr_cpu_base *cpu_base, kसमय_प्रकार now,
				 अचिन्हित दीर्घ flags, अचिन्हित पूर्णांक active_mask)
अणु
	काष्ठा hrसमयr_घड़ी_base *base;
	अचिन्हित पूर्णांक active = cpu_base->active_bases & active_mask;

	क्रम_each_active_base(base, cpu_base, active) अणु
		काष्ठा समयrqueue_node *node;
		kसमय_प्रकार basenow;

		basenow = kसमय_add(now, base->offset);

		जबतक ((node = समयrqueue_getnext(&base->active))) अणु
			काष्ठा hrसमयr *समयr;

			समयr = container_of(node, काष्ठा hrसमयr, node);

			/*
			 * The immediate goal क्रम using the softexpires is
			 * minimizing wakeups, not running समयrs at the
			 * earliest पूर्णांकerrupt after their soft expiration.
			 * This allows us to aव्योम using a Priority Search
			 * Tree, which can answer a stabbing query क्रम
			 * overlapping पूर्णांकervals and instead use the simple
			 * BST we alपढ़ोy have.
			 * We करोn't add extra wakeups by delaying समयrs that
			 * are right-of a not yet expired समयr, because that
			 * समयr will have to trigger a wakeup anyway.
			 */
			अगर (basenow < hrसमयr_get_softexpires_tv64(समयr))
				अवरोध;

			__run_hrसमयr(cpu_base, base, समयr, &basenow, flags);
			अगर (active_mask == HRTIMER_ACTIVE_SOFT)
				hrसमयr_sync_रुको_running(cpu_base, flags);
		पूर्ण
	पूर्ण
पूर्ण

अटल __latent_entropy व्योम hrसमयr_run_softirq(काष्ठा softirq_action *h)
अणु
	काष्ठा hrसमयr_cpu_base *cpu_base = this_cpu_ptr(&hrसमयr_bases);
	अचिन्हित दीर्घ flags;
	kसमय_प्रकार now;

	hrसमयr_cpu_base_lock_expiry(cpu_base);
	raw_spin_lock_irqsave(&cpu_base->lock, flags);

	now = hrसमयr_update_base(cpu_base);
	__hrसमयr_run_queues(cpu_base, now, flags, HRTIMER_ACTIVE_SOFT);

	cpu_base->softirq_activated = 0;
	hrसमयr_update_softirq_समयr(cpu_base, true);

	raw_spin_unlock_irqrestore(&cpu_base->lock, flags);
	hrसमयr_cpu_base_unlock_expiry(cpu_base);
पूर्ण

#अगर_घोषित CONFIG_HIGH_RES_TIMERS

/*
 * High resolution समयr पूर्णांकerrupt
 * Called with पूर्णांकerrupts disabled
 */
व्योम hrसमयr_पूर्णांकerrupt(काष्ठा घड़ी_event_device *dev)
अणु
	काष्ठा hrसमयr_cpu_base *cpu_base = this_cpu_ptr(&hrसमयr_bases);
	kसमय_प्रकार expires_next, now, entry_समय, delta;
	अचिन्हित दीर्घ flags;
	पूर्णांक retries = 0;

	BUG_ON(!cpu_base->hres_active);
	cpu_base->nr_events++;
	dev->next_event = KTIME_MAX;

	raw_spin_lock_irqsave(&cpu_base->lock, flags);
	entry_समय = now = hrसमयr_update_base(cpu_base);
retry:
	cpu_base->in_hrtirq = 1;
	/*
	 * We set expires_next to KTIME_MAX here with cpu_base->lock
	 * held to prevent that a समयr is enqueued in our queue via
	 * the migration code. This करोes not affect enqueueing of
	 * समयrs which run their callback and need to be requeued on
	 * this CPU.
	 */
	cpu_base->expires_next = KTIME_MAX;

	अगर (!kसमय_beक्रमe(now, cpu_base->softirq_expires_next)) अणु
		cpu_base->softirq_expires_next = KTIME_MAX;
		cpu_base->softirq_activated = 1;
		उठाओ_softirq_irqoff(HRTIMER_SOFTIRQ);
	पूर्ण

	__hrसमयr_run_queues(cpu_base, now, flags, HRTIMER_ACTIVE_HARD);

	/* Reevaluate the घड़ी bases क्रम the [soft] next expiry */
	expires_next = hrसमयr_update_next_event(cpu_base);
	/*
	 * Store the new expiry value so the migration code can verअगरy
	 * against it.
	 */
	cpu_base->expires_next = expires_next;
	cpu_base->in_hrtirq = 0;
	raw_spin_unlock_irqrestore(&cpu_base->lock, flags);

	/* Reprogramming necessary ? */
	अगर (!tick_program_event(expires_next, 0)) अणु
		cpu_base->hang_detected = 0;
		वापस;
	पूर्ण

	/*
	 * The next समयr was alपढ़ोy expired due to:
	 * - tracing
	 * - दीर्घ lasting callbacks
	 * - being scheduled away when running in a VM
	 *
	 * We need to prevent that we loop क्रमever in the hrसमयr
	 * पूर्णांकerrupt routine. We give it 3 attempts to aव्योम
	 * overreacting on some spurious event.
	 *
	 * Acquire base lock क्रम updating the offsets and retrieving
	 * the current समय.
	 */
	raw_spin_lock_irqsave(&cpu_base->lock, flags);
	now = hrसमयr_update_base(cpu_base);
	cpu_base->nr_retries++;
	अगर (++retries < 3)
		जाओ retry;
	/*
	 * Give the प्रणाली a chance to करो something अन्यथा than looping
	 * here. We stored the entry समय, so we know exactly how दीर्घ
	 * we spent here. We schedule the next event this amount of
	 * समय away.
	 */
	cpu_base->nr_hangs++;
	cpu_base->hang_detected = 1;
	raw_spin_unlock_irqrestore(&cpu_base->lock, flags);

	delta = kसमय_sub(now, entry_समय);
	अगर ((अचिन्हित पूर्णांक)delta > cpu_base->max_hang_समय)
		cpu_base->max_hang_समय = (अचिन्हित पूर्णांक) delta;
	/*
	 * Limit it to a sensible value as we enक्रमce a दीर्घer
	 * delay. Give the CPU at least 100ms to catch up.
	 */
	अगर (delta > 100 * NSEC_PER_MSEC)
		expires_next = kसमय_add_ns(now, 100 * NSEC_PER_MSEC);
	अन्यथा
		expires_next = kसमय_add(now, delta);
	tick_program_event(expires_next, 1);
	pr_warn_once("hrtimer: interrupt took %llu ns\n", kसमय_प्रकारo_ns(delta));
पूर्ण

/* called with पूर्णांकerrupts disabled */
अटल अंतरभूत व्योम __hrसमयr_peek_ahead_समयrs(व्योम)
अणु
	काष्ठा tick_device *td;

	अगर (!hrसमयr_hres_active())
		वापस;

	td = this_cpu_ptr(&tick_cpu_device);
	अगर (td && td->evtdev)
		hrसमयr_पूर्णांकerrupt(td->evtdev);
पूर्ण

#अन्यथा /* CONFIG_HIGH_RES_TIMERS */

अटल अंतरभूत व्योम __hrसमयr_peek_ahead_समयrs(व्योम) अणु पूर्ण

#पूर्ण_अगर	/* !CONFIG_HIGH_RES_TIMERS */

/*
 * Called from run_local_समयrs in hardirq context every jअगरfy
 */
व्योम hrसमयr_run_queues(व्योम)
अणु
	काष्ठा hrसमयr_cpu_base *cpu_base = this_cpu_ptr(&hrसमयr_bases);
	अचिन्हित दीर्घ flags;
	kसमय_प्रकार now;

	अगर (__hrसमयr_hres_active(cpu_base))
		वापस;

	/*
	 * This _is_ ugly: We have to check periodically, whether we
	 * can चयन to highres and / or nohz mode. The घड़ीsource
	 * चयन happens with xसमय_lock held. Notअगरication from
	 * there only sets the check bit in the tick_oneshot code,
	 * otherwise we might deadlock vs. xसमय_lock.
	 */
	अगर (tick_check_oneshot_change(!hrसमयr_is_hres_enabled())) अणु
		hrसमयr_चयन_to_hres();
		वापस;
	पूर्ण

	raw_spin_lock_irqsave(&cpu_base->lock, flags);
	now = hrसमयr_update_base(cpu_base);

	अगर (!kसमय_beक्रमe(now, cpu_base->softirq_expires_next)) अणु
		cpu_base->softirq_expires_next = KTIME_MAX;
		cpu_base->softirq_activated = 1;
		उठाओ_softirq_irqoff(HRTIMER_SOFTIRQ);
	पूर्ण

	__hrसमयr_run_queues(cpu_base, now, flags, HRTIMER_ACTIVE_HARD);
	raw_spin_unlock_irqrestore(&cpu_base->lock, flags);
पूर्ण

/*
 * Sleep related functions:
 */
अटल क्रमागत hrसमयr_restart hrसमयr_wakeup(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा hrसमयr_sleeper *t =
		container_of(समयr, काष्ठा hrसमयr_sleeper, समयr);
	काष्ठा task_काष्ठा *task = t->task;

	t->task = शून्य;
	अगर (task)
		wake_up_process(task);

	वापस HRTIMER_NORESTART;
पूर्ण

/**
 * hrसमयr_sleeper_start_expires - Start a hrसमयr sleeper समयr
 * @sl:		sleeper to be started
 * @mode:	समयr mode असल/rel
 *
 * Wrapper around hrसमयr_start_expires() क्रम hrसमयr_sleeper based समयrs
 * to allow PREEMPT_RT to tweak the delivery mode (soft/hardirq context)
 */
व्योम hrसमयr_sleeper_start_expires(काष्ठा hrसमयr_sleeper *sl,
				   क्रमागत hrसमयr_mode mode)
अणु
	/*
	 * Make the enqueue delivery mode check work on RT. If the sleeper
	 * was initialized क्रम hard पूर्णांकerrupt delivery, क्रमce the mode bit.
	 * This is a special हाल क्रम hrसमयr_sleepers because
	 * hrसमयr_init_sleeper() determines the delivery mode on RT so the
	 * fiddling with this decision is aव्योमed at the call sites.
	 */
	अगर (IS_ENABLED(CONFIG_PREEMPT_RT) && sl->समयr.is_hard)
		mode |= HRTIMER_MODE_HARD;

	hrसमयr_start_expires(&sl->समयr, mode);
पूर्ण
EXPORT_SYMBOL_GPL(hrसमयr_sleeper_start_expires);

अटल व्योम __hrसमयr_init_sleeper(काष्ठा hrसमयr_sleeper *sl,
				   घड़ीid_t घड़ी_id, क्रमागत hrसमयr_mode mode)
अणु
	/*
	 * On PREEMPT_RT enabled kernels hrसमयrs which are not explicitly
	 * marked क्रम hard पूर्णांकerrupt expiry mode are moved पूर्णांकo soft
	 * पूर्णांकerrupt context either क्रम latency reasons or because the
	 * hrसमयr callback takes regular spinlocks or invokes other
	 * functions which are not suitable क्रम hard पूर्णांकerrupt context on
	 * PREEMPT_RT.
	 *
	 * The hrसमयr_sleeper callback is RT compatible in hard पूर्णांकerrupt
	 * context, but there is a latency concern: Untrusted userspace can
	 * spawn many thपढ़ोs which arm समयrs क्रम the same expiry समय on
	 * the same CPU. That causes a latency spike due to the wakeup of
	 * a gazillion thपढ़ोs.
	 *
	 * OTOH, privileged real-समय user space applications rely on the
	 * low latency of hard पूर्णांकerrupt wakeups. If the current task is in
	 * a real-समय scheduling class, mark the mode क्रम hard पूर्णांकerrupt
	 * expiry.
	 */
	अगर (IS_ENABLED(CONFIG_PREEMPT_RT)) अणु
		अगर (task_is_realसमय(current) && !(mode & HRTIMER_MODE_SOFT))
			mode |= HRTIMER_MODE_HARD;
	पूर्ण

	__hrसमयr_init(&sl->समयr, घड़ी_id, mode);
	sl->समयr.function = hrसमयr_wakeup;
	sl->task = current;
पूर्ण

/**
 * hrसमयr_init_sleeper - initialize sleeper to the given घड़ी
 * @sl:		sleeper to be initialized
 * @घड़ी_id:	the घड़ी to be used
 * @mode:	समयr mode असल/rel
 */
व्योम hrसमयr_init_sleeper(काष्ठा hrसमयr_sleeper *sl, घड़ीid_t घड़ी_id,
			  क्रमागत hrसमयr_mode mode)
अणु
	debug_init(&sl->समयr, घड़ी_id, mode);
	__hrसमयr_init_sleeper(sl, घड़ी_id, mode);

पूर्ण
EXPORT_SYMBOL_GPL(hrसमयr_init_sleeper);

पूर्णांक nanosleep_copyout(काष्ठा restart_block *restart, काष्ठा बारpec64 *ts)
अणु
	चयन(restart->nanosleep.type) अणु
#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
	हाल TT_COMPAT:
		अगर (put_old_बारpec32(ts, restart->nanosleep.compat_rmtp))
			वापस -EFAULT;
		अवरोध;
#पूर्ण_अगर
	हाल TT_NATIVE:
		अगर (put_बारpec64(ts, restart->nanosleep.rmtp))
			वापस -EFAULT;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	वापस -ERESTART_RESTARTBLOCK;
पूर्ण

अटल पूर्णांक __sched करो_nanosleep(काष्ठा hrसमयr_sleeper *t, क्रमागत hrसमयr_mode mode)
अणु
	काष्ठा restart_block *restart;

	करो अणु
		set_current_state(TASK_INTERRUPTIBLE);
		hrसमयr_sleeper_start_expires(t, mode);

		अगर (likely(t->task))
			मुक्तzable_schedule();

		hrसमयr_cancel(&t->समयr);
		mode = HRTIMER_MODE_ABS;

	पूर्ण जबतक (t->task && !संकेत_pending(current));

	__set_current_state(TASK_RUNNING);

	अगर (!t->task)
		वापस 0;

	restart = &current->restart_block;
	अगर (restart->nanosleep.type != TT_NONE) अणु
		kसमय_प्रकार rem = hrसमयr_expires_reमुख्यing(&t->समयr);
		काष्ठा बारpec64 rmt;

		अगर (rem <= 0)
			वापस 0;
		rmt = kसमय_प्रकारo_बारpec64(rem);

		वापस nanosleep_copyout(restart, &rmt);
	पूर्ण
	वापस -ERESTART_RESTARTBLOCK;
पूर्ण

अटल दीर्घ __sched hrसमयr_nanosleep_restart(काष्ठा restart_block *restart)
अणु
	काष्ठा hrसमयr_sleeper t;
	पूर्णांक ret;

	hrसमयr_init_sleeper_on_stack(&t, restart->nanosleep.घड़ीid,
				      HRTIMER_MODE_ABS);
	hrसमयr_set_expires_tv64(&t.समयr, restart->nanosleep.expires);
	ret = करो_nanosleep(&t, HRTIMER_MODE_ABS);
	destroy_hrसमयr_on_stack(&t.समयr);
	वापस ret;
पूर्ण

दीर्घ hrसमयr_nanosleep(kसमय_प्रकार rqtp, स्थिर क्रमागत hrसमयr_mode mode,
		       स्थिर घड़ीid_t घड़ीid)
अणु
	काष्ठा restart_block *restart;
	काष्ठा hrसमयr_sleeper t;
	पूर्णांक ret = 0;
	u64 slack;

	slack = current->समयr_slack_ns;
	अगर (dl_task(current) || rt_task(current))
		slack = 0;

	hrसमयr_init_sleeper_on_stack(&t, घड़ीid, mode);
	hrसमयr_set_expires_range_ns(&t.समयr, rqtp, slack);
	ret = करो_nanosleep(&t, mode);
	अगर (ret != -ERESTART_RESTARTBLOCK)
		जाओ out;

	/* Absolute समयrs करो not update the rmtp value and restart: */
	अगर (mode == HRTIMER_MODE_ABS) अणु
		ret = -ERESTARTNOHAND;
		जाओ out;
	पूर्ण

	restart = &current->restart_block;
	restart->nanosleep.घड़ीid = t.समयr.base->घड़ीid;
	restart->nanosleep.expires = hrसमयr_get_expires_tv64(&t.समयr);
	set_restart_fn(restart, hrसमयr_nanosleep_restart);
out:
	destroy_hrसमयr_on_stack(&t.समयr);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_64BIT

SYSCALL_DEFINE2(nanosleep, काष्ठा __kernel_बारpec __user *, rqtp,
		काष्ठा __kernel_बारpec __user *, rmtp)
अणु
	काष्ठा बारpec64 tu;

	अगर (get_बारpec64(&tu, rqtp))
		वापस -EFAULT;

	अगर (!बारpec64_valid(&tu))
		वापस -EINVAL;

	current->restart_block.nanosleep.type = rmtp ? TT_NATIVE : TT_NONE;
	current->restart_block.nanosleep.rmtp = rmtp;
	वापस hrसमयr_nanosleep(बारpec64_to_kसमय(tu), HRTIMER_MODE_REL,
				 CLOCK_MONOTONIC);
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME

SYSCALL_DEFINE2(nanosleep_समय32, काष्ठा old_बारpec32 __user *, rqtp,
		       काष्ठा old_बारpec32 __user *, rmtp)
अणु
	काष्ठा बारpec64 tu;

	अगर (get_old_बारpec32(&tu, rqtp))
		वापस -EFAULT;

	अगर (!बारpec64_valid(&tu))
		वापस -EINVAL;

	current->restart_block.nanosleep.type = rmtp ? TT_COMPAT : TT_NONE;
	current->restart_block.nanosleep.compat_rmtp = rmtp;
	वापस hrसमयr_nanosleep(बारpec64_to_kसमय(tu), HRTIMER_MODE_REL,
				 CLOCK_MONOTONIC);
पूर्ण
#पूर्ण_अगर

/*
 * Functions related to boot-समय initialization:
 */
पूर्णांक hrसमयrs_prepare_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा hrसमयr_cpu_base *cpu_base = &per_cpu(hrसमयr_bases, cpu);
	पूर्णांक i;

	क्रम (i = 0; i < HRTIMER_MAX_CLOCK_BASES; i++) अणु
		काष्ठा hrसमयr_घड़ी_base *घड़ी_b = &cpu_base->घड़ी_base[i];

		घड़ी_b->cpu_base = cpu_base;
		seqcount_raw_spinlock_init(&घड़ी_b->seq, &cpu_base->lock);
		समयrqueue_init_head(&घड़ी_b->active);
	पूर्ण

	cpu_base->cpu = cpu;
	cpu_base->active_bases = 0;
	cpu_base->hres_active = 0;
	cpu_base->hang_detected = 0;
	cpu_base->next_समयr = शून्य;
	cpu_base->softirq_next_समयr = शून्य;
	cpu_base->expires_next = KTIME_MAX;
	cpu_base->softirq_expires_next = KTIME_MAX;
	hrसमयr_cpu_base_init_expiry_lock(cpu_base);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU

अटल व्योम migrate_hrसमयr_list(काष्ठा hrसमयr_घड़ी_base *old_base,
				काष्ठा hrसमयr_घड़ी_base *new_base)
अणु
	काष्ठा hrसमयr *समयr;
	काष्ठा समयrqueue_node *node;

	जबतक ((node = समयrqueue_getnext(&old_base->active))) अणु
		समयr = container_of(node, काष्ठा hrसमयr, node);
		BUG_ON(hrसमयr_callback_running(समयr));
		debug_deactivate(समयr);

		/*
		 * Mark it as ENQUEUED not INACTIVE otherwise the
		 * समयr could be seen as !active and just vanish away
		 * under us on another CPU
		 */
		__हटाओ_hrसमयr(समयr, old_base, HRTIMER_STATE_ENQUEUED, 0);
		समयr->base = new_base;
		/*
		 * Enqueue the समयrs on the new cpu. This करोes not
		 * reprogram the event device in हाल the समयr
		 * expires beक्रमe the earliest on this CPU, but we run
		 * hrसमयr_पूर्णांकerrupt after we migrated everything to
		 * sort out alपढ़ोy expired समयrs and reprogram the
		 * event device.
		 */
		enqueue_hrसमयr(समयr, new_base, HRTIMER_MODE_ABS);
	पूर्ण
पूर्ण

पूर्णांक hrसमयrs_dead_cpu(अचिन्हित पूर्णांक scpu)
अणु
	काष्ठा hrसमयr_cpu_base *old_base, *new_base;
	पूर्णांक i;

	BUG_ON(cpu_online(scpu));
	tick_cancel_sched_समयr(scpu);

	/*
	 * this BH disable ensures that उठाओ_softirq_irqoff() करोes
	 * not wakeup ksoftirqd (and acquire the pi-lock) जबतक
	 * holding the cpu_base lock
	 */
	local_bh_disable();
	local_irq_disable();
	old_base = &per_cpu(hrसमयr_bases, scpu);
	new_base = this_cpu_ptr(&hrसमयr_bases);
	/*
	 * The caller is globally serialized and nobody अन्यथा
	 * takes two locks at once, deadlock is not possible.
	 */
	raw_spin_lock(&new_base->lock);
	raw_spin_lock_nested(&old_base->lock, SINGLE_DEPTH_NESTING);

	क्रम (i = 0; i < HRTIMER_MAX_CLOCK_BASES; i++) अणु
		migrate_hrसमयr_list(&old_base->घड़ी_base[i],
				     &new_base->घड़ी_base[i]);
	पूर्ण

	/*
	 * The migration might have changed the first expiring softirq
	 * समयr on this CPU. Update it.
	 */
	hrसमयr_update_softirq_समयr(new_base, false);

	raw_spin_unlock(&old_base->lock);
	raw_spin_unlock(&new_base->lock);

	/* Check, अगर we got expired work to करो */
	__hrसमयr_peek_ahead_समयrs();
	local_irq_enable();
	local_bh_enable();
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

व्योम __init hrसमयrs_init(व्योम)
अणु
	hrसमयrs_prepare_cpu(smp_processor_id());
	खोलो_softirq(HRTIMER_SOFTIRQ, hrसमयr_run_softirq);
पूर्ण

/**
 * schedule_hrसमयout_range_घड़ी - sleep until समयout
 * @expires:	समयout value (kसमय_प्रकार)
 * @delta:	slack in expires समयout (kसमय_प्रकार)
 * @mode:	समयr mode
 * @घड़ी_id:	समयr घड़ी to be used
 */
पूर्णांक __sched
schedule_hrसमयout_range_घड़ी(kसमय_प्रकार *expires, u64 delta,
			       स्थिर क्रमागत hrसमयr_mode mode, घड़ीid_t घड़ी_id)
अणु
	काष्ठा hrसमयr_sleeper t;

	/*
	 * Optimize when a zero समयout value is given. It करोes not
	 * matter whether this is an असलolute or a relative समय.
	 */
	अगर (expires && *expires == 0) अणु
		__set_current_state(TASK_RUNNING);
		वापस 0;
	पूर्ण

	/*
	 * A शून्य parameter means "infinite"
	 */
	अगर (!expires) अणु
		schedule();
		वापस -EINTR;
	पूर्ण

	hrसमयr_init_sleeper_on_stack(&t, घड़ी_id, mode);
	hrसमयr_set_expires_range_ns(&t.समयr, *expires, delta);
	hrसमयr_sleeper_start_expires(&t, mode);

	अगर (likely(t.task))
		schedule();

	hrसमयr_cancel(&t.समयr);
	destroy_hrसमयr_on_stack(&t.समयr);

	__set_current_state(TASK_RUNNING);

	वापस !t.task ? 0 : -EINTR;
पूर्ण

/**
 * schedule_hrसमयout_range - sleep until समयout
 * @expires:	समयout value (kसमय_प्रकार)
 * @delta:	slack in expires समयout (kसमय_प्रकार)
 * @mode:	समयr mode
 *
 * Make the current task sleep until the given expiry समय has
 * elapsed. The routine will वापस immediately unless
 * the current task state has been set (see set_current_state()).
 *
 * The @delta argument gives the kernel the मुक्तकरोm to schedule the
 * actual wakeup to a समय that is both घातer and perक्रमmance मित्रly.
 * The kernel give the normal best efक्रमt behavior क्रम "@expires+@delta",
 * but may decide to fire the समयr earlier, but no earlier than @expires.
 *
 * You can set the task state as follows -
 *
 * %TASK_UNINTERRUPTIBLE - at least @समयout समय is guaranteed to
 * pass beक्रमe the routine वापसs unless the current task is explicitly
 * woken up, (e.g. by wake_up_process()).
 *
 * %TASK_INTERRUPTIBLE - the routine may वापस early अगर a संकेत is
 * delivered to the current task or the current task is explicitly woken
 * up.
 *
 * The current task state is guaranteed to be TASK_RUNNING when this
 * routine वापसs.
 *
 * Returns 0 when the समयr has expired. If the task was woken beक्रमe the
 * समयr expired by a संकेत (only possible in state TASK_INTERRUPTIBLE) or
 * by an explicit wakeup, it वापसs -EINTR.
 */
पूर्णांक __sched schedule_hrसमयout_range(kसमय_प्रकार *expires, u64 delta,
				     स्थिर क्रमागत hrसमयr_mode mode)
अणु
	वापस schedule_hrसमयout_range_घड़ी(expires, delta, mode,
					      CLOCK_MONOTONIC);
पूर्ण
EXPORT_SYMBOL_GPL(schedule_hrसमयout_range);

/**
 * schedule_hrसमयout - sleep until समयout
 * @expires:	समयout value (kसमय_प्रकार)
 * @mode:	समयr mode
 *
 * Make the current task sleep until the given expiry समय has
 * elapsed. The routine will वापस immediately unless
 * the current task state has been set (see set_current_state()).
 *
 * You can set the task state as follows -
 *
 * %TASK_UNINTERRUPTIBLE - at least @समयout समय is guaranteed to
 * pass beक्रमe the routine वापसs unless the current task is explicitly
 * woken up, (e.g. by wake_up_process()).
 *
 * %TASK_INTERRUPTIBLE - the routine may वापस early अगर a संकेत is
 * delivered to the current task or the current task is explicitly woken
 * up.
 *
 * The current task state is guaranteed to be TASK_RUNNING when this
 * routine वापसs.
 *
 * Returns 0 when the समयr has expired. If the task was woken beक्रमe the
 * समयr expired by a संकेत (only possible in state TASK_INTERRUPTIBLE) or
 * by an explicit wakeup, it वापसs -EINTR.
 */
पूर्णांक __sched schedule_hrसमयout(kसमय_प्रकार *expires,
			       स्थिर क्रमागत hrसमयr_mode mode)
अणु
	वापस schedule_hrसमयout_range(expires, 0, mode);
पूर्ण
EXPORT_SYMBOL_GPL(schedule_hrसमयout);
