<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Broadcom BCM6345 style Level 1 पूर्णांकerrupt controller driver
 *
 * Copyright (C) 2014 Broadcom Corporation
 * Copyright 2015 Simon Arlott
 *
 * This is based on the BCM7038 (which supports SMP) but with a single
 * enable रेजिस्टर instead of separate mask/set/clear रेजिस्टरs.
 *
 * The BCM3380 has a similar mask/status रेजिस्टर layout, but each pair
 * of words is at separate locations (and SMP is not supported).
 *
 * ENABLE/STATUS words are packed next to each other क्रम each CPU:
 *
 * BCM6368:
 *   0x1000_0020: CPU0_W0_ENABLE
 *   0x1000_0024: CPU0_W1_ENABLE
 *   0x1000_0028: CPU0_W0_STATUS		IRQs 31-63
 *   0x1000_002c: CPU0_W1_STATUS		IRQs 0-31
 *   0x1000_0030: CPU1_W0_ENABLE
 *   0x1000_0034: CPU1_W1_ENABLE
 *   0x1000_0038: CPU1_W0_STATUS		IRQs 31-63
 *   0x1000_003c: CPU1_W1_STATUS		IRQs 0-31
 *
 * BCM63168:
 *   0x1000_0020: CPU0_W0_ENABLE
 *   0x1000_0024: CPU0_W1_ENABLE
 *   0x1000_0028: CPU0_W2_ENABLE
 *   0x1000_002c: CPU0_W3_ENABLE
 *   0x1000_0030: CPU0_W0_STATUS	IRQs 96-127
 *   0x1000_0034: CPU0_W1_STATUS	IRQs 64-95
 *   0x1000_0038: CPU0_W2_STATUS	IRQs 32-63
 *   0x1000_003c: CPU0_W3_STATUS	IRQs 0-31
 *   0x1000_0040: CPU1_W0_ENABLE
 *   0x1000_0044: CPU1_W1_ENABLE
 *   0x1000_0048: CPU1_W2_ENABLE
 *   0x1000_004c: CPU1_W3_ENABLE
 *   0x1000_0050: CPU1_W0_STATUS	IRQs 96-127
 *   0x1000_0054: CPU1_W1_STATUS	IRQs 64-95
 *   0x1000_0058: CPU1_W2_STATUS	IRQs 32-63
 *   0x1000_005c: CPU1_W3_STATUS	IRQs 0-31
 *
 * IRQs are numbered in CPU native endian order
 * (which is big-endian in these examples)
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME	": " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <linux/types.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>

#घोषणा IRQS_PER_WORD		32
#घोषणा REG_BYTES_PER_IRQ_WORD	(माप(u32) * 2)

काष्ठा bcm6345_l1_cpu;

काष्ठा bcm6345_l1_chip अणु
	raw_spinlock_t		lock;
	अचिन्हित पूर्णांक		n_words;
	काष्ठा irq_करोमुख्य	*करोमुख्य;
	काष्ठा cpumask		cpumask;
	काष्ठा bcm6345_l1_cpu	*cpus[NR_CPUS];
पूर्ण;

काष्ठा bcm6345_l1_cpu अणु
	व्योम __iomem		*map_base;
	अचिन्हित पूर्णांक		parent_irq;
	u32			enable_cache[];
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक reg_enable(काष्ठा bcm6345_l1_chip *पूर्णांकc,
					   अचिन्हित पूर्णांक word)
अणु
#अगर_घोषित __BIG_ENDIAN
	वापस (1 * पूर्णांकc->n_words - word - 1) * माप(u32);
#अन्यथा
	वापस (0 * पूर्णांकc->n_words + word) * माप(u32);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक reg_status(काष्ठा bcm6345_l1_chip *पूर्णांकc,
				      अचिन्हित पूर्णांक word)
अणु
#अगर_घोषित __BIG_ENDIAN
	वापस (2 * पूर्णांकc->n_words - word - 1) * माप(u32);
#अन्यथा
	वापस (1 * पूर्णांकc->n_words + word) * माप(u32);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cpu_क्रम_irq(काष्ठा bcm6345_l1_chip *पूर्णांकc,
					काष्ठा irq_data *d)
अणु
	वापस cpumask_first_and(&पूर्णांकc->cpumask, irq_data_get_affinity_mask(d));
पूर्ण

अटल व्योम bcm6345_l1_irq_handle(काष्ठा irq_desc *desc)
अणु
	काष्ठा bcm6345_l1_chip *पूर्णांकc = irq_desc_get_handler_data(desc);
	काष्ठा bcm6345_l1_cpu *cpu;
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक idx;

#अगर_घोषित CONFIG_SMP
	cpu = पूर्णांकc->cpus[cpu_logical_map(smp_processor_id())];
#अन्यथा
	cpu = पूर्णांकc->cpus[0];
