<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * Copyright (c) 2020 MediaTek Inc.
 * Author Mark-PK Tsai <mark-pk.tsai@mediatek.com>
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/syscore_ops.h>

#घोषणा MST_INTC_MAX_IRQS	64

#घोषणा INTC_MASK		0x0
#घोषणा INTC_REV_POLARITY	0x10
#घोषणा INTC_EOI		0x20

#अगर_घोषित CONFIG_PM_SLEEP
अटल LIST_HEAD(mst_पूर्णांकc_list);
#पूर्ण_अगर

काष्ठा mst_पूर्णांकc_chip_data अणु
	raw_spinlock_t	lock;
	अचिन्हित पूर्णांक	irq_start, nr_irqs;
	व्योम __iomem	*base;
	bool		no_eoi;
#अगर_घोषित CONFIG_PM_SLEEP
	काष्ठा list_head entry;
	u16 saved_polarity_conf[DIV_ROUND_UP(MST_INTC_MAX_IRQS, 16)];
#पूर्ण_अगर
पूर्ण;

अटल व्योम mst_set_irq(काष्ठा irq_data *d, u32 offset)
अणु
	irq_hw_number_t hwirq = irqd_to_hwirq(d);
	काष्ठा mst_पूर्णांकc_chip_data *cd = irq_data_get_irq_chip_data(d);
	u16 val, mask;
	अचिन्हित दीर्घ flags;

	mask = 1 << (hwirq % 16);
	offset += (hwirq / 16) * 4;

	raw_spin_lock_irqsave(&cd->lock, flags);
	val = पढ़ोw_relaxed(cd->base + offset) | mask;
	ग_लिखोw_relaxed(val, cd->base + offset);
	raw_spin_unlock_irqrestore(&cd->lock, flags);
पूर्ण

अटल व्योम mst_clear_irq(काष्ठा irq_data *d, u32 offset)
अणु
	irq_hw_number_t hwirq = irqd_to_hwirq(d);
	काष्ठा mst_पूर्णांकc_chip_data *cd = irq_data_get_irq_chip_data(d);
	u16 val, mask;
	अचिन्हित दीर्घ flags;

	mask = 1 << (hwirq % 16);
	offset += (hwirq / 16) * 4;

	raw_spin_lock_irqsave(&cd->lock, flags);
	val = पढ़ोw_relaxed(cd->base + offset) & ~mask;
	ग_लिखोw_relaxed(val, cd->base + offset);
	raw_spin_unlock_irqrestore(&cd->lock, flags);
पूर्ण

अटल व्योम mst_पूर्णांकc_mask_irq(काष्ठा irq_data *d)
अणु
	mst_set_irq(d, INTC_MASK);
	irq_chip_mask_parent(d);
पूर्ण

अटल व्योम mst_पूर्णांकc_unmask_irq(काष्ठा irq_data *d)
अणु
	mst_clear_irq(d, INTC_MASK);
	irq_chip_unmask_parent(d);
पूर्ण

अटल व्योम mst_पूर्णांकc_eoi_irq(काष्ठा irq_data *d)
अणु
	काष्ठा mst_पूर्णांकc_chip_data *cd = irq_data_get_irq_chip_data(d);

	अगर (!cd->no_eoi)
		mst_set_irq(d, INTC_EOI);

	irq_chip_eoi_parent(d);
पूर्ण

अटल पूर्णांक mst_irq_chip_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल IRQ_TYPE_LEVEL_LOW:
	हाल IRQ_TYPE_EDGE_FALLING:
		mst_set_irq(data, INTC_REV_POLARITY);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
	हाल IRQ_TYPE_EDGE_RISING:
		mst_clear_irq(data, INTC_REV_POLARITY);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस irq_chip_set_type_parent(data, IRQ_TYPE_LEVEL_HIGH);
पूर्ण

अटल काष्ठा irq_chip mst_पूर्णांकc_chip = अणु
	.name			= "mst-intc",
	.irq_mask		= mst_पूर्णांकc_mask_irq,
	.irq_unmask		= mst_पूर्णांकc_unmask_irq,
	.irq_eoi		= mst_पूर्णांकc_eoi_irq,
	.irq_get_irqchip_state	= irq_chip_get_parent_state,
	.irq_set_irqchip_state	= irq_chip_set_parent_state,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
	.irq_set_vcpu_affinity	= irq_chip_set_vcpu_affinity_parent,
	.irq_set_type		= mst_irq_chip_set_type,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.flags			= IRQCHIP_SET_TYPE_MASKED |
				  IRQCHIP_SKIP_SET_WAKE |
				  IRQCHIP_MASK_ON_SUSPEND,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम mst_पूर्णांकc_polarity_save(काष्ठा mst_पूर्णांकc_chip_data *cd)
अणु
	पूर्णांक i;
	व्योम __iomem *addr = cd->base + INTC_REV_POLARITY;

	क्रम (i = 0; i < DIV_ROUND_UP(cd->nr_irqs, 16); i++)
		cd->saved_polarity_conf[i] = पढ़ोw_relaxed(addr + i * 4);
पूर्ण

अटल व्योम mst_पूर्णांकc_polarity_restore(काष्ठा mst_पूर्णांकc_chip_data *cd)
अणु
	पूर्णांक i;
	व्योम __iomem *addr = cd->base + INTC_REV_POLARITY;

	क्रम (i = 0; i < DIV_ROUND_UP(cd->nr_irqs, 16); i++)
		ग_लिखोw_relaxed(cd->saved_polarity_conf[i], addr + i * 4);
पूर्ण

