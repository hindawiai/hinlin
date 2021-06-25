<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic cpu hotunplug पूर्णांकerrupt migration code copied from the
 * arch/arm implementation
 *
 * Copyright (C) Russell King
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/irq.h>
#समावेश <linux/sched/isolation.h>

#समावेश "internals.h"

/* For !GENERIC_IRQ_EFFECTIVE_AFF_MASK this looks at general affinity mask */
अटल अंतरभूत bool irq_needs_fixup(काष्ठा irq_data *d)
अणु
	स्थिर काष्ठा cpumask *m = irq_data_get_effective_affinity_mask(d);
	अचिन्हित पूर्णांक cpu = smp_processor_id();

#अगर_घोषित CONFIG_GENERIC_IRQ_EFFECTIVE_AFF_MASK
	/*
	 * The cpumask_empty() check is a workaround क्रम पूर्णांकerrupt chips,
	 * which करो not implement effective affinity, but the architecture has
	 * enabled the config चयन. Use the general affinity mask instead.
	 */
	अगर (cpumask_empty(m))
		m = irq_data_get_affinity_mask(d);

	/*
	 * Sanity check. If the mask is not empty when excluding the outgoing
	 * CPU then it must contain at least one online CPU. The outgoing CPU
	 * has been हटाओd from the online mask alपढ़ोy.
	 */
	अगर (cpumask_any_but(m, cpu) < nr_cpu_ids &&
	    cpumask_any_and(m, cpu_online_mask) >= nr_cpu_ids) अणु
		/*
		 * If this happens then there was a missed IRQ fixup at some
		 * poपूर्णांक. Warn about it and enक्रमce fixup.
		 */
		pr_warn("Eff. affinity %*pbl of IRQ %u contains only offline CPUs after offlining CPU %u\n",
			cpumask_pr_args(m), d->irq, cpu);
		वापस true;
	पूर्ण
#पूर्ण_अगर
	वापस cpumask_test_cpu(cpu, m);
पूर्ण

अटल bool migrate_one_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_data *d = irq_desc_get_irq_data(desc);
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(d);
	bool maskchip = !irq_can_move_pcntxt(d) && !irqd_irq_masked(d);
	स्थिर काष्ठा cpumask *affinity;
	bool brokeaff = false;
	पूर्णांक err;

	/*
	 * IRQ chip might be alपढ़ोy torn करोwn, but the irq descriptor is
	 * still in the radix tree. Also अगर the chip has no affinity setter,
	 * nothing can be करोne here.
	 */
	अगर (!chip || !chip->irq_set_affinity) अणु
		pr_debug("IRQ %u: Unable to migrate away\n", d->irq);
		वापस false;
	पूर्ण

	/*
	 * No move required, अगर:
	 * - Interrupt is per cpu
	 * - Interrupt is not started
	 * - Affinity mask करोes not include this CPU.
	 *
	 * Note: Do not check desc->action as this might be a chained
	 * पूर्णांकerrupt.
	 */
	अगर (irqd_is_per_cpu(d) || !irqd_is_started(d) || !irq_needs_fixup(d)) अणु
		/*
		 * If an irq move is pending, पात it अगर the dying CPU is
		 * the sole target.
		 */
		irq_fixup_move_pending(desc, false);
		वापस false;
	पूर्ण

	/*
	 * Complete an eventually pending irq move cleanup. If this
	 * पूर्णांकerrupt was moved in hard irq context, then the vectors need
	 * to be cleaned up. It can't रुको until this पूर्णांकerrupt actually
	 * happens and this CPU was involved.
	 */
	irq_क्रमce_complete_move(desc);

	/*
	 * If there is a setaffinity pending, then try to reuse the pending
	 * mask, so the last change of the affinity करोes not get lost. If
	 * there is no move pending or the pending mask करोes not contain
	 * any online CPU, use the current affinity mask.
	 */
	अगर (irq_fixup_move_pending(desc, true))
		affinity = irq_desc_get_pending_mask(desc);
	अन्यथा
		affinity = irq_data_get_affinity_mask(d);

	/* Mask the chip क्रम पूर्णांकerrupts which cannot move in process context */
	अगर (maskchip && chip->irq_mask)
		chip->irq_mask(d);

	अगर (cpumask_any_and(affinity, cpu_online_mask) >= nr_cpu_ids) अणु
		/*
		 * If the पूर्णांकerrupt is managed, then shut it करोwn and leave
		 * the affinity untouched.
		 */
		अगर (irqd_affinity_is_managed(d)) अणु
			irqd_set_managed_shutकरोwn(d);
			irq_shutकरोwn_and_deactivate(desc);
			वापस false;
		पूर्ण
		affinity = cpu_online_mask;
		brokeaff = true;
	पूर्ण
	/*
	 * Do not set the क्रमce argument of irq_करो_set_affinity() as this
	 * disables the masking of offline CPUs from the supplied affinity
	 * mask and thereक्रमe might keep/reassign the irq to the outgoing
	 * CPU.
	 */
	err = irq_करो_set_affinity(d, affinity, false);
	अगर (err) अणु
		pr_warn_ratelimited("IRQ%u: set affinity failed(%d).\n",
				    d->irq, err);
		brokeaff = false;
	पूर्ण

	अगर (maskchip && chip->irq_unmask)
		chip->irq_unmask(d);

	वापस brokeaff;
