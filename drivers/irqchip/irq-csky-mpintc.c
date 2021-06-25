<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/module.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/reg_ops.h>

अटल काष्ठा irq_करोमुख्य *root_करोमुख्य;
अटल व्योम __iomem *INTCG_base;
अटल व्योम __iomem *INTCL_base;

#घोषणा IPI_IRQ		15
#घोषणा INTC_IRQS	256
#घोषणा COMM_IRQ_BASE	32

#घोषणा INTCG_SIZE	0x8000
#घोषणा INTCL_SIZE	0x1000

#घोषणा INTCG_ICTLR	0x0
#घोषणा INTCG_CICFGR	0x100
#घोषणा INTCG_CIDSTR	0x1000

#घोषणा INTCL_PICTLR	0x0
#घोषणा INTCL_CFGR	0x14
#घोषणा INTCL_SIGR	0x60
#घोषणा INTCL_RDYIR	0x6c
#घोषणा INTCL_SENR	0xa0
#घोषणा INTCL_CENR	0xa4
#घोषणा INTCL_CACR	0xb4

अटल DEFINE_PER_CPU(व्योम __iomem *, पूर्णांकcl_reg);

अटल अचिन्हित दीर्घ *__trigger;

#घोषणा IRQ_OFFSET(irq) ((irq < COMM_IRQ_BASE) ? irq : (irq - COMM_IRQ_BASE))

#घोषणा TRIG_BYTE_OFFSET(i)	((((i) * 2) / 32) * 4)
#घोषणा TRIG_BIT_OFFSET(i)	 (((i) * 2) % 32)

#घोषणा TRIG_VAL(trigger, irq)	(trigger << TRIG_BIT_OFFSET(IRQ_OFFSET(irq)))
#घोषणा TRIG_VAL_MSK(irq)	    (~(3 << TRIG_BIT_OFFSET(IRQ_OFFSET(irq))))

#घोषणा TRIG_BASE(irq) \
	(TRIG_BYTE_OFFSET(IRQ_OFFSET(irq)) + ((irq < COMM_IRQ_BASE) ? \
	(this_cpu_पढ़ो(पूर्णांकcl_reg) + INTCL_CFGR) : (INTCG_base + INTCG_CICFGR)))

अटल DEFINE_SPINLOCK(setup_lock);
अटल व्योम setup_trigger(अचिन्हित दीर्घ irq, अचिन्हित दीर्घ trigger)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	spin_lock(&setup_lock);

	/* setup trigger */
	पंचांगp = पढ़ोl_relaxed(TRIG_BASE(irq)) & TRIG_VAL_MSK(irq);

	ग_लिखोl_relaxed(पंचांगp | TRIG_VAL(trigger, irq), TRIG_BASE(irq));

	spin_unlock(&setup_lock);
पूर्ण

अटल व्योम csky_mpपूर्णांकc_handler(काष्ठा pt_regs *regs)
अणु
	व्योम __iomem *reg_base = this_cpu_पढ़ो(पूर्णांकcl_reg);

	handle_करोमुख्य_irq(root_करोमुख्य,
		पढ़ोl_relaxed(reg_base + INTCL_RDYIR), regs);
पूर्ण

अटल व्योम csky_mpपूर्णांकc_enable(काष्ठा irq_data *d)
अणु
	व्योम __iomem *reg_base = this_cpu_पढ़ो(पूर्णांकcl_reg);

	setup_trigger(d->hwirq, __trigger[d->hwirq]);

	ग_लिखोl_relaxed(d->hwirq, reg_base + INTCL_SENR);
पूर्ण

अटल व्योम csky_mpपूर्णांकc_disable(काष्ठा irq_data *d)
अणु
	व्योम __iomem *reg_base = this_cpu_पढ़ो(पूर्णांकcl_reg);

	ग_लिखोl_relaxed(d->hwirq, reg_base + INTCL_CENR);
पूर्ण

अटल व्योम csky_mpपूर्णांकc_eoi(काष्ठा irq_data *d)
अणु
	व्योम __iomem *reg_base = this_cpu_पढ़ो(पूर्णांकcl_reg);

	ग_लिखोl_relaxed(d->hwirq, reg_base + INTCL_CACR);
पूर्ण

अटल पूर्णांक csky_mpपूर्णांकc_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_LEVEL_HIGH:
		__trigger[d->hwirq] = 0;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		__trigger[d->hwirq] = 1;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		__trigger[d->hwirq] = 2;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		__trigger[d->hwirq] = 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक csky_irq_set_affinity(काष्ठा irq_data *d,
				 स्थिर काष्ठा cpumask *mask_val,
				 bool क्रमce)
