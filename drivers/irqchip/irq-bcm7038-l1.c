<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Broadcom BCM7038 style Level 1 पूर्णांकerrupt controller driver
 *
 * Copyright (C) 2014 Broadcom Corporation
 * Author: Kevin Cernekee
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME	": " fmt

#समावेश <linux/bitops.h>
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
#समावेश <linux/syscore_ops.h>
#अगर_घोषित CONFIG_ARM
#समावेश <यंत्र/smp_plat.h>
#पूर्ण_अगर

#घोषणा IRQS_PER_WORD		32
#घोषणा REG_BYTES_PER_IRQ_WORD	(माप(u32) * 4)
#घोषणा MAX_WORDS		8

काष्ठा bcm7038_l1_cpu;

काष्ठा bcm7038_l1_chip अणु
	raw_spinlock_t		lock;
	अचिन्हित पूर्णांक		n_words;
	काष्ठा irq_करोमुख्य	*करोमुख्य;
	काष्ठा bcm7038_l1_cpu	*cpus[NR_CPUS];
#अगर_घोषित CONFIG_PM_SLEEP
	काष्ठा list_head	list;
	u32			wake_mask[MAX_WORDS];
#पूर्ण_अगर
	u32			irq_fwd_mask[MAX_WORDS];
	u8			affinity[MAX_WORDS * IRQS_PER_WORD];
पूर्ण;

काष्ठा bcm7038_l1_cpu अणु
	व्योम __iomem		*map_base;
	u32			mask_cache[];
पूर्ण;

/*
 * STATUS/MASK_STATUS/MASK_SET/MASK_CLEAR are packed one right after another:
 *
 * 7038:
 *   0x1000_1400: W0_STATUS
 *   0x1000_1404: W1_STATUS
 *   0x1000_1408: W0_MASK_STATUS
 *   0x1000_140c: W1_MASK_STATUS
 *   0x1000_1410: W0_MASK_SET
 *   0x1000_1414: W1_MASK_SET
 *   0x1000_1418: W0_MASK_CLEAR
 *   0x1000_141c: W1_MASK_CLEAR
 *
 * 7445:
 *   0xf03e_1500: W0_STATUS
 *   0xf03e_1504: W1_STATUS
 *   0xf03e_1508: W2_STATUS
 *   0xf03e_150c: W3_STATUS
 *   0xf03e_1510: W4_STATUS
 *   0xf03e_1514: W0_MASK_STATUS
 *   0xf03e_1518: W1_MASK_STATUS
 *   [...]
 */

अटल अंतरभूत अचिन्हित पूर्णांक reg_status(काष्ठा bcm7038_l1_chip *पूर्णांकc,
				      अचिन्हित पूर्णांक word)
अणु
	वापस (0 * पूर्णांकc->n_words + word) * माप(u32);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक reg_mask_status(काष्ठा bcm7038_l1_chip *पूर्णांकc,
					   अचिन्हित पूर्णांक word)
अणु
	वापस (1 * पूर्णांकc->n_words + word) * माप(u32);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक reg_mask_set(काष्ठा bcm7038_l1_chip *पूर्णांकc,
					अचिन्हित पूर्णांक word)
अणु
	वापस (2 * पूर्णांकc->n_words + word) * माप(u32);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक reg_mask_clr(काष्ठा bcm7038_l1_chip *पूर्णांकc,
					अचिन्हित पूर्णांक word)
अणु
	वापस (3 * पूर्णांकc->n_words + word) * माप(u32);
पूर्ण

अटल अंतरभूत u32 l1_पढ़ोl(व्योम __iomem *reg)
अणु
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		वापस ioपढ़ो32be(reg);
	अन्यथा
		वापस पढ़ोl(reg);
पूर्ण

अटल अंतरभूत व्योम l1_ग_लिखोl(u32 val, व्योम __iomem *reg)
अणु
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		ioग_लिखो32be(val, reg);
	अन्यथा
		ग_लिखोl(val, reg);
पूर्ण

