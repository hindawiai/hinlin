<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम MIPS Goldfish Programmable Interrupt Controller.
 *
 * Author: Miodrag Dinic <miodrag.dinic@mips.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#घोषणा GFPIC_NR_IRQS			32

/* 8..39 Cascaded Goldfish PIC पूर्णांकerrupts */
#घोषणा GFPIC_IRQ_BASE			8

#घोषणा GFPIC_REG_IRQ_PENDING		0x04
#घोषणा GFPIC_REG_IRQ_DISABLE_ALL	0x08
#घोषणा GFPIC_REG_IRQ_DISABLE		0x0c
#घोषणा GFPIC_REG_IRQ_ENABLE		0x10

काष्ठा goldfish_pic_data अणु
	व्योम __iomem *base;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
पूर्ण;

अटल व्योम goldfish_pic_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा goldfish_pic_data *gfpic = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *host_chip = irq_desc_get_chip(desc);
	u32 pending, hwirq, virq;

	chained_irq_enter(host_chip, desc);

	pending = पढ़ोl(gfpic->base + GFPIC_REG_IRQ_PENDING);
	जबतक (pending) अणु
		hwirq = __fls(pending);
		virq = irq_linear_revmap(gfpic->irq_करोमुख्य, hwirq);
		generic_handle_irq(virq);
		pending &= ~(1 << hwirq);
	पूर्ण

	chained_irq_निकास(host_chip, desc);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops goldfish_irq_करोमुख्य_ops = अणु
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल पूर्णांक __init goldfish_pic_of_init(काष्ठा device_node *of_node,
				       काष्ठा device_node *parent)
अणु
	काष्ठा goldfish_pic_data *gfpic;
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;
	अचिन्हित पूर्णांक parent_irq;
	पूर्णांक ret = 0;

	gfpic = kzalloc(माप(*gfpic), GFP_KERNEL);
	अगर (!gfpic) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	parent_irq = irq_of_parse_and_map(of_node, 0);
	अगर (!parent_irq) अणु
		pr_err("Failed to map parent IRQ!\n");
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	gfpic->base = of_iomap(of_node, 0);
	अगर (!gfpic->base) अणु
		pr_err("Failed to map base address!\n");
		ret = -ENOMEM;
		जाओ out_unmap_irq;
	पूर्ण

	/* Mask पूर्णांकerrupts. */
	ग_लिखोl(1, gfpic->base + GFPIC_REG_IRQ_DISABLE_ALL);

	gc = irq_alloc_generic_chip("GFPIC", 1, GFPIC_IRQ_BASE, gfpic->base,
				    handle_level_irq);
	अगर (!gc) अणु
		pr_err("Failed to allocate chip structures!\n");
		ret = -ENOMEM;
		जाओ out_iounmap;
	पूर्ण

	ct = gc->chip_types;
	ct->regs.enable = GFPIC_REG_IRQ_ENABLE;
	ct->regs.disable = GFPIC_REG_IRQ_DISABLE;
	ct->chip.irq_unmask = irq_gc_unmask_enable_reg;
	ct->chip.irq_mask = irq_gc_mask_disable_reg;

	irq_setup_generic_chip(gc, IRQ_MSK(GFPIC_NR_IRQS), 0,
			       IRQ_NOPROBE | IRQ_LEVEL, 0);

	gfpic->irq_करोमुख्य = irq_करोमुख्य_add_legacy(of_node, GFPIC_NR_IRQS,
						  GFPIC_IRQ_BASE, 0,
						  &goldfish_irq_करोमुख्य_ops,
						  शून्य);
	अगर (!gfpic->irq_करोमुख्य) अणु
		pr_err("Failed to add irqdomain!\n");
		ret = -ENOMEM;
		जाओ out_destroy_generic_chip;
	पूर्ण

	irq_set_chained_handler_and_data(parent_irq,
					 goldfish_pic_cascade, gfpic);

	pr_info("Successfully registered.\n");
	वापस 0;

out_destroy_generic_chip:
	irq_destroy_generic_chip(gc, IRQ_MSK(GFPIC_NR_IRQS),
				 IRQ_NOPROBE | IRQ_LEVEL, 0);
out_iounmap:
	iounmap(gfpic->base);
out_unmap_irq:
	irq_dispose_mapping(parent_irq);
out_मुक्त:
	kमुक्त(gfpic);
out_err:
	pr_err("Failed to initialize! (errno = %d)\n", ret);
	वापस ret;
पूर्ण

IRQCHIP_DECLARE(google_gf_pic, "google,goldfish-pic", goldfish_pic_of_init);
