<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HiSilicon HiP04 INTC
 *
 * Copyright (C) 2002-2014 ARM Limited.
 * Copyright (c) 2013-2014 HiSilicon Ltd.
 * Copyright (c) 2013-2014 Linaro Ltd.
 *
 * Interrupt architecture क्रम the HIP04 INTC:
 *
 * o There is one Interrupt Distributor, which receives पूर्णांकerrupts
 *   from प्रणाली devices and sends them to the Interrupt Controllers.
 *
 * o There is one CPU Interface per CPU, which sends पूर्णांकerrupts sent
 *   by the Distributor, and पूर्णांकerrupts generated locally, to the
 *   associated CPU. The base address of the CPU पूर्णांकerface is usually
 *   aliased so that the same address poपूर्णांकs to dअगरferent chips depending
 *   on the CPU it is accessed from.
 *
 * Note that IRQs 0-31 are special - they are local to each CPU.
 * As such, the enable set/clear, pending set/clear and active bit
 * रेजिस्टरs are banked per-cpu क्रम these sources.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/smp.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/arm-gic.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/smp_plat.h>

#समावेश "irq-gic-common.h"

#घोषणा HIP04_MAX_IRQS		510

काष्ठा hip04_irq_data अणु
	व्योम __iomem *dist_base;
	व्योम __iomem *cpu_base;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	अचिन्हित पूर्णांक nr_irqs;
पूर्ण;

अटल DEFINE_RAW_SPINLOCK(irq_controller_lock);

/*
 * The GIC mapping of CPU पूर्णांकerfaces करोes not necessarily match
 * the logical CPU numbering.  Let's use a mapping as वापसed
 * by the GIC itself.
 */
#घोषणा NR_HIP04_CPU_IF 16
अटल u16 hip04_cpu_map[NR_HIP04_CPU_IF] __पढ़ो_mostly;

अटल काष्ठा hip04_irq_data hip04_data __पढ़ो_mostly;

अटल अंतरभूत व्योम __iomem *hip04_dist_base(काष्ठा irq_data *d)
अणु
	काष्ठा hip04_irq_data *hip04_data = irq_data_get_irq_chip_data(d);
	वापस hip04_data->dist_base;
पूर्ण

अटल अंतरभूत व्योम __iomem *hip04_cpu_base(काष्ठा irq_data *d)
अणु
	काष्ठा hip04_irq_data *hip04_data = irq_data_get_irq_chip_data(d);
	वापस hip04_data->cpu_base;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक hip04_irq(काष्ठा irq_data *d)
अणु
	वापस d->hwirq;
पूर्ण

/*
 * Routines to acknowledge, disable and enable पूर्णांकerrupts
 */
अटल व्योम hip04_mask_irq(काष्ठा irq_data *d)
अणु
	u32 mask = 1 << (hip04_irq(d) % 32);

	raw_spin_lock(&irq_controller_lock);
	ग_लिखोl_relaxed(mask, hip04_dist_base(d) + GIC_DIST_ENABLE_CLEAR +
		       (hip04_irq(d) / 32) * 4);
	raw_spin_unlock(&irq_controller_lock);
पूर्ण

अटल व्योम hip04_unmask_irq(काष्ठा irq_data *d)
अणु
	u32 mask = 1 << (hip04_irq(d) % 32);

	raw_spin_lock(&irq_controller_lock);
	ग_लिखोl_relaxed(mask, hip04_dist_base(d) + GIC_DIST_ENABLE_SET +
		       (hip04_irq(d) / 32) * 4);
	raw_spin_unlock(&irq_controller_lock);
पूर्ण

अटल व्योम hip04_eoi_irq(काष्ठा irq_data *d)
अणु
	ग_लिखोl_relaxed(hip04_irq(d), hip04_cpu_base(d) + GIC_CPU_EOI);
पूर्ण

