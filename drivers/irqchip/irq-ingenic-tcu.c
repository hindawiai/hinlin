<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * JZ47xx SoCs TCU IRQ driver
 * Copyright (C) 2019 Paul Cercueil <paul@crapouillou.net>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/mfd/ingenic-tcu.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/regmap.h>

काष्ठा ingenic_tcu अणु
	काष्ठा regmap *map;
	काष्ठा clk *clk;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	अचिन्हित पूर्णांक nb_parent_irqs;
	u32 parent_irqs[3];
पूर्ण;

अटल व्योम ingenic_tcu_पूर्णांकc_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *irq_chip = irq_data_get_irq_chip(&desc->irq_data);
	काष्ठा irq_करोमुख्य *करोमुख्य = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip_generic *gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);
	काष्ठा regmap *map = gc->निजी;
	uपूर्णांक32_t irq_reg, irq_mask;
	अचिन्हित पूर्णांक i;

	regmap_पढ़ो(map, TCU_REG_TFR, &irq_reg);
	regmap_पढ़ो(map, TCU_REG_TMR, &irq_mask);

	chained_irq_enter(irq_chip, desc);

	irq_reg &= ~irq_mask;

	क्रम_each_set_bit(i, (अचिन्हित दीर्घ *)&irq_reg, 32)
		generic_handle_irq(irq_linear_revmap(करोमुख्य, i));

	chained_irq_निकास(irq_chip, desc);
पूर्ण

अटल व्योम ingenic_tcu_gc_unmask_enable_reg(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	काष्ठा regmap *map = gc->निजी;
	u32 mask = d->mask;

	irq_gc_lock(gc);
	regmap_ग_लिखो(map, ct->regs.ack, mask);
	regmap_ग_लिखो(map, ct->regs.enable, mask);
	*ct->mask_cache |= mask;
	irq_gc_unlock(gc);
पूर्ण

अटल व्योम ingenic_tcu_gc_mask_disable_reg(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	काष्ठा regmap *map = gc->निजी;
	u32 mask = d->mask;

	irq_gc_lock(gc);
	regmap_ग_लिखो(map, ct->regs.disable, mask);
	*ct->mask_cache &= ~mask;
	irq_gc_unlock(gc);
पूर्ण

अटल व्योम ingenic_tcu_gc_mask_disable_reg_and_ack(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	काष्ठा regmap *map = gc->निजी;
	u32 mask = d->mask;

	irq_gc_lock(gc);
	regmap_ग_लिखो(map, ct->regs.ack, mask);
	regmap_ग_लिखो(map, ct->regs.disable, mask);
	irq_gc_unlock(gc);
पूर्ण

अटल पूर्णांक __init ingenic_tcu_irq_init(काष्ठा device_node *np,
				       काष्ठा device_node *parent)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;
	काष्ठा ingenic_tcu *tcu;
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret, irqs;

	map = device_node_to_regmap(np);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	tcu = kzalloc(माप(*tcu), GFP_KERNEL);
	अगर (!tcu)
		वापस -ENOMEM;

	tcu->map = map;

	irqs = of_property_count_elems_of_size(np, "interrupts", माप(u32));
	अगर (irqs < 0 || irqs > ARRAY_SIZE(tcu->parent_irqs)) अणु
		pr_crit("%s: Invalid 'interrupts' property\n", __func__);
		ret = -EINVAL;
		जाओ err_मुक्त_tcu;
	पूर्ण

	tcu->nb_parent_irqs = irqs;

	tcu->करोमुख्य = irq_करोमुख्य_add_linear(np, 32, &irq_generic_chip_ops,
					    शून्य);
	अगर (!tcu->करोमुख्य) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_tcu;
	पूर्ण

	ret = irq_alloc_करोमुख्य_generic_chips(tcu->करोमुख्य, 32, 1, "TCU",
					     handle_level_irq, 0,
					     IRQ_NOPROBE | IRQ_LEVEL, 0);
	अगर (ret) अणु
		pr_crit("%s: Invalid 'interrupts' property\n", __func__);
		जाओ out_करोमुख्य_हटाओ;
	पूर्ण

	gc = irq_get_करोमुख्य_generic_chip(tcu->करोमुख्य, 0);
	ct = gc->chip_types;

	gc->wake_enabled = IRQ_MSK(32);
	gc->निजी = tcu->map;

	ct->regs.disable = TCU_REG_TMSR;
	ct->regs.enable = TCU_REG_TMCR;
	ct->regs.ack = TCU_REG_TFCR;
	ct->chip.irq_unmask = ingenic_tcu_gc_unmask_enable_reg;
	ct->chip.irq_mask = ingenic_tcu_gc_mask_disable_reg;
	ct->chip.irq_mask_ack = ingenic_tcu_gc_mask_disable_reg_and_ack;
	ct->chip.flags = IRQCHIP_MASK_ON_SUSPEND | IRQCHIP_SKIP_SET_WAKE;

	/* Mask all IRQs by शेष */
	regmap_ग_लिखो(tcu->map, TCU_REG_TMSR, IRQ_MSK(32));

	/*
	 * On JZ4740, समयr 0 and समयr 1 have their own पूर्णांकerrupt line;
	 * समयrs 2-7 share one पूर्णांकerrupt.
	 * On SoCs >= JZ4770, समयr 5 has its own पूर्णांकerrupt line;
	 * समयrs 0-4 and 6-7 share one single पूर्णांकerrupt.
	 *
	 * To keep things simple, we just रेजिस्टर the same handler to
	 * all parent पूर्णांकerrupts. The handler will properly detect which
	 * channel fired the पूर्णांकerrupt.
	 */
	क्रम (i = 0; i < irqs; i++) अणु
		tcu->parent_irqs[i] = irq_of_parse_and_map(np, i);
		अगर (!tcu->parent_irqs[i]) अणु
			ret = -EINVAL;
			जाओ out_unmap_irqs;
		पूर्ण

		irq_set_chained_handler_and_data(tcu->parent_irqs[i],
						 ingenic_tcu_पूर्णांकc_cascade,
						 tcu->करोमुख्य);
	पूर्ण

	वापस 0;

out_unmap_irqs:
	क्रम (; i > 0; i--)
		irq_dispose_mapping(tcu->parent_irqs[i - 1]);
out_करोमुख्य_हटाओ:
	irq_करोमुख्य_हटाओ(tcu->करोमुख्य);
err_मुक्त_tcu:
	kमुक्त(tcu);
	वापस ret;
पूर्ण
IRQCHIP_DECLARE(jz4740_tcu_irq, "ingenic,jz4740-tcu", ingenic_tcu_irq_init);
IRQCHIP_DECLARE(jz4725b_tcu_irq, "ingenic,jz4725b-tcu", ingenic_tcu_irq_init);
IRQCHIP_DECLARE(jz4760_tcu_irq, "ingenic,jz4760-tcu", ingenic_tcu_irq_init);
IRQCHIP_DECLARE(jz4770_tcu_irq, "ingenic,jz4770-tcu", ingenic_tcu_irq_init);
IRQCHIP_DECLARE(x1000_tcu_irq, "ingenic,x1000-tcu", ingenic_tcu_irq_init);
