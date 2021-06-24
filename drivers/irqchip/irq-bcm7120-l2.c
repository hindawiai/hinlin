<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Broadcom BCM7120 style Level 2 पूर्णांकerrupt controller driver
 *
 * Copyright (C) 2014 Broadcom Corporation
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME	": " fmt

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/reboot.h>
#समावेश <linux/bitops.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>

/* Register offset in the L2 पूर्णांकerrupt controller */
#घोषणा IRQEN		0x00
#घोषणा IRQSTAT		0x04

#घोषणा MAX_WORDS	4
#घोषणा MAX_MAPPINGS	(MAX_WORDS * 2)
#घोषणा IRQS_PER_WORD	32

काष्ठा bcm7120_l1_पूर्णांकc_data अणु
	काष्ठा bcm7120_l2_पूर्णांकc_data *b;
	u32 irq_map_mask[MAX_WORDS];
पूर्ण;

काष्ठा bcm7120_l2_पूर्णांकc_data अणु
	अचिन्हित पूर्णांक n_words;
	व्योम __iomem *map_base[MAX_MAPPINGS];
	व्योम __iomem *pair_base[MAX_WORDS];
	पूर्णांक en_offset[MAX_WORDS];
	पूर्णांक stat_offset[MAX_WORDS];
	काष्ठा irq_करोमुख्य *करोमुख्य;
	bool can_wake;
	u32 irq_fwd_mask[MAX_WORDS];
	काष्ठा bcm7120_l1_पूर्णांकc_data *l1_data;
	पूर्णांक num_parent_irqs;
	स्थिर __be32 *map_mask_prop;
पूर्ण;

अटल व्योम bcm7120_l2_पूर्णांकc_irq_handle(काष्ठा irq_desc *desc)
अणु
	काष्ठा bcm7120_l1_पूर्णांकc_data *data = irq_desc_get_handler_data(desc);
	काष्ठा bcm7120_l2_पूर्णांकc_data *b = data->b;
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक idx;

	chained_irq_enter(chip, desc);

	क्रम (idx = 0; idx < b->n_words; idx++) अणु
		पूर्णांक base = idx * IRQS_PER_WORD;
		काष्ठा irq_chip_generic *gc =
			irq_get_करोमुख्य_generic_chip(b->करोमुख्य, base);
		अचिन्हित दीर्घ pending;
		पूर्णांक hwirq;

		irq_gc_lock(gc);
		pending = irq_reg_पढ़ोl(gc, b->stat_offset[idx]) &
					    gc->mask_cache &
					    data->irq_map_mask[idx];
		irq_gc_unlock(gc);

		क्रम_each_set_bit(hwirq, &pending, IRQS_PER_WORD) अणु
			generic_handle_irq(irq_find_mapping(b->करोमुख्य,
					   base + hwirq));
		पूर्ण
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम bcm7120_l2_पूर्णांकc_suspend(काष्ठा irq_chip_generic *gc)
अणु
	काष्ठा bcm7120_l2_पूर्णांकc_data *b = gc->निजी;
	काष्ठा irq_chip_type *ct = gc->chip_types;

	irq_gc_lock(gc);
	अगर (b->can_wake)
		irq_reg_ग_लिखोl(gc, gc->mask_cache | gc->wake_active,
			       ct->regs.mask);
	irq_gc_unlock(gc);
पूर्ण

अटल व्योम bcm7120_l2_पूर्णांकc_resume(काष्ठा irq_chip_generic *gc)
अणु
	काष्ठा irq_chip_type *ct = gc->chip_types;

	/* Restore the saved mask */
	irq_gc_lock(gc);
	irq_reg_ग_लिखोl(gc, gc->mask_cache, ct->regs.mask);
	irq_gc_unlock(gc);
पूर्ण

अटल पूर्णांक bcm7120_l2_पूर्णांकc_init_one(काष्ठा device_node *dn,
					काष्ठा bcm7120_l2_पूर्णांकc_data *data,
					पूर्णांक irq, u32 *valid_mask)
