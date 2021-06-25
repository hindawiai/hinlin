<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_PREEMPT_H
#घोषणा __LINUX_PREEMPT_H

/*
 * include/linux/preempt.h - macros क्रम accessing and manipulating
 * preempt_count (used क्रम kernel preemption, पूर्णांकerrupt count, etc.)
 */

#समावेश <linux/linkage.h>
#समावेश <linux/list.h>

/*
 * We put the hardirq and softirq counter पूर्णांकo the preemption
 * counter. The biपंचांगask has the following meaning:
 *
 * - bits 0-7 are the preemption count (max preemption depth: 256)
 * - bits 8-15 are the softirq count (max # of softirqs: 256)
 *
 * The hardirq count could in theory be the same as the number of
 * पूर्णांकerrupts in the प्रणाली, but we run all पूर्णांकerrupt handlers with
 * पूर्णांकerrupts disabled, so we cannot have nesting पूर्णांकerrupts. Though
 * there are a few palaeontologic drivers which reenable पूर्णांकerrupts in
 * the handler, so we need more than one bit here.
 *
 *         PREEMPT_MASK:	0x000000ff
 *         SOFTIRQ_MASK:	0x0000ff00
 *         HARसूचीQ_MASK:	0x000f0000
 *             NMI_MASK:	0x00f00000
 * PREEMPT_NEED_RESCHED:	0x80000000
 */
#घोषणा PREEMPT_BITS	8
#घोषणा SOFTIRQ_BITS	8
#घोषणा HARसूचीQ_BITS	4
#घोषणा NMI_BITS	4

#घोषणा PREEMPT_SHIFT	0
#घोषणा SOFTIRQ_SHIFT	(PREEMPT_SHIFT + PREEMPT_BITS)
#घोषणा HARसूचीQ_SHIFT	(SOFTIRQ_SHIFT + SOFTIRQ_BITS)
#घोषणा NMI_SHIFT	(HARसूचीQ_SHIFT + HARसूचीQ_BITS)

#घोषणा __IRQ_MASK(x)	((1UL << (x))-1)

#घोषणा PREEMPT_MASK	(__IRQ_MASK(PREEMPT_BITS) << PREEMPT_SHIFT)
#घोषणा SOFTIRQ_MASK	(__IRQ_MASK(SOFTIRQ_BITS) << SOFTIRQ_SHIFT)
#घोषणा HARसूचीQ_MASK	(__IRQ_MASK(HARसूचीQ_BITS) << HARसूचीQ_SHIFT)
#घोषणा NMI_MASK	(__IRQ_MASK(NMI_BITS)     << NMI_SHIFT)

#घोषणा PREEMPT_OFFSET	(1UL << PREEMPT_SHIFT)
#घोषणा SOFTIRQ_OFFSET	(1UL << SOFTIRQ_SHIFT)
#घोषणा HARसूचीQ_OFFSET	(1UL << HARसूचीQ_SHIFT)
#घोषणा NMI_OFFSET	(1UL << NMI_SHIFT)

#घोषणा SOFTIRQ_DISABLE_OFFSET	(2 * SOFTIRQ_OFFSET)

#घोषणा PREEMPT_DISABLED	(PREEMPT_DISABLE_OFFSET + PREEMPT_ENABLED)

/*
 * Disable preemption until the scheduler is running -- use an unconditional
 * value so that it also works on !PREEMPT_COUNT kernels.
 *
 * Reset by start_kernel()->sched_init()->init_idle()->init_idle_preempt_count().
 */
#घोषणा INIT_PREEMPT_COUNT	PREEMPT_OFFSET

/*
 * Initial preempt_count value; reflects the preempt_count schedule invariant
 * which states that during context चयनes:
 *
 *    preempt_count() == 2*PREEMPT_DISABLE_OFFSET
 *
 * Note: PREEMPT_DISABLE_OFFSET is 0 क्रम !PREEMPT_COUNT kernels.
 * Note: See finish_task_चयन().
 */
#घोषणा FORK_PREEMPT_COUNT	(2*PREEMPT_DISABLE_OFFSET + PREEMPT_ENABLED)

/* preempt_count() and related functions, depends on PREEMPT_NEED_RESCHED */
#समावेश <यंत्र/preempt.h>