अटल व्योम bcm7038_l1_irq_handle(काष्ठा irq_desc *desc)
अणु
	काष्ठा bcm7038_l1_chip *पूर्णांकc = irq_desc_get_handler_data(desc);
	काष्ठा bcm7038_l1_cpu *cpu;
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
		अचिन्हित दीर्घ pending, flags;
		पूर्णांक hwirq;

		raw_spin_lock_irqsave(&पूर्णांकc->lock, flags);
		pending = l1_पढ़ोl(cpu->map_base + reg_status(पूर्णांकc, idx)) &
			  ~cpu->mask_cache[idx];
		raw_spin_unlock_irqrestore(&पूर्णांकc->lock, flags);

		क्रम_each_set_bit(hwirq, &pending, IRQS_PER_WORD) अणु
			generic_handle_irq(irq_find_mapping(पूर्णांकc->करोमुख्य,
							    base + hwirq));
		पूर्ण
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम __bcm7038_l1_unmask(काष्ठा irq_data *d, अचिन्हित पूर्णांक cpu_idx)
अणु
	काष्ठा bcm7038_l1_chip *पूर्णांकc = irq_data_get_irq_chip_data(d);
	u32 word = d->hwirq / IRQS_PER_WORD;
	u32 mask = BIT(d->hwirq % IRQS_PER_WORD);

	पूर्णांकc->cpus[cpu_idx]->mask_cache[word] &= ~mask;
	l1_ग_लिखोl(mask, पूर्णांकc->cpus[cpu_idx]->map_base +
			reg_mask_clr(पूर्णांकc, word));
पूर्ण

अटल व्योम __bcm7038_l1_mask(काष्ठा irq_data *d, अचिन्हित पूर्णांक cpu_idx)
अणु
	काष्ठा bcm7038_l1_chip *पूर्णांकc = irq_data_get_irq_chip_data(d);
	u32 word = d->hwirq / IRQS_PER_WORD;
	u32 mask = BIT(d->hwirq % IRQS_PER_WORD);

	पूर्णांकc->cpus[cpu_idx]->mask_cache[word] |= mask;
	l1_ग_लिखोl(mask, पूर्णांकc->cpus[cpu_idx]->map_base +
			reg_mask_set(पूर्णांकc, word));
पूर्ण

अटल व्योम bcm7038_l1_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा bcm7038_l1_chip *पूर्णांकc = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&पूर्णांकc->lock, flags);
	__bcm7038_l1_unmask(d, पूर्णांकc->affinity[d->hwirq]);
	raw_spin_unlock_irqrestore(&पूर्णांकc->lock, flags);
पूर्ण

अटल व्योम bcm7038_l1_mask(काष्ठा irq_data *d)
अणु
	काष्ठा bcm7038_l1_chip *पूर्णांकc = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&पूर्णांकc->lock, flags);
	__bcm7038_l1_mask(d, पूर्णांकc->affinity[d->hwirq]);
	raw_spin_unlock_irqrestore(&पूर्णांकc->lock, flags);
पूर्ण

अटल पूर्णांक bcm7038_l1_set_affinity(काष्ठा irq_data *d,
				   स्थिर काष्ठा cpumask *dest,
				   bool क्रमce)
अणु
	काष्ठा bcm7038_l1_chip *पूर्णांकc = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ flags;
	irq_hw_number_t hw = d->hwirq;
	u32 word = hw / IRQS_PER_WORD;
	u32 mask = BIT(hw % IRQS_PER_WORD);
	अचिन्हित पूर्णांक first_cpu = cpumask_any_and(dest, cpu_online_mask);
	bool was_disabled;

	raw_spin_lock_irqsave(&पूर्णांकc->lock, flags);

	was_disabled = !!(पूर्णांकc->cpus[पूर्णांकc->affinity[hw]]->mask_cache[word] &
			  mask);
	__bcm7038_l1_mask(d, पूर्णांकc->affinity[hw]);
	पूर्णांकc->affinity[hw] = first_cpu;
	अगर (!was_disabled)
		__bcm7038_l1_unmask(d, first_cpu);

	raw_spin_unlock_irqrestore(&पूर्णांकc->lock, flags);
	irq_data_update_effective_affinity(d, cpumask_of(first_cpu));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल व्योम bcm7038_l1_cpu_offline(काष्ठा irq_data *d)
अणु
	काष्ठा cpumask *mask = irq_data_get_affinity_mask(d);
	पूर्णांक cpu = smp_processor_id();
	cpumask_t new_affinity;

	/* This CPU was not on the affinity mask */
	अगर (!cpumask_test_cpu(cpu, mask))
		वापस;

	अगर (cpumask_weight(mask) > 1) अणु
		/*
		 * Multiple CPU affinity, हटाओ this CPU from the affinity
		 * mask
		 */
		cpumask_copy(&new_affinity, mask);
		cpumask_clear_cpu(cpu, &new_affinity);
	पूर्ण अन्यथा अणु
		/* Only CPU, put on the lowest online CPU */
		cpumask_clear(&new_affinity);
		cpumask_set_cpu(cpumask_first(cpu_online_mask), &new_affinity);
	पूर्ण
	irq_set_affinity_locked(d, &new_affinity, false);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init bcm7038_l1_init_one(काष्ठा device_node *dn,
				      अचिन्हित पूर्णांक idx,
				      काष्ठा bcm7038_l1_chip *पूर्णांकc)
