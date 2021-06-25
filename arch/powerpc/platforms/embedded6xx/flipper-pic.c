<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/platक्रमms/embedded6xx/flipper-pic.c
 *
 * Nपूर्णांकenकरो GameCube/Wii "Flipper" पूर्णांकerrupt controller support.
 * Copyright (C) 2004-2009 The GameCube Linux Team
 * Copyright (C) 2007,2008,2009 Albert Herranz
 */
#घोषणा DRV_MODULE_NAME "flipper-pic"
#घोषणा pr_fmt(fmt) DRV_MODULE_NAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <यंत्र/पन.स>

#समावेश "flipper-pic.h"

#घोषणा FLIPPER_NR_IRQS		32

/*
 * Each पूर्णांकerrupt has a corresponding bit in both
 * the Interrupt Cause (ICR) and Interrupt Mask (IMR) रेजिस्टरs.
 *
 * Enabling/disabling an पूर्णांकerrupt line involves setting/clearing
 * the corresponding bit in IMR.
 * Except क्रम the RSW पूर्णांकerrupt, all पूर्णांकerrupts get deनिश्चितed स्वतःmatically
 * when the source deनिश्चितs the पूर्णांकerrupt.
 */
#घोषणा FLIPPER_ICR		0x00
#घोषणा FLIPPER_ICR_RSS		(1<<16) /* reset चयन state */

#घोषणा FLIPPER_IMR		0x04

#घोषणा FLIPPER_RESET		0x24


/*
 * IRQ chip hooks.
 *
 */

अटल व्योम flipper_pic_mask_and_ack(काष्ठा irq_data *d)
अणु
	पूर्णांक irq = irqd_to_hwirq(d);
	व्योम __iomem *io_base = irq_data_get_irq_chip_data(d);
	u32 mask = 1 << irq;

	clrbits32(io_base + FLIPPER_IMR, mask);
	/* this is at least needed क्रम RSW */
	out_be32(io_base + FLIPPER_ICR, mask);
पूर्ण

अटल व्योम flipper_pic_ack(काष्ठा irq_data *d)
अणु
	पूर्णांक irq = irqd_to_hwirq(d);
	व्योम __iomem *io_base = irq_data_get_irq_chip_data(d);

	/* this is at least needed क्रम RSW */
	out_be32(io_base + FLIPPER_ICR, 1 << irq);
पूर्ण

अटल व्योम flipper_pic_mask(काष्ठा irq_data *d)
अणु
	पूर्णांक irq = irqd_to_hwirq(d);
	व्योम __iomem *io_base = irq_data_get_irq_chip_data(d);

	clrbits32(io_base + FLIPPER_IMR, 1 << irq);
पूर्ण

अटल व्योम flipper_pic_unmask(काष्ठा irq_data *d)
अणु
	पूर्णांक irq = irqd_to_hwirq(d);
	व्योम __iomem *io_base = irq_data_get_irq_chip_data(d);

	setbits32(io_base + FLIPPER_IMR, 1 << irq);
पूर्ण


अटल काष्ठा irq_chip flipper_pic = अणु
	.name		= "flipper-pic",
	.irq_ack	= flipper_pic_ack,
	.irq_mask_ack	= flipper_pic_mask_and_ack,
	.irq_mask	= flipper_pic_mask,
	.irq_unmask	= flipper_pic_unmask,
पूर्ण;

/*
 * IRQ host hooks.
 *
 */

अटल काष्ठा irq_करोमुख्य *flipper_irq_host;

