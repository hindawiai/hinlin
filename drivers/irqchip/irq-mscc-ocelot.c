<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Microsemi Ocelot IRQ controller driver
 *
 * Copyright (c) 2017 Microsemi Corporation
 */
#समावेश <linux/bitops.h>
#समावेश <linux/irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा ICPU_CFG_INTR_DST_INTR_IDENT(_p, x) ((_p)->reg_off_ident + 0x4 * (x))
#घोषणा ICPU_CFG_INTR_INTR_TRIGGER(_p, x)   ((_p)->reg_off_trigger + 0x4 * (x))

#घोषणा FLAGS_HAS_TRIGGER	BIT(0)
#घोषणा FLAGS_NEED_INIT_ENABLE	BIT(1)

काष्ठा chip_props अणु
	u8 flags;
	u8 reg_off_sticky;
	u8 reg_off_ena;
	u8 reg_off_ena_clr;
	u8 reg_off_ena_set;
	u8 reg_off_ident;
	u8 reg_off_trigger;
	u8 reg_off_ena_irq0;
	u8 n_irq;
पूर्ण;

अटल काष्ठा chip_props ocelot_props = अणु
	.flags			= FLAGS_HAS_TRIGGER,
	.reg_off_sticky		= 0x10,
	.reg_off_ena		= 0x18,
	.reg_off_ena_clr	= 0x1c,
	.reg_off_ena_set	= 0x20,
	.reg_off_ident		= 0x38,
	.reg_off_trigger	= 0x5c,
	.n_irq			= 24,
पूर्ण;

अटल काष्ठा chip_props serval_props = अणु
	.flags			= FLAGS_HAS_TRIGGER,
	.reg_off_sticky		= 0xc,
	.reg_off_ena		= 0x14,
	.reg_off_ena_clr	= 0x18,
	.reg_off_ena_set	= 0x1c,
	.reg_off_ident		= 0x20,
	.reg_off_trigger	= 0x4,
	.n_irq			= 24,
पूर्ण;

अटल काष्ठा chip_props luton_props = अणु
	.flags			= FLAGS_NEED_INIT_ENABLE,
	.reg_off_sticky		= 0,
	.reg_off_ena		= 0x4,
	.reg_off_ena_clr	= 0x8,
	.reg_off_ena_set	= 0xc,
	.reg_off_ident		= 0x18,
	.reg_off_ena_irq0	= 0x14,
	.n_irq			= 28,
पूर्ण;

अटल काष्ठा chip_props jaguar2_props = अणु
	.flags			= FLAGS_HAS_TRIGGER,
	.reg_off_sticky		= 0x10,
	.reg_off_ena		= 0x18,
	.reg_off_ena_clr	= 0x1c,
	.reg_off_ena_set	= 0x20,
	.reg_off_ident		= 0x38,
	.reg_off_trigger	= 0x5c,
	.n_irq			= 29,
पूर्ण;

अटल व्योम ocelot_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(data);
	काष्ठा irq_करोमुख्य *d = data->करोमुख्य;
	काष्ठा chip_props *p = d->host_data;
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(data);
	अचिन्हित पूर्णांक mask = data->mask;
	u32 val;

	irq_gc_lock(gc);
	val = irq_reg_पढ़ोl(gc, ICPU_CFG_INTR_INTR_TRIGGER(p, 0)) |
		irq_reg_पढ़ोl(gc, ICPU_CFG_INTR_INTR_TRIGGER(p, 1));
	अगर (!(val & mask))
		irq_reg_ग_लिखोl(gc, mask, p->reg_off_sticky);

	*ct->mask_cache &= ~mask;
	irq_reg_ग_लिखोl(gc, mask, p->reg_off_ena_set);
	irq_gc_unlock(gc);
पूर्ण

