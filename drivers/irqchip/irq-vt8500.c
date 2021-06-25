<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  arch/arm/mach-vt8500/irq.c
 *
 *  Copyright (C) 2012 Tony Prisk <linux@prisktech.co.nz>
 *  Copyright (C) 2010 Alexey Charkov <alअक्षरk@gmail.com>
 */

/*
 * This file is copied and modअगरied from the original irq.c provided by
 * Alexey Charkov. Minor changes have been made क्रम Device Tree Support.
 */

#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bitops.h>

#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/mach/irq.h>

#घोषणा VT8500_ICPC_IRQ		0x20
#घोषणा VT8500_ICPC_FIQ		0x24
#घोषणा VT8500_ICDC		0x40		/* Destination Control 64*u32 */
#घोषणा VT8500_ICIS		0x80		/* Interrupt status, 16*u32 */

/* ICPC */
#घोषणा ICPC_MASK		0x3F
#घोषणा ICPC_ROTATE		BIT(6)

/* IC_DCTR */
#घोषणा ICDC_IRQ		0x00
#घोषणा ICDC_FIQ		0x01
#घोषणा ICDC_DSS0		0x02
#घोषणा ICDC_DSS1		0x03
#घोषणा ICDC_DSS2		0x04
#घोषणा ICDC_DSS3		0x05
#घोषणा ICDC_DSS4		0x06
#घोषणा ICDC_DSS5		0x07

#घोषणा VT8500_INT_DISABLE	0
#घोषणा VT8500_INT_ENABLE	BIT(3)

#घोषणा VT8500_TRIGGER_HIGH	0
#घोषणा VT8500_TRIGGER_RISING	BIT(5)
#घोषणा VT8500_TRIGGER_FALLING	BIT(6)
#घोषणा VT8500_EDGE		( VT8500_TRIGGER_RISING \
				| VT8500_TRIGGER_FALLING)

/* vt8500 has 1 पूर्णांकc, wm8505 and wm8650 have 2 */
#घोषणा VT8500_INTC_MAX		2

काष्ठा vt8500_irq_data अणु
	व्योम __iomem 		*base;		/* IO Memory base address */
	काष्ठा irq_करोमुख्य	*करोमुख्य;	/* Doमुख्य क्रम this controller */
पूर्ण;

/* Global variable क्रम accessing io-mem addresses */
अटल काष्ठा vt8500_irq_data पूर्णांकc[VT8500_INTC_MAX];
अटल u32 active_cnt = 0;

अटल व्योम vt8500_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा vt8500_irq_data *priv = d->करोमुख्य->host_data;
	व्योम __iomem *base = priv->base;
	व्योम __iomem *stat_reg = base + VT8500_ICIS + (d->hwirq < 32 ? 0 : 4);
	u8 edge, dctr;
	u32 status;

	edge = पढ़ोb(base + VT8500_ICDC + d->hwirq) & VT8500_EDGE;
	अगर (edge) अणु
		status = पढ़ोl(stat_reg);

		status |= (1 << (d->hwirq & 0x1f));
		ग_लिखोl(status, stat_reg);
	पूर्ण अन्यथा अणु
		dctr = पढ़ोb(base + VT8500_ICDC + d->hwirq);
		dctr &= ~VT8500_INT_ENABLE;
		ग_लिखोb(dctr, base + VT8500_ICDC + d->hwirq);
	पूर्ण
पूर्ण

अटल व्योम vt8500_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा vt8500_irq_data *priv = d->करोमुख्य->host_data;
	व्योम __iomem *base = priv->base;
	u8 dctr;

	dctr = पढ़ोb(base + VT8500_ICDC + d->hwirq);
	dctr |= VT8500_INT_ENABLE;
	ग_लिखोb(dctr, base + VT8500_ICDC + d->hwirq);
पूर्ण

अटल पूर्णांक vt8500_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा vt8500_irq_data *priv = d->करोमुख्य->host_data;
	व्योम __iomem *base = priv->base;
	u8 dctr;

	dctr = पढ़ोb(base + VT8500_ICDC + d->hwirq);
	dctr &= ~VT8500_EDGE;

	चयन (flow_type) अणु
	हाल IRQF_TRIGGER_LOW:
		वापस -EINVAL;
	हाल IRQF_TRIGGER_HIGH:
		dctr |= VT8500_TRIGGER_HIGH;
		irq_set_handler_locked(d, handle_level_irq);
		अवरोध;
	हाल IRQF_TRIGGER_FALLING:
		dctr |= VT8500_TRIGGER_FALLING;
		irq_set_handler_locked(d, handle_edge_irq);
		अवरोध;
	हाल IRQF_TRIGGER_RISING:
		dctr |= VT8500_TRIGGER_RISING;
		irq_set_handler_locked(d, handle_edge_irq);
		अवरोध;
	पूर्ण
	ग_लिखोb(dctr, base + VT8500_ICDC + d->hwirq);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip vt8500_irq_chip = अणु
	.name = "vt8500",
	.irq_ack = vt8500_irq_mask,
	.irq_mask = vt8500_irq_mask,
	.irq_unmask = vt8500_irq_unmask,
	.irq_set_type = vt8500_irq_set_type,