अटल पूर्णांक hip04_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	व्योम __iomem *base = hip04_dist_base(d);
	अचिन्हित पूर्णांक irq = hip04_irq(d);
	पूर्णांक ret;

	/* Interrupt configuration क्रम SGIs can't be changed */
	अगर (irq < 16)
		वापस -EINVAL;

	/* SPIs have restrictions on the supported types */
	अगर (irq >= 32 && type != IRQ_TYPE_LEVEL_HIGH &&
			 type != IRQ_TYPE_EDGE_RISING)
		वापस -EINVAL;

	raw_spin_lock(&irq_controller_lock);

	ret = gic_configure_irq(irq, type, base + GIC_DIST_CONFIG, शून्य);
	अगर (ret && irq < 32) अणु
		/* Misconfigured PPIs are usually not fatal */
		pr_warn("GIC: PPI%d is secure or misconfigured\n", irq - 16);
		ret = 0;
	पूर्ण

	raw_spin_unlock(&irq_controller_lock);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक hip04_irq_set_affinity(काष्ठा irq_data *d,
				  स्थिर काष्ठा cpumask *mask_val,
				  bool क्रमce)
अणु
	व्योम __iomem *reg;
	अचिन्हित पूर्णांक cpu, shअगरt = (hip04_irq(d) % 2) * 16;
	u32 val, mask, bit;

	अगर (!क्रमce)
		cpu = cpumask_any_and(mask_val, cpu_online_mask);
	अन्यथा
		cpu = cpumask_first(mask_val);

	अगर (cpu >= NR_HIP04_CPU_IF || cpu >= nr_cpu_ids)
		वापस -EINVAL;

	raw_spin_lock(&irq_controller_lock);
	reg = hip04_dist_base(d) + GIC_DIST_TARGET + ((hip04_irq(d) * 2) & ~3);
	mask = 0xffff << shअगरt;
	bit = hip04_cpu_map[cpu] << shअगरt;
	val = पढ़ोl_relaxed(reg) & ~mask;
	ग_लिखोl_relaxed(val | bit, reg);
	raw_spin_unlock(&irq_controller_lock);

	irq_data_update_effective_affinity(d, cpumask_of(cpu));

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल व्योम hip04_ipi_send_mask(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *mask)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ flags, map = 0;

	raw_spin_lock_irqsave(&irq_controller_lock, flags);

	/* Convert our logical CPU mask पूर्णांकo a physical one. */
	क्रम_each_cpu(cpu, mask)
		map |= hip04_cpu_map[cpu];

	/*
	 * Ensure that stores to Normal memory are visible to the
	 * other CPUs beक्रमe they observe us issuing the IPI.
	 */
	dmb(ishst);

	/* this always happens on GIC0 */
	ग_लिखोl_relaxed(map << 8 | d->hwirq, hip04_data.dist_base + GIC_DIST_SOFTINT);

	raw_spin_unlock_irqrestore(&irq_controller_lock, flags);
पूर्ण
#पूर्ण_अगर

अटल व्योम __exception_irq_entry hip04_handle_irq(काष्ठा pt_regs *regs)
अणु
	u32 irqstat, irqnr;
	व्योम __iomem *cpu_base = hip04_data.cpu_base;

	करो अणु
		irqstat = पढ़ोl_relaxed(cpu_base + GIC_CPU_INTACK);
		irqnr = irqstat & GICC_IAR_INT_ID_MASK;

		अगर (irqnr <= HIP04_MAX_IRQS)
			handle_करोमुख्य_irq(hip04_data.करोमुख्य, irqnr, regs);
	पूर्ण जबतक (irqnr > HIP04_MAX_IRQS);
पूर्ण

अटल काष्ठा irq_chip hip04_irq_chip = अणु
	.name			= "HIP04 INTC",
	.irq_mask		= hip04_mask_irq,
	.irq_unmask		= hip04_unmask_irq,
	.irq_eoi		= hip04_eoi_irq,
	.irq_set_type		= hip04_irq_set_type,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity	= hip04_irq_set_affinity,
	.ipi_send_mask		= hip04_ipi_send_mask,
