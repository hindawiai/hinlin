<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * RDA8810PL SoC irqchip driver
 *
 * Copyright RDA Microelectronics Company Limited
 * Copyright (c) 2017 Andreas Fथअrber
 * Copyright (c) 2018 Manivannan Sadhasivam
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/exception.h>

#घोषणा RDA_INTC_FINALSTATUS	0x00
#घोषणा RDA_INTC_MASK_SET	0x08
#घोषणा RDA_INTC_MASK_CLR	0x0c

#घोषणा RDA_IRQ_MASK_ALL	0xFFFFFFFF

#घोषणा RDA_NR_IRQS 32

अटल व्योम __iomem *rda_पूर्णांकc_base;
अटल काष्ठा irq_करोमुख्य *rda_irq_करोमुख्य;

अटल व्योम rda_पूर्णांकc_mask_irq(काष्ठा irq_data *d)
अणु
	ग_लिखोl_relaxed(BIT(d->hwirq), rda_पूर्णांकc_base + RDA_INTC_MASK_CLR);
पूर्ण

अटल व्योम rda_पूर्णांकc_unmask_irq(काष्ठा irq_data *d)
अणु
	ग_लिखोl_relaxed(BIT(d->hwirq), rda_पूर्णांकc_base + RDA_INTC_MASK_SET);
पूर्ण

अटल पूर्णांक rda_पूर्णांकc_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक flow_type)
अणु
	/* Hardware supports only level triggered पूर्णांकerrupts */
	अगर ((flow_type & (IRQF_TRIGGER_HIGH | IRQF_TRIGGER_LOW)) == flow_type)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल व्योम __exception_irq_entry rda_handle_irq(काष्ठा pt_regs *regs)
अणु
	u32 stat = पढ़ोl_relaxed(rda_पूर्णांकc_base + RDA_INTC_FINALSTATUS);
	u32 hwirq;

	जबतक (stat) अणु
		hwirq = __fls(stat);
		handle_करोमुख्य_irq(rda_irq_करोमुख्य, hwirq, regs);
		stat &= ~BIT(hwirq);
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip rda_irq_chip = अणु
	.name		= "rda-intc",
	.irq_mask	= rda_पूर्णांकc_mask_irq,
	.irq_unmask	= rda_पूर्णांकc_unmask_irq,
	.irq_set_type	= rda_पूर्णांकc_set_type,
पूर्ण;

अटल पूर्णांक rda_irq_map(काष्ठा irq_करोमुख्य *d,
		       अचिन्हित पूर्णांक virq, irq_hw_number_t hw)
अणु
	irq_set_status_flags(virq, IRQ_LEVEL);
	irq_set_chip_and_handler(virq, &rda_irq_chip, handle_level_irq);
	irq_set_chip_data(virq, d->host_data);
	irq_set_probe(virq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops rda_irq_करोमुख्य_ops = अणु
	.map = rda_irq_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल पूर्णांक __init rda8810_पूर्णांकc_init(काष्ठा device_node *node,
				    काष्ठा device_node *parent)
अणु
	rda_पूर्णांकc_base = of_io_request_and_map(node, 0, "rda-intc");
	अगर (IS_ERR(rda_पूर्णांकc_base))
		वापस PTR_ERR(rda_पूर्णांकc_base);

	/* Mask all पूर्णांकerrupt sources */
	ग_लिखोl_relaxed(RDA_IRQ_MASK_ALL, rda_पूर्णांकc_base + RDA_INTC_MASK_CLR);

	rda_irq_करोमुख्य = irq_करोमुख्य_create_linear(&node->fwnode, RDA_NR_IRQS,
						  &rda_irq_करोमुख्य_ops,
						  rda_पूर्णांकc_base);
	अगर (!rda_irq_करोमुख्य) अणु
		iounmap(rda_पूर्णांकc_base);
		वापस -ENOMEM;
	पूर्ण

	set_handle_irq(rda_handle_irq);

	वापस 0;
पूर्ण

IRQCHIP_DECLARE(rda_पूर्णांकc, "rda,8810pl-intc", rda8810_पूर्णांकc_init);
