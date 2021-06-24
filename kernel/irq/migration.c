<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "internals.h"

/**
 * irq_fixup_move_pending - Cleanup irq move pending from a dying CPU
 * @desc:		Interrupt descriptor to clean up
 * @क्रमce_clear:	If set clear the move pending bit unconditionally.
 *			If not set, clear it only when the dying CPU is the
 *			last one in the pending mask.
 *
 * Returns true अगर the pending bit was set and the pending mask contains an
 * online CPU other than the dying CPU.
 */
bool irq_fixup_move_pending(काष्ठा irq_desc *desc, bool क्रमce_clear)
अणु
	काष्ठा irq_data *data = irq_desc_get_irq_data(desc);

	अगर (!irqd_is_setaffinity_pending(data))
		वापस false;

	/*
	 * The outgoing CPU might be the last online target in a pending
	 * पूर्णांकerrupt move. If that's the हाल clear the pending move bit.
	 */
	अगर (cpumask_any_and(desc->pending_mask, cpu_online_mask) >= nr_cpu_ids) अणु
		irqd_clr_move_pending(data);
		वापस false;
	पूर्ण
	अगर (क्रमce_clear)
		irqd_clr_move_pending(data);
	वापस true;
पूर्ण

व्योम irq_move_masked_irq(काष्ठा irq_data *idata)
अणु
	काष्ठा irq_desc *desc = irq_data_to_desc(idata);
	काष्ठा irq_data *data = &desc->irq_data;
	काष्ठा irq_chip *chip = data->chip;

	अगर (likely(!irqd_is_setaffinity_pending(data)))
		वापस;

	irqd_clr_move_pending(data);

	/*
	 * Paranoia: cpu-local पूर्णांकerrupts shouldn't be calling in here anyway.
	 */
	अगर (irqd_is_per_cpu(data)) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	अगर (unlikely(cpumask_empty(desc->pending_mask)))
		वापस;

	अगर (!chip->irq_set_affinity)
		वापस;

	निश्चित_raw_spin_locked(&desc->lock);

	/*
	 * If there was a valid mask to work with, please
	 * करो the disable, re-program, enable sequence.
	 * This is *not* particularly important क्रम level triggered
	 * but in a edge trigger हाल, we might be setting rte
	 * when an active trigger is coming in. This could
	 * cause some ioapics to mal-function.
	 * Being paranoid i guess!
	 *
	 * For correct operation this depends on the caller
	 * masking the irqs.
	 */
	अगर (cpumask_any_and(desc->pending_mask, cpu_online_mask) < nr_cpu_ids) अणु
		पूर्णांक ret;

		ret = irq_करो_set_affinity(data, desc->pending_mask, false);
		/*
		 * If the there is a cleanup pending in the underlying
		 * vector management, reschedule the move क्रम the next
		 * पूर्णांकerrupt. Leave desc->pending_mask पूर्णांकact.
		 */
		अगर (ret == -EBUSY) अणु
			irqd_set_move_pending(data);
			वापस;
		पूर्ण
	पूर्ण
	cpumask_clear(desc->pending_mask);
पूर्ण

व्योम __irq_move_irq(काष्ठा irq_data *idata)
अणु
	bool masked;

	/*
	 * Get top level irq_data when CONFIG_IRQ_DOMAIN_HIERARCHY is enabled,
	 * and it should be optimized away when CONFIG_IRQ_DOMAIN_HIERARCHY is
	 * disabled. So we aव्योम an "#ifdef CONFIG_IRQ_DOMAIN_HIERARCHY" here.
	 */
	idata = irq_desc_get_irq_data(irq_data_to_desc(idata));

	अगर (unlikely(irqd_irq_disabled(idata)))
		वापस;

	/*
	 * Be careful vs. alपढ़ोy masked पूर्णांकerrupts. If this is a
	 * thपढ़ोed पूर्णांकerrupt with ONESHOT set, we can end up with an
	 * पूर्णांकerrupt storm.
	 */
	masked = irqd_irq_masked(idata);
	अगर (!masked)
		idata->chip->irq_mask(idata);
	irq_move_masked_irq(idata);
	अगर (!masked)
		idata->chip->irq_unmask(idata);
पूर्ण