अटल व्योम ocelot_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा irq_करोमुख्य *d = irq_desc_get_handler_data(desc);
	काष्ठा chip_props *p = d->host_data;
	काष्ठा irq_chip_generic *gc = irq_get_करोमुख्य_generic_chip(d, 0);
	u32 reg = irq_reg_पढ़ोl(gc, ICPU_CFG_INTR_DST_INTR_IDENT(p, 0));

	chained_irq_enter(chip, desc);

	जबतक (reg) अणु
		u32 hwirq = __fls(reg);

		generic_handle_irq(irq_find_mapping(d, hwirq));
		reg &= ~(BIT(hwirq));
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक __init vcoreiii_irq_init(काष्ठा device_node *node,
				    काष्ठा device_node *parent,
				    काष्ठा chip_props *p)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा irq_chip_generic *gc;
	पूर्णांक parent_irq, ret;

	parent_irq = irq_of_parse_and_map(node, 0);
	अगर (!parent_irq)
		वापस -EINVAL;

	करोमुख्य = irq_करोमुख्य_add_linear(node, p->n_irq,
				       &irq_generic_chip_ops, शून्य);
	अगर (!करोमुख्य) अणु
		pr_err("%pOFn: unable to add irq domain\n", node);
		वापस -ENOMEM;
	पूर्ण

	ret = irq_alloc_करोमुख्य_generic_chips(करोमुख्य, p->n_irq, 1,
					     "icpu", handle_level_irq,
					     0, 0, 0);
	अगर (ret) अणु
		pr_err("%pOFn: unable to alloc irq domain gc\n", node);
		जाओ err_करोमुख्य_हटाओ;
	पूर्ण

	gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);
	gc->reg_base = of_iomap(node, 0);
	अगर (!gc->reg_base) अणु
		pr_err("%pOFn: unable to map resource\n", node);
		ret = -ENOMEM;
		जाओ err_gc_मुक्त;
	पूर्ण

	gc->chip_types[0].chip.irq_ack = irq_gc_ack_set_bit;
	gc->chip_types[0].regs.ack = p->reg_off_sticky;
	अगर (p->flags & FLAGS_HAS_TRIGGER) अणु
		gc->chip_types[0].regs.mask = p->reg_off_ena_clr;
		gc->chip_types[0].chip.irq_unmask = ocelot_irq_unmask;
		gc->chip_types[0].chip.irq_mask = irq_gc_mask_set_bit;
	पूर्ण अन्यथा अणु
		gc->chip_types[0].regs.enable = p->reg_off_ena_set;
		gc->chip_types[0].regs.disable = p->reg_off_ena_clr;
		gc->chip_types[0].chip.irq_mask = irq_gc_mask_disable_reg;
		gc->chip_types[0].chip.irq_unmask = irq_gc_unmask_enable_reg;
	पूर्ण

	/* Mask and ack all पूर्णांकerrupts */
	irq_reg_ग_लिखोl(gc, 0, p->reg_off_ena);
	irq_reg_ग_लिखोl(gc, 0xffffffff, p->reg_off_sticky);

	/* Overall init */
	अगर (p->flags & FLAGS_NEED_INIT_ENABLE)
		irq_reg_ग_लिखोl(gc, BIT(0), p->reg_off_ena_irq0);

	करोमुख्य->host_data = p;
	irq_set_chained_handler_and_data(parent_irq, ocelot_irq_handler,
					 करोमुख्य);

	वापस 0;

err_gc_मुक्त:
	irq_मुक्त_generic_chip(gc);

err_करोमुख्य_हटाओ:
	irq_करोमुख्य_हटाओ(करोमुख्य);

	वापस ret;
पूर्ण

अटल पूर्णांक __init ocelot_irq_init(काष्ठा device_node *node,
				  काष्ठा device_node *parent)
अणु
	वापस vcoreiii_irq_init(node, parent, &ocelot_props);
पूर्ण

IRQCHIP_DECLARE(ocelot_icpu, "mscc,ocelot-icpu-intr", ocelot_irq_init);

अटल पूर्णांक __init serval_irq_init(काष्ठा device_node *node,
				  काष्ठा device_node *parent)
अणु
	वापस vcoreiii_irq_init(node, parent, &serval_props);
पूर्ण

IRQCHIP_DECLARE(serval_icpu, "mscc,serval-icpu-intr", serval_irq_init);

अटल पूर्णांक __init luton_irq_init(काष्ठा device_node *node,
				 काष्ठा device_node *parent)
अणु
	वापस vcoreiii_irq_init(node, parent, &luton_props);
पूर्ण

IRQCHIP_DECLARE(luton_icpu, "mscc,luton-icpu-intr", luton_irq_init);

अटल पूर्णांक __init jaguar2_irq_init(काष्ठा device_node *node,
				   काष्ठा device_node *parent)
अणु
	वापस vcoreiii_irq_init(node, parent, &jaguar2_props);
पूर्ण

IRQCHIP_DECLARE(jaguar2_icpu, "mscc,jaguar2-icpu-intr", jaguar2_irq_init);
