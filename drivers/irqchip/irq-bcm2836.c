<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Root पूर्णांकerrupt controller क्रम the BCM2836 (Raspberry Pi 2).
 *
 * Copyright 2015 Broadcom
 */

#समावेश <linux/cpu.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqchip/irq-bcm2836.h>

#समावेश <यंत्र/exception.h>

काष्ठा bcm2836_arm_irqchip_पूर्णांकc अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	व्योम __iomem *base;
पूर्ण;

अटल काष्ठा bcm2836_arm_irqchip_पूर्णांकc पूर्णांकc  __पढ़ो_mostly;

अटल व्योम bcm2836_arm_irqchip_mask_per_cpu_irq(अचिन्हित पूर्णांक reg_offset,
						 अचिन्हित पूर्णांक bit,
						 पूर्णांक cpu)
अणु
	व्योम __iomem *reg = पूर्णांकc.base + reg_offset + 4 * cpu;

	ग_लिखोl(पढ़ोl(reg) & ~BIT(bit), reg);
पूर्ण

अटल व्योम bcm2836_arm_irqchip_unmask_per_cpu_irq(अचिन्हित पूर्णांक reg_offset,
						   अचिन्हित पूर्णांक bit,
						 पूर्णांक cpu)
अणु
	व्योम __iomem *reg = पूर्णांकc.base + reg_offset + 4 * cpu;

	ग_लिखोl(पढ़ोl(reg) | BIT(bit), reg);
पूर्ण

अटल व्योम bcm2836_arm_irqchip_mask_समयr_irq(काष्ठा irq_data *d)
अणु
	bcm2836_arm_irqchip_mask_per_cpu_irq(LOCAL_TIMER_INT_CONTROL0,
					     d->hwirq - LOCAL_IRQ_CNTPSIRQ,
					     smp_processor_id());
पूर्ण

अटल व्योम bcm2836_arm_irqchip_unmask_समयr_irq(काष्ठा irq_data *d)
अणु
	bcm2836_arm_irqchip_unmask_per_cpu_irq(LOCAL_TIMER_INT_CONTROL0,
					       d->hwirq - LOCAL_IRQ_CNTPSIRQ,
					       smp_processor_id());
पूर्ण

अटल काष्ठा irq_chip bcm2836_arm_irqchip_समयr = अणु
	.name		= "bcm2836-timer",
	.irq_mask	= bcm2836_arm_irqchip_mask_समयr_irq,
	.irq_unmask	= bcm2836_arm_irqchip_unmask_समयr_irq,
पूर्ण;

अटल व्योम bcm2836_arm_irqchip_mask_pmu_irq(काष्ठा irq_data *d)
अणु
	ग_लिखोl(1 << smp_processor_id(), पूर्णांकc.base + LOCAL_PM_ROUTING_CLR);
पूर्ण

अटल व्योम bcm2836_arm_irqchip_unmask_pmu_irq(काष्ठा irq_data *d)
अणु
	ग_लिखोl(1 << smp_processor_id(), पूर्णांकc.base + LOCAL_PM_ROUTING_SET);
पूर्ण

अटल काष्ठा irq_chip bcm2836_arm_irqchip_pmu = अणु
	.name		= "bcm2836-pmu",
	.irq_mask	= bcm2836_arm_irqchip_mask_pmu_irq,
	.irq_unmask	= bcm2836_arm_irqchip_unmask_pmu_irq,
पूर्ण;

अटल व्योम bcm2836_arm_irqchip_mask_gpu_irq(काष्ठा irq_data *d)
अणु
पूर्ण

अटल व्योम bcm2836_arm_irqchip_unmask_gpu_irq(काष्ठा irq_data *d)
अणु
पूर्ण

अटल काष्ठा irq_chip bcm2836_arm_irqchip_gpu = अणु
	.name		= "bcm2836-gpu",
	.irq_mask	= bcm2836_arm_irqchip_mask_gpu_irq,
	.irq_unmask	= bcm2836_arm_irqchip_unmask_gpu_irq,
पूर्ण;

अटल व्योम bcm2836_arm_irqchip_dummy_op(काष्ठा irq_data *d)
अणु
पूर्ण

अटल काष्ठा irq_chip bcm2836_arm_irqchip_dummy = अणु
	.name		= "bcm2836-dummy",
	.irq_eoi	= bcm2836_arm_irqchip_dummy_op,
पूर्ण;

अटल पूर्णांक bcm2836_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
		       irq_hw_number_t hw)
