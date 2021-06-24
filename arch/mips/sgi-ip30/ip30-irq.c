<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ip30-irq.c: Highlevel पूर्णांकerrupt handling क्रम IP30 architecture.
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/percpu.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/tick.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/sgi/heart.h>

#समावेश "ip30-common.h"

काष्ठा heart_irq_data अणु
	u64	*irq_mask;
	पूर्णांक	cpu;
पूर्ण;

अटल DECLARE_BITMAP(heart_irq_map, HEART_NUM_IRQS);

अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, irq_enable_mask);

अटल अंतरभूत पूर्णांक heart_alloc_पूर्णांक(व्योम)
अणु
	पूर्णांक bit;

again:
	bit = find_first_zero_bit(heart_irq_map, HEART_NUM_IRQS);
	अगर (bit >= HEART_NUM_IRQS)
		वापस -ENOSPC;

	अगर (test_and_set_bit(bit, heart_irq_map))
		जाओ again;

	वापस bit;
पूर्ण

अटल व्योम ip30_error_irq(काष्ठा irq_desc *desc)
अणु
	u64 pending, mask, cause, error_irqs, err_reg;
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक i;

	pending = heart_पढ़ो(&heart_regs->isr);
	mask = heart_पढ़ो(&heart_regs->imr[cpu]);
	cause = heart_पढ़ो(&heart_regs->cause);
	error_irqs = (pending & HEART_L4_INT_MASK & mask);

	/* Bail अगर there's nothing to process (how did we get here, then?) */
	अगर (unlikely(!error_irqs))
		वापस;

	/* Prevent any of the error IRQs from firing again. */
	heart_ग_लिखो(mask & ~(pending), &heart_regs->imr[cpu]);

	/* Ack all error IRQs. */
	heart_ग_लिखो(HEART_L4_INT_MASK, &heart_regs->clear_isr);

	/*
	 * If we also have a cause value, then something happened, so loop
	 * through the error IRQs and report a "heart attack" क्रम each one
	 * and prपूर्णांक the value of the HEART cause रेजिस्टर.  This is really
	 * primitive right now, but it should hopefully work until a more
	 * robust error handling routine can be put together.
	 *
	 * Refer to heart.h क्रम the HC_* macros to work out the cause
	 * that got us here.
	 */
	अगर (cause) अणु
		pr_alert("IP30: CPU%d: HEART ATTACK! ISR = 0x%.16llx, IMR = 0x%.16llx, CAUSE = 0x%.16llx\n",
			 cpu, pending, mask, cause);

		अगर (cause & HC_COR_MEM_ERR) अणु
			err_reg = heart_पढ़ो(&heart_regs->mem_err_addr);
			pr_alert("  HEART_MEMERR_ADDR = 0x%.16llx\n", err_reg);
		पूर्ण

		/* i = 63; i >= 51; i-- */
		क्रम (i = HEART_ERR_MASK_END; i >= HEART_ERR_MASK_START; i--)
			अगर ((pending >> i) & 1)
				pr_alert("  HEART Error IRQ #%d\n", i);

		/* XXX: Seems possible to loop क्रमever here, so panic(). */
		panic("IP30: Fatal Error !\n");
	पूर्ण

	/* Unmask the error IRQs. */
	heart_ग_लिखो(mask, &heart_regs->imr[cpu]);
पूर्ण

अटल व्योम ip30_normal_irq(काष्ठा irq_desc *desc)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा irq_करोमुख्य *करोमुख्य;
	u64 pend, mask;
	पूर्णांक irq;

	pend = heart_पढ़ो(&heart_regs->isr);
	mask = (heart_पढ़ो(&heart_regs->imr[cpu]) &
		(HEART_L0_INT_MASK | HEART_L1_INT_MASK | HEART_L2_INT_MASK));

	pend &= mask;
	अगर (unlikely(!pend))
		वापस;

