<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 Red Hat, Inc., Peter Zijlstra
 *
 * Provides a framework क्रम enqueueing and running callbacks from hardirq
 * context. The enqueueing is NMI-safe.
 */

#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/percpu.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/sched.h>
#समावेश <linux/tick.h>
#समावेश <linux/cpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/kasan.h>

अटल DEFINE_PER_CPU(काष्ठा llist_head, उठाओd_list);
अटल DEFINE_PER_CPU(काष्ठा llist_head, lazy_list);

/*
 * Claim the entry so that no one अन्यथा will poke at it.
 */
अटल bool irq_work_claim(काष्ठा irq_work *work)
अणु
	पूर्णांक oflags;

	oflags = atomic_fetch_or(IRQ_WORK_CLAIMED | CSD_TYPE_IRQ_WORK, &work->node.a_flags);
	/*
	 * If the work is alपढ़ोy pending, no need to उठाओ the IPI.
	 * The pairing smp_mb() in irq_work_single() makes sure
	 * everything we did beक्रमe is visible.
	 */
	अगर (oflags & IRQ_WORK_PENDING)
		वापस false;
	वापस true;
पूर्ण

व्योम __weak arch_irq_work_उठाओ(व्योम)
अणु
	/*
	 * Lame architectures will get the समयr tick callback
	 */
पूर्ण

/* Enqueue on current CPU, work must alपढ़ोy be claimed and preempt disabled */
अटल व्योम __irq_work_queue_local(काष्ठा irq_work *work)
अणु
	/* If the work is "lazy", handle it from next tick अगर any */
	अगर (atomic_पढ़ो(&work->node.a_flags) & IRQ_WORK_LAZY) अणु
		अगर (llist_add(&work->node.llist, this_cpu_ptr(&lazy_list)) &&
		    tick_nohz_tick_stopped())
			arch_irq_work_उठाओ();
	पूर्ण अन्यथा अणु
		अगर (llist_add(&work->node.llist, this_cpu_ptr(&उठाओd_list)))
			arch_irq_work_उठाओ();
	पूर्ण
पूर्ण

/* Enqueue the irq work @work on the current CPU */
bool irq_work_queue(काष्ठा irq_work *work)
अणु
	/* Only queue अगर not alपढ़ोy pending */
	अगर (!irq_work_claim(work))
		वापस false;

	/* Queue the entry and उठाओ the IPI अगर needed. */
	preempt_disable();
	__irq_work_queue_local(work);
	preempt_enable();

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(irq_work_queue);

/*
 * Enqueue the irq_work @work on @cpu unless it's alपढ़ोy pending
 * somewhere.
 *
 * Can be re-enqueued जबतक the callback is still in progress.
 */
bool irq_work_queue_on(काष्ठा irq_work *work, पूर्णांक cpu)
अणु
#अगर_अघोषित CONFIG_SMP
	वापस irq_work_queue(work);

#अन्यथा /* CONFIG_SMP: */
	/* All work should have been flushed beक्रमe going offline */
	WARN_ON_ONCE(cpu_is_offline(cpu));

	/* Only queue अगर not alपढ़ोy pending */
	अगर (!irq_work_claim(work))
		वापस false;

	kasan_record_aux_stack(work);

	preempt_disable();
	अगर (cpu != smp_processor_id()) अणु
		/* Arch remote IPI send/receive backend aren't NMI safe */
		WARN_ON_ONCE(in_nmi());
		__smp_call_single_queue(cpu, &work->node.llist);
	पूर्ण अन्यथा अणु
		__irq_work_queue_local(work);
	पूर्ण
	preempt_enable();

	वापस true;
#पूर्ण_अगर /* CONFIG_SMP */
पूर्ण


bool irq_work_needs_cpu(व्योम)
अणु
	काष्ठा llist_head *उठाओd, *lazy;

	उठाओd = this_cpu_ptr(&उठाओd_list);
	lazy = this_cpu_ptr(&lazy_list);

	अगर (llist_empty(उठाओd) || arch_irq_work_has_पूर्णांकerrupt())
		अगर (llist_empty(lazy))
			वापस false;

	/* All work should have been flushed beक्रमe going offline */
	WARN_ON_ONCE(cpu_is_offline(smp_processor_id()));

	वापस true;
पूर्ण

व्योम irq_work_single(व्योम *arg)
अणु
	काष्ठा irq_work *work = arg;
	पूर्णांक flags;

	/*
	 * Clear the PENDING bit, after this poपूर्णांक the @work can be re-used.
	 * The PENDING bit acts as a lock, and we own it, so we can clear it
	 * without atomic ops.
	 */
	flags = atomic_पढ़ो(&work->node.a_flags);
	flags &= ~IRQ_WORK_PENDING;
	atomic_set(&work->node.a_flags, flags);

	/*
	 * See irq_work_claim().
	 */
	smp_mb();

	lockdep_irq_work_enter(flags);
	work->func(work);
	lockdep_irq_work_निकास(flags);

	/*
	 * Clear the BUSY bit, अगर set, and वापस to the मुक्त state अगर no-one
	 * अन्यथा claimed it meanजबतक.
	 */
	(व्योम)atomic_cmpxchg(&work->node.a_flags, flags, flags & ~IRQ_WORK_BUSY);
पूर्ण

अटल व्योम irq_work_run_list(काष्ठा llist_head *list)
अणु
	काष्ठा irq_work *work, *पंचांगp;
	काष्ठा llist_node *llnode;

	BUG_ON(!irqs_disabled());

	अगर (llist_empty(list))
		वापस;

	llnode = llist_del_all(list);
	llist_क्रम_each_entry_safe(work, पंचांगp, llnode, node.llist)
		irq_work_single(work);
पूर्ण

/*
 * hotplug calls this through:
 *  hotplug_cfd() -> flush_smp_call_function_queue()
 */
व्योम irq_work_run(व्योम)
अणु
	irq_work_run_list(this_cpu_ptr(&उठाओd_list));
	irq_work_run_list(this_cpu_ptr(&lazy_list));
पूर्ण
EXPORT_SYMBOL_GPL(irq_work_run);

व्योम irq_work_tick(व्योम)
अणु
	काष्ठा llist_head *उठाओd = this_cpu_ptr(&उठाओd_list);

	अगर (!llist_empty(उठाओd) && !arch_irq_work_has_पूर्णांकerrupt())
		irq_work_run_list(उठाओd);
	irq_work_run_list(this_cpu_ptr(&lazy_list));
पूर्ण

/*
 * Synchronize against the irq_work @entry, ensures the entry is not
 * currently in use.
 */
व्योम irq_work_sync(काष्ठा irq_work *work)
अणु
	lockdep_निश्चित_irqs_enabled();

	जबतक (irq_work_is_busy(work))
		cpu_relax();
पूर्ण
EXPORT_SYMBOL_GPL(irq_work_sync);
