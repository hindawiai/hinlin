<शैली गुरु>
/*
 * Allwinner A1X SoCs IRQ chip driver.
 *
 * Copyright (C) 2012 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 *
 * Based on code from
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Benn Huang <benn@allwinnertech.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश <यंत्र/exception.h>

#घोषणा SUN4I_IRQ_VECTOR_REG		0x00
#घोषणा SUN4I_IRQ_PROTECTION_REG	0x08
#घोषणा SUN4I_IRQ_NMI_CTRL_REG		0x0c
#घोषणा SUN4I_IRQ_PENDING_REG(x)	(0x10 + 0x4 * x)
#घोषणा SUN4I_IRQ_FIQ_PENDING_REG(x)	(0x20 + 0x4 * x)
#घोषणा SUN4I_IRQ_ENABLE_REG(data, x)	((data)->enable_reg_offset + 0x4 * x)
#घोषणा SUN4I_IRQ_MASK_REG(data, x)	((data)->mask_reg_offset + 0x4 * x)
#घोषणा SUN4I_IRQ_ENABLE_REG_OFFSET	0x40
#घोषणा SUN4I_IRQ_MASK_REG_OFFSET	0x50
#घोषणा SUNIV_IRQ_ENABLE_REG_OFFSET	0x20
#घोषणा SUNIV_IRQ_MASK_REG_OFFSET	0x30

काष्ठा sun4i_irq_chip_data अणु
	व्योम __iomem *irq_base;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	u32 enable_reg_offset;
	u32 mask_reg_offset;
पूर्ण;

अटल काष्ठा sun4i_irq_chip_data *irq_ic_data;

अटल व्योम __exception_irq_entry sun4i_handle_irq(काष्ठा pt_regs *regs);

अटल व्योम sun4i_irq_ack(काष्ठा irq_data *irqd)
अणु
	अचिन्हित पूर्णांक irq = irqd_to_hwirq(irqd);

	अगर (irq != 0)
		वापस; /* Only IRQ 0 / the ENMI needs to be acked */

	ग_लिखोl(BIT(0), irq_ic_data->irq_base + SUN4I_IRQ_PENDING_REG(0));
पूर्ण

अटल व्योम sun4i_irq_mask(काष्ठा irq_data *irqd)
अणु
	अचिन्हित पूर्णांक irq = irqd_to_hwirq(irqd);
	अचिन्हित पूर्णांक irq_off = irq % 32;
	पूर्णांक reg = irq / 32;
	u32 val;

	val = पढ़ोl(irq_ic_data->irq_base +
			SUN4I_IRQ_ENABLE_REG(irq_ic_data, reg));
	ग_लिखोl(val & ~(1 << irq_off),
	       irq_ic_data->irq_base + SUN4I_IRQ_ENABLE_REG(irq_ic_data, reg));
पूर्ण

अटल व्योम sun4i_irq_unmask(काष्ठा irq_data *irqd)
अणु
	अचिन्हित पूर्णांक irq = irqd_to_hwirq(irqd);
	अचिन्हित पूर्णांक irq_off = irq % 32;
	पूर्णांक reg = irq / 32;
	u32 val;

	val = पढ़ोl(irq_ic_data->irq_base +
			SUN4I_IRQ_ENABLE_REG(irq_ic_data, reg));
	ग_लिखोl(val | (1 << irq_off),
	       irq_ic_data->irq_base + SUN4I_IRQ_ENABLE_REG(irq_ic_data, reg));
पूर्ण

अटल काष्ठा irq_chip sun4i_irq_chip = अणु
	.name		= "sun4i_irq",
	.irq_eoi	= sun4i_irq_ack,
	.irq_mask	= sun4i_irq_mask,
	.irq_unmask	= sun4i_irq_unmask,
	.flags		= IRQCHIP_EOI_THREADED | IRQCHIP_EOI_IF_HANDLED,
पूर्ण;

अटल पूर्णांक sun4i_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
			 irq_hw_number_t hw)
