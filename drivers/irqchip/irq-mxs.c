<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2009-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright (C) 2014 Oleksij Rempel <linux@rempel-privat.de>
 *	Add Alphascale ASM9260 support.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sपंचांगp_device.h>
#समावेश <यंत्र/exception.h>

#समावेश "alphascale_asm9260-icoll.h"

/*
 * this device provide 4 offsets क्रम each रेजिस्टर:
 * 0x0 - plain पढ़ो ग_लिखो mode
 * 0x4 - set mode, OR logic.
 * 0x8 - clr mode, XOR logic.
 * 0xc - togle mode.
 */
#घोषणा SET_REG 4
#घोषणा CLR_REG 8

#घोषणा HW_ICOLL_VECTOR				0x0000
#घोषणा HW_ICOLL_LEVELACK			0x0010
#घोषणा HW_ICOLL_CTRL				0x0020
#घोषणा HW_ICOLL_STAT_OFFSET			0x0070
#घोषणा HW_ICOLL_INTERRUPT0			0x0120
#घोषणा HW_ICOLL_INTERRUPTn(n)			((n) * 0x10)
#घोषणा BM_ICOLL_INTR_ENABLE			BIT(2)
#घोषणा BV_ICOLL_LEVELACK_IRQLEVELACK__LEVEL0	0x1

#घोषणा ICOLL_NUM_IRQS		128

क्रमागत icoll_type अणु
	ICOLL,
	ASM9260_ICOLL,
पूर्ण;

काष्ठा icoll_priv अणु
	व्योम __iomem *vector;
	व्योम __iomem *levelack;
	व्योम __iomem *ctrl;
	व्योम __iomem *stat;
	व्योम __iomem *पूर्णांकr;
	व्योम __iomem *clear;
	क्रमागत icoll_type type;
पूर्ण;

अटल काष्ठा icoll_priv icoll_priv;
अटल काष्ठा irq_करोमुख्य *icoll_करोमुख्य;

/* calculate bit offset depending on number of पूर्णांकerrupt per रेजिस्टर */
अटल u32 icoll_पूर्णांकr_bitshअगरt(काष्ठा irq_data *d, u32 bit)
अणु
	/*
	 * mask lower part of hwirq to convert it
	 * in 0, 1, 2 or 3 and then multiply it by 8 (or shअगरt by 3)
	 */
	वापस bit << ((d->hwirq & 3) << 3);
पूर्ण

/* calculate mem offset depending on number of पूर्णांकerrupt per रेजिस्टर */
अटल व्योम __iomem *icoll_पूर्णांकr_reg(काष्ठा irq_data *d)
अणु
	/* offset = hwirq / पूर्णांकr_per_reg * 0x10 */
	वापस icoll_priv.पूर्णांकr + ((d->hwirq >> 2) * 0x10);
पूर्ण

अटल व्योम icoll_ack_irq(काष्ठा irq_data *d)
अणु
	/*
	 * The Interrupt Collector is able to prioritize irqs.
	 * Currently only level 0 is used. So acking can use
	 * BV_ICOLL_LEVELACK_IRQLEVELACK__LEVEL0 unconditionally.
	 */
	__raw_ग_लिखोl(BV_ICOLL_LEVELACK_IRQLEVELACK__LEVEL0,
			icoll_priv.levelack);
पूर्ण

अटल व्योम icoll_mask_irq(काष्ठा irq_data *d)
अणु
	__raw_ग_लिखोl(BM_ICOLL_INTR_ENABLE,
			icoll_priv.पूर्णांकr + CLR_REG + HW_ICOLL_INTERRUPTn(d->hwirq));
पूर्ण

अटल व्योम icoll_unmask_irq(काष्ठा irq_data *d)
अणु
	__raw_ग_लिखोl(BM_ICOLL_INTR_ENABLE,
			icoll_priv.पूर्णांकr + SET_REG + HW_ICOLL_INTERRUPTn(d->hwirq));
पूर्ण

अटल व्योम यंत्र9260_mask_irq(काष्ठा irq_data *d)
अणु
	__raw_ग_लिखोl(icoll_पूर्णांकr_bitshअगरt(d, BM_ICOLL_INTR_ENABLE),
			icoll_पूर्णांकr_reg(d) + CLR_REG);
पूर्ण

अटल व्योम यंत्र9260_unmask_irq(काष्ठा irq_data *d)
अणु
	__raw_ग_लिखोl(ASM9260_BM_CLEAR_BIT(d->hwirq),
		     icoll_priv.clear +
		     ASM9260_HW_ICOLL_CLEARn(d->hwirq));

	__raw_ग_लिखोl(icoll_पूर्णांकr_bitshअगरt(d, BM_ICOLL_INTR_ENABLE),
			icoll_पूर्णांकr_reg(d) + SET_REG);
पूर्ण