अणु
	काष्ठा irq_chip *chip;

	चयन (hw) अणु
	हाल LOCAL_IRQ_MAILBOX0:
		chip = &bcm2836_arm_irqchip_dummy;
		अवरोध;
	हाल LOCAL_IRQ_CNTPSIRQ:
	हाल LOCAL_IRQ_CNTPNSIRQ:
	हाल LOCAL_IRQ_CNTHPIRQ:
	हाल LOCAL_IRQ_CNTVIRQ:
		chip = &bcm2836_arm_irqchip_समयr;
		अवरोध;
	हाल LOCAL_IRQ_GPU_FAST:
		chip = &bcm2836_arm_irqchip_gpu;
		अवरोध;
	हाल LOCAL_IRQ_PMU_FAST:
		chip = &bcm2836_arm_irqchip_pmu;
		अवरोध;
	शेष:
		pr_warn_once("Unexpected hw irq: %lu\n", hw);
		वापस -EINVAL;
	पूर्ण

	irq_set_percpu_devid(irq);
	irq_करोमुख्य_set_info(d, irq, hw, chip, d->host_data,
			    handle_percpu_devid_irq, शून्य, शून्य);
	irq_set_status_flags(irq, IRQ_NOAUTOEN);

	वापस 0;
पूर्ण

अटल व्योम
__exception_irq_entry bcm2836_arm_irqchip_handle_irq(काष्ठा pt_regs *regs)
अणु
	पूर्णांक cpu = smp_processor_id();
	u32 stat;

	stat = पढ़ोl_relaxed(पूर्णांकc.base + LOCAL_IRQ_PENDING0 + 4 * cpu);
	अगर (stat) अणु
		u32 hwirq = ffs(stat) - 1;

		handle_करोमुख्य_irq(पूर्णांकc.करोमुख्य, hwirq, regs);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल काष्ठा irq_करोमुख्य *ipi_करोमुख्य;

