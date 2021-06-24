<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2016,2017 IBM Corporation.
 */

#घोषणा pr_fmt(fmt) "xive: " fmt

#समावेश <linux/types.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/irq.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/msi.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/xive.h>
#समावेश <यंत्र/xive-regs.h>
#समावेश <यंत्र/xmon.h>

#समावेश "xive-internal.h"

#अघोषित DEBUG_FLUSH
#अघोषित DEBUG_ALL

#अगर_घोषित DEBUG_ALL
#घोषणा DBG_VERBOSE(fmt, ...)	pr_devel("cpu %d - " fmt, \
					 smp_processor_id(), ## __VA_ARGS__)
#अन्यथा
#घोषणा DBG_VERBOSE(fmt...)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

bool __xive_enabled;
EXPORT_SYMBOL_GPL(__xive_enabled);
bool xive_cmdline_disabled;

/* We use only one priority क्रम now */
अटल u8 xive_irq_priority;

/* TIMA exported to KVM */
व्योम __iomem *xive_tima;
EXPORT_SYMBOL_GPL(xive_tima);
u32 xive_tima_offset;

/* Backend ops */
अटल स्थिर काष्ठा xive_ops *xive_ops;

/* Our global पूर्णांकerrupt करोमुख्य */
अटल काष्ठा irq_करोमुख्य *xive_irq_करोमुख्य;

#अगर_घोषित CONFIG_SMP
/* The IPIs use the same logical irq number when on the same chip */
अटल काष्ठा xive_ipi_desc अणु
	अचिन्हित पूर्णांक irq;
	अक्षर name[16];
पूर्ण *xive_ipis;

/*
 * Use early_cpu_to_node() क्रम hot-plugged CPUs
 */
अटल अचिन्हित पूर्णांक xive_ipi_cpu_to_irq(अचिन्हित पूर्णांक cpu)
अणु
	वापस xive_ipis[early_cpu_to_node(cpu)].irq;
पूर्ण
#पूर्ण_अगर

/* Xive state क्रम each CPU */
अटल DEFINE_PER_CPU(काष्ठा xive_cpu *, xive_cpu);

/* An invalid CPU target */
#घोषणा XIVE_INVALID_TARGET	(-1)

/*
 * Read the next entry in a queue, वापस its content अगर it's valid
 * or 0 अगर there is no new entry.
 *
 * The queue poपूर्णांकer is moved क्रमward unless "just_peek" is set
 */
अटल u32 xive_पढ़ो_eq(काष्ठा xive_q *q, bool just_peek)
अणु
	u32 cur;

	अगर (!q->qpage)
		वापस 0;
	cur = be32_to_cpup(q->qpage + q->idx);

	/* Check valid bit (31) vs current toggle polarity */
	अगर ((cur >> 31) == q->toggle)
		वापस 0;

	/* If consuming from the queue ... */
	अगर (!just_peek) अणु
		/* Next entry */
		q->idx = (q->idx + 1) & q->msk;

		/* Wrap around: flip valid toggle */
		अगर (q->idx == 0)
			q->toggle ^= 1;
	पूर्ण
	/* Mask out the valid bit (31) */
	वापस cur & 0x7fffffff;
पूर्ण

/*
 * Scans all the queue that may have पूर्णांकerrupts in them
 * (based on "pending_prio") in priority order until an
 * पूर्णांकerrupt is found or all the queues are empty.
 *
 * Then updates the CPPR (Current Processor Priority
 * Register) based on the most favored पूर्णांकerrupt found
 * (0xff अगर none) and वापस what was found (0 अगर none).
 *
 * If just_peek is set, वापस the most favored pending
 * पूर्णांकerrupt अगर any but करोn't update the queue poपूर्णांकers.
 *
 * Note: This function can operate generically on any number
 * of queues (up to 8). The current implementation of the XIVE
 * driver only uses a single queue however.
 *
 * Note2: This will also "flush" "the pending_count" of a queue
 * पूर्णांकo the "count" when that queue is observed to be empty.
 * This is used to keep track of the amount of पूर्णांकerrupts
 * targetting a queue. When an पूर्णांकerrupt is moved away from
 * a queue, we only decrement that queue count once the queue
 * has been observed empty to aव्योम races.
 */
अटल u32 xive_scan_पूर्णांकerrupts(काष्ठा xive_cpu *xc, bool just_peek)
अणु
	u32 irq = 0;
	u8 prio = 0;

	/* Find highest pending priority */
	जबतक (xc->pending_prio != 0) अणु
		काष्ठा xive_q *q;

		prio = ffs(xc->pending_prio) - 1;
		DBG_VERBOSE("scan_irq: trying prio %d\n", prio);

		/* Try to fetch */
		irq = xive_पढ़ो_eq(&xc->queue[prio], just_peek);

		/* Found something ? That's it */
		अगर (irq) अणु
			अगर (just_peek || irq_to_desc(irq))
				अवरोध;
			/*
			 * We should never get here; अगर we करो then we must
			 * have failed to synchronize the पूर्णांकerrupt properly
			 * when shutting it करोwn.
			 */
			pr_crit("xive: got interrupt %d without descriptor, dropping\n",
				irq);
			WARN_ON(1);
			जारी;
		पूर्ण

		/* Clear pending bits */
		xc->pending_prio &= ~(1 << prio);

		/*
		 * Check अगर the queue count needs adjusting due to
		 * पूर्णांकerrupts being moved away. See description of
		 * xive_dec_target_count()
		 */
		q = &xc->queue[prio];
		अगर (atomic_पढ़ो(&q->pending_count)) अणु
			पूर्णांक p = atomic_xchg(&q->pending_count, 0);
			अगर (p) अणु
				WARN_ON(p > atomic_पढ़ो(&q->count));
				atomic_sub(p, &q->count);
			पूर्ण
		पूर्ण
	पूर्ण

	/* If nothing was found, set CPPR to 0xff */
	अगर (irq == 0)
		prio = 0xff;

	/* Update HW CPPR to match अगर necessary */
	अगर (prio != xc->cppr) अणु
		DBG_VERBOSE("scan_irq: adjusting CPPR to %d\n", prio);
		xc->cppr = prio;
		out_8(xive_tima + xive_tima_offset + TM_CPPR, prio);
	पूर्ण

	वापस irq;
पूर्ण

/*
 * This is used to perक्रमm the magic loads from an ESB
 * described in xive-regs.h
 */
अटल notrace u8 xive_esb_पढ़ो(काष्ठा xive_irq_data *xd, u32 offset)
अणु
	u64 val;

	अगर (offset == XIVE_ESB_SET_PQ_10 && xd->flags & XIVE_IRQ_FLAG_STORE_EOI)
		offset |= XIVE_ESB_LD_ST_MO;

	अगर ((xd->flags & XIVE_IRQ_FLAG_H_INT_ESB) && xive_ops->esb_rw)
		val = xive_ops->esb_rw(xd->hw_irq, offset, 0, 0);
	अन्यथा
		val = in_be64(xd->eoi_mmio + offset);

	वापस (u8)val;
पूर्ण

अटल व्योम xive_esb_ग_लिखो(काष्ठा xive_irq_data *xd, u32 offset, u64 data)
अणु
	अगर ((xd->flags & XIVE_IRQ_FLAG_H_INT_ESB) && xive_ops->esb_rw)
		xive_ops->esb_rw(xd->hw_irq, offset, data, 1);
	अन्यथा
		out_be64(xd->eoi_mmio + offset, data);
पूर्ण

#अगर_घोषित CONFIG_XMON
अटल notrace व्योम xive_dump_eq(स्थिर अक्षर *name, काष्ठा xive_q *q)
अणु
	u32 i0, i1, idx;

	अगर (!q->qpage)
		वापस;
	idx = q->idx;
	i0 = be32_to_cpup(q->qpage + idx);
	idx = (idx + 1) & q->msk;
	i1 = be32_to_cpup(q->qpage + idx);
	xmon_म_लिखो("%s idx=%d T=%d %08x %08x ...", name,
		     q->idx, q->toggle, i0, i1);