अणु
	irq_set_chip_and_handler(virq, &sun4i_irq_chip, handle_fasteoi_irq);
	irq_set_probe(virq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops sun4i_irq_ops = अणु
	.map = sun4i_irq_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल पूर्णांक __init sun4i_of_init(काष्ठा device_node *node,
				काष्ठा device_node *parent)
अणु
	irq_ic_data->irq_base = of_iomap(node, 0);
	अगर (!irq_ic_data->irq_base)
		panic("%pOF: unable to map IC registers\n",
			node);

	/* Disable all पूर्णांकerrupts */
	ग_लिखोl(0, irq_ic_data->irq_base + SUN4I_IRQ_ENABLE_REG(irq_ic_data, 0));
	ग_लिखोl(0, irq_ic_data->irq_base + SUN4I_IRQ_ENABLE_REG(irq_ic_data, 1));
	ग_लिखोl(0, irq_ic_data->irq_base + SUN4I_IRQ_ENABLE_REG(irq_ic_data, 2));

	/* Unmask all the पूर्णांकerrupts, ENABLE_REG(x) is used क्रम masking */
	ग_लिखोl(0, irq_ic_data->irq_base + SUN4I_IRQ_MASK_REG(irq_ic_data, 0));
	ग_लिखोl(0, irq_ic_data->irq_base + SUN4I_IRQ_MASK_REG(irq_ic_data, 1));
	ग_लिखोl(0, irq_ic_data->irq_base + SUN4I_IRQ_MASK_REG(irq_ic_data, 2));

	/* Clear all the pending पूर्णांकerrupts */
	ग_लिखोl(0xffffffff, irq_ic_data->irq_base + SUN4I_IRQ_PENDING_REG(0));
	ग_लिखोl(0xffffffff, irq_ic_data->irq_base + SUN4I_IRQ_PENDING_REG(1));
	ग_लिखोl(0xffffffff, irq_ic_data->irq_base + SUN4I_IRQ_PENDING_REG(2));

	/* Enable protection mode */
	ग_लिखोl(0x01, irq_ic_data->irq_base + SUN4I_IRQ_PROTECTION_REG);

	/* Configure the बाह्यal पूर्णांकerrupt source type */
	ग_लिखोl(0x00, irq_ic_data->irq_base + SUN4I_IRQ_NMI_CTRL_REG);

	irq_ic_data->irq_करोमुख्य = irq_करोमुख्य_add_linear(node, 3 * 32,
						 &sun4i_irq_ops, शून्य);
	अगर (!irq_ic_data->irq_करोमुख्य)
		panic("%pOF: unable to create IRQ domain\n", node);

	set_handle_irq(sun4i_handle_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __init sun4i_ic_of_init(काष्ठा device_node *node,
				   काष्ठा device_node *parent)
अणु
	irq_ic_data = kzalloc(माप(काष्ठा sun4i_irq_chip_data), GFP_KERNEL);
	अगर (!irq_ic_data) अणु
		pr_err("kzalloc failed!\n");
		वापस -ENOMEM;
	पूर्ण

	irq_ic_data->enable_reg_offset = SUN4I_IRQ_ENABLE_REG_OFFSET;
	irq_ic_data->mask_reg_offset = SUN4I_IRQ_MASK_REG_OFFSET;

	वापस sun4i_of_init(node, parent);
पूर्ण

IRQCHIP_DECLARE(allwinner_sun4i_ic, "allwinner,sun4i-a10-ic", sun4i_ic_of_init);

अटल पूर्णांक __init suniv_ic_of_init(काष्ठा device_node *node,
				   काष्ठा device_node *parent)
अणु
	irq_ic_data = kzalloc(माप(काष्ठा sun4i_irq_chip_data), GFP_KERNEL);
	अगर (!irq_ic_data) अणु
		pr_err("kzalloc failed!\n");
		वापस -ENOMEM;
	पूर्ण

	irq_ic_data->enable_reg_offset = SUNIV_IRQ_ENABLE_REG_OFFSET;
	irq_ic_data->mask_reg_offset = SUNIV_IRQ_MASK_REG_OFFSET;

	वापस sun4i_of_init(node, parent);
पूर्ण

IRQCHIP_DECLARE(allwinner_sunvi_ic, "allwinner,suniv-f1c100s-ic",
		suniv_ic_of_init);

अटल व्योम __exception_irq_entry sun4i_handle_irq(काष्ठा pt_regs *regs)
अणु
	u32 hwirq;

	/*
	 * hwirq == 0 can mean one of 3 things:
	 * 1) no more irqs pending
	 * 2) irq 0 pending
	 * 3) spurious irq
	 * So अगर we immediately get a पढ़ोing of 0, check the irq-pending reg
	 * to dअगरferentiate between 2 and 3. We only करो this once to aव्योम
	 * the extra check in the common हाल of 1 happening after having
	 * पढ़ो the vector-reg once.
	 */
	hwirq = पढ़ोl(irq_ic_data->irq_base + SUN4I_IRQ_VECTOR_REG) >> 2;
	अगर (hwirq == 0 &&
		  !(पढ़ोl(irq_ic_data->irq_base + SUN4I_IRQ_PENDING_REG(0)) &
			  BIT(0)))
		वापस;

	करो अणु
		handle_करोमुख्य_irq(irq_ic_data->irq_करोमुख्य, hwirq, regs);
		hwirq = पढ़ोl(irq_ic_data->irq_base +
				SUN4I_IRQ_VECTOR_REG) >> 2;
	पूर्ण जबतक (hwirq != 0);
पूर्ण