#घोषणा nmi_count()	(preempt_count() & NMI_MASK)
#घोषणा hardirq_count()	(preempt_count() & HARसूचीQ_MASK)
#अगर_घोषित CONFIG_PREEMPT_RT
# define softirq_count()	(current->softirq_disable_cnt & SOFTIRQ_MASK)
#अन्यथा
# define softirq_count()	(preempt_count() & SOFTIRQ_MASK)
#पूर्ण_अगर
#घोषणा irq_count()	(nmi_count() | hardirq_count() | softirq_count())

/*
 * Macros to retrieve the current execution context:
 *
 * in_nmi()		- We're in NMI context
 * in_hardirq()		- We're in hard IRQ context
 * in_serving_softirq()	- We're in softirq context
 * in_task()		- We're in task context
 */
#घोषणा in_nmi()		(nmi_count())
#घोषणा in_hardirq()		(hardirq_count())
#घोषणा in_serving_softirq()	(softirq_count() & SOFTIRQ_OFFSET)
#घोषणा in_task()		(!(in_nmi() | in_hardirq() | in_serving_softirq()))

/*
 * The following macros are deprecated and should not be used in new code:
 * in_irq()       - Obsolete version of in_hardirq()
 * in_softirq()   - We have BH disabled, or are processing softirqs
 * in_पूर्णांकerrupt() - We're in NMI,IRQ,SoftIRQ context or have BH disabled
 */
#घोषणा in_irq()		(hardirq_count())
#घोषणा in_softirq()		(softirq_count())
#घोषणा in_पूर्णांकerrupt()		(irq_count())

/*
 * The preempt_count offset after preempt_disable();
 */
#अगर defined(CONFIG_PREEMPT_COUNT)
# define PREEMPT_DISABLE_OFFSET	PREEMPT_OFFSET
#अन्यथा
# define PREEMPT_DISABLE_OFFSET	0
#पूर्ण_अगर

/*
 * The preempt_count offset after spin_lock()
 */
#घोषणा PREEMPT_LOCK_OFFSET	PREEMPT_DISABLE_OFFSET

/*
 * The preempt_count offset needed क्रम things like:
 *
 *  spin_lock_bh()
 *
 * Which need to disable both preemption (CONFIG_PREEMPT_COUNT) and
 * softirqs, such that unlock sequences of:
 *
 *  spin_unlock();
 *  local_bh_enable();
 *
 * Work as expected.
 */
#घोषणा SOFTIRQ_LOCK_OFFSET (SOFTIRQ_DISABLE_OFFSET + PREEMPT_LOCK_OFFSET)

/*
 * Are we running in atomic context?  WARNING: this macro cannot
 * always detect atomic context; in particular, it cannot know about
 * held spinlocks in non-preemptible kernels.  Thus it should not be
 * used in the general हाल to determine whether sleeping is possible.
 * Do not use in_atomic() in driver code.
 */
#घोषणा in_atomic()	(preempt_count() != 0)

/*
 * Check whether we were atomic beक्रमe we did preempt_disable():
 * (used by the scheduler)
 */
#घोषणा in_atomic_preempt_off() (preempt_count() != PREEMPT_DISABLE_OFFSET)

#अगर defined(CONFIG_DEBUG_PREEMPT) || defined(CONFIG_TRACE_PREEMPT_TOGGLE)
बाह्य व्योम preempt_count_add(पूर्णांक val);
बाह्य व्योम preempt_count_sub(पूर्णांक val);
#घोषणा preempt_count_dec_and_test() \
	(अणु preempt_count_sub(1); should_resched(0); पूर्ण)
#अन्यथा
#घोषणा preempt_count_add(val)	__preempt_count_add(val)
#घोषणा preempt_count_sub(val)	__preempt_count_sub(val)
#घोषणा preempt_count_dec_and_test() __preempt_count_dec_and_test()
#पूर्ण_अगर

#घोषणा __preempt_count_inc() __preempt_count_add(1)
#घोषणा __preempt_count_dec() __preempt_count_sub(1)

#घोषणा preempt_count_inc() preempt_count_add(1)
#घोषणा preempt_count_dec() preempt_count_sub(1)