पूर्ण;

अटल व्योम __init vt8500_init_irq_hw(व्योम __iomem *base)
अणु
	u32 i;

	/* Enable rotating priority क्रम IRQ */
	ग_लिखोl(ICPC_ROTATE, base + VT8500_ICPC_IRQ);
	ग_लिखोl(0x00, base + VT8500_ICPC_FIQ);

	/* Disable all पूर्णांकerrupts and route them to IRQ */
	क्रम (i = 0; i < 64; i++)
		ग_लिखोb(VT8500_INT_DISABLE | ICDC_IRQ, base + VT8500_ICDC + i);
पूर्ण

अटल पूर्णांक vt8500_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
							irq_hw_number_t hw)
अणु
	irq_set_chip_and_handler(virq, &vt8500_irq_chip, handle_level_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops vt8500_irq_करोमुख्य_ops = अणु
	.map = vt8500_irq_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल व्योम __exception_irq_entry vt8500_handle_irq(काष्ठा pt_regs *regs)
अणु
	u32 stat, i;
	पूर्णांक irqnr;
	व्योम __iomem *base;

	/* Loop through each active controller */
	क्रम (i=0; i<active_cnt; i++) अणु
		base = पूर्णांकc[i].base;
		irqnr = पढ़ोl_relaxed(base) & 0x3F;
		/*
		  Highest Priority रेजिस्टर शेष = 63, so check that this
		  is a real पूर्णांकerrupt by checking the status रेजिस्टर
		*/
		अगर (irqnr == 63) अणु
			stat = पढ़ोl_relaxed(base + VT8500_ICIS + 4);
			अगर (!(stat & BIT(31)))
				जारी;
		पूर्ण

		handle_करोमुख्य_irq(पूर्णांकc[i].करोमुख्य, irqnr, regs);
	पूर्ण
पूर्ण

अटल पूर्णांक __init vt8500_irq_init(काष्ठा device_node *node,
				  काष्ठा device_node *parent)
अणु
	पूर्णांक irq, i;
	काष्ठा device_node *np = node;

	अगर (active_cnt == VT8500_INTC_MAX) अणु
		pr_err("%s: Interrupt controllers > VT8500_INTC_MAX\n",
								__func__);
		जाओ out;
	पूर्ण

	पूर्णांकc[active_cnt].base = of_iomap(np, 0);
	पूर्णांकc[active_cnt].करोमुख्य = irq_करोमुख्य_add_linear(node, 64,
			&vt8500_irq_करोमुख्य_ops,	&पूर्णांकc[active_cnt]);

	अगर (!पूर्णांकc[active_cnt].base) अणु
		pr_err("%s: Unable to map IO memory\n", __func__);
		जाओ out;
	पूर्ण

	अगर (!पूर्णांकc[active_cnt].करोमुख्य) अणु
		pr_err("%s: Unable to add irq domain!\n", __func__);
		जाओ out;
	पूर्ण

	set_handle_irq(vt8500_handle_irq);

	vt8500_init_irq_hw(पूर्णांकc[active_cnt].base);

	pr_info("vt8500-irq: Added interrupt controller\n");

	active_cnt++;

	/* check अगर this is a slaved controller */
	अगर (of_irq_count(np) != 0) अणु
		/* check that we have the correct number of पूर्णांकerrupts */
		अगर (of_irq_count(np) != 8) अणु
			pr_err("%s: Incorrect IRQ map for slaved controller\n",
					__func__);
			वापस -EINVAL;
		पूर्ण

		क्रम (i = 0; i < 8; i++) अणु
			irq = irq_of_parse_and_map(np, i);
			enable_irq(irq);
		पूर्ण

		pr_info("vt8500-irq: Enabled slave->parent interrupts\n");
	पूर्ण
out:
	वापस 0;
पूर्ण

IRQCHIP_DECLARE(vt8500_irq, "via,vt8500-intc", vt8500_irq_init);
