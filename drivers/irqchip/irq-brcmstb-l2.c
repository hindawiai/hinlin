<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic Broadcom Set Top Box Level 2 Interrupt controller driver
 *
 * Copyright (C) 2014-2017 Broadcom
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME	": " fmt

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>

काष्ठा brcmstb_पूर्णांकc_init_params अणु
	irq_flow_handler_t handler;
	पूर्णांक cpu_status;
	पूर्णांक cpu_clear;
	पूर्णांक cpu_mask_status;
	पूर्णांक cpu_mask_set;
	पूर्णांक cpu_mask_clear;
पूर्ण;

/* Register offsets in the L2 latched पूर्णांकerrupt controller */
अटल स्थिर काष्ठा brcmstb_पूर्णांकc_init_params l2_edge_पूर्णांकc_init = अणु
	.handler		= handle_edge_irq,
	.cpu_status		= 0x00,
	.cpu_clear		= 0x08,
	.cpu_mask_status	= 0x0c,
	.cpu_mask_set		= 0x10,
	.cpu_mask_clear		= 0x14
पूर्ण;

/* Register offsets in the L2 level पूर्णांकerrupt controller */
अटल स्थिर काष्ठा brcmstb_पूर्णांकc_init_params l2_lvl_पूर्णांकc_init = अणु
	.handler		= handle_level_irq,
	.cpu_status		= 0x00,
	.cpu_clear		= -1, /* Register not present */
	.cpu_mask_status	= 0x04,
	.cpu_mask_set		= 0x08,
	.cpu_mask_clear		= 0x0C
पूर्ण;

/* L2 पूर्णांकc निजी data काष्ठाure */
काष्ठा brcmstb_l2_पूर्णांकc_data अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा irq_chip_generic *gc;
	पूर्णांक status_offset;
	पूर्णांक mask_offset;
	bool can_wake;
	u32 saved_mask; /* क्रम suspend/resume */
पूर्ण;

/**
 * brcmstb_l2_mask_and_ack - Mask and ack pending पूर्णांकerrupt
 * @d: irq_data
 *
 * Chip has separate enable/disable रेजिस्टरs instead of a single mask
 * रेजिस्टर and pending पूर्णांकerrupt is acknowledged by setting a bit.
 *
 * Note: This function is generic and could easily be added to the
 * generic irqchip implementation अगर there ever becomes a will to करो so.
 * Perhaps with a name like irq_gc_mask_disable_and_ack_set().
 *
 * e.g.: https://patchwork.kernel.org/patch/9831047/
 */
