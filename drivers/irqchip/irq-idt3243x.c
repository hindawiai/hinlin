<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम IDT/Renesas 79RC3243x Interrupt Controller.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#घोषणा IDT_PIC_NR_IRQS		32

#घोषणा IDT_PIC_IRQ_PEND		0x00
#घोषणा IDT_PIC_IRQ_MASK		0x08

काष्ठा idt_pic_data अणु
	व्योम __iomem *base;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	काष्ठा irq_chip_generic *gc;
पूर्ण;

अटल व्योम idt_irq_dispatch(काष्ठा irq_desc *desc)
अणु
	काष्ठा idt_pic_data *idtpic = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *host_chip = irq_desc_get_chip(desc);
	u32 pending, hwirq, virq;

	chained_irq_enter(host_chip, desc);

	pending = irq_reg_पढ़ोl(idtpic->gc, IDT_PIC_IRQ_PEND);
	pending &= ~idtpic->gc->mask_cache;
	जबतक (pending) अणु
		hwirq = __fls(pending);
		virq = irq_linear_revmap(idtpic->irq_करोमुख्य, hwirq);
		अगर (virq)
			generic_handle_irq(virq);
		pending &= ~(1 << hwirq);
	पूर्ण

	chained_irq_निकास(host_chip, desc);
पूर्ण

अटल पूर्णांक idt_pic_init(काष्ठा device_node *of_node, काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा idt_pic_data *idtpic;
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;
	अचिन्हित पूर्णांक parent_irq;
	पूर्णांक ret = 0;

	idtpic = kzalloc(माप(*idtpic), GFP_KERNEL);
	अगर (!idtpic) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	parent_irq = irq_of_parse_and_map(of_node, 0);
	अगर (!parent_irq) अणु
		pr_err("Failed to map parent IRQ!\n");
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	idtpic->base = of_iomap(of_node, 0);
	अगर (!idtpic->base) अणु
		pr_err("Failed to map base address!\n");
		ret = -ENOMEM;
		जाओ out_unmap_irq;
	पूर्ण

	करोमुख्य = irq_करोमुख्य_add_linear(of_node, IDT_PIC_NR_IRQS,
				       &irq_generic_chip_ops, शून्य);
	अगर (!करोमुख्य) अणु
		pr_err("Failed to add irqdomain!\n");
		ret = -ENOMEM;
		जाओ out_iounmap;
	पूर्ण
	idtpic->irq_करोमुख्य = करोमुख्य;

	ret = irq_alloc_करोमुख्य_generic_chips(करोमुख्य, 32, 1, "IDTPIC",
					     handle_level_irq, 0,
					     IRQ_NOPROBE | IRQ_LEVEL, 0);
	अगर (ret)
		जाओ out_करोमुख्य_हटाओ;

	gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);
	gc->reg_base = idtpic->base;
	gc->निजी = idtpic;

	ct = gc->chip_types;
	ct->regs.mask = IDT_PIC_IRQ_MASK;
	ct->chip.irq_mask = irq_gc_mask_set_bit;
	ct->chip.irq_unmask = irq_gc_mask_clr_bit;
	idtpic->gc = gc;

	/* Mask पूर्णांकerrupts. */
	ग_लिखोl(0xffffffff, idtpic->base + IDT_PIC_IRQ_MASK);
	gc->mask_cache = 0xffffffff;

	irq_set_chained_handler_and_data(parent_irq,
					 idt_irq_dispatch, idtpic);

	वापस 0;

out_करोमुख्य_हटाओ:
	irq_करोमुख्य_हटाओ(करोमुख्य);
out_iounmap:
	iounmap(idtpic->base);
out_unmap_irq:
	irq_dispose_mapping(parent_irq);
out_मुक्त:
	kमुक्त(idtpic);
out_err:
	pr_err("Failed to initialize! (errno = %d)\n", ret);
	वापस ret;
पूर्ण

IRQCHIP_DECLARE(idt_pic, "idt,32434-pic", idt_pic_init);