पूर्ण

/**
 * irq_migrate_all_off_this_cpu - Migrate irqs away from offline cpu
 *
 * The current CPU has been marked offline.  Migrate IRQs off this CPU.
 * If the affinity settings करो not allow other CPUs, क्रमce them onto any
 * available CPU.
 *
 * Note: we must iterate over all IRQs, whether they have an attached
 * action काष्ठाure or not, as we need to get chained पूर्णांकerrupts too.
 */
व्योम irq_migrate_all_off_this_cpu(व्योम)
अणु
	काष्ठा irq_desc *desc;
	अचिन्हित पूर्णांक irq;

	क्रम_each_active_irq(irq) अणु
		bool affinity_broken;

		desc = irq_to_desc(irq);
		raw_spin_lock(&desc->lock);
		affinity_broken = migrate_one_irq(desc);
		raw_spin_unlock(&desc->lock);

		अगर (affinity_broken) अणु
			pr_warn_ratelimited("IRQ %u: no longer affine to CPU%u\n",
					    irq, smp_processor_id());
		पूर्ण
	पूर्ण
पूर्ण

अटल bool hk_should_isolate(काष्ठा irq_data *data, अचिन्हित पूर्णांक cpu)
अणु
	स्थिर काष्ठा cpumask *hk_mask;

	अगर (!housekeeping_enabled(HK_FLAG_MANAGED_IRQ))
		वापस false;

	hk_mask = housekeeping_cpumask(HK_FLAG_MANAGED_IRQ);
	अगर (cpumask_subset(irq_data_get_effective_affinity_mask(data), hk_mask))
		वापस false;

	वापस cpumask_test_cpu(cpu, hk_mask);
पूर्ण

अटल व्योम irq_restore_affinity_of_irq(काष्ठा irq_desc *desc, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा irq_data *data = irq_desc_get_irq_data(desc);
	स्थिर काष्ठा cpumask *affinity = irq_data_get_affinity_mask(data);

	अगर (!irqd_affinity_is_managed(data) || !desc->action ||
	    !irq_data_get_irq_chip(data) || !cpumask_test_cpu(cpu, affinity))
		वापस;

	अगर (irqd_is_managed_and_shutकरोwn(data)) अणु
		irq_startup(desc, IRQ_RESEND, IRQ_START_COND);
		वापस;
	पूर्ण

	/*
	 * If the पूर्णांकerrupt can only be directed to a single target
	 * CPU then it is alपढ़ोy asचिन्हित to a CPU in the affinity
	 * mask. No poपूर्णांक in trying to move it around unless the
	 * isolation mechanism requests to move it to an upcoming
	 * housekeeping CPU.
	 */
	अगर (!irqd_is_single_target(data) || hk_should_isolate(data, cpu))
		irq_set_affinity_locked(data, affinity, false);
पूर्ण

/**
 * irq_affinity_online_cpu - Restore affinity क्रम managed पूर्णांकerrupts
 * @cpu:	Upcoming CPU क्रम which पूर्णांकerrupts should be restored
 */
पूर्णांक irq_affinity_online_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा irq_desc *desc;
	अचिन्हित पूर्णांक irq;

	irq_lock_sparse();
	क्रम_each_active_irq(irq) अणु
		desc = irq_to_desc(irq);
		raw_spin_lock_irq(&desc->lock);
		irq_restore_affinity_of_irq(desc, cpu);
		raw_spin_unlock_irq(&desc->lock);
	पूर्ण
	irq_unlock_sparse();

	वापस 0;
पूर्ण
