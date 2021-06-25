<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2019, Jiaxun Yang <jiaxun.yang@flygoat.com>
 *  Loongson-1 platक्रमm IRQ support
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip/chained_irq.h>

#घोषणा LS_REG_INTC_STATUS	0x00
#घोषणा LS_REG_INTC_EN	0x04
#घोषणा LS_REG_INTC_SET	0x08
#घोषणा LS_REG_INTC_CLR	0x0c
#घोषणा LS_REG_INTC_POL	0x10
#घोषणा LS_REG_INTC_EDGE	0x14

/**
 * काष्ठा ls1x_पूर्णांकc_priv - निजी ls1x-पूर्णांकc data.
 * @करोमुख्य:		IRQ करोमुख्य.
 * @पूर्णांकc_base:	IO Base of पूर्णांकc रेजिस्टरs.
 */

काष्ठा ls1x_पूर्णांकc_priv अणु
	काष्ठा irq_करोमुख्य	*करोमुख्य;
	व्योम __iomem		*पूर्णांकc_base;
पूर्ण;


अटल व्योम ls1x_chained_handle_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा ls1x_पूर्णांकc_priv *priv = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	u32 pending;

	chained_irq_enter(chip, desc);
	pending = पढ़ोl(priv->पूर्णांकc_base + LS_REG_INTC_STATUS) &
			पढ़ोl(priv->पूर्णांकc_base + LS_REG_INTC_EN);

	अगर (!pending)
		spurious_पूर्णांकerrupt();

	जबतक (pending) अणु
		पूर्णांक bit = __ffs(pending);

		generic_handle_irq(irq_find_mapping(priv->करोमुख्य, bit));
		pending &= ~BIT(bit);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम ls_पूर्णांकc_set_bit(काष्ठा irq_chip_generic *gc,
							अचिन्हित पूर्णांक offset,
							u32 mask, bool set)
अणु
	अगर (set)
		ग_लिखोl(पढ़ोl(gc->reg_base + offset) | mask,
		gc->reg_base + offset);
	अन्यथा
		ग_लिखोl(पढ़ोl(gc->reg_base + offset) & ~mask,
		gc->reg_base + offset);
पूर्ण

अटल पूर्णांक ls_पूर्णांकc_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(data);
	u32 mask = data->mask;

	चयन (type) अणु
	हाल IRQ_TYPE_LEVEL_HIGH:
		ls_पूर्णांकc_set_bit(gc, LS_REG_INTC_EDGE, mask, false);
		ls_पूर्णांकc_set_bit(gc, LS_REG_INTC_POL, mask, true);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		ls_पूर्णांकc_set_bit(gc, LS_REG_INTC_EDGE, mask, false);
		ls_पूर्णांकc_set_bit(gc, LS_REG_INTC_POL, mask, false);
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		ls_पूर्णांकc_set_bit(gc, LS_REG_INTC_EDGE, mask, true);
		ls_पूर्णांकc_set_bit(gc, LS_REG_INTC_POL, mask, true);
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		ls_पूर्णांकc_set_bit(gc, LS_REG_INTC_EDGE, mask, true);
		ls_पूर्णांकc_set_bit(gc, LS_REG_INTC_POL, mask, false);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	irqd_set_trigger_type(data, type);
	वापस irq_setup_alt_chip(data, type);
पूर्ण


अटल पूर्णांक __init ls1x_पूर्णांकc_of_init(काष्ठा device_node *node,
				       काष्ठा device_node *parent)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;
	काष्ठा ls1x_पूर्णांकc_priv *priv;
	पूर्णांक parent_irq, err = 0;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->पूर्णांकc_base = of_iomap(node, 0);
	अगर (!priv->पूर्णांकc_base) अणु
		err = -ENODEV;
		जाओ out_मुक्त_priv;
	पूर्ण

	parent_irq = irq_of_parse_and_map(node, 0);
	अगर (!parent_irq) अणु
		pr_err("ls1x-irq: unable to get parent irq\n");
		err =  -ENODEV;
		जाओ out_iounmap;
	पूर्ण

	/* Set up an IRQ करोमुख्य */
	priv->करोमुख्य = irq_करोमुख्य_add_linear(node, 32, &irq_generic_chip_ops,
					     शून्य);
	अगर (!priv->करोमुख्य) अणु
		pr_err("ls1x-irq: cannot add IRQ domain\n");
		err = -ENOMEM;
		जाओ out_iounmap;
	पूर्ण

	err = irq_alloc_करोमुख्य_generic_chips(priv->करोमुख्य, 32, 2,
		node->full_name, handle_level_irq,
		IRQ_NOREQUEST | IRQ_NOPROBE | IRQ_NOAUTOEN, 0,
		IRQ_GC_INIT_MASK_CACHE);
	अगर (err) अणु
		pr_err("ls1x-irq: unable to register IRQ domain\n");
		जाओ out_मुक्त_करोमुख्य;
	पूर्ण

	/* Mask all irqs */
	ग_लिखोl(0x0, priv->पूर्णांकc_base + LS_REG_INTC_EN);

	/* Ack all irqs */
	ग_लिखोl(0xffffffff, priv->पूर्णांकc_base + LS_REG_INTC_CLR);

	/* Set all irqs to high level triggered */
	ग_लिखोl(0xffffffff, priv->पूर्णांकc_base + LS_REG_INTC_POL);

	gc = irq_get_करोमुख्य_generic_chip(priv->करोमुख्य, 0);

	gc->reg_base = priv->पूर्णांकc_base;

	ct = gc->chip_types;
	ct[0].type = IRQ_TYPE_LEVEL_MASK;
	ct[0].regs.mask = LS_REG_INTC_EN;
	ct[0].regs.ack = LS_REG_INTC_CLR;
	ct[0].chip.irq_unmask = irq_gc_mask_set_bit;
	ct[0].chip.irq_mask = irq_gc_mask_clr_bit;
	ct[0].chip.irq_ack = irq_gc_ack_set_bit;
	ct[0].chip.irq_set_type = ls_पूर्णांकc_set_type;
	ct[0].handler = handle_level_irq;

	ct[1].type = IRQ_TYPE_EDGE_BOTH;
	ct[1].regs.mask = LS_REG_INTC_EN;
	ct[1].regs.ack = LS_REG_INTC_CLR;
	ct[1].chip.irq_unmask = irq_gc_mask_set_bit;
	ct[1].chip.irq_mask = irq_gc_mask_clr_bit;
	ct[1].chip.irq_ack = irq_gc_ack_set_bit;
	ct[1].chip.irq_set_type = ls_पूर्णांकc_set_type;
	ct[1].handler = handle_edge_irq;

	irq_set_chained_handler_and_data(parent_irq,
		ls1x_chained_handle_irq, priv);

	वापस 0;

out_मुक्त_करोमुख्य:
	irq_करोमुख्य_हटाओ(priv->करोमुख्य);
out_iounmap:
	iounmap(priv->पूर्णांकc_base);
out_मुक्त_priv:
	kमुक्त(priv);

	वापस err;
पूर्ण

IRQCHIP_DECLARE(ls1x_पूर्णांकc, "loongson,ls1x-intc", ls1x_पूर्णांकc_of_init);