अणु
	काष्ठा bcm7120_l1_पूर्णांकc_data *l1_data = &data->l1_data[irq];
	पूर्णांक parent_irq;
	अचिन्हित पूर्णांक idx;

	parent_irq = irq_of_parse_and_map(dn, irq);
	अगर (!parent_irq) अणु
		pr_err("failed to map interrupt %d\n", irq);
		वापस -EINVAL;
	पूर्ण

	/* For multiple parent IRQs with multiple words, this looks like:
	 * <irq0_w0 irq0_w1 irq1_w0 irq1_w1 ...>
	 *
	 * We need to associate a given parent पूर्णांकerrupt with its corresponding
	 * map_mask in order to mask the status रेजिस्टर with it because we
	 * have the same handler being called क्रम multiple parent पूर्णांकerrupts.
	 *
	 * This is typically something needed on BCM7xxx (STB chips).
	 */
	क्रम (idx = 0; idx < data->n_words; idx++) अणु
		अगर (data->map_mask_prop) अणु
			l1_data->irq_map_mask[idx] |=
				be32_to_cpup(data->map_mask_prop +
					     irq * data->n_words + idx);
		पूर्ण अन्यथा अणु
			l1_data->irq_map_mask[idx] = 0xffffffff;
		पूर्ण
		valid_mask[idx] |= l1_data->irq_map_mask[idx];
	पूर्ण

	l1_data->b = data;

	irq_set_chained_handler_and_data(parent_irq,
					 bcm7120_l2_पूर्णांकc_irq_handle, l1_data);
	अगर (data->can_wake)
		enable_irq_wake(parent_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __init bcm7120_l2_पूर्णांकc_iomap_7120(काष्ठा device_node *dn,
					     काष्ठा bcm7120_l2_पूर्णांकc_data *data)
अणु
	पूर्णांक ret;

	data->map_base[0] = of_iomap(dn, 0);
	अगर (!data->map_base[0]) अणु
		pr_err("unable to map registers\n");
		वापस -ENOMEM;
	पूर्ण

	data->pair_base[0] = data->map_base[0];
	data->en_offset[0] = IRQEN;
	data->stat_offset[0] = IRQSTAT;
	data->n_words = 1;

	ret = of_property_पढ़ो_u32_array(dn, "brcm,int-fwd-mask",
					 data->irq_fwd_mask, data->n_words);
	अगर (ret != 0 && ret != -EINVAL) अणु
		/* property exists but has the wrong number of words */
		pr_err("invalid brcm,int-fwd-mask property\n");
		वापस -EINVAL;
	पूर्ण

	data->map_mask_prop = of_get_property(dn, "brcm,int-map-mask", &ret);
	अगर (!data->map_mask_prop ||
	    (ret != (माप(__be32) * data->num_parent_irqs * data->n_words))) अणु
		pr_err("invalid brcm,int-map-mask property\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init bcm7120_l2_पूर्णांकc_iomap_3380(काष्ठा device_node *dn,
					     काष्ठा bcm7120_l2_पूर्णांकc_data *data)
अणु
	अचिन्हित पूर्णांक gc_idx;

	क्रम (gc_idx = 0; gc_idx < MAX_WORDS; gc_idx++) अणु
		अचिन्हित पूर्णांक map_idx = gc_idx * 2;
		व्योम __iomem *en = of_iomap(dn, map_idx + 0);
		व्योम __iomem *stat = of_iomap(dn, map_idx + 1);
		व्योम __iomem *base = min(en, stat);

		data->map_base[map_idx + 0] = en;
		data->map_base[map_idx + 1] = stat;

		अगर (!base)
			अवरोध;

		data->pair_base[gc_idx] = base;
		data->en_offset[gc_idx] = en - base;
		data->stat_offset[gc_idx] = stat - base;
	पूर्ण

	अगर (!gc_idx) अणु
		pr_err("unable to map registers\n");
		वापस -EINVAL;
	पूर्ण

	data->n_words = gc_idx;
	वापस 0;
पूर्ण

अटल पूर्णांक __init bcm7120_l2_पूर्णांकc_probe(काष्ठा device_node *dn,
				 काष्ठा device_node *parent,
				 पूर्णांक (*iomap_regs_fn)(काष्ठा device_node *,
					काष्ठा bcm7120_l2_पूर्णांकc_data *),
				 स्थिर अक्षर *पूर्णांकc_name)
अणु
	अचिन्हित पूर्णांक clr = IRQ_NOREQUEST | IRQ_NOPROBE | IRQ_NOAUTOEN;
	काष्ठा bcm7120_l2_पूर्णांकc_data *data;
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक idx, irq, flags;
	u32 valid_mask[MAX_WORDS] = अणु पूर्ण;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->num_parent_irqs = of_irq_count(dn);
	अगर (data->num_parent_irqs <= 0) अणु
		pr_err("invalid number of parent interrupts\n");
		ret = -ENOMEM;
		जाओ out_unmap;
	पूर्ण

	data->l1_data = kसुस्मृति(data->num_parent_irqs, माप(*data->l1_data),
				GFP_KERNEL);
	अगर (!data->l1_data) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_l1_data;
	पूर्ण

	ret = iomap_regs_fn(dn, data);
	अगर (ret < 0)
		जाओ out_मुक्त_l1_data;

	data->can_wake = of_property_पढ़ो_bool(dn, "brcm,irq-can-wake");

	क्रम (irq = 0; irq < data->num_parent_irqs; irq++) अणु
		ret = bcm7120_l2_पूर्णांकc_init_one(dn, data, irq, valid_mask);
		अगर (ret)
			जाओ out_मुक्त_l1_data;
	पूर्ण

	data->करोमुख्य = irq_करोमुख्य_add_linear(dn, IRQS_PER_WORD * data->n_words,
					     &irq_generic_chip_ops, शून्य);
	अगर (!data->करोमुख्य) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_l1_data;
	पूर्ण

	/* MIPS chips strapped क्रम BE will स्वतःmagically configure the
	 * peripheral रेजिस्टरs क्रम CPU-native byte order.
	 */
	flags = IRQ_GC_INIT_MASK_CACHE;
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		flags |= IRQ_GC_BE_IO;

	ret = irq_alloc_करोमुख्य_generic_chips(data->करोमुख्य, IRQS_PER_WORD, 1,
				dn->full_name, handle_level_irq, clr, 0, flags);
	अगर (ret) अणु
		pr_err("failed to allocate generic irq chip\n");
		जाओ out_मुक्त_करोमुख्य;
	पूर्ण

	क्रम (idx = 0; idx < data->n_words; idx++) अणु
		irq = idx * IRQS_PER_WORD;
		gc = irq_get_करोमुख्य_generic_chip(data->करोमुख्य, irq);

		gc->unused = 0xffffffff & ~valid_mask[idx];
		gc->निजी = data;
		ct = gc->chip_types;

		gc->reg_base = data->pair_base[idx];
		ct->regs.mask = data->en_offset[idx];

		/* gc->reg_base is defined and so is gc->ग_लिखोl */
		irq_reg_ग_लिखोl(gc, data->irq_fwd_mask[idx],
			       data->en_offset[idx]);

		ct->chip.irq_mask = irq_gc_mask_clr_bit;
		ct->chip.irq_unmask = irq_gc_mask_set_bit;
		ct->chip.irq_ack = irq_gc_noop;
		gc->suspend = bcm7120_l2_पूर्णांकc_suspend;
		gc->resume = bcm7120_l2_पूर्णांकc_resume;

		/*
		 * Initialize mask-cache, in हाल we need it क्रम
		 * saving/restoring fwd mask even w/o any child पूर्णांकerrupts
		 * installed
		 */
		gc->mask_cache = irq_reg_पढ़ोl(gc, ct->regs.mask);

		अगर (data->can_wake) अणु
			/* This IRQ chip can wake the प्रणाली, set all
			 * relevant child पूर्णांकerrupts in wake_enabled mask
			 */
			gc->wake_enabled = 0xffffffff;
			gc->wake_enabled &= ~gc->unused;
			ct->chip.irq_set_wake = irq_gc_set_wake;
		पूर्ण
	पूर्ण

	pr_info("registered %s intc (%pOF, parent IRQ(s): %d)\n",
		पूर्णांकc_name, dn, data->num_parent_irqs);

	वापस 0;

out_मुक्त_करोमुख्य:
	irq_करोमुख्य_हटाओ(data->करोमुख्य);
out_मुक्त_l1_data:
	kमुक्त(data->l1_data);
out_unmap:
	क्रम (idx = 0; idx < MAX_MAPPINGS; idx++) अणु
		अगर (data->map_base[idx])
			iounmap(data->map_base[idx]);
	पूर्ण
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक __init bcm7120_l2_पूर्णांकc_probe_7120(काष्ठा device_node *dn,
					     काष्ठा device_node *parent)
अणु
	वापस bcm7120_l2_पूर्णांकc_probe(dn, parent, bcm7120_l2_पूर्णांकc_iomap_7120,
				     "BCM7120 L2");
पूर्ण

अटल पूर्णांक __init bcm7120_l2_पूर्णांकc_probe_3380(काष्ठा device_node *dn,
					     काष्ठा device_node *parent)
अणु
	वापस bcm7120_l2_पूर्णांकc_probe(dn, parent, bcm7120_l2_पूर्णांकc_iomap_3380,
				     "BCM3380 L2");
पूर्ण

IRQCHIP_DECLARE(bcm7120_l2_पूर्णांकc, "brcm,bcm7120-l2-intc",
		bcm7120_l2_पूर्णांकc_probe_7120);

IRQCHIP_DECLARE(bcm3380_l2_पूर्णांकc, "brcm,bcm3380-l2-intc",
		bcm7120_l2_पूर्णांकc_probe_3380);