पूर्ण

notrace व्योम xmon_xive_करो_dump(पूर्णांक cpu)
अणु
	काष्ठा xive_cpu *xc = per_cpu(xive_cpu, cpu);

	xmon_म_लिखो("CPU %d:", cpu);
	अगर (xc) अणु
		xmon_म_लिखो("pp=%02x CPPR=%02x ", xc->pending_prio, xc->cppr);

#अगर_घोषित CONFIG_SMP
		अणु
			u64 val = xive_esb_पढ़ो(&xc->ipi_data, XIVE_ESB_GET);

			xmon_म_लिखो("IPI=0x%08x PQ=%c%c ", xc->hw_ipi,
				    val & XIVE_ESB_VAL_P ? 'P' : '-',
				    val & XIVE_ESB_VAL_Q ? 'Q' : '-');
		पूर्ण
#पूर्ण_अगर
		xive_dump_eq("EQ", &xc->queue[xive_irq_priority]);
	पूर्ण
	xmon_म_लिखो("\n");
पूर्ण

अटल काष्ठा irq_data *xive_get_irq_data(u32 hw_irq)
अणु
	अचिन्हित पूर्णांक irq = irq_find_mapping(xive_irq_करोमुख्य, hw_irq);

	वापस irq ? irq_get_irq_data(irq) : शून्य;
पूर्ण

पूर्णांक xmon_xive_get_irq_config(u32 hw_irq, काष्ठा irq_data *d)
अणु
	पूर्णांक rc;
	u32 target;
	u8 prio;
	u32 lirq;

	rc = xive_ops->get_irq_config(hw_irq, &target, &prio, &lirq);
	अगर (rc) अणु
		xmon_म_लिखो("IRQ 0x%08x : no config rc=%d\n", hw_irq, rc);
		वापस rc;
	पूर्ण

	xmon_म_लिखो("IRQ 0x%08x : target=0x%x prio=%02x lirq=0x%x ",
		    hw_irq, target, prio, lirq);

	अगर (!d)
		d = xive_get_irq_data(hw_irq);

	अगर (d) अणु
		काष्ठा xive_irq_data *xd = irq_data_get_irq_handler_data(d);
		u64 val = xive_esb_पढ़ो(xd, XIVE_ESB_GET);

		xmon_म_लिखो("flags=%c%c%c PQ=%c%c",
			    xd->flags & XIVE_IRQ_FLAG_STORE_EOI ? 'S' : ' ',
			    xd->flags & XIVE_IRQ_FLAG_LSI ? 'L' : ' ',
			    xd->flags & XIVE_IRQ_FLAG_H_INT_ESB ? 'H' : ' ',
			    val & XIVE_ESB_VAL_P ? 'P' : '-',
			    val & XIVE_ESB_VAL_Q ? 'Q' : '-');
	पूर्ण

	xmon_म_लिखो("\n");
	वापस 0;
पूर्ण

व्योम xmon_xive_get_irq_all(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा irq_desc *desc;

	क्रम_each_irq_desc(i, desc) अणु
		काष्ठा irq_data *d = irq_desc_get_irq_data(desc);
		अचिन्हित पूर्णांक hwirq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);

		अगर (d->करोमुख्य == xive_irq_करोमुख्य)
			xmon_xive_get_irq_config(hwirq, d);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_XMON */

अटल अचिन्हित पूर्णांक xive_get_irq(व्योम)
अणु
	काष्ठा xive_cpu *xc = __this_cpu_पढ़ो(xive_cpu);
	u32 irq;

	/*
	 * This can be called either as a result of a HW पूर्णांकerrupt or
	 * as a "replay" because EOI decided there was still something
	 * in one of the queues.
	 *
	 * First we perक्रमm an ACK cycle in order to update our mask
	 * of pending priorities. This will also have the effect of
	 * updating the CPPR to the most favored pending पूर्णांकerrupts.
	 *
	 * In the future, अगर we have a way to dअगरferentiate a first
	 * entry (on HW पूर्णांकerrupt) from a replay triggered by EOI,
	 * we could skip this on replays unless we soft-mask tells us
	 * that a new HW पूर्णांकerrupt occurred.
	 */
	xive_ops->update_pending(xc);

	DBG_VERBOSE("get_irq: pending=%02x\n", xc->pending_prio);

	/* Scan our queue(s) क्रम पूर्णांकerrupts */
	irq = xive_scan_पूर्णांकerrupts(xc, false);

	DBG_VERBOSE("get_irq: got irq 0x%x, new pending=0x%02x\n",
	    irq, xc->pending_prio);

	/* Return pending पूर्णांकerrupt अगर any */
	अगर (irq == XIVE_BAD_IRQ)
		वापस 0;
	वापस irq;
पूर्ण

/*
 * After EOI'ing an पूर्णांकerrupt, we need to re-check the queue
 * to see अगर another पूर्णांकerrupt is pending since multiple
 * पूर्णांकerrupts can coalesce पूर्णांकo a single notअगरication to the
 * CPU.
 *
 * If we find that there is indeed more in there, we call
 * क्रमce_बाह्यal_irq_replay() to make Linux synthetize an
 * बाह्यal पूर्णांकerrupt on the next call to local_irq_restore().
 */
अटल व्योम xive_करो_queue_eoi(काष्ठा xive_cpu *xc)
अणु
	अगर (xive_scan_पूर्णांकerrupts(xc, true) != 0) अणु
		DBG_VERBOSE("eoi: pending=0x%02x\n", xc->pending_prio);
		क्रमce_बाह्यal_irq_replay();
	पूर्ण
पूर्ण

/*
 * EOI an पूर्णांकerrupt at the source. There are several methods
 * to करो this depending on the HW version and source type
 */
अटल व्योम xive_करो_source_eoi(काष्ठा xive_irq_data *xd)
अणु
	u8 eoi_val;

	xd->stale_p = false;

	/* If the XIVE supports the new "store EOI facility, use it */
	अगर (xd->flags & XIVE_IRQ_FLAG_STORE_EOI) अणु
		xive_esb_ग_लिखो(xd, XIVE_ESB_STORE_EOI, 0);
		वापस;
	पूर्ण

	/*
	 * For LSIs, we use the "EOI cycle" special load rather than
	 * PQ bits, as they are स्वतःmatically re-triggered in HW when
	 * still pending.
	 */
	अगर (xd->flags & XIVE_IRQ_FLAG_LSI) अणु
		xive_esb_पढ़ो(xd, XIVE_ESB_LOAD_EOI);
		वापस;
	पूर्ण

	/*
	 * Otherwise, we use the special MMIO that करोes a clear of
	 * both P and Q and वापसs the old Q. This allows us to then
	 * करो a re-trigger अगर Q was set rather than synthesizing an
	 * पूर्णांकerrupt in software
	 */
	eoi_val = xive_esb_पढ़ो(xd, XIVE_ESB_SET_PQ_00);
	DBG_VERBOSE("eoi_val=%x\n", eoi_val);

	/* Re-trigger अगर needed */
	अगर ((eoi_val & XIVE_ESB_VAL_Q) && xd->trig_mmio)
		out_be64(xd->trig_mmio, 0);
पूर्ण

/* irq_chip eoi callback, called with irq descriptor lock held */
अटल व्योम xive_irq_eoi(काष्ठा irq_data *d)
अणु
	काष्ठा xive_irq_data *xd = irq_data_get_irq_handler_data(d);
	काष्ठा xive_cpu *xc = __this_cpu_पढ़ो(xive_cpu);

	DBG_VERBOSE("eoi_irq: irq=%d [0x%lx] pending=%02x\n",
		    d->irq, irqd_to_hwirq(d), xc->pending_prio);

	/*
	 * EOI the source अगर it hasn't been disabled and hasn't
	 * been passed-through to a KVM guest
	 */
	अगर (!irqd_irq_disabled(d) && !irqd_is_क्रमwarded_to_vcpu(d) &&
	    !(xd->flags & XIVE_IRQ_FLAG_NO_EOI))
		xive_करो_source_eoi(xd);
	अन्यथा
		xd->stale_p = true;

	/*
	 * Clear saved_p to indicate that it's no दीर्घer occupying
	 * a queue slot on the target queue
	 */
	xd->saved_p = false;

	/* Check क्रम more work in the queue */
	xive_करो_queue_eoi(xc);