#अगर_घोषित CONFIG_SMP
	अगर (pend & BIT_ULL(HEART_L2_INT_RESCHED_CPU_0)) अणु
		heart_ग_लिखो(BIT_ULL(HEART_L2_INT_RESCHED_CPU_0),
			    &heart_regs->clear_isr);
		scheduler_ipi();
	पूर्ण अन्यथा अगर (pend & BIT_ULL(HEART_L2_INT_RESCHED_CPU_1)) अणु
		heart_ग_लिखो(BIT_ULL(HEART_L2_INT_RESCHED_CPU_1),
			    &heart_regs->clear_isr);
		scheduler_ipi();
	पूर्ण अन्यथा अगर (pend & BIT_ULL(HEART_L2_INT_CALL_CPU_0)) अणु
		heart_ग_लिखो(BIT_ULL(HEART_L2_INT_CALL_CPU_0),
			    &heart_regs->clear_isr);
		generic_smp_call_function_पूर्णांकerrupt();
	पूर्ण अन्यथा अगर (pend & BIT_ULL(HEART_L2_INT_CALL_CPU_1)) अणु
		heart_ग_लिखो(BIT_ULL(HEART_L2_INT_CALL_CPU_1),
			    &heart_regs->clear_isr);
		generic_smp_call_function_पूर्णांकerrupt();
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		करोमुख्य = irq_desc_get_handler_data(desc);
		irq = irq_linear_revmap(करोमुख्य, __ffs(pend));
		अगर (irq)
			generic_handle_irq(irq);
		अन्यथा
			spurious_पूर्णांकerrupt();
	पूर्ण
पूर्ण

अटल व्योम ip30_ack_heart_irq(काष्ठा irq_data *d)
अणु
	heart_ग_लिखो(BIT_ULL(d->hwirq), &heart_regs->clear_isr);
पूर्ण

अटल व्योम ip30_mask_heart_irq(काष्ठा irq_data *d)
अणु
	काष्ठा heart_irq_data *hd = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ *mask = &per_cpu(irq_enable_mask, hd->cpu);

	clear_bit(d->hwirq, mask);
	heart_ग_लिखो(*mask, &heart_regs->imr[hd->cpu]);
पूर्ण

अटल व्योम ip30_mask_and_ack_heart_irq(काष्ठा irq_data *d)
अणु
	काष्ठा heart_irq_data *hd = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ *mask = &per_cpu(irq_enable_mask, hd->cpu);

	clear_bit(d->hwirq, mask);
	heart_ग_लिखो(*mask, &heart_regs->imr[hd->cpu]);
	heart_ग_लिखो(BIT_ULL(d->hwirq), &heart_regs->clear_isr);
पूर्ण

अटल व्योम ip30_unmask_heart_irq(काष्ठा irq_data *d)
अणु
	काष्ठा heart_irq_data *hd = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ *mask = &per_cpu(irq_enable_mask, hd->cpu);

	set_bit(d->hwirq, mask);
	heart_ग_लिखो(*mask, &heart_regs->imr[hd->cpu]);
पूर्ण

