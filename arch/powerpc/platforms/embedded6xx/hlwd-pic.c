<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/platक्रमms/embedded6xx/hlwd-pic.c
 *
 * Nपूर्णांकenकरो Wii "Hollywood" पूर्णांकerrupt controller support.
 * Copyright (C) 2009 The GameCube Linux Team
 * Copyright (C) 2009 Albert Herranz
 */
#घोषणा DRV_MODULE_NAME "hlwd-pic"
#घोषणा pr_fmt(fmt) DRV_MODULE_NAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <यंत्र/पन.स>

#समावेश "hlwd-pic.h"

#घोषणा HLWD_NR_IRQS	32

/*
 * Each पूर्णांकerrupt has a corresponding bit in both
 * the Interrupt Cause (ICR) and Interrupt Mask (IMR) रेजिस्टरs.
 *
 * Enabling/disabling an पूर्णांकerrupt line involves निश्चितing/clearing
 * the corresponding bit in IMR. ACK'ing a request simply involves
 * निश्चितing the corresponding bit in ICR.
 */
#घोषणा HW_BROADWAY_ICR		0x00
#घोषणा HW_BROADWAY_IMR		0x04
#घोषणा HW_STARLET_ICR		0x08
#घोषणा HW_STARLET_IMR		0x0c


/*
 * IRQ chip hooks.
 *
 */

अटल व्योम hlwd_pic_mask_and_ack(काष्ठा irq_data *d)
अणु
	पूर्णांक irq = irqd_to_hwirq(d);
	व्योम __iomem *io_base = irq_data_get_irq_chip_data(d);
	u32 mask = 1 << irq;

	clrbits32(io_base + HW_BROADWAY_IMR, mask);
	out_be32(io_base + HW_BROADWAY_ICR, mask);
पूर्ण

अटल व्योम hlwd_pic_ack(काष्ठा irq_data *d)
अणु
	पूर्णांक irq = irqd_to_hwirq(d);
	व्योम __iomem *io_base = irq_data_get_irq_chip_data(d);

	out_be32(io_base + HW_BROADWAY_ICR, 1 << irq);
पूर्ण

अटल व्योम hlwd_pic_mask(काष्ठा irq_data *d)
अणु
	पूर्णांक irq = irqd_to_hwirq(d);
	व्योम __iomem *io_base = irq_data_get_irq_chip_data(d);

	clrbits32(io_base + HW_BROADWAY_IMR, 1 << irq);
पूर्ण

अटल व्योम hlwd_pic_unmask(काष्ठा irq_data *d)
अणु
	पूर्णांक irq = irqd_to_hwirq(d);
	व्योम __iomem *io_base = irq_data_get_irq_chip_data(d);

	setbits32(io_base + HW_BROADWAY_IMR, 1 << irq);

	/* Make sure the ARM (aka. Starlet) करोesn't handle this पूर्णांकerrupt. */
	clrbits32(io_base + HW_STARLET_IMR, 1 << irq);
पूर्ण


अटल काष्ठा irq_chip hlwd_pic = अणु
	.name		= "hlwd-pic",
	.irq_ack	= hlwd_pic_ack,
	.irq_mask_ack	= hlwd_pic_mask_and_ack,
	.irq_mask	= hlwd_pic_mask,
	.irq_unmask	= hlwd_pic_unmask,
पूर्ण;

/*
 * IRQ host hooks.
 *
 */

अटल काष्ठा irq_करोमुख्य *hlwd_irq_host;