#पूर्ण_अगर
	.flags			= IRQCHIP_SET_TYPE_MASKED |
				  IRQCHIP_SKIP_SET_WAKE |
				  IRQCHIP_MASK_ON_SUSPEND,
पूर्ण;

अटल u16 hip04_get_cpumask(काष्ठा hip04_irq_data *पूर्णांकc)
अणु
	व्योम __iomem *base = पूर्णांकc->dist_base;
	u32 mask, i;

	क्रम (i = mask = 0; i < 32; i += 2) अणु
		mask = पढ़ोl_relaxed(base + GIC_DIST_TARGET + i * 2);
		mask |= mask >> 16;
		अगर (mask)
			अवरोध;
	पूर्ण

	अगर (!mask)
		pr_crit("GIC CPU mask not found - kernel will fail to boot.\n");

	वापस mask;
पूर्ण

अटल व्योम __init hip04_irq_dist_init(काष्ठा hip04_irq_data *पूर्णांकc)
अणु
	अचिन्हित पूर्णांक i;
	u32 cpumask;
	अचिन्हित पूर्णांक nr_irqs = पूर्णांकc->nr_irqs;
	व्योम __iomem *base = पूर्णांकc->dist_base;

	ग_लिखोl_relaxed(0, base + GIC_DIST_CTRL);

	/*
	 * Set all global पूर्णांकerrupts to this CPU only.
	 */
	cpumask = hip04_get_cpumask(पूर्णांकc);
	cpumask |= cpumask << 16;
	क्रम (i = 32; i < nr_irqs; i += 2)
		ग_लिखोl_relaxed(cpumask, base + GIC_DIST_TARGET + ((i * 2) & ~3));

	gic_dist_config(base, nr_irqs, शून्य);

	ग_लिखोl_relaxed(1, base + GIC_DIST_CTRL);
पूर्ण

अटल व्योम hip04_irq_cpu_init(काष्ठा hip04_irq_data *पूर्णांकc)
अणु
	व्योम __iomem *dist_base = पूर्णांकc->dist_base;
	व्योम __iomem *base = पूर्णांकc->cpu_base;
	अचिन्हित पूर्णांक cpu_mask, cpu = smp_processor_id();
	पूर्णांक i;

	/*
	 * Get what the GIC says our CPU mask is.
	 */
	BUG_ON(cpu >= NR_HIP04_CPU_IF);
	cpu_mask = hip04_get_cpumask(पूर्णांकc);
	hip04_cpu_map[cpu] = cpu_mask;

	/*
	 * Clear our mask from the other map entries in हाल they're
	 * still undefined.
	 */
	क्रम (i = 0; i < NR_HIP04_CPU_IF; i++)
		अगर (i != cpu)
			hip04_cpu_map[i] &= ~cpu_mask;

	gic_cpu_config(dist_base, 32, शून्य);

	ग_लिखोl_relaxed(0xf0, base + GIC_CPU_PRIMASK);
	ग_लिखोl_relaxed(1, base + GIC_CPU_CTRL);
पूर्ण

अटल पूर्णांक hip04_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
				irq_hw_number_t hw)
अणु
	अगर (hw < 32) अणु
		irq_set_percpu_devid(irq);
		irq_set_chip_and_handler(irq, &hip04_irq_chip,
					 handle_percpu_devid_irq);
	पूर्ण अन्यथा अणु
		irq_set_chip_and_handler(irq, &hip04_irq_chip,
					 handle_fasteoi_irq);
		irq_set_probe(irq);
		irqd_set_single_target(irq_desc_get_irq_data(irq_to_desc(irq)));
	पूर्ण
	irq_set_chip_data(irq, d->host_data);
	वापस 0;