#पूर्ण_अगर

	chained_irq_enter(chip, desc);

	क्रम (idx = 0; idx < पूर्णांकc->n_words; idx++) अणु
		पूर्णांक base = idx * IRQS_PER_WORD;
		अचिन्हित दीर्घ pending;
		irq_hw_number_t hwirq;
		अचिन्हित पूर्णांक irq;

		pending = __raw_पढ़ोl(cpu->map_base + reg_status(पूर्णांकc, idx));
		pending &= __raw_पढ़ोl(cpu->map_base + reg_enable(पूर्णांकc, idx));

		क्रम_each_set_bit(hwirq, &pending, IRQS_PER_WORD) अणु
			irq = irq_linear_revmap(पूर्णांकc->करोमुख्य, base + hwirq);
			अगर (irq)
				करो_IRQ(irq);
			अन्यथा
				spurious_पूर्णांकerrupt();
		पूर्ण
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल अंतरभूत व्योम __bcm6345_l1_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा bcm6345_l1_chip *पूर्णांकc = irq_data_get_irq_chip_data(d);
	u32 word = d->hwirq / IRQS_PER_WORD;
	u32 mask = BIT(d->hwirq % IRQS_PER_WORD);
	अचिन्हित पूर्णांक cpu_idx = cpu_क्रम_irq(पूर्णांकc, d);

	पूर्णांकc->cpus[cpu_idx]->enable_cache[word] |= mask;
	__raw_ग_लिखोl(पूर्णांकc->cpus[cpu_idx]->enable_cache[word],
		पूर्णांकc->cpus[cpu_idx]->map_base + reg_enable(पूर्णांकc, word));
पूर्ण

अटल अंतरभूत व्योम __bcm6345_l1_mask(काष्ठा irq_data *d)
अणु
	काष्ठा bcm6345_l1_chip *पूर्णांकc = irq_data_get_irq_chip_data(d);
	u32 word = d->hwirq / IRQS_PER_WORD;
	u32 mask = BIT(d->hwirq % IRQS_PER_WORD);
	अचिन्हित पूर्णांक cpu_idx = cpu_क्रम_irq(पूर्णांकc, d);

	पूर्णांकc->cpus[cpu_idx]->enable_cache[word] &= ~mask;
	__raw_ग_लिखोl(पूर्णांकc->cpus[cpu_idx]->enable_cache[word],
		पूर्णांकc->cpus[cpu_idx]->map_base + reg_enable(पूर्णांकc, word));
पूर्ण

अटल व्योम bcm6345_l1_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा bcm6345_l1_chip *पूर्णांकc = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&पूर्णांकc->lock, flags);
	__bcm6345_l1_unmask(d);
	raw_spin_unlock_irqrestore(&पूर्णांकc->lock, flags);
पूर्ण

अटल व्योम bcm6345_l1_mask(काष्ठा irq_data *d)
अणु
	काष्ठा bcm6345_l1_chip *पूर्णांकc = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&पूर्णांकc->lock, flags);
	__bcm6345_l1_mask(d);
	raw_spin_unlock_irqrestore(&पूर्णांकc->lock, flags);
पूर्ण

अटल पूर्णांक bcm6345_l1_set_affinity(काष्ठा irq_data *d,
				   स्थिर काष्ठा cpumask *dest,
				   bool क्रमce)
अणु
	काष्ठा bcm6345_l1_chip *पूर्णांकc = irq_data_get_irq_chip_data(d);
	u32 word = d->hwirq / IRQS_PER_WORD;
	u32 mask = BIT(d->hwirq % IRQS_PER_WORD);
	अचिन्हित पूर्णांक old_cpu = cpu_क्रम_irq(पूर्णांकc, d);
	अचिन्हित पूर्णांक new_cpu;
	काष्ठा cpumask valid;
	अचिन्हित दीर्घ flags;
	bool enabled;

	अगर (!cpumask_and(&valid, &पूर्णांकc->cpumask, dest))
		वापस -EINVAL;

	new_cpu = cpumask_any_and(&valid, cpu_online_mask);
	अगर (new_cpu >= nr_cpu_ids)
		वापस -EINVAL;

	dest = cpumask_of(new_cpu);

	raw_spin_lock_irqsave(&पूर्णांकc->lock, flags);
	अगर (old_cpu != new_cpu) अणु
		enabled = पूर्णांकc->cpus[old_cpu]->enable_cache[word] & mask;
		अगर (enabled)
			__bcm6345_l1_mask(d);
		cpumask_copy(irq_data_get_affinity_mask(d), dest);
		अगर (enabled)
			__bcm6345_l1_unmask(d);
	पूर्ण अन्यथा अणु
		cpumask_copy(irq_data_get_affinity_mask(d), dest);
	पूर्ण
	raw_spin_unlock_irqrestore(&पूर्णांकc->lock, flags);

	irq_data_update_effective_affinity(d, cpumask_of(new_cpu));

	वापस IRQ_SET_MASK_OK_NOCOPY;
पूर्ण

अटल पूर्णांक __init bcm6345_l1_init_one(काष्ठा device_node *dn,
				      अचिन्हित पूर्णांक idx,
				      काष्ठा bcm6345_l1_chip *पूर्णांकc)