पूर्ण

/*
 * Helper used to mask and unmask an पूर्णांकerrupt source.
 */
अटल व्योम xive_करो_source_set_mask(काष्ठा xive_irq_data *xd,
				    bool mask)
अणु
	u64 val;

	/*
	 * If the पूर्णांकerrupt had P set, it may be in a queue.
	 *
	 * We need to make sure we करोn't re-enable it until it
	 * has been fetched from that queue and EOId. We keep
	 * a copy of that P state and use it to restore the
	 * ESB accordingly on unmask.
	 */
	अगर (mask) अणु
		val = xive_esb_पढ़ो(xd, XIVE_ESB_SET_PQ_01);
		अगर (!xd->stale_p && !!(val & XIVE_ESB_VAL_P))
			xd->saved_p = true;
		xd->stale_p = false;
	पूर्ण अन्यथा अगर (xd->saved_p) अणु
		xive_esb_पढ़ो(xd, XIVE_ESB_SET_PQ_10);
		xd->saved_p = false;
	पूर्ण अन्यथा अणु
		xive_esb_पढ़ो(xd, XIVE_ESB_SET_PQ_00);
		xd->stale_p = false;
	पूर्ण
पूर्ण

/*
 * Try to chose "cpu" as a new पूर्णांकerrupt target. Increments
 * the queue accounting क्रम that target अगर it's not alपढ़ोy
 * full.
 */
अटल bool xive_try_pick_target(पूर्णांक cpu)
अणु
	काष्ठा xive_cpu *xc = per_cpu(xive_cpu, cpu);
	काष्ठा xive_q *q = &xc->queue[xive_irq_priority];
	पूर्णांक max;

	/*
	 * Calculate max number of पूर्णांकerrupts in that queue.
	 *
	 * We leave a gap of 1 just in हाल...
	 */
	max = (q->msk + 1) - 1;
	वापस !!atomic_add_unless(&q->count, 1, max);
पूर्ण

/*
 * Un-account an पूर्णांकerrupt क्रम a target CPU. We करोn't directly
 * decrement q->count since the पूर्णांकerrupt might still be present
 * in the queue.
 *
 * Instead increment a separate counter "pending_count" which
 * will be substracted from "count" later when that CPU observes
 * the queue to be empty.
 */
अटल व्योम xive_dec_target_count(पूर्णांक cpu)
अणु
	काष्ठा xive_cpu *xc = per_cpu(xive_cpu, cpu);
	काष्ठा xive_q *q = &xc->queue[xive_irq_priority];

	अगर (WARN_ON(cpu < 0 || !xc)) अणु
		pr_err("%s: cpu=%d xc=%p\n", __func__, cpu, xc);
		वापस;
	पूर्ण

	/*
	 * We increment the "pending count" which will be used
	 * to decrement the target queue count whenever it's next
	 * processed and found empty. This ensure that we करोn't
	 * decrement जबतक we still have the पूर्णांकerrupt there
	 * occupying a slot.
	 */
	atomic_inc(&q->pending_count);
पूर्ण

/* Find a tentative CPU target in a CPU mask */
अटल पूर्णांक xive_find_target_in_mask(स्थिर काष्ठा cpumask *mask,
				    अचिन्हित पूर्णांक fuzz)
अणु
	पूर्णांक cpu, first, num, i;

	/* Pick up a starting poपूर्णांक CPU in the mask based on  fuzz */
	num = min_t(पूर्णांक, cpumask_weight(mask), nr_cpu_ids);
	first = fuzz % num;

	/* Locate it */
	cpu = cpumask_first(mask);
	क्रम (i = 0; i < first && cpu < nr_cpu_ids; i++)
		cpu = cpumask_next(cpu, mask);

	/* Sanity check */
	अगर (WARN_ON(cpu >= nr_cpu_ids))
		cpu = cpumask_first(cpu_online_mask);

	/* Remember first one to handle wrap-around */
	first = cpu;

	/*
	 * Now go through the entire mask until we find a valid
	 * target.
	 */
	करो अणु
		/*
		 * We re-check online as the fallback हाल passes us
		 * an untested affinity mask
		 */
		अगर (cpu_online(cpu) && xive_try_pick_target(cpu))
			वापस cpu;
		cpu = cpumask_next(cpu, mask);
		/* Wrap around */
		अगर (cpu >= nr_cpu_ids)
			cpu = cpumask_first(mask);
	पूर्ण जबतक (cpu != first);

	वापस -1;
पूर्ण

/*
 * Pick a target CPU क्रम an पूर्णांकerrupt. This is करोne at
 * startup or अगर the affinity is changed in a way that
 * invalidates the current target.
 */
अटल पूर्णांक xive_pick_irq_target(काष्ठा irq_data *d,
				स्थिर काष्ठा cpumask *affinity)
अणु
	अटल अचिन्हित पूर्णांक fuzz;
	काष्ठा xive_irq_data *xd = irq_data_get_irq_handler_data(d);
	cpumask_var_t mask;
	पूर्णांक cpu = -1;

	/*
	 * If we have chip IDs, first we try to build a mask of
	 * CPUs matching the CPU and find a target in there
	 */
	अगर (xd->src_chip != XIVE_INVALID_CHIP_ID &&
		zalloc_cpumask_var(&mask, GFP_ATOMIC)) अणु
		/* Build a mask of matching chip IDs */
		क्रम_each_cpu_and(cpu, affinity, cpu_online_mask) अणु
			काष्ठा xive_cpu *xc = per_cpu(xive_cpu, cpu);
			अगर (xc->chip_id == xd->src_chip)
				cpumask_set_cpu(cpu, mask);
		पूर्ण
		/* Try to find a target */
		अगर (cpumask_empty(mask))
			cpu = -1;
		अन्यथा
			cpu = xive_find_target_in_mask(mask, fuzz++);
		मुक्त_cpumask_var(mask);
		अगर (cpu >= 0)
			वापस cpu;
		fuzz--;
	पूर्ण

	/* No chip IDs, fallback to using the affinity mask */
	वापस xive_find_target_in_mask(affinity, fuzz++);
पूर्ण

अटल अचिन्हित पूर्णांक xive_irq_startup(काष्ठा irq_data *d)
अणु
	काष्ठा xive_irq_data *xd = irq_data_get_irq_handler_data(d);
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);
	पूर्णांक target, rc;

	xd->saved_p = false;
	xd->stale_p = false;
	pr_devel("xive_irq_startup: irq %d [0x%x] data @%p\n",
		 d->irq, hw_irq, d);

#अगर_घोषित CONFIG_PCI_MSI
	/*
	 * The generic MSI code वापसs with the पूर्णांकerrupt disabled on the
	 * card, using the MSI mask bits. Firmware करोesn't appear to unmask
	 * at that level, so we करो it here by hand.
	 */
	अगर (irq_data_get_msi_desc(d))
		pci_msi_unmask_irq(d);
#पूर्ण_अगर

	/* Pick a target */
	target = xive_pick_irq_target(d, irq_data_get_affinity_mask(d));
	अगर (target == XIVE_INVALID_TARGET) अणु
		/* Try again अवरोधing affinity */
		target = xive_pick_irq_target(d, cpu_online_mask);
		अगर (target == XIVE_INVALID_TARGET)
			वापस -ENXIO;
		pr_warn("irq %d started with broken affinity\n", d->irq);
	पूर्ण

	/* Sanity check */
	अगर (WARN_ON(target == XIVE_INVALID_TARGET ||
		    target >= nr_cpu_ids))
		target = smp_processor_id();

	xd->target = target;

	/*
	 * Configure the logical number to be the Linux IRQ number
	 * and set the target queue
	 */
	rc = xive_ops->configure_irq(hw_irq,
				     get_hard_smp_processor_id(target),
				     xive_irq_priority, d->irq);
	अगर (rc)
		वापस rc;

	/* Unmask the ESB */
	xive_करो_source_set_mask(xd, false);

	वापस 0;