अटल व्योम brcmstb_l2_mask_and_ack(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	u32 mask = d->mask;

	irq_gc_lock(gc);
	irq_reg_ग_लिखोl(gc, mask, ct->regs.disable);
	*ct->mask_cache &= ~mask;
	irq_reg_ग_लिखोl(gc, mask, ct->regs.ack);
	irq_gc_unlock(gc);
पूर्ण

अटल व्योम brcmstb_l2_पूर्णांकc_irq_handle(काष्ठा irq_desc *desc)
अणु
	काष्ठा brcmstb_l2_पूर्णांकc_data *b = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक irq;
	u32 status;

	chained_irq_enter(chip, desc);

	status = irq_reg_पढ़ोl(b->gc, b->status_offset) &
		~(irq_reg_पढ़ोl(b->gc, b->mask_offset));

	अगर (status == 0) अणु
		raw_spin_lock(&desc->lock);
		handle_bad_irq(desc);
		raw_spin_unlock(&desc->lock);
		जाओ out;
	पूर्ण

	करो अणु
		irq = ffs(status) - 1;
		status &= ~(1 << irq);
		generic_handle_irq(irq_linear_revmap(b->करोमुख्य, irq));
	पूर्ण जबतक (status);
out:
	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम brcmstb_l2_पूर्णांकc_suspend(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	काष्ठा brcmstb_l2_पूर्णांकc_data *b = gc->निजी;
	अचिन्हित दीर्घ flags;

	irq_gc_lock_irqsave(gc, flags);
	/* Save the current mask */
	b->saved_mask = irq_reg_पढ़ोl(gc, ct->regs.mask);

	अगर (b->can_wake) अणु
		/* Program the wakeup mask */
		irq_reg_ग_लिखोl(gc, ~gc->wake_active, ct->regs.disable);
		irq_reg_ग_लिखोl(gc, gc->wake_active, ct->regs.enable);
	पूर्ण
	irq_gc_unlock_irqrestore(gc, flags);
पूर्ण

अटल व्योम brcmstb_l2_पूर्णांकc_resume(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	काष्ठा brcmstb_l2_पूर्णांकc_data *b = gc->निजी;
	अचिन्हित दीर्घ flags;

	irq_gc_lock_irqsave(gc, flags);
	अगर (ct->chip.irq_ack) अणु
		/* Clear unmasked non-wakeup पूर्णांकerrupts */
		irq_reg_ग_लिखोl(gc, ~b->saved_mask & ~gc->wake_active,
				ct->regs.ack);
	पूर्ण

	/* Restore the saved mask */
	irq_reg_ग_लिखोl(gc, b->saved_mask, ct->regs.disable);
	irq_reg_ग_लिखोl(gc, ~b->saved_mask, ct->regs.enable);
	irq_gc_unlock_irqrestore(gc, flags);
पूर्ण

अटल पूर्णांक __init brcmstb_l2_पूर्णांकc_of_init(काष्ठा device_node *np,
					  काष्ठा device_node *parent,
					  स्थिर काष्ठा brcmstb_पूर्णांकc_init_params
					  *init_params)
अणु
	अचिन्हित पूर्णांक clr = IRQ_NOREQUEST | IRQ_NOPROBE | IRQ_NOAUTOEN;
	काष्ठा brcmstb_l2_पूर्णांकc_data *data;
	काष्ठा irq_chip_type *ct;
	पूर्णांक ret;
	अचिन्हित पूर्णांक flags;
	पूर्णांक parent_irq;
	व्योम __iomem *base;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	base = of_iomap(np, 0);
	अगर (!base) अणु
		pr_err("failed to remap intc L2 registers\n");
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	/* Disable all पूर्णांकerrupts by शेष */
	ग_लिखोl(0xffffffff, base + init_params->cpu_mask_set);

	/* Wakeup पूर्णांकerrupts may be retained from S5 (cold boot) */
	data->can_wake = of_property_पढ़ो_bool(np, "brcm,irq-can-wake");
	अगर (!data->can_wake && (init_params->cpu_clear >= 0))
		ग_लिखोl(0xffffffff, base + init_params->cpu_clear);

	parent_irq = irq_of_parse_and_map(np, 0);
	अगर (!parent_irq) अणु
		pr_err("failed to find parent interrupt\n");
		ret = -EINVAL;
		जाओ out_unmap;
	पूर्ण

	data->करोमुख्य = irq_करोमुख्य_add_linear(np, 32,
				&irq_generic_chip_ops, शून्य);
	अगर (!data->करोमुख्य) अणु
		ret = -ENOMEM;
		जाओ out_unmap;
	पूर्ण

	/* MIPS chips strapped क्रम BE will स्वतःmagically configure the
	 * peripheral रेजिस्टरs क्रम CPU-native byte order.
	 */
	flags = 0;
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		flags |= IRQ_GC_BE_IO;

	/* Allocate a single Generic IRQ chip क्रम this node */
	ret = irq_alloc_करोमुख्य_generic_chips(data->करोमुख्य, 32, 1,
			np->full_name, init_params->handler, clr, 0, flags);
	अगर (ret) अणु
		pr_err("failed to allocate generic irq chip\n");
		जाओ out_मुक्त_करोमुख्य;
	पूर्ण

	/* Set the IRQ chaining logic */
	irq_set_chained_handler_and_data(parent_irq,
					 brcmstb_l2_पूर्णांकc_irq_handle, data);

	data->gc = irq_get_करोमुख्य_generic_chip(data->करोमुख्य, 0);
	data->gc->reg_base = base;
	data->gc->निजी = data;
	data->status_offset = init_params->cpu_status;
	data->mask_offset = init_params->cpu_mask_status;

	ct = data->gc->chip_types;

	अगर (init_params->cpu_clear >= 0) अणु
		ct->regs.ack = init_params->cpu_clear;
		ct->chip.irq_ack = irq_gc_ack_set_bit;
		ct->chip.irq_mask_ack = brcmstb_l2_mask_and_ack;
	पूर्ण अन्यथा अणु
		/* No Ack - but still slightly more efficient to define this */
		ct->chip.irq_mask_ack = irq_gc_mask_disable_reg;
	पूर्ण

	ct->chip.irq_mask = irq_gc_mask_disable_reg;
	ct->regs.disable = init_params->cpu_mask_set;
	ct->regs.mask = init_params->cpu_mask_status;

	ct->chip.irq_unmask = irq_gc_unmask_enable_reg;
	ct->regs.enable = init_params->cpu_mask_clear;

	ct->chip.irq_suspend = brcmstb_l2_पूर्णांकc_suspend;
	ct->chip.irq_resume = brcmstb_l2_पूर्णांकc_resume;
	ct->chip.irq_pm_shutकरोwn = brcmstb_l2_पूर्णांकc_suspend;

	अगर (data->can_wake) अणु
		/* This IRQ chip can wake the प्रणाली, set all child पूर्णांकerrupts
		 * in wake_enabled mask
		 */
		data->gc->wake_enabled = 0xffffffff;
		ct->chip.irq_set_wake = irq_gc_set_wake;
		enable_irq_wake(parent_irq);
	पूर्ण

	pr_info("registered L2 intc (%pOF, parent irq: %d)\n", np, parent_irq);

	वापस 0;

out_मुक्त_करोमुख्य:
	irq_करोमुख्य_हटाओ(data->करोमुख्य);
out_unmap:
	iounmap(base);
out_मुक्त:
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक __init brcmstb_l2_edge_पूर्णांकc_of_init(काष्ठा device_node *np,
	काष्ठा device_node *parent)
अणु
	वापस brcmstb_l2_पूर्णांकc_of_init(np, parent, &l2_edge_पूर्णांकc_init);
पूर्ण
IRQCHIP_DECLARE(brcmstb_l2_पूर्णांकc, "brcm,l2-intc", brcmstb_l2_edge_पूर्णांकc_of_init);
IRQCHIP_DECLARE(brcmstb_hअगर_spi_l2_पूर्णांकc, "brcm,hif-spi-l2-intc",
		brcmstb_l2_edge_पूर्णांकc_of_init);
IRQCHIP_DECLARE(brcmstb_upg_aux_aon_l2_पूर्णांकc, "brcm,upg-aux-aon-l2-intc",
		brcmstb_l2_edge_पूर्णांकc_of_init);

अटल पूर्णांक __init brcmstb_l2_lvl_पूर्णांकc_of_init(काष्ठा device_node *np,
	काष्ठा device_node *parent)
अणु
	वापस brcmstb_l2_पूर्णांकc_of_init(np, parent, &l2_lvl_पूर्णांकc_init);
पूर्ण
IRQCHIP_DECLARE(bcm7271_l2_पूर्णांकc, "brcm,bcm7271-l2-intc",
	brcmstb_l2_lvl_पूर्णांकc_of_init);