अणु
	काष्ठा resource res;
	resource_माप_प्रकार sz;
	काष्ठा bcm6345_l1_cpu *cpu;
	अचिन्हित पूर्णांक i, n_words;

	अगर (of_address_to_resource(dn, idx, &res))
		वापस -EINVAL;
	sz = resource_size(&res);
	n_words = sz / REG_BYTES_PER_IRQ_WORD;

	अगर (!पूर्णांकc->n_words)
		पूर्णांकc->n_words = n_words;
	अन्यथा अगर (पूर्णांकc->n_words != n_words)
		वापस -EINVAL;

	cpu = पूर्णांकc->cpus[idx] = kzalloc(माप(*cpu) + n_words * माप(u32),
					GFP_KERNEL);
	अगर (!cpu)
		वापस -ENOMEM;

	cpu->map_base = ioremap(res.start, sz);
	अगर (!cpu->map_base)
		वापस -ENOMEM;

	क्रम (i = 0; i < n_words; i++) अणु
		cpu->enable_cache[i] = 0;
		__raw_ग_लिखोl(0, cpu->map_base + reg_enable(पूर्णांकc, i));
	पूर्ण

	cpu->parent_irq = irq_of_parse_and_map(dn, idx);
	अगर (!cpu->parent_irq) अणु
		pr_err("failed to map parent interrupt %d\n", cpu->parent_irq);
		वापस -EINVAL;
	पूर्ण
	irq_set_chained_handler_and_data(cpu->parent_irq,
						bcm6345_l1_irq_handle, पूर्णांकc);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip bcm6345_l1_irq_chip = अणु
	.name			= "bcm6345-l1",
	.irq_mask		= bcm6345_l1_mask,
	.irq_unmask		= bcm6345_l1_unmask,
	.irq_set_affinity	= bcm6345_l1_set_affinity,
पूर्ण;

अटल पूर्णांक bcm6345_l1_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
			  irq_hw_number_t hw_irq)
अणु
	irq_set_chip_and_handler(virq,
		&bcm6345_l1_irq_chip, handle_percpu_irq);
	irq_set_chip_data(virq, d->host_data);
	irqd_set_single_target(irq_desc_get_irq_data(irq_to_desc(virq)));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops bcm6345_l1_करोमुख्य_ops = अणु
	.xlate			= irq_करोमुख्य_xlate_onecell,
	.map			= bcm6345_l1_map,
पूर्ण;

अटल पूर्णांक __init bcm6345_l1_of_init(काष्ठा device_node *dn,
			      काष्ठा device_node *parent)
अणु
	काष्ठा bcm6345_l1_chip *पूर्णांकc;
	अचिन्हित पूर्णांक idx;
	पूर्णांक ret;

	पूर्णांकc = kzalloc(माप(*पूर्णांकc), GFP_KERNEL);
	अगर (!पूर्णांकc)
		वापस -ENOMEM;

	क्रम_each_possible_cpu(idx) अणु
		ret = bcm6345_l1_init_one(dn, idx, पूर्णांकc);
		अगर (ret)
			pr_err("failed to init intc L1 for cpu %d: %d\n",
				idx, ret);
		अन्यथा
			cpumask_set_cpu(idx, &पूर्णांकc->cpumask);
	पूर्ण

	अगर (!cpumask_weight(&पूर्णांकc->cpumask)) अणु
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	raw_spin_lock_init(&पूर्णांकc->lock);

	पूर्णांकc->करोमुख्य = irq_करोमुख्य_add_linear(dn, IRQS_PER_WORD * पूर्णांकc->n_words,
					     &bcm6345_l1_करोमुख्य_ops,
					     पूर्णांकc);
	अगर (!पूर्णांकc->करोमुख्य) अणु
		ret = -ENOMEM;
		जाओ out_unmap;
	पूर्ण

	pr_info("registered BCM6345 L1 intc (IRQs: %d)\n",
			IRQS_PER_WORD * पूर्णांकc->n_words);
	क्रम_each_cpu(idx, &पूर्णांकc->cpumask) अणु
		काष्ठा bcm6345_l1_cpu *cpu = पूर्णांकc->cpus[idx];

		pr_info("  CPU%u at MMIO 0x%p (irq = %d)\n", idx,
				cpu->map_base, cpu->parent_irq);
	पूर्ण

	वापस 0;

out_unmap:
	क्रम_each_possible_cpu(idx) अणु
		काष्ठा bcm6345_l1_cpu *cpu = पूर्णांकc->cpus[idx];

		अगर (cpu) अणु
			अगर (cpu->map_base)
				iounmap(cpu->map_base);
			kमुक्त(cpu);
		पूर्ण
	पूर्ण
out_मुक्त:
	kमुक्त(पूर्णांकc);
	वापस ret;
पूर्ण

IRQCHIP_DECLARE(bcm6345_l1, "brcm,bcm6345-l1-intc", bcm6345_l1_of_init);