#अगर_घोषित CONFIG_PREEMPT_COUNT

#घोषणा preempt_disable() \
करो अणु \
	preempt_count_inc(); \
	barrier(); \
पूर्ण जबतक (0)

#घोषणा sched_preempt_enable_no_resched() \
करो अणु \
	barrier(); \
	preempt_count_dec(); \
पूर्ण जबतक (0)

#घोषणा preempt_enable_no_resched() sched_preempt_enable_no_resched()

#घोषणा preemptible()	(preempt_count() == 0 && !irqs_disabled())

#अगर_घोषित CONFIG_PREEMPTION
#घोषणा preempt_enable() \
करो अणु \
	barrier(); \
	अगर (unlikely(preempt_count_dec_and_test())) \
		__preempt_schedule(); \
पूर्ण जबतक (0)

#घोषणा preempt_enable_notrace() \
करो अणु \
	barrier(); \
	अगर (unlikely(__preempt_count_dec_and_test())) \
		__preempt_schedule_notrace(); \
पूर्ण जबतक (0)

#घोषणा preempt_check_resched() \
करो अणु \
	अगर (should_resched(0)) \
		__preempt_schedule(); \
पूर्ण जबतक (0)

#अन्यथा /* !CONFIG_PREEMPTION */
#घोषणा preempt_enable() \
करो अणु \
	barrier(); \
	preempt_count_dec(); \
पूर्ण जबतक (0)

#घोषणा preempt_enable_notrace() \
करो अणु \
	barrier(); \
	__preempt_count_dec(); \
पूर्ण जबतक (0)

#घोषणा preempt_check_resched() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_PREEMPTION */

#घोषणा preempt_disable_notrace() \
करो अणु \
	__preempt_count_inc(); \
	barrier(); \
पूर्ण जबतक (0)

#घोषणा preempt_enable_no_resched_notrace() \
करो अणु \
	barrier(); \
	__preempt_count_dec(); \
पूर्ण जबतक (0)

#अन्यथा /* !CONFIG_PREEMPT_COUNT */

/*
 * Even अगर we करोn't have any preemption, we need preempt disable/enable
 * to be barriers, so that we करोn't have things like get_user/put_user
 * that can cause faults and scheduling migrate पूर्णांकo our preempt-रक्षित
 * region.
 */
#घोषणा preempt_disable()			barrier()
#घोषणा sched_preempt_enable_no_resched()	barrier()
#घोषणा preempt_enable_no_resched()		barrier()
#घोषणा preempt_enable()			barrier()
#घोषणा preempt_check_resched()			करो अणु पूर्ण जबतक (0)

#घोषणा preempt_disable_notrace()		barrier()
#घोषणा preempt_enable_no_resched_notrace()	barrier()
#घोषणा preempt_enable_notrace()		barrier()
#घोषणा preemptible()				0

#पूर्ण_अगर /* CONFIG_PREEMPT_COUNT */

#अगर_घोषित MODULE
/*
 * Modules have no business playing preemption tricks.
 */
#अघोषित sched_preempt_enable_no_resched
#अघोषित preempt_enable_no_resched
#अघोषित preempt_enable_no_resched_notrace
#अघोषित preempt_check_resched
#पूर्ण_अगर

#घोषणा preempt_set_need_resched() \
करो अणु \
	set_preempt_need_resched(); \
पूर्ण जबतक (0)
#घोषणा preempt_fold_need_resched() \
करो अणु \
	अगर (tअगर_need_resched()) \
		set_preempt_need_resched(); \
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_PREEMPT_NOTIFIERS

काष्ठा preempt_notअगरier;

/**
 * preempt_ops - notअगरiers called when a task is preempted and rescheduled
 * @sched_in: we're about to be rescheduled:
 *    notअगरier: काष्ठा preempt_notअगरier क्रम the task being scheduled
 *    cpu:  cpu we're scheduled on
 * @sched_out: we've just been preempted
 *    notअगरier: काष्ठा preempt_notअगरier क्रम the task being preempted
 *    next: the task that's kicking us out
 *
 * Please note that sched_in and out are called under dअगरferent
 * contexts.  sched_out is called with rq lock held and irq disabled
 * जबतक sched_in is called without rq lock and irq enabled.  This
 * dअगरference is पूर्णांकentional and depended upon by its users.
 */