पूर्ण

अटल पूर्णांक hip04_irq_करोमुख्य_xlate(काष्ठा irq_करोमुख्य *d,
				  काष्ठा device_node *controller,
				  स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
				  अचिन्हित दीर्घ *out_hwirq,
				  अचिन्हित पूर्णांक *out_type)
अणु
	अगर (irq_करोमुख्य_get_of_node(d) != controller)
		वापस -EINVAL;
	अगर (पूर्णांकsize == 1 && पूर्णांकspec[0] < 16) अणु
		*out_hwirq = पूर्णांकspec[0];
		*out_type = IRQ_TYPE_EDGE_RISING;
		वापस 0;
	पूर्ण
	अगर (पूर्णांकsize < 3)
		वापस -EINVAL;

	/* Get the पूर्णांकerrupt number and add 16 to skip over SGIs */
	*out_hwirq = पूर्णांकspec[1] + 16;

	/* For SPIs, we need to add 16 more to get the irq ID number */
	अगर (!पूर्णांकspec[0])
		*out_hwirq += 16;

	*out_type = पूर्णांकspec[2] & IRQ_TYPE_SENSE_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक hip04_irq_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	hip04_irq_cpu_init(&hip04_data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops hip04_irq_करोमुख्य_ops = अणु
	.map	= hip04_irq_करोमुख्य_map,
	.xlate	= hip04_irq_करोमुख्य_xlate,
पूर्ण;

अटल पूर्णांक __init
hip04_of_init(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	पूर्णांक nr_irqs, irq_base, i;

	अगर (WARN_ON(!node))
		वापस -ENODEV;

	hip04_data.dist_base = of_iomap(node, 0);
	WARN(!hip04_data.dist_base, "fail to map hip04 intc dist registers\n");

	hip04_data.cpu_base = of_iomap(node, 1);
	WARN(!hip04_data.cpu_base, "unable to map hip04 intc cpu registers\n");

	/*
	 * Initialize the CPU पूर्णांकerface map to all CPUs.
	 * It will be refined as each CPU probes its ID.
	 */
	क्रम (i = 0; i < NR_HIP04_CPU_IF; i++)
		hip04_cpu_map[i] = 0xffff;

	/*
	 * Find out how many पूर्णांकerrupts are supported.
	 * The HIP04 INTC only supports up to 510 पूर्णांकerrupt sources.
	 */
	nr_irqs = पढ़ोl_relaxed(hip04_data.dist_base + GIC_DIST_CTR) & 0x1f;
	nr_irqs = (nr_irqs + 1) * 32;
	अगर (nr_irqs > HIP04_MAX_IRQS)
		nr_irqs = HIP04_MAX_IRQS;
	hip04_data.nr_irqs = nr_irqs;

	irq_base = irq_alloc_descs(-1, 0, nr_irqs, numa_node_id());
	अगर (irq_base < 0) अणु
		pr_err("failed to allocate IRQ numbers\n");
		वापस -EINVAL;
	पूर्ण

	hip04_data.करोमुख्य = irq_करोमुख्य_add_legacy(node, nr_irqs, irq_base,
						  0,
						  &hip04_irq_करोमुख्य_ops,
						  &hip04_data);
	अगर (WARN_ON(!hip04_data.करोमुख्य))
		वापस -EINVAL;

#अगर_घोषित CONFIG_SMP
	set_smp_ipi_range(irq_base, 16);
#पूर्ण_अगर
	set_handle_irq(hip04_handle_irq);

	hip04_irq_dist_init(&hip04_data);
	cpuhp_setup_state(CPUHP_AP_IRQ_HIP04_STARTING, "irqchip/hip04:starting",
			  hip04_irq_starting_cpu, शून्य);
	वापस 0;
पूर्ण
IRQCHIP_DECLARE(hip04_पूर्णांकc, "hisilicon,hip04-intc", hip04_of_init);