अटल पूर्णांक hlwd_pic_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			   irq_hw_number_t hwirq)
अणु
	irq_set_chip_data(virq, h->host_data);
	irq_set_status_flags(virq, IRQ_LEVEL);
	irq_set_chip_and_handler(virq, &hlwd_pic, handle_level_irq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops hlwd_irq_करोमुख्य_ops = अणु
	.map = hlwd_pic_map,
पूर्ण;

अटल अचिन्हित पूर्णांक __hlwd_pic_get_irq(काष्ठा irq_करोमुख्य *h)
अणु
	व्योम __iomem *io_base = h->host_data;
	पूर्णांक irq;
	u32 irq_status;

	irq_status = in_be32(io_base + HW_BROADWAY_ICR) &
		     in_be32(io_base + HW_BROADWAY_IMR);
	अगर (irq_status == 0)
		वापस 0;	/* no more IRQs pending */

	irq = __ffs(irq_status);
	वापस irq_linear_revmap(h, irq);
पूर्ण

अटल व्योम hlwd_pic_irq_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा irq_करोमुख्य *irq_करोमुख्य = irq_desc_get_handler_data(desc);
	अचिन्हित पूर्णांक virq;

	raw_spin_lock(&desc->lock);
	chip->irq_mask(&desc->irq_data); /* IRQ_LEVEL */
	raw_spin_unlock(&desc->lock);

	virq = __hlwd_pic_get_irq(irq_करोमुख्य);
	अगर (virq)
		generic_handle_irq(virq);
	अन्यथा
		pr_err("spurious interrupt!\n");

	raw_spin_lock(&desc->lock);
	chip->irq_ack(&desc->irq_data); /* IRQ_LEVEL */
	अगर (!irqd_irq_disabled(&desc->irq_data) && chip->irq_unmask)
		chip->irq_unmask(&desc->irq_data);
	raw_spin_unlock(&desc->lock);
पूर्ण

/*
 * Platक्रमm hooks.
 *
 */

अटल व्योम __hlwd_quiesce(व्योम __iomem *io_base)
अणु
	/* mask and ack all IRQs */
	out_be32(io_base + HW_BROADWAY_IMR, 0);
	out_be32(io_base + HW_BROADWAY_ICR, 0xffffffff);
पूर्ण

अटल काष्ठा irq_करोमुख्य *hlwd_pic_init(काष्ठा device_node *np)
अणु
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	काष्ठा resource res;
	व्योम __iomem *io_base;
	पूर्णांक retval;

	retval = of_address_to_resource(np, 0, &res);
	अगर (retval) अणु
		pr_err("no io memory range found\n");
		वापस शून्य;
	पूर्ण
	io_base = ioremap(res.start, resource_size(&res));
	अगर (!io_base) अणु
		pr_err("ioremap failed\n");
		वापस शून्य;
	पूर्ण

	pr_info("controller at 0x%08x mapped to 0x%p\n", res.start, io_base);

	__hlwd_quiesce(io_base);

	irq_करोमुख्य = irq_करोमुख्य_add_linear(np, HLWD_NR_IRQS,
					   &hlwd_irq_करोमुख्य_ops, io_base);
	अगर (!irq_करोमुख्य) अणु
		pr_err("failed to allocate irq_domain\n");
		iounmap(io_base);
		वापस शून्य;
	पूर्ण

	वापस irq_करोमुख्य;
पूर्ण

अचिन्हित पूर्णांक hlwd_pic_get_irq(व्योम)
अणु
	वापस __hlwd_pic_get_irq(hlwd_irq_host);
पूर्ण

/*
 * Probe function.
 *
 */

व्योम hlwd_pic_probe(व्योम)
अणु
	काष्ठा irq_करोमुख्य *host;
	काष्ठा device_node *np;
	स्थिर u32 *पूर्णांकerrupts;
	पूर्णांक cascade_virq;

	क्रम_each_compatible_node(np, शून्य, "nintendo,hollywood-pic") अणु
		पूर्णांकerrupts = of_get_property(np, "interrupts", शून्य);
		अगर (पूर्णांकerrupts) अणु
			host = hlwd_pic_init(np);
			BUG_ON(!host);
			cascade_virq = irq_of_parse_and_map(np, 0);
			irq_set_handler_data(cascade_virq, host);
			irq_set_chained_handler(cascade_virq,
						hlwd_pic_irq_cascade);
			hlwd_irq_host = host;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * hlwd_quiesce() - quiesce hollywood irq controller
 *
 * Mask and ack all पूर्णांकerrupt sources.
 *
 */
व्योम hlwd_quiesce(व्योम)
अणु
	व्योम __iomem *io_base = hlwd_irq_host->host_data;

	__hlwd_quiesce(io_base);
पूर्ण

