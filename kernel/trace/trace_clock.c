<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * tracing घड़ीs
 *
 *  Copyright (C) 2009 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *
 * Implements 3 trace घड़ी variants, with dअगरfering scalability/precision
 * tradeoffs:
 *
 *  -   local: CPU-local trace घड़ी
 *  -  medium: scalable global घड़ी with some jitter
 *  -  global: globally monotonic, serialized घड़ी
 *
 * Tracer plugins will chose a शेष from these घड़ीs.
 */
#समावेश <linux/spinlock.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/module.h>
#समावेश <linux/percpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/trace_घड़ी.h>

/*
 * trace_घड़ी_local(): the simplest and least coherent tracing घड़ी.
 *
 * Useful क्रम tracing that करोes not cross to other CPUs nor
 * करोes it go through idle events.
 */
u64 notrace trace_घड़ी_local(व्योम)
अणु
	u64 घड़ी;

	/*
	 * sched_घड़ी() is an architecture implemented, fast, scalable,
	 * lockless घड़ी. It is not guaranteed to be coherent across
	 * CPUs, nor across CPU idle events.
	 */
	preempt_disable_notrace();
	घड़ी = sched_घड़ी();
	preempt_enable_notrace();

	वापस घड़ी;
पूर्ण
EXPORT_SYMBOL_GPL(trace_घड़ी_local);

/*
 * trace_घड़ी(): 'between' trace घड़ी. Not completely serialized,
 * but not completely incorrect when crossing CPUs either.
 *
 * This is based on cpu_घड़ी(), which will allow at most ~1 jअगरfy of
 * jitter between CPUs. So it's a pretty scalable घड़ी, but there
 * can be offsets in the trace data.
 */
u64 notrace trace_घड़ी(व्योम)
अणु
	वापस local_घड़ी();
पूर्ण
EXPORT_SYMBOL_GPL(trace_घड़ी);

/*
 * trace_jअगरfy_घड़ी(): Simply use jअगरfies as a घड़ी counter.
 * Note that this use of jअगरfies_64 is not completely safe on
 * 32-bit प्रणालीs. But the winकरोw is tiny, and the effect अगर
 * we are affected is that we will have an obviously bogus
 * बारtamp on a trace event - i.e. not lअगरe threatening.
 */
u64 notrace trace_घड़ी_jअगरfies(व्योम)
अणु
	वापस jअगरfies_64_to_घड़ी_प्रकार(jअगरfies_64 - INITIAL_JIFFIES);
पूर्ण
EXPORT_SYMBOL_GPL(trace_घड़ी_jअगरfies);

/*
 * trace_घड़ी_global(): special globally coherent trace घड़ी
 *
 * It has higher overhead than the other trace घड़ीs but is still
 * an order of magnitude faster than GTOD derived hardware घड़ीs.
 *
 * Used by plugins that need globally coherent बारtamps.
 */

/* keep prev_समय and lock in the same cacheline. */
अटल काष्ठा अणु
	u64 prev_समय;
	arch_spinlock_t lock;
पूर्ण trace_घड़ी_काष्ठा ____cacheline_aligned_in_smp =
	अणु
		.lock = (arch_spinlock_t)__ARCH_SPIN_LOCK_UNLOCKED,
	पूर्ण;

u64 notrace trace_घड़ी_global(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक this_cpu;
	u64 now, prev_समय;

	raw_local_irq_save(flags);

	this_cpu = raw_smp_processor_id();

	/*
	 * The global घड़ी "guarantees" that the events are ordered
	 * between CPUs. But अगर two events on two dअगरferent CPUS call
	 * trace_घड़ी_global at roughly the same समय, it really करोes
	 * not matter which one माला_लो the earlier समय. Just make sure
	 * that the same CPU will always show a monotonic घड़ी.
	 *
	 * Use a पढ़ो memory barrier to get the latest written
	 * समय that was recorded.
	 */
	smp_rmb();
	prev_समय = READ_ONCE(trace_घड़ी_काष्ठा.prev_समय);
	now = sched_घड़ी_cpu(this_cpu);

	/* Make sure that now is always greater than or equal to prev_समय */
	अगर ((s64)(now - prev_समय) < 0)
		now = prev_समय;

	/*
	 * If in an NMI context then करोnt risk lockups and simply वापस
	 * the current समय.
	 */
	अगर (unlikely(in_nmi()))
		जाओ out;

	/* Tracing can cause strange recursion, always use a try lock */
	अगर (arch_spin_trylock(&trace_घड़ी_काष्ठा.lock)) अणु
		/* Reपढ़ो prev_समय in हाल it was alपढ़ोy updated */
		prev_समय = READ_ONCE(trace_घड़ी_काष्ठा.prev_समय);
		अगर ((s64)(now - prev_समय) < 0)
			now = prev_समय;

		trace_घड़ी_काष्ठा.prev_समय = now;

		/* The unlock acts as the wmb क्रम the above rmb */
		arch_spin_unlock(&trace_घड़ी_काष्ठा.lock);
	पूर्ण
 out:
	raw_local_irq_restore(flags);

	वापस now;
पूर्ण
EXPORT_SYMBOL_GPL(trace_घड़ी_global);

अटल atomic64_t trace_counter;

/*
 * trace_घड़ी_counter(): simply an atomic counter.
 * Use the trace_counter "counter" क्रम हालs where you करो not care
 * about timings, but are पूर्णांकerested in strict ordering.
 */
u64 notrace trace_घड़ी_counter(व्योम)
अणु
	वापस atomic64_add_वापस(1, &trace_counter);
पूर्ण