काष्ठा preempt_ops अणु
	व्योम (*sched_in)(काष्ठा preempt_notअगरier *notअगरier, पूर्णांक cpu);
	व्योम (*sched_out)(काष्ठा preempt_notअगरier *notअगरier,
			  काष्ठा task_काष्ठा *next);
पूर्ण;

/**
 * preempt_notअगरier - key क्रम installing preemption notअगरiers
 * @link: पूर्णांकernal use
 * @ops: defines the notअगरier functions to be called
 *
 * Usually used in conjunction with container_of().
 */
काष्ठा preempt_notअगरier अणु
	काष्ठा hlist_node link;
	काष्ठा preempt_ops *ops;
पूर्ण;

व्योम preempt_notअगरier_inc(व्योम);
व्योम preempt_notअगरier_dec(व्योम);
व्योम preempt_notअगरier_रेजिस्टर(काष्ठा preempt_notअगरier *notअगरier);
व्योम preempt_notअगरier_unरेजिस्टर(काष्ठा preempt_notअगरier *notअगरier);

अटल अंतरभूत व्योम preempt_notअगरier_init(काष्ठा preempt_notअगरier *notअगरier,
				     काष्ठा preempt_ops *ops)
अणु
	INIT_HLIST_NODE(&notअगरier->link);
	notअगरier->ops = ops;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP

/*
 * Migrate-Disable and why it is undesired.
 *
 * When a preempted task becomes elegible to run under the ideal model (IOW it
 * becomes one of the M highest priority tasks), it might still have to रुको
 * क्रम the preemptee's migrate_disable() section to complete. Thereby suffering
 * a reduction in bandwidth in the exact duration of the migrate_disable()
 * section.
 *
 * Per this argument, the change from preempt_disable() to migrate_disable()
 * माला_लो us:
 *
 * - a higher priority tasks gains reduced wake-up latency; with preempt_disable()
 *   it would have had to रुको क्रम the lower priority task.
 *
 * - a lower priority tasks; which under preempt_disable() could've instantly
 *   migrated away when another CPU becomes available, is now स्थिरrained
 *   by the ability to push the higher priority task away, which might itself be
 *   in a migrate_disable() section, reducing it's available bandwidth.
 *
 * IOW it trades latency / moves the पूर्णांकerference term, but it stays in the
 * प्रणाली, and as दीर्घ as it reमुख्यs unbounded, the प्रणाली is not fully
 * deterministic.
 *
 *
 * The reason we have it anyway.
 *
 * PREEMPT_RT अवरोधs a number of assumptions traditionally held. By क्रमcing a
 * number of primitives पूर्णांकo becoming preemptible, they would also allow
 * migration. This turns out to अवरोध a bunch of per-cpu usage. To this end,
 * all these primitives employ migirate_disable() to restore this implicit
 * assumption.
 *
 * This is a 'temporary' work-around at best. The correct solution is getting
 * rid of the above assumptions and reworking the code to employ explicit
 * per-cpu locking or लघु preempt-disable regions.
 *
 * The end goal must be to get rid of migrate_disable(), alternatively we need
 * a schedulability theory that करोes not depend on abritrary migration.
 *
 *
 * Notes on the implementation.
 *
 * The implementation is particularly tricky since existing code patterns
 * dictate neither migrate_disable() nor migrate_enable() is allowed to block.
 * This means that it cannot use cpus_पढ़ो_lock() to serialize against hotplug,
 * nor can it easily migrate itself पूर्णांकo a pending affinity mask change on
 * migrate_enable().
 *
 *
 * Note: even non-work-conserving schedulers like semi-partitioned depends on
 *       migration, so migrate_disable() is not only a problem क्रम
 *       work-conserving schedulers.
 *
 */
बाह्य व्योम migrate_disable(व्योम);
बाह्य व्योम migrate_enable(व्योम);

#अन्यथा

अटल अंतरभूत व्योम migrate_disable(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम migrate_enable(व्योम) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

#पूर्ण_अगर /* __LINUX_PREEMPT_H */