अटल व्योम bcm2836_arm_irqchip_handle_ipi(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	पूर्णांक cpu = smp_processor_id();
	u32 mbox_val;

	chained_irq_enter(chip, desc);

	mbox_val = पढ़ोl_relaxed(पूर्णांकc.base + LOCAL_MAILBOX0_CLR0 + 16 * cpu);
	अगर (mbox_val) अणु
		पूर्णांक hwirq = ffs(mbox_val) - 1;
		generic_handle_irq(irq_find_mapping(ipi_करोमुख्य, hwirq));
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम bcm2836_arm_irqchip_ipi_ack(काष्ठा irq_data *d)
अणु
	पूर्णांक cpu = smp_processor_id();

	ग_लिखोl_relaxed(BIT(d->hwirq),
		       पूर्णांकc.base + LOCAL_MAILBOX0_CLR0 + 16 * cpu);
पूर्ण

अटल व्योम bcm2836_arm_irqchip_ipi_send_mask(काष्ठा irq_data *d,
					      स्थिर काष्ठा cpumask *mask)
अणु
	पूर्णांक cpu;
	व्योम __iomem *mailbox0_base = पूर्णांकc.base + LOCAL_MAILBOX0_SET0;

	/*
	 * Ensure that stores to normal memory are visible to the
	 * other CPUs beक्रमe issuing the IPI.
	 */
	smp_wmb();

	क्रम_each_cpu(cpu, mask)
		ग_लिखोl_relaxed(BIT(d->hwirq), mailbox0_base + 16 * cpu);
पूर्ण

अटल काष्ठा irq_chip bcm2836_arm_irqchip_ipi = अणु
	.name		= "IPI",
	.irq_mask	= bcm2836_arm_irqchip_dummy_op,
	.irq_unmask	= bcm2836_arm_irqchip_dummy_op,
	.irq_ack	= bcm2836_arm_irqchip_ipi_ack,
	.ipi_send_mask	= bcm2836_arm_irqchip_ipi_send_mask,
पूर्ण;

अटल पूर्णांक bcm2836_arm_irqchip_ipi_alloc(काष्ठा irq_करोमुख्य *d,
					 अचिन्हित पूर्णांक virq,
					 अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_set_percpu_devid(virq + i);
		irq_करोमुख्य_set_info(d, virq + i, i, &bcm2836_arm_irqchip_ipi,
				    d->host_data,
				    handle_percpu_devid_irq,
				    शून्य, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bcm2836_arm_irqchip_ipi_मुक्त(काष्ठा irq_करोमुख्य *d,
					 अचिन्हित पूर्णांक virq,
					 अचिन्हित पूर्णांक nr_irqs)
अणु
	/* Not मुक्तing IPIs */
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops ipi_करोमुख्य_ops = अणु
	.alloc	= bcm2836_arm_irqchip_ipi_alloc,
	.मुक्त	= bcm2836_arm_irqchip_ipi_मुक्त,
पूर्ण;

अटल पूर्णांक bcm2836_cpu_starting(अचिन्हित पूर्णांक cpu)
अणु
	bcm2836_arm_irqchip_unmask_per_cpu_irq(LOCAL_MAILBOX_INT_CONTROL0, 0,
					       cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक bcm2836_cpu_dying(अचिन्हित पूर्णांक cpu)
अणु
	bcm2836_arm_irqchip_mask_per_cpu_irq(LOCAL_MAILBOX_INT_CONTROL0, 0,
					     cpu);
	वापस 0;
पूर्ण

#घोषणा BITS_PER_MBOX	32

अटल व्योम __init bcm2836_arm_irqchip_smp_init(व्योम)
अणु
	काष्ठा irq_fwspec ipi_fwspec = अणु
		.fwnode		= पूर्णांकc.करोमुख्य->fwnode,
		.param_count	= 1,
		.param		= अणु
			[0]	= LOCAL_IRQ_MAILBOX0,
		पूर्ण,
	पूर्ण;
	पूर्णांक base_ipi, mux_irq;

	mux_irq = irq_create_fwspec_mapping(&ipi_fwspec);
	अगर (WARN_ON(mux_irq <= 0))
		वापस;

	ipi_करोमुख्य = irq_करोमुख्य_create_linear(पूर्णांकc.करोमुख्य->fwnode,
					      BITS_PER_MBOX, &ipi_करोमुख्य_ops,
					      शून्य);
	अगर (WARN_ON(!ipi_करोमुख्य))
		वापस;

	ipi_करोमुख्य->flags |= IRQ_DOMAIN_FLAG_IPI_SINGLE;
	irq_करोमुख्य_update_bus_token(ipi_करोमुख्य, DOMAIN_BUS_IPI);

	base_ipi = __irq_करोमुख्य_alloc_irqs(ipi_करोमुख्य, -1, BITS_PER_MBOX,
					   NUMA_NO_NODE, शून्य,
					   false, शून्य);

	अगर (WARN_ON(!base_ipi))
		वापस;

	set_smp_ipi_range(base_ipi, BITS_PER_MBOX);

	irq_set_chained_handler_and_data(mux_irq,
					 bcm2836_arm_irqchip_handle_ipi, शून्य);

	/* Unmask IPIs to the boot CPU. */
	cpuhp_setup_state(CPUHP_AP_IRQ_BCM2836_STARTING,
			  "irqchip/bcm2836:starting", bcm2836_cpu_starting,
			  bcm2836_cpu_dying);
पूर्ण
#अन्यथा
#घोषणा bcm2836_arm_irqchip_smp_init()	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

अटल स्थिर काष्ठा irq_करोमुख्य_ops bcm2836_arm_irqchip_पूर्णांकc_ops = अणु
	.xlate = irq_करोमुख्य_xlate_onetwocell,
	.map = bcm2836_map,
पूर्ण;

/*
 * The LOCAL_IRQ_CNT* समयr firings are based off of the बाह्यal
 * oscillator with some scaling.  The firmware sets up CNTFRQ to
 * report 19.2Mhz, but करोesn't set up the scaling रेजिस्टरs.
 */
अटल व्योम bcm2835_init_local_समयr_frequency(व्योम)
अणु
	/*
	 * Set the समयr to source from the 19.2Mhz crystal घड़ी (bit
	 * 8 unset), and only increment by 1 instead of 2 (bit 9
	 * unset).
	 */
	ग_लिखोl(0, पूर्णांकc.base + LOCAL_CONTROL);

	/*
	 * Set the समयr prescaler to 1:1 (समयr freq = input freq *
	 * 2**31 / prescaler)
	 */
	ग_लिखोl(0x80000000, पूर्णांकc.base + LOCAL_PRESCALER);
पूर्ण

अटल पूर्णांक __init bcm2836_arm_irqchip_l1_पूर्णांकc_of_init(काष्ठा device_node *node,
						      काष्ठा device_node *parent)
अणु
	पूर्णांकc.base = of_iomap(node, 0);
	अगर (!पूर्णांकc.base) अणु
		panic("%pOF: unable to map local interrupt registers\n", node);
	पूर्ण

	bcm2835_init_local_समयr_frequency();

	पूर्णांकc.करोमुख्य = irq_करोमुख्य_add_linear(node, LAST_IRQ + 1,
					    &bcm2836_arm_irqchip_पूर्णांकc_ops,
					    शून्य);
	अगर (!पूर्णांकc.करोमुख्य)
		panic("%pOF: unable to create IRQ domain\n", node);

	irq_करोमुख्य_update_bus_token(पूर्णांकc.करोमुख्य, DOMAIN_BUS_WIRED);

	bcm2836_arm_irqchip_smp_init();

	set_handle_irq(bcm2836_arm_irqchip_handle_irq);
	वापस 0;
पूर्ण

IRQCHIP_DECLARE(bcm2836_arm_irqchip_l1_पूर्णांकc, "brcm,bcm2836-l1-intc",
		bcm2836_arm_irqchip_l1_पूर्णांकc_of_init);