अटल पूर्णांक flipper_pic_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			   irq_hw_number_t hwirq)
अणु
	irq_set_chip_data(virq, h->host_data);
	irq_set_status_flags(virq, IRQ_LEVEL);
	irq_set_chip_and_handler(virq, &flipper_pic, handle_level_irq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops flipper_irq_करोमुख्य_ops = अणु
	.map = flipper_pic_map,
पूर्ण;

/*
 * Platक्रमm hooks.
 *
 */

अटल व्योम __flipper_quiesce(व्योम __iomem *io_base)
अणु
	/* mask and ack all IRQs */
	out_be32(io_base + FLIPPER_IMR, 0x00000000);
	out_be32(io_base + FLIPPER_ICR, 0xffffffff);
पूर्ण

अटल काष्ठा irq_करोमुख्य * __init flipper_pic_init(काष्ठा device_node *np)
अणु
	काष्ठा device_node *pi;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य = शून्य;
	काष्ठा resource res;
	व्योम __iomem *io_base;
	पूर्णांक retval;

	pi = of_get_parent(np);
	अगर (!pi) अणु
		pr_err("no parent found\n");
		जाओ out;
	पूर्ण
	अगर (!of_device_is_compatible(pi, "nintendo,flipper-pi")) अणु
		pr_err("unexpected parent compatible\n");
		जाओ out;
	पूर्ण

	retval = of_address_to_resource(pi, 0, &res);
	अगर (retval) अणु
		pr_err("no io memory range found\n");
		जाओ out;
	पूर्ण
	io_base = ioremap(res.start, resource_size(&res));

	pr_info("controller at 0x%08x mapped to 0x%p\n", res.start, io_base);

	__flipper_quiesce(io_base);

	irq_करोमुख्य = irq_करोमुख्य_add_linear(np, FLIPPER_NR_IRQS,
				  &flipper_irq_करोमुख्य_ops, io_base);
	अगर (!irq_करोमुख्य) अणु
		pr_err("failed to allocate irq_domain\n");
		वापस शून्य;
	पूर्ण

out:
	वापस irq_करोमुख्य;
पूर्ण

अचिन्हित पूर्णांक flipper_pic_get_irq(व्योम)
अणु
	व्योम __iomem *io_base = flipper_irq_host->host_data;
	पूर्णांक irq;
	u32 irq_status;

	irq_status = in_be32(io_base + FLIPPER_ICR) &
		     in_be32(io_base + FLIPPER_IMR);
	अगर (irq_status == 0)
		वापस 0;	/* no more IRQs pending */

	irq = __ffs(irq_status);
	वापस irq_linear_revmap(flipper_irq_host, irq);
पूर्ण

/*
 * Probe function.
 *
 */

व्योम __init flipper_pic_probe(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "nintendo,flipper-pic");
	BUG_ON(!np);

	flipper_irq_host = flipper_pic_init(np);
	BUG_ON(!flipper_irq_host);

	irq_set_शेष_host(flipper_irq_host);

	of_node_put(np);
पूर्ण

/*
 * Misc functions related to the flipper chipset.
 *
 */

/**
 * flipper_quiesce() - quiesce flipper irq controller
 *
 * Mask and ack all पूर्णांकerrupt sources.
 *
 */
व्योम flipper_quiesce(व्योम)
अणु
	व्योम __iomem *io_base = flipper_irq_host->host_data;

	__flipper_quiesce(io_base);
पूर्ण

/*
 * Resets the platक्रमm.
 */
व्योम flipper_platक्रमm_reset(व्योम)
अणु
	व्योम __iomem *io_base;

	अगर (flipper_irq_host && flipper_irq_host->host_data) अणु
		io_base = flipper_irq_host->host_data;
		out_8(io_base + FLIPPER_RESET, 0x00);
	पूर्ण
पूर्ण

/*
 * Returns non-zero अगर the reset button is pressed.
 */
पूर्णांक flipper_is_reset_button_pressed(व्योम)
अणु
	व्योम __iomem *io_base;
	u32 icr;

	अगर (flipper_irq_host && flipper_irq_host->host_data) अणु
		io_base = flipper_irq_host->host_data;
		icr = in_be32(io_base + FLIPPER_ICR);
		वापस !(icr & FLIPPER_ICR_RSS);
	पूर्ण
	वापस 0;
पूर्ण

