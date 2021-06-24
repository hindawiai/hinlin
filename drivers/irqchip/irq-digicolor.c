<शैली गुरु>
/*
 * Conexant Digicolor SoCs IRQ chip driver
 *
 * Author: Baruch Siach <baruch@tkos.co.il>
 *
 * Copyright (C) 2014 Paraकरोx Innovation Ltd.
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
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश <यंत्र/exception.h>

#घोषणा UC_IRQ_CONTROL		0x04

#घोषणा IC_FLAG_CLEAR_LO	0x00
#घोषणा IC_FLAG_CLEAR_XLO	0x04
#घोषणा IC_INT0ENABLE_LO	0x10
#घोषणा IC_INT0ENABLE_XLO	0x14
#घोषणा IC_INT0STATUS_LO	0x18
#घोषणा IC_INT0STATUS_XLO	0x1c

अटल काष्ठा irq_करोमुख्य *digicolor_irq_करोमुख्य;

अटल व्योम __exception_irq_entry digicolor_handle_irq(काष्ठा pt_regs *regs)
अणु
	काष्ठा irq_करोमुख्य_chip_generic *dgc = digicolor_irq_करोमुख्य->gc;
	काष्ठा irq_chip_generic *gc = dgc->gc[0];
	u32 status, hwirq;

	करो अणु
		status = irq_reg_पढ़ोl(gc, IC_INT0STATUS_LO);
		अगर (status) अणु
			hwirq = ffs(status) - 1;
		पूर्ण अन्यथा अणु
			status = irq_reg_पढ़ोl(gc, IC_INT0STATUS_XLO);
			अगर (status)
				hwirq = ffs(status) - 1 + 32;
			अन्यथा
				वापस;
		पूर्ण

		handle_करोमुख्य_irq(digicolor_irq_करोमुख्य, hwirq, regs);
	पूर्ण जबतक (1);
पूर्ण

अटल व्योम __init digicolor_set_gc(व्योम __iomem *reg_base, अचिन्हित irq_base,
				    अचिन्हित en_reg, अचिन्हित ack_reg)
अणु
	काष्ठा irq_chip_generic *gc;

	gc = irq_get_करोमुख्य_generic_chip(digicolor_irq_करोमुख्य, irq_base);
	gc->reg_base = reg_base;
	gc->chip_types[0].regs.ack = ack_reg;
	gc->chip_types[0].regs.mask = en_reg;
	gc->chip_types[0].chip.irq_ack = irq_gc_ack_set_bit;
	gc->chip_types[0].chip.irq_mask = irq_gc_mask_clr_bit;
	gc->chip_types[0].chip.irq_unmask = irq_gc_mask_set_bit;
पूर्ण

अटल पूर्णांक __init digicolor_of_init(काष्ठा device_node *node,
				काष्ठा device_node *parent)
अणु
	व्योम __iomem *reg_base;
	अचिन्हित पूर्णांक clr = IRQ_NOREQUEST | IRQ_NOPROBE | IRQ_NOAUTOEN;
	काष्ठा regmap *ucregs;
	पूर्णांक ret;

	reg_base = of_iomap(node, 0);
	अगर (!reg_base) अणु
		pr_err("%pOF: unable to map IC registers\n", node);
		वापस -ENXIO;
	पूर्ण

	/* disable all पूर्णांकerrupts */
	ग_लिखोl(0, reg_base + IC_INT0ENABLE_LO);
	ग_लिखोl(0, reg_base + IC_INT0ENABLE_XLO);

	ucregs = syscon_regmap_lookup_by_phandle(node, "syscon");
	अगर (IS_ERR(ucregs)) अणु
		pr_err("%pOF: unable to map UC registers\n", node);
		वापस PTR_ERR(ucregs);
	पूर्ण
	/* channel 1, regular IRQs */
	regmap_ग_लिखो(ucregs, UC_IRQ_CONTROL, 1);

	digicolor_irq_करोमुख्य =
		irq_करोमुख्य_add_linear(node, 64, &irq_generic_chip_ops, शून्य);
	अगर (!digicolor_irq_करोमुख्य) अणु
		pr_err("%pOF: unable to create IRQ domain\n", node);
		वापस -ENOMEM;
	पूर्ण

	ret = irq_alloc_करोमुख्य_generic_chips(digicolor_irq_करोमुख्य, 32, 1,
					     "digicolor_irq", handle_level_irq,
					     clr, 0, 0);
	अगर (ret) अणु
		pr_err("%pOF: unable to allocate IRQ gc\n", node);
		वापस ret;
	पूर्ण

	digicolor_set_gc(reg_base, 0, IC_INT0ENABLE_LO, IC_FLAG_CLEAR_LO);
	digicolor_set_gc(reg_base, 32, IC_INT0ENABLE_XLO, IC_FLAG_CLEAR_XLO);

	set_handle_irq(digicolor_handle_irq);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(conexant_digicolor_ic, "cnxt,cx92755-ic", digicolor_of_init);