अणु
	काष्ठा resource res;
	resource_माप_प्रकार sz;
	काष्ठा bcm7038_l1_cpu *cpu;
	अचिन्हित पूर्णांक i, n_words, parent_irq;
	पूर्णांक ret;

	अगर (of_address_to_resource(dn, idx, &res))
		वापस -EINVAL;
	sz = resource_size(&res);
	n_words = sz / REG_BYTES_PER_IRQ_WORD;

	अगर (n_words > MAX_WORDS)
		वापस -EINVAL;
	अन्यथा अगर (!पूर्णांकc->n_words)
		पूर्णांकc->n_words = n_words;
	अन्यथा अगर (पूर्णांकc->n_words != n_words)
		वापस -EINVAL;

	ret = of_property_पढ़ो_u32_array(dn , "brcm,int-fwd-mask",
					 पूर्णांकc->irq_fwd_mask, n_words);
	अगर (ret != 0 && ret != -EINVAL) अणु
		/* property exists but has the wrong number of words */
		pr_err("invalid brcm,int-fwd-mask property\n");
		वापस -EINVAL;
	पूर्ण

	cpu = पूर्णांकc->cpus[idx] = kzalloc(माप(*cpu) + n_words * माप(u32),
					GFP_KERNEL);
	अगर (!cpu)
		वापस -ENOMEM;

	cpu->map_base = ioremap(res.start, sz);
	अगर (!cpu->map_base)
		वापस -ENOMEM;

	क्रम (i = 0; i < n_words; i++) अणु
		l1_ग_लिखोl(~पूर्णांकc->irq_fwd_mask[i],
			  cpu->map_base + reg_mask_set(पूर्णांकc, i));
		l1_ग_लिखोl(पूर्णांकc->irq_fwd_mask[i],
			  cpu->map_base + reg_mask_clr(पूर्णांकc, i));
		cpu->mask_cache[i] = ~पूर्णांकc->irq_fwd_mask[i];
	पूर्ण

	parent_irq = irq_of_parse_and_map(dn, idx);
	अगर (!parent_irq) अणु
		pr_err("failed to map parent interrupt %d\n", parent_irq);
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_bool(dn, "brcm,irq-can-wake"))
		enable_irq_wake(parent_irq);

	irq_set_chained_handler_and_data(parent_irq, bcm7038_l1_irq_handle,
					 पूर्णांकc);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * We keep a list of bcm7038_l1_chip used क्रम suspend/resume. This hack is
 * used because the काष्ठा chip_type suspend/resume hooks are not called
 * unless chip_type is hooked onto a generic_chip. Since this driver करोes
 * not use generic_chip, we need to manually hook our resume/suspend to
 * syscore_ops.
 */
अटल LIST_HEAD(bcm7038_l1_पूर्णांकcs_list);
अटल DEFINE_RAW_SPINLOCK(bcm7038_l1_पूर्णांकcs_lock);

अटल पूर्णांक bcm7038_l1_suspend(व्योम)
अणु
	काष्ठा bcm7038_l1_chip *पूर्णांकc;
	पूर्णांक boot_cpu, word;
	u32 val;

	/* Wakeup पूर्णांकerrupt should only come from the boot cpu */
#अगर_घोषित CONFIG_SMP
	boot_cpu = cpu_logical_map(0);
#अन्यथा
	boot_cpu = 0;
#पूर्ण_अगर

	list_क्रम_each_entry(पूर्णांकc, &bcm7038_l1_पूर्णांकcs_list, list) अणु
		क्रम (word = 0; word < पूर्णांकc->n_words; word++) अणु
			val = पूर्णांकc->wake_mask[word] | पूर्णांकc->irq_fwd_mask[word];
			l1_ग_लिखोl(~val,
				पूर्णांकc->cpus[boot_cpu]->map_base + reg_mask_set(पूर्णांकc, word));
			l1_ग_लिखोl(val,
				पूर्णांकc->cpus[boot_cpu]->map_base + reg_mask_clr(पूर्णांकc, word));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bcm7038_l1_resume(व्योम)
अणु
	काष्ठा bcm7038_l1_chip *पूर्णांकc;
	पूर्णांक boot_cpu, word;

#अगर_घोषित CONFIG_SMP
	boot_cpu = cpu_logical_map(0);
#अन्यथा
	boot_cpu = 0;