अणु
	अचिन्हित पूर्णांक cpu;
	अचिन्हित पूर्णांक offset = 4 * (d->hwirq - COMM_IRQ_BASE);

	अगर (!क्रमce)
		cpu = cpumask_any_and(mask_val, cpu_online_mask);
	अन्यथा
		cpu = cpumask_first(mask_val);

	अगर (cpu >= nr_cpu_ids)
		वापस -EINVAL;

	/*
	 * The csky,mpपूर्णांकc could support स्वतः irq deliver, but it only
	 * could deliver बाह्यal irq to one cpu or all cpus. So it
	 * करोesn't support deliver बाह्यal irq to a group of cpus
	 * with cpu_mask.
	 * SO we only use स्वतः deliver mode when affinity mask_val is
	 * equal to cpu_present_mask.
	 *
	 */
	अगर (cpumask_equal(mask_val, cpu_present_mask))
		cpu = 0;
	अन्यथा
		cpu |= BIT(31);

	ग_लिखोl_relaxed(cpu, INTCG_base + INTCG_CIDSTR + offset);

	irq_data_update_effective_affinity(d, cpumask_of(cpu));

	वापस IRQ_SET_MASK_OK_DONE;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा irq_chip csky_irq_chip = अणु
	.name           = "C-SKY SMP Intc",
	.irq_eoi	= csky_mpपूर्णांकc_eoi,
	.irq_enable	= csky_mpपूर्णांकc_enable,
	.irq_disable	= csky_mpपूर्णांकc_disable,
	.irq_set_type	= csky_mpपूर्णांकc_set_type,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = csky_irq_set_affinity,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक csky_irqकरोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
			      irq_hw_number_t hwirq)
अणु
	अगर (hwirq < COMM_IRQ_BASE) अणु
		irq_set_percpu_devid(irq);
		irq_set_chip_and_handler(irq, &csky_irq_chip,
					 handle_percpu_irq);
	पूर्ण अन्यथा अणु
		irq_set_chip_and_handler(irq, &csky_irq_chip,
					 handle_fasteoi_irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक csky_irq_करोमुख्य_xlate_cells(काष्ठा irq_करोमुख्य *d,
		काष्ठा device_node *ctrlr, स्थिर u32 *पूर्णांकspec,
		अचिन्हित पूर्णांक पूर्णांकsize, अचिन्हित दीर्घ *out_hwirq,
		अचिन्हित पूर्णांक *out_type)
अणु
	अगर (WARN_ON(पूर्णांकsize < 1))
		वापस -EINVAL;

	*out_hwirq = पूर्णांकspec[0];
	अगर (पूर्णांकsize > 1)
		*out_type = पूर्णांकspec[1] & IRQ_TYPE_SENSE_MASK;
	अन्यथा
		*out_type = IRQ_TYPE_LEVEL_HIGH;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops csky_irqकरोमुख्य_ops = अणु
	.map	= csky_irqकरोमुख्य_map,
	.xlate	= csky_irq_करोमुख्य_xlate_cells,
पूर्ण;

#अगर_घोषित CONFIG_SMP
अटल व्योम csky_mpपूर्णांकc_send_ipi(स्थिर काष्ठा cpumask *mask)
अणु
	व्योम __iomem *reg_base = this_cpu_पढ़ो(पूर्णांकcl_reg);

	/*
	 * INTCL_SIGR[3:0] INTID
	 * INTCL_SIGR[8:15] CPUMASK
	 */
	ग_लिखोl_relaxed((*cpumask_bits(mask)) << 8 | IPI_IRQ,
					reg_base + INTCL_SIGR);
पूर्ण
#पूर्ण_अगर

/* C-SKY multi processor पूर्णांकerrupt controller */
अटल पूर्णांक __init
csky_mpपूर्णांकc_init(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक cpu, nr_irq;
#अगर_घोषित CONFIG_SMP
	अचिन्हित पूर्णांक ipi_irq;
#पूर्ण_अगर

	अगर (parent)
		वापस 0;

	ret = of_property_पढ़ो_u32(node, "csky,num-irqs", &nr_irq);
	अगर (ret < 0)
		nr_irq = INTC_IRQS;

	__trigger  = kसुस्मृति(nr_irq, माप(अचिन्हित दीर्घ), GFP_KERNEL);
	अगर (__trigger == शून्य)
		वापस -ENXIO;

	अगर (INTCG_base == शून्य) अणु
		INTCG_base = ioremap(mfcr("cr<31, 14>"),
				     INTCL_SIZE*nr_cpu_ids + INTCG_SIZE);
		अगर (INTCG_base == शून्य)
			वापस -EIO;

		INTCL_base = INTCG_base + INTCG_SIZE;

		ग_लिखोl_relaxed(BIT(0), INTCG_base + INTCG_ICTLR);
	पूर्ण

	root_करोमुख्य = irq_करोमुख्य_add_linear(node, nr_irq, &csky_irqकरोमुख्य_ops,
					    शून्य);
	अगर (!root_करोमुख्य)
		वापस -ENXIO;

	/* क्रम every cpu */
	क्रम_each_present_cpu(cpu) अणु
		per_cpu(पूर्णांकcl_reg, cpu) = INTCL_base + (INTCL_SIZE * cpu);
		ग_लिखोl_relaxed(BIT(0), per_cpu(पूर्णांकcl_reg, cpu) + INTCL_PICTLR);
	पूर्ण

	set_handle_irq(&csky_mpपूर्णांकc_handler);

#अगर_घोषित CONFIG_SMP
	ipi_irq = irq_create_mapping(root_करोमुख्य, IPI_IRQ);
	अगर (!ipi_irq)
		वापस -EIO;

	set_send_ipi(&csky_mpपूर्णांकc_send_ipi, ipi_irq);
#पूर्ण_अगर

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(csky_mpपूर्णांकc, "csky,mpintc", csky_mpपूर्णांकc_init);