पूर्ण

/* called with irq descriptor lock held */
अटल व्योम xive_irq_shutकरोwn(काष्ठा irq_data *d)
अणु
	काष्ठा xive_irq_data *xd = irq_data_get_irq_handler_data(d);
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);

	pr_devel("xive_irq_shutdown: irq %d [0x%x] data @%p\n",
		 d->irq, hw_irq, d);

	अगर (WARN_ON(xd->target == XIVE_INVALID_TARGET))
		वापस;

	/* Mask the पूर्णांकerrupt at the source */
	xive_करो_source_set_mask(xd, true);

	/*
	 * Mask the पूर्णांकerrupt in HW in the IVT/EAS and set the number
	 * to be the "bad" IRQ number
	 */
	xive_ops->configure_irq(hw_irq,
				get_hard_smp_processor_id(xd->target),
				0xff, XIVE_BAD_IRQ);

	xive_dec_target_count(xd->target);
	xd->target = XIVE_INVALID_TARGET;
पूर्ण

अटल व्योम xive_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा xive_irq_data *xd = irq_data_get_irq_handler_data(d);

	pr_devel("xive_irq_unmask: irq %d data @%p\n", d->irq, xd);

	xive_करो_source_set_mask(xd, false);
पूर्ण

अटल व्योम xive_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा xive_irq_data *xd = irq_data_get_irq_handler_data(d);

	pr_devel("xive_irq_mask: irq %d data @%p\n", d->irq, xd);

	xive_करो_source_set_mask(xd, true);
पूर्ण

अटल पूर्णांक xive_irq_set_affinity(काष्ठा irq_data *d,
				 स्थिर काष्ठा cpumask *cpumask,
				 bool क्रमce)
अणु
	काष्ठा xive_irq_data *xd = irq_data_get_irq_handler_data(d);
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);
	u32 target, old_target;
	पूर्णांक rc = 0;

	pr_devel("xive_irq_set_affinity: irq %d\n", d->irq);

	/* Is this valid ? */
	अगर (cpumask_any_and(cpumask, cpu_online_mask) >= nr_cpu_ids)
		वापस -EINVAL;

	/* Don't do anything if the interrupt isn't started */
	अगर (!irqd_is_started(d))
		वापस IRQ_SET_MASK_OK;

	/*
	 * If existing target is alपढ़ोy in the new mask, and is
	 * online then करो nothing.
	 */
	अगर (xd->target != XIVE_INVALID_TARGET &&
	    cpu_online(xd->target) &&
	    cpumask_test_cpu(xd->target, cpumask))
		वापस IRQ_SET_MASK_OK;

	/* Pick a new target */
	target = xive_pick_irq_target(d, cpumask);

	/* No target found */
	अगर (target == XIVE_INVALID_TARGET)
		वापस -ENXIO;

	/* Sanity check */
	अगर (WARN_ON(target >= nr_cpu_ids))
		target = smp_processor_id();

	old_target = xd->target;

	/*
	 * Only configure the irq अगर it's not currently passed-through to
	 * a KVM guest
	 */
	अगर (!irqd_is_क्रमwarded_to_vcpu(d))
		rc = xive_ops->configure_irq(hw_irq,
					     get_hard_smp_processor_id(target),
					     xive_irq_priority, d->irq);
	अगर (rc < 0) अणु
		pr_err("Error %d reconfiguring irq %d\n", rc, d->irq);
		वापस rc;
	पूर्ण

	pr_devel("  target: 0x%x\n", target);
	xd->target = target;

	/* Give up previous target */
	अगर (old_target != XIVE_INVALID_TARGET)
	    xive_dec_target_count(old_target);

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल पूर्णांक xive_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा xive_irq_data *xd = irq_data_get_irq_handler_data(d);

	/*
	 * We only support these. This has really no effect other than setting
	 * the corresponding descriptor bits mind you but those will in turn
	 * affect the resend function when re-enabling an edge पूर्णांकerrupt.
	 *
	 * Set set the शेष to edge as explained in map().
	 */
	अगर (flow_type == IRQ_TYPE_DEFAULT || flow_type == IRQ_TYPE_NONE)
		flow_type = IRQ_TYPE_EDGE_RISING;

	अगर (flow_type != IRQ_TYPE_EDGE_RISING &&
	    flow_type != IRQ_TYPE_LEVEL_LOW)
		वापस -EINVAL;

	irqd_set_trigger_type(d, flow_type);

	/*
	 * Double check it matches what the FW thinks
	 *
	 * NOTE: We करोn't know yet अगर the PAPR पूर्णांकerface will provide
	 * the LSI vs MSI inक्रमmation apart from the device-tree so
	 * this check might have to move पूर्णांकo an optional backend call
	 * that is specअगरic to the native backend
	 */
	अगर ((flow_type == IRQ_TYPE_LEVEL_LOW) !=
	    !!(xd->flags & XIVE_IRQ_FLAG_LSI)) अणु
		pr_warn("Interrupt %d (HW 0x%x) type mismatch, Linux says %s, FW says %s\n",
			d->irq, (u32)irqd_to_hwirq(d),
			(flow_type == IRQ_TYPE_LEVEL_LOW) ? "Level" : "Edge",
			(xd->flags & XIVE_IRQ_FLAG_LSI) ? "Level" : "Edge");
	पूर्ण

	वापस IRQ_SET_MASK_OK_NOCOPY;
पूर्ण

अटल पूर्णांक xive_irq_retrigger(काष्ठा irq_data *d)
अणु
	काष्ठा xive_irq_data *xd = irq_data_get_irq_handler_data(d);

	/* This should be only क्रम MSIs */
	अगर (WARN_ON(xd->flags & XIVE_IRQ_FLAG_LSI))
		वापस 0;

	/*
	 * To perक्रमm a retrigger, we first set the PQ bits to
	 * 11, then perक्रमm an EOI.
	 */
	xive_esb_पढ़ो(xd, XIVE_ESB_SET_PQ_11);
	xive_करो_source_eoi(xd);

	वापस 1;
पूर्ण

/*
 * Caller holds the irq descriptor lock, so this won't be called
 * concurrently with xive_get_irqchip_state on the same पूर्णांकerrupt.
 */
