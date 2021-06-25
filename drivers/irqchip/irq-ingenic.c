<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2009-2010, Lars-Peter Clausen <lars@metafoo.de>
 *  Ingenic XBurst platक्रमm IRQ support
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/समयx.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/पन.स>

काष्ठा ingenic_पूर्णांकc_data अणु
	व्योम __iomem *base;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	अचिन्हित num_chips;
पूर्ण;

#घोषणा JZ_REG_INTC_STATUS	0x00
#घोषणा JZ_REG_INTC_MASK	0x04
#घोषणा JZ_REG_INTC_SET_MASK	0x08
#घोषणा JZ_REG_INTC_CLEAR_MASK	0x0c
#घोषणा JZ_REG_INTC_PENDING	0x10
#घोषणा CHIP_SIZE		0x20

अटल irqवापस_t पूर्णांकc_cascade(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ingenic_पूर्णांकc_data *पूर्णांकc = irq_get_handler_data(irq);
	काष्ठा irq_करोमुख्य *करोमुख्य = पूर्णांकc->करोमुख्य;
	काष्ठा irq_chip_generic *gc;
	uपूर्णांक32_t pending;
	अचिन्हित i;

	क्रम (i = 0; i < पूर्णांकc->num_chips; i++) अणु
		gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, i * 32);

		pending = irq_reg_पढ़ोl(gc, JZ_REG_INTC_PENDING);
		अगर (!pending)
			जारी;

		जबतक (pending) अणु
			पूर्णांक bit = __fls(pending);

			irq = irq_linear_revmap(करोमुख्य, bit + (i * 32));
			generic_handle_irq(irq);
			pending &= ~BIT(bit);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init ingenic_पूर्णांकc_of_init(काष्ठा device_node *node,
				       अचिन्हित num_chips)
अणु
	काष्ठा ingenic_पूर्णांकc_data *पूर्णांकc;
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक parent_irq, err = 0;
	अचिन्हित i;

	पूर्णांकc = kzalloc(माप(*पूर्णांकc), GFP_KERNEL);
	अगर (!पूर्णांकc) अणु
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण

	parent_irq = irq_of_parse_and_map(node, 0);
	अगर (!parent_irq) अणु
		err = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	err = irq_set_handler_data(parent_irq, पूर्णांकc);
	अगर (err)
		जाओ out_unmap_irq;

	पूर्णांकc->num_chips = num_chips;
	पूर्णांकc->base = of_iomap(node, 0);
	अगर (!पूर्णांकc->base) अणु
		err = -ENODEV;
		जाओ out_unmap_irq;
	पूर्ण

	करोमुख्य = irq_करोमुख्य_add_linear(node, num_chips * 32,
				       &irq_generic_chip_ops, शून्य);
	अगर (!करोमुख्य) अणु
		err = -ENOMEM;
		जाओ out_unmap_base;
	पूर्ण

	पूर्णांकc->करोमुख्य = करोमुख्य;

	err = irq_alloc_करोमुख्य_generic_chips(करोमुख्य, 32, 1, "INTC",
					     handle_level_irq, 0,
					     IRQ_NOPROBE | IRQ_LEVEL, 0);
	अगर (err)
		जाओ out_करोमुख्य_हटाओ;

	क्रम (i = 0; i < num_chips; i++) अणु
		gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, i * 32);

		gc->wake_enabled = IRQ_MSK(32);
		gc->reg_base = पूर्णांकc->base + (i * CHIP_SIZE);

		ct = gc->chip_types;
		ct->regs.enable = JZ_REG_INTC_CLEAR_MASK;
		ct->regs.disable = JZ_REG_INTC_SET_MASK;
		ct->chip.irq_unmask = irq_gc_unmask_enable_reg;
		ct->chip.irq_mask = irq_gc_mask_disable_reg;
		ct->chip.irq_mask_ack = irq_gc_mask_disable_reg;
		ct->chip.irq_set_wake = irq_gc_set_wake;
		ct->chip.flags = IRQCHIP_MASK_ON_SUSPEND;

		/* Mask all irqs */
		irq_reg_ग_लिखोl(gc, IRQ_MSK(32), JZ_REG_INTC_SET_MASK);
	पूर्ण

	अगर (request_irq(parent_irq, पूर्णांकc_cascade, IRQF_NO_SUSPEND,
			"SoC intc cascade interrupt", शून्य))
		pr_err("Failed to register SoC intc cascade interrupt\n");
	वापस 0;

out_करोमुख्य_हटाओ:
	irq_करोमुख्य_हटाओ(करोमुख्य);
out_unmap_base:
	iounmap(पूर्णांकc->base);
out_unmap_irq:
	irq_dispose_mapping(parent_irq);
out_मुक्त:
	kमुक्त(पूर्णांकc);
out_err:
	वापस err;
पूर्ण

अटल पूर्णांक __init पूर्णांकc_1chip_of_init(काष्ठा device_node *node,
				     काष्ठा device_node *parent)
अणु
	वापस ingenic_पूर्णांकc_of_init(node, 1);
पूर्ण
IRQCHIP_DECLARE(jz4740_पूर्णांकc, "ingenic,jz4740-intc", पूर्णांकc_1chip_of_init);
IRQCHIP_DECLARE(jz4725b_पूर्णांकc, "ingenic,jz4725b-intc", पूर्णांकc_1chip_of_init);

अटल पूर्णांक __init पूर्णांकc_2chip_of_init(काष्ठा device_node *node,
	काष्ठा device_node *parent)
अणु
	वापस ingenic_पूर्णांकc_of_init(node, 2);
पूर्ण
IRQCHIP_DECLARE(jz4760_पूर्णांकc, "ingenic,jz4760-intc", पूर्णांकc_2chip_of_init);
IRQCHIP_DECLARE(jz4770_पूर्णांकc, "ingenic,jz4770-intc", पूर्णांकc_2chip_of_init);
IRQCHIP_DECLARE(jz4775_पूर्णांकc, "ingenic,jz4775-intc", पूर्णांकc_2chip_of_init);
IRQCHIP_DECLARE(jz4780_पूर्णांकc, "ingenic,jz4780-intc", पूर्णांकc_2chip_of_init);