अटल व्योम mst_irq_resume(व्योम)
अणु
	काष्ठा mst_पूर्णांकc_chip_data *cd;

	list_क्रम_each_entry(cd, &mst_पूर्णांकc_list, entry)
		mst_पूर्णांकc_polarity_restore(cd);
पूर्ण

अटल पूर्णांक mst_irq_suspend(व्योम)
अणु
	काष्ठा mst_पूर्णांकc_chip_data *cd;

	list_क्रम_each_entry(cd, &mst_पूर्णांकc_list, entry)
		mst_पूर्णांकc_polarity_save(cd);
	वापस 0;
पूर्ण

अटल काष्ठा syscore_ops mst_irq_syscore_ops = अणु
	.suspend	= mst_irq_suspend,
	.resume		= mst_irq_resume,
पूर्ण;

अटल पूर्णांक __init mst_irq_pm_init(व्योम)
अणु
	रेजिस्टर_syscore_ops(&mst_irq_syscore_ops);
	वापस 0;
पूर्ण
late_initcall(mst_irq_pm_init);
#पूर्ण_अगर

अटल पूर्णांक mst_पूर्णांकc_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
				     काष्ठा irq_fwspec *fwspec,
				     अचिन्हित दीर्घ *hwirq,
				     अचिन्हित पूर्णांक *type)
अणु
	काष्ठा mst_पूर्णांकc_chip_data *cd = d->host_data;

	अगर (is_of_node(fwspec->fwnode)) अणु
		अगर (fwspec->param_count != 3)
			वापस -EINVAL;

		/* No PPI should poपूर्णांक to this करोमुख्य */
		अगर (fwspec->param[0] != 0)
			वापस -EINVAL;

		अगर (fwspec->param[1] >= cd->nr_irqs)
			वापस -EINVAL;

		*hwirq = fwspec->param[1];
		*type = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mst_पूर्णांकc_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				 अचिन्हित पूर्णांक nr_irqs, व्योम *data)
अणु
	पूर्णांक i;
	irq_hw_number_t hwirq;
	काष्ठा irq_fwspec parent_fwspec, *fwspec = data;
	काष्ठा mst_पूर्णांकc_chip_data *cd = करोमुख्य->host_data;

	/* Not GIC compliant */
	अगर (fwspec->param_count != 3)
		वापस -EINVAL;

	/* No PPI should poपूर्णांक to this करोमुख्य */
	अगर (fwspec->param[0])
		वापस -EINVAL;

	hwirq = fwspec->param[1];
	क्रम (i = 0; i < nr_irqs; i++)
		irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq + i, hwirq + i,
					      &mst_पूर्णांकc_chip,
					      करोमुख्य->host_data);

	parent_fwspec = *fwspec;
	parent_fwspec.fwnode = करोमुख्य->parent->fwnode;
	parent_fwspec.param[1] = cd->irq_start + hwirq;

	/*
	 * mst-पूर्णांकc latch the पूर्णांकerrupt request अगर it's edge triggered,
	 * so the output संकेत to parent GIC is always level sensitive.
	 * And अगर the irq संकेत is active low, configure it to active high
	 * to meet GIC SPI spec in mst_irq_chip_set_type via REV_POLARITY bit.
	 */
	parent_fwspec.param[2] = IRQ_TYPE_LEVEL_HIGH;

	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs, &parent_fwspec);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mst_पूर्णांकc_करोमुख्य_ops = अणु
	.translate	= mst_पूर्णांकc_करोमुख्य_translate,
	.alloc		= mst_पूर्णांकc_करोमुख्य_alloc,
	.मुक्त		= irq_करोमुख्य_मुक्त_irqs_common,
पूर्ण;

अटल पूर्णांक __init mst_पूर्णांकc_of_init(काष्ठा device_node *dn,
				   काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य, *करोमुख्य_parent;
	काष्ठा mst_पूर्णांकc_chip_data *cd;
	u32 irq_start, irq_end;

	करोमुख्य_parent = irq_find_host(parent);
	अगर (!करोमुख्य_parent) अणु
		pr_err("mst-intc: interrupt-parent not found\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32_index(dn, "mstar,irqs-map-range", 0, &irq_start) ||
	    of_property_पढ़ो_u32_index(dn, "mstar,irqs-map-range", 1, &irq_end))
		वापस -EINVAL;

	cd = kzalloc(माप(*cd), GFP_KERNEL);
	अगर (!cd)
		वापस -ENOMEM;

	cd->base = of_iomap(dn, 0);
	अगर (!cd->base) अणु
		kमुक्त(cd);
		वापस -ENOMEM;
	पूर्ण

	cd->no_eoi = of_property_पढ़ो_bool(dn, "mstar,intc-no-eoi");
	raw_spin_lock_init(&cd->lock);
	cd->irq_start = irq_start;
	cd->nr_irqs = irq_end - irq_start + 1;
	करोमुख्य = irq_करोमुख्य_add_hierarchy(करोमुख्य_parent, 0, cd->nr_irqs, dn,
					  &mst_पूर्णांकc_करोमुख्य_ops, cd);
	अगर (!करोमुख्य) अणु
		iounmap(cd->base);
		kमुक्त(cd);
		वापस -ENOMEM;
	पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
	INIT_LIST_HEAD(&cd->entry);
	list_add_tail(&cd->entry, &mst_पूर्णांकc_list);
#पूर्ण_अगर
	वापस 0;
पूर्ण

IRQCHIP_DECLARE(mst_पूर्णांकc, "mstar,mst-intc", mst_पूर्णांकc_of_init);