अटल पूर्णांक xive_irq_set_vcpu_affinity(काष्ठा irq_data *d, व्योम *state)
अणु
	काष्ठा xive_irq_data *xd = irq_data_get_irq_handler_data(d);
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);
	पूर्णांक rc;
	u8 pq;

	/*
	 * This is called by KVM with state non-शून्य क्रम enabling
	 * pass-through or शून्य क्रम disabling it
	 */
	अगर (state) अणु
		irqd_set_क्रमwarded_to_vcpu(d);

		/* Set it to PQ=10 state to prevent further sends */
		pq = xive_esb_पढ़ो(xd, XIVE_ESB_SET_PQ_10);
		अगर (!xd->stale_p) अणु
			xd->saved_p = !!(pq & XIVE_ESB_VAL_P);
			xd->stale_p = !xd->saved_p;
		पूर्ण

		/* No target ? nothing to करो */
		अगर (xd->target == XIVE_INVALID_TARGET) अणु
			/*
			 * An untargetted पूर्णांकerrupt should have been
			 * also masked at the source
			 */
			WARN_ON(xd->saved_p);

			वापस 0;
		पूर्ण

		/*
		 * If P was set, adjust state to PQ=11 to indicate
		 * that a resend is needed क्रम the पूर्णांकerrupt to reach
		 * the guest. Also remember the value of P.
		 *
		 * This also tells us that it's in flight to a host queue
		 * or has alपढ़ोy been fetched but hasn't been EOIed yet
		 * by the host. This it's potentially using up a host
		 * queue slot. This is important to know because as दीर्घ
		 * as this is the हाल, we must not hard-unmask it when
		 * "returning" that पूर्णांकerrupt to the host.
		 *
		 * This saved_p is cleared by the host EOI, when we know
		 * क्रम sure the queue slot is no दीर्घer in use.
		 */
		अगर (xd->saved_p) अणु
			xive_esb_पढ़ो(xd, XIVE_ESB_SET_PQ_11);

			/*
			 * Sync the XIVE source HW to ensure the पूर्णांकerrupt
			 * has gone through the EAS beक्रमe we change its
			 * target to the guest. That should guarantee us
			 * that we *will* eventually get an EOI क्रम it on
			 * the host. Otherwise there would be a small winकरोw
			 * क्रम P to be seen here but the पूर्णांकerrupt going
			 * to the guest queue.
			 */
			अगर (xive_ops->sync_source)
				xive_ops->sync_source(hw_irq);
		पूर्ण
	पूर्ण अन्यथा अणु
		irqd_clr_क्रमwarded_to_vcpu(d);

		/* No host target ? hard mask and वापस */
		अगर (xd->target == XIVE_INVALID_TARGET) अणु
			xive_करो_source_set_mask(xd, true);
			वापस 0;
		पूर्ण

		/*
		 * Sync the XIVE source HW to ensure the पूर्णांकerrupt
		 * has gone through the EAS beक्रमe we change its
		 * target to the host.
		 */
		अगर (xive_ops->sync_source)
			xive_ops->sync_source(hw_irq);

		/*
		 * By convention we are called with the पूर्णांकerrupt in
		 * a PQ=10 or PQ=11 state, ie, it won't fire and will
		 * have latched in Q whether there's a pending HW
		 * पूर्णांकerrupt or not.
		 *
		 * First reconfigure the target.
		 */
		rc = xive_ops->configure_irq(hw_irq,
					     get_hard_smp_processor_id(xd->target),
					     xive_irq_priority, d->irq);
		अगर (rc)
			वापस rc;

		/*
		 * Then अगर saved_p is not set, effectively re-enable the
		 * पूर्णांकerrupt with an EOI. If it is set, we know there is
		 * still a message in a host queue somewhere that will be
		 * EOId eventually.
		 *
		 * Note: We करोn't check irqd_irq_disabled(). Effectively,
		 * we *will* let the irq get through even अगर masked अगर the
		 * HW is still firing it in order to deal with the whole
		 * saved_p business properly. If the पूर्णांकerrupt triggers
		 * जबतक masked, the generic code will re-mask it anyway.
		 */
		अगर (!xd->saved_p)
			xive_करो_source_eoi(xd);

	पूर्ण
	वापस 0;
पूर्ण

/* Called with irq descriptor lock held. */
अटल पूर्णांक xive_get_irqchip_state(काष्ठा irq_data *data,
				  क्रमागत irqchip_irq_state which, bool *state)
अणु
	काष्ठा xive_irq_data *xd = irq_data_get_irq_handler_data(data);
	u8 pq;

	चयन (which) अणु
	हाल IRQCHIP_STATE_ACTIVE:
		pq = xive_esb_पढ़ो(xd, XIVE_ESB_GET);

		/*
		 * The esb value being all 1's means we couldn't get
		 * the PQ state of the पूर्णांकerrupt through mmio. It may
		 * happen, क्रम example when querying a PHB पूर्णांकerrupt
		 * जबतक the PHB is in an error state. We consider the
		 * पूर्णांकerrupt to be inactive in that हाल.
		 */
		*state = (pq != XIVE_ESB_INVALID) && !xd->stale_p &&
			(xd->saved_p || !!(pq & XIVE_ESB_VAL_P));
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip xive_irq_chip = अणु
	.name = "XIVE-IRQ",
	.irq_startup = xive_irq_startup,
	.irq_shutकरोwn = xive_irq_shutकरोwn,
	.irq_eoi = xive_irq_eoi,
	.irq_mask = xive_irq_mask,
	.irq_unmask = xive_irq_unmask,
	.irq_set_affinity = xive_irq_set_affinity,
	.irq_set_type = xive_irq_set_type,
	.irq_retrigger = xive_irq_retrigger,
	.irq_set_vcpu_affinity = xive_irq_set_vcpu_affinity,
	.irq_get_irqchip_state = xive_get_irqchip_state,
पूर्ण;

bool is_xive_irq(काष्ठा irq_chip *chip)
अणु
	वापस chip == &xive_irq_chip;
पूर्ण
EXPORT_SYMBOL_GPL(is_xive_irq);

व्योम xive_cleanup_irq_data(काष्ठा xive_irq_data *xd)
अणु
	अगर (xd->eoi_mmio) अणु
		iounmap(xd->eoi_mmio);
		अगर (xd->eoi_mmio == xd->trig_mmio)
			xd->trig_mmio = शून्य;
		xd->eoi_mmio = शून्य;
	पूर्ण
	अगर (xd->trig_mmio) अणु
		iounmap(xd->trig_mmio);
		xd->trig_mmio = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(xive_cleanup_irq_data);

अटल पूर्णांक xive_irq_alloc_data(अचिन्हित पूर्णांक virq, irq_hw_number_t hw)
अणु
	काष्ठा xive_irq_data *xd;
	पूर्णांक rc;

	xd = kzalloc(माप(काष्ठा xive_irq_data), GFP_KERNEL);
	अगर (!xd)
		वापस -ENOMEM;
	rc = xive_ops->populate_irq_data(hw, xd);
	अगर (rc) अणु
		kमुक्त(xd);
		वापस rc;
	पूर्ण
	xd->target = XIVE_INVALID_TARGET;
	irq_set_handler_data(virq, xd);

	/*
	 * Turn OFF by शेष the पूर्णांकerrupt being mapped. A side
	 * effect of this check is the mapping the ESB page of the
	 * पूर्णांकerrupt in the Linux address space. This prevents page
	 * fault issues in the crash handler which masks all
	 * पूर्णांकerrupts.
	 */
	xive_esb_पढ़ो(xd, XIVE_ESB_SET_PQ_01);

	वापस 0;
पूर्ण

अटल व्योम xive_irq_मुक्त_data(अचिन्हित पूर्णांक virq)
अणु
	काष्ठा xive_irq_data *xd = irq_get_handler_data(virq);

	अगर (!xd)
		वापस;
	irq_set_handler_data(virq, शून्य);
	xive_cleanup_irq_data(xd);
	kमुक्त(xd);
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल व्योम xive_cause_ipi(पूर्णांक cpu)
अणु
	काष्ठा xive_cpu *xc;
	काष्ठा xive_irq_data *xd;

	xc = per_cpu(xive_cpu, cpu);

	DBG_VERBOSE("IPI CPU %d -> %d (HW IRQ 0x%x)\n",
		    smp_processor_id(), cpu, xc->hw_ipi);

	xd = &xc->ipi_data;
	अगर (WARN_ON(!xd->trig_mmio))
		वापस;
	out_be64(xd->trig_mmio, 0);
पूर्ण