अटल काष्ठा irq_chip mxs_icoll_chip = अणु
	.irq_ack = icoll_ack_irq,
	.irq_mask = icoll_mask_irq,
	.irq_unmask = icoll_unmask_irq,
	.flags = IRQCHIP_MASK_ON_SUSPEND |
		 IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल काष्ठा irq_chip यंत्र9260_icoll_chip = अणु
	.irq_ack = icoll_ack_irq,
	.irq_mask = यंत्र9260_mask_irq,
	.irq_unmask = यंत्र9260_unmask_irq,
	.flags = IRQCHIP_MASK_ON_SUSPEND |
		 IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

यंत्रlinkage व्योम __exception_irq_entry icoll_handle_irq(काष्ठा pt_regs *regs)
अणु
	u32 irqnr;

	irqnr = __raw_पढ़ोl(icoll_priv.stat);
	__raw_ग_लिखोl(irqnr, icoll_priv.vector);
	handle_करोमुख्य_irq(icoll_करोमुख्य, irqnr, regs);
पूर्ण

अटल पूर्णांक icoll_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
				irq_hw_number_t hw)
अणु
	काष्ठा irq_chip *chip;

	अगर (icoll_priv.type == ICOLL)
		chip = &mxs_icoll_chip;
	अन्यथा
		chip = &यंत्र9260_icoll_chip;

	irq_set_chip_and_handler(virq, chip, handle_level_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops icoll_irq_करोमुख्य_ops = अणु
	.map = icoll_irq_करोमुख्य_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल व्योम __init icoll_add_करोमुख्य(काष्ठा device_node *np,
			  पूर्णांक num)
अणु
	icoll_करोमुख्य = irq_करोमुख्य_add_linear(np, num,
					     &icoll_irq_करोमुख्य_ops, शून्य);

	अगर (!icoll_करोमुख्य)
		panic("%pOF: unable to create irq domain", np);
पूर्ण

अटल व्योम __iomem * __init icoll_init_iobase(काष्ठा device_node *np)
अणु
	व्योम __iomem *icoll_base;

	icoll_base = of_io_request_and_map(np, 0, np->name);
	अगर (IS_ERR(icoll_base))
		panic("%pOF: unable to map resource", np);
	वापस icoll_base;
पूर्ण

अटल पूर्णांक __init icoll_of_init(काष्ठा device_node *np,
			  काष्ठा device_node *पूर्णांकerrupt_parent)
अणु
	व्योम __iomem *icoll_base;

	icoll_priv.type = ICOLL;

	icoll_base		= icoll_init_iobase(np);
	icoll_priv.vector	= icoll_base + HW_ICOLL_VECTOR;
	icoll_priv.levelack	= icoll_base + HW_ICOLL_LEVELACK;
	icoll_priv.ctrl		= icoll_base + HW_ICOLL_CTRL;
	icoll_priv.stat		= icoll_base + HW_ICOLL_STAT_OFFSET;
	icoll_priv.पूर्णांकr		= icoll_base + HW_ICOLL_INTERRUPT0;
	icoll_priv.clear	= शून्य;

	/*
	 * Interrupt Collector reset, which initializes the priority
	 * क्रम each irq to level 0.
	 */
	sपंचांगp_reset_block(icoll_priv.ctrl);

	icoll_add_करोमुख्य(np, ICOLL_NUM_IRQS);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(mxs, "fsl,icoll", icoll_of_init);

अटल पूर्णांक __init यंत्र9260_of_init(काष्ठा device_node *np,
			  काष्ठा device_node *पूर्णांकerrupt_parent)
अणु
	व्योम __iomem *icoll_base;
	पूर्णांक i;

	icoll_priv.type = ASM9260_ICOLL;

	icoll_base = icoll_init_iobase(np);
	icoll_priv.vector	= icoll_base + ASM9260_HW_ICOLL_VECTOR;
	icoll_priv.levelack	= icoll_base + ASM9260_HW_ICOLL_LEVELACK;
	icoll_priv.ctrl		= icoll_base + ASM9260_HW_ICOLL_CTRL;
	icoll_priv.stat		= icoll_base + ASM9260_HW_ICOLL_STAT_OFFSET;
	icoll_priv.पूर्णांकr		= icoll_base + ASM9260_HW_ICOLL_INTERRUPT0;
	icoll_priv.clear	= icoll_base + ASM9260_HW_ICOLL_CLEAR0;

	ग_लिखोl_relaxed(ASM9260_BM_CTRL_IRQ_ENABLE,
			icoll_priv.ctrl);
	/*
	 * ASM9260 करोn't provide reset bit. So, we need to set level 0
	 * manually.
	 */
	क्रम (i = 0; i < 16 * 0x10; i += 0x10)
		ग_लिखोl(0, icoll_priv.पूर्णांकr + i);

	icoll_add_करोमुख्य(np, ASM9260_NUM_IRQS);
	set_handle_irq(icoll_handle_irq);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(यंत्र9260, "alphascale,asm9260-icoll", यंत्र9260_of_init);
