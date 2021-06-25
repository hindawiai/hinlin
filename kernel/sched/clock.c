<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sched_घड़ी() क्रम unstable CPU घड़ीs
 *
 *  Copyright (C) 2008 Red Hat, Inc., Peter Zijlstra
 *
 *  Updates and enhancements:
 *    Copyright (C) 2008 Red Hat, Inc. Steven Rostedt <srostedt@redhat.com>
 *
 * Based on code by:
 *   Ingo Molnar <mingo@redhat.com>
 *   Guillaume Chazarain <guichaz@gmail.com>
 *
 *
 * What this file implements:
 *
 * cpu_घड़ी(i) provides a fast (execution समय) high resolution
 * घड़ी with bounded drअगरt between CPUs. The value of cpu_घड़ी(i)
 * is monotonic क्रम स्थिरant i. The बारtamp वापसed is in nanoseconds.
 *
 * ######################### BIG FAT WARNING ##########################
 * # when comparing cpu_घड़ी(i) to cpu_घड़ी(j) क्रम i != j, समय can #
 * # go backwards !!                                                  #
 * ####################################################################
 *
 * There is no strict promise about the base, although it tends to start
 * at 0 on boot (but people really shouldn't rely on that).
 *
 * cpu_घड़ी(i)       -- can be used from any context, including NMI.
 * local_घड़ी()      -- is cpu_घड़ी() on the current CPU.
 *
 * sched_घड़ी_cpu(i)
 *
 * How it is implemented:
 *
 * The implementation either uses sched_घड़ी() when
 * !CONFIG_HAVE_UNSTABLE_SCHED_CLOCK, which means in that हाल the
 * sched_घड़ी() is assumed to provide these properties (mostly it means
 * the architecture provides a globally synchronized highres समय source).
 *
 * Otherwise it tries to create a semi stable घड़ी from a mixture of other
 * घड़ीs, including:
 *
 *  - GTOD (घड़ी monotonic)
 *  - sched_घड़ी()
 *  - explicit idle events
 *
 * We use GTOD as base and use sched_घड़ी() deltas to improve resolution. The
 * deltas are filtered to provide monotonicity and keeping it within an
 * expected winकरोw.
 *
 * Furthermore, explicit sleep and wakeup hooks allow us to account क्रम समय
 * that is otherwise invisible (TSC माला_लो stopped).
 *
 */
#समावेश "sched.h"
#समावेश <linux/sched_घड़ी.h>

/*
 * Scheduler घड़ी - वापसs current समय in nanosec units.
 * This is शेष implementation.
 * Architectures and sub-architectures can override this.
 */
अचिन्हित दीर्घ दीर्घ __weak sched_घड़ी(व्योम)
अणु
	वापस (अचिन्हित दीर्घ दीर्घ)(jअगरfies - INITIAL_JIFFIES)
					* (NSEC_PER_SEC / HZ);
पूर्ण
EXPORT_SYMBOL_GPL(sched_घड़ी);

अटल DEFINE_STATIC_KEY_FALSE(sched_घड़ी_running);

#अगर_घोषित CONFIG_HAVE_UNSTABLE_SCHED_CLOCK
/*
 * We must start with !__sched_घड़ी_stable because the unstable -> stable
 * transition is accurate, जबतक the stable -> unstable transition is not.
 *
 * Similarly we start with __sched_घड़ी_stable_early, thereby assuming we
 * will become stable, such that there's only a single 1 -> 0 transition.
 */
अटल DEFINE_STATIC_KEY_FALSE(__sched_घड़ी_stable);
अटल पूर्णांक __sched_घड़ी_stable_early = 1;

/*
 * We want: kसमय_get_ns() + __gtod_offset == sched_घड़ी() + __sched_घड़ी_offset
 */
__पढ़ो_mostly u64 __sched_घड़ी_offset;
अटल __पढ़ो_mostly u64 __gtod_offset;

काष्ठा sched_घड़ी_data अणु
	u64			tick_raw;
	u64			tick_gtod;
	u64			घड़ी;
पूर्ण;

अटल DEFINE_PER_CPU_SHARED_ALIGNED(काष्ठा sched_घड़ी_data, sched_घड़ी_data);

अटल अंतरभूत काष्ठा sched_घड़ी_data *this_scd(व्योम)
अणु
	वापस this_cpu_ptr(&sched_घड़ी_data);
पूर्ण

अटल अंतरभूत काष्ठा sched_घड़ी_data *cpu_sdc(पूर्णांक cpu)
अणु
	वापस &per_cpu(sched_घड़ी_data, cpu);
पूर्ण

पूर्णांक sched_घड़ी_stable(व्योम)
अणु
	वापस अटल_branch_likely(&__sched_घड़ी_stable);
पूर्ण

अटल व्योम __scd_stamp(काष्ठा sched_घड़ी_data *scd)
अणु
	scd->tick_gtod = kसमय_get_ns();
	scd->tick_raw = sched_घड़ी();
पूर्ण

अटल व्योम __set_sched_घड़ी_stable(व्योम)
अणु
	काष्ठा sched_घड़ी_data *scd;

	/*
	 * Since we're still unstable and the tick is alपढ़ोy running, we have
	 * to disable IRQs in order to get a consistent scd->tick* पढ़ोing.
	 */
	local_irq_disable();
	scd = this_scd();
	/*
	 * Attempt to make the (initial) unstable->stable transition continuous.
	 */
	__sched_घड़ी_offset = (scd->tick_gtod + __gtod_offset) - (scd->tick_raw);
	local_irq_enable();

	prपूर्णांकk(KERN_INFO "sched_clock: Marking stable (%lld, %lld)->(%lld, %lld)\n",
			scd->tick_gtod, __gtod_offset,
			scd->tick_raw,  __sched_घड़ी_offset);

	अटल_branch_enable(&__sched_घड़ी_stable);
	tick_dep_clear(TICK_DEP_BIT_CLOCK_UNSTABLE);
पूर्ण

/*
 * If we ever get here, we're screwed, because we found out -- typically after
 * the fact -- that TSC wasn't good. This means all our घड़ीsources (including
 * kसमय) could have reported wrong values.
 *
 * What we करो here is an attempt to fix up and जारी sort of where we left
 * off in a coherent manner.
 *
 * The only way to fully aव्योम अक्रमom घड़ी jumps is to boot with:
 * "tsc=unstable".
 */
अटल व्योम __sched_घड़ी_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sched_घड़ी_data *scd;
	पूर्णांक cpu;

	/* take a current बारtamp and set 'now' */
	preempt_disable();
	scd = this_scd();
	__scd_stamp(scd);
	scd->घड़ी = scd->tick_gtod + __gtod_offset;
	preempt_enable();

	/* clone to all CPUs */
	क्रम_each_possible_cpu(cpu)
		per_cpu(sched_घड़ी_data, cpu) = *scd;

	prपूर्णांकk(KERN_WARNING "TSC found unstable after boot, most likely due to broken BIOS. Use 'tsc=unstable'.\n");
	prपूर्णांकk(KERN_INFO "sched_clock: Marking unstable (%lld, %lld)<-(%lld, %lld)\n",
			scd->tick_gtod, __gtod_offset,
			scd->tick_raw,  __sched_घड़ी_offset);

	अटल_branch_disable(&__sched_घड़ी_stable);
पूर्ण

अटल DECLARE_WORK(sched_घड़ी_work, __sched_घड़ी_work);

अटल व्योम __clear_sched_घड़ी_stable(व्योम)
अणु
	अगर (!sched_घड़ी_stable())
		वापस;

	tick_dep_set(TICK_DEP_BIT_CLOCK_UNSTABLE);
	schedule_work(&sched_घड़ी_work);
पूर्ण

व्योम clear_sched_घड़ी_stable(व्योम)
अणु
	__sched_घड़ी_stable_early = 0;

	smp_mb(); /* matches sched_घड़ी_init_late() */

	अगर (अटल_key_count(&sched_घड़ी_running.key) == 2)
		__clear_sched_घड़ी_stable();
पूर्ण

अटल व्योम __sched_घड़ी_gtod_offset(व्योम)
अणु
	काष्ठा sched_घड़ी_data *scd = this_scd();

	__scd_stamp(scd);
	__gtod_offset = (scd->tick_raw + __sched_घड़ी_offset) - scd->tick_gtod;
पूर्ण

व्योम __init sched_घड़ी_init(व्योम)
अणु
	/*
	 * Set __gtod_offset such that once we mark sched_घड़ी_running,
	 * sched_घड़ी_प्रकारick() जारीs where sched_घड़ी() left off.
	 *
	 * Even अगर TSC is buggered, we're still UP at this poपूर्णांक so it
	 * can't really be out of sync.
	 */
	local_irq_disable();
	__sched_घड़ी_gtod_offset();
	local_irq_enable();

	अटल_branch_inc(&sched_घड़ी_running);
पूर्ण
/*
 * We run this as late_initcall() such that it runs after all built-in drivers,
 * notably: acpi_processor and पूर्णांकel_idle, which can mark the TSC as unstable.
 */
अटल पूर्णांक __init sched_घड़ी_init_late(व्योम)
अणु
	अटल_branch_inc(&sched_घड़ी_running);
	/*
	 * Ensure that it is impossible to not करो a अटल_key update.
	 *
	 * Either अणुset,clearपूर्ण_sched_घड़ी_stable() must see sched_घड़ी_running
	 * and करो the update, or we must see their __sched_घड़ी_stable_early
	 * and करो the update, or both.
	 */
	smp_mb(); /* matches अणुset,clearपूर्ण_sched_घड़ी_stable() */

	अगर (__sched_घड़ी_stable_early)
		__set_sched_घड़ी_stable();

	वापस 0;
पूर्ण
late_initcall(sched_घड़ी_init_late);

/*
 * min, max except they take wrapping पूर्णांकo account
 */

अटल अंतरभूत u64 wrap_min(u64 x, u64 y)
अणु
	वापस (s64)(x - y) < 0 ? x : y;
पूर्ण

अटल अंतरभूत u64 wrap_max(u64 x, u64 y)
अणु
	वापस (s64)(x - y) > 0 ? x : y;
पूर्ण

/*
 * update the percpu scd from the raw @now value
 *
 *  - filter out backward motion
 *  - use the GTOD tick value to create a winकरोw to filter crazy TSC values
 */
अटल u64 sched_घड़ी_local(काष्ठा sched_घड़ी_data *scd)
अणु
	u64 now, घड़ी, old_घड़ी, min_घड़ी, max_घड़ी, gtod;
	s64 delta;

again:
	now = sched_घड़ी();
	delta = now - scd->tick_raw;
	अगर (unlikely(delta < 0))
		delta = 0;

	old_घड़ी = scd->घड़ी;

	/*
	 * scd->घड़ी = clamp(scd->tick_gtod + delta,
	 *		      max(scd->tick_gtod, scd->घड़ी),
	 *		      scd->tick_gtod + TICK_NSEC);
	 */

	gtod = scd->tick_gtod + __gtod_offset;
	घड़ी = gtod + delta;
	min_घड़ी = wrap_max(gtod, old_घड़ी);
	max_घड़ी = wrap_max(old_घड़ी, gtod + TICK_NSEC);

	घड़ी = wrap_max(घड़ी, min_घड़ी);
	घड़ी = wrap_min(घड़ी, max_घड़ी);

	अगर (cmpxchg64(&scd->घड़ी, old_घड़ी, घड़ी) != old_घड़ी)
		जाओ again;

	वापस घड़ी;
पूर्ण

अटल u64 sched_घड़ी_remote(काष्ठा sched_घड़ी_data *scd)
अणु
	काष्ठा sched_घड़ी_data *my_scd = this_scd();
	u64 this_घड़ी, remote_घड़ी;
	u64 *ptr, old_val, val;

#अगर BITS_PER_LONG != 64
again:
	/*
	 * Careful here: The local and the remote घड़ी values need to
	 * be पढ़ो out atomic as we need to compare the values and
	 * then update either the local or the remote side. So the
	 * cmpxchg64 below only protects one पढ़ोout.
	 *
	 * We must reपढ़ो via sched_घड़ी_local() in the retry हाल on
	 * 32-bit kernels as an NMI could use sched_घड़ी_local() via the
	 * tracer and hit between the पढ़ोout of
	 * the low 32-bit and the high 32-bit portion.
	 */
	this_घड़ी = sched_घड़ी_local(my_scd);
	/*
	 * We must enक्रमce atomic पढ़ोout on 32-bit, otherwise the
	 * update on the remote CPU can hit inbetween the पढ़ोout of
	 * the low 32-bit and the high 32-bit portion.
	 */
	remote_घड़ी = cmpxchg64(&scd->घड़ी, 0, 0);
#अन्यथा
	/*
	 * On 64-bit kernels the पढ़ो of [my]scd->घड़ी is atomic versus the
	 * update, so we can aव्योम the above 32-bit dance.
	 */
	sched_घड़ी_local(my_scd);
again:
	this_घड़ी = my_scd->घड़ी;
	remote_घड़ी = scd->घड़ी;
#पूर्ण_अगर

	/*
	 * Use the opportunity that we have both locks
	 * taken to couple the two घड़ीs: we take the
	 * larger समय as the latest समय क्रम both
	 * runqueues. (this creates monotonic movement)
	 */
	अगर (likely((s64)(remote_घड़ी - this_घड़ी) < 0)) अणु
		ptr = &scd->घड़ी;
		old_val = remote_घड़ी;
		val = this_घड़ी;
	पूर्ण अन्यथा अणु
		/*
		 * Should be rare, but possible:
		 */
		ptr = &my_scd->घड़ी;
		old_val = this_घड़ी;
		val = remote_घड़ी;
	पूर्ण

	अगर (cmpxchg64(ptr, old_val, val) != old_val)
		जाओ again;

	वापस val;
पूर्ण

/*
 * Similar to cpu_घड़ी(), but requires local IRQs to be disabled.
 *
 * See cpu_घड़ी().
 */
u64 sched_घड़ी_cpu(पूर्णांक cpu)
अणु
	काष्ठा sched_घड़ी_data *scd;
	u64 घड़ी;

	अगर (sched_घड़ी_stable())
		वापस sched_घड़ी() + __sched_घड़ी_offset;

	अगर (!अटल_branch_likely(&sched_घड़ी_running))
		वापस sched_घड़ी();

	preempt_disable_notrace();
	scd = cpu_sdc(cpu);

	अगर (cpu != smp_processor_id())
		घड़ी = sched_घड़ी_remote(scd);
	अन्यथा
		घड़ी = sched_घड़ी_local(scd);
	preempt_enable_notrace();

	वापस घड़ी;
पूर्ण
EXPORT_SYMBOL_GPL(sched_घड़ी_cpu);

व्योम sched_घड़ी_प्रकारick(व्योम)
अणु
	काष्ठा sched_घड़ी_data *scd;

	अगर (sched_घड़ी_stable())
		वापस;

	अगर (!अटल_branch_likely(&sched_घड़ी_running))
		वापस;

	lockdep_निश्चित_irqs_disabled();

	scd = this_scd();
	__scd_stamp(scd);
	sched_घड़ी_local(scd);
पूर्ण

व्योम sched_घड़ी_प्रकारick_stable(व्योम)
अणु
	अगर (!sched_घड़ी_stable())
		वापस;

	/*
	 * Called under watchकरोg_lock.
	 *
	 * The watchकरोg just found this TSC to (still) be stable, so now is a
	 * good moment to update our __gtod_offset. Because once we find the
	 * TSC to be unstable, any computation will be computing crap.
	 */
	local_irq_disable();
	__sched_घड़ी_gtod_offset();
	local_irq_enable();
पूर्ण

/*
 * We are going deep-idle (irqs are disabled):
 */
व्योम sched_घड़ी_idle_sleep_event(व्योम)
अणु
	sched_घड़ी_cpu(smp_processor_id());
पूर्ण
EXPORT_SYMBOL_GPL(sched_घड़ी_idle_sleep_event);

/*
 * We just idled; resync with kसमय.
 */
व्योम sched_घड़ी_idle_wakeup_event(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	अगर (sched_घड़ी_stable())
		वापस;

	अगर (unlikely(समयkeeping_suspended))
		वापस;

	local_irq_save(flags);
	sched_घड़ी_प्रकारick();
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(sched_घड़ी_idle_wakeup_event);

#अन्यथा /* CONFIG_HAVE_UNSTABLE_SCHED_CLOCK */

व्योम __init sched_घड़ी_init(व्योम)
अणु
	अटल_branch_inc(&sched_घड़ी_running);
	local_irq_disable();
	generic_sched_घड़ी_init();
	local_irq_enable();
पूर्ण

u64 sched_घड़ी_cpu(पूर्णांक cpu)
अणु
	अगर (!अटल_branch_likely(&sched_घड़ी_running))
		वापस 0;

	वापस sched_घड़ी();
पूर्ण

#पूर्ण_अगर /* CONFIG_HAVE_UNSTABLE_SCHED_CLOCK */

/*
 * Running घड़ी - वापसs the समय that has elapsed जबतक a guest has been
 * running.
 * On a guest this value should be local_घड़ी minus the समय the guest was
 * suspended by the hypervisor (क्रम any reason).
 * On bare metal this function should वापस the same as local_घड़ी.
 * Architectures and sub-architectures can override this.
 */
u64 __weak running_घड़ी(व्योम)
अणु
	वापस local_घड़ी();
पूर्ण