अटल irqवापस_t xive_muxed_ipi_action(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस smp_ipi_demux();
पूर्ण

अटल व्योम xive_ipi_eoi(काष्ठा irq_data *d)
अणु
	काष्ठा xive_cpu *xc = __this_cpu_पढ़ो(xive_cpu);

	/* Handle possible race with unplug and drop stale IPIs */
	अगर (!xc)
		वापस;

	DBG_VERBOSE("IPI eoi: irq=%d [0x%lx] (HW IRQ 0x%x) pending=%02x\n",
		    d->irq, irqd_to_hwirq(d), xc->hw_ipi, xc->pending_prio);

	xive_करो_source_eoi(&xc->ipi_data);
	xive_करो_queue_eoi(xc);
पूर्ण

अटल व्योम xive_ipi_करो_nothing(काष्ठा irq_data *d)
अणु
	/*
	 * Nothing to करो, we never mask/unmask IPIs, but the callback
	 * has to exist क्रम the काष्ठा irq_chip.
	 */
पूर्ण

अटल काष्ठा irq_chip xive_ipi_chip = अणु
	.name = "XIVE-IPI",
	.irq_eoi = xive_ipi_eoi,
	.irq_mask = xive_ipi_करो_nothing,
	.irq_unmask = xive_ipi_करो_nothing,
पूर्ण;

/*
 * IPIs are marked per-cpu. We use separate HW पूर्णांकerrupts under the
 * hood but associated with the same "linux" पूर्णांकerrupt
 */
काष्ठा xive_ipi_alloc_info अणु
	irq_hw_number_t hwirq;
पूर्ण;

अटल पूर्णांक xive_ipi_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				     अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा xive_ipi_alloc_info *info = arg;
	पूर्णांक i;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_करोमुख्य_set_info(करोमुख्य, virq + i, info->hwirq + i, &xive_ipi_chip,
				    करोमुख्य->host_data, handle_percpu_irq,
				    शून्य, शून्य);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops xive_ipi_irq_करोमुख्य_ops = अणु
	.alloc  = xive_ipi_irq_करोमुख्य_alloc,
पूर्ण;

अटल पूर्णांक __init xive_request_ipi(व्योम)
अणु
	काष्ठा fwnode_handle *fwnode;
	काष्ठा irq_करोमुख्य *ipi_करोमुख्य;
	अचिन्हित पूर्णांक node;
	पूर्णांक ret = -ENOMEM;

	fwnode = irq_करोमुख्य_alloc_named_fwnode("XIVE-IPI");
	अगर (!fwnode)
		जाओ out;

	ipi_करोमुख्य = irq_करोमुख्य_create_linear(fwnode, nr_node_ids,
					      &xive_ipi_irq_करोमुख्य_ops, शून्य);
	अगर (!ipi_करोमुख्य)
		जाओ out_मुक्त_fwnode;

	xive_ipis = kसुस्मृति(nr_node_ids, माप(*xive_ipis), GFP_KERNEL | __GFP_NOFAIL);
	अगर (!xive_ipis)
		जाओ out_मुक्त_करोमुख्य;

	क्रम_each_node(node) अणु
		काष्ठा xive_ipi_desc *xid = &xive_ipis[node];
		काष्ठा xive_ipi_alloc_info info = अणु node पूर्ण;

		/* Skip nodes without CPUs */
		अगर (cpumask_empty(cpumask_of_node(node)))
			जारी;

		/*
		 * Map one IPI पूर्णांकerrupt per node क्रम all cpus of that node.
		 * Since the HW पूर्णांकerrupt number करोesn't have any meaning,
		 * simply use the node number.
		 */
		xid->irq = irq_करोमुख्य_alloc_irqs(ipi_करोमुख्य, 1, node, &info);
		अगर (xid->irq < 0) अणु
			ret = xid->irq;
			जाओ out_मुक्त_xive_ipis;
		पूर्ण

		snम_लिखो(xid->name, माप(xid->name), "IPI-%d", node);

		ret = request_irq(xid->irq, xive_muxed_ipi_action,
				  IRQF_PERCPU | IRQF_NO_THREAD, xid->name, शून्य);

		WARN(ret < 0, "Failed to request IPI %d: %d\n", xid->irq, ret);
	पूर्ण

	वापस ret;

out_मुक्त_xive_ipis:
	kमुक्त(xive_ipis);
out_मुक्त_करोमुख्य:
	irq_करोमुख्य_हटाओ(ipi_करोमुख्य);
out_मुक्त_fwnode:
	irq_करोमुख्य_मुक्त_fwnode(fwnode);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक xive_setup_cpu_ipi(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक xive_ipi_irq = xive_ipi_cpu_to_irq(cpu);
	काष्ठा xive_cpu *xc;
	पूर्णांक rc;

	pr_debug("Setting up IPI for CPU %d\n", cpu);

	xc = per_cpu(xive_cpu, cpu);

	/* Check अगर we are alपढ़ोy setup */
	अगर (xc->hw_ipi != XIVE_BAD_IRQ)
		वापस 0;

	/* Grab an IPI from the backend, this will populate xc->hw_ipi */
	अगर (xive_ops->get_ipi(cpu, xc))
		वापस -EIO;

	/*
	 * Populate the IRQ data in the xive_cpu काष्ठाure and
	 * configure the HW / enable the IPIs.
	 */
	rc = xive_ops->populate_irq_data(xc->hw_ipi, &xc->ipi_data);
	अगर (rc) अणु
		pr_err("Failed to populate IPI data on CPU %d\n", cpu);
		वापस -EIO;
	पूर्ण
	rc = xive_ops->configure_irq(xc->hw_ipi,
				     get_hard_smp_processor_id(cpu),
				     xive_irq_priority, xive_ipi_irq);
	अगर (rc) अणु
		pr_err("Failed to map IPI CPU %d\n", cpu);
		वापस -EIO;
	पूर्ण
	pr_devel("CPU %d HW IPI %x, virq %d, trig_mmio=%p\n", cpu,
	    xc->hw_ipi, xive_ipi_irq, xc->ipi_data.trig_mmio);

	/* Unmask it */
	xive_करो_source_set_mask(&xc->ipi_data, false);

	वापस 0;
पूर्ण

अटल व्योम xive_cleanup_cpu_ipi(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc)
अणु
	अचिन्हित पूर्णांक xive_ipi_irq = xive_ipi_cpu_to_irq(cpu);

	/* Disable the IPI and मुक्त the IRQ data */

	/* Alपढ़ोy cleaned up ? */
	अगर (xc->hw_ipi == XIVE_BAD_IRQ)
		वापस;

	/* Mask the IPI */
	xive_करो_source_set_mask(&xc->ipi_data, true);

	/*
	 * Note: We करोn't call xive_cleanup_irq_data() to मुक्त
	 * the mappings as this is called from an IPI on kexec
	 * which is not a safe environment to call iounmap()
	 */

	/* Deconfigure/mask in the backend */
	xive_ops->configure_irq(xc->hw_ipi, hard_smp_processor_id(),
				0xff, xive_ipi_irq);

	/* Free the IPIs in the backend */
	xive_ops->put_ipi(cpu, xc);
पूर्ण

व्योम __init xive_smp_probe(व्योम)
अणु
	smp_ops->cause_ipi = xive_cause_ipi;

	/* Register the IPI */
	xive_request_ipi();

	/* Allocate and setup IPI क्रम the boot CPU */
	xive_setup_cpu_ipi(smp_processor_id());
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

अटल पूर्णांक xive_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			       irq_hw_number_t hw)
अणु
	पूर्णांक rc;

	/*
	 * Mark पूर्णांकerrupts as edge sensitive by शेष so that resend
	 * actually works. Will fix that up below अगर needed.
	 */
	irq_clear_status_flags(virq, IRQ_LEVEL);

	rc = xive_irq_alloc_data(virq, hw);
	अगर (rc)
		वापस rc;

	irq_set_chip_and_handler(virq, &xive_irq_chip, handle_fasteoi_irq);

	वापस 0;
पूर्ण

अटल व्योम xive_irq_करोमुख्य_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq)
अणु
	xive_irq_मुक्त_data(virq);
पूर्ण

अटल पूर्णांक xive_irq_करोमुख्य_xlate(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *ct,
				 स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
				 irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_flags)

अणु
	*out_hwirq = पूर्णांकspec[0];

	/*
	 * If पूर्णांकsize is at least 2, we look क्रम the type in the second cell,
	 * we assume the LSB indicates a level पूर्णांकerrupt.
	 */
	अगर (पूर्णांकsize > 1) अणु
		अगर (पूर्णांकspec[1] & 1)
			*out_flags = IRQ_TYPE_LEVEL_LOW;
		अन्यथा
			*out_flags = IRQ_TYPE_EDGE_RISING;
	पूर्ण अन्यथा
		*out_flags = IRQ_TYPE_LEVEL_LOW;

	वापस 0;
पूर्ण