अटल पूर्णांक ip30_set_heart_irq_affinity(काष्ठा irq_data *d,
				       स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	काष्ठा heart_irq_data *hd = irq_data_get_irq_chip_data(d);

	अगर (!hd)
		वापस -EINVAL;

	अगर (irqd_is_started(d))
		ip30_mask_and_ack_heart_irq(d);

	hd->cpu = cpumask_first_and(mask, cpu_online_mask);

	अगर (irqd_is_started(d))
		ip30_unmask_heart_irq(d);

	irq_data_update_effective_affinity(d, cpumask_of(hd->cpu));

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip heart_irq_chip = अणु
	.name			= "HEART",
	.irq_ack		= ip30_ack_heart_irq,
	.irq_mask		= ip30_mask_heart_irq,
	.irq_mask_ack		= ip30_mask_and_ack_heart_irq,
	.irq_unmask		= ip30_unmask_heart_irq,
	.irq_set_affinity	= ip30_set_heart_irq_affinity,
पूर्ण;

अटल पूर्णांक heart_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			      अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा irq_alloc_info *info = arg;
	काष्ठा heart_irq_data *hd;
	पूर्णांक hwirq;

	अगर (nr_irqs > 1 || !info)
		वापस -EINVAL;

	hd = kzalloc(माप(*hd), GFP_KERNEL);
	अगर (!hd)
		वापस -ENOMEM;

	hwirq = heart_alloc_पूर्णांक();
	अगर (hwirq < 0) अणु
		kमुक्त(hd);
		वापस -EAGAIN;
	पूर्ण
	irq_करोमुख्य_set_info(करोमुख्य, virq, hwirq, &heart_irq_chip, hd,
			    handle_level_irq, शून्य, शून्य);

	वापस 0;
पूर्ण

अटल व्योम heart_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
			      अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *irqd;

	अगर (nr_irqs > 1)
		वापस;

	irqd = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	अगर (irqd) अणु
		clear_bit(irqd->hwirq, heart_irq_map);
		kमुक्त(irqd->chip_data);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops heart_करोमुख्य_ops = अणु
	.alloc = heart_करोमुख्य_alloc,
	.मुक्त  = heart_करोमुख्य_मुक्त,
पूर्ण;

व्योम __init ip30_install_ipi(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ *mask = &per_cpu(irq_enable_mask, cpu);

	set_bit(HEART_L2_INT_RESCHED_CPU_0 + cpu, mask);
	heart_ग_लिखो(BIT_ULL(HEART_L2_INT_RESCHED_CPU_0 + cpu),
		    &heart_regs->clear_isr);
	set_bit(HEART_L2_INT_CALL_CPU_0 + cpu, mask);
	heart_ग_लिखो(BIT_ULL(HEART_L2_INT_CALL_CPU_0 + cpu),
		    &heart_regs->clear_isr);

	heart_ग_लिखो(*mask, &heart_regs->imr[cpu]);
पूर्ण

व्योम __init arch_init_irq(व्योम)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा fwnode_handle *fn;
	अचिन्हित दीर्घ *mask;
	पूर्णांक i;

	mips_cpu_irq_init();

	/* Mask all IRQs. */
	heart_ग_लिखो(HEART_CLR_ALL_MASK, &heart_regs->imr[0]);
	heart_ग_लिखो(HEART_CLR_ALL_MASK, &heart_regs->imr[1]);
	heart_ग_लिखो(HEART_CLR_ALL_MASK, &heart_regs->imr[2]);
	heart_ग_लिखो(HEART_CLR_ALL_MASK, &heart_regs->imr[3]);

	/* Ack everything. */
	heart_ग_लिखो(HEART_ACK_ALL_MASK, &heart_regs->clear_isr);

	/* Enable specअगरic HEART error IRQs क्रम each CPU. */
	mask = &per_cpu(irq_enable_mask, 0);
	*mask |= HEART_CPU0_ERR_MASK;
	heart_ग_लिखो(*mask, &heart_regs->imr[0]);
	mask = &per_cpu(irq_enable_mask, 1);
	*mask |= HEART_CPU1_ERR_MASK;
	heart_ग_लिखो(*mask, &heart_regs->imr[1]);

	/*
	 * Some HEART bits are reserved by hardware or by software convention.
	 * Mark these as reserved right away so they won't be accidentally
	 * used later.
	 */
	set_bit(HEART_L0_INT_GENERIC, heart_irq_map);
	set_bit(HEART_L0_INT_FLOW_CTRL_HWTR_0, heart_irq_map);
	set_bit(HEART_L0_INT_FLOW_CTRL_HWTR_1, heart_irq_map);
	set_bit(HEART_L2_INT_RESCHED_CPU_0, heart_irq_map);
	set_bit(HEART_L2_INT_RESCHED_CPU_1, heart_irq_map);
	set_bit(HEART_L2_INT_CALL_CPU_0, heart_irq_map);
	set_bit(HEART_L2_INT_CALL_CPU_1, heart_irq_map);
	set_bit(HEART_L3_INT_TIMER, heart_irq_map);

	/* Reserve the error पूर्णांकerrupts (#51 to #63). */
	क्रम (i = HEART_L4_INT_XWID_ERR_9; i <= HEART_L4_INT_HEART_EXCP; i++)
		set_bit(i, heart_irq_map);

	fn = irq_करोमुख्य_alloc_named_fwnode("HEART");
	WARN_ON(fn == शून्य);
	अगर (!fn)
		वापस;
	करोमुख्य = irq_करोमुख्य_create_linear(fn, HEART_NUM_IRQS,
					  &heart_करोमुख्य_ops, शून्य);
	WARN_ON(करोमुख्य == शून्य);
	अगर (!करोमुख्य)
		वापस;

	irq_set_शेष_host(करोमुख्य);

	irq_set_percpu_devid(IP30_HEART_L0_IRQ);
	irq_set_chained_handler_and_data(IP30_HEART_L0_IRQ, ip30_normal_irq,
					 करोमुख्य);
	irq_set_percpu_devid(IP30_HEART_L1_IRQ);
	irq_set_chained_handler_and_data(IP30_HEART_L1_IRQ, ip30_normal_irq,
					 करोमुख्य);
	irq_set_percpu_devid(IP30_HEART_L2_IRQ);
	irq_set_chained_handler_and_data(IP30_HEART_L2_IRQ, ip30_normal_irq,
					 करोमुख्य);
	irq_set_percpu_devid(IP30_HEART_ERR_IRQ);
	irq_set_chained_handler_and_data(IP30_HEART_ERR_IRQ, ip30_error_irq,
					 करोमुख्य);
पूर्ण
