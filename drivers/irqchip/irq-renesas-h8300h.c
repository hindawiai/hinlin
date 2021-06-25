<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * H8/300H पूर्णांकerrupt controller driver
 *
 * Copyright 2015 Yoshinori Sato <ysato@users.sourceक्रमge.jp>
 */

#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <यंत्र/पन.स>

अटल स्थिर अक्षर ipr_bit[] = अणु
	 7,  6,  5,  5,
	 4,  4,  4,  4,  3,  3,  3,  3,
	 2,  2,  2,  2,  1,  1,  1,  1,
	 0,  0,  0,  0, 15, 15, 15, 15,
	14, 14, 14, 14, 13, 13, 13, 13,
	-1, -1, -1, -1, 11, 11, 11, 11,
	10, 10, 10, 10,  9,  9,  9,  9,
पूर्ण;

अटल व्योम __iomem *पूर्णांकc_baseaddr;

#घोषणा IPR (पूर्णांकc_baseaddr + 6)

अटल व्योम h8300h_disable_irq(काष्ठा irq_data *data)
अणु
	पूर्णांक bit;
	पूर्णांक irq = data->irq - 12;

	bit = ipr_bit[irq];
	अगर (bit >= 0) अणु
		अगर (bit < 8)
			ctrl_bclr(bit & 7, IPR);
		अन्यथा
			ctrl_bclr(bit & 7, (IPR+1));
	पूर्ण
पूर्ण

अटल व्योम h8300h_enable_irq(काष्ठा irq_data *data)
अणु
	पूर्णांक bit;
	पूर्णांक irq = data->irq - 12;

	bit = ipr_bit[irq];
	अगर (bit >= 0) अणु
		अगर (bit < 8)
			ctrl_bset(bit & 7, IPR);
		अन्यथा
			ctrl_bset(bit & 7, (IPR+1));
	पूर्ण
पूर्ण

काष्ठा irq_chip h8300h_irq_chip = अणु
	.name		= "H8/300H-INTC",
	.irq_enable	= h8300h_enable_irq,
	.irq_disable	= h8300h_disable_irq,
पूर्ण;

अटल पूर्णांक irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
		   irq_hw_number_t hw_irq_num)
अणु
       irq_set_chip_and_handler(virq, &h8300h_irq_chip, handle_simple_irq);

       वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops irq_ops = अणु
       .map    = irq_map,
       .xlate  = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल पूर्णांक __init h8300h_पूर्णांकc_of_init(काष्ठा device_node *पूर्णांकc,
				      काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;

	पूर्णांकc_baseaddr = of_iomap(पूर्णांकc, 0);
	BUG_ON(!पूर्णांकc_baseaddr);

	/* All पूर्णांकerrupt priority low */
	ग_लिखोb(0x00, IPR + 0);
	ग_लिखोb(0x00, IPR + 1);

	करोमुख्य = irq_करोमुख्य_add_linear(पूर्णांकc, NR_IRQS, &irq_ops, शून्य);
	BUG_ON(!करोमुख्य);
	irq_set_शेष_host(करोमुख्य);
	वापस 0;
पूर्ण

IRQCHIP_DECLARE(h8300h_पूर्णांकc, "renesas,h8300h-intc", h8300h_पूर्णांकc_of_init);