अटल पूर्णांक xive_irq_करोमुख्य_match(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *node,
				 क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	वापस xive_ops->match(node);
पूर्ण

#अगर_घोषित CONFIG_GENERIC_IRQ_DEBUGFS
अटल स्थिर अक्षर * स्थिर esb_names[] = अणु "RESET", "OFF", "PENDING", "QUEUED" पूर्ण;

अटल स्थिर काष्ठा अणु
	u64  mask;
	अक्षर *name;
पूर्ण xive_irq_flags[] = अणु
	अणु XIVE_IRQ_FLAG_STORE_EOI, "STORE_EOI" पूर्ण,
	अणु XIVE_IRQ_FLAG_LSI,       "LSI"       पूर्ण,
	अणु XIVE_IRQ_FLAG_H_INT_ESB, "H_INT_ESB" पूर्ण,
	अणु XIVE_IRQ_FLAG_NO_EOI,    "NO_EOI"    पूर्ण,
पूर्ण;

अटल व्योम xive_irq_करोमुख्य_debug_show(काष्ठा seq_file *m, काष्ठा irq_करोमुख्य *d,
				       काष्ठा irq_data *irqd, पूर्णांक ind)
अणु
	काष्ठा xive_irq_data *xd;
	u64 val;
	पूर्णांक i;

	/* No IRQ करोमुख्य level inक्रमmation. To be करोne */
	अगर (!irqd)
		वापस;

	अगर (!is_xive_irq(irq_data_get_irq_chip(irqd)))
		वापस;

	seq_म_लिखो(m, "%*sXIVE:\n", ind, "");
	ind++;

	xd = irq_data_get_irq_handler_data(irqd);
	अगर (!xd) अणु
		seq_म_लिखो(m, "%*snot assigned\n", ind, "");
		वापस;
	पूर्ण

	val = xive_esb_पढ़ो(xd, XIVE_ESB_GET);
	seq_म_लिखो(m, "%*sESB:      %s\n", ind, "", esb_names[val & 0x3]);
	seq_म_लिखो(m, "%*sPstate:   %s %s\n", ind, "", xd->stale_p ? "stale" : "",
		   xd->saved_p ? "saved" : "");
	seq_म_लिखो(m, "%*sTarget:   %d\n", ind, "", xd->target);
	seq_म_लिखो(m, "%*sChip:     %d\n", ind, "", xd->src_chip);
	seq_म_लिखो(m, "%*sTrigger:  0x%016llx\n", ind, "", xd->trig_page);
	seq_म_लिखो(m, "%*sEOI:      0x%016llx\n", ind, "", xd->eoi_page);
	seq_म_लिखो(m, "%*sFlags:    0x%llx\n", ind, "", xd->flags);
	क्रम (i = 0; i < ARRAY_SIZE(xive_irq_flags); i++) अणु
		अगर (xd->flags & xive_irq_flags[i].mask)
			seq_म_लिखो(m, "%*s%s\n", ind + 12, "", xive_irq_flags[i].name);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा irq_करोमुख्य_ops xive_irq_करोमुख्य_ops = अणु
	.match = xive_irq_करोमुख्य_match,
	.map = xive_irq_करोमुख्य_map,
	.unmap = xive_irq_करोमुख्य_unmap,
	.xlate = xive_irq_करोमुख्य_xlate,
#अगर_घोषित CONFIG_GENERIC_IRQ_DEBUGFS
	.debug_show = xive_irq_करोमुख्य_debug_show,
#पूर्ण_अगर
पूर्ण;

अटल व्योम __init xive_init_host(काष्ठा device_node *np)
अणु
	xive_irq_करोमुख्य = irq_करोमुख्य_add_nomap(np, XIVE_MAX_IRQ,
					       &xive_irq_करोमुख्य_ops, शून्य);
	अगर (WARN_ON(xive_irq_करोमुख्य == शून्य))
		वापस;
	irq_set_शेष_host(xive_irq_करोमुख्य);
पूर्ण

अटल व्योम xive_cleanup_cpu_queues(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc)
अणु
	अगर (xc->queue[xive_irq_priority].qpage)
		xive_ops->cleanup_queue(cpu, xc, xive_irq_priority);
पूर्ण

अटल पूर्णांक xive_setup_cpu_queues(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc)
अणु
	पूर्णांक rc = 0;

	/* We setup 1 queues क्रम now with a 64k page */
	अगर (!xc->queue[xive_irq_priority].qpage)
		rc = xive_ops->setup_queue(cpu, xc, xive_irq_priority);

	वापस rc;
पूर्ण

अटल पूर्णांक xive_prepare_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा xive_cpu *xc;

	xc = per_cpu(xive_cpu, cpu);
	अगर (!xc) अणु
		xc = kzalloc_node(माप(काष्ठा xive_cpu),
				  GFP_KERNEL, cpu_to_node(cpu));
		अगर (!xc)
			वापस -ENOMEM;
		xc->hw_ipi = XIVE_BAD_IRQ;
		xc->chip_id = XIVE_INVALID_CHIP_ID;
		अगर (xive_ops->prepare_cpu)
			xive_ops->prepare_cpu(cpu, xc);

		per_cpu(xive_cpu, cpu) = xc;
	पूर्ण

	/* Setup EQs अगर not alपढ़ोy */
	वापस xive_setup_cpu_queues(cpu, xc);
पूर्ण

अटल व्योम xive_setup_cpu(व्योम)
अणु
	काष्ठा xive_cpu *xc = __this_cpu_पढ़ो(xive_cpu);

	/* The backend might have additional things to करो */
	अगर (xive_ops->setup_cpu)
		xive_ops->setup_cpu(smp_processor_id(), xc);

	/* Set CPPR to 0xff to enable flow of पूर्णांकerrupts */
	xc->cppr = 0xff;
	out_8(xive_tima + xive_tima_offset + TM_CPPR, 0xff);
पूर्ण

#अगर_घोषित CONFIG_SMP
व्योम xive_smp_setup_cpu(व्योम)
अणु
	pr_devel("SMP setup CPU %d\n", smp_processor_id());

	/* This will have alपढ़ोy been करोne on the boot CPU */
	अगर (smp_processor_id() != boot_cpuid)
		xive_setup_cpu();

पूर्ण

पूर्णांक xive_smp_prepare_cpu(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक rc;

	/* Allocate per-CPU data and queues */
	rc = xive_prepare_cpu(cpu);
	अगर (rc)
		वापस rc;

	/* Allocate and setup IPI क्रम the new CPU */
	वापस xive_setup_cpu_ipi(cpu);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम xive_flush_cpu_queue(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc)
अणु
	u32 irq;

	/* We assume local irqs are disabled */
	WARN_ON(!irqs_disabled());

	/* Check what's alपढ़ोy in the CPU queue */
	जबतक ((irq = xive_scan_पूर्णांकerrupts(xc, false)) != 0) अणु
		/*
		 * We need to re-route that पूर्णांकerrupt to its new destination.
		 * First get and lock the descriptor
		 */
		काष्ठा irq_desc *desc = irq_to_desc(irq);
		काष्ठा irq_data *d = irq_desc_get_irq_data(desc);
		काष्ठा xive_irq_data *xd;

		/*
		 * Ignore anything that isn't a XIVE irq and ignore
		 * IPIs, so can just be dropped.
		 */
		अगर (d->करोमुख्य != xive_irq_करोमुख्य)
			जारी;

		/*
		 * The IRQ should have alपढ़ोy been re-routed, it's just a
		 * stale in the old queue, so re-trigger it in order to make
		 * it reach is new destination.
		 */
#अगर_घोषित DEBUG_FLUSH
		pr_info("CPU %d: Got irq %d while offline, re-sending...\n",
			cpu, irq);
#पूर्ण_अगर
		raw_spin_lock(&desc->lock);
		xd = irq_desc_get_handler_data(desc);

		/*
		 * Clear saved_p to indicate that it's no दीर्घer pending
		 */
		xd->saved_p = false;

		/*
		 * For LSIs, we EOI, this will cause a resend अगर it's
		 * still निश्चितed. Otherwise करो an MSI retrigger.
		 */
		अगर (xd->flags & XIVE_IRQ_FLAG_LSI)
			xive_करो_source_eoi(xd);
		अन्यथा
			xive_irq_retrigger(d);

		raw_spin_unlock(&desc->lock);
	पूर्ण
पूर्ण

व्योम xive_smp_disable_cpu(व्योम)
अणु
	काष्ठा xive_cpu *xc = __this_cpu_पढ़ो(xive_cpu);
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	/* Migrate पूर्णांकerrupts away from the CPU */
	irq_migrate_all_off_this_cpu();

	/* Set CPPR to 0 to disable flow of पूर्णांकerrupts */
	xc->cppr = 0;
	out_8(xive_tima + xive_tima_offset + TM_CPPR, 0);

	/* Flush everything still in the queue */
	xive_flush_cpu_queue(cpu, xc);

	/* Re-enable CPPR  */
	xc->cppr = 0xff;
	out_8(xive_tima + xive_tima_offset + TM_CPPR, 0xff);
पूर्ण

व्योम xive_flush_पूर्णांकerrupt(व्योम)
अणु
	काष्ठा xive_cpu *xc = __this_cpu_पढ़ो(xive_cpu);
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	/* Called अगर an पूर्णांकerrupt occurs जबतक the CPU is hot unplugged */
	xive_flush_cpu_queue(cpu, xc);
पूर्ण

#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

#पूर्ण_अगर /* CONFIG_SMP */

व्योम xive_tearकरोwn_cpu(व्योम)
अणु
	काष्ठा xive_cpu *xc = __this_cpu_पढ़ो(xive_cpu);
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	/* Set CPPR to 0 to disable flow of पूर्णांकerrupts */
	xc->cppr = 0;
	out_8(xive_tima + xive_tima_offset + TM_CPPR, 0);

	अगर (xive_ops->tearकरोwn_cpu)
		xive_ops->tearकरोwn_cpu(cpu, xc);

#अगर_घोषित CONFIG_SMP
	/* Get rid of IPI */
	xive_cleanup_cpu_ipi(cpu, xc);
#पूर्ण_अगर

	/* Disable and मुक्त the queues */
	xive_cleanup_cpu_queues(cpu, xc);
पूर्ण

व्योम xive_shutकरोwn(व्योम)
अणु
	xive_ops->shutकरोwn();
पूर्ण

bool __init xive_core_init(काष्ठा device_node *np, स्थिर काष्ठा xive_ops *ops,
			   व्योम __iomem *area, u32 offset, u8 max_prio)
अणु
	xive_tima = area;
	xive_tima_offset = offset;
	xive_ops = ops;
	xive_irq_priority = max_prio;

	ppc_md.get_irq = xive_get_irq;
	__xive_enabled = true;

	pr_devel("Initializing host..\n");
	xive_init_host(np);

	pr_devel("Initializing boot CPU..\n");

	/* Allocate per-CPU data and queues */
	xive_prepare_cpu(smp_processor_id());

	/* Get पढ़ोy क्रम पूर्णांकerrupts */
	xive_setup_cpu();

	pr_info("Interrupt handling initialized with %s backend\n",
		xive_ops->name);
	pr_info("Using priority %d for all interrupts\n", max_prio);

	वापस true;
पूर्ण

__be32 *xive_queue_page_alloc(अचिन्हित पूर्णांक cpu, u32 queue_shअगरt)
अणु
	अचिन्हित पूर्णांक alloc_order;
	काष्ठा page *pages;
	__be32 *qpage;

	alloc_order = xive_alloc_order(queue_shअगरt);
	pages = alloc_pages_node(cpu_to_node(cpu), GFP_KERNEL, alloc_order);
	अगर (!pages)
		वापस ERR_PTR(-ENOMEM);
	qpage = (__be32 *)page_address(pages);
	स_रखो(qpage, 0, 1 << queue_shअगरt);

	वापस qpage;
पूर्ण

अटल पूर्णांक __init xive_off(अक्षर *arg)
अणु
	xive_cmdline_disabled = true;
	वापस 0;
पूर्ण
__setup("xive=off", xive_off);

अटल व्योम xive_debug_show_cpu(काष्ठा seq_file *m, पूर्णांक cpu)
अणु
	काष्ठा xive_cpu *xc = per_cpu(xive_cpu, cpu);

	seq_म_लिखो(m, "CPU %d:", cpu);
	अगर (xc) अणु
		seq_म_लिखो(m, "pp=%02x CPPR=%02x ", xc->pending_prio, xc->cppr);

#अगर_घोषित CONFIG_SMP
		अणु
			u64 val = xive_esb_पढ़ो(&xc->ipi_data, XIVE_ESB_GET);

			seq_म_लिखो(m, "IPI=0x%08x PQ=%c%c ", xc->hw_ipi,
				   val & XIVE_ESB_VAL_P ? 'P' : '-',
				   val & XIVE_ESB_VAL_Q ? 'Q' : '-');
		पूर्ण
#पूर्ण_अगर
		अणु
			काष्ठा xive_q *q = &xc->queue[xive_irq_priority];
			u32 i0, i1, idx;

			अगर (q->qpage) अणु
				idx = q->idx;
				i0 = be32_to_cpup(q->qpage + idx);
				idx = (idx + 1) & q->msk;
				i1 = be32_to_cpup(q->qpage + idx);
				seq_म_लिखो(m, "EQ idx=%d T=%d %08x %08x ...",
					   q->idx, q->toggle, i0, i1);
			पूर्ण
		पूर्ण
	पूर्ण
	seq_माला_दो(m, "\n");
पूर्ण

अटल व्योम xive_debug_show_irq(काष्ठा seq_file *m, काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);
	पूर्णांक rc;
	u32 target;
	u8 prio;
	u32 lirq;
	काष्ठा xive_irq_data *xd;
	u64 val;

	rc = xive_ops->get_irq_config(hw_irq, &target, &prio, &lirq);
	अगर (rc) अणु
		seq_म_लिखो(m, "IRQ 0x%08x : no config rc=%d\n", hw_irq, rc);
		वापस;
	पूर्ण

	seq_म_लिखो(m, "IRQ 0x%08x : target=0x%x prio=%02x lirq=0x%x ",
		   hw_irq, target, prio, lirq);

	xd = irq_data_get_irq_handler_data(d);
	val = xive_esb_पढ़ो(xd, XIVE_ESB_GET);
	seq_म_लिखो(m, "flags=%c%c%c PQ=%c%c",
		   xd->flags & XIVE_IRQ_FLAG_STORE_EOI ? 'S' : ' ',
		   xd->flags & XIVE_IRQ_FLAG_LSI ? 'L' : ' ',
		   xd->flags & XIVE_IRQ_FLAG_H_INT_ESB ? 'H' : ' ',
		   val & XIVE_ESB_VAL_P ? 'P' : '-',
		   val & XIVE_ESB_VAL_Q ? 'Q' : '-');
	seq_माला_दो(m, "\n");
पूर्ण

अटल पूर्णांक xive_core_debug_show(काष्ठा seq_file *m, व्योम *निजी)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा irq_desc *desc;
	पूर्णांक cpu;

	अगर (xive_ops->debug_show)
		xive_ops->debug_show(m, निजी);

	क्रम_each_possible_cpu(cpu)
		xive_debug_show_cpu(m, cpu);

	क्रम_each_irq_desc(i, desc) अणु
		काष्ठा irq_data *d = irq_desc_get_irq_data(desc);

		अगर (d->करोमुख्य == xive_irq_करोमुख्य)
			xive_debug_show_irq(m, d);
	पूर्ण
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(xive_core_debug);

पूर्णांक xive_core_debug_init(व्योम)
अणु
	अगर (xive_enabled())
		debugfs_create_file("xive", 0400, घातerpc_debugfs_root,
				    शून्य, &xive_core_debug_fops);
	वापस 0;
पूर्ण