#पूर्ण_अगर

	list_क्रम_each_entry(पूर्णांकc, &bcm7038_l1_पूर्णांकcs_list, list) अणु
		क्रम (word = 0; word < पूर्णांकc->n_words; word++) अणु
			l1_ग_लिखोl(पूर्णांकc->cpus[boot_cpu]->mask_cache[word],
				पूर्णांकc->cpus[boot_cpu]->map_base + reg_mask_set(पूर्णांकc, word));
			l1_ग_लिखोl(~पूर्णांकc->cpus[boot_cpu]->mask_cache[word],
				पूर्णांकc->cpus[boot_cpu]->map_base + reg_mask_clr(पूर्णांकc, word));
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा syscore_ops bcm7038_l1_syscore_ops = अणु
	.suspend	= bcm7038_l1_suspend,
	.resume		= bcm7038_l1_resume,
पूर्ण;

अटल पूर्णांक bcm7038_l1_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा bcm7038_l1_chip *पूर्णांकc = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ flags;
	u32 word = d->hwirq / IRQS_PER_WORD;
	u32 mask = BIT(d->hwirq % IRQS_PER_WORD);

	raw_spin_lock_irqsave(&पूर्णांकc->lock, flags);
	अगर (on)
		पूर्णांकc->wake_mask[word] |= mask;
	अन्यथा
		पूर्णांकc->wake_mask[word] &= ~mask;
	raw_spin_unlock_irqrestore(&पूर्णांकc->lock, flags);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा irq_chip bcm7038_l1_irq_chip = अणु
	.name			= "bcm7038-l1",
	.irq_mask		= bcm7038_l1_mask,
	.irq_unmask		= bcm7038_l1_unmask,
	.irq_set_affinity	= bcm7038_l1_set_affinity,
#अगर_घोषित CONFIG_SMP
	.irq_cpu_offline	= bcm7038_l1_cpu_offline,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PM_SLEEP
	.irq_set_wake		= bcm7038_l1_set_wake,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक bcm7038_l1_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
			  irq_hw_number_t hw_irq)
अणु
	काष्ठा bcm7038_l1_chip *पूर्णांकc = d->host_data;
	u32 mask = BIT(hw_irq % IRQS_PER_WORD);
	u32 word = hw_irq / IRQS_PER_WORD;

	अगर (पूर्णांकc->irq_fwd_mask[word] & mask)
		वापस -EPERM;

	irq_set_chip_and_handler(virq, &bcm7038_l1_irq_chip, handle_level_irq);
	irq_set_chip_data(virq, d->host_data);
	irqd_set_single_target(irq_desc_get_irq_data(irq_to_desc(virq)));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops bcm7038_l1_करोमुख्य_ops = अणु
	.xlate			= irq_करोमुख्य_xlate_onecell,
	.map			= bcm7038_l1_map,
पूर्ण;

अटल पूर्णांक __init bcm7038_l1_of_init(काष्ठा device_node *dn,
			      काष्ठा device_node *parent)
अणु
	काष्ठा bcm7038_l1_chip *पूर्णांकc;
	पूर्णांक idx, ret;

	पूर्णांकc = kzalloc(माप(*पूर्णांकc), GFP_KERNEL);
	अगर (!पूर्णांकc)
		वापस -ENOMEM;

	raw_spin_lock_init(&पूर्णांकc->lock);
	क्रम_each_possible_cpu(idx) अणु
		ret = bcm7038_l1_init_one(dn, idx, पूर्णांकc);
		अगर (ret < 0) अणु
			अगर (idx)
				अवरोध;
			pr_err("failed to remap intc L1 registers\n");
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	पूर्णांकc->करोमुख्य = irq_करोमुख्य_add_linear(dn, IRQS_PER_WORD * पूर्णांकc->n_words,
					     &bcm7038_l1_करोमुख्य_ops,
					     पूर्णांकc);
	अगर (!पूर्णांकc->करोमुख्य) अणु
		ret = -ENOMEM;
		जाओ out_unmap;
	पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
	/* Add bcm7038_l1_chip पूर्णांकo a list */
	raw_spin_lock(&bcm7038_l1_पूर्णांकcs_lock);
	list_add_tail(&पूर्णांकc->list, &bcm7038_l1_पूर्णांकcs_list);
	raw_spin_unlock(&bcm7038_l1_पूर्णांकcs_lock);

	अगर (list_is_singular(&bcm7038_l1_पूर्णांकcs_list))
		रेजिस्टर_syscore_ops(&bcm7038_l1_syscore_ops);
#पूर्ण_अगर

	pr_info("registered BCM7038 L1 intc (%pOF, IRQs: %d)\n",
		dn, IRQS_PER_WORD * पूर्णांकc->n_words);

	वापस 0;

out_unmap:
	क्रम_each_possible_cpu(idx) अणु
		काष्ठा bcm7038_l1_cpu *cpu = पूर्णांकc->cpus[idx];

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

IRQCHIP_DECLARE(bcm7038_l1, "brcm,bcm7038-l1-intc", bcm7038_l1_of_init);
